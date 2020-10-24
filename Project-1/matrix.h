#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <chrono>

class Matrix {
	private:
		long unsigned int cols;
		long unsigned int rows;
		float** mat;
	public:
		Matrix();
		Matrix(long unsigned int, long unsigned int);
		float** newMat() const;
		void fillMatrix();
		void printMatrix();
		long unsigned int getRows() const;
		long unsigned int getCols() const;
		Matrix transpose();
		Matrix& inverse();
		Matrix& padMatrix();
		void bHat();
		bool symTest();
		Matrix nonSymInv(Matrix);
		int det(Matrix);
		Matrix operator+ (const Matrix& a){
			int ops = 0;
			auto begin = std::chrono::system_clock::now();
			Matrix result = Matrix(rows, cols);
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					result.mat[i][j] = mat[i][j] + a.mat[i][j];
					ops++;
				}
			}
			auto finish = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = finish-begin;
			std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
			std::cout << "Operations for Addition of matrix size " << rows << "X" << cols << ": " << ops << std::endl;
			std::cout << "Time taken for operation: " << elapsed_seconds.count() << std::endl;
			return result;
		}
		Matrix operator- (const Matrix& a){
			int ops = 0;
			auto begin = std::chrono::system_clock::now();
			Matrix result = Matrix(rows, cols);
                        for(int i = 0; i < rows; i++) {
                                for(int j = 0; j < cols; j++) {
                                        result.mat[i][j] = mat[i][j] - a.mat[i][j];
					ops++;
				}
			}
			auto finish = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = finish-begin;
			std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
			std::cout << "Operations for Subtraction of matrix size " << rows << "X" << cols << ": " << ops << std::endl;
                        std::cout << "Time taken for operation: " << elapsed_seconds.count() << std::endl;
			return result;
		}
		Matrix operator* (const Matrix& a){
			int ops = 0;
			auto begin = std::chrono::system_clock::now();
			Matrix result = Matrix(rows, a.cols);
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < a.cols; j++) {
					for(int k = 0; k < a.rows; k++) {
						result.mat[i][j] += mat[i][k] * a.mat[k][j];
						ops++;
					}
				}
			}
			auto finish = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = finish-begin;
			std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
			std::cout << "Operations for Multiplication of matrix size " << rows << "X" << cols << " and size " << a.rows << "X" << a.cols << ": " << ops << std::endl;
			std::cout << "Time taken for operation: " << elapsed_seconds.count() << std::endl;
			return result;
		}
		Matrix operator* (const int& a) {
			int ops = 0;
			auto begin = std::chrono::system_clock::now();
			Matrix result(rows, cols);
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					result.mat[i][j] = a * mat[i][j];
					ops++;
				}
			}
			auto finish = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = finish-begin;
			std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
			std::cout << "Operations for Scalar Muliplication of matrix size " << rows << "X" << cols << ": " << ops << std::endl;
			std::cout << "Time taken for operation: " << elapsed_seconds.count() << std::endl;
			return result;
		}
};

#endif
