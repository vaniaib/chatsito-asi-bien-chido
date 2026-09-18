#include<bits/stdc++.h>
#include "Sala.h"
using namespace std;

ListaUsuarios Sala:: getUsuarios(){
    return usuariosEnlasala;
}
// bool Sala::estaInvitado(){
  
// }
void Sala::agregarAlasala(string username){
  usuariosEnlasala.agregaUsuario(username); 
}



  



