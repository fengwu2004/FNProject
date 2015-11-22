//
//  FNAnalyseMgr.hpp
//  FNProject
//
//  Created by user on 15/10/22.
//  Copyright Â© 2015å¹?user. All rights reserved.
//

#ifndef FNAnalyseMgr_hpp
#define FNAnalyseMgr_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "FNDataDefine.h"

class FNAnalyseMgr {
	
public:
	static FNAnalyseMgr* sharedInstance();
	
	void Excute();
	
	void OutputResult();
	
private:
	void RunOnCondition();

	void OnSaveToDB();
	
	bool AnalyseData(const std::vector<FNData>& dataArray);
	
private:
	std::map<int, std::vector<FNData> > m_dicStockData;
	
	std::vector<int> m_vctResult;
};


#endif /* FNAnalyseMgr_hpp */
