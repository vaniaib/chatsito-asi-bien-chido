#include<bits/stdc++.h>
#include "Bitacora.h"
using namespace std;

string Bitacora:: fechayhora(){
  time_t tiempoActual = std::time(nullptr);
  tm* localTime = std::localtime(&tiempoActual);  
    char buffer[100];
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", localTime);
    return string(buffer); 
}

void  Bitacora:: construyeBitacora(const string& usuario, const string& msj){

  cout << prefijo << fechayhora() << "[usuario :" << usuario <<"] "<< msj << "\n";
  // string inicio = prefijo;
  // printf(prefijo + fechayhora() +  "[usuario : %s] ", usuario + msj + "\n" );
  //  string u = format("[usuario : %s] ", usuario);
  //  inicio += u;  
  //  inicio += fechayhora();
  //  inicio += msj + "\n";
  }
