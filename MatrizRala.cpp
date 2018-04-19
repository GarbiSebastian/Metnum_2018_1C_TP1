#include <stdexcept>
#include <cassert>
#include <cmath>
#include "MatrizRala.h"
#include "constantes.h"
#include <vector>
#include <complex>

using namespace std;

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols) {
    this->initialize(rows, cols);
    this->_matriz = matRala(rows, mapDato());
}

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols, double valorInicial) {
    this->initialize(rows, cols);
    this->_matriz = matRala(rows, mapDato());
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
        this->_matriz[i - 1][j] = valor;
        //        insertResult res = this->_matriz[i - 1].insert(parDato(j, valor)); //hago una copia del par
        //        if (res.second == false) {//existe la clave
        //            res.first->second = valor; //actualizo el valor
        //        }
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
    double m_ij, calculo, ajj, aij;
    unsigned int min_row_cols = std::min(this->_cols, this->_rows);
    mapDato::iterator j_it,j_fin,i_it,i_fin,k_it;
    matRala* mat = &(this->_matriz);
    for (unsigned int j = 1; j <= min_row_cols; j++) {
        j_it = (*mat)[j - 1].begin();
        j_fin = (*mat)[j - 1].end();
//        assert((*j_it).first == j);
        //Asumo que se puede hace EG sin pivoteo entonces la diagonal en j debe
        //estar definida y la fila j ya estar triangulada
        ajj = (*j_it).second;
        if (fabs(ajj) < epsilon) throw 4;
        ++j_it;

        for (unsigned int i = j + 1; i <= this->_rows; i++) {
            i_it = (*mat)[i - 1].begin();
            i_fin = (*mat)[i - 1].end();
            //Todas las filas por debajo de la j deberían tener 0 hasta la columna j-1
            //El primer dato de cada una de ellas debe estar como mínimo en la columna j
//            assert((*i_it).first >= j);
            if ((*i_it).first == j) {//La j-esima columna de la fila i no es 0, hay que triangularla
                aij = (*i_it).second;
                m_ij = aij / ajj;
                //seteo 0 en la posicion aij.
                i_it=(*mat)[i - 1].erase(i_it);//Return an iterator to the element that follows the last element removed (or map::end, if the last element was removed).
                k_it = j_it;
                while (k_it != j_fin) {
                    int k = (*k_it).first;
                    while (i_it != i_fin && (*i_it).first < k) {
                        ++i_it; //avanzo el iterador hasta una posición que se vaya a modificar
                    }
                    if (i_it!=i_fin && (*i_it).first == k) {//había un dato en la posición aik
                        calculo = (*i_it).second - m_ij * (*k_it).second;
                        if (fabs(calculo) < epsilon) {
                            i_it = (*mat)[i - 1].erase(i_it);
                        } else {
                            (*i_it).second = calculo;
                        }
                    } else {//el iterador se pasó de largo
                        calculo = -m_ij * (*k_it).second; // m_ij != 0 , (*k_it).second != 0 => calculo != 0
                        (*mat)[i-1].insert(i_it,parDato(k,calculo));//The function optimizes its insertion time if position points to the element that will follow the inserted element (or to the end, if it would be the last).
                    }
                    ++k_it;
                }
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

