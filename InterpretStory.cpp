//
//  InterpretStory.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

InterpretStory::InterpretStory(const string s)
{
    StoryTokenizer st(s);
    int pass = 0;
    while (st.hasNextPassage())
    {
        PassageToken ptok = st.nextPassage();
        passUMap[ptok.getName()] = pass; // adding the passage # to pair.second
        updPassVec.push_back(ptok);
        pass++;
        passUMap.emplace(updPassVec.at(0).getName(), pass);
        string temp = ptok.getText();
        string linkPass = ptok.getText();
        PassageTokenizer pt(temp);
        
    }
    readPassage(updPassVec[0]);
}

void InterpretStory::readPassage(PassageToken curr_Tok)
{
    string temp = curr_Tok.getText();
    PassageTokenizer ptoktemp(temp);
    string nxtPass;
    vector <links> linkVec;
    bool entblk = true;
    
    while (ptoktemp.hasNextSection())
    {
        SectionToken tempstok = ptoktemp.nextSection();
        switch (tempstok.getType())
        {
            case LINK:
                cout << links(tempstok.getText()).getDisplayText();
                linkVec.push_back(links(tempstok.getText()));
                break;
            case BLOCK:
                if (entblk == true)
                {
                    BlockToken btok(tempstok.getText());
                    readPassage(btok);
                }
                else {}
                
                break;
            case SET:
                varUMap[CommandSET(tempstok.getText()).getVar()] = CommandSET(tempstok.getText()).SetTestVal();
                break;
            case GOTO:
                readPassage(updPassVec[passUMap[CommandGOTO(tempstok.getText()).getName()]]);
                break;
            case IF:
                if (varUMap[CommandIF(tempstok.getText()).getVar()] == CommandIF(tempstok.getText()).SetTestVal())
                { entblk = true; }
                else
                { entblk = false; }
                break;
            case ELSEIF:
                if (entblk == true)
                { entblk = false; }
                else {
                    if (varUMap[CommandELSEIF(tempstok.getText()).getVar()] == CommandELSEIF(tempstok.getText()).SetTestVal())
                    { entblk = true; }
                    else { entblk = false; }
                }
                break;
            case ELSE: // updating entblk if didn't execute so setting it back
                if (entblk == true)
                { entblk = false;}
                else if(entblk == false)
                { entblk = true; }
                break;
            case TEXT:
                cout << tempstok.getText();
                break;
        }
    }

    if (linkVec.empty()) { // BlockToken
        // do nothing
    }
    
    else
    {
        cout << endl << "Please put in the corresponding option" << endl;
        
        for (int i = 0; i < linkVec.size(); ++i)
        {
            cout << i << ". " << linkVec[i].getDisplayText() << endl;
        }
        
        int i;
        cin >> i;
        
        readPassage(updPassVec[passUMap[linkVec[i].getName()]]);
    }
}

void InterpretStory::readPassage(BlockToken curr_Tok)
{
    string temp = curr_Tok.getText();
    PassageTokenizer ptoktemp(temp);
    string nxtPass;
    vector <links> linkVec;
    bool endtBlk = true;
    
    while (ptoktemp.hasNextSection())
    {
        
        SectionToken tempstok = ptoktemp.nextSection();
        switch (tempstok.getType())
        {
            case LINK:
                
                cout << links(tempstok.getText()).getDisplayText();
                linkVec.push_back(links(tempstok.getText()));
                break;
                
            case BLOCK:
                if (endtBlk == true) {
                    // enter block, and execute
                    // create passageToken out of temptok.getText()
                    // pass that to readPassage()
                    BlockToken btok(tempstok.getText());
                    readPassage(btok);
                    
                }
                else {// do nothing}
                break;
            case SET:
                varUMap[CommandSET(tempstok.getText()).getVar()] = CommandSET(tempstok.getText()).SetTestVal();
                break;
            case GOTO:
                readPassage(updPassVec[passUMap[CommandGOTO(tempstok.getText()).getName()]]);
                break;
            case IF:
                if (varUMap[CommandIF(tempstok.getText()).getVar()] == CommandIF(tempstok.getText()).SetTestVal())
                { endtBlk = true; }
                else { endtBlk = false; }
                break;
            case ELSEIF:
                if (endtBlk == true)
                { endtBlk = false; }
                else
                {
                    if (varUMap[CommandELSEIF(tempstok.getText()).getVar()] == CommandELSEIF(tempstok.getText()).SetTestVal())
                    { endtBlk = true; }
                    else
                    { endtBlk = false;}
                }
                break;
            case ELSE: // updating entblk if didn't execute so setting it back
                if (endtBlk == true)
                { endtBlk = false; }
                else if(endtBlk == false)
                { endtBlk = true; }
                break;
            case TEXT:
                cout << tempstok.getText();
                break;
        }
    }
    
    // linkvec is empty, do nothing
    //else for each index of the link vector, print out the index and the link option
    if(linkVec.empty()){ // BlockToken
        // do nothing
        // cout << "herehere, linkVec empty!";
    }
    else {
        
        cout << endl << "Please put in the corresponding option" << endl;
        
        for(int i = 0; i < linkVec.size(); ++i){
            cout << i << ". " << linkVec[i].getDisplayText() << endl;
        }
        
        int i;
        
        cin >> i;
        
        readPassage(updPassVec[passUMap[linkVec[i].getName()]]);
    }
  }
}

template<typename K, typename V>
void print_unord_map(unordered_map<K,V> &passUMap)
{
    for (auto const& pair : passUMap)
    {
        cout << "{" << pair.first << ":" << pair.second << "}" << endl;
    }
}

