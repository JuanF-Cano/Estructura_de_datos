#include <iostream>
#include <vector>
#include <random>
#include <chrono>

/*  VECTORES
1. Sus elementos están almacenados continuamente en la memoria. Igual que los arreglos.
2. Son dinámicos. Se adaptan al almacenamiento de cualquier número de elementos. Difiere de los arreglos.
*/

using namespace std;

vector<int> generateRandomArray(int size) {
  random_device rd;
  uniform_int_distribution<> distrib(0, 100);
  mt19937 gen(rd());

  vector<int> randomArray(size);

  for (int i = 0; i < size; ++i) {
    randomArray[i] = distrib(gen);
  }

  return randomArray;
}

int main() { // Comparación arreglos y vectores

  cout << "vector examples" << endl;
  vector<int> b;
  b = generateRandomArray(100);
  for (int j = 0; j < b.size(); j++) {
    cout << b.at(j) << " ";
  }
  cout << endl << b.size() << endl;
  for (int i = 0; i < b.size()/2; i++) {
    b.pop_back();
  }
  cout << endl;
  for (int j = 0; j < b.size(); j++) {
    cout << b.at(j) << " ";
  }
  cout << endl << b.size() << endl;
  
  return 0;
}