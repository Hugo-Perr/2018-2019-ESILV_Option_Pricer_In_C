//
//  European_Option_TD5.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 27/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef European_Option_TD5_hpp
#define European_Option_TD5_hpp

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

enum option_type {call, put};

class european_option
{
    private :
    double r; // Interest rate
    double sigma; // Volatility
    double K; // Strike price
    double T; // Expiry date (or maturity)
    double S0; // Underlying price
    double b; // Cost of carry
    option_type option_t; // option type CALL or PUT
public:
    // CONSTRUCTEUR :
    european_option(option_type opt_t, double r_, double sigma_, double K_, double T_, double S_, double b);
    
    // GET & SET de la Classe :
    double get_r(){ return r;}
    double get_sigma(){ return sigma;}
    double get_K(){ return K;}
    double get_T(){ return T;}
    double get_S(){ return S0;}
    double get_b(){ return b;}
    double get_option_type(){ return option_t;}
    
    // METHODES :
    void Blackschole(int t); // Return the theorical value of the Option at t
    void Print_Trees(int n);
    double Pay_Off_t0(int n); // CRR Method to return price of PayOff at t=0
    
};

#endif /* European_Option_TD5_hpp */
