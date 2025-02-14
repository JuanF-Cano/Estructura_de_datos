#include <iostream>
#include <vector>
#include <random>

using namespace std;

void Sort(vector<int>* v, int pivotIndex, int start, int final) { // Función recursiva para el QuickSort
  // declaración de los vectores auxiliares que contendrán las porciones de vector a la izquierda y derecha del pivote
  vector<int> auxLeft, auxRight; 
  int pivot = v->at(pivotIndex); // Se cuarda el valor del pivote

  for (int i = start; i <= final; i++) { // Recorre el vector para poner todos los menores al pivote a la izquierda
    if (i != pivotIndex) { // No tiene en cuenta el pivote en la comparación para no duplicar el valor
      if (v->at(i) < pivot) {
        auxLeft.push_back(v->at(i)); // Si el valor i-ésimo es menor al valor del pivote se guarda en el vector auxiliar
      } else {
        auxRight.push_back(v->at(i)); // Si el valor i-ésimo es mayor al valor del pivote se guarda en el vector auxiliar
      }
    }
  }

  int j = start; // Inicia el contador en donde inicia la porción de vector analizada
  for (int i = 0; i < auxLeft.size(); i++, j++) { // Se copia el vector auxiliar izquierdo en el vector original
    (*v)[j] = auxLeft[i];
  }
  
  int newPivotIndex = j; // Se guarda el nuevo índice del pivote
  (*v)[j] = pivot; // Se guarda el valor del pivote en la posición siguiente a los valores menores a él
  j++; // Se incrementa en 1 para continuar con el vector de los valores mayores al pivote

  for (int i = 0; i < auxRight.size(); i++, j++) { // Se copia el vector auxiliar derecho en el vector original
    (*v)[j] = auxRight[i];
  }
  
  // Creación del proximo pivote random
  random_device rd;
  mt19937 gen(rd());
  
  if (start < newPivotIndex - 1) { // Se cumple hasta que el vector sea de tamaño 2 (inicio y pivote)
    uniform_int_distribution<> distrib(start, newPivotIndex - 1);
    Sort(v, distrib(gen), start, newPivotIndex - 1); // Llamada recursiva con los datos de la porción del vector sin el pivote
  }
  if (newPivotIndex + 1 < final) { // Se cumple hasta que el vector sea de tamaño 2 (pivote y final)
    uniform_int_distribution<> distrib(newPivotIndex + 1, final);
    Sort(v, distrib(gen), newPivotIndex + 1, final); // Llamada recursiva con los datos de la porción del vector sin el pivote
  }

  return;
}

void QuickSort(vector<int>* v) { // Función QuickSort que recibe el puntero al vector y se usa como función auxiliar
  if (v->size() == 0) { // Se revisa que el vector no esté vacío
    cout << "Empty vector" << endl;
    return;
  }

  // Creación del primer pivote random
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(0, v->size() - 1);
  Sort(v, distrib(gen), 0, v->size() - 1); // Llamado a la función recursiva que ordena al vector

  return;
}

int main() {
    vector<int> v = {29, 31, 2, 4, 90}; // Vector ejemplo
  
    for(int i = 0; i < v.size(); i++) { // Mostramos los datos del vector sin ordenar
      cout << v.at(i) << " " ;
    }
    cout << endl;
  
    QuickSort(&v); // Llamada a la función principal
    
    for(int i = 0; i < v.size(); i++) { // Mostramos los datos del vector ordenado
      cout << v.at(i) << " " ;
    }
    cout << endl;
  
    return 0;
  }