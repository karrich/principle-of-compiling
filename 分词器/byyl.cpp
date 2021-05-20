#include <bits/stdc++.h>
using namespace std;

map<string, int> sign, ma[5];
map<int, string> rema[5];
int leng[5] = {0};
string key[21] = {"int", "for", "char", "float", "void", "const", "if", "else", "do", "while", "scanf", "printf", "return", "main", "read", "string", "using", "namespace", "long", "double", "printf"};
string operatorChar[24] = {"+", "-", "*", "/", "%", "=", "==", ">", "<", "!=", ">=", "<=", "&&", "||", "!", "|", "&", "^", "++", "--", "~", "<>", "<<", ">>"};
string delimiter[12] = {"{", "}", "[", "]", "(", ")", ",", ";", ".", "\"", "'", ":"};
vector<pair<int, int>> words;
bool isChar(char c) //判断是否是字母
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    return false;
}
bool isNumber(char c) //判断是否为数字
{
    if (c <= '9' && c >= '0')
        return true;
    return false;
}
long long change(string s) //16进制转10进制
{
    int tlen = s.length();
    int sum = 0;
    for (int j = tlen - 1; j >= 2; j--)
    {
        sum *= 16;
        if (isNumber(s[j]))
        {
            sum += s[j] - '0';
        }
        else if (s[j] <= 'f' && s[j] >= 'a')
        {
            sum += s[j] - 'a' + 10;
        }
        else if (s[j] <= 'F' && s[j] >= 'A')
        {
            sum += s[j] - 'A' + 10;
        }
    }
    return sum;
}
int main()
{
#pragma region 预处理关键字
    int len = 21;
    for (int i = 0; i < len; i++)
    {
        ma[0][key[i]] = ++leng[0];
        rema[0][leng[0]] = key[i];
        sign[key[i]] = 1;
    }
#pragma endregion

#pragma region 预处理操作符
    len = 24;
    for (int i = 0; i < len; i++)
    {
        ma[3][operatorChar[i]] = ++leng[3];
        rema[3][leng[3]] = operatorChar[i];
        sign[operatorChar[i]] = 4;
    }
#pragma endregion

#pragma region 预处理界符
    len = 12;
    for (int i = 0; i < len; i++)
    {
        ma[4][delimiter[i]] = ++leng[4];
        rema[4][leng[4]] = delimiter[i];
        sign[delimiter[i]] = 5;
    }
#pragma endregion
    string s, input = "";
    while (cin >> s)
        if (input == "")
            input = s;
        else
            input = input + " " + s;
    len = input.length();
    int i = 0;
    while (1)
    {
        while (i < len && (input[i] == ' ' || input[i] == '\n'))
            i++;
        if (i == len)
            break;
        string temp = "";
        if (isChar(input[i]) || input[i] == '_') //变量名
        {
            while (i < len && (isChar(input[i]) || input[i] == '_'))
            {
                temp += input[i];
                i++;
            }
            if (sign[temp] == 0) //字段不存在,存入变量名中
            {
                sign[temp] = 3;
                ma[2][temp] = ++leng[2];
                rema[2][leng[2]] = temp;
            }
        }
        else if (isNumber(input[i])) //数值常量
        {
            bool haveChar = 0;
            while (i < len && (isChar(input[i]) || isNumber(input[i])))
            {
                if (!isNumber(input[i]))
                    haveChar = 1;
                temp += input[i];
                i++;
            }
            if (sign[temp] == 0)
            {
                if (!haveChar)
                {
                    sign[temp] = 2;
                    ma[1][temp] = ++leng[1];
                    rema[1][leng[1]] = temp;
                }
                else
                {
                    int tlen = temp.length();
                    bool ok = 1;
                    if (temp[0] == '0' && (temp[1] == 'x' || temp[1] == 'X') && tlen > 2) //16进制转10进制
                    {
                        for (int j = tlen - 1; j >= 2; j--)
                        {
                            if (isNumber(temp[j]) || (temp[j] <= 'f' && temp[j] >= 'a') || (temp[j] <= 'F' && temp[j] >= 'A'))
                            {
                                continue;
                            }
                            else
                            {
                                ok = 0;
                                break;
                            }
                        }
                    }
                    else
                        ok = 0;
                    if (!ok)
                    {
                        cout << "ERROR:不应该出现这样的变量或者常量：" << temp << '\n';
                        exit(0);
                    }
                    sign[temp] = 2;
                    ma[1][temp] = ++leng[1];
                    rema[1][leng[1]] = temp;
                }
            }
        }
        else if (input[i] == '"') //字符串常量
        {
            temp = input[i];
            words.push_back(make_pair(sign[temp], ma[sign[temp] - 1][temp]));
            i++;
            while (i < len && input[i] != '"')
            {
                temp += input[i];
                i++;
            }
            temp += '"';
            if (temp.length() > 2) //非空字符串常量
            {
                if (sign[temp] == 0)
                {
                    sign[temp] = 2;
                    ma[1][temp] = ++leng[1];
                    rema[1][leng[1]] = temp;
                }
                words.push_back(make_pair(sign[temp], ma[sign[temp] - 1][temp]));
            }
            if (i == len)
            {
                cout << "ERROR:界符匹配失败:" << '"';
                exit(0);
            }
            temp = input[i];
            i++;
        }
        else if (input[i] == '\'') //字符常量
        {
            temp = input[i];
            words.push_back(make_pair(sign[temp], ma[sign[temp] - 1][temp]));
            i++;
            while (i < len && input[i] != '\'')
            {
                temp += input[i];
                i++;
            }
            temp += '\'';
            if (temp.length() == 3)
            {
                if (sign[temp] == 0)
                {
                    sign[temp] = 2;
                    ma[1][temp] = ++leng[1];
                    rema[1][leng[1]] = temp;
                }
                words.push_back(make_pair(sign[temp], ma[sign[temp] - 1][temp]));
            }
            if (i == len)
            {
                cout << "ERROR:界符匹配失败:" << '\'';
                exit(0);
            }
            else if (temp.length() > 3)
            {
                cout << "ERROR:字符输出错误:" << temp;
                exit(0);
            }
            temp = input[i];
        }
        else
        {
            int maxi = i;
            string t = "";
            while (i < len && !isChar(input[i]) && !isNumber(input[i]) && input[i] != ' ' && input[i] != '\n') //搜寻最大匹配的界符或者运算符
            {
                temp += input[i];
                i++;
                if (sign[temp] != 0)
                {
                    t = temp;
                    maxi = i;
                }
            }
            if (t == "") //无匹配的界符或者运算符
            {
                cout << "ERROR:不能理解:" << temp;
                exit(0);
            }
            else
            {
                temp = t;
                i = maxi;
            }
        }
        words.push_back(make_pair(sign[temp], ma[sign[temp] - 1][temp]));
    }
    for (auto i : words)
    {
        cout << rema[i.first - 1][i.second] << '\t';
        if (i.first == 1)
            cout << "关键字\t";
        else if (i.first == 2)
            cout << "常量\t";
        else if (i.first == 3)
            cout << "变量名\t";
        else if (i.first == 4)
            cout << "运算符\t";
        else if (i.first == 5)
            cout << "界符\t";
        cout << i.second << '\n';
    }
    system("pause");
}