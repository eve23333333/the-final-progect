#include<stdio.h>
#include<time.h>
#include<malloc.h>

//[������]	timeToString
//[����]		��time_tת�����ַ������ַ����ĸ�ʽΪ����-��-�� ʱ���֡�
//[����]		time_t t:��Ҫת����ʱ�䣻 char* pBuf:ת������ַ���
//[����ֵ]	void
void timeToString(time_t t, char* pBuf) {
	struct tm* timeinfo ;
	timeinfo = (struct tm*)malloc(sizeof(struct tm));
	localtime_s(timeinfo, &t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}

//[������]	stringToTime
//[����]		���ַ���ת����time_t���ַ����ĸ�ʽΪ����-��-�� ʱ���֡�
//[����]		char* pTime���ַ����ĸ�ʽΪ����-��-�� ʱ����
//[����ֵ]	time_t:ʱ������
time_t stringToTime(char* pTime) {
	struct tm tm_1;
	time_t time_1;

	sscanf_s(pTime, "%d-%d-%d %d:%d", &tm_1.tm_year, &tm_1.tm_mon, &tm_1.tm_mday, &tm_1.tm_hour, &tm_1.tm_min);
	
	tm_1.tm_year -= 1900;
	tm_1.tm_mon -= 1;
	tm_1.tm_sec = 0;
	tm_1.tm_isdst = -1;

	time_1 = mktime(&tm_1);

	return time_1;
}

//[������]	timeToYear
//[����]		�õ�time_t����ʾ�����
//[����]		time_t t:��Ҫת����ʱ�䣻 
//[����ֵ]	int
int timeToYear(time_t t) {
	struct tm* timeinfo;
	timeinfo = (struct tm*)malloc(sizeof(struct tm));
	localtime_s(timeinfo, &t);
	return timeinfo->tm_year + 1900;
}

//[������]	timeToMonth
//[����]		�õ�time_t����ʾ���·�
//[����]		time_t t:��Ҫת����ʱ�䣻
//[����ֵ]	int
int timeToMonth(time_t t) {
	struct tm* timeinfo;
	timeinfo = (struct tm*)malloc(sizeof(struct tm));
	localtime_s(timeinfo, &t);
	return timeinfo->tm_mon + 1;
}