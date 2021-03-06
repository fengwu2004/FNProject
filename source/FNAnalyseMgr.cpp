﻿//
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
#include "FNDBSystem.h"
#include <iostream>
#include <stdio.h>
#include "FNAnalyser.hpp"
#include "FNAnalyserFactory.hpp"
#include <assert.h>

FNAnalyseMgr* FNAnalyseMgr::sharedInstance() {

	static FNAnalyseMgr _FNAnalyseMgr;
	
	return &_FNAnalyseMgr;
}

void FNAnalyseMgr::SaveToDB()
{
	std::vector<std::string> fileNames;

	FNCommonUtility::ReadDir("c:/data/", fileNames);

	for (int i = 0; i < fileNames.size(); ++i) {

		FNStockData::sharedInstance()->LoadFromFile(fileNames[i], m_dicStockData);
	}

	FNDBSystem::SaveToArchive(m_dicStockData);

	std::cout << "数据库更新成功" << std::endl;
}

void FNAnalyseMgr::LoadFromDB() {

	FNDBSystem::LoadFromArchive(m_dicStockData);

	std::cout << "数据库加载成功" << std::endl;
}

bool IsFileExist()
{
	bool fileExist = true;

	FILE* fh = fopen(DBFilePath.c_str(), "r");

	if (fh == NULL)
	{
		fileExist = false;
	}
	else
	{
		fclose(fh);
	}

	return fileExist;
}

void FNAnalyseMgr::Excute() {
	
	if (!IsFileExist())
	{
		SaveToDB();
	}

	LoadFromDB();

	RunOnCondition();
}

void FNAnalyseMgr::RunOnCondition() {
	
	m_vctResult.clear();
	
	FNAnalyser* pAnalyser = FNAnalyserFactory::sharedInstance()->getAnalyser(0);
	
	assert(pAnalyser);
	
	for (std::map<int, std::vector<FNData> >::iterator iter = m_dicStockData.begin(); iter != m_dicStockData.end(); ++iter) {

		if (pAnalyser->AnalyserData(iter->second)) {
			
			m_vctResult.push_back(iter->first);
		}
	}

	OutputResult();
}

std::string GetStockUrl(int nStockId)
{
	//http://quote.eastmoney.com/sz000036.html?StockCode=000036
	//http://quote.eastmoney.com/sh600036.html?StockCode=600036

	char szText[256] = { 0 };

	if (nStockId < 60000)
	{
		sprintf(szText, "http://quote.eastmoney.com/sz%06d.html?StockCode=%06d", nStockId, nStockId);
	}
	else
	{
		sprintf(szText, "http://quote.eastmoney.com/sh%06d.html?StockCode=%06d", nStockId, nStockId);
	}

	return szText;
}

void FNAnalyseMgr::OutputResult() {
	
	std::ofstream myfile(analysePath.c_str());
	
	if (!myfile) {
		
		return;
	}
	
	std::cout << "<html>" << std::endl;

	std::cout << "<body>" << std::endl;

	std::cout << "<h1>到过高点，高点至少为50左右,现在跌下来或者分拆，股价低于45%%</h1>" << std::endl;

	for (int i = 0; i < m_vctResult.size(); ++i) {
		
		std::string stockUrl = GetStockUrl(m_vctResult[i]);

		myfile << "<a href=\"" << stockUrl << "\">" << m_vctResult[i] << "</a>" <<std::endl;

		myfile << "<br>" <<std::endl;
	}

	std::cout << "</body>" << std::endl;

	std::cout << "</html>" << std::endl;
	
	myfile.close();
}