// QuantCTP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include ".\win32api\ThostFtdcMdApi.h"
#include "MdSpi.h"
#include "DataInfo.h"

int main()
{
	CThostFtdcMdApi *mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	MdSpi mymdapi(mdapi);
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
    return 0;
}

