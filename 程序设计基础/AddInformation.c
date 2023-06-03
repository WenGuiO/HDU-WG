#include "Teacher.h"
#include "AddInformation.h"
void AddTeacherInformation(struct Teacher *pHead) //信息录入 
{
	double shouldsalary, allconsume, income;
	while(1)     //循环目的： 实现用户多次录入意愿 
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |               录入教师信息              |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		
		struct Teacher* pnew = (struct Teacher*)malloc(sizeof(struct Teacher));
		pnew->next = NULL;        //为新数录入分配空间 
		if (pnew == NULL) return;
		printf("\n\t\t\t  请输入：\n\n");
		printf("\t\t\t\t教师号: ");
		scanf("%d", &pnew->id);
		
		while(1)
		{
			if (IdIsExist(pHead, pnew->id))     //判断教师号是否重复 
			{
				printf("\t\t\t\t教师号重复,请重新输入:");
				scanf("%d", &pnew->id);
			}	
			else 
				break;
		}
		
		printf("\t\t\t\t姓名: "); 
		scanf("%s", pnew->name);
		printf("\t\t\t\t性别: "); 
		scanf("%s", pnew->gender);
		printf("\t\t\t\t单位名称: "); 
		scanf("%s", pnew->workadress);
		printf("\t\t\t\t家庭地址: "); 
		scanf("%s", pnew->homeadress);
		printf("\t\t\t\t联系电话: "); 
		scanf("%s", pnew->tel);
		printf("\t\t\t\t基本工资: "); 
		scanf("%lf", &pnew->salary);
		printf("\t\t\t\t津贴: "); 
		scanf("%lf", &pnew->allowance);
		printf("\t\t\t\t生活补贴: ");  
		scanf("%lf", &pnew->livingall);
		printf("\t\t\t\t电话费: "); 
		scanf("%lf", &pnew->telbill);
		printf("\t\t\t\t水电费: "); 
		scanf("%lf", &pnew->waterelectricbill);
		printf("\t\t\t\t房租: "); 
		scanf("%lf", &pnew->roomcharge);
		printf("\t\t\t\t所得税: "); 
		scanf("%lf", &pnew->incometax);
		printf("\t\t\t\t卫生费: ");
		scanf("%lf", &pnew->sanitationfee);
		printf("\t\t\t\t公积金: "); 
		scanf("%lf", &pnew->reservefund);
		
		shouldsalary = pnew->salary + pnew->allowance + pnew->livingall;       //应发工资 
		allconsume = pnew->telbill + pnew->waterelectricbill + pnew->roomcharge + 
				    pnew->incometax + pnew->sanitationfee + pnew->reservefund;      //合计扣款 
		income = shouldsalary - allconsume;      //实发工资 
		printf("\n\t\t\t\t应发工资:   %.1lf", shouldsalary); 
		printf("\n\t\t\t\t合计扣款:   %.1lf", allconsume); 
		printf("\n\t\t\t\t实发工资:   %.1lf", income); 
		
		struct Teacher* pTem = pHead;        //指向首节点（用于排序） 
		while (pTem->next != NULL)  
		{
			if (pnew->id < pTem->next->id)   //判断插入位置，以教师号排序 
			{
				pnew->next = pTem->next; 
				break; 
			}
			pTem = pTem->next;
		}     //以教师号排序
		pTem->next = pnew;    //连接新节点 （当数据为空时，录入的数据在第二节点，故首节点无教师信息）
		 
		getchar();      
		printf("\n\t\t\t\t是否需要再次录入新教师信息?（Y/N）: ");    
		char choice = getchar();
		if(choice != 'Y' && choice != 'y')        //不需要录入，按任意键退出 
			break;
	}
}

int IdIsExist(struct Teacher* pHead, int id)    //判断教师号是否重复 
{
	struct Teacher* pTem = pHead->next;         //录入时是从第二节点开始 ，建立指针pTem遍历链表 
	while (pTem != NULL)
	{
		if (pTem->id == id)
		return 1;
		pTem = pTem->next;
	}
	return 0;
}

