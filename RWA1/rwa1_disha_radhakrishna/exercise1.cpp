/**
 * @file exercise1.cpp
 * @author Disha Radhakrishna (dradhakr@umd.edu)
 * 
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief 
 * This program involves a robotic arm that can pick up parts and place them on tables.
 * The arm has to follow the below rules
 * Ball can only be picked up with the suction gripper and placed on the green table only
 * Cube can only be picked up with the finger gripper and placed on the red table only
 * Peg can only be picked up with the finger gripper and placed on the blue table only
 * 
 * User can choose the object to pick up, griper to use and table to be placed on (in this order)
 * 
 * Based on user input, success/failure messages will be displayed.
 * User can repeat this task by pressing 'y' at the end. 'n' will exit the program.
 * @return int 
 */

int main(){
    //constant value to ignore upto 100 additional character inputs
    const int limit{100};

    //variables initialization (uniform) 
    char rounds{'y'};               //to manage the main do-while loop
    bool continueLoop{true};        //to manage the inner do-while loops
    string part{};                  //to store part name
    string gripper{};               //to store gripper name
    string table{};                 //to store table name
    cout << "-------------------------------------------------------";
    cout << "\nEXERCISE 1";

    do{
        // char variables to store user input
        char p{}, g{}, t{}; 
        cout << "\n-------------------------------------------------------";
        do{
            cout << "\nWhich part to pick up (c, b, p)? ";

            //p stores single character of user input for parts
            cin >> p;

            //if user inputs more than 1 letter, ignore() considers the first character and ignores the rest upto 100 characters
            cin.ignore(limit, '\n'); 

            //true -> wrong input, repeat question; false -> input is 'c', 'b', or 'p'. move to next question
            continueLoop = (p =='c' || p=='b' || p=='p') ? false : true;
        } while (continueLoop);
        cout << "\n-------------------------------------------------------";
        do{
            cout << "\nWhich gripper to use (s, f)? ";

            //g stores single character of user input for grippers
            cin >> g;

            //if user inputs more than 1 letter, ignore() considers the first character and ignores the rest upto 100 characters
            cin.ignore(limit, '\n');

            //true -> wrong input, repeat question; false -> input is 's', or 'f'. move to next question
            continueLoop = (g =='s' || g=='f') ? false : true;
        } while (continueLoop);
        cout << "\n-------------------------------------------------------";
        //assign parts and grippers full names to display success/failure messages.
        part = (p == 'c') ? "cube" : (p == 'b') ? "ball" : "peg";
        gripper = (g == 's') ? "suction" : "finger";

        //condition to check if user selected the right combination of part and gripper
        //acceptable combination => ball + suction, cube/peg + finger => (move to table question)
        //if input is incorrect, jump to else. display failure message
        if((p == 'b' && g =='s') || ((p == 'c' || p == 'p') && g == 'f')){
            do {
                cout << "\nWhich table to use (r, g, b)? ";

                //t stores single character of user input for tables
                cin >> t;

                //if user inputs more than 1 letter, ignore() considers the first character and ignores the rest upto 100 characters
                cin.ignore(limit, '\n');

                //true -> wrong input, repeat question; false -> input is 'r', 'g', or 'b'. move to next question
                continueLoop = (t == 'r' || t == 'g' || t == 'b') ? false : true;
            } while (continueLoop);
            cout << "\n-------------------------------------------------------";
            //assign table full names to display success/failure messages.
            table = (t == 'r') ? "red" : (t == 'g') ? "green" : "blue";

            //condition to check if user selected the right combination of part and table
            //acceptable combination => cube + red, ball + green, peg + blue => display success message
            //if input is incorrect, jump to else. display failure message
            if((p == 'c' && t == 'r') || (p == 'b' && t == 'g') || (p == 'p' && t == 'b')){
                cout << "\nSuccess: The " << part << " was placed on the " << table << " table. \n";
            }
            else {
                cout << "\nFailure: Cannot place the " << part << " on the " << table << " table. \n";
            }
            cout << "\n-------------------------------------------------------";
        }
        else {
            cout << "\nFailure: Cannot pick up the " << part << " with the " << gripper << " gripper. \n";
            cout << "\n-------------------------------------------------------";
        }
        do{
            cout << "\nTry again? (y, n)? ";

            //rounds stores single character of user input to repeat or quit the loop
            cin >> rounds;

            //if user inputs more than 1 letter, ignore() considers the first character and ignores the rest upto 100 characters
            cin.ignore(limit, '\n');

            //true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to condition evaluation
            continueLoop = (rounds == 'y' || rounds == 'n') ? false : true;
        } while(continueLoop);

    } while(rounds != 'n'); //y -> to keep the loop active; n -> to exit loop

    return 0;
}
