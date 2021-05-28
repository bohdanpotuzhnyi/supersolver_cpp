//
// Created by Anna Kuzmenko
//
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector <string> first, second, st;
int n;

string del_e(vector<char> x)
{
    string res;
    res.resize(x.size());
    int j = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        if (x[i] != '_')
        {
            res[j] = x[i];
            ++j;
        }
    }
    res.resize(j);
    if (j==0) {res[0] = '_'; res.resize(1);}
    return res;
}
bool check(string x)
{
    bool f = true;
    for (int i = 0; i < st.size(); ++i)
    {
        if (st[i] == x){
            f =  false;
            break;
        }
    }
    st.push_back(x);
    return f;
}

void Markov(string x, ofstream &file)
{
    st.push_back(x);
    bool cycle = 0;
    while (1)
    {
        bool c = false;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < x.size() - first[i].size() + 1; ++j)
            {
                bool p = false;
                if (x[j] == first[i][0])
                {
                    p = true;
                    for (int k = j + 1, l = 1; l < first[i].size(); ++k, ++l)
                    {
                        if (x[k] != first[i][l])
                        {
                            p = false;
                            break;
                        }
                    }
                }
                if (p == true)
                {
                    vector <char> x1;
                    for (int k = 0; k < j; ++k) {
                        x1.push_back(x[k]);
                        file << x[k];
                    }
                    file << "\\underline{" << first[i] << "}";
                    for (int k = j, l = 0; l < second[i].size(); ++k, ++l)
                    {
                        x1.push_back(second[i][l]);

                    }
                    for (int k = j + first[i].size(); k < x.size(); ++k)
                    {
                        x1.push_back(x[k]);
                        file << x[k];
                    }
                    string x2;
                    x2 = del_e(x1);
                    x = x2;
                    file << "\\vdash ";
                    //file << endl << x << endl;
                    if (!check(x))
                    {
                        file << x << "\\\\$ cycle $";
                        cycle = 1;
                    }
                    c = 1;
                    if (second[i][0] == '*') {
                        cycle = 1;
                    }
                    break;
                }
            }
            if (c)break;
            if (cycle) break;
        }
        if (!c) break;
        if (cycle) break;
    }
    if (x[0]=='_') file << "\\varepsilon $";
    else file << x;
}

int main(int argc, char* argv[])
{
    std::ofstream file(argv[argc-1]);
    n = 0;

    file << "\\documentclass{article}" << std::endl;
    file << "\\usepackage[T2A,T1]{fontenc}" << std::endl;
    file << "\\usepackage[utf8]{inputenc}" << std::endl;
    file << "\\usepackage[english,russian,ukrainian]{babel}" << std::endl;
    file << "\\usepackage[a6paper]{geometry}" << std::endl;
    file << "\\usepackage{lmodern}" << std::endl;
    file << "\\usepackage{textcomp}" << std::endl;
    file << "\\usepackage{lastpage}" << std::endl;
    file << "\\usepackage{amsmath}" << std::endl;
    file << "\\usepackage{amsfonts}" << std::endl;
    file << "\\usepackage{amssymb}" << std::endl;
    file << "\\usepackage{centernot}" << std::endl;
    file << "\\pagenumbering{gobble}" << std::endl;
    file << "\\begin{document}$" << std::endl;
    
    //file << "Enter number if rules: ";
    //cin >> n;
    //file << endl << "Input word1 -> word2" << endl;
    for (int i = 1; i < argc-3; i+=2)
    {
        string a, b;
        //file <<endl<< "--------------------------------" << endl;
        //file << "word1: ";
        //cin >> a;
        //file <<endl<< "word2: ";
        //cin >> b;
        a = argv[i];
        b = argv[i+1];
        first.push_back(a);
        second.push_back(b);
        n++;
        //file << a << " " << b << endl;
    }
    //file << endl << "Enter word: ";
    string x;
    //cin >> x;
    x = argv[argc-2];
    //file << x;
    Markov(x, file);
    file << "$\\end{document}";
    file.close();
    return 0;
}