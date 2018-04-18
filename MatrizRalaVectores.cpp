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
	if (filita.size() == 0) return 0;
	for (fila::iterator it = filita.begin(); it != filita.end(); ++it)
		cout << " puntero: " << &it << endl;
	return 0;

}

Matriz& MatrizRalaVectores::set(unsigned int i, unsigned int j, double valor) {
	assert(i <= this->_rows);
	assert(j <= this->_cols);
	pair<int, double> nuevo(j - 1, valor);
	fila::iterator it;
	if (this->_matriz[i - 1].size() == 0 && valor != 0) {
		this->_matriz[i - 1].push_back(nuevo);
		return *this;
	}
	it = (this->_matriz[i - 1]).begin();
	while (it != (this->_matriz[i - 1]).end() && (*it).first < j - 1) {
		it++;
	}
	if (valor != 0) {
		if ((*it).first == j - 1) {
			(*it).second = valor;
		}
		if ((*it).first > j - 1) {
			(this->_matriz[i - 1]).insert(it, nuevo);
		}
		if ((*it).first < j - 1) {
			(this->_matriz[i - 1]).push_back(nuevo);
		}
	} else {
		if ((*it).first == j - 1) {
			(this->_matriz[i - 1]).erase(it);
		}
	}
	return *this;
}

Matriz& MatrizRalaVectores::operator+(const Matriz& mat) {
	return Matriz::operator+(mat);
}

Matriz& MatrizRalaVectores::eliminacionGaussiana(vector<double>& v) {
	cout << *this << endl;
	double m_ij, calculo, ajj, aij;
	vector<fila>::iterator iteradorFila1, iteradorFila2;
	vector<fila>::iterator fin_i = this->_matriz.end();
	fila::iterator iteradorColumna1, iteradorColumna2, muerto;

	fin_i--; //hasta n-1
	int i = 0, j = 0;

	pair<int, double> nuevodato;
	bool terminofila1, terminofila2;
	for (iteradorFila1 = this->_matriz.begin(); iteradorFila1 != fin_i; ++iteradorFila1) {

		ajj = (*(*iteradorFila1).begin()).second;
		cout << *this << endl;
		//assert((*(*iteradorFila1).begin()).first == i); //el primer elemento de la fila debe ser el de la diagonal
		if ((*((*iteradorFila1).begin())).first != i) {

			exit(3);
		}
		assert(fabs(ajj) >= epsilon); //Se demostró que se puede hacer EG sin problemas entonces debería dar siempre distinto de 0
		iteradorFila2 = iteradorFila1;
		iteradorFila2++;
		j = i + 1;
		while (iteradorFila2 != this->_matriz.end()) {//filas por las que voy a ciclar

			iteradorColumna1 = (*iteradorFila1).begin(); //vale fila1.begin()
			iteradorColumna2 = (*iteradorFila2).begin(); //vale fila2.begin()

			//cout << "averiguo si tengo que mirar la fila" << endl;
			if ((*iteradorColumna1).first == (*iteradorColumna2).first) {//Encontró un dato en la posicion a_ij entonces es distinto de 0 y debo procesar la fila i
				aij = iteradorColumna2->second;
				m_ij = aij / ajj;
				terminofila2 = false;
				if ((*iteradorFila2).size() == 0) {
					terminofila2 = true;
				}
				for (iteradorColumna1 = (*iteradorFila1).begin(); iteradorColumna1 != (*iteradorFila1).end(); ++iteradorColumna1) {
					calculo = -m_ij * (*iteradorColumna1).second;
					nuevodato = pair<int, double>((*iteradorColumna1).first, calculo);
					if (!terminofila2) {
						while ((*iteradorColumna2).first < (*iteradorColumna1).first && iteradorColumna2 != (*iteradorFila2).end()) {
							iteradorColumna2++;
						}
						if ((*iteradorColumna2).first == (*iteradorColumna1).first) {
							(*iteradorColumna2).second = (*iteradorColumna2).second + calculo;

						}
						if ((*iteradorColumna2).first < (*iteradorColumna1).first) {
							(*iteradorFila2).insert(iteradorColumna2, nuevodato);
						}
						if ((*iteradorColumna2).first > (*iteradorColumna1).first) {
							(*iteradorFila2).push_back(nuevodato);
							terminofila2 = true;
						}
						if (fabs((*iteradorColumna2).second) < epsilon) {
							muerto = iteradorColumna2;
							if (iteradorColumna2 == (*iteradorFila2).end()) {
								terminofila2 = true;
							} else {
								iteradorColumna2++;
							}
							(*iteradorFila2).erase(muerto);
						}
					} else {
						(*iteradorFila2).push_back(nuevodato);
					}
				}

				v[i] = v[i] - m_ij * v[j];

			}
			//cout << "termine la fila" << endl;

			iteradorFila2++;
			j++;

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

Matriz& MatrizRalaVectores::multiplicaPorDiagonal(const std::vector<double>& D) {
	cout << *this << endl;
	for (unsigned int i = 0; i < this->_rows; i++) {
		cout << D[i] << " ";
	}
	cout << endl;
	for (unsigned int i = 0; i < this->_rows; i++) {
		for (fila::iterator it = _matriz[i].begin(); it != _matriz[i].end(); ++it) {
			(*it).second = (*it).second * D[(*it).first];
		}
	}
	cout << *this << endl;
	return *this;
}

Matriz& MatrizRalaVectores::operator*(double lambda) {
	for (unsigned int i = 0; i < this->_rows; i++) {
		for (fila::iterator it = _matriz[i].begin(); it != _matriz[i].end(); ++it) {
			(*it).second = (*it).second * lambda;
		}
	}
	return *this;
}

double MatrizRalaVectores::operator()(unsigned int i, unsigned int j) const {
	return this->get(i, j);
}

Matriz& MatrizRalaVectores::operator()(unsigned int i, unsigned int j, double valor) {

	return this->set(i, j, valor);
}

int MatrizRalaVectores::paso(int x, int y) {
	int ret;
	if (x == y) {
		ret = 0;
	} else {
		ret = ((x - y) / fabs(x - y));
	}
	return ret;
}