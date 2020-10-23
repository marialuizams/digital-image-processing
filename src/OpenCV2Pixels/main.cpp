#include <iostream>
#include "pixels.h"
#include "regions.h"
#include "swapregions.h"

using namespace std;

int main()
{
    cout << "1 - Pixels" << endl;
    cout << "2 - Regions" << endl;
    cout << "3 - Swap Regions" << endl;

    int x;
    cin >> x;

    switch (x) {
    case 1 :
        pixels();
        break;
    case 2:
        regions();
        break;
    case 3:
        swapregions();
        break;
    default:
        break;
    }

    return 0;
}