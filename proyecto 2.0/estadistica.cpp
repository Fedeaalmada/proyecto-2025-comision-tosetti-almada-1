#include "estadistica.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;
// mide los ifs y t de ejecuccion con chrono
extern int contadorIfs;

void procesarEstadisticas(const vector<Venta>& ventas) {
    cout << "\n Estadisticas Generales:\n";
    auto start = chrono::high_resolution_clock::now();
//agrupa ventas por pais y ciudad,suma montos y top5
    map<string, map<string, double>> ventasPorCiudad;
    for (const auto& v : ventas) {
        contadorIfs++;
        ventasPorCiudad[v.pais][v.ciudad] += v.montoTotal;
    }
   for (auto it = ventasPorCiudad.begin(); it != ventasPorCiudad.end(); ++it) {
    string pais = it->first;
    const map<string, double>& ciudades = it->second;
    cout << "\n Top ciudades en " << pais << ":\n";
    vector<pair<string, double>> ordenadas(ciudades.begin(), ciudades.end());
    sort(ordenadas.begin(), ordenadas.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });
    for (int i = 0; i < min(5, (int)ordenadas.size()); ++i) {
        cout << "   - " << ordenadas[i].first << ": $" << ordenadas[i].second << endl;
    

    }
}

estadistica_MontoPorProductoPorPais(ventas);
    estadistica_PromedioCategoriaPorPais(ventas);
    estadistica_MedioEnvioPorPais(ventas);
    estadistica_EstadoEnvioFrecuentePorPais(ventas);
    estadistica_ProductoMasMenosVendido(ventas);

    estadistica_MedioEnvioPorCategoria(ventas);
    estadistica_DiaConMasVentas(ventas);

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n Tiempo total: " << dur.count() << " ms | Condicionales (if): " << contadorIfs << endl;
    contadorIfs = 0;
}
//maxelement para el mas usado 
void estadistica_MedioEnvioPorCategoria(const vector<Venta>& ventas) {
    map<string, map<string, int>> medioPorCategoria;
    for (const auto& v : ventas) {
        contadorIfs++;
        medioPorCategoria[v.categoria][v.medioEnvio]++;
    }
    cout << "\n Medio de envio mas utilizado por categoria:\n";
    for (map<string, map<string, int> >::iterator it = medioPorCategoria.begin(); it != medioPorCategoria.end(); ++it) {
    string categoria = it->first;
    const map<string, int>& medios = it->second;

    auto maxIt = max_element(medios.begin(), medios.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });

    cout << "   - " << categoria << ": " << maxIt->first << " (" << maxIt->second << " envíos)" << endl;
}
}
//amontona por fecha, suma total del dia y dia que mas vendio 
void estadistica_DiaConMasVentas(const vector<Venta>& ventas) {
    map<string, double> montoPorFecha;
    for (const auto& v : ventas) {
        contadorIfs++;
        montoPorFecha[v.fecha] += v.montoTotal;
    }
    auto maxIt = max_element(montoPorFecha.begin(), montoPorFecha.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    cout << "\n Dia con mayor monto total de ventas: " << maxIt->first << " con $" << maxIt->second << endl;
}
void estadistica_MontoPorProductoPorPais(const vector<Venta>& ventas) {
    map<string, map<string, double>> datos;
    for (const auto& v : ventas) {
        datos[v.pais][v.producto] += v.montoTotal;
    }

    cout << "\nMonto total vendido por producto por país:\n";
    for (const auto& pais : datos) {
        cout << "País: " << pais.first << endl;
        for (const auto& producto : pais.second) {
            cout << "  - " << producto.first << ": $" << producto.second << endl;
        }
    }
}
void estadistica_PromedioCategoriaPorPais(const vector<Venta>& ventas) {
    map<string, map<string, pair<double, int>>> datos;
    for (const auto& v : ventas) {
        datos[v.pais][v.categoria].first += v.montoTotal;
        datos[v.pais][v.categoria].second++;
    }

    cout << "\nPromedio de ventas por categoría por país:\n";
    for (const auto& pais : datos) {
        cout << "País: " << pais.first << endl;
        for (const auto& categoria : pais.second) {
            double promedio = categoria.second.first / categoria.second.second;
            cout << "  - " << categoria.first << ": $" << promedio << endl;
        }
    }
}
void estadistica_MedioEnvioPorPais(const vector<Venta>& ventas) {
    map<string, map<string, int>> conteo;
    for (const auto& v : ventas) {
        conteo[v.pais][v.medioEnvio]++;
    }

    cout << "\nMedio de envío más utilizado por país:\n";
    for (const auto& pais : conteo) {
        auto maxIt = max_element(pais.second.begin(), pais.second.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });
        cout << "País: " << pais.first << " - " << maxIt->first << " (" << maxIt->second << " envíos)" << endl;
    }
}
void estadistica_EstadoEnvioFrecuentePorPais(const vector<Venta>& ventas) {
    map<string, map<string, int>> estados;
    for (const auto& v : ventas) {
        estados[v.pais][v.estadoEnvio]++;
    }

    cout << "\nEstado de envío más frecuente por país:\n";
    for (const auto& pais : estados) {
        auto maxIt = max_element(pais.second.begin(), pais.second.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });
        cout << "País: " << pais.first << " - " << maxIt->first << " (" << maxIt->second << " veces)" << endl;
    }
}
void estadistica_ProductoMasMenosVendido(const vector<Venta>& ventas) {
    map<string, int> cantidades;
    for (const auto& v : ventas) {
        cantidades[v.producto] += v.cantidad;
    }

    auto maxIt = max_element(cantidades.begin(), cantidades.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    auto minIt = min_element(cantidades.begin(), cantidades.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    cout << "\nProducto más vendido en unidades: " << maxIt->first << " (" << maxIt->second << " unidades)" << endl;
    cout << "Producto menos vendido en unidades: " << minIt->first << " (" << minIt->second << " unidades)" << endl;
}
