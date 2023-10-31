#define OK 0
#define Error -1

char* moveStr(char* str, int begin) {
	if (begin < 0) {
		return Error;
	}
	do {
		str[begin] = str[begin+1];
		begin++;
	} while (str[begin - 1] != '\0');
	return str;
}