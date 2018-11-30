#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include "Header.h"
using namespace std;

int main()
{
    int lineCounter = 0, passCounter = 0, storyBegin = 0;
    int storyEnd = 0, HTMLend = 0, passBegin = 0, passEnd = 0;
    string line, passage, story;
    bool begFound = false, endFound = false;
    bool passBegFound = false;
    const string PASS_TAG_BEGIN = "<tw-passagedata";
    const string PASS_TAG_END = "</tw-passagedata>";
    const string STORY_TAG_BEGIN = "<tw-storydata";
    const string STORY_TAG_END = "</tw-storydata";
    const string HTML_END_TAG = "</html>";
    
    // Opens .html from directory sharing executable, locates line # with STORY_TAG_BEGIN
    // STORY_TAG_END  and HTML_END_TAG. prints the lines for our visual...
    ifstream myfile("if.html");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            story += line + '\n';
            lineCounter++;
            
            if ((line.substr(0, 13) == STORY_TAG_BEGIN) && (begFound == false))
            {
                storyBegin = lineCounter;
                begFound = true;
            }
            
            if ((line.substr(0, 14) == STORY_TAG_END) && (endFound == false))
            {
                storyEnd = lineCounter;
                endFound = true;
                passEnd = (lineCounter - 1);
            }
            
            if (line.substr(0, 7) == HTML_END_TAG)
            {
                HTMLend = lineCounter;
            }
            
            if ((line.substr(0, 15) == PASS_TAG_BEGIN) && (passBegFound == false))
            {
                passBegin = lineCounter;
                passBegFound = true;
            }
        }
        
        myfile.close();
    }
    
    else{
        cout << "Unable to open file" << endl;}
    
    cout << "Story begins at line: " << storyBegin << endl;
    cout << "Story ends at line: " << storyEnd << endl;
    cout << "HTML end line: " << HTMLend << endl;
    cout << "Passages start at: " << passBegin << endl;
    cout << "Passages end at: " << passEnd << endl << endl;
    
    istringstream iss(story);
    
    for (string temp; getline(iss, temp); )
    {
        passCounter++;
        if (passCounter >= passBegin && passCounter <= passEnd)
        {
            passage += temp + '\n';
        }
    }
    
    //sends passage to interpreter
    InterpretStory it(passage);
    
    //cout << passage;
    
    //system("pause");
    
    return 0;
}
