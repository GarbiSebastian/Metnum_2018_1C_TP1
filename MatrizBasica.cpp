#include <stdexcept>
#include <cassert>

#include "MatrizBasica.h"
#include "Matriz.h"

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols) : Matriz(rows,cols){
    this->_matriz = matBas(rows,vectorBas(cols,0.0));
}

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols, double valorInicial) : Matriz(rows,cols,valorInicial){
    this->_matriz = matBas(rows,vectorBas(cols,valorInicial));
}

MatrizBasica::MatrizBasica(const MatrizBasica& orig) : Matriz(orig){
    this->_matriz = matBas(this->rowSize(),vectorBas(this->colSize(),0.0));
    for (unsigned int i = 1; i <= this->rowSize(); i++) {
        for (unsigned int j = 1; j <= this->colSize(); j++) {
            this->set(i,j,orig.get(i,j));
        }
    }
}

MatrizBasica::~MatrizBasica() {
}

double MatrizBasica::get(unsigned int i, unsigned int j) const{
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    return this->_matriz[i-1][j-1];
}

Matriz& MatrizBasica::set(unsigned int i, unsigned int j, double valor){
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    this->_matriz[i-1][j-1]= valor;
    return *this;
}
