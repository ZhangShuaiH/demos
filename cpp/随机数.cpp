#include <iostream>
#include <iomanip>

using namespace std;

int main(){
   srand(time(NULL));
   for (int i = 0; i < 10; i++)
   {
       cout << rand() << endl;
   }
   return 0;
}
