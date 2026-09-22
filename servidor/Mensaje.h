#ifndef MENSAJE_H
#define MENSAJE_H
#include<bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Mensaje{
  
public:
  // Mensaje(){};
  //enumeracion para los tipos
  enum class Type{
    
    RESPONSE, 

    NEW_USER,

    NEW_STATUS,

    USER_LIST,

    TEXT_FROM,

    PUBLIC_TEXT_FROM,

    INVITATION,

    JOINED_ROOM,

    ROOM_USER_LIST,

    ROOM_TEXT_FROM,

    LEFT_ROOM,

    DISCONNECTED,    
  
  };

  //enumeracion para los estados
  enum class Status{

    ACTIVE,

    BUSY,
    
    AWAY
  };  
  //enumeracion para las operaciones de los mensajes que recibe el cliente
  enum class Operation{

    IDENTIFY,

    STATUS,

    USERS,
    
    TEXT,

    PUBLIC_TEXT,

    NEW_ROOM,

    INVITE,

    JOIN_ROOM,

    ROOM_USERS,

    ROOM_TEXT,
    
    LEAVE_ROOM,

    DISCONNECT
    
  };

  //enumeracion para los resultados en response
  enum class Result{

    SUCCESS,

    USER_ALREADY_EXISTS,    
    
    ROOM_ALREADY_EXISTS,
    
    NO_SUCH_ROOM,

    NOT_JOINED,

    NOT_INVITED,

    NO_SUCH_USER,    
    
  };
  //  para respuestas
  static string cadenaTipo(Type t);
  static string cadenaStatus(Status s);
  static string cadenaOperacion(Operation o);
  static string cadenaResultado(Result r);
  void anotaRespuesta(Type tipo, Operation operacion, Result resultado, string extra);
  // para mensajes que manda el servidor
  //  static string anotaRespuesta(Operation operacion,Result resultado, const string& extra);
  static string nuevoUsuario(const string& username);
  static string nuevoStatus(const string& username, const Status& status);
  static string listaUsuarios(const map<string, Status>& usuarios);
  static string textoPrivado(const string& username,const string& text);
  static string textoPublico(const string& username,const string& text);
  static string invitacion(const string& username,const string& roomname);
  static string unioSala(const string& username, const string& roomname);
  static string listausuariosSala(const string& roomname, const map<std::string, Status>& usuarios);
  static string textoSala(const string& roomname, const string& username,const string& text);
  static string salioSala(const string& roomname, const string& username);
  static string desconectado(const string& username);    
};

#endif
