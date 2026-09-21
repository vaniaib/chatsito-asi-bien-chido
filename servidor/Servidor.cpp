#include<bits/stdc++.h>
#include "Servidor.h"
using namespace std;
//int puerto

//para identificar usuarios
void Servidor:: identificaUsuario(string u){
  //deberia no aceptar usernames con longitid >8 pero ns q ponber lol
  //  if(u.length() > 8)
  // m.anotaRespuesta();
  if(general.getUsuarios().validaUsuario(u)){     
    general.agregarAlasala(u);
    m.anotaRespuesta(tipoRespuesta, opIdentify, resSuccess, u);
    //notificar a los demás tambien  
  }
  else
    m.anotaRespuesta(tipoRespuesta, opIdentify, resUserexists, u);
}

//para enviar textos publicos y privados?
//void mensajePublico()

//para crear las salas
bool Servidor:: validaNombredeSala(string username){    
  if(salas.find(username) == salas.end())     
    return true;          
  return false;
}
void Servidor:: creaSala(string nombre, string creador){
  if(validaNombredeSala(nombre)){
    Sala s(nombre);
    salas.insert({nombre, s});
    s.agregarAlasala(creador);
    //mensaje de qeu si se creó
  }
  cout << "errorcito del servidor y asi";
  //mensaje de que nombre invalido o algo asi
}


//para invitar a las salas
//void invitaaSala()

//para unirse a una sala
void uniraSala(string sala, string user){
  
}

//pedir la lista de usuarios
//void listadeUsuarios

//para enviar mensajes en la sala
//void mensajesenSala()

//para salir de una sala
//void salirdeSala()

//para desconectarse del servidor
//void desconecta()


void Servidor::sirve(){
    
  string nombre;  
  for(int i = 0; i <3; i++){
    cin >> nombre;
    identificaUsuario(nombre);    

  }
  for(const auto& [name, estado] : general.getUsuarios().getLista())
    cout << name << estado << "\n";
    
}
// void mensajeRecibido(Conexion c, Mensaje mensajito){
//   if(!c.isActiva()){
//     return;
//     switch(mensaje){
//     case BASE_DE_DATOS:
// 	baseDeDatos(conexion);
// 	break;
//     case REGISTRO_AGREGADO:
// 	registroAlterado(conexion, mensaje);
// 	break;
//     case REGISTRO_ELIMINADO:
// 	registroAlterado(conexion, mensaje);
// 	break;
//     case REGISTRO_MODIFICADO:
// 	registroModificado(conexion);
// 	break;
//     case DESCONECTAR:
// 	desconectar(conexion);
// 	break;
//     case GUARDA:
// 	guarda();
// 	break;
//     case DETENER_SERVICIO:
// 	detenerServicio();
// 	break;
//     case ECO:
// 	eco(conexion);
// 	break;
//     case INVALIDO:
// 	error(conexion, "Mensaje inválido");
// 	break;
//     }
//   }
// }
    

//  }
  
