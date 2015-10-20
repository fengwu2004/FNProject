//
//  FNData.hpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright © 2015年 user. All rights reserved.
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
	
	void LoadFromFile(const std::string& fileName);
	
private:
	std::map<int, std::vector<FNData> > m_vctStockData;
	
	std::vector<int> m_vctResult;
};

#endif /* FNData_hpp */
