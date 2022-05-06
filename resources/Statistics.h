#pragma once

class Statistics {
public:
	void   Calculation(void);
	void   operator=(double [50]);
	void   SetOneData(double,int);
	void   SetDataFi(int);
	void   Show(void);				//打印数值
	double sum(void);				//返回总值，下功能同
	double mean();					//平均值
	double max();					//最大值
	double min();					//最小值
	double range();					//极差
	double median();				//中位数
	double harmonic();				//调和平均值
	double geometrical();			//几何平均数
	double variance();				//方差
	double c_Variance();			//修正方差
	double standard_Deviation();	//标准差
	double c_Standard_Deviation();	//修正标准差
	double variable_Coefficient();	//变异系数
	double mean_Variation();		//平均偏差
	int    modeFi();				//众数个数
	int	   mode_Time();				//众数出现次数
	void   mode();					//挨个打印众数
	double mode(int);				//打印特定众数
private:
	double Sum = 0;					//总值
	double Mean;					//平均值
	double Max;						//最大值
	double Min;						//最小值
	double Range;					//极差
	double Median;					//中位数
	double Harmonic = 0;			//调和平均值
	double Geometrical = 1;			//几何平均数
	double Variance;				//方差
	double C_Variance;				//修正方差
	double Standard_Deviation;		//标准差
	double C_Standard_Deviation;	//修正标准差
	double Variable_Coefficient;	//变异系数
	double Mean_Variation;			//平均偏差
	double Mode[50];				//众数
	int    ModeFi;					//众数个数
	int    Mode_Time;				//众数出现次数
	double Data[50];				//数据
	int    DataFi;					//数据个数
};