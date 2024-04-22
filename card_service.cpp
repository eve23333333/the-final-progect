#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include"card_file.h"
#include"card_service.h"
#include"billing_file.h"
#include"billing_service.h"
#include"model.h"
#include"global.h"

lpCardNode cardList = NULL;		//����ͷָ��

//[������]		addCard
//[����]		��ӿ���Ϣ���ṹ������
//[����]		����Ϣ�ṹ��
//[����ֵ]		����1����ӳɹ�������0���������
int addCard(Card crd) {

	if (saveCard(&crd, CARDPATH) == TRUE) {
		return TRUE;
	}
	return FALSE;
}


//[������]		queryCard
//[����]		�ڽṹ�������в��ҿ���Ϣ
//[����]		�û������Ҫ��ѯָ�����ŵĿ���Ϣ
//[����ֵ]		�ṹ�������в�ѯ���Ŀ���Ϣ��ַ��û���ҵ�����NULL
Card* queryCard(const char* pName) {
	Card* pCard  = NULL;
	lpCardNode p;		//���ڲ����е���������ָ�������е�ÿ���ڵ�

	//�ӿ���Ϣ�ļ��ж�ȡ����Ϣ������ʧ�ܷ���NULL��
	
	if (getCard() == FALSE){
		return NULL;
	}
	//ָ������ͷ��㣬���ڵ���
	p = cardList;
	//�������в���ָ������
	while (p != NULL) {
		if (strcmp(p->data.aName, pName) == 0) {
			pCard = &(p->data);
			return pCard;
		}
		else {
			p = p->next;
		}
	}
	//��δ�ҵ��򷵻�NULL
	return pCard;
}

//[������]		getCard
//[����]		�ӿ���Ϣ�ļ��У���ȡ����Ϣ�����浽������
//[����]		void
//[����ֵ]		��ȡ�ɹ�����TRUE�����򷵻�FALSE
int getCard() {
	int i = 0;
	Card* pCard = NULL;		// ��ȡ����һ������Ϣ
	int nCount = 0;		//ʵ�ʵĿ���Ϣ��
	lpCardNode node = NULL;		//��ǰ��β�ڵ�
	lpCardNode cur = NULL;		//��ӵ������еĽڵ�

	//����������Ѿ����ڵ�����
	if (cardList != NULL) {
		releaseCardList();
	}
	//��ʼ������
	initCardList();

	//��ȡ�ļ��п���Ϣ����
	nCount = getCardCount(CARDPATH);
	if (nCount == 0) {
		return FALSE;
	}
	else if (nCount == -1) {
		printf("�ļ��޷��򿪣�\n");
		return FALSE;
	}
	//��̬�����ڴ������������еĿ���Ϣ���൱�ڽṹ�����飬pCard�൱��������
	pCard = (Card*)malloc(sizeof(Card) * nCount);
	if (pCard != NULL) {
		//�������FALSE���ȡʧ��
		if (readCard(pCard, CARDPATH) == 0) {
			free(pCard);
			return FALSE;
		}

		//����ȡ����Ϣ�����浽������
 		for (i = 0, node = cardList; i < nCount;i++) {
			//Ϊ�ڵ�����ڴ�
			cur = (lpCardNode)malloc(sizeof(CardNode));
			//��������ڴ�ʧ�ܣ��򷵻�
			if (cur == NULL) {
				free(pCard);
				return FALSE;
			}
			//��ʼ���µĿռ䣬ȫ����ֵΪ0��
			memset(cur, 0, sizeof(CardNode));

			//������Ϣ���浽�ڵ���
			cur->data = pCard[i];
			cur->next = NULL;

			//�������ӵ������β��
			node->next = cur;
			node = cur;
		}
		//�ͷ��ڴ�
		free(pCard);
		return TRUE;
	}
	return FALSE;
}


//[������]		intiCardList
//[����]		��ʼ������Ϣ����
//[����]		void
//[����ֵ]		int�ͣ�TRUE��ʾ�ɹ���FALSE��ʾʧ��
int initCardList() {
	lpCardNode head = NULL;
	if (cardList == NULL) {
		head = (lpCardNode)malloc(sizeof(CardNode));
		//�������ʧ�ܣ�������ָ��
		if (head != NULL) {
			head->next = NULL;
			cardList = head;	//������ͷָ�븳ֵ��ȫ�ֱ���cardList
			return TRUE;
		}
	}
	return FALSE;
}

