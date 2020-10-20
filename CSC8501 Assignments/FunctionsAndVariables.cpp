void v1(char* a, const char* b) {

	while (*b != '\0') {

		*a = *b;
		a++;
		b++;

	}
	*a = '\0';
}

void v2(char* a, const char* b) {

}