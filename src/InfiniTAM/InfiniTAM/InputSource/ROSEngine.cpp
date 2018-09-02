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

//	bool bUsedCache = false;
//
//	if (cached_imu != NULL)
//	{
//		imu->R = cached_imu->R;
//		delete cached_imu;
//		cached_imu = NULL;
//		bUsedCache = true;
//	}
//
//	if (!bUsedCache) {
//		//load into cache

	imuSource->cached_imu = new ITMIMUMeasurement();

	float x = imu_msg->orientation.x;
	float y = imu_msg->orientation.y;
	float z = imu_msg->orientation.z;
	float w = imu_msg->orientation.w;

	double roll, pitch, yaw;
    // roll (x-axis rotation)
    double sinr = +2.0 * (w * x + y * z);
    double cosr = +1.0 - 2.0 * (x * x + y * y);
    roll = atan2(sinr, cosr);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (w * y - z * x);
    if (fabs(sinp) >= 1) {
        pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    }
    else {
        pitch = asin(sinp);
    }

    // yaw (z-axis rotation)
    double siny = +2.0 * (w * z + x * y);
    double cosy = +1.0 - 2.0 * (y * y + z * z);
    yaw = atan2(siny, cosy);

    //std::cout << "roll: " << roll * 180 / M_PI << " pitch: " << pitch * 180 / M_PI << " yaw: " << yaw * 180 / M_PI << std::endl;

    if (yaw < 0) {
        yaw = yaw + 2 * M_PI;
    }
    double t = double(imu_msg->header.stamp.sec) + double(imu_msg->header.stamp.nsec) * 1e-9;
    if (imuSource->currentFrameNo <= 0) {
        pre_yaw = yaw;
        pre_t = t;
    }
    else if ((t - pre_t) >= 0.2){
//        double yaw_diff = yaw - pre_yaw;
//        //   std::cout << yaw_diff << std::endl;
//        if (yaw_diff > M_PI / 180 * 10) {
//            robot_state = "rotating left";
//        }
//        else if (yaw_diff < M_PI / 180 * -10) {
//            robot_state = "rotating right";
//        }
//        else if (imu_msg->angular_velocity.y <= -0.35) {
//            robot_state = "forward";
//        }
//        else if (abs(imu_msg->angular_velocity.x) < 0.2 && abs(imu_msg->angular_velocity.y) < 0.2 && abs(imu_msg->angular_velocity.z < 0.2)) {
//            robot_state = "no motion";
//        }
//        std::cout << "motion: " << robot_state << std::endl;
//        std::cout << "vel.y: " << imu_msg->angular_velocity.y << std::endl;
//        std::cout << "yaw: " << yaw_diff << std::endl;
//        pre_yaw = yaw;
//        pre_t = t;
    }

//    std::cout << robot_state << std::endl;

	imuSource->cached_imu->R.m00 = 1-2*y*y-2*z*z;
	imuSource->cached_imu->R.m01 = 2*x*y-2*z*w;
	imuSource->cached_imu->R.m02 = 2*x*z+2*y*w;
	imuSource->cached_imu->R.m10 = 2*x*y+2*z*w;
	imuSource->cached_imu->R.m11 = 1-2*x*x-2*z*z;
	imuSource->cached_imu->R.m12 = 2*y*z-2*x*w;
	imuSource->cached_imu->R.m20 = 2*x*z-2*y*w;
	imuSource->cached_imu->R.m21 = 2*y*z+2*x*w;
	imuSource->cached_imu->R.m22 = 1-2*x*x-2*y*y;
//	}
//    std::cout << imuSource->currentFrameNo << std::endl;
//    std::cout << imu_msg->angular_velocity.x << " " << imu_msg->angular_velocity.y << " " << imu_msg->angular_velocity.z << std::endl;
}

void ROSEngine::topicListenerThread()
{
	// subscribe to rgb and depth topics
    message_filters::Subscriber<sensor_msgs::Image> rgb_sub_(nh_, "/camera/color/image_raw", 1);
    //message_filters::Subscriber<sensor_msgs::Image> depth_sub_(nh_, "/camera/depth/image_rect_raw", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub_(nh_, "/camera/aligned_depth_to_color/image_raw", 1);
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

