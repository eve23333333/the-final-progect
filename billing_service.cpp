#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include"billing_file.h"
#include"global.h"
#include"model.h"
#include"tool.h"

lpBillingNode billingList = NULL;

//[������]		addBilling
//[����]		�ϻ�ʱ���������Ϣ���ļ�
//[����]		pName���ϻ����ţ�pBilling��ָ��������Ϣ�ṹ��
//[����ֵ]		TRUE������ɹ�	FALSE������ʧ��
int addBilling(const char* pName, Billing* pBilling) {
	//��������Ϣд��ṹ��
	strcpy_s(pBilling->aCardName, pName);		//�ϻ�����
	pBilling->tStart = time(nullptr);		//�ϻ�ʱ��
	pBilling->tEnd = 0;		//�»�ʱ��		��δ�»������עΪ0��
	pBilling->fAmount = 0;		//���ѽ��
	pBilling->nStatus = 0;		//����״̬	0δ����1����
	pBilling->nDel = 0;		//ɾ��״̬ 0δɾ1ɾ

	//������Ϣ�ṹ��д���ļ�
	if (saveBilling(pBilling, BILLINGPATH) == FALSE) {
		return FALSE;
	}
	return TRUE;
}

//[������]		intiBillingList
//[����]		��ʼ���Ʒ���Ϣ����
//[����]		void
//[����ֵ]		void
void initBillingList() {
	lpBillingNode head = NULL;
	if (billingList == NULL) {
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		head->next = NULL;
		billingList = head;
	}
}


//[������]		releaseBillingList
//[����]		�ͷżƷ���Ϣ����
//[����]		void
//[����ֵ]		void
void releaseBillingList() {
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	//��������
	while (cur != NULL) {
		next = cur->next;		//����ڴ��ͷ�ǰ��next��������
		free(cur);
		cur = next;
	}
	billingList = NULL;
}

//[������]		getBilling
//[����]		�ӼƷ���Ϣ�ļ��У���ȡ�Ʒ���Ϣ�����浽������
//[����]		void
//[����ֵ]		��ȡ�ɹ�����TRUE�����򷵻�FALSE
int getBilling() {
	int i = 0;
	int nCount = 0;		//ʵ�ʵļƷ���Ϣ��
	Billing* pBilling = NULL;		// ��ȡ����һ���Ʒ���Ϣ
	lpBillingNode node = NULL;		//��ǰ��β�ڵ�
	lpBillingNode cur = NULL;		//��ӵ������еĽڵ�

	//����������Ѿ����ڵ�����
	if (billingList != NULL) {
		releaseBillingList();
	}
	//��ʼ������
	initBillingList();

	//��ȡ�ļ��мƷ���Ϣ����
	nCount = getBillingCount(BILLINGPATH);
	
	//��̬�����ڴ������������еļƷ���Ϣ���൱�ڽṹ�����飬pCard�൱��������
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);
	if (pBilling != NULL) {
		//�������FALSE���ȡʧ��
		if (readBilling(pBilling, BILLINGPATH) == FALSE) {
			free(pBilling);
			return FALSE;
		}

		//����ȡ����Ϣ�����浽������
		for (i = 0, node = billingList; i < nCount; i++) {
			//Ϊ�ڵ�����ڴ�
			cur = (lpBillingNode)malloc(sizeof(BillingNode));
			//��������ڴ�ʧ�ܣ��򷵻�
			if (cur == NULL) {
				free(pBilling);
				return FALSE;
			}
			//��ʼ���µĿռ䣬ȫ����ֵΪ0��
			memset(cur, 0, sizeof(BillingNode));

			//�����ݱ��浽������
			cur->data = pBilling[i];
			cur->next = NULL;

			//�������ӵ������β��
			node->next = cur;
			node = cur;
		}
		//�ͷ��ڴ�
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}

