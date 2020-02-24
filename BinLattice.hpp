//
//  BinLattice.hpp
//  C_finance_td6Q3
//
//  Created by PERIER Hugo on 06/12/2018.
//  Copyright © 2018 PERIER Hugo. All rights reserved.
//

#ifndef BinLattice_hpp
#define BinLattice_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;


template <class T>
class binlattice
{
private:
    int n;
    vector<vector<T>> lattice;
    
public:
    // ---------------------------------------  CONSTRUCTOR   -----------------------------------------------//
    binlattice(int n_, vector<vector<T>> lattice_)
    {
        n = n_;
        lattice = lattice_;
    }

    // ---------------------------------  some necessary functions   ----------------------------------------//
    int get_n() {return n;}
    vector<vector<T>> get_lattice() { return lattice;}
    void set_lattice(vector<vector<T>> new_lattice){lattice=new_lattice;}
    
    
    // -------------------------------------------  set n  -------------------------------------------------//
    void set_n(int new_n)
    {
        if (new_n>0)
        {
            n=new_n;
            vector<vector<T>> new_lattice(n+1,vector<T>(n+1));
            vector<vector<T>> former_lattice = get_lattice();
            for (int i=0;i<=n;i++)
            {
                for (int j=0;j<=n;j++)
                {
                    new_lattice[i][j]=former_lattice[i][j];
                }
            }
            set_lattice(new_lattice);
        }
    }
    
    
    // ------------------------------------------  set node  ------------------------------------------------//
   void set_node(int i,T value)
    {
        vector<vector<T>> current_lattice = get_lattice();
        current_lattice[get_n()][i]=value;
    }
    
    
    
    // ------------------------------------------  get node  ------------------------------------------------//
    T get_node(int i){return get_lattice()[get_n()][i];}
    
    
    
    // ------------------------------------------  display  -------------------------------------------------//
    void display()
    {
        vector<vector<T>> current_lattice = get_lattice();
        cout <<  "---------- display -----------" << endl;
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=i;j++)
            {
                cout << " /  " << current_lattice[i][j] ;
            }
            cout << endl;
        }
        cout << "------------------------------" << endl;
    }
};
#endif /* BinLattice_hpp */
