#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>
#include <vector> 

#ifndef _STATIC_HELPER
#define _STATIC_HELPER

static void removeDuplicatedMove(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& moves) 
{
	std::sort(moves.begin(), moves.end());
	moves.erase(std::unique(moves.begin(), moves.end()), moves.end());
}

static void removeDuplicatedLoc(std::vector<std::pair<int, int>>& locs) {
	std::sort(locs.begin(), locs.end());
	locs.erase(std::unique(locs.begin(), locs.end()), locs.end());
}


#endif