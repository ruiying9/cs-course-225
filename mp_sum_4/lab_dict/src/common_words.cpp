/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) {return std::ispunct(c);});
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}
/*for each file,put its common words in a map and then put into vector file_word_maps*/
void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        map<string, unsigned int> memoWords;
        for (auto word : words) {
            memoWords[word]++;
        }
        file_word_maps[i] = memoWords;
    }
}
/*for the vector file_word_maps, find each word's number of file occurence*/
void CommonWords::init_common()
{
    for(auto map: file_word_maps){
        for(auto pair : map){
            if(common.find(pair.first)==common.end()){
                common[pair.first]=1;
            } else{
                common[pair.first]++;
            }
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
 /*get a vector of words' occurence in every files for larger or equal to n times*/
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    int size_=(int)file_word_maps.size();
    for(auto pair:common){
        if((int)pair.second==size_){/*appear in each file*/
            int i=0;
            for(auto map:file_word_maps){/*loop through each file*/
                if(map[pair.first]<n){
                    i=1;
                    break;
                }
            }
            if(i==0){
                out.push_back(pair.first);
            }
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
