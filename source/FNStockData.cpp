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

int GetStockId(const std::string& fileName) {
	
	std::vector<std::string> tempData = FNCommonUtility::SplitString(fileName, "#");
	
	std::string value = tempData[1];
	
	tempData = FNCommonUtility::SplitString(value, ".txt");
	
	return atoi(tempData[0].c_str());
}

void RetriveTime(const std::string& str, FNTime& time) {
	
	std::vector<std::string> tempData = FNCommonUtility::SplitString(str, "/");
	
	time.m_nYear = atoi(tempData[0].c_str());
	
	time.m_nMonth = atoi(tempData[1].c_str());
	
	time.m_nDay = atoi(tempData[2].c_str());
}

bool RetriveDataFromString(const std::string& str, FNData& data) {
	
	std::vector<std::string> tempData = FNCommonUtility::SplitString(str, "\\s");
	
	RetriveTime(tempData[ekey_time], data.m_time);
	
	data.m_fMin = atof(tempData[ekey_min].c_str());
	
	data.m_fMax = atof(tempData[ekey_max].c_str());
	
	data.m_fStart = atof(tempData[ekey_start].c_str());
	
	data.m_fEnd = atof(tempData[ekey_end].c_str());
	
	data.m_nTradingVolume = atoi(tempData[ekey_tradevolume].c_str());
	
	data.m_nTradingMoney = atoi(tempData[ekey_trademoney].c_str());
	
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

