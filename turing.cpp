#include "turing.h"

const char *errortag = "==================== ERR ================";
const char *endtag = "==================== END ===============";
const char *runtag = "==================== RUN ===============";

void turing::error(string s, int i)
{
    switch (i)
    {
    //文件打开错误
    case 1:
        cerr << "can not open file!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:can not open " << filename << endl;
        }
        break;
    //定义语句错误
    case 2:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:the definition grammer is wrong: " << s << endl;
        }
        break;
    //含有非法字符
    case 3:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:the character is illegal: " << s << endl;
        }
        break;
    //初始或终止状态不在Q内
    case 4:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:q0 or F not in Q: " << s << endl;
        }
        break;
    //转移函数中符号数或方向数不等于tape数
    case 5:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's tapnum not equals N: " << s << endl;
        }
        break;
    //转移方程定义错误
    case 6:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's definition is wrong: " << s << endl;
        }
        break;
    //转移函数中状态不在Q内
    case 7:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's state not in Q: " << s << endl;
        }
        break;
    //转移函数中非法字符
    case 8:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's symbol is illegal: " << s << endl;
        }
        break;
    //转移函数中非法方向
    case 9:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's direction is illegal: " << s << endl;
        }
        break;
    //不由纸带符号构成
    case 10:
        cerr << "syntax error!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:delta's symbol not in G: " << s << endl;
        }
        break;
    //
    case 11:

        break;
    }
    cerr << endtag << endl;
    exit(i);
}
string turing::findstring(string s)
{
    int first_space = s.find_first_of(' ');
    int last_space = s.find_last_of(' ');
    int begin = s.find("{");
    int end = s.find("}");
    //grammer error
    if (first_space == last_space)
    {
        return "";
    }
    else if (s[first_space + 1] != '=')
    {
        return "";
    }
    else if (last_space - first_space != 2)
    {
        return "";
    }
    //return {,,,}
    else if (begin != string::npos && end != string::nops)
    {
        string temp = s.substr(begin + 1, end - begin - 1);
        return temp;
    }
    //return q0 = 0
    else if (begin == string::npos && end == string::nops)
    {
        string temp = s.substr(last_space + 1, s.size() - last_space);
        return temp;
    }
    else
    {
        return "";
    }
}
vector<string> turing::split(string s, string c)
{
    vector<string> v;
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}
bool turing::is_symbol_legal(string s)
{
    if (s.size() != 1)
        return false;
    else
    {
        int c = (int)s[0];
        if (c >= 21 && c <= 126)
        {
            //',' 、';' 、'{' 、'}' 、'*' 、'_'
            if (c == 44 || c == 59 || c == 123 || c == 125 || c == 95 || c == 42)
                return false;
            else
                return true;
        }
    }
}
bool turing::is_state_legal(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '_')
            continue;
        else if (s[i] >= '0' && s[i] <= '9')
            continue;
        else if (s[i] >= 'a' && s[i] <= 'z')
            continue;
        else if (s[i] >= 'A' && s[i] <= 'Z')
            continue;
        else
            return false;
    }
    return true;
}
bool turing::is_direction_legal(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != 'l' || s[i] != 'r' || s[i] != '*')
            return false;
    }
    return true;
}
turing::turing(string fname, bool v)
{
    filename = fname;
    verbose = v;

    fstream f(filename);
    if (!f.is_open())
    {
        error("", 1);
    }
    else
    {
        string line = "";
        while (getline(f, line))
        {
            //
            if (line[0] == ';' || line[0] == ' ')
                continue;
            else if (line[0] == '#')
            {
                string temp = findstring(line);
                switch (line[1])
                {
                case 'Q':
                    if (temp != "")
                    {
                        vector<string> v;
                        v = split(temp, ",");
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (is_state_legal(v[i]))
                                state.insert(v[i]);
                            else
                            {
                                error(line, 3);
                                break;
                            }
                        }
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'S':
                    if (temp != "")
                    {
                        vector<string> v;
                        v = split(temp, ",");
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (is_symbol_legal(v[i]))
                                input_symbol.insert(v[i]);
                            else
                            {
                                error(line, 3);
                                break;
                            }
                        }
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'G':
                    if (temp != "")
                    {
                        vector<string> v;
                        v = split(temp, ",");
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (is_symbol_legal(v[i]))
                                tape_symbol.insert(v[i]);
                            else
                            {
                                error(line, 3);
                                break;
                            }
                        }
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'q':
                    if (line[2] == '0')
                    {
                        if (temp != "")
                        {
                            if (is_state_legal(temp))
                            {
                                if (state.count(temp) == 1)
                                    start_state = temp;
                                else
                                    error(line, 4);
                            }
                            else
                                error(line, 3);
                        }
                        else
                            error(line, 2);
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'B':
                    if (temp != "")
                    {
                        if (temp == "_")
                            blank = '_';
                        else
                            error(line, 3);
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'F':
                    if (temp != "")
                    {
                        vector<string> v;
                        v = split(temp, ",");
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (is_state_legal(v[i]))
                            {
                                if (state.count(v[i]) == 1)
                                    final_state.insert(v[i]);
                                else
                                    error(line, 4);
                            }
                            else
                            {
                                error(line, 3);
                                break;
                            }
                        }
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                case 'N':
                    if (temp != "")
                    {
                        for (int i = 0; i < temp.size(); i++)
                        {
                            if (temp[i] < '0' || temp[i] > '9')
                                error(line, 3);
                        }
                        stringstream ss;
                        ss << temp;
                        ss >> N;
                    }
                    else
                    {
                        error(line, 2);
                    }
                    break;
                default:
                    error(line, 2);
                    break;
                }
            }
            else
            {
                vector<string> v;
                v = split(line, " ");
                if (v.size() != 5)
                    error(line, 6);

                if (state.count(v[0]) == 0 || state.count(v[4]) == 0)
                    error(line, 7);

                for (int i = 0; i < v[1].size(); i++)
                    if (!is_symbol_legal(v[1][i]))
                        error(line, 8);
                for (int i = 0; i < v[1].size(); i++)
                    if (!is_symbol_legal(v[2][i]))
                        error(line, 8);

                if (!is_direction_legal(v[3]))
                    error(line, 9);

                for (int i = 0; i < v[1].size(); i++)
                    if (tape_symbol.count(v[1][i]) == 0)
                        error(line, 10);
                for (int i = 0; i < v[1].size(); i++)
                    if (tape_symbol.count(v[2][i]) == 0)
                        error(line, 10);

                if (v[1].size() != N || v[2].size() != N || v[3].size() != N)
                    error(line, 5);

                delta d(v[0], v[1], v[2], v[3], v[4]);
                deltafunc[v[0]].push_back(d);
            }
        }
    }
    f.close();
}
void turing::run(string input)
{
    if(verbose)
    {
        cout<<"Input: "<<input<<endl;
        
    }
}