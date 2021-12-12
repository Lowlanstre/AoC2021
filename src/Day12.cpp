#include "Day12.hpp"

void Day12::Solve() {

    typedef std::vector<std::pair<std::vector<std::string>,bool>> VecPVecStr;

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

    VecPVecStr paths = {{{"start"}, true}};
    VecPVecStr closedPaths;

    while(!paths.empty()) {

        VecPVecStr newPaths;

        for(auto& path : paths) {
            if(path.first.back() == "end") {
                closedPaths.emplace_back(path);
                continue;
            }

            for(auto& pair : connections) {
                if(pair.first == path.first.back()) {

                    bool pred1 = int(pair.second[0]) == std::toupper(pair.second[0]);
                    bool pred2 = std::find(path.first.begin(), path.first.end(), pair.second) == path.first.end();
                    bool pred3 = path.second && pair.second != "start";

                    if(pred1 || pred2 || pred3) {
                        newPaths.emplace_back(path);
                        newPaths.back().first.emplace_back(pair.second);
                    }
                    if(!pred1 && !pred2 && pred3)
                        newPaths.back().second = false;
                }
            }
        }

        paths = newPaths;
    }

    partOne = std::count_if(closedPaths.begin(), closedPaths.end(), [](auto p){return p.second;});
    partTwo = closedPaths.size();

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}