#include "Day14.hpp"

void Day14::Solve() {

    const int steps = 40;

    typedef unsigned long long ull;

    ull partOne = 0;
    ull partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day14.txt");

    std::string polymer;
    std::string line;

    std::getline(inputStream,polymer);
    std::getline(inputStream,line);

    std::vector<std::pair<std::string,ull>> pairs;
    std::vector<std::string> transformations;

    while (!inputStream.eof()) {

        std::string first,second;

        inputStream >> first >> second >> second;

        for(auto& x : {first,first[0]+second,first[1]+second}) {
            if (std::find(pairs.begin(), pairs.end(), std::make_pair(x, ull(0))) == pairs.end()) {
                pairs.emplace_back(x, 0);
            }
        }

        transformations.emplace_back(first+second);
    }

    for(int i = 0; i < polymer.size()-1; ++i) {
        ++std::find_if(pairs.begin(), pairs.end(),
                              [&polymer,i](auto p){return p.first == polymer.substr(i,2);})->second;
    }

    std::vector<std::pair<std::string,ull>> partOnePairs;

    for(int step = 0; step < steps; ++step) {

        auto bufferPairs = pairs;

        for(auto &pair : bufferPairs)
            pair.second = 0;

        for(auto& pair : pairs) {

            for(auto& trans : transformations) {

                if(trans.substr(0,2) == pair.first) {
                    auto prodOne = trans.substr(0,1) + trans.substr(2,1);
                    auto prodTwo = trans.substr(2,1) + trans.substr(1,1);

                    for(auto& x : {prodOne,prodTwo}) {
                        std::find_if(bufferPairs.begin(), bufferPairs.end(),
                                     [&x](auto p){return p.first == x;})->second += pair.second;
                    }
                    break;
                }
            }
        }
        pairs = bufferPairs;

        if(step+1 == 10) {
            partOnePairs = pairs;
        }
    }

    std::vector<std::vector<ull>> occurrences = {2,std::vector<ull>{}};
    std::vector<std::vector<std::pair<std::string,ull>>*> pairPair = {&partOnePairs,&pairs};

    for(int index = 0; index < 2; ++index) {

        for(int i = 65; i < 91; ++i) {

            double count = 0;

            if(polymer[0] == char(i))
                count += 0.5;
            if(polymer.back() == char(i))
                count += 0.5;

            for (auto &pair: *pairPair[index]) {

                if (pair.first == std::string{char(i),char(i)})
                    count += pair.second;
                else if (pair.first[0] == char(i) || pair.first[1] == char(i)) {
                    count += double(pair.second) / 2;
                }
            }
            occurrences[index].push_back(ull(count));
        }

        occurrences[index].erase(std::remove(occurrences[index].begin(),
                                             occurrences[index].end(), 0), occurrences[index].end());
        std::sort(occurrences[index].begin(), occurrences[index].end());
    }

    partOne = occurrences[0].back() - occurrences[0][0];
    partTwo = occurrences[1].back() - occurrences[1][0];

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
