/*
 * SensorModel.h
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#ifndef SENSORMODEL_H_
#define SENSORMODEL_H_

#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "WorldModel.h"
#include "Common.h"

class SensorModel
{
    public:

        static const float fieldOfView = 1.04719755;

        struct SensorMeasurement
        {
            SensorMeasurement(int inLandmark, float inDistance, float inBearing)
             : landmark(inLandmark), distance(inDistance), bearing(inBearing)
            {}
            int landmark;
            float distance;
            float bearing;
        };

        static std::vector<SensorMeasurement> getVisibleLandmarks()
        {
            std::vector<SensorMeasurement> visible;

            for(unsigned int i = 0; i < WorldModel::landmarkPositions.size(); i++)
            {
                Vector2<float> lineOfSight = WorldModel::landmarkPositions[i] - WorldModel::currentPose.translation;

                float distance = lineOfSight.abs();

                float angleBetween = normalize(WorldModel::currentPose.rotation - lineOfSight.angle());

                if(distance <= 150.0f &&
                   distance >= 10.0f &&
                   fabs(angleBetween) < fieldOfView)
                {
                    visible.push_back(SensorMeasurement(i, distance + (randomFloat() * 10.0f) - 5.0f,
                                                           angleBetween + (randomFloat() * 0.087266462f) - 0.043633231f));
                }
            }

            return visible;
        }
};

#endif /* SENSORMODEL_H_ */
