// name: Jing Ming
// email: ming.j@northeastern.edu
// 3 * N Tiling Problem with 2 kinds tiles
// 1 x 2 and 2 x 1 tiles.

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    // If n is odd, 0 possible cases.
    if(n % 2 == 1) return d[n]; // d[n] = 0
    if(n == 2) return d[n] = 3;
    if(d[n] != 0) return d[n];

    int i = 4;
    long long int sum = dp(n - 2) * 3;
    while(i < n){
	   sum += dp(n - i) * 2;
	   i += 2;
    }

    // when n > 2, n is even, has 2 more cases
    sum += 2;

    return d[n] = sum;
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
