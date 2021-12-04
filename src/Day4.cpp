#include "Day4.hpp"

void Day4::Solve() {

    typedef std::vector<std::vector<int>> VVecI;
    typedef std::vector<VVecI> VVVecI;

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day4.txt");

    std::vector<int> drawnNums;
    std::string sdrawnNums;

    inputStream >> sdrawnNums;

    std::replace(sdrawnNums.begin(),sdrawnNums.end(), ',', ' ');
    std::istringstream is(sdrawnNums);

    int drawnNum;
    while(is >> drawnNum) {
        drawnNums.push_back(drawnNum);
    }

    VVVecI cards;

    while (!inputStream.eof()) {

        VVecI rowlumn(10, std::vector<int>());

        for(int i = 0; i < 25; ++i) {

            int number;

            inputStream >> number;

            rowlumn[i % 5].push_back(number);
            rowlumn[5 + i / 5].push_back(number);
        }

        cards.push_back(rowlumn);

    }

    bool partOneFound = false;

    std::vector<VVecI> toRemove;

    for (auto number : drawnNums) {

        for (auto &card : cards) {

            bool markForRemove = false;

            for (auto &rowlumn : card) {
                rowlumn.erase(std::remove(rowlumn.begin(), rowlumn.end(), number), rowlumn.end());
                if (rowlumn.empty()) {
                    partOneFound = true;
                    markForRemove = true;
                }
            }

            if(markForRemove)
                toRemove.push_back(card);

            if(partOneFound && partOne == 0) {

                int res = 0;

                for(auto &rowlumn : card) {
                    res += std::accumulate(rowlumn.begin(),rowlumn.end(),0);
                }
                partOne = res/2 * number;
            }
        }

        if(!toRemove.empty() && cards.size() == 1) {
            int res = 0;

            for(auto &rowlumn : toRemove.back()) {
                res += std::accumulate(rowlumn.begin(),rowlumn.end(),0);
            }
            partTwo = res/2 * number;
        }

        if(!toRemove.empty()) {
            for(auto card : toRemove) {
                cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
            }
            toRemove.clear();
        }

    }

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
