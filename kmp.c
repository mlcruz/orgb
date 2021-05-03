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

    // scan linear
    for (int i = 0; i < n; i++)
    {
        // prox char não da match -> escrita na memoria
        while (q > 0 && (p[q] != t[i]))
        {
            q = prefix[q - 1];
        }
        ///
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
    char *text = "A string-matching algorithm wants to find the starting index m in string S[] that matches the search word W[]. The most straightforward algorithm, known as the Brute-force or Naive algorithm, is to look for a word match at each index m, i.e. the position in the string being searched that corresponds to the character S[m]. At each position m the algorithm first checks for equality of the first character in the word being searched, i.e. S[m] =? W[0]. If a match is found, the algorithm tests the other characters in the word being searched by checking successive values of the word position index, i. The algorithm retrieves the character W[i] in the word being searched and checks for equality of the expression S[m+i] =? W[i]. If all successive characters match in W at position m, then a match is found at that position in the search string. If the index m reaches the end of the string then there is no match, in which case the search is said to fail. ";
    char *pattern = "characters";
    int offset = kmp_matcher(text, pattern);
    printf("offset is %d\n", offset);
    return 0;
}
