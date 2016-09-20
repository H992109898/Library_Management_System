#include"stdafx.h"
#include"picture_model.h"
using namespace std;
picture_model::picture_model(
	long long id,
	string title,
	string author,
	int classification,  //·ÖÀà
	bool E_Resourse,
	string productionNationality,
	int width,
	int height) :media_data_base(id, media_data_base::PICTURE,title, author, classification, E_Resourse){
	this->productionNationality = productionNationality;
	this->width = width;
	this->height = height;
}

picture_model::~picture_model(){

}

string picture_model::toString(){
	string temp("picture ");
	temp += width;
	temp += "  ";
	temp += height;
	temp += "  ";
	temp += productionNationality;
	temp += "  ";
	return temp + this->media_data_base::toString();
}

int picture_model::getWidth(){
	return this->width;
}

int picture_model::setWidth(int width){
	return this->width = width;
}

int picture_model::getHeight(){
	return this->height;
}

int picture_model::setHeight(int height){
	return this->height = height;
}

string picture_model::getProductionNationality(){
	return this->productionNationality;
}

string picture_model::setProductionNationality(string productionNationality){
	return this->productionNationality = productionNationality;
}


//´ý²¹³ä
bool picture_model::checkData(){
	return true;
}