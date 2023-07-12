#include "Teacher.h"
#include "ExtractFile.h"
struct Teacher *ExtractTeacherOfFile()  //初始化链表，提取文件数据 
{
	FILE* fp = fopen("教师工资表", "r+");
	if (fp == NULL)	    	//没有文件时先创建一个文件
		fp = fopen("杭电教师工资表", "w+");
		
	struct Teacher* pHead = (struct Teacher*)malloc(sizeof(struct Teacher));
	pHead->next = NULL;     //先为pHead分配内存，确保文件为空时有返回值 
	struct Teacher* pTem;   //用以排序 
	
	while(1)
	{
		struct Teacher* pNew = (struct Teacher*)malloc(sizeof(struct Teacher));
		pNew->next = NULL;
		
		if(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", 
				&pNew->id, pNew->name, pNew->gender, pNew->workadress, pNew->homeadress, pNew->tel, &pNew->salary, 
				&pNew->allowance, &pNew->livingall, &pNew->telbill, &pNew->waterelectricbill, &pNew->roomcharge, 
				&pNew->incometax, &pNew->sanitationfee, &pNew->reservefund) == EOF )  //从文件提取数据，提取失败则进行下列操作后退出 
		{
			free(pNew);    //释放内存 
			pNew = NULL;   //指向空 
			break;
		}
		
		pTem = pHead;      //指向首节点（排序开始操作） 
		while (pTem->next != NULL)
		{
			if (pNew->id < pTem->next->id)   //判断插入位置 （以教师号排序） 
			{
				pNew->next = pTem->next;     //新节点指向当前节点的下一节点 
				break; 
			}
			pTem = pTem->next;   
		}   
		pTem->next = pNew;   //当前节点指向新节点 
	}    //初始化排序的原因是： 确保当用户进行信息修改，保存文件后，再次打开仍按照教师号排序的状态 
	
	fclose(fp);
	return pHead;
}


