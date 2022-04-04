#include <iostream>
#include <math.h>       /* round, floor, ceil, trunc */

using namespace std;

int main() {
  int rocketsize;
    //  cin >> rocketsize;
    rocketsize = 116;

    // BEGIN: your code
    // Name the variable that contains the answer `result`.
    if (rocketsize <= 15) {
        cout << 0;
    } else {
        float result;
        float numbFuelTanks = ceil(rocketsize / 115.0f);
        int remainder = rocketsize % 115;
        float spaceLeftAfterTanks;
        if (remainder < 15 && remainder != 0){
            numbFuelTanks -=1;
            spaceLeftAfterTanks = numbFuelTanks * 100;
        }else{
            spaceLeftAfterTanks = rocketsize - (numbFuelTanks * 15.0f);
        }
        result = spaceLeftAfterTanks;

        cout << result << " fuel tanks: " << numbFuelTanks << " size: " << result << endl;
    }
}