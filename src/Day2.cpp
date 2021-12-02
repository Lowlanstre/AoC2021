#include "Day2.hpp"

void Day2::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day2.txt");

    int depthOne = 0;
    int lengthOne = 0;

    int depthTwo = 0;
    int lengthTwo = 0;
    int aimTwo = 0;


    while (!inputStream.eof()) {

        std::string instruction;
        int value;

        inputStream >> instruction >> value;

        if(instruction == "forward") {
            lengthOne += value;
            lengthTwo += value;
            depthTwo += aimTwo * value;
        }
        else if(instruction == "down") {
            depthOne += value;
            aimTwo += value;
        }
        else if(instruction == "up") {
            depthOne -= value;
            aimTwo -= value;
        }
    }

    partOne = depthOne * lengthOne;
    partTwo = depthTwo * lengthTwo;

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
