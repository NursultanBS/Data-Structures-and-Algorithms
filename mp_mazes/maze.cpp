#include "maze.h" 
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <queue>
#include <stack>
using namespace cs225;
        
SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
    size_ = 0;
}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    size_ = height_ * width_;
    sets.addelements(size_); //for each square create a separate disjoint set
    for (int i = 0; i < size_; ++i) {
        rdwalls.push_back(std::pair<bool, bool> (true, true));
    }

    while (sets.size(0) != size_) { //continues until we have only one set with all the elements
        int X = rand() % width_;
        int Y = rand() % height_;
        bool rightWall = rand() % 2;
        int cur = X + Y * width_;
        int atRight = (X + 1) + Y * width_;
        int atDown = X + (Y + 1) * width_;
        if (rightWall) {
            if (X < (width_ - 1) && rdwalls[cur].first) {
                if (sets.find(cur) != sets.find(atRight)) {
                    setWall(X, Y, 0, false);
                    sets.setunion(cur, atRight);
                }
            }
        } else { //down wall
            if (Y < (height_ - 1) && rdwalls[cur].second) {
                if (sets.find(cur) != sets.find(atDown)) {
                    setWall(X, Y, 1, false);
                    sets.setunion(cur, atDown);
                }
            }
        }
    }
}

/*dir: 0 is a rightward step
       1 is a downward step
       2 is a leftward step
       3 is an upward step */
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        if (!rdwalls[x + y*width_].first && x < width_ - 1) {
            return true;
        } 
    }

    if (dir == 1) {
        if (!rdwalls[x + y*width_].second && y < height_ - 1) {
            return true;
        } 
    }

    if (dir == 2) {
        if (!rdwalls[(x - 1) + y*width_].first && x > 0) {
            return true;
        }
    }

    if (dir == 3) {
        if (!rdwalls[x + (y - 1)*width_].second && y > 0) {
            return true;
        }
    }

    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) {
        rdwalls[x + y*width_].first = exists;
    }

    if (dir == 1) {
        rdwalls[x + y*width_].second = exists;
    }
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> longestPath;
    std::queue<int> q;
    std::vector<bool> visited;
    visited.resize(size_, false);
    std::vector<int> prev;
    prev.resize(size_, -1);
    std::vector<int> length;
    length.resize(size_, -1);

    visited[0] = true;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int X = v%width_;
        int Y = v/width_;
        if (canTravel(X, Y, 0) && !visited[v+1] && length[v+1] == -1) {
            length[v+1] = length[v] + 1;
            prev[v+1] = v;
            visited[v+1] = true;
            q.push(v+1);
        }
        if (canTravel(X, Y, 1) && !visited[v + width_] && length[v+width_] == -1) {
            length[v + width_] = length[v] + 1;
            prev[v + width_] = v;
            visited[v + width_] = true;
            q.push(v + width_);
        }
        if (canTravel(X, Y, 2) && !visited[v-1] && length[v-1] == -1) {
            length[v-1] = length[v] + 1;
            prev[v-1] = v;
            visited[v-1] = true;;
            q.push(v-1);
        }
        if (canTravel(X, Y, 3) && !visited[v - width_] && length[v-width_] == -1) {
            length[v - width_] = length[v] + 1;
            prev[v - width_] = v;
            visited[v - width_] = true;
            q.push(v - width_);
        }
    }

    // Now we find the longest path to one of the bottom cells
    int largestLength = 0;
    int index;
    for (int i = size_ - width_; i < size_; i++) {
        if (length[i] > largestLength) {
            largestLength = length[i];
            index = i;
        }
    }

    std::stack<int> s;
    while (index) {
        if (prev[index] == index - 1) {
            s.push(0);
        } else if (prev[index] == index - width_) {
            s.push(1);
        } else if (prev[index] == index + 1) {
            s.push(2);
        } else if (prev[index] == index + width_) {
            s.push(3);
        }
        index = prev[index];
    }

    while (!s.empty()) {
        longestPath.push_back(s.top());
        s.pop();
    }

    return longestPath;
}

PNG * SquareMaze::drawMaze() const {
    PNG * png = new PNG(width_*10 + 1, height_*10 + 1);
    for (int x = 0; x < width_*10 + 1; ++x) {
        for (int y = 0; y < height_*10 +1; ++y) {
            if (x == 0) {
                png->getPixel(x, y).l = 0;
            }
            if (x > 9 && y == 0) {
                png->getPixel(x, y).l = 0;
            }
        }
    }
    
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            if (rdwalls[x + y*width_].first) { //if we have the right wall
                for (int k = 0; k < 11; ++k){
                    png->getPixel((x+1)*10, y*10 + k).l = 0;
                }
            }
            if (rdwalls[x + y*width_].second) { //if we have the bottom wall
                for (int k = 0; k < 11; ++k) {
                    png->getPixel(x*10 + k, (y+1)*10).l = 0;
                }
            }
        }
    }
    return png;
}

PNG * SquareMaze::drawMazeWithSolution() {
    PNG * png = drawMaze();
    std::vector<int> longestPath = solveMaze();
    int X = 5;
    int Y = 5;

    for (int step = 0; step < int(longestPath.size()); ++step) {
        if (longestPath[step] == 0) {
            for (int k = 0; k < 11; ++k) {
                HSLAPixel & pixel = png->getPixel(X + k, Y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            X = X + 10;
        } else if (longestPath[step] == 1) {
            for (int k = 0; k < 11; ++k) {
                HSLAPixel & pixel = png->getPixel(X, Y + k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            Y = Y + 10;
        } else if (longestPath[step] == 2) {
            for (int k = 0; k < 11; ++k) {
                HSLAPixel & pixel = png->getPixel(X - k, Y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            X = X -10;
        } else if (longestPath[step] == 3) {
            for (int k = 0; k < 11; ++k) {
                HSLAPixel & pixel = png->getPixel(X, Y - k);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            Y = Y - 10;
        }
    }

    for (int i = X - 4; i < X + 5; ++i) {
        HSLAPixel & pixel = png->getPixel(i, Y + 5);
        pixel.l = 1;
        pixel.a = 1;
    }

    return png;
}