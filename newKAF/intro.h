void play_intro(int x, int y)
{
	int i, j;
	int wait_time = 1000;
	attron(COLOR_PAIR(5));

	int level = y/2 - 8;

	i = level;
	j = 1;
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
	Sleep(wait_time);

	i = level;
	j = 18;
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
	Sleep(wait_time);

	i = level;
	j = 35;
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
	Sleep(wait_time);

	i = level;
	j = 52;
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
	Sleep(wait_time*2);

	return;
}
