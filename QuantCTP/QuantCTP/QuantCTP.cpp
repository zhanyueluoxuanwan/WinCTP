// QuantCTP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\win64api\ThostFtdcMdApi.h"
#include "DataInfo.h"
#include "MdSpi.h"
#include "DBWriter.h"

int main()
{
	CThostFtdcMdApi *mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	MdSpi mymdapi(mdapi);
	mymdapi.GetDBInstance(new DBWriter());
	mdapi->RegisterSpi(&mymdapi);
	mdapi->RegisterFront(MARKET_FRONT_IP);
	std::cout << "Registration Success!" << endl;
	mdapi->Init();
	std::cout << "Init API Success!" << endl;
	mdapi->Join();
	std::cout << "Start Thread Success!" << endl;
	mdapi->Release();
	std::cout << "Stop Thread Success!" << endl;
	return 0;
}

