#include "Teacher.h"
#include "ExtractFile.h"
struct Teacher *ExtractTeacherOfFile()  //��ʼ��������ȡ�ļ����� 
{
	FILE* fp = fopen("�����ʦ���ʱ�", "r+");
	if (fp == NULL)	    	//û���ļ�ʱ�ȴ���һ���ļ�
		fp = fopen("�����ʦ���ʱ�", "w+");
		
	struct Teacher* pHead = (struct Teacher*)malloc(sizeof(struct Teacher));
	pHead->next = NULL;     //��ΪpHead�����ڴ棬ȷ���ļ�Ϊ��ʱ�з���ֵ 
	struct Teacher* pTem;   //�������� 
	
	while(1)
	{
		struct Teacher* pNew = (struct Teacher*)malloc(sizeof(struct Teacher));
		pNew->next = NULL;
		
		if(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", 
				&pNew->id, pNew->name, pNew->gender, pNew->workadress, pNew->homeadress, pNew->tel, &pNew->salary, 
				&pNew->allowance, &pNew->livingall, &pNew->telbill, &pNew->waterelectricbill, &pNew->roomcharge, 
				&pNew->incometax, &pNew->sanitationfee, &pNew->reservefund) == EOF )  //���ļ���ȡ���ݣ���ȡʧ����������в������˳� 
		{
			free(pNew);    //�ͷ��ڴ� 
			pNew = NULL;   //ָ��� 
			break;
		}
		
		pTem = pHead;      //ָ���׽ڵ㣨����ʼ������ 
		while (pTem->next != NULL)
		{
			if (pNew->id < pTem->next->id)   //�жϲ���λ�� ���Խ�ʦ������ 
			{
				pNew->next = pTem->next;     //�½ڵ�ָ��ǰ�ڵ����һ�ڵ� 
				break; 
			}
			pTem = pTem->next;   
		}   
		pTem->next = pNew;   //��ǰ�ڵ�ָ���½ڵ� 
	}    //��ʼ�������ԭ���ǣ� ȷ�����û�������Ϣ�޸ģ������ļ����ٴδ��԰��ս�ʦ�������״̬ 
	
	fclose(fp);
	return pHead;
}


