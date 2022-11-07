#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>

#include "simulator/simulator.h"
#include "algorithm/algorithm.h"

int main(int argc, char *argv[])
{
    auto algo = std::make_unique<rwa2group13::Algorithm>();
    if(argc > 1 && (strcmp( argv[1], "-right" ) == 0 || strcmp( argv[1], "right" ) == 0 || strcmp( argv[1], "r" ) == 0 || strcmp( argv[1], "R" ) == 0)){
        algo -> run_right();
    }
    else {
        algo -> run_left();
    }
}
