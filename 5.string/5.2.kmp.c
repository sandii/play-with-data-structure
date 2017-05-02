/*
* author: chenzhi <chenzhibupt@qq.com>
* data: May 2, 2017
*
* kmp
* - invented by knuth-morris-pratt in 1977
* - key is to find common part of prefix and suffix of pattern string
* - and we can get an array next[]
*/

#include <stdio.h>
#include <string.h> // strlen

int violentMath (char* s, char* p) {
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen) {
		if (s[i] == p[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == pLen) {
		return i - j;
	} else {
		return -1;
	}
}

main () {
	printf("%d\n", violentMath("hello", "ell"));
	printf("%d\n", violentMath("hello", "all"));
	printf("%d\n", violentMath("hello", "hel"));
	printf("%d\n", violentMath("hello", "loo"));
}

