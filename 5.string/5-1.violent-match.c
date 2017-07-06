/*
* author: chenzhi <chenzhibupt@qq.com>
* date: May 2, 2017
*
* violent match
* - match string s and p by each charactor, at postion i and j
* - if match (s[i] == p[j]), match next charactor (i++, j++)
* - if not match, reset i and j (i = i - j + 1, j = 0)
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

