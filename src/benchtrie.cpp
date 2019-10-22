/**
 * Benchmark the autocomplete function in DictionaryTrie
 */
#include <fstream>
#include <sstream>
#include "DictionaryTrie.hpp"
#include "util.hpp"
using namespace std;

/* Test the runtime of autocompelte using different prefix and number of
 * completions
 */
void testRuntime(string filename) {
    const unsigned int NUM_COMP = 10;

    ifstream in;
    in.open(filename, ios::binary);

    // Testing student's trie
    cout << "\nLoading dictionary..." << endl;

    DictionaryTrie* trie = new DictionaryTrie();
    Utils::loadDict(*trie, in);

    Timer timer;
    vector<string> results;
    long long time = 0;

    // Test 1: iterate through alphabet prefix
    cout << "\nTest 1: prefix = \"iterating through alphabet\", "
         << "numCompletions = " << NUM_COMP << endl;
    timer.begin_timer();
    unsigned int count = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        results = trie->predictCompletions(string(1, c), NUM_COMP);
        count += results.size();
    }
    time = timer.end_timer();
    cout << "\tTime taken: " << time << " nanoseconds." << endl;
    cout << "\tResults found: " << count << endl;

    // Test 2: "a" as prefix
    cout << "\nTest 2: prefix = \"a\", numCompletions = " << NUM_COMP << endl;
    timer.begin_timer();
    results = trie->predictCompletions("a", NUM_COMP);
    time = timer.end_timer();
    cout << "\tTime taken: " << time << " nanoseconds." << endl;
    cout << "\tResults found: " << results.size() << endl;

    // Test 3: "the" as prefix
    cout << "\nTest 3: prefix= \"the\", numCompletions = " << NUM_COMP << endl;
    timer.begin_timer();
    results = trie->predictCompletions("the", NUM_COMP);
    time = timer.end_timer();
    cout << "\tTime taken: " << time << " nanoseconds." << endl;
    cout << "\tResults found: " << results.size() << endl;

    // Test 4: "app" as prefix
    cout << "\nTest 4: prefix= \"app\", numCompletions = " << NUM_COMP << endl;
    timer.begin_timer();
    results = trie->predictCompletions("app", NUM_COMP);
    time = timer.end_timer();
    cout << "\tTime taken: " << time << " nanoseconds." << endl;
    cout << "\tResults found: " << results.size() << endl;

    // Test 5: "man" as prefix
    cout << "\nTest 5: prefix= \"man\", numCompletions = " << NUM_COMP << endl;
    timer.begin_timer();
    results = trie->predictCompletions("man", NUM_COMP);
    time = timer.end_timer();
    cout << "\tTime taken: " << time << " nanoseconds." << endl;
    cout << "\tResults found: " << results.size() << endl;

    // Addtional tests
    cout << "\nWould you like to run additional tests? (y/n) ";
    string response;
    getline(cin, response);

    if (response.compare("y") == 0) {
        string prefix;
        string ws;

        cout << "\nEnter prefix: ";

        while (getline(cin, prefix)) {
            cout << "Enter numCompletions: ";
            getline(cin, ws);
            int numCompletions = stoi(ws);

            cout << "\nUser Test: prefix = \"" << prefix
                 << "\", numCompletions = " << numCompletions << endl;
            timer.begin_timer();
            results = trie->predictCompletions(prefix, numCompletions);
            time = timer.end_timer();
            cout << "\tTime taken: " << time << " nanoseconds." << endl;
            cout << "\tResults found: " << results.size() << "\n\n";
            cout << "Enter prefix: ";
        }
    }
    delete trie;
}

/* Check if a given data file is valid */
bool fileValid(const char* fileName) {
    ifstream in;
    in.open(fileName, ios::binary);

    // Check if input file was actually opened
    if (!in.is_open()) {
        cout << "Invalid input file. No file was opened. Please try again.\n";
        return false;
    }

    // Check for empty file
    in.seekg(0, ios_base::end);
    unsigned int len = in.tellg();
    if (len == 0) {
        cout << "The file is empty. \n";
        return false;
    }
    in.close();
    return true;
}

/* The main function that drives the program */
int main(int argc, char* argv[]) {
    const int NUM_ARG = 2;

    if (argc != NUM_ARG) {
        cout << "Invalid number of arguments.\n"
             << "Usage: ./benchtrie <dictionary filename>" << endl;
        return -1;
    }

    if (!fileValid(argv[1])) return -1;
    testRuntime(argv[1]);
}