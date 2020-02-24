//
//  Option.cpp
//  C_finance_td6
//
//  Created by PERIER Hugo on 05/11/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include "Option.hpp"

// CONSTRUCTOR
Option::Option(double r_,double sigma_,double K_,double T_,double S0_,double b_,int n_)
{
    r=r_;
    sigma=sigma_;
    K=K_;
    T=T_;
    S0=S0_;
    b=b_;
    n=n_;
    
    // just to use QUESTION 3 of PW6 :
    vector<vector<double>> vt_(n_+1,vector<double>(n_+1));
    vector<vector<double>> st_(n_+1,vector<double>(n_+1));
    saved_valueTree = vt_; // to us QUESTION 3 of PW6 !
    saved_stockTree = st_;
}



// METHODES
// -------------------------------------------------------------------------------------------------------//
// -------------------------------------     0. Useful function      -------------------------------------//
// -------------------------------------------------------------------------------------------------------//

int Option::factorial(int n) // factorial function, necessary to closed formula of the Pricer (PW6)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

void Option::Print_Trees()
{
    //double payoff = CRRPricer(); // Call this function to initialize stock tree & value tree
    // ----------------------------------------------------------------> PRINT STOCK PRICE TREE
    vector<vector<double>> stockTree = get_stockTree();
    cout << "STOCK PRICE TREE" << endl << "---------------------" << endl;
    for(int i=0;i<=n;i++)
    {
        cout << "i=" << i;
        for(int j=0;j<=i;j++)
        {
            cout << " /  " << stockTree[i][j] ;
        }
        cout << endl;
    }
    cout << "---------------------" << endl;
    
    
    // ----------------------------------------------------------------> PRINT VALUE TREE
    vector<vector<double>> valueTree = get_valueTree();
    cout << endl << "VALUE TREE" << endl << "---------------------" << endl;
    for (int i=0;i<=n;i++)
    {
        cout << "i=" << i;
        for (int j=0;j<=i;j++)
        {
            cout << " /  " << valueTree[i][j] ;
        }
        cout << endl;
    }
    cout << endl << "---------------------" << endl;
}






// -------------------------------------------------------------------------------------------------------//
// ----------------------------- 0.   PW#5 CRRPricer (iterative procedure)    ------------------------------//
// -------------------------------------------------------------------------------------------------------//
//                                             -> BINOMIAL
double Option::CRRPricer(){
    // -------------------------------------------------------------------------------------------------> THE STOCK PRICE TREE
    double dt,u,d,q; // declare and initialise local variables (u,d,q)
    dt = T/n;
    u = exp(sigma*sqrt(dt)); // the price of stock involve with a factor u ...
    d = exp(-sigma*sqrt(dt)); // ... or decrease with -d
    q = (exp(r*dt)-d)/(u-d); // q=(R-D)/(U-D) : it's the risk-neutral probability
    
    // create storage for the stock price tree and option price tree
    vector<vector<double>> stockTree(n+1,vector<double>(n+1)); // "S" in the PW sheet
    
    // setup and initialise the stock price tree
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=i;j++) {
            stockTree[i][j]=S0*pow(u,j)*pow(d,i-j); // (i-j) instead of (n-i) cause j depend on i
        }
    }
    set_stockTree(stockTree);
    
    
    
    
    // -------------------------------------------------------------------------------------------------> THE VALUE TREE
    // Step 1 // PW#5
    vector<vector<double>> valueTree(n+1,vector<double>(n+1));
    for (int j=0;j<=n;j++) // initialize the last step (i=n) according to the nature of the option
    {   valueTree[n][j] = h (stockTree[n][j]);   }// compute with the parametrable function "h"
    
    // Step 2 // PW#5
    // Now we need to loop backwards through the tree to generate the value at each node using the equation: Vij = e - rdeltat(qVi+1,j+1   +  (1-q)Vi+1,j)
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {   valueTree[i][j] = exp(-r*dt)*( q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]);   }
    }
    set_valueTree(valueTree);
    double responce= valueTree[0][0];
    return responce;
}







// -------------------------------------------------------------------------------------------------------//
// ----------------------  1. Extend the CRRPricer developped in PW#5 in PW#6   --------------------------//
// -------------------------------------------------------------------------------------------------------//

double Option::CRRPricer2()
{
    // -------------------------------------------------------------------------------------------------> THE STOCK PRICE TREE
    double dt,u,d,q; // declare and initialise local variables (u,d,q)
    dt = T/n;
    u = exp(sigma*sqrt(dt)); // the price of stock involve with a factor u ...
    d = exp(-sigma*sqrt(dt)); // ... or decrease with -d
    q = (exp(r*dt)-d)/(u-d); // q=(R-D)/(U-D) : it's the risk-neutral probability
    
    // create storage for the stock price tree and option price tree
    vector<vector<double>> stockTree(n+1,vector<double>(n+1)); // "S" in the PW sheet
    
    // setup and initialise the stock price tree
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=i;j++) {
            stockTree[i][j]=S0*pow(u,j)*pow(d,i-j); // (i-j) instead of (n-i) cause j depend on i
        }
    }
    set_stockTree(stockTree);
    
    
    
    // ------------------------------------------------------------------------------------> CLOSED-FORMULA FOR OPTION PRICING
    double pay_off_t0 = 0.;
    double sum = 0.;
    for (int i=0; i<=n ;i++)
    {
        sum += factorial(n)/(factorial(i)*factorial(n-i)) * pow(q, i) * pow(1-q, n-i) * h (stockTree[n][i]);
    }
    pay_off_t0 = exp(-r*T) * sum;
    return pay_off_t0;
}


// -------------------------------------------------------------------------------------------------------//
// ----------------------------------  2. Monte Carlo Pricer PW#7    -------------------------------------//
// -------------------------------------------------------------------------------------------------------//

double Option::gaussian_box_muller() { //implement Wiener process : Normal distribution N(0,t-s)
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


// European vanilla coption pricer (with a Monte Carlo method)
// Can be use for CALL & PUT options !!!
// Because function h is a parametrable function, give each option its own payoff method depending on the option type
double Option::monte_carlo_pricer(const int& num_sims)
{
    double S = get_S0();
    double r = get_r();
    double v = get_sigma();
    double T = get_T();
    
    double S_adjust = S * exp(T*(r-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;
    
    for (int i=0; i<num_sims; i++)
    {
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
        payoff_sum += h (S_cur);
    }
    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}
