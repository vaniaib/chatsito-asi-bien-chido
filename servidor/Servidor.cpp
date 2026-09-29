#include<bits/stdc++.h>
#include "Servidor.h"
using namespace std;
//int puerto
//para mandar a un usuario algo
void Servidor::enviaaUsuario(const string& username,const string& mensaje) {
  int socket = conexiones.getSocket(username);
  if (socket == -1) {
    return;
  }
  send( socket,mensaje.c_str(),mensaje.size(),0);
}
//para mandar a todos algo
void Servidor::enviaATodos(const string& mensaje, const string& excepto) {
  const map<string, int> copia = conexiones.getConexiones();
  for(const auto& [username, socket] : copia) {
    if (username == excepto) {
      continue;
    }
    send( socket,mensaje.c_str(),mensaje.size(),0);
  }
}


//para identificar usuarios
void Servidor:: identificaUsuario(int socketcliente, const string& username) {
  if(username.length() > 8)
    close(socketcliente);
  if (general.getUsuarios().validaUsuario(username)) {
    general.agregarAlasala(username);
    conexiones.agrega(username, socketcliente);
    string respuesta = Mensaje::respuesta(Mensaje::Operation::IDENTIFY, Mensaje::Result::SUCCESS,username);
    send(socketcliente, respuesta.c_str(), respuesta.size(),0);
    string nuevo = Mensaje::nuevoUsuario(username);
    enviaATodos(nuevo,username);
  }else {
    string respuesta = Mensaje::respuesta( Mensaje::Operation::IDENTIFY, Mensaje::Result::USER_ALREADY_EXISTS,username);
    send(socketcliente,respuesta.c_str(), respuesta.size(),0);
  }
}
//  if(u.length() > 8)
// mat al cliente jeje
void Servidor:: cambiaEstado(const string& usuario,const string& estado){
  if((estado != "AWAY") ^ (estado != "BUSY") ^ (estado != "ACTIVE"))
    return;
  if(general.getUsuarios().getEstado(usuario) == estado)
    return;
  general.getUsuarios().cambiaStatus(usuario, estado);
  json j;
  j["type"] = "NEW_STATUS";
  j["username"] = usuario;
  j["status"] = estado;
  string mensaje = j.dump() + "\n";
  enviaATodos(mensaje, usuario);
  
}

//para enviar textos privados?
void  Servidor::mandaTextoPrivado(const string& usuario,const string& destinatario,const string& texto){
  //valida usuario checa que no haya un nombre igual en la lista, entonces lo podemos usar
  if(general.getUsuarios().validaUsuario(usuario)){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "TEXT";
    j["result"] = "NO_SUCH_USER";
    j["extra"] = destinatario;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(destinatario, mensaje);
    
  }

  json j;
  j["type"] = "TEXT_FROM";
  j["username"] = usuario;
  j["text"] = texto;
  string mensaje = j.dump() + "\n";
  enviaaUsuario(destinatario, mensaje);
}

//para enviar textos publicos
void  Servidor::mandaTextoPublico(const string& usuario,const string& texto){
  json j;
  j["type"] = "PUBLIC_TEXT_FROM";
  j["username"] = usuario;
  j["text"] = texto;
  string mensaje = j.dump() + "\n";
  enviaATodos(mensaje, usuario);
}
// void  Servidor::mandaTextoSala(const string& usuario,const string& salaconst string& texto){
//   json j;
//   j["type"] = "PUBLIC_TEXT_FROM";
//   j["username"] = usuario;
//   j["text"] = texto;
//   string mensaje = j.dump() + "\n";
//   enviaATodos(mensaje, usuario);
// }

