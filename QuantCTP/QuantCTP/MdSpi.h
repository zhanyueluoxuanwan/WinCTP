//行情接收单元头文件
#pragma once

#include "DBWriter.h"
#include ".\win64api\ThostFtdcMdApi.h"
#include <ctime>
#include <cstring>
#include <string>
#include <fstream>

class MdSpi : public CThostFtdcMdSpi {
public:
	//use mdapi to construct an instance
	MdSpi(CThostFtdcMdApi *mdapi);
	~MdSpi();
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

	//get database pointer
	void GetDBInstance(DBWriter *inst) { db = inst; };

private:
	CThostFtdcMdApi *mymdapi;
	CThostFtdcReqUserLoginField *mylogin;
	int myloginID;
	string broker;
	string user_id;
	string password;
	int instrumentNum;
	char **instrumentID;
	FT_DATA *fd;
	DBWriter *db;
};