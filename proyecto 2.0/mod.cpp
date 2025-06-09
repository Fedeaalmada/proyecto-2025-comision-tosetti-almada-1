
#include "mod.h"
#include <iostream>
#include <algorithm>

using namespace std;
//modifica el vector de ventas en la memoria 

//usa indices para mapear las posciones real
void eliminarVentaPorCiudad(vector<Venta>& ventas) {
    string ciudad;
    cin.ignore();
    cout << "Ingrese la ciudad para filtrar ventas: ";
    getline(cin, ciudad);

    vector<int> indices;
    for (size_t i = 0; i < ventas.size(); ++i) {
        if (ventas[i].ciudad == ciudad) {
            indices.push_back(i);
            cout << indices.size() - 1 << ". " << ventas[i].producto << " | " << ventas[i].cliente << " | $" << ventas[i].montoTotal << endl;
        }
    }

    if (indices.empty()) {
        cout << "No se encontraron ventas en la ciudad especificada." << endl;
        return;
    }

    int opcion;
    cout << "Seleccione el numero de la venta a eliminar: ";
    cin >> opcion;

    if (opcion >= 0 && opcion < indices.size()) {
        int realIndex = indices[opcion];
        ventas.erase(ventas.begin() + realIndex);
        cout << "Venta eliminada correctamente." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}
// igual al de arriba pero filtra por pais 
void eliminarVentaPorPais(vector<Venta>& ventas) {
    string pais;
    cin.ignore();
    cout << "Ingrese el pais para filtrar ventas: ";
    getline(cin, pais);

    vector<int> indices;
    for (size_t i = 0; i < ventas.size(); ++i) {
        if (ventas[i].pais == pais) {
            indices.push_back(i);
            cout << indices.size() - 1 << ". " << ventas[i].producto << " | " << ventas[i].ciudad << " | $" << ventas[i].montoTotal << endl;
        }
    }

    if (indices.empty()) {
        cout << "No se encontraron ventas en el pais especificado." << endl;
        return;
    }

    int opcion;
    cout << "Seleccione el número de la venta a eliminar: ";
    cin >> opcion;

    if (opcion >= 0 && opcion < indices.size()) {
        int realIndex = indices[opcion];
        ventas.erase(ventas.begin() + realIndex);
        cout << "Venta eliminada correctamente." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}
//busca las ventas por el id 
void modificarVentaPorID(vector<Venta>& ventas) {
    int id;
    cout << "Ingrese el ID de la venta que desea modificar: ";
    cin >> id;

    auto it = find_if(ventas.begin(), ventas.end(), [id](const Venta& v) {
        return v.idVenta == id;
    });

    if (it == ventas.end()) {
        cout << "Venta no encontrada con ese ID." << endl;
        return;
    }

    Venta& v = *it;
    cin.ignore();
    cout << "Modificando venta ID " << v.idVenta << ":\n";
    cout << "Fecha actual: " << v.fecha << " | Nueva: "; getline(cin, v.fecha);
    cout << "Pais actual: " << v.pais << " | Nuevo: "; getline(cin, v.pais);
    cout << "Ciudad actual: " << v.ciudad << " | Nueva: "; getline(cin, v.ciudad);
    cout << "Cliente actual: " << v.cliente << " | Nuevo: "; getline(cin, v.cliente);
    cout << "Producto actual: " << v.producto << " | Nuevo: "; getline(cin, v.producto);
    cout << "Categoria actual: " << v.categoria << " | Nueva: "; getline(cin, v.categoria);
    cout << "Cantidad actual: " << v.cantidad << " | Nueva: "; cin >> v.cantidad;
    cout << "Precio Unitario actual: " << v.precioUnitario << " | Nuevo: "; cin >> v.precioUnitario;
    v.montoTotal = v.cantidad * v.precioUnitario;
    cin.ignore();
    cout << "Medio de Envio actual: " << v.medioEnvio << " | Nuevo: "; getline(cin, v.medioEnvio);
    cout << "Estado de Envio actual: " << v.estadoEnvio << " | Nuevo: "; getline(cin, v.estadoEnvio);

    cout << "Venta modificada correctamente." << endl;
}
