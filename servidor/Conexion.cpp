#include<bits/stdc++.h>
using namespace std;
#include "Conexion.h"

void Conexion::agrega(const string& username, int socket){
  lock_guard<mutex> lock(mutexConexiones);
  conexiones[username] = socket;
}

void Conexion::elimina(const string& username){
  lock_guard<mutex> lock(mutexConexiones);
    conexiones.erase(username);
}

bool Conexion::existe(const string& username)const{
  lock_guard<mutex> lock(mutexConexiones);
  return (conexiones.find(username) != conexiones.end());
}
int Conexion::getSocket(const string& username)const{
  lock_guard<mutex> lock(mutexConexiones);
    auto it = conexiones.find(username);
    if (it == conexiones.end())
        return -1;
    return it->second;
}
const map<string, int> Conexion::getConexiones() const{
  lock_guard<mutex> lock(mutexConexiones);
  return conexiones;
}
