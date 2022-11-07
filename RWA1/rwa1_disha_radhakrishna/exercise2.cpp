/**
 * @file exercise2.cpp
 * @author Disha Radhakrishna (dradhakr@umd.edu)
 *
 * @version 0.1
 * @date 2022-09-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <array>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @brief This program guides a robotic arm to place 0 to 3 types of colored pegs in user inputted slots from 1 to 9.
 *
 * User is asked about the color of peg to choose in the order red, green and blue
 * any color can be skipped and the next color will be displayed for user to select
 * If the user wants to place green pegs first, they have to say 'n' to red pegs first.
 * Once the color is chosen, program prompts for slots to be entered, separated by space.
 * This question also displayed the available slots, to help user choose the right slots.
 * Wrong inputs will lead to repeating the question
 * If all the slots are occupied, program prompts for restart. press 'y' to restart and 'n' to exit.
 * After each input, status of the slots will be displayed.
 *
 * @return int
 */

int main() {
    // constant value to ignore upto 100 additional character inputs
    const int limit{100};

    // variables initialization (uniform)
    // to manage the main do-while loop
    char rounds{'y'};  

    do {
        cout << "-------------------------------------------------------";
        cout << "\nEXERCISE 2 ";
        cout << "\n-------------------------------------------------------\n";

        // to manage the inner do-while loops
        bool continueLoop{false};  

        // 0-red, 1-green, 2-blue (for code reusability)
        int color{0};              

        // box with slots
        array<array<string, 3>, 3> box{{{"1", "2", "3"},
                                        {"4", "5", "6"},
                                        {"7", "8", "9"}}};  

        // to know available slots
        string slotsAvailable = "1-9";  

         // to store user request for slots
        string slotsRequested{};  

        // display available slots in the begining
        for (auto i = 0; i < 3; i++) {
            for (auto j = 0; j < 3; j++) {
                cout << box.at(i).at(j) << "  ";
            }
            cout << "\n";
        }
        string msg1_1 = "Do you want to place ";
        string msg1_2 = " pegs (y, n)? ";
        string msg2_1 = "Where to place ";

        cout << "\n-------------------------------------------------------";
        do {
            // stores user's wish to placed colored pegs 'y' or 'n'.
            char place_pegs{};

            do {
                // ask if user wishes to place pegs and store the result in place_pegs.
                cout << "\n" << msg1_1 << (color == 0 ? "red" : color == 1 ? "green" : "blue") << msg1_2;
                cin >> place_pegs;

                // if user inputs more than 1 letter, ignore() considers the first character;
                // ignores the rest upto 100 characters.
                cin.ignore(limit, '\n');

                // true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to next question.
                continueLoop = (place_pegs == 'y' || place_pegs == 'n') ? false : true;
            } while (continueLoop);

            if (place_pegs == 'y') {
                do {
                    continueLoop = false;

                    // ask user where to place the pegs. displays slots available for easy choosing.
                    cout << "\n" << msg2_1 << (color == 0 ? "red" : color == 1 ? "green" : "blue") 
                         << " pegs (" << slotsAvailable << ")? ";

                    // prereuisite: user should input slot numbers each separated by space.
                    // getline accepts whitespace inputs.
                    getline(cin, slotsRequested);
                    stringstream str(slotsRequested);
                    string word{};

                    // this loop checks if user request contains duplicate
                    for (int i = 0; i < slotsRequested.size(); i++) {
                        char s = slotsRequested[i];
                        if (slotsRequested.find(s, i + 1) != string::npos && s != ' ') {
                            continueLoop = true;
                            break;
                        }
                        //erase tab if found any
                        if(s == '\t'){
                            slotsRequested.erase(i, 1);
                        }
                    }

                    // this loop checks if user request contains invalid input like 10, aaa, 39f9, duplicate
                    // for valid inputs, it computes the length of the total requested slots
                    while (str >> word) {
                        if ((word.find_first_not_of("123456789") != string::npos) || stoi(word) > 9) {
                            continueLoop = true;
                            break;
                        }
                        // checks if slotsAvailable has been modified by red pegs (for green) and red/green pegs (for blue)
                        // then checks if user input matches available slots; if not, repeat the question
                        if (slotsAvailable.find('-') == string::npos && slotsAvailable.find(word) == string::npos) {
                            continueLoop = true;
                            break;
                        }
                    }

                    // if above checks prove invalid input, repeat the question
                    if (continueLoop == true) continue;

                    //below for loop is for displaying slots after placing colored pegs
                    cout << "\n-------------------------------------------------------\n";
                    for (auto i = 0; i < 3; i++) {
                        for (auto j = 0; j < 3; j++) {
                            int b{};
                            //if slot already has pegs placed in them, b = 0; else, we need to capture slot number.
                            (box.at(i).at(j) == "r" || box.at(i).at(j) == "g") ? b = 0 : b = stoi(box.at(i).at(j));

                            for (auto k = 0; k < slotsRequested.length(); k++) {
                                // if space, ignore the iteration
                                if (slotsRequested.substr(k, 1) == " ") continue;

                                // here s is the substring (from user input) between the whitespaces (string to int conversion)
                                int s = stoi(slotsRequested.substr(k, slotsRequested.find(" ", k)));

                                // if user input s matches slot number b (ex: 5 == 5) then place r/g/b in that slot.
                                if (b == s) {
                                    box.at(i).at(j) = (color == 0) ? "r" : (color == 1) ? "g"
                                                                                        : "b";
                                }
                            }
                            cout << box.at(i).at(j) << "  ";  // print the slots
                        }
                        cout << "\n";
                    }
                    slotsRequested = "";  // clear user input for next color
                } while (continueLoop);

                // check for available slots and store in correct format for display (with comma)
                // count: sum of occpuied slots
                slotsAvailable = "";
                int count{0};
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        if (box.at(i).at(j).find_first_not_of("123456789") == string::npos) {
                            slotsAvailable.append(box[i][j]);
                            slotsAvailable.append(", ");
                        } else {
                            count++;
                        }
                    }
                }

                // if all 9 slots are full, skip questions and ask user to try again
                if (count == 9) {
                    continueLoop = false;
                    break;
                } else {
                    // remove the last comma and space
                    slotsAvailable.resize(slotsAvailable.size() - 2);
                }
            } else {
                //if user selects 'n' to place pegs, then display current state of the slots
                cout << "\n-------------------------------------------------------\n";
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        cout << box.at(i).at(j) << "  ";
                    }
                    cout << "\n";
                }
            }
            
            //move to the next color question
            color++;
        } while (color < 3);

        do {
            cout << "\n-------------------------------------------------------";
            cout << "\nTry again? (y, n)?: ";

            // rounds stores single character of user input to repeat or quit the loop
            cin >> rounds;

            // if user inputs more than 1 letter, ignore() considers the first character and ignores the rest upto 100 characters
            cin.ignore(limit, '\n');

            // true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to condition evaluation
            continueLoop = (rounds == 'y' || rounds == 'n') ? false : true;
        } while (continueLoop);
        cout << "\n";
    } while (rounds != 'n');  // y -> to keep the loop active; n -> to exit loop
    return 0;
}

