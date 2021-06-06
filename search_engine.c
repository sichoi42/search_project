#include "search_engine.h"

void count_words()
{
	FILE *fp;
	char fname[]="doc000.txt";
	char tmp[20];
	int i;

	for (i=1;i<=COUNT_DOC;i++)
	{
		int_to_string(i, fname);
		fp = fopen(fname, "r");
		while (fscanf(fp, "%s", tmp) == 1)
		{
			total_words++;
			count_each_doc_words[i]++;
		}
		fclose(fp);
	}
}

void print_table()
{
	int i;
	list_pointer p;

	i = 0;
	while (i < table_size)
	{
		p = ht[i];
		printf("ht[%d] : \n", i);
		if (p->item.key)
		{
			while (p)
			{
				printf("key : %s\n", p->item.key);
				printf("document : %s\n", p->item.doc);
				printf("around : ");
				for (int j=0;p->item.around[j];j++)
					printf("%s ", p->item.around[j]);
				printf("\n");
				p = p->link;
			}
		}
		printf("-----------------------------\n");
		i++;
	}
}

void free_table()
{
	int i, j;
	list_pointer p, tmp;

	for (i=0;i<table_size;i++)
	{
		p = ht[i];
		if (p->item.key == NULL)
			free(p);
		else
		{
			while (p)
			{
				for (j=0;p->item.around[j];j++)
					free(p->item.around[j]);
				free(p->item.around[j]);
				free(p->item.around);
				free(p->item.key);
				free(p->item.doc);
				tmp = p->link;
				free(p);
				p = tmp;
			}
		}
	}
	free(ht);
}

int main(void)
{
	count_words();
	table_size = find_next_prime((int)(total_words * 0.8));
	ht = malloc(sizeof(list_pointer) * table_size);
	for (int i = 0; i < table_size; i++)
	{
		ht[i] = malloc(sizeof(list));
		ht[i]->item.key = 0;
	}
	put_words();
	char c;
	char s[20];
	while (1)
	{
		printf("----------------------------\n");
		printf("p : print table, s : search key, q : exit\n");
		printf("----------------------------\n");
		printf("command->");
		scanf(" %c", &c);
		if (c == 'p')
			print_table();
		else if (c == 's')
		{
			printf("What you want to search : ");
			scanf("%s", s);
			size_t j;
			for (j=0;j<ft_strlen(s);j++)
				if (is_alpha(s[j]) == 0)
				{
					printf("invaild word\n");
					break;
				}
			if (j == ft_strlen(s))
				hash_search(s);
		}
		else if (c == 'q')
		{
			printf("exit program\n");
			break;
		}
		else
			printf("invalid command\n");
	}
	free_table();
}
