#include <iostream>
#include <vector>
#include <chrono>
#include <random>

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

void Merge(vector<int>* v, int left, int right, int medium) { // Función Merge para ordenar el vector
  int i = left, j = medium + 1; // Creación de los indices para los ciclos
  vector<int> temporal; // Vector temporal que va a guardar la sección del vector ordenada 

  while (i <= medium && j <= right) { // Hasta que alguna de las mitades termine de revisarse
    if (v->at(i) < v->at(j)) { // Si el elementi i-ésimo es menor al j-ésimo.
      temporal.push_back(v->at(i)); i++; // Se añade al vector temporal el elemento i-ésimo que es menor
    } else {
      temporal.push_back(v->at(j)); j++; // Se añade al vector temporal el elemento j-ésimo que es menor
    }
  }

  while (i <= medium) { // Mientras queden números en la mitad izquierda se terminan de meter en el vector temproal
    temporal.push_back(v->at(i)); i++;
  }
  
  while (j <= right) { // Mientras queden números en la mitad derecha se terminan de meter en el vector temproal
    temporal.push_back(v->at(j)); j++;
  }

  for (int k = 0; k < temporal.size(); k++) { // Copiar los elementos ordenados de vuelta al vector original
    v->at(left + k) = temporal[k];
  }

  return;
}

void Sort(vector<int>* v, int left, int right) { // Función que hace la "separación" del vector en mitades mas pequeñas
  if (left < right) {
    int medium = left + (right - left) / 2;
    Sort(v, left, medium); // Llamada recursiva con la mitad izquierda del vector
    Sort(v, medium + 1, right); // Llamada recursiva con la mitad derecha del vector
    Merge(v, left, right, medium); // Llamada a la función para la organización
  }

  return;
}

void MergeSort(vector<int>* v) { // Función MergeSort que recibe el puntero al vector y se usa como función auxiliar
  if (v->size() == 0) { // Se revisa que el vector no esté vacío
    cout << "Empty vector" << endl;
    return;
  }
  
  Sort(v, 0, v->size() - 1); // Llamada a la función Sort con el primer y último índice del vector

  return;
}

int main() {
  vector<int> original;
  vector<int> v; 
  
  for (int i = 2; i <= 8; i++) {
    original.clear();
    int size = 1;
    for (int k = 0; k < i; k++) size *= 10;
    FillVector(size, &original);
    cout << "10^" << i << endl;
    
    for (int j = 1; j <= 10; j++) {
      v = original;
      auto inicio = high_resolution_clock::now();
      MergeSort(&v);
      auto fin = high_resolution_clock::now();
      auto duracion = duration_cast<nanoseconds>(fin - inicio);
      cout << " -> (" << j << ") " << "Tiempo de ordenamiento: " << duracion.count() << " ns" << endl;
    }

    cout << endl;
  }


  return 0;
}