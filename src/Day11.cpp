#include "Day11.hpp"

void Day11::Solve() {

    int partOne = 0;
    int partTwo = 0;

    int partOneBuffer = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day11.txt");

    VVecI field;

    while (!inputStream.eof()) {

        std::vector<int> row;

        std::string line;

        std::getline(inputStream, line);

        for(auto& c : line) {
            row.emplace_back(c - '0');
        }
        field.emplace_back(row);
    }

    for(int i = 1;; ++i) {

        for(auto& row : field) {
            for(auto &val : row){
                ++val;
            }
        }

        std::vector<std::pair<int,int>> popped;

        for (int y_t = 0; y_t < field.size(); ++y_t) {
            for (int x_t = 0; x_t < field.at(y_t).size(); ++x_t) {

                std::queue<std::pair<int, int>> queue;

                queue.emplace(y_t, x_t);

                while (!queue.empty()) {

                    int y = queue.front().first;
                    int x = queue.front().second;

                    if (field[y][x] > 9) {
                        ++partOneBuffer;
                        popped.emplace_back(y, x);
                        field[y][x] = -69;

                        for (int yy = -1; yy <= 1; ++yy) {
                            for (int xx = -1; xx <= 1; ++xx) {
                                if (inBounds(field, y+yy, x+xx)) {
                                    ++field[y+yy][x+xx];
                                    if (field[y+yy][x+xx] > 9)
                                        queue.emplace(y+yy, x+xx);
                                }
                            }
                        }
                    }
                    queue.pop();
                }
            }
        }

        if(i == 100) {
            partOne = partOneBuffer;
        }

        if(popped.size() == field.size() * field.back().size()) {
            partTwo = i;
            break;
        }

        for (auto &pair: popped) {
            field[pair.first][pair.second] = 0;
        }
    }

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << partTwo << "\n";
}

bool Day11::inBounds(Day11::VVecI &v, int y, int x) {
    if(x < 0 || y < 0)
        return false;
    if(y >= v.size() || x >= v.back().size())
        return false;
    return true;
}
