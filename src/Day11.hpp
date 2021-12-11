#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class Day11 {

private:
    typedef std::vector<std::vector<int>> VVecI;

public:

    static void Solve();

    static bool inBounds(VVecI& v, int y, int x);
};

