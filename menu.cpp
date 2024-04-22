#include<stdio.h>
#include<Windows.h>
#include<malloc.h>
#include"model.h"
#include"card_service.h"
#include"global.h"
#include"tool.h"
#include"service.h"
#include"statistic.h"

//[������]		outputMenu
//[����]		���ϵͳ�˵�
//[����]		void
//[����ֵ]		void
void outputMenu() {
	//���ϵͳ�˵�
	printf("****------���ɼƷѹ���ϵͳ-----****\n");
	printf("|          1. ��ӿ�\t        |\n");
	printf("|          2. ��ѯ��\t        |\n");
	printf("|          3. �ϻ�\t\t|\n");
	printf("|          4. �»�\t\t|\n");
	printf("|          5. ��ֵ\t\t|\n");
	printf("|          6. �˷�\t\t|\n");
	printf("|          7. ��ѯͳ��\t        |\n");
	printf("|          8. ע����\t        |\n");
	printf("|          0. �˳�\t\t|\n");
	printf("****--------------------------****\n\n");
	printf("��ѡ��˵���ţ�");
}

//[������]		add
//[����]		����û�����Ϣ���ṹ�������������Ļ��ʾ
//[����]		void
//[����ֵ]		void
void add() {
	Card card;
	char name[30];		//��ʱ����û���
	char pwd[20];		//��ʱ�������
	struct tm* endTime;			//��ʱ��Ž�ֹʱ��
	struct tm* startTime;		//��ʱ��ſ���ʱ��
	endTime = startTime = (struct tm*)malloc(sizeof(struct tm));
	getCard();		//���ڲ���

step1: 
	printf("�����뿨�ţ�����Ϊ1~17����");
	scanf_s("%s", name,30);
	system("cls");
	//�ж�����Ŀ��ų����Ƿ���ϱ�׼
	if (strlen(name) > 17) {
		printf("���뿨�ų��ȳ������ֵ�����������룡\n");
		rewind(stdin);		//��ֹ���������쳣
		Sleep(1000);
		system("cls");
		goto step1;
	}
	//�ж�����Ŀ����Ƿ��Ѿ�����
	if (queryCardInfo(name) != NULL) {
		printf("����Ŀ����Ѿ����ڣ����������룡\n");
		rewind(stdin);		//��ֹ���������쳣
		Sleep(1000);
		system("cls");
		goto step1;
	}
	//������Ŀ��ű��汣�浽�ṹ�������
	strcpy_s(card.aName, strlen(name) + 1, name);
	system("cls");

step2: 
	printf("���������루����Ϊ1~7����");
	scanf_s("%s", pwd,20);
	system("cls");
	//�ж���������볤���Ƿ���ϱ�׼
	if (strlen(pwd) > 7) {
		printf("�������볤�ȳ������ֵ�����������룡\n");
		rewind(stdin);		//��ֹ���������쳣
		Sleep(1000);
		system("cls");
		goto step2;
	}
	//������Ŀ��ű��汣�浽�ṹ�������
	strcpy_s(card.aPwd, strlen(pwd) + 1,pwd);
	system("cls");
	
	printf("�����뿪����RMB����");
	scanf_s("%f", &card.fBalance);
	system("cls");

	card.fTotalUse = card.fBalance;		//�ۼƽ����ڿ������
	card.nDel = 0;						//ɾ����־
	card.nStatus = 0;					//��״̬
	card.nUseCount = 0;					//ʹ�ô���
	//����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ��
	//time��NULL����ȡ��ǰ����ʱ�䣨����ʱ�䣩��1970-01-01 00��00��00�������������
	card.tStart = card.tEnd = card.tLastTime = time(nullptr);
	
	//���ݿ���ʱ�䣬�����ֹʱ�䣬��Ч�ھ�Ϊһ��
	localtime_s(startTime,&card.tStart);
	localtime_s(endTime,&card.tEnd);
	endTime->tm_year += 1;				//��Ч��ֹʱ���������1��
	card.tEnd = mktime(endTime);		//���ֽ�ʱ��ת��������ʱ��

	printf("----------------��ӵĿ���Ϣ����----------------\n");
	printf("����\t\t    ����      ״̬    �������\n");
	printf("%-20s%-10s%-8d%-15.2f\n",card.aName,card.aPwd,card.nStatus,card.fBalance);

	//����Ϣ�Ƿ���ӳɹ�
	if (addCardInfo(card) == FALSE) {
		printf("------****------��ӿ���Ϣʧ�ܣ�------****------\n");
		system("pause");
		system("cls");
	}
	else {
		printf("------****------��ӿ���Ϣ�ɹ���------****------\n");
		system("pause");
		system("cls");
	}
}

