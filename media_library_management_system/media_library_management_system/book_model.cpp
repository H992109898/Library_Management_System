#include"stdafx.h"
#include"book_model.h"

book_model::book_model(
	long long id,
	string title,
	string author,
	int classification,  //·ÖÀà
	bool E_Resourse,
	string ISBN,
	string publishingCompany,
	int page,
	bool hasVideoDisc,
	long long videoDiscId
	) :media_data_base(id, media_data_base::BOOK, title, author, classification, E_Resourse){

	this->ISBN = ISBN;
	this->publishingCompany = publishingCompany;
	this->page = page;
	this->hasVideoDisc = hasVideoDisc;
	this->videoDiscId = videoDiscId;
}


//´ý²¹³ä
string book_model::toString(){
	return "";
}

//´ý²¹³ä
bool book_model::checkData(){
	return true;
}