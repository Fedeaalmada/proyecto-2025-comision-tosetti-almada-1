
#ifndef ESTADISTICA_H
#define ESTADISTICA_H

#include "ventas.h"
#include <vector>
//estadisticas del codigo, mejor explicado en el cpp
void procesarEstadisticas(const std::vector<Venta>& ventas);
void estadistica_MedioEnvioPorCategoria(const std::vector<Venta>& ventas);
void estadistica_DiaConMasVentas(const std::vector<Venta>& ventas);
void estadistica_MontoPorProductoPorPais(const vector<Venta>& ventas);
void estadistica_PromedioCategoriaPorPais(const vector<Venta>& ventas);
void estadistica_MedioEnvioPorPais(const vector<Venta>& ventas);
void estadistica_EstadoEnvioFrecuentePorPais(const vector<Venta>& ventas);
void estadistica_ProductoMasMenosVendido(const vector<Venta>& ventas);

#endif
