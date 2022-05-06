#include "Statistics.h"
#include <iostream>
#include <cmath>
using namespace std;

void Statistics::Calculation(void)
{
	for (int i = 0; i < DataFi; i++)
		Sum += Data[i];
	Mean = Sum/DataFi;

	double Changed[50];//从小到大排序
	for (int i = 0; i < DataFi; i++)
		Changed[i] = Data[i];
	for (int i = 0; i < DataFi; i++) {
		for (int j = 0; j < DataFi - i - 1; j++) {
			if (Changed[j] > Changed[j + 1]) {
				double t = Changed[j];
				Changed[j] = Changed[j+1];
				Changed[j+1] = t;
			}
		}
	}

	Min = Changed[0];

	Max = Changed[DataFi - 1];

	Range = Max - Min;

	if(DataFi%2==0){Median = (Data[-1 + DataFi/2] + Data[DataFi/2])/2;}
	else{Median = Data[(DataFi-1)/2]; }

	for(int i=0;i<DataFi;i++)
		Harmonic += 1/(Data[i]);
	Harmonic = DataFi/Harmonic;
	
	for (int i=0;i<DataFi;i++)
		Geometrical = Geometrical * Data[i];
	Geometrical = pow(Geometrical,1.0/(double)DataFi);

	double Tempo = 0;
	for(int i=0;i<DataFi;i++)
		Tempo += pow(Data[i]-Mean,2);

	Variance = Tempo/DataFi;

	C_Variance = Tempo/(DataFi-1);

	Standard_Deviation = pow(Variance,0.5);

	C_Standard_Deviation = pow(C_Variance,0.5);

	Variable_Coefficient = Standard_Deviation / Mean;

	Tempo = 0;
	for (int i = 0; i < DataFi; i++) {
		Tempo = Data[i] - Mean;
		if(Tempo < 0){Tempo = -Tempo;};
		Mean_Variation += Tempo;
	}
	Mean_Variation = Mean_Variation/(double)DataFi;

	Tempo = 1;
	Mode_Time = 1;
	ModeFi = 0;
	for (int i = 0; i < DataFi-1; ) {
		while (Changed[i] == Changed[i + 1]) {
			Tempo++;
			i++;
		}
		if (Tempo > Mode_Time) {
			Mode_Time = Tempo;
			ModeFi = 0;
			Mode[ModeFi] = Changed[i];
		}
		else if (Tempo == Mode_Time) {
			ModeFi++;
			Mode[ModeFi] = Changed[i];
		}
		Tempo = 1;
		i++;
	}
	ModeFi++;

}

void Statistics::operator=(double Resources[50])
{
	for(int i=0;i<50;i++)
		Data[i] = Resources[i];
}

void Statistics::SetOneData(double Resource,int Number)
{
	Data[Number] = Resource;
}

void Statistics::Show(void)
{
	for (int i = 0; i < DataFi; i++) {
		cout << Data[i] << "  ";
	}
}

void Statistics::SetDataFi(int Fi)
{
	DataFi = Fi;
}

double Statistics::sum(void)				{ return Sum; }
double Statistics::mean()					{ return Mean; }
double Statistics::max()					{ return Max; }
double Statistics::min()					{ return Min; }
double Statistics::range()					{ return Range; }
double Statistics::median()					{ return Median; }
double Statistics::harmonic()				{ return Harmonic; }
double Statistics::geometrical()			{ return Geometrical; }
double Statistics::variance()				{ return Variance; }
double Statistics::c_Variance()				{ return C_Variance; }
double Statistics::standard_Deviation()		{ return Standard_Deviation; }
double Statistics::c_Standard_Deviation()	{ return C_Standard_Deviation; }
double Statistics::variable_Coefficient()	{ return Variable_Coefficient; }
double Statistics::mean_Variation()			{ return Mean_Variation; }
int    Statistics::modeFi()					{ return ModeFi; }
int    Statistics::mode_Time()				{ return Mode_Time; }

void   Statistics::mode()
{	
	if (Mode_Time > 1) {
		for(int i=0;i<ModeFi;i++)
			cout << Mode[i] << endl;
	}
	else {cout << "No Mode!" << endl; }

}

double Statistics::mode(int Fi)
{
	return Mode[Fi];
}