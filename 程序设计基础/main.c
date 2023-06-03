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
    pHead = ExtractTeacherOfFile();          //��ȡ�ļ����ݣ���ʼ������ 
    int key = -1;
	while (key != 0)
	{
		MainMenu();    //���˵�չʾ 
		scanf("%d", &key);  
		switch (key)
		{
			case 1: AddTeacherInformation(pHead);      //�����Ϣ 
					break;
        	case 2: ModifyTeacherInformation(pHead);   //�޸���Ϣ 
					break;
       	 	case 3: DeleteTeacherInformation(pHead);   //ɾ����Ϣ 
					break;
       		case 4: SearchMenu(pHead);                 //������Ϣ 
					break;
       	 	case 0: ReserveTeacherInformation(pHead);  //�����˳� 
					break;
		}
	}
	return 0;
}	
