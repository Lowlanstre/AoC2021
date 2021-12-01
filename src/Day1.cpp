#include "Day1.hpp"

void Day1::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day1.txt");

    int last = std::numeric_limits<int>::max();
    int lastWindow = std::numeric_limits<int>::max();
    std::vector<int> window;

    for (int i = 0; !inputStream.eof(); ++i) {

        int num;

        inputStream >> num;

        window.push_back(num);

        if (num > last)
            ++partOne;

        last = num;

        if (i > 1)  {
            auto winLengths = window[i-2] + window[i-1] + window[i];

            if(winLengths > lastWindow)
                ++ partTwo;
            lastWindow = winLengths;
        }
    }

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
