#include<bits/stdc++.h>
#include "Servidor.h"
using namespace std;

// class Servidor{
  
// public :
//   Servidor (int puerto);
  
//   this -> puerto = puerto;
  
void Servidor::sirve(){
    
  string nombre;
  string status = "ACTIVE";
  
  for(int i = 0; i <3; i++){
    cin >> nombre;
    usuarios.agregaUsuario(nombre);
  }
  for(const auto& [name, estado] : usuarios.getLista())
    cout << name << estado << "\n";
    
  }

// private:
//   void anotaMensaje(String format){
    
//   }

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
  
