//
//  Travel.hpp
//  SY
//
//  Created by Rachel Phan on 5/27/20.
//  Copyright © 2020 Rachel Phan. All rights reserved.
//

#ifndef Travel_h
#define Travel_h

#include <stdio.h>
#include <string>

using namespace std;

class Travel {
    
private:
    char trans;
    int dest;
public:
    void setTrans(char tr);
    void setDest (int d);
    
    int getDest();
    char getTrans();
    
    
    
};

#endif /* Travel_h */
