#include <iostream>
#include "labeling.h"

using namespace std;

int main()
{
    cout << "1 - Labeling " << endl;

    int x;
    cin >> x;

    switch (x) {
    case 1:
        labeling();
        break;
    default:
        break;
    }

    return 0;
}