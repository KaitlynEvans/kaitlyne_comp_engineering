//
//  StoryTokenizer.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>

StoryTokenizer::StoryTokenizer(string strng)
{
    int begins = 0, ends = 0, lineCounter2 = 0;
    string newStrng, passage, empty;
    
    isstrobj.str(strng); // equiv getline(sstrobj, s)
    while (getline(isstrobj, s) )
    {
        size_t index = s.find("<tw-passagedata");
        size_t index2 = s.find("</tw-passagedata>");
        
        lineCounter2++;
        
        if (index != string::npos) //if beginning tag found
        {
            begins = lineCounter2;
        }
        
        if(index2 != string::npos)
        {
            ends = lineCounter2;
        }
        
        else //if beginning tag not found, do nothing
        {}
        
        if (ends != 0)          //with each iteration, while loop finds beginning line number and ending line number of a passage.
        {                       // when both are found, the line numbers are passes into passReturn function and the function returns
            string newStrng;    //The passage and then push_back is used.
            newStrng = passReturn (begins, ends, strng);
            passVec.push_back(newStrng);
            begins = 0;
            ends = 0;
        }
    } // while end bracket!
} // storytokenizer end bracket!

string StoryTokenizer::passReturn (int a, int b, string wholestring) // new function
{
    istringstream iss(wholestring);
    string line, passpart;
    int counter = 0;
    
    for (string line; getline(iss, line); )
    {
        counter++;
        if(counter >= a && counter <= b)
        {
            passpart += line + '\n';
        }
    }
    
    return passpart;
}

bool StoryTokenizer::hasNextPassage()
{
    if (passVec.size() <= 0)
    {
        return false;
    }
    else
        return true;
}

PassageToken StoryTokenizer::nextPassage()
{
    if (hasNextPassage())
    {
        PassageToken ptoken(passVec.at(0));
        passVec.erase(passVec.begin());
        return ptoken;
    }
    else
    {
        PassageToken ptoken("");
        return ptoken;
    }
}