//[������]		queryBilling
//[����]		�ڼƷ���Ϣ�����У���ѯ��Ӧ�Ŀ��Ʒ���Ϣ������ȡ���������е�������
//[����]		pName:ָ���û������Ҫ��ѯ�Ŀ��� pIndex��ָ���ѯ���Ŀ���Ϣ�������е�������
//[����ֵ]		ָ���ѯ���ļƷ���Ϣָ��
Billing* queryBilling(const char* pName, int* pIndex) {
	lpBillingNode node = NULL;
	int nIndex = 0;

	//�ӼƷ���Ϣ�ļ��ж�ȡ�Ʒ���Ϣ�б�ʧ�ܷ���NULL
	if (getBilling() == FALSE) {
		return NULL;
	}

	//nodeָ���һ�����ݣ�׼����ʼ����
	node = billingList;		//��һ������

	//��������ָ���βNULLʱ������
	while (node != NULL) {
		//�ж��ڱ����Ŀ����У������Ƿ����pName�ַ�����
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0) {
			//������ͬ����û�н���Ʒ���Ϣ
			return &node->data;
		}

		//�ƶ�����һ�����
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}

//[������]		doStatisticMonth
//[����]		����ͳ��ȫ��ʹ�����
//[����]		nYear:���           nMonth���·�		fTotalUse��ȫ��ʹ�ý��
//[����ֵ]		TRUE:�ɹ�	FALSE��ʧ��
int doStatisticMonth(const int nYear, const int nMonth, float* fTotalUse) {
	lpBillingNode node = NULL;
	*fTotalUse = 0.0;	//��ʼ�����

	//�ӼƷ���Ϣ�ļ��ж�ȡ�Ʒ���Ϣ�б�ʧ�ܷ���NULL
	if (getBilling() == FALSE) {
		return NULL;
	}

	//nodeָ���һ�����ݣ�׼����ʼ����
	node = billingList;		//��һ������
	while (node != NULL) {
		
		if ((node->data.nStatus == 1) && (timeToYear(node->data.tEnd) == nYear) && (timeToMonth(node->data.tEnd) == nMonth)) {
			//�ѽɷѲ���������»�ʱ�����������ѽ��
			(*fTotalUse) = (*fTotalUse) + node->data.fAmount;
		}
		node = node->next;
	}
	return TRUE;
}

//[������]		doStatisticUser
//[����]		ͳ��һλ�û���ʹ������
//[����]		aName���û��� curHead��ָ�����ݵ�ͷָ��ĵ�ַ��
//[����ֵ]		TRUE:�ɹ�	FALSE��ʧ��
int doStatisticUser(const char* aName,lpBillingNode* curHead) {

	int i = 0;
	int nCount = 0;		//ʵ�ʵļƷ���Ϣ��
	Billing* pBilling = NULL;		// ��ȡ����һ���Ʒ���Ϣ
	lpBillingNode node = NULL;		//��ǰ��β�ڵ�
	lpBillingNode cur = NULL;		//��ӵ������еĽڵ�

	//����������Ѿ����ڵ�����
	if (billingList != NULL) {
		releaseBillingList();
	}
	//��ʼ������
	initBillingList();

	//��ȡ�ļ��мƷ���Ϣ����
	nCount = getBillingCount(BILLINGPATH);

	//��̬�����ڴ������������еļƷ���Ϣ���൱�ڽṹ�����飬pCard�൱��������
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);
	if (pBilling != NULL) {
		//�������FALSE���ȡʧ��
		if (readBilling(pBilling, BILLINGPATH) == FALSE) {
			free(pBilling);
			return FALSE;
		}

		//����ȡ����Ϣ�����浽������
		for (i = 0, node = billingList; i < nCount; i++) {
			if (strcmp(pBilling[i].aCardName, aName) == 0) {		//���ƥ��ɹ��������ݱ��浽����
				//Ϊ�ڵ�����ڴ�
				cur = (lpBillingNode)malloc(sizeof(BillingNode));
				//��������ڴ�ʧ�ܣ��򷵻�
				if (cur == NULL) {
					free(pBilling);
					return FALSE;
				}
				//��ʼ���µĿռ䣬ȫ����ֵΪ0��
				memset(cur, 0, sizeof(BillingNode));

				//�����ݱ��浽������
				cur->data = pBilling[i];
				cur->next = NULL;
				
				//�������ӵ������β��
				node->next = cur;
				node = cur;
			}
		}
		*curHead = billingList;
		//�ͷ��ڴ�
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}