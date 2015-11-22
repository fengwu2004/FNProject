//
//  FNData.cpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright Â© 2015å¹?user. All rights reserved.
//

#include "FNStockData.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "boost/regex.hpp"
#include "FNCommon.hpp"
#include <time.h>

int GetStockId(const std::string& fileName) {
	
	std::vector<std::string> tempData = FNCommonUtility::SplitString(fileName, "#");
	
	std::string value = tempData[1];
	
	tempData = FNCommonUtility::SplitString(value, ".txt");
	
	return atoi(tempData[0].c_str());
}

time_t RetriveTime(const std::string& str) {
	
	tm thistime;

	memset(&thistime, 0x00, sizeof(thistime));

	std::vector<std::string> tempData = FNCommonUtility::SplitString(str, "/");
	
	thistime.tm_year = atoi(tempData[0].c_str());
	
	thistime.tm_mon = atoi(tempData[1].c_str());
	
	thistime.tm_mday = atoi(tempData[2].c_str());

	return mktime(&thistime);	
}

bool RetriveDataFromString(const std::string& str, FNData& data) {
	
	std::vector<std::string> tempData = FNCommonUtility::SplitString(str, "\\s");
	
	data.m_time = RetriveTime(tempData[ekey_time]);
	
	data.m_fLowPrice = atof(tempData[ekey_min].c_str());
	
	data.m_fHighPrice = atof(tempData[ekey_max].c_str());
	
	data.m_fOpenPrice = atof(tempData[ekey_start].c_str());
	
	data.m_fEndPrice = atof(tempData[ekey_end].c_str());
	
	data.m_nTradingVolume = atoi(tempData[ekey_tradevolume].c_str());
	
	data.m_nTradingAmount = atoi(tempData[ekey_trademoney].c_str());
	
	return true;
}

FNStockData* FNStockData::sharedInstance() {
	
	static FNStockData _instance;
	
	return &_instance;
}

std::vector<FNData> GetLimitStockData(const std::vector<std::string>& strData) {
	
	std::vector<FNData> tempData;
	
	for (int i = 0; i < strData.size(); ++i) {
		
		FNData data;
		
		if (RetriveDataFromString(strData[i], data)) {
			
			tempData.push_back(data);
		}
	}
	
	return tempData;
}

void FNStockData::LoadFromFile(const std::string& fileName, std::map<int, std::vector<FNData> >& data) {
	
	std::ifstream infile(fileName.c_str());

	if (!infile) {
		
		return;
	}
	
	int nId = GetStockId(fileName);
	
	std::string line;
	
	std::vector<std::string> vctData;
	
	int i = 0;
	
	while (getline(infile, line)) {
		
		if (i < 2) {
			
			++i;
			
			continue;
		}
		
		std::cout << line << std::endl;
		
		vctData.push_back(line);
	}
	
	vctData.pop_back();
	
	data[nId] = GetLimitStockData(vctData);
}

