/*
 * InputHandler.h
 *
 *  Created on: 25 Sep 2011
 *      Author: thomas
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Pose2D.h"

class InputHandler
{
    public:
        static Pose2D processInput(char key)
        {
            Pose2D movement;

            if(key == 83)
            {
                movement.rotation = 0.174532925;
            }
            else if(key == 81)
            {
                movement.rotation = -0.174532925;
            }
            else if(key == 82)
            {
                movement.translation.x = 4.0f;
            }
            else if(key == 84)
            {
                movement.translation.x = -4.0f;
            }

            return movement;
        }
};
#endif /* INPUTHANDLER_H_ */
