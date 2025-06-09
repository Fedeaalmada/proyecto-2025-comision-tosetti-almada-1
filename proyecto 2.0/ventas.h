#ifndef VENTAS_H
#define VENTAS_H

#include <string>
using namespace std;

// Estructura de una venta individual
struct Venta {
    int idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precioUnitario;
    double montoTotal;
    string medioEnvio;
    string estadoEnvio;
};

//  el siguiente ID disponible desde el archivo CSV
int obtenerSiguienteID(const string& archivoCSV);

// Carga datos de una venta nueva ingresada por el usuario
Venta cargarVentaDeUsuario(int idVenta);

#endif
