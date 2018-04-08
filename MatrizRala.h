#ifndef MATRIZRALA_H
#define MATRIZRALA_H

#include <tuple>
#include <vector>
#include <map>
#include "Matriz.h"

using namespace std;

typedef map<int,double> mapDato;
typedef vector<mapDato> matRala;
typedef pair<int,double> parDato;
typedef pair<mapDato::iterator,bool> insertResult;

class MatrizRala : public Matriz{
public:
    MatrizRala(unsigned int rows, unsigned int cols);
    MatrizRala(unsigned int rows, unsigned int cols, double valorInicial);
    MatrizRala(const MatrizRala& orig);
    virtual ~MatrizRala();
    double get(unsigned int i, unsigned int j) const override;
    Matriz& set(unsigned int i, unsigned int j, double valor) override;
    Matriz& operator +(const Matriz& mat) override;
    MatrizRala& operator +(const MatrizRala& mat);
    Matriz& eliminacionGaussiana(vector<double>& v) override;
    void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) override;
    Matriz& multiplicaPorDiagonal(const std::vector<double>& D) override;
    Matriz& operator*(double lambda) override;
    double operator()(unsigned int i, unsigned int j) const override;
    Matriz& operator()(unsigned int i, unsigned int j, double valor) override;
protected:
    matRala _matriz;
private:

};

#endif /* MATRIZRALA_H */

