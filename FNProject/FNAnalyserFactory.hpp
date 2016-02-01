//
//  FNAnalyserFactory.hpp
//  FNProject
//
//  Created by user on 15/11/23.
//  Copyright © 2015年 user. All rights reserved.
//

#ifndef FNAnalyserFactory_hpp
#define FNAnalyserFactory_hpp

#include <stdio.h>
#include <map>
#include "FNAnalyser.hpp"

class FNAnalyserFactory {
	
public:
	static FNAnalyserFactory* sharedInstance();

	FNAnalyser* getAnalyser(int nType);

private:
	std::map<int, FNAnalyser*> m_allAnalysers;
};

#endif /* FNAnalyserFactory_hpp */
