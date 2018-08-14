del KefAirportFlug\kvl.exe
del KefAirportFlug\komur
del KefAirportFlug\out.fly
gcc KefAirportFlug\kvl.c -o KefAirportFlug\kvl
copy KefAirportFlug\kvl.exe newKAF\kvl.exe

del newKAF\komur
del newKAF\brottfarir
del newKAF\out.fly
del newKAF\inn.fly
del newKAF\charlone.exe
gcc newKAF\charlone.c -o newKAF\charlone -lpdcurses
