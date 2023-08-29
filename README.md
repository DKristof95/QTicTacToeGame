# QTicTacToeGame
A Qt project about a tricky TicTacToe game.

# Készítette
Doszkocs Kristóf

E-mail: doszkocs.kristof@gmail.com

Csoportszám: 4

# Feladat
## Kiszúrós amőba
Készítsünk programot, amellyel a közismert amőba játék következő változatát
játszhatjuk.

Adott egy 𝑛 × 𝑛 -es tábla, amelyen a két játékos felváltva X, illetve O jeleket helyez
el. Csak olyan mezőre tehetünk jelet, amely még üres. A játék akkor ér véget, ha
betelik a tábla (döntetlen), vagy valamelyik játékos kirak 5 egymással szomszédos
jelet vízszintesen, függőlegesen vagy átlósan. A program minden lépésnél jelezze,
hogy melyik játékos következik, és a tábla egy üres mezőjét kijelölve helyezhessük
el a megfelelő jelet.

A kiszúrás a játékban az, hogy ha egy játékos eléri a 3 egymással szomszédos jelet,
akkor a program automatikusan törli egy jelét egy véletlenszerűen kiválasztott
pozícióról (nem biztos, hogy a hármasból), ha 4 egymással szomszédos jelet ér el,
akkor pedig kettőt.

A program biztosítson lehetőséget új játék kezdésére a táblaméret megadásával
(6 × 6, 10 × 10, 14 × 14), valamint az aktuális játék mentésére és egy korábban
elmentett játék betöltésére. Ismerje fel, ha vége a játéknak, és jelenítse meg,
melyik játékos győzött, illetve azt is, ha döntetlen lett a vége, majd automatikusan
kezdjen új játékot.

# A feladat elemzése
A játékban két játékos vesz részt, de az alkalmazás szempontjából mindig csak egy felhasználó van. Ő hétféle tevékenységet végezhet.

![image](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/e4a724e4-9d13-4fa2-957d-2f8b94c7041e)

A felhasználói tevékenységek során az alábbi esetek következhetnek be:

![image](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/e4a96f0f-be07-4360-a7d4-6f48e8aef7d2)

# Architektúra
Az alkalmazást három rétegű (nézet-modell-perzisztencia) architektúrában valósítjuk 
meg. A nézet a játéktáblát megjelenítő ablak mellett két dialógus ablakot is tartalmaz a 
mentés, illetve a betöltés párbeszédhez. 

![02](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/a0c296d7-1605-452c-8e73-3d32fea51c85)

# Perzisztencia
A korábban elmentett, legfeljebb 5 játékállást külön-külön tároljuk. Az adatelérési réteg 
osztálya ezen játékállásokhoz történő hozzáférést biztosítja a modell számára úgy, hogy 
a modellnek nem kell tudnia arról, hogy milyen módon történik a tárolás.

## Osztálydiagram

![03](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/98a5c014-7805-48bd-815a-f89690e0fb68)

## Metódusok
Az adatelérési réteg négy fő metódust kínál. 

A loadGame() egy megadott sorszámú állományból (ezt adjuk meg az első 
paraméterével) tud betölteni egy játékállást (ez a második paraméter). 

A saveGame() egy megadott méretű (ezt adjuk meg az első paraméterrel), megadott 
sorszámú állományba (ezt adjuk meg a második paraméterrel) tud elmenteni egy 
játékállást (ez a harmadik paraméter). 

A saveGameList() az elmentett állományokat adja vissza. 

Az isAvaible() rendelkezésre állás lekérdezéséért felel. 

# Modell
A modell segítségével tároljuk el az aktuális állást. A modell publikus metódusait a 
nézet hívja, a modell szignálok segítségével üzen a nézetnek és vezérli azt.

![04](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/b24dcd6d-e46e-4f6a-b704-266545b47f45)

## Adattagok
Az adattagok a játékállást írják le: hányadik lépésnél járunk (_stepNumber), melyik a 
jelenlegi játékos (_currentPlayer), a játéktábla reprezentációja (_gameTable), az 
adathozzáférés módja (_dataAccess), a játéktábla mérete (_boardSize) és az egyes 
játékosok mezői (_xList és _oList). 

## Metódusok
A modell metódusai a játék indításáért (newGame()), léptetéséért (stepGame()), a 
mentésért és a betöltésért (saveGame() és loadGame()) felelnek. 

Getterek a saveGameList() (mentett játékok lekérdezése), a stemNumber() (lépések 
számának lekérdezése), a currentPlayer() (aktuális játékos lekérdezése), a getField() 
(játékmező lekérdezése) és a getBoardSize() (pálya méretének lekérdezése). 

A setBoardSize() setter, a pálya méretét állítja be. 

A checkGame() metódus ellenőrzi a pályát és a játékosok mezői által dönti el, hogy 
vége van-e a játéknak, vagy, hogy el kell-e venni az aktuális játékostól mezőket. Ehhez 
a find3To5Adjacent() metódust használja fel, ami visszaadja egy párban, hogy van-e a 
két játékosnak 3 és 5 közé eső egymás melletti mezője.

# Nézet

## Felhasználói felület terve
Főablak:

![05](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/ea88fc0f-8aef-4b1d-bec2-ee3e939fe3ef)

Mentés és betöltés:

<img width="857" alt="06" src="https://github.com/DKristof95/QTicTacToeGame/assets/139268216/0ba81245-a2c8-4ea8-b304-a410ed834a75">

Beállítások: 

![07](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/08b7dc80-ce50-4219-94fe-8f00dcc5d70e)

## Osztálydiagram

![08](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/0a58c8fe-aae4-47af-87ee-dcaf93c50dac)

![09](https://github.com/DKristof95/QTicTacToeGame/assets/139268216/4a3f53dc-f905-4413-a286-816bc51eb6f5)

## Vezérlők és adattagok
A főablak osztályának adattagjai a menü megjelenítésére szolgáló elemeket tárolják. 

A TicTacToeWidget adattagjai a grafikai elemeket, a tábla méretét tartalmazzák, 
valamint egy-egy hivatkozást a beállítás, a mentés és betöltés dialógus ablakokra és a 
modellre. 

A SaveGameWidget, LoadGameWidget és ConfigureGameWidget adattagjai a 
szükséges gombok és vezérlők. 

## Metódusok
A főablak és a MyMenu metódusai azt a célt szolgálnák, hogy ne tűnjön el az aktuális 
játékos kiírása a statusBarból, ha a kurzort a menü fölé visszük, de nem működnek. 

A SaveGameWidget okButtonEnabler szignálja és slotja teszi lehetővé, hogy a mentési 
és betöltési dialógusban az OK gomb addig ne legyen kattintható, amíg ki nem jelölünk 
egy mentési helyet. 

A ConfigureGameWidget newSize() metódusa beálltja a tábla új méretét. 

A TicTacToeWidget metódusai felelnek a grafikus elemek kirajzolásáért és frissítéséért, 
reagálva a modell eseményeire és a különböző dialógusablakok megjelenítéséért.

## Eseménykezelés

# Végfelhasználói tesztesetek:
