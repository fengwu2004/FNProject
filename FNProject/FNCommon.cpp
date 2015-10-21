//
//  FNCommon.cpp
//  FNProject
//
//  Created by user on 15/10/21.
//  Copyright © 2015年 user. All rights reserved.
//

#include "FNCommon.hpp"
#include "boost/regex.hpp"

namespace FNCommonUtility {
	
	std::vector<std::string> SplitString(const std::string& str, const std::string& placeHoldstr) {
		
		std::vector<std::string> tempData;
		
		boost::regex pat(placeHoldstr);
		
		boost::sregex_token_iterator it(str.begin(), str.end(), pat, -1);
		
		boost::sregex_token_iterator end;
		
		while (it != end) {
			
			tempData.push_back(*it++);
		}
		
		return tempData;
	}
}