#include<stdio.h>
#include"global.h"
#include"model.h"
int saveMoney(const Money* pMoney, const char* pPath) {
	//��׷�ӷ�ʽ��������д��
	FILE* fp;
	fopen_s(&fp, pPath, "ab+");
	if (fp == NULL) {
		printf("�ļ��޷���ȷ�򿪣�����д���ֵ�˷���Ϣ��\n");
		return FALSE;
	}
	//���Ʒ���Ϣ���浽�ļ���
	fwrite(pMoney, sizeof(*pMoney), 1, fp);
	//�ر��ļ�
	fclose(fp);
	printf("-----******-----��ֵ�˷���Ϣ�ɹ������ļ��У�-----******-----\n\n");
	return TRUE;
}
