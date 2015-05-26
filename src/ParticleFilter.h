/*
 * ParticleFilter.h
 *
 *  Created on: 22 Sep 2011
 *      Author: thomas
 */

#ifndef PARTICLEFILTER_H_
#define PARTICLEFILTER_H_

#include <iostream>
#include <assert.h>
#include <vector>

#include "SensorModel.h"
#include "Particle.h"
#include "WorldModel.h"
#include "Probabilistics.h"

class ParticleFilter
{
    public:
        ParticleFilter(int numParticles);
        virtual ~ParticleFilter();

        Pose2D processFrame(Pose2D & odometry, std::vector<SensorModel::SensorMeasurement> visibleLandmarks);

        std::vector<Particle> * getParticles()
        {
            return &particles;
        }

    private:
        Particle generateRandomSample();
        void processMotion(Pose2D & odometry);
        void processSensor(std::vector<SensorModel::SensorMeasurement> & visibleLandmarks);
        void resample();
        void normaliseWeights();
        void resetWeights();
        bool shouldResample();

        std::vector<Particle> particles;

        float weightSum;

        static const float resampleEffectiveParticleThreshold = 0.5f;

        static const float landmarkDistMeasurementStdDev = 10.0f;
        static const float landmarkAngleMeasurementStdDev = 0.087266462f;

        static const float odometryTranslationTimeVariance = 1.0f;
        static const float odometryTranslationMotionVariance = 1.0f;

        static const float odometryRotationTimeVariance = 0.5f;
        static const float odometryRotationMotionVariance = 0.5f;
};

#endif /* PARTICLEFILTER_H_ */
