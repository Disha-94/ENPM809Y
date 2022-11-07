#include <iostream>
#include <string.h>
#include <memory>

#include "simulator/simulator.h"
#include "algorithm/algorithm.h"

int main(int argc, char *argv[])
{
    auto algo = std::make_unique<rwa2group13::Algorithm>();
    
    if (strcmp(argv[1], "-right") == 0 || strcmp(argv[1], "right") == 0 ||
     strcmp(argv[1], "r") == 0 || strcmp(argv[1], "R") == 0){
        algo -> run_right();
    }
    else if (strcmp(argv[1], "-left") == 0 || strcmp(argv[1], "left") == 0 ||
     strcmp(argv[1], "l") == 0 || strcmp(argv[1], "L") == 0){
        algo -> run_left();
    }
    else {
        std::cerr << "Please try again with the valid arguments to main()";
    }
}