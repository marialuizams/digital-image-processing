#include <iostream>
#include "histogram.h"
#include "equalize.h"
#include "motiondetector.h"

using namespace std;

int main()
{
    cout << "1 - Histogram " << endl;
    cout << "2 - Equalize" << endl;
    cout << "3 - Motion detector" << endl;

    int x;
    cin >> x;

    switch (x) {
    case 1:
        histogram();
        break;
    case 2:
        equalize();
        break;
    case 3:
        motiondetector();
        break;
    default:
        break;
    }

    return 0;
}