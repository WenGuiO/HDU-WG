#include "Teacher.h"
#include "DeleteInformation.h" 
void DeleteTeacherInformation(struct Teacher *pHead)  //ɾ����Ϣ 
{
	system("cls");
	int id;
	char choice;   //�ж��Ƿ�ɾ�� 
	printf("\n\n\n");
    printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |             ɾ����ʦ��Ϣ                |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	
	printf("\t\t\t������Ҫɾ���Ľ�ʦ��: ");
	scanf("%d", &id);
	struct Teacher* pDelete = pHead->next;  //pDelete�������ݵĵڶ��ڵ㿪ʼ 
	struct Teacher* pRe = pHead;        //pRe���׽ڵ�β�� 
	
	while (pDelete != NULL)
	{
		if (pDelete->id == id)  //��ǰ�ڵ�Ľ�ʦ�ŷ��� 
		{
			ShowTeacherInformation(pDelete);    //չʾ�ý�ʦ��Ϣ 
			
			getchar();
			printf("\n\t\t\t�Ƿ�ɾ��? (Y/N): ");
			scanf("%c", &choice);
			if (choice != 'Y' && choice != 'y')
				return;
				
			pRe->next = pDelete->next;   //ɾ����ǰһ�ڵ㣨pRe��ָ��ǰ�ڵ㣨pDelete������һ�ڵ� 
			free(pDelete);       //�ͷ�ɾ���ڵ��ڴ� 
			pDelete = NULL;
			
			system("cls");
			printf("\n\n\n\t\t\t\t\t-------------------------\n");
			printf("\t\t\t\t\t|       ɾ���ɹ�        |\n"); 
			printf("\t\t\t\t\t-------------------------\n\n");
			system("pause");
			return;
		}
		pDelete = pDelete->next;
		pRe = pRe->next;
	}
	
	printf("\n\t\t\t\tû���ҵ��ý�ʦ!!\n\n");
	system("pause");
}