//[������]		query
//[����]		��������Ŀ��ţ��ж����޸ÿ����еĻ������������Ϣ
//[����]		void
//[����ֵ]		void
void query() {
	Card* pCard = NULL;
	char name[18];		//���Ҫ��ѯ���û�����
	char aLastTime[30];		//���ָ����ʽ���ַ�����ʱ��
	int icha = 0;		//ѡ���ѯ��ʽ
	int nIndex = 0;		//����ѯ������Ϣ����

	printf("1.��ȷ��ѯ\n2.ģ����ѯ\n��ѡ���ѯ��ʽ��");
	scanf_s("%d", &icha);
	system("cls");
	
	if (icha == 1 || icha == 2) {
		printf("������Ҫ����Ŀ��ţ�����Ϊ1~17����");
		scanf_s("%s", name, 18);
		system("cls");
	}
	
	
	switch (icha) {
		case 1: {		//��ȷ��ѯ
			rewind(stdin);		//��ֹ���������쳣
			pCard = queryCardInfo(name);
			break;
		}
		case 2: {		//ģ����ѯ
			rewind(stdin);		//��ֹ���������쳣
			pCard = queryCardsInfo(name, &nIndex);
			break;
		}
		case 3: {		//��ѯȫ��
			rewind(stdin);		//��ֹ���������쳣
			 pCard = queryAllCardsInfo(&nIndex);
			 break;
		}	
		default: {
			rewind(stdin);		//��ֹ���������쳣
			printf("�������ѡ�����������飡\n");
			Sleep(1000);
			system("cls");
			return;
		}
	}

	//pCardΪNULL˵��û�в�ѯ������Ϣ
	if (pCard == NULL) {
		printf("------****------û�иÿ�����Ϣ��------****------\n");
		Sleep(1000);
		system("cls");
	}
	else {
		printf("------------********------------��ѯ���ÿ���Ϣ���£�------------********------------\n");
		printf("����\t\t  ״̬\t  ���\t\t �ۼƽ��\tʹ�ô���    �ϴ�ʹ��ʱ��\n");

		if (icha == 1) {		//��ȷ���
			timeToString(pCard->tLastTime, aLastTime);
		
			printf("%-18s%-8d%-15.2f%-15.2f%-12d%-30s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse,pCard->nUseCount, aLastTime);
			printf("�ϻ�");
			system("pause");
			system("cls");
		}
		else {		//ģ�������ȫ�����
			for (int i = 0; i < nIndex; i++) {
				timeToString(pCard[i].tLastTime, aLastTime);

				printf("%-18s%-8d%-15.2f%-15.2f%-12d%-30s\n", pCard[i].aName, pCard[i].nStatus, pCard[i].fBalance, pCard[i].fTotalUse, pCard[i].nUseCount, aLastTime);
				printf("�»�");
			}
			printf("---------------------------------��ѯ��%-3d������Ϣ��---------------------------------\n",nIndex);
													
			system("pause");
			system("cls");
			//�ͷŶ�̬������ڴ棻
			free(pCard);
		}
		pCard = NULL;
	}
}

//[������]		exitApp
//[����]		�˳�Ӧ�ó���
//[����]		void
//[����ֵ]		void
void exitApp() {
	releaseList();
}

//[������]		logon
//[����]		�����ϻ�����Ϣ������ѯ�����������Ϣ
//[����]		void
//[����ֵ]		void
void logon() {
	char aName[30];		//�ϻ�����
	char aPwd[20];		//�ϻ�������
//	Card* pCard = nullptr;
	char aLastTime[30];		//���ָ����ʽ���ַ���ʱ��
	LogonInfo* pInfo = NULL;
	int nResult = 0;

	memset(aName, 0, sizeof(aName));
	memset(aPwd, 0, sizeof(aPwd));
	memset(aLastTime, 0, sizeof(aLastTime));

	//��ʾ�������ϻ�����
	printf("�������ϻ����ţ�����Ϊ1-17����");
	scanf_s("%s", aName,30);
	rewind(stdin);		//��ֹ���������쳣

	//�ж�����Ŀ����Ƿ����Ҫ��
	if (strlen(aName) >= 18) {
		printf("���뿨�ų��ȳ������ֵ��\n");
		system("pause");
		system("cls");
		return;
	}

	//��ʾ�������ϻ����룻
	printf("�������ϻ����루����Ϊ1-7��:");
	scanf_s("%s", aPwd,20);
	rewind(stdin);		//��ֹ���������쳣
	system("cls");

	//�ж�����Ŀ��������Ƿ����Ҫ��
	if (strlen(aPwd) >= 8) {
		printf("���뿨�ų��ȳ������ֵ��\n");
		system("pause");
		system("cls");
		return;
	}

	//��ʼ�ϻ�
//	pCard = doLogon(aName, aPwd);
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	//�����ϻ��Ľ������ʾ�����ͬ��Ϣ
	nResult = doLogon(aName, aPwd, pInfo);


	//�����ϻ���Ϣ����ʾ��ͬ����Ϣ
	switch (nResult) {
		case 0:
			printf("------------�ϻ�ʧ�ܣ�------------\n"); break;
		case 1:
			printf("-----******-----�ϻ���Ϣ����-----******-----\n");
			printf("����              ���              �ϻ�ʱ��\n");		//18 18

			timeToString(pInfo->tLogon, aLastTime);

			//�����Ϣ
			printf("%-18s", pInfo->aCardName);
			printf("%-18.2f", pInfo->fBalance);
			printf("%s\n", aLastTime);
			printf("�ϻ��ɹ���\n");
			break;
		case 2:
			printf("------------�ÿ�����ʹ�ã�------------\n"); break;
		case 3:
			printf("------------���㣡------------\n"); break;

			
	}
	system("pause");
	system("cls");
	free(pInfo);
}

//[������]		settle
//[����]		�����»�����Ϣ����ѯ��������ϻ�����Ϣ
//[����]		void
//[����ֵ]		void
void settle() {
	char aName[18] = { 0 };		//����
	char aPwd[8] = { 0 };		//����
	int nResult = -1;		//�»����
	SettleInfo* pInfo = NULL;		//�»���Ϣ
	char aStartTime[30] = { 0 };	//�ϻ�ʱ��
	char aEndTime[30] = { 0 };		//�»�ʱ��

	//Ϊ�»���Ϣ��̬�����ڴ�
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));

	//��ʾ�������»�����
	printf("�������»����ţ�����Ϊ1-17����");
	scanf_s("%s", aName, 18);
	rewind(stdin);		//��ֹ���������쳣

	//�ж�����Ŀ����Ƿ����Ҫ��
	if (strlen(aName) >= 18) {
		printf("���뿨�ų��ȳ������ֵ��\n");
		system("pause");
		system("cls");
		return;
	}

	//��ʾ�������»����룻
	printf("�������»����루����Ϊ1-7��:");
	scanf_s("%s", aPwd, 8);
	rewind(stdin);		//��ֹ���������쳣
	system("cls");

	//�ж�����Ŀ��������Ƿ����Ҫ��
	if (strlen(aPwd) >= 8) {
		printf("���뿨�ų��ȳ������ֵ��\n");
		system("pause");
		system("cls");
		return;
	}

	//�����»�
	nResult = doSettle(aName, aPwd, pInfo);

	//�����»���������жϣ���ʾ��ͬ��Ϣ
	printf("------------******------------�»���Ϣ����------------******------------\n");
	switch (nResult) {
		case 0: {
			printf("�»�ʧ�ܣ�\n");
			system("pause");
			system("cls");
			break;
		}
		case 1: {
			//�»��ɹ���
			printf("����              ����           ���           ");
			printf("�ϻ�ʱ��                      �»�ʱ��                      \n");
			timeToString(pInfo->tStart, aStartTime);
			timeToString(pInfo->tEnd, aEndTime);

			//����»�����Ϣ
			printf("%-18s", pInfo->aCardName);
			printf("%-15.2f", pInfo->fAmount);
			printf("%-15.2f", pInfo->fBalance);
			printf("%-30s", aStartTime);
			printf("%-30s\n\n", aEndTime);
			printf("---------�»��ɹ�---------\n");
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			//δ��ʹ�û�����ע��
			printf("�ÿ�δ��ʹ�ã�\n");
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			//������
			printf("�����㣡\n");
			system("pause");
			system("cls");
			break;
		}
		default: {
			break;
		}
	}
	//�ͷŶ�̬������ڴ�
	free(pInfo);
}

