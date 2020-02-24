//
//  European_Option_Put.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 08/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef European_Option_Put_hpp
#define European_Option_Put_hpp
#include <iostream>
#include <stdio.h>
#include "Option.hpp"
using namespace std;

class European_Option_Put : public Option
{
public:
    // CONSTRUCTOR
    European_Option_Put(double r_,double sigma_,double K_,double T_,double S0_,double b_, int n_) : Option(r_,sigma_,K_,T_,S0_,b_,n_)
    { }
    // METHODE
    double h(double Stock_) // redefines function h of Option class
    {
        return max((get_K()-Stock_), 0.0);
    }
};
#endif /* European_Option_Put_hpp */
