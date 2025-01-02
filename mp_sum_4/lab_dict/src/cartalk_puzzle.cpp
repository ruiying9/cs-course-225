/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                                                         const string &word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    std::string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            if (word.length() < 3) {
                continue;
            }
            std::string word2=word;
            word2.erase(0,1);
            std::string word3=word;
            word3.erase(1,1);
            // std::cout<<word<<std::endl;
            // std::cout<<word2<<std::endl;
            // std::cout<<word3<<std::endl;
            if(d.homophones(word,word2)&&d.homophones(word,word3)){
                ret.push_back(std::make_tuple(word,word2,word3));
            }
        }
    }
    return ret;
}
