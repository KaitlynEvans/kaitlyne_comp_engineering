#ifndef CommandELSE_h
#define CommandELSE_h

#include "CommandELSEIF.h"
#include "SectionToken.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream> 

using namespace std;

 class CommandELSE : public CommandIF { // completed because commandIF is completed -- will be worked on in readPassage()
 public:
	 CommandELSE(const string stok) : CommandIF(stok) {}
	 ~CommandELSE() {}

	  // virtual void display() override {}
     
 protected:

 };

#endif /* CommandELSE_h */