//para crear las salas
bool Servidor:: validaNombredeSala(const string& nombre, const string& salaname){    
  if(salas.find(salaname) == salas.end())     
    return true;
  else{
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "NEW_ROOM";
    j["result"] = "ROOM_ALREADY_EXISTS";
    j["extra"] = salaname;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(nombre, mensaje);
    return false;  
  }
}
void Servidor:: creaSala(const string& nombre, const string& nomsala){
  if(nomsala.length() > 16)
    return;
  if (validaNombredeSala(nombre, nomsala)) {
    auto s = make_unique<Sala>(nomsala);
    s->agregarAlasala(nombre);
    salas.insert({nomsala, move(s)});
    //mensaje de qeu si se creó
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "NEW_ROOM";
    j["result"] = "SUCCESS";
    j["extra"] = nomsala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(nombre, mensaje);
  // }else{
  //   json j;
  //   j["type"] = "RESPONSE";
  //   j["operation"] = "NEW_ROOM";
  //   j["result"] = "ROOM_ALREADY_EXISTS";
  //   j["extra"] = nombre;
  //   string mensaje = j.dump() + "\n";
  //   enviaaUsuario(u, mensaje);
  }
}

//para invitar a las salas
void Servidor ::invitaaSala(const string& dueño, const string& nombreSala,const vector<string>& usuarios){
  auto it = salas.find(nombreSala);
  //Si no existe la sala se manda una respuesta
  if(it == salas.end()){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "INVITE";
    j["result"] = "NO_SUCH_ROOM";
    j["extra"] = nombreSala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(dueño, mensaje);
    return;
  }  
  Sala& s = *it->second;
  //mandar las invitaciones 
  for(const string& u : usuarios){
    //si no existe un usuario se cancela todo
    if(general.getUsuarios().getLista().find(u) == general.getUsuarios().getLista().end()){
      json j;
      j["type"] = "RESPONSE";
      j["operation"] = "INVITE";
      j["result"] = "NO_SUCH_USER";
      j["extra"] = u;
      string mensaje = j.dump() + "\n";
      enviaaUsuario(dueño, mensaje);
      return;
    } else{
      //se manda el msj solo a los que no esten ya en la sala o invutados
      if(s.buscaInvitado(u) || s.buscaUser(u))
	continue;
      //mandar el mensaje de invitacion y meter a la lista de invitados
      s.agregaInvitado(u);
      json j;
      j["type"] = "INVITATION";
      j["username"] = dueño;
      j["roomname"] = nombreSala;
      string mensaje = j.dump() + "\n";
      enviaaUsuario(u, mensaje);
    }
  }
}	    
//para unirse a una sala
void Servidor::uniraSala(const string& sala, const string& user){
  //ver que la sala exista
  auto it = salas.find(sala);
  if(it == salas.end()){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "JOIN_ROOM";
    j["result"] = "NO_SUCH_ROOM";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(user, mensaje);
    return;
  }
  Sala& s = *it->second;
  //ver que esté invitadito
  if(!s.buscaInvitado(user)){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "JOIN_ROOM";
    j["result"] = "NOT_INVITED";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(user, mensaje);
    return;
  }
    //ya meterlo y mandarle el msj
    s.agregarAlasala(user);
    json jeison;
    jeison["type"] = "RESPONSE";
    jeison["operation"] = "JOIN_ROOM";
    jeison["result"] = "SUCCES";
    jeison["extra"] = sala;
    string msj = jeison.dump() + "\n";
    enviaaUsuario(user, msj);
    json j;
    j["type"] = "JOINED_ROOM";
    j["roomname"] = sala;
    j["username"] = user;
    string mensaje = j.dump() + "\n";
    for(const auto& [u, i] : s.getUsuarios().getLista()) {
      if (u == user) {
	continue;
      }
      enviaaUsuario(u, mensaje);
    }    
  }

//envia la lista de ususarios en la sala
void Servidor::enviaUsuariosSala(const string& usuario, const string& nombreSala){
  //si la sala no existe
  auto it = salas.find(nombreSala);
  if (it == salas.end()){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "ROOM_USERS";
    j["result"] = "NO_SUCH_ROOM";
    j["extra"] = nombreSala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;
  }
  Sala& sala = *it->second;
  //si no está en la sala
  if (!sala.buscaUser(usuario)){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "ROOM_USERS";
    j["result"] = "NOT_JOINED";
    j["extra"] = nombreSala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;
  }
  json j;
  j["type"] = "ROOM_USER_LIST";
  j["roomname"] = nombreSala;
  j["users"] = json::object();
  for (const auto& [nombre, estado] : sala.getUsuarios().getLista()){
    j["users"][nombre] = estado;
  }
  string mensaje = j.dump() + "\n";
  enviaaUsuario(usuario, mensaje);
}
//pedir la lista de usuarios en la sala general
void Servidor::enviaListaUsuarios(const string& usuario){
  json j;  
  j["type"] = "USER_LIST";
  j["users"] = json::object();  
  for (const auto& [usuario, estado] : general.getUsuarios().getLista()) {
    j["users"][usuario] = estado;
  }
  string mensaje = j.dump() + "\n";
  enviaaUsuario(usuario, mensaje);
  
}



//para enviar mensajes en la sala
void Servidor:: mandaTextoSala(const string& usuario,const string& sala, const string& texto){
  auto it = salas.find(sala);
  //si no existe la sala
  if (it == salas.end()){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "ROOM_TEXT";
    j["result"] = "NO_SUCH_ROOM";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;
  }
  Sala& s = *it->second;  
  if(!s.buscaUser(usuario)){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "ROOM_TEXT";
    j["result"] = "NOT_JOINED";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;
  }
  json j;
  j["type"] = "ROOM_TEXT_FROM";
  j["roomname"] = sala;
  j["username"] = usuario;
  j["text"] = texto;
  string mensaje = j.dump() + "\n";
  for (const auto& [username, status] : s.getUsuarios().getLista())
    enviaaUsuario(username, mensaje);
}
//para salir de una sala
void Servidor::salirSala(const string& usuario,const string& sala){
  auto it = salas.find(sala);
  if (it == salas.end()){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "LEAVE_ROOM";
    j["result"] = "NO_SUCH_ROOM";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;    
  }
  Sala& s = *it->second;
  //si no está en la sala
  if(!s.buscaUser(usuario)){
    json j;
    j["type"] = "RESPONSE";
    j["operation"] = "LEAVE_ROOM";
    j["result"] = "NOT_JOINED";
    j["extra"] = sala;
    string mensaje = j.dump() + "\n";
    enviaaUsuario(usuario, mensaje);
    return;    
  }
  s.eliminadeSala(usuario);
  s.eliminaInvitado(usuario);
  if(s.getUsuarios().getLista().empty())
    salas.erase(sala);
  json j;
  j["type"] = "LEFT_ROOM";
  j["roomname"] = sala;
  j["username"] = usuario;
  string mensaje = j.dump() + "\n";
  for (const auto& [username, status] : s.getUsuarios().getLista())
    enviaaUsuario(username, mensaje);
} 
  

//para desconectarse del servidor
void Servidor::desconecta(const string& user, int socketcliente){
  conexiones.elimina(user);
  for(auto& [n,s] : salas){
    Sala& sala = *s;
    json j;
    j["type"] = "LEFT_ROOM";
    j["roomname"] = sala.getNombre();
    j["username"] = user;
    string mensaje = j.dump() + "\n";
    //eliminar de las salas a las que pertenezca
    if(sala.buscaUser(user)){
      sala.eliminadeSala(user);
      sala.eliminaInvitado(user);
      for (const auto& [username, status] : sala.getUsuarios().getLista())
	enviaaUsuario(username, mensaje);
    }
  }
  general.eliminadeSala(user);
  json jeison;
  jeison["type"] = "DISCONNECTED";
  jeison["username"] = user;
  string msj = jeison.dump() + "\n";
  for (const auto& [username, status] : general.getUsuarios().getLista())
    enviaATodos(username, msj);
  shutdown(socketcliente, SHUT_RDWR);
  close(socketcliente);
}
  

