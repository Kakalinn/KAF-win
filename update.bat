del KefAirportFlug\kvl.exe
del KefAirportFlug\komur
del KefAirportFlug\out.fly
gcc KefAirportFlug\kvl.c -o KefAirportFlug\kvl

del newKAF\komur
del newKAF\brottfarir
del newKAF\out.fly
del newKAF\inn.fly
del newKAF\charlone.exe
del newKAF\kvl.exe
gcc newKAF\charlone.c -o newKAF\charlone -lpdcurses
copy KefAirportFlug\kvl.exe newKAF\kvl.exe
