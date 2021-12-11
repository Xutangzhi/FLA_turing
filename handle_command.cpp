#include "turing.h"

const char *usage="usage: turing [-v|--verbose] [-h|--help] <tm> <i";
const char *endtag = "==================== END ===============";

int main(int argc, char **argv)
{
    string filename = "";
    string input = "";
    bool verbose = false;

    if (argc == 1)
    {
        cout << usage << endl;
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
                    break;
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
                    if (arg[-1] == 'm' && arg[-2] == 't' && arg[-3] == '.')
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
    string res = tm.run(input);
    if(verbose)
        cout << "Result: ";
    cout << res << endl;
    if(verbose)
        cout <<endtag<< endl;
    return 0;
}