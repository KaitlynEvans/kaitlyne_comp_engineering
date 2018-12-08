#ifndef CommandGOTO_h
#define CommandGOTO_h

#include "SectionToken.h"
#include "CommandIF.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

const string NAME = "start";
const string SPEC_STR_GOTO = "&quot;";

// (go-to: &quot;start&quot;)

 class CommandGOTO : public SectionToken {
 public:
	 CommandGOTO(const string strng) : SectionToken(strng) {
		 unsigned int start = strng.find(SPEC_STR_GOTO);
		 unsigned int end = strng.find_last_of(SPEC_STR_GOTO);
		 name = strng.substr(start +5, end - start +5);


	 }

	 string getName() {
		 return name;
	 }
     ~CommandGOTO() {}
     
 protected:

	 string name;

 };


#endif /* CommandGOTO_h */
