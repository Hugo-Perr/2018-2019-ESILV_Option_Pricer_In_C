//
//  American_Option_Put.cpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 27/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#include "American_Option_Put.hpp"


// *********************************************************************************** //
// ------------------  creation of the Tree of the decision tree --------------------- //
// *********************************************************************************** //

void American_Option_Put::creat_exercice_policy()
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

void American_Option_Put::print_exercice_policy()
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

double American_Option_Put::american_payoff(int step_i, int node_n)
{
    vector<vector<double>> value_tree = get_valueTree();
    return value_tree[step_i][node_n];
}





// *********************************************************************************** //
// ------- Decision function, print in the console the decision and the PayOff  -------//
// *********************************************************************************** //

void American_Option_Put::should_option_be_exerciced(int step_i, int node_n)
{
    if (node_n<=step_i and step_i<=get_n() and node_n>=0 ) // condition to enter in the loop and find values
    {
        vector<vector<bool>> current_exercice_policy = get_exercice_policy();
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
