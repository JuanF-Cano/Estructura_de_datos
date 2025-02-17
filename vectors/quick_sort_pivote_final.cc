#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void FillVector(int n, vector<int>* v) {
  v->reserve(n);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(0, 1000);
  
  for (int i = 0; i < n; i++) {
    v->push_back(dist(gen));
  }

  return;
}

void QuickSort(vector<int>* v, int left, int right) {
  if (left < right) {
    int pivot = (*v)[right];
    int i = left;

    for (int j = left; j < right; j++) {
      if ((*v)[j] < pivot) {
        swap((*v)[i], (*v)[j]);
        i++;
      }
    }
    swap((*v)[i], (*v)[right]);

    QuickSort(v, left, i - 1);
    QuickSort(v, i + 1, right);
  } 
  
  return;
}

void printVector(const vector<int>* v) {
  for (int i = 0; i < v->size(); i++) {
      cout << v->at(i) << " ";
  }
  cout << endl;
}

int main() {
  vector<int> original;
  vector<int> v;

  for (int i = 2; i <= 7; i++) {
    original.clear();
    int size = 1;
    for (int k = 0; k < i; k++) size *= 10;
    FillVector(size, &original);
    cout << "10^" << i << endl;
    
    for (int j = 1; j <= 10; j++) {
      v = original;
      auto inicio = high_resolution_clock::now();
      QuickSort(&v, 0, v.size() - 1);
      auto fin = high_resolution_clock::now();
      auto duracion = duration_cast<nanoseconds>(fin - inicio);
      cout << " -> (" << j << ") " << "Tiempo de ordenamiento: " << duracion.count() << " ns" << endl;
    }

    cout << endl;
  }


  return 0;
}
