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
		if ((*it).first == j - 1) {
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
	for (it = (this->_matriz[i - 1]).begin(); it != (this->_matriz[i - 1]).end() && (*it).first <= j - 1; ++it);
	if (valor != 0) {
		if ((*it).first == j) {
			(*it).second = valor;
		}
		if ((*it).first > j) {
			(this->_matriz[i - 1]).insert(it, pair<int, double>(j - 1, valor));
		}
		if ((*it).first < j) {
			(this->_matriz[i - 1]).push_back(pair<int, double>(j - 1, valor));
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
	vector<fila>::iterator it1_i, it2_i;
	vector<fila>::iterator fin_i = this->_matriz.end();
	fila::iterator it1_j, it2_j, muerto;
	fila fila1_i, fila2_i;
	fin_i--; //hasta n-1
	int i = 0, j = 0;
	fila::iterator fruta;
	pair<int, double> nuevodato;
	bool terminofila1, terminofila2;
	for (it1_i = this->_matriz.begin(); it1_i != fin_i; ++it1_i) {
		fila1_i = (*it1_i);
		ajj = (*(fila1_i.begin())).second;
		fruta = (fila1_i.begin());
		assert((*(fila1_i.begin())).first == i); //el primer elemento de la fila debe ser el de la diagonal
		assert(fabs(ajj) >= epsilon); //Se demostró que se puede hacer EG sin problemas entonces debería dar siempre distinto de 0
		it2_i = it1_i;
		it2_i++;
		j = i + 1;
		while (it2_i != this->_matriz.end()) {//filas por las que voy a ciclar
			fila2_i = (*it2_i);
			it1_j = (*it1_i).begin(); //vale fila1_i.begin()
			it2_j = (*it2_i).begin(); //vale fila2_i.begin()
			if ((*it1_j).first == (*it2_j).first) {//Encontró un dato en la posicion a_ij entonces es distinto de 0 y debo procesar la fila i
				aij = it2_j->second;
				m_ij = aij / ajj;
				terminofila1 = false;
				terminofila2 = false;
				while (!terminofila2 && !terminofila1) {//ciclo en todos los elementos no nulos de la fila j
					cout << "entro" << endl;
					if ((*it1_j).first == (*it2_j).first) {
						cout << "iguales" << endl;
						calculo = it2_j->second - m_ij * (*it1_j).second;
						(*it2_j).second = calculo;
						if (it1_j == fila1_i.end()) {
							terminofila1 = true;
						} else {
							it1_j++;
						}

						if (it2_j == fila2_i.end()) {
							terminofila2 = true;
							if (calculo < epsilon) {
								fila2_i.erase(it2_j);
							}
						} else {
							if (calculo < epsilon) {
								muerto = it2_j;
								it2_j++;
								fila2_i.erase(muerto);
							} else {
								it2_j++;
							}
						}
						continue;
					}

					if ((*it1_j).first > (*it2_j).first) {
						cout << "superior adelantada" << endl;
						if (it2_j == fila2_i.end()) {
							terminofila2 = true;
						} else {
							it2_j++;
						}
						continue;
					}
					if ((*it1_j).first < (*it2_j).first) {
						cout << "superior atrasada" << "   1: " << (*it1_j).first << "   2: " << (*it2_j).first << endl;
						nuevodato = pair<int, double>((*it1_j).first, m_ij * (*it1_j).second);
						fila2_i.insert(it2_j, nuevodato);
						if (it1_j == fila1_i.end()) {
							terminofila1 = true;
						} else {
							it1_j++;
						}
						continue;
					}
				}
				while (!terminofila1) {
					nuevodato = pair<int, double>((*it1_j).first, -m_ij * (*it1_j).second);
					fila2_i.push_back(nuevodato);
					if (it1_j == fila1_i.end()) {
						terminofila1 = true;
					} else {

						it1_j++;
					}
				}
				cout << "termine la fila" << endl;
			}
			v[i] = v[i] - m_ij * v[j];
			j++;
			it2_i++;
		}
		i++;
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
