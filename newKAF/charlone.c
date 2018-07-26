#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include "intro.h"

int main(int argc, char** argv)
{
	char c;
	int i, j, x, y, size, cur;
	char last_rfr[20];
	last_rfr[19] = '\0';

	WINDOW* win = initscr();
	curs_set(0);
	scrollok(win, 1);
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE,  COLOR_BLACK);
	init_pair(2, COLOR_GREEN,  COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED,    COLOR_BLACK);
	init_pair(5, COLOR_CYAN,   COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA,   COLOR_BLACK);
	init_pair(7, COLOR_BLACK,  COLOR_WHITE);
	bkgdset(COLOR_PAIR(1));

	getmaxyx(win, y, x);

	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi;


	int tmpl = strlen(argv[0]);
	char loc[tmpl];
	char batloc[tmpl*4];
	strcpy(loc, argv[0]);
	strcpy(batloc, argv[0]);
	for (i = tmpl - 1; i != -1; i--)
	{
		if (loc[i] == '\\' || loc[i] == '/')
		{
			break;
		}
	}
	i++;
	batloc[i] = 'r';
	loc[i++] = 'o';
	batloc[i] = 'f';
	loc[i++] = 'u';
	batloc[i] = 'r';
	loc[i++] = 't';
	batloc[i] = '.';
	loc[i++] = '.';
	batloc[i] = 'b';
	loc[i++] = 'f';
	batloc[i] = 'a';
	loc[i++] = 'l';
	batloc[i] = 't';
	loc[i++] = 'y';
	batloc[i] = '\0';
	loc[i++] = '\0';

	strcat(batloc, " \"");
	strcat(batloc, loc);
	batloc[strlen(batloc) - 8] = '\0';
	strcat(batloc, "\"");

	if (!CreateProcess(NULL, batloc, NULL, NULL, 1, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		return 9;
	}
	CloseHandle(pi.hThread);

	play_intro(x, y);


	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);




	FILE* fp = fopen(loc, "r");

	if (!fp)
	{
		printf("%s: fatal error: could not open file \"%s\"\n", argv[0], loc);
		printf("execution terminated\n");
		return 6;
	}

	char file[512][256];

	i = 0;
	j = 0;

	while (1)
	{
		c = fgetc(fp);

		if (c == EOF)
		{
			break;
		}
		else if (c == 10 || j == 255)
		{
			file[i][j] = '\0';
			i++;
			j = 0;
		}
		else
		{
			if (i == 1)
			{
				last_rfr[j] = c;
				last_rfr[j + 1] = '\0';
			}
			file[i][j++] = c;
		}
	}
	fclose(fp);
	fp = NULL;

	size = i;

	for (; i < 512; i++)
	{
		file[i][0] = '\0';
	}



	cur = 0;

	for (i = 0; i < y; i++)
	{
		attron(COLOR_PAIR(1));
		mvprintw(i, 0, "%s", file[cur + i]);
		clrtoeol();

		if (file[i][88] == 'L')
		{
			attron(COLOR_PAIR(5));
			mvprintw(i, 88, "%s", "Landed");
		}
		else if (file[i][88] == 'C' && file[i][89] == 'a')
		{
			attron(COLOR_PAIR(4));
			mvprintw(i, 88, "%s", "Cancelled");
		}
		else if (file[i][88] == 'C' && file[i][89] == 'o')
		{
			attron(COLOR_PAIR(2));
			mvprintw(i, 88, "%s", "Confirmed");
		}
		else if (file[i][88] == 'E')
		{
			attron(COLOR_PAIR(3));
			mvprintw(i, 88, "%s", "Expected");
		}

		if (i%2 == 1 && i > 1 && file[i][0] != '\0')
		{
			attron(COLOR_PAIR(6));
			mvaddch(i, 0, file[i][0]);
			mvaddch(i, 1, file[i][1]);
			mvaddch(i, 2, file[i][2]);
			mvaddch(i, 3, file[i][3]);
			mvaddch(i, 4, file[i][4]);
			mvaddch(i, 5, file[i][5]);
		}
	}
	refresh();


	while (1)
	{
		c = getch();

		switch (c)
		{
			case 'l':
				cur -= y/2*2 - 2;
				break;
			case 'h':
				cur += y/2*2 - 2;
				break;
			case 'J':
				cur += 4;
			case 'j':
				cur += 2;

				break;
			case 'K':
				cur -= 4;
			case 'k':
				cur -= 2;

				break;
			case ' ':
				attron(COLOR_PAIR(7));
				i = 1;
				j = 3;
				/*
				mvprintw(i++, j, " Last refresh: %s ", last_rfr);
				mvprintw(i++, j, "                                  ");
				mvprintw(i++, j, "                                  ");
				mvprintw(i++, j, "                                  ");
				mvprintw(i++, j, "                                  ");
				mvprintw(i++, j, "                                  ");
				mvprintw(i++, j, "                                  ");
				*/

				
				attron(COLOR_PAIR(7));
				for (i = 0; i < 65; i++)
				{
					mvaddch(4, i + 4, ' ');
					mvaddch(35, i + 4, ' ');
				}
				for (i = 5; i < 35; i++)
				{
					mvaddch(i, 4, ' ');
					mvaddch(i, 68, ' ');
				}

				attron(COLOR_PAIR(1));
				i = 5;
				j = 5;
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, " Press...                                                      ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...j to go down one line.                                    ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...k to go up one line.                                      ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...J to go down two lines.                                   ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...K to go up two lines.                                     ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...h to go down one screen.                                  ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...l to go up one screen.                                    ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...H to go to the top.                                       ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...L to go to the bottom.                                    ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...r to refresh.                                             ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...SPACE to open and close this help window.                 ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "  ...q twice to close window.                                  ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...Q to close the window.                                    ");
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...g to show the planes that are about to land.              ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i,   j, "                                                               ");
				attron(COLOR_PAIR(1)); mvprintw(i++, j, " Last refresh: %s", last_rfr);




				c = getch();
				while (c != ' ')
				{
					c = getch();
				}
				break;
			case 'r':;
					 attron(COLOR_PAIR(7));
					 mvprintw(y/3 - 1, x/4, "              ");
					 mvprintw(y/3,     x/4, "  REFRESHING  ");
					 mvprintw(y/3 + 1, x/4, "              ");
					 refresh();


					 refresh();
					 if (!CreateProcess(NULL, batloc, NULL, NULL, 1, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
					 {
						 return 9;
					 }
					 CloseHandle(pi.hThread);

					 WaitForSingleObject(pi.hProcess, INFINITE);
					 CloseHandle(pi.hProcess);

					 fp = fopen(loc, "r");

					 i = 0;
					 j = 0;

					 while (1)
					 {
						 c = fgetc(fp);

						 if (c == EOF)
						 {
							 break;
						 }
						 else if (c == 10 || j == 255)
						 {
							 file[i][j] = '\0';
							 i++;
							 j = 0;
						 }
						 else
						 {
							 if (i == 1)
							 {
								 last_rfr[j] = c;
								 last_rfr[j + 1] = '\0';
							 }
							 file[i][j++] = c;
						 }
					 }
					 fclose(fp);
					 fp = NULL;

					 size = i;

					 for (; i < 512; i++)
					 {
						 file[i][0] = '\0';
					 }

					 refresh();
					 break;
			case 'Q':
					 c = 'q';
					 break;
			case 'q':
					 c = getch();
					 break;
			case 'g':
					 for (cur = 2; cur < size; cur += 2)
					 {
						 if (file[cur + 1][88] != 'L' && (file[cur + 1][88] != 'C' || file[cur + 1][89] != 'a'))
						 {
							 int current_time = ((last_rfr[11] - '0')*10 + last_rfr[12])*60 + (last_rfr[14] - '0')*10 + last_rfr[15];
							 int compare_time = ((file[cur + 1][98] - '0')*10 + file[cur + 1][99])*60 + (file[cur + 1][101] - '0')*10 + file[cur + 1][102];

							 /*
							 attron(COLOR_PAIR(7));
							 mvprintw(10, 10, "            ");
							 mvprintw(11, 10, " Num1:      ");
							 mvprintw(12, 10, " Num2:      ");
							 mvprintw(13, 10, "            ");
							 mvprintw(11, 17, "%d", current_time);
							 mvprintw(12, 17, "%d", compare_time);
							 refresh();
							 getch();
							 */

							 if (current_time - compare_time < 120)
							 {
								 break;
							 }
						 }
					 }

					 cur -= 6;

					 if (cur > size - y)
					 {
						 cur = size - y;
					 }

					 break;
			case 'L':
					 cur = 0;
					 break;
			case 'H':
					 cur = size - y;
					 break;
		}
		if (c == 'q')
		{
			break;
		}

		if (cur < 0)
		{
			cur = 0;
		}
		else if (cur > size - y)
		{
			cur = size - y;
		}

		for (i = 0; i < y; i++)
		{
			attron(COLOR_PAIR(1));
			mvprintw(i, 0, "%s", file[cur + i]);
			clrtoeol();

			if (file[cur + i][88] == 'L')
			{
				attron(COLOR_PAIR(5));
				mvprintw(i, 88, "%s", "Landed");
			}
			else if (file[cur + i][88] == 'C' && file[cur + i][89] == 'a')
			{
				attron(COLOR_PAIR(4));
				mvprintw(i, 88, "%s", "Cancelled");
			}
			else if (file[cur + i][88] == 'C' && file[cur + i][89] == 'o')
			{
				attron(COLOR_PAIR(2));
				mvprintw(i, 88, "%s", "Confirmed");
			}
			else if (file[cur + i][88] == 'E')
			{
				attron(COLOR_PAIR(3));
				mvprintw(i, 88, "%s", "Expected");
			}

			if (i%2 == 1 && i + cur != 1 && i + cur != size - 1 && file[cur + i][0] != '\0')
			{
				attron(COLOR_PAIR(6));
				mvaddch(i, 0, file[cur + i][0]);
				mvaddch(i, 1, file[cur + i][1]);
				mvaddch(i, 2, file[cur + i][2]);
				mvaddch(i, 3, file[cur + i][3]);
				mvaddch(i, 4, file[cur + i][4]);
				mvaddch(i, 5, file[cur + i][5]);
			}
		}
		refresh();
	}


	clear();
	move(0, 0);
	refresh();
	endwin();



	return 0;
}