//para leer a los clientes
void Servidor::leeCliente(int socketcliente){
  char buffer[1024] = {0};
  string datos;
  string usuarioActual;
  int i = 0;
  while(continuaEjecucion){
    ssize_t bytes_read = recv(socketcliente, buffer, sizeof(buffer)-1, 0);
    if(bytes_read <= 0)
      break;
    datos.append(buffer, bytes_read);
    size_t pos;
    while((pos=datos.find('\n')) != string::npos) {
      string linea = datos.substr(0, pos);
      datos.erase(0, pos+1);
      if (linea.empty())
	continue;    
      try {
	json j = json::parse(linea);      
	string tipo = j.at("type");
	if ((i = 0) && (tipo != "IDENTIFY")){
	  json j;
	  j["type"] = "RESPONSE";
	  j["operation"] = "INVALID";
	  j["result"] = "NOT_IDENTIFIED";
	  string mensaje = j.dump() + "\n";
	  //	  enviaaUsuario(usuarioActual, mensaje);
	  send(socketcliente, mensaje.c_str(),mensaje.size(),0);
	  desconecta(usuarioActual, socketcliente);
	}
	if (tipo == "IDENTIFY"  && i != 0 ){
	  usuarioActual = j.at("username");
	  desconecta(usuarioActual, socketcliente);
	}
	i++;
	if (tipo == "IDENTIFY") {
	  usuarioActual = j.at("username");
	  identificaUsuario(socketcliente,usuarioActual);
	}
	else if (tipo == "STATUS") {
	  cambiaEstado(usuarioActual,j.at("status").get<string>());
	}
	else if (tipo == "USERS") {
	  enviaListaUsuarios(usuarioActual);
	}
	else if (tipo == "TEXT") {
	  mandaTextoPrivado(usuarioActual, j.at("username"),j.at("text"));
	}
	else if (tipo == "PUBLIC_TEXT") {
	  mandaTextoPublico(usuarioActual, j.at("text"));
	}
	else if (tipo == "NEW_ROOM") {
	  creaSala(j.at("roomname"), usuarioActual);
	}
	else if (tipo == "INVITE") {
	  invitaaSala(usuarioActual,j.at("roomname"),j.at("usernames").get<vector<string>>());
	}
	else if (tipo == "JOIN_ROOM") {
	  uniraSala(j.at("roomname"), usuarioActual);
	}
	else if (tipo == "ROOM_USERS") {
	  enviaUsuariosSala(usuarioActual,j.at("roomname"));
	}
	else if (tipo == "ROOM_TEXT") {
	  mandaTextoSala(usuarioActual,j.at("roomname"),j.at("text"));
	}
	else if (tipo == "LEAVE_ROOM") {
	  salirSala(usuarioActual,j.at("roomname"));
	}
	else if (tipo == "DISCONNECT") {
	  desconecta(usuarioActual, socketcliente);
	  //close(socketcliente);
	  return;
	}
	else{
	  json j;
	  j["type"] = "RESPONSE";
	  j["operation"] = "INVALID";
	  j["result"] = "INVALID";
	  string mensaje = j.dump() + "\n";
	  enviaaUsuario(usuarioActual, mensaje);
	  desconecta(usuarioActual, socketcliente);
	}
	b.construyeBitacora(usuarioActual, tipo);
      }      
      catch (const json::exception& e) {
	json j;
	j["type"] = "RESPONSE";
	j["operation"] = "INVALID";
	j["result"] = "INVALID";
	string mensaje = j.dump() + "\n";
	enviaaUsuario(usuarioActual, mensaje);
	desconecta(usuarioActual, socketcliente);
	cerr << mensaje << e.what()<< endl;
      }
    }
  }
  if (!usuarioActual.empty()) {
    desconecta(usuarioActual, socketcliente);
  }
  close(socketcliente);
}

void Servidor::sirve(){
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlength = sizeof(address);
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket");
    return ;
  }
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(puerto);
  if (bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0) {
    perror("bind");
    close(server_fd);
    return ;
  }
  if (listen(server_fd, 10) < 0) {
    perror("listen");
    close(server_fd);
    return ;
  }
  printf("Servidor escuchando en puerto %d\n", puerto);
  while(continuaEjecucion) {
    int client_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlength);
    if (client_socket < 0) {
      perror("accept");
      continue;
    }
    thread client_thread(&Servidor::leeCliente,this,client_socket);
    client_thread.detach();
  }
  close(server_fd);
  return ;
}  
