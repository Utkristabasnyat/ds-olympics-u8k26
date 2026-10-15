
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

using namespace std;
using namespace std::chrono;

const int NUM_CODES = 20000;

int main() {
  vector<string> codes;
  list<string> codeList;
  set<string> codeSet;

  // store the timing results for each race
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

  // check that the data was loaded
  if (codes.size() != NUM_CODES ||
      codeList.size() != NUM_CODES) {
    cout << "Error: Incorrect number of codes." << endl;
    return 1;
  }

  // display the race results
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

  cout << left << setw(15) << operations[0]
       << setw(14) << results[0][0]
       << setw(14) << results[0][1]
       << setw(14) << results[0][2] << endl;

  cout << "-------------------------------------------------------"
       << endl;

  cout << "Vector elements: " << codes.size() << endl;
  cout << "List elements: " << codeList.size() << endl;
  cout << "Set elements: " << codeSet.size() << endl;

  return 0;
}
