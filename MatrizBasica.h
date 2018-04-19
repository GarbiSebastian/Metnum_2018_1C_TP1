#ifndef MATRIZBASICA_H
#define MATRIZBASICA_H

#include <vector>
#include "Matriz.h"

using namespace std;

typedef vector<double> vectorBas;
typedef vector<vectorBas> matBas;

class MatrizBasica : public Matriz {
public:
    MatrizBasica(unsigned int rows, unsigned int cols);
    MatrizBasica(unsigned int rows, unsigned int cols, double valorInicial);
    virtual ~MatrizBasica();
    double get(unsigned int i, unsigned int j) const override;
    Matriz& set(unsigned int i, unsigned int j, double valor) override;
    Matriz& eliminacionGaussiana(vector<double>& v) override;
    void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) override;
    Matriz& multiplicaPorDiagonal(const std::vector<double>& D) override;
    Matriz& operator*(double lambda) override;
    double operator()(unsigned int i, unsigned int j) const override;
    Matriz& operator()(unsigned int i, unsigned int j, double valor) override;
protected:
    matBas _matriz;
private:

};

#endif /* MATRIZBASICA_H */

