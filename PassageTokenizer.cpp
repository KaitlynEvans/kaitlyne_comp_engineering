//
//  PassageTokenizer.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>

PassageTokenizer::PassageTokenizer(string strng)
{
    int opn_link = 0;
    int cl_link = 0;
    int outter_opn_brkt = 0;
    int outter_cl_brkt = 0;
    int inner_opn_brkt = 0;
    int inner_cl_brkt = 0;
    
    if (strng.length() <= 0)
    {
        
    }
    else
    {
        
        strng.insert(1, 1, '|');
        
        for (unsigned int i = 0; i < strng.length(); i++)
        {
            if (strng.at(i) == '(')
            {
                if (outter_opn_brkt == outter_cl_brkt) { // are we outside of a block?
                    if (strng.at(i - 1) != '|') {// is there already a delimiter?
                        strng.insert(i, 1, '|'); // 1: the number of chars inserted
                        i++;
                    }
                }
                continue;
            }
            
            if (strng.at(i) == ')')
            { // now need to find closing ")"
                if (outter_opn_brkt == outter_cl_brkt)
                { // are we outside of a block?
                    strng.insert(i + 1, 1, '|'); // add the delimiter
                }
                continue;
            }
            
            if (strng.at(i) == '[')
            {
                if (outter_opn_brkt == outter_cl_brkt) { // are we outside of a block? NO, Case 1
                    if (strng.at(i - 1) == '|') {
                        outter_opn_brkt++;
                        inner_opn_brkt++;
                        continue;
            }
                    
            if (strng.at(i + 1) == '[')
            { // checking if this is a link?
                strng.insert(i, 1, '|');
                i = i + 2;
                continue;
            }
                }
                
            if (outter_opn_brkt != outter_cl_brkt) { // are we inside of a block? YES, Case 2
                if (strng.at(i - 1) == ')')
                {
                        inner_opn_brkt++;
                    }
                    else if (strng.at(i + 1) == '[') { // link inside of a block?
                        opn_link++;
                        i++;
                    }
                    continue;
                }
            }
            
            
            if (strng.at(i) == ']') { // is the char a closing bracket?
                if (outter_opn_brkt == outter_cl_brkt) { // if this is outside of block,
                    if (strng.at(i + 1) == ']') { // check if it is a link, then do this
                        i++;
                        strng.insert(i + 1, 1, '|');
                        cl_link++;
                        continue;
                    }
                }
                
                if (outter_opn_brkt != outter_cl_brkt) { // is it inside of a block? YES
                    if (opn_link != cl_link) {
                        cl_link++;
                        i++;
                        continue;
                    }
                    if (inner_opn_brkt - inner_cl_brkt == 1) { // it is an external close
                        strng.insert(i + 1, 1, '|');
                        inner_cl_brkt++;
                        outter_cl_brkt++;
                    }
                    else {
                        inner_cl_brkt++;
                    }
                }
            }
        }
        
        if (strng.at(strng.length() - 2) == '|') { // taking care of \n in front
            strng.insert(strng.length() - 1, 1, '|'); // adding delimiter at end of code, text
        }
        
        isstrobj.str(strng);
        string strDelim;
        while (getline(isstrobj, strDelim, '|')) {
            if (strDelim == "\n") {
                continue;
            }
            
            else
                secVec.push_back(strDelim);
        }
    }
}

bool PassageTokenizer::hasNextSection()
{
    if (secVec.size() <= 0)
    {
        return false;
    }
    else
        return true;
}

SectionToken PassageTokenizer::nextSection()
{
    if (hasNextSection())
    {
        SectionToken stoken(secVec.at(0));
        secVec.erase(secVec.begin());
        return stoken;
    }
    else
    {
        SectionToken stoken("");
        return stoken;
    }
}