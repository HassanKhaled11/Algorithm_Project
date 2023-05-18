#include <iostream>
using namespace std;

int main() {
int n;
cin >> n;

if (n == 2) {
// Special case for n = 2
cout << "1 1" << endl;
return 0;
}

// Start shooting at spot 2
int shot = 2;
while (shot <= n-1)
{
// Shoot at consecutive spots until the target is hit or guaranteed to be hit
cout << shot << " ";
shot++;
}

// Shoot at spot n-1 to force the target to move to an even-numbered spot
cout << n-1 << " ";

// Continue shooting at consecutive even-numbered spots until the target is hit
shot = n-2;
while (shot >= 2)
{
cout << shot << " ";
shot--;
}
cout << endl;
return 0;
}
