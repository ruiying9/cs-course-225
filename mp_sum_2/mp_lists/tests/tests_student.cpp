#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.
TEST_CASE("List::test1", "[weight=5][part=2]") {
  List<int> list;
  for(int i=0;i<6;i++){
    list.insertBack(i);
  }
  list.reverseNth(2);
  stringstream s;
  list.print(s);

  REQUIRE( "< 1 0 3 2 5 4 >" == s.str() );
  // PNG in;        in.readFromFile("../data/alma.png");
  // PNG expected;  expected.readFromFile("../data/expected-reverse.png");

  // List<HSLAPixel> list = imageToList(in);
  // list.reverse();
  // PNG out = listToImage(list, in.width(), in.height());
  // out.writeToFile("actual-reverse.png");
  // INFO("Output image `out` saved as actual-reverse.png");
}

TEST_CASE("List::test2", "[weight=5][part=2]") {
  PNG in;        in.readFromFile("../data/alma.png");
  PNG expected;  expected.readFromFile("../data/expected-reverseN_2.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 61);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_2.png");

//   REQUIRE( out == expected );
}