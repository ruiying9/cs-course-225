#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"
TEST_CASE("My Test Case", "") {
    const V2D roster = {{"CS577", "1", "2"},\
     {"CS591", "1", "3"}, \
     {"CS386", "3", "2"}, 
     };
    std::vector<std::string> timeslots = {"9AM", "11AM", "12AM","1pm"};
    V2D out = schedule(roster, timeslots);
    std::cout<<"*********"<<std::endl;
    for(std::vector<std::string> r: out){
        std::cout<<"--------"<<std::endl;
        for(std::string item:r){
            std::cout<<item<<std::endl;
        }
        std::cout<<"--------"<<std::endl;
    }
    std::cout<<"*********"<<std::endl;
    verifySchedule(roster, out, 4);
}
