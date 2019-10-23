/*  
 * Filename: DictionaryTrie.cpp
 * Author: Abdulkhaliq Omar/Andrew Master
 * UserId: cs30s2019ac
 * Date:    10/23/2019
 * Sources of Help: None
 *
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

/*
 * Function Name: getPrefix()
 * Function Prototype:TrieNode* DictionaryTrie::getPrefixRoot(TrieNode* root, string prefix, int charIndex)
 * Description: this function returns the root of the subtrie under prefix
 * Return Value: last node under prefix
 */
TrieNode* DictionaryTrie::getPrefixRoot(TrieNode* root, string prefix, int charIndex)const{
    //base case
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


/*
 * Function Name: insertHelper()
 * Function Prototype:bool DictionaryTrie::insertHelper(string word, unsigned int freq, TrieNode ** node, int i)
 * Description: this function iserts a word in the TST
 * Return Value: true if successfully inserted, false otherwise
 */
bool DictionaryTrie::insertHelper(string word, unsigned int freq, TrieNode ** node, int i){
	
  if(*node == nullptr){
	    (*node) = new TrieNode(word[i]);
	}
	
  //if char is less than current node char
	if(word[i] < (*node)->letter){
	    insertHelper(word, freq, &((*node)->left), i);
	} 
  //if char is greater than the current node char
  else if(word[i] > (*node)->letter){
	    insertHelper(word, freq, &((*node)->right), i);
	} 
  //if equal
  else {
      //if last letter of string
	    if(i == word.size() ){
        //word already there
		    if((*node)->wordEnd) return false;
		     //otherwise
        (*node)->freq = freq;
		    (*node)->wordEnd = true;
		     return true;
	    } 
      //if char is not last letter of word
      else {
	    	insertHelper(word, freq, &((*node)->middle), i+1);
	    }
	 }

	 return false;	
}

/*
 * Function Name: deleteAll()
 * Function Prototype:void DictionaryTrie::deleteAll(TrieNode* node)
 * Description: this function deletes the tree
 * Return Value: NONE
 */
void DictionaryTrie::deleteAll(TrieNode* node){
	
	if(node == nullptr){
	    return;
	}

	deleteAll(node->left);
	deleteAll(node->middle);
	deleteAll(node->right);

	delete node;
    }

    /*
 * Function Name: DictionaryTrie()
 * Function Prototype: DictionaryTrie();
 * Description: constructor forclass
 * Return Value: NONE
 */
DictionaryTrie::DictionaryTrie(){
	root = nullptr;
}
/*
 * Function Name: insert()
 * Function Prototype:bool DictionaryTrie::bool DictionaryTrie::insert(string word, unsigned int freq)
 * Description: this function iserts a word in the TST
 *Parameters:
            word- word to insert
            freq - frequency of word
 * Return Value: true if successfully inserted, false otherwise
 */
bool DictionaryTrie::insert(string word, unsigned int freq){

	if(word.empty()) return false;
	
  return insertHelper(word, freq, &root, 0);
}
/*
 * Function Name: find()
 * Function Prototype: bool DictionaryTrie::find(string word) const
 * Description: searches a word in the TST
 *Parameters:
            word- word to search
            
 * Return Value: true if successfully found, false otherwise
 */
bool DictionaryTrie::find(string word) const{
  //check if word was found
  return getPrefixRoot(root, word, 0) != nullptr;
}
/*
* Function Name: predictCompletions()
* Function Prototype: vector<string> DictionaryTrie::predictCompletions(string prefix,
                                     unsigned int numCompletions)
* Description: Return a vector holding up to numCompletions of the most frequent completions of prefix, 
                and the completions must be valid words in the dictionary. 
                These completions should be listed from most to least frequent.

                If there are fewer than numCompletions legal completions, 
                this method should return a vector with as many completions as possible.

                If no completions exist, then the function should return a vector of size 0.

                if there are more than one word/phrase with the same frequency, 
                they should be ordered alphabetically. For example, if prefix is “a” and numCompletions is 1,
                then if “ant” and “and” have the same largest frequency, only “and” should be returned.

                the prefix itself may be included in results if the prefix itself is a valid word
                in the DictionaryTrie and is among the numCompletions top most frequent completions
*Parameters:
            prefix - the prefix whose completions to search for
            numCompletions - the number of search results
            
* Return Value: true if successfully found, false otherwise
*/
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                     unsigned int numCompletions){
    
    vector<pair<string, unsigned int>> topCompletions;//number of completions
	
    vector<pair<string, unsigned int>> completions;//number of completions
     
    vector<string> vec;//the string of prefix completions to return

    
    if(!root) return vec; //empty tree	
        
    //get root of prefix subtrie
    TrieNode* node = getPrefixRoot(root, prefix, 0);
    
    if(!node) return vec; //prefix does not exist    
    
    //if prefix is valid word itself
    if(node && node->wordEnd) {    
       //add to the completions
       completions.emplace_back(make_pair(prefix, node->freq));
    }
    //recursively get all the words in the subtree
    getAllWords( node->middle, prefix, completions);
    
    //no valid completions
    if(completions.size() < 1) return vec;
    
    //sort the vectors in order of increasing frequency and alphabetically if tied	
    sort(completions.begin(), completions.end(), 
       [](const pair<string,unsigned int> &left, const std::pair<string ,unsigned int> &right) {
       if(left.second != right.second) {
         return left.second > right.second;
      }
      else { 
        return left.first < right.first;
      }
    });
   
    //check if not enough valid words
    if(completions.size() < numCompletions) {  
    
      numCompletions = completions.size();
    }   
    //get the top completions
    for( int i = 0 ; i < numCompletions; i++) {  
     
      topCompletions.emplace_back(make_pair(completions[i].first.substr(0, completions[i].first.length() -1), 
                                  completions[i].second));      
   }
   //return the top completions
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
/*
 * Function Name: predictUnderscores()
 * Function Prototype: vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions)
 * Description: searches for wildcard completions in TST
 *Parameters:
            wild card pattern to search for
            
 * Return Value: true if successfully found, false otherwise
 */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/*
 * Function Name: DictionaryTrie()
 * Function Prototype: DictionaryTrie::~DictionaryTrie()
 * Description: destructor for the class
 *Parameters:
            NONE
            
 * Return Value: true if successfully found, false otherwise
 */
DictionaryTrie::~DictionaryTrie() {
	deleteAll(root);
}
