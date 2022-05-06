#pragma once

class Matrix {
public:
	Matrix(int,int);
	Matrix(void);
	double Determinant_Calculation(void);	//����ʽ����//
	Matrix Transposition(void);				//����ת��//
	Matrix operator+(const Matrix&);		//����ӷ�//
	Matrix operator-(const Matrix&);		//�������//
	Matrix operator*(const Matrix&);		//����˷�//
	Matrix operator*(double);				//��������//
	Matrix operator^(int);					//����η�//
	Matrix Inverse(void);					//��������//
	Matrix Rank_Changed(void);				//������ȼ��仯����//
	double MatrixFi(int,int);				//��ȡ�ض�����ֵ//
	void operator=(Matrix);					//���ݾ����趨����//
	void operator=(double a[5][5]);			//�趨����ֵ//
	void Show(void);						//�����ã���ʾ������ֵ//
	int Show_Rank(void);
	bool Used = false;
	int Det_H,Det_L;
private:
	double Det[5][5];
	bool Existance = true;
	int Rank;
};