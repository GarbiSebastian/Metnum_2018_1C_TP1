#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>

class Matriz {
public:
    
    void initialize(unsigned int rows , unsigned int cols);
    unsigned int rowSize() const;
    unsigned int colSize() const;
    
    virtual double get(unsigned int i, unsigned int j) const{std::cout << "get" << std::endl; exit(0);};
    virtual Matriz& set(unsigned int i, unsigned int j, double valor){std::cout << "set" << std::endl; exit(0);};
    
    virtual Matriz& eliminacionGaussiana(std::vector<double>& v){std::cout << "EG" << std::endl; exit(0);};
    virtual void backwardSubstitution(const std::vector<double>& b, std::vector<double>& x){std::cout << "BS" << std::endl; exit(0);};
    
    virtual Matriz& multiplicaPorDiagonal(const std::vector<double>& D){std::cout << "MPD" << std::endl; exit(0);};

    double operator()(unsigned int i, unsigned int j) const; 
    Matriz& operator()(unsigned int i, unsigned int j, double valor);
    virtual Matriz& operator+(const Matriz& m2);
    virtual Matriz& operator*(double lambda){std::cout << "*" << std::endl; exit(0);};
    friend std::ostream& operator<<(std::ostream& os, const Matriz& mat);
    
protected:
    unsigned int _rows;
    unsigned int _cols;
private:
};

#endif /* MATRIZ_H */

