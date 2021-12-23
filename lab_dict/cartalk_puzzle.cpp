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
	
	    /* Your code goes here! */
	    
	    ifstream wordsfile(word_list_fname);
		string word;
		bool b = wordsfile.is_open();
	    if (b) {
	        while (getline(wordsfile, word)) {
	            if (!(word.size() != 5)) {
	            	string w1 = word.substr(1, word.size() - 2 + 1);
	            	string w2 = word[0] + word.substr(2, word.size() - 2 + 1);
					bool a = d.homophones(word, w1);
					bool c = d.homophones(word, w2);
	            	if (a && c)
	            		ret.push_back(tuple<string, string, string>(word, w1, w2));
	            }
	        }
	    }
	    wordsfile.close();
	    return ret;
	}