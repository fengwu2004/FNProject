//
//  FNAnalyserFactory.cpp
//  FNProject
//
//  Created by user on 15/11/23.
//  Copyright © 2015年 user. All rights reserved.
//

#include "FNAnalyserFactory.hpp"
#include "FNAnalyserOne.hpp"

FNAnalyserFactory* FNAnalyserFactory::sharedInstance()
{
	static FNAnalyserFactory instance;
	
	return &instance;
}

FNAnalyser* FNAnalyserFactory::getAnalyser(int nType)
{
	switch (nType) {
  case 0:
			if (m_allAnalysers.count(nType) == 0)
			{
				m_allAnalysers[nType] = new FNAnalyserOne;
			}
			
			return m_allAnalysers[nType];
			
  default:
			
			return NULL;
	}
}