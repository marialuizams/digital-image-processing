#include <iostream>
#include "tiltshift.h"

using namespace std;

int main()
{
    cout << "1 - Tilt Shift" << endl;

    int x;
    cin >> x;

    switch (x) {
    case 1:
        tiltshift();
        break;
    default:
        break;
    }

    return 0;
}