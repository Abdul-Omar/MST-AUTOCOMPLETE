/*  
 * Filename: TrieNode.hpp
 * Author: Abdulkhaliq Omar/Andrew Masters
 * UserId: cs30s2019ac
 * Date:    10/23/2019
 * Sources of Help: None
 * A TrieNode is created that has a left, right and middle pointer nodes
 * Holds the letter, freq and end of word
 */

#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <string>

class TrieNode {

   public:
      TrieNode* left;
      TrieNode* right;
      TrieNode* middle;

      char letter;
      unsigned int freq;
      bool wordEnd;
      int maxBelow;

      //Constructor for class
      TrieNode(const char l) : letter(l) {
        freq = 0;
	wordEnd = false;
	maxBelow = 0;

	left = right = middle = nullptr;
      }

};

#endif // TRIENODE_HPP
