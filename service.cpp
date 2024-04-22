#include<stdio.h>
#include"model.h"
#include"global.h"
#include"card_file.h"
#include"card_service.h"
#include"billing_file.h"
#include"billing_service.h"
#include"money_file.h"

//[������]		addCardInfo
//[����]		��ӿ���Ϣ
//[����]		card	����Ϣ�ṹ��
//[����ֵ]		TRUE����ɹ� FALSE����ʧ��
int addCardInfo(Card card) {
	//������Ϣ���浽�ļ���
	if (TRUE == saveCard(&card, CARDPATH)) {
		return TRUE;
	}
	return FALSE;
}

//[������]		queryCardsInfo
//[����]		ģ����ѯ����Ϣ
//[����]		pName��ָ���û������Ҫ��ѯ�Ŀ���
//			pIndex:ָ��鵽�Ŀ���Ϣ������
//[����ֵ]		ָ����Ϣ�ṹ���ָ��
Card* queryCardsInfo(const char* pName, int* pIndex) {
	Card* pCard = NULL;
	pCard = queryCards(pName, pIndex);
	return pCard;
}

//[������]		queryCardInfo
//[����]		��ȷ��ѯ����Ϣ
//[����]		pName��ָ���û������Ҫ��ѯ�Ŀ���
//[����ֵ]		ָ����Ϣ�ṹ���ָ��
Card* queryCardInfo(const char* pName) {
	Card* pCard = NULL;
	pCard = queryCard(pName);
	return pCard;
}

//[������]		queryAllCardsInfo
//[����]		��ѯȫ������Ϣ
//[����]		pIndex:ָ��鵽�Ŀ���Ϣ������
//[����ֵ]		ָ����Ϣ�ṹ���ָ��
Card* queryAllCardsInfo(int* pIndex) {
	Card* pCard = NULL;
	pCard = queryAllCards(pIndex);
	return pCard;
}

//[������]		doLogon
//[����]		�����ϻ�����
//[����]		pName:�ϻ�����	pPwd���ϻ�����	pInfo��ָ���ϻ���Ϣ�ṹ��
//[����ֵ]	TRUE���ϻ��ɹ� FALSE���ϻ�ʧ��
int doLogon(const char* pName, const char* pPwd, LogonInfo* pInfo) {
	Card* pCard = NULL;
	int nIndex = 0;		//ƥ��Ŀ�����Ϣ����������е���ţ����ڸ��¿���Ϣ
	Billing billing;		//�Ʒ���Ϣ

	//���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�������
	pCard = checkCard(pName, pPwd, &nIndex);
	
	//�������ϢΪ�գ�����û�иÿ���Ϣ���ϻ�ʧ��
	if (pCard == NULL) {
		return FALSE;
	}
	//ֻ��δ�ϻ��Ŀ������ϻ�
	if (pCard->nStatus == 1) {
		printf("�ÿ������ϻ��У�\n");
		return UNUSE;
	}
	if (pCard->nStatus == 2) {
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
	}
	//������0�Ĳ����ϻ�
	if (pCard->fBalance <= 0) {
		printf("���㣬���ֵ�����ϻ���\n");
		return ENOUGHMONEY;
	}

	//���������еĿ���Ϣ��
	pCard->nStatus = 1;
	pCard->nUseCount++;
	pCard->tLastTime = time(nullptr);

	//�����ļ��еĿ���Ϣ
	if (updateCard(pCard, CARDPATH, nIndex) == FALSE) {
		//���ļ�����ʧ�ܷ��أ��ɹ����ܼ���������Ѽ�¼
		return FALSE;
	}

	//������Ѽ�¼
	strcpy_s(billing.aCardName, pName);		//�ϻ�����
	billing.tStart = time(nullptr);		//�ϻ�ʱ��
	billing.tEnd = 0;		//�»�ʱ��
	billing.nStatus = 0;		//����״̬				//ע���޸Ļ�ԭ��
	billing.fAmount = 0;		//���ѽ��
	billing.nDel = 0;		//ɾ����ʶ

	//�Ƚ��Ʒ���Ϣ���浽�ļ���
	if (TRUE == saveBilling(&billing, BILLINGPATH)) {
		//��װ�ϻ���Ϣ
		strcpy_s(pInfo->aCardName, pName);
		pInfo->fBalance = pCard->fBalance;
		pInfo->tLogon = billing.tStart;
		return TRUE;
	}
	return FALSE;
}

