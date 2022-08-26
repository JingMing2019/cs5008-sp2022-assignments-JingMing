/* Jing Ming */
/* ming.j@northeastern.edu */
/* Partition Problem */

#include<stdio.h>
#define MAXN 50       /* largest number of books */
#define MAXK 10        /* largest number of dividers */
#define MAXINT 100000  /* infinity */

/*function to find the maximum of two numbers*/
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

/* function to calculate the sum of an array*/
/* not necessary in this problem */
int sum(int arr[], int from, int to)
{
    int total = 0;
    for (int i = from; i <= to; i++) {
        total += arr[i];
    }
    return total;
}

/* function to print the books with partition*/
void print_books(int s[], int start, int end){
    int i;            /* counter */

    printf("\n{");
    for (i = start; i <= end; i++) {
        printf(" %d ", s[i]);
    }
    printf("}\n");
}

/* function to print the DP table */
void print_matrix(int m[MAXN][MAXK], int n, int k)
{
    int i, j;        /* counters */

    printf("\n");
    printf("    ");
    for (j = 1; j <= k; j++) {
        printf(" %5d ", j);
    }
    printf("\n");
    printf("    -------------------------------");
    printf("\n");

    for (i = 1; i <= n; i++) {
        printf("%d | ", i);
        for (j = 1; j <= k; j++) {
            printf(" %5d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Recursive function to reconstruct the partition to print the books*/
// s[]              book thicknesses to partition
// d[MAXN][MAXK]    DP Table for dividers
// n                number of books
// k                number of partition
void reconstruct_partition(int s[], int d[MAXN][MAXK], int n, int k){
    if (k == 1)  //base case
        print_books(s, 1, n);
    else {
        reconstruct_partition(s, d, d[n][k], k - 1);
        print_books(s, d[n][k] + 1, n);
    }
}

/* Function to create DP table for n books and k partitions*/
void partition(int s[], int n, int k){
    int p[MAXN];                  /* prefix sums array */
    int m[MAXN][MAXK];            /* DP table for values */
    int d[MAXN][MAXK] = {0};     /* DP table for dividers */
    int cost;                     /* track the minimum cost*/
    int i, j, x;                  /* counters */

    /*Insert your code here*/
    p[0] = 0; // precomputing the sum
    // 1 partition, n books
    for(i = 1; i <= n; i++) {
    	p[i] = p[i - 1] + s[i];
    	m[i][1] = p[i];
    }

    // 1 book, k partitions
    for(j = 1; j <= k; j++) {
        m[1][j] = s[1];
    }

    /* 2 to k partitions*/
    // n books
    for (i = 2; i <= n; i++) {
        // k partitions
        for (j = 2; j <= k; j++) {
            m[i][j] = MAXINT; /*initialize infinity*/
            for (x = 1; x <= i; x++) {
                //cost = max(m[x][j-1],sum(s,x+1,i));O(kN2)
                cost = max(m[x][j - 1], p[i] - p[x]); // O(K * N^2)
                if(m[i][j] > cost) {
                    /* store the minimum cost for x from 1 to i */
                    m[i][j] = cost;
                    /* position of dividers is stored in matrix d */
                    d[i][j] = x;
                }
            }
        }
    }
    printf("DP Table for value: \n");
    print_matrix(m, n, k);

    printf("DP Table for dividers \n");
    print_matrix(d, n, k);

    printf("Partition of the books are:\n");
    reconstruct_partition(s, d, n, k);        /* print book partition */
}


/*-------------- Main program--------*/
int main()
{
    int s[MAXN];        /* book thicknesses to partition */
    int n, i;           /* how many books? */
    int k;              /* how many partitions? */
    // n = 9;              /* total 9 books*/
    // k = 3;              /* 3 partitions*/

    printf("Enter the total number of books: ");
    scanf("%d", &n);

    printf("Enter the total number of partitions: ");
    scanf("%d", &k);

    printf("Enter the thickness of %d books: ", n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    printf("\n");

    partition(s, n, k);
    return 0;
}
