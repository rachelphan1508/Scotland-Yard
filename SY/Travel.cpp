//
//  Travel.cpp
//  SY
//
//  Created by Rachel Phan on 5/27/20.
//  Copyright © 2020 Rachel Phan. All rights reserved.
//

#include "Travel.h"


void Travel:: setDest(int d) {
    dest = d;
}

void Travel:: setTrans(char tr) {
    trans = tr;
}

int Travel:: getDest() {
    return dest;
}

char Travel:: getTrans() {
    return trans;
}
