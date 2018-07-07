#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char time[8];
	char origin[32];
	char number[16];
	char airline[32];

	/*
	   0   = ekkert
	   'x' = aflyst
	   'c' = stadfest
	   'e' = aaetlud
	   'l' = lent
	   'u' = oksilgreint
    */
	char state;
	char stime[8];
} flight;


int flightcomp(const void* a, const void* b)
{
	char p[8], q[8];

	flight* r = (flight*)a;
	flight* s = (flight*)b;

	switch (r->state)
	{
		case 0:
		case 'x':
		case 'u':
			strcpy(p, r->time);
			break;
		default:
			strcpy(p, r->stime);

			if (r->time[0] == '0' && r->time[1] < '8' && r->stime[0] == '2')
			{
				p[0] = '.';
			}

			break;
	}
	
	switch (s->state)
	{
		case 0:
		case 'x':
		case 'u':
			strcpy(q, s->time);
			break;
		default:
			strcpy(q, s->stime);

			if (s->time[0] == '0' && s->time[1] < '8' && s->stime[0] == '2')
			{
				q[0] = '.';
			}

			break;
	}

	return strcmp(p, q);
}


int main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("No input\n");
		return 4;
	}

	int i, j, o;
	char c;
	flight l[1024];

	FILE* fp = fopen(argv[1], "r");

	char line[1024];

	/* FINDS THE START OF THE TABLE */
	while (1)
	{
		c = fgetc(fp);
		if (c == EOF)
		{
			break;
		}


		/* IGNORE WHITESPACES */
		for (; c == ' ' || c == '\t'; c = fgetc(fp));

		/* READ LINE TO BUFFER */
		for (i = 0; c != 10 && c != EOF; i++, c = fgetc(fp))
		{
			line[i] = c;
		}
		line[i] = '\0';

		//printf("%s\n", line);

		if (strcmp("<table class=\"table-schedule\">", line) == 0)
		{
			break;
		}
	}

	while (1)
	{
		c = fgetc(fp);
		if (c == EOF)
		{
			break;
		}


		/* IGNORE WHITESPACES */
		for (; c == ' ' || c == '\t'; c = fgetc(fp));

		/* READ LINE TO BUFFER */
		for (i = 0; c != 10 && c != EOF; i++, c = fgetc(fp))
		{
			line[i] = c;
		}
		line[i] = '\0';

		//printf("%s\n", line);

		if (strcmp("<tbody>", line) == 0)
		{
			break;
		}
	}

	while (c == 10)
	{
		c = fgetc(fp);
	}

	int flightc = 0;
	int itemc = 0;
	while (1)
	{
		c = fgetc(fp);
		if (c == EOF)
		{
			break;
		}


		/* IGNORE WHITESPACES */
		for (; c == ' ' || c == '\t'; c = fgetc(fp));

		/* READ LINE TO BUFFER */
		for (i = 0; c != 10 && c != EOF; i++, c = fgetc(fp))
		{
			line[i] = c;
		}
		line[i] = '\0';

		//printf("%s\n", line);

		if (line[1] == 't' && line[2] == 'r')
		{
			/* NOP */
		}

		else if (line[1] == 't' && line[2] == 'd')
		{
			if (itemc == 0)
			{
				l[flightc].time[0] = line[4];
				l[flightc].time[1] = line[5];
				l[flightc].time[2] = ':';
				l[flightc].time[3] = line[7];
				l[flightc].time[4] = line[8];
				l[flightc].time[5] = '\0';

				itemc = 1;
			}

			else if(itemc == 1)
			{
				for (i = 4; line[i] != '>'; i++);
				i++;

				for (o = i; line[i] != '<'; i++)
				{
					l[flightc].origin[i - o] = line[i];
				}
				l[flightc].origin[i - o] = '\0';

				itemc = 2;
			}

			else if(itemc == 2)
			{
				for (i = 4; line[i] != '<'; i++)
				{
					l[flightc].number[i - 4] = line[i];
				}
				l[flightc].number[i - 4] = '\0';

				itemc = 3;
			}

			else if(itemc == 3)
			{
				for (i = 4; line[i] != '>'; i++);

				for (i = i + 1; line[i] != '>'; i++);
				i++;

				for (o = i; line[i] != '<'; i++)
				{
					l[flightc].airline[i - o] = line[i];
				}
				l[flightc].airline[i - o] = '\0';

				itemc = 4;
			}

			else if(itemc == 4)
			{
				if (line[4] == '<')
				{
					l[flightc].state = 0;
				}

				else if (line[4] == '&')
				{
					l[flightc].state = 'e';

					l[flightc].stime[0] = line[31];
					l[flightc].stime[1] = line[32];
					l[flightc].stime[2] = line[33];
					l[flightc].stime[3] = line[34];
					l[flightc].stime[4] = line[35];
					l[flightc].stime[5] = '\0';
				}

				else if (line[4] == 'A')
				{
					l[flightc].state = 'x';
				}

				else if (line[4] == 'S')
				{
					l[flightc].state = 'c';

					l[flightc].stime[0] = line[18];
					l[flightc].stime[1] = line[19];
					l[flightc].stime[2] = line[20];
					l[flightc].stime[3] = line[21];
					l[flightc].stime[4] = line[22];
					l[flightc].stime[5] = '\0';
				}

				else if (line[4] == 'L')
				{
					l[flightc].state = 'l';

					l[flightc].stime[0] = line[9];
					l[flightc].stime[1] = line[10];
					l[flightc].stime[2] = line[11];
					l[flightc].stime[3] = line[12];
					l[flightc].stime[4] = line[13];
					l[flightc].stime[5] = '\0';
				}

				else
				{
					l[flightc].state = 'u';
				}

				itemc = 5;
			}

			else
			{
				/* NOP */
			}
		}

		else if (line[1] == '/' && line[2] == 't' && line[3] == 'r')
		{
			flightc++;
			itemc = 0;
		}

		if (strcmp("</tbody>", line) == 0)
		{
			break;
		}
	}

	qsort(l, flightc, sizeof(flight), flightcomp);

	for (j = 0; j < 128; j++)
	{
		if (j == 6)
		{
			putchar(':');
		}
		else
		{
			putchar('-');
		}
	}
	putchar(10);

	for (i = 0; i < flightc; i++)
	{
		printf("%s | ", l[i].time);

		for (j = 0; l[i].origin[j] != '\0'; j++)
		{
			putchar(l[i].origin[j]);
		}
		while (j != 32)
		{
			putchar(' ');
			j++;
		}

		for (j = 0; l[i].number[j] != '\0'; j++)
		{
			putchar(l[i].number[j]);
		}
		while (j != 16)
		{
			putchar(' ');
			j++;
		}

		for (j = 0; l[i].airline[j] != '\0'; j++)
		{
			putchar(l[i].airline[j]);
		}
		while (j != 32)
		{
			putchar(' ');
			j++;
		}

		switch (l[i].state)
		{
			case 'x':
				printf("Cancelled\n");
				break;
			case 'c':
				printf("Confirmed %s\n", l[i].stime);
				break;
			case 'l':
				printf("Landed    %s\n", l[i].stime);
				break;
			case 'e':
				printf("Expected  %s\n", l[i].stime);
				break;
			case 'u':
				printf("Unknown state. This is a bug..\n");
				break;
			case 0:
				printf("\n");
		}

		for (j = 0; j < 128; j++)
		{
			if (j == 6)
			{
				putchar(':');
			}
			else
			{
				putchar('-');
			}
		}
		putchar(10);
	}

	fclose(fp);
}
