/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MatrizRalaVectores.h
 * Author: panda
 *
 * Created on 16 de abril de 2018, 14:01
 */

#ifndef MATRIZRALAVECTORES_H
#define MATRIZRALAVECTORES_H

#include <vector>
#include "Matriz.h"
#include "constantes.h"
#include "cassert"
#include "list"
#include "vector"

using namespace std;

typedef list<pair<int, double> > fila;

class MatrizRalaVectores : public Matriz {
public:
public:
	MatrizRalaVectores(unsigned int rows, unsigned int cols);
	MatrizRalaVectores(unsigned int rows, unsigned int cols, double valorInicial);
	virtual ~MatrizRalaVectores();
	double get(unsigned int i, unsigned int j) const override;
	Matriz& set(unsigned int i, unsigned int j, double valor) override;
	Matriz& operator+(const Matriz& mat) override;

	Matriz& eliminacionGaussiana(vector<double>& v) override;
	void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) override;
	/*Matriz& multiplicaPorDiagonal(const std::vector<double>& D) override;
	Matriz& operator*(double lambda) override;*/
	double operator()(unsigned int i, unsigned int j) const override;
	Matriz& operator()(unsigned int i, unsigned int j, double valor) override;
private:
	vector<fila> _matriz;
};

#endif /* MATRIZRALAVECTORES_H */

