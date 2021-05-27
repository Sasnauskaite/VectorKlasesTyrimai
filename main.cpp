#include <iostream>
#include <string>
#include "Vector.h"


int main()
{   int size = 20;
    Vector<int> test1;
     for (int i = 0; i < size; i++) {
        test1.push_back(i);
        std::cout<<test1[i]<<" ";
    }


    
	return 0;
}