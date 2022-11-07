#ifndef __ALGORITHM__h
#define __ALGORITHM__H

/**
 * @file algorithm.h
 * @author sam2808 (sam2808@umd.edu)
 * @author as03050 (as03050@umd.edu)
 * @author dradhakr (dradhakr@umd.edu)
 * @brief Functions to implement the movement of the robot in a particular direction.
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <vector>

namespace rwa2group13
{
    // group the x and y coordinates/cell positions of the robot in the maze along with the direction that the robot is facing
    struct coordinates
    {
        int x;
        int y;
        char dir;
    };
    /**
     * @brief 
     * Robot class implements the robot movement
     *
     */
    class Robot
    {

    public:
        /**
         * @brief 
         * Move the robot forward in whichever direction it is facing
         *
         * @param pos current position (x,y,direction) of the robot
         * 
         * @return updated position (x,y only) of the robot after moving forward
         */
        static coordinates forward(coordinates pos);

        /**
         * @brief 
         * Move the robot in the opposite direction that it is currently facing
         *
         * @param pos current position (x,y,direction) of the robot
         * 
         * @return updated position (x,y,direction) of the robot after moving in the opposite direction
         */
        static coordinates back(coordinates pos);

        /**
         * @brief 
         * Turn the robot to the right of the current facing direction and move forward
         *
         * @param pos current position (x,y,direction) of the robot
         * 
         * @return updated position (x,y,direction) of the robot after turning right and moving forward
         */
        static coordinates right(coordinates pos);

       /**
         * @brief 
         * Turn the robot to the rigleftht of the current facing direction and move forward
         *
         * @param pos current position (x,y,direction) of the robot
         * 
         * @return updated position (x,y,direction) of the robot after turning left and moving forward
         */
        static coordinates left(coordinates pos);

        /**
         * @brief 
         * Turn the robot to the opposite direction of the current facing direction only.
         *
         * @param pos current position (x,y,direction) of the robot
         * 
         * @return updated position (direction only) of the robot after rotating 180 degree
         */
        static coordinates rotate(coordinates pos);
    };
} // namespace rwa2group13

#endif
