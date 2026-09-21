#include<bits/stdc++.h>
#include "Sala.h"
using namespace std;

ListaUsuarios Sala:: getUsuarios(){
    return usuariosEnlasala;
}
void Sala::agregarAlasala(string username){
  usuariosEnlasala.agregaUsuario(username); 
}
void Sala::eliminadeSala(string username){
  usuariosEnlasala.eliminaUsuario(username); 
}




  



