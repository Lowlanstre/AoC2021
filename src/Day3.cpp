///////////////////////////////
// 3.12.2021
//
// As of writing this message I feel extremely lazy and uninterested to clean up this solution,
// so i just did the good old copypasting, might rewrite in near future.
//
///////////////////////////////

#include "Day3.hpp"

void Day3::Solve() {

    int partOne = 0;
    int partTwo = 0;

    int gammaOne = 0;
    int epsilonOne = 0;

    int gammaTwo = 0;
    int epsilonTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day3.txt");

    std::vector<int> signals;

    std::vector<std::vector<int>> instructions;

    while (!inputStream.eof()) {

        std::string instruction;

        inputStream >> instruction;

        if(signals.empty())
            signals = std::vector<int>(instruction.size(),0);

        std::vector<int> line;

        for (int i = 0; i < instruction.size(); ++i) {

            line.push_back(instruction[i] - '0');

            if (instruction[i] == '1')
                ++signals.at(i);
            else
                --signals.at(i);
        }

        instructions.push_back(line);
    }

    auto gamEp = binToDec(signals);

    gammaOne = gamEp.first;
    epsilonOne = gamEp.second;

    partOne = gammaOne * epsilonOne;

    auto instructionsCopy = instructions;

    for (int i = 0; i < signals.size(); ++i) {

        int val = 0;

        for (auto ins : instructionsCopy) {
            if (ins.at(i) == 1)
                val += 1;
            else
                val -= 1;
        }

        if (val >= 0)
            val = 1;
        else
            val = 0;

        decltype(instructionsCopy) instructionsCopyCopy(instructionsCopy.size(), std::vector<int>());
        auto s = std::copy_if(instructionsCopy.begin(), instructionsCopy.end(),instructionsCopyCopy.begin(),\
                [&val, &i](std::vector<int> x){return x[i]==val;});
        instructionsCopyCopy.resize(std::distance(instructionsCopyCopy.begin(),s));
        instructionsCopy = instructionsCopyCopy;

        if(instructionsCopy.size() == 1) {
            gammaTwo = binToDec(instructionsCopy.back()).first;
        }
    }

    for (int i = 0; i < signals.size(); ++i) {

        int val = 0;

        for (auto ins : instructions) {
            if (ins.at(i) == 1)
                val += 1;
            else
                val -= 1;
        }

        if (val >= 0)
            val = 0;
        else
            val = 1;

        decltype(instructions) instructionsCopyCopy(instructions.size(), std::vector<int>());
        auto s = std::copy_if(instructions.begin(), instructions.end(),instructionsCopyCopy.begin(),\
                [&val, &i](std::vector<int> x){return x[i]==val;});
        instructionsCopyCopy.resize(std::distance(instructionsCopyCopy.begin(),s));
        instructions = instructionsCopyCopy;

        if(instructions.size() == 1) {
            epsilonTwo = binToDec(instructions.back()).first;
        }
    }

    partTwo = gammaTwo * epsilonTwo;

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

std::pair<int,int> Day3::binToDec(std::vector<int> inp) {

    int ret = 0;

    int degree = 1;
    for (auto rit = inp.rbegin(); rit != inp.rend(); ++rit) {

        if(*rit > 0)
            ret += degree;
        degree *= 2;
    }

    int ret2 = degree-ret-1;

    return std::make_pair(ret,ret2);
}
