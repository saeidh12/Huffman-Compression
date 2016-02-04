//
//  Charinfo.h
//  Compress
//
//  Created by Saeid on 12/24/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#ifndef Charinfo_h
#define Charinfo_h

struct CharInfo {
    long long int num;
    int perc;
    string code;
    int codeval;
    
    CharInfo() {
        num = 0;
        perc = 0;
        code = "";
    }
};

#endif /* Charinfo_h */
