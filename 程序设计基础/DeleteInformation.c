#include "Teacher.h"
#include "DeleteInformation.h" 
void DeleteTeacherInformation(struct Teacher *pHead)  //删除信息 
{
	system("cls");
	int id;
	char choice;   //判断是否删除 
	printf("\n\n\n");
    printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |             删除教师信息                |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	
	printf("\t\t\t请输入要删除的教师号: ");
	scanf("%d", &id);
	struct Teacher* pDelete = pHead->next;  //pDelete从有数据的第二节点开始 
	struct Teacher* pRe = pHead;        //pRe从首节点尾随 
	
	while (pDelete != NULL)
	{
		if (pDelete->id == id)  //当前节点的教师号符合 
		{
			ShowTeacherInformation(pDelete);    //展示该教师信息 
			
			getchar();
			printf("\n\t\t\t是否删除? (Y/N): ");
			scanf("%c", &choice);
			if (choice != 'Y' && choice != 'y')
				return;
				
			pRe->next = pDelete->next;   //删除：前一节点（pRe）指向当前节点（pDelete）的下一节点 
			free(pDelete);       //释放删除节点内存 
			pDelete = NULL;
			
			system("cls");
			printf("\n\n\n\t\t\t\t\t-------------------------\n");
			printf("\t\t\t\t\t|       删除成功        |\n"); 
			printf("\t\t\t\t\t-------------------------\n\n");
			system("pause");
			return;
		}
		pDelete = pDelete->next;
		pRe = pRe->next;
	}
	
	printf("\n\t\t\t\t没有找到该教师!!\n\n");
	system("pause");
}
