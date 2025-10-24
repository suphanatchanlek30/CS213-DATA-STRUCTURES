#include <stdio.h>

int main(){
	
	// input
	int a;
	int b;
	
	scanf("%d", &a);
	scanf("%d", &b);
	
	// process
	float car = 0;
	
	if(b == 1){
		car = a * 0.0003;
	} else if(b == 2){
		car = a * 0.0001;
	} else if(b == 3) {
		car = a *  0.0004;
	} else {
		printf("Invalid Input");
		return;
	}
	
	// output
	printf("%.4f", car);
	
	
	return 0;
}
