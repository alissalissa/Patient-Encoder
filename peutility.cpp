//Definitions of the utilities declared in peutility.h

#include "peutility.h"

using namespace std;

int char_count(string haystack,char target){

	int cnt=0; //stands for count, not cunt ;)
	for(size_t i=0;i<haystack.length();i++)
		if(haystack[i]==target)
			cnt++;

	return cnt;

}

void pa_split(string haystack,char target,string *ret){

	int occurences=char_count(haystack,target);

	for(int i=0;i<occurences;i++){
		ret[i]=haystack.substr(0,haystack.find(target));
		haystack=haystack.substr(haystack.find(target)+1,string::npos);
	}
	ret[occurences]=haystack;

}
