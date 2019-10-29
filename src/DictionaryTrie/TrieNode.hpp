#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <string>

/**
 * A TrieNode is created that has a left, right and middle pointer nodes
 * Holds the letter, freq and end of word
 */
class TrieNode {

   public:
      TrieNode* left;
      TrieNode* right;
      TrieNode* middle;
		
      char letter;
      unsigned int freq;
      bool wordEnd;
      int maxBelow;

      TrieNode(const char l) : letter(l) {
        freq = 0;
	wordEnd = false;
	maxBelow = 0;

	left = right = middle = nullptr;
      }


};

#endif // TRIENODE_HPP
