//
//  FNData.hpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright © 2015�?user. All rights reserved.
//

#ifndef FNData_hpp
#define FNData_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "FNDataDefine.h"

class FNStockData
{
public:
	static FNStockData* sharedInstance();
	
	void FNStockData::LoadFromFile(const std::string& fileName, std::map<int, std::vector<FNData> >& data);
};

#endif /* FNData_hpp */
