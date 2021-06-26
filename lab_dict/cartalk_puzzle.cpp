/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

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
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            string word1 = word.substr(1);
            string word2 = word[0] + word.substr(2);
            if (d.homophones(word, word1) && d.homophones(word, word2)) {
                tuple<string, string, string> words = {word, word1, word2};
                ret.push_back(words);
            }
        }
    }     
    return ret;
}
