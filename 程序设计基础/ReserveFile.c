#include "Teacher.h"
#include "ReserveFile.h"
void ReserveTeacherInformation(struct Teacher *pHead)  //�����˳� 
{
	struct Teacher* pTem = pHead->next;    //�������ݵĵڶ��ڵ㿪ʼ 
	FILE *fp = fopen("�����ʦ���ʱ�", "w+");
	
	if(fp == NULL)
	{
		system("cls");
		printf("\n\n\n\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t|       ����ʧ��        |\n"); 
		printf("\t\t\t\t\t-------------------------\n\n");
	}
	else
	{
		while(pTem != NULL)
		{ 
			fprintf(fp,"%d\t%s\t%s\t%s\t%s\t%s\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\n", 
				pTem->id, pTem->name, pTem->gender, pTem->workadress, pTem->homeadress, pTem->tel, pTem->salary, 
				pTem->allowance, pTem->livingall, pTem->telbill, pTem->waterelectricbill, pTem->roomcharge, 
				pTem->incometax, pTem->sanitationfee, pTem->reservefund);
			pTem = pTem->next;
		}// ��������������ļ� 
		
		system("cls");
		printf("\n\n\n\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t|       ����ɹ�        |\n"); 
		printf("\t\t\t\t\t-------------------------\n\n");
	}
	system("pause"); 
	fclose(fp);
}
