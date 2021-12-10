#include "Day10.hpp"

void Day10::Solve() {

    int partOne = 0;
    long long partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day10.txt");

    std::vector<std::string> lines;
    std::vector<long long> scores;

    while (!inputStream.eof()) {

        std::string line;

        std::getline(inputStream, line);

        lines.push_back(line);
    }

    for(auto &line : lines) {

        bool corrupted = false;

        std::stack<char> open;

        for(auto charac : line) {

            if(charac == translate(charac)) {
                open.emplace(charac);
            } else if(translate(charac) == open.top()){
                open.pop();
            }   else {
                partOne += points(charac,1);
                corrupted = true;
                break;
            }
        }

        if(!corrupted) {
            if(!open.empty())
                scores.push_back(0);
            while(!open.empty()) {
                scores.back() *= 5;
                scores.back() += points(open.top(),2);
                open.pop();
            }
        }
    }

    std::sort(scores.begin(),scores.end());

    partTwo = scores[(scores.size()-1)/2];

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

char Day10::translate(char c) {
    switch (c) {
        case ')':
            return '(';
        case ']':
            return '[';
        case '}':
            return '{';
        case '>':
            return '<';
        default:
            return c;
    }
}

int Day10::points(char c, int part) {
    if(!(part-1)) {
        switch (c) {
            case ')':
                return 3;
            case ']':
                return 57;
            case '}':
                return 1197;
            case '>':
                return 25137;
            default:
                std::cout << "Logic error\n";
                return -1;
        }
    } else {
        switch (c) {
            case '(':
                return 1;
            case '[':
                return 2;
            case '{':
                return 3;
            case '<':
                return 4;
            default:
                std::cout << "Logic error\n";
                return -1;
        }
    }
}
