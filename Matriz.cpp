#include "Matriz.h"
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <math.h>
#include <vector>

using namespace std;

void Matriz::initialize(unsigned int rows, unsigned int cols) {
    this->_rows=rows;
    this->_cols=cols;
}


unsigned int Matriz::colSize() const{
    return this->_cols;
}

unsigned int Matriz::rowSize() const{
    return this->_rows;
}

Matriz& Matriz::operator+(const Matriz& m2) {
    assert(this->colSize() == m2.colSize());
    assert(this->rowSize() == m2.rowSize());
    for (unsigned int i = 1; i <= this->rowSize(); i++) {
        for (unsigned int j = 1; j <= m2.colSize(); j++) {
            double suma = this->get(i, j) + m2.get(i, j);
            this->set(i, j, suma);
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