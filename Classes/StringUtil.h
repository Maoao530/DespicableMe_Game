#pragma once
/**
 * @file         StringUtil.h    
 * @date         2014-7-5
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class StringUtil{
public:
	static vector<string> split(string str,string pattern);
	static vector<int> splitForInt(string str,string pattern);
};