//
//  FNData.cpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright © 2015年 user. All rights reserved.
//

#include "FNStockData.hpp"
#include <string>
#include <iostream>
#include <fstream>

int GetStockId(const std::string& fileName) {
	
	return -1;
}

bool RetriveDataFromString(const std::string& str, FNData& data) {
	
	return true;
}

FNStockData* FNStockData::sharedInstance() {
	
	static FNStockData _instance;
	
	return &_instance;
}

std::vector<FNData> GetLimitStockData(std::vector<std::string> strData) {
	
	std::vector<FNData> tempData;
	
	for (int i = 0; i < strData.size(); ++i) {
		
		FNData data;
		
		if (RetriveDataFromString(strData[i], data)) {
			
			tempData.push_back(data);
		}
	}
	
	return tempData;
}

void FNStockData::LoadFromFile(const std::string& fileName) {
	
	std::ifstream infile(fileName);

	if (!infile) {
		
		return;
	}
	
	int nId = GetStockId(fileName);
	
	std::string line;
	
	std::vector<std::string> vctData;
	
	while (getline(infile, line)) {
		
		std::cout << line << std::endl;
		
		vctData.push_back(line);
	}
	
	m_vctStockData[nId] = GetLimitStockData(vctData);
}

