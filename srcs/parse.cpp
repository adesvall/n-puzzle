#include <vector>
#include <fstream>
#include <iostream>

std::vector<int> parse_file(const char *arg)
{
    std::ifstream       file(arg);
    std::vector<int>    res;

    if (file.fail())
    {
        std::cout << "Parse Error\n";
        file.close();
        exit(1);
    }
    int n;
    file >> n;
    if (file.fail())
    {
        std::cout << "Parse Error\n";
        file.close();
        exit(1);
    }
    while (!file.eof())
    {
        int k;
        file >> k;

        if (file.fail())
        {
            std::cout << "Parse Error\n";
            file.close();
            exit(1);
        }
        res.push_back(k);
    }
    if (res.size() != n * n)
    {
        std::cout << "Parse Error\n";
        file.close();
        exit(1);
    }
    return res;
}

std::vector<int> generate_board(int n)
{
    std::vector<int>    res;

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
    }
    return res;
}

std::vector<int> parse(const char *arg)
{
    bool isfile = false;

    if (!arg[0] || arg[0] == '0')
        isfile = true;
    for (int i = 0; arg[i] && !isfile; i++)
    {
        if (arg[i] < '0' && arg[i] > '9')
            isfile = true;
    }

    if (isfile)
        return parse_file(arg);
    
    return generate_board(atoi(arg));
}
