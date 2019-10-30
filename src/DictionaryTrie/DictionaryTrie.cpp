/*  
 * Filename: DictionaryTrie.cpp
 * Author: Abdulkhaliq Omar/Andrew Masters
 * UserId: cs30s2019ac
 * Date:    10/23/2019
 * Sources of Help: None
 * DictionaryTrie.cpp implements all functions that were declared in DictionaryTrie.hpp
 * Helper funcitons are added to assist and use recursion on primary functions
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>
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
  	else if( prefix.length() - 1  > charIndex)
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

  if(freq > (*node)->maxBelow){
    (*node)->maxBelow = freq;
  } 

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
      if(i == word.size() - 1 ){
        
	//word already there
	if((*node)->wordEnd) return false;
	else {
	  //otherwise
          (*node)->freq = freq;
          (*node)->wordEnd = true;
          return true;
	}
      } 
      //if char is not last letter of word
      else {
	
        insertHelper(word, freq, &((*node)->middle), i + 1);    
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
  TrieNode* node  = getPrefixRoot(root, word, 0);
  
  return node == nullptr ? false : node->wordEnd;
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
                they should be ordered alphabetically. For example, if prefix 'a' and numCompletions is 1,
                then if \"ant\" and \"and\" have the same largest frequency, only \"and\" should be returned.

                the prefix itself may be included in results if the prefix itself is a valid word
                in the DictionaryTrie and is among the numCompletions top most frequent completions
*Parameters:
            prefix - the prefix whose completions to search for
            numCompletions - the number of search results
            
* Return Value: true if successfully found, false otherwise
*/
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                     unsigned int numCompletions){
    
    	
      priority_queue< pair<unsigned int, string>, vector<pair<unsigned int, string>>, comparator>  pq;
      vector<string> vec(0);//the string of prefix completions to return


    
    if(!root) return vec; //empty tree	
    if(numCompletions < 1 ) return vec;
        
    //get root of prefix subtrie
    TrieNode* node = getPrefixRoot(root, prefix, 0);
    
    if(!node) return vec; //prefix does not exist    
    
    //if prefix is valid word itself
    if(node && node->wordEnd) { 
	 
       //add to the completions
       pq.emplace(make_pair(node->freq, prefix));
    }
    
    //recursively get all the words in the subtree
    getAllWords( node->middle, prefix, pq, numCompletions);
    //no valid completions
    if(pq.size() < 1) return vec;

    //check if not enough valid words
    if(pq.size() < numCompletions) {  
    
      numCompletions = pq.size();
    }  
    
   vec.resize(numCompletions);
   //sort the vectors in order of increasing frequency and alphabetically if tied
    pair<unsigned int, string> top;
    
    for(int i = (numCompletions-1); i >= 0; i--){
	top = pq.top();
	pq.pop();
	vec[i] = top.second;	
    }
 
       
    
   return vec;
}


void DictionaryTrie::getAllWords(TrieNode* root, string prefix, priority_queue< pair<unsigned int, int, string> & pq, int numCompletions, bool maxFound) { 
   
   if(root != nullptr) {

     //for each node, check if it is a word node
    /* if(root->wordEnd) {  
      
       if(pq.size() == numCompletions) {
	 
	  pair<unsigned int , string> top = pq.top();
	 
	 if(top.first < root->freq){
           pq.pop();
           pq.emplace( make_pair( root->freq, prefix + root->letter ));//add to list if a valid word	 
	 }
	
	 else if( top.first == root->freq) { 
	   	    
	     pq.emplace( make_pair( root->freq, prefix + root->letter ));
	     numCompletions += 1;
	 }
       }*/
       //else {
	 
//	  pq.emplace( make_pair( root->freq, prefix + root->letter ));
	 
      // }
            
    // }
    //
	//Check if queue is full and max at root is less than or equal; return if true 
	if(pq.size() == numCompletions){
	    pair<unsigned int, int, unsigned int> top = pq.top();
	    if(pq.top.second >= root->maxBelow){
		return;
	    }
	}

	//Check if end of word
	if(root->wordEnd){
	    //Check if queue is full
	    if(pq.size() == numCompletions){
		pair<unsigned int, int, unsigned int> top = pq.top();
		//If frequency of top of queue is less than the root frequency, add the word and pop the top
	    	if(top.first < root->freq){
	    	    pq.emplace( make_pair( root->freq, root->maxBelow, prefix + root->letter ));
	 	    pq.pop()
	    	}

	    }
	    //If queue is not full, set maxFound to true if queue is empty and add the word regardless
	    else {
	        if(pq.empty()) maxFound = true;
	        pq.emplace( make_pair( root->freq, root->maxBelow, prefix + root->letter ));

	    }
	   
	}

	//traverse left subtree
	if(root->maxBelow == root->left->maxBelow || maxFound){
           getAllWords(root->left, prefix, pq, numCompletions);
	}

	//traverse right subtree
	if(root->maxBelow == root->right->maxBelow || maxFound){
           getAllWords(root->right, prefix, pq, numCompletions);
	}

	//traverse middle subtree
	if(root->maxBelow == root->left->maxBelow || maxFound){
           getAllWords(root->left, prefix, pq, numCompletions);
	}


   
       pq.emplace( make_pair( root->freq, root->maxBelow, prefix + root->letter ));

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
	
  
     //hold each  valid completion and its frequency
     vector<string> vec;
    if(numCompletions < 1) return vec;
    vector<pair<string, unsigned int>> completions;

    vector<pair<string, unsigned int>> topCompletions;
    
    
    //get the completions
    getWildCard( root, pattern, "", completions, 0); 

 
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
     
      topCompletions.emplace_back(make_pair(completions[i].first, completions[i].second));      
   }
   //return the top completions
   for( int i = 0; i < topCompletions.size(); i++) { 
    
     vec.emplace_back(topCompletions[i].first);    
   }
  
   return vec;



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


void DictionaryTrie::getWildCard(TrieNode* root, string wildCard, string prefix, vector<pair<string, unsigned int>> & vect, unsigned int index) {   

  if(!root) return;//base case
  
  if(!wildCard[index]) return;
  
  //if current letter is wildcard or current letter is less
  if( (wildCard[index] == '_' || wildCard[index] < root->letter)) {   
      
    getWildCard( root->left, wildCard, prefix, vect, index);  
  }
  
  //if current letter is wildcard or current letter is greater
  if( wildCard.at(index) == '_' || wildCard[index] > root->letter) {  
     getWildCard( root-> right, wildCard, prefix,vect, index);
  }
 
  //if current letter is wildcard or current letter is == to current node letter 
  if( (wildCard[index] == '_' || wildCard[index] == root->letter ) ) {  
         
    if( index == wildCard.length() - 1) {  
                
      if(root->wordEnd) { 
      	
           vect.emplace_back( make_pair( prefix + root->letter, root->freq)); 	        
     }       
     }
     else 
	  
       getWildCard( root-> middle, wildCard, prefix + root->letter, vect, index + 1); 
  }
  
}
