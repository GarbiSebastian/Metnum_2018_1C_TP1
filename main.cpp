#include <cstdlib>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <complex>
#include "MatrizBasica.h"
#include "MatrizRala.h"
#include "MatrizRalaUnordered.h"
//#include "MatrizRalaVectores.h"
#include "constantes.h"

typedef MatrizBasica matriz;
//typedef MatrizRala matriz;
//typedef MatrizRalaUnordered matriz;
//typedef MatrizRalaVectores matriz;

using namespace std;

unsigned int n;
double p;
vector<double> grados;
vector<double> D;
vector<double> z;

void imprimirVector(const vector<double>& x, ostream &os) {
	for (auto elem : x)os << elem << "\t";
	os << endl;
}

Matriz* parsearEntrada(int argc, char** argv) {
	if (argc < 3) {
		cout << "Deben pasarse los parametros 'archivo' y 'probabilidad'" << endl;
		cout << "Parametros Pasados " << argc << endl;
		exit(0);
	}
	string pathEntrada = argv[1];
	p = stod(argv[2]);
	if (p < 0 || p > 1) {
		cout << "La probabilidad debe ser un double positivo entre 0 y 1" << endl;
		exit(0);
	}
	unsigned int i, j, m;
	cout << "Archivo de entrada: " << pathEntrada << endl;
	cout << "Probabilidad de navegante aleatorio: " << p << endl;
	ifstream archivoDeEntrada;
	archivoDeEntrada.open(pathEntrada.c_str(), ifstream::in);
	archivoDeEntrada >> n;
	archivoDeEntrada >> m;
	cout << "Cantidad de páginas: " << n << endl << "Cantidad de links: " << m << endl;
	Matriz* A = new matriz(n, n);
	grados = vector<double>(n, 0);
	for (unsigned int _m = 0; _m < m; _m++) {
		archivoDeEntrada >> i;
		archivoDeEntrada >> j;
		grados[i - 1]++;
		(*A)(j, i, 1);
	}
	return A;
}

void armarDiagonalyZ() {
	D = vector<double>(n, 0);
	z = vector<double>(n, 0);
	double uno_menos_p = 1 - p;
	double uno_sobre_n = 1 / n;
	double uno_menos_p_sobre_n = uno_menos_p / n;
	for (unsigned int k = 0; k < n; k++) {
		if (grados[k] == 0) {
			D[k] = 0;
			z[k] = uno_sobre_n;
		} else {
			D[k] = 1 / grados[k];
			z[k] = uno_menos_p_sobre_n;
		}
	}
}

void calcularIpWD(Matriz* W) {
	W->multiplicaPorDiagonal(D);
	(*W)*(-p);
	double fruta;
	for (unsigned int i = 1; i <= n; i++) {
		fruta = (*W)(i, i);
		(*W)(i, i, fruta + 1);
	}
}

void normalizar(vector<double>& x) {
	double norma = 0;
	for (auto& elem : x) {
		norma += elem;
	}
	for (unsigned int i = 0; i < x.size(); i++) {
		x[i] = x[i] / norma;
	}
}

int main(int argc, char** argv) {
    double tiempo;
    clock_t t_a = clock();
    Matriz* W = parsearEntrada(argc, argv);
    clock_t t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "parseada " << tiempo <<  endl;
    armarDiagonalyZ();
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "diagonal " << tiempo << endl;
    vector<double> e(n, 1);
    vector<double> x(n, 0);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "vectores e y x " << tiempo << endl;
    calcularIpWD(W);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "IpWD " << tiempo << endl;
    W->eliminacionGaussiana(e);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "EG " << tiempo << endl;
    W->backwardSubstitution(e,x);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "BS " << tiempo << endl;
    normalizar(x);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "normalizar " << tiempo << endl;
    string extension = ".out";
    string nombreArchivoSalida = argv[1] + extension;
    cout << "Archivo de salida: " << nombreArchivoSalida << endl;
    ofstream archivoSalida(nombreArchivoSalida.c_str(), ofstream::out);
    archivoSalida << p << endl;
    for (unsigned int i = 0; i < n; i++) {
        archivoSalida << x[i] << endl;
    }
    return 0;
}
