/*
 * main.h
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <sys/time.h>

#include "WorldDrawer.h"
#include "InputHandler.h"
#include "ParticleFilter.h"

timeval timer;

WorldDrawer * myWorldDrawer;
ParticleFilter * myParticleFilter;

Pose2D odometry;

#endif /* MAIN_H_ */
