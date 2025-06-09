#include "csv.h"
#include <fstream>
#include <sstream>
#include <iostream>
//lee el archivo csv, y extrae cada dato, convierte strings en enteros 
vector<Venta> leerVentasDesdeCSV(const string& nombreArchivo) {
    vector<Venta> ventas; //para poder usar pushback despues en el vector 
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << " No se pudo abrir el archivo: " << nombreArchivo << endl;
        return ventas;
    }
    string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        Venta v;
        getline(ss, campo, ','); v.idVenta = stoi(campo);
        getline(ss, v.fecha, ',');
        getline(ss, v.pais, ',');
        getline(ss, v.ciudad, ',');
        getline(ss, v.cliente, ',');
        getline(ss, v.producto, ',');
        getline(ss, v.categoria, ',');
        getline(ss, campo, ','); v.cantidad = stoi(campo);
        getline(ss, campo, ','); v.precioUnitario = stod(campo);
        getline(ss, campo, ','); v.montoTotal = stod(campo);
        getline(ss, v.medioEnvio, ',');
        getline(ss, v.estadoEnvio, ',');
        ventas.push_back(v);
    }
    return ventas;
}
//nuevas ventas al archivo
void guardarVentaEnCSV(const Venta& v, const string& archivoCSV) {
    ofstream archivo(archivoCSV, ios::app);
    if (archivo.is_open()) {
        archivo << v.idVenta << "," << v.fecha << "," << v.pais << "," << v.ciudad << ","
                << v.cliente << "," << v.producto << "," << v.categoria << ","
                << v.cantidad << "," << v.precioUnitario << "," << v.montoTotal << ","
                << v.medioEnvio << "," << v.estadoEnvio << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para escritura.";
    }
}