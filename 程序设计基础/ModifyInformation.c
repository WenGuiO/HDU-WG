#include "Teacher.h"
#include "ModifyInformation.h"
void ModifyTeacherInformation(struct Teacher *pHead)
{
	int key, id, Changcount = 0;  // keyΪ�޸���Ŀ��ţ�ChangcountΪ�޸Ĵ��� 
	char choice;        //�����ж��Ƿ��ٴΣ��޸� 
	system("cls");
	printf("\n\n\n");
    printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |             �޸Ľ�ʦ��Ϣ                |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	printf("\t\t\t������Ҫ�޸ĵĽ�ʦ��: ");
	scanf("%d", &id);
	
	struct Teacher* pTem = pHead->next;    //�ڶ��ڵ㿪ʼ 
	while(pTem != NULL)
	{
		if(pTem->id == id)
		{
			ShowTeacherInformation(pTem);
			getchar();
			printf("\n\t\t\t��ȷ���Ƿ���Ҫ�޸ģ� ��Y/N��: ");
			scanf("%c", &choice);
			if(choice != 'Y' && choice != 'y')
				return;
				
			printf("\n\t\t\t��ѡ���޸���: ");
			printf("\n\t\t\t\t1--��ʦ��\t2--����"); 
			printf("\n\t\t\t\t3--�Ա�\t\t4--������λ");
			printf("\n\t\t\t\t5--��ͥ��ַ\t6--�绰");
			printf("\n\t\t\t\t7--��������\t8--����");
			printf("\n\t\t\t\t9--�����\t10-�绰��");
			printf("\n\t\t\t\t11-ˮ���\t12-����");
			printf("\n\t\t\t\t13-����˰\t14-����˰"); 
			printf("\n\t\t\t\t15-������\t0--����\n\n");
			
			while(choice == 'Y' || choice == 'y')
			{
				printf("\n\t\t\t��ѡ��: ");
				scanf("%d", &key);
				while(key < 0 || key > 15)
				{
					printf("\t\t\t��ѡ���޸���: ");
					scanf("%d", &key);
				}
				switch(key)
				{
					case 1: printf("\t\t\t�µĽ�ʦ��: ");
							scanf("%d", &pTem->id); 
							break;
					case 2: printf("\t\t\t�µ�����: ");
							scanf("%s", pTem->name);
							break;
					case 3: printf("\t\t\t�µ��Ա�: ");
							scanf("%s", pTem->gender);
							break;
					case 4: printf("\t\t\t�µĹ�����λ: ");
							scanf("%s", pTem->workadress);
							break;
					case 5: printf("\t\t\t�µļ�ͥ��ַ: ");
							scanf("%s", pTem->homeadress);
							break;
					case 6: printf("\t\t\t�µĵ绰: ");
							scanf("%s", pTem->tel);
							break;
					case 7: printf("\t\t\t�µĻ�������: ");
							scanf("%lf", &pTem->salary);
							break;
					case 8: printf("\t\t\t�µĽ���: ");
							scanf("%lf", &pTem->allowance);
							break;
					case 9: printf("\t\t\t�µ������: ");
							scanf("%lf", &pTem->livingall);
							break;
					case 10: printf("\t\t\t�µĵ绰��: ");
							scanf("%lf", &pTem->telbill);
							break;
					case 11: printf("\t\t\t�µ�ˮ���: ");
							scanf("%lf", &pTem->waterelectricbill);
							break;
					case 12: printf("\t\t\t�µķ���: ");
							scanf("%lf", &pTem->roomcharge);
							break;
					case 13: printf("\t\t\t�µ�����˰: ");
							scanf("%lf", &pTem->incometax);
							break;
					case 14: printf("\t\t\t�µ�����˰: ");
							scanf("%lf", &pTem->sanitationfee);
							break;
					case 15: printf("\t\t\t�µĹ�����: ");
							scanf("%lf", &pTem->reservefund);
							break;
				}
				
				if(key > 0 && key <=15)
					Changcount++;     //�ж��Ƿ��Ѿ��޸� ����������޸ĺ���Ϣ 
				if(key <= 0 || key >15)
					break;
					
				getchar();
				printf("\n\t\t\t�Ƿ���Ҫ�޸��������ݣ� ��Y/N��: ");
				scanf("%c", &choice);
			}
			if(Changcount > 0)       //��δ�޸ģ������ 
			{
				system("cls");
				printf("\n\n\t\t\t�޸ĺ����Ϣ����:\n");
				ShowTeacherInformation(pTem);
				system("pause");
			}
			return;
		}
		pTem = pTem->next;
	}
	printf("\n\t\t\t\t�ý�ʦ�Ų����ڣ�����");	
	system("pause");
}
