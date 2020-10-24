#include <iostream>
#include "matrix.h"

int main() {
	srand(time(NULL));
	std::cout << "2X2 Matrix:" << std::endl;
	Matrix a(2, 2);
	a.fillMatrix();
	Matrix b(2, 2);
	b.fillMatrix();
	std::cout << "Matrix A:" << std::endl;
	a.printMatrix();
	std::cout << "Matrix B:" << std::endl;
	b.printMatrix();
	std::cout << "Multiplication:" << std::endl;
	Matrix c = a * b;
	c.printMatrix();
	std::cout << "Addition:" << std::endl;
	Matrix d = a + b;
	d.printMatrix();
	std::cout << "Subtraction:" << std::endl;
	Matrix e = a - b;
	e.printMatrix();
	std::cout << "Scalar Multiplication:" << std::endl;
	Matrix f = a * 4;
	f.printMatrix();
	std::cout << "Transpose:" << std::endl;
	Matrix g = a.transpose();
	g.printMatrix();
	std::cout << "Inverse:" << std::endl;
	Matrix h = (a * g).inverse();
	h.printMatrix();
	std::cout << std::endl;

	std::cout << "3X3 Matrix:" << std::endl;
        Matrix a2(3, 3);
        a2.fillMatrix();
        Matrix b2(3, 3);
        b2.fillMatrix();
        std::cout << "Matrix A:" << std::endl;
        a2.printMatrix();
        std::cout << "Matrix B:" << std::endl;
        b2.printMatrix();
        std::cout << "Multiplication:" << std::endl;
        Matrix c2 = a2 * b2;
        c2.printMatrix();
        std::cout << "Addition:" << std::endl;
        Matrix d2 = a2 + b2;
        d2.printMatrix();
        std::cout << "Subtraction:" << std::endl;
        Matrix e2 = a2 - b2;
        e2.printMatrix();
        std::cout << "Scalar Multiplication:" << std::endl;
        Matrix f2 = a2 * 4;
        f2.printMatrix();
        std::cout << "Transpose:" << std::endl;
        Matrix g2 = a2.transpose();
        g2.printMatrix();
	std::cout << "Inverse:" << std::endl;
        Matrix h2 = (a2 * g2).inverse();
        h2.printMatrix();
	std::cout << std::endl;

	std::cout << "5X5 Matrix:" << std::endl;
        Matrix a3(5, 5);
        a3.fillMatrix();
        Matrix b3(5, 5);
        b3.fillMatrix();
        std::cout << "Matrix A:" << std::endl;
        a3.printMatrix();
        std::cout << "Matrix B:" << std::endl;
        b3.printMatrix();
        std::cout << "Multiplication:" << std::endl;
        Matrix c3 = a3 * b3;
        c3.printMatrix();
        std::cout << "Addition:" << std::endl;
        Matrix d3 = a3 + b3;
        d3.printMatrix();
        std::cout << "Subtraction:" << std::endl;
        Matrix e3 = a3 - b3;
        e3.printMatrix();
        std::cout << "Scalar Multiplication:" << std::endl;
        Matrix f3 = a3 * 4;
        f3.printMatrix();
        std::cout << "Transpose:" << std::endl;
        Matrix g3 = a3.transpose();
        g3.printMatrix();
	std::cout << "Inverse:" << std::endl;
        Matrix h3 = (a3 * g3).inverse();
        h3.printMatrix();
	std::cout << std::endl;

	std::cout << "10X10 Matrix:" << std::endl;
        Matrix a4(10, 10);
        a4.fillMatrix();
        Matrix b4(10, 10);
        b4.fillMatrix();
        std::cout << "Matrix A:" << std::endl;
        a4.printMatrix();
        std::cout << "Matrix B:" << std::endl;
        b4.printMatrix();
        std::cout << "Multiplication:" << std::endl;
        Matrix c4 = a4 * b4;
        c4.printMatrix();
        std::cout << "Addition:" << std::endl;
        Matrix d4 = a4 + b4;
        d4.printMatrix();
        std::cout << "Subtraction:" << std::endl;
        Matrix e4 = a4 - b4;
        e4.printMatrix();
        std::cout << "Scalar Multiplication:" << std::endl;
        Matrix f4 = a4 * 4;
        f4.printMatrix();
        std::cout << "Transpose:" << std::endl;
        Matrix g4 = a4.transpose();
        g4.printMatrix();
        std::cout << "Inverse:" << std::endl;
        Matrix h4 = (a4 * g4).inverse();
        h4.printMatrix();
	std::cout << std::endl;

	std::cout << "Bonus (Non-Symetric Inverse):" << std::endl;
	Matrix Bonus(3, 3);
	Bonus.fillMatrix();
	if(!Bonus.symTest()) {
		Matrix BonusInv = Bonus.nonSymInv(Bonus);
		Bonus.printMatrix();
		BonusInv.printMatrix();
	}
	std::cout << std::endl;

	std::cout << "Bonus (Non-Singluar):" << std::endl;
	Matrix Bonus2(5, 5);
	Bonus2.fillMatrix();
	Bonus2.printMatrix();
	if(Bonus2.det(Bonus2) == 0) {
		std::cout << "Martrix is singluar" << std::endl;
	}
	else {
		std::cout << "Matrix is non-singular" << std::endl;
	}

	return 0;
}
