#include <iostream>
#include <string.h>
using namespace std;
int main() {
   int d = 238;
   std::string s = std::to_string(d);
   cout << "Conversion of double to string: " << s;
   return 0;
}