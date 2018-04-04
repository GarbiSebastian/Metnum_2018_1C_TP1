#ifndef MATRIZBASICA_H
#define MATRIZBASICA_H

#include <vector>
#include "Matriz.h"

typedef std::vector<double> vectorBas;
typedef std::vector<vectorBas> matBas;

class MatrizBasica : public Matriz {
public:
    MatrizBasica(unsigned int rows, unsigned int cols);
    MatrizBasica(unsigned int rows, unsigned int cols, double valorInicial);
    MatrizBasica(const MatrizBasica& orig);
    virtual ~MatrizBasica();
    double get(unsigned int i, unsigned int j) const override;
    Matriz& set(unsigned int i, unsigned int j, double valor) override;
protected:
    matBas _matriz;
private:

};

#endif /* MATRIZBASICA_H */

