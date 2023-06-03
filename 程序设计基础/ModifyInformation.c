#include "Teacher.h"
#include "ModifyInformation.h"
void ModifyTeacherInformation(struct Teacher *pHead)
{
	int key, id, Changcount = 0;  // key为修改项目序号，Changcount为修改次数 
	char choice;        //用以判断是否（再次）修改 
	system("cls");
	printf("\n\n\n");
    printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |             修改教师信息                |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	printf("\t\t\t请输入要修改的教师号: ");
	scanf("%d", &id);
	
	struct Teacher* pTem = pHead->next;    //第二节点开始 
	while(pTem != NULL)
	{
		if(pTem->id == id)
		{
			ShowTeacherInformation(pTem);
			getchar();
			printf("\n\t\t\t请确认是否需要修改？ （Y/N）: ");
			scanf("%c", &choice);
			if(choice != 'Y' && choice != 'y')
				return;
				
			printf("\n\t\t\t请选择修改项: ");
			printf("\n\t\t\t\t1--教师号\t2--姓名"); 
			printf("\n\t\t\t\t3--性别\t\t4--工作单位");
			printf("\n\t\t\t\t5--家庭地址\t6--电话");
			printf("\n\t\t\t\t7--基本工资\t8--津贴");
			printf("\n\t\t\t\t9--生活补贴\t10-电话费");
			printf("\n\t\t\t\t11-水电费\t12-房租");
			printf("\n\t\t\t\t13-所得税\t14-卫生税"); 
			printf("\n\t\t\t\t15-公积金\t0--返回\n\n");
			
			while(choice == 'Y' || choice == 'y')
			{
				printf("\n\t\t\t请选择: ");
				scanf("%d", &key);
				while(key < 0 || key > 15)
				{
					printf("\t\t\t请选择修改项: ");
					scanf("%d", &key);
				}
				switch(key)
				{
					case 1: printf("\t\t\t新的教师号: ");
							scanf("%d", &pTem->id); 
							break;
					case 2: printf("\t\t\t新的姓名: ");
							scanf("%s", pTem->name);
							break;
					case 3: printf("\t\t\t新的性别: ");
							scanf("%s", pTem->gender);
							break;
					case 4: printf("\t\t\t新的工作单位: ");
							scanf("%s", pTem->workadress);
							break;
					case 5: printf("\t\t\t新的家庭地址: ");
							scanf("%s", pTem->homeadress);
							break;
					case 6: printf("\t\t\t新的电话: ");
							scanf("%s", pTem->tel);
							break;
					case 7: printf("\t\t\t新的基本工资: ");
							scanf("%lf", &pTem->salary);
							break;
					case 8: printf("\t\t\t新的津贴: ");
							scanf("%lf", &pTem->allowance);
							break;
					case 9: printf("\t\t\t新的生活补贴: ");
							scanf("%lf", &pTem->livingall);
							break;
					case 10: printf("\t\t\t新的电话费: ");
							scanf("%lf", &pTem->telbill);
							break;
					case 11: printf("\t\t\t新的水电费: ");
							scanf("%lf", &pTem->waterelectricbill);
							break;
					case 12: printf("\t\t\t新的房租: ");
							scanf("%lf", &pTem->roomcharge);
							break;
					case 13: printf("\t\t\t新的所得税: ");
							scanf("%lf", &pTem->incometax);
							break;
					case 14: printf("\t\t\t新的卫生税: ");
							scanf("%lf", &pTem->sanitationfee);
							break;
					case 15: printf("\t\t\t新的公积金: ");
							scanf("%lf", &pTem->reservefund);
							break;
				}
				
				if(key > 0 && key <=15)
					Changcount++;     //判断是否已经修改 ，用于输出修改后信息 
				if(key <= 0 || key >15)
					break;
					
				getchar();
				printf("\n\t\t\t是否还需要修改其他内容？ （Y/N）: ");
				scanf("%c", &choice);
			}
			if(Changcount > 0)       //若未修改，则不输出 
			{
				system("cls");
				printf("\n\n\t\t\t修改后的信息如下:\n");
				ShowTeacherInformation(pTem);
				system("pause");
			}
			return;
		}
		pTem = pTem->next;
	}
	printf("\n\t\t\t\t该教师号不存在！！！");	
	system("pause");
}
