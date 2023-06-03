#include "Teacher.h"
#include "ReserveFile.h"
void ReserveTeacherInformation(struct Teacher *pHead)  //保存退出 
{
	struct Teacher* pTem = pHead->next;    //从有数据的第二节点开始 
	FILE *fp = fopen("杭电教师工资表", "w+");
	
	if(fp == NULL)
	{
		system("cls");
		printf("\n\n\n\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t|       保存失败        |\n"); 
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
		}// 遍历链表输出到文件 
		
		system("cls");
		printf("\n\n\n\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t|       保存成功        |\n"); 
		printf("\t\t\t\t\t-------------------------\n\n");
	}
	system("pause"); 
	fclose(fp);
}
