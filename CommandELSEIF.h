#ifndef CommandESLEIF_h
#define CommandESLEIF_h

#include "SectionToken.h"
#include "CommandIF.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream> // all inherited from sectionToken


using namespace std;

 class CommandELSEIF : public CommandIF {
 public:
	 CommandELSEIF(const string stok) : CommandIF(stok) {}
	 ~CommandELSEIF() {}

	// virtual void display() override {}
     
 protected:

 };

#endif /* CommandESLEIF_h */
