//
//  FNAnalyserOne.cpp
//  FNProject
//
//  Created by user on 15/11/23.
//  Copyright © 2015年 user. All rights reserved.
//

#include "FNAnalyserOne.hpp"

bool FNAnalyserOne::AnalyserData(const std::vector<FNData>& dataArray) {
	
	//刚刚开的新股
	if (dataArray.size() < 2)
	{
		return true;
	}
	
	//到过高点，高点至少为50左右
	float fHighestPrice = 0;
	
	for (std::vector<FNData>::const_iterator iter = dataArray.begin(); iter != dataArray.end(); ++iter)
	{
		if (fHighestPrice < iter->m_fHighPrice)
		{
			fHighestPrice = iter->m_fHighPrice;
		}
	}
	
	if (fHighestPrice > 160)
	{
		return false;
	}
	
	if (fHighestPrice < 50)
	{
		return false;
	}
	
	//现在跌下来或者分拆，股价 < 30
	float fCurPrice = dataArray[0].m_fHighPrice;
	
	if (fCurPrice > 0.45 * fHighestPrice)
	{
		return false;
	}
	
	return true;
}