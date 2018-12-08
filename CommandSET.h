#ifndef CommandSET_h
#define CommandSET_h
#include "SectionToken.h"
#include "CommandIF.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

const string SPEC_STR_SET = "to";

 class CommandSET : public CommandIF {
 public:
	 CommandSET(const string strng): CommandIF (strng) {
		 setVarAndsetTest();
	}
	 ~CommandSET() {}

	 bool SetTestVal() {
		 return testVal;
	 }

	 string getVar() {
		 return variable;
	 }

	 void setVarAndsetTest() {
		 if (s.find("true") != string::npos) { // if find true, then compare to map
			 testVal = true;
		 }
		 else {
			 testVal = false;
		 }

		 unsigned int pos = s.find(SPECIAL_VARCHAR); // starting position of instant of $ (variable)
		 string g = s.substr(pos + 1, s.find(")") - pos + 1);
		 unsigned int space = g.find(" "); // find position for " "; now create a substring
		 variable = g.substr(0, space);
	 }

	 // virtual void display() override {}
	 // get() const override {};
     
 protected:
	string variable;
	 // string special_lK; do you remember what this is?
	 bool testVal;
 };

#endif /* CommandSET_h */
