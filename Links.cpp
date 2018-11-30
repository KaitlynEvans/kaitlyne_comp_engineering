//
//  Links.cpp
//  IF-Interpreter Final Version
//
//  Created by Kaitlyn Evans and Ben Morrison
//  Copyright © 2018 Benjamin Morrison. All rights reserved.
//

#include "Header.h"
#include <stdio.h>

void links::setDisplayAndNames() {
    
    if (s.length() <= 0) {
        
        
    }
    else{
        
        if (s.find(SPECIAL_STR_LINK) != string::npos) { // if find true, then compare to map
            // [[Take the blue pill-&gt;Bad dream?]] -- use this as reference
            unsigned int blk = s.find("[[") + 2; // finds first inst of [ then add two to get what is inside
            unsigned int spc_tag = s.find(SPECIAL_STR_LINK);
            display = s.substr(blk, spc_tag - blk + 2);
            
            
            unsigned int END_BLK = s.find("]]");
            name = s.substr(spc_tag + 4, END_BLK - spc_tag + 4);
            
        }
        else {
            // then it is a normal link....
            unsigned int normblk = s.find("[[") + 2; // finds first inst of [ then add two to get what is inside
            unsigned int normend = s.find("]]");
            name = s.substr(normblk, normend - 2 + normblk - 2);
            display = name; // in this instance, they are the same
            
        }
    }
    
}
