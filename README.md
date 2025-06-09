Projektni zadatak iz predmeta Programski jezici 1 (2023/24)

U programskom jeziku C++ realizovati simulator saobraćaja. Program se mora moći kompajlirati, izvršiti i
testirati. Pravilno izvršiti modularizaciju. Dozvoljeno je korištenje samo standardnih biblioteka. Pridržavati
se principa OOP, SOLID principa i konvencija za programski jezik C++. Obezbijediti primjere za testiranje
implementiranih funkcionalnosti.

-> Definisati klasu za usmjereni graf kakvim se predstavlja saobraćajna mreža. Tipovi čvorova su: 1) čvor
lokacije, npr. grad, parking itd. – sve što može da služi kao polazna tačka ili odredište pri vožnji, 2) čvor
puta, kojim se predstavlja put ili segment puta, u jednom smjeru, između tačno dva čvora u grafu, kao i 3)
čvor raskrsnice, koji može da povezuje više puteva. Za svaki čvor puta se čuvaju sljedeći podaci: 1) dužina
puta u metrima, kojom se određuje težina između čvorova koje taj čvor puta povezuje, 2) maksimalna
dozvoljena brzina kretanja na putu i 3) maksimalan broj vozila na putu. Na čvor raskrsnice se vezuju čvorovi
puta, tako da se čvorovi puta koji imaju usmjerenu vezu ka čvoru raskrsnice smatraju ulaznim čvorovima,
dok se čvorovi puta prema kojima čvor raskrsnice ima usmjerene veze smatraju izlaznim čvorovima. U tom
kontekstu, za svaki par ulaznog i izlaznog čvora definiše se da li je moguće preći sa tog ulaznog čvora na
taj izlazni čvor, dužina u metrima koju je pri tome potrebno preći, kao i prosječna brzina kretanja vozila
koja zavisi od trenutnog broja vozila na raskrsnici. Takođe, treba biti moguće da se specificira i maksimalan
dozvoljen broj vozila na raskrsnici. Omogućiti serijalizaciju i deserijalizaciju grafa saobraćajne mreže.

-> Definisati klasu kojom se predstavljaju vozila. Vozilo se kreće od jedne lokacije ka drugoj. Svako vozilo
ima definisanu prosječnu brzinu kretanja kojom teži da se kreće na putu, s tim da je stvarna brzina kretanja
vozila, u nekom trenutku, ograničena maksimalnom brzinom kretanja na segmentu puta. Omogućiti da se
za vozilo može izračunati najbolja putanja kroz saobraćajnu mrežu, tako da se može minimizovati ili
pređena distanca ili utrošeno vrijeme, uzimajući u obzir dužine puteva i ograničenja brzine na putu.

-> Definisati klasu koja predstavlja simulaciju saobraćaja. Simulacija saobraćaja se odvija u tačno jednoj
saobraćajnoj mreži i u njoj učestvuje specificiran broj vozila, tako da svako vozilo ima sopstvenu polaznu
tačku i odredište (za veliki broj vozila, ovi parametri mogu biti nasumično odabrani na početku simulacije).
Svaka simulacija ima definisano vrijeme trajanja jednog koraka simulacije. U svakom koraku potrebno je
izračunati i pomjeriti svako vozilo, uzimajući u obzir njegovu brzinu kretanja, preostalu dužina puta, kao i
ograničenja na broj vozila na dijelovima puta. Ukoliko vozač treba preći u čvor koji je već popunjen, vozač
u datom koraku ostaje na trenutnom čvoru. Klasa za simulaciju treba da ima javni interfejs, koji omogućava
korisniku da izvrši jedan korak simulacije, da provjeri da li je simulacija završena, da vidi trenutno stanje
pojedinačnih vozila, kao i da vidi prosječno vrijeme putovanja između dvije specificirane lokacije.

