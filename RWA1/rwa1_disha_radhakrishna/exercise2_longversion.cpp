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
 * @brief This program guides a robotic arm to place 0 to 3 types of colored pegs in user inputted slots from 1 to 9 through elaborate code.
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
    char rounds{'y'};  // to manage the main do-while loop

    do {
        cout << "-------------------------------------------------------";
        cout << "\nEXERCISE 2 ";
        cout << "\n-------------------------------------------------------\n";
        bool continueLoop{false};  // to manage the inner do-while loops

        array<array<string, 3>, 3> box{{{"1", "2", "3"},
                                        {"4", "5", "6"},
                                        {"7", "8", "9"}}};  // box with slots

        string slotsAvailable = "1-9";  // to know available slots
        string slotsRequested{};        // to store user request for slots
        // display available slots in the begining
        for (auto i = 0; i < 3; i++) {
            for (auto j = 0; j < 3; j++) {
                cout << box.at(i).at(j) << "  ";
            }
            cout << "\n";
        }

        cout << "\n-------------------------------------------------------";
        do {
            char place_red{}, place_green{}, place_blue{};  // stores user's wish to placed colored pegs
            do {
                cout << "\nDo you want to place red pegs (y, n)? ";
                cin >> place_red;

                // if user inputs more than 1 letter, ignore() considers the first character
                // ignores the rest upto 100 characters
                cin.ignore(limit, '\n');

                // true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to next question
                continueLoop = (place_red == 'y' || place_red == 'n') ? false : true;
            } while (continueLoop);

            if (place_red == 'y') {
                do {
                    cout << "\nWhere to place red pegs (1-9)? ";
                    continueLoop = false;
                    // stores sequence of slot numbers requested by the user separated by space.
                    // getline accepts whitespace inputs
                    getline(cin, slotsRequested);
                    stringstream str(slotsRequested);
                    string word{};
                    int slotsReqLength{0};

                    // this loop checks if user request contains duplicate
                    for (int i = 0; i < slotsRequested.size(); i++) {
                        char s = slotsRequested[i];
                        if (slotsRequested.find(s, i + 1) != string::npos && s != ' ') {
                            continueLoop = true;
                            break;
                        }
                    }

                    // this loop checks if user request contains invalid input like 10, aaa, 39f9, duplicate
                    // for valid inputs, it computes the length of the total requested slots
                    while (str >> word) {
                        if ((word.find_first_not_of("123456789") != string::npos) || stoi(word) > 9) {
                            continueLoop = true;
                            break;
                        } else {
                            slotsReqLength++;
                        }
                    }

                    // if above 2 loops prove invalid input, repeat the question
                    if (continueLoop == true) continue;

                    // if user inputs more than 1 letter, ignore() considers the first character
                    // ignores the rest upto 100 characters
                    if (slotsReqLength > 10) {
                        continueLoop = true;
                        break;
                    } else {
                        cout << "\n-------------------------------------------------------\n";
                        for (auto i = 0; i < 3; i++) {
                            for (auto j = 0; j < 3; j++) {
                                int b = stoi(box.at(i).at(j));
                                for (auto k = 0; k < slotsRequested.length(); k++) {
                                    // if space, ignore the iteration
                                    if (slotsRequested.substr(k, 1) == " ") continue;

                                    // here s is the substring between the whitespaces (string to int conversion)
                                    int s = stoi(slotsRequested.substr(k, slotsRequested.find(" ", k)));

                                    // if user input s matches slot number b (ex: 5 == 5) then place r in place of b in box
                                    if (b == s) {
                                        box.at(i).at(j) = "r";
                                    }
                                }
                                cout << box.at(i).at(j) << "  ";  // print the slots
                            }
                            cout << "\n";
                        }
                        slotsRequested = "";  // clear user input for next color
                    }
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
                cout << "\n-------------------------------------------------------\n";
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        cout << box.at(i).at(j) << "  ";
                    }
                    cout << "\n";
                }
            }
            do {
                cout << "\nDo you want to place green pegs (y, n)? ";
                cin >> place_green;

                // if user inputs more than 1 letter, ignore() considers the first character
                // ignores the rest upto 100 characters
                cin.ignore(limit, '\n');

                // true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to next question
                continueLoop = (place_green == 'y' || place_green == 'n') ? false : true;
            } while (continueLoop);

            if (place_green == 'y') {
                do {
                    cout << "\nWhere to place green pegs (" << slotsAvailable << ")? ";
                    continueLoop = false;
                    // stores sequence of slot numbers requested by the user separated by space.
                    // getline accepts whitespace inputs
                    getline(cin, slotsRequested);
                    stringstream str(slotsRequested);
                    string word{};
                    int slotsReqLength{0};
                    int slotsAvailLength{0};

                    // this loop checks if user request contains duplicate; if found, repeat question
                    for (int i = 0; i < slotsRequested.size(); i++) {
                        char s = slotsRequested[i];
                        if (slotsRequested.find(s, i + 1) != string::npos && s != ' ') {
                            continueLoop = true;
                            break;
                        }
                    }

                    // this loop checks if user request contains invalid input like 10, aaa, 39f9; if found, repeat question
                    // for valid inputs, it computes the length of the total requested slots
                    while (str >> word) {
                        if ((word.find_first_not_of("123456789") != string::npos) || stoi(word) > 9) {
                            continueLoop = true;
                            break;
                        } else {
                            slotsReqLength++;
                        }
                        // checks if slotsAvailable has been modified by red pegs
                        // then checks if user input matches available slots; if not, repeat the question
                        if (place_red == 'y' && slotsAvailable.find(word) == string::npos) {
                            continueLoop = true;
                            break;
                        }
                    }
                    // if user has chooses to place green pegs after red pegs, then get length of available slots
                    if (place_red == 'y') {
                        stringstream str(slotsAvailable);
                        string word{};
                        while (str >> word) {
                            if ((word.find_first_of("123456789") != string::npos)) {
                                slotsAvailLength++;
                            }
                        }
                    }

                    // if above 2 loops prove invalid input, repeat the question
                    if (continueLoop == true) continue;

                    // if green is placed after red pegs, then check if requested slots are not more than available slots
                    // or if red is skipped, then all 9 slots are available. check if requested slots are not more than 10
                    // if any of these conditions fail, repeat the question
                    if ((slotsAvailLength != 0 && slotsReqLength > slotsAvailLength) || slotsReqLength > 10) {
                        continueLoop = true;
                        break;
                    } else {
                        cout << "\n-------------------------------------------------------\n";
                        for (auto i = 0; i < 3; i++) {
                            for (auto j = 0; j < 3; j++) {
                                int b{};

                                // if the slots contain red, then user cannot place green there. so b = 0
                                // if the slots contain number, then proceed to place green at requested slot
                                // rest of process of placing green is same as the process for red
                                box.at(i).at(j) == "r" ? b = 0 : b = stoi(box.at(i).at(j));
                                for (auto k = 0; k < slotsRequested.length(); k++) {
                                    if (slotsRequested.substr(k, 1) == " ") continue;
                                    int s = stoi(slotsRequested.substr(k, slotsRequested.find(" ", k)));
                                    if (b == s) {
                                        box.at(i).at(j) = "g";
                                    }
                                }
                                cout << box.at(i).at(j) << "  ";
                            }
                            cout << "\n";
                        }
                        slotsRequested = "";
                    }
                } while (continueLoop);

                // check for available slots and store in correct format for display (with comma)
                // count: sum of occpuied slots
                slotsAvailable = "";
                int count{0};
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        if (box.at(i).at(j).find_first_not_of("123456789") == string::npos) {
                            slotsAvailable.append(box.at(i).at(j));
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
                cout << "\n-------------------------------------------------------\n";
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        cout << box.at(i).at(j) << "  ";
                    }
                    cout << "\n";
                }
            }

            do {
                cout << "\nDo you want to place blue pegs (y, n)? ";
                cin >> place_blue;

                // if user inputs more than 1 letter, ignore() considers the first character
                // ignores the rest upto 100 characters
                cin.ignore(limit, '\n');

                // true -> wrong input, repeat question; false -> input is ''y' or 'n'. move to next question
                continueLoop = (place_blue == 'y' || place_blue == 'n') ? false : true;
            } while (continueLoop);

            if (place_blue == 'y') {
                do {
                    cout << "\nWhere to place blue pegs (" << slotsAvailable << ")? ";
                    continueLoop = false;

                    getline(cin, slotsRequested);
                    stringstream str(slotsRequested);
                    string word{};
                    int slotsReqLength{0};
                    int slotsAvailLength{0};

                    // this loop checks if user request contains duplicate; if found, repeat question
                    for (int i = 0; i < slotsRequested.size(); i++) {
                        char s = slotsRequested[i];
                        if (slotsRequested.find(s, i + 1) != string::npos && s != ' ') {
                            continueLoop = true;
                            break;
                        }
                    }

                    // this loop checks if user request contains invalid input like 10, aaa, 39f9; if found, repeat question
                    // for valid inputs, it computes the length of the total requested slots
                    while (str >> word) {
                        if ((word.find_first_not_of("123456789") != string::npos) || stoi(word) > 9) {
                            continueLoop = true;
                            break;
                        } else {
                            slotsReqLength++;
                        }
                        // checks if slotsAvailable has been modified by red pegs
                        // then checks if user input matches available slots; if not, repeat the question
                        if ((place_red == 'y' || place_green == 'y') && slotsAvailable.find(word) == string::npos) {
                            continueLoop = true;
                            break;
                        }
                    }
                    // if user chooses to place blue pegs after red/green pegs, then get length of available slots
                    if (place_red == 'y' || place_green == 'y') {
                        stringstream str(slotsAvailable);
                        string word{};
                        while (str >> word) {
                            if ((word.find_first_of("123456789") != string::npos)) {
                                slotsAvailLength++;
                            }
                        }
                    }

                    // if above 2 loops prove invalid input, repeat the question
                    if (continueLoop == true) continue;

                    // if blue is placed after red/green pegs, then check if requested slots are not more than available slots
                    // or if red/green is skipped, then all 9 slots are available. check if requested slots are not more than 10
                    // if any of these conditions fail, repeat the question
                    if ((slotsAvailLength != 0 && slotsReqLength > slotsAvailLength) || slotsReqLength > 10) {
                        continueLoop = true;
                        break;
                    } else {
                        cout << "\n-------------------------------------------------------\n";
                        for (auto i = 0; i < 3; i++) {
                            for (auto j = 0; j < 3; j++) {
                                int b{};

                                // if the slots contain red/green, then user cannot place blue there. so b = 0.
                                // if the slots contain number, then proceed to place blue at requested slot.
                                // rest of process of placing blue is same as the process for red and green.
                                (box.at(i).at(j) == "r" || box.at(i).at(j) == "g") ? b = 0 : b = stoi(box.at(i).at(j));
                                for (auto k = 0; k < slotsRequested.length(); k++) {
                                    if (slotsRequested.substr(k, 1) == " ") {
                                        continue;
                                    }
                                    int s = stoi(slotsRequested.substr(k, slotsRequested.find(" ", k)));
                                    if (b == s && s < 10) {
                                        box.at(i).at(j) = "b";
                                    }
                                }
                                cout << box.at(i).at(j) << "  ";
                                // if (i == 2 && j == 2) {
                                //     continueLoop = false;
                                //     break;
                                //     ;
                                // }
                            }
                            cout << "\n";
                        }
                        slotsRequested = "";
                    }
                } while (continueLoop);

                // check for available slots and store in correct format for display (with comma)
                // count: sum of occpuied slots
                slotsAvailable = "";
                int count{0};
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        if (box.at(i).at(j).find_first_not_of("123456789") == string::npos) {
                            slotsAvailable.append(box.at(i).at(j));
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
                cout << "\n-------------------------------------------------------\n";
                for (auto i = 0; i < 3; i++) {
                    for (auto j = 0; j < 3; j++) {
                        cout << box.at(i).at(j) << "  ";
                    }
                    cout << "\n";
                }
            }
        } while (continueLoop);
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
