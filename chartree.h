//
//  chartree.h
//  Compress
//
//  Created by Saeid on 12/24/15.
//  Copyright © 2015 Saeid. All rights reserved.
//

#ifndef chartree_h
#define chartree_h



struct node {
    char val;
    int per;
    node *l;
    node *r;
    node *p;
};



class chartree {
    
    int numchar;
    node **chars;
    node *root;
    node *lown[2];
    string str;
    
    node* creatree(void);
    void gencode (map<char, CharInfo>&, node *);
    void D(node *);
    
public:
    chartree(node **tmp, int n, map<char, CharInfo>& m) {
        numchar = n;
        chars = tmp;
        lown[0] = nullptr;
        lown[1] = nullptr;
        root = creatree();
        str = "";
        
        gencode (m, root);
    }
    
    ~chartree() {
        D(root);
    }
    
    
};

node* chartree::creatree (void) {
    for (int i = 0; i < numchar; i++) {
        node *tmp = chars[i];
        while (tmp->p) tmp = tmp->p;
        
        if (lown[0] == nullptr || lown[1] == nullptr) {
            if (lown[0] == nullptr) lown[0] = tmp;
            else {
                if (tmp->per < lown[0]->per) {
                    lown[1] = lown[0];
                    lown[0] = tmp;
                }
                else if (tmp != lown[0]) lown[1] = tmp;
            }
        }
        else {
            if (tmp->per < lown[0]->per) {
                lown[1] = lown[0];
                lown[0] = tmp;
            }
            else if (tmp->per < lown[1]->per && tmp != lown[0]) lown[1] = tmp;
        }
    }
    
    if (!lown[1]) return lown[0];
    
    node *temp = new node;
    temp->val = NULL;
    temp->per = lown[0]->per + lown[1]->per;
    temp->l = lown[0];
    temp->r = lown[1];
    temp->p = nullptr;
    
    lown[0]->p = lown[1]->p = temp;
    
    lown[0] = nullptr;
    lown[1] = nullptr;
    return creatree();
}

void chartree::gencode (map<char, CharInfo>& m, node *ptr) {
    if (ptr->l == nullptr && ptr->r == nullptr) {
        m[ptr->val].code = str.substr(0);
        str = str.substr(0, str.size() - 1);
        return;
    }
    
    str.append("0");
    gencode (m, ptr->l);
    
    str.append("1");
    gencode (m, ptr->r);
    
    str = str.substr(0, str.size() - 1);
}

void chartree::D(node *ptr) {
    if (ptr->l == nullptr && ptr->r == nullptr) return;
    
    D(ptr->l);
    D(ptr->r);
    
    delete ptr;
}

#endif /* chartree_h */
