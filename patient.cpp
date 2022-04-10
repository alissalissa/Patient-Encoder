//Implementation for Patient

#include "patient.h"

using namespace std;

//Constructors
Patient::Patient(void){
	age=-1;
	gender=peGENDER_DEFAULT;
	race=peRACE_DEFAULT;
	orientation=peORIENTATION_DEFAULT;
	name="";
	code="";
}

Patient::Patient(string n,string c,int a,char g,char r,char o){
	name=n;
	code=c;
	age=a;
	gender=g;
	race=r;
	orientation=o;
}

Patient::Patient(const Patient &haystack){
	name=haystack.name;
	code=haystack.code;
	age=haystack.age;
	gender=haystack.gender;
	race=haystack.race;
	orientation=haystack.orientation;
}
/*********************END CONSTRUCTORS*********************/

//Accessors
int &Patient::Age(void){return age;}
char &Patient::Gender(void){return gender;}
char &Patient::Race(void){return race;}
char &Patient::Orientation(void){return orientation;}
string &Patient::Name(void){return name;}
string &Patient::Code(void){return code;}
/*******************END ACCESSORS***************************/

//Operators
Patient &Patient::operator=(Patient &haystack){
	age=haystack.Age();
	gender=haystack.Gender();
	orientation=haystack.Orientation();
	race=haystack.Race();
	name=haystack.Name();
	code=haystack.Code();
	return haystack;
}

bool Patient::operator==(Patient haystack){
	bool ret=true;
	ret=((haystack.Age()==age)&&(haystack.Gender()==gender)&&(haystack.Race()==race)&&(haystack.Orientation()==orientation)&&(haystack.Name()==name)&&(haystack.Code()==code))?true:false;
	return ret;
}

bool Patient::operator!=(Patient haystack){
	return !this->operator==(haystack);
}

bool Patient::operator<(Patient haystack){
	if(age<haystack.Age()) return true;
	if(age>haystack.Age()) return false;
	if(age==haystack.Age()){
		if(code[code.length()-1]<haystack.Code()[haystack.Code().length()-1]) return true;
	}
	return false;
}
/*************************END OPERATORS********************/

void Patient::print(void){
	cout<<code<<"\t\t"<<name<<"\t\t"<<age<<"\t\t"<<gender<<"\t\t"<<race<<"\t\t"<<orientation<<endl;
}
