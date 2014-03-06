/*
 * Particle.h
 *
 *  Created on: 22 Sep 2011
 *      Author: thomas
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Pose2D.h"

class Particle
{
    public:
        Particle(Pose2D position = Pose2D(), float weight = 0)
         : position(position), weight(weight)
        {}

        Pose2D position;
        float weight;
};

#endif /* PARTICLE_H_ */
