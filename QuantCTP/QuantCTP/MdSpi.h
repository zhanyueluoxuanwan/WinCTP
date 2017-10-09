//����̳�ͷ�ļ�
#pragma once

#include ".\win32api\ThostFtdcMdApi.h"
#include<iostream>
#include<ctime>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;

class MdSpi : public CThostFtdcMdSpi {
public:
	//use mdapi to construct an instance
	MdSpi(CThostFtdcMdApi *mdapi);
	//construct connection
	void OnFrontConnected();
	//Response the login request
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//Response the logout request
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//require market data
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//receive data
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *MarketData);

	//cancel market data
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//disconnected
	void OnFrontDisconnected(int nReason) {};

private:
	CThostFtdcMdApi *mymdapi;
	CThostFtdcReqUserLoginField *mylogin;
	int myloginID;
	string broker;
	string user_id;
	string password;
	int instrumentNum;
	char **instrumentID;
	string market_file_name;
	fstream market_file;
	SYSTEMTIME market_time;
};