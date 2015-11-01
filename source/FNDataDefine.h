//
//  FNDataDefine.h
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright Â© 2015å¹?user. All rights reserved.
//

#ifndef FNDataDefine_h
#define FNDataDefine_h

#include <time.h>

enum DataType {
	
	ekey_time,
	ekey_min,
	ekey_max,
	ekey_start,
	ekey_end,
	ekey_tradevolume,
	ekey_trademoney,
};

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
