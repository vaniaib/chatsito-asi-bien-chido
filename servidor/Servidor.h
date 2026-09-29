#ifndef SERVIDOR_H
#define SERVIDOR_H
#include<bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "Conexion.h"
#include "ListaUsuarios.h"
#include "Sala.h"
#include "Mensaje.h"
#include "Bitacora.h"
using namespace std;

class Servidor{
private:
  //par aque siempre ejecute
  bool continuaEjecucion;
  //sala general y demás salas
  Sala general;
  map<string, unique_ptr<Sala>> salas;
  Bitacora b;
  //para mandar mensajes de repuestas
  Mensaje m;
  Mensaje::Type tipoRespuesta = Mensaje::Type::RESPONSE;
  Mensaje::Type tipoNewuser = Mensaje::Type::NEW_USER;
  Mensaje::Type tipoNewstatus = Mensaje::Type::NEW_STATUS;
  Mensaje::Type tipoUslist = Mensaje::Type::USER_LIST;
  Mensaje::Operation opIdentify = Mensaje::Operation::IDENTIFY;
  Mensaje::Operation opjoinroom = Mensaje::Operation::JOIN_ROOM;
  Mensaje::Operation opinvite = Mensaje::Operation::INVITE;
  Mensaje::Result resSuccess = Mensaje::Result::SUCCESS;
  Mensaje::Result resUserexists = Mensaje::Result::USER_ALREADY_EXISTS;
  Mensaje::Result roomexists = Mensaje::Result::ROOM_ALREADY_EXISTS;
  Mensaje::Result roomnoexiste = Mensaje::Result::NO_SUCH_ROOM;
  Mensaje::Result nohayuser = Mensaje::Result::NO_SUCH_USER;
  //lo de los sockets y conexiones
  int puerto;
  int serversocket;
  Conexion conexiones;
  //  map<string, int> conexiones;
  //lo de los hilos
  //mutex mutex;  
public:  
  Servidor(int puerto) : general("general"){
    continuaEjecucion=true;
    this -> puerto = puerto;
  };
  void uniraSala(const string& sala, const string& user);
  void invitaaSala(const string& dueño, const string& nombreSala,const vector<string>& usuarios);
  void creaSala(const string& nombre,const string& creador);
  void sirve();
  bool validaNombredeSala(const string& nombre, const string& salaname);
  void enviaaUsuario(const string& username,const string& mensaje);
  void enviaATodos(const string& mensaje,const string& excepto);
  void mensajesenSala(Sala& sala, const string& mensaje);
  void identificaUsuario(int socketcliente, const string& username);
  void enviaListaUsuarios(const string& usuario);
  void  mandaTextoPrivado(const string& usuario,const string& destinatario,const string& texto);
  void mandaTextoPublico(const string& usuario,const string& texto);
  void  mandaTextoSala(const string& usuario,const string& sala, const string& texto);
  void enviaUsuariosSala(const string& usuario, const string& sala);
  void  cambiaEstado(const string& usuario,const string& estado);
  void salirSala(const string& user,const string& sala);
  void desconecta(const string& user, int socketcliente);
  void inicia();
  void leeCliente(int socketcliente);
  
};

#endif
