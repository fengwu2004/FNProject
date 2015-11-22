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
	try
	{
		sql::Database db;

		db.open("c:/output/stocks.db");

		for (std::map<int, std::vector<FNData> >::const_iterator iter = allStocks.begin(); iter != allStocks.end(); ++iter)
		{
			int nStockId = iter->first;

			const std::vector<FNData>& vctStock = iter->second;

			const std::string& tablePreix = "table_";

			std::string tableName = tablePreix + INT2STR(nStockId);

			Table tbStock(db.getHandle(), tableName, stockField);

			if (tbStock.exists())
			{
				tbStock.remove();
			}

			tbStock.create();

			sqlite3_exec (db.getHandle() , "begin transaction", 0, 0, NULL);

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

			sqlite3_exec (db.getHandle(), "commit transaction", 0, 0, NULL);
		}

		db.close();
	}
	catch (Exception e) {

		printf("ERROR: %s\r\n", e.msg().c_str());
	}
}