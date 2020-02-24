//
//  Digital_Option_Put.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 08/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef Digital_Option_Put_hpp
#define Digital_Option_Put_hpp

#include <iostream>
#include <stdio.h>
#include "Option.hpp"
using namespace std;

class Digital_Option_Put: public Option
{
public:
    // CONSTRUCTOR
    Digital_Option_Put(double r_,double sigma_,double K_,double T_,double S0_,double b_, int n_) : Option(r_,sigma_,K_,T_,S0_,b_,n_)
    { }
    // METHODE
    double h(double Stock_) // redefines function h of Option class
    {
        double result = 0;
        if (get_K()>Stock_)
        {
            result = 1;
        }
        return result;
    }
};
#endif /* Digital_Option_Put_hpp */
