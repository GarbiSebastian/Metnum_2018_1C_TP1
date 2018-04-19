#ifndef MATRIZRALAUNORDERED_H
#define MATRIZRALAUNORDERED_H

#include <unordered_map>
#include <vector>

#include "Matriz.h"


using namespace std;

typedef unordered_map<int,double> mapDatoU;
typedef vector<mapDatoU> matRalaU;
typedef pair<int,double> parDatoU;
typedef pair<mapDatoU::iterator,bool> insertResultU;

class MatrizRalaUnordered : public Matriz{
public:
    public:
    MatrizRalaUnordered(unsigned int rows, unsigned int cols);
    MatrizRalaUnordered(unsigned int rows, unsigned int cols, double valorInicial);
    virtual ~MatrizRalaUnordered();
    double get(unsigned int i, unsigned int j) const override;
    Matriz& set(unsigned int i, unsigned int j, double valor) override;
    Matriz& operator +(const Matriz& mat) override;
    MatrizRalaUnordered& operator +(const MatrizRalaUnordered& mat);
    Matriz& eliminacionGaussiana(vector<double>& v) override;
    void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x) override;
    Matriz& multiplicaPorDiagonal(const std::vector<double>& D) override;
    Matriz& operator*(double lambda) override;
    double operator()(unsigned int i, unsigned int j) const override;
    Matriz& operator()(unsigned int i, unsigned int j, double valor) override;
protected:
    matRalaU _matriz;
private:

};

#endif /* MATRIZRALAUNORDERED_H */

