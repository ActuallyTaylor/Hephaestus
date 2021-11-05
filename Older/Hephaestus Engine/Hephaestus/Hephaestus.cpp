//
//  Hephaestus.cpp
//  Hephaestus
//
//  Created by Zachary lineman on 10/29/21.
//

#include <iostream>
#include "Hephaestus.hpp"
#include "HephaestusPriv.hpp"

void Hephaestus::HelloWorld(const char * s)
{
    HephaestusPriv *theObj = new HephaestusPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void HephaestusPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

