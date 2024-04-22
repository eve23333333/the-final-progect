#include<stdio.h>
#include<malloc.h>
#include"model.h"
#include"global.h"

//[������]		saveBilling
//[����]		����Ʒ���Ϣ
//[����]		pBilling���Ʒ���Ϣ�ṹ��ָ��	pPath������Ʒ���Ϣ�ļ�·��
//[����ֵ]		True ����ɹ�	False������ʧ��
int saveBilling(const Billing* pBilling, const char* pPath) {
	//��׷�ӷ�ʽ��������д��
	FILE* fp;
	fopen_s(&fp,pPath,"ab+");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣�����д��Ʒ���Ϣ��\n");
		return FALSE;
	}
	//���Ʒ���Ϣ���浽�ļ���
	fwrite(pBilling, sizeof(*pBilling), 1, fp);
	//�ر��ļ�
	fclose(fp);
	printf("-----******-----�Ʒ���Ϣ�ɹ������ļ��У�-----******-----\n\n");
	return TRUE;
}

//[������]		readBilling
//[����]		��ȡ�Ʒ���Ϣ
//[����]		pBilling���Ʒ���Ϣ�ṹ��ָ��	pPath������Ʒ���Ϣ�ļ�·��
//[����ֵ]		True ��ȡ�ɹ�	False����ȡʧ��
int readBilling(Billing* pBilling, const char* pPath) {
	int nIndex = 0;

	//�Զ����Ʒ�ʽ��ȡ
	FILE* fp;
	fopen_s(&fp, pPath, "rb");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣����ܶ�ȡ�Ʒ���Ϣ��\n");
		return FALSE;
	}
	else {
		//�����ļ�����ȡ�ļ�����
		while (!feof(fp)) {
			if (fread(&pBilling[nIndex], sizeof(Billing), 1, fp) != 0) {
				nIndex++;
			}
		}
		//�ر��ļ�
		fclose(fp);
		return TRUE;
	}
}

//[������]		getBillingCount
//[����]		��ȡ�ļ��мƷ���Ϣ������
//[����]		�Ʒ���Ϣ�ļ�·��
//[����ֵ]		�Ʒ���Ϣ����
int getBillingCount(const char* pPath) {
	int nCount = 0;
	Billing* pBilling = (Billing*)malloc(sizeof(Billing));
	//�Զ����Ʒ�ʽ��ȡ
	FILE* fp;
	fopen_s(&fp, pPath, "rb");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣�����ͳ�ƼƷ���Ϣ������\n");
		return FALSE;
	}
	else {
		//�����ļ�����ȡ�ļ�����
		while (!feof(fp)) {
			if (fread(pBilling, sizeof(Billing), 1, fp) != 0) {
				nCount++;
			}
		}
	}
	//�ر��ļ�
	fclose(fp);
	free(pBilling);
	return nCount;
}

//[������]		updateBilling
//[����]		���¼Ʒ���Ϣ�ļ��е�һ���Ʒ���Ϣ�ļ�
//[����]		pBilling��ָ��Ʒ���Ϣ�ṹ�壻pPath���Ʒ���Ϣ�ļ�·����nIndex���Ʒ���Ϣ���
//[����ֵ]		int
int updateBilling(const Billing* pBilling, const char* pPath, int nIndex) {
	int nCount = 0;		//��ȡ����
	long lPosition = 0;		//�ļ�λ��
	Billing pbBuf;

	//�Զ����ƶ�дģʽ���ļ������ʧ�ܣ�����FALSE
	FILE* fp;
	fopen_s(&fp, pPath, "rb+");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣����ܸ���������Ϣ��\n");
		return FALSE;
	}
	//�����ļ�����ȡ������Ϣ���ļ��е�λ��
	while ((!feof(fp)) && (nCount < nIndex)) {
		if (fread(&pbBuf, sizeof(Billing), 1, fp) != 0) {
			//��ȡ�ļ���ʶλ�ã����һ�����ҵ���λ��
			lPosition = ftell(fp);
		}
		nCount++;
	}
	//�ƶ����ļ���ʶλ��
	fseek(fp, lPosition - sizeof(Billing), SEEK_SET);		//���ļ�ָ�����Ҫ�滻����β��ǰһ��
	//��������Ϣд���ļ�
	fwrite(pBilling, sizeof(Billing), 1, fp);
	printf("-----******-----������Ϣ���µ��ļ��ɹ���-----******-----\n\n");
	
	fclose(fp);
	return TRUE;
}