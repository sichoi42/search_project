#include "search_engine.h"

char **put_in_buf(char **buf, int i, char *fname)
{
	int j;
	FILE* fp;
	char tmp[20];

	fp = fopen(fname, "r");
	buf = malloc(sizeof(char *) * (count_each_doc_words[i] + 1));
	j = 0;
	while (fscanf(fp, "%s", tmp) == 1)
	{
		buf[j] = strdup(tmp);
		j++;
	}
	buf[j] = 0;
	fclose(fp);
	return buf;
}

void	special_case_of_buf(char **buf, int i, int words, element *tmp)
{
	int j;
	int k;

	k = 0;
	if (words <= 4)
	{
		tmp->around_words = words;
		tmp->around = malloc(sizeof(char *) * (words + 1));
		for (j=0;j<words;j++)
			tmp->around[j] = strdup(buf[j]);
		tmp->around[j] = 0;
	}
	else
	{
		if (i == 0 || i == words - 1)
		{
			tmp->around_words = 4;
			tmp->around = malloc(sizeof(char *) * (4 + 1));
			if (i == 0)
			{
				for (j=0;j<4;j++)
				{
					tmp->around[k] = strdup(buf[j]);
					k++;
				}
				tmp->around[k] = 0;
			}
			else
			{
				for (j=words-4;j<words;j++)
				{
					tmp->around[k] = strdup(buf[j]);
					k++;
				}
				tmp->around[k] = 0;
			}
		}
		else if (words == 6 && (i == 1 || i == words - 2))
		{
			tmp->around_words = 5;
			tmp->around = malloc(sizeof(char *) * (5 + 1));
			if (i == 1)
			{
				for (j=0;j<5;j++)
				{
					tmp->around[k] = strdup(buf[j]);
					k++;
				}
				tmp->around[k] = 0;
			}
			else
			{
				for (j=words-5;j<words;j++)
				{
					tmp->around[k] = strdup(buf[j]);
					k++;
				}
				tmp->around[k] = 0;
			}
		}
		else
		{
			tmp->around_words = words;
			tmp->around = malloc(sizeof(char *) * (words + 1));
			for (j=0;j<words;j++)
				tmp->around[j] = strdup(buf[j]);
			tmp->around[j] = 0;
		}
	}
}

void insert_around(char **buf, int i, int words, element *tmp)
{
	int j,k;

	k = 0;
	if (words < 7)
		special_case_of_buf(buf, i, words, tmp);
	else if (i <= 2 || i >= words - 3)
	{
		if (i == 0)
		{
			tmp->around_words = 4;
			tmp->around = malloc(sizeof(char *) * (4 + 1));
			for (j=0; j<=3; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
		else if (i == 1)
		{
			tmp->around_words = 5;
			tmp->around = malloc(sizeof(char *) * (5 + 1));
			for (j=0; j<=4; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
		else if (i == 2)
		{
			tmp->around_words = 6;
			tmp->around = malloc(sizeof(char *) * (6 + 1));
			for (j=0; j<=5; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
		else if (i == words - 1)
		{
			tmp->around_words = 4;
			tmp->around = malloc(sizeof(char *) * (4 + 1));
			for (j=words-4; j<=words-1; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
		else if (i == words - 2)
		{
			tmp->around_words = 5;
			tmp->around = malloc(sizeof(char *) * (5 + 1));
			for (j=words-5; j<=words-1; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
		else if (i == words - 3)
		{
			tmp->around_words = 6;
			tmp->around = malloc(sizeof(char *) * (6 + 1));
			for (j=words-6; j<=words-1; j++)
			{
				tmp->around[k] = strdup(buf[j]);
				k++;
			}
			tmp->around[k] = 0;
		}
	}
	else
	{
		tmp->around_words = 7;
		tmp->around = malloc(sizeof(char *) * (7 + 1));
		for (j = i - 3;j <= i + 3; j++)
		{
			tmp->around[k] = strdup(buf[j]);
			k++;
		}
		tmp->around[k] = 0;
	}
}

char *to_low(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + 32;
		i++;
	}
	return s;
}

int hash_insert(char **buf, char *fname, int words)
{
	char *key;
	char *tmp;
	int i,k,n;
	int count_cmp;
	int hash_result;

	i = 0;
	count_cmp = 0;
	while (buf[i])
	{
		tmp = strdup(buf[i]);
		tmp = to_low(tmp);
		key = ft_strtrim(tmp);
		free(tmp);
		n = 0;
		k = 0;
		while (n < table_size * table_size)
		{
			hash_result = (hash(key) + n) % table_size;
			if (ht[hash_result]->item.key == NULL)//빈 곳이라면 삽입
			{
				ht[hash_result]->item.key = key;
				ht[hash_result]->item.doc = strdup(fname);
				insert_around(buf, i, words, &(ht[hash_result]->item));
				ht[hash_result]->link = NULL;
				count_cmp++;
				break;
			}
			if (strncmp(ht[hash_result]->item.key, key, ft_strlen(key)) == 0
			&& strncmp(ht[hash_result]->item.key, key, ft_strlen(ht[hash_result]->item.key)) == 0)//충돌이 일어났지만 key값이 동일하다면 linked_list로 연결
			{
				list_pointer p;
				p = ht[hash_result];
				while (p->link)
					p = p->link;
				p->link = malloc(sizeof(list));
				p->link->item.key = key;
				p->link->item.doc = strdup(fname);
				insert_around(buf, i, words, &(p->link->item));
				p->link->link = NULL;
				count_cmp++;
				break;
			}
			//충돌이 일어났으며, key값이 다른 경우, +n^2에 저장 시도
			n = ++k;
			count_cmp++;
			n = n * n;
		}
		i++;
	}
	return count_cmp;
}

void put_words()
{
	char fname[]="doc000.txt";
	char **buf=0;
	char **key_seg[COUNT_DOC + 1];
	int i;
	int j;
	int total_cmp;

	total_cmp = 0;
	printf("Reading from files...\n");
	for (i=1;i<=COUNT_DOC;i++)
	{
		int_to_string(i, fname);
		printf("%s\n", fname);
		buf = put_in_buf(buf, i, fname);
		total_cmp += hash_insert(buf, fname, count_each_doc_words[i]);
		for (j=0;j<count_each_doc_words[i];j++)
			free(buf[j]);
		free(buf[j]);
		free(buf);
	}
	printf("Insert finished!\n");
	printf("Total number of documents : %d\n", COUNT_DOC);
	printf("Total number of words : %d\n", total_words);
	printf("Total number of comparison : %d\n", total_cmp);
}
