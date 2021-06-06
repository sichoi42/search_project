#include "search_engine.h"

typedef struct docu
{
	int searched_words;//해당 문서에서 검색된 단어의 개수
	char **searched_words_around;//해당 문서에서 검색된 단어의 주변 단어들
}docu;

void get_rank(int rank[], docu doc[])
{
	int i,j;

	for (i=1;i<=COUNT_DOC;i++)
		rank[i] = 1;
	for (i=1;i<=COUNT_DOC;i++)
		for (j=1;j<=COUNT_DOC;j++)
			if (doc[i].searched_words < doc[j].searched_words)
				rank[i]++;
}

void hash_search(char *key)
{
	int k, n, i, j, m;
	int total_cmp;
	int total_words;
	int hash_result;
	list_pointer p;
	docu doc[COUNT_DOC + 1];
	int count[COUNT_DOC + 1]={0};
	int rank[COUNT_DOC + 1] = {0};
	for (i=1;i<=COUNT_DOC;i++)
		doc[i].searched_words = 0;

	k = 0;
	n = 0;
	total_words = 0;
	total_cmp = 0;
	while (n < table_size * table_size)
	{
		hash_result = (hash(key) + n) % table_size;
		if (ht[hash_result]->item.key == NULL)
		{
			printf("This word does not exist..\n");
			total_cmp++;
			break;
		}
		if (strncmp(ht[hash_result]->item.key, key, ft_strlen(key)) == 0
		&& strncmp(ht[hash_result]->item.key, key, ft_strlen(ht[hash_result]->item.key)) == 0)
		{
			p = ht[hash_result];
			while (p)
			{
				i = string_to_int(p->item.doc);
				count[i] = count[i] + p->item.around_words + 1;
				(doc[i].searched_words)++;
				if (p->link)
				{
					if (string_to_int(p->link->item.doc) - string_to_int(p->item.doc) != 0)
						doc[i].searched_words_around = malloc(sizeof(char *) * (count[i] + 1));
				}
				else
					doc[i].searched_words_around = malloc(sizeof(char *) * (count[i] + 1));
				p = p->link;
				total_words++;
			}
			p = ht[hash_result];
			m = 0;
			while (p)
			{
				i = string_to_int(p->item.doc);
				for (j=0;p->item.around[j];j++)
				{
					doc[i].searched_words_around[m] = strdup(p->item.around[j]);
					m++;
					if (p->item.around[j+1] == 0)
						{
							doc[i].searched_words_around[m] = strdup("\n");
							m++;
						}
				}
				if (p->link)
				{
					if (string_to_int(p->link->item.doc) - string_to_int(p->item.doc) != 0)
					{
						doc[i].searched_words_around[m] = 0;
						m = 0;
					}
				}
				else
					doc[i].searched_words_around[m] = 0;
				p = p->link;
			}
			get_rank(rank, doc);
			for (m=1;m<=COUNT_DOC;m++)
				for (i=1;i<=COUNT_DOC;i++)
				{
					if (rank[i] == m && doc[i].searched_words != 0)
					{
						char s[] = "doc000.txt";
						int_to_string(i, s);
						printf("%s (%s : %d)\n", s, ht[hash_result]->item.key, doc[i].searched_words);
						for (j=0;doc[i].searched_words_around[j];j++)
							printf("%s ", doc[i].searched_words_around[j]);
						printf("\n");
					}
				}
			total_cmp++;
			break;
		}
		total_cmp++;
		n = ++k;
		n = n * n;
	}
	for (i=1;i<=COUNT_DOC;i++)
	{
		if (doc[i].searched_words != 0)
		{
			for (j=0;doc[i].searched_words_around[j];j++)
				free(doc[i].searched_words_around[j]);
			free(doc[i].searched_words_around[j]);
			free(doc[i].searched_words_around);
		}
	}
	printf("Total number of searched words : %d\n", total_words);
	printf("Total number of comparison : %d\n", total_cmp);
}

