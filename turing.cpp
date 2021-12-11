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
    //输入为空
    case 11:
        cerr << "illegal input!" << endl;
        if (verbose)
        {
            cerr << errortag << endl
                 << "error:the input is empty" << endl;
        }
        break;
    //输入不合法
    case 12:
        cerr << "illegal input!" << endl;
        if (verbose)
        {
            char c = s[0];
            int i = c - '0';
            string st = s.substr(1, s.size() - 1);
            cerr << errortag << endl
                 << "error: " << st[i] << "was not declared in the set of input symbols" << endl
                 << "Input: " << st << endl
                 << "       ";
            for (int j = 0; j < i; j++)
                cerr << " ";
            cerr << "^" << endl;
        }
        break;
    }
    if (verbose)
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
    else if (begin != string::npos && end != string::npos)
    {
        string temp = s.substr(begin + 1, end - begin - 1);
        return temp;
    }
    //return q0 = 0
    else if (begin == string::npos && end == string::npos)
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
bool turing::is_symbol_legal_S(string s)
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
        else
            return false;
    }
}
bool is_symbol_legal_G(string s)
{
    if (s.size() != 1)
        return false;
    else
    {
        int c = (int)s[0];
        if (c >= 21 && c <= 126)
        {
            //',' 、';' 、'{' 、'}' 、'*'
            if (c == 44 || c == 59 || c == 123 || c == 125 || c == 42)
                return false;
            else
                return true;
        }
        else
            return false;
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
        if (s[i] != 'l' && s[i] != 'r' && s[i] != '*')
        {
            cout << i;
            return false;
        }
    }
    return true;
}
bool is_symbol_legal_char(char c)
{
    if (c >= 21 && c <= 126)
    {
        //',' 、';' 、'{' 、'}' 、'*'
        if (c == ' ' || c == ',' || c == ';' || c == '{' || c == '}' || c == '*')
            return false;
        else
            return true;
    }
    else
        return false;
}
string clean(string line)
{
    //删除行内注释
    int tagindex = -1;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ';')
        {
            tagindex = i;
            break;
        }
    }
    //删除行末空格
    int spaceindex = line.size() - 1;
    if (tagindex == -1)
    {
        for (int i = line.size() - 1; i > 0; i--)
        {
            if (line[i] != ' ')
            {
                spaceindex = i;
                break;
            }
        }
    }
    else
    {
        for (int i = tagindex - 1; i > 0; i--)
        {
            if (line[i] != ' ')
            {
                spaceindex = i;
                break;
            }
        }
    }
    //返回删除后子串
    string s = line.substr(0, spaceindex + 1);
    return s;
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
        int linec = 1;
        while (getline(f, line))
        {
            line = clean(line);
            cout << linec << line << endl;
            linec++;
            if (line[0] == ';' || line == "")
                continue;
            else if (line[0] == '#')
            {
                //读出每行有效部分
                string temp = findstring(line);
                //cout<<temp<<endl;
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
                            if (is_symbol_legal_S(v[i]))
                                input_symbol.insert(v[i][0]);
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
                            if (is_symbol_legal_G(v[i]))
                                tape_symbol.insert(v[i][0]);
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

                for (int i = 0; i < v.size(); i++)
                    cout << v[i] << ' ';

                //是否与纸带数相同
                if (v[1].size() != N || v[2].size() != N || v[3].size() != N)
                    error(line, 5);
                //是否由五部分组成
                if (v.size() != 5)
                    error(line, 6);
                //放在循环外判断状态是否在Q中
                //if (state.count(v[0]) == 0 || state.count(v[4]) == 0)
                //    error(line, 7);

                //判断符号组中符号是否合法
                for (int i = 0; i < v[1].size(); i++)
                    if (!is_symbol_legal_char(v[1][i]))
                    {
                        error(line, 8);
                    }
                for (int i = 0; i < v[2].size(); i++)
                    if (!is_symbol_legal_char(v[2][i]))
                        error(line, 8);

                if (!is_direction_legal(v[3]))
                    error(line, 9);

                //for (int i = 0; i < v[1].size(); i++)
                //    if (tape_symbol.count(v[1][i]) == 0)
                //        error(line, 10);
                //for (int i = 0; i < v[2].size(); i++)
                //    if (tape_symbol.count(v[2][i]) == 0)
                //        error(line, 10);

                delta d(v[0], v[1], v[2], v[3], v[4]);
                deltafunc[v[0]].push_back(d);
            }
        }
        map<string, vector<delta>>::iterator iter;
        //判断新旧状态是否在Q中
        for (iter = deltafunc.begin(); iter != deltafunc.end(); iter++)
        {
            vector<delta> value = iter->second;
            for (int i = 0; i < value.size(); i++)
            {
                if (state.count(value[i].old_state) == 0 || state.count(value[i].new_state) == 0)
                    error(line, 7);
            }
        }
        //判断新旧符号组是否在G中
        for (iter = deltafunc.begin(); iter != deltafunc.end(); iter++)
        {
            vector<delta> value = iter->second;
            for (int i = 0; i < value.size(); i++)
            {
                for (int j = 0; j < value[i].old_symbol.size(); j++)
                    if (tape_symbol.count(value[i].old_symbol[j]) == 0)
                        error(line, 10);
                for (int j = 0; j < value[i].new_symbol.size(); j++)
                    if (tape_symbol.count(value[i].new_symbol[j]) == 0)
                        error(line, 10);
            }
        }
    }
    f.close();
}
string turing::run(string input)
{
    if (verbose)
        cout << "Input: " << input << endl;
    //初始化tape
    for (int i = 0; i < N; i++)
    {
        list<unit> tape(1, unit(0, '_'));
        tapes.push_back(tape);
        heads.push_back(tapes[i].begin());
    }
    //初始化第一条tape并检验合法
    if (input != "")
    {
        tapes[0].clear();
        for (int i = 0; i < input.size(); i++)
        {
            if (input_symbol.count(input[i]) == 0)
            {
                error(to_string(i) + input, 12);
            }
            else
            {
                tapes[0].push_back(unit(i, input[i]));
            }
        }
    }
    else
    {
        error(input, 11);
    }
    //开始进行运行
    int step = 0;
    string cur_state = start_state;
    if (verbose)
        cout << runtag << endl;
    while (1)
    {
        //打印verbose信息
        if (verbose)
            printtape(step, cur_state);
        //若在终止状态中则停止
        if (final_state.count(cur_state) == 1)
            return result();
        //若找不到状态转移函数则停止
        if (deltafunc.find(cur_state) == deltafunc.end())
            return result();
        //找到现符号组
        string cur_symbols = "";
        for (int i = 0; i < N; i++)
        {
            char ch = (*heads[i]).symbol;
            cur_symbols += ch;
        }
        //找到对应的转移函数
        vector<delta> tapen = deltafunc[cur_state];
        int funcindex;
        for (funcindex = 0; funcindex < tapen.size(); funcindex++)
        {
            if (tapen[funcindex].old_state == cur_state && tapen[funcindex].old_symbol == cur_symbols)
                break;
        }
        //改变相应符号组
        for (int i = 0; i < N; i++)
        {
            (*heads[i]).symbol = tapen[funcindex].new_symbol[i];
            //移动纸带头
            switch (tapen[funcindex].direction[i])
            {
            case 'l':
                //如果最左边省略负号(后面再乘-1)
                if (heads[i] == tapes[i].begin())
                {
                    tapes[i].push_front(unit((*heads[i]).index - 1, '_'));
                    heads[i]--;
                }
                else
                    heads[i]--;
                break;
            case 'r':
                //如果最右边扩展
                if (heads[i] == tapes[i].end())
                {
                    tapes[i].push_back(unit((*heads[i]).index + 1, '_'));
                    heads[i]++;
                }
                else
                    heads[i]++;
                break;
            case '*':
                break;
            default:
                error(tapen[funcindex].direction, 9);
                break;
            }
        }
        //改变状态
        cur_state = tapen[funcindex].new_state;
        step++;
    }
}
string turing::result()
{
    string res = "";
    for (auto i = tapes[0].begin(); i != tapes[0].end(); i++)
    {
        char ch = (*i).symbol;
        if (ch != blank)
            res = res + ch;
    }
    return res;
}
void turing::printtape(int step, string cur_state)
{
    cout << "Step\t: " << step << endl;
    //分别为每一行打印
    string index = "";
    string tape = "";
    string head = "";
    for (int i = 0; i < N; i++)
    {
        //找到打印的左右区间
        /*int left = 0;
        int right = tapes[i].size() - 1;
        for (int j = 0; j < tapes[i].size(); j++)
        {
            if (tapes[i][j].symbol != '_')
                break;
            left++;
        }
        for (int j = tapes[i].size() - 1; j > left; j--)
        {
            if (tapes[i][j].symbol != '_')
                break;
            right--;
        }*/
        auto left = tapes[i].begin();
        auto right = tapes[i].end()--;
        for (auto iter = tapes[i].begin(); iter != tapes[i].end(); iter++)
        {
            if ((*iter).symbol != blank)
                break;
            left++;
        }
        for (auto iter = tapes[i].end(); iter != left; iter--)
        {
            if ((*iter).symbol != blank)
                break;
            right--;
        }
        //打印串
        for (auto j = left; j != right; j++)
        {
            //index
            if ((*j).index < 0)
                (*j).index *= -1;
            string indexstr = to_string((*j).index);
            index = index + indexstr + " ";
            //tape，与index左对齐
            int num = indexstr.size();
            tape = tape + (*j).symbol + string(num, ' ');
            //head
            if ((*j).index == (*heads[i]).index)
                head = head + "^";
            head = head + string(num + 1, ' ');
        }
        cout << "Index" << i << "\t: " << index << endl
             << "Tape" << i << "\t: " << tape << endl
             << "Head" << i << "\t: " << head << endl;
    }
    cout << "State\t: " + cur_state << endl
         << "-------------------------------------------" << endl;
}