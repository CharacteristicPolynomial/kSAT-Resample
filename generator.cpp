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
        c = 0;
        // initially set all variables and values to 0
    }
    int k; // the clause size
    vector<int> var; // store the indices of the variables
    vector<int> value; // store the value of each variable
    int c; // current number of assigned variables
    bool insert(int v) {
        if (c >= k) {
            cerr << "assigning variable to full clauses" << endl;
            exit(-1);
        }
        bool flag = false;
        for (size_t i = 0; i < c; i++)
        {
            if (var[i] == v) {
                flag = true;
                // so if it is assigned before, ignore this assignemnt
                break;
            }
        }
        if(!flag) {
            var[c] = v;
            value[c] = rand() % 2; // randomly assign a value
        }
        c++; // note that a repeated assignment also increases the variable counter
        if (c == k) 
            return 1; // full
        else return 0; // not full yet
    }
    int print(ostream& ost) {
        for (size_t i = 0; i < k; i++)
        {
            ost << var[i] << " " << value[i] << " ";
        }
    }
};

int main() {
    srand(time(NULL));
    int n = 10000;
    int k = 10;
    int d = 600;
    int r = 100;
    int copy_n = d/k + 1; // number of copies
    int var_n = k * n / copy_n; // number of variables

    // create clauses
    vector<Clause*> clauses;
    vector<Clause*> living_clauses;
    clauses.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        clauses[i] = new Clause(k);
    }

    int clause_counter = 0;
    for (size_t var = 1; var < var_n; var++)
    {
        for (size_t i = 0; i < copy_n; i++)
        {
            int living_n = living_clauses.size();
            double q = 1 - exp(-living_n/r);
            // cout << living_n << " " << clause_counter << endl;
            int remaining_n = living_n + n - clause_counter;
            int prechoice = rand() % remaining_n;
            if (prechoice < living_n || rand() < q*RAND_MAX) {
                // the case where the clause shoulde be choosen among the living clause
                int choice = rand() % living_n;
                bool fullQ = living_clauses[choice]->insert(var);
                if (fullQ)
                    living_clauses.erase(living_clauses.begin()+choice);
            }
            else {
                // when adding to a new clause, without loss of generality, let it to be the next clause
                Clause* ptr = clauses[clause_counter];
                living_clauses.push_back(ptr);
                ptr->insert(var);
                clause_counter++;
            }
        }        
    }

    ofstream file;
    file.open("hahaha");
    file << n << " " << k << " " << var_n << endl;
    for (size_t i = 0; i < n; i++)
    {
        clauses[i]->print(file);
        file << endl;
    }
    file.close();
    

    // free the clauses
    for (size_t i = 0; i < n; i++)
    {
        delete clauses[i];
    }
    
    return 0;
}
