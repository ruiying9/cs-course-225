#include "maze.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
SquareMaze::SquareMaze() {}
void SquareMaze::makeMaze(int width, int height){
    width_=width;
    height_=height;
    walls.clear();
    walls.resize(width, vector<pair<bool,bool>>(height, make_pair(true,true)));
	set.addelements(width*height);
    while(set.size(0)!=width*height){
        for(int j=0;j<height;j++){/*row number*/
            for(int i=0;i<width;i++){/*column number*/
                int direct = rand() % 2;
                if(direct==0){
                    if(i!=(width-1)){
                        if(set.find(i+j*width)!=set.find((i+1)+j*width)){/*they are not connected yet*/
                            setWall(i, j, 0, false);/*right*/
                            set.setunion(i+j*width,(i+1)+j*width);
                        }
                    }
                }
                if(direct==1){
                    if(j!=height-1){/*go down*/
                        if(set.find(i+j*width)!=set.find(i+(j+1)*width)){/*they are not connected yet*/
                            setWall(i, j, 1, false);/*set its wall to false-no wall*/
                            set.setunion(i+j*width,i+(j+1)*width);/*make elements in the set(node) have the same root*/
                        }
                    }
                }
            }
        }
    }
}
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir==0){/*right:remember x is column number y is row number*/
        if(x>=width_-1){/*x column y row*/
            return false;
        } 
        return !walls[x][y].first;
    } else if(dir==1){/*go down*/
        if(y>=height_-1){
            return false;
        }
        return !walls[x][y].second;
    } else if (dir==2){/*go left*/
        if(x<=0){
            return false;
        }
        return !walls[x-1][y].first;
    } else{/*go up*/
        if(y<=0){
            return false;
        }
        return !walls[x][y-1].second;
    }
    return false;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir==0){/*go right*/
        walls[x][y].first=exists;
    } else{/*go down*/
        walls[x][y].second=exists;
    }
}
vector<int> SquareMaze::solveMaze() {
    /*pathinde used to store the path length and prevcell used to store the previous visited cell
    q used to store wait for visiting cell and whenever the cell's neightbor is not visited then the cell's value
    will be the path length and my previous is used to store current cell's index, thus at end i can use pathinde to find
    longest path and then use the index and prevcell to find the previous cell of that index cell and store the whole longest path
    remember that visited cell should not be visited*/
    vector<int> pathInde(width_ * height_, -1);
    vector<int> prevCell(width_ * height_, -1);
    queue<int> q;
    pathInde[0] = 0;/*begin cell*/
    q.push(0);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        int x = curr % width_;
        int y = curr / width_;
        for (int dir = 0; dir < 4; dir++) {/*loop through its neighbor and if it haven't been visited, then its neighbor's value will be current value+1-path length*/
            int x2 = x;/*prev cell will be the current cell's parent cell-used to store the path*/
            int y2 = y;
            if (canTravel(x, y, dir)) {
                if (dir == 0) {
                    x2++;
                } else if (dir == 1) {
                    y2++;
                } else if (dir == 2) {
                    x2--;
                } else {
                    y2--;
                }
                int next = x2+y2 * width_;
                if (pathInde[next] == -1) {
                    prevCell[next] = curr;
                    pathInde[next] = pathInde[curr] + 1;
                    q.push(next);
                }
            }
        }
    }
    int end = -1;
    int max = 0;
    for (int x = 0; x < width_; x++) {
        int curr = (height_ - 1) * width_ + x;
        if (pathInde[curr] > max) {/*find the cell with the longest path from the last row*/
            end = curr;
            max = pathInde[curr];
        }
    }
    vector<int> finalP;
    while (end != 0) {/*from bottom up if end=0 means topmost reached and stop*/
        int prev = prevCell[end];
        if (prev % width_ < end % width_) {/*my previous cell is on its left*/
            finalP.push_back(0);
        } else if (prev / width_ < end / width_) {/*my previous cell is on its top*/
            finalP.push_back(1);
        } else if (prev % width_ > end % width_) {/*my previous cell is on its right*/
            finalP.push_back(2);
        }else{
            finalP.push_back(3);/*my previous cell is on its bottom*/
        }
        end = prev;
    }
    reverse(finalP.begin(), finalP.end());
    return finalP;
}
cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* maze = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    // Blacken the topmost row and leftmost column
    for (int i = 0; i < width_ * 10 + 1; i++) {
        if (i > 9) {
            maze->getPixel(i, 0).l=0;
        }
    }
    for (int j = 0; j < height_ * 10 + 1; j++) {
        maze->getPixel(0, j).l=0;
    }
    for (int i = 0; i < width_; i++) {/*i is row j is column */
        for (int j = 0; j < height_; j++) {
            if (walls[i][j].first) {
                for (int k = 0; k <= 10; k++) {
                    maze->getPixel((i + 1) * 10, j * 10 + k).l = 0;
                }
            }
            if (walls[i][j].second) {
                for (int k = 0; k <= 10; k++) {
                    maze->getPixel(i * 10 + k, (j + 1) * 10).l = 0;
                }
            }
        }
    }
    return maze;
}
cs225::PNG* SquareMaze::drawMazeWithSolution() {
    cs225::PNG* maze = drawMaze();
    vector<int> solve = solveMaze();
    int x = 5, y = 5;
    for (size_t i = 0; i < solve.size(); i++) {
        if (solve[i] == 0) {
            for (int k = 0; k <= 10; k++) {
                cs225::HSLAPixel& pixel = maze->getPixel(x+k, y);/*right*/
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            x += 10;
        } else if (solve[i] == 1) {
            for (int k = 0; k <= 10; k++) {
                cs225::HSLAPixel& pixel = maze->getPixel(x, y+k);/*down*/
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            y += 10;
        } else if (solve[i] == 2) {
            for (int k = 0; k <= 10; k++) {
                cs225::HSLAPixel& pixel = maze->getPixel(x-k, y);/*left*/
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            x -= 10;
        } else {
            for (int k = 0; k <= 10; k++) {
                cs225::HSLAPixel& pixel = maze->getPixel(x, y - k);/*up*/
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
            y -= 10;
        }
    }
    int finalx=x-5;
    int finaly=(int)maze->height()-1;/*last cell's index*/
    for (int k = 1; k <= 9; k++) {
        maze->getPixel(finalx + k, finaly).l = 1;
    }
    return maze;
}