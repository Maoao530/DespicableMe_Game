#include "XMLParser.h"

using namespace std;
using namespace cocos2d;

//字符ascii码
// 空格
const static int SPACE = 32;
// 换行
const static int NEXTLINE = 10;
// tab 横向制表符
const static int TAB = 9;

XMLParser* XMLParser::parseWithFile(const char *xmlFileName)
{
	XMLParser *pXMLParser = new XMLParser();
	if( pXMLParser->initWithFile(xmlFileName) )
	{
		pXMLParser->autorelease();   
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithFile(const char *xmlFileName)
{
	m_pDictionary = new CCDictionary();
	SAXParser _parser;
	_parser.setDelegator(this);
	//获取文件全路径
	string fullPath = FileUtils::getInstance()->fullPathForFilename(xmlFileName);
//	CCLog("xml parser full path : %s",fullPath.c_str());

	return _parser.parse(fullPath);
}

XMLParser* XMLParser::parseWithString(const char *content)
{
	XMLParser *pXMLParser = new XMLParser();
	if( pXMLParser->initWithString(content) )
	{
		pXMLParser->autorelease();   
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithString(const char *content)
{
	m_pDictionary = new CCDictionary();
	SAXParser _parse;
	_parse.setDelegator(this);
	return _parse.parse(content, strlen(content) );
}

//开始一个节点
// 比如<string name="app_name">小黄人大作战</string>
//name    为		:string 
//atts[0] 为属性	: name
//atts[1] 为值		: app_name
//atts[2] 以此类推
void XMLParser::startElement(void *ctx, const char *name, const char **atts)
{
	this->startXMLElement = (char *)name;
//	CCLog("start=%s", startXMLElement.c_str());//name

	if(this->startXMLElement == "string")
	{
		while(atts && *atts)
		{
//			CCLog("attrs0=%s", atts[0]);	//atts[0] : name
//			CCLog("attrs1=%s", atts[1]);	//atts[1] : app_name
// 			CCLog("attrs2=%s", atts[2]);	//atts[2]
// 			CCLog("attrs3=%s", atts[3]);	//atts[3]

			const char *attsKey = *atts;    
			if(0 == strcmp(attsKey, "name"))
			{
				++ atts;
				const char *attsValue = *atts;
				m_key = attsValue;			//key
				break;
			}
			++ atts;
		}

	}

	if(this->startXMLElement == "total_wave"){
		m_key = "total_wave";
	}
	if(this->startXMLElement == "wave"){
		while(atts && *atts)
		{
//			CCLog("attrs0=%s", atts[0]);	
//			CCLog("attrs1=%s", atts[1]);	
			
			const char *attsKey = *atts;    
			if(0 == strcmp(attsKey, "id"))
			{
				++ atts;
				const char *attsValue = *atts;
				m_key = attsValue;			//key
				break;
			}
			++ atts;
		}
	}

}

void XMLParser::endElement(void *ctx, const char *name)
{
	this->endXMLElement = (char *)name;
//	CCLog("end=%s", endXMLElement.c_str());
}

void XMLParser::textHandler(void *ctx, const char *s, int len)
{
	string value((char *)s, 0, len);

	//是否全是非正常字符
	bool noValue = true;
	for(int i = 0; i < len; ++i)
	{
		if(s[i] != SPACE && s[i] != NEXTLINE && s[i] != TAB)
		{
			noValue = false;    
			break;
		}
	}
	if(noValue) return;
	String *pString = String::create(value);
//	CCLog("key=%s value=%s", m_key.c_str(), pString->getCString());
	this->m_pDictionary->setObject(pString, this->m_key);
}

String* XMLParser::getString(const char *key)
{
	string strKey(key);
	return (String *)this->m_pDictionary->objectForKey(strKey);
}

XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
	CC_SAFE_DELETE(this->m_pDictionary);
}