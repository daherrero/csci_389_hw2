#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;
using key_type = const std::string;  // Keys for K-V pairs
using val_type = const void*;        // Values for K-V pairs
using index_type = uint32_t;      

int main()
{
    int a = 40;
    tuple < key_type , val_type> myCache;
    myCache = make_tuple("the",&a); 
    std::cout << get<0>(myCache) << std::endl;
}
