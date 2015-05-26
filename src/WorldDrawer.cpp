/*
 * WorldDrawer.cpp
 *
 *  Created on: 23 Sep 2011
 *      Author: thomas
 */

#include "WorldDrawer.h"

WorldDrawer::WorldDrawer()
{
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.3, 0.3, 0, 1, 8);
    image = cvCreateImage(cvSize(WorldModel::worldSize, WorldModel::worldSize), IPL_DEPTH_8U, 3);
    cvNamedWindow("World", CV_WINDOW_AUTOSIZE);
}

WorldDrawer::~WorldDrawer()
{
    cvReleaseImage(&image);
    cvDestroyWindow("World");
}

void WorldDrawer::drawWorld()
{
    memset(image->imageData, 0, sizeof(char) * image->width * image->height * image->nChannels);
    drawLandmarks();
}

void WorldDrawer::showImage()
{
    cvShowImage("World", image);
}

void WorldDrawer::drawParticles(Particle averageParticle, std::vector<Particle> * particles)
{
    for(unsigned int i = 0; i < particles->size(); i++)
    {
        int r, g, b;
        getHeatMapColor(particles->at(i).weight, r, g, b);
        drawSample(particles->at(i).position, CV_RGB(r, g, b));
    }

    drawSample(WorldModel::currentPose, CV_RGB(255, 255, 255));

    drawSample(averageParticle.position, CV_RGB(255, 0, 0));
}

void WorldDrawer::drawSample(Pose2D & sample, CvScalar color)
{
    cvCircle(image, cvPoint(sample.translation.x, sample.translation.y), 4, color, 1);
    cvLine(image, cvPoint(sample.translation.x, sample.translation.y),
                  cvPoint(sample.translation.x + cos(sample.rotation) * 10, sample.translation.y + sin(sample.rotation) * 10),
                  color, 1);
}

void WorldDrawer::drawLandmarks()
{
    for(unsigned int i = 0; i < WorldModel::landmarkPositions.size(); i++)
    {
        cvCircle(image, cvPoint(WorldModel::landmarkPositions[i].x, WorldModel::landmarkPositions[i].y), 5, CV_RGB(255, 255, 255), CV_FILLED);
    }

    std::vector<SensorModel::SensorMeasurement> visibleLandmarks = SensorModel::getVisibleLandmarks();

    for(unsigned int i = 0; i < visibleLandmarks.size(); i++)
    {
        cvCircle(image, cvPoint(WorldModel::landmarkPositions[visibleLandmarks[i].landmark].x, WorldModel::landmarkPositions[visibleLandmarks[i].landmark].y), 7, CV_RGB(255, 0, 0), 2);
    }
}
