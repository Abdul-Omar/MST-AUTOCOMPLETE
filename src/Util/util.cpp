/**
 * This file defines some functions useful for parsing input file and
 * benchmarking DictionaryTrie
 */
#include "util.hpp"
#include <iostream>
#include <sstream>

/* Starts the timer. Saves the current time. */
void Timer::begin_timer() { start = std::chrono::high_resolution_clock::now(); }

/* Ends the timer. Compares end time with the start time and returns number of
 * nanoseconds
 */
long long Timer::end_timer() {
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    end = std::chrono::high_resolution_clock::now();

    return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(
               end - start)
        .count();
}

/* Load all the words in word stream into the dictionary trie */
void Utils::loadDict(DictionaryTrie& dict, istream& words) {
    unsigned int freq;
    string data = "";
    string tempWord;
    string word;
    vector<string> wordString;
    unsigned int i;
    while (getline(words, data)) {
        tempWord = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> freq;
        while (1) {
            iss >> tempWord;
            if (tempWord == ".") break;
            if (tempWord.length() > 0) wordString.push_back(tempWord);
        }
        for (i = 0; i < wordString.size(); i++) {
            if (i > 0) word = word + " ";
            word = word + wordString[i];
        }
        dict.insert(word, freq);
        wordString.clear();
        if (words.eof()) break;
    }
}

/* Load numWords from words stream into the dictionary trie */
void Utils::loadDict(DictionaryTrie& dict, istream& words,
                     unsigned int numWords) {
    unsigned int freq;
    string data = "";
    string tempWord;
    string word;
    vector<string> wordString;
    unsigned int i;
    unsigned int j = 0;
    for (; j < numWords; j++) {
        getline(words, data);
        tempWord = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> freq;
        while (1) {
            iss >> tempWord;
            if (tempWord == ".") break;
            if (tempWord.length() > 0) wordString.push_back(tempWord);
        }
        for (i = 0; i < wordString.size(); i++) {
            if (i > 0) word = word + " ";
            word = word + wordString[i];
        }
        dict.insert(word, freq);
        wordString.clear();
        if (words.eof()) break;
    }
}

/* Load all the words in word stream into a vector */
void Utils::loadDict(vector<string>& dict, istream& words) {
    unsigned int junk;
    string data = "";
    string tempWord;
    string word;
    vector<string> wordString;
    unsigned int i;

    while (getline(words, data)) {
        tempWord = "";
        word = "";
        data = data + " .";
        istringstream iss(data);
        iss >> junk;
        while (1) {
            iss >> tempWord;
            if (tempWord == ".") break;
            if (tempWord.length() > 0) wordString.push_back(tempWord);
        }
        for (i = 0; i < wordString.size(); i++) {
            if (i > 0) word = word + " ";
            word = word + wordString[i];
        }
        dict.push_back(word);
        wordString.clear();
        if (words.eof()) break;
    }
}
