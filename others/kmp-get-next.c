/*
* author: chenzhi <chenzhibupt@qq.com>
* date: july 29, 2017
*
* kmp
* - invented by knuth-morris-pratt in 1977
*
* - key is to get an array next[] 
* - by calculate length of same prefix and suffix of pattern string
* - table below shows that: 
* - p[3] is 2 means it has same prefix and suffix "AB" 
* - p[4] is 3 means it has same prefix and suffix "ABA"
* - at last we should shift it one step to right to get next[]
*  0 1 2 3 4 5 6
*  A B A B A C D - pattern string
*  0 0 1 2 3 0 0 - length of same prefix and suffix
*  0 0 0 1 2 3 0 - move one step to right
*
* - after we have next[]
* - when s[i] != p[j], we can reset j = next[j] instead of j = 0 in violent match
* - because we already know string before position j has same prefix and suffix,
* - with length of next[j]
* - so we can simply match them from position next[j] instead of 0
*
* - time complexity O(m + n)
*/

#include <stdio.h>
#include <string.h> // strlen

void getNext (char* p, int next[]) {
	// init
	int len = strlen(p);
	int sta = 0;
	int end = 1;
	next[0] = 0;

	// main loop
	while (end < len) {

		// if equal, situation is simple
		if (p[sta] == p[end]) {
			next[end] = sta + 1;
			sta++;
			end++;
			continue;
		} 

		// if not equal, have 2 possibilities
		if (sta == 0) {
			next[end++] = 0;
		} else {
			sta = 0;
		}
	}

	// shift one step to right
	for (int i = len - 1; i > 0; i--) {
		next[i] = next[i - 1];
	}
}

int kmp (char* s, char* p) {
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0;
	int j = 0;	
	int next[pLen];
	getNext(p, next);
	while (i < sLen && j < pLen) {
		if (s[i] == p[j]) {
			i++;
			j++;
			continue;
		} 
		if (j == 0) {
			i++;
		} else {
			j = next[j];
		}
	}
	if (j == pLen) {
		return i - j;
	} else {
		return -1;
	}	
}

main () {
	char* p = (char*)("ABCFFABCGAG");
	int len = strlen(p);
	int next[len];
	getNext(p, next);
	for (int i = 0; i < len; i++) printf("%2d ", i); printf("\n");
	for (int i = 0; i < len; i++) printf("%2c ", p[i]); printf("\n");
	for (int i = 0; i < len; i++) printf("%2d ", next[i]); printf("\n");
	
	printf("%d\n", kmp((char*)("hello"), (char*)("ell")));
	printf("%d\n", kmp((char*)("hello"), (char*)("all")));
	printf("%d\n", kmp((char*)("hello"), (char*)("hel")));
	printf("%d\n", kmp((char*)("hello"), (char*)("ababacd")));
}
