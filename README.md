## Demon synchronizujący dwa katalogi
## Poprawne użycie programu:

 (1) ```Poprawna składnia programu = ./program -s [Sciezka] -d [Sciezka]```
 
 (2) ``` Działanie rekursywne programu= ./program -r -s [Sciezka] -d [Sciezka]```
 
 (3) ``` Ustawienie interwału synchronizacji= ./program -s [Sciezka] -d [Sciezka] -t [CZAS]```
 
 (4) ``` Ustawienie progu wagi plikow= ./program -s [Sciezka] -d [Sciezka] -w [LICZBA W MB]```
 
 (5) ``` Cała składnia= ./program -r -s [Sciezka] -d [Sciezka] -t [CZAS] -w [LICZBA W MB]```

### Opis opcji:

 ```-r``` : kopiowanie rekursywne

 ``` -t [CZAS]``` : czas uśpienia demona, jednostki (domyślnie sekundy):


 ```-w [LICZBA W MB]``` : rozmiar pliku:

### Proste uzycie:
* ```./test.sh - tworzy katalogi w katalogu glownym wraz z plikami i uruchamia program```
* ```./killdemon.sh - zamyka demona ktory pracuje w tle```
* ```./synchdemon.sh - wymusza synchronizacje```
* ```./time_test.sh - Test który ma na celu zobrazowanie uzytkownikowi jaka jest roznica miedzy kopiowaniem pliku za pomoca mmpa a read/write.// program znajduje sie w folderze Test_speed```

## INFO
Program domyślnie uzywa read/write do plikow ważacych mniej niz 10MB, dla plikow ktore waza wiecej uzywa mmapa. Domyślny interwał synchronizacji ustawiony jest na 10s.
Program przechowuje logi w /var/log/local0, aby odseparować logi z programu od innych.
## AUTORZY
Projekt wykonali Filip Rybiński i Dominik Gudalewski
