/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MatrizRalaVectores.cpp
 * Author: panda
 *
 * Created on 16 de abril de 2018, 14:01
 */

#include "MatrizRalaVectores.h"


using namespace std;

MatrizRalaVectores::MatrizRalaVectores(unsigned int rows, unsigned int cols) {
	this->initialize(rows, cols);
	this->_matriz = vector<fila>(rows, list<pair<int, double> >(0, pair<int, double>(0, 0)));
}

MatrizRalaVectores::MatrizRalaVectores(unsigned int rows, unsigned int cols, double valorInicial) {
	this->initialize(rows, cols);
	this->_matriz = vector<fila>(rows, list<pair<int, double> >(0, pair<int, double>(0, valorInicial)));
}

MatrizRalaVectores::~MatrizRalaVectores() {
}

double MatrizRalaVectores::get(unsigned int i, unsigned int j) const {
	assert(i <= this->_rows);
	assert(j <= this->_cols);
	fila filita = this->_matriz[i - 1];
	for (auto it = filita.begin(); it != filita.end(); ++it) {
		if ((*it).first == j) {
			return (*it).second;
		}
	}
	return 0;

}

Matriz& MatrizRalaVectores::set(unsigned int i, unsigned int j, double valor) {
	assert(i <= this->_rows);
	assert(j <= this->_cols);
	;
	fila::iterator it;
	for (it = (this->_matriz[i - 1]).begin(); it != (this->_matriz[i - 1]).end() && (*it).first <= j; ++it);
	if (valor != 0) {
		if ((*it).first == j) {
			(*it).second = valor;
		}
		if ((*it).first > j) {
			(this->_matriz[i - 1]).insert(it, pair<int, double>(j, valor));
		}
		if ((*it).first < j) {
			(this->_matriz[i - 1]).push_back(pair<int, double>(j, valor));
		}
	} else {
		if ((*it).first == j) {
			(this->_matriz[i - 1]).erase(it);
		}
	}


	return *this;
}

Matriz& MatrizRalaVectores::operator+(const Matriz& mat) {
	return Matriz::operator+(mat);
}

Matriz& MatrizRalaVectores::eliminacionGaussiana(vector<double>& v) {
	double m_ij, calculo, ajj, aij;
	fila::iterator j_it, j_fin, i_it, i_fin, k_it;
	unsigned int k;
	for (unsigned int j = 0; j < this->_rows; j++) {
		j_it = this->_matriz[j].begin();
		j_fin = this->_matriz[j].end();
		ajj = this->get(j, j);
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

void MatrizRalaVectores::backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) {
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

/*
Matriz& MatrizRalaVectores::multiplicaPorDiagonal(const std::vector<double>& D) {
	for (unsigned int i = 0; i < this->_rows; i++) {
		for (auto& elem : this->_matriz[i]) {
			elem.second *= D[elem.first - 1];
		}
	}
	return *this;
}

Matriz& MatrizRalaVectores::operator*(double lambda) {
	for (unsigned int i = 0; i < this->_rows; i++) {
		for (auto& elem : this->_matriz[i]) {
			elem.second = elem.second*lambda;
		}
	}
	return *this;
}
 */
double MatrizRalaVectores::operator()(unsigned int i, unsigned int j) const {
	return this->get(i, j);
}

Matriz& MatrizRalaVectores::operator()(unsigned int i, unsigned int j, double valor) {

	return this->set(i, j, valor);
}
