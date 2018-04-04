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

void parsearEntrada(int argc, char** argv){
    if(argc < 3){
        cout << "Deben pasarse los parametros 'archivo' y 'probabilidad'" <<  endl;
        cout << "Parametros Pasados "<< argc << endl; 
        exit(0);
    }
    string pathEntrada = argv[1];
    p = stod(argv[2]);
    if( p < 0 || p > 1){
        cout << "La probabilidad debe ser un double positivo entre 0 y 1" << endl;
        exit(0);
    }
    cout << pathEntrada << endl;
    cout << p << endl;
    ifstream archivoDeEntrada;
	archivoDeEntrada.open(pathEntrada.c_str(),ifstream::in);
    archivoDeEntrada >> n;
    archivoDeEntrada >> m;
    cout << n << " " << m << endl ;
    MatrizBasica A(n,n,0);
    MatrizRala B(n,n);
    unsigned int i,j;
    for(int _m = 0; _m < m; _m++){
        archivoDeEntrada >> i;
        archivoDeEntrada >> j;
        A(i,j,1);
        B(i,j,1);
    }
}

void prueba1(){
    n = 10;
    MatrizBasica A1(n,n,0);
    MatrizBasica A2(n,n,0);
    MatrizRala B1(n,n,0);
    MatrizRala B2(n,n,0);
    MatrizRala B3(n,n,0);
        
    for(unsigned int k =0; k < n*n;k++ ){
        unsigned int i = ceil(k/n)+1;
        unsigned int j = (k%n)+1;
        A1(i,j,k);
        A2(i,j,-k);
        B1(i,j,k);
        B2(i,j,-k);
    }
    
    auto start1 = chrono::steady_clock::now();
    A1+A2;
    auto end1 = chrono::steady_clock::now();
    auto diff1 = end1 - start1;
    
    auto start2 = chrono::steady_clock::now();
    B1+B2;
    auto end2 = chrono::steady_clock::now();
    auto diff2 = end2 - start2;
    
    auto start3 = chrono::steady_clock::now();
    A1+B2;
    auto end3 = chrono::steady_clock::now();
    auto diff3 = end3 - start3;
    
    auto start4 = chrono::steady_clock::now();
    B1+A2;
    auto end4 = chrono::steady_clock::now();
    auto diff4 = end4 - start4;
    
    cout << "A1+A2 " << chrono::duration <double, milli> (diff1).count() << " ms" << endl;
    cout << "B1+B2 " << chrono::duration <double, milli> (diff2).count() << " ms" << endl;
    cout << "A1+B2 " << chrono::duration <double, milli> (diff3).count() << " ms" << endl;
    cout << "B1+A2 " << chrono::duration <double, milli> (diff4).count() << " ms" << endl;
}

int main(int argc, char** argv) {
    parsearEntrada(argc,argv);
    string extension = ".out";
    string nombreArchivoSalida = argv[1]+extension;
    cout << nombreArchivoSalida << endl; 
    ofstream archivoSalida(nombreArchivoSalida.c_str(),ofstream::out);
    archivoSalida << p << endl;
    for(unsigned int i = 1; i <= n;i++){
        archivoSalida << i << endl;
    }
    return 0;
}

