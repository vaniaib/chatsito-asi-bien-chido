#ifndef SERVIDOR_H
#define SERVIDOR_H
#include<bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "ListaUsuarios.h"
#include "Sala.h"
#include "Mensaje.h"
using namespace std;

class Servidor{
private:
  bool continuaEjecucuion;
  Sala general;
  map<string, Sala> salas;
  Mensaje m;
  Mensaje::Type tipoRespuesta = Mensaje::Type::RESPONSE;
  Mensaje::Type tipoNewuser = Mensaje::Type::NEW_USER;
  Mensaje::Type tipoNewstatus = Mensaje::Type::NEW_STATUS;
  Mensaje::Type tipoUslist = Mensaje::Type::USER_LIST;
  Mensaje::Operation opIdentify = Mensaje::Operation::IDENTIFY;
  Mensaje::Result resSuccess = Mensaje::Result::SUCCESS;
  Mensaje::Result resUserexists = Mensaje::Result::USER_ALREADY_EXISTS;   
  int puerto;
  int serversocket;
  mutex mutex;
  
public:
  
  Servidor(int puerto) : general("general"){
    this -> puerto = puerto;
  };
  void creaSala(string nombre, string creador);
  void sirve();
  bool validaNombredeSala(string username);
  
  void identificaUsuario(string nombre); 
  void inicia();
  
};

#endif
