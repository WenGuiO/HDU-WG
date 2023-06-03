#include "Teacher.h"
#include "SearchInformation.h"
void SearchMenu(struct Teacher *pHead)
{
	int key = -1;
	while(key != 0)    //ȷ��������ɿɻص������� 
	{
		system("cls");
		printf("\n\n\n");
	    printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |             ���ҽ�ʦ��Ϣ                |\n");
		printf("\t\t\t\t |                                         |\n");
		printf("\t\t\t\t |            1.����ʦ�Ų���               |\n");
		printf("\t\t\t\t |            2.����������                 |\n");
		printf("\t\t\t\t |            3.�鿴���н�ʦ��Ϣ           |\n");
		printf("\t\t\t\t |            0.�˳�                       |\n");
		printf("\t\t\t\t |                                         |\n");
		printf("\t\t\t\t -------------------------------------------\n\n");
		printf("\t\t\t��ѡ����: ");
		scanf("%d",&key);
		
		switch(key)
		{
			case 1: SearchTeacherById(pHead);      //��ʦ�Ų��� 
					break;
			case 2: SearchTeacherByName(pHead);    //�������� 
					break; 
			case 3: ShowAllTeacher(pHead);         //�鿴���н�ʦ��Ϣ 
					break; 
		}
	}
} 

void ShowTeacherInformation(struct Teacher *pTem)  //չʾ��ǰ��ʦ���� 
{
	double shouldsalary, allconsume, income;
	printf("\n\n\t\t\t\t��ʦ��-----%d", pTem->id);
	printf("\n\t\t\t\t����-------%s", pTem->name);
	printf("\n\t\t\t\t�Ա�-------%s", pTem->gender);
	printf("\n\t\t\t\t������λ---%s", pTem->workadress);
	printf("\n\t\t\t\t��ͥ��ַ---%s", pTem->homeadress);
	printf("\n\t\t\t\t��ϵ�绰---%s", pTem->tel);
	printf("\n\t\t\t\t��������---%.1lf", pTem->salary);
	printf("\n\t\t\t\t����-------%.1lf", pTem->allowance);
	printf("\n\t\t\t\t�����---%.1lf", pTem->livingall);
	printf("\n\t\t\t\t�绰��-----%.1lf", pTem->telbill);
	printf("\n\t\t\t\tˮ���-----%.1lf", pTem->waterelectricbill);
	printf("\n\t\t\t\t����-------%.1lf", pTem->roomcharge);
	printf("\n\t\t\t\t����˰-----%.1lf", pTem->incometax);
	printf("\n\t\t\t\t����˰-----%.1lf", pTem->sanitationfee);
	printf("\n\t\t\t\t������-----%.1lf", pTem->reservefund);
	
	shouldsalary = pTem->salary + pTem->allowance + pTem->livingall;       //Ӧ������ 
	allconsume = pTem->telbill + pTem->waterelectricbill + pTem->roomcharge + 
			pTem->incometax + pTem->sanitationfee + pTem->reservefund;      //�ϼƿۿ� 
	income = shouldsalary - allconsume; 
	printf("\n\t\t\t\t��Ӧ������----%.1lf", shouldsalary);
	printf("\n\t\t\t\t��ϼƿۿ�----%.1lf", allconsume);
	printf("\n\t\t\t\t��ʵ������---%.1lf", income);
	printf("\n\n\t\t\t  *************************************"); 
	return;
}

void SearchTeacherById(struct Teacher *pHead)
{
	while(1)    //���û������Ƿ�ѭ�����Ƿ��ٴβ��ң� 
	{
		int flag = 1;    //�����жϽ�ʦ�Ƿ���ڣ�������Ϊ 0 
		char choice;         //�����ж��Ƿ���Ҫ���� 
		system("cls");
		printf("\n\n\n");
	    printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |             �Խ�ʦ�Ų���                |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\n");
		printf("\t\t\t\t������Ҫ���ҵĽ�ʦ��: ");
		int id; 
		scanf("%d", &id);
		
		struct Teacher* pTem = pHead->next;
		while (pTem != NULL)        //�������� 
		{
			if(pTem->id == id)
				{
					ShowTeacherInformation(pTem);     //չʾ�˽�ʦ��Ϣ 
				    flag = 0; 
				    break;
				}
			pTem = pTem->next;
		}
		
		if(flag)
			printf("\n\t\t\t\t�ý�ʦ�Ų����ڣ���\n"); 
			
			
		getchar();       //ͣ�� 
		printf("\n\n\t\t\t\t�Ƿ���Ҫ���ң���Y/N): ");
		scanf("%c", &choice);
		if(choice != 'Y' && choice != 'y')    //�����ٴβ�����������˳� 
			return;
	}
}

void SearchTeacherByName(struct Teacher *pHead)
{
	while(1)
	{
		int flag = 1;
		system("cls");
		printf("\n\n\n");
	    printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |              ����������                 |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\n");
		printf("\t\t\t\t������Ҫ���ҵĽ�ʦ����: ");
		char name[10]; 
		scanf("%s", name);
		
		struct Teacher* pTem = pHead->next;
		while (pTem != NULL)
		{
			if( strcmp(pTem->name, name) == 0 )
				{
					ShowTeacherInformation(pTem);
				    flag = 0; 
				}
			pTem = pTem->next;
		}
		if(flag)
			printf("\n\n\t\t\t\t�ý�ʦ�����ڣ���"); 
			
		getchar();
		printf("\n\n\t\t\t\t�Ƿ���Ҫ���ң���Y/N): ");
		char choice;
		scanf("%c", &choice); 
		if(choice != 'Y' && choice != 'y')
			break;
	}
}

void ShowAllTeacher(struct Teacher *pHead)
{ 
	int count = 0;    //�ж��Ƿ���ڽ�ʦ���� 
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |           �鿴���н�ʦ��Ϣ              |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	printf("\t\t\t  ���н�ʦ��Ϣ���£�"); 
	
	struct Teacher* pTem = pHead->next;
	while(pTem != NULL)
	{
		count++; 
		ShowTeacherInformation(pTem);
		pTem = pTem->next;
	} 
	
	if(count == 0)
		printf("\n\n\t\t\t\t  ��δ¼���κν�ʦ��Ϣ����"); 
	system("pause"); 
}
