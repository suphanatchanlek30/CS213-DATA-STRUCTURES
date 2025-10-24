#include <stdio.h>

int main(){
	int a1, a2, a3;
	int b1, b2, b3;
	
	int a = 0;
	int b = 0;
	
	// input
	scanf("%d %d %d", &a1, &a2, &a3);
	scanf("%d %d %d", &b1, &b2, &b3);
	
	// process
	if(a1 > b1){
		a = a + 1;
	} else if(b1 > a1) {
		b = b + 1;
	} else {
		a = a + 0;
		b = b + 0;
	}
	
	if(a2 > b2){
		a = a + 1;
	} else if(b2 > a2) {
		b = b + 1;
	} else {
		a = a + 0;
		b = b + 0;
	}
	
	if(a3 > b3){
		a = a + 1;
	} else if(b3 > a3) {
		b = b + 1;
	} else {
		a = a + 0;
		b = b + 0;
	}
	
	
	
	
	// output
	printf("%d %d", a, b);
	
	return 0;
}
