#include <iostream>
#include <fstream>
#include <math.h>
#include "matrix.h"

Matrix::Matrix() {
	rows = 0;
	cols = 0;
}

Matrix::Matrix(long unsigned int i, long unsigned int j) {
	rows = i;
	cols = j;
	mat = newMat();
}

float** Matrix::newMat() const {
	float** nmat = new float*[rows];
	for(int i = 0; i < rows; i++) {
		nmat[i] = new float[cols];
		for(int j = 0; j < cols; j++) {
			nmat[i][j] = 0;
		}
	}
	return nmat;
}

void Matrix::printMatrix() {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

long unsigned int Matrix::getRows() const {
	return rows;
}

long unsigned int Matrix::getCols() const {
	return cols;
}

Matrix Matrix::transpose() {
	Matrix transpose = Matrix(cols, rows);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			transpose.mat[j][i] = mat[i][j];
		}
	}
	return transpose;
}
	
Matrix& Matrix::inverse() {
	if(rows == 1 && cols == 1) {
		if(mat[0][0] != 0) {
			mat[0][0] = 1/mat[0][0];
		}
		return *this;
	}
	int urow = rows;
	int ucol = cols;
	padMatrix();
	int hrow = rows/2;
	int hcol = cols/2;
	Matrix B = Matrix(hrow, hcol);
	Matrix Ct = Matrix(hrow, hcol);
	Matrix C = Matrix(hrow, hcol);
	Matrix D = Matrix(hrow, hcol);
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(i < hrow && j < hcol) {
				B.mat[i][j] = mat[i][j];
			}
			else if(i < hrow && j >= hcol) {
				Ct.mat[i][j - hcol] = mat[i][j];
			}
			else if(i >= hcol && j < hcol) {
				C.mat[i - hrow][j] = mat[i][j];
			}
			else if(i >= hrow && j >= hcol) {
				D.mat[i - hrow][j - hcol] = mat[i][j];
			}
		}
	}
	Matrix invB = B.inverse();
	Matrix W = C * invB;
	Matrix Wt = W.transpose();
	Matrix X = W * Ct;
	Matrix S = D - X;
	Matrix V = S.inverse();
	Matrix Y = V * W;
	Matrix Yt = Y.transpose();
	Matrix L = Yt * -1;
	Matrix U = Y * -1;
	Matrix Z = Wt * Y;
	Matrix R = invB + Z;
	for(int i = 0; i < rows; i++) {
		delete[] mat[i];
	}
	delete[] mat;
	rows = urow;
	cols = ucol;
	mat = newMat();
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(i < hrow && j < hcol) {
				mat[i][j] = R.mat[i][j];
			}
			else if(i < hrow && j >= hcol) {
				mat[i][j] = L.mat[i][j - hcol];
			}
			else if(i >= hcol && j < hcol) {
				mat[i][j] = U.mat[i - hrow][j];
			}
			else if(i >= hrow && j >= hcol) {
				mat[i][j] = V.mat[i - hrow][j - hcol];
			}
		}
	}
	return *this;
}

Matrix& Matrix::padMatrix() {
	int size = 2;
	while((size < rows || size < cols) && size > 0 ){
		size = size * 2; 
	}
	float** old = mat;
	int orows = rows;
	int ocols = cols;
	rows = size;
	cols = size;
	mat = newMat();
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(i >= orows || j >= ocols) {
				if(i == j) {
					mat[i][j] = 1;
				}
				else {
					mat[i][j] = 0;
				}
			}
			else {
				mat[i][j] = old[i][j];
			}
		}
	}
	for(int i = 0; i < orows; i++){
		delete [] old[i];
	}
	delete [] old;
	return *this;
}

void Matrix::fillMatrix() {
	srand(time(0));
	int r = rows;
	int c = cols;
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			mat[i][j] = rand() % 10;
		}
	}
}

bool Matrix::symTest() {
	for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                        if(mat[i][j] != mat[j][i]) {
				return false;
			}
                }
        }
	return true;
}

Matrix Matrix::nonSymInv(Matrix A) {
	return ((((A.transpose() * A).inverse()) * A.transpose()));
}

int Matrix::det(Matrix A) {
	int total = 0;
	Matrix B(A.rows - 1, A.cols - 1);
	if(A.rows == 2) {
		return ((A.mat[0][0] * A.mat[1][1]) - (A.mat[1][0] * A.mat[0][1]));
	}
      	for (int a = 0; a < A.rows; a++) {
            	int Bi = 0; 
            	for (int i = 1; i < A.rows; i++) {
               		int Bj = 0;
               		for (int j = 0; j < A.rows; j++) {
                  		if (j != a) {
                  			B.mat[Bi][Bj] = A.mat[i][j];
                 			Bj++;
				}
               		}
               		Bi++;
            	}
            	total = total + (pow(-1, a) * A.mat[0][a] * det(B));
      	}
   	return total;
}

void Matrix::bHat() {
	std::ifstream infile("points100.dat");
	Matrix A(100, 2);
        Matrix B(100, 1);
        float c = 0;
	float d = 0;
	int i = 0;
        while((infile >> c >> d) && (i < 100)) {
        	A.mat[i][0] = c;
                A.mat[i][1] = 1;
		B.mat[i][0] = d;
		i++;
        }
        infile.close();
	((((A.transpose() * A).inverse()) * A.transpose()) * B).printMatrix();
}
