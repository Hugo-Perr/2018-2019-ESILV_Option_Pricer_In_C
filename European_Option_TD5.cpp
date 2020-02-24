//
//  European_Option_TD5.cpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 27/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include "European_Option_TD5.hpp"

// CONSTRUCTOR ///////////////////////////////////////////////////////////////////////////////////////////
european_option::european_option(option_type opt_t_, double r_, double sigma_, double K_, double T_, double S_, double b_)
{
    r = r_;
    sigma = sigma_;
    K = K_;
    T = T_;
    S0 = S_;
    b = b_;
    option_t = opt_t_;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////// METHOD //////////////////////////////////////////////

// -------------------------------------------------------------------------------------------------------//
// -------------  1. Build up a class modelling a European Option, and its pricing and delta. ------------//
// -------------------------------------------------------------------------------------------------------//
double normalCFD(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

void european_option::Blackschole(int t)
{
    cout  << "BlackSchole : " << endl;
    double d1 = (log(S0/K)+(r+pow(sigma,2)/2)*(T-t)) / (sigma *sqrt(T-t));
    double d2 = d1-sigma*sqrt(T-t);
    double price = 0;
    if (option_t == call)
    {
        price = S0*normalCFD(d1) - K*exp(-r*(T-t))*normalCFD(d2);
        cout << "d1 = " << d1 << endl << "d2 = " << d2 << endl << "Call price : " << price << endl;
    }
    else if (option_t == put)
    {
        price = K*exp(-r*(T-t))*normalCFD(-d2) - S0*normalCFD(-d1);
        cout << "d1 = " << d1 << endl << "d2 = " << d2 << endl << "Put price : " << price << endl;
    }
}






// -------------------------------------------------------------------------------------------------------//
// -----------------  2. Implement an option pricer according to the CRR method --------------------------//
// -------------------------------------------------------------------------------------------------------//

double european_option::Pay_Off_t0(int n)
{
    
    // THE STOCK PRICE TREE ////////////////////////////////////////////////////////////////////////////////////
    // n is tree paramaters (steps in tree)
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
    
    
    
    // THE VALUE TREE  (PAY OFF) ///////////////////////////////////////////////////////////////////////////////
    // create storage for the stock price tree and option price tree
    vector<vector<double>> valueTree(n+1,vector<double>(n+1));
    for (int j=0;j<=n;j++)
    {
        if (option_t == call)
        {
            valueTree[n][j]=max(stockTree[n][j]-K,0.);
            //cout << n << " " << j << " " << valueTree[n][j] << endl;
        }
        
        else if (option_t == put)
        {
            valueTree[n][j]=max(K-stockTree[n][j],0.);
            //cout << n << " " << j << " " << valueTree[n][j] << endl;
        }
    }
    // Now we need to loop backwards through the tree to generate the value at each node using the equation:
    // Vij = e - rdeltat(qVi+1,j+1   +  (1-q)Vi+1,j)
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            valueTree[i][j] = exp(-r*dt)*( q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]);
        }
    }
    
    double responce= valueTree[0][0];
    return responce;
}



///// JUST TO PRINT STOCK PRICE TREE //////
void european_option::Print_Trees(int n)
{
    cout << "STOCK PRICE TREE" << endl;
    double dt,u,d,q; // declare and initialise local variables (u,d,q)
    dt = T/n;
    u = exp(sigma*sqrt(dt)); // the price of stock involve with a factor u ...
    d = exp(-sigma*sqrt(dt)); // ... or decrease with -d
    q = (exp(r*dt)-d)/(u-d); // q=(R-D)/(U-D) : it's the risk-neutral probability
    
    // create storage for the stock price tree and option price tree
    vector<vector<double>> stockTree(n+1,vector<double>(n+1));
    
    // setup and initialise the stock price tree
    cout << "---------------------" << endl;
    for(int i=0;i<=n;i++)
    {
        
        for(int j=0;j<=i;j++) {
            stockTree[i][j]=S0*pow(u,j)*pow(d,i-j); // (i-j) instead of (n-i) cause j depend on i
            if (i>=j)
            {
                cout << " /  " << stockTree[i][j] ;
            }
            else
            {
                cout << "/  *  /" ;
            }
        }
        cout << endl; }
    cout << "---------------------" << endl;
    
    
    // THE VALUE TREE //
    cout << endl << "VALUE TREE" << endl;
    cout << "---------------------" << endl;
    vector<vector<double>> valueTree(n+1,vector<double>(n+1));
    for (int j=0;j<=n;j++)
    {
        if (option_t == call)
        {
            valueTree[n][j]=max(stockTree[n][j]-K,0.);
            //cout << n << " " << j << " " << valueTree[n][j] << endl;
        }
        
        else if (option_t == put)
        {
            valueTree[n][j]=max(K-stockTree[n][j],0.);
            //cout << n << " " << j << " " << valueTree[n][j] << endl;
        }
    }
    // Now we need to loop backwards through the tree to generate the value at each node using the equation:
    // Vij = e - rdeltat(qVi+1,j+1   +  (1-q)Vi+1,j)
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            valueTree[i][j] = exp(-r*dt)*( q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]);
        }
    }
    
    for (int i=0;i<=n;i++)
    {
        for (int j=0;j<=i;j++)
        {
            cout << " /  " << valueTree[i][j] ;
        }
        cout << endl;
    }
    cout << endl << "---------------------" << endl;
}
