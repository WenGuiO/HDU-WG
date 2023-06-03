#include "Teacher.h"
#include "SearchInformation.h"
void SearchMenu(struct Teacher *pHead)
{
	int key = -1;
	while(key != 0)    //确保查找完成可回到主界面 
	{
		system("cls");
		printf("\n\n\n");
	    printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |             查找教师信息                |\n");
		printf("\t\t\t\t |                                         |\n");
		printf("\t\t\t\t |            1.按教师号查找               |\n");
		printf("\t\t\t\t |            2.按姓名查找                 |\n");
		printf("\t\t\t\t |            3.查看所有教师信息           |\n");
		printf("\t\t\t\t |            0.退出                       |\n");
		printf("\t\t\t\t |                                         |\n");
		printf("\t\t\t\t -------------------------------------------\n\n");
		printf("\t\t\t请选择功能: ");
		scanf("%d",&key);
		
		switch(key)
		{
			case 1: SearchTeacherById(pHead);      //教师号查找 
					break;
			case 2: SearchTeacherByName(pHead);    //姓名查找 
					break; 
			case 3: ShowAllTeacher(pHead);         //查看所有教师信息 
					break; 
		}
	}
} 

void ShowTeacherInformation(struct Teacher *pTem)  //展示当前教师数据 
{
	double shouldsalary, allconsume, income;
	printf("\n\n\t\t\t\t教师号-----%d", pTem->id);
	printf("\n\t\t\t\t姓名-------%s", pTem->name);
	printf("\n\t\t\t\t性别-------%s", pTem->gender);
	printf("\n\t\t\t\t工作单位---%s", pTem->workadress);
	printf("\n\t\t\t\t家庭地址---%s", pTem->homeadress);
	printf("\n\t\t\t\t联系电话---%s", pTem->tel);
	printf("\n\t\t\t\t基本工资---%.1lf", pTem->salary);
	printf("\n\t\t\t\t津贴-------%.1lf", pTem->allowance);
	printf("\n\t\t\t\t生活补贴---%.1lf", pTem->livingall);
	printf("\n\t\t\t\t电话费-----%.1lf", pTem->telbill);
	printf("\n\t\t\t\t水电费-----%.1lf", pTem->waterelectricbill);
	printf("\n\t\t\t\t房租-------%.1lf", pTem->roomcharge);
	printf("\n\t\t\t\t所得税-----%.1lf", pTem->incometax);
	printf("\n\t\t\t\t卫生税-----%.1lf", pTem->sanitationfee);
	printf("\n\t\t\t\t公积金-----%.1lf", pTem->reservefund);
	
	shouldsalary = pTem->salary + pTem->allowance + pTem->livingall;       //应发工资 
	allconsume = pTem->telbill + pTem->waterelectricbill + pTem->roomcharge + 
			pTem->incometax + pTem->sanitationfee + pTem->reservefund;      //合计扣款 
	income = shouldsalary - allconsume; 
	printf("\n\t\t\t\t★应发工资----%.1lf", shouldsalary);
	printf("\n\t\t\t\t★合计扣款----%.1lf", allconsume);
	printf("\n\t\t\t\t★实发工资---%.1lf", income);
	printf("\n\n\t\t\t  *************************************"); 
	return;
}

void SearchTeacherById(struct Teacher *pHead)
{
	while(1)    //由用户决定是否循环（是否再次查找） 
	{
		int flag = 1;    //用以判断教师是否存在，存在则为 0 
		char choice;         //用以判断是否还需要查找 
		system("cls");
		printf("\n\n\n");
	    printf("\t\t\t\t -------------------------------------------\n");
		printf("\t\t\t\t |             以教师号查找                |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\n");
		printf("\t\t\t\t请输入要查找的教师号: ");
		int id; 
		scanf("%d", &id);
		
		struct Teacher* pTem = pHead->next;
		while (pTem != NULL)        //遍历链表 
		{
			if(pTem->id == id)
				{
					ShowTeacherInformation(pTem);     //展示此教师信息 
				    flag = 0; 
				    break;
				}
			pTem = pTem->next;
		}
		
		if(flag)
			printf("\n\t\t\t\t该教师号不存在！！\n"); 
			
			
		getchar();       //停顿 
		printf("\n\n\t\t\t\t是否还需要查找？（Y/N): ");
		scanf("%c", &choice);
		if(choice != 'Y' && choice != 'y')    //不需再次查找则按任意键退出 
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
		printf("\t\t\t\t |              以姓名查找                 |\n");
		printf("\t\t\t\t -------------------------------------------\n");
		printf("\n");
		printf("\t\t\t\t请输入要查找的教师姓名: ");
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
			printf("\n\n\t\t\t\t该教师不存在！！"); 
			
		getchar();
		printf("\n\n\t\t\t\t是否还需要查找？（Y/N): ");
		char choice;
		scanf("%c", &choice); 
		if(choice != 'Y' && choice != 'y')
			break;
	}
}

void ShowAllTeacher(struct Teacher *pHead)
{ 
	int count = 0;    //判断是否存在教师数据 
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\t\t\t\t |           查看所有教师信息              |\n");
	printf("\t\t\t\t -------------------------------------------\n");
	printf("\n");
	printf("\t\t\t  所有教师信息如下："); 
	
	struct Teacher* pTem = pHead->next;
	while(pTem != NULL)
	{
		count++; 
		ShowTeacherInformation(pTem);
		pTem = pTem->next;
	} 
	
	if(count == 0)
		printf("\n\n\t\t\t\t  暂未录入任何教师信息！！"); 
	system("pause"); 
}
