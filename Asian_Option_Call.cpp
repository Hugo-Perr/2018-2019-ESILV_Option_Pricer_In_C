//
//  Asian_Option_Call.cpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 14/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include "Asian_Option_Call.hpp"

// CONSTRUCTOR :
Asian_Option_Call::Asian_Option_Call(double r_,double sigma_,double K_,double T_,double S0_,int num_sims_,int num_intervals_)
{
    r=r_;
    sigma=sigma_;
    K=K_;
    T=T_;
    S0=S0_;
    num_sims = num_sims_;
    num_intervals = num_intervals_;
    std::vector<double> spot_prices_(num_intervals_, S0_);
    spot_prices = spot_prices_;
}

// METHODES :


// -------------------------------------------------------------------------------------------------------//
// --------------------------------  USEFOOL TOOLS FOR PRICER :     --------------------------------------//
// -------------------------------------------------------------------------------------------------------//

double Asian_Option_Call::gaussian_box_muller() { //implement Wiener process : Normal distribution N(0,t-s)
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;
    // generate two uniform random variables
    // until the square of their "euclidean distance" is less than unity
    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        euclid_sq = x*x + y*y;
    } while (euclid_sq >= 1.0);
    
    return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

double Asian_Option_Call::vector_sum (std::vector<double> vecto_element)
{
    int n = get_num_intervals();
    double sum = 0.0;
    for (int i=0; i<=n ; i++)
    {
        sum = sum + vecto_element[i];
    }
    return sum;
}



// -------------------------------------------------------------------------------------------------------//
// --------------------------  Monte Carlo ASIAN OPTION Pricer PW#7    -----------------------------------//
// -------------------------------------------------------------------------------------------------------//

// This provides a vector containing sampled points of a
// Geometric Brownian Motion stock price path
void Asian_Option_Call::calc_path_spot_prices() // Vector of spot prices to be filled in
{
    std::vector<double> spot_prices_ = get_spot_prices();
    // Since the drift and volatility of the asset are constant
    // we will precalculate as much as possible for maximum efficiency
    double r = get_r();
    double v = get_sigma();
    double T = get_T();
    int n_ = get_num_intervals();
    double dt = (T/n_);
    double drift = exp(dt*(r-0.5*v*v));
    double vol = sqrt(v*v*dt);
    
    
    for (int i=1; i<n_; i++)
    {
        double gauss_bm = Asian_Option_Call::gaussian_box_muller();
        spot_prices_[i] = spot_prices_[i-1] * drift * exp(vol*gauss_bm);
    }
    set_spot_prices(spot_prices_);
}

// -------------------------------------------------------------------------------------------------------//



// PAY OFF PRICE
double  Asian_Option_Call::Arithmetic_pay_off_price()
{
    std::vector<double> spot_prices_ = get_spot_prices();
    double sum = vector_sum(spot_prices_);
    double arith_mean = sum / get_num_intervals();
    return arith_mean;
}


// -------------------------------------------------------------------------------------------------------//


// FINAL PRICER :
double Asian_Option_Call::monte_carlo_pricer()
{
    std::vector<double> spot_prices_ = get_spot_prices();
    double payoff_sum = 0.0;
    int n_ = get_num_sims();
    
    
    for (int i=0; i<n_; i++)
    {
        calc_path_spot_prices();
        payoff_sum += Arithmetic_pay_off_price();
    }
    
    
    double discount_payoff_avg = (payoff_sum / num_sims) * exp(-r*T);
    return discount_payoff_avg;
}



// -----------------------------------------------  END  ------------------------------------------------//
