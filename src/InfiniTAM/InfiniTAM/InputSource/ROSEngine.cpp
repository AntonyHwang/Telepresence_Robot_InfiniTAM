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
//
//		cached_imu = new ITMIMUMeasurement();
//
//		float x = imu_msg->orientation.x;
//		float y = imu_msg->orientation.y;
//		float z = imu_msg->orientation.z;
//		float w = imu_msg->orientation.w;
//
//		cached_imu->R.m00 = 1-2*y*y-2*z*z;
//		cached_imu->R.m01 = 2*x*y-2*z*w;
//		cached_imu->R.m02 = 2*x*z+2*y*w;
//		cached_imu->R.m10 = 2*x*y+2*z*w;
//		cached_imu->R.m11 = 1-2*x*x-2*z*z;
//		cached_imu->R.m12 = 2*y*z-2*x*w;
//		cached_imu->R.m20 = 2*x*z-2*y*w;
//		cached_imu->R.m21 = 2*y*z+2*x*w;
//		cached_imu->R.m22 = 1-2*x*x-2*y*y;
//	}
//
//	++currentFrameNo;
}

void ROSEngine::topicListenerThread()
{
	// subscribe to rgb and depth topics
    message_filters::Subscriber<sensor_msgs::Image> rgb_sub_(nh_, "/camera/color/image_raw", 5);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub_(nh_, "/camera/depth/image_rect_raw", 5);
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

	currentFrameNo = 0;
	cachedFrameNo = -1;

	cached_imu = NULL;
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

void ROSEngine::loadIMUIntoCache(void)
{
	char str[2048]; FILE *f; bool success = false;

	cached_imu = new ITMIMUMeasurement();

	sprintf(str, imuMask, currentFrameNo);
	f = fopen(str, "r");
	if (f)
	{
		size_t ret = fscanf(f, "%f %f %f %f %f %f %f %f %f",
							&cached_imu->R.m00, &cached_imu->R.m01, &cached_imu->R.m02,
							&cached_imu->R.m10, &cached_imu->R.m11, &cached_imu->R.m12,
							&cached_imu->R.m20, &cached_imu->R.m21, &cached_imu->R.m22);

		fclose(f);

		if (ret == 9) success = true;
	}

	if (!success) {
		delete cached_imu; cached_imu = NULL;
		printf("error reading file '%s'\n", str);
	}
}

bool ROSEngine::hasMoreMeasurements(void)
{
	loadIMUIntoCache();

	return (cached_imu != NULL);
}

void ROSEngine::getMeasurement(ITMIMUMeasurement *imu)
{
	bool bUsedCache = false;

	if (cached_imu != NULL)
	{
		imu->R = cached_imu->R;
		delete cached_imu;
		cached_imu = NULL;
		bUsedCache = true;
	}

	if (!bUsedCache) this->loadIMUIntoCache();

	++currentFrameNo;
}

ROSEngine::~ROSEngine()
{}

