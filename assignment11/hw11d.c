// name: Jing Ming
// email: ming.j@northeastern.edu
// 2 * N Tiling Problem with 3 kinds tiles
// 1 x 2, 2 x 1 and 1 x 1 tiles.

#include <stdio.h>

// max number of inputs
#define MAX_D 20

// MEMO definition
// type of array to hold computed data values
typedef unsigned long long memo_d[MAX_D];

unsigned long long dp(int n) {
    static memo_d d = {0};
    // Add your code here
    if(n == 1) return d[n] = 2;
    if(n == 2) return d[n] = 7;
    if(d[n] != 0) return d[n];

    unsigned long long sum = dp(n - 2) * 3 + dp(n - 1) * 2;
    int i;
    for(i = 3; i < n; i++) {
        sum += dp(n - 1) * 2;
    }

    // plus n, 2 * D[0]
    d[n] = sum + 2;

    return d[n];

}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
