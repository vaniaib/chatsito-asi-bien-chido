#ifndef MENSAJE_H
#define MENSAJE_H
#include<bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Mensaje{
  
public:
  Mensaje(){};
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
    
    TEXT,

    NEW_ROOM,

    INVITE,

    JOIN_ROOM,

    ROOM_USERS,

    ROOM_TEXT,
    
    LEAVE_ROOM,
    
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
  string cadenaTipo(Type t);
  string cadenaEstado(Status s);
  string cadenaOperacion(Operation o);
  string cadenaResultado(Result r);
  void anotaRespuesta(Type tipo, Operation operacion, Result resultado, string extra);
    
};

#endif
