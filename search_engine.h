#define COUNT_DOC 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned long size_t;
typedef struct element//해시 테이블에 담길 원소
{
	char *key;
	char **around;
	int around_words;
	char *doc;
}element;
typedef struct list* list_pointer;
typedef struct list//충돌이 일어났을 때 linked list로 연결하기 위한 자료구조
{
	element item;
	list_pointer link;
}list;

list_pointer *ht;
int table_size;
int total_words;
int count_each_doc_words[1 + COUNT_DOC];

void	int_to_string(int i, char *s);
int		string_to_int(char *s1);
int		is_prime(int nb);
int		find_next_prime(int nb);
int		transform(char *key);
int		hash(char *key);
size_t	ft_strlen(char *s);
size_t	is_alpha(char c);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strtrim(char *s1);
char	**put_in_buf(char **buf, int i, char *fname);
void	special_case_of_buf(char **buf, int i, int words, element *tmp);
void	insert_around(char **buf, int i, int words, element *tmp);
char	*to_low(char *s);
int		hash_insert(char **buf, char *fname, int words);
void	put_words();
void	hash_search(char *key);
