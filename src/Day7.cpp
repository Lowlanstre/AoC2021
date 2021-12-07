#include "Day7.hpp"

void Day7::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day7.txt");

    std::vector<int> numbers;

    while (!inputStream.eof()) {

        int number;
        char garbage;

        inputStream >> number >> garbage;

        numbers.emplace_back(number);
    }

    std::sort(numbers.begin(),numbers.end());
    int target = numbers[numbers.size()/2];
    
    double meanTwo = std::accumulate(numbers.begin(),numbers.end(),0)/double(numbers.size());

    int posOne = 0;
    int posTwo = 0;

    for(auto n : numbers) {
        partOne += std::abs(n-target);

        for(int i = 1; i <= std::abs(n-int(std::ceil(meanTwo)));++i)
            posOne += i;
        for(int i = 1; i <= std::abs(n-int(std::floor(meanTwo)));++i)
            posTwo += i;

    }

    partTwo = posOne < posTwo ? posOne : posTwo;

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
