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

        static void getHeatMapColor(float value, int & red, int & green, int & blue)
        {
            const int NUM_COLORS = 4;
            static float color[NUM_COLORS][3] = {{0,0,1}, {0,1,0}, {1,1,0}, {1,0,0}};

            int idx1;
            int idx2;
            float fractBetween = 0;

            if(value <= 0)
            {
                idx1 = idx2 = 0;
            }
            else if(value >= 1)
            {
                idx1 = idx2 = NUM_COLORS - 1;
            }
            else
            {
                value = value * (NUM_COLORS - 1);
                idx1 = floor(value);
                idx2 = idx1 + 1;
                fractBetween = value - float(idx1);
            }

            red   = ((color[idx2][0] - color[idx1][0])*fractBetween + color[idx1][0]) * 255.0f;
            green = ((color[idx2][1] - color[idx1][1])*fractBetween + color[idx1][1]) * 255.0f;
            blue  = ((color[idx2][2] - color[idx1][2])*fractBetween + color[idx1][2]) * 255.0f;
        }

        void drawParticles(Particle averageParticle, std::vector<Particle> * particles);
        void drawWorld();
        void showImage();

    private:
        void drawSample(Pose2D & sample, CvScalar color);
        void drawLandmarks();

        IplImage * image;
        CvFont font;
};

#endif /* WORLDDRAWER_H_ */
