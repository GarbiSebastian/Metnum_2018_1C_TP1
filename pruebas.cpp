
#include <cmath>

#include "MatrizBasica.h"
#include "MatrizRala.h"
#include "constantes.h"
#include "funciones.h"
#include <iostream>


typedef unsigned long int clave_t;
using namespace std;

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
void pruebaNormalizar(){
    vector<double> x(5,1);
    normalizar(x);
    imprimirVector(x,cout);
    x = vector<double>(5,2);
    normalizar(x);
    imprimirVector(x,cout);    
}
void pruebaIM_begin(clave_t size){
    double tiempo;
    clave_t j;
    std::map<clave_t, double> m;
    clock_t inicio,fin;
    std::map<clave_t, double>::iterator it = m.begin();
    
    inicio = clock();
    for (clave_t i = 0; i < size; i++) {
        j = size-i;
        it = m.insert(it,std::pair<clave_t, double>(i,i+1));
    }
    fin = clock();
    tiempo = (double) (fin - inicio) / CLOCKS_PER_SEC;
    cout << "tiempo con begin:\t"<< tiempo << endl;
}
void pruebaIM_end(clave_t size){
    double tiempo;
    clave_t j;
    std::map<clave_t, double> m;
    clock_t inicio,fin;
    std::map<clave_t, double>::iterator it = m.end();
    
    inicio = clock();
    for (clave_t i = 0; i < size; i++) {
        j = size-i;
        it= m.insert(it,std::pair<clave_t, double>(i,i+1));
    }
    fin = clock();
    tiempo = (double) (fin - inicio) / CLOCKS_PER_SEC;
    cout << "tiempo con end:  \t"<< tiempo << endl;
}
void pruebaIM_end_mejor(clave_t size){
    double tiempo;
    clave_t j;
    std::map<clave_t, double> m;
    clock_t inicio,fin;
    std::map<clave_t, double>::iterator it = m.end();
    
    inicio = clock();
    for (clave_t i = 0; i < size; i++) {
        j = size-i;
        it = m.insert(it,std::pair<clave_t, double>(j,i+1));
    }
    fin = clock();
    tiempo = (double) (fin - inicio) / CLOCKS_PER_SEC;
    cout << "tiempo con end opt:\t"<< tiempo << endl;
}
void pruebaInsertMap(){
    clave_t size = 10000000;
    pruebaIM_begin(size);
    pruebaIM_end(size);
    pruebaIM_end_mejor(size);
    exit(0);
}
