#include "Day6.hpp"

void Day6::Solve() {

    typedef std::vector<unsigned  long long> VecULL;

    const int days1 = 80;
    const int days2 = 256;

    unsigned long long partOne = 0;
    unsigned long long partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day6.txt");

    VecULL fish(9,0);
    VecULL bufferFish(9,0);

    while (!inputStream.eof()) {

        int number;
        char garbage;

        inputStream >> number >> garbage;

        ++fish.at(number);

    }

    for(int i = 0; i < days2; ++i) {

        for (int j = 0; j < fish.size(); ++j) {

            bufferFish.at(wrap(j)) += fish.at(j);

        }

        bufferFish.at(8) = fish.at(0);

        fish = bufferFish;

        for (auto& val: bufferFish)
            val = 0;

        if(i == days1-1) {
            for(auto x : fish)
                partOne += x;
        }
    }

    for(auto x : fish)
        partTwo += x;

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

int Day6::wrap(int n) {
    if (!n)
        return 6;
    return n-1;
}
