@ECHO OFF

echo %CD%

echo %date:~5% - %time:~0,-3% - Updating flights (Pressing a key in this window forces a refresh)
del komur
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur" -q
powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss') + ' (Press F5 to refresh)'" > out.fly
kvl komur >> out.fly

start "" /MAX gvim -n -M out.fly -c "map <F5> :e %<CR>gg | set autoread | set noswapfile"

TIMEOUT /T 30

:loop
echo %date:~5% - %time:~0,-3% - Updating flights (Pressing a key in this window forces a refresh)
del komur*
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur" -q
powershell "(Get-Date).ToString('yyyy-MM-dd HH:mm:ss') + ' (Press F5 to refresh)'" > out.fly
kvl komur >> out.fly
TIMEOUT /T 30
goto loop
