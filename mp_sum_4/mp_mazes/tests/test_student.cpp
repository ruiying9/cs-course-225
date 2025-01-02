#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"
#include "mazereader.h"

using namespace cs225;
using namespace std;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {

    SquareMaze maze;
    maze.makeMaze(10, 15);
    PNG* out = maze.drawMaze();
    out->writeToFile("testing.png");
    vector<int> solution = maze.solveMaze();
    bool student_wrote_test_case = true;
    REQUIRE( student_wrote_test_case );
}
