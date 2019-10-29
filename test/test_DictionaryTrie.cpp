/**
 * Test Cases for DictionaryTrie
 * Every function that is implemented in DictionaryTrie.cpp is tested
 *
 * Author: Andrew Masters, Abdulkhaliq Omar
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

TEST(DictTrieTests, TEST_FIND_ONE_WORD){
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    
    ASSERT_EQ(dict.find("ball"), false);


}



TEST(DictTrieTests, TEST_FIND) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);

  ASSERT_EQ( dict.find("applet"), true);
   ASSERT_EQ( dict.find("applett"), false);
   ASSERT_EQ( dict.find("ape"), true);

}

TEST(DictTrieTests, TEST_INSERT_EMPTY_STRING) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);

  ASSERT_EQ( dict.insert("", 10), false);
  
}
TEST(DictTrieTests, TEST_INSERT_SAME_STRING) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);

  ASSERT_EQ( dict.insert("", 10), false);
  
}
TEST(DictTrieTests, TEST_COMPLETIONS) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);

    vector<string> vec = dict.predictCompletions("ap", 3);

    string ape = "ape";
    string apple = "apple";
    string applet = "applet";
   EXPECT_EQ(vec.at(0), applet);
   EXPECT_EQ(vec.at(1), ape);
  EXPECT_EQ(vec.at(2), apple);

}

TEST(DictTrieTests, TEST_INSERT_TWICE) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);

  ASSERT_EQ( dict.insert("applet", 8), false);
}

TEST(DictTrieTests, TEST_COMPLETIONS_NONE) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    
    vector<string> vec = dict.predictCompletions("XY", 3);

    ASSERT_EQ(vec.size(), 0);
 
}
TEST(DictTrieTests, TEST_COMPLETIONS_ORDERED) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 6);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    
    vector<string> vec = dict.predictCompletions("ap", 3);
     string ape = "ape";
    string apple = "apple";
    string applet = "applet";
   EXPECT_EQ(vec.at(0), ape);
   EXPECT_EQ(vec.at(1), apple);
  EXPECT_EQ(vec.at(2), applet);
 
}
TEST(DictTrieTests, TEST_COMPLETIONS_PREFIX_VALID) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    dict.insert( "app", 3);

    vector<string> vec = dict.predictCompletions("app", 3);

    ASSERT_EQ(vec.size(), 3);
 
}
TEST(DictTrieTests, TEST_COMPLETIONS_VALID_PREFIX_NOT_TOP) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    dict.insert( "app", 3);

   
    vector<string> vec = dict.predictCompletions("app", 2);

    string apple = "apple";
    string applet = "applet";
    
    EXPECT_EQ(vec.at(0), applet);
    EXPECT_EQ(vec.at(1), apple);


 
}



TEST(DictTrieTests, TEST_COMPLETIONS_WILDCARD) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tap", 5);
    dict.insert( "tape", 7);
    dict.insert( "app", 3);

    vector<string> vec = dict.predictUnderscores("_p_", 2);
    
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec.at(0), "ape");
    ASSERT_EQ(vec.at(1), "app");
 
}

TEST(DictTrieTests, TEST_COMPLETIONS_WILDCARD_ORDERED) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tapp", 5);
    dict.insert( "tape", 7);
    dict.insert( "app", 3);

    vector<string> vec = dict.predictUnderscores("t___", 3);
    
    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.at(0), "tall");
    ASSERT_EQ(vec.at(1), "tape");
    ASSERT_EQ(vec.at(2), "tapp");
}

TEST(DictTrieTests, TEST_COMPLETIONS_WILDCARD_ORDERED_2) {
    DictionaryTrie dict;
    dict.insert("cape", 1);
    dict.insert("apple",  6);
    dict.insert("ape", 6);
    dict.insert( "applet", 8);
    dict.insert("tall",  8);
    dict.insert("tapp", 5);
    dict.insert( "tape", 7);
    dict.insert( "app", 3);

    vector<string> vec = dict.predictUnderscores("____", 3);
    
    ASSERT_EQ(vec.size(), 3);
    ASSERT_EQ(vec.at(0), "tall");
    ASSERT_EQ(vec.at(1), "tape");
    ASSERT_EQ(vec.at(2), "tapp");

}

/* TODO */
