#ifndef CSV_H
#define CSV_H
#include "ventas.h"
#include <vector>
#include <string>
using namespace std;
//lee el archivo csv
vector<Venta> leerVentasDesdeCSV(const string& nombreArchivo);
void guardarVentaEnCSV(const Venta& venta, const string& nombreArchivo);

#endif