/**
 * This file defines some functions useful for parsing input file and
 * benchmarking DictionaryTrie
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <chrono>
#include <iostream>
#include <vector>
#include "DictionaryTrie.hpp"

using namespace std;

/** Timer class to time the program execution */
class Timer {
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

  public:
    /* Function called when starting the timer. */
    void begin_timer();

    /* Function called when ending the timer. Returns duration in nanoseconds
     * PRECONDITION: begin_timer() must be called before this function
     */
    long long end_timer();
};

/** Contains useful functions to parse input file */
class Utils {
  public:
    /* Load the words in the file into the dictionary */
    void static loadDict(DictionaryTrie& dict, istream& words);

    /* Load numWords from words stream into the dictionary */
    void static loadDict(DictionaryTrie& dict, istream& words,
                         unsigned int numWords);

    /* Load all the words in word stream into a vector */
    void static loadDict(vector<string>& dict, istream& words);
};

#endif  // UTIL_HPP
