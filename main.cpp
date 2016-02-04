//
//  main.cpp
//  Compress
//
//  Created by Saeid on 12/24/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "Charinfo.h"
#include "chartree.h"

long long int totalchar = 0;

int main(int argc, const char * argv[]) {
    map<char, CharInfo> charmap;
    
    ifstream in0("/Users/Apple/Documents/programming/programs/C:C++/college programming/Compress/Compress/01.txt");
    
    if (in0) { // Verify that the file was open successfully
        string tmp = "";
        for (; getline(in0, tmp);) {
            for (int i = 0; tmp[i] && tmp[i] != EOF && i < tmp.size(); i++) {
                charmap[tmp[i]].num++;
                totalchar++;
            }
        }
        
        in0.close();
        
        int j = 0;
        node** array = new node*[charmap.size()];
        
        for (auto it = charmap.begin(); it != charmap.end() ; it++){
            it->second.perc = (int) ((it->second.num * 100/ totalchar));
            
            node *temp = new node;
            temp->val = it->first;
            temp->per = it->second.perc;
            temp->l = nullptr;
            temp->r = nullptr;
            temp->p = nullptr;
            
            array[j] = temp;
            
            j++;
        }
        
        chartree tree(array, charmap.size(), charmap);
        
        
        /////////////////////////////////////////////////////////Minitured File
        string zerone = "";
        ifstream in("/Users/Apple/Documents/programming/programs/C:C++/college programming/Compress/Compress/01.txt");
        
        
        
        ///put all 0 and 1 in one string
        if (in) { // Verify that the file was open successfully
            for (; getline(in, tmp);) {
                for (int i = 0; tmp[i] && tmp[i] != EOF && i < tmp.size(); i++) {
                    zerone.append(charmap[tmp[i]].code);
                }
            }
            in.close();
        }
        
        
        ofstream out("/Users/Apple/Documents/programming/programs/C:C++/college programming/Compress/Compress/01.min.txt");
        if (out) {
            int k = 0;
            for (; k <= zerone.size() - 9; k += 8) out << (char) stoi(zerone.substr(k, 8),nullptr,2);
            out << (char) stoi(zerone.substr(k),nullptr,2);
            
            out.close();
        }
        
        ////////////////////////////////////////////////////////Table
        ofstream out0("/Users/Apple/Documents/programming/programs/C:C++/college programming/Compress/Compress/01.min.table");
        if (out0) {
            out0 << "CHAR -  # - % - code" << endl;
            for (auto it = charmap.begin(); it != charmap.end() ; it++){
                out0 << it->first << ": " << it->second.num << " - " << it->second.perc << " - " << it->second.code << endl;
            }
            
            out0.close();
        }
        
        
        delete array;
    }
    else {
        cout << "error opening file!" << endl;
        cerr << "Error code: " << strerror(errno) << endl;
        return 1;
    }
    
    return 0;
}
