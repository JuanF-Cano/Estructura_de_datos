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

void QuickSortCentralPivot(vector<int>* v, int left, int right) {
  if (left < right) {
    int pivot = (*v)[left + (right - left) / 2];
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

    if (left < j) QuickSortCentralPivot(v, left, j);
    if (i < right) QuickSortCentralPivot(v, i, right);
  }
}

void QuickSortFinalPivot(vector<int>* v, int left, int right) {
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

    QuickSortFinalPivot(v, left, i - 1);
    QuickSortFinalPivot(v, i + 1, right);
  } 
  
  return;
}

void QuickSortRandomPivot(vector<int>* v, int left, int right, mt19937& gen) {
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
  
    if (left < j) QuickSortRandomPivot(v, left, j, gen);
    if (i < right) QuickSortRandomPivot(v, i, right, gen);
  }
}

int main() {
  vector<int> original;
  vector<int> v;  
  random_device rd;
  mt19937 gen(rd());
  
  for (int i = 2; i <= 8; i++) {
    original.clear();
    int size = 1;
    for (int k = 0; k < i; k++) size *= 10;
    FillVector(size, &original);
    cout << "10^" << i << "\t| Pivote medio  | Pivote final  | Pivote random" << endl;
    
    for (int j = 1; j <= 10; j++) {
      v = original;
      auto start = high_resolution_clock::now();
      QuickSortCentralPivot(&v, 0, v.size() - 1);
      auto end = high_resolution_clock::now();
      auto duration = duration_cast<nanoseconds>(end - start);
      cout << " > (" << j << ")\t|" << duration.count();
      if (duration.count() < 1000000) {
        cout << "\t";
      }

      if (i < 8) {
        v = original;
        start = high_resolution_clock::now();
        QuickSortFinalPivot(&v, 0, v.size() - 1);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        cout << "\t|" << duration.count();
      } else {
        cout << "\t\t";
      }

      v = original;
      start = high_resolution_clock::now();
      QuickSortRandomPivot(&v, 0, v.size() - 1, gen);
      end = high_resolution_clock::now();
      duration = duration_cast<nanoseconds>(end - start);
      if (duration.count() < 1000000) {
        cout << "\t";
      }
      cout << "\t|" << duration.count() << endl;
    }

    cout << endl << endl;
  }

  return 0;
}
