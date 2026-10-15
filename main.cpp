
/*
  Name: Utkrista Mardan Basnyat
  Course: COMSC-210 Data Structures
  Lab 25: Data Structures Races
  File: main.cpp
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace std::chrono;

const int NUM_CODES = 20000;

// Store the name and times for one race
struct RaceResult {
  string operation;
  long long vectorTime;
  long long listTime;
  long long setTime;
};

int main() {
  vector<string> codes;
  list<string> codeList;
  set<string> codeSet;

  // New races can be added to this collection
  vector<RaceResult> results;

  ifstream fin("codes.txt");

  if (!fin) {
    cout << "Error: Could not open codes.txt" << endl;
    return 1;
  }

  string code;

  // Race 1: Reading
  auto start = high_resolution_clock::now();

  while (fin >> code) {
    codes.push_back(code);
  }

  auto end = high_resolution_clock::now();
  long long vectorTime =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();
  fin.open("codes.txt");

  if (!fin) {
    cout << "Error: Could not reopen codes.txt" << endl;
    return 1;
  }

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeList.push_back(code);
  }

  end = high_resolution_clock::now();
  long long listTime =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();
  fin.open("codes.txt");

  if (!fin) {
    cout << "Error: Could not reopen codes.txt" << endl;
    return 1;
  }

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeSet.insert(code);
  }

  end = high_resolution_clock::now();
  long long setTime =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();

  results.push_back({"Reading", vectorTime, listTime, setTime});

  // Check that all codes were read
  if (codes.size() != NUM_CODES ||
      codeList.size() != NUM_CODES) {
    cout << "Error: Incorrect number of codes." << endl;
    return 1;
  }

  // Race 2: Sorting
  start = high_resolution_clock::now();

  sort(codes.begin(), codes.end());

  end = high_resolution_clock::now();
  vectorTime = duration_cast<nanoseconds>(end - start).count();

  start = high_resolution_clock::now();

  codeList.sort();

  end = high_resolution_clock::now();
  listTime = duration_cast<nanoseconds>(end - start).count();

  // A set is already sorted
  setTime = -1;

  results.push_back({"Sorting", vectorTime, listTime, setTime});

  // Race 3: Inserting
  start = high_resolution_clock::now();

  codes.insert(codes.begin() + codes.size() / 2, "TESTCODE");

  end = high_resolution_clock::now();
  vectorTime = duration_cast<nanoseconds>(end - start).count();

  list<string>::iterator listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();

  codeList.insert(listMiddle, "TESTCODE");

  end = high_resolution_clock::now();
  listTime = duration_cast<nanoseconds>(end - start).count();

  start = high_resolution_clock::now();

  codeSet.insert("TESTCODE");

  end = high_resolution_clock::now();
  setTime = duration_cast<nanoseconds>(end - start).count();

  results.push_back({"Inserting", vectorTime, listTime, setTime});

  // Race 4: Deleting
  vector<string>::iterator vectorMiddle =
    codes.begin() + codes.size() / 2;

  start = high_resolution_clock::now();

  codes.erase(vectorMiddle);

  end = high_resolution_clock::now();
  vectorTime = duration_cast<nanoseconds>(end - start).count();

  listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();

  codeList.erase(listMiddle);

  end = high_resolution_clock::now();
  listTime = duration_cast<nanoseconds>(end - start).count();

  set<string>::iterator setMiddle = codeSet.begin();
  advance(setMiddle, codeSet.size() / 2);

  start = high_resolution_clock::now();

  codeSet.erase(setMiddle);

  end = high_resolution_clock::now();
  setTime = duration_cast<nanoseconds>(end - start).count();

  results.push_back({"Deleting", vectorTime, listTime, setTime});

  // Display results in a table
  cout << endl << "DATA STRUCTURES RACES" << endl;
  cout << "All times in nanoseconds" << endl;
  cout << "-------------------------------------------------------"
       << endl;

  cout << left << setw(15) << "Operation"
       << setw(14) << "Vector"
       << setw(14) << "List"
       << setw(14) << "Set" << endl;

  cout << "-------------------------------------------------------"
       << endl;

  for (size_t i = 0; i < results.size(); i++) {
    cout << left << setw(15) << results[i].operation
         << setw(14) << results[i].vectorTime
         << setw(14) << results[i].listTime
         << setw(14) << results[i].setTime << endl;
  }

  cout << "-------------------------------------------------------"
       << endl;

  cout << "Vector elements: " << codes.size() << endl;
  cout << "List elements: " << codeList.size() << endl;
  cout << "Set elements: " << codeSet.size() << endl;

  return 0;
}
