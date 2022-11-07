#ifndef __CELL__H
#define __CELL__H

/**
 * @file algorithm.h
 * @author sam2808 (sam2808@umd.edu)
 * @author as03050 (as03050@umd.edu)
 * @author dradhakr (dradhakr@umd.edu)
 * @brief Functions to color the walls that get detected by the robot.
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../robot/robot.h"
#include <string>
#include <vector>

namespace rwa2group13
{
    /**
     * @brief 
     * Cell class implements wall color when the robot detects them.
     *
     */
    class Cell
    {

    public:
    	/**
    	 * @brief
    	 * Entry point that decides in what direction the wall is and calls set_wall
    	 * 
    	 * @param robot_pos current pose (x, y, direction) of the robot
    	 */
    	static void init_cell_walls(coordinates robot_pos);
    	
    	/**
    	 * @brief
    	 * Sets the wall color at the given position and direction
    	 *
    	 * @param x current x position of the cell position
    	 * @param y current y position of the cell position
    	 * @param dir direction of the cell wall at the cell position
    	 */
    	static void set_wall(int x, int y, char dir);
    	
    	/**
    	 * @brief Checks for wall in the given direction
    	 *
    	 * @param x current x position of the cell position
    	 * @param y current y position of the cell position
    	 * @param dir direction of the cell wall at the cell position
    	 *
    	 * @return true if there is wall in the given direction
    	 */
    	static bool is_wall(int x, int y, char dir);
    };
} // namespace rwa2group13

#endif