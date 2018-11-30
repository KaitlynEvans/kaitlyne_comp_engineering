//
//  Header.h
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;

enum tok_t { LINK, GOTO, IF, ELSEIF, ELSE, SET, BLOCK, TEXT };
const string NAME = "start";
const string SPEC_STR_GOTO = "&quot;";
const string SPECIAL_STR_LINK = "-&gt";
const string KEY_WORD_IS = "is";
const char SPECIAL_VARCHAR = '$';
const string SPEC_STR_SET = "to";

class PassageToken
{
public:
    PassageToken() : s(), name() {}
    PassageToken(const string strng);
    ~PassageToken() {}
    string getText() const {return s;}
    string getName() const {return name;}
    
protected:
    string s;
    string name;
};

class StoryTokenizer
{
public:
    StoryTokenizer(string strng);
    ~StoryTokenizer() {};
    string passReturn (int a, int b, string wholestring);
    bool hasNextPassage();
    PassageToken nextPassage();
protected:
    string s;
    istringstream isstrobj;
    vector<string> passVec;
};

class SectionToken
{
public:
    SectionToken(const string strng);
    ~SectionToken() {};
    string getText() const {return s;};
    tok_t getType() const {return sectoken;};
protected:
    string s;
    tok_t sectoken;
};

class PassageTokenizer
{
public:
    PassageTokenizer(string strng);
    ~PassageTokenizer() {};
    bool hasNextSection();
    SectionToken nextSection();
protected:
    istringstream isstrobj;
    char delimiter = '|';
    vector <SectionToken> secVec;
};

class BlockToken
{
public:
    BlockToken(string strng);
    ~BlockToken() {};
    string getText() const {return s;}
    string getName() const {return name;}
protected:
    string s;
    string name;
};

class InterpretStory
{
public:
    InterpretStory() {}
    InterpretStory(const string s);
    ~InterpretStory() {}
    void readPassage(PassageToken curr_Tok);
    void readPassage(BlockToken curr_Tok);
protected:
    vector<PassageToken> updPassVec; // now full, completed
    unordered_map <string, int> passUMap; // now full, completed
    unordered_map <string, bool> varUMap;
    static bool testIFVal; // for ELSE
};

class BlockTokenizer
{
public:
    BlockTokenizer(string strng);
    ~BlockTokenizer() {};
    bool hasNextSection();
    SectionToken nextSection();
protected:
    istringstream iss;
    char delimiter = '*';
    vector<SectionToken> blockSecVec;
};

class CommandIF : public SectionToken
{
public:
    CommandIF(const string stok) : SectionToken(stok) {setVarAndsetTest();}
    ~CommandIF() {};
    bool SetTestVal() {return testVal;};
    string getVar() {return variable;};
    void setVarAndsetTest();
protected:
    string variable;
    bool testVal;
    
};

class CommandELSE : public CommandIF
{
public:
    CommandELSE(const string stok) : CommandIF(stok) {};
    ~CommandELSE() {};
protected:
    
};

class CommandELSEIF : public CommandIF
{
public:
    CommandELSEIF(const string stok) : CommandIF(stok) {}
    ~CommandELSEIF() {}
protected:
};

class CommandGOTO : public SectionToken {
public:
    CommandGOTO(const string strng) : SectionToken(strng)
    {
        unsigned int start = strng.find(SPEC_STR_GOTO);
        unsigned int end = strng.find_last_of(SPEC_STR_GOTO);
        name = strng.substr(start +5, end - start +5);
    }
    string getName() {return name;}
    ~CommandGOTO() {}
protected:
    string name;
};

class CommandSET : public CommandIF
{
public:
    CommandSET(const string strng): CommandIF (strng) {setVarAndsetTest();}
    ~CommandSET() {}
    bool SetTestVal() {return testVal;}
    string getVar() {return variable;}
    void setVarAndsetTest();
protected:
    string variable;
    bool testVal;
};

class links : public SectionToken
{
public:
    links(const string str) : SectionToken(str) {setDisplayAndNames();};
    void setDisplayAndNames();
    string getName() { return name; };
    string getDisplayText() { return display; };
protected:
    string name;
    string display = "";
    
protected:
    
};

#endif /* Header_h */
