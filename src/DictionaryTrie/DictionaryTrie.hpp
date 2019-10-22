/**
 * TODO: File Header
 *
 * Author: Andrew Masters, Abdulkhaliq Omar
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "TrieNode.hpp"

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    // pointer to root of DictionaryTrie
    TrieNode * root;

    // Helper function for predictCompletions; finds prefix nodes
    TrieNode* getPrefixRoot(TrieNode* root, string prefix, int charIndex)const;

    // Second helper function for predictCompletions; uses recursion to find all words starting from prefix nodes
    void getAllWords(TrieNode* root, string prefix, vector<pair<string, unsigned int>>& vect);

    // Helper function for insert; uses recursion to insert TrieNodes
    bool insertHelper(string word, unsigned int freq, TrieNode ** node, int i);

    void deleteAll(TrieNode * node);

  public:
    /* Constructor that intializes Dictionary Trie; sets root to null */
    DictionaryTrie();

    /** Insert function returns true if word was inserted, false if it already exists, given a word and its frequency
     *	Calls insertHelper to recursively insert TrieNodes
     */
    bool insert(string word, unsigned int freq);

    /** Find function return true if word is found, false if it can't be found, given a word
     *	Calls getPrefixRoot to recursively find word
     */
    bool find(string word) const;

    /* PredictCompletions returns a vector of all strings given a prefix and number of words below prefix
     * Calls getPrefixRoot to find the prefix nodes
     * Calls getAllWords to recursively find all words below prefix*/
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Deconstructor, deletes all nodes and the root */
    ~DictionaryTrie();
};

#endif