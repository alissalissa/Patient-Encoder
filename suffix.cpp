//Implementation for a code generator

//local includes
#include "suffix.h"

using namespace std;

//Constructors
//Goes through a list of patients to generate the code tree
SuffixGenerator::SuffixGenerator(vector<Patient*> pl){
	//Cycle through each patient
	for_each(pl.begin(),pl.end(),[&](Patient* p){
		string code=p->Code();
		string year=code.substr(0,2);
		string age=code.substr(2,2);
		string current=codes[year][age];
		if(current==""){
			codes[year][age]="a";
		}else{
			codes[year][age]=iterate(current);
		}
	});
}

/*********************END CONSTRUCTORS**********************/

//Iterator
string SuffixGenerator::iterate(string code){
	//This may have been passed an empty string.  If so, return 'a'
	if(code=="") return "a";

	string ret="";

	//turn the code into lower case
	for(int i=0;i<(int)code.length();i++){
		code[i]=tolower(code[i]);
	}

	//We do two different things if this is a one character code versus a two character code
	if(code.length()==1){
		//Is it a z?
		if(code=="z"){
			ret="aa";
		}else{
			++code[0];
			ret=code;
		}
	}else{ //must be a length of two
		//Are we at the end of this list of letters?
		if(code[1]=='z'){
			++code[0];
			code[1]='a';
			ret=code;
		}else{
			++code[1];
			ret=code;
		}
	}

	return ret;

}
/********************END ITERATOR*************************/

//Tracking
void SuffixGenerator::update(Patient *p){
	string c=p->Code();
	string year=c.substr(0,2);
	string age=c.substr(2,2);
	//Some debug code
	//cout<<c<<"\t\t"<<year<<"\t\t"<<age<<endl;
	//cout<<codes.size()<<endl;
	//cout<<codes[year][age]<<endl;
	codes[year][age]=iterate(codes[year][age]);
}

string SuffixGenerator::nextCode(string y,string a){
	return iterate(codes[y][a]);
}

void SuffixGenerator::regenerate(vector<Patient*> pl){
	codes.clear();
	for(size_t patient_index=0;patient_index<pl.size();patient_index++) this->update(pl[patient_index]);
}

/******************END TRACKING***********************/

/*bool SuffixGenerator::is_initialized(void){
    if(&codes == NULL) return false;
    return true;
}*/

//A debug method
/*void SuffixGenerator::test(void){
	cout<<((codes["18"]["18"]=="")?"Empty":"Something else")<<endl;
}*/
