#include <iostream>
#include"include/Controller.h"

using namespace std;

int main()
{
     //cout << "Hello world!" << endl;
    srand(time(0));
    Controller gameController;
    gameController.run();

    return 0;
}
