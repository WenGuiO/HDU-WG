#include "Teacher.h"
#include "ExtractFile.h"
#include "AddInformation.h"
#include "DeleteInformation.h" 
#include "ModifyInformation.h"
#include "ReserveFile.h"
#include "SearchInformation.h"

int main()
{
    struct Teacher* pHead = NULL;
    pHead = ExtractTeacherOfFile();          //提取文件数据，初始化链表 
    int key = -1;
	while (key != 0)
	{
		MainMenu();    //主菜单展示 
		scanf("%d", &key);  
		switch (key)
		{
			case 1: AddTeacherInformation(pHead);      //添加信息 
					break;
        	case 2: ModifyTeacherInformation(pHead);   //修改信息 
					break;
       	 	case 3: DeleteTeacherInformation(pHead);   //删除信息 
					break;
       		case 4: SearchMenu(pHead);                 //查找信息 
					break;
       	 	case 0: ReserveTeacherInformation(pHead);  //保存退出 
					break;
		}
	}
	return 0;
}	
