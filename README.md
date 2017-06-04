# Teoria i inżynieria ruchu teleinformatycznego.

## Jak uruchomić
### Wymagania

* Program `Omnet++` w wersji `5.1.1` (dla innych wersji projekt może nie działać)
* Zainstalowane i skonfigurowane `gcc` i `g++` w środowisku `Omnet++`

### Uruchomienie projekt

* Uruchamiamy środowisko **Omnet++**
* Importujemy projekt *Import -> Project from Git* lub *Import -> Existing Project from workspace*
* Na projkecie *PPM -> Clean Project* następnie *PPM -> Build Project*
* Wybieramy symulacje (e.g. `PoissonDistribution.ned`), kolejno *PPM -> Run As -> 1 Omnet++ Simulation*

## Krótki dev guide

1. Tworzymy sobie jakiś moduł e.g. `PoissonGenerator` (kazdy modul, który chcemy umieścić na symulacji powinien dziedziczyć po public cSimpleModule i być zdefiniowany w pliku `*.cpp` dla modułu e.g. pod konstruktorem piszemy `Define_Module(PoissonGenerator)`. 

2. Definiujemy odpowiednie zmienne i metody dla klasy (`initialize()`, `handleMessage()` ect. Pamietamy o rejstracji sygnału/eventu  w `initialize()`).

3. Tworzymy plik PoissonGenerator.ned (plik definiujący  parametry, wejścia/wyjścia ect. modułu dla symulacji) - dzięki temu moduł będzie dostępny z okna wyboru modułów (`Submodules`) przy tworzeniu symulacji.

4. Tworzymy plik z symulacją e.g. `PoissonDistrubution.ned` (przeciągamy z okna po prawej wybieramy Network z 
grupy Types, kolejno do sieci wrzucamy nasze moduły z grupy `Submodules` (e.g. `PoissonGenerator`) "do" sieci.

## Struktura projektu 
<pre>
.
├── generator                       - generatory Poisson/OnOff/MMP ect.
│   ├── BasicGenerator.cpp          - klasa bazowa (parent) dla generatorów
│   ├── BasicGenerator.h
│   ├── PoissonGenerator.cpp        - generator Poissona: BasicGenerator
│   ├── PoissonGenerator.h
│   └── ... 
├── Makefile
├── message                          
│   └── Message.msg                 - przesyłana wiadomość, omnet generuje Message_m.* z tego 
├── object                         
│   ├── Sink.cpp
│   ├── Sink.h                      
│   └── ...
├── omnetpp.ini                     - konfiguracja naszych symulacji (*.ned), np. ograniczenie czasowe
├── out
├── PoissonDistribution.ned         - przykładowa symulacja przy użyciu `PoissonGenerator` 
├── ...                             
├── README.md                       - ten plik 
├── results							- folder z danymi, wykresami ect. tworzynymi z naszych symulacji
│   ├── General-#0.vci
│   └── General-#0.vec
└── submodules                      - moduły tworzone dla symulacji. Parametry ustawiamy własnie tu 
    ├── BasicGenerator.ned          - moduł dla BasicGenerator
    ├── PoissonGenerator.ned        - moduł dla PoissonGenerator (tu ustawiamy wartość lambda)
    ├── Sink.ned                    - moduł dla Sink
    └── ...						

