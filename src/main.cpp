/*
 * main.cpp
 *
 *  Created on: 2018年7月15日
 *      Author: Administrator
 */

#include <iostream>
#include <map>
#include "lzw.cpp"


using std::cout;
using std::endl;
using std::cin;

int main(){
//	std::map<char,int> mapTest;
//
//	char p = '/';
//
//	mapTest.insert(std::pair<char,int> (p,(int)p));
//	cout<<mapTest.at(p);
//	testAsciiToHex();
//	myMap mt;
//	mt.initMap();
//	mt.insertNew("aa");
//	mt.insertNew("/");
//	mt.insertNew("iloveyou");
//	cout<<mt.getCode(19)<<endl;
//	cout<<mt.getCode(47)<<endl;;
//	cout<<mt.getCode(256)<<endl;
//	cout<<mt.getCode(257)<<endl;
//	cout<<mt.getSize()<<endl;
//	cout<<mt.findByValue("iloveyou")<<endl;
//	H:\\LZWin.txt

	char inFile[100],outFile[100],chFile[100];
	encrypt et;
//	int i;
//	cout<<"压缩文件输入1，解压文件输入2，打印字典输入3："<<endl;
//	cin>>i;
//	if(i==1){
//		cout<<"输入被压缩文件地址："<<endl;
//		cin>>inFile;
//		cout<<"输入压缩后文件地址："<<endl;
//		cin>>chFile;
//		et.Compress(inFile,chFile);
//	}
//	else if(i==2){
//		cout<<"输入被解压文件地址："<<endl;
//		cin>>chFile;
//		cout<<"输入解压后文件地址："<<endl;
//		cin>>outFile;
//		et.Decompress(chFile,outFile);
//	}
//	else if(i==3){
//		cout<<"输入被压缩文件地址："<<endl;
//		cin>>chFile;
//		cout<<"输入压缩后字典地址："<<endl;
//		cin>>outFile;
//		et.printDic(chFile,outFile);
//	}
//	else{
//		cout<<"输入错误"<<endl;
//		return 0;
//	}
	while(1){
		int i;
		cout<<"压缩文件输入1，解压文件输入2，打印字典输入3，退出输入0："<<endl;
		cin>>i;
		try{
			if(cin.fail())
				throw "wrong!";
		}
		catch(const char*){
			cin.clear();        //清楚错误输入的缓存
			cin.sync();
			cout<<"请确认输入的为数字！"<<endl;
			continue;
		}
		switch(i){
		case 1 :{
			cout<<"输入被压缩文件地址："<<endl;
			cin>>inFile;
			cout<<"输入压缩后文件地址："<<endl;
			cin>>chFile;
			et.Compress(inFile,chFile);
//			fflush(stdout);
//		    freopen("CON","r",stdin);
//		    freopen("CON","w",stdout);
//		    fflush(stdout);
			break;
		}
		case 2 :{
			cout<<"输入被解压文件地址："<<endl;
			cin>>chFile;
			cout<<"输入解压后文件地址："<<endl;
			cin>>outFile;
			et.Decompress(chFile,outFile);
			break;
		}
		case 3 :{
			cout<<"输入被压缩文件地址："<<endl;
			cin>>chFile;
			cout<<"输入压缩后字典地址："<<endl;
			cin>>outFile;
			et.printDic(chFile,outFile);
			break;
		}
		case 0 :{
			return 0;
		}
		default: cout<<"无效的输入！"<<endl;
		}

	}
	return 0;
}


