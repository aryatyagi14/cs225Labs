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
    /* Your code goes here! */
    ifstream wordsFile(filename);
	    string word;
		bool isOpen = wordsFile.is_open();
	    if (isOpen) {
	    /* Reads a line from `wordsFile` into `word` until the file ends. */
	      while (getline(wordsFile, word)) {
	        string temp(word);
			//after creating the string we start to sort
	        std::sort(temp.begin(), temp.end());
	        dict[temp].push_back(word);
	    }
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
     
	    for(size_t count = 0; count<words.size(); count++)
	    {
	      string s(words[count]);
	      std::sort(s.begin(), s.end());
	      dict[s].push_back(words[count]);
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
    /* Your code goes here! */
	int s = word.size();
    if(s<3) {
		return vector<string>();
	}
	    string t(word);
	    std::sort(t.begin(), t.end());
	    if (!(dict.count(t) != 0)) {
			return vector<string>();
		}
	    return dict.at(t);
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
    /* Your code goes here! */
    std::vector<std::vector<string>> vect;
	    for (std::pair<string, vector<std::string>> each : dict)
	    {
	      vector<string> a = each.second;
	      if (!(!(a.size() <= 1))) {
			  continue;
		  }
	      vect.push_back(a);
	    }
	    return vect;
    return vector<vector<string>>();
}
