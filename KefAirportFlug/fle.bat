del komur
wget "https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur"
echo %date:~5% -%time:~0,-3% > out.fly
stable >> out.fly

