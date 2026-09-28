#include<bits/stdc++.h>
#include "Sala.h"
using namespace std;

Sala::Sala(const string& nombre): nombre(nombre){}
ListaUsuarios& Sala:: getUsuarios(){
  lock_guard<mutex> lock(mutexSala);
    return usuariosEnlasala;
}
string Sala:: getNombre(){
  return nombre;
}
void Sala::agregarAlasala(const string& username){
  lock_guard<mutex> lock(mutexSala);
  usuariosEnlasala.agregaUsuario(username); 
}
void Sala::eliminadeSala(const string& username){
  lock_guard<mutex> lock(mutexSala);
  usuariosEnlasala.eliminaUsuario(username); 
}
void Sala:: agregaInvitado(const string& i){
  listaInvitados.insert(i);
}
void Sala:: eliminaInvitado(const string& i){
  listaInvitados.erase(i);
}
//verifica que este un user invitado a la sala, regresa verdadero si está
bool Sala:: buscaInvitado(const string& i){
  if(listaInvitados.find(i) == listaInvitados.end())
    return false;
  return true;
}
//verifica que este un user en l a la sala
bool Sala:: buscaUser(const string& i){
  if(usuariosEnlasala.getLista().find(i) == usuariosEnlasala.getLista().end())
    return false;
  return true;
}




  



