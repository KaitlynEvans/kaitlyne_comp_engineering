//
//  SectionToken.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>

/* Universal const strings as sectiontoken is inherited for all*/
const char OPEN_BRACKET = '(';
const string SET_BEGIN = "(set:";
const string GO_TO_BEGIN = "(go-to:";
const string IF_BEGIN = "(if:";
const string ELSE_IF_BEGIN = "(else-if:";
const string ELSE_BEGIN = "(else:";

SectionToken::SectionToken(const string strng)
{
    
    if (strng == "")
    {
        s = "";
    }
    
    else
    {
        s = strng;
        if (s.at(0) == OPEN_BRACKET) {
            if (s.find(SET_BEGIN) == 0) {
                sectoken = SET;
            }
            if (s.find(GO_TO_BEGIN) == 0) {
                sectoken = GOTO;
            }
            if (s.find(IF_BEGIN) == 0) {
                sectoken = IF;
            }
            if (s.find(ELSE_IF_BEGIN) == 0) {
                sectoken = ELSEIF;
            }
            if (s.find(ELSE_BEGIN) == 0) {
                sectoken = ELSE;
            }
        }
        else {
            if (s.at(0) == '[') {
                if (s.at(1) == '[') {
                    sectoken = LINK;
                }
                else {
                    sectoken = BLOCK;
                }
            }
            else {
                sectoken = TEXT;
            }
        }
    }
}
