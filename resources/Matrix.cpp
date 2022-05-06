#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(int H, int L)
{
	Det_H = H;
	Det_L = L;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Det[i][j] = 0;
}

Matrix::Matrix(void)
{
	Det_H = 5;
	Det_L = 5;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Det[i][j] = 0;
}

Matrix Matrix::Transposition(void)
{
	Matrix Tempo;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Tempo.Det[i][j] = Det[j][i];
	Tempo.Det_H = Det_L;
	Tempo.Det_L = Det_H;
	return Tempo;
}

Matrix Matrix::operator+(const Matrix &B)
{
	Matrix Tempo;
	if (Det_H == B.Det_H && Det_L == B.Det_L) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				Tempo.Det[i][j] = Det[i][j] + B.Det[i][j];
		Tempo.Det_H = Det_H;
		Tempo.Det_L = Det_L;
	}
	else {Tempo.Existance = false;}
	return Tempo;
}

Matrix Matrix::operator-(const Matrix& B)
{
	Matrix Tempo;
	if (Det_H == B.Det_H && Det_L == B.Det_L) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				Tempo.Det[i][j] = Det[i][j] - B.Det[i][j];
		Tempo.Det_H = Det_H;
		Tempo.Det_L = Det_L;
	}
	else { Tempo.Existance = false; }
	return Tempo;
}

Matrix Matrix::operator*(const Matrix& B)
{
	Matrix Tempo;
	if (Det_L == B.Det_H) {
		for (int i = 0; i < Det_H; i++) {
			for (int j = 0; j < B.Det_L; j++) {
				for (int k = 0; k < Det_L; k++)
					Tempo.Det[i][j] += Det[i][k] * B.Det[k][j];
			}
		}
		Tempo.Det_H = Det_H;
		Tempo.Det_L = B.Det_L;
	}
	else {Tempo.Existance = false;}
	return Tempo;
}

Matrix Matrix::operator*(double K)
{
	Matrix Tempo;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Tempo.Det[i][j] = K * Det[i][j];
	Tempo.Det_H = Det_H;
	Tempo.Det_L = Det_L;
	return Tempo;
}

Matrix Matrix::operator^(int A) 
{
	Matrix Tempo;
	Matrix _Tempo;
	if (A == -1) {
		Tempo = this->Inverse();
		Tempo.Det_H = Det_H;
		Tempo.Det_L = Det_L;
		return Tempo;
	}
	else if (A == 1) {
		Tempo = Det;
		Tempo.Det_H = Det_H;
		Tempo.Det_L = Det_L;
		return Tempo;
	}
	else if (Det_H != Det_L) {
		Tempo.Existance = false;
		return Tempo;
	}
	else if (A > 1) {
		Tempo = Det;
		Tempo.Det_H = Det_H;
		Tempo.Det_L = Det_L;
		_Tempo = Det;
		_Tempo.Det_H = Det_H;
		_Tempo.Det_L = Det_L;
		for (int i = 0; i < A - 1; i++)
			Tempo = Tempo * _Tempo;
	}
	return Tempo;
} 

double Matrix::Determinant_Calculation(void)
{
	double Result = 1.0;
	double Tempo[5][5];
	double T;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Tempo[i][j] = Det[i][j];
	for (int z = 0; z < Det_H - 1; z++)
		for (int i = z; i < Det_H - 1; i++)
		{
			if (Tempo[z][z] == 0)
				for (i = z; Tempo[z][z] == 0; i++)
				{
					for (int j = 0; j < Det_H; j++)
						Tempo[z][j] = Tempo[z][j] + Tempo[i + 1][j];
					if (Tempo[z][z] != 0)
						break;
					else {
						Result = 0;
						return Result;
					}
				}
			T = -Tempo[i + 1][z] / Tempo[z][z];
			for (int j = z; j < Det_H; j++)
				Tempo[i + 1][j] = T * (Tempo[z][j]) + Tempo[i + 1][j];
		}
	for (int z = 0; z < Det_H; z++)
		Result = Result * (Tempo[z][z]);
	return Result;
}

