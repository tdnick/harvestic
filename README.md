# Harvestic

## Proiect dezvoltat de:

* [Iliescu Mihai-Nicolas](https://github.com/tdnick)
* [Stoian Andreea](https://github.com/stoianandreea)
* [Memenduf Alen-George](https://github.com/alenmemenduf)
* [Chiruț Veronica](https://github.com/veronicachirut)
* [Vultur Cristina](https://github.com/CristinaVultur)
* [Lupu Mihai-Răzvan](https://github.com/MikeDerWolf)

Parte a cursului de "Ingineria Programării", Facultatea de Matematică și Informatică, Universitatea din București, 2021.

Atenție! Codul sursă poate fi compilat doar pe un sistem de operare Linux. Recomandăm Ubuntu sau rularea prin [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

## Instrucțiuni de rulare

Depinzând de instalarea dvs. de Linux, este posibil să fie necesară actualizarea repo-urilor și instalarea a g++ și make.
```
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install g++
$ sudo apt install make
```

### Instalare Pistache
```
$ sudo add-apt-repository ppa:pistache+team/unstable
$ sudo apt update
$ sudo apt install libpistache-dev
```
### Pachete suplimentare
```
$ sudo apt install libssl-dev
$ sudo apt install libjsoncpp-dev
```
### Compilare și rulare
```
$ make
$ ./harvestic
```

## Instrucțiuni de folosire

Cererile GET, PUT și POST pot fi testate folosind ```curl``` sau prin intermediul unei aplicații dedicate (Postman).

De exemplu, pentru a vedea situația sistemului de irigație (interogarea câte unui furtun), putem rula
```
curl -XGET 'http://localhost:9080/map/:index'
```
unde parametrul index se află în intervalul 0 - numărul de furtunuri instalate.