//[������]		releaseCardList
//[����]		�ͷſ���Ϣ����
//[����]		void
//[����ֵ]		void
void releaseCardList() {
	lpCardNode cur = cardList;
	lpCardNode next = NULL;

	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	cardList = NULL;
}

//[������]		queryCards
//[����]		�ڿ���Ϣ�����У�ģ����ѯ���������п���Ϣ
//[����]		pName:ָ���û������Ҫ��ѯ�Ŀ��� pIndex��ָ��鵽�Ŀ���Ϣ������
//[����ֵ]		ָ����Ϣ�ṹ���ָ��
Card* queryCards(const char* pName, int* pIndex) {
	lpCardNode node = NULL;
	Card* pCard = NULL;		//�����ѯ���ķ��������Ŀ���Ϣ��

	//�ӿ���Ϣ�ļ��ж�ȡ����Ϣ�б�ʧ�ܷ���NULL
	if (getCard() == FALSE) {
		return NULL;
	}
	//���ȷ���һ��Card��С�Ŀռ䣻
	pCard = (Card*)malloc(sizeof(Card));
	if (pCard == NULL) {
		return NULL;
	}

	//nodeָ���һ�����ݣ�׼����ʼ����
	node = cardList->next;		//��һ������

	//��������ָ���βNULLʱ������
	while (node != NULL) {
		//�ж��ڱ����Ŀ����У������Ƿ����pName�ַ�����
		if (strstr(node->data.aName, pName) != NULL) {
			//����У��򱣴����е�����
			pCard[*pIndex] = node->data;
			(*pIndex)++;

			//����Ϊָ������ڴ棬������������
			pCard = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card));
		}

		//�ƶ�����һ�����
		node = node->next;
	}
	if (*pIndex == 0) {
		return NULL;		//δ��ѯ�������Ϣ
	}
	return pCard;
}

Card* queryAllCards(int* pIndex) {
	Card* pCard = NULL;
	lpCardNode node;

	*pIndex = getCardCount(CARDPATH);
	
	//�ӿ���Ϣ�ļ��ж�ȡ����Ϣ�б�ʧ�ܷ���NULL
	if (getCard() == FALSE) {
		return NULL;
	}

	pCard = (Card*)malloc((*pIndex)*sizeof(Card));		//�����ڴ�ռ�
	if (pCard == NULL) {
		return NULL;
	}
	
	int i = 0;
	node = cardList->next;
	while (node != NULL){		//���������浽���ٵĿռ�pCard��
		pCard[i++] = node->data;
		node = node->next;
	}
	return pCard;
}


//[������]		checkCard
//[����]		���ļ��ж�ȡ����Ϣ�������������в�ѯ����Ϣ���������������е�λ��
//[����]		pName:�ϻ�����	pPwd���ϻ�����	pIndex�����ص�������
//[����ֵ]		�ϻ����ṹ��
Card* checkCard(const char* pName, const char* pPwd, int* pIndex) {
	lpCardNode cardNode = NULL;		//��ǰ���
	int nIndex = 0;		//ƥ��Ŀ�����Ϣ����������е���ţ����ڸ��¿���Ϣ
	//�ӿ���Ϣ�ж�ȡ����Ϣ������ʧ�ܷ���NULL
	if (getCard() == FALSE) {
		return FALSE;
	}
	//��ǰ���ָ��ͷ���
	if (cardList != NULL) cardNode = cardList;

	while (cardNode != NULL) {
		//�������в����Ƿ��ж�Ӧ�Ŀ���Ϣ
		if ((strcmp(cardNode->data.aName, pName) == 0) && (strcmp(cardNode->data.aPwd, pPwd) == 0)) {
			//���ؿ���Ϣ�ڵ����ݵ�ַ
			*pIndex = nIndex;
			return &cardNode->data;
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return NULL;
}
