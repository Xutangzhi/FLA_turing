#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string.h>
#include <sstream>
using namespace std;

struct delta
{
    string old_state;
    string old_symbol;
    string new_symbol;
    string direction;
    string new_state;
    delta(string a, string b, string c, string d, string e)
    {
        old_state = a;
        old_symbol = b;
        new_symbol = c;
        direction = d;
        new_state = e;
    }
};
struct unit
{
    int index;
    char symbol;
    unit(int a, char b)
    {
        index = a;
        symbol = b;
    }
};

class turing
{
private:
    //grammer
    set<string> state;                    //Q
    set<string> input_symbol;             //S
    set<string> tape_symbol;              //G
    set<string> final_state;              //F
    string start_state;                   //q0
    char blank;                           //B
    int N;                                //N
    map<string, vector<delta> > deltafunc; //delta

    //tape
    vector<list<unit> > tapes;
    vector<list<unit>::iterator> heads;

    //command
    string filename;
    bool verbose;

public:
    //initialize
    turing(string fname, bool v);
    //error
    void error(string s, int i);
    //func
    vector<string> split(string s, string c);
    string findstring(string s);
    bool is_symbol_legal(string s);
    bool is_state_legal(string s);
    bool is_direction_legal(string s);
    void run(string input);
};