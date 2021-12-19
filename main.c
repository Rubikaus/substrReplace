#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* str_find(char* src, char* subsrt);
int str_count(char* src, char* substr);
char* str_replace(char* src, char* substr, char* repstr);
int str_split(char*** tokens, char* src, char sep);

// нахождение длины строки
int my_strlen(char* src) {
	int len = 0;
	while (1)
	{
		if (src[len] == 0)
		{
			return len;
		}
		else
		{
			len++;
		}
	}
}

// копирует n символов из строки src в строку dst
void my_strncpy(char* src, char* dst, int n) {
	int i;
	for (i = 0; i < n; i++)
	{
		dst[i] = src[i];
	}
	dst[i] = 0;
	return;
}

// дописывает в конец строки dst строку src
void my_strcat(char* src, char* dst) {
	int dst_len = my_strlen(dst);
	int src_len = my_strlen(src);
	dst = dst + dst_len;
	my_strncpy(src, dst, src_len);
	return;
}

// дописывает в конец строки dst n символов строки src
void my_strncat(char* src, char* dst, int n) {
	int dst_len = my_strlen(dst);
	dst = dst + dst_len;
	my_strncpy(src, dst, n);
	return;
}

// возвращает указатель на первое вхождение подстроки в строку
// если строка не сожержит подстроку, то возвращает NULL
char* str_find(char* src, char* subsrt) {
	int size_src = my_strlen(src);
	int size_subsrt = my_strlen(subsrt);
	for (int i = 0; i < size_src; i++)
	{
		for (int j = 0; j < size_subsrt; j++)
		{
			if (src[j] == subsrt[j])
			{
				if (j == size_subsrt - 1)
				{
					return src;
				}
			}
			else
			{
				src = src + sizeof(char);
				break;
			}
		}
	}
	return NULL;
}


// возвращает число вхождений подстроки в строку
int str_count(char* src, char* substr) {
	int count = 0;
	src = str_find(src, substr);
	while (src != NULL) {
		count++;
		src = str_find(src + sizeof(char), substr);
	}
	return count;
}


// возвращает новую строку, в которой все вхождения подстроки substr
// заменяются строкой repstr
// исходная строка src остаётся неизменной
char* str_replace(char* src, char* substr, char* repstr) {
	int count_subs = str_count(src, substr);
	if (count_subs == 0)
	{
		return NULL;
	}
	int diff = my_strlen(repstr) - my_strlen(substr);
	char* res = (char*)malloc(my_strlen(repstr) * count_subs + my_strlen(src) + sizeof(char));
	my_strncpy(src, res, str_find(src, substr) - src);
	for (int i = 1; i <= count_subs; i++)
	{
		my_strcat(repstr, res);
		int lgth_res = my_strlen(res);
		if (str_find(src + lgth_res - i * diff, substr) == 0)
		{
			my_strncat(src + lgth_res - count_subs * diff,
				res,
				my_strlen(src) - lgth_res + count_subs * diff);
		}
		else
		{
			my_strncat(src + lgth_res - i * diff,
				res,
				str_find(src + lgth_res - i * diff, substr) - (src + lgth_res) + i * diff);
		}
	}
	return res;
}


// разделяет строку по символу sep, сохраняя результат в массиве tokens
// и возвращает число полученных строк
// если символ sep не входит в строку, то возвращает 0
int str_split(char*** tokens, char* src, char sep) {
	char arr_sep[2];
	arr_sep[0] = sep;
	arr_sep[1] = 0;
	if (str_find(src, arr_sep) == NULL)
	{
		return 0;
	}
	else
	{
		int count = str_count(src, arr_sep) + 1;
		(*tokens) = (char**)malloc((count) * sizeof(char*));
		for (int i = 0; i < count; i++)
		{
			if (i != count - 1)
			{
				int lgth = str_find(src, arr_sep) - src;
				(*tokens)[i] = (char*)malloc(lgth + sizeof(char));
				for (int j = 0; j < lgth; j++)
				{
					my_strncpy(src,
						(*tokens)[i],
						lgth);
				}
				src = str_find(src, arr_sep) + sizeof(char);
			}
			else
			{
				int lgth = my_strlen(src);
				(*tokens)[i] = (char*)malloc(lgth + sizeof(char));
				for (int j = 0; j < lgth; j++)
				{
					my_strncpy(src,
						(*tokens)[i],
						lgth);
				}
			}
		}
		return count;
	}
}


void test_str() {
	char my_str[256] = "Kobalt is my alt art pal";
	char months[256] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
	char** tokens = 0;
	int count, i;

	// str_find test
	printf("%s\n\n", str_find(my_str, "alt"));

	// str_count test
	printf("%d\n\n", str_count(my_str, "al"));

	// str_replace test
	printf("%s\n\n", str_replace(my_str, "al", "BOOM"));

	//str_split test
	count = str_split(&tokens, months, ',');
	for (i = 0; i < count; i++) {
		printf("month=[%s]\n", *(tokens + i));
		free(*(tokens + i));
	}
	printf("\n");
	free(tokens);
}

int main() {
	test_str();
	return 0;
}