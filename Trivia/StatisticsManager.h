#pragma once

#include "SqliteDatabase.h"

class StatisticsManager : public SqliteDatabase
{
	// CTOR && DTOR //
	StatisticsManager();
	virtual ~StatisticsManager();

private:
	SqliteDatabase* _sqlDatabase;
};