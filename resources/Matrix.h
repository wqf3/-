#pragma once

class Matrix {
public:
	Matrix(int,int);
	Matrix(void);
	double Determinant_Calculation(void);	//行列式计算//
	Matrix Transposition(void);				//矩阵转置//
	Matrix operator+(const Matrix&);		//矩阵加法//
	Matrix operator-(const Matrix&);		//矩阵减法//
	Matrix operator*(const Matrix&);		//矩阵乘法//
	Matrix operator*(double);				//矩阵数乘//
	Matrix operator^(int);					//矩阵次方//
	Matrix Inverse(void);					//矩阵求逆//
	Matrix Rank_Changed(void);				//矩阵的秩及变化矩阵//
	double MatrixFi(int,int);				//获取特定行列值//
	void operator=(Matrix);					//根据矩阵设定矩阵//
	void operator=(double a[5][5]);			//设定矩阵值//
	void Show(void);						//测试用，显示矩阵数值//
	int Show_Rank(void);
	bool Used = false;
	int Det_H,Det_L;
private:
	double Det[5][5];
	bool Existance = true;
	int Rank;
};