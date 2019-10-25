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
	//cout << "dsakdmslka " << (*node)->letter << endl;	
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
		   // cout << "inserting " << (*node)->letter << endl;
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
  TrieNode* node  = getPrefixRoot(root, word, 0);
  return node->wordEnd;
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
   /* 
    	
     vector<pair<unsigned int, string>> completions;//number of completions
    
     priority_queue<pair<unsigned int, string>> pq;
 
    vector<string> vec;//the string of prefix completions to return


    
    if(!root) return vec; //empty tree	
        
    //get root of prefix subtrie
    TrieNode* node = getPrefixRoot(root, prefix, 0);
    
    if(!node) return vec; //prefix does not exist    
    
    //if prefix is valid word itself
    if(node && node->wordEnd) {    
       //add to the completions
       pq.emplace(make_pair(node->freq, prefix));
    }
    //recursively get all the words in the subtree
    getAllWords( node->middle, prefix, pq);
    //no valid completions
    if(pq.size() < 1) return vec;

     //check if not enough valid words
    if(pq.size() < numCompletions) {  
    
      numCompletions = pq.size();
    }  
    
    //sort the vectors in order of increasing frequency and alphabetically if tied
    pair<unsigned int, string> top;
    pair<unsigned int, string> top2;
    
    for(int i = 0; i < pq.size() - 2; i++){
	top = pq.top();
	pq.pop();

       if(!completions.empty()){
	  top2 = completions.at(i-1);
       	  if(top.first == top2.first) {   
       
            if( top.second > top2.second) {
	      completions.at(i-1) = top2;
      	      completions.emplace_back(make_pair(top.second.substr(0, top.second.length() -1), 
                                  top.first)); 
	    }
 	  }
            else {
	      completions.at(i-1) = top;
      	      completions.emplace_back(make_pair(top2.second.substr(0, top2.second.length() -1), 
                                  top2.first)); 
       }  

       }	       
    }   
       
      
   //return the top completions
   for( int i = 0; i < completions.size(); i++) {
     vec.emplace_back(completions[i].second);    
   }
  
   return vec;*/
}


void DictionaryTrie::getAllWords(TrieNode* root, string prefix, priority_queue<pair<unsigned int, string>> & pq) { 
   
   /*if(root != nullptr) {

     //cout<< root->letter<<endl;
        //for each node, check if it is a word node
     if(root->wordEnd) {  
       pq.emplace( make_pair( root->freq, prefix + root->letter ));//add to list if a valid word	   
     }

     //traverse left subtree
     getAllWords(root->left, prefix, pq);
  
     //traverse right subtree
     getAllWords(root->right, prefix, pq);
   
     

     getAllWords(root->middle, (prefix + root->letter), pq);
   }
*/   
 
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

	vector<pair<string, unsigned int>> vect;
	vector<string> completions;


        
        getWildCard( root, pattern, "",vect, 0); 

	cout<< "size of matchs found "<< vect.size()<<endl;
        for( int i = 0; i < vect.size(); i++) {  
	
	  completions.emplace_back( vect[i].first);
	
	}
        return completions;
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
      
     
     //cout<< "wildCard search is now on the left "<< prefix<<endl;
     /* if( wildCard.at(index) == '_') {  
	  
	     getWildCard( root-> left , wildCard, prefix,vect, index + 1);	  
     }

      else */
    	     getWildCard( root->left, wildCard, prefix, vect, index);
  
  }
  //if current letter is wildcard or current letter is greater
  if( wildCard.at(index) == '_' || wildCard[index] > root->letter) {  
         //cout<<"current node is :  " << root->letter<<endl;
	  
	  //cout<< "wildCard search is now on the right "<< prefix<<endl;

	 
	 /* if( wildCard.at(index) == '_') {  
	  
	     getWildCard( root-> right, wildCard, prefix,vect, index + 1);	  
	  }
          else*/
             getWildCard( root-> right, wildCard, prefix,vect, index);
  
  }
  //if current letter is wildcard or current letter is == to current node letter 
  if( (wildCard[index] == '_' || wildCard[index] == root->letter ) ) {  
         
     //  cout<<"current node is :  " << root->letter<<endl;
 
      // cout<< "wildCard search is now on the middle :"<< prefix<<endl;
      // cout << "Index is :  " <<index <<endl<< "wildcard.length : " << wildCard.length()<<endl;
       
       if( index == wildCard.length() - 1) {  
         //cout<< root->letter <<" hello " << root->wordEnd <<endl;
          //if(root->wordEnd) { 
          //if(root->wordEnd) { 
      	
            //cout<< "current match " << prefix + root->letter <<endl;
      	    vect.emplace_back( make_pair( prefix + root->letter, root->freq)); 	 
         //}       
     }
     else 
	  getWildCard( root-> middle, wildCard, prefix + root->letter, vect, index + 1); 
  }
  
}
