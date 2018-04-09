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
    double m_ij, calculo, ajj, aij;
    for (unsigned int j = 1; j <= std::min(this->_cols, this->_rows); j++) {
//        cout << j << endl << *this << endl << endl;
        mapDato::iterator j_it = this->_matriz[j - 1].begin();
        mapDato::iterator j_fin = this->_matriz[j - 1].end();
        assert((*j_it).first == j); //Asumo que se puede hace EG sin pivoteo entonces la diagonal en j debe estar definida y para la fila j ya esta
        ajj = (*j_it).second;
        if (ajj == 0) throw 4;
        ++j_it;

        for (unsigned int i = j + 1; i <= this->_rows; i++) {
            mapDato::iterator i_it = this->_matriz[i - 1].begin();
            mapDato::iterator i_fin = this->_matriz[i - 1].end();
            assert((*i_it).first >= j); //todas las filas por debajo de la j deberían tener 0 hasta la posición j-1

            if ((*i_it).first == j) {//la j-esima columna de la fila i no es 0
                aij = (*i_it).second;
                m_ij = aij / ajj;
                i_it=this->_matriz[i - 1].erase(i_it); //seteo 0 en la posicion aij
                mapDato::iterator k_it = j_it;
                while (k_it != j_fin) {
                    //                    cout << (*k_it).first << " " << (*k_it).second << endl;
                    int k = (*k_it).first;
                    while (i_it != i_fin && (*i_it).first < k) {
//                        cout << "i: " << i << " j: " << j << " k: " << k << endl;
                        ++i_it; //avanzo el iterador hasta una posición que se vaya a modificar
                    }
                    if ((*i_it).first == k) {//había un dato en la posición aik
                        calculo = (*i_it).second - m_ij * (*k_it).second;
                        if (fabs(calculo) < epsilon) {
                            i_it = this->_matriz[i - 1].erase(i_it);
                        } else {
                            (*i_it).second = calculo;
                        }
                    } else {
                        calculo = -m_ij * (*k_it).second; // m_ij != 0 , (*k_it).second != 0 => calculo != 0
                        this->set(i, k, calculo);
                    }
                    ++k_it;
                }
            }
            v[i - 1] = v[i - 1] - m_ij * v[j - 1];
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

