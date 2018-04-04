#include "Matriz.h"
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <math.h>

Matriz::Matriz(unsigned int rows, unsigned int cols) {
    this->_rows=rows;
    this->_cols=cols;
}

Matriz::Matriz(unsigned int rows, unsigned int cols, double valorInicial){
    this->_rows=rows;
    this->_cols=cols;
}

Matriz::Matriz(const Matriz& orig) {
    this->_rows=orig.rowSize();
    this->_cols=orig.colSize();
}

Matriz::~Matriz() {
}

double Matriz::get(unsigned int i, unsigned int j) const{
    throw 0;
}

Matriz& Matriz::set(unsigned int i, unsigned int j, double valor) {
    throw 1;
}

unsigned int Matriz::colSize() const{
    return this->_cols;
}

unsigned int Matriz::rowSize() const{
    return this->_rows;
}

//Matriz& operator+(Matriz& m1, const Matriz& m2) {
//    assert(m1.colSize() == m2.colSize());
//    assert(m1.rowSize() == m2.rowSize());
//    for (unsigned int i = 1; i <= m1.rowSize(); i++) {
//        for (unsigned int j = 1; j <= m2.colSize(); j++) {
//            m1.set(i, j, m1.get(i, j) + m2.get(i, j));
//        }
//    }
//    return m1;
//}

Matriz& Matriz::operator+(const Matriz& m2) {
    assert(this->colSize() == m2.colSize());
    assert(this->rowSize() == m2.rowSize());
    for (unsigned int i = 1; i <= this->rowSize(); i++) {
        for (unsigned int j = 1; j <= m2.colSize(); j++) {
            this->set(i, j, this->get(i, j) + m2.get(i, j));
        }
    }
    return *this;
}

std::ostream& operator <<(std::ostream& os, const Matriz& mat){
    for (unsigned int i = 1; i <= mat.rowSize(); i++) {
        for (unsigned int j = 1; j <= mat.colSize(); j++) {
            os << mat.get(i, j) << " \t";
        }
        os << std::endl;
    }
    return os;
}

double Matriz::operator ()(unsigned int i, unsigned int j) const{
    return this->get(i,j);
}

Matriz& Matriz::operator ()(unsigned int i, unsigned int j, double valor){
    this->set(i,j,valor);
    return *this;
}