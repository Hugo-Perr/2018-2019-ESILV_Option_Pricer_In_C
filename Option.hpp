//
//  Option.hpp
//  C_finance_td6
//
//  Created by PERIER Hugo on 05/11/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//
#ifndef Option_hpp
#define Option_hpp
#include <algorithm>    // Needed for the "max" function
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

class Option
{
private :
    double r; // Interest rate
    double sigma; // Volatility
    double K; // Strike price
    double T; // Expiry date (or maturity) // Sometimes "N" in the PW sheet !!!!!!  AND != n which is the node considerated
    double S0; // Underlying price
    double b; // Cost of carry
    int n; // // n is tree paramaters (steps in tree)
    vector<vector<double>> saved_valueTree; // save value tree
    vector<vector<double>> saved_stockTree; // save stock price tree
    
public :
    // CONSTRUCTOR
    Option(double r_,double sigma_,double K_,double T_,double S0_,double b_,int n_);
    
    // GET/SET
    int get_n(){return n;}
    double get_r(){return r;}
    double get_sigma(){return sigma;}
    double get_K(){return K;}
    double get_T(){return T;}
    double get_S0(){return S0;}
    double get_b(){return b;}
    vector<vector<double>> get_stockTree(){return saved_stockTree;}
    vector<vector<double>> get_valueTree(){return saved_valueTree;}
    void set_stockTree(vector<vector<double>> st) {saved_stockTree = st;}
    void set_valueTree(vector<vector<double>> vt) {saved_valueTree = vt;}

    
    // METHODES:
    // A. // factorial function, necessary to closed formula of the Pricer (PW6)
    int factorial(int n);
    
    // B. // parametrable function, give each option its own payoff method depending on the option type
    // NB: by default it works like option is CALL!
    virtual double h(double value_tree){return max(value_tree-K,0.);}

    //C. // function to print Stock price tree & value tree in the consol
    void Print_Trees();
    
    //D. Grouped CRR Pricer of PW#5 & PW#6, also creat and save Stock Price tree & Value Tree.
    double CRRPricer(); // PW#5
    double CRRPricer2(); // PW#6
    
    //E. Monte Carlo Pricer
    double gaussian_box_muller(); //implement Wiener process : Normal distribution N(0,t-s)
    double monte_carlo_pricer(const int& num_sims);
    
    
};






#endif /* Option_hpp */
