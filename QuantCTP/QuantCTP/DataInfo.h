#include"stdafx.h"

//基本文件信息
#define UID "E://uid.txt"
#define INSTRUMENT_FILE "E://InstrumentID.txt"

//基本数据类型信息

//合约信息结构，同数据库表类型结构一致
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
	double vol;			//成交量
	double interest;	//成交额
	double holding;		//持仓
}FT_DATA;

//基础信息类头文件
#pragma once
#define TRADE_FRONT_IP "tcp://180.168.146.187:10000" 
#define MARKET_FRONT_IP "tcp://180.168.146.187:10010"
#define BROKER_ID "9999"

//数据库相关信息
#define ROOT "root"
#define PSWD "123456"
#define DBHOST "localhost"
#define FUTURE_TABLE "future_data"
#define MAX_ARRAY_SIZE 1000