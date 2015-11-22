#include "FNDBSystem.h"
#include "FNCommon.hpp"
#include "FNDataDefine.h"
#include "easysqlite3/SqlCommon.h"
#include "easysqlite3/SqlField.h"
#include "easysqlite3/SqlDatabase.h"
#include "easysqlite3/SqlTable.h"

using namespace sql;

void FNDBSystem::SaveToArchive(const std::map<int, std::vector<FNData> >& allStocks) 
{
	sql::Database db;

	db.open("c:/data/stocks.db");

	for (std::map<int, std::vector<FNData> >::const_iterator iter = allStocks.begin(); iter != allStocks.end(); ++iter)
	{
		int nStockId = iter->first;

		const std::vector<FNData>& vctStock = iter->second;

		std::string tableName = INT2STR(nStockId);

		Table tbStock(db.getHandle(), "tableName", stockField);

		if (tbStock.exists())
		{
			tbStock.remove();
		}

		tbStock.create();

		for (std::vector<FNData>::const_iterator iter = vctStock.begin(); iter != vctStock.end(); ++iter)
		{
			Record record(tbStock.fields());

			record.setTime(field_tradingDay, iter->m_time);

			record.setDouble(field_lowPrice, iter->m_fLowPrice);

			record.setDouble(field_highPrice, iter->m_fHighPrice);

			record.setDouble(field_openPrice, iter->m_fOpenPrice);

			record.setDouble(field_endPrice, iter->m_fEndPrice);

			record.setInteger(field_tradingVolum, iter->m_nTradingVolume);

			record.setInteger(field_tradingAmount, iter->m_nTradingAmount);

			tbStock.addRecord(&record);
		}
	}
	
	db.close();
}