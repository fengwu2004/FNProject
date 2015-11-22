#include "FNDBSystem.h"
#include "FNCommon.hpp"
#include "FNDataDefine.h"
#include "easysqlite3/SqlCommon.h"
#include "easysqlite3/SqlField.h"
#include "easysqlite3/SqlDatabase.h"
#include "easysqlite3/SqlTable.h"
#include <stdio.h>

using namespace sql;

void SaveOneStocks(sql::Database& db, const std::string& strTableName, const std::vector<FNData>& vctStock)
{
	Table tbStock(db.getHandle(), strTableName, FieldOfStockInfo);

	if (tbStock.exists())
	{
		tbStock.remove();
	}

	tbStock.create();

	sqlite3_exec(db.getHandle(), "begin transaction", 0, 0, NULL);

	for (std::vector<FNData>::const_iterator it = vctStock.begin(); it != vctStock.end(); ++it)
	{
		Record record(tbStock.fields());

		record.setTime(field_tradingDay, it->m_time);

		record.setDouble(field_lowPrice, it->m_fLowPrice);

		record.setDouble(field_highPrice, it->m_fHighPrice);

		record.setDouble(field_openPrice, it->m_fOpenPrice);

		record.setDouble(field_endPrice, it->m_fEndPrice);

		record.setInteger(field_tradingVolum, it->m_nTradingVolume);

		record.setInteger(field_tradingAmount, it->m_nTradingAmount);

		tbStock.addRecord(&record);
	}

	sqlite3_exec(db.getHandle(), "commit transaction", 0, 0, NULL);
}

void SaveStockIndex(sql::Database& db, const std::vector<int>& stocksIndex)
{
	Table tbStock(db.getHandle(), "stockIds", FieldOfStockId);

	if (tbStock.exists())
	{
		tbStock.remove();
	}

	tbStock.create();

	sqlite3_exec(db.getHandle(), "begin transaction", 0, 0, NULL);

	for (std::vector<int>::const_iterator iter = stocksIndex.begin(); iter != stocksIndex.end(); ++iter)
	{
		Record record(tbStock.fields());

		record.setInteger(field_stockId, *iter);

		tbStock.addRecord(&record);
	}

	sqlite3_exec(db.getHandle(), "commit transaction", 0, 0, NULL);
}

void FNDBSystem::SaveToArchive(const std::map<int, std::vector<FNData> >& allStocks) 
{
	try
	{
		remove("c:/output/stocks.db");

		sql::Database db;

		db.open("c:/output/stocks.db");

		std::vector<int> stocksIndex;

		for (std::map<int, std::vector<FNData> >::const_iterator iter = allStocks.begin(); iter != allStocks.end(); ++iter)
		{
			int nStockId = iter->first;

			stocksIndex.push_back(nStockId);

			const std::vector<FNData>& vctStock = iter->second;

			const std::string& tablePreix = "table_";

			std::string tableName = tablePreix + INT2STR(nStockId);

			SaveOneStocks(db, tableName, vctStock);
		}

		SaveStockIndex(db, stocksIndex);

		db.close();
	}
	catch (Exception e) {

		printf("ERROR: %s\r\n", e.msg().c_str());
	}
}

FNData dataFromRecord(Record* record)
{
	FNData fndata;

	fndata.m_fEndPrice = record->getValue(field_endPrice)->asDouble();

	fndata.m_fOpenPrice = record->getValue(field_openPrice)->asDouble();

	fndata.m_fHighPrice = record->getValue(field_highPrice)->asDouble();

	fndata.m_fLowPrice = record->getValue(field_lowPrice)->asDouble();

	fndata.m_time = record->getValue(field_tradingDay)->asDouble();

	fndata.m_nTradingVolume = record->getValue(field_tradingVolum)->asInteger();

	fndata.m_nTradingAmount = record->getValue(field_tradingAmount)->asInteger();

	return fndata;
}

void FNDBSystem::LoadFromArchive(std::map<int, std::vector<FNData> >& allStocks)
{
	sql::Database db;

	db.open("c:/output/stocks.db");

	Table tbStockIds(db.getHandle(), "stockIds", FieldOfStockId);

	tbStockIds.open();

	std::vector<int> stockId;

	for (int index = 0; index < tbStockIds.recordCount(); index++)
	{
		Record* record = tbStockIds.getRecord(index);

		if (record)
		{
			int nStockId = record->getValue(field_stockId)->asInteger();
			
			stockId.push_back(nStockId);
		}
	}
	
	for (std::vector<int>::iterator iter = stockId.begin(); iter != stockId.end(); ++iter)
	{
		int stockId = *iter;

		const std::string& tablePreix = "table_";

		std::string tableName = tablePreix + INT2STR(stockId );

		Table tbStock(db.getHandle(), tableName, FieldOfStockInfo);

		tbStock.open();

		for (int index = 0; index < tbStock.recordCount(); index++)
		{
			Record* record = tbStock.getRecord(index);

			if (record)
			{
				FNData fndate = dataFromRecord(record);

				allStocks[stockId].push_back(fndate);
			}
		}
	}
}