//
//  European_Option_Call.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 06/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef European_Option_Call_hpp
#define European_Option_Call_hpp

#include <stdio.h>
#include "Option.hpp"

class European_Option_Call : public Option
{
public:
    // CONSTRUCTOR
    European_Option_Call(double r_,double sigma_,double K_,double T_,double S0_,double b_, int n_) : Option(r_,sigma_,K_,T_,S0_,b_,n_)
    {}
    
    // METHODE
    double h(double Stock_) // redefines function h of Option class
    {
        return max((Stock_-get_K()), 0.0);
    }
    
};


#endif /* European_Option_Call_hpp */
