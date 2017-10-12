//行情接口实现
#include "stdafx.h"
#include "MdSpi.h"
#include "DataInfo.h"


MdSpi::MdSpi(CThostFtdcMdApi *mdapi) {
	//init api
	fd = new FT_DATA();
	mymdapi = mdapi;
	myloginID = 10;
	//reading instruments
	ifstream instrumentFile(INSTRUMENT_FILE);
	if (instrumentFile.is_open()) {
		string len;
		getline(instrumentFile, len);
		instrumentNum = stoi(len);
		instrumentID = (char **)malloc(sizeof(char *) * instrumentNum);
		for (int line = 0; line < instrumentNum; line++) {
			string instrument;
			getline(instrumentFile, instrument);
			instrumentID[line] = (char *)malloc(sizeof(char) * instrument.size());
			strcpy_s(instrumentID[line], instrument.size()+1, instrument.c_str());
			cout << "Current instrument is: " << instrumentID[line] << endl;
		}
	}
	else
		cout << "Cannot read instruments!" << endl;
	instrumentFile.close();
};

MdSpi::~MdSpi() {
	for (int i = 0; i < instrumentNum; i++)
		delete[] instrumentID[i];
	delete[] instrumentID;
	delete fd;
	delete db;
};

void MdSpi::OnFrontConnected() {
	//processing connected operation
	//采取自动读取用户名和密码，进行系统内置重连
	ifstream uid(UID);
	if (uid.is_open()) {
		getline(uid, user_id);
		getline(uid, password);
		cout << "完成载入用户名和密码！" << endl;
	}
	else
		cout << "无用户名和密码文件!" << endl;
	uid.close();
	broker = BROKER_ID;
	mylogin = new CThostFtdcReqUserLoginField();
	strcpy_s(mylogin->BrokerID, broker.c_str());
	strcpy_s(mylogin->UserID, user_id.c_str());
	strcpy_s(mylogin->Password, password.c_str());
	mymdapi->ReqUserLogin(mylogin, myloginID);
	std::cout << "Connected" << endl;

};

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	cout << "Request login\n";
	cout << "Trading day:" << mymdapi->GetTradingDay() << endl;
	if (pRspInfo->ErrorID == 0) {
		cout << "Success login-->ID: " << myloginID << endl;
		cout << "Requiring market data!" << endl;
		int ret = mymdapi->SubscribeMarketData(instrumentID, instrumentNum);
		cout << ((ret == 0) ? "Successful subscribe!" : "Failed subscribe!") << endl;
	}
};

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	cout << "Market data respones" << endl;
	cout << "Instruments:" << pSpecificInstrument->InstrumentID << endl;
	cout << "ResponseInfo:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
};

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *MarketData) {
	fd->id = MarketData->InstrumentID;
	fd->time = MarketData->TradingDay;
	fd->time += '-';
	fd->time += MarketData->UpdateTime;
	fd->time += '-';
	fd->time += std::to_string(MarketData->UpdateMillisec);
	fd->open = MarketData->OpenPrice;
	fd->high = MarketData->HighestPrice;
	fd->low = MarketData->LowestPrice;
	fd->close = MarketData->LastPrice;
	fd->ask1 = MarketData->AskPrice1;
	fd->bid1 = MarketData->BidPrice1;
	fd->askvol1 = MarketData->AskVolume1;
	fd->bidvol1 = MarketData->BidVolume1;
	fd->vol = MarketData->Volume;
	fd->interest = MarketData->Turnover;
	fd->holding = MarketData->OpenInterest;
	db->DBInsert(fd);
};

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	
};
