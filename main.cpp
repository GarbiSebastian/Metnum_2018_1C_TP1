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
#include "constantes.h"

using namespace std;

unsigned int n;
unsigned int m;
double p;
vector<double> grados;
vector<double> D;
vector<double> z;

Matriz& parsearEntrada(int argc, char** argv) {
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
    cout << pathEntrada << endl;
    cout << p << endl;
    ifstream archivoDeEntrada;
    archivoDeEntrada.open(pathEntrada.c_str(), ifstream::in);
    archivoDeEntrada >> n;
    archivoDeEntrada >> m;
    cout << n << " " << m << endl;
    static MatrizBasica A(n, n);
    grados = vector<double>(n, 0);
    //    MatrizRala* A = new MatrizRala(n,n);
    unsigned int i, j;
    for (unsigned int _m = 0; _m < m; _m++) {
        archivoDeEntrada >> i;
        archivoDeEntrada >> j;
        grados[i - 1]++;
        A(j, i, 1);
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

void prueba1() {
    n = 10;
    MatrizBasica A1(n, n, 0);
    MatrizBasica A2(n, n, 0);
    MatrizRala B1(n, n, 0);
    MatrizRala B2(n, n, 0);
    MatrizRala B3(n, n, 0);

    for (unsigned int k = 0; k < n * n; k++) {
        unsigned int i = ceil(k / n) + 1;
        unsigned int j = (k % n) + 1;
        A1(i, j, k);
        A2(i, j, -k);
        B1(i, j, k);
        B2(i, j, -k);
    }

    auto start1 = chrono::steady_clock::now();
    A1 + A2;
    auto end1 = chrono::steady_clock::now();
    auto diff1 = end1 - start1;

    auto start2 = chrono::steady_clock::now();
    B1 + B2;
    auto end2 = chrono::steady_clock::now();
    auto diff2 = end2 - start2;

    auto start3 = chrono::steady_clock::now();
    A1 + B2;
    auto end3 = chrono::steady_clock::now();
    auto diff3 = end3 - start3;

    auto start4 = chrono::steady_clock::now();
    B1 + A2;
    auto end4 = chrono::steady_clock::now();
    auto diff4 = end4 - start4;

    cout << "A1+A2 " << chrono::duration <double, milli> (diff1).count() << " ms" << endl;
    cout << "B1+B2 " << chrono::duration <double, milli> (diff2).count() << " ms" << endl;
    cout << "A1+B2 " << chrono::duration <double, milli> (diff3).count() << " ms" << endl;
    cout << "B1+A2 " << chrono::duration <double, milli> (diff4).count() << " ms" << endl;
}

void pruebaBS1() {
    MatrizBasica A(2, 2, 0);
    A(1, 1, 1);
    A(1, 2, 2);
    A(2, 2, 3);
    vector<double> b(2, 0);
    b[0] = 5;
    b[1] = 6;
    vector<double> x(2, 0);
    A.backwardSubstitution(b, x);
    cout << "A: " << endl << A << "b: [ ";
    for (auto elem : b) cout << elem << " ";
    cout << "]" << endl << "x | Ax=b: [ ";
    for (auto elem : x) cout << elem << " ";
    cout << "]" << endl << endl;
}

void pruebaBS2() {
    MatrizBasica A(3, 3, 0);
    A(1, 1, 1);
    A(1, 2, 2);
    A(1, 3, 3);
    A(2, 2, 4);
    A(2, 3, 5);
    A(3, 3, 6);
    vector<double> b(3, 0);
    b[0] = 6;
    b[1] = 9;
    b[2] = 6;
    vector<double> x(3, 0);
    A.backwardSubstitution(b, x);
    cout << "A: " << endl << A << "b: [ ";
    for (auto elem : b) cout << elem << " ";
    cout << "]" << endl << "x | Ax=b: [ ";
    for (auto elem : x) cout << elem << " ";
    cout << "]" << endl;
}

void pruebaBS3() {
    MatrizRala A(2, 2, 0);
    A(1, 1, 1);
    A(1, 2, 2);
    A(2, 2, 3);
    vector<double> b(2, 0);
    b[0] = 5;
    b[1] = 6;
    vector<double> x(2, 0);
    A.backwardSubstitution(b, x);
    cout << "A: " << endl << A << "b: [ ";
    for (auto elem : b) cout << elem << " ";
    cout << "]" << endl << "x | Ax=b: [ ";
    for (auto elem : x) cout << elem << " ";
    cout << "]" << endl << endl;
}

void pruebaBS4() {
    MatrizRala A(3, 3, 0);
    A(1, 1, 1);
    A(1, 2, 2);
    A(1, 3, 3);
    A(2, 2, 4);
    A(2, 3, 5);
    A(3, 3, 6);
    vector<double> b(3, 0);
    b[0] = 6;
    b[1] = 9;
    b[2] = 6;
    vector<double> x(3, 0);
    A.backwardSubstitution(b, x);
    cout << "A: " << endl << A << "b: [ ";
    for (auto elem : b) cout << elem << " ";
    cout << "]" << endl << "x | Ax=b: [ ";
    for (auto elem : x) cout << elem << " ";
    cout << "]" << endl;
}

void pruebaBSConTiempo(unsigned int n) {
    MatrizBasica B(n, n);
    MatrizRala R(n, n);
    vector<double> b(n, 1), x(n, 0), y(n, 0);
    unsigned int f = 0;
    for (unsigned int i = 1; i <= n; i++) {
        //Diagonal completa
        f++;
        B(i, i, f);
        R(i, i, f);
        for (unsigned int j = i + 1; j <= n; j++) {
            if (rand() % 100 < 10) { // 90% rala en el triangulo superior
                B(i, j, f);
                R(i, j, f);
            }
            f++;
        }
    }
    clock_t tStart1 = clock();
    B.backwardSubstitution(b,x);
    clock_t tEnd1 = clock();
	double tiempo1 = (double) (tEnd1 - tStart1) / CLOCKS_PER_SEC;
    clock_t tStart2 = clock();
    R.backwardSubstitution(b,y);
    clock_t tEnd2 = clock();
	double tiempo2 = (double) (tEnd2 - tStart2) / CLOCKS_PER_SEC;
    cout << "Para Matrices de " << n << "x" << n << endl;
    cout << "tiempo MatrizBasica: " << tiempo1 << "s" << endl;
    cout << "tiempo MatrizRala: " << tiempo2 << "s" << endl;
    cout << "proporción: " << tiempo1/tiempo2 << endl;
    bool distintos = false;
    for (unsigned int i = 0; i < n; i++) {
        if( fabs(x[i]-y[i]) < epsilon){
            //toto joya
        }else{
            distintos=true;
        }
    }
    if(distintos){
        cout << "resultados diferentes " << endl;
        for (auto elem : x) {
            cout << elem << " ";
        }
        cout << endl;
        for (auto elem : y) {
            cout << elem << " ";
        }

    }
}

int main(int argc, char** argv) {
    //    pruebaBS1();
    //    pruebaBS2();
    //    pruebaBS3();
    //    pruebaBS4();
    //    pruebaBSConTiempo(10000);
    //    exit(0);


    Matriz W = parsearEntrada(argc, argv);
    armarDiagonalyZ();
    vector<double> e(n, 1);
    //Matriz R = W*D;
    string extension = ".out";
    string nombreArchivoSalida = argv[1] + extension;
    cout << nombreArchivoSalida << endl;
    ofstream archivoSalida(nombreArchivoSalida.c_str(), ofstream::out);
    archivoSalida << p << endl;
    for (unsigned int i = 1; i <= n; i++) {
        archivoSalida << "algo" << endl;
    }
    return 0;
}

