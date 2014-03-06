/*
 * WorldModel.h
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#ifndef WORLDMODEL_H_
#define WORLDMODEL_H_

#define TARGET_SPEED_MS 33
#define NUM_LANDMARKS 5

#include <vector>
#include "Pose2D.h"
#include "Vector2.h"

class WorldModel
{
    public:
        static Pose2D currentPose;
        static const float worldSize = 750.0f;
        static std::vector<Vector2<float> > landmarkPositions;
};

#endif /* WORLDMODEL_H_ */
