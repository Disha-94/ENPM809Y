#include "cell.h"
#include "../simulator/simulator.h"

/**
 * @brief 
 * 
 */
namespace rwa2group13
{
    void Cell::init_cell_walls(coordinates pos)
    {
    	/*check the orientation of the robot with respect to grid
    	  and check if there is wall with respect to grid position
    	  and orientation accordingly*/
        if(pos.dir == 'n') {	//orientations of robot and grid align
            if (is_wall(pos.x, pos.y, 'n'))
            	set_wall(pos.x, pos.y, 'n');
            if (is_wall(pos.x, pos.y, 'w'))
            	set_wall(pos.x, pos.y, 'w');
            if (is_wall(pos.x, pos.y, 'e'))
            	set_wall(pos.x, pos.y, 'e');
        }
        else if(pos.dir == 's') { //robot is oriented 180 degrees to grid
            if (is_wall(pos.x, pos.y, 'n'))
            	set_wall(pos.x, pos.y, 's');
            if (is_wall(pos.x, pos.y, 'w'))
            	set_wall(pos.x, pos.y, 'e');
            if (is_wall(pos.x, pos.y, 'e'))
            	set_wall(pos.x, pos.y, 'w');
        }
        else if(pos.dir == 'e') { //robot faces east with respect to grid
            if (is_wall(pos.x, pos.y, 'n'))
            	set_wall(pos.x, pos.y, 'e');
            if (is_wall(pos.x, pos.y, 'w'))
            	set_wall(pos.x, pos.y, 'n');
            if (is_wall(pos.x, pos.y, 'e'))
            	set_wall(pos.x, pos.y, 's');
        }
        else {	//robot faces west with respect to grid
            if (is_wall(pos.x, pos.y, 'n'))
            	set_wall(pos.x, pos.y, 'w');
            if (is_wall(pos.x, pos.y, 'w'))
            	set_wall(pos.x, pos.y, 's');
            if (is_wall(pos.x, pos.y, 'e'))
            	set_wall(pos.x, pos.y, 'n');
        }
    }
    
    void Cell::set_wall(int x, int y, char dir)
    {
    	//set the wall at the given direction at the particular cell position
    	Simulator::setWall(x, y, dir);
    }
    
    bool Cell::is_wall(int x, int y, char dir)
    {
    	//check for the wall on the front, left and right
    	if (dir == 'n')
    	    return Simulator::wallFront();
    	else if (dir == 'w')
    	    return Simulator::wallLeft();
    	else	//only remaining condition left is east/'e'
    	    return Simulator::wallRight();
    }
} //namespace rwa2group13