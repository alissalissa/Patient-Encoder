#ifndef __PATIENTENCODER_PATIENT_H__
#define __PATIENTENCODER_PATIENT_H__

//STL includes
#include <cstdlib>
#include <iostream>
#include <string>

//wx Includes
#include <wx/wx.h>

//Macros
//Gender
#define peGENDER_FEMALE 'F'
#define peGENDER_MALE 'M'
#define peGENDER_TRANS 'T'
#define peGENDER_DEFAULT peGENDER_FEMALE
//Race
#define peRACE_WHITE 'W'
#define peRACE_BLACK 'B'
#define peRACE_HISPANIC 'H'
#define peRACE_ASIAN 'A'
#define peRACE_BIRACIAL 'I'
#define peRACE_OTHER 'O'
#define peRACE_DEFAULT peRACE_WHITE
//Define others once we verify the time2track categories
//Orientation
#define peORIENTATION_STRAIGHT 'S'
#define peORIENTATION_GAY 'G'
#define peORIENTATION_BI 'B'
#define peORIENTATION_OTHER 'O'
#define peORIENTATION_UNKNOWN 'U'
#define peORIENTATION_DEFAULT peORIENTATION_UNKNOWN
//Define others once we verify the time2track categories

using namespace std;

class Patient{
private:

	int age;
	char gender;
	char race;
	char orientation;
	string name;
	string code;

public:

	//Constructors
	Patient(void);
	Patient(string,string,int,char=peGENDER_DEFAULT,char=peRACE_DEFAULT,char=peORIENTATION_DEFAULT);
	Patient(const Patient&);
	~Patient()=default;

	//Accessors
	int &Age(void);
	char &Gender(void);
	char &Race(void);
	char &Orientation(void);
	string &Name(void);
	string &Code(void);
	string get_name(void)const{return name;}
	string get_code(void)const{return code;}
	int get_age(void)const{return age;}
	char get_gender(void)const{return gender;}
	char get_race(void)const{return race;}
	char get_orientation(void)const{return orientation;}

	//Operators
	Patient &operator=(Patient&);
	bool operator==(Patient);
	bool operator!=(Patient);
	bool operator<(Patient); //For container sorting

	void print(void);

};

#endif // __PATIENTENCODER_PATIENT_H__
