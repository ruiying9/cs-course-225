/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream file(filename);
    std::string word;
    while (getline(file, word)) {
        std::string sorted=word; 
        std::sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(word);
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for(string a:words){
        std::string sorted=a; 
        std::sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(a);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    string sorted=word;
    std::sort(sorted.begin(), sorted.end());
    if(dict.find(sorted)!=dict.end()){
        return dict.find(sorted)->second;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> result;
    for(auto pair:dict){
        auto vec=pair.second;
        if(vec.size()>=2){
            result.push_back(vec);
        }
    }
    return result;
}
