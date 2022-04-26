Demon synchronizujący dwa katalogi

(1) Poprawna składnia programu = ./program -s [Sciezka] -d [Sciezka]
(2) Działanie rekurencyjne programu= ./program -r -s [Sciezka] -d [Sciezka]
(3) Ustawienie interwału synchronizacji= ./program -s [Sciezka] -d [Sciezka] -t [CZAS]

Program domyślnie uzywa read/write do plikow ważacych mniej niz 10MB, dla plikow ktore waza wiecej uzywa mmapa.
Program przechowuje logi w /var/log/local0, aby odseparować logi z programu od innych.
