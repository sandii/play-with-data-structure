#include <stdio.h>

int year (int y) {  
  if ((y % 4 == 0) && (y % 100 != 0) || y % 400 == 0)  
    return 366;  
  else  
    return 365;  
}
  
int main () {  
  int y;
  scanf("%d", &y);

  int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};  
  if (year(y) == 366) days[1] = 29;

  // what day is the first day of this year
  int sum = 0;
  for (int i = 1; i < y; i++) {
    sum += year(i);    
  }
  int week = (sum + 1) % 7;


  printf("\nYear %d\n\n",y);  

  for (int i = 0; i < 12; i++) {  
    printf("Month %d\n", i + 1);  
    printf("  7  1  2  3  4  5  6\n");  
    printf("=====================\n");  
    int begin = 1;  
    for (int j = 0; j < week; j++) {
      printf("   ");        
    }  
    while (begin <= days[i]) {  
      printf("%3d", begin); 
      begin++;
      week = (week + 1) % 7;  
      if (week % 7 == 0) {
        printf("\n");
      }
    }
    printf("\n\n");
  }
}  