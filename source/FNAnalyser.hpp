//
//  FNAnalyser.hpp
//  FNProject
//
//  Created by user on 15/10/22.
//  Copyright ¬© 2015Âπ?user. All rights reserved.
//

#ifndef FNAnalyser_hpp
#define FNAnalyser_hpp

#include <stdio.h>
#include "FNDataDefine.h"

class FNAnalyser {
	
public:
	~FNAnalyser() {}
	
	virtual bool AnalyserData(const std::vector<FNData>& vctFNData) = 0;
};

#endif /* FNAnalyser_hpp */
