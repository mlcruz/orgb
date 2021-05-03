#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// From CLRS 32.4 - The Knuth-Morris-Pratt algorithm - 926

int *compute_prefix_function(char *p)
{
    int m = strlen(p);

    int *prefix = (int *)malloc(m * sizeof(int));
    prefix[0] = 0;
    int k = 0;
    for (int q = 1; q < m; q++)
    {
        while (k > 0 && (p[k] != p[q]))
        {
            k = prefix[k - 1];
        }
        if (p[k] == p[q])
        {

            k++;
        }
        prefix[q] = k;
    }
    return prefix;
}

int kmp_matcher(char *t, char *p)
{
    int n = strlen(t);
    int m = strlen(p);
    int *prefix = compute_prefix_function(p);

    int q = 0;

    for (int i = 0; i < n; i++)
    {
        while (q > 0 && (p[q] != t[i]))
        {
            q = prefix[q - 1];
        }
        if (p[q] == t[i])
        {
            q++;
        }
        if (q == m)
        {
            return i + 1 - m;
        }
    }
    free(prefix);
    return -1;
}

int main()
{
    char *text = "adsadstestestestes";
    char *pattern = "teste";
    int offset = kmp_matcher(text, pattern);
    printf("offset is %d\n", offset);
    return 0;
}
