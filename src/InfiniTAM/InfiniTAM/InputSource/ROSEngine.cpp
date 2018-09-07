// authored by https://github.com/ravich2-7183

#include "ROSEngine.h"
#include <stdio.h>
#include "../ORUtils/FileUtils.h"

using namespace std;
using namespace ORUtils;
using namespace InputSource;
using namespace sensor_msgs;
using namespace message_filters;
using namespace ITMLib;

std::vector<double> qToRPY(std::vector<double> q) {
    double x = q[0];
    double y = q[1];
    double z = q[2];
    double w = q[3];
    std::vector<double> rpy = {0, 0, 0};

    double sinr = +2.0 * (w * x + y * z);
    double cosr = +1.0 - 2.0 * (x * x + y * y);
    rpy[0] = atan2(sinr, cosr);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (w * y - z * x);
    if (fabs(sinp) >= 1) {
        rpy[1] = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    }
    else {
        rpy[1] = asin(sinp);
    }

    // yaw (z-axis rotation)
    double siny = +2.0 * (w * z + x * y);
    double cosy = +1.0 - 2.0 * (y * y + z * z);
    rpy[2] = atan2(siny, cosy);

    return rpy;
}

std::vector<double> rpyToQ(std::vector<double> rpy) {
    std::vector<double> q = {0, 0, 0, 0};
    double roll = rpy[0];
    double pitch = rpy[1];
    double yaw = rpy[2];
    double t0 = std::cos(yaw * 0.5f);
    double t1 = std::sin(yaw * 0.5f);
    double t2 = std::cos(roll * 0.5f);
    double t3 = std::sin(roll * 0.5f);
    double t4 = std::cos(pitch * 0.5f);
    double t5 = std::sin(pitch * 0.5f);

    q[3] = t0 * t2 * t4 + t1 * t3 * t5;
    q[0] = t0 * t3 * t4 - t1 * t2 * t5;
    q[1] = t0 * t2 * t5 + t1 * t3 * t4;
    q[2] = t1 * t2 * t4 - t0 * t3 * t5;
    return q;
}

void ROSEngine::processMessage(const ImageConstPtr& rgb_image_msg, const ImageConstPtr& depth_image_msg, const ImuConstPtr& imu_msg)
{
	std::lock_guard<std::mutex> process_message_lock(images_mutex_);

	// copy rgb_image_msg into rgb_image_
	Vector4u *rgb = rgb_image_.GetData(MEMORYDEVICE_CPU);
	for(int i = 0; i < rgb_image_.noDims.x * rgb_image_.noDims.y; i++) {
		Vector4u newPix;
		newPix.x = (rgb_image_msg->data)[i*3+2];
		newPix.y = (rgb_image_msg->data)[i*3+1];
		newPix.z = (rgb_image_msg->data)[i*3+0];
		newPix.w = 255;

		rgb[i] = newPix;
	}

	// copy depth_image_msg into depth_image_
	short *depth = depth_image_.GetData(MEMORYDEVICE_CPU);
	const short *depth_msg_data  = reinterpret_cast<const short*>(depth_image_msg->data.data());
	for(int i = 0; i < depth_image_.noDims.x * depth_image_.noDims.y; i++) {
		depth[i] = depth_msg_data[i];
	}

	imuSource->cached_imu = new ITMIMUMeasurement();

	std::vector<double> quaternion = {0, 0, 0, 0};
	quaternion[0] = (imu_msg->orientation.x);
    quaternion[1] = (imu_msg->orientation.y);
    quaternion[2] = (imu_msg->orientation.z);
    quaternion[3] = (imu_msg->orientation.w);
    //convert quaternion to euler
    std::vector<double> rpy = qToRPY(quaternion);

	double yaw = rpy[2];

    if (yaw < 0) {
        yaw = yaw + 2 * M_PI;
    }

    double t = double(imu_msg->header.stamp.sec) + double(imu_msg->header.stamp.nsec) * 1e-9;

	if (imuSource->currentFrameNo <= 0) {
        pre_yaw = yaw;
        pre_t = t;
		avg_x_accel = imu_msg->linear_acceleration.x;
    }
    else if ((t - pre_t) >= 0.1){
	    //detect robot motion
        avg_x_accel = (avg_x_accel + imu_msg->linear_acceleration.x) / 2;
        double yaw_diff = yaw - pre_yaw;
        double accel_diff = avg_x_accel - pre_avg_x_accel;

        if ((accel_diff < -0.1 || accel_diff > 0.1) && abs(yaw_diff) < M_PI / 180 * 5){
            imuSource->state = "forward/reverse";
        }
        else if (yaw_diff > M_PI / 180 * 1) {
            imuSource->state = "left";
        }
        else if (yaw_diff < M_PI / 180 * -1) {
            imuSource->state = "right";
        }
		else {
            imuSource->state = "no motion";
        }
        pre_yaw = yaw;
        pre_t = t;
    }
    else {
        avg_x_accel = (avg_x_accel + imu_msg->linear_acceleration.x) / 2;
	}
    pre_avg_x_accel = avg_x_accel;

	if (imuSource->state == "left" || imuSource->state == "right") {
        //constraint pitch roll
        rpy[0] = pre_rpy[0];
        rpy[1] = pre_rpy[1];
	}
	else if (imuSource->state == "forward" || imuSource->state == "reverse") {
	    //contraint roll yaw
        rpy[2] = pre_rpy[0];
        rpy[2] = pre_rpy[2];
	}
	else if (imuSource->state == "no motion") {
        rpy = pre_rpy;
	}
	pre_rpy = rpy;
    //convert euler to quaternion
	quaternion = rpyToQ(rpy);

    double x = quaternion[0];
    double y = quaternion[1];
    double z = quaternion[2];
    double w = quaternion[3];

	imuSource->cached_imu->R.m00 = 1-2*y*y-2*z*z;
	imuSource->cached_imu->R.m01 = 2*x*y-2*z*w;
	imuSource->cached_imu->R.m02 = 2*x*z+2*y*w;
	imuSource->cached_imu->R.m10 = 2*x*y+2*z*w;
	imuSource->cached_imu->R.m11 = 1-2*x*x-2*z*z;
	imuSource->cached_imu->R.m12 = 2*y*z-2*x*w;
	imuSource->cached_imu->R.m20 = 2*x*z-2*y*w;
	imuSource->cached_imu->R.m21 = 2*y*z+2*x*w;
	imuSource->cached_imu->R.m22 = 1-2*x*x-2*y*y;
}

