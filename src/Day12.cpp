#include "Day12.hpp"

void Day12::Solve() {

    typedef std::vector<std::pair<std::vector<std::string>,bool>> VecPVecStr;
    typedef std::vector<std::vector<std::string>> VVecStr;

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day12.txt");

    std::vector<std::pair<std::string,std::string>> connections;

    while (!inputStream.eof()) {

        std::string line;

        std::getline(inputStream, line);

        auto gap = line.find('-');

        connections.emplace_back(line.substr(0,gap),line.substr(gap+1,std::string::npos));
        connections.emplace_back(line.substr(gap+1,std::string::npos),line.substr(0,gap));
    }

    VVecStr paths = {{"start"}};
    VVecStr closedPaths;

    VecPVecStr pathsTwo = {{{"start"}, true}};
    VecPVecStr closedPathsTwo;

    while(!paths.empty() || !pathsTwo.empty()) {

        VVecStr newPaths;
        VecPVecStr newPathsTwo;

        // Part 1

        for(auto& path : paths) {
            if(path.back() == "end") {
                closedPaths.emplace_back(path);
                continue;
            }
            for(auto& pair : connections) {
                if(pair.first == path.back()) {
                    bool pred1 = int(pair.second[0]) == std::toupper(pair.second[0]);
                    bool pred2 = std::find(path.begin(), path.end(), pair.second) == path.end();

                    if(pred1 || pred2) {
                        newPaths.emplace_back(path);
                        newPaths.back().emplace_back(pair.second);
                    }
                }
            }
        }

        // Part 2

        for(auto& path : pathsTwo) {
            if(path.first.back() == "end") {
                closedPathsTwo.emplace_back(path);
                continue;
            }

            for(auto& pair : connections) {
                if(pair.first == path.first.back()) {

                    bool pred1 = int(pair.second[0]) == std::toupper(pair.second[0]);
                    bool pred2 = std::find(path.first.begin(), path.first.end(), pair.second) == path.first.end();
                    bool pred3 = path.second && pair.second != "start";

                    if(pred1 || pred2 || pred3) {
                        newPathsTwo.emplace_back(path);
                        newPathsTwo.back().first.emplace_back(pair.second);
                    }
                    if(!pred1 && !pred2 && pred3)
                        newPathsTwo.back().second = false;
                }
            }
        }

        paths = newPaths;
        pathsTwo = newPathsTwo;
    }

    partOne = closedPaths.size();
    partTwo = closedPathsTwo.size();

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}
