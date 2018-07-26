powershell "'wget https://www.isavia.is/keflavikurflugvollur/flugaaetlun/komur?d=' + ((Get-Date).AddDays(1).ToString('yyyy-MM-dd'))"