//[������]		addMoney
//[����]		��ֵ
//[����]		void
//[����ֵ]		void
void addMoney() {
	char aName[18] = { 0 };		//����
	char aPwd[8] = { 0 };		//����
	float fAmount = 0;		//��ֵ���
	MoneyInfo sMoneyInfo;		//��ֵ��Ϣ

	printf("��������Ҫ��ֵ�Ŀ��ţ�1-17��:");
	scanf_s("%s", aName, 18);
	
	printf("���������루1-7��:");
	scanf_s("%s", aPwd,8);
	rewind(stdin);
	system("cls");

	printf("��������Ҫ��ֵ�Ľ�RMB��:");
	scanf_s("%f", &fAmount);
	rewind(stdin);
	system("cls");

	//�����ֵ���
	sMoneyInfo.fMoney = fAmount;

	//�жϳ�ֵ�Ƿ�ɹ�
	if (TRUE == doAddMoney(aName, aPwd, &sMoneyInfo)) {
		//��ʾ��ֵ��Ϣ
		printf("------****------��ֵ��Ϣ����------****------\n");

		//�����ͷ�ļ�
		printf("����              ��ֵ���    ���      \n");
		//�����ֵ����Ϣ
		printf("%-18s%-12.2f%-12.2f\n\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
		system("pause");
		system("cls");
	}
	else {
		printf("--------��ֵʧ��--------");
		Sleep(1000);
		system("cls");
	}
}

//[������]		refundMoney
//[����]		�˷�
//[����]		void
//[����ֵ]		void
void refundMoney() {
	char aName[18] = { 0 };		//����
	char aPwd[8] = { 0 };		//����
	int nResult = -1;		//�˷ѽ��
	MoneyInfo sMoneyInfo;		//�˷���Ϣ

	printf("��������Ҫ��ֵ�Ŀ��ţ�1-17��:");
	scanf_s("%s", aName, 18);
	
	printf("���������루1-7��:");
	scanf_s("%s", aPwd, 8);
	rewind(stdin);
	system("cls");

	//�����˷�
	nResult = doRefundMoney(aName, aPwd, &sMoneyInfo);
	//�����˷���Ϣ����ʾ��ͬ���
	switch (nResult) {
		case 0: { //�˷�ʧ��
			printf("--------�˷�ʧ�ܣ�--------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		case 1: {	//�˷ѳɹ�
			//��ʾ�˷���Ϣ
			printf("----****----�˷���Ϣ����----****----\n");
			//�����ͷ
			printf("����              �˷ѽ��    ���\n");
			//����˷ѿ���Ϣ
			printf("%-18s%-12.2f%-12.2f\n\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
			system("pause");
			system("cls");
			break;
		}
		case 2: { //����ʹ�û��Ѿ�ע��
			printf("--------�ÿ�����ʹ�û�����ע����--------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		case 3: {	//������
			printf("--------�ÿ����㣡--------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		default: {
			break;
		}
	}
}

//[������]		annual
//[����]		ע��
//[����]		void
//[����ֵ]		void
void annual() {
	Card card;
	printf("��������Ҫע���Ŀ��ţ�1-17��:");
	scanf_s("%s", card.aName, 18);
	
	printf("���������루1-7��:");
	scanf_s("%s", card.aPwd, 8);
	rewind(stdin);
	system("cls");

	if (FALSE == annulCard(&card)) {
		printf("--------ע����ʧ�ܣ�--------\n");
		Sleep(1000);
		system("cls");
		return;
	}
	else {
		//��ʾע����Ϣ
		printf("----****----ע����Ϣ����----****----\n");
		//�����ͷ
		printf("����              �˿���\n");
		//����˷ѿ���Ϣ
		printf("%-18s%-12.2f\n\n", card.aName, card.fBalance);
		system("pause");
		system("cls");
		return;
	}
}

//[������]		statistic
//[����]		����ͳ��
//[����]		void
//[����ֵ]		void
void statistic() {
	int nSelection = -1;
	printf("1.���·�ͳ���û�ʹ����Ӫҵ��\n");
	printf("2.���û�����ͳ�Ƹ��û�ʹ�ý��\n");
	printf("0.����\n");
	printf("��ѡ����Ҫ���е�ͳ�Ʋ�����");

	//��ȡ�û�����
	scanf_s("%d", &nSelection);
	system("cls");
	
	switch (nSelection) {
		case 0: {
			return;
		}
		case 1: {
			statisticMonth();
			break;
		}
		case 2: {
			statisticUser();
			break;
		}
		default: {
			printf("�����������\n");
			rewind(stdin);
			Sleep(1000);
			return;
		}
	}
}