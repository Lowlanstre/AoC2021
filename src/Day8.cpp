#include "Day8.hpp"

void Day8::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day8.txt");

    std::vector<std::string> lines;

    while (!inputStream.eof()) {

        std::string line;

        std::getline(inputStream,line);

        lines.emplace_back(line);
    }

    for(auto& line : lines) {

        std::stringstream ss(line);
        std::string token;

        std::unordered_map<int,std::string> decode;
        std::vector<std::string> numbers;
        std::vector<std::string> output;

        for(int i = 0; i < 10; ++i) {
            ss >> token;
            std::sort(token.begin(),token.end());
            numbers.emplace_back(token);
        }
        ss >> token;
        for(int i = 0; i < 4; ++i) {
            ss >> token;
            std::sort(token.begin(),token.end());
            output.emplace_back(token);
        }

        // First iteration, get 1 4 7 8

        for(auto& number : numbers) {
            if(number.length() == 2)
                decode.emplace(1,number);
            else if(number.length() == 4)
                decode.emplace(4,number);
            else if(number.length() == 3)
                decode.emplace(7,number);
            else if(number.length() == 7)
                decode.emplace(8,number);
        }

        // Second iteration, get 0,2,3,5,6,9

        for(auto& number : numbers) {
            if(number.length() == 5 && containsNum(number,decode.at(1)) == 2)
                decode.emplace(3,number);
            else if(number.length() == 6 && containsNum(number,decode.at(1)) == 1)
                decode.emplace(6,number);
            else if(number.length() == 6 && containsNum(number,decode.at(4)) == 4)
                decode.emplace(9,number);
            else if(number.length() == 6 && containsNum(number,decode.at(1)) == 2)
                decode.emplace(0,number);
            else if(number.length() == 5 && containsNum(number,decode.at(4)) == 3)
                decode.emplace(5,number);
            else if(number.length() == 5)
                decode.emplace(2,number);
        }

        int outputVal = 0;

        for (int i = 1000, j = 0; i > 0; i /= 10, ++j) {

            for(auto& [number, signal] : decode) {

                if(output[j] == signal) {
                    if (number == 1 || number == 4 || number == 7 || number == 8)
                        ++partOne;
                    outputVal += number*i;
                    break;
                }
            }
        }

        partTwo += outputVal;
    }


    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

int Day8::containsNum(std::string &s, std::string& str) {
    int res = 0;

    for (auto c : str) {
        if(s.find(c) != std::string::npos)
            ++res;
    }

    return res;
}
