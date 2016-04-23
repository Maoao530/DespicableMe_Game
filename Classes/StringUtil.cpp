#include "StringUtil.h"

vector<string> StringUtil::split(string str,string pattern){

	string::size_type pos;
	vector<string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i = 0; i < size; i++)
	{
		pos=str.find(pattern,i);
		if(pos < size)
		{
			string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;

}

vector<int> StringUtil::splitForInt(string str,string pattern){
	string::size_type pos;
	vector<int> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i = 0; i < size; i++)
	{
		pos=str.find(pattern,i);
		if(pos < size)
		{
			string s=str.substr(i,pos-i);
			int n = atoi(s.c_str());
			result.push_back(n);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}