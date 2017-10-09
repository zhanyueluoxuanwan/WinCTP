//����ӿ�ʵ��
#include "stdafx.h"
#include "MdSpi.h"
#include "DataInfo.h"


MdSpi::MdSpi(CThostFtdcMdApi *mdapi) {
	//init api
	mymdapi = mdapi;
	myloginID = 10;
	//creating market file
	time_t now = time(0);
	GetLocalTime(&market_time);
	market_file_name = "./MarketData/" + std::to_string(market_time.wYear) + std::to_string(market_time.wMonth) + std::to_string(market_time.wDay) + ".csv";
	market_file.open(market_file_name, ios::app);
	cout << "Creating market file: " << market_file_name << endl;
	if (market_file.is_open())
		cout << "Successful creating market file" << endl;
	else
		cout << "Error in creating file" << endl;

	//reading instruments
	ifstream instrumentFile("InstrumentID.txt");
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

}

void MdSpi::OnFrontConnected() {
	//processing connected operation
	broker = BROKER_ID;
	cout << "�������û�����";
	cin>>user_id;
	cout << "���������룺";
	cin >> password;
	cout << endl;
	mylogin = new CThostFtdcReqUserLoginField();
	strcpy_s(mylogin->BrokerID, broker.c_str());
	strcpy_s(mylogin->UserID, user_id.c_str());
	strcpy_s(mylogin->Password, password.c_str());
	mymdapi->ReqUserLogin(mylogin, myloginID);
	std::cout << "Connected" << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	cout << "Request login\n";
	cout << "Trading day:" << mymdapi->GetTradingDay() << endl;
	if (pRspInfo->ErrorID == 0) {
		cout << "Success login-->ID: " << myloginID << endl;
		cout << "Requiring market data!" << endl;
		int ret = mymdapi->SubscribeMarketData(instrumentID, instrumentNum);
		cout << ((ret == 0) ? "Successful subscribe!" : "Failed subscribe!") << endl;
	}
}

void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	cout << "Market data respones" << endl;
	cout << "Instruments:" << pSpecificInstrument->InstrumentID << endl;
	cout << "ResponseInfo:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *MarketData) {
	if(!market_file.is_open())
		market_file.open(market_file_name, ios::app);
	market_file << MarketData->InstrumentID << "," << MarketData->UpdateTime << "." << MarketData->UpdateMillisec << "," << MarketData->LastPrice
		<< "," << MarketData->Volume << "," << MarketData->BidPrice1 << "," << MarketData->BidVolume1 << "," << MarketData->AskPrice1
		<< "," << MarketData->AskVolume1 << "," << MarketData->OpenInterest << "," << MarketData->Turnover << endl;
	market_file.close();
};

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	
};