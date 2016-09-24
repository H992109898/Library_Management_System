#include"stdafx.h"
#include"object.h"
#include <sstream>

string object::operator = (CString& t){
	std::stringstream sstr;
	sstr << t;
	string result;
	sstr >> result;
	return result;
}

object::object(){}

//book
object::object(long long id,
	int type,
	string title,
	string author,
	int classification,  //分类
	bool E_Resourse,
	string ISBN,
	string publishingCompany,
	int page,
	bool hasVideoDisc,
	long long videoDiscId){

	this->id = id;
	this->type = type;
	this->title = title;
	this->author = author;
	this->classification = classification;
	this->E_Resourse = E_Resourse;

	this->ISBN = ISBN;
	this->publishingCompany = publishingCompany;
	this->page = page;
	this->hasVideoDisc = hasVideoDisc;
	this->videoDiscId = videoDiscId;
}


//video
object::object(long long id,
	int type,
	string title,
	string author,
	int classification,  //分类
	bool E_Resourse,
	string producer,
	string production_time,
	int duration){

	this->id = id;
	this->type = type;
	this->title = title;
	this->author = author;
	this->classification = classification;
	this->E_Resourse = E_Resourse;

	this->producer = producer;
	this->production_time = production_time;
	this->duration = duration;
}

//picture
object::object(long long id,
	int type,
	string title,
	string author,
	int classification,  //分类
	bool E_Resourse,
	string productionNationality,  //出品国籍
	int width,
	int height){

	this->id = id;
	this->type = type;
	this->title = title;
	this->author = author;
	this->classification = classification;
	this->E_Resourse = E_Resourse;

	this->productionNationality = productionNationality;
	this->width = width;
	this->height = height;
}

object::object(string objStr){
	std::istringstream is(objStr);
	is >> this->id 
		>> this->type 
		>> this->title
		>> this->author
		>> this->classification
		>>this->E_Resourse;


	switch (this->type){
	case TYPE_BOOK:
		is >> this->ISBN
			>> this->publishingCompany
			>> this->page
			>> this->hasVideoDisc
			>> this->videoDiscId;

		break;

	case TYPE_VIDEO:
		is >> this->producer
			>> this->production_time
			>> this->duration;
		break;

	case TYPE_PICTURE:
		is >> this->productionNationality
			>> this->width
			>> this->height;
		break;

	default:
		break;
	}

}

bool object::checkData(){
	//check base data;
	if (id < 0)
		return false;
	if (title.length() >= 500 || title.length() == 0)
		return false;
	if (author.length() >= 300 || author.length() == 0)
		return false;
	if (classification >4 || classification < 1)
		return false;


	switch (this->type){
	case TYPE_BOOK:
		if (publishingCompany.length() >=50 || publishingCompany.length() == 0
			||ISBN.length() >= 50 || ISBN.length()==0
			||page < 0
			|| (hasVideoDisc == true && videoDiscId <= 0))
			return false;
		break;
	case TYPE_VIDEO:
		if (producer.length() >= 30 ||producer.length() == 0
			||duration < 0)
			return false;
		break;
	case TYPE_PICTURE:
		if (productionNationality.length() >= 30 || productionNationality.length() ==0
			|| width < 0
			|| height < 0)
		return false;
		break;
	default:
		return false;
	}
	return true;
}


string object::toString(){
	std::ostringstream os;
	os << this->id << "  "
		<< this->type << "  "
		<< this->title << "  "
		<< this->author << "  "
		<< this->classification << "  "
		<< this->E_Resourse << "  ";

	switch (this->type){
	case TYPE_BOOK:
		os << this->ISBN << "  "
			<< this->publishingCompany << "  "
			<< this->page << "  "
			<< this->hasVideoDisc << "  "
			<< this->videoDiscId;

		break;

	case TYPE_VIDEO:
		os << this->producer << "  "
			<< this->production_time << "  "
			<< this->duration;
		break;

	case TYPE_PICTURE:
		os << this->productionNationality << "  "
			<< this->width << "  "
			<< this->height;
		break;

	default:
		break;
	}

	os << std::endl;

	return os.str();
}

bool object::checkDate(CString t){
	string temp = (CStringA)t;
	char date[15];
	strcpy_s(date, temp.c_str());
	int time[3] = { 0, 0, 0 };
	int pos[2] = { 0, 0 };
	int j = 0, k = 0;
	if (date[0] <'0' || date[0] >'9')
		return false;
	for (int i = 0; i < strlen(date); i++){
		if (date[i] == '/')
			pos[j++] = i;
		if (date[i] == '-')
			pos[k++] = i;
		if ((date[i] == '-' || date[i] == '/' || date[i] >= '0' && date[i] <= '9') == false)
			return false;
	}

	if (j == 2 && k == 0 ||
		j == 0 && k == 2){
		//获取并且判断一下三个时间
		string subString = temp.substr(0, pos[0]);
		time[0] = atoi(subString.c_str());

		subString = temp.substr(pos[0] + 1, pos[1]);
		time[1] = atoi(subString.c_str());

		subString = temp.substr(pos[1] + 1, temp.length());
		time[2] = atoi(subString.c_str());

		if (time[1]<0 || time[1] >12 || time[2] < 0 || time[2] >31)
			return false;

	}
	else
		return false;

	return true;
}