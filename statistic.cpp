#include<stdio.h>
#include<time.h>
#include<windows.h>
#include"tool.h"
#include"global.h"
#include"model.h"
#include"billing_service.h"


//[������]		statisticMonth
//[����]		ͳ��ÿ���ϻ���ȡ���
//[����]		void
//[����ֵ]		void
void statisticMonth() {
	int nMonth,nYear;
	float fTotalUse = 0.0;
	time_t tNow = time(nullptr);	//��ǰʱ��

	printf("��������Ҫͳ�Ƶ�����·ݣ�");
	scanf_s("%d%d",&nYear,&nMonth);
	rewind(stdin);
	system("cls");
	
	//�ж�����ʱ���Ƿ����Ҫ��
	if (nMonth > 12 || nMonth < 1 || nYear > timeToYear(tNow)) {
		printf("�������ͳ��ʱ�����\n");
		Sleep(1000);
		system("cls");
		return;
	}

	if (FALSE == doStatisticMonth(nYear, nMonth, &fTotalUse)) {
		printf("ͳ��ʧ�ܣ�\n");
		system("pause");
		system("cls");
		return;
	}

	//���
	printf("��ѯ������Ϣ���£�\n%d��%d�µ���ʹ�ý��Ϊ��%-12.2f\n", nYear, nMonth, fTotalUse);
	system("pause");
	system("cls");
	return;
}

//[������]		statisticUser
//[����]		ͳ��һ���û��ϻ�����
//[����]		void
//[����ֵ]		void
void statisticUser() {
	char aName[18];		//���ڴ���û����ƣ�
	char aStartTime[30] = {0};		//��ſ�ʼʱ��
	char aLastTime[30] = {0};		//��Ž���ʱ��
	int nCount = 0;		//ͳ����Ŀ
	lpBillingNode node = NULL;
	printf("��������Ҫ��ѯ���û����ţ�");
	scanf_s("%s", aName, 18);
	system("cls");

	if (FALSE == doStatisticUser(aName, &node)) {
		printf("��ѯ����\n");
		system("pause");
		system("cls");
		return;
	}

	if (node == NULL) {
		printf("δ��ѯ���ÿ��ŵ�ʹ�����ݣ�\n");
		system("pause");
		system("cls");
		return;
	}
	else {
		printf("����%s��ʹ����Ϣ���£�\n", aName);		//�����ͷ
		printf("--------------------------------------------------------------------------------------------\n");
		printf("�ϻ�ʱ��                      �»�ʱ��                      ʹ�ý��       �Ƿ����  �Ƿ�ע��\n");
		while (node->next != NULL) {
			node = node->next;
			timeToString(node->data.tStart, aStartTime);
			printf("%-30s", aStartTime);
			
			if (node->data.tEnd == 0) {		//���tEndΪ0��֤��δ�»���ִ�����δ�»�����
				printf("δ�»�                        ");
			}
			else {
				timeToString(node->data.tEnd, aLastTime);
				printf("%-30s", aLastTime);
			}
			printf("%-15.2f", node->data.fAmount);
			printf("%-10d%-10d\n", node->data.nStatus, node->data.nDel);
			nCount++;
		}
		printf("---------------------------------------�û���%-3d����¼-------------------------------------------\n",nCount);
		system("pause");
		system("cls");
		return;
	}
}