#include<bits/stdc++.h>
#include "ListaUsuarios.h"
#include "Servidor.h"
using namespace std;
//solo manda a llamar al servidor
//para manejar cuando pasan numeros imvalidos y otras excepciones jeje 

void INSTRUCCIONES(){
  cout << "Debes poner un número [1024, 65535]" << '\n';
}
void USO(exception& e){
  cout << "Algo salió mal con : " << e.what() << "\n";
}

int main(){
try{
    int puerto;
    cin >> puerto;
    if(cin.fail() || puerto < 1024 || puerto > 65535){
      INSTRUCCIONES();
      return 0;
    }
    Servidor s(puerto);
    s.sirve();
 }catch(exception& e){
  USO(e);
  return 0;
 }
}


