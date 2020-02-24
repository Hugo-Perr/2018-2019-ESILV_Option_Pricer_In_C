//
//  Asian_Option_Call.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 14/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef Asian_Option_Call_hpp
#define Asian_Option_Call_hpp

#include <iostream>

#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <stdio.h>
#include <vector>

class Asian_Option_Call
{
private:
    double r; // Interest rate
    double sigma; // Volatility
    double K; // Strike price
    double T; // Expiry date (or maturity) // Sometimes "N" in the PW sheet !!!!!!  AND != n which is the node considerated
    double S0; // Underlying price
    int num_sims;
    int num_intervals;
    std::vector<double> spot_prices; // The vector of spot prices
public:
    
    // GET & SET :
    std::vector<double> get_spot_prices(){return spot_prices;}
    void set_spot_prices(std::vector<double> spot_prices_){spot_prices = spot_prices_;}
    int get_num_sims(){return num_sims;};
    int get_num_intervals(){return num_intervals;};
    double get_r(){return r;}
    double get_sigma(){return sigma;}
    double get_K(){return K;}
    double get_T(){return T;}
    double get_S0(){return S0;}
    
    //CONSTRUCTOR
    Asian_Option_Call(double r_,double sigma_,double K_,double T_,double S0_,int num_sims_,int num_intervals);
    
    // METHODES :
    double gaussian_box_muller(); // For random Gaussian generation
    void calc_path_spot_prices(); // This provides a vector containing sampled points of a Geometric Brownian Motion stock price path
    double vector_sum (std::vector<double> vecto_element); // Give the sum of all double in Vector
    double Arithmetic_pay_off_price(); // Each step Pay_off in formul
    double monte_carlo_pricer(); // Final Asian Pricer
};


#endif /* Asian_Option_Call_hpp */
