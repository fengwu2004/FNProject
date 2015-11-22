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
#include "easysqlite3/SqlCommon.h"
#include "easysqlite3/SqlField.h"

using namespace sql;

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

static const std::string  field_stockId			= "stockId";
static const std::string  field_lowPrice		= "lowPrice";
static const std::string  field_highPrice		= "highPrice";
static const std::string  field_openPrice		= "openPrice";
static const std::string  field_endPrice		= "endPrice";
static const std::string  field_tradingVolum	= "tradingVolum";
static const std::string  field_tradingAmount	= "tradingAmount";
static const std::string  field_tradingDay		= "tradingDay";

static sql::Field stockField[] =
{
	sql::Field(FIELD_KEY),
	sql::Field(field_lowPrice, type_float),
	sql::Field(field_highPrice, type_float),
	sql::Field(field_openPrice, type_float),
	sql::Field(field_endPrice, type_float),
	sql::Field(field_tradingVolum, type_float),
	sql::Field(field_tradingAmount, type_float),
	sql::Field(field_tradingDay, type_time),
	sql::Field(DEFINITION_END),
};

struct FNData {

	time_t m_time;
	float m_fLowPrice;
	float m_fHighPrice;
	float m_fOpenPrice;
	float m_fEndPrice;
	int m_nTradingVolume;
	int m_nTradingAmount;
};

#endif /* FNDataDefine_h */
