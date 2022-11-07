#include "algorithm.h"
#include "../simulator/simulator.h"

#include <iostream>
#include <utility>
#include <ctime> //for random number seed
#include "../robot/robot.h"
#include <unistd.h>

namespace rwa2group13
{
    void Algorithm::generate_goal()
    {
        srand(time(0));
        int x{(rand() % 16)};                       // x is initialized within range 0 to 15
        int y{0};                                   // y is initialized to 0
        if (x == 0)
        {                                           // if x is 0, y is assigned in the range 1 to 15
            y = 1 + (rand() % 15);                  // because goal cannot be in 0,0 as it is the start position for a robot
        }
        else if (x == 15)
        {                                           // else if x is 15, y is assigned in the range 0 to 15
            y = rand() % 16;
        }
        else
        {                                            // if x is in range 1 to 14, then array y_vals in assigned values 0 and 15
            int y_vals[2] = {0, 15};                 // randomly picks 0 or 15 and assigned to y.
            y = y_vals[rand() % 2];                  //This ensures either goal is adjacent to outer walls
        }
        goal.x = x;                                  // assign the goals to the x and y members of the structure - goal
        goal.y = y;

        Simulator::setColor(x, y, 'r');               //set the goal cell background color as red
        Simulator::setText(x, y, "G");                //Mark the goal cell as "G" 
    }

    void Algorithm::init_outer_walls()
    {
        for (int row{0}; row <= 15; ++row)
        {
            for (int col{0}; col <= 15; ++col)
            {
                // checking the bottom and top row
                if (col == 0)                               //y = 0, x = 0-15 => south
                {
                    Simulator::setWall(row, col, 's');
                }
                if (col == 15)                              //y = 15, x = 0-15 => north
                {
                    Simulator::setWall(row, col, 'n');
                }
                // checking the left and right column
                if (row == 0)                               //x = 0, y = 0-15 => west
                {
                    Simulator::setWall(row, col, 'w');
                }
                if (row == 15)                              //x = 15, y = 0-15 => east
                {
                    Simulator::setWall(row, col, 'e');
                }
            }
        }
    }

    void Algorithm::get_goal()
    {
        std::cerr << "The goal is: " << std::endl;
        std::cerr << "(" << goal.x << ", " << goal.y << ")";        //print goal coordinates
        std::cerr << std::endl;
        sleep(2);
    }

    void Algorithm::run_left()
    {
        generate_goal();                     
        init_outer_walls();
        wall_follow_left();
    }

    void Algorithm::run_right()
    {
        generate_goal();
        init_outer_walls();
        wall_follow_right();
    }

    void Algorithm::wall_follow_left()
    {
        direction = "nwse";
        coordinates pos;
        coordinates temp_pos;
        pos.x = 0;
        pos.y = 0;
        pos.dir = 'n';
        path.push_back(pos);
        while ((pos.x != goal.x) or (pos.y != goal.y))
        {
            Simulator::setColor(pos.x, pos.y, 'c');
            if (!Simulator::wallLeft())
            {
                pos = Robot::left(pos);
            }
            else if (!Simulator::wallFront())
            {
                pos = Robot::forward(pos);
            }
            else if (!Simulator::wallRight())
            {
                pos = Robot::right(pos);
            }
            else
            {
                path.pop_back();
                pos = Robot::back(pos);
            }

            if ((pos.x == path.at(path.size() - 1).x) and ((pos.y == path.at(path.size() - 1).y)))
            {
                temp = true;
                temp_pos = pos;
                path.pop_back();
            }
            else
            {
                if (temp)
                {
                    temp = false;
                    path.push_back(temp_pos);
                }
                path.push_back(pos);
            }
        }
        backtrack(pos);
    }

    void Algorithm::wall_follow_right()
    {
        direction = "nwse";
        coordinates pos;
        coordinates temp_pos;
        pos.x = 0;
        pos.y = 0;
        pos.dir = 'n';
        path.push_back(pos);
        while ((pos.x != goal.x) or (pos.y != goal.y))
        {
            Simulator::setColor(pos.x, pos.y, 'c');
            if (!Simulator::wallRight())
            {
                pos = Robot::right(pos);
            }
            else if (!Simulator::wallFront())
            {
                pos = Robot::forward(pos);
            }
            else if (!Simulator::wallLeft())
            {
                pos = Robot::left(pos);
            }
            else
            {
                path.pop_back();
                pos = Robot::back(pos);
            }

            if ((pos.x == path.at(path.size() - 1).x) and ((pos.y == path.at(path.size() - 1).y)))
            {
                temp = true;
                temp_pos = pos;
                path.pop_back();
            }
            else
            {
                if (temp)
                {
                    temp = false;
                    path.push_back(temp_pos);
                }
                path.push_back(pos);
            }
        }
        backtrack(pos);
    }

    void Algorithm::backtrack(coordinates pos)
    {
        pos = Robot::rotate(pos);
        pos = Robot::forward(pos);
        Simulator::setColor(pos.x, pos.y, 'r');
        path.pop_back();
        path.pop_back();
        std::cerr << "PATH" << std::endl;
        for (int i = path.size() - 1; i >= 0; i--)
        {
            std::cerr << path.at(i).x << "  " << path.at(i).y << std::endl;
        }
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (path.at(i).y == pos.y + 1)
                path.at(i).dir = 'n';
            else if (path.at(i).y == pos.y - 1)
                path.at(i).dir = 's';
            else if (path.at(i).x == pos.x + 1)
                path.at(i).dir = 'e';
            else if (path.at(i).x == pos.x - 1)
                path.at(i).dir = 'w';

            // std::cerr << path.at(i).x << "  "<<  path.at(i).y << "  "<<  path.at(i).dir <<std::endl;
            if (path.at(i).dir == 'n')
            {
                if (pos.dir == 'n')
                    pos = Robot::forward(pos);
                else if (pos.dir == 'w')
                    pos = Robot::right(pos);
                else if (pos.dir == 'e')
                    pos = Robot::left(pos);
            }
            else if (path.at(i).dir == 's')
            {
                if (pos.dir == 's')
                    pos = Robot::forward(pos);
                else if (pos.dir == 'e')
                    pos = Robot::right(pos);
                else if (pos.dir == 'w')
                    pos = Robot::left(pos);
            }
            else if (path.at(i).dir == 'e')
            {
                if (pos.dir == 'e')
                    pos = Robot::forward(pos);
                else if (pos.dir == 'n')
                    pos = Robot::right(pos);
                else if (pos.dir == 's')
                    pos = Robot::left(pos);
            }
            else if (path.at(i).dir == 'w')
            {
                if (pos.dir == 'w')
                    pos = Robot::forward(pos);
                else if (pos.dir == 's')
                    pos = Robot::right(pos);
                else if (pos.dir == 'n')
                    pos = Robot::left(pos);
            }
            Simulator::setColor(pos.x, pos.y, 'r');
        }
    }
} // namespace rwa2group13
