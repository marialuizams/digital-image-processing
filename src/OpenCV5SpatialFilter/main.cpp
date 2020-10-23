#include <iostream>
#include "spatialfilter.h"

using namespace std;

int main()
{
    cout << "1 - Spatial Filter " << endl;

    int x;
    cin >> x;

    switch (x) {
    case 1:
        spatialfilter();
        break;
    default: 
        break;
    }

    return 0;
}