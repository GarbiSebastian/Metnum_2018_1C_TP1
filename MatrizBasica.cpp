#include <stdexcept>
#include <cassert>
#include "MatrizBasica.h"
#include "Matriz.h"
#include <vector>

using namespace std;

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols) {
    this->initialize(rows,cols);
    this->_matriz = matBas(rows, vectorBas(cols, 0.0));
}

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols, double valorInicial) {
    this->initialize(rows,cols);
    this->_matriz = matBas(rows, vectorBas(cols, valorInicial));
}

MatrizBasica::MatrizBasica(const MatrizBasica& orig) {
    unsigned int rows = orig.rowSize(),cols=orig.colSize();
    this->initialize(rows,cols);
    this->_matriz = matBas(this->rowSize(), vectorBas(this->colSize(), 0.0));
    for (unsigned int i = 1; i <= this->rowSize(); i++) {
        for (unsigned int j = 1; j <= this->colSize(); j++) {
            this->set(i, j, orig.get(i, j));
        }
    }
}

MatrizBasica::~MatrizBasica() {
}

double MatrizBasica::get(unsigned int i, unsigned int j) const {
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    return this->_matriz[i - 1][j - 1];
}

Matriz& MatrizBasica::set(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    this->_matriz[i - 1][j - 1] = valor;
    return *this;
}

Matriz& MatrizBasica::eliminacionGaussiana(vector<double>& v) {
    double m_ij,calculo;
    for(unsigned int j=1; j <= this->colSize(); j++){
        for(unsigned int i = j+1; i <= this->rowSize();i++){
            if(this->get(i,j) != 0){
                m_ij = this->get(i,j)/this->get(j,j);
                for (unsigned int k = j; k <= this->colSize(); k++) {
                    calculo = this->get(i,k) - m_ij*this->get(j,k);
                    this->set(i,k,calculo);
                }
                this->set(i,j,0);
                v[i-1] = v[i-1] - m_ij*v[j-1];
            }
        }
    }
    return *this;
}

void MatrizBasica::backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) {
    unsigned int tam = this->colSize();
    double suma_parcial, div;
    for (unsigned int i = tam; i > 0; i--) {
        div = this->get(i, i);
        suma_parcial = 0;
        for (unsigned int j = i + 1; j <= tam; j++) {
            suma_parcial += x[j - 1] * this->get(i, j) / div;
        }
        x[i - 1] = b[i - 1] / div - suma_parcial;
    }
}

Matriz& MatrizBasica::operator*(double lambda) {
    for (unsigned int i = 0; i < this->rowSize(); i++) {
        for (unsigned int j = 0; j < this->colSize(); j++) {
            this->_matriz[i][j]=this->_matriz[i][j]*lambda;
        }
    }
    return *this;
}

Matriz& MatrizBasica::multiplicaPorDiagonal(const std::vector<double>& D) {
    std::cout << "mult basica " <<std::endl;
    for (unsigned int i = 0; i < this->rowSize(); i++) {
        for (int j = 0; j < this->colSize(); j++) {
            this->_matriz[i][j]*= D[j];
        }
    }
    return *this;
}
