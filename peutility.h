//This header and associated source file are for utilities for use by the
//	larger code base that did not fit in an existing class or header

#ifndef __PEUTILITY_H__
#define __PEUTILITY_H__

#include <algorithm>
#include <ctype.h>
#include <sstream>
#include <string>

#include <wx/wx.h>

using namespace std;

//counts the occurrences of a target character within a string
int char_count(string,char);

//Splits a string based on a delimiter
//	atypical algorithm based around pre-allocating memory via char_count()
void pa_split(string,char,string*);

//Simplify making a string lower case
string string_to_lower(string);

//Simplify making a wxString from a std::string or int
wxString make_wx_string(string);
wxString make_wx_string(int);

#endif
