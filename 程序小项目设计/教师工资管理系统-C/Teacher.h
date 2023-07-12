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
	double salary;  				//基本工资 
	double allowance;  			 	//津贴 
	double livingall;				//生活补贴
	double telbill;				//电话费 
	double waterelectricbill;		//水电费 
	double roomcharge;				//房租
	double incometax;				//所得税 
	double sanitationfee;			//卫生稅 
	double reservefund;			//公积金
	struct Teacher* next;
};

int MainMenu ();                                          //开始主菜单 


#endif

