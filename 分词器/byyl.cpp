#include <bits/stdc++.h>
using namespace std;

map<string, int> sign, ma[5];
map<int, string> rema[5];
int leng[5] = {0};
string key[21] = {"int", "for", "char", "float", "void", "const", "if", "else", "do", "while", "scanf", "printf", "return", "main", "read", "string", "using", "namespace", "long", "double", "printf"};
string operatorChar[24] = {"+", "-", "*", "/", "%", "=", "==", ">", "<", "!=", ">=", "<=", "&&", "||", "!", "|", "&", "^", "++", "--", "~", "<>", "<<", ">>"};
string delimiter[12] = {"{", "}", "[", "]", "(", ")", ",", ";", ".", "\"", "'", ":"};
vector<pair<int, int>> words;
bool isChar(char c) //�ж��Ƿ�����ĸ
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    return false;
}
bool isNumber(char c) //�ж��Ƿ�Ϊ����
{
    if (c <= '9' && c >= '0')
        return true;
    return false;
}
long long change(string s) //16����ת10����
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
#pragma region Ԥ����ؼ���
    int len = 21;
    for (int i = 0; i < len; i++)
    {
        ma[0][key[i]] = ++leng[0];
        rema[0][leng[0]] = key[i];
        sign[key[i]] = 1;
    }
#pragma endregion

#pragma region Ԥ���������
    len = 24;
    for (int i = 0; i < len; i++)
    {
        ma[3][operatorChar[i]] = ++leng[3];
        rema[3][leng[3]] = operatorChar[i];
        sign[operatorChar[i]] = 4;
    }
#pragma endregion

#pragma region Ԥ������
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
        if (isChar(input[i]) || input[i] == '_') //������
        {
            while (i < len && (isChar(input[i]) || input[i] == '_'))
            {
                temp += input[i];
                i++;
            }
            if (sign[temp] == 0) //�ֶβ�����,�����������
            {
                sign[temp] = 3;
                ma[2][temp] = ++leng[2];
                rema[2][leng[2]] = temp;
            }
        }
        else if (isNumber(input[i])) //��ֵ����
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
                    if (temp[0] == '0' && (temp[1] == 'x' || temp[1] == 'X') && tlen > 2) //16����ת10����
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
                        cout << "ERROR:��Ӧ�ó��������ı������߳�����" << temp << '\n';
                        exit(0);
                    }
                    sign[temp] = 2;
                    ma[1][temp] = ++leng[1];
                    rema[1][leng[1]] = temp;
                }
            }
        }
        else if (input[i] == '"') //�ַ�������
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
            if (temp.length() > 2) //�ǿ��ַ�������
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
                cout << "ERROR:���ƥ��ʧ��:" << '"';
                exit(0);
            }
            temp = input[i];
            i++;
        }
        else if (input[i] == '\'') //�ַ�����
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
                cout << "ERROR:���ƥ��ʧ��:" << '\'';
                exit(0);
            }
            else if (temp.length() > 3)
            {
                cout << "ERROR:�ַ��������:" << temp;
                exit(0);
            }
            temp = input[i];
        }
        else
        {
            int maxi = i;
            string t = "";
            while (i < len && !isChar(input[i]) && !isNumber(input[i]) && input[i] != ' ' && input[i] != '\n') //��Ѱ���ƥ��Ľ�����������
            {
                temp += input[i];
                i++;
                if (sign[temp] != 0)
                {
                    t = temp;
                    maxi = i;
                }
            }
            if (t == "") //��ƥ��Ľ�����������
            {
                cout << "ERROR:�������:" << temp;
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
            cout << "�ؼ���\t";
        else if (i.first == 2)
            cout << "����\t";
        else if (i.first == 3)
            cout << "������\t";
        else if (i.first == 4)
            cout << "�����\t";
        else if (i.first == 5)
            cout << "���\t";
        cout << i.second << '\n';
    }
    system("pause");
}