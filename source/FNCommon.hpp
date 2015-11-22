//
//  FNCommon.hpp
//  FNProject
//
//  Created by user on 15/10/21.
//  Copyright 漏 2015骞?user. All rights reserved.
//

#ifndef FNCommon_hpp
#define FNCommon_hpp

#include <stdio.h>
#include <string>
#include <vector>

#define MAX_PATH 256
#define INT2STR(k) FNCommonUtility::int2str(k) 
#define TIME2DATA(k) FNCommonUtility::time2date(k)

namespace FNCommonUtility {
	
	std::vector<std::string> SplitString(const std::string& str, const std::string& placeHoldstr);
	
	bool ReadDir(const std::string& dirName, std::vector<std::string>& vecFileNames);

	std::string int2str(int value);

	std::string time2date(time_t t);
}

#endif /* FNCommon_hpp */
