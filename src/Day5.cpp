#include "Day5.hpp"

void Day5::Solve() {

    const int fieldSize = 1000;

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day5.txt");

    std::vector<std::pair<int,int>> starts;
    std::vector<std::pair<int,int>> finishes;

    std::vector<std::vector<int>> field(fieldSize,std::vector<int>(fieldSize,0));
    std::vector<std::vector<int>> fieldTwo(fieldSize,std::vector<int>(fieldSize,0));

    while (!inputStream.eof()) {

            int numberX;
            int numberY;
            char garbage;

            inputStream >> numberX >> garbage >> numberY;

            starts.emplace_back(numberX,numberY);

            inputStream >> garbage >> garbage;

            inputStream >> numberX >> garbage >> numberY;

            finishes.emplace_back(numberX,numberY);

    }

    for(int index = 0; index < starts.size(); ++index) {

        if(starts[index].first == finishes[index].first) {

            auto min = std::min(starts[index].second, finishes[index].second);
            auto max = std::max(starts[index].second, finishes[index].second);

            for(int i = min; i <= max; ++i) {
                ++field[starts[index].first][i];
                ++fieldTwo[starts[index].first][i];
            }

        } else if(starts[index].second == finishes[index].second) {

            auto min = std::min(starts[index].first, finishes[index].first);
            auto max = std::max(starts[index].first, finishes[index].first);

            for(int i = min; i <= max; ++i) {
                ++field[i][starts[index].second];
                ++fieldTwo[i][starts[index].second];
            }

        } else {

            int dirX = 1;
            int dirY = 1;

            if(starts[index].first > finishes[index].first)
                dirX = -1;
            if(starts[index].second > finishes[index].second) {
                dirY = -1;
            }

            auto minFirst = std::min(starts[index].first, finishes[index].first);
            auto maxFirst = std::max(starts[index].first, finishes[index].first);



            for(int i = 0; i <= maxFirst - minFirst ; ++i) {
                ++fieldTwo[starts[index].first+ (i*dirX)][starts[index].second + (i*dirY)];
            }

        }

    }

    for(int i = 0; i < fieldSize; ++i) {

        for(int j = 0; j < fieldSize; ++j) {

            if (field[i][j] > 1)
                ++partOne;
            if (fieldTwo[i][j] > 1)
                ++partTwo;
        }
    }

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
