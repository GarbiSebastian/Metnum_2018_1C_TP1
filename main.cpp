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

//typedef MatrizBasica matriz;
typedef MatrizRala matriz;
using namespace std;

unsigned int n;
double p;
vector<double> grados;
vector<double> D;
vector<double> z;

void imprimirVector(const vector<double>& x, ostream &os){
    for (auto elem : x)os << elem << "\t"; os << endl;
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
    cout << "Probabilidad de navegante aleatorio: "<< p << endl;
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

void calcularIpWD(Matriz* W){
    double valor;
    W->multiplicaPorDiagonal(D);
    (*W)*(-p);
    for (unsigned int i = 1; i <= n; i++) {
        (*W)(i,i,(*W)(i,i)+1);
    }
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

void pruebaBS5(){
    
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

void pruebaMultiplicaPorDiagonal(){
    unsigned int mi_n = 3;
    MatrizBasica A(mi_n,mi_n);
    MatrizRala   B(mi_n,mi_n);
    unsigned int k=1;
    for (int i = 0; i < mi_n; i++) {
        for (int j = 0; j < mi_n; j++) {
            A(i+1,j+1,k);
            B(i+1,j+1,k);
            k++;
        }
    }
    vector<double> D(mi_n,2);
    D[1]=3;
    D[2]=1;
    cout << "Basica " << endl << A.multiplicaPorDiagonal(D) << endl;
    cout << "Rala" << endl << B.multiplicaPorDiagonal(D);
}

void pruebaMultiplicaPorNumero(){
    unsigned int mi_n = 3;
    MatrizBasica A(mi_n,mi_n);
    MatrizRala   B(mi_n,mi_n);
    unsigned int k=1;
    for (int i = 0; i < mi_n; i++) {
        for (int j = 0; j < mi_n; j++) {
            A(i+1,j+1,k);
            B(i+1,j+1,k);
            k++;
        }
    }
    double lambda = -5;
    cout << "Basica " << endl << A*lambda << endl;
    cout << "Rala" << endl << B*lambda << endl;
}

void normalizar(vector<double>& x){
    double norma=0;
    for (auto& elem : x) {
        norma+= elem;
    }
    for (unsigned int i = 0; i < x.size(); i++) {
        x[i]=x[i]/norma;
    }
}

void pruebaNormalizar(){
    vector<double> x(5,1);
    normalizar(x);
    imprimirVector(x,cout);
    x = vector<double>(5,2);
    normalizar(x);
    imprimirVector(x,cout);    
}

int main(int argc, char** argv) {
//    pruebaBS1();
//    pruebaBS2();
//    pruebaBS3();
//    pruebaBS4();
//    exit(0);
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
    cout << "vecotres e y x " << tiempo << endl;
    calcularIpWD(W);
    t_b = clock();
    tiempo = (double) (t_b - t_a) / CLOCKS_PER_SEC;
    t_a = t_b;
    cout << "IpWD " << tiempo << endl;
//    try{    
    W->eliminacionGaussiana(e);
//    }catch(int a){
//        cout << endl << "explota por los aires " << a << endl;exit(0);
//    }
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