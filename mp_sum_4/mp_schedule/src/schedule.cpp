/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    std::ifstream csv_file(filename);
    // std::string file_ = file_to_string(filename);
    std::vector<std::vector<std::string>> end;
    std::string line;
    while (std::getline(csv_file, line)) {
        std::vector<std::string> row_;
        std::vector<std::string> row_clean;
        split_string(line, ',', row_);
        for(std::string item: row_){
            row_clean.push_back(trim(item));
        }
        end.push_back(row_clean);
    }
    return end;

}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    std::vector<std::vector<std::string>> end_roaster;
    std::map<std::string, std::vector<std::string>> cv_;
    std::map<std::string, std::vector<std::string>> roaster;
    for(int i=0; i<(int)cv.size();i++){
        for(int j=1;j<(int)cv[i].size();j++){
            cv_[cv[i][0]].push_back(trim(cv[i][j]));
        }
    }
    for(int i=0; i<(int)student.size();i++){
        std::string key_=trim(student[i][0]);
        for(int j=1;j<(int)student[i].size();j++){
            std::string value_=trim(student[i][j]);
            if(cv_.find(value_) != cv_.end()){
                for(std::string v: cv_[value_]){
                    if(v==key_){
                        roaster[value_].push_back(key_);
                    }
                }
            }
        }
    }
    for(int i=0; i<(int)cv.size();i++){
        std::vector<std::string> row_;
        if(roaster.find(cv[i][0])!=roaster.end()){
            std::string course=cv[i][0];
            row_.push_back(course);
            for(int p=1; p<(int)cv[i].size();p++){
                std::string person=cv[i][p];
                if(std::find(roaster[course].begin(), roaster[course].end(), person)!=roaster[course].end()){
                    row_.push_back(person);
                }
            }
            end_roaster.push_back(row_);
        }
    }
    return end_roaster;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
// V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
//     if(timeslots.empty()||courses.empty()){
//         V2D invalid(1, std::vector<std::string>(1, "-1"));
//         return invalid;
//     }
//     std::vector<std::vector<std::string>> schedule_={{"-1"}};
//     std::vector<std::string> existed;
//     std::map<std::string, std::set<std::string>> graph_=courgraph(courses);
//     std::vector<std::pair<std::string, int>> degree;
//     for(auto pair: graph_){/*key-course, size-degree*/
//         degree.push_back(std::make_pair(pair.first, (int)pair.second.size()));
//     }
//     std::sort(degree.begin(), degree.end(),compare);
//     std::vector<std::vector<std::string>> degree2;/*its a 2dvector with first to be itself and rest to be conflict course with the highest degree on the first row*/
//     std::vector<std::string> order;
//     for(auto pair:degree){
//         std::vector<std::string> v;
//         v.push_back(pair.first);
//         order.push_back(pair.first);
//         // std::cout<<"-----"<<std::endl;
//         // std::cout<<pair.first<<std::endl;
//         for(std::string c: graph_[pair.first]){
//             // std::cout<<c<<std::endl;
//             v.push_back(c);
//         }
//         // std::cout<<"-----"<<std::endl;
//         degree2.push_back(v);
//     }
//     int t=0;
//     std::vector<std::string> last=degree2[degree2.size()-1];
//     int check=0;
//     while(check!=2&&schedule_==std::vector<std::vector<std::string>>{{"-1"}}){
//         schedule_.clear();
//         for(int i=0; i<(int)degree2.size();i++){
//             std::vector<std::string> time;
//             std::string course=degree2[i][0];
//             if(t>=(int)timeslots.size()&&existed.size()<order.size()){
//                 schedule_={{"-1"}};
//                 std::vector<std::string> temp=degree2[0];
//                 if(temp==last) check=1;
//                 if(check==1) check=2;
//                 degree2.erase(degree2.begin());
//                 degree2.push_back(temp);
//                 break;
//             } else{
//                 if(std::find(existed.begin(),existed.end(),course)==existed.end()){/*course haven't been added*/
//                     time.push_back(timeslots[t]);
//                     time.push_back(course);
//                     existed.push_back(course);
//                     t++;
//                 }
//                 for(std::string c: order){/*according to degree to add non conflict exam*/
//                     if(std::find(degree2[i].begin(), degree2[i].end(), c)==degree2[i].end()){/*we can't find c in conflict*/
//                         if(std::find(existed.begin(),existed.end(),c)==existed.end()&&c!=course){/*haven't added c and c is not course itself*/
//                             time.push_back(c);
//                             existed.push_back(c);
//                         }
//                     }
//                 }
//                 if(!time.empty()){
//                     schedule_.push_back(time);
//                 }
//             }
//         }
//     }
//     for(int s=t; s<(int)timeslots.size();s++){
//         std::vector<std::string> temp;
//         temp.push_back(timeslots[s]);
//         schedule_.push_back(temp);
//     }
//     return schedule_;
// }

