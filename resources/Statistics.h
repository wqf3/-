#pragma once

class Statistics {
public:
	void   Calculation(void);
	void   operator=(double [50]);
	void   SetOneData(double,int);
	void   SetDataFi(int);
	void   Show(void);				//��ӡ��ֵ
	double sum(void);				//������ֵ���¹���ͬ
	double mean();					//ƽ��ֵ
	double max();					//���ֵ
	double min();					//��Сֵ
	double range();					//����
	double median();				//��λ��
	double harmonic();				//����ƽ��ֵ
	double geometrical();			//����ƽ����
	double variance();				//����
	double c_Variance();			//��������
	double standard_Deviation();	//��׼��
	double c_Standard_Deviation();	//������׼��
	double variable_Coefficient();	//����ϵ��
	double mean_Variation();		//ƽ��ƫ��
	int    modeFi();				//��������
	int	   mode_Time();				//�������ִ���
	void   mode();					//������ӡ����
	double mode(int);				//��ӡ�ض�����
private:
	double Sum = 0;					//��ֵ
	double Mean;					//ƽ��ֵ
	double Max;						//���ֵ
	double Min;						//��Сֵ
	double Range;					//����
	double Median;					//��λ��
	double Harmonic = 0;			//����ƽ��ֵ
	double Geometrical = 1;			//����ƽ����
	double Variance;				//����
	double C_Variance;				//��������
	double Standard_Deviation;		//��׼��
	double C_Standard_Deviation;	//������׼��
	double Variable_Coefficient;	//����ϵ��
	double Mean_Variation;			//ƽ��ƫ��
	double Mode[50];				//����
	int    ModeFi;					//��������
	int    Mode_Time;				//�������ִ���
	double Data[50];				//����
	int    DataFi;					//���ݸ���
};