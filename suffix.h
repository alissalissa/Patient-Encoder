//Object to generate suffix codes

#ifndef __PATIENT_ENCODER_SUFFIX_GEN_H__
#define __PATIENT_ENCODER_SUFFIX_GEN_H__

//System/STL includes
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

//local includes
#include "patient.h"

using namespace std;

class SuffixGenerator {
private:

	//key is a year, value is another map
	//	2nd map key is an age, value is a suffix code
	map<string,map<string,string> > codes;

	//iterates a letter code
	string iterate(string);

public:
	//Constructors
	SuffixGenerator(void)=default;
	SuffixGenerator(vector<Patient*>);

	//updates teh dictionary based on a single patient entry
	void update(Patient*);
	//Next code -> takes a year and an age and returns the next suffix code
	string nextCode(string,string);
	//Recreates the entire dictionary based on a passed vector of patient objects
	void regenerate(vector<Patient*>);

	//A debug method
	//void test(void);

};

#endif // __PATIENT_ENCODER_SUFFIX_GEN_H__