//[������]		releaseList
//[����]		�˳�Ӧ��ʱ���ͷ������ڴ�
//[����]		void
//[����ֵ]		void
void releaseList() {
	releaseCardList();		//�ͷſ���Ϣ�����ڴ�
	releaseBillingList();		//�ͷżƷ���Ϣ�����ڴ�
}


//[������]		getAmount
//[����]		�����ϻ�ʱ�䣬�������ѽ��
//[����]		�ϻ�ʱ��
//[����ֵ]		���ѽ��
double getAmount(time_t tStart) {
	double dbAmount = 0;		//���ѽ��
	int nCount = 0;		//�ϻ���ʱ�䵥Ԫ����ÿ����Ԫ15����
	int nSec = 0;		//����ʱ�䣨��λ���룩
	int nMinutes = 0;		//����ʱ�䣨��λ���룩
	time_t tEnd = time(nullptr);		//����ʱ��Ϊ��ǰʱ��

	//��������ʱ��
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	//�������ѵ�ʱ�䵥Ԫ��
	if (nMinutes % UNIT == 0) {
		nCount = nMinutes / UNIT;		//����
	}
	else {
		nCount = nMinutes / UNIT + 1;		//������
	}
	//�������ѽ��
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

//[������]		doSettle
//[����]		�����»�����
//[����]		pName���»�����	pPwd:�»����룻pInfo:ָ���»���Ϣ�ṹ��
//[����ֵ]		�»���Ϣֵ����ͬ��������ͬ��Ϣ
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo) {
	Card* pCard = NULL;
	Billing* pBilling = NULL;
	int nIndex = 0;		//����Ϣ�������е�������
	int nPosition = 0;		//�Ʒ���Ϣ�������е�������
	double dbAmount = 0.0;		//���ѽ��
	float fBalance = 0.0;		//���

	//��ѯ�ϼ���
	pCard = checkCard(pName, pPwd, &nIndex);

	//���Ϊ�գ���ʾû�иÿ���Ϣ������FALSE
	if (pCard == NULL) {
		printf("�޸ÿ���Ϣ�����������룡\n");
		return FALSE;
	}
	//�жϸÿ��Ƿ������ϻ���ֻ���ϻ��еĿ����ܽ����»�����
	if (pCard->nStatus != 1) {
		printf("�ÿ�δ�ϻ���\n");
		return UNUSE;
	}
	//���ݿ��ţ���ѯ�Ʒ���Ϣ
	pBilling = queryBilling(pName, &nPosition);

	//�����ѯ���Ʒ���ϢΪ�ձ�ʾ�ļ�ʧ��
	if (pBilling == NULL) {
		printf("�޸ÿ���Ϣ�����������룡\n");
		return FALSE;
	}

	//�������ѽ��
	dbAmount = getAmount(pBilling->tStart);

	//������С�����ѽ������»�
	fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance < 0) {
		return ENOUGHMONEY;
	}

	//���¿���Ϣ
	pCard->fBalance = fBalance;		//���
	pCard->nStatus = 0;		//״̬
	pCard->tLastTime = time(nullptr);		//�ϴ�ʹ��ʱ��
	//�����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex)) {
		return FALSE;
	}

	//���¼Ʒ���Ϣ
	pBilling->fAmount = (float)dbAmount;		//������Ϣ
	pBilling->nStatus = 1;		//״̬���ѽ���
	pBilling->tEnd = time(nullptr);		//�»�ʱ��

	//�����ļ��еļƷ���Ϣ
	if (FALSE == updateBilling(pBilling, BILLINGPATH, nPosition)) {
		return FALSE;
	}

	//��װ�»���Ϣ
	strcpy_s(pInfo->aCardName, pName);	//����
	pInfo->fAmount = (float)dbAmount;		//���ѽ��
	pInfo->fBalance = fBalance;		//���
	pInfo->tStart = pBilling->tStart;		//�ϻ�ʱ��
	pInfo->tEnd = time(nullptr);		//�»�ʱ��

	return TRUE;
}

