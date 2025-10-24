#include <stdio.h>

int main(){
	int w, d, d1, h1;
	int h;
	scanf("%d", &h);
	// 400
	
	// 1 week 
	w = h / 168; // 2
	
	d1 = h % 168;
	
	d = d1 / 24; // 2
	
	h1 = d1 % 24;
	
	
	printf("%d\n%d\n%d", w, d, h1);
	
	
	
	
	
	return 0;
}
