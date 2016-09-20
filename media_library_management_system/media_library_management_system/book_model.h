#include"media_data_base.h"

class book_model:public media_data_base{
public:
	book_model(
		long long id,
		string title,
		string author,
		int classification,  //·ÖÀà
		bool E_Resourse,
		string ISBN,
		string publishingCompany,
		int page,
		bool hasVideoDisc,
		long long videoDiscId = -1
		);

	string toString();
	bool checkData();

protected:
	string ISBN;
	string publishingCompany;
	int page;
	bool hasVideoDisc;
	long long videoDiscId;

};