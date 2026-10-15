
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

int main() {
  vector<string> codes;
  list<string> codeList;
  set<string> codeSet;

  // Store timing results for the four races
  string operations[4] = {
    "Reading", "Sorting", "Inserting", "Deleting"
  };

  long long results[4][3] = {};

  // Race 1: Reading into a vector
  ifstream fin("codes.txt");

  if (!fin) {
    cout << "Error: Could not open codes.txt" << endl;
    return 1;
  }

  string code;
  auto start = high_resolution_clock::now();

  while (fin >> code) {
    codes.push_back(code);
  }

  auto end = high_resolution_clock::now();

  results[0][0] =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();

  // Race 1: Reading into a list
  fin.open("codes.txt");

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeList.push_back(code);
  }

  end = high_resolution_clock::now();

  results[0][1] =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();

  // Race 1: Reading into a set
  fin.open("codes.txt");

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeSet.insert(code);
  }

  end = high_resolution_clock::now();

  results[0][2] =
    duration_cast<nanoseconds>(end - start).count();

  fin.close();

  // Verify the data was loaded
  if (codes.size() != NUM_CODES ||
      codeList.size() != NUM_CODES) {
    cout << "Error: Incorrect number of codes." << endl;
    return 1;
  }

  // Race 2: Sorting the vector
  start = high_resolution_clock::now();

  sort(codes.begin(), codes.end());

  end = high_resolution_clock::now();

  results[1][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 2: Sorting the list
  start = high_resolution_clock::now();

  codeList.sort();

  end = high_resolution_clock::now();

  results[1][1] =
    duration_cast<nanoseconds>(end - start).count();

  // A set already maintains sorted order
  results[1][2] = -1;

  // Race 3: Insert TESTCODE into the middle of the vector
  start = high_resolution_clock::now();

  codes.insert(codes.begin() + codes.size() / 2, "TESTCODE");

  end = high_resolution_clock::now();

  results[2][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Find the middle of the list before starting the timer
  list<string>::iterator listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  // Race 3: Insert TESTCODE into the middle of the list
  start = high_resolution_clock::now();

  codeList.insert(listMiddle, "TESTCODE");

  end = high_resolution_clock::now();

  results[2][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 3: Insert TESTCODE into the set
  start = high_resolution_clock::now();

  codeSet.insert("TESTCODE");

  end = high_resolution_clock::now();

  results[2][2] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 4: Delete the middle element from the vector
  vector<string>::iterator vectorMiddle =
    codes.begin() + codes.size() / 2;

  start = high_resolution_clock::now();

  codes.erase(vectorMiddle);

  end = high_resolution_clock::now();

  results[3][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Find the middle of the list before starting the timer
  listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  // Race 4: Delete the middle element from the list
  start = high_resolution_clock::now();

  codeList.erase(listMiddle);

  end = high_resolution_clock::now();

  results[3][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Find the middle-ish element of the set
  set<string>::iterator setMiddle = codeSet.begin();
  advance(setMiddle, codeSet.size() / 2);

  // Race 4: Delete the middle-ish element from the set
  start = high_resolution_clock::now();

  codeSet.erase(setMiddle);

  end = high_resolution_clock::now();

  results[3][2] =
    duration_cast<nanoseconds>(end - start).count();

  // Display the race results
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

  // Display all four races
  for (int i = 0; i < 4; i++) {
    cout << left << setw(15) << operations[i]
         << setw(14) << results[i][0]
         << setw(14) << results[i][1]
         << setw(14) << results[i][2] << endl;
  }

  cout << "-------------------------------------------------------"
       << endl;

  cout << "Vector elements: " << codes.size() << endl;
  cout << "List elements: " << codeList.size() << endl;
  cout << "Set elements: " << codeSet.size() << endl;

  return 0;
}
