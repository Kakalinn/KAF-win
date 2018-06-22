@ECHO OFF

start gvim -n -M out.fly -c "map <F5> :e %<CR> | set autoread | set noswapfile | set lines=9999 columns=9999"

:loop
echo %date:~5% -%time:~0,-3% - Updating flights (Pressing a key in this window forces a refresh)
del komur
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur" -q
echo %date:~5% -%time:~0,-3% (Press F5 to refresh) > out.fly
stable >> out.fly
timeout /t 30 > nul
goto loop
