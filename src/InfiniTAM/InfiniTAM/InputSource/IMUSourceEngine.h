// Copyright 2014-2017 Oxford University Innovation Limited and the authors of InfiniTAM

#pragma once

#include "../ITMLib/Objects/Misc/ITMIMUMeasurement.h"

namespace InputSource {

class IMUSourceEngine
{

public:
	IMUSourceEngine();
	~IMUSourceEngine() { }

	ITMLib::ITMIMUMeasurement *cached_imu;

	//void loadIMUIntoCache();
	int cachedFrameNo;
	int currentFrameNo;
<<<<<<< HEAD
=======
	std::string state;
>>>>>>> develop

	bool hasMoreMeasurements(void);
	void getMeasurement(ITMLib::ITMIMUMeasurement *imu);
};

}
