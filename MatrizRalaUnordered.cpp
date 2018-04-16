#include <cassert>
#include <cmath>

#include "MatrizRalaUnordered.h"
#include "constantes.h"

MatrizRalaUnordered::MatrizRalaUnordered(unsigned int rows, unsigned int cols) {
    this->initialize(rows, cols);
    this->_matriz = matRalaU(rows, mapDatoU(cols / 10));
}

MatrizRalaUnordered::MatrizRalaUnordered(unsigned int rows, unsigned int cols, double valorInicial) {
    this->initialize(rows, cols);
    this->_matriz = matRalaU(rows, mapDatoU());
}

MatrizRalaUnordered::~MatrizRalaUnordered() {
}

double MatrizRalaUnordered::get(unsigned int i, unsigned int j) const {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    try {
        return this->_matriz[i - 1].at(j);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Matriz& MatrizRalaUnordered::set(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    if (fabs(valor) >= epsilon) {
        this->_matriz[i - 1][j] = valor;
    } else {
        this->_matriz[i - 1].erase(j);
    }
    return *this;
}

Matriz& MatrizRalaUnordered::operator+(const Matriz& mat) {
    return Matriz::operator+(mat);
}

MatrizRalaUnordered& MatrizRalaUnordered::operator+(const MatrizRalaUnordered& mat) {
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
                this->_matriz[i].insert(parDatoU(elem)); // trato de insertar el elemento en la primera
                //si tiene éxito es porque no estaba en la matriz (corresponde 0+ elem.second)
                //si falla había que sumarlo y eso se hizo en el primer for
            }
        }
    }
    return *this;
}

Matriz& MatrizRalaUnordered::eliminacionGaussiana(vector<double>& v) {
    double m_ij, calculo, ajj, aij;
    mapDatoU::iterator j_it, j_fin, i_it, i_fin, k_it;
    unsigned int k;
    for (unsigned int j = 1; j <= std::min(this->_cols, this->_rows); j++) {
        j_it = this->_matriz[j - 1].begin();
        j_fin = this->_matriz[j - 1].end();
        ajj = this->_matriz[j - 1][j];
        assert(fabs(ajj) >= epsilon); //Se demostró que se puede hacer EG sin problemas entonces debería dar siempre distinto de 0
        for (unsigned int i = j + 1; i <= this->_rows; i++) {//filas por las que voy a ciclar
            i_fin = this->_matriz[i - 1].end();
            i_it = this->_matriz[i - 1].find(j);
            if (i_it != i_fin) {//Encontró un dato en la posicion a_ij entonces es distinto de 0 y debo procesar la fila i
                aij = i_it->second;
                m_ij = aij / ajj;
                k_it = j_it;
                for (k_it = j_it; k_it != j_fin; ++k_it) {//ciclo en todos los elementos no nulos de la fila j
                    k = k_it->first;
                    //                    calculo = this->_matriz[i - 1][k] - m_ij * (k_it->second); //this->_matriz[i-1][k] crea el dato k si no existe la clave
                    //                    if (fabs(calculo) < epsilon) {//lo consideramos 0
                    //                        this->_matriz[i - 1].erase(k);
                    //                    } else {
                    //                        this->_matriz[i - 1][k] = calculo;
                    //                    }
                    i_it = this->_matriz[i - 1].find(k);
                    if (i_it != i_fin) {
                        calculo = (i_it->second) - m_ij * (k_it->second);
                        if (fabs(calculo) < epsilon) {//lo consideramos 0
                            this->_matriz[i - 1].erase(k);
                        } else {
                            this->_matriz[i - 1][k] = calculo;
                        }
                    } else {
                        calculo = -m_ij * (k_it->second);
                        this->_matriz[i - 1].insert(parDatoU(k, calculo));
                    }
                }
                v[i - 1] = v[i - 1] - m_ij * v[j - 1];
            }
        }
    }
    return *this;
}

void MatrizRalaUnordered::backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) {
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

Matriz& MatrizRalaUnordered::multiplicaPorDiagonal(const std::vector<double>& D) {
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& elem : this->_matriz[i]) {
            elem.second *= D[elem.first - 1];
        }
    }
    return *this;
}

Matriz& MatrizRalaUnordered::operator*(double lambda) {
    for (unsigned int i = 0; i < this->_rows; i++) {
        for (auto& elem : this->_matriz[i]) {
            elem.second = elem.second*lambda;
        }
    }
    return *this;
}

double MatrizRalaUnordered::operator()(unsigned int i, unsigned int j) const {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    try {
        return this->_matriz[i - 1].at(j);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Matriz& MatrizRalaUnordered::operator()(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->_rows);
    assert(j <= this->_cols);
    if (fabs(valor) >= epsilon) {
        insertResultU res = this->_matriz[i - 1].insert(parDatoU(j, valor)); //hago una copia del par
        if (res.second == false) {//existe la clave
            res.first->second = valor; //actualizo el valor
        }
    } else {
        this->_matriz[i - 1].erase(j);
    }
    return *this;
}