//[������]		 doAddMoney
//[����]		���г�ֵ����
//[����]		pName:��ֵ����	pPwd:��ֵ����	pMoneyInfo:��ֵ��Ϣ
//[����ֵ]		int:��ֵ�Ľ��	TRUE����ֵ�ɹ�	FALSE����ֵʧ��
int doAddMoney(const char* pName, const char* pPwd, MoneyInfo* pMoneyInfo) {
	Card* pCard = NULL;		//����Ϣ�������е�������
	int nIndex = 0;
	Money sMoney;

	//��ѯ��ֵ�� 
	pCard = checkCard(pName, pPwd, &nIndex);

	//�������ϢΪ�գ���ʾδ�ҵ�����Ϣ
	if (pCard == NULL) {
		printf("���޸ÿ������ܳ�ֵ��\n");
		return FALSE;
	}
	//�жϿ��Ƿ����ϻ���ֻ��δʹ�ú������ϻ��Ŀ����ܽ��г�ֵ����
	if (pCard->nStatus != 0 && pCard->nStatus != 1) {
		return FALSE;
	}
	//������Գ�ֵ�����¿���Ϣ
	pCard->fBalance += pMoneyInfo->fMoney;
	pCard->fTotalUse += pMoneyInfo->fMoney;

	//�����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex)) {
		return TRUE;
	}

	//��װ��ֵ��Ϣ
	strcpy_s(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(nullptr);
	sMoney.nStatus = 0;
	sMoney.fMoney = pMoneyInfo->fMoney;
	sMoney.nDel = 0;

	if (TRUE == saveMoney(&sMoney, MONEYPATH)) {
		strcpy_s(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fBalance = pCard->fBalance;
		return TRUE;
	}
	return FALSE;
}

//[������]		 doRefundMoney
//[����]		�����˷Ѳ���
//[����]		pName:�˷ѿ���	pPwd:������	pMoneyInfo:�˷���Ϣ
//[����ֵ]		int:��ֵ�Ľ��	TRUE����ֵ�ɹ�	FALSE����ֵʧ��
int doRefundMoney(const char* pName, const char* pPwd, MoneyInfo* pMoneyInfo) {
	Card* pCard = NULL;		//����Ϣ�������е�������
	int nIndex = 0;
	float fBalance = 0.0;
	Money sMoney;

	//��ѯ��ֵ�� 
	pCard = checkCard(pName, pPwd, &nIndex);

	//�������ϢΪ�գ���ʾδ�ҵ�����Ϣ
	if (pCard == NULL) {
		printf("���޸ÿ��������˷ѣ�\n");
		return FALSE;
	}
	//�жϿ��Ƿ����ϻ���ֻ��δʹ�ò��ܽ����˷Ѳ���
	if (pCard->nStatus != 0) {
		return UNUSE;
	}
	//������Ϊ0�����˷�
	fBalance = pCard->fBalance;
	if (fBalance <= 0) {
		return ENOUGHMONEY;
	}
	
	//��������˷ѣ����¿���Ϣ
	pCard->fBalance = 0;
	pCard->fTotalUse -= fBalance;

	//�����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex)) {
		return FALSE;
	}

	//��װ�˷���Ϣ
	strcpy_s(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(nullptr);
	sMoney.nStatus = 1;
	sMoney.fMoney = fBalance;
	sMoney.nDel = 0;

	if (TRUE == saveMoney(&sMoney, MONEYPATH)) {
		strcpy_s(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fMoney = sMoney.fMoney;
		pMoneyInfo->fBalance = pCard->fBalance;
		return TRUE;
	}
	return FALSE;
}
//[������]		annulCard
//[����]		ע����
//[����]		pCard ����Ϣ�ṹ��
//[����ֵ]		TRUE�ɹ� FALSEʧ��
int annulCard(Card* pCard) {
	Card* pCurCard = NULL;
	int nIndex = -1;	//����
	if (pCard == NULL) {
		return FALSE;
	}
	//���ݿ��ź����룬��ѯ����Ϣ
	pCurCard = checkCard(pCard->aName, pCard->aPwd, &nIndex);

	if (pCurCard == NULL) {
		return FALSE;
	}
	//ֻ��δ�ϻ��Ŀ�����ע��
	if (pCurCard->nStatus != 0) {
		return FALSE;
	}

	//����ע���������
	pCard->fBalance = pCurCard->fBalance;
	//����ע������Ϣ
	pCurCard->nStatus = 2;		//״̬�޸�Ϊע��
	pCurCard->nDel = 1;		//ɾ����Ǳ��Ϊ��ɾ��
	pCurCard->fBalance = 0;		//�����Ϊ0
	pCurCard->tLastTime = time(nullptr);		//���ʹ��ʱ��

	//���¿����ļ��е���Ϣ
	if (FALSE == updateCard(pCurCard, CARDPATH, nIndex)) {
		return FALSE;
	}
	return TRUE;
}