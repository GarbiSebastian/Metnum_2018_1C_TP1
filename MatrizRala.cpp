#include <stdexcept>
#include <cassert>
#include <cmath>
#include "MatrizRala.h"
#include "constantes.h"
#include <vector>

using namespace std;

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols) {
    this->initialize(rows, cols);
    this->_matriz = matRala(rows, mapDato());
}

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols, double valorInicial) {
    this->initialize(rows, cols);
    this->_matriz = matRala(rows, mapDato());
}

MatrizRala::MatrizRala(const MatrizRala& orig) : Matriz(orig) {
    unsigned int rows = orig.rowSize(), cols = orig.colSize();
    this->initialize(rows, cols);
    this->_matriz = matRala(this->_rows, mapDato());
    insertResult ret;
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& datoOrig : orig._matriz[i]) {
            ret = this->_matriz[i].insert(parDato(datoOrig)); //hago una copia del par
            if (ret.second == false) {//existe la clave
                ret.first->second = datoOrig.second; //actualizo el valor
            }
        }
    }
}

MatrizRala::~MatrizRala() {
}

double MatrizRala::get(unsigned int i, unsigned int j) const {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    try {
        return this->_matriz[i - 1].at(j);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Matriz& MatrizRala::set(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    if (fabs(valor) >= epsilon) {
        insertResult res = this->_matriz[i - 1].insert(parDato(j, valor)); //hago una copia del par
        if (res.second == false) {//existe la clave
            res.first->second = valor; //actualizo el valor
        }
    } else {
        this->_matriz[i - 1].erase(j);
    }
    return *this;
}

Matriz& MatrizRala::operator+(const Matriz& mat) {
    return Matriz::operator+(mat);
}

MatrizRala& MatrizRala::operator+(const MatrizRala& mat) {
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& elem : this->_matriz[i]) {//Sumo los que si estan
            double suma = elem.second + mat(i + 1, elem.first);
            if (fabs(suma) < epsilon) {
                this->_matriz[i].erase(elem.first);
            } else {
                elem.second = suma;
            }
        }
        for (auto& elem : mat._matriz[i]) {//para todos los que estan en la segunda matriz
            if (fabs(elem.second) >= epsilon) {
                this->_matriz[i].insert(parDato(elem)); // trato de insertar el elemento en la primera
                //si tiene éxito es porque no estaba en la matriz (corresponde 0+ elem.second) 
                //si falla había que sumarlo y eso se hizo en el primer for
            }
        }
    }
    return *this;
}

Matriz& MatrizRala::eliminacionGaussiana(vector<double>& v) {
    double m_ij, calculo, valor_j_j, valor_i_j;
    for (unsigned int j = 1; j <= std::min(this->_cols, this->_rows); j++) {
        valor_j_j = this->get(j, j);
        if (valor_j_j == 0) throw 4;

        for (unsigned int i = j + 1; i <= this->_rows; i++) {
            cout << i << " " << j << endl;
            valor_i_j = this->get(i, j);
            if (valor_i_j != 0) {
                m_ij = valor_i_j / valor_j_j;
                for (auto& elem : this->_matriz[j - 1]) {//Le resto uno porque estoy trabajando con la matriz directamente
                    int k = elem.first;
                    calculo = this->get(i, k) - m_ij * elem.second;
                    this->set(i, k, calculo);
                }
                //this->set(i,j,0);//No es necesario hacer esto
                v[i - 1] = v[i - 1] - m_ij * v[j - 1];
            }
        }
    }
    return *this;
}

void MatrizRala::backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) {
    unsigned int tam = this->_cols, j;
    double suma_parcial, div;
    for (unsigned int i = tam; i > 0; i--) {
        div = this->get(i, i);
        if (div == 0) {
            throw 10;
        }
        suma_parcial = 0;
        for (auto elem : this->_matriz[i - 1]) {
            j = elem.first;
            if (j >= i + 1) {
                suma_parcial += x[j - 1]*(elem.second) / div;
            }
        }
        //        for (unsigned int j = i+1; j <= tam; j++) {
        //            suma_parcial += x[j-1]*this->get(i,j)/div;
        //        }
        x[i - 1] = b[i - 1] / div - suma_parcial;
    }
}

Matriz& MatrizRala::multiplicaPorDiagonal(const std::vector<double>& D) {
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& elem : this->_matriz[i]) {
            elem.second *= D[elem.first - 1];
        }
    }
    return *this;
}

Matriz& MatrizRala::operator*(double lambda) {
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& elem : this->_matriz[i]) {
            elem.second = elem.second*lambda;
        }
    }
    return *this;
}

double MatrizRala::operator()(unsigned int i, unsigned int j) const {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    try {
        return this->_matriz[i - 1].at(j);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Matriz& MatrizRala::operator()(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    if (fabs(valor) >= epsilon) {
        insertResult res = this->_matriz[i - 1].insert(parDato(j, valor)); //hago una copia del par
        if (res.second == false) {//existe la clave
            res.first->second = valor; //actualizo el valor
        }
    } else {
        this->_matriz[i - 1].erase(j);
    }
    return *this;
}

