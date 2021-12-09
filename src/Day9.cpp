#include "Day9.hpp"

void Day9::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day9.txt");

    std::vector<std::vector<int>> field;
    std::vector<std::vector<int>> basins;

    std::queue<std::pair<int,int>> queue;

    int basinCount = 0;

    while (!inputStream.eof()) {

        std::vector<int> fieldLine;
        std::vector<int> basinLine;

        std::string line;

        std::getline(inputStream,line);

        for(auto c : line) {

            fieldLine.emplace_back(c - '0');
            basinLine.emplace_back(0);

        }
        field.emplace_back(fieldLine);
        basins.emplace_back(basinLine);
    }

    for(int y = 0; y < field.size(); ++y) {
        for(int x = 0; x < field[y].size(); ++x) {

            bool low = true;

            if(inBounds(field,x-1,y)) {
                if(field[y][x-1] <= field[y][x])
                    low = false;
            }
            if(inBounds(field,x+1,y)) {
                if(field[y][x+1] <= field[y][x])
                    low = false;
            }
            if(inBounds(field,x,y-1)) {
                if(field[y-1][x] <= field[y][x])
                    low = false;
            }
            if(inBounds(field,x,y+1)) {
                if(field[y+1][x] <= field[y][x])
                    low = false;
            }

            if(low)
                partOne += 1+field[y][x];

            // Part 2

            queue.emplace(y,x);

            while(!queue.empty()) {

                int y_t = queue.front().first;
                int x_t = queue.front().second;

                if(field[y_t][x_t] == 9) {
                    queue.pop();
                    continue;
                }

                if(basins[y_t][x_t] == 0) {
                    ++basinCount;
                    basins[y_t][x_t] = basinCount;
                }
                if(inBounds(field,x_t-1,y_t)) {
                    if(field[y_t][x_t-1] != 9 && basins[y_t][x_t-1] == 0) {
                        basins[y_t][x_t-1] = basins[y_t][x_t];
                        queue.emplace(y_t,x_t-1);
                    }
                }
                if(inBounds(field,x_t,y_t-1)) {
                    if(field[y_t-1][x_t] != 9 && basins[y_t-1][x_t] == 0) {
                        basins[y_t-1][x_t] = basins[y_t][x_t];
                        queue.emplace(y_t-1,x_t);
                    }
                }
                if(inBounds(field,x_t+1,y_t)) {
                    if(field[y_t][x_t+1] != 9 && basins[y_t][x_t+1] == 0) {
                        basins[y_t][x_t+1] = basins[y_t][x_t];
                        queue.emplace(y_t,x_t+1);
                    }
                }
                if(inBounds(field,x_t,y_t+1)) {
                    if(field[y_t+1][x_t] != 9 && basins[y_t+1][x_t] == 0) {
                        basins[y_t+1][x_t] = basins[y_t][x_t];
                        queue.emplace(y_t+1,x_t);
                    }
                }
                queue.pop();
            }
        }
    }

    std::vector<int> basinSize(basinCount,0);


    for(auto& row : basins) {
        for(auto basin : row) {
            if(basin == 0)
                continue;
            else
                ++basinSize.at(basin-1);
        }
    }

    std::sort(basinSize.begin(),basinSize.end(), [](int a,int b){return b < a;});

    partTwo = basinSize[0] * basinSize[1] * basinSize[2];

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

bool Day9::inBounds(std::vector<std::vector<int>> &v, int x, int y) {
    if(x < 0 || y < 0)
        return false;
    if(y >= v.size() || x >= v.back().size())
        return false;
    return true;
}
