#include "Day13.hpp"

void Day13::Solve() {

    int partOne = 0;
    int partTwo = 0;

    std::ifstream inputStream;
    inputStream.open("..\\input\\day13.txt");

    std::vector<std::pair<std::string,int>> folds;

    std::vector<std::pair<int,int>> points;

    while (!inputStream.eof()) {

        std::string line;

        std::getline(inputStream,line);

        if(!line.empty()) {

            std::replace(line.begin(),line.end(),',',' ');

            std::stringstream ss(line);

            int numX, numY;

            ss >> numX >> numY;

            points.emplace_back(numX,numY);

        } else {
            while(!inputStream.eof()) {

                std::getline(inputStream,line);

                std::string toRemove = "fold along ";

                line.replace(line.find(toRemove),toRemove.length(),"");

                std::replace(line.begin(),line.end(),'=',' ');

                std::stringstream ss(line);

                std::string dir;
                int amount;

                ss >> dir >> amount;

                folds.emplace_back(dir,amount);
            }
        }
    }

    auto maxX = std::max_element(points.begin(),points.end(), [](auto p1, auto p2){return p1.first < p2.first;})->first;
    auto maxY = std::max_element(points.begin(),points.end(), [](auto p1, auto p2){return p1.second < p2.second;})->second;

    std::vector<std::vector<int>> field(maxY+1,std::vector<int>(maxX+1,0));

    for(auto& point : points) {

        field[point.second][point.first] = 1;
    }

    for(auto& fold : folds) {

        if(fold.first == "y") {

            if(field.size()-1-fold.second > fold.second) {

                for(int i = 1; i <= fold.second; ++i) {
                    for(int x = 0; x < field.back().size(); ++x) {
                        field[fold.second+i][x] += field[fold.second-i][x];
                    }
                }
                field = std::vector<std::vector<int>>(field.begin()+fold.second+1,field.end());
            } else {

                for(int i = 1; i <= field.size()-1-fold.second; ++i) {
                    for(int x = 0; x < field.back().size(); ++x) {
                        field[fold.second-i][x] += field[fold.second+i][x];
                    }
                }
                field = std::vector<std::vector<int>>(field.begin(),field.end()-(field.size()-fold.second));
            }
        }
        else {

            if(field.back().size()-1-fold.second > fold.second) {

                for(int y = 0; y < field.size(); ++y) {
                    for(int i = 1; i <= fold.second; ++i) {
                        field[y][fold.second+i] += field[y][fold.second-i];
                    }
                }

                for(auto& row : field) {
                    row = std::vector<int>(row.begin()+fold.second+1,row.end());
                }

            } else {

                for(int y = 0; y < field.size(); ++y) {
                    for(int i = 1; i <= field.back().size()-1-fold.second; ++i) {
                        field[y][fold.second-i] += field[y][fold.second+i];
                    }
                }

                for(auto& row : field) {
                    row = std::vector<int>(row.begin(),row.end()-(field.back().size()-fold.second));
                }

            }
        }
        if(!partOne) {
            for(auto& row : field) {
                for(auto val : row) {
                    if(val != 0)
                        ++partOne;
                }
            }
        }
    }

    std::cout << "The answer to part 1 is: " << partOne << "\n";
    std::cout << "The answer to part 2 is: " << "\n";

    for(auto& row : field) {

        std::string printrow;

        for(auto val : row) {
            if(val == 0) {
                printrow += char(176);
            }
            if(val != 0) {
                printrow += char(178);
            }
        }
        std::cout << printrow << "\n";
    }
}