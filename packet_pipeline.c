#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "packet_pipeline.h"

// Helper function to build the KMP Longest Proper Prefix which is also Suffix (LPS) table
void compute_lps_array(const char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Highly efficient Knuth-Morris-Pratt string matching running in O(n + m) time
bool kmp_search(const char* txt, const char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    if (M > N || M == 0) return false;

    int* lps = (int*)malloc(sizeof(int) * M);
    compute_lps_array(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    bool found = false;

    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            found = true; // Match hit found!
            break;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    free(lps);
    return found;
}