std::vector<std::vector<std::string>> schedule(const V2D &courses, const std::vector<std::string> &timeslots) {
    if (timeslots.empty() || courses.empty()) {
        V2D invalid(1, std::vector<std::string>(1, "-1"));
        return invalid;
    }
    std::vector<std::vector<std::string>> schedule_;
    std::map<std::string, std::set<std::string>> graph_ = courgraph(courses);
    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> visited;
    q.push(courses[0][0]);
    std::vector<std::string> visiColor; 
    int position=0;
    while (!q.empty()) {
        visiColor.clear(); 
        std::string course = q.front();
        q.pop();
        if (visited.find(course) == visited.end()) {
            for(std::string c: graph_[course]){
                if (visited.find(c) != visited.end()){
                    visiColor.push_back(visited[c]);
                }else{
                    q.push(c);
                }
            }
            for(std::string t: timeslots){
                if(std::find(visiColor.begin(), visiColor.end(), t)==visiColor.end()){
                    visiColor.push_back(t);
                    visited[course]=t;
                }
            }
            if(visited.find(course) == visited.end()){
                position++;
                if(position==(int)courses.size()){
                    schedule_ = {{"-1"}};
                    return schedule_;
                }
                std::queue<std::string>().swap(q);
                q.push(courses[position][0]);
                visited.clear();
            }
        }
    }
    for(const auto& pair : visited){
        std::unordered_map<std::string, std::string> visited;
        std::vector<std::string> cour;
        int t=-1;
        for(int i=0; i< (int)schedule_.size(); i++){
            if(schedule_[i][0]==pair.second){
                t=i;
                break;
            }
        }
        if(t==-1){
            cour.push_back(pair.second);
            cour.push_back(pair.first);
            schedule_.push_back(cour);
        }else{
            schedule_[t].push_back(pair.first);
        }
    }
    if(schedule_.size()<timeslots.size()){
        for(int i=schedule_.size(); i<(int)timeslots.size(); i++){
            std::vector<std::string> cour;
            cour.push_back(timeslots[i]);
            schedule_.push_back(cour);
        }
    }
    return schedule_;
}

std::map<std::string, std::set<std::string>> courgraph(const V2D& roaster){
    std::map<std::string, std::vector<std::string>> students;
    std::map<std::string, std::set<std::string>> conflict;
    for (auto row : roaster) {
        auto course = row[0];
        for (int i = 1; i < (int)row.size(); ++i) {
            students[row[i]].push_back(course);/*add each person's taken courses-conflict into the map*/
        }
    }
    for (auto s : students) {
        auto courses = s.second;/*loop through each students' taken course*/
        for (int i = 0; i < (int)courses.size(); ++i) {
            for (int j = i + 1; j < (int)courses.size(); ++j) {
                conflict[courses[i]].insert(courses[j]);/*add each course as conflict of another as it is a set-unique-no repetition*/
                conflict[courses[j]].insert(courses[i]);
            }
        }
    }
    return conflict;
}
// bool compare (std::pair<std::string,int> a, std::pair<std::string,int> b ){
//    return a.second > b.second;
// }