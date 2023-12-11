#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <optional>

using namespace std;

auto subStrWithDifferentLenghtInDigits(unordered_map<string, int>& digits,const string& line, int& i, const uint lenght)
{
    int digit = 0;
    if(i + lenght <= line.size())
    {
        digit = digits[line.substr(i, lenght)];
        if(digit != 0)
        {
            // i += lenght - 1;
        }
    }

    return digit;
}

auto substrInDigits(unordered_map<string, int>& digits,const string& line, int& i)
{
    int digit = subStrWithDifferentLenghtInDigits(digits, line, i, 3);
    if(digit != 0)
    {
        // cout << "l3" << endl;
        return digit;
    }
    digit = subStrWithDifferentLenghtInDigits(digits, line, i, 4);;
    if(digit != 0)
    {
        return digit;
    }
    digit = subStrWithDifferentLenghtInDigits(digits, line, i, 5);;
    return digit;
}

int main()
{
  unordered_map<string, int> digits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    fstream file("input.txt");

    string line;
    int sum = 0;
    int lastD = 0;
    while(getline(file, line))
    {
        int i = 0;
        int firstD = 0;
        bool isFirstD = true;
        sum += lastD;
        
        while(i < line.size())
        {
            if(line[i] >= '0' && line[i] <= '9')
            {
                if(isFirstD)
                {
                    firstD = 10 * static_cast<int>(line[i] - '0');
                    // cout << firstD << " ";
                    isFirstD = false;
                }

                lastD = static_cast<int>(line[i]  - '0');
            }
            else{
                int digit = substrInDigits(digits, line, i);
                if(digit != 0)
                {
                    if(isFirstD)
                    {
                        firstD = 10 * digit;
                        cout << firstD << " ";
                        isFirstD = false;
                    }

                    lastD = digit;
                    cout << lastD << " ";
                }
            }
            i++;
        }
        sum += firstD;

        cout << line << " linesum = " << firstD + lastD << endl;
        // cout << sum << " ";
    }
    sum += lastD;
    cout << sum << endl;
    return sum;
}