#pragma once

struct FNData;

#include <map>
#include <vector>

class FNDBSystem
{
public:
	static void SaveToArchive(const std::map<int, std::vector<FNData> >& allStocks);

	static void LoadFromArchive(std::map<int, std::vector<FNData> >& allStocks);
};