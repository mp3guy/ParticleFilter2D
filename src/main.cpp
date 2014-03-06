/*
 * main.cpp
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#include "main.h"

void onMouse(int event, int x, int y, int flags, void * param)
{
    if(event == CV_EVENT_LBUTTONDOWN)
    {
        WorldModel::currentPose.translation.x = x;
        WorldModel::currentPose.translation.y = y;

        myWorldDrawer->drawWorld();
        myWorldDrawer->drawParticles(myParticleFilter->processFrame(odometry, SensorModel::getVisibleLandmarks()),
                                     myParticleFilter->getParticles(), myParticleFilter->maxParticle);
        myWorldDrawer->showImage();
    }
}

int main()
{
    myParticleFilter = new ParticleFilter(10000);

    myWorldDrawer = new WorldDrawer();

    cvStartWindowThread();

    cvSetMouseCallback("World", onMouse);

    char key;

    gettimeofday(&timer, 0);

    srand(timer.tv_usec);

    for(unsigned int i = 0; i < NUM_LANDMARKS; i++)
    {
        WorldModel::landmarkPositions.push_back(Vector2<float>(randomFloat() * WorldModel::worldSize,
                                                               randomFloat() * WorldModel::worldSize));
    }

    while(true)
    {
        gettimeofday(&timer, 0);

        WorldModel::currentPose += odometry;

        myWorldDrawer->drawWorld();
        myWorldDrawer->drawParticles(myParticleFilter->processFrame(odometry, SensorModel::getVisibleLandmarks()),
                                     myParticleFilter->getParticles(), myParticleFilter->maxParticle);
        myWorldDrawer->showImage();

        odometry = Pose2D();

        key = cvWaitKey(33);

        if(key == 'q')
        {
            break;
        }
        else if(key == 81 ||
                key == 82 ||
                key == 83 ||
                key == 84)
        {
            odometry = InputHandler::processInput(key);
        }
    }

    delete myParticleFilter;

    delete myWorldDrawer;

    return 0;
}
