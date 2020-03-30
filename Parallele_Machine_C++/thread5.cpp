/*http://www.zedwood.com/article/cpp-md5-function*/
#include <iostream>
#include "md5.h"
 
using std::cout; using std::endl;
 
int main(int argc, char *argv[])
{
    cout << "md5 of 'grape': " << md5("grape") << endl;
    return 0;
}