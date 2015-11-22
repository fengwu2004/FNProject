#pragma once

#include "easysqlite3/SqlCommon.h"

class FNDBSystem
{
public:
	static FNDBSystem * sharedInstance();

public:
	void init();
};

