#pragma once
#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>

using namespace cs225;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();
    private:
        int width_;
        int height_;
        int size_;
        DisjointSets sets;
        std::vector<std::pair<bool, bool>> rdwalls; //first is the right wall and second is the down wall
};