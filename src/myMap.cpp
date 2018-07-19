/*
 * myMap.cpp
 *
 *  Created on: 2018年7月15日
 *      Author: Administrator
 */


#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
using  std::string;

class map_value_finder
{
public:
       map_value_finder(const std::string &cmp_string):m_s_cmp_string(cmp_string){}
       bool operator ()(const std::map<int, std::string>::value_type &pair)
       {
            return pair.second == m_s_cmp_string;
       }
private:
        const std::string &m_s_cmp_string;
};


class myMap{
public:
	void initMap(){
		cnt = 0;
		for(int i=0;i<=255;i++)
		{
			Dic.insert(std::pair<int,string>(i,"-1"));
			cnt++;
		}
	}
	void initCompressMap(){
		dDic.clear();
		cnt = 256;
	}
	void insertNew(const string &newcode){
		if(newcode.length()<2&&(int)newcode[0]<=255){
			Dic[(int)newcode[0]] = newcode;
		}
		else{
			Dic.insert(std::pair<int,string>(cnt,newcode));
			cnt++;
		}
	}
	void compressInsert(const string &newcode){
		if(newcode.length()<2&&(int)newcode[0]<=255){
			dDic.insert(std::pair<string,int>(newcode,(int)newcode[0]));
		}
		else{
			dDic.insert(std::pair<string,int>(newcode,cnt));
			cnt++;
		}
	}

	int getCode(const string &value){
		return dDic[value];
	}
	int existKey(string str){
		return dDic.count(str);
	}
	string getValue(const int &num){
		return Dic.at(num);
	}
	int getSize(){
		return Dic.size();
	}
	int findByValue(string value){
		std::map<int,string>::iterator it = Dic.end();
		it = std::find_if(Dic.begin(),Dic.end(),map_value_finder(value));
		if(it == Dic.end()){
			return -2;
		}
		else
			return it->first;
	}
	void goTo(std::ostream &s){
		std::map<string,int>::iterator iter = dDic.begin();
		while(iter != dDic.end()) {
//			 std::cout << iter->first;
//				printf(" : ");
//				printf("%03x",iter->second);
//				std::cout<<std::endl;
		        s << iter->first << " : " <<std::hex <<iter->second << std::endl;
		        iter++;
		    }
	}

private:
	std::map<string,int> dDic;
	std::map<int,string> Dic;
	int cnt = 0;
};

