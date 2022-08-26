// name: Jing Ming
// email: ming.j@northeastern.edu
// 2 * N Tiling Problem

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    if(n == 1 || n == 2){
    	d[n] = n;
    	return d[n];
    }
    if(d[n] != 0){
        return d[n];
    }
    return d[n] = dp(n - 2) + dp(n - 1);
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
