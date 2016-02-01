//
//  FNCommon.cpp
//  FNProject
//
//  Created by user on 15/10/21.
//  Copyright © 2015�?user. All rights reserved.
//

#include "FNCommon.hpp"
#include <sstream>
#include "boost/regex.hpp"
#include "easysqlite3/SqlCommon.h"

#ifdef WIN32
#include "win/dirent.h"
#else
#include <dirent.h>
#endif

#include <sys/stat.h>

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
	
	bool ReadDir(const std::string& dirName, std::vector<std::string>& vecFileNames) {
		
		DIR *dir;
		
		struct dirent *drt;
		
		if ((dir = opendir(dirName.c_str())) == NULL) {
			
			return false;
		}
		
		while ((drt = readdir(dir)) != NULL) {
			
			if ((strcmp(drt->d_name, ".") != 0) && (strcmp(drt->d_name, "..") != 0)) {
				
				char szTempDir[MAX_PATH] = { 0 };
				
				sprintf(szTempDir, "%s/%s", dirName.c_str(), drt->d_name);
				
				struct stat buf;
				
				stat(szTempDir, &buf);
				
				if (!S_ISDIR(buf.st_mode)) {
					
					vecFileNames.push_back(szTempDir);
				}
			}
		}
		
		closedir(dir);
		
		return true;
	}

	std::string int2str(int value) {

		char szText[64] = { 0 };

		sprintf(szText, "%06d", value);
		
		return szText;
	}

	std::string time2date(time_t t) {

		sql::time mytime(t);

		return mytime.asDateString();
	}
}