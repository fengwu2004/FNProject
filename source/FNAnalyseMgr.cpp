//
//  FNAnalyseMgr.cpp
//  FNProject
//
//  Created by user on 15/10/22.
//  Copyright 漏 2015骞?user. All rights reserved.
//

#include "FNAnalyseMgr.hpp"
#include "FNStockData.hpp"
#include <vector>
#include "FNCommon.hpp"
#include <fstream>

FNAnalyseMgr* FNAnalyseMgr::sharedInstance() {

	static FNAnalyseMgr _FNAnalyseMgr;
	
	return &_FNAnalyseMgr;
}

void FNAnalyseMgr::Excute() {
	
	std::vector<std::string> fileNames;
	
	FNCommonUtility::ReadDir("c:/data/", fileNames);
	
	for (int i = 0; i < fileNames.size(); ++i) {
		
		FNStockData::sharedInstance()->LoadFromFile(fileNames[i], m_dicStockData);
	}
	
	RunOnCondition();
}

bool FNAnalyseMgr::AnalyseData(const std::vector<FNData>& dataArray) {
	
	return true;
}

void FNAnalyseMgr::RunOnCondition() {
	
	m_vctResult.clear();
	
	for (std::map<int, std::vector<FNData> >::iterator iter = m_dicStockData.begin(); iter != m_dicStockData.end(); ++iter) {
		
		if (AnalyseData(iter->second)) {
			
			m_vctResult.push_back(iter->first);
		}
	}
}

void FNAnalyseMgr::OutputResult() {
	
	std::ofstream myfile("c://a.txt");
	
	if (!myfile) {
		
		return;
	}
	
	for (int i = 0; i < m_vctResult.size(); ++i) {
		
		myfile << m_vctResult[i] << std::endl;
	}
	
	myfile.close();
}