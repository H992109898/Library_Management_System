#include"stdafx.h"
#include"media_data_base.h"

class video_model:public media_data_base{
public:
	video_model(
		long long id,
		string title,
		string author,
		int classification,  //·ÖÀà
		bool E_Resourse,
		string producer,
		string production_time,
		int duration
		);

	string toString();
	bool checkData();

protected:
	string producer;
	string production_time;
	int duration;
};