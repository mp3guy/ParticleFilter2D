/*
 * ParticleFilter.cpp
 *
 *  Created on: 22 Sep 2011
 *      Author: thomas
 */

#include "ParticleFilter.h"

ParticleFilter::ParticleFilter(int numParticles)
{
    particles.reserve(numParticles);

    for(int i = 0; i < numParticles; i++)
    {
        particles.push_back(Particle(Pose2D::random(Range<float>(0, WorldModel::worldSize),
                                                    Range<float>(0, WorldModel::worldSize),
                                                    Range<float>(-pi, pi)), 1.0f / numParticles));
    }
}

ParticleFilter::~ParticleFilter()
{

}

Particle ParticleFilter::generateRandomSample()
{
    return Particle(Pose2D::random(Range<float>(0, WorldModel::worldSize),
                                   Range<float>(0, WorldModel::worldSize),
                                   Range<float>(-pi, pi)));
}

void ParticleFilter::normaliseWeights()
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].weight /= weightSum;
    }
}

void ParticleFilter::resetWeights()
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].weight = 1.0f / particles.size();
    }
}

Pose2D ParticleFilter::processFrame(Pose2D & odometry, std::vector<SensorModel::SensorMeasurement> visibleLandmarks)
{
    processMotion(odometry);

    processSensor(visibleLandmarks);

    if(shouldResample())
    {
        resample();
        resetWeights();
    }
    else
    {
        normaliseWeights();
    }

    Pose2D averageParticle;
    float averageCos = 0.0f;
    float averageSin = 0.0f;

    for(unsigned int i = 0; i < particles.size(); i++)
    {
        averageParticle.translation.x += particles[i].position.translation.x * particles[i].weight;
        averageParticle.translation.y += particles[i].position.translation.y * particles[i].weight;
        averageCos += cos(particles[i].position.rotation) * particles[i].weight;
        averageSin += sin(particles[i].position.rotation) * particles[i].weight;
    }

    averageParticle.rotation = atan2(averageSin, averageCos);

    return averageParticle;
}

void ParticleFilter::processMotion(Pose2D & odometry)
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].position.translation.x += sampleTriangularDistribution(odometryTranslationTimeVariance  * (float(TARGET_SPEED_MS) / 1000.0f)
                                                                            + odometryTranslationMotionVariance * fabs(odometry.translation.x));

        particles[i].position.translation.y += sampleTriangularDistribution(odometryTranslationTimeVariance * (float(TARGET_SPEED_MS) / 1000.0f)
                                                                            + odometryTranslationMotionVariance * fabs(odometry.translation.y));

        particles[i].position.rotation += sampleTriangularDistribution(odometryRotationTimeVariance * (float(TARGET_SPEED_MS) / 1000.0f)
                                                                       + odometryRotationMotionVariance * fabs(odometry.rotation));

        particles[i].position += odometry;
    }
}

void ParticleFilter::processSensor(std::vector<SensorModel::SensorMeasurement> & visibleLandmarks)
{
    for(unsigned int i = 0; i < particles.size(); i++)
    {
        for(unsigned int j = 0; j < visibleLandmarks.size(); j++)
        {
            Vector2<float> difference = WorldModel::landmarkPositions[visibleLandmarks[j].landmark] - particles[i].position.translation;

            float distance = difference.abs();

            float angle = normalize(particles[i].position.rotation - difference.angle());

            particles[i].weight *= gaussianProbability(fabs(distance - visibleLandmarks[j].distance), landmarkDistMeasurementStdDev)
                                 * gaussianProbability(fabs(angle - visibleLandmarks[j].bearing), landmarkAngleMeasurementStdDev);
        }
    }

    float maxWeight = 0.0f;

    for(unsigned int i = 0; i < particles.size(); i++)
    {
        if(particles[i].weight > maxWeight)
        {
            maxWeight = particles[i].weight;
            maxParticle = particles[i];
        }
    }
}

void ParticleFilter::resample()
{
    std::vector<Particle> oldSet = particles;

    float weightBetweenTwoDrawnSamples = weightSum / particles.size();
    float nextPos = randomFloat() * weightBetweenTwoDrawnSamples;
    float currentSum = 0.0f;

    particles.clear();

    for(unsigned int i = 0; i < oldSet.size(); i++)
    {
        currentSum += oldSet[i].weight;

        while(currentSum > nextPos)
        {
            particles.push_back(oldSet[i]);

            nextPos += weightBetweenTwoDrawnSamples;

            if(particles.size() == oldSet.size())
            {
                return;
            }
        }
    }

    while(particles.size() < oldSet.size())
    {
        particles.push_back(generateRandomSample());
    }
}

bool ParticleFilter::shouldResample()
{
    bool resample;

    weightSum = 0.0f;

    for(unsigned int i = 0; i < particles.size(); i++)
    {
        weightSum += particles[i].weight;
    }

    float effectiveParticleCount = 0.0f;

    for(unsigned int i = 0; i < particles.size(); i++)
    {
        effectiveParticleCount += pow(particles[i].weight / weightSum, 2);
    }

    effectiveParticleCount = 1 / effectiveParticleCount;

    resample = effectiveParticleCount / particles.size() < resampleEffectiveParticleThreshold;

    return resample;
}