void ROSEngine::topicListenerThread()
{
	// subscribe to rgb and depth topics
    message_filters::Subscriber<sensor_msgs::Image> rgb_sub_(nh_, "/camera/color/image_raw", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub_(nh_, "/camera/depth/image_rect_raw", 1);
    //message_filters::Subscriber<sensor_msgs::Image> depth_sub_(nh_, "/camera/aligned_depth_to_color/image_raw", 1);
	message_filters::Subscriber<sensor_msgs::Imu> imu_sub_(nh_, "/imu", 5);
	typedef sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Imu> ITAMSyncPolicy;
	Synchronizer<ITAMSyncPolicy> sync(ITAMSyncPolicy(10), rgb_sub_, depth_sub_, imu_sub_);
	sync.registerCallback(boost::bind(&ROSEngine::processMessage, this, _1, _2, _3));

	ros::spin();
}

ROSEngine::ROSEngine(const char *calibFilename,
					 Vector2i requested_imageSize_rgb,
					 Vector2i requested_imageSize_d) :
			BaseImageSourceEngine(calibFilename),
			nh_(),
			rgb_image_(requested_imageSize_rgb, MEMORYDEVICE_CPU),
			depth_image_(requested_imageSize_d, MEMORYDEVICE_CPU),
			topic_listener_thread(&ROSEngine::topicListenerThread, this) // Starts up topicListenerThread
{
	this->calib.disparityCalib.SetStandard(); // assumes depth is in millimeters
//	std::cout << this->calib.intrinsics_rgb.projectionParamsSimple.all << std::endl;
//	std::cout << this->calib.intrinsics_d.projectionParamsSimple.all << std::endl;
//    std::cout << this->calib.trafo_rgb_to_depth.calib << std::endl;
//    std::cout << this->calib.disparityCalib.GetParams() << std::endl;

//	ITMLib::readIntrinsics(src, this->calib.intrinsics_rgb);
//	ITMLib::readIntrinsics(src, this->calib.intrinsics_d);

}

void ROSEngine::getImages(ITMUChar4Image *rgbImage, ITMShortImage *rawDepthImage)
{
	std::lock_guard<std::mutex> get_images_lock(images_mutex_);

	rgbImage->SetFrom(&rgb_image_,        MemoryBlock<Vector4u>::CPU_TO_CPU); 
	rawDepthImage->SetFrom(&depth_image_, MemoryBlock<short>::CPU_TO_CPU);
}

bool ROSEngine::hasMoreImages(void) const
{
	return ros::ok();
}

Vector2i ROSEngine::getDepthImageSize(void) const
{
	return Vector2i(depth_image_.noDims.x , depth_image_.noDims.y);
}

Vector2i ROSEngine::getRGBImageSize(void) const
{
	return Vector2i(rgb_image_.noDims.x , rgb_image_.noDims.y);
}

ROSEngine::~ROSEngine()
{}

