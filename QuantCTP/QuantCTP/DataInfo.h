#include"stdafx.h"

//�����ļ���Ϣ
#define UID "E://uid.txt"
#define INSTRUMENT_FILE "E://InstrumentID.txt"

//��������������Ϣ

//��Լ��Ϣ�ṹ��ͬ���ݿ�����ͽṹһ��
typedef struct{
	string id;
	string time;
	double open;
	double high;
	double low;
	double close;
	double ask1;
	double bid1;
	double askvol1;
	double bidvol1;
	double vol;			//�ɽ���
	double interest;	//�ɽ���
	double holding;		//�ֲ�
}FT_DATA;

//������Ϣ��ͷ�ļ�
#pragma once
#define TRADE_FRONT_IP "tcp://180.168.146.187:10000" 
#define MARKET_FRONT_IP "tcp://180.168.146.187:10010"
#define BROKER_ID "9999"

//���ݿ������Ϣ
#define ROOT "root"
#define PSWD "123456"
#define DBHOST "localhost"
#define FUTURE_TABLE "future_data"
#define MAX_ARRAY_SIZE 1000