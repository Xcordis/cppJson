#include <iostream>
#include "../json/json.h"

using namespace yazi::json;

int main () 
{
    Json v = 4;
    Json arr;
    arr[0] = 1;
    int a = arr[0];
    std::cout << a << std::endl;
    return 0;
}

