#include <stdexcept>
#include <cassert>
#include "MatrizBasica.h"
#include "Matriz.h"
#include "constantes.h"
#include <vector>
#include <complex>

using namespace std;

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols) {
    this->initialize(rows, cols);
    this->_matriz = matBas(rows, vectorBas(cols, 0.0));
}

MatrizBasica::MatrizBasica(unsigned int rows, unsigned int cols, double valorInicial) {
    this->initialize(rows, cols);
    this->_matriz = matBas(rows, vectorBas(cols, valorInicial));
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
    double m_ij, calculo, a_ij, a_jj;
    unsigned int cols = this->_cols, rows = this->_rows;

    for (unsigned int j = 0; j < cols; j++) {
        //        cout << endl << j << endl << *this << endl;
        a_jj = this->_matriz[j][j];
        for (unsigned int i = j + 1; i < rows; i++) {
            a_ij = this->_matriz[i][j];
            if (fabs(a_ij) > epsilon) {//if a_ij != 0
                m_ij = a_ij / a_jj;
                for (unsigned int k = j; k < cols; k++) {
                    calculo = this->_matriz[i][k] - m_ij * this->_matriz[j][k];
                    this->_matriz[i][k] = calculo;
                    //this->set(i, k, calculo);
                }
                this->_matriz[i][j] = 0;
                //                this->set(i, j, 0);
                //                v[i - 1] = v[i - 1] - m_ij * v[j - 1];
                v[i] = v[i] - m_ij * v[j];
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
            this->_matriz[i][j] = this->_matriz[i][j] * lambda;
        }
    }
    return *this;
}

Matriz& MatrizBasica::multiplicaPorDiagonal(const std::vector<double>& D) {
    for (unsigned int i = 0; i < this->rowSize(); i++) {
        for (int j = 0; j < this->colSize(); j++) {
            this->_matriz[i][j] *= D[j];
        }
    }
    return *this;
}

double MatrizBasica::operator()(unsigned int i, unsigned int j) const {
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    return this->_matriz[i - 1][j - 1];
}

Matriz& MatrizBasica::operator()(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    this->_matriz[i - 1][j - 1] = valor;
    return *this;
}
