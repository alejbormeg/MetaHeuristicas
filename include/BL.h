
#ifndef BL
#define BL

#include <vector>
#include "utilidades.h"

std::vector<double> inicializacionBL(int dim);
void Mov(std::vector<double>& w,double sigma,int pos);

template <typename T>
void BusquedaLocal(std::vector<std::pair<std::vector<double>,T>> &datos,std::vector<double>w){
    
}

#endif
