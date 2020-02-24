//
//  American_Option_Call.cpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 27/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include "American_Option_Call.hpp"


// *********************************************************************************** //
// ------------------  creation of the Tree of the decision tree --------------------- //
// *********************************************************************************** //

void American_Option_Call::creat_exercice_policy()
{
    int n_ = Option::get_n();
    vector<vector<double>> value_tree = Option::get_valueTree();
    vector<vector<bool>> new_exercice_policy(n_+1,vector<bool>(n_+1));
    double temp_valuetree = 0;
    
    for (int i=0;i<=n_;i++)
    {
        for (int j=0;j<=i;j++)
        {
            temp_valuetree = value_tree[i][j];
            if (temp_valuetree>0)
            {
                new_exercice_policy[i][j]=true;
            }
            else
            {
                new_exercice_policy[i][j]=false;
            }
        }
    }
    set_exercice_policy(new_exercice_policy);
}



// *********************************************************************************** //
// --------------------  Print the decision tree in the console ---------------------- //
// *********************************************************************************** //

void American_Option_Call::print_exercice_policy()
{
    int n_ = Option::get_n();
    // ----------------------------------------------------------------> PRINT STOCK PRICE TREE
    vector<vector<bool>> exercice_policy = get_exercice_policy();
    cout << "EXERCICE POLICY TREE" << endl << "---------------------" << endl;
    for(int i=0;i<=n_;i++)
    {
        cout << "i=" << i;
        for(int j=0;j<=i;j++)
        {
            cout << " /  " << exercice_policy[i][j] ;
        }
        cout << endl;
    }
    cout << "---------------------" << endl;
}




// *********************************************************************************** //
// --------------------------  American Option return PayOff ------------------------- //
// *********************************************************************************** //

double American_Option_Call::american_payoff(int step_i, int node_n)
{
    vector<vector<double>> value_tree = get_valueTree();
    return value_tree[step_i][node_n];
}





// *********************************************************************************** //
// ------- Decision function, print in the console the decision and the PayOff  -------//
// *********************************************************************************** //

void American_Option_Call::should_option_be_exerciced(int step_i, int node_n)
{
    if (node_n<=step_i and step_i<=get_n() and node_n>=0 ) // condition to enter in the loop and find values
        {
            vector<vector<bool>> current_exercice_policy= get_exercice_policy();
            bool chosen_element = current_exercice_policy[step_i][node_n];
            if (chosen_element == true)
            {
                cout << "For node[" << step_i << "," << node_n << "] -> You SHOULD exercice this option. The holder will receive the payoff : " << american_payoff(step_i, node_n)<< endl;
            }
            else
            {
                cout << "For node[" << step_i << "," << node_n << "] -> You SHOULD NOT exercice this option!" << endl;
            }
        }
    else
        {
            cout << "For node[" << step_i << "," << node_n << "] -> Incorrect input values, can't find the node." << endl;
        }
}




// *********************************************************************************** //
// --------------------------- Black-Scholes and Binomial method  ---------------------//
// *********************************************************************************** //

void American_Option_Call::Blackschole()
{
    int n = get_n();
    double S0 = get_S0();
    double K = get_K();
    double r = get_r();
    double sigma = get_sigma();
    double T = get_T();
    
    
    // -------------------------------------------------------------------------------------------------> THE STOCK PRICE TREE
    double dt,u,d,q; // declare and initialise local variables (u,d,q)
    dt = T/n; // It-s the "h" in the practical work n°8 'subject
    u= exp((r+sigma*sigma*0.5)*dt +sigma*sqrt(dt))-1; // New way to compute U here
    d = exp((r+sigma*sigma/2)*dt - sigma*sqrt(K))-1; // New way to compute D here
    double R_ = exp(r*dt)-1;
    q = (R_-d)/(u-d); // New way to compute Q
    
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
    // Step 1 //
    vector<vector<double>> valueTree(n+1,vector<double>(n+1));
    for (int j=0;j<=n;j++) // initialize the last step (i=n) according to the nature of the option
    {   valueTree[n][j] = h (stockTree[n][j]);   }// compute with the parametrable function "h"
    
    // Step 2 // 
    // Now we need to loop backwards through the tree to generate the value at each node using the equation: Vij = e - rdeltat(qVi+1,j+1   +  (1-q)Vi+1,j)
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {   valueTree[i][j] = exp(-r*dt)*( q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]);   }
    }
    Option::set_valueTree(valueTree);
}


double American_Option_Call::get_payoff()
{
    vector<vector<double>> value_tree = get_valueTree();
    return value_tree[0][0];
}
