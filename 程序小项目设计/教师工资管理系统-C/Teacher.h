#ifndef _TEACHER_H
#define _TEACHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Teacher
{
	int id;
	char name[10];
	char gender[5];
	char workadress[20];
	char homeadress[20];
	char tel[11];
	double salary;  				//�������� 
	double allowance;  			 	//���� 
	double livingall;				//�����
	double telbill;				//�绰�� 
	double waterelectricbill;		//ˮ��� 
	double roomcharge;				//����
	double incometax;				//����˰ 
	double sanitationfee;			//������ 
	double reservefund;			//������
	struct Teacher* next;
};

int MainMenu ();                                          //��ʼ���˵� 


#endif

