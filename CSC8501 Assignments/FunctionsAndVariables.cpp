#include <iostream>
using namespace std;


void v1(char* a, const char* b) {
	while (*b != '\0') {
		*a = *b;
		a++;
		b++;
	}
	*a = '\0';
}

void v2(char* a, const char* b) {
	for (int x = strlen(b); x > 0; x--,b++, a++){
		*a = *b;
	}
	*a = '\0';
}

int main() {
	
	char* a = new char[5];
	const char* b = "testtest";
	//cout << strlen(b) << endl;

	v2(a, b);
	//cout << "a is " << a << endl;
	//cout << "b is " <<b << endl;
}