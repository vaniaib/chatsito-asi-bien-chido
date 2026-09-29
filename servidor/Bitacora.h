#ifndef BITACORA_H
#define BITACORA_H

#include <bits/stdc++.h>
using namespace std;

class Bitacora{
  
private:  
  string prefijo = "|=|";
  
public:
  Bitacora(){};
  void  construyeBitacora(const string& usuario, const string& msj);
  string fechayhora();
  
};

#endif
