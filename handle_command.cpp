#include "turing.h"

const char *usage="usage: turing [-v|--verbose] [-h|--help] <tm> <i";
const char *endtag1 = "==================== END ===============";

int main(int argc, char **argv)
{
    string filename = "";
    string input = "";
    bool verbose = false;

    if (argc == 1)
    {
        cout << usage << endl;
        exit(0);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            //option
            if (arg[0] == '-')
            {
                if (arg == "-h" || arg == "--help")
                {
                    cout << usage << endl;
                    exit(0);
                }
                else if (arg == "-v" || arg == "--verbose")
                {
                    verbose = true;
                }
                else
                {
                    cerr << usage << endl;
                    exit(0);
                }
            }
            //run .tm
            else
            {
                if (filename == "")
                {
                    string argrev = arg;
                    reverse(argrev.begin(),argrev.end());
                    if (argrev[0] == 'm' && argrev[1] == 't' && argrev[2] == '.')
                        filename = arg;
                    else
                    {
                        cerr << usage << endl;
                        exit(0);
                    }
                }
                else if (input == "")
                {
                    input = arg;
                }
                else
                {
                    cerr << usage << endl;
                    exit(0);
                }
            }
        }
    }
    
    turing tm(filename,verbose);
   cout<<1<<endl;
    string res = tm.run(input); 
    if(verbose)
        cout << "Result: ";
    cout << res << endl;
    if(verbose)
        cout <<endtag1<< endl;
    return 0;
}