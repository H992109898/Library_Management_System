#include"stdafx.h"
#include"media_data_base.h"

media_data_base::media_data_base(
	long long id,
	int type,
	string title,
	string author,
	int classification,  //·ÖÀà
	bool E_Resourse){

	this->id = id;
	this->type = type;
	this->title = title;
	this->author = author;
	this->classification = classification;
	this->E_Resourse = E_Resourse;
}


media_data_base::~media_data_base(){
	
}


bool media_data_base::isE_Resourse(){
	return this->E_Resourse;
}


bool media_data_base::setE_Resourse(bool b){
	return this->E_Resourse = b;
}

long long media_data_base::getId(){
	return this->id;
}

long long media_data_base::setId(long long t){
	return this->id = t;
}

int media_data_base::getType(){
	return this->type;
}

int media_data_base::setType(int t){
	return this->type = t;
}

string media_data_base::getTitle(){
	return this->title;
}

string media_data_base::setTitle(string title){
	return this->title = title;
}

string media_data_base::getAuthor(){
	return this->author;
}

string media_data_base::setAuthor(string Author){
	return this->author = Author;
}

int media_data_base::getClassification(){
	return this->classification;
}

int media_data_base::setClassification(int classification){
	return this->classification = classification;
}

string media_data_base::toString(){
	string temp("");
	temp += this->id;
	temp += "  ";
	temp += this->title;
	temp += "  ";
	temp += this->author;
	temp += "  ";
	temp += this->classification;
	temp += "  ";
	return temp;
}

bool media_data_base::checkData(){
	return true;
}
