
#ifndef MOD_H
#define MOD_H

#include "ventas.h"
#include <vector>
#include <string>

using namespace std;

void eliminarVentaPorCiudad(vector<Venta>& ventas);
void eliminarVentaPorPais(vector<Venta>& ventas);
void modificarVentaPorID(vector<Venta>& ventas);  //  faltaba esto

#endif
