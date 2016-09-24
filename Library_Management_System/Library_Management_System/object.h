#pragma once
#include "stdafx.h"
#include <string>
using std::string;




class object{
public:
	static bool checkDate(CString);
	string operator = (CString& t);
	object();

	//book
	object(long long id,
		int type,
		string title,
		string author,
		int classification,  //分类
		bool E_Resourse, 
		string ISBN,
		string publishingCompany,
		int page,
		bool videoDisc,
		long long videoDiscId = -1);


	//video
	object(long long id,
		int type,
		string title,
		string author,
		int classification,  //分类
		bool E_Resourse,
		string producer,
		string production_time,
		int duration);

	//picture
	object(long long id,
		int type,
		string title,
		string author,
		int classification,  //分类
		bool E_Resourse,
		string productionNationality,  //出品国籍
		int width,
		int height);

	object(string objStr);

	bool checkData();
	string toString();


	long long id;
	int type;
	string title;
	string author;
	int classification;  //分类
	bool E_Resourse;

	static const int CLASSIFICATION_CHILDREN = 1;
	static const int CLASSIFICATION_NORMAL = 2;
	static const int CLASSIFICATION_UNDIFINE = 3;
	static const int CLASSIFICATION_ADULT = 4;
	static const int TYPE_BOOK = 1;
	static const int TYPE_VIDEO = 2;
	static const int TYPE_PICTURE = 3;

	//field for book
	string ISBN;
	string publishingCompany;
	int page;
	bool hasVideoDisc;
	long long videoDiscId;

	//field for video
	string producer;
	string production_time;
	int duration;

	//field for picture
	string productionNationality;  //出品国籍
	int width;
	int height;

	
};