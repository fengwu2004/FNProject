//
//  FNAnalyserOne.hpp
//  FNProject
//
//  Created by user on 15/11/23.
//  Copyright © 2015年 user. All rights reserved.
//

#ifndef FNAnalyserOne_hpp
#define FNAnalyserOne_hpp

#include <stdio.h>
#include "FNAnalyser.hpp"

class FNAnalyserOne: public FNAnalyser {
	
public:
	virtual bool AnalyserData(const std::vector<FNData>& vctFNData);
};

#endif /* FNAnalyserOne_hpp */
