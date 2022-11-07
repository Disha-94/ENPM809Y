#ifndef __ALGORITHM__h
#define __ALGORITHM__H

/**
 * @file algorithm.h
 * @author sam2808 (sam2808@umd.edu)
 * @author as03050 (as03050@umd.edu)
 * @author dradhakr (dradhakr@umd.edu)
 * @brief Functions to implement the left and right hand rule approach, set the walls, generate goal and trace the robot route to reach that goal
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
     * @brief Algorithm class implements the search algorithm
     *
     */
    class Algorithm
    {
    private:
        // optimized path is stored sequentially
        std::vector<std::pair<int, int>> m_position_vector;

        // stores the coordinates of goals.
        coordinates goal;

        std::string direction = "nwse";
        int cur_dir = 0;

        std::vector<coordinates> path;

        bool temp = false;

    public:
        /**
         * @brief Constructor
         *
         */
        Algorithm() : goal{0, 0} {}

        /**
         * @brief 
         * Entry point of the program
         * generates the goal G randomly, initiates the outer walls with direction, runs the robot in left wall follower approach
         * to reach the goal
         */
        void run_left();

        /**
         * @brief 
         * Entry point of the program
         * generates the goal G randomly, initiates the outer walls with direction, runs the robot in right wall follower approach
         * to reach the goal
         */
        void run_right();

        /**
         * @brief 
         * Set the outer walls directions north, east, west, south
         *
         * @return
         */
        void init_outer_walls();

        /**
         * @brief 
         * Algorithm for Left-wall follower approach
         *
         */
        void wall_follow_left();

        /**
         * @brief 
         * Algorithm for Right-wall follower approach
         *
         */
        void wall_follow_right();

        /**
         * @brief 
         * randomly generates goal adjacent to the outer wall
         *
         * @return
         */
        void generate_goal();

        /**
         * @brief 
         * sets right wall w.r.t. robot as red
         *
         */
        void set_right_wall();

        /**
         * @brief 
         * sets left wall w.r.t. robot as red
         *
         */
        void set_left_wall();

        /**
         * @brief 
         * sets front wall w.r.t. robot as red
         *
         */
        void set_front_wall();

        /**
         * @brief 
         * displays the coordinates of the goal (x and y)
         *
         */
        void get_goal();

        /**
         * @brief 
         * return the robot to the start position from the goal.
         * called in left and right wall follow algorithm
         *
         * @param pos  coordinate of the goal cell as start position for backtracking.
         */
        void backtrack(coordinates pos);
    };
} // namespace rwa2group13

#endif
