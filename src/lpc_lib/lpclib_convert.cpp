/***
 ====================================================================================

 WARNING

 The code in this file only contains INTERNAL IMPLEMENTATION code for the
 LPCGraphics library. You SHOULD NOT edit it, and you do NOT need
 to read or understand it in order to use the library.

 ====================================================================================
 ***/


#include <iostream>
#include <sstream>
#include <cstdlib>
#include "lpclib.h"
using namespace std;

#define Err(x) { cerr << "*** Runtime Error: " << x << endl; exit(-1); }

template <typename In, typename Out>
Out ConvertValue(In val)
{
    Out result;
    stringstream ss;
    ss << val;
    ss >> result;
    if (! ss)
    {
        stringstream ss2;
        ss2 << "Bad conversion attempted with value " << val;
        Err(ss2.str());
    }
    return (result);
}

string IntToString(int num)
{
    return (ConvertValue<int, string>(num));
}

string DoubleToString(double num)
{
    return (ConvertValue<double, string>(num));
}

int StringToInt(string str)
{
    return (ConvertValue<string, int>(str));
}

double StringToDouble(string str)
{
    return (ConvertValue<string, double>(str));
}

string ConvertToLowerCase(string s)
{
    string result = s;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        result[i] = tolower(result[i]);
    }
    return (result);
}

string ConvertToUpperCase(string s)
{
    string result = s;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        result[i] = toupper(result[i]);
    }
    return (result);
}

