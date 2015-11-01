//
//  main.cpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright 漏 2015骞?user. All rights reserved.
//

#include <iostream>
#include "FNStockData.hpp"
#include "FNAnalyseMgr.hpp"

int main(int argc, const char * argv[]) {

	FNAnalyseMgr::sharedInstance()->Excute();
	
	return 0;
}