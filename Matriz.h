#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>

class Matriz {
public:
    Matriz(unsigned int rows, unsigned int cols);
    Matriz(unsigned int rows, unsigned int cols,double valorInicial);
    Matriz(const Matriz& orig);
    virtual ~Matriz();
    unsigned int rowSize() const;
    unsigned int colSize() const;
    
    virtual double get(unsigned int i, unsigned int j) const;
    virtual Matriz& set(unsigned int i, unsigned int j, double valor);
    
    virtual Matriz& eliminacionGaussiana(std::vector<double>& v);
    virtual void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x);
    
    virtual Matriz& multiplicaPorDiagonal(const std::vector<double>& D);

    double operator()(unsigned int i, unsigned int j) const; 
    Matriz& operator()(unsigned int i, unsigned int j, double valor);
    virtual Matriz& operator+(const Matriz& m2);
    virtual Matriz& operator*(double lambda);
    friend std::ostream& operator<<(std::ostream& os, const Matriz& mat);
    
protected:
    unsigned int _rows;
    unsigned int _cols;
private:
};

#endif /* MATRIZ_H */

