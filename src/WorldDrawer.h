/*
 * WorldDrawer.h
 *
 *  Created on: 23 Sep 2011
 *      Author: thomas
 */

#ifndef WORLDDRAWER_H_
#define WORLDDRAWER_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "Particle.h"
#include "Pose2D.h"
#include "WorldModel.h"
#include "SensorModel.h"

class WorldDrawer
{
    public:
        WorldDrawer();
        virtual ~WorldDrawer();

        void drawParticles(Particle averageParticle, std::vector<Particle> * particles, Particle & maxParticle);
        void drawWorld();
        void showImage();

    private:
        void drawSample(Pose2D & sample, CvScalar color);
        void drawLandmarks();

        IplImage * image;
        CvFont font;
};

#endif /* WORLDDRAWER_H_ */
