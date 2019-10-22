/**
 * TODO: File HEADER
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

}

/* TODO */
