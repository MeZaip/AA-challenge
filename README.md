# Proiect AA - Subset Sum problem
## Descriere generala
Acest repository conține implementări și experimente destinate validării cercetării asupra problemei Subset Sum Problem, o problemă clasică din clasa NP-Complete. Codul inclus este utilizat pentru evaluarea corectitudinii și eficienței algoritmilor analizați în cadrul raportului asociat.

Scopul principal al acestui repository este de a susține, prin experimente și teste, concluziile teoretice și practice prezentate în documentația științifică.

## Suport teoretic
Suportul teoretic al lucrării este disponibil în următoarele forme:

- Versiunea online (LaTeX):
https://app.crixet.com/?u=f930bbbc-3de4-4c32-ab45-5c9a5f879c4b&pg=1&m=main.tex&d=7

- Versiune alternativă:
Documentul este disponibil și sub formă de PDF (atașat repository-ului).

Aceste materiale includ:

- definirea formală a problemei Subset Sum;
- demonstrația de NP-Hard / NP-Complete;
- descrierea algoritmilor analizați;
- metodologia de evaluare experimentală.

## Structura arhivei
```
.
├── raport.pdf
├── README.md
├── src
│   ├── Makefile
│   ├── backtracking.cpp
│   ├── dynamic.cpp
│   ├── dynamic_positives.cpp
│   └── genetic.cpp
└── tests
    ├── Makefile
    ├── generate-tests.py
    └── run_tests.sh
```

In folderul `src` sunt prezente mai multe metode de rezolvare a problemei
Subset Sum. `dynamic_positives.cpp` este o rezolvare in stil programare dinamica
foarte rapida, dar care functioneaza doar pentru numere pozitive si din acest
motiv executabilul este exclus la rularea automata a testelor.

## Rularea automata a testelor:
Se va folosi scriptul `tests/run_tests.sh` pentru a rula toate testele cu
cei 3 algoritmi ( backtracking, dynamic, genetic ), cu un timp
limita de **30 de secunde** pe test
```
cd tests
./run_tests.sh
```
> **Evaluarea solutiilor**: Solutiile de backtracking si dynamic vor afisa
solutia (subsetul) impreuna cu suma care s-a cautat. Singura diferenta o face 
algoritmul genetic care are timp limita de 5 secunde si va afisa solutia
cu suma cea mai apropiata de cea cautata la care a putut ajunge.
>
> In acelasi timp se va masura in timp executia fiecarui test si se va
afisa in milisecunde cat dureaza pentru comparare de performanta.


### Pasii pentru rulare manuala:
Pentru a compila si rula executabilele:
```
cd src
make
./<backtracking / dynamic / genetic> <file>
```
Pentru a genera testele:
```
cd tests
make
```
Iar pentru curatarea de executabile / teste se poate face `make clean` in
folderul aferent.

## Bibliografie
- https://www.geeksforgeeks.org/dsa/subset-sum-problem-dp-25/
- https://www.geeksforgeeks.org/dsa/subset-sum-problem/

## Autori
- Ioan Ursescu
- Ionuț Mihăilescu
- Mihut Matei

**Universitatea Națională de Știință și Tehnologie Politehnica București** - 
Facultatea de Automatică și Calculatoare