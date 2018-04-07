#ifndef MATRIZRALA_H
#define MATRIZRALA_H

#include <tuple>
#include <vector>
#include <map>
#include "Matriz.h"

typedef std::map<int,double> mapDato;
typedef std::vector<mapDato> matRala;
typedef std::pair<int,double> parDato;
typedef std::pair<mapDato::iterator,bool> insertResult;

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
    Matriz& eliminacionGaussiana() override;
protected:
    matRala _matriz;
private:

};

#endif /* MATRIZRALA_H */

