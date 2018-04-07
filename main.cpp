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
    double uno_sobre_n = 1/n;
    double uno_menos_p_sobre_n = uno_menos_p/n;
    for (unsigned int k = 0; k < n; k++) {
        if( grados[k] == 0){
            D[k] = 0;
            z[k] = uno_sobre_n;
        }else{
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

void pruebasEliminacionGaussiana() {
    
    //MatrizBasica mat(3, 3);
    MatrizRala mat(3, 3);
    mat(1,1,1);
    mat(1,2,2);
    mat(1,3,3);
    mat(2,1,4);
    mat(2,2,5);
    mat(2,3,6);
    mat(3,1,7);
    mat(3,2,8);
    mat(3,3,5);
    vector<double> v(3, 1);   
    
    /*
    //MatrizBasica mat(4, 4);
    MatrizRala mat(4, 4);
    mat(1,1,1);
    mat(1,2,0);
    mat(1,3,0);
    mat(1,4,3);
    mat(2,1,2);
    mat(2,2,1);
    mat(2,3,0);
    mat(2,4,0);
    mat(3,1,0);
    mat(3,2,3);
    mat(3,3,1);
    mat(3,4,0);
    mat(4,1,0);
    mat(4,2,5);
    mat(4,3,0);
    mat(4,4,1);
    vector<double> v(4, 1);   
    
    MatrizBasica mat(4, 4);
    mat(1,1,1);
    mat(1,2,2);
    mat(1,3,3);
    mat(1,4,4);
    mat(2,1,5);
    mat(2,2,6);
    mat(2,3,7);
    mat(2,4,8);
    mat(3,1,9);
    mat(3,2,10);
    mat(3,3,11);
    mat(3,4,12);
    mat(4,1,13);
    mat(4,2,14);
    mat(4,3,15);
    mat(4,4,16);
    vector<double> v(4, 1);   
    */
    cout << "Matriz: " << endl;
    cout << mat;
    cout << "Vector: " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " \t";
    }
    cout << endl;
    mat.eliminacionGaussiana(v);
    cout << "Eliminacion Gaussiana" << endl;
    cout << "Matriz: " << endl;
    cout << mat;
    cout << "Vector: " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " \t";
    }
    cout << endl;
    system("Pause");
}



int main(int argc, char** argv) {
    pruebasEliminacionGaussiana();
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

