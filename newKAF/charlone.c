#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include "intro.h"

int main(int argc, char** argv)
{
	int c;
	int i, j, x, y, size[2], cur;
	int window_view = 0; /* 0 = komur, 1 = brottfarir */
	char last_rfr[20];
	last_rfr[19] = '\0';

	WINDOW* win = initscr();
	curs_set(0);
	scrollok(win, 1);
	keypad(win, 1);
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
	int loc_loc = i;
	batloc[i] = 'r';
	loc[i++] = 'i';
	batloc[i] = 'f';
	loc[i++] = 'n';
	batloc[i] = 'r';
	loc[i++] = 'n';
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



	loc[loc_loc + 0] = 'i';
	loc[loc_loc + 1] = 'n';
	loc[loc_loc + 2] = 'n';
	FILE* fp_brottfor = fopen(loc, "r");

	if (!fp_brottfor)
	{
		printf("%s: fatal error: could not open file \"%s\"\n", argv[0], loc);
		printf("execution terminated\n");
		return 6;
	}

	char file[2][512][256];

	i = 0;
	j = 0;

	while (1)
	{
		c = fgetc(fp_brottfor);

		if (c == EOF)
		{
			break;
		}
		else if (c == 10 || j == 255)
		{
			file[1][i][j] = '\0';
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
			file[1][i][j++] = c;
		}
	}
	fclose(fp_brottfor);
	fp_brottfor = NULL;

	size[1] = i;

	for (; i < 512; i++)
	{
		file[1][i][0] = '\0';
	}

	loc[loc_loc + 0] = 'o';
	loc[loc_loc + 1] = 'u';
	loc[loc_loc + 2] = 't';
	FILE* fp_komur = fopen(loc, "r");

	if (!fp_komur)
	{
		printf("%s: fatal error: could not open file \"%s\"\n", argv[0], loc);
		printf("execution terminated\n");
		return 6;
	}

	i = 0;
	j = 0;

	while (1)
	{
		c = fgetc(fp_komur);

		if (c == EOF)
		{
			break;
		}
		else if (c == 10 || j == 255)
		{
			file[0][i][j] = '\0';
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
			file[0][i][j++] = c;
		}
	}
	fclose(fp_komur);
	fp_komur = NULL;

	size[0] = i;

	for (; i < 512; i++)
	{
		file[0][i][0] = '\0';
	}



	cur = 0;

	for (i = 0; i < y; i++)
	{
		attron(COLOR_PAIR(1));
		mvprintw(i, 0, "%s", file[window_view][cur + i]);
		clrtoeol();

		if (file[window_view][i][88] == 'L')
		{
			attron(COLOR_PAIR(5));
			mvprintw(i, 88, "%s", "Landed");
		}
		else if (file[window_view][i][88] == 'C' && file[window_view][i][89] == 'a')
		{
			attron(COLOR_PAIR(4));
			mvprintw(i, 88, "%s", "Cancelled");
		}
		else if (file[window_view][i][88] == 'C' && file[window_view][i][89] == 'o')
		{
			attron(COLOR_PAIR(2));
			mvprintw(i, 88, "%s", "Confirmed");
		}
		else if (file[window_view][i][88] == 'E')
		{
			attron(COLOR_PAIR(3));
			mvprintw(i, 88, "%s", "Expected");
		}

		if (i%2 == 1 && i > 1 && file[window_view][i][0] != '\0')
		{
			attron(COLOR_PAIR(6));
			mvaddch(i, 0, file[window_view][i][0]);
			mvaddch(i, 1, file[window_view][i][1]);
			mvaddch(i, 2, file[window_view][i][2]);
			mvaddch(i, 3, file[window_view][i][3]);
			mvaddch(i, 4, file[window_view][i][4]);
			mvaddch(i, 5, file[window_view][i][5]);
		}
	}
	attron(COLOR_PAIR(7));
	mvprintw(y - 2, 0, "------'-------------------------------------------------------------------------------------------------------------------------");
	attron(COLOR_PAIR(1));
	mvprintw(y - 1, 0, "                                                                                                                                ");

	if (window_view == 0)
	{
		attron(COLOR_PAIR(2));
		mvprintw(y - 1, 8, "Arrivals");
	}
	else if (window_view == 1)
	{
		attron(COLOR_PAIR(5));
		mvprintw(y - 1, 8, "Departures");
	}

	attron(COLOR_PAIR(1));
	mvprintw(y - 1, 40, "Last update:");
	attron(COLOR_PAIR(4));
	printw(" %s", last_rfr);

	int percentage = (int)(100.0*cur/(size[window_view] - y) + 0.5);

	percentage == 0;
	if (percentage == 0)
	{
		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 98, "TOP");
	}
	else if (percentage >= 100)
	{
		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 98, "BOT");
	}
	else if (percentage < 10)
	{
		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 98, " %d%c", percentage, '%');
	}
	else
	{
		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 98, "%d%c", percentage, '%');
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
			case KEY_RIGHT:
			case 'J':
				cur += 4;
			case KEY_DOWN:
			case 'j':
				cur += 2;

				break;
			case KEY_LEFT:
			case 'K':
				cur -= 4;
			case KEY_UP:
			case 'k':
				cur -= 2;

				break;
			case ' ':
				attron(COLOR_PAIR(7));
				i = 1;
				j = 3;

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
				attron(COLOR_PAIR(2)); mvprintw(i++, j, "  ...u to change between arrivals and departures.              ");
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
			case 'u':
				window_view = (window_view + 1)%2;
				break;

			case 'r':
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

				loc[loc_loc + 0] = 'i';
				loc[loc_loc + 1] = 'n';
				loc[loc_loc + 2] = 'n';
				fp_brottfor = fopen(loc, "r");

				i = 0;
				j = 0;

				while (1)
				{
					c = fgetc(fp_brottfor);

					if (c == EOF)
					{
						break;
					}
					else if (c == 10 || j == 255)
					{
						file[1][i][j] = '\0';
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
						file[1][i][j++] = c;
					}
				}
				fclose(fp_brottfor);
				fp_brottfor = NULL;
				size[1] = i;

				for (; i < 512; i++)
				{
					file[1][i][0] = '\0';
				}


				loc[loc_loc + 0] = 'o';
				loc[loc_loc + 1] = 'u';
				loc[loc_loc + 2] = 't';
				fp_komur = fopen(loc, "r");

				i = 0;
				j = 0;

				while (1)
				{
					c = fgetc(fp_komur);

					if (c == EOF)
					{
						break;
					}
					else if (c == 10 || j == 255)
					{
						file[0][i][j] = '\0';
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
						file[0][i][j++] = c;
					}
				}
				fclose(fp_komur);
				fp_komur = NULL;

				size[0] = i;

				for (; i < 512; i++)
				{
					file[0][i][0] = '\0';
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
				if (window_view == 0)
				{
					for (cur = 2; cur < size[window_view]; cur += 2)
					{
						if (file[window_view][cur + 1][88] != 'L' && (file[window_view][cur + 1][88] != 'C' || file[window_view][cur + 1][89] != 'a'))
						{
							int current_time = ((last_rfr[11] - '0')*10 + last_rfr[12])*60 + (last_rfr[14] - '0')*10 + last_rfr[15];
							int compare_time = ((file[window_view][cur + 1][98] - '0')*10 + file[window_view][cur + 1][99])*60 + (file[window_view][cur + 1][101] - '0')*10 + file[window_view][cur + 1][102];
							if (current_time - compare_time < 120)
							{
								break;
							}
						}
					}
				}
				else if (window_view == 1)
				{
					for (cur = 2; cur < size[window_view]; cur += 2)
					{
						if (file[window_view][cur + 1][88] != 'D' && (file[window_view][cur + 1][88] != 'C' || file[window_view][cur + 1][89] != 'a'))
						{
							break;
						}
					}
				}

				cur -= 6;

				if (cur > size[window_view] - y)
				{
					cur = size[window_view] - y;
				}

				break;
			case 'L':
				cur = 0;
				break;
			case 'H':
				cur = size[window_view] - y;
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
		else if (cur > size[window_view] - y)
		{
			cur = size[window_view] - y;
		}
		if (cur%2 == 1)
		{
			cur--;
		}

		getmaxyx(win, y, x);

		clear();
		for (i = 0; i < y; i++)
		{
			attron(COLOR_PAIR(1));
			mvprintw(i, 0, "%s", file[window_view][cur + i]);
			clrtoeol();

			if (file[window_view][cur + i][88] == 'L')
			{
				attron(COLOR_PAIR(5));
				mvprintw(i, 88, "%s", "Landed");
			}
			else if (file[window_view][cur + i][88] == 'C' && file[window_view][cur + i][89] == 'a')
			{
				attron(COLOR_PAIR(4));
				mvprintw(i, 88, "%s", "Cancelled");
			}
			else if (file[window_view][cur + i][88] == 'C' && file[window_view][cur + i][89] == 'o')
			{
				attron(COLOR_PAIR(2));
				mvprintw(i, 88, "%s", "Confirmed");
			}
			else if (file[window_view][cur + i][88] == 'E')
			{
				attron(COLOR_PAIR(3));
				mvprintw(i, 88, "%s", "Expected");
			}
			else if (file[window_view][cur + i][88] == 'D')
			{
				attron(COLOR_PAIR(5));
				mvprintw(i, 88, "%s", "Departed");
			}
			else if (file[window_view][cur + i][88] == 'G' && file[window_view][cur + i][93] == 'c')
			{
				attron(COLOR_PAIR(6));
				mvprintw(i, 88, "%s", "Gate closed");
			}
			else if (file[window_view][cur + i][88] == 'G' && file[window_view][cur + i][93] == ' ')
			{
				attron(COLOR_PAIR(2));
				mvprintw(i, 88, "%s", "Go to gate");
			}
			else if (file[window_view][cur + i][88] == 'G' && file[window_view][cur + i][93] == 'o')
			{
				attron(COLOR_PAIR(3));
				mvprintw(i, 88, "%s", "Gate opened");
			}
			else if (file[window_view][cur + i][88] == 'F')
			{
				attron(COLOR_PAIR(4));
				mvprintw(i, 88, "%s", "Final call");
			}

			if (i%2 == 1 && i + cur != 1 && i + cur != size[window_view] - 1 && file[window_view][cur + i][0] != '\0')
			{
				attron(COLOR_PAIR(6));
				mvaddch(i, 0, file[window_view][cur + i][0]);
				mvaddch(i, 1, file[window_view][cur + i][1]);
				mvaddch(i, 2, file[window_view][cur + i][2]);
				mvaddch(i, 3, file[window_view][cur + i][3]);
				mvaddch(i, 4, file[window_view][cur + i][4]);
				mvaddch(i, 5, file[window_view][cur + i][5]);
			}
		}
		attron(COLOR_PAIR(7));
		mvprintw(y - 2, 0, "------'-------------------------------------------------------------------------------------------------------------------------");
		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 0, "                                                                                                                                ");

		if (window_view == 0)
		{
			attron(COLOR_PAIR(2));
			mvprintw(y - 1, 8, "Arrivals");
		}
		else if (window_view == 1)
		{
			attron(COLOR_PAIR(5));
			mvprintw(y - 1, 8, "Departures");
		}

		attron(COLOR_PAIR(1));
		mvprintw(y - 1, 40, "Last update:");
		attron(COLOR_PAIR(4));
		printw(" %s", last_rfr);

		int percentage = (int)(100.0*cur/(size[window_view] - y) + 0.5);

		percentage == 0;
		if (percentage == 0)
		{
			attron(COLOR_PAIR(1));
			mvprintw(y - 1, 98, "TOP");
		}
		else if (percentage >= 100)
		{
			attron(COLOR_PAIR(1));
			mvprintw(y - 1, 98, "BOT");
		}
		else if (percentage < 10)
		{
			attron(COLOR_PAIR(1));
			mvprintw(y - 1, 98, " %d%c", percentage, '%');
		}
		else
		{
			attron(COLOR_PAIR(1));
			mvprintw(y - 1, 98, "%d%c", percentage, '%');
		}


		refresh();
	}


	clear();
	move(0, 0);
	refresh();
	endwin();



	return 0;
}
