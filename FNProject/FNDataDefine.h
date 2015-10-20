//
//  FNDataDefine.h
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright © 2015年 user. All rights reserved.
//

#ifndef FNDataDefine_h
#define FNDataDefine_h

#include <time.h>

struct FNTime {
	
	int m_nYear;
	int m_nMonth;
	int m_nDay;
};

struct FNData {
	
	FNTime m_time;
	float m_fMin;
	float m_fMax;
	float m_fStart;
	float m_fEnd;
	int m_nTradingVolume;
	int m_nTradingMoney;
};

#endif /* FNDataDefine_h */
