#include <iostream>
#include <vector>

using namespace std;

int main() {
  // Creación
  int a[5];
  vector<int> v;

  // Inserción
  a[0] = 42;
  v.push_back(42); // Insertar al final
//  v.push_front(42); // Insertar al inicio
  v[0] = 142; // Setear un valor especifico con el índice
  
  // consulta
  cout << "Size:" << v.size() << endl; // 2
  cout << "Empty:" << v.empty() << endl; // Si está o no vacío
  cout << "value: " << v[0] << endl; // No revisa si la posición es valida
  cout << "value: " << v.at(0) << endl; // Revisa si la posición es valida
  
  // Borrado
  v.pop_back(); // Eliminar el último valor del vector
//  v.pop_front(); // Eliminar el primer valor del vector


  return 0;
}