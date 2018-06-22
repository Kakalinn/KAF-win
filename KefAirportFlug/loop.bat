@ECHO OFF

echo %CD%

echo %date:~5% - %time:~0,-3% - Updating flights (Pressing a key in this window forces a refresh)
del komur
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur" -q
echo %date:~5% - %time:~0,-3% (Press F5 to refresh) > out.fly
kvl >> out.fly

start "" /MAX gvim -n -M out.fly -c "map <F5> :e %<CR>gg | set autoread | set noswapfile"

PING -n 31 127.0.0.1 > nul

:loop
echo %date:~5% - %time:~0,-3% - Updating flights (Pressing a key in this window forces a refresh)
del komur
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur" -q
echo %date:~5% - %time:~0,-3% (Press F5 to refresh) > out.fly
kvl >> out.fly
PING -n 31 127.0.0.1 > nul
goto loop
