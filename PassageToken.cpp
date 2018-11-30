//
//  PassageToken.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>

PassageToken::PassageToken(const string strng)
{
    // cout << strng;
    
    if (strng.empty())
    {
        s = strng;
    }
    else
    {
        // cout << endl << endl;
        
        // looking for name,
        unsigned int begin = (strng.find("name") +6); // find "name", manipualte
        unsigned int end = (strng.find("tags") -2); // find "tag", manipulate
        name = strng.substr(begin, end-begin); // tested, this -- looks like it works!
        
        // cout << "  Name:  " << name << endl;
        
        unsigned int firstInst = strng.find_first_of('>') + 1;
        unsigned int updatedfirstInst = strng.find_last_of('<');
        string passText;
        passText = "\n" + strng.substr(firstInst, updatedfirstInst-firstInst) + "\n";
        // cout << passText << endl; // gets rid of tags!!
        s = passText;
    }
}
