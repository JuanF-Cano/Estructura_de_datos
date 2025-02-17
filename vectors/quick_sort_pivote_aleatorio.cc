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
}

void QuickSort(vector<int>* v, int left, int right, mt19937& gen) {
  if (left < right)  {
    uniform_int_distribution<int> dist(left, right);
    int pivotIndex = dist(gen);
    int pivot = (*v)[pivotIndex];
  
    int i = left, j = right;
    
    while (i <= j) {
      while ((*v)[i] < pivot) i++;
      while ((*v)[j] > pivot) j--;

      if (i <= j) {
        swap((*v)[i], (*v)[j]);
        i++;
        j--;
      }
    }
  
    if (left < j) QuickSort(v, left, j, gen);
    if (i < right) QuickSort(v, i, right, gen);
  }
}

int main() {
    vector<int> original;
    vector<int> v;
    random_device rd;
    mt19937 gen(rd());  

    for (int i = 2; i <= 8; i++) {
        original.clear();
        original.shrink_to_fit();
        int size = 1;
        for (int k = 0; k < i; k++) size *= 10;
        FillVector(size, &original);
        cout << "10^" << i << endl;
    
        for (int j = 1; j <= 10; j++) {
            v = original;
            auto inicio = high_resolution_clock::now();
            QuickSort(&v, 0, v.size() - 1, gen);
            auto fin = high_resolution_clock::now();
            auto duracion = duration_cast<nanoseconds>(fin - inicio);
            cout << " -> (" << j << ") " << "Tiempo de ordenamiento: " << duracion.count() << " ns" << endl;
        }
        cout << endl;
    }

    return 0;
}
