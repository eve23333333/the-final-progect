#include<stdio.h>
#include<Windows.h>
#include"menu.h"
#include"global.h"

//[������]	main
//[����]		������ں���
//[����]		void
//[����ֵ]	0:���������˳�����0�������쳣��
int main() {
	
	/*printf("------��ӭʹ�üƷѹ���ϵͳ------\n");
	printf("---------��������ʽ��ս--------\n\n");
	Sleep(1000);
	system("cls");*/
	//����ѡ��Ĳ˵���Ŀ�ı�ţ�
	int nSelection = -1;

	do{
		//���ѡ��˵���
		outputMenu();
		
		nSelection = -1;
		scanf_s("%d", &nSelection);
		system("cls");
		switch (nSelection) {
		case 0: {
			rewind(stdin);		//��ֹ���������쳣
			exitApp();
			break;
		}
		case 1: {
			printf("----------��ӿ�----------\n");
			rewind(stdin);		//��ֹ���������쳣
			add();
			break;
		}
		case 2: {
			printf("----------��ѯ��----------\n");
			rewind(stdin);		//��ֹ���������쳣
			query();
			break;
		}
		case 3: {
			printf("----------�ϻ�----------\n");
			rewind(stdin);		//��ֹ���������쳣
			logon();
			break;
		}
		case 4: {
			printf("----------�»�----------\n");
			rewind(stdin);		//��ֹ���������쳣
			settle();
			break;
		}
		case 5: {
			printf("----------��ֵ----------\n");
			rewind(stdin);		//��ֹ���������쳣
			addMoney();
			break;
		}
		case 6: {
			printf("----------�˷�----------\n");
			rewind(stdin);		//��ֹ���������쳣
			refundMoney();
			break;
		}
        case 7: {
			printf("----------ͳ��----------\n");
			rewind(stdin);		//��ֹ���������쳣
			statistic();
			break;
		}		
		case 8: {
			printf("----------ע����----------\n");
			rewind(stdin);		//��ֹ���������쳣
			annual();
			break;
		}
		default: {
			rewind(stdin);		//��ֹ���������쳣
			printf("�������ѡ�����������飡\n");
			Sleep(1000);
			system("cls");
		}
		}//��鹦���Ƿ���ڣ�
	} while (nSelection != 0);
	printf("------��ӭ�´�ʹ��------\n");
	return 0;
}