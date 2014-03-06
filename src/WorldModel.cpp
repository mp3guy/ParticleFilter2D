/*
 * WorldModel.cpp
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#include "WorldModel.h"

Pose2D WorldModel::currentPose = Pose2D::random(Range<float>(0, worldSize),
                                                Range<float>(0, worldSize),
                                                Range<float>(-pi, pi));

std::vector<Vector2<float> > WorldModel::landmarkPositions = std::vector<Vector2<float> >(NUM_LANDMARKS);
