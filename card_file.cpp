#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include"card_file.h"
#include "model.h"
#include "global.h"
#include "tool.h"
//#define CARDCHARNUM 256		//���ļ��ж�ȡ���ַ������ֵ

//[������]		saveCard
//[����]		������Ϣ���浽�ļ���
//[����]		pCard:ָ��Ҫ����Ľṹ�壻 pPath��������ļ�·��
//[����ֵ]		����ɹ�����TRUE,ʧ�ܷ���FALSE
int saveCard(const Card* pCard, const char* pPath) {
	//��׷�ӷ�ʽ��������д��
	FILE* fp;
	fopen_s(&fp, pPath, "ab+");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣�����д�뿨��Ϣ��\n");
		return FALSE;
	}
	//������Ϣ���浽�ļ���
	fwrite(pCard, sizeof(Card), 1, fp);
	//�ر��ļ�
	fclose(fp);
	printf("-----******-----����Ϣ�ɹ������ļ���-----******-----\n\n");
	return TRUE;
}

//[������]		readCard
//[����]		���ļ��ж�ȡ����Ϣ���ṹ������
//[����]		pCard��ָ��ṹ�����飻	pPath���ļ�·��
//[����ֵ]		��ȷ��ȡ����TRUE ����ΪFALSE
int readCard(Card* pCard, const char* pPath) {
	int nIndex = 0;		//����Ϣ����

	//�Զ����Ʒ�ʽ��ȡ
	FILE* fp;
	fopen_s(&fp, pPath, "rb");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣����ܶ�ȡ����Ϣ��\n");
		return FALSE;
	}
	else {
		//�����ļ�����ȡ�ļ�����
		while (!feof(fp)) {
			if (fread(&pCard[nIndex], sizeof(Card), 1, fp) != 0) {
				nIndex++;
			}
		}
		//�ر��ļ�
		fclose(fp);
		return TRUE;
	}
}


//[������]		getCardCount
//[����]		���ļ��ж�ȡ����Ϣ���㿨����
//[����]		pPath���ļ�·��
//[����ֵ]		�ļ�������
int getCardCount(const char* pPath) {
	int nCount = 0;		//����Ϣ����
	Card* pCard = (Card*)malloc(sizeof(Card));
	//�Զ����Ʒ�ʽ��ȡ
	FILE* fp;
	fopen_s(&fp, pPath, "rb");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣�����ͳ�ƿ���Ϣ������\n");
		return -1;		//-1��ʾ�ļ��޷���ȷ��
	}
	else {
		//�����ļ�����ȡ�ļ�����
		while (!feof(fp)) {
			if (fread(pCard, sizeof(Card), 1, fp) != 0) {
				nCount++;
			}
		}
	}
	//�ر��ļ�
	fclose(fp);
	free(pCard);
	return nCount;

}

//[������]		updateCard
//[����]		���¿���Ϣ�ļ��ж�Ӧ��һ������Ϣ
//[����]		pCard�����º�Ŀ�����		pPath������Ϣ�ļ�·��
//			nIndex����Ҫ���µĿ���Ϣ�ļ����ļ��еĿ����
//[����ֵ]		TRUE���³ɹ�		FALSE����ʧ��
int updateCard(const Card* pCard, const char* pPath, int nIndex) {
	int nCount = 0;		//�ļ��еĵ�ǰ�����
	long lPosition = 0;		//�ļ����λ��
	Card pcBuf;

	//�Զ����ƶ�дģʽ���ļ������ʧ�ܣ�����FALSE
	FILE* fp;
	fopen_s(&fp, pPath, "rb+");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣����ܸ��¿���Ϣ��\n");
		return FALSE;
	}
	//�����ļ�����ȡ������Ϣ���ļ��е�λ��
	while ((!feof(fp)) && (nCount < nIndex)) {
		if (fread(&pcBuf, sizeof(Card), 1, fp) != 0) {
			//��ȡ�ļ���ʶλ�ã����һ�����ҵ���λ��
			lPosition = ftell(fp);
		}
		nCount++;
	}
	//�ƶ����ļ���ʶλ��
	fseek(fp, lPosition - sizeof(Card), SEEK_SET);		//���ļ�ָ�����Ҫ�滻����β��ǰһ��
	//��������Ϣд���ļ�
	fwrite(pCard, sizeof(Card), 1, fp);
	printf("-----******-----����Ϣ���µ��ļ��ɹ���-----******-----\n\n");

	fclose(fp);
	return TRUE;
	
}