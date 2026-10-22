
/*
  Name: Utkrista Mardan Basnyat
  Course: COMSC-210 Data Structures
  Lab 26: Data Structures Olympics
  File: main.cpp
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

const int NUM_CODES = 20000;
const int NUM_RUNS = 15;
const int NUM_RACES = 4;
const int NUM_STRUCTURES = 3;

// The two slices of our 3D array
const int CURRENT = 0;
const int TOTAL = 1;

// 3D results array:
// Slice CURRENT = times from one simulation
// Slice TOTAL = sum of times from all simulations
// Rows = Read, Sort, Insert, Delete
// Columns = Vector, List, Set
void runSimulation(long long results[2][NUM_RACES][NUM_STRUCTURES]) {
  // Fresh containers for each simulation
  vector<string> codes;
  list<string> codeList;
  set<string> codeSet;
  string code;

  auto start = high_resolution_clock::now();
  auto end = high_resolution_clock::now();

  // Race 1: Read 20,000 codes into a vector
  ifstream fin("codes.txt");
  if (!fin) {
    cout << "Error opening codes.txt" << endl;
    exit(1);
  }

  start = high_resolution_clock::now();

  while (fin >> code) {
    codes.push_back(code);
  }

  end = high_resolution_clock::now();
  results[CURRENT][0][0] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  // Race 1: Read the same codes into a list
  fin.open("codes.txt");

  if (!fin) {
    cout << "Error opening codes.txt" << endl;
    exit(1);
  }

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeList.push_back(code);
  }

  end = high_resolution_clock::now();
  results[CURRENT][0][1] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  // Race 1: Read the same codes into a set
  fin.open("codes.txt");

  if (!fin) {
    cout << "Error opening codes.txt" << endl;
    exit(1);
  }

  start = high_resolution_clock::now();

  while (fin >> code) {
    codeSet.insert(code);
  }

  end = high_resolution_clock::now();
  results[CURRENT][0][2] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  // Check that all codes were read
  if (codes.size() != NUM_CODES ||
      codeList.size() != NUM_CODES) {
    cout << "Error: Incorrect number of codes." << endl;
    exit(1);
  }

  // Race 2: Sort the vector
  start = high_resolution_clock::now();
  sort(codes.begin(), codes.end());
  end = high_resolution_clock::now();

  results[CURRENT][1][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 2: Sort the list
  start = high_resolution_clock::now();
  codeList.sort();
  end = high_resolution_clock::now();

  results[CURRENT][1][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Set is automatically sorted, so its sort time is zero
  results[CURRENT][1][2] = 0;

  // Race 3: Insert TESTCODE into the middle of vector
  start = high_resolution_clock::now();
  codes.insert(codes.begin() + codes.size() / 2, "TESTCODE");
  end = high_resolution_clock::now();

  results[CURRENT][2][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Find list's middle before timing the insertion
  list<string>::iterator listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();
  codeList.insert(listMiddle, "TESTCODE");
  end = high_resolution_clock::now();

  results[CURRENT][2][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 3: Insert TESTCODE into the set
  start = high_resolution_clock::now();
  codeSet.insert("TESTCODE");
  end = high_resolution_clock::now();

  results[CURRENT][2][2] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 4: Delete the middle element of vector
  vector<string>::iterator vectorMiddle =
    codes.begin() + codes.size() / 2;

  start = high_resolution_clock::now();
  codes.erase(vectorMiddle);
  end = high_resolution_clock::now();

  results[CURRENT][3][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Find list's middle before timing the deletion
  listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();
  codeList.erase(listMiddle);
  end = high_resolution_clock::now();

  results[CURRENT][3][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Find the middle-ish set element before timing
  set<string>::iterator setMiddle = codeSet.begin();
  advance(setMiddle, codeSet.size() / 2);

  start = high_resolution_clock::now();
  codeSet.erase(setMiddle);
  end = high_resolution_clock::now();

  results[CURRENT][3][2] =
    duration_cast<nanoseconds>(end - start).count();
}

int main() {
  // Two slices, four races, three data structures
  long long results[2][NUM_RACES][NUM_STRUCTURES] = {};

  string operations[NUM_RACES] = {
    "Read", "Sort", "Insert", "Delete"
  };

  // Repeat the entire experiment 15 times
  for (int run = 0; run < NUM_RUNS; run++) {
    runSimulation(results);

    // Add this simulation's times to the totals
    for (int race = 0; race < NUM_RACES; race++) {
      for (int structure = 0; structure < NUM_STRUCTURES;
           structure++) {
        results[TOTAL][race][structure] +=
          results[CURRENT][race][structure];
      }
    }
  }

  // Display the average time for each operation
  cout << "Number of simulations: " << NUM_RUNS << endl;

  cout << right << setw(10) << "Operation"
       << setw(12) << "Vector"
       << setw(12) << "List"
       << setw(12) << "Set" << endl;

  for (int race = 0; race < NUM_RACES; race++) {
    cout << right << setw(10) << operations[race];

    for (int structure = 0; structure < NUM_STRUCTURES;
         structure++) {
      // Average = total nanoseconds / number of runs
      cout << setw(12)
           << results[TOTAL][race][structure] / NUM_RUNS;
    }

    cout << endl;
  }

  return 0;
}
