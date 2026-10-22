
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

using namespace std;
using namespace std::chrono;

const int NUM_CODES = 20000;
const int NUM_RUNS = 15;
const int NUM_RACES = 4;
const int NUM_STRUCTURES = 3;

// 3D array:
// [0] = results for the current simulation
// [1] = accumulated results from all simulations
// Rows = Reading, Sorting, Inserting, Deleting
// Columns = Vector, List, Set
void runSimulation(long long results[2][NUM_RACES][NUM_STRUCTURES]) {
  vector<string> codes;
  list<string> codeList;
  set<string> codeSet;
  string code;

  auto start = high_resolution_clock::now();
  auto end = high_resolution_clock::now();

  // Race 1: Reading into vector
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
  results[0][0][0] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  // Race 1: Reading into list
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
  results[0][0][1] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  // Race 1: Reading into set
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
  results[0][0][2] =
    duration_cast<nanoseconds>(end - start).count();
  fin.close();

  if (codes.size() != NUM_CODES ||
      codeList.size() != NUM_CODES) {
    cout << "Error: Incorrect number of codes." << endl;
    exit(1);
  }

  // Race 2: Sorting vector
  start = high_resolution_clock::now();
  sort(codes.begin(), codes.end());
  end = high_resolution_clock::now();

  results[0][1][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 2: Sorting list
  start = high_resolution_clock::now();
  codeList.sort();
  end = high_resolution_clock::now();

  results[0][1][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Set is already sorted, so no sorting time
  results[0][1][2] = 0;

  // Race 3: Inserting into vector
  start = high_resolution_clock::now();
  codes.insert(codes.begin() + codes.size() / 2, "TESTCODE");
  end = high_resolution_clock::now();

  results[0][2][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Find the middle of list before timing
  list<string>::iterator listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();
  codeList.insert(listMiddle, "TESTCODE");
  end = high_resolution_clock::now();

  results[0][2][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 3: Inserting into set
  start = high_resolution_clock::now();
  codeSet.insert("TESTCODE");
  end = high_resolution_clock::now();

  results[0][2][2] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 4: Deleting from vector
  vector<string>::iterator vectorMiddle =
    codes.begin() + codes.size() / 2;

  start = high_resolution_clock::now();
  codes.erase(vectorMiddle);
  end = high_resolution_clock::now();

  results[0][3][0] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 4: Deleting from list
  listMiddle = codeList.begin();
  advance(listMiddle, codeList.size() / 2);

  start = high_resolution_clock::now();
  codeList.erase(listMiddle);
  end = high_resolution_clock::now();

  results[0][3][1] =
    duration_cast<nanoseconds>(end - start).count();

  // Race 4: Deleting from set
  set<string>::iterator setMiddle = codeSet.begin();
  advance(setMiddle, codeSet.size() / 2);

  start = high_resolution_clock::now();
  codeSet.erase(setMiddle);
  end = high_resolution_clock::now();

  results[0][3][2] =
    duration_cast<nanoseconds>(end - start).count();
}

int main() {
  // Two slices, four races, three data structures
  long long results[2][NUM_RACES][NUM_STRUCTURES] = {};

  string operations[NUM_RACES] = {
    "Reading", "Sorting", "Inserting", "Deleting"
  };

  // Run the complete experiment 15 times
  for (int run = 0; run < NUM_RUNS; run++) {
    runSimulation(results);

    // Add the current results to the accumulated totals
    for (int race = 0; race < NUM_RACES; race++) {
      for (int structure = 0; structure < NUM_STRUCTURES;
           structure++) {
        results[1][race][structure] +=
          results[0][race][structure];
      }
    }

    cout << "Simulation " << run + 1 << " completed." << endl;
  }

  // Temporary output for Milestone 2
  cout << endl;
  cout << "Number of simulations: " << NUM_RUNS << endl;
  cout << "Average times in nanoseconds:" << endl;

  for (int race = 0; race < NUM_RACES; race++) {
    cout << operations[race] << ": ";

    for (int structure = 0; structure < NUM_STRUCTURES;
         structure++) {
      cout << results[1][race][structure] / NUM_RUNS << " ";
    }

    cout << endl;
  }

  return 0;
}