void Matrix::operator=(double T[5][5])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Det[i][j] = T[i][j];
}

void Matrix::operator=(Matrix T)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			Det[i][j] = T.Det[i][j];
	Det_H = T.Det_H;
	Det_L = T.Det_L;
	Rank = T.Rank;
	Existance = T.Existance;
}

void Matrix::Show(void)
{
	for (int i = 0; i < Det_H; i++) {
		for(int j = 0; j < Det_L;j++)
			cout << Det[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

Matrix Matrix::Inverse(void)
{
	Matrix Tempo;
	double d[5][5];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			d[i][j] = Det[i][j];
	double b[5][5] = {0};
	for (int i = 0; i < 5; i++)
		b[i][i] = 1.0;
	for (int m = 0; m < Det_H; m++)
	{
		double t = d[m][m];
		int i = m;
		while (d[m][m] == 0)
		{
			d[m][m] = d[i + 1][m];
			i++;
		}
		if (i > m)
		{
			d[i][m] = t;
			for (int j = 0; j < Det_H; j++)
			{
				t = d[m][j];
				d[m][j] = d[i][j];
				d[i][j] = t;
			}
			for (int j = 0; j < Det_H; j++)
			{
				t = b[m][j];
				b[m][j] = b[i][j];
				b[i][j] = t;
			}
		}
		for (i = m + 1; i < Det_H; i++)
			for (int j = Det_H - 1; j >= 0; j--)
				b[i][j] -= b[m][j] * d[i][m] / d[m][m];
		for (i = m + 1; i < Det_H; i++)
			for (int j = Det_H - 1; j >= m; j--)
				d[i][j] -= d[m][j] * d[i][m] / d[m][m];
		for (int j = Det_H - 1; j >= 0; j--)
			b[m][j] /= d[m][m];
		for (int j = Det_H - 1; j >= m; j--)
			d[m][j] /= d[m][m];
	}

	int m = Det_H - 1;
	while (m > 0)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = Det_H - 1; j >= 0; j--)
				b[i][j] -= d[i][m] * b[m][j];
			for (int j = Det_H - 1; j >= m; j--)
				d[i][j] -= d[i][m] * d[m][j];
		}
		m--;
	}
	for (int i = 0; i < Det_H; i++)
		for (int j = 0; j < Det_H; j++)
			Tempo.Det[i][j] = b[i][j];
	Tempo.Det_H = Det_H;
	return Tempo;
}

Matrix Matrix::Rank_Changed(void)
{
	Matrix Tempo;
	double d[5][5];
	double t;
	int ri,ci,f_z;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			d[i][j] = Det[i][j];
	for (ri = ci = 0; ci < Det_L; ci++)
	{
		f_z = 1;
		for (int i = ri; i < Det_H; i++)
			if (d[i][ci] != 0)
			{
				if (i != ri)
					if (f_z)
						for (int j = 0; j < Det_L - ci; j++)
						{
							t = d[ri][ci + j];
							d[ri][ci + j] = d[i][ci + j];
							d[i][ci + j] = t;
						}
					else
					{
						t = d[i][ci];
						for (int j = 0; j < Det_L - ci; j++)
							d[i][ci + j] *= d[ri][ci];
						for (int j = 0; j < Det_L - ci; j++)
							d[i][ci + j] += d[ri][ci + j] * (-t);
					}
				f_z = 0;
			}
		if (!f_z) ri++;
	}
	for (int i = 0; i < Det_H; i++)
		for (int j = 0; j < Det_L; j++)
			Tempo.Det[i][j] = d[i][j];
	Tempo.Det_H = Det_H;
	Tempo.Det_L = Det_L;
	Rank = ri;
	Tempo.Rank = Rank;
	return Tempo;
}

int Matrix::Show_Rank(void)
{
	return Rank;
}

double Matrix::MatrixFi(int H, int L)
{
	return Det[H][L];
}

