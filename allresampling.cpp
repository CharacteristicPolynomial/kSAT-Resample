#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
using namespace std;

class Clause {
    public:
    Clause(int _k) {
        k = _k;
        var.resize(k, 0);
        value.resize(k, 0);
        // initially set all variables and values to 0
    }
    int k; // the clause size
    vector<int> var; // store the indices of the variables
    vector<int> value; // store the value of each variable
    int import(istream& ist) {
        for (size_t i = 0; i < k; i++)
        {
            ist >> var[i] >> value[i];
        }
    }
    int print(ostream& ost) {
        for (size_t i = 0; i < k; i++)
        {
            ost << var[i] << " " << value[i] << " ";
        }
    }
    bool resample_if_bad(const vector<bool>& state_cache, vector<bool>& state) {
        bool flag = true;
        for (size_t i = 0; i < k; i++)
        {
            if(state_cache[var[i]] == value[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            // reample all variables
            for (size_t i = 0; i < k; i++)
            {
                state[var[i]] = rand()%2;
            }            
        }    
        return flag;    
    }
};

int main() {
    srand(time(NULL));

    ifstream ifs;
    ifs.open("hahaha");
    int n, k, var_n;
    ifs >> n >> k >> var_n;
    // create clauses
    vector<Clause*> clauses;
    clauses.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        clauses[i] = new Clause(k);
        clauses[i]->import(ifs);
    }
    ifs.close();
    
    vector<bool> state(var_n);
    vector<bool> state_cache(var_n);
    for (size_t i = 0; i < var_n; i++)
    {
        state[i] = rand()%2;
    }
    state_cache = state;
    int round = 0;
    while(true) {
        cout << round << endl;
        bool flag = false;
        for (size_t i = 0; i < n; i++)
        {
            if(clauses[i]->resample_if_bad(state_cache, state))
                flag = true;
        }
        if(!flag) 
            break;
        state_cache = state;
        round++;
    }
    
        for (size_t i = 0; i < var_n; i++)
        {
            cout << state[i] << " ";
        }
        cout << endl;

    // free the clauses
    for (size_t i = 0; i < n; i++)
    {
        delete clauses[i];
    }
    
    return 0;
}
