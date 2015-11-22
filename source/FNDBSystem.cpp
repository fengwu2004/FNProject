#include "FNDBSystem.h"
#include "easysqlite3/SqlCommon.h"
#include "easysqlite3/SqlField.h"
#include "easysqlite3/SqlDatabase.h"
#include "easysqlite3/SqlTable.h"

using namespace sql;

FNDBSystem *FNDBSystem::sharedInstance() {

	static FNDBSystem instance;

	return &instance;
}

void FNDBSystem::init() {

	Field definition_tbPerson[] =
	{
		Field(FIELD_KEY),
		Field("fname", type_text, flag_not_null),
		Field("lname", type_text, flag_not_null),
		Field("birthdate", type_time),
		Field(DEFINITION_END),
	};

	//define database object
	sql::Database db;

	db.open("test.db");

	//define table object
	Table tbPerson(db.getHandle(), "person", definition_tbPerson);

	//remove table from database if exists
	if (tbPerson.exists())
		tbPerson.remove();

	//create new table
	tbPerson.create();

	//define new record
	Record record(tbPerson.fields());

	//set record data
	record.setString("fname", "Jan");
	record.setString("lname", "Kowalski");
	record.setTime("birthdate", time::now());

	//add 10 records
	for (int index = 0; index < 10; index++)
		tbPerson.addRecord(&record);

	//select record to update
	if (Record* record = tbPerson.getRecordByKeyId(7))
	{
		record->setString("fname", "Frank");
		record->setString("lname", "Sinatra");
		record->setNull("birthdate");

		tbPerson.updateRecord(record);
	}

	//load all records
	tbPerson.open();

	//list loaded records
	for (int index = 0; index < tbPerson.recordCount(); index++)
		if (Record* record = tbPerson.getRecord(index))
			sql::log(record->toString());

	sql::log("");
	sql::log("ALL OK");
}