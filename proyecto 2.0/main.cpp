#include <iostream>
#include <vector>
#include <chrono>
#include "ventas.h"
#include "csv.h"
#include "estadistica.h"
#include "mod.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// Variables globales
vector<Venta> ventas;
string archivoCSV = "ventas_sudamerica.csv";
int contadorIfs = 0;

// Procesar estadísticas
void procesarEstadisticas() {
    cout << "\n--- Procesando estadisticas ---\n";
    auto start = chrono::high_resolution_clock::now();

    map<string, map<string, double> > montoPorCiudad;
    for (size_t i = 0; i < ventas.size(); ++i) {
        contadorIfs++;
        montoPorCiudad[ventas[i].pais][ventas[i].ciudad] += ventas[i].montoTotal;
    }

    for (map<string, map<string, double> >::iterator it = montoPorCiudad.begin(); it != montoPorCiudad.end(); ++it) {
        string pais = it->first;
        const map<string, double>& ciudades = it->second;
        cout << "Top ciudades en " << pais << ":\n";
        vector<pair<string, double> > vec(ciudades.begin(), ciudades.end());
        sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second > b.second;
        });
        for (int i = 0; i < min(5, (int)vec.size()); ++i)
            cout << " - " << vec[i].first << ": $" << vec[i].second << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\nTiempo de ejecucion: " << duration.count() << " ms\n";
    cout << "Cantidad de condicionales (if): " << contadorIfs << endl;
    contadorIfs = 0;
}


// Menu principal
void mostrarMenu() {
    int opcion;
    do {
        cout << "\n==== Menu Principal ====" << endl;
        cout << "1. Agregar nueva venta" << endl;
        cout << "2. Ver estadisticas" << endl;
        cout << "3. Eliminar venta por ciudad" << endl;
        cout << "4. Eliminar venta por pais" << endl;
        cout << "5. Modificar venta por ID" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
//ejecuta segun la opcion elegida
        switch (opcion) {
            case 1: {
                int nuevoID = obtenerSiguienteID(archivoCSV);
                Venta nueva = cargarVentaDeUsuario(nuevoID);
                ventas.push_back(nueva);
                guardarVentaEnCSV(nueva, archivoCSV);
                cout << "Venta agregada correctamente.\n";
                break;
            }
            case 2:
                {
    int op;
    cout<<"1. Top 5 Ciudades"<<endl;
    cout<<"2. Monto total vendido por producto"<<endl;
    cout<<"3. Promedio por categoria por pais"<<endl;
    cout<<"4. Medio de envio mas utilizado por pais"<<endl;
    cout<<"5. Medio de envio mas utilizado por categoria"<<endl;
    cout<<"6. Dia con mayor cantidad de ventas"<<endl;
    cout<<"7. Estado de envio mas frecuente por pais"<<endl;
    cout<<"8. Producto mas vendido en cantidad total"<<endl;
    cout<<"9. Producto menos vendido en cantidad total"<<endl;
    cout<<"10. Volver al menu principal"<<endl;
    cout<<"Ingrese la estadistica que desea vizualirar"<<endl;
    cin>>op;
    switch (op)
    {
    case 1:
        procesarEstadisticas();
        break;
    
    default:
        break;
    }
 }
                
                break;
            case 3:
                eliminarVentaPorCiudad(ventas);
                break;
            case 4:
                eliminarVentaPorPais(ventas);
                break;
            case 5:
                modificarVentaPorID(ventas);
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);


}
//menu secundario

// carga ventas desde el csv
int main() {
    ventas = leerVentasDesdeCSV(archivoCSV);
    cout << "Se cargaron " << ventas.size() << " ventas desde " << archivoCSV << endl;
    mostrarMenu();
    return 0;
}