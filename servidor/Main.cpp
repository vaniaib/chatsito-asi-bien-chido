#include<bits/stdc++.h>
#include "ListaUsuarios.h"
using namespace std;
//solo manda a llamar al servidor
//para manejar cuando pasan numeros imvalidos y otras excepciones jeje 

int INSTRUCCIONES(){
  cout << "Debes poner un número [1024, 65535]" << '\n';
  return 0;
}
void USO(exception& e){
  cout << "Algo salió mal con : " << e.what() << "\n";
}

int main(){
  ListaUsuarios lista;
  int puerto;
  string nombre;
  string status = "ACTIVE";
  cin >> puerto;
  if(cin.fail() || puerto < 1024 || puerto > 65535)
    INSTRUCCIONES();
  for(int i = 0; i <3; i++){
    cin >> nombre;
    lista.agregaUsuario(nombre);
  }
  for(const auto& [name, estado] : lista.getLista())
    cout << name << estado << "\n";
  // try{
  //Servidor s(puerto);
  //s.sirve();
  //  }catch(exception& e){
  //USO(exception& e);
  //return 0;
  cout << "ola jeje" << "\n";
  }


