#include<bits/stdc++.h>
using namespace std;

class ListaUsuarios{

private:
  map<string, string> lista;

public:
  ListaUsuarios();

  map<string, string> getLista() const{
    return lista;
  }

  void agregaUsuario(string nombre, string status){
    lista.insert({nombre, status});
  }
  void eliminaUsuario(string nombre){
    lista.erase(nombre);
  }
  void cambioStatus(string usuario, string status){
    lista[usuario] = status;
  }
    
  
}
  
