#include "ventas.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int obtenerSiguienteID(const string& archivoCSV) {
    ifstream archivo(archivoCSV);
    string linea;
    int maxID = 0;
    getline(archivo, linea); // Saltea cabecera
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        int id = stoi(campo);
        if (id > maxID) maxID = id;
    }
    return maxID + 1;
}

Venta cargarVentaDeUsuario(int idVenta) {
    Venta v;
    v.idVenta = idVenta;
    cin.ignore(); // Limpia buffer
    cout << "\n--- Ingreso de nueva venta ---\n";
    cout << "Fecha (DD/MM/AAAA): "; getline(cin, v.fecha);
    cout << "Pais: "; getline(cin, v.pais);
    cout << "Ciudad: "; getline(cin, v.ciudad);
    cout << "Cliente: "; getline(cin, v.cliente);
    cout << "Producto: "; getline(cin, v.producto);
    cout << "Categoria: "; getline(cin, v.categoria);
    cout << "Cantidad: "; cin >> v.cantidad;
    cout << "Precio unitario: "; cin >> v.precioUnitario;
    v.montoTotal = v.cantidad * v.precioUnitario;
    cin.ignore();
    cout << "Medio de envio: "; getline(cin, v.medioEnvio);
    cout << "Estado del envio: "; getline(cin, v.estadoEnvio);

    // Guardar la venta al final del archivo CSV
    ofstream archivo("ventas.csv", ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << v.idVenta << ","
                << v.fecha << ","
                << v.pais << ","
                << v.ciudad << ","
                << v.cliente << ","
                << v.producto << ","
                << v.categoria << ","
                << v.cantidad << ","
                << v.precioUnitario << ","
                << v.montoTotal << ","
                << v.medioEnvio << ","
                << v.estadoEnvio << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para guardar la venta.\n";
    }

    return v;
}
