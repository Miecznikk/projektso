## Demon synchronizujący dwa katalogi
## Poprawne użycie programu:

 (1) ```Poprawna składnia programu = ./program -s [Sciezka] -d [Sciezka]```
 
 (2) ``` Działanie rekurencyjne programu= ./program -r -s [Sciezka] -d [Sciezka]```
 
 (3) ``` Ustawienie interwału synchronizacji= ./program -s [Sciezka] -d [Sciezka] -t [CZAS]```
 
 (4) ``` Ustawienie progu wagi plikow= ./program -s [Sciezka] -d [Sciezka] -w [LICZBA W MB]```
 
 (5) ``` Cała składnia= ./program -r -s [Sciezka] -d [Sciezka] -t [CZAS] -w [LICZBA W MB]```

### Opis opcji:

 -R : kopiowanie rekursywne

 ``` -t [CZAS]``` : czas uśpienia demona, jednostki (domyślnie sekundy):


 ```-w [LICZBA W MB]``` : rozmiar pliku:

### Opis opcji stosowanych w (2) przypadku użycia:

 * -F : powoduje natychmiastowe wybudzenie demona (synchronizację)
 * -S : bezpieczne zakończenie pracy demona (kończy synchronizację, jeśli rozpoczęta)
 * -K : natychmiastowe zakończenie pracy demona.


### Proste uzycie:
* ```./test.sh - towrzy katalogu w katalogu glownym wraz z plikami i uruchamia demona```
* ```./killdemon.sh - zabija demona```
* ```./synchdemon.sh - wymusza synchronizacje```
* ```./time_test.sh - Pokazuje roznice czasu miedzy kopiowaniem read/write i mmap // program znajduje sie w folderze Test_speed```

## INFO
Program domyślnie uzywa read/write do plikow ważacych mniej niz 10MB, dla plikow ktore waza wiecej uzywa mmapa. Domyślny czas ustawiony jest na 10s.
Program przechowuje logi w /var/log/local0, aby odseparować logi z programu od innych.
## AUTORZY
Projekt wykonali Filip Rybiński i Dominik Gudalewski
