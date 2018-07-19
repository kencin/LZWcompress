/*
 * lzw.cpp
 *
 *  Created on: 2018年7月15日
 *      Author: Administrator
 */

#include<string>
#include "myMap.cpp"
#include<sstream>
#include<iostream>
#include <fstream>

#include<time.h>
using std::string;

struct node{
	string P;   //previous
	char C;	  //current
	string S;
};

class encrypt{
public:
	encrypt(){
	}

	/*
	 * 下面为根据值去查找键的方法，
	 * 查找效率实在太低，弃用
	 */
//	void Compress(char *inFile,char *chFile){
//		startTime = clock();
//		mp.initMap();
//		freopen(inFile,"r",stdin);
//		freopen(chFile,"w",stdout);
//		while((nd.C = getchar()) && nd.C != EOF){
//			std::stringstream stream;
//			stream<<nd.C;
//			mp.insertNew(stream.str());          // n
//			searchDic(nd.C);          //n^2
//		}
//		printf("%03x",mp.findByValue(nd.P));   //1
//		endTime = clock();
//		std::cout << "Total Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
//		fclose(stdin);
//		fclose(stdout);
//	}
//	void searchDic(char c){
//		std::stringstream stream;
//		stream<<nd.P;
//		stream<<c;
//		string str = stream.str();
//		if(mp.findByValue(str)==-2){
//			printf("%03x",mp.findByValue(nd.P));
//			mp.insertNew(str);
//			nd.P=c;
//		}
//		else
//			nd.P=nd.P+c;
//	}
	void Compress(char *inFile,char *chFile){
		startTime = clock();
		initNd();
		mp.initCompressMap();
//		freopen(inFile,"r",stdin);
//		freopen(chFile,"w",stdout);
		std::ofstream out(chFile);
		std::ifstream in(inFile);
		while((nd.C = in.get()) && nd.C != EOF){
			std::stringstream stream;
			stream<<nd.C;                   //字符转换为字符串
			mp.compressInsert(stream.str());          //把current读入的字符插入字典中
			searchDic(nd.C,out);          //搜索字典
		}
//		mp.goTo();
//		printf("%x",mp.getCode(nd.P));   //1
//		printf(" ");
		out << std::hex << mp.getCode(nd.P)<<" ";
		out.close();
		in.close();
		endTime = clock();
		std::cout << "压缩此文件耗时 : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;    //程序运行时间的打印
	}
	void searchDic(char c,std::ofstream &s){
		std::stringstream stream;
		stream<<nd.P;
		stream<<c;
		string str = stream.str();       //str=P+C
		if(mp.existKey(str)==0){         //如果str在字典中不存在，输出P的编码，插入str，然后P=C
//			printf("%x",mp.getCode(nd.P));
//			printf(" ");
			s << std::hex << mp.getCode(nd.P)<<" ";
			mp.compressInsert(str);
			nd.P=c;
		}
		else          //如果P在字典中，P=P+C
			nd.P=nd.P+c;
	}
	void Decompress(char *chFile,char *outFile){
		startTime = clock();
		initNd();
		mp.initMap();
		int Q;
		std::ofstream out(outFile);
		std::ifstream in(chFile);
		in >> std::hex >>Q;      //以16进制读取至Q
		while(in.get()!= EOF){
				if(Q<mp.getSize() && mp.getValue(Q) == "-1"){      //如果读入的字符属于ASCII表，强制转换成int并插入字典
					std::stringstream stream;
					stream<<(char)Q;
					mp.insertNew(stream.str());
//					std::cout<<(char)Q<<" ";
				}

				if(Q<mp.getSize()){           //读入字符在字典里面，输出Q对应的值，在字典中添加tmp
					out<<mp.getValue(Q);
					nd.S=mp.getValue(Q).substr(0,1);         // S取Q对应的值的第一个字符
					string tmp = nd.P+nd.S;
					mp.insertNew(tmp);
				}
				else{                          //读入字符不在字典中，	tmp=P的值+P的值的第一位字符。 添加tmp的值,并输出tmp的值
					string tmp = nd.P+nd.P.substr(0,1);
					mp.insertNew(tmp);
					out<<tmp;
				}
				nd.P=mp.getValue(Q);
				in >> std::hex >>Q;
			}
		out.close();
		in.close();
		endTime = clock();
		std::cout << "解压此文件耗时 : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;    //程序运行时间的打印
	}
	void printDic(char *inFile,char *chFile){
		startTime = clock();
		initNd();
		mp.initCompressMap();
//		freopen(inFile,"r",stdin);
//		freopen(chFile,"w",stdout);
		std::ofstream out(chFile);
		std::ifstream in(inFile);
		while((nd.C = in.get()) && nd.C != EOF){
			std::stringstream stream;
			stream<<nd.C;
			mp.compressInsert(stream.str());          // n
			searchDicNoPrint(nd.C);          //n^2
		}
		mp.goTo(out);   //字典遍历输出
		out.close();
		in.close();
		endTime = clock();
		std::cout << "打印字典耗时 : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;    //程序运行时间的打印
	}
	void searchDicNoPrint(char c){
			std::stringstream stream;
			stream<<nd.P;
			stream<<c;
			string str = stream.str();
			if(mp.existKey(str)==0){
				mp.compressInsert(str);
				nd.P=c;
			}
			else
				nd.P=nd.P+c;
		}
private:
	void initNd(){      //清空字符串
		nd.P.clear();
		nd.S.clear();
	}
	node nd;
	myMap mp;
	clock_t startTime,endTime;
};


