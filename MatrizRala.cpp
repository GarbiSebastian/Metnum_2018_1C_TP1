#include <stdexcept>
#include <cassert>
#include <cmath>
#include "MatrizRala.h"
#include "constantes.h"

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols) : Matriz(rows, cols) {
    this->_matriz = matRala(rows, mapDato());
}

MatrizRala::MatrizRala(unsigned int rows, unsigned int cols, double valorInicial) : Matriz(rows, cols, valorInicial) {
    this->_matriz = matRala(rows, mapDato());
}

MatrizRala::MatrizRala(const MatrizRala& orig) : Matriz(orig) {
    this->_matriz = matRala(this->rowSize(), mapDato());
    insertResult ret;
    for (unsigned int i = 0; i < this->rowSize(); i++) {
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
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    try {
        return this->_matriz[i - 1].at(j);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Matriz& MatrizRala::set(unsigned int i, unsigned int j, double valor) {
    assert(i <= this->rowSize());
    assert(j <= this->colSize());
    if (fabs(valor) >= epsilon) {
        insertResult res = this->_matriz[i - 1].insert(parDato(j, valor)); //hago una copia del par
        if (res.second == false) {//existe la clave
            res.first->second = valor; //actualizo el valor
        }
    }else{
        this->_matriz[i-1].erase(j);
    }
    return *this;
}

Matriz& MatrizRala::operator+(const Matriz& mat) {
    return Matriz::operator+(mat);
}

MatrizRala& MatrizRala::operator+(const MatrizRala& mat) {
    for (unsigned int i = 0; i < this->rowSize(); i++) {
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

Matriz& MatrizRala::eliminacionGaussiana() {
    double m_ij,calculo;
    for(unsigned int j=1; j <= std::min(this->colSize(),this->rowSize()); j++){
        for(unsigned int i = j+1; i <= this->rowSize();i++){
            m_ij = this->get(i,j)/this->get(j,j);
            for (unsigned int k = j; k <= this->colSize(); k++) {
                calculo = this->get(i,k) - m_ij*this->get(j,k);
                this->set(i,k,calculo);
            }
            this->set(i,j,0);
        }
    }
    return *this;
}

