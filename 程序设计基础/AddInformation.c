#include "Teacher.h"
#include "AddInformation.h"
void AddTeacherInformation(struct Teacher *pHead) //��Ϣ¼�� 
{
	double shouldsalary, allconsume, income;
	while(1)     //ѭ��Ŀ�ģ� ʵ���û����¼����Ը 
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |               ¼���ʦ��Ϣ              |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		
		struct Teacher* pnew = (struct Teacher*)malloc(sizeof(struct Teacher));
		pnew->next = NULL;        //Ϊ����¼�����ռ� 
		if (pnew == NULL) return;
		printf("\n\t\t\t  �����룺\n\n");
		printf("\t\t\t\t��ʦ��: ");
		scanf("%d", &pnew->id);
		
		while(1)
		{
			if (IdIsExist(pHead, pnew->id))     //�жϽ�ʦ���Ƿ��ظ� 
			{
				printf("\t\t\t\t��ʦ���ظ�,����������:");
				scanf("%d", &pnew->id);
			}	
			else 
				break;
		}
		
		printf("\t\t\t\t����: "); 
		scanf("%s", pnew->name);
		printf("\t\t\t\t�Ա�: "); 
		scanf("%s", pnew->gender);
		printf("\t\t\t\t��λ����: "); 
		scanf("%s", pnew->workadress);
		printf("\t\t\t\t��ͥ��ַ: "); 
		scanf("%s", pnew->homeadress);
		printf("\t\t\t\t��ϵ�绰: "); 
		scanf("%s", pnew->tel);
		printf("\t\t\t\t��������: "); 
		scanf("%lf", &pnew->salary);
		printf("\t\t\t\t����: "); 
		scanf("%lf", &pnew->allowance);
		printf("\t\t\t\t�����: ");  
		scanf("%lf", &pnew->livingall);
		printf("\t\t\t\t�绰��: "); 
		scanf("%lf", &pnew->telbill);
		printf("\t\t\t\tˮ���: "); 
		scanf("%lf", &pnew->waterelectricbill);
		printf("\t\t\t\t����: "); 
		scanf("%lf", &pnew->roomcharge);
		printf("\t\t\t\t����˰: "); 
		scanf("%lf", &pnew->incometax);
		printf("\t\t\t\t������: ");
		scanf("%lf", &pnew->sanitationfee);
		printf("\t\t\t\t������: "); 
		scanf("%lf", &pnew->reservefund);
		
		shouldsalary = pnew->salary + pnew->allowance + pnew->livingall;       //Ӧ������ 
		allconsume = pnew->telbill + pnew->waterelectricbill + pnew->roomcharge + 
				    pnew->incometax + pnew->sanitationfee + pnew->reservefund;      //�ϼƿۿ� 
		income = shouldsalary - allconsume;      //ʵ������ 
		printf("\n\t\t\t\tӦ������:   %.1lf", shouldsalary); 
		printf("\n\t\t\t\t�ϼƿۿ�:   %.1lf", allconsume); 
		printf("\n\t\t\t\tʵ������:   %.1lf", income); 
		
		struct Teacher* pTem = pHead;        //ָ���׽ڵ㣨�������� 
		while (pTem->next != NULL)  
		{
			if (pnew->id < pTem->next->id)   //�жϲ���λ�ã��Խ�ʦ������ 
			{
				pnew->next = pTem->next; 
				break; 
			}
			pTem = pTem->next;
		}     //�Խ�ʦ������
		pTem->next = pnew;    //�����½ڵ� ��������Ϊ��ʱ��¼��������ڵڶ��ڵ㣬���׽ڵ��޽�ʦ��Ϣ��
		 
		getchar();      
		printf("\n\t\t\t\t�Ƿ���Ҫ�ٴ�¼���½�ʦ��Ϣ?��Y/N��: ");    
		char choice = getchar();
		if(choice != 'Y' && choice != 'y')        //����Ҫ¼�룬��������˳� 
			break;
	}
}

int IdIsExist(struct Teacher* pHead, int id)    //�жϽ�ʦ���Ƿ��ظ� 
{
	struct Teacher* pTem = pHead->next;         //¼��ʱ�Ǵӵڶ��ڵ㿪ʼ ������ָ��pTem�������� 
	while (pTem != NULL)
	{
		if (pTem->id == id)
		return 1;
		pTem = pTem->next;
	}
	return 0;
}

