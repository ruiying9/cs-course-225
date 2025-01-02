#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "Animation.h"
#include "FloodFilledImage.h"
#include "ImageTraversal.h"

#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    // PNG png;       png.readFromFile("../data/i.png");
    // PNG expected;  expected.readFromFile("../data/i-rainbow-dfs.png");
    // PNG expected2; expected2.readFromFile("../data/i-rainbow-dfs-2.png");

    // FloodFilledImage image(png);
    // Traversals::ImageTraversal dfs(png, Point(40, 40), 0.05, Traversals::dfs_add, Traversals::dfs_pop);
    // RainbowColorPicker rainbow(0.05);
    // image.addFloodFill( dfs, rainbow );

    // Animation animation = image.animate(1000);

    // PNG secondFrame = animation.getFrame(1);
    // for(unsigned int i=0;i<png.width();i++){
    //     for(unsigned int j=0;j<png.height();j++){
    //         if(png.getPixel(i,j)!=secondFrame.getPixel(i,j)){
    //             std::cout<<"here is the issue"<<std::endl;
    //             std::cout<<i<<std::endl;
    //             std::cout<<j<<std::endl;
    //         }
    //     }
    // }
}
