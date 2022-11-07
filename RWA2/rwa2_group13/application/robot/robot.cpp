#include "robot.h"
#include "../simulator/simulator.h"

#include <iostream>
#include <ctime>    //for random number seed

//---------------------------------------------------------------------
/**
 * @brief 
 * 
 */
namespace rwa2group13
{
    coordinates Robot::forward(coordinates pos)
    {
        //move 1 step forward
        //return the updated position (new coordinates only) of the robot based on the current direction
        Simulator::moveForward(1);
        if(pos.dir == 'n')
            pos.y += 1;
        else if(pos.dir == 's')
            pos.y -= 1;
        else if(pos.dir == 'e')
            pos.x += 1;
        else if(pos.dir == 'w')
            pos.x -= 1;
        return pos;
    }
    
    coordinates Robot::back(coordinates pos)
    {
        //turn right twice and move 1 step forward i.e., move 1 step back
        //return the updated posiiton (new coordinates and direction) of the robot based on the current direction
        Simulator::turnRight();
        Simulator::turnRight();
        Simulator::moveForward(1);
        if(pos.dir == 'n'){
            pos.y -= 1;
            pos.dir = 's';
        }
        else if(pos.dir == 's'){
            pos.y += 1;
            pos.dir = 'n';
        }
        else if(pos.dir == 'e'){
            pos.x -= 1;
            pos.dir = 'w';
        }
        else if(pos.dir == 'w'){
            pos.x += 1;
            pos.dir = 'e';
        }
        return pos;
    }

    coordinates Robot::right(coordinates pos)
    {
        //turn right and move 1 step forward
        //return the updated posiiton (new coordinates and direction) of the robot based on the current direction
        Simulator::turnRight();
        Simulator::moveForward(1);
        if(pos.dir == 'n'){
            pos.x += 1;
            pos.dir = 'e';
        }
        else if(pos.dir == 's'){
            pos.x -= 1;
            pos.dir = 'w';
        }
        else if(pos.dir == 'e'){
            pos.y -= 1;
            pos.dir = 's';
        }
        else if(pos.dir == 'w'){
            pos.y += 1;
            pos.dir = 'n';
        }
        return pos;
    }

    coordinates Robot::left(coordinates pos)
    {
        //turn left and move 1 step forward
        //return the updated posiiton (new coordinates and direction) of the robot based on the current direction
        Simulator::turnLeft();
        Simulator::moveForward(1);
        if(pos.dir == 's'){
            pos.x += 1;
            pos.dir = 'e';
        }
        else if(pos.dir == 'n'){
            pos.x -= 1;
            pos.dir = 'w';
        }
        else if(pos.dir == 'w'){
            pos.y -= 1;
            pos.dir = 's';
        }
        else if(pos.dir == 'e'){
            pos.y += 1;
            pos.dir = 'n';
        }
        return pos;
    }

    coordinates Robot::rotate(coordinates pos)
    {
        //turn left twice i.e., turn to the opposite direction i.e., rotate
        //return the updated position (direction only) of the robot based on the current direction
        Simulator::turnLeft();
        Simulator::turnLeft();
        if(pos.dir == 'n')
            pos.dir = 's';
        else if(pos.dir == 's')
            pos.dir = 'n';
        else if(pos.dir == 'e')
            pos.dir = 'w';
        else if(pos.dir == 'w')
            pos.dir = 'e';
        return pos;
    } 
} //namespace rwa2group13