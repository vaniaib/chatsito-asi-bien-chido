#include<bits/stdc++.h>
using namespace std;
#include "Mensaje.h"

string Mensaje::cadenaTipo(Type t){
  switch(t){
  case Type:: RESPONSE:
    return "RESPONSE";      	
  case Type::NEW_USER:
    return "NEW_USER";

  case Type::NEW_STATUS:
    return "NEW_STATUS";

  case Type::USER_LIST:
    return "USER_LIST";

  case Type::TEXT_FROM:
    return "TEXT_FROM";

  case Type::PUBLIC_TEXT_FROM:
    return "PUBLIC_TEXT_FROM";

  case Type::INVITATION:
    return "INVITATION";

  case Type::JOINED_ROOM :
    return  "JOINED_ROOM";

  case Type::ROOM_USER_LIST:
    return "ROOM_USER_LIST";

  case Type::ROOM_TEXT_FROM:
    return"ROOM_TEXT_FROM";

  case Type::LEFT_ROOM:
    return "LEFT_ROOM";
  case Type::DISCONNECTED:
    return "DISCONNECTED";
  default:
    return "RESPONS";
      
  }
}

string Mensaje::cadenaStatus(Status s){
  switch(s){
  case Status::ACTIVE:
    return "ACTIVE";
  case Status::BUSY:
    return "BUSY";
  case Status::AWAY:
    return "AWAY";
  default:
    return "INVALIDO";
  }
}
 

string Mensaje::cadenaOperacion(Operation o){
  switch(o){
  case Operation:: IDENTIFY:
    return"IDENTIFY";
  case Operation:: TEXT:
    return"TEXT";
  case Operation:: NEW_ROOM:
    return"NEW_ROOM";
  case Operation:: INVITE:
    return"INVITE";
  case Operation:: JOIN_ROOM:
    return"JOIN_ROOM";
  case Operation:: ROOM_USERS:
    return"ROOM_USERS";
  case Operation:: ROOM_TEXT:
    return"ROOM_TEXT";
  case Operation::LEAVE_ROOM:
    return "LEAVE_ROOM";
  default:
    return "INVALID";       
  }
}

string Mensaje::cadenaResultado(Result r){
  switch(r){
  case Result:: SUCCESS:
    return"SUCCESS";
  case Result:: ROOM_ALREADY_EXISTS:
    return  "ROOM_ALREADY_EXISTS";
  case Result:: USER_ALREADY_EXISTS:
    return"USER_ALREADY_EXISTS";
  case Result:: NO_SUCH_ROOM:
    return"NO_SERVIDORSUCH_ROOM";
  case Result:: NOT_JOINED:
    return"NOT_JOINED";
  case Result:: NOT_INVITED:
    return"NOT_INVITED";
  case Result:: NO_SUCH_USER:
    return"NO_SUCH_USER";
  default:
    return "INVALID";
      
  }
}
string Mensaje::nuevoUsuario(const string& username) {
  json j = {
    {"type", "NEW_USER"},
    {"username", username}
  };
  return j.dump() + "\n";
}

string Mensaje::nuevoStatus(const string& username, const Status& status){
  string s = cadenaStatus(status);
  json j = {
    {"type", "NEW_STATUS"},
    {"username", username},
    {"status", s}
  };

  return j.dump() + "\n";
}

string Mensaje::listaUsuarios(const map<string, Status>& usuarios){
  json users = json::object();
  for (const auto& [username, estado] : usuarios) {
    users[username] = cadenaStatus(estado);
  }  
  json j = {
    {"type", "USER_LIST"},
    {"users", users}
  };
  return j.dump() + "\n";
}
string Mensaje::textoPrivado(const string& username,const string& text){
  json j = {
    {"type", "TEXT_FROM"},
    {"username", username},
    {"text", text}
  };
  return j.dump() + "\n";
}
string Mensaje::textoPublico(const string& username,const string& text){
  json j = {
    {"type", "PUBLIC_TEXT_FROM"},
    {"username", username},
    {"text", text}
  };
  return j.dump() + "\n";
}
string Mensaje::unioSala(const string& username, const string& roomname){
  json j = {
    {"type", "JOINED_ROOM"},
    {"roomname", roomname},
    {"username", username},
  };
  return j.dump() + "\n";
}
string Mensaje::invitacion(const string& username,const string& roomname){
  json j = {
    {"type", "INVITATION"},
    {"username", username},
    {"roomname", roomname}
  };
  return j.dump() + "\n";
}
string Mensaje::listausuariosSala(const string& roomname, const map<std::string, Status>& usuarios){
  json users = json::object();
  for (const auto& [username, estado] : usuarios) {
    users[username] = cadenaStatus(estado);
  }
  json j = {
    {"type", "ROOM_USER_LIST"},
    {"roomname", roomname},
    {"users", users}
  }; 
  return j.dump() + "\n";
}
string Mensaje::textoSala(const string& roomname, const string& username,const string& text){
  json j = {
    {"type", "ROOM_TEXT_FROM"},
    {"roomname", roomname},
    {"username", username},
    {"text", text}
  };
  return j.dump() + "\n";
}
string Mensaje::salioSala(const string& roomname, const string& username){
  json j = {
    {"type", "LEFT_ROOM"},
    {"roomname", roomname},
    {"username", username}
  };
  return j.dump() + "\n";
}

string Mensaje::desconectado(const string& username){
  json j = {
    {"type", "DISCONNECTED"},
    {"username", username}
  };
  return j.dump() + "\n";
}


void Mensaje::anotaRespuesta(Type tipo, Operation operacion, Result resultado, string extra){
  string t = cadenaTipo(tipo);
  string o = cadenaOperacion(operacion);
  string r = cadenaResultado(resultado);
  json j = {
    {"type", t},
    {"operation", o},
    {"result", r},
    {"extra", extra}	
  };
  cout << j << "\n";  
}
//   switch(case){
      
//   }
   
  

