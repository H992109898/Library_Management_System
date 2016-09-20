#include"stdafx.h"
#include"media_data_base.h"

#include <string>

class picture_model :public media_data_base{
public:
	picture_model(long long id,
		string title,
		string author,
		int classification,  //分类
		bool E_Resourse,
		string productionNationality,
		int width,
		int height);
	~picture_model();
	string toString();
	int getWidth();
	int setWidth(int width);
	int getHeight();
	int setHeight(int height);
	string getProductionNationality();
	string setProductionNationality(string productionNationality);

protected:
	string productionNationality;  //出品国籍
	int width;
	int height;
};