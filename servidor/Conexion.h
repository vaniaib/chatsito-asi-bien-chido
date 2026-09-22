#ifndef CONEXION_H
#define CONEXION_H
#include<bits/stdc++.h>
#include <thread>
#include <mutex>
#include "ListaUsuarios.h"
using namespace std;
class Conexion{
private:
    map<string, int> conexiones;
    mutable mutex mutexConexiones;
public:
    void agrega(const string& username, int socket);
    void elimina(const string& username);
    bool existe(const string& username) const;
    int getSocket(const string& username) const;
    const map<string, int>& getConexiones() const;
};

#endif
