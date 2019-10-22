/**
 * TODO: File Header
 *
 * Author: Andrew Masters, Abdulkhaliq Omar
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>


    TrieNode* DictionaryTrie::getPrefixRoot(TrieNode* root, string prefix, int charIndex)const{

  	if( !root){
  		return nullptr;
  	}
        //if less than current node go left
  	if( prefix.at(charIndex) < root->letter) 
  		return getPrefixRoot( root->left, prefix, charIndex);
  		//if greater than current node gor right
  	else if( prefix.at(charIndex) > root->letter)
  		return getPrefixRoot( root->right, prefix, charIndex);
  	//if equal but we have more letter left in word traverse middle child 
  	//for next letter
  	else if( prefix.length() - 1 > charIndex)
  		return getPrefixRoot( root->middle, prefix, charIndex + 1);
  	//if equal and end of prefix
  	else 
  		return root;

  	}

    bool DictionaryTrie::insertHelper(string word, unsigned int freq, TrieNode ** node, int i){
	if(*node == nullptr){
	    (*node) = new TrieNode(word[i]);
	}
	
	if(word[i] < (*node)->letter){
	    insertHelper(word, freq, &((*node)->left), i);
	} else if(word[i] > (*node)->letter){
	    insertHelper(word, freq, &((*node)->right), i);
	} else {
	    if(i == word.size()){
		(*node)->freq = freq;
		(*node)->wordEnd = true;
		return true;
	    } else {
	    	insertHelper(word, freq, &((*node)->middle), i+1);
	    }
	}
	return true;	
    }

    void DictionaryTrie::deleteAll(TrieNode* node){
	
	if(node == nullptr){
	    return;
	}

	deleteAll(node->left);
	deleteAll(node->middle);
	deleteAll(node->right);

	delete node;
    }

    /* TODO: */
    DictionaryTrie::DictionaryTrie(){
	root = nullptr;
    }

    /* TODO: */
    bool DictionaryTrie::insert(string word, unsigned int freq){
	return insertHelper(word, freq, &root, 0);
    }

    /* TODO: */
    bool DictionaryTrie::find(string word) const{

      return getPrefixRoot(root, word, 0) != nullptr;
    }

    /* TODO: */
    vector<string> DictionaryTrie::predictCompletions(string prefix,
                                     unsigned int numCompletions){
      vector<pair<string, unsigned int>> topCompletions;//number of completions
	
     vector<pair<string, unsigned int>> completions;//number of completions
     
     vector<string> vec;

     if(!root) return vec;  	
    
     //get root of prefix subtrie
     TrieNode* node = getPrefixRoot(root, prefix, 0);                       
   
     getAllWords( node->middle, prefix, completions);
    
     //sort the vectors in order of increasing frequency	
    sort(completions.begin(), completions.end(), 
       [](const pair<string,unsigned int> &left, const std::pair<string ,unsigned int> &right) {
      return left.second > right.second;
    });
 
        
    //get the top completions
    for( int i = 0 ; i < numCompletions; i++) {  
     
         topCompletions.emplace_back(make_pair(completions[i].first.substr(0, completions[i].first.length() -1), completions[i].second));      
   }
     //if there is tie in frequency, sort by alphabet order
    for( int i = 0; i < topCompletions.size() - 1 ; i++) {  
   
      if(topCompletions[i].second == topCompletions[i + 1].second) { 
    
        sort(topCompletions.begin() + i, (topCompletions.begin() + (i + 1)), 
          [](const pair<string,unsigned int> &left, const std::pair<string ,unsigned int> &right) {
          return left.first < right.first;
      });
    }
    
    } 

    for( int i = 0; i < topCompletions.size(); i++) { 
    
      vec.emplace_back(topCompletions[i].first);
    
    }
    return vec;
 }

 void DictionaryTrie::getAllWords(TrieNode* root, string prefix, vector<pair<string, unsigned int>>& vect) { 
   
   if(root != nullptr) {

     //cout<< root->letter<<endl;
        //for each node, check if it is a word node
     if(root->wordEnd) {  
       vect.emplace_back( make_pair( prefix + root->letter, root->freq));//add to list if a valid word	   
     }

     //traverse left subtree
     getAllWords(root->left, prefix, vect);
  
     //traverse right subtree
     getAllWords(root->right, prefix, vect);
   
     

     getAllWords(root->middle, (prefix + root->letter), vect);
   }
   
 
}
/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {
	deleteAll(root);
}
