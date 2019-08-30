#ifdef KAF_LINUX
#define SLEEP sleep
#else
#define SLEEP Sleep
#endif
void play_intro(int x, int y)
{
	int i, j;
#ifdef KAF_LINUX
	int wait_time = 1;
#else
	int wait_time = 1000;
#endif
	attron(COLOR_PAIR(5));

	int level = y/2 - 8;

	i = level;
	j = x/2 - 32;
	mvprintw(i++, j, ".:::.    .:::.");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::   :::::'");
	mvprintw(i++, j, ":::::.:::::'  ");
	mvprintw(i++, j, "::::::::::'   ");
	mvprintw(i++, j, ":::::::::::.  ");
	mvprintw(i++, j, ":::::'  ':::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, "':::'    ':::'");
	flash();
	refresh();
	SLEEP(wait_time);

	i = level;
	j = x/2 - 15;
	mvprintw(i++, j, "  .::::::::.  ");
	mvprintw(i++, j, " :::::::::::: ");
	mvprintw(i++, j, " ::::'  ':::: ");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::.  .:::::");
	mvprintw(i++, j, "::::::::::::::");
	mvprintw(i++, j, "::::::::::::::");
	mvprintw(i++, j, ":::::'  ':::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, ":::::    :::::");
	mvprintw(i++, j, "':::'    ':::'");
	flash();
	refresh();
	SLEEP(wait_time);

	i = level;
	j = x/2 + 2;
	mvprintw(i++, j, "  .::::::::::.");
	mvprintw(i++, j, " ::::::::::::'");
	mvprintw(i++, j, " ::::'        ");
	mvprintw(i++, j, ":::::         ");
	mvprintw(i++, j, ":::::.        ");
	mvprintw(i++, j, ":::::::::::::.");
	mvprintw(i++, j, ":::::::::::::'");
	mvprintw(i++, j, ":::::'        ");
	mvprintw(i++, j, ":::::         ");
	mvprintw(i++, j, ":::::         ");
	mvprintw(i++, j, ":::::         ");
	mvprintw(i++, j, ":::::         ");
	mvprintw(i++, j, "':::'         ");
	flash();
	refresh();
	SLEEP(wait_time);

	i = level;
	j = x/2 + 19;
	attron(COLOR_PAIR(6));
	mvprintw(i++, j, "        ..::           ");
	mvprintw(i++, j, "     ..::::'        .:.");
	mvprintw(i++, j, "    ::::::.       .:::'");
	mvprintw(i++, j, "    ''''::::.   .::::' ");
	mvprintw(i++, j, "        '::::..:::::'  ");
	mvprintw(i++, j, "         ':::::::::'   ");
	mvprintw(i++, j, "     ....:::::::::'    ");
	mvprintw(i++, j, ".:::::::::::::::::.    ");
	mvprintw(i++, j, "'::::::::::::::::::.   ");
	mvprintw(i++, j, "              ':::::.  ");
	mvprintw(i++, j, "                :::::: ");
	mvprintw(i++, j, "                 ':::: ");
	mvprintw(i++, j, "                   ''  ");
	flash();
	refresh();
	SLEEP(wait_time*2);

	return;
}
