#pragma once
#include"stdafx.h"
#include<iostream>
#include<string>
using namespace std;

class media_data_base{
public:
	media_data_base(
		long long id,
		int type,
		string title,
		string author,
		int classification,  //分类
		bool E_Resourse);

	~media_data_base();
	long long getId();
	long long setId(long long t);
	int getType();
	int setType(int t);

	string getTitle();
	string setTitle(string title);
	string getAuthor();
	string setAuthor(string Author);
	int getClassification();
	int setClassification(int classification);
	bool isE_Resourse();
	bool setE_Resourse(bool b);
	virtual string toString();
	virtual bool checkData();

	static const int UNASSORTED = 1;  //未分级
	static const int COMMON = 2;      //一般
	static const int ADULT = 3;       //成人 
	static const int CHILDREN = 4;    //儿童
	static const int BOOK = 1;
	static const int VIDEO = 2;
	static const int PICTURE = 3;

	long long id;
	int type;
	string title;
	string author;
	int classification;  //分类
	bool E_Resourse;

};