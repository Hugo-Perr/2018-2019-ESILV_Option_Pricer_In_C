//
//  American_Option_Call.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 27/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef American_Option_Call_hpp
#define American_Option_Call_hpp

#include <stdio.h>
#include "Option.hpp"
#include <vector>
using namespace std;


class American_Option_Call : public Option
{
private:
    vector<vector<bool>> exercice_policy; // save a tree were each node = if the option should be exercice (value of the node =1) or not(value of the node =0)
public:
    // CONSTRUCTOR
    American_Option_Call(double r_,double sigma_,double K_,double T_,double S0_,double b_, int n_) : Option(r_,sigma_,K_,T_,S0_,b_,n_)
    {
        vector<vector<double>> exercice_policy;
    }
    
    // Additional GET/SET
    vector<vector<bool>> get_exercice_policy(){return exercice_policy;}
    void set_exercice_policy(vector<vector<bool>> ep) {exercice_policy = ep;}
    
    
    // METHODE
    double h(double Stock_) // redefines function h of Option class
    { return max((Stock_-get_K()), 0.0); }
    
    void creat_exercice_policy();
    void print_exercice_policy();
    double american_payoff(int step_i, int node_n);
    void should_option_be_exerciced(int step_i, int node_n);
    
    
    void Blackschole(); // Black-Scholes with  Binomial method
    double get_payoff();
    
    
};
#endif /* American_Option_Call_hpp */
