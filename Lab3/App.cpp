#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "TestMethod.h"

int main(){
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
    testRemoveAll();
    std::cout << "New method tests over" << std::endl;
    system("pause");
}