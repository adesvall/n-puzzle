#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

int get_number(std::string str, int i, std::vector<int>& vec)
{
    size_t j = i;


    for (; !isspace(str[j]) && j < str.size(); j++)
    {
        if (str[j] < '0' || str[j] > '9')
        {
            std::cout << "Parse Error: " << str[j] << " not a number" << std::endl;   
            exit(1);
        }
    }
    vec.push_back(atoi(str.substr(i, j-i).c_str()));

    return j - 1;
}

bool check_board(std::vector<int>& res)
{
    int i;
    for (i=0; i*i<res.size();i++)
        ;
    if (i < 3 || i*i != res.size())
        return false;

    std::vector<bool> checker(res.size());
    for (size_t j = 0; j < res.size(); j++)
    {
        if (res[j] < 0 || res[j] >= (int)checker.size())
            return false;
        if (checker[res[j]])
            return false;
        checker[res[j]] = true;
    }
    return true;
}

std::vector<int> parse_file(const char *arg)
{
    std::ifstream       file(arg);
    std::vector<int>    res;
    std::stringstream   buff;
    std::string         str;

    if (file.fail())
    {
        std::cout << "Parse Error: couldn't load file" << std::endl;
        file.close();
        exit(1);
    }
    buff << file.rdbuf();
    str = buff.str();
    file.close();

    int n = -1;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '#')
            while (i < str.size() && str[i] != '\n')
                i++;
        else if (!isspace(str[i]))
        {
            i = get_number(str, i, res);
            if (n == -1)
            {
                n = res[0];
                res.pop_back();
            }
        }
    }
    if (n == 0 || res.size() != n * n || !check_board(res))
    {
        std::cout << n << res.size() << std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
        std::cout << "Parse Error : bad format" << std::endl;
        exit(1);
    }
    return res;
}

std::vector<int> generate_board(int n)
{
    std::vector<int>    res;

    if (n < 3)
    {
        std::cout << "Parse Error: wrong number" << std::endl;
        exit(1);
    }
    srand(time(NULL));
    for (int i = 0; i < n*n; i++)
    {
        res.push_back(i);
    }
    for (int i = 0; i < n*n; i++)
    {
        int j = rand() % (n*n - i);
        if (j) {
            int swap = res[i];
            res[i] = res[i + j];
            res[i + j] = swap;
        }
        // std::cout << res[i] << std::endl;
    }
    if (n == 0 || res.size() != n * n || !check_board(res))
    {
        std::cout << n << res.size() << std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
        std::cout << "Parse Error : generation failed !" << n << std::endl;
        exit(1);
    }
    return res;
}

std::vector<int> parse(const char *arg)
{
    bool isfile = false;

    // std::cout << "Parsing arg = " << arg << std::endl;


    if (!arg[0] || arg[0] == '0')
        isfile = true;
    for (int i = 0; arg[i] && !isfile; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
            isfile = true;
    }

    if (isfile)
        return parse_file(arg);
    
    return generate_board(atoi(arg));
}
