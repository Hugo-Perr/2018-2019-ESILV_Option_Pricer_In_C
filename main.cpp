//
//  main.cpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 06/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include <iostream>

#include "European_Option_TD5.hpp"
#include "Option.hpp"
#include "BinLattice.hpp"
#include "European_Option_Call.hpp"
#include "European_Option_Put.hpp"
#include "Digital_Option_Call.hpp"
#include "Digital_Option_Put.hpp"
#include "BinLattice.hpp"
#include "Asian_Option_Call.hpp"
#include "American_Option_Call.hpp"
#include "American_Option_Put.hpp"

using namespace std;






int main(int argc, const char * argv[]) {
    cout << endl << "En debut de projet, mon binome m'a abandonné, pour un autre eleve. A titre informatif, j'ai réalisé ce projet seul." << endl;
    cout << "Bonne lecture" << endl << endl;
    
    cout << endl << endl << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////// TD5 : ///////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    std::cout << "TD5 : modelling a European Option " << endl;
    
    // initialising Black Scholes parameters :
    //double S0=100.,K=100.,T=1.,r=0.06,sigma=0.2,b=0;
    double S0_=35.,K_=36.,T_=1.,r_=0.05,sigma_=0.3,b_=0;
    int n_=2;
    
    
    // creation of the option :
    european_option myoption_ = european_option(call,r_,sigma_,K_,T_,S0_,b_);
    european_option myoption_put_ = european_option(put,r_,sigma_,K_,T_,S0_,b_);
    cout << endl << "PART 1 : Price of a call option" << endl;
    myoption_.Blackschole(0);
    cout << endl << "PART 1 : Price of a put option" << endl;
    myoption_put_.Blackschole(0);
    
    cout << endl << "PART 2 : option pricer according to the CRR method" << endl;
    myoption_.Print_Trees(n_);
    cout << "PAY OFF RESULT : " << myoption_.Pay_Off_t0(n_) << endl;
    
    
    
    
    
    
    
    
    cout << endl << endl << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////// TD6 : ///////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    
    std::cout << endl << endl << "TD6 : " << endl;
    cout << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    double S0=35.,K=36.,T=1.,r=0.05,sigma=0.3,b=0;
    int n=2;
    Option myoption = Option(r, sigma, K, T, S0, b, n);
    // 1. The CRR method provides also a closed-form formula for option pricing, instead of the iterative procedure seen in TD #5.
    cout << "PART 1 : Extend the CRRPricer developped in TD #5 (call)" << endl;
    cout << "PAY OFF RESULT (CRRPricer 1) : " << myoption.CRRPricer() << endl;
    cout << "PAY OFF RESULT (CRRPricer 2) : " << myoption.CRRPricer2() << endl;
    myoption.Print_Trees(); // You can copy/past this line at each line of the code in order to verify the correctness of the trees.
    
    
    
    // 2. Option payoff depends on option type. Define an abstract Option class with the attributes common to all the option types and with a payoff method, so that separate classes (children of the parent Option class) can be defined for each option type. Each option class has to exhibit its own payoff method depending on the option type (design is up to you).
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout <<  "PART 2.A : Option payoff -> European Option Call" << endl;
    European_Option_Call eur_opt_call = European_Option_Call(r, sigma, K, T, S0, b, n);
    cout << "PAY OFF RESULT : " << eur_opt_call.CRRPricer2() << endl;
    
    
    cout << endl << "PART 2.B : Option payoff -> European Option Put" << endl;
    European_Option_Put eur_opt_put = European_Option_Put(r, sigma, K, T, S0, b,n);
    cout << "PAY OFF RESULT : " << eur_opt_put.CRRPricer2() << endl;
    
    
    cout << endl << "PART 2.C : Option payoff -> Digital_Option_Call" << endl;
    Digital_Option_Call dig_opt_call = Digital_Option_Call(r, sigma, K, T, S0, b,n);
    cout << "PAY OFF RESULT : " << dig_opt_call.CRRPricer2() << endl;
    
    
    cout << endl << "PART 2.D : Option payoff -> Digital_Option_Put" << endl;
    Digital_Option_Put dig_opt_put = Digital_Option_Put(r, sigma, K, T, S0, b, n);
    cout << "PAY OFF RESULT : " << dig_opt_put.CRRPricer2() << endl << endl ;
    
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "PART 3 : Implement a class BinLattice" << endl;
    binlattice<double> mybinlattice(n,myoption.get_valueTree());
    mybinlattice.display();
    
    
    
    
    
    
    cout << endl << endl << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////// TD7 : ///////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "PART 1 : Monte Carlo pricer : EUROPEAN OPTIONS" << endl;
    int N = 1000; // Number of simulated asset paths
    cout << "PAY OFF (CALL): " << eur_opt_call.monte_carlo_pricer(N) << endl; // use of past variable eur_opt_call
    cout << "PAY OFF (PUT): " << eur_opt_put.monte_carlo_pricer(N) << endl;
    cout <<  "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl << endl;
    
    
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "PART 2 : Monte Carlo pricer : ARITHMETIC ASIAN CALL OPTIONS" << endl;
    
    // Let's set all the parameters (clearly)
    int num_sims = 100000;   // Number of simulated asset paths
    int num_intervals = 250;  // Number of intervals for the asset path to be sampled
    S0 = 30.0;  // Option price
    K = 29.0;  // Strike price
    r = 0.08;   // Risk-free rate (8%)
    sigma = 0.3;    // Volatility of the underlying (30%)
    T = 1.00;    // One year until expiry
    
    Asian_Option_Call asia_opt_call = Asian_Option_Call(r, sigma, K, T, S0, num_sims, num_intervals);
    cout << "PAY OFF (ASIAN OPTION CALL ARITHM.): " << asia_opt_call.monte_carlo_pricer() << endl << endl;
    
    
    cout << endl << endl << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////// TD8 : ///////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////" << endl;
    
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "PART 1 : Binomial Pricer - American Option" << endl;
    n=2;
    b=0;
    S0 = 30.0;  // Option price
    K = 29.0;  // Strike price
    r = 0.08;   // Risk-free rate (8%)
    sigma = 0.3;    // Volatility of the underlying (30%)
    T = 1.00;    // One year until expiry
    
    cout << "----------------------------------------------------   American CALL OPTION " << endl;
    American_Option_Call amer_opt_call = American_Option_Call(r, sigma, K, T, S0, b, n);
    double payoff = amer_opt_call.CRRPricer(); // Call this function to initialize stock tree & value tree
    amer_opt_call.creat_exercice_policy();
    amer_opt_call.Print_Trees();
    amer_opt_call.print_exercice_policy();
    amer_opt_call.should_option_be_exerciced(1,1);
    amer_opt_call.should_option_be_exerciced(2,0);
    
    cout << "----------------------------------------------------   American PUT OPTION " << endl;
    American_Option_Put amer_opt_put = American_Option_Put(r, sigma, K, T, S0, b, n);
    payoff = amer_opt_put.CRRPricer(); // Call this function to initialize stock tree & value tree
    amer_opt_put.creat_exercice_policy();
    amer_opt_put.Print_Trees();
    amer_opt_put.print_exercice_policy();
    amer_opt_put.creat_exercice_policy();
    amer_opt_put.should_option_be_exerciced(2, 0);
    amer_opt_put.should_option_be_exerciced(1, 1);
    
    
    
    
    cout << endl << "* * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "PART 2 : Pricing an American option with Black-Scholes and Binomial method" << endl;
    amer_opt_call.Blackschole();
    amer_opt_call.Print_Trees();
    vector<vector<double>> value_tree = amer_opt_call.get_valueTree();
    double payoff_opt = value_tree[0][0];
    cout << "PriceOff american option (call) : "  << payoff_opt << endl;
    
    
    
    return 0;
}
