//
//  main.cpp
//  FNProject
//
//  Created by user on 15/10/19.
//  Copyright © 2015�?user. All rights reserved.
//

#include <iostream>
#include "FNStockData.hpp"

int main(int argc, const char * argv[]) {
	
	FNStockData::sharedInstance()->LoadFromFile("C:/data/SH#600004.txt");
	
	return 0;
}