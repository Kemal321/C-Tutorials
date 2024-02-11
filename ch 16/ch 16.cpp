#include <iostream>
#include <vector>

int main()
{/*
    std::vector primes{ 2, 3, 5, 7, 11 };
    std::cout << primes[11]<< '\n';*/
    std::vector primes{ 2 , 3, 5, 7, 11 };
    std::cout << primes.at(19) << '\n'; // -> �stisna f�rlatcek 

    return 0;
}
/*

16.1 � Konteynerlara ve dizilere giri�
--------------------------------------
De�i�ken �l�eklenebilirlik sorunu
---------------------------------
30 ��rencinin s�nav sonu�lar�n� kaydetmek ve s�n�f�n ortalama puan�n� hesaplamak istedi�imiz bir senaryoyu d���n�n. Bunu yapmak i�in 30 de�i�kene
ihtiyac�m�z olacak. Bu de�i�kenleri �u �ekilde tan�mlayabiliriz:

                // 30 tam say� de�i�keni tahsis edin (her birinin farkl� bir ad� var)
                int testScore1 {};
                int testScore2 {};
                int testScore3 {};
                // ...
                int testScore30 {};
Tan�mlanacak �ok fazla de�i�ken var! Ve s�n�f�n ortalama puan�n� hesaplamak i�in ��yle bir �ey yapmam�z gerekecek:

int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
Bu sadece �ok fazla yaz�, ayn� zamanda �ok tekrarlay�c�d�r (ve numaralardan birini yanl�� yazmak ve fark etmemek o kadar da zor olmazd�). 
Ve bu de�erlerin her biriyle (�rne�in, onlar� ekrana yazd�rmak gibi) bir �eyler yapmak istiyorsak, bu de�i�ken isimlerini tekrar tekrar girmemiz 
gerekecek.

�imdi, s�n�fa yeni eklenen bir ��renciyi bar�nd�racak �ekilde program�m�z� de�i�tirmemiz gerekti�ini s�yleyelim. T�m kod taban�n� taray�p ilgili
yerlere manuel olarak testScore31 eklememiz gerekecek. Mevcut kodu her de�i�tirdi�imizde, yeni hatalar olu�turma riskimiz vard�r. �rne�in,
ortalaman�n hesaplanmas�ndaki b�leni 30'dan 31'e g�ncellemeyi unutmak o kadar da zor olmazd�!

Ve bu sadece 30 de�i�kenle. Y�zlerce veya binlerce nesnemiz oldu�u durumu d���n�n. Ayn� t�rden birka� nesneye ihtiya� duydu�umuzda, bireysel
de�i�kenlerin tan�mlanmas� basit�e �l�eklenmez.

Verilerimizi bir struct�n i�ine koyabiliriz:

                struct testScores
                {
                // 30 tam say� de�i�keni tahsis edin (her birinin farkl� bir ad� var)
                int score1 {};
                int score2 {};
                int score3 {};
                // ...
                int score30 {};
                }
Bu, puanlar�m�z i�in ek bir organizasyon sa�lar (ve onlar� daha kolay bir �ekilde fonksiyonlara ge�memizi sa�lar), ancak temel sorunu ��zmez:
hala her test puan� nesnesini bireysel olarak tan�mlamam�z ve eri�memiz gerekiyor.

Tahmin etmi� olabilirsiniz, C++'�n yukar�daki zorluklara ��z�mleri var. Bu b�l�mde, bu ��z�mlerden birini tan�taca��z. Ve takip eden b�l�mlerde,
bu ��z�m�n baz� di�er varyantlar�n� inceleyece�iz.

Konteynerlar
------------
Bir d�zine yumurta almak i�in markete gitti�inizde, muhtemelen 12 yumurtay� bireysel olarak se�miyor ve sepetinize koymuyorsunuz (de�il mi?).
Bunun yerine, muhtemelen tek bir yumurta kartonu se�iyorsunuz. Karton, belirli bir say�da yumurta i�eren bir t�r konteynerdir (muhtemelen 6, 12 
veya 24). �imdi kahvalt�l�k gevrekleri d���n�n, bir�ok k���k gevrek par�as� i�erir. T�m bu par�alar� mutfak dolab�n�zda bireysel olarak saklamak
istemezsiniz! Gevrek genellikle bir kutuda gelir, bu da ba�ka bir konteynerdir. Ger�ek hayatta s�rekli olarak konteynerlar� kullan�yoruz ��nk� bir 
koleksiyonu y�netmeyi kolayla�t�r�rlar.

Programlamada da konteynerlar var, (potansiyel olarak b�y�k) nesne koleksiyonlar�n� olu�turmay� ve y�netmeyi kolayla�t�r�r. Genel programlamada, 
bir konteyner, isimsiz nesnelerin (elementler olarak adland�r�l�r) bir koleksiyonu i�in depolama sa�layan bir veri tipidir.

Anahtar i�g�r�; Genellikle, ilgili de�erlerle �al��mam�z gerekti�inde konteynerlar� kullan�r�z.

Anla��lan o ki, zaten bir konteyner t�r�n� kullan�yorsunuz: dizeler! Bir dize konteyneri, bir karakter koleksiyonu i�in depolama sa�lar,
bu da metin olarak ��kt� alabilir:

                #include <iostream>
                #include <string>

                int main()
                {
                    std::string name{ "Alex" }; // dizeler, karakterler i�in bir konteynerd�r
                    std::cout << name; // dizemizi bir karakter dizisi olarak ��kt� al

                    return 0;
                }

Bir konteyn�r�n elemanlar� isimsizdir
-------------------------------------
Konteyn�r nesnesinin kendisi genellikle bir isme sahip olur (aksi takdirde nas�l kullan�r�z?), ancak bir konteyn�r�n elemanlar� isimsizdir. 
Bu, istedi�imiz kadar �ok eleman� konteyn�r�m�za koyabilmemiz i�in b�yledir, her bir elemana benzersiz bir isim vermek zorunda kalmadan!
�simlendirilmemi� elemanlar�n olmamas� �nemlidir ve konteyn�rlar� di�er veri yap�lar�ndan ay�ran �ey budur. Bu y�zden d�z yap�lar (yukar�daki
testScores yap�m�z gibi sadece bir veri �yesi koleksiyonu olanlar) genellikle konteyn�r olarak kabul edilmez -- veri �yeleri benzersiz isimler
gerektirir.

Yukar�daki �rnekte, string konteyn�r�m�z�n bir ismi var (name), ancak konteyn�r�n i�indeki karakterlerin ('A', 'l', 'e', 'x') ismi yok.

Peki, elemanlar kendileri isimsizse, onlara nas�l eri�iriz? Her konteyn�r, elemanlar�na eri�mek i�in bir veya daha fazla y�ntem sa�lar -- 
ancak tam olarak nas�l, konteyn�r�n t�r�ne ba�l�d�r. Bu konudaki ilk �rne�imizi bir sonraki dersimizde g�rece�iz.

Anahtar ��g�r�; Bir konteyn�r�n elemanlar� kendi isimlerine sahip de�ildir, b�ylece konteyn�r�n istedi�imiz kadar �ok elemana sahip olmas�n�
sa�lar�z, her bir elemana benzersiz bir isim vermek zorunda kalmadan. Her konteyn�r, bu elemanlara eri�mek i�in bir y�ntem sa�lar,
ancak nas�l oldu�u, konteyn�r�n belirli t�r�ne ba�l�d�r.

Bir konteyn�r�n uzunlu�u
------------------------
Programlamada, bir konteyn�r�n eleman say�s� genellikle uzunlu�u (veya bazen say�s�) olarak adland�r�l�r.Stringler i�in a�a��daki �rnek:

                #include <iostream>
                #include <string>

                int main()
                {
                    std::string name{ "Alex" };
                    std::cout << name << " has " << name.length() << " characters\n";

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Alex has 4 characters
C++'da, bir konteyn�r�n eleman say�s� i�in genellikle boyut ( size ) terimi de kullan�l�r. Bu, nomenklat�rde talihsiz bir se�imdir, ��nk� �boyut� 
terimi ayn� zamanda bir nesnenin kulland��� bellek bayt say�s�na (sizeof operat�r� taraf�ndan d�nd�r�l�r) da i�aret edebilir.

Konteyn�r�n eleman say�s�na at�fta bulunurken �uzunluk� terimini tercih ederiz ve bir nesnenin gerektirdi�i depolama miktar�na at�fta bulunmak i�in
�boyut� terimini kullan�r�z.

Konteyn�r ��lemleri
-------------------
Bir an i�in yumurta kartonumuza geri d�nelim. B�yle bir kartonla ne yapabilirsiniz? �lk olarak, bir yumurta kartonu edinebilirsiniz.
Yumurta kartonunu a�abilir ve bir yumurta se�ebilir, ard�ndan o yumurtayla istedi�inizi yapabilirsiniz. Kartondan mevcut bir yumurtay� ��karabilir
veya bo� bir alana yeni bir yumurta ekleyebilirsiniz. Ayr�ca kartondaki yumurta say�s�n� da sayabilirsiniz.

Benzer �ekilde, konteyn�rlar genellikle a�a��daki i�lemlerin �nemli bir alt k�mesini uygular:

*- Bir konteyn�r olu�turun (�r. bo�, baz� ba�lang�� elemanlar� i�in depolama alan�yla, bir de�er listesinden).
*- Elemanlara eri�im (�r. ilk eleman� al, son eleman� al, herhangi bir eleman� al).
*- Elemanlar� ekle ve ��kar.
*- Konteyn�rdaki eleman say�s�n� al.

Konteyn�rlar ayr�ca, eleman koleksiyonunu y�netmeye yard�mc� olan di�er i�lemleri (veya yukar�dakilerin varyasyonlar�n�) sa�layabilir.

Modern programlama dilleri genellikle �e�itli farkl� konteyn�r t�rleri sa�lar. Bu konteyn�r t�rleri, hangi i�lemleri ger�ekten destekledikleri ve
bu i�lemlerin ne kadar performansl� oldu�u a��s�ndan farkl�l�k g�sterir. �rne�in, bir konteyn�r t�r�, konteyn�rdaki herhangi bir elemana h�zl�
eri�im sa�layabilir, ancak elemanlar�n eklenmesini veya ��kar�lmas�n� desteklemeyebilir. Ba�ka bir konteyn�r t�r�, elemanlar�n h�zl� bir �ekilde 
eklenmesini ve ��kar�lmas�n� sa�lar, ancak yaln�zca elemanlara s�ral� bir �ekilde eri�ime izin verir.

Her konteyn�r�n bir dizi g��l� ve zay�f y�n� vard�r. ��zmeye �al��t���n�z g�rev i�in do�ru konteyn�r t�r�n� se�mek, hem kodun bak�m�n� hem de genel
performans� �zerinde b�y�k bir etkisi olabilir. Bu konuyu ileride bir dersimizde daha ayr�nt�l� olarak tart��aca��z.

Element t�rleri
---------------
�o�u programlama dilinde (C++ dahil), konteynerlar homojendir, yani bir konteynerin elemanlar�n�n ayn� t�rde olmas� gerekir.

Baz� konteynerlar �nceden belirlenmi� bir eleman t�r� kullan�r (�rne�in, bir string genellikle char elemanlar�na sahiptir), ancak daha s�k olarak
eleman t�r�, konteyner�n kullan�c�s� taraf�ndan belirlenebilir. C++'da, konteynerlar genellikle s�n�f �ablonlar� olarak uygulan�r, b�ylece 
kullan�c� istenen eleman t�r�n� bir �ablon t�r� arg�man� olarak sa�layabilir. Bu konuda bir �rne�i bir sonraki derste g�rece�iz.

Bu, konteynerlar� esnek hale getirir, ��nk� tutmak istedi�imiz her eleman t�r� i�in yeni bir konteyner s�n�f� olu�turmam�z gerekmez. Bunun yerine,
sadece istenen eleman t�r� ile s�n�f �ablonunu �rneklendiririz ve haz�r�z.

Bir not olarak Homojen bir konteyner�n z�tt�, heterojen bir konteynerdir, bu da elemanlar�n farkl� t�rlerde olmas�na izin verir.
Heterojen konteynerlar genellikle betik dilleri (Python gibi) taraf�ndan desteklenir.

C++'da Konteynerlar
-------------------
Konteynerlar k�t�phanesi, C++ standart k�t�phanesinin bir par�as�d�r ve baz� ortak konteyner t�rlerini uygulayan �e�itli s�n�f t�rlerini i�erir.
Bir konteyner� uygulayan bir s�n�f t�r� bazen bir konteyner s�n�f� olarak adland�r�l�r. Konteynerlar k�t�phanesindeki konteynerlar�n tam listesi 
https://en.cppreference.com/w/cpp/container da belgelenmi�tir.

C++'da "konteyner" tan�m�, genel programlama tan�m�ndan daha dar bir anlama gelir. Sadece Konteynerlar k�t�phanesindeki s�n�f t�rleri C++'da
konteyner olarak kabul edilir. Genel olarak konteynerlardan bahsederken "konteyner" terimini kullanaca��z ve Konteynerlar k�t�phanesinin bir 
par�as� olan konteyner s�n�f t�rlerinden �zellikle bahsederken "konteyner s�n�f�" terimini kullanaca��z.

Sa�lanan konteyner s�n�flar� aras�nda, std::vector ve std::array en �ok kullan�lanlard�r ve dikkatimizin b�y�k �o�unlu�unu bu konulara 
odaklayaca��z. Di�er konteyner s�n�flar� genellikle daha �zel durumlarda kullan�l�r.

Dizilere Giri�
--------------
Bir dizi, bir dizi de�eri ard���k olarak (yani her eleman�n biti�ik bir bellek konumuna yerle�tirildi�i, arada bo�luk olmadan) depolayan bir 
konteyner veri t�r�d�r. Diziler, herhangi bir elemana h�zl�, do�rudan eri�im sa�lar. Kavramsal olarak basit ve kullan�m� kolayd�rlar, bu da onlar�
bir dizi ilgili de�er olu�turup �al��mam�z gerekti�inde ilk se�enek yapar.

C++'da �� ana dizi t�r� vard�r: (C tarz�) diziler, std::vector konteyner s�n�f� ve std::array konteyner s�n�f�.

(C tarz�) diziler C dilinden miras al�nm��t�r. Geriye d�n�k uyumluluk i�in, bu diziler temel veri t�rleri gibi �ekirdek C++ dilinin bir par�as� 
olarak tan�mlan�r. C++ standard� bunlara "diziler" der, ancak modern C++'da bunlar genellikle std::array'den ay�rt etmek i�in C dizileri veya C 
tarz� diziler olarak adland�r�l�r. C tarz� dizilere bazen "��plak diziler ( naked arrays )", "sabit boyutlu diziler ( fixed-sized arrays )", 
"sabit diziler ( fixed arrays )" veya "yerle�ik diziler ( built-in arrays )" denir.
Biz "C tarz� dizi" terimini tercih edece�iz ve genel olarak dizi t�rlerinden bahsederken "dizi" terimini kullanaca��z. Modern standartlara g�re, 
C tarz� diziler tuhaf davran�r ve tehlikelidirler. Nedenini bir sonraki b�l�mde inceleyece�iz.

C++'da dizileri daha g�venli ve kullan�m� kolay hale getirmek i�in, std::vector konteyner s�n�f� C++03'te tan�t�ld�. std::vector, 
�� dizi t�r� aras�nda en esnek olan�d�r ve di�er dizi t�rlerinin sahip olmad��� bir dizi kullan��l� �zelli�e sahiptir.

Son olarak, std::array konteyner s�n�f�, C tarz� dizilerin do�rudan yerine ge�mek �zere C++11'de tan�t�ld�. std::vector'dan daha s�n�rl�d�r,
ancak �zellikle daha k���k diziler i�in daha verimli olabilir.

Bu dizi t�rlerinin t�m�, modern C++'da farkl� kapasitelerde hala kullan�lmaktad�r, bu y�zden ���n� de �e�itli derecelerde ele alaca��z.

�lerleyi�
---------
Bir sonraki derste, ilk konteyner s�n�f�m�z olan std::vector'� tan�taca��z ve bu dersin ba��nda sundu�umuz meydan okumay� nas�l verimli bir �ekilde
��zebilece�ini g�stermeye ba�layaca��z. std::vector ile �ok zaman ge�irece�iz, ��nk� olduk�a fazla yeni kavram� tan�tmam�z ve yolda baz� 
ek zorluklar� ele almam�z gerekecek.

G�zel olan bir �ey, t�m konteyner s�n�flar�n�n benzer aray�zlere sahip olmas�d�r. Bu nedenle, bir konteyneri (�rne�in std::vector) nas�l 
kullanaca��n�z� ��rendikten sonra, di�erlerini (�rne�in std::array) ��renmek �ok daha basittir. Gelecekteki konteynerler i�in (�rne�in std::array),
belirgin farkl�l�klar� (ve en �nemli noktalar� tekrarlayaca��z).

Yazar�n Notu
------------
Terminoloji �zerine h�zl� bir not:

�o�u veya t�m standart k�t�phane konteyner s�n�flar�na uygulanan bir �ey hakk�nda konu�urken konteyner s�n�flar�n� kullanaca��z.
T�m dizi t�rlerine genellikle uygulanan bir �ey hakk�nda konu�urken dizi kullanaca��z, di�er programlama dillerinde uygulananlar bile.
std::vector, bu iki kategoriye de girer, bu y�zden farkl� terimler kullan�yor olabiliriz, ancak std::vector'a hala uygulan�r.

Tamam, haz�r m�s�n�z?

Hadi ba�layal�m.

16.2 � std::vector'a Giri� ve list constructors
-----------------------------------------------
�nceki derste 16.1 -- Konteynerlere ve dizilere giri�, hem konteynerleri hem de dizileri tan�tt�k. Bu derste, b�l�m�n geri kalan�nda 
odaklanaca��m�z dizi t�r�n� tan�taca��z: std::vector. Ayr�ca ge�en derste tan�tt���m�z �l�eklenebilirlik meydan okumas�n�n bir k�sm�n� ��zece�iz.

std::vector'a Giri�
-------------------
std::vector, bir dizi uygulayan C++ standart konteynerler k�t�phanesindeki konteyner s�n�flar�ndan biridir. std::vector, <vector> ba�l���nda bir 
s�n�f �ablonu olarak tan�mlan�r, bir �ablon t�r parametresi ile, bu da ��elerin t�r�n� tan�mlar. Bu nedenle, std::vector<int> bir std::vector'�
tan�mlar, ��eleri int t�r�ndedir.

Bir std::vector nesnesini �rnekleme basittir:

                #include <vector>

                int main()
                {
                    // De�er ba�latma (varsay�lan yap�land�r�c�y� kullan�r)
                    std::vector<int> empty{}; // 0 int ��esi i�eren vector

                    return 0;
                }

Bo� de�i�keni, ��eleri int t�r�nde olan bir std::vector olarak tan�mlanm��t�r. Burada de�er ba�latmay� kulland���m�z i�in, vector'�m�z bo� 
(yani, hi�bir ��e olmadan) ba�lar.

�imdilik hi� ��esi olmayan bir vector kullan��l� g�r�nmeyebilir, ancak bu durumu gelecekteki derslerde (�zellikle 16.11 -- std::vector ve stack 
davran���) tekrar kar��la�aca��z.

Bir std::vector'� bir de�er listesiyle ba�latma
-----------------------------------------------
Bir konteynerin amac�, bir dizi ilgili de�eri y�netmek oldu�undan, �o�u zaman konteynerimizi bu de�erlerle ba�latmak isteyece�iz. Bunu, istedi�imiz
belirli ba�latma de�erleriyle liste ba�latmay� kullanarak yapabiliriz. �rne�in:

                #include <vector>

                int main()
                {
                    // Liste yap�s� (liste yap�land�r�c�s�n� kullan�r)
                    std::vector<int> primes{ 2, 3, 5, 7 };          // 2, 3, 5 ve 7 de�erlerine sahip 4 int ��esi i�eren vector
                    std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // 'a', 'e', 'i', 'o' ve 'u' de�erlerine sahip 5 char ��esi i�eren vector.  
                                                                    // CTAD (C++17) kullan�r ve char ��e t�r�n� ��kar�r ( deduce ) (tercih edilir).
                    return 0;
                }

Primes ile, ��elerinin int t�r�nde oldu�u bir std::vector istedi�imizi a��k�a belirtiyoruz. 4 ba�latma de�eri sa�lad���m�z i�in,
primes 2, 3, 5 ve 7 de�erlerine sahip 4 ��e i�erecektir.

Sesli harflerle, a��k�a bir ��e t�r� belirtmedik. Bunun yerine, derleyicinin ba�lat�c�lar�ndan ��e t�r�n� ��karmas� i�in C++17'nin CTAD
(s�n�f �ablonu arg�man ��kar�m�) �zelli�ini kullan�yoruz. 5 ba�latma de�eri sa�lad���m�z i�in, sesli harfler 'a', 'e', 'i', 'o' ve 'u' de�erlerine 
sahip 5 ��e i�erecek.

Liste yap�c�lar� ve ba�lat�c� listeler
--------------------------------------
Yukar�daki i�leyi�in biraz daha detay�na girelim.

13.6 dersinde -- Struct'� toplu ba�latma, bir ba�lat�c� listeyi virg�lle ayr�lm�� de�erlerin s�sl� parantez i�indeki listesi olarak tan�mlad�k
(�r. { 1, 2, 3 }).

Konteynerler genellikle, bir ba�lat�c� listeyi kullanarak konteynerin bir �rne�ini olu�turmam�za izin veren �zel bir kurucuya sahiptir. 
Liste yap�c�s� �� �ey yapar:

*- T�m ba�latma de�erlerini saklamak i�in konteynerin yeterli depolama alan�na sahip olmas�n� sa�lar (gerekirse).
*- onteynerin uzunlu�unu, ba�lat�c� listedeki ��e say�s�na ayarlar (gerekirse).
*- ��eleri, ba�lat�c� listedeki de�erlere (s�ral� olarak) ba�lat�r.
* 
Dolay�s�yla, bir konteynera bir ba�lat�c� de�er listesi sa�lad���m�zda, liste yap�c� �a�r�l�r ve konteyner, bu de�er listesini kullanarak 
olu�turulur!

*** BEST -> Bir konteyneri, bu ��e de�erleriyle olu�turmak i�in bir ba�lat�c� de�er listesi ile liste ba�latmas�n� kullan�n.

Subscript operat�r� (operator[]) kullanarak dizi ��elerine eri�im
-----------------------------------------------------------------
Peki, bir dizi ��e olu�turduk... onlara nas�l eri�iriz?

Bir an i�in bir benzetme kullanal�m. Yan yana olan ayn� posta kutular�n� d���n�n. Posta kutular�n� daha kolay tan�mlamak i�in, her posta kutusunun
�n�nde bir numara boyanm��. �lk posta kutusu numaras� 0, ikincisi numaras� 1, vb... Yani size posta kutusu numaras� 0'a bir �ey koyman�z 
s�ylendi�inde, bu ilk posta kutusu anlam�na geldi�ini bilirsiniz.

C++'da, dizi ��elerine eri�menin en yayg�n yolu, dizinin ad�n� ve subscript operat�r�n� (operator[]) kullanmakt�r. Belirli bir ��eyi se�mek i�in, 
subscript operat�r�n�n k��eli parantezlerinin i�ine, hangi ��eyi se�mek istedi�imizi belirleyen bir tam say� de�eri sa�lar�z. Bu tam say� de�eri,
bir subscript (veya gayri resmi olarak, bir index) olarak adland�r�l�r. Posta kutular�m�z gibi, ilk ��eye index 0 kullan�larak, ikinciye index 1 
kullan�larak eri�ilir, vb...

�rne�in, primes[0] asal dizi i�indeki index 0'a sahip ��eyi (ilk ��eyi) d�nd�recektir. Subscript operat�r�, ger�ek ��eye bir referans d�nd�r�r, 
bir kopya de�il. Bir dizi ��esine eri�tikten sonra, onu normal bir nesne gibi kullanabiliriz (�r. bir de�er atayabiliriz, 
onu ��kt� olarak verebiliriz, vb...)

Dizileme 0'dan ba�lad��� i�in, C++'daki dizilerin s�f�r tabanl� oldu�unu s�yleriz. Bu, nesneleri 1'den ba�layarak saymaya al��k�n oldu�umuz i�in
kafa kar��t�r�c� olabilir. Bu ayr�ca bir belirsizli�e de neden olabilir ��nk� dizi ��esi 1 hakk�nda konu�tu�umuzda, ilk dizi ��esi (index 0 ile)
mi yoksa ikinci dizi ��esi (index 1 ile) mi oldu�u a��k olmayabilir.

��te bir �rnek:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

                    std::cout << "The first prime number is: " << primes[0] << '\n';
                    std::cout << "The second prime number is: " << primes[1] << '\n';
                    std::cout << "The sum of the first 5 primes is: " << primes[0] + primes[1] + primes[2] + primes[3] + primes[4] << '\n';

                    return 0;
                }
                Bu, �unu yazd�r�r:

                The first prime number is: 2
                The second prime number is: 3
                The sum of the first 5 primes is: 28

Dizileri kullanarak, 5 asal de�erimizi tutmak i�in 5 farkl� adl� de�i�ken tan�mlamam�z gerekmiyor. Bunun yerine, 5 ��eli tek bir dizi (primes) 
tan�mlayabilir ve farkl� ��elere eri�mek i�in index de�erini de�i�tirebiliriz!

Bir sonraki ders olan 16.3 -- std::vector ve i�aretsiz uzunluk ve subscript sorunu dersinde operator[] ve di�er baz� array elemanlar�na eri�im
y�ntemleri hakk�nda daha fazla konu�aca��z.

Subscript s�n�rlar�n d���nda
----------------------------
Bir dizini indexlerken, sa�lanan indexin dizinin ge�erli bir eleman�n� se�mesi gerekir. Yani, N uzunlu�unda bir dizi i�in, subscript 0 ve N-1
(dahil) aras�nda bir de�er olmal�d�r.

operator[] herhangi bir s�n�rlama kontrol� yapmaz, yani indexin 0 ile N-1 (dahil) s�n�rlar� i�inde olup olmad���n� kontrol etmez. operator[]'ye 
ge�ersiz bir index ge�mek tan�ms�z bir davran��a neden olur.

Negatif subscriptleri kullanmamay� hat�rlamak olduk�a kolayd�r. Index N olan bir eleman olmad���n� hat�rlamak daha az kolayd�r! Dizinin son 
eleman�n�n indexi N-1'dir, bu y�zden N indexini kullanmak, derleyicinin dizinin sonundan bir sonraki elemana eri�meye �al��mas�na neden olur.

�pucu

N elemanl� bir dizide, ilk eleman�n indexi 0, ikincinin indexi 1 ve son eleman�n indexi N-1'dir. N indexli bir eleman yoktur!

N'yi subscript olarak kullanmak tan�ms�z bir davran��a neden olur (��nk� bu asl�nda dizinin par�as� olmayan N+1. elemana eri�meye �al���yor).

�pucu

Baz� derleyiciler (Visual Studio gibi) indexin ge�erli oldu�unu kontrol eden bir runtime assert sa�lar. Bu t�r durumlarda, debug modunda ge�ersiz
bir index sa�lan�rsa, program assert ��kar�r. Release modunda, assert derlenir, bu y�zden hi�bir performans penalty'si yoktur.

Diziler bellekte biti�iktir
---------------------------
Dizilerin belirleyici �zelliklerinden biri, elemanlar�n her zaman bellekte biti�ik olarak ayr�lmas�d�r, yani elemanlar bellekte birbirine 
biti�iktir (aralar�nda bo�luk yoktur).

Bunu g�stermek i�in:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

                    std::cout << "An int is " << sizeof(int) << " bytes\n";
                    std::cout << &(primes[0]) << '\n';
                    std::cout << &(primes[1]) << '\n';
                    std::cout << &(primes[2]) << '\n';

                    return 0;
                }
                Yazar�n makinesinde, yukar�daki program�n bir �al��t�r�lmas� a�a��daki sonucu verdi:

                An int is 4 bytes
                00DBF720
                00DBF724
                00DBF728

Bu int elemanlar�n�n bellek adreslerinin, yazar�n makinesindeki bir int'in boyutu olan 4 byte kadar ayr� oldu�unu not edeceksiniz.

Bu, dizilerin herhangi bir eleman ba��na ekstra maliyeti olmad��� anlam�na gelir. Ayr�ca derleyicinin dizinin herhangi bir eleman�n�n adresini
h�zl�ca hesaplamas�n� sa�lar.

Diziler, her bir elemana do�rudan ve e�it h�zda eri�im sa�layan birka� konteyn�r t�r�nden biridir, konteyn�r�n eleman say�s�na bak�lmaks�z�n.
Herhangi bir elemana h�zl�ca do�rudan eri�im yetene�i, dizilerin konteyn�r se�imi i�in birincil nedenidir.

Belirli bir uzunlukta bir std::vector olu�turma
-----------------------------------------------
Kullan�c�n�n 10 de�er girmesini ve bunlar� bir std::vector'da saklamas�n� istedi�imiz bir durumu d���n�n. Bu durumda, std::vector'a herhangi bir 
de�er koymadan �nce 10 uzunlu�unda bir std::vector'a ihtiyac�m�z var. Bunu nas�l ��zeriz?

Bir std::vector olu�turabilir ve onu 10 adet yer tutucu de�eri olan bir ba�lat�c� listesi ile ba�latabiliriz:

                std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
Ama bu, bir�ok nedenle k�t�d�r. �ok fazla yaz�m gerektirir. Ka� tane ba�lat�c� oldu�unu g�rmek kolay de�ildir. Ve daha sonra farkl� bir de�er
say�s� istemeye karar verirsek g�ncellemesi kolay olmaz.

Neyse ki, std::vector'�n, olu�turulacak std::vector'�n uzunlu�unu tan�mlayan tek bir int de�eri alan bir explicit constructor'�
(explicit std::vector<T>(int)) vard�r:

                std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
Olu�turulan her bir eleman de�er-initialize edilir, bu int i�in s�f�r-initialization yapar (ve s�n�f t�rleri i�in default constructor'� �a��r�r).

Ancak, bu constructor'� kullan�rken g�zden ka�an bir �ey var: do�rudan ba�latma kullan�larak �a�r�lmal�d�r.

Liste constructorlar� di�er constructorlardan �nceliklidir

�nceki constructor'�n neden do�rudan ba�latma kullan�larak �a�r�lmas� gerekti�ini anlamak i�in bu tan�mlamay� d���n�n:

                std::vector<int> data{ 10 }; // bu ne yapar?
Bu ba�latmay� e�le�tiren iki farkl� constructor vard�r:

*- { 10 } bir ba�lat�c� listesi olarak yorumlanabilir ve liste constructor'� ile e�le�tirilerek de�eri 10 olan uzunlu�u 1 olan bir 
   vekt�r olu�turabilir

*- { 10 } tek bir s�sl� ba�latma de�eri olarak yorumlanabilir ve std::vector<T>(int) constructor'� ile e�le�tirilerek elemanlar� 0'a de�er
   ba�lat�lm�� uzunlu�u 10 olan bir vekt�r olu�turabilir.

Normalde bir s�n�f t�r� tan�m� birden fazla constructor'� e�le�tirirse, e�le�me belirsiz kabul edilir ve bir derleme hatas� olu�ur. Ancak,
C++'�n bu durum i�in �zel bir kural� vard�r: E�le�en bir liste constructor'�, di�er e�le�en constructor'lardan se�ilir. Bu kural olmasayd�, 
bir liste constructor'�, tek tip arg�man alan herhangi bir constructor ile belirsiz bir e�le�me olu�tururdu.

{ 10 } bir ba�lat�c� listesi olarak yorumlanabilir ve std::vector'�n bir liste constructor'� oldu�undan, bu durumda liste constructor'� 
�nceliklidir.

Anahtar i�g�r�

Bir s�n�f t�r� nesnesi olu�tururken, e�le�en bir liste constructor'�, di�er e�le�en constructor'lardan se�ilir.

�e�itli ba�latma durumlar�nda ne oldu�unu daha da a��kl��a kavu�turmak i�in, kopya, do�rudan ve liste ba�latma kullan�larak benzer durumlara
bakal�m:

                // Kopya ba�latma
                std::vector<int> v1 = 10;     // 10 bir ba�lat�c� liste de�il, kopya ba�latma explicit constructor'� e�le�tirmez: derleme hatas�

                // Do�rudan ba�latma
                std::vector<int> v2(10);      // 10 bir ba�lat�c� liste de�il, explicit tek arg�manl� constructor'� e�le�tirir

                // Liste ba�latma
                std::vector<int> v3{ 10 };    // { 10 } ba�lat�c� liste olarak yorumlan�r, liste constructor'� ile e�le�ir

                // Kopya liste ba�latma
                std::vector<int> v4 = { 10 }; // { 10 } ba�lat�c� liste olarak yorumlan�r, liste constructor'� ile e�le�ir
                std::vector<int> v5({ 10 });  // { 10 } ba�lat�c� liste olarak yorumlan�r, liste constructor'� ile e�le�ir

v1 durumunda, 10 ba�latma de�eri bir ba�lat�c� liste de�il, bu y�zden liste constructor'� bir e�le�me de�il. Tek arg�manl� constructor
explicit std::vector<T>(int) de kopya ba�latma ile explicit constructor'lar� e�le�tirmeyece�i i�in bir e�le�me de�il. 
Hi�bir constructor e�le�medi�i i�in bu bir derleme hatas�d�r.

v2 durumunda, 10 ba�latma de�eri bir ba�lat�c� liste de�il, bu y�zden liste constructor'� bir e�le�me de�il. Tek arg�manl� constructor
explicit std::vector<T>(int) bir e�le�medir, bu y�zden tek arg�manl� constructor se�ilir.

v3 durumunda (liste ba�latma), { 10 } liste constructor'� veya explicit std::vector<T>(int) ile e�le�tirilebilir. Liste constructor'�,
di�er e�le�en constructor'lardan �ncelikli olur ve se�ilir.

v4 durumunda (kopya liste ba�latma), { 10 } bir ba�lat�c� liste ile e�le�tirilebilir (bu, explicit olmayan bir constructor'dur, bu y�zden kopya
ba�latma ile kullan�labilir). Liste constructor'� se�ilir.

v5 durumu �a��rt�c� bir �ekilde kopya liste ba�latma i�in alternatif bir s�zdizimi (do�rudan ba�latma de�il) ve v4 ile ayn�d�r.

Bu, C++ ba�latmas�n�n bir kusurudur: { 10 } varsa bir liste constructor'� ile e�le�ir, veya bir liste constructor'� yoksa tek arg�manl� bir 
constructor ile e�le�ir. Bu, hangi davran��� elde etti�inizin bir liste constructor'�n�n var olup olmad���na ba�l� oldu�u anlam�na gelir! 
Genellikle konteynerlar�n liste constructor'lar� oldu�unu varsayabilirsiniz.

�zetlemek gerekirse, liste ba�lat�c�lar genellikle bir konteyner� bir eleman de�erleri listesi ile ba�latmam�za izin vermek i�in tasarlanm��t�r
ve bu ama� i�in kullan�lmal�d�r. Zaten �o�unlukla istedi�imiz �ey budur. Bu nedenle, { 10 } 10'un bir eleman de�eri oldu�u durumlarda uygundur. 
E�er 10, bir konteyner�n liste olmayan bir constructor'�na bir arg�man olarak anlam�na geliyorsa, do�rudan ba�latmay� kullan�n.

*** BEST -> Bir konteyneri (veya bir liste yap�c�ya sahip herhangi bir t�r�) ��e de�erleri olmayan ba�lat�c�larla olu�tururken, do�rudan ba�latmay�
            kullan�n.

�pucu

Bir std::vector, bir s�n�f t�r�n�n �yesi oldu�unda, bir std::vector'�n uzunlu�unu belirli bir ba�lang�� de�erine ayarlayan bir varsay�lan 
ba�lat�c�y� nas�l sa�layaca�� a��k de�ildir:

                #include <vector>

                struct Foo
                {
                    std::vector<int> v1(8); // derleme hatas�: �ye varsay�lan ba�lat�c�lar� i�in do�rudan ba�latmaya izin verilmez
                };

Bir s�n�f t�r�n�n bir �yesi i�in varsay�lan bir ba�lat�c� sa�larken:

*- Ya kopya ba�latmay� ya da liste ba�latmay� kullanmal�y�z.
*- CTAD'a izin verilmez (bu y�zden ��e t�r�n� a��k�a belirtmeliyiz).

Cevap �u �ekildedir:

                struct Foo
                {
                    std::vector<int> v{ std::vector<int>(8) }; // tamam
                };

Bu, kapasitesi 8 olan bir std::vector olu�turur ve ard�ndan bunu v'nin ba�lat�c�s� olarak kullan�r.

Const ve constexpr std::vector
------------------------------
std::vector t�r�ndeki nesneler const yap�labilir:

                #include <vector>

                int main()
                {
                    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime ve ��eleri de�i�tirilemez

                    return 0;
                }

Bir const std::vector ba�lat�lmal� ve ard�ndan de�i�tirilemez. Bu t�r bir vector'�n ��eleri, constmu� gibi ele al�n�r.

Bir non-const std::vector'�n ��eleri non-const olmal�d�r. Bu nedenle, a�a��dakine izin verilmez:

                #include <vector>

                int main()
                {
                    std::vector<const int> prime { 2, 3, 5, 7, 11 };
                }

std::vector'�n en b�y�k dezavantajlar�ndan biri, constexpr yap�lamamas�d�r. E�er constexpr bir diziye ihtiyac�n�z varsa, std::array kullan�n.

Neden vector olarak adland�r�ld�?
---------------------------------
�nsanlar konu�ma s�ras�nda "vector" terimini kulland�klar�nda, genellikle bir b�y�kl��� ve y�n� olan bir nesne olan bir geometrik vector'�
kastediyorlar. Peki std::vector, bir geometrik vector olmad���nda ad�n� nas�l ald�?

"Matematikten Genel Programlamaya" adl� kitapta Alexander Stepanov, "STL'deki vector ad�, daha �nceki programlama dilleri Scheme ve Common Lisp'ten
al�nd�. Ne yaz�k ki, bu, matematikteki �ok daha eski terimin anlam�yla tutars�zd�... bu veri yap�s�na dizi denmeliydi. �zg�n�m, e�er bir hata
yaparsan�z ve bu ilkeleri ihlal ederseniz, sonu� uzun s�re boyunca kalabilir." diye yazd�.

Yani, temelde, std::vector yanl�� adland�r�lm��t�r, ancak �imdi onu de�i�tirmek i�in �ok ge�tir.

16.3 � std::vector ve i�aretsiz uzunluk ve subscript sorunu
----------------------------------------------------------
�nceki ders olan 16.2 -- std::vector ve liste kurucular�na giri�te, bir diziyi subscript etmek ve bir ��eye eri�mek i�in kullan�labilecek
operator[]'i tan�tt�k. Bu derste, dizi ��elerine eri�menin di�er yollar�na ve bir konteyner s�n�f�n�n uzunlu�unu (konteyner s�n�f�nda �u anda 
bulunan ��e say�s�) alman�n birka� farkl� yoluna bakaca��z.

Ama bunu yapmadan �nce, C++'�n tasar�mc�lar�n�n yapt��� b�y�k bir hatay� ve bu hatan�n C++ standart k�t�phanesindeki t�m konteyner s�n�flar�n� 
nas�l etkiledi�ini tart��mam�z gerekiyor.

Konteyner uzunluk i�aret sorunu
-------------------------------
Bir iddiayla ba�layal�m: bir diziyi subscript etmek i�in kullan�lan veri tipi, dizinin uzunlu�unu saklamak i�in kullan�lan veri tipiyle
e�le�melidir. Bu, en uzun olas� dizideki t�m ��elerin indexlenebilmesi ve daha fazlas�n�n olmamas� i�in gereklidir.

Bjarne Stroustrup'un hat�rlad���na g�re, C++ standart k�t�phanesindeki konteyner s�n�flar� tasarlan�rken (yakla��k 1997), tasar�mc�lar�n uzunlu�u
(ve dizi subcriptlerini) i�aretli mi yoksa i�aretsiz mi yapacaklar�na karar vermesi gerekiyordu. Onlar bunlar� i�aretsiz ( i�aretsiz )
yapmay� se�tiler.

Bunun i�in verilen nedenler: standart k�t�phane dizi tiplerinin subcriptleri negatif olamaz, bir i�aretsiz tip kullanmak ekstra bit nedeniyle
daha uzun dizilere izin verir (bu, 16-bit g�nlerinde �nemliydi) ve subscriptin aral�k kontrol� iki yerine bir ko�ullu kontrol gerektirir
(��nk� indexin 0'dan k���k oldu�unu sa�lamak i�in kontrol yapmaya gerek yoktu).

Geriye d�n�p bakt���m�zda, bu genellikle yanl�� bir se�im olarak kabul edilir. Art�k i�aretsiz de�erlerin negatif olmayanlar� zorlamaya �al��man�n,
implicit d�n���m kurallar� nedeniyle i�e yaramad���n� anl�yoruz (��nk� negatif bir i�aretli tam say�, sadece b�y�k bir i�aretsiz tam say�ya 
implicit olarak d�n���r ve ��p bir sonu� �retir), ekstra bit aral��� genellikle 32-bit veya 64-bit sistemlerde gerekli de�ildir
(��nk� muhtemelen 2 milyondan fazla ��e i�eren diziler olu�turmuyorsunuzdur) ve yayg�n olarak kullan�lan operator[] zaten aral�k kontrol� yapmaz.

4.5 dersinde -- ��aretsiz tam say�lar ve onlardan ka��nma nedenleri, nicelikleri tutmak i�in i�aretli de�erleri kullanmay� tercih etti�imiz
nedenleri tart��t�k. Ayr�ca, i�aretli ve i�aretsiz de�erlerin kar��t�r�lmas�n�n beklenmedik davran��lara yol a�abilece�ini de belirttik. 
Dolay�s�yla, standart k�t�phane konteyner s�n�flar�n�n uzunluk (ve indeksler) i�in i�aretsiz de�erler kullanmas� sorunludur, ��nk� bu t�rleri
kullan�rken i�aretsiz de�erlerden ka��nmay� imkans�z k�lar.

�imdilik, bu se�imle ve neden oldu�u gereksiz karma��kl�kla ba�a ��kmak zorunday�z.

Bir inceleme i�aret d�n���mleri daralt�c� d�n���mlerdir, constexpr oldu�unda hari�
----------------------------------------------------------------------------------
Daha ileri gitmeden �nce, bu b�l�mde �ok konu�aca��m�z i�aret d�n���mleri (i�aretli'den i�aretsiz'e veya tam tersi integral d�n���mler) 
hakk�nda 10.4 dersi -- Daralt�c� d�n���mler, liste ba�latma ve constexpr ba�lat�c�lar�ndan baz� materyalleri h�zl�ca g�zden ge�irelim.

��aret d�n���mleri, bir i�aretli veya i�aretsiz tipin, kar��t tipin aral���ndaki t�m de�erleri tutamamas� nedeniyle daralt�c� d�n���mler olarak 
kabul edilir. B�yle bir d�n���m, �al��ma zaman�nda denenirse, derleyici daralt�c� d�n���mlerin izin verilmedi�i ba�lamlarda (�rne�in liste
ba�latmas�nda) bir hata verecek ve bu t�r bir d�n���m gerektiren di�er ba�lamlarda uyar� verebilir veya vermeyebilir.

�rne�in:

                #include <iostream>

                void foo(unsigned int)
                {
                }

                int main()
                {
                    int s { 5 };

                    [[maybe_unused]] i�aretsiz int u { s }; // compile error: list initialization disallows narrowing conversion
                    foo(s);                                // possible warning: copy initialization allows narrowing conversion

                    return 0;
                }

Yukar�daki �rnekte, u de�i�keninin ba�lat�lmas� bir derleme hatas� olu�turur ��nk� daralt�c� d�n���mler list initialization yap�l�rken kabul
edilmez. foo() �a�r�s� copy initialization ger�ekle�tirir, bu daralt�c� d�n���mlere izin verir ve derleyicinin sign conversion uyar�lar�n� 
ne kadar agresif �retti�ine ba�l� olarak bir uyar� olu�turabilir veya olu�turmayabilir. �rne�in, hem GCC hem de Clang, -Wsign-conversion derleyici 
bayra�� kullan�ld���nda bu durumda uyar�lar olu�turacakt�r.

Ancak, i�aret d�n��t�r�lmesi gereken de�er constexpr ise ve kar�� t�rde e�de�er bir de�ere d�n��t�r�lebilirse, i�aret d�n���m� daralt�c� olarak
kabul edilmez. Bu, derleyicinin d�n���m�n g�venli oldu�unu garanti edebilece�i veya derleme s�recini durdurabilece�i i�indir.

                #include <iostream>

                void foo(unsigned int)
                {
                }

                int main()
                {
                    constexpr int s { 5 };                 // now constexpr
                    [[maybe_unused]] i�aretsiz int u { s }; // ok: x is constexpr and can be converted safely, not a narrowing conversion
                    foo(s);                                // ok: x is constexpr and can be converted safely, not a narrowing conversion

                    return 0;
                }

Bu durumda, s constexpr oldu�u ve d�n��t�r�lmesi gereken de�erin (5) i�aretsiz bir de�er olarak temsil edilebildi�i i�in, d�n���m daralt�c� olarak 
kabul edilmez ve sorunsuz bir �ekilde implicit olarak ger�ekle�tirilebilir.

Bu daraltmayan d�n���m, constexpr int'ten constexpr std::size_t'ye, �ok fazla kullanaca��m�z bir �eydir.

std::vector'�n uzunlu�u ve indeksleri size_type tipindedir

10.7 Dersinde -- Typedefs and type aliases, typedef'lerin ve type alias'lar�n genellikle bir t�r�n de�i�ebilece�i durumlarda
(�r. ��nk� implementation-defined) bir t�r i�in bir isme ihtiya� duydu�umuzda s�kl�kla kullan�ld���n� belirttik. �rne�in std::size_t,
genellikle i�aretsiz long veya i�aretsiz long long olan baz� b�y�k i�aretsiz integral tipi i�in bir typedef'tir.

Standart k�t�phane konteyn�r s�n�flar�n�n her biri, konteyn�r�n uzunlu�u (ve destekleniyorsa indeksleri) i�in kullan�lan tip i�in bir alias olan 
size_type (bazen T::size_type olarak yaz�l�r) ad�nda bir nested typedef �ye tan�mlar.

size_type'� genellikle belgelerde ve derleyici uyar�lar�/hata mesajlar�nda g�r�rs�n�z. �rne�in, std::vector'�n size() �ye fonksiyonu i�in bu belge,
size()'�n size_type de�eri d�nd�rd���n� belirtir.

�lgili ��erik

Nested typedef'leri 15.3 -- Nested types (member types) dersinde ele al�yoruz.

size_type neredeyse her zaman std::size_t i�in bir alias't�r, ancak nadir durumlarda farkl� bir tipi kullanmak �zere ge�ersiz k�l�nabilir.

Anahtar ��g�r�

size_type, standart k�t�phane konteyn�r s�n�flar�nda tan�mlanan bir nested typedef'tir, konteyn�r s�n�f�n�n uzunlu�u (ve destekleniyorsa indeksleri)
i�in kullan�lan tipe kar��l�k gelir.

size_type varsay�lan olarak std::size_t'ye ayarlan�r ve bu neredeyse hi� de�i�tirilmedi�i i�in, size_type'�n std::size_t i�in bir alias oldu�unu
makul bir �ekilde varsayabiliriz.
Bir konteyn�r s�n�f�n�n size_type �yesine eri�irken, onu konteyn�r s�n�f�n�n tamamen �ablonlanm�� ad� ile scope qualify etmeliyiz.
�rne�in, std::vector<int>::size_type.

size() �ye fonksiyonunu kullanarak bir std::vector'�n uzunlu�unu almak veya std::size() kullanmak

Bir konteyn�r s�n�f� nesnesinden uzunlu�unu size() �ye fonksiyonunu kullanarak sorabiliriz (bu, uzunlu�u i�aretsiz size_type olarak d�nd�r�r):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
                    return 0;
                }

                Bu, �unu yazd�r�r:

                length: 5
hem length() hem de size() �ye fonksiyonuna sahip olan std::string ve std::string_view'in aksine, std::vector (ve C++'daki di�er �o�u konteyn�r
t�r�) yaln�zca size()'a sahiptir. Ve �imdi bir konteyn�r�n uzunlu�unun bazen belirsiz bir �ekilde boyutu olarak adland�r�lmas�n�n nedenini
anlad�n�z.

C++17'de, ayr�ca std::size() non-member fonksiyonunu da kullanabiliriz (bu, konteyn�r s�n�flar� i�in yaln�zca size() �ye fonksiyonunu �a��r�r).

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    std::cout << "uzunluk: " << std::size(prime); // C++17, `size_type` t�r�nde ( `std::size_t` i�in takma ad) uzunluk d�nd�r�r

                    return 0;
                }

E�er yukar�daki y�ntemlerden herhangi birini uzunlu�u i�aretli bir t�rdeki bir de�i�kende saklamak i�in kullanmak istiyorsak, bu muhtemelen 
i�aretli/i�aretsiz d�n���m uyar�s� veya hatas� sonucunu do�uracakt�r. Burada yap�lacak en basit �ey, sonucu istenen t�re static_cast etmektir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    int uzunluk { static_cast<int>(prime.size()) }; // d�n�� de�erini int'e static_cast
                    std::cout << "uzunluk: " << uzunluk ;

                    return 0;
                }

std::ssize() kullanarak std::vector'�n uzunlu�unu almak C++20
--------------------------------------------------------------
C++20, uzunlu�u b�y�k bir i�aretli integral t�r olarak d�nd�ren std::ssize() adl� �ye olmayan bir fonksiyonu tan�t�r (genellikle std::ptrdiff_t, 
ki bu genellikle std::size_t'nin i�aretli kar��l��� olarak kullan�lan t�rd�r):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    std::cout << "uzunluk: " << std::ssize(prime); // C++20, uzunlu�u b�y�k bir i�aretli integral t�r olarak d�nd�r�r

                    return 0;
                }

Bu, �� fonksiyon aras�nda uzunlu�u i�aretli bir t�r olarak d�nd�ren tek fonksiyondur. E�er bu y�ntemi uzunlu�u i�aretli bir t�rdeki bir de�i�kende
saklamak istiyorsan�z, birka� se�ene�iniz var.

�ncelikle, int t�r� std::ssize() taraf�ndan d�nd�r�len i�aretli t�rden daha k���k olabilir, e�er uzunlu�u bir int de�i�kenine atayacaksan�z, 
sonucu int'e static_cast etmelisiniz ki herhangi bir d�n���m a��k�a belirtilmi� olsun (aksi takdirde daralt�c� d�n���m uyar�s� veya hatas�
alabilirsiniz):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    int uzunluk { static_cast<int>(std::ssize(prime)) }; // d�n�� de�erini int'e static_cast
                    std::cout << "uzunluk: " << uzunluk;

                    return 0;
                }

Alternatif olarak, derleyicinin de�i�ken i�in kullan�lacak do�ru i�aretli t�r� ��karmas�n� sa�lamak i�in auto'yu kullanabilirsiniz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    auto uzunluk { std::ssize(prime) }; // std::ssize() taraf�ndan d�nd�r�len i�aretli t�r� ��karmak i�in auto kullan�n
                    std::cout << "uzunluk: " << uzunluk;

                    return 0;
                }

operator[] kullanarak dizi elemanlar�na eri�im s�n�rlama kontrol� yapmaz
------------------------------------------------------------------------
�nceki derste, subscript operat�r�n� (operator[]) tan�tt�k:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3];  // indeksi 3 olan eleman�n de�erini yazd�r (7)
                    std::cout << prime[9]; // ge�ersiz indeks (tan�ms�z davran��)

                    return 0;
                }

operator[] s�n�rlama kontrol� yapmaz. operator[] i�in indeks non-const olabilir. Bunu daha sonra bir b�l�mde tart��aca��z.

at() �ye fonksiyonunu kullanarak dizi elemanlar�na eri�im, �al��ma zaman�nda s�n�rlama kontrol� yapar
-----------------------------------------------------------------------------------------------------
Dizi konteyner s�n�flar�, bir diziyi eri�mek i�in ba�ka bir y�ntem destekler. at() �ye fonksiyonu, �al��ma zaman�nda s�n�rlama kontrol� ile dizi
eri�imi yapmak i�in kullan�labilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime.at(3); // indeksi 3 olan eleman�n de�erini yazd�r
                    std::cout << prime.at(9); // ge�ersiz indeks (istisna f�rlat�r)

                    return 0;
                }

Yukar�daki �rnekte, prime.at(3) �a�r�s�, indeksin 3'�n ge�erli oldu�unu kontrol eder ve ��nk� �yledir, dizi eleman� 3'e bir referans d�nd�r�r.
Bu de�eri daha sonra yazd�rabiliriz. Ancak, prime.at(9) �a�r�s�, 9'un bu dizi i�in ge�erli bir indeks olmad��� i�in (�al��ma zaman�nda) ba�ar�s�z
olur. Bir referans d�nd�rmek yerine, at() fonksiyonu program� sonland�ran bir hata olu�turur.

Operator[] gibi, at() fonksiyonuna ge�irilen indeks de non-const olabilir.

Her �a�r�da �al��ma zaman� s�n�rlar�n� kontrol etti�i i�in, at() fonksiyonu operator[]'den daha yava� (ama daha g�venli) olabilir.
Daha az g�venli olmas�na ra�men, operator[] genellikle at() �zerinde tercih edilir, ��nk� at() fonksiyonunu �a��rmadan �nce s�n�rlar�n
kontrol edilmesi daha iyidir, b�ylece ba�tan beri ge�ersiz bir indeksle �a��rmay�z.

constexpr i�aretliint ile std::vector �ndeksleme
-----------------------------------------------
Bir std::vector'� bir constexpr (signed) int ile indekslerken, derleyicinin bunu bir daraltma d�n���m� olmadan std::size_t'ye d�n��t�rmesine 
izin verebiliriz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3] << '\n';     // tamam: 3 int'ten std::size_t'ye d�n��t�r�l�r, daraltma d�n���m� de�il

                    constexpr int index { 3 };         // constexpr
                    std::cout << prime[index] << '\n'; // tamam: constexpr indeks std::size_t'ye d�n��t�r�l�r, daraltma d�n���m� de�il

                    return 0;
                }

Non-constexpr De�er ile std::vector �ndeksleme
----------------------------------------------
Bir diziyi indekslemek i�in kullan�lan alt dizinler non-const olabilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::size_t index { 3 };           // non-constexpr
                    std::cout << prime[index] << '\n'; // operator[] bir std::size_t t�r�nde indeks bekler, d�n���m gerekmez

                    return 0;
                }

Ancak, en iyi uygulamalar�m�za g�re , genellikle miktarlar� tutmak i�in i�aretsiz t�rlerini kullanmaktan ka��nmak istiyoruz.
Alt dizinimiz non-constexpr bir i�aretlide�er oldu�unda, sorunlarla kar��la��yoruz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    int index { 3 };                   // non-constexpr
                    std::cout << prime[index] << '\n'; // olas� uyar�: indeks std::size_t'ye d�n��t�r�l�r, daraltma d�n���m�

                    return 0;
                }

Bu �rnekte, indeks bir non-constexpr i�aretliint'tir. std::vector'�n bir par�as� olarak tan�mlanan operator[]'nin alt dizi t�r� size_type'd�r
(std::size_t i�in bir takma ad). Bu nedenle, print[index] dedi�imizde, i�aretliint'imiz std::size_t'ye d�n��t�r�lmelidir.

B�yle bir d�n���m tehlikeli olmamal�d�r (��nk� bir std::vector'�n indeksinin negatif olmamas� beklenir ve negatif olmayan bir i�aretlide�er g�venli 
bir �ekilde i�aretsiz bir de�ere d�n��t�r�l�r). Ancak �al��ma zaman�nda ger�ekle�tirildi�inde, bu bir daraltma d�n���m� olarak kabul edilir ve
derleyicinizin bu d�n���m�n g�vensiz oldu�una dair bir uyar� �retmesi gerekir (e�er �retmezse, uyar�lar�n�z� de�i�tirerek bunu yapmas� gerekti�ini
d���nmelisiniz).

Dizi alt dizinleme yayg�n oldu�u ve her bir d�n���m�n bir uyar� olu�turaca�� i�in, bu durum kolayca derleme g�nl���n�z� gereksiz uyar�larla 
doldurabilir. Veya, "uyar�lar� hatalar olarak i�le" se�ene�ini etkinle�tirdiyseniz, derlemeniz durur.

Bu sorunu �nlemek i�in bir�ok olas� yol vard�r (�rne�in, her bir dizi indeksleme i�leminde int'inizi std::size_t'ye static_cast yap�n),
ancak hi�biri uygun de�ildir - hepsi ka��n�lmaz olarak kodunuzu bir �ekilde karma��kla�t�r�r veya kar��t�r�r.

Bu durumda yap�lacak en basit �ey, indeksiniz olarak std::size_t t�r�nde bir de�i�ken kullanmakt�r ve bu de�i�keni yaln�zca indeksleme 
i�in kullan�n.

16.4 � std::vector'�n Ge�irilmesi
---------------------------------
std::vector tipindeki bir nesne, di�er herhangi bir nesne gibi bir fonksiyona ge�irilebilir. Bu, bir std::vector'� de�er olarak ge�irdi�imizde, 
pahal� bir kopya yap�laca�� anlam�na gelir. Bu nedenle, genellikle bu t�r kopyalar� �nlemek i�in std::vector'� (const) referans olarak ge�iririz.

Bir std::vector ile, ��e tipi nesnenin tip bilgilerinin bir par�as�d�r. Bu nedenle, bir std::vector'� bir fonksiyon parametresi olarak
kulland���m�zda, ��e tipini a��k�a belirtmemiz gerekir:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector<int>& arr) // burada <int> belirtmeliyiz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes);

                    return 0;
                }

Farkl� ��e tiplerine sahip std::vector'lar�n ge�irilmesi
--------------------------------------------------------
passByRef() fonksiyonumuz bir std::vector<int> bekledi�i i�in, farkl� ��e tiplerine sahip vekt�rleri ge�iremiyoruz:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector<int>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes);  // tamam: bu bir std::vector<int>

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl); // derleme hatas�: std::vector<double> std::vector<int>'e d�n��t�r�lemez

                    return 0;
                }

C++17 veya daha yenisiyle, bu sorunu ��zmek i�in CTAD'yi kullanmay� deneyebilirsiniz:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector& arr) // derleme hatas�: CTAD, fonksiyon parametrelerini ��karmak i�in kullan�lamaz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 }; // tamam: CTAD'yi kullanarak std::vector<int>'i ��kar
                    passByRef(primes);

                    return 0;
                }

CTAD, bir vekt�r�n ��e tipini tan�mland���nda ba�lat�c�lardan ��karmak i�in �al��acak olsa da, CTAD (�u anda) fonksiyon parametreleriyle �al��maz.
Parametre tipinden sadece farkl� olan a��r� y�klenmi� fonksiyonlar oldu�unda bu t�r bir sorunla daha �nce kar��la�t�k. Bu, fonksiyon �ablonlar�n�
kullanman�n harika bir yeri! ��e tipini parametrize eden bir fonksiyon �ablonu olu�turabiliriz ve sonra C++ bu fonksiyon �ablonunu ger�ek tiplerle
fonksiyonlar� �rnekle�tirmek i�in kullanacakt�r.

Ayn� �ablon parametre bildirimini kullanan bir fonksiyon �ablonu olu�turabiliriz:

                #include <iostream>
                #include <vector>

                template <typename T>
                void passByRef(const std::vector<T>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i �rnekle�tirecek

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i �rnekle�tirecek

                    return 0;
                }

Yukar�daki �rnekte, const std::vector<T>& tipinde bir parametreye sahip olan passByRef() ad�nda tek bir fonksiyon �ablonu olu�turduk. 
T, �nceki sat�rdaki �ablon parametre bildiriminde tan�mlanm��t�r: template <typename T. T, �a��ran�n ��e tipini belirtmesine izin veren standart 
bir tip �ablon parametresidir.

Bu nedenle, main() i�inden passByRef(primes) �a�r�s�n� yapt���m�zda (primes, std::vector<int> olarak tan�mlanm��t�r), derleyici
void passByRef(const std::vector<int>& arr)'yi �rnekle�tirecek ve �a��racakt�r.

Main() i�inden passByRef(dbl) �a�r�s�n� yapt���m�zda (dbl, std::vector<double> olarak tan�mlanm��t�r), derleyici 
void passByRef(const std::vector<double>& arr)'yi �rnekle�tirecek ve �a��racakt�r.

B�ylece, herhangi bir ��e tipi ve uzunlu�a sahip std::vector arg�manlar�n� i�lemek i�in fonksiyonlar� �rnekle�tirebilen tek bir fonksiyon �ablonu 
olu�turduk!

Herhangi bir t�rdeki nesneyi kabul edecek bir fonksiyon �ablonu da olu�turabiliriz:

                #include <iostream>
                #include <vector>

                template <typename T>
                void passByRef(const T& arr) // overloaded operator[] olan her t�rdeki nesneyi kabul eder
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i �rnekle�tirir

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i �rnekle�tirir

                    return 0;
                }

C++20'de ayn� �eyi yapmak i�in k�salt�lm�� bir fonksiyon �ablonu (bir auto parametresi arac�l���yla) kullanabiliriz:

                #include <iostream>
                #include <vector>

                void passByRef(const auto& arr) // abbreviated function template
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i �rnekle�tirir

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i �rnekle�tirir

                    return 0;
                }

Her iki durumda da, derlenebilecek her t�rden bir arg�man kabul edilir. Bu, belki de yaln�zca bir std::vector �zerinde �al��mak istemeyece�imiz 
fonksiyonlar yazarken arzu edilebilir. �rne�in, yukar�daki fonksiyonlar ayr�ca bir std::array, bir std::string veya belki de hi� d���nmedi�imiz
ba�ka bir t�r �zerinde de �al��acakt�r. Bu y�ntemin potansiyel dezavantaj�, fonksiyonun, derlenebilir ancak semantik olarak mant�kl� olmayan bir
t�r�n nesnesini ge�ti�inde hatalara yol a�abilece�idir.

Dizi Uzunlu�unda assert yapmak 
------------------------------
Yukar�da sunulanlara benzer bir fonksiyon �ablonu d���n�n:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printElement3(const std::vector<T>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr);

                    return 0;
                }

printElement3(arr) bu durumda iyi �al���rken, bu programda dikkatsiz bir programc�y� bekleyen potansiyel bir hata var. G�rd�n m�?

Yukar�daki program, dizinin 3 indeksli eleman�n�n de�erini yazd�r�r. Bu, dizinin 3 indeksli ge�erli bir eleman� oldu�u s�rece iyidir.
Ancak, derleyici, 3 indeksinin s�n�rlar�n d���nda oldu�u dizileri ge�menize seve seve izin verir. �rne�in:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printElement3(const std::vector<T>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::vector arr{ 9, 7 }; // 2 elemanl� bir dizi (ge�erli indeksler 0 ve 1)
                    printElement3(arr);

                    return 0;
                }

Bu, tan�ms�z bir davran��a yol a�ar. Burada bir se�enek, arr.size() �zerinde assert yapmakt�r, bu da debug build konfig�rasyonunda 
�al��t�r�ld���nda bu t�r hatalar� yakalar. ��nk� std::vector::size() bir non-constexpr i�lev oldu�u i�in, burada yaln�zca bir runtime assert
yapabiliriz.

�pucu

Daha iyi bir se�enek, dizi uzunlu�unda iddia etmeniz gereken durumlarda std::vector kullanmaktan ka��nmakt�r. Constexpr dizileri destekleyen
bir t�r kullanmak (�r. std::array), muhtemelen daha iyi bir se�enektir, ��nk� bir constexpr dizinin uzunlu�unda static_assert yapabilirsiniz.
Bu konuyu gelecekteki 17.3 -- Passing and returning std::array dersinde ele alaca��z.

*** BEST -> Ba�tan beri kullan�c�n�n minimum uzunlukta bir vekt�r ge�mesine dayanan fonksiyonlar yazmaktan ka��nmakt�r.

16.5 � Std::vector'un d�nd�r�lmesi ve hareket semanti�ine giri�
---------------------------------------------------------------
Bir std::vector'� bir fonksiyona ge�irmemiz gerekti�inde, dizinin verisini pahal� bir kopya olu�turmadan ge�irmek i�in (const) referans olarak 
ge�iririz. Bu y�zden, bir std::vector'� de�er olarak d�nd�rmenin tamam oldu�unu ��renmek sizi �a��rtabilir.

Nas�l yani?

Kopya semanti�i
---------------
A�a��daki program� d���n�n:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr1 { 1, 2, 3, 4, 5 }; // { 1, 2, 3, 4, 5 }'i arr1'e kopyalar
                    std::vector arr2 { arr1 };          // arr1'i arr2'ye kopyalar

                    arr1[0] = 6; // arr1'i kullanmaya devam edebiliriz
                    arr2[0] = 7; // ve arr2'yi kullanmaya devam edebiliriz

                    std::cout << arr1[0] << arr2[0] << '\n';

                    return 0;
                }

arr2, arr1 ile ba�lat�ld���nda, std::vector'�n kopya constructor'� �a�r�l�r, bu da arr1'i arr2'ye kopyalar. Bu durumda bir kopya yapmak tek 
mant�kl� �eydir, ��nk� hem arr1'in hem de arr2'nin ba��ms�z olarak ya�amas� gerekmektedir. Bu �rnek, her ba�latma i�in iki kopya olu�turur.

Kopya semanti�i terimi, nesnelerin kopyalar�n�n nas�l yap�ld���n� belirleyen kurallara at�fta bulunur. Bir t�r�n kopya semanti�ini destekledi�ini 
s�yledi�imizde, bu t�r�n nesnelerinin kopyalanabilir oldu�unu, ��nk� bu t�r kopyalar� yapma kurallar�n�n tan�mland���n� ifade ederiz. 
Kopya semanti�inin �a�r�ld���n� s�yledi�imizde, bir nesnenin bir kopyas�n� yapacak bir �ey yapt���m�z� ifade ederiz.

S�n�f t�rleri i�in, kopya semanti�i genellikle kopya constructor'� (ve kopya atama operat�r�) arac�l���yla uygulan�r, bu da o t�r�n nesnelerinin
nas�l kopyaland���n� tan�mlar. Genellikle bu, s�n�f t�r�n�n her veri �yesinin kopyalanmas� sonucunu verir. �nceki �rnekte,
std::vector arr2 { arr1 }; ifadesi kopya semanti�ini �a��r�r, bu da std::vector'�n kopya constructor'�n�n �a�r�lmas�na ve ard�ndan arr1'in her veri
�yesinin arr2'ye kopyalanmas�na yol a�ar. Sonu� olarak, arr1 arr2'ye e�ittir (ancak arr2'den ba��ms�zd�r).

Kopya semanti�inin optimal olmad��� durumlar
--------------------------------------------
�imdi bu ilgili �rne�i d���n�n:

                #include <iostream>
                #include <vector>

                std::vector<int> generate() // de�er olarak d�nd�r
                {
                    // Zorunlu kopya elisyonunun uygulanmamas� i�in burada kas�tl� olarak adland�r�lm�� bir nesne kullan�yoruz
                    std::vector arr1 { 1, 2, 3, 4, 5 }; // { 1, 2, 3, 4, 5 }'i arr1'e kopyalar
                    return arr1;
                }

                int main()
                {
                    std::vector arr2 { generate() }; // generate()'un d�n�� de�eri ifadenin sonunda �l�r

                    // generate()'un d�n�� de�erini burada kullanman�n bir yolu yok
                    arr2[0] = 7; // sadece arr2'ye eri�imimiz var

                    std::cout << arr2[0] << '\n';

                    return 0;
                }

Bu sefer arr2 ba�lat�ld���nda, generate() fonksiyonundan d�nen ge�ici bir nesne kullan�larak ba�lat�l�r. �nceki durumda, ba�lat�c� gelecekteki
ifadelerde kullan�labilecek bir lvalue idi, bu durumda, ge�ici nesne bir rvalue olacak ve ba�latma ifadesinin sonunda yok edilecektir.
Ge�ici nesne o noktadan sonra kullan�lamaz. Ge�ici (ve verisi) ifadenin sonunda yok edilece�i i�in, veriyi ge�iciden ��kar�p arr2'ye koymak i�in
bir yol bulmam�z gerekiyor.

Burada yap�lacak al���lm�� �ey, �nceki �rnekte oldu�u gibi: kopya semanti�ini kullan�n ve potansiyel olarak pahal� bir kopya yap�n. 
Bu �ekilde arr2, ge�ici (ve verisi) yok edildikten sonra bile kullan�labilecek kendi veri kopyas�na sahip olur.

Ancak, bu durumu �nceki �rnektekinden farkl� k�lan �ey, ge�icinin zaten yok edilecek olmas�d�r. Ba�latma tamamland�ktan sonra, ge�ici verisine
daha fazla ihtiya� duymaz (bu y�zden onu yok edebiliriz). �ki veri k�mesinin ayn� anda var olmas�na ihtiyac�m�z yok. Bu t�r durumlarda, 
potansiyel olarak pahal� bir kopya yapmak ve ard�ndan orijinal veriyi yok etmek optimal de�ildir.

Ta��ma Semanti�ine Giri�
------------------------
Peki, arr2'nin ge�ici veriyi kopyalamak yerine "�almas�na" izin veren bir yol olsayd� ne olurdu? arr2, verinin yeni sahibi olurdu ve verinin hi�bir
kopyas�n�n yap�lmas�na gerek kalmazd�. Verinin sahipli�i bir nesneden di�erine aktar�ld���nda, verinin ta��nd���n� s�yleriz. B�yle bir ta��man�n 
maliyeti genellikle �nemsizdir (genellikle sadece iki veya �� pointer atamas�, bir dizi veriyi kopyalamaktan �ok daha h�zl�d�r!).

Ek bir fayda olarak, ifadenin sonunda ge�ici nesne yok edildi�inde, art�k yok edilecek hi�bir verisi olmaz, bu y�zden bu maliyeti de �dememiz
gerekmez.

Bu, ta��ma semanti�inin �z�d�r, bu da bir nesnenin verisinin ba�ka bir nesneye nas�l ta��nd���n� belirleyen kurallara at�fta bulunur. 
Ta��ma semanti�i �a�r�ld���nda, ta��nabilen herhangi bir veri �yesi ta��n�r ve ta��namayan herhangi bir veri �yesi kopyalan�r. 
Veriyi kopyalamak yerine ta��ma yetene�i, ta��ma semanti�ini, �zellikle pahal� bir kopyay� ucuz bir ta��ma ile de�i�tirebildi�imizde,
kopya semanti�inden daha verimli hale getirebilir.

Anahtar nokta �udur ki; Ta��ma semanti�i, belirli durumlar alt�nda, baz� veri �yelerinin sahipli�ini bir nesneden di�erine ucuz bir �ekilde
aktarmam�za izin veren bir optimizasyondur (daha pahal� bir kopya yapmak yerine). Ta��namayan veri �yeleri kopyalan�r.

Ta��ma Semanti�i Nas�l �a�r�l�r
-------------------------------
Normalde, bir nesne ayn� t�rden bir nesne ile ba�lat�l�yor veya atan�yorsa, kopya semanti�i kullan�lacakt�r (kopya elided de�ilse).
Ancak, a�a��dakilerin t�m� do�ru oldu�unda, kopya semanti�i yerine ta��ma semanti�i �a�r�l�r:

*- Nesnenin t�r� ta��ma semanti�ini destekler.
*- Ba�lat�c� veya atanm�� nesne bir rvalue (ge�ici) nesnedir.
*- Ta��ma elided de�ildir.
* 
��te �z�c� haber: �ok fazla t�r ta��ma semanti�ini desteklemiyor. Ancak, std::vector ve std::string her ikisi de yapar!

Ta��ma semanti�inin nas�l �al��t���n� 22. b�l�mde daha ayr�nt�l� olarak inceleyece�iz. �imdilik, ta��ma semanti�inin ne oldu�unu ve hangi t�rlerin
ta��ma yetene�ine sahip oldu�unu bilmek yeterlidir.

std::vector gibi ta��ma yetene�ine sahip t�rleri de�er olarak d�nd�rebiliriz
----------------------------------------------------------------------------
De�er olarak d�nd�rme bir rvalue d�nd�rd��� i�in, d�nd�r�len t�r ta��ma semanti�ini destekliyorsa, d�nd�r�len de�er hedef nesneye kopyalanmak
yerine ta��nabilir! Bu, bu t�rler i�in de�er olarak d�nd�rmeyi son derece ucuz hale getirir!

Anahtar nokta �udur ki; Ta��ma yetene�ine sahip t�rleri (std::vector ve std::string gibi) de�er olarak d�nd�rebiliriz. Bu t�rler, pahal� bir kopya
yapmak yerine de�erlerini ucuz bir �ekilde ta��yacaklard�r.

16.6 � Diziler ve D�ng�ler
--------------------------
Bu b�l�m�n giri� dersinde (16.1 -- Konteynerlara ve dizilere giri�), bir�ok ilgili bireysel de�i�kenimiz oldu�unda kar��la�t���m�z
�l�eklenebilirlik sorunlar�n� tan�tt�k. Bu derste, sorunu tekrar ele alaca��z ve ard�ndan dizilerin bu t�r sorunlar� nas�l zarif bir �ekilde 
��zebilece�ini tart��aca��z. 

De�i�ken �l�eklenebilirlik sorunu, tekrar ziyaret edildi
--------------------------------------------------------
Bir s�n�f�n ��rencilerinin ortalama test puan�n� bulmak istedi�imiz bir durumu d���n�n. Bu �rnekleri �zl� tutmak i�in, s�n�f�n sadece 5 ��rencisi 
oldu�unu varsayaca��z.

Bunu bireysel de�i�kenler kullanarak nas�l ��zebilece�imizi g�sterelim:

                #include <iostream>

                int main()
                {
                    // 5 tam say� de�i�keni tahsis edin (her birinin farkl� bir ad� var)
                    int testScore1{ 84 };
                    int testScore2{ 92 };
                    int testScore3{ 76 };
                    int testScore4{ 81 };
                    int testScore5{ 56 };

                    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

                    std::cout << "S�n�f ortalamas�: " << average << '\n';

                    return 0;
                }

Bu, tan�mlanacak �ok fazla de�i�ken ve �ok fazla yaz�d�r. 30 ��renci veya 600 i�in ne kadar �ok i� yapmam�z gerekti�ini hayal edin. Ayr�ca,
yeni bir test puan� eklenirse, yeni bir de�i�kenin tan�mlanmas�, ba�lat�lmas� ve ortalama hesaplamas�na eklenmesi gerekecektir. 
Ve b�leni g�ncellemeyi hat�rlad�n�z m�? Unuttuysan�z, art�k semantik bir hatan�z var. Mevcut kodu her de�i�tirdi�inizde, hatalar olu�turma riskiniz
vard�r.

�imdiye kadar, bir s�r� ilgili de�i�kenimiz oldu�unda bir dizi kullanmam�z gerekti�ini biliyorsunuz. O zaman bireysel de�i�kenlerimizi 
bir std::vector ile de�i�tirelim:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector testScore { 84, 92, 76, 81, 56 };
                    std::size_t length { testScore.size() };

                    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
                        / static_cast<int>(length) };

                    std::cout << "S�n�f ortalamas�: " << average << '\n';

                    return 0;
                }

Bu daha iyi -- tan�mlanan de�i�ken say�s�n� �nemli �l��de azaltt�k ve ortalama hesaplaman�n b�leni art�k do�rudan dizinin uzunlu�undan belirleniyor.
Ancak ortalama hesaplama hala bir sorun, ��nk� her ��eyi tek tek manuel olarak listelemek zorunday�z. Ve her ��eyi a��k�a listelemek zorunda 
oldu�umuz i�in, ortalama hesaplamam�z yaln�zca listelenen kadar �ok ��esi olan diziler i�in �al���r. E�er ayr�ca di�er uzunluklardaki dizilerin
ortalamas�n� da alabilmek istiyorsak, her farkl� dizi uzunlu�u i�in yeni bir ortalama hesaplama yazmam�z gerekecek.

Ger�ekten ihtiyac�m�z olan �ey, her dizi ��esine eri�ebilmek i�in her birini a��k�a listelememize gerek kalmadan bir yol.

Diziler ve d�ng�ler
-------------------
�nceki derslerde, dizi subcriptlerinin sabit ifadeler olmas� gerekmedi�ini -- bunlar�n �al��ma zaman� ifadeleri olabilece�ini belirttik. 
Bu, bir de�i�kenin de�erini bir index olarak kullanabilece�imiz anlam�na gelir.

Ayr�ca, �nceki �rnekteki ortalama hesaplamada kullan�lan dizi indekslerinin artan bir dizi oldu�unu da not edin: 0, 1, 2, 3, 4. Bu nedenle, 
bir de�i�keni s�rayla 0, 1, 2, 3 ve 4 de�erlerine ayarlayabilecek bir yolumuz olsayd�, o zaman bu de�i�keni dizi indeksi olarak kullanabiliriz 
yerine literaller. Ve bunu nas�l yapaca��m�z� zaten biliyoruz -- bir for-d�ng�s� ile.

Yukar�daki �rne�i, d�ng� de�i�keninin dizi indeksi olarak kullan�ld��� bir for-d�ng�s� kullanarak yeniden yazal�m:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector testScore { 84, 92, 76, 81, 56 };
                    std::size_t length { testScore.size() };

                    int average { 0 };
                    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
                        average += testScore[index];                      // add the value of element with index `index`
                    average /= static_cast<int>(length);                  // calculate the average

                    std::cout << "Average of Class: " << average << '\n';

                    return 0;
                }

Bu olduk�a basit olmal�. index 0'da ba�lar, testScore[0] ortalama'ya eklenir ve index 1 art�r�l�r. testScore[1] ortalama'ya eklenir ve index 2
art�r�l�r. Sonunda, index 5 art�r�ld���nda, index < length yanl�� olur ve d�ng� sona erer. Bu noktada, d�ng� testScore[0], testScore[1],
testScore[2], testScore[3] ve testScore[4]'�n de�erlerini ortalama'ya eklemi�tir. Son olarak, biriken de�erleri dizi uzunlu�una b�leriz ve 
ortalamam�z� hesaplar�z.

Bu ��z�m, bak�m a��s�ndan idealdir. D�ng�n�n ka� kez yineledi�i, dizinin uzunlu�undan belirlenir ve d�ng� de�i�keni, t�m dizi indekslemesini yapmak
i�in kullan�l�r. Art�k her bir dizi eleman�n� manuel olarak listelememiz gerekmiyor.

Bir test skoru eklemek veya ��karmak istiyorsak, yaln�zca dizi ba�lat�c�lar�n�n say�s�n� de�i�tirebiliriz ve kodun geri kalan� daha fazla
de�i�iklik yapmadan hala �al���r!

Bir konteyn�r�n her bir eleman�na belirli bir s�rayla eri�mek, konteyn�r� dola�ma ( traversal ) veya konteyn�r� gezinme olarak adland�r�l�r.
Dola�ma ayr�ca bazen konteyn�r �zerinde yineleme veya konteyn�r i�inden yineleme olarak adland�r�l�r.

Yazar�n Notu
------------
Konteyn�r s�n�flar�, uzunluk ve indeksler i�in size_t tipini kulland���ndan, bu derste ayn�s�n� yapaca��z. i�aretli uzunluklar� ve indeksleri
kullanmay� gelecek ders olan 16.7 -- Arrays, loops, and sign challenge solutions dersinde tart��aca��z.

�ablonlar, diziler ve d�ng�ler �l�eklenebilirli�i a�ar
------------------------------------------------------
*-Diziler, her bir elemana isim vermeden birden �ok nesneyi saklama olana�� sa�lar.
*-D�ng�ler, her bir eleman� a��k�a listelemeden bir diziyi dola�ma olana�� sa�lar.
*-�ablonlar, eleman tipini parametrize etme olana�� sa�lar.

Birlikte, �ablonlar, diziler ve d�ng�ler, eleman tipine veya konteyn�rda bulunan elemanlar�n say�s�na bak�lmaks�z�n, bir konteyn�r�n elemanlar� 
�zerinde i�lem yapabilecek kodlar� yazmam�za olanak sa�lar!

Bunu daha da a��klamak i�in, yukar�daki �rne�i yeniden yazal�m, ortalama hesaplamas�n� bir fonksiyon �ablonuna �evirelim:

                #include <iostream>
                #include <vector>

                // std::vector'deki de�erlerin ortalamas�n� hesaplamak i�in fonksiyon �ablonu
                template <typename T>
                T calculateAverage(const std::vector<T>& arr)
                {
                    std::size_t length { arr.size() };

                    T average { 0 };                                  // e�er dizimiz T tipinde elemanlara sahipse, ortalamam�z da T tipinde olmal�
                    for (std::size_t index{ 0 }; index < length; ++index) // t�m elemanlar� d�ng�ye al
                        average += arr[index];                            // t�m elemanlar� topla
                    average /= static_cast<int>(length);

                    return average;
                }

                int main()
                {
                    std::vector class1 { 84, 92, 76, 81, 56 };
                    std::cout << "S�n�f 1'in ortalamas�: " << calculateAverage(class1) << '\n'; // 5 int'in ortalamas�n� hesapla

                    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
                    std::cout << "S�n�f 2'nin ortalamas�: " << calculateAverage(class2) << '\n'; // 4 double'�n ortalamas�n� hesapla

                    return 0;
                }

                Bu, �unu yazd�r�r:

                S�n�f 1'in ortalamas�: 77
                S�n�f 2'nin ortalamas�: 81.75
Yukar�daki �rnekte, herhangi bir eleman tipine ve herhangi bir uzunlu�a sahip bir std::vector al�p, ortalamay� d�nd�ren calculateAverage() 
ad�nda bir fonksiyon �ablonu olu�turduk. main() i�inde, bu fonksiyonun 5 int eleman� olan bir diziyle veya 4 double eleman� olan bir diziyle
�a�r�ld���nda e�it derecede iyi �al��t���n� g�steriyoruz!

calculateAverage() fonksiyonu, fonksiyon i�inde kullan�lan operat�rleri destekleyen herhangi bir T tipi i�in �al��acakt�r (operator+=(T),
operator/=(int)). Bu operat�rleri desteklemeyen bir T kullanmay� denerseniz, derleyici, �rnekle�tirilmi� fonksiyon �ablonunu derlemeye �al���rken
hata verecektir.

Diziler ve d�ng�lerle neler yapabilece�iz
-----------------------------------------
Bir eleman konteynerini bir d�ng� kullanarak nas�l gezinece�imizi bildi�imize g�re, konteyner gezinmesini ne i�in kullanabilece�imize bakal�m.
Genellikle bir konteyneri d�rt �ey yapmak i�in geziniriz:

*- Mevcut elemanlar�n de�erine dayal� yeni bir de�er hesapla (�r. ortalama de�er, de�erlerin toplam�).
*- Mevcut bir eleman� ara (�r. tam e�le�me var m�, e�le�me say�s�n� say, en y�ksek de�eri bul).
*- Her bir eleman �zerinde i�lem yap (�r. her bir eleman� ��kt� olarak ver, t�m elemanlar� 2 ile �arp).
*- Elemanlar� yeniden s�rala (�r. elemanlar� artan s�rayla s�rala).
* 
Bu i�lemlerin ilk ��� olduk�a basittir. Her bir eleman� uygun �ekilde incelemek veya de�i�tirmek i�in tek bir d�ng� kullanabiliriz. Bir konteynerin
elemanlar�n� yeniden s�ralamak biraz daha zordur, ��nk� bunu yapmak genellikle ba�ka bir d�ng�n�n i�inde bir d�ng� kullanmay� gerektirir.
Bunu manuel olarak yapabiliriz, ancak genellikle bunu yapmak i�in standart k�t�phaneden mevcut bir algoritmay� kullanmak daha iyidir. Algoritmalar�
tart��aca��m�z bir gelecek b�l�mde bunu daha ayr�nt�l� olarak ele alaca��z.

Diziler ve bir fazla hatalar -> For d�ng�s�nde anlat�ld� ayn�s� oldu�u i�in ge�tim. 

16.7 � Diziler, d�ng�ler ve i�aret sorunlar� ��z�mleri
------------------------------------------------------
4.5 -- i�aretsiz tam say�lar ve neden onlardan ka��nmal�y�z dersinde, genellikle miktarlar� tutmak i�in i�aretli de�erleri kullanmay� tercih 
etti�imizi belirttik, ��nk� i�aretsiz de�erler �a��rt�c� �ekillerde davranabilir. Ancak, 16.3 -- std::vector ve i�aretsiz uzunluk ve subscript 
problemi dersinde, std::vector'�n (ve di�er konteyner s�n�flar�n�n) uzunluk ve indeksler i�in i�aretsiz integral t�r� std::size_t'yi kulland���n�
tart��t�k. Bu, a�a��daki gibi sorunlara yol a�abilir:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printReverse(const std::vector<T>& arr)
                {
                    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index i�aretsizdir
                    {
                        std::cout << arr[index] << ' ';
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

                    printReverse(arr);

                    return 0;
                }

                Bu kod, diziyi tersine �evirerek yazd�rmaya ba�lar:

                9 1 2 8 3 7 6 4
Ve sonra tan�ms�z bir davran�� sergiler. ��p de�erler yazd�rabilir veya uygulaman�n ��kmesine neden olabilir. Burada iki sorun var. �lk olarak, 
d�ng�m�z index >= 0 oldu�u s�rece (di�er bir deyi�le, index pozitif oldu�u s�rece) �al���r, bu da index'in i�aretsiz oldu�unda her zaman do�ru 
oldu�u anlam�na gelir. Bu y�zden d�ng� asla sona ermez.

�kincisi, indeksi 0 de�erinde azaltt���m�zda, b�y�k bir pozitif de�ere sarar, bu de�eri daha sonra bir sonraki yinelemede diziyi indekslemek 
i�in kullan�r�z. Bu, s�n�rlar�n d���nda bir indekstir ve tan�ms�z davran��a neden olur. Dizimiz bo�sa ayn� sorunla kar��la��r�z.

Ve bu t�r �zel sorunlar� ��zmenin bir�ok yolu olsa da, bu t�r sorunlar hata m�knat�lar�d�r.

Bir d�ng� de�i�keni i�in i�aretli bir t�r kullanmak bu t�r sorunlardan daha kolay ka��n�r, ancak kendi zorluklar� vard�r. ��te i�aretli bir indeks
kullanan yukar�daki sorunun bir versiyonu:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printReverse(const std::vector<T>& arr)
                {
                    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index i�aretlidir
                    {
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

                    printReverse(arr);

                    return 0;
                }

Bu versiyon, ama�land��� gibi i�lev g�r�r, ancak eklenen iki static_cast nedeniyle kod da karma��kt�r. arr[static_cast<std::size_t>(index)]
�zellikle okumas� zordur. Bu durumda, g�venli�i okunabilirlik pahas�na �nemli �l��de art�rd�k.

��te i�aretli indeks kullanman�n ba�ka bir �rne�i:

                #include <iostream>
                #include <vector>

                // Bir std::vector'deki ortalama de�eri hesaplamak i�in fonksiyon �ablonu
                template <typename T>
                T calculateAverage(const std::vector<T>& arr)
                {
                    int length{ static_cast<int>(arr.size()) };

                    T average{ 0 };
                    for (int index{ 0 }; index < length; ++index)
                        average += arr[static_cast<std::size_t>(index)];
                    average /= length;

                    return average;
                }

                int main()
                {
                    std::vector testScore1 { 84, 92, 76, 81, 56 };
                    std::cout << "S�n�f 1 ortalamas�: " << calculateAverage(testScore1) << '\n';

                    return 0;
                }
Kodumuzun static_cast'lerle dolmas� olduk�a k�t�. Peki ne yapmal�y�z? Bu, ideal bir ��z�m�n olmad��� bir aland�r.

Burada bir�ok ge�erli se�enek var, bunlar� en k�t�den en iyisine do�ru s�ralayaca��z. Di�erleri taraf�ndan yaz�lan kodda bunlar�n hepsini
muhtemelen kar��la�acaks�n�z.

Yazar�n Notu
------------
Bu konuyu std::vector ba�lam�nda tart��acak olsak da, t�m standart k�t�phane konteynerleri (�rne�in std::array) benzer �ekilde �al���r ve ayn�
zorluklara sahiptir. A�a��daki tart��ma, bunlar�n herhangi birine uygulanabilir.

Signed/unsigned d�n���m uyar�lar�n� kapat�n
-------------------------------------------     
E�er signed/unsigned d�n���m uyar�lar�n�n genellikle varsay�lan olarak devre d��� b�rak�ld���n� merak ediyorsan�z, bu konu ana nedenlerden biridir.
Her seferinde bir standart k�t�phane konteynerini bir i�aretli indeks kullanarak alt dizinledi�imizde, bir i�aret d�n���m uyar�s� olu�turulur. 
Bu, derleme g�nl���n�z� gereksiz uyar�larla h�zla doldurur, ger�ekten me�ru olan uyar�lar� bo�ar.

Bu y�zden, bir s�r� signed/unsigned d�n���m uyar�s�yla u�ra�mak zorunda kalmamak i�in bir yol, bu uyar�lar� basit�e kapal� b�rakmakt�r.

Bu en basit ��z�m, ancak bunu �nermiyoruz, ��nk� bu ayn� zamanda hatalara neden olabilecek me�ru i�aret d�n���m uyar�lar�n�n olu�turulmas�n� da
engeller.

Unsigned d�ng� de�i�keni kullanma
---------------------------------
Bir�ok geli�tirici, standart k�t�phane dizi t�rlerinin i�aretsiz indeksler kullanmak �zere tasarland���na inan�r, bu y�zden i�aretsiz indeksler 
kullanmal�y�z! Bu tamamen makul bir pozisyon. Sadece signed/unsigned uyumsuzluklar�na kar�� ekstra dikkatli olmam�z gerekiyor. M�mk�nse, indeks 
d�ng� de�i�kenini yaln�zca indeksleme i�in kullan�n.

Bu yakla��m� kullanmaya karar verirsek, hangi i�aretsiz t�r�n� ger�ekten kullanmal�y�z?

16.3 -- std::vector ve i�aretsiz uzunluk ve alt dizi problemi dersinde, standart k�t�phane konteyner s�n�flar�n�n i� i�e ge�mi� typedef size_type'�
tan�mlad���n� belirttik, bu bir i�aretsiz integral t�rd�r ve dizi uzunluklar� ve indeksler i�in kullan�l�r. size() �ye fonksiyonu size_type
d�nd�r�r ve operator[] bir indeks olarak size_type kullan�r, bu y�zden indeksinizin t�r� olarak size_type kullanmak teknik olarak en tutarl� ve 
g�venli i�aretsiz t�r�n� kullanmakt�r (bu, t�m durumlarda �al���r, hatta size_type'�n size_t'den ba�ka bir �ey olmad��� son derece nadir durumda 
bile). �rne�in:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr { 1, 2, 3, 4, 5 };

                    for (std::vector<int>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';

                    return 0;
                }

Ancak, size_type kullanman�n b�y�k bir dezavantaj� vard�r: i� i�e ge�mi� bir t�r oldu�u i�in, onu kullanmak i�in ad�n tamamen �ablonlu ad�yla
a��k�a �ne ��kmam�z gerekiyor (yani std::vector<int>::size_type yazmak yerine sadece std::size_type yazmam�z gerekiyor). Bu, �ok fazla yazmay� 
gerektirir, okumas� zordur ve konteyner ve ��e t�r�ne ba�l� olarak de�i�ir.

Bir fonksiyon �ablonu i�inde kullan�ld���nda, �ablon arg�manlar� i�in T'yi kullanabiliriz. Ancak t�r� typename anahtar kelimesiyle �ne ��karmam�z
da gerekiyor:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printArray(const std::vector<T>& arr)
                {
                    // ba��ml� tip i�in typename anahtar kelime �neki gereklidir
                    for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';
                }

                int main()
                {
                    std::vector arr { 9, 7, 5, 3, 1 };

                    printArray(arr);

                    return 0;
                }
E�er typename anahtar kelimesini unutursan�z, derleyiciniz muhtemelen size onu eklemenizi hat�rlatacakt�r.

Bazen dizi tipinin, d�ng�y� daha kolay okunabilir hale getirmek i�in takma adla�t�r�ld���n� g�rebilirsiniz:

                using arrayi = std::vector<int>;
                for (arrayi::size_type index { 0 }; index < arr.size(); ++index)
                
Daha genel bir ��z�m, derleyicinin bizim i�in dizi tipi nesnesinin tipini getirmesidir, b�ylece konteyner tipini veya �ablon arg�manlar�n� a��k�a
belirtmek zorunda kalmay�z. Bunu yapmak i�in, parametresinin tipini d�nd�ren decltype anahtar kelimesini kullanabiliriz.

                // arr baz� referans olmayan bir tip
                for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index) // decltype(arr) std::vector<int>'i ��zer

Ancak, arr bir referans tipi ise (�r. referansla ge�irilen bir dizi), yukar�daki i�e yaramaz. �lk �nce arr'dan referans� kald�rmam�z gerekiyor:

                template <typename T>
                void printArray(const std::vector<T>& arr)
                {
                    // arr bir referans veya referans olmayan tip olabilir
                    for (typename std::remove_reference_t<decltype(arr)>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';
                }

Ne yaz�k ki, bu art�k �ok �zl� veya kolay hat�rlanabilir de�il.

��nk� size_type neredeyse her zaman size_t i�in bir typedef oldu�u i�in, bir�ok programc� size_type'� tamamen atlar ve daha kolay hat�rlanabilir
ve yaz�labilir std::size_t'yi do�rudan kullan�r:

                for (std::size_t index { 0 }; index < arr.size(); ++index)

�zel bellek ay�r�c�lar� kullanm�yorsan�z (ve muhtemelen kullanm�yorsunuzdur), bunun makul bir yakla��m oldu�una inan�yoruz.

��aretli d�ng� de�i�keni kullanma
---------------------------------
Standart k�t�phane konteyner tipleriyle �al��may� biraz daha zorla�t�rsa da, i�aretli bir d�ng� de�i�keni kullanmak, kodumuzun geri kalan�nda
uygulanan en iyi uygulamalarla tutarl�d�r (miktarlar i�in i�aretli de�erleri tercih etmek). Ve en iyi uygulamalar�m�z� ne kadar tutarl� bir �ekilde
uygularsak, genel olarak o kadar az hatam�z olur.

E�er i�aretli d�ng� de�i�kenleri kullanmay� d���n�yorsak, ele al�nmas� gereken �� konu var:

*- Hangi i�aretli tipi kullanmal�y�z?
*- Dizinin uzunlu�unu i�aretli bir de�er olarak alma
*- ��aretli d�ng� de�i�kenini i�aretsiz bir indekse d�n��t�rme

Hangi i�aretli tipi kullanmal�y�z?
----------------------------------
Burada �� (bazen d�rt) iyi se�enek var.

1 - �ok b�y�k bir diziyle �al��m�yorsan�z, int kullanmak iyidir (�zellikle int'in 4 byte oldu�u mimarilerde). int, tipin aksi halde �nemli olmad���
    her �ey i�in kulland���m�z varsay�lan i�aretli integral tipidir ve burada aksi y�nde bir sebep yoktur.

2 - �ok b�y�k dizilerle u�ra��yorsan�z veya biraz daha savunmac� olmak istiyorsan�z, garip adl� std::ptrdiff_t'yi kullanabilirsiniz. Bu typedef,
    genellikle std::size_t'nin i�aretli kar��l��� olarak kullan�l�r.

3 - ��nk� std::ptrdiff_t'nin garip bir ad� var, ba�ka iyi bir yakla��m, indeksler i�in kendi tip takma ad�n�z� tan�mlamakt�r:

                using Index = std::ptrdiff_t;

                // �rnek d�ng� index kullanarak
                for (Index index{ 0 }; index < static_cast<Index>(arr.size()); ++index)
Bunu bir sonraki b�l�mde tam bir �rnekle g�sterece�iz.

Kendi tip takma ad�n�z� tan�mlamak da potansiyel bir gelecek faydas� vard�r: e�er C++ standart k�t�phanesi bir g�n i�aretli bir index olarak 
kullan�lmak �zere tasarlanm�� bir tip yay�nlarsa, Index'i o tipi taklit etmek i�in de�i�tirmek veya Index'i ne olursa olsun o tipin ad�yla bulup 
de�i�tirmek kolay olacakt�r.

4 - D�ng� de�i�keninizin tipini ba�lat�c�dan t�retebilece�iniz durumlarda, derleyicinin tipi ��karmas�n� sa�lamak i�in auto kullanabilirsiniz:

                for (auto index{ static_cast<std::ptrdiff_t>(arr.size())-1 }; index >= 0; --index)

C++23'te, Z soneki std::size_t'nin i�aretli kar��l��� olan bir tipin (muhtemelen std::ptrdiff_t) �rne�ini tan�mlamak i�in kullan�labilir:

                for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)

Bir dizinin uzunlu�unu i�aretli bir de�er olarak alma
---------------------------------------------------
1 - C++20'den �nce, en iyi se�enek size() �ye fonksiyonunun veya std::size()'�n d�n�� de�erini i�aretli bir tipe static_cast yapmakt�r:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    for (auto index{ static_cast<Index>(arr.size())-1 }; index >= 0; --index)
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
Bu �ekilde, arr.size() taraf�ndan d�nd�r�len unsigned de�er, kar��la�t�rma operat�r�m�z�n iki i�aretli i�lemciye sahip olmas� i�in bir i�aretli 
tipe d�n��t�r�l�r. Ve i�aretli indeksler negatif oldu�unda ta�mayaca�� i�in, unsigned indeksler kullan�rken kar��la�t���m�z wrap-around sorunu
olmayacak.

Bu yakla��m�n dezavantaj�, d�ng�m�z� kar��t�rmas� ve okumas�n� zorla�t�rmas�d�r. Bunu, uzunlu�u d�ng�den ��kararak bu sorunu ��zebiliriz:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    auto length{ static_cast<Index>(arr.size()) };
                    for (auto index{ length-1 }; index >= 0; --index)
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
2 - C++20'de, std::ssize() kullan�n:
C++'n�n tasar�mc�lar�n�n art�k i�aretli indekslerin yolunun bu oldu�una inand���n� daha fazla kan�t istiyorsan�z, C++20'de std::ssize()'�n
tan�t�lmas�n� d���n�n. Bu fonksiyon, bir dizi tipinin boyutunu i�aretli bir tip olarak (muhtemelen ptrdiff_t) d�nd�r�r.

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    for (auto index{ std::ssize(arr)-1 }; index >= 0; --index) // std::ssize C++20'de tan�t�ld�
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
i�aretli d�ng� de�i�kenini unsigned bir indekse d�n��t�rme

Bir kez i�aretli bir d�ng� de�i�kenine sahip oldu�umuzda, bu i�aretli d�ng� de�i�kenini bir indeks olarak kullanmaya �al��t���m�zda her zaman
implicit i�aret d�n���m uyar�lar� alaca��z. Bu y�zden i�aretli d�ng� de�i�kenimizi bir indeks olarak kullanmay� d���nd���m�z her yerde unsigned bir
de�ere d�n��t�rmenin bir yoluna ihtiyac�m�z var.

1 - A��k se�enek, i�aretli d�ng� de�i�kenimizi unsigned bir indekse static_cast yapmakt�r. Bunu �nceki �rnekte g�steriyoruz. Ne yaz�k ki, bunu 
    dizinin her alt dizininde yapmam�z gerekiyor ve bu, dizinin indekslerini okumas�n� zorla�t�r�yor.

2 - K�sa bir ad� olan bir d�n���m fonksiyonu kullan�n:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                constexpr std::size_t toUZ(Index value)
                {
                    return static_cast<std::size_t>(value);
                }

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    auto length { static_cast<Index>(arr.size()) };  // C++20'de, std::ssize() tercih edilir
                    for (auto index{ length-1 }; index >= 0; --index)
                        std::cout << arr[toUZ(index)] << ' '; // i�aret d�n���m uyar�s�n� �nlemek i�in toUZ() kullan�n

                    return 0;
                }
Yukar�daki �rnekte, Index tipindeki de�erleri std::size_t tipindeki de�erlere d�n��t�rmek �zere tasarlanm�� toUZ() ad�nda bir fonksiyon olu�turduk.
Bu, dizimizi arr[toUZ(index)] olarak indekslememize izin verir, bu da olduk�a okunabilir.

3 - �zel bir g�r�n�m kullanma

�nceki derslerde, std::string'in bir stringe sahip oldu�unu, std::string_view'in ise ba�ka bir yerde var olan bir stringe bir g�r�n�m sundu�unu
tart��t�k. std::string_view'in g�zel yanlar�ndan biri, farkl� t�rdeki stringlere (C tarz� string literalleri, std::string ve di�er std::string_view)
bakabilmesi ancak bizim i�in tutarl� bir aray�z sa�lamas�d�r.

Standart k�t�phane konteynerlerini i�aretli integral bir indeks kabul edecek �ekilde de�i�tiremesek de, standart k�t�phane konteyner s�n�f�n� 
"g�rmek" i�in kendi �zel g�r�n�m s�n�f�m�z� olu�turabiliriz. Bunu yaparak, kendi aray�z�m�z� istedi�imiz gibi tan�mlayabiliriz.

A�a��daki �rnekte, indekslemeyi destekleyen herhangi bir standart k�t�phane konteynerini g�rebilen bir �zel g�r�n�m s�n�f� tan�ml�yoruz.
Aray�z�m�z iki �ey yapacak:

*- Bize, i�aretli integral bir t�rle operator[] kullanarak elemanlara eri�me imkan� sa�lar.
*- Konteynerin uzunlu�unu i�aretli integral bir t�r olarak al�r (��nk� std::ssize() yaln�zca C++20'de mevcuttur).

Bu, operator[]'i uygulamak i�in hen�z ele almad���m�z bir konu olan operat�r a��r� y�klemeyi kullan�r. SignedArrayView'in nas�l uyguland���n� 
bilmeye gerek yoktur, onu kullanabilirsiniz.

                SignedArrayView.h:


                #ifndef SIGNED_ARRAY_VIEW_H
                #define SIGNED_ARRAY_VIEW_H

                #include <cstddef> // for std::size_t and std::ptrdiff_t

                // SignedArrayView provides a view into a container that supports indexing
                // allowing us to work with these types using signed indices
                template <typename T>
                class SignedArrayView // C++17
                {
                private:
                    T& m_array;

                public:
                    using Index = std::ptrdiff_t;

                    SignedArrayView(T& array)
                        : m_array{ array } {}

                    // Overload operator[] to take a signed index
                    constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
                    constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
                    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
                };

                #endif

                main.cpp:


                #include <iostream>
                #include <vector>
                #include "SignedArrayView.h"

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };
                    SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

                    for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
                        std::cout << sarr[index] << ' '; // index using a i�aretlitype

                    return 0;
                }

Tek mant�kl� se�enek: indekslemeyi tamamen b�rak�n!

Yukar�da sunulan t�m se�eneklerin kendi dezavantajlar� vard�r, bu y�zden bir yakla��m� di�erine tercih etmek zordur. Ancak, di�erlerinden �ok daha
mant�kl� olan bir se�enek var: integral de�erlerle indekslemeyi tamamen b�rak�n.

C++, indeks kullanmadan dizilerden ge�mek i�in birka� ba�ka y�ntem sa�lar. Ve indekslerimiz olmad���nda, bu signed/unsigned d�n���m sorunlar�na 
girmez.

�ndeksler olmadan dizi gezinmesi i�in iki yayg�n y�ntem aral�kl� d�ng�ler ( range-based for loops ) ve yineleyicilerdir ( iterators ).
E�er diziyi gezinmek i�in yaln�zca indeks de�i�kenini kullan�yorsan�z, indeks kullanmayan bir y�ntemi tercih edin.

*** BEST -> M�mk�n oldu�unda integral de�erlerle dizi indekslemekten ka��n�n.

16.8 � Range-based for loops (for-each) ( kapsam bazl� d�ng�ler )
-----------------------------------------------------------------
16.6 -- Diziler ve d�ng�ler dersinde, bir dizi de�i�keni olarak bir d�ng� de�i�keni kullanarak bir dizi �zerinde her bir ��eyi yinelemek i�in bir
for d�ng�s� kulland���m�z �rnekleri g�sterdik. ��te b�yle bir �rne�in daha:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    std::size_t length { fibonacci.size() };
                    for (std::size_t index { 0 }; index < length; ++index)
                       std::cout << fibonacci[index] << ' ';

                    std::cout << '\n';

                    return 0;
                }

For d�ng�leri, bir dizinin �zerinden ge�mek i�in uygun ve esnek bir yol sa�lasa da, kolayca hata yap�labilir, bir fazla/bir eksik hatalar�na
e�ilimlidir ve dizi indeksleme i�aret problemlar�na tabidir.

Bir dizinin (ileri do�ru) �zerinden ge�mek bu kadar yayg�n bir i�lem oldu�u i�in, C++ ba�ka bir t�r for d�ng�s�n� destekler, buna range-based for 
d�ng�s� (bazen for-each d�ng�s� olarak da adland�r�l�r) denir ve a��k�a indeksleme yapmadan bir konteynerin �zerinden ge�meyi sa�lar. Range-based 
for d�ng�leri daha basit, daha g�venli ve C++'daki t�m yayg�n dizi t�rleriyle (std::vector, std::array ve C tarz� diziler dahil) �al���r.

Range-based for d�ng�leri
-------------------------
Range-based for ifadesinin �u �ekilde bir s�zdizimi vard�r:

                for (element_declaration : array_object)
                   statement;

Bir range-based for d�ng�s� kar��la��ld���nda, d�ng� array_object'teki her bir ��eyi yineleyecektir. Her yineleme i�in, ge�erli dizi ��esinin
de�eri element_declaration'da bildirilen de�i�kene atan�r ve ard�ndan statement ifadesi �al��t�r�l�r.

En iyi sonu�lar i�in, element_declaration dizi ��eleriyle ayn� t�rde olmal�d�r, aksi takdirde t�r d�n���m� ger�ekle�ir.
��te, fibonacci adl� bir dizideki t�m ��eleri yazd�rmak i�in bir range-based for d�ng�s� kullanan basit bir �rnek:

#include <iostream>
#include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    for (int num : fibonacci) // fibonacci dizisi �zerinde yinele ve her de�eri `num`a kopyala
                       std::cout << num << ' '; // `num`un ge�erli de�erini yazd�r

                    std::cout << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:
                0 1 1 2 3 5 8 13 21 34 55 89
Bu �rnekte, dizinin uzunlu�unu kullanmam�z veya diziyi indekslememiz gerekmiyor! Bu nas�l �al��t���na daha yak�ndan bakal�m.
Bu range-based for d�ng�s�, fibonacci'nin t�m ��eleri �zerinde �al��acakt�r. �lk yineleme i�in, num de�i�kenine ilk ��enin (0) de�eri atan�r. 
Ard�ndan program, num'un (0) de�erini konsola yazd�ran ili�kili ifadeyi �al��t�r�r. �kinci yineleme i�in, num ikinci ��enin (1) de�erine atan�r. 
�li�kili ifade tekrar �al��t�r�l�r, bu 1'i yazd�r�r. Range-based for d�ng�s�, her biri i�in ili�kili ifadeyi �al��t�rarak dizinin her bir ��esi
�zerinde s�rayla yinelemeye devam eder, ta ki dizide yinelenecek ba�ka ��e kalmayana kadar. Bu noktada, d�ng� sona erer ve program y�r�tmesine
devam eder (bir sat�r sonu yazd�r�r ve ard�ndan i�letim sistemine 0 d�nd�r�r).

Anahtar nokta �udur ki; Bildirilen ��e (�nceki �rnekte num) bir dizi indeksi de�ildir. Bunun yerine, �zerinde yinelendi�i dizi ��esinin de�eri 
atan�r. Num, dizi ��esinin de�erine atan�r ��nk� bu, dizi ��esinin kopyaland��� anlam�na gelir (bu, baz� t�rler i�in pahal� olabilir).

*** BEST -> Konteynerleri dola��rken range-based for d�ng�lerini d�zenli for d�ng�lerine tercih edin.

Aral�k-tabanl� for d�ng�leri ve auto anahtar kelimesi kullanarak tip ��kar�m�
-----------------------------------------------------------------------------
element_declaration'�n, dizi ��eleriyle ayn� tip olmas� gerekti�i i�in (tip d�n���m�n�n olu�mas�n� �nlemek i�in), bu, auto anahtar kelimesini
kullanman�n ve derleyicinin bizim i�in dizi ��elerinin tipini ��karmas�n�n ideal bir durumdur. Bu �ekilde, tipi gereksiz yere belirtmek zorunda
kalmay�z ve yanl�� yazma riski yoktur.

��te yukar�daki ayn� �rnek, ancak num'�n tipi auto olarak:
    
                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    for (auto num : fibonacci) // derleyici num'un tipini `int` olarak ��karacak
                       std::cout << num << ' ';

                    std::cout << '\n';

                    return 0;
                }
��nk� std::vector fibonacci'nin ��eleri int tipindedir, num bir int olarak ��kar�lacakt�r.

*** BEST -> Dizi ��esinin tipini derleyicinin ��karmas� i�in aral�k-tabanl� for d�ng�lerinde tip ��kar�m�n� (auto) kullan�n.

Auto'yu kullanman�n bir ba�ka avantaj� da, dizi ��esinin tipi her g�ncellendi�inde (�r. int'ten long'a), auto otomatik olarak g�ncellenmi� ��e
tipini ��kar�r, bunlar�n senkron kalmas�n� sa�lar (ve tip d�n���m�n�n olu�mas�n� �nler).

��e kopyalar�ndan ka��n�n, referanslar� kullan�n
------------------------------------------------
Bir dizi std::string �zerinde yineleyen a�a��daki aral�k-tabanl� for d�ng�s�n� d���n�n:

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // std::string literalleri i�in s soneki
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // std::vector<std::string>

                    for (auto word : words)
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Bu d�ng�n�n her yinelemesi i�in, words dizisinden sonraki std::string ��esi, word de�i�kenine atan�r (kopyalan�r). Bir std::string'i kopyalamak 
pahal�d�r, bu y�zden genellikle std::string'i fonksiyonlara const referans olarak ge�iririz. Ger�ekten bir kopyaya ihtiyac�m�z olmad�k�a,
kopyalamas� pahal� olan �eylerin kopyalar�n� yapmaktan ka��nmak isteriz. Bu durumda, sadece kopyan�n de�erini yazd�r�yoruz ve sonra kopya yok
ediliyor. Bir kopya yapmaktan ka��nmak ve sadece ger�ek dizi ��esine referans vermek daha iyi olurdu.

Neyse ki, element_declaration'�m�z� bir (const) referans yaparak tam olarak bunu yapabiliriz:

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // std::string literalleri i�in s soneki
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // std::vector<std::string>

                    for (const auto& word : words) // word art�k bir const referans
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Yukar�daki �rnekte, word art�k bir const referanst�r. Bu d�ng�n�n her yinelemesiyle, word sonraki dizi ��esine ba�lan�r. Bu, pahal� bir kopya
yapmak zorunda kalmadan dizi ��esinin de�erine eri�memizi sa�lar. Referans const olmayan ise, ayr�ca dizideki de�erleri de�i�tirmek i�in
kullan�labilir (element_declaration'�m�z de�erin bir kopyas� ise bu m�mk�n de�ildir).

*** BEST -> Aral�k-tabanl� for d�ng�lerinde, ��e bildirimi, normalde o ��e tipini (const) referans olarak ge�irdi�inizde bir (const) referans
            kullanmal�d�r.

Normalde ucuz kopyalanabilir t�rler i�in `auto` kullan�r�z ve pahal� kopyalanabilir t�rler i�in `const auto&` kullan�r�z. Ancak range-based for
d�ng�leriyle bir�ok geli�tirici, daha gelece�e dayan�kl� oldu�u i�in her zaman `const auto&` kullanman�n daha uygun oldu�una inan�r.

�rne�in, a�a��daki �rne�i d���n�n:

                #include <iostream>
                #include <string_view>
                #include <vector>

                int main()
                {
                    using namespace std::literals;
                    std::vector words{ "peter"sv, "likes"sv, "frozen"sv, "yogurt"sv }; // std::vector<std::string_view>

                    for (auto word : words) // Normalde string_view de�eri ge�eriz, bu y�zden burada auto kullanaca��z
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Bu �rnekte, `std::string_view` nesneleri i�eren bir `std::vector`'�m�z var. `std::string_view` normalde de�er olarak ge�ti�i i�in, `auto` kullanmak
uygun g�r�n�yor. Ancak, `words`'�n daha sonra bir `std::string` dizisine g�ncellendi�ini d���n�n.

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals;
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // buray� g�ncellemeliyiz

                    for (auto word : words) // Buray� da g�ncellememiz gerekti�i muhtemelen a��k de�il
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Range-based for d�ng�s� sorunsuz bir �ekilde derlenecek ve �al��acakt�r, ancak `word` art�k bir `std::string` olacakt�r ve `auto` kullan�ld��� i�in
d�ng�m�z sessizce `std::string` elemanlar�n�n pahal� kopyalar�n� yapacakt�r. B�y�k bir performans kayb� ya�ad�k!

Bu durumun olmamas�n� sa�lamak i�in birka� makul yol vard�r:

- Range-based for d�ng�n�zde t�r ��kar�m�n� kullanmay�n. E�er eleman t�r�n� `std::string_view` olarak a��k�a belirtmi� olsayd�k, daha sonra dizi 
  `std::string`'e g�ncellendi�inde, `std::string` elemanlar� sorunsuz bir �ekilde `std::string_view`'e d�n��t�r�l�rd�. E�er dizi daha sonra 
  d�n��t�r�lemez bir ba�ka t�re g�ncellenirse, derleyici hata verecektir ve o noktada ne yap�lmas� gerekti�ini anlayabiliriz.

- `auto` yerine range-based for d�ng�n�zde t�r ��kar�m� kullan�rken her zaman `const auto&` kullan�n. Bir referans �zerinden elemanlara eri�menin 
  de�er �zerinden eri�meye g�re performans cezas� muhtemelen k���k olacakt�r ve bu, eleman t�r� daha sonra kopyalamas� pahal� olan bir �eye
  de�i�tirilirse bizi potansiyel olarak �nemli performans cezalar�ndan korur.

�pucu

Bir range-based for d�ng�s�nde t�r ��kar�m� kullan�yorsan�z, kopyalarla �al��mak istemedi�iniz s�rece her zaman `const auto&` kullanmay� d���n�n.
Bu, eleman t�r� daha sonra de�i�tirilse bile kopyalar�n yap�lmayaca��n� garanti eder.

Range-based for d�ng�leri ve di�er standart konteyn�r t�rleri
-------------------------------------------------------------
Range-based for d�ng�leri, (decay olmam��) C-stil dizileri, `std::array`, `std::vector`, linked list, trees, ve maps dahil olmak �zere �e�itli dizi
t�rleriyle �al���r. Bunlar�n hi�birini hen�z ele almad�k, bu y�zden bunlar�n ne oldu�unu bilmiyorsan�z endi�elenmeyin. Sadece range-based for
d�ng�lerinin, yaln�zca `std::vector` �zerinde de�il, daha geni� bir yelpazede yineleme yapman�n esnek ve genel bir yolunu sa�lad���n� unutmay�n:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; // burada std::array kullan�l�yor

                    for (auto number : fibonacci)
                    {
                        std::cout << number << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }

Mevcut eleman�n indeksini alma
------------------------------
Aral�kl� d�ng�ler, mevcut eleman�n dizi indeksini do�rudan alman�n bir yolunu sa�lamaz. Bu, bir aral�kl� d�ng�n�n yineleyebilece�i bir�ok yap�
(�rne�in std::list) indeksleri desteklemedi�i i�indir.

Ancak, aral�kl� d�ng�ler her zaman ileri y�nde yinelendi�i ve elemanlar� atlamad��� i�in, her zaman kendi saya��n�z� bildirebilir 
(ve art�rabilirsiniz). Ancak bunu yapacaksan�z, bir aral�kl� d�ng� yerine normal bir d�ng� kullanman�n daha iyi olup olmad���n� d���nmelisiniz.

Ters aral�kl� d�ng�ler C++20
----------------------------
Aral�kl� d�ng�ler yaln�zca ileri s�radad�r. Ancak, bir diziyi ters s�rayla gezinmek istedi�imiz durumlar vard�r. C++20'den �nce, aral�kl� d�ng�ler
bu ama� i�in kolayca kullan�lamazd� ve ba�ka ��z�mler kullan�lmal�yd� (genellikle normal d�ng�ler).

Ancak, C++20 itibariyle, Ranges k�t�phanesinin std::views::reverse �zelli�ini kullanarak elemanlar�n tersine bir g�r�n�m�n� olu�turabilir ve 
yineleyebilirsiniz:

                #include <iostream>
                #include <ranges> // C++20
                #include <string_view>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // for sv suffix for std::string_view literals
                    std::vector words{ "Alex"sv, "Bobby"sv, "Chad"sv, "Dave"sv }; // sorted in alphabetical order

                    for (const auto& word : std::views::reverse(words)) // create a reverse view
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Dave
                Chad
                Bobby
                Alex
Ranges k�t�phanesini hen�z ele almad�k, bu y�zden bunu �imdilik yararl� bir sihir olarak d���n�n.

16.9 � Enumerat�rler kullanarak dizi indekslemesi ve uzunlu�u
-------------------------------------------------------------
Dizilerle ilgili daha b�y�k belgelendirme sorunlar�ndan biri, tamsay� indekslerinin programc�ya indeksin anlam� hakk�nda bilgi sa�lamamas�d�r.
5 test puan�n� tutan bir dizi d���n�n:

                #include <vector>

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    testScores[2] = 76; // bu kimin puan�n� temsil ediyor?
                }
testScores[2] taraf�ndan temsil edilen ��renci kimdir? Bu a��k de�il.

�ndekslemek i�in kapsams�z enumerat�rler kullanma
-------------------------------------------------
16.3 -- std::vector ve i�aretsiz uzunluk ve subscript problemi dersinde, std::vector<T>::operator[]'nin (ve subscript olabilen di�er 
C++ konteyner s�n�flar�n�n) indeksinin size_type t�r�nde oldu�unu, bu t�r�n genellikle std::size_t i�in bir takma ad oldu�unu tart��t�k.
Bu nedenle, indekslerimiz ya std::size_t t�r�nde olmal�, ya da std::size_t'ye d�n��en bir t�rde olmal�d�r.

Kapsams�z enumerasyonlar, std::size_t'ye do�rudan d�n��t�r�lece�inden, bu, kapsams�z enumerasyonlar� indeksin anlam�n� belgelemek i�in dizi 
indeksleri olarak kullanabilece�imiz anlam�na gelir:

                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    testScores[Students::stan] = 76; // �imdi stan'�n test puan�n� g�ncelliyoruz

                    return 0;
                }
Bu �ekilde, dizinin her bir eleman�n�n neyi temsil etti�i �ok daha a��k hale gelir. Enumerat�rlerin do�rudan constexpr oldu�u i�in, 
bir enumerat�r�n i�aretsiz integral bir t�re d�n��t�r�lmesi daralt�c� bir d�n���m olarak kabul edilmez, b�ylece signed/unsigned indeksleme 
sorunlar�ndan ka��n�l�r.

Non-constexpr Kapsams�z Enumerasyon ile �ndeksleme
--------------------------------------------------
Bir kapsams�z enumerasyonun alt t�r� uygulamaya ba�l�d�r (ve bu nedenle, ya bir i�aretli ya da i�aretsiz integral t�r� olabilir).
Enumerat�rlerin do�al olarak constexpr oldu�u i�in, kapsams�z enumerat�rlerle indekslemeye devam etti�imiz s�rece, i�aret d�n���m� 
sorunlar�yla kar��la�may�z.

Ancak, enumerasyon t�r�n�n non-constexpr bir de�i�kenini tan�mlar ve ard�ndan std::vector'�m�z� bununla indekslersek, kapsams�z enumerasyonlar�
bir i�aretli t�r�ne varsay�lan herhangi bir platformda i�aret d�n���m� uyar�lar� alabiliriz:

                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };
                    Students::Names name { Students::stan }; // non-constexpr

                    testScores[name] = 76; // Student::Names'in i�aretlibir alt t�r�ne varsay�lan bir durumda i�aret d�n���m� uyar�s� tetikleyebilir

                    return 0;
                }
name'i constexpr yapabilirdik (b�ylece bir constexpr i�aretli integral t�r�nden std::size_t'ye yap�lan d�n���m daralt�c� olmaz), 
ancak daha iyi bir yol var. Bunun yerine, enumerasyonun alt t�r�n� a��k�a bir i�aretsiz int olarak belirtebiliriz:

                #include <vector>

                namespace Students
                {
                    enum Names : unsigned int // alt t�r�n a��k�a i�aretsiz int oldu�unu belirtir
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };
                    Students::Names name { Students::stan }; // non-constexpr

                    testScores[name] = 76; // ad i�aretsiz oldu�u i�in bir i�aret d�n���m� de�il

                    return 0;
                }
Yukar�daki �rnekte, name'in art�k bir i�aretsiz int oldu�u garantilendi�inden, i�aret d�n���m� sorunlar� olmadan bir std::size_t'ye d�n��t�r�lebilir

Say�m Enumerat�r� Kullanma
--------------------------
Not edin ki, enumerat�r listesinin sonunda max_students ad�nda ekstra bir enumerat�r tan�mlad�k. �nceki t�m enumerat�rler varsay�lan de�erleri
kullan�yorsa (ki bu �nerilir), bu enumerat�r �nceki enumerat�rlerin say�s�n� e�le�tiren bir varsay�lan de�ere sahip olacakt�r.
Yukar�daki �rnekte, max_students de�eri 5'tir, ��nk� �nce 5 enumerat�r tan�mlanm��t�r. Resmi olmayan bir �ekilde, bunu bir say�m enumerat�r� olarak 
adland�raca��z, ��nk� de�eri �nceden tan�mlanm�� enumerat�rlerin say�s�n� temsil eder.

Bu say�m enumerat�r�, �nceki enumerat�rlerin bir say�s�na ihtiya� duydu�umuz her yerde kullan�labilir. �rne�in:

                #include <iostream>
                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        // gelecekteki enumerat�rleri buraya ekleyin
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector<int> testScores(Students::max_students); // 5 ��eli bir vector olu�tur

                    testScores[Students::stan] = 76; // �imdi stan'a ait test skorunu g�ncelliyoruz

                    std::cout << "S�n�fta " << Students::max_students << " ��renci var\n";

                    return 0;
                }
max_students'� iki yerde kullan�yoruz: �ncelikle, max_students uzunlu�unda bir std::vector olu�turuyoruz, b�ylece vector her ��renci i�in bir ��eye
sahip olacak. Ayr�ca max_students'� ��renci say�s�n� yazd�rmak i�in de kullan�yoruz.

Bu teknik ayr�ca g�zeldir ��nk� e�er ba�ka bir enumerat�r daha sonra eklenirse (max_students'ten hemen �nce), o zaman max_students otomatik olarak
bir daha b�y�k olacak ve max_students'i kullanan t�m dizilerimiz yeni uzunlu�u kullanmak �zere g�ncellenecektir.

                #include <vector>
                #include <iostream>

                namespace Ogrenciler
                {
                    enum Isimler
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        wendy, // 5 (eklendi)
                        // gelecekteki numaraland�r�c�lar� buraya ekleyin
                        max_ogrenciler // �imdi 6
                    };
                }

                int main()
                {
                    std::vector<int> testScores(Ogrenciler::max_ogrenciler); // �imdi 6 ��e ay�r�r

                    testScores[Ogrenciler::stan] = 76; // hala �al���r

                    std::cout << "S�n�fta " << Ogrenciler::max_ogrenciler << " ��renci var\n";

                    return 0;
                }

Bir say�m Enumerat�r� ile dizi uzunlu�unu do�rulama
---------------------------------------------------
Daha s�k olarak, bir dizi olu�tururken bir ba�latma listesi de�erlerini kullan�yoruz, bu diziyi numaraland�r�c�larla indeksleme niyetiyle.
Bu t�r durumlarda, konteynerin boyutunun say�m numaraland�r�c�m�za e�it oldu�unu do�rulamak yararl� olabilir. Bu do�rulama tetiklenirse, 
ya numaraland�r�c� listemiz bir �ekilde yanl��t�r, ya da yanl�� say�da ba�lat�c� sa�lam���zd�r. Bu, bir numaraland�r�c�n�n numaraland�rmaya 
yeni eklenmesi, ancak dizisine yeni bir ba�latma de�eri eklenmemesi durumunda kolayca olabilir �rne�in:

                #include <cassert>
                #include <iostream>
                #include <vector>

                enum OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 5
                };

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    // Test puanlar�n�n say�s�n�n ��renci say�s�yla ayn� oldu�undan emin olun
                    assert(std::size(testScores) == max_ogrenciler);

                    return 0;
                }
�pucu

E�er diziniz constexpr ise, o zaman static_assert kullanmal�s�n�z. std::vector constexpr'i desteklemez, ancak std::array (ve C tarz� diziler) yapar.

*** BEST -> constexpr dizinizin uzunlu�unun say�m numaraland�r�c�n�za uydu�undan emin olmak i�in bir static_assert kullan�n.
            non-constexpr dizinizin uzunlu�unun say�m numaraland�r�c�n�za uydu�undan emin olmak i�in bir assert kullan�n.

Diziler ve enum s�n�flar�
-------------------------
Kapsams�z numaraland�rmalar, numaraland�r�c�lar�yla birlikte tan�mland�klar� ad alan�n� kirletti�i i�in, numaraland�rma zaten ba�ka bir kapsam 
b�lgesinde (�r. bir ad alan� veya s�n�f) bulunmad��� durumlarda enum s�n�flar�n� kullanmak tercih edilir.

Ancak, enum s�n�flar�n�n integral tiplere do�rudan bir d�n���m� olmad��� i�in, numaraland�r�c�lar�n� dizi indeksleri olarak kullanmaya
�al��t���m�zda bir sorunla kar��la��yoruz:

                #include <iostream>
                #include <vector>

                enum class OgrenciIsimleri // �imdi bir enum s�n�f�
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 5
                };

                int main()
                {
                    // derleme hatas�: OgrenciIsimleri'nden std::size_t'ye d�n���m yok
                    std::vector<int> testScores(OgrenciIsimleri::max_ogrenciler);

                    // derleme hatas�: OgrenciIsimleri'nden std::size_t'ye d�n���m yok
                    testScores[OgrenciIsimleri::stan] = 76;

                    // derleme hatas�: operator<<'nin ��kt� yapabilece�i herhangi bir tipe OgrenciIsimleri'nden d�n���m yok
                    std::cout << "S�n�fta " << OgrenciIsimleri::max_ogrenciler << " ��renci var\n";

                    return 0;
                }
Bunu ele alman�n birka� yolu var. En a��k olan�, numaraland�r�c�y� bir tam say�ya static_cast yapabiliriz:

                #include <iostream>
                #include <vector>

                enum class OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 6
                };

                int main()
                {
                    std::vector<int> testScores(static_cast<int>(OgrenciIsimleri::max_ogrenciler));

                    testScores[static_cast<int>(OgrenciIsimleri::stan)] = 76;

                    std::cout << "S�n�fta " << static_cast<int>(OgrenciIsimleri::max_ogrenciler) << " ��renci var\n";

                    return 0;
                
Ancak, bunu yazmak sadece can s�k�c� de�il, ayn� zamanda kodumuzu �nemli �l��de karma��kla�t�r�yor. Daha iyi bir se�enek, 
13.4 dersinde tan�tt���m�z yard�mc� fonksiyonu kullanmakt�r - Kapsaml� numaraland�rmalar (enum s�n�flar�), bu sayede enum s�n�flar�n�n
numaraland�r�c�lar�n� tekli operat�r+ kullanarak integral de�erlere d�n��t�rmemizi sa�lar.

                #include <iostream>
                #include <type_traits> // std::underlying_type_t i�in
                #include <vector>

                enum class OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    wendy, // 5
                    max_ogrenciler // 6
                };

                // Unary + operat�r�n� a��r� y�kleyin ve OgrenciIsimleri'ni altta yatan tipe d�n��t�r�n
                constexpr auto operator+(OgrenciIsimleri a) noexcept
                {
                    return static_cast<std::underlying_type_t<OgrenciIsimleri>>(a);
                }

                int main()
                {
                    std::vector<int> testScores(+OgrenciIsimleri::max_ogrenciler);

                    testScores[+OgrenciIsimleri::stan] = 76;

                    std::cout << "S�n�fta " << +OgrenciIsimleri::max_ogrenciler << " ��renci var\n";

                    return 0;
                }
Ancak, �ok fazla numaraland�r�c�y� integral d�n���mlere yapmay� d���n�yorsan�z, muhtemelen bir ad alan� (veya s�n�f) i�inde standart bir enum 
kullanmak daha iyidir.

16.10 � std::vector yeniden boyutland�rma ve kapasite
-----------------------------------------------------
Bu b�l�mdeki �nceki derslerde, konteynerleri, dizileri ve std::vector'� tan�tt�k. Ayr�ca dizi ��elerine nas�l eri�ilece�i, bir dizinin uzunlu�unu 
nas�l alaca��m�z ve bir diziyi nas�l gezece�imiz gibi konular� da tart��t�k. �rneklerimizde std::vector'� kulland�k, ancak tart��t���m�z kavramlar
genellikle t�m dizi tiplerine uygulanabilir.

Bu b�l�mdeki kalan derslerde, std::vector'� di�er dizi tiplerinin �o�undan �nemli �l��de farkl� k�lan bir �eye odaklanaca��z: olu�turulduktan sonra
kendini yeniden boyutland�rma yetene�i.

Sabit boyutlu diziler vs dinamik diziler
----------------------------------------
�o�u dizi tipinin �nemli bir k�s�tlamas� vard�r: dizinin uzunlu�u olu�turma noktas�nda bilinmelidir ve daha sonra de�i�tirilemez.
Bu t�r dizilere sabit boyutlu diziler veya sabit uzunluklu diziler denir. Hem std::array hem de C tarz� diziler sabit boyutlu dizi tipleridir. 
Bunlar� bir sonraki b�l�mde daha fazla tart��aca��z.

Di�er yandan, std::vector bir dinamik dizidir. Bir dinamik dizi (veya yeniden boyutland�r�labilir dizi), boyutu olu�turulduktan sonra 
de�i�tirilebilen bir dizidir. Bu yeniden boyutland�r�labilir olma yetene�i, std::vector'� �zel k�lar.

Bir std::vector'� �al��ma zaman�nda yeniden boyutland�rma
---------------------------------------------------------
Bir std::vector, yeni istenen uzunlukla resize() �ye fonksiyonunu �a��rarak olu�turulduktan sonra yeniden boyutland�r�labilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector v{ 0, 1, 2 }; // 3 ��eli bir vekt�r olu�tur
                    std::cout << "Uzunluk: " << v.size() << '\n';

                    v.resize(5);              // 5 ��eye yeniden boyutland�r
                    std::cout << "Uzunluk: " << v.size() << '\n';

                    for (auto i : v)
                        std::cout << i << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Uzunluk: 3
                Uzunluk: 5
                0 1 2 0 0
Burada iki �eyi not etmek �nemlidir. �lk olarak, vekt�r� yeniden boyutland�rd���m�zda, mevcut ��e de�erleri korundu! �kincisi, yeni ��eler de�er 
ba�lat�l�r (s�n�f tipleri i�in varsay�lan ba�latmay�, di�er tipler i�in s�f�r ba�latmay� ger�ekle�tirir). Bu nedenle, int tipindeki iki yeni ��e 
de�eri 0'a zero-initialize edildi.

Vekt�rler ayr�ca daha k���k olacak �ekilde yeniden boyutland�r�labilir:
-----------------------------------------------------------------------
                #include <iostream>
                #include <vector>

                void printLength(const std::vector<int>& v)
                {
                    std::cout << "Uzunluk: "	<< v.size() << '\n';
                }

                int main()
                {
                    std::vector v{ 0, 1, 2, 3, 4 }; // uzunluk ba�lang��ta 5
                    printLength(v);

                    v.resize(3);                    // 3 ��eye yeniden boyutland�r
                    printLength(v);

                    for (int i : v)
                        std::cout << i << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Uzunluk: 5
                Uzunluk: 3
                0 1 2

Bir `std::vector`'�n uzunlu�u vs. kapasitesi 
--------------------------------------------
12 evlik bir s�ra d���n�n. Evlerin say�s�n�n (veya evlerin s�ras�n�n uzunlu�unun) 12 oldu�unu s�yleriz. Hangi evlerin �u anda i�gal edildi�ini 
bilmek istesek... bunu ba�ka bir �ekilde belirlememiz gerekir (�rne�in, kap� zilini �alar ve birinin cevap verip vermedi�ini g�r�r�z).
Sadece bir uzunlu�umuz oldu�unda, ka� tane �eyin var oldu�unu biliriz.

�imdi i�inde �u anda 5 yumurta olan bir yumurta kartonunu d���n�n. Yumurtalar�n say�s�n�n 5 oldu�unu s�yleriz. Ancak bu ba�lamda, ba�ka bir boyutla
ilgileniriz: kartonun dolu oldu�unda ka� yumurta alabilece�i. Yumurta kartonunun kapasitesinin 12 oldu�unu s�yleriz. Kartonda 12 yumurta i�in yer 
var ve yaln�zca 5 tanesi kullan�l�yor - bu nedenle, kartonu ta��rmadan 7 yumurta daha ekleyebiliriz. Hem bir uzunlu�umuz hem de bir kapasitemiz 
oldu�unda, ka� tane �eyin �u anda var oldu�unu ka� tane �ey i�in yer oldu�undan ay�rt edebiliriz.

Bu noktaya kadar, yaln�zca bir `std::vector`'�n uzunlu�undan bahsettik. Ancak `std::vector`'�n ayn� zamanda bir kapasitesi de vard�r. 
Bir `std::vector` ba�lam�nda, kapasite `std::vector`'�n ne kadar �ok eleman i�in depolama alan� ay�rd���d�r ve uzunluk �u anda ka� eleman�n 
kullan�ld���d�r.

Kapasitesi 5 olan bir `std::vector` 5 eleman i�in depolama alan� ay�r�r. E�er vekt�r aktif olarak kullan�lan 2 eleman i�eriyorsa, vekt�r�n uzunlu�u
(boyutu) 2'dir. Geri kalan 3 eleman i�in bellek ayr�lm��t�r, ancak bunlar aktif olarak kullan�lmad��� kabul edilir. Bunlar daha sonra vekt�r�
ta��rmadan kullan�labilir.

Anahtar Bilgi

*- Bir vekt�r�n uzunlu�u, ka� eleman�n "kullan�mda" oldu�udur.
*- Bir vekt�r�n kapasitesi, ka� eleman�n bellekte ayr�ld���d�r.

Bir `std::vector`'�n kapasitesini alma
--------------------------------------
Bir `std::vector`'den kapasitesini `capacity()` �ye fonksiyonu arac�l���yla isteyebiliriz �rne�in:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
                }

                int main()
                {
                    std::vector v{ 0, 1, 2 }; // uzunluk ba�lang��ta 3

                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    v.resize(5); // 5 elemana yeniden boyutland�r

                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu a�a��dakileri yazd�r�r:

                Capacity: 3  Length: 3
                0 1 2
                Capacity: 5  Length: 5
                0 1 2 0 0
�ncelikle, vekt�r� 3 elemanla ba�latt�k. Bu, vekt�r�n 3 eleman i�in depolama alan� ay�rmas�na (kapasite 3) neden olur ve t�m 3 eleman aktif olarak
kullan�l�r (uzunluk = 3). Daha sonra `resize(5)` �a��r�r�z, yani art�k uzunlu�u 5 olan bir vekt�r istiyoruz. Vekt�r�n yaln�zca 3 eleman i�in 
depolama alan� var, ancak 5'e ihtiyac� var, bu y�zden vekt�r, ek elemanlar� tutmak i�in daha fazla depolama alan� almal�d�r. `resize()` �a�r�s� 
tamamland�ktan sonra, vekt�r�n art�k 5 eleman i�in yer oldu�unu (kapasite 5) ve t�m 5 eleman�n art�k kullan�mda oldu�unu (uzunluk 5) g�rebiliriz.

�o�u zaman `capacity()` fonksiyonunu kullanman�z gerekmez, ancak vekt�r�n depolamas�n�n ne oldu�unu g�rebilmek i�in a�a��daki �rneklerde �ok
kullanaca��z.

Depolaman�n yeniden tahsis edilmesi ve bu neden pahal�d�r
---------------------------------------------------------
Bir `std::vector` y�netti�i depolama miktar�n� de�i�tirdi�inde, bu s�rece yeniden tahsis ( reallocation ) denir. Resmi olmayan bir �ekilde,
yeniden tahsis s�reci ��yle gider:

*- `std::vector` istenen say�da eleman i�in kapasiteye sahip yeni bir bellek al�r. Bu elemanlar de�erle ba�lat�l�r.
*- Eski bellekteki elemanlar yeni belle�e kopyalan�r (veya m�mk�nse ta��n�r). Eski bellek daha sonra sisteme geri verilir.
*- `std::vector`'�n kapasitesi ve uzunlu�u yeni de�erlere ayarlan�r.

D��ar�dan bak�ld���nda, `std::vector`'�n yeniden boyutland�r�ld��� g�r�n�r. Ancak i�eride, bellek (ve t�m elemanlar) asl�nda de�i�tirilmi�tir!
�al��ma zaman�nda yeni bellek alman�n s�recine dinamik bellek tahsisi denir. Bunu ileride ele alaca��z. Yeniden tahsis genellikle dizinin her
eleman�n�n kopyalanmas�n� gerektirdi�inden, yeniden tahsis pahal� bir i�lemdir. Sonu� olarak, yeniden tahsisi m�mk�n oldu�unca ka��nmak istiyoruz.

Anahtar nokta �udur ki; Yeniden tahsis genellikle pahal�d�r. Gereksiz yeniden tahsislerden ka��n�n.

Uzunluk ve kapasiteyi neden ay�rt ediyoruz?
-------------------------------------------
Bir std::vector, gerekti�inde depolamas�n� yeniden tahsis eder, ancak Melville�in Bartleby�si gibi, tercih etmez, ��nk� depolaman�n reallocatesi
hesaplama a��s�ndan pahal�d�r. Bir std::vector yaln�zca uzunlu�unu takip ederse, her resize() iste�i yeni uzunlu�a pahal� bir yeniden tahsis 
sonucunu do�urur. Uzunlu�u ve kapasiteyi ay�rmak, std::vector'�n yeniden tahsislerin ne zaman gerekti�i konusunda daha ak�ll� olabilmesini sa�lar.
A�a��daki �rnek bunu g�sterir:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Kapasite: " << v.capacity() << " Uzunluk:"	<< v.size() << '\n';
                }

                int main()
                {
                    // Uzunlu�u 5 olan bir vekt�r olu�turun
                    std::vector v{ 0, 1, 2, 3, 4 };
                    v = { 0, 1, 2, 3, 4 }; // tamam, dizi uzunlu�u = 5
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Vekt�r� 3 elemana yeniden boyutland�r
                    v.resize(3); // burada 3 elemanl� bir liste de atayabilirdik
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Vekt�r� 5 elemana geri yeniden boyutland�r
                    v.resize(5);
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Bu, a�a��dakileri �retir:

                Kapasite: 5  Uzunluk: 5
                0 1 2 3 4
                Kapasite: 5  Uzunluk: 3
                0 1 2
                Kapasite: 5  Uzunluk: 5
                0 1 2 0 0
5 elemanla vekt�r�m�z� ba�latt���m�zda, kapasite 5 olarak ayarland�, bu da vekt�r�m�z�n ba�lang��ta 5 eleman i�in yer ay�rd���n� g�sterir. 
Uzunluk da 5 olarak ayarland�, bu da t�m bu elemanlar�n kullan�mda oldu�unu g�sterir. v.resize(3) dedikten sonra, uzunluk daha k���k bir dizi 
i�in iste�imizi yerine getirmek �zere 3'e de�i�tirildi. Ancak, kapasitenin hala 5 oldu�unu unutmay�n, bu da vekt�r�n bir yeniden tahsis yapmad���n�
anlam�na gelir!

Son olarak, v.resize(5) dedik. ��nk� vekt�r zaten 5 kapasiteye sahipti, yeniden tahsis yapmaya ihtiya� duymad�. Sadece uzunlu�u 5'e geri de�i�tirdi
ve son iki eleman� de�er ba�latmal� olarak ayarlad�.

Uzunlu�u ve kapasiteyi ay�rarak, bu �rnekte aksi halde meydana gelecek 2 yeniden tahsisi �nledik. Bir sonraki derste, bir vekt�re birer birer 
eleman ekledi�imiz �rnekleri g�rece�iz. Bu t�r durumlarda, uzunluk her de�i�ti�inde yeniden tahsis etmeme yetene�i daha da �nemlidir.

Anahtar nokta, Kapasiteyi uzunluktan ayr� olarak takip etmek, std::vector'�n uzunluk de�i�ti�inde baz� yeniden tahsislerden ka��nmas�n� sa�lar.

Vekt�r indekslemesi uzunlu�a dayal�d�r, kapasiteye de�il
--------------------------------------------------------
subscript operat�r�n�n (operator[]) ve at() �ye fonksiyonunun ge�erli indeksleri Vekt�r�n uzunlu�una ba�l�d�r, kapasitesine de�il.
Yukar�daki �rnekte, v'nin kapasitesi 5 ve uzunlu�u 3 oldu�unda, yaln�zca 0 ve 2 indeksleri ge�erlidir. Uzunlu�un 3 (dahil) ve kapasitenin 5 (hari�)
aras�ndaki indekslerle elemanlar var olsa bile, indeksleri s�n�rlar�n d���nda kabul edilir.

*** Uyar� -> Bir subscript, yaln�zca 0 ile vekt�r�n uzunlu�u (kapasitesi de�il) aras�nda ise ge�erlidir!

Bir std::vector'� K���ltme ( shrinking )
----------------------------------------
Bir vekt�r� daha b�y�k hale getirmek i�in yeniden boyutland�rmak, vekt�r�n uzunlu�unu art�r�r ve gerekti�inde kapasitesini art�r�r. Ancak,
bir vekt�r� daha k���k hale getirmek i�in yeniden boyutland�rmak, yaln�zca uzunlu�unu azalt�r ve kapasitesini de�il.

Art�k ihtiya� duyulmayan birka� ��enin belle�ini geri almak i�in bir vekt�r� yeniden tahsis etmek k�t� bir se�imdir. Ancak, art�k ihtiya� 
duymad���m�z b�y�k say�da ��eye sahip oldu�umuz bir vekt�r durumunda, bellek israf� �nemli olabilir.

Bu durumu ele almak i�in, std::vector'�n kapasitesini uzunlu�una uyacak �ekilde k���ltmesini isteyen shrink_to_fit() ad�nda bir �ye fonksiyonu
vard�r. Bu istek ba�lay�c� de�ildir, yani uygulaman�n bunu g�rmezden gelme hakk� vard�r. Uygulaman�n en iyisi neyse ona ba�l� olarak, uygulama 
iste�i yerine getirebilir, k�smen yerine getirebilir (�rne�in, kapasiteyi azaltabilir ama tamamen de�il) veya iste�i tamamen g�rmezden gelebilir.

��te bir �rnek:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
                }

                int main()
                {

                    std::vector<int> v(1000); // 1000 ��e i�in yer ay�r
                    printCapLen(v);

                    v.resize(0); // 0 ��eye yeniden boyutland�r
                    printCapLen(v);

                    v.shrink_to_fit();
                    printCapLen(v);

                    return 0;
                }

                Yazar�n makinesinde, bu a�a��daki sonucu verir:

                Capacity: 1000  Length: 1000
                Capacity: 1000  Length: 0
                Capacity: 0  Length: 0
G�rd���n�z gibi, v.shrink_to_fit() �a�r�ld���nda, vekt�r kapasitesini 0'a yeniden tahsis etti, 1000 ��e i�in belle�i serbest b�rakt�.

16.11 � std::vector ve Y���n Davran��� ( stack behavior )
---------------------------------------------------------
Bir kullan�c�n�n bir dizi de�er girece�i (�rne�in bir dizi test skoru) bir program yazd���n�z� d���n�n. Bu durumda, girecekleri de�erlerin say�s�
derleme zaman�nda bilinmez ve program� her �al��t�rd�klar�nda de�i�ebilir. Bu de�erleri bir std::vector'de saklayacak ve/veya i�leyeceksiniz.

�imdiye kadar tart��t���m�z �eylere dayanarak, bunu nas�l ele alabilece�iniz konusunda birka� yol olabilir:

�ncelikle, kullan�c�dan ka� giri�i oldu�unu sormak, bu uzunlukta bir vekt�r olu�turmak ve ard�ndan kullan�c�dan bu say�da de�er girmesini 
isteyebilirsiniz. Bu k�t� bir yakla��m de�il, ancak kullan�c�n�n tam olarak ka� giri�i oldu�unu �nceden bilmesini ve sayarken hata yapmam��
olmas�n� gerektirir. On veya yirmiden fazla ��eyi manuel olarak saymak s�k�c� olabilir - ve bizim onlar i�in bunu yapmam�z gerekirken neden
kullan�c�dan girilen de�erlerin say�s�n� saymas�n� isteyelim ki?

Alternatif olarak, kullan�c�n�n belirli bir say�dan fazla de�er girmek istemeyece�ini (�rne�in 30) varsayabilir ve bu kadar �ok ��eye sahip bir 
vekt�r olu�turabilir (veya yeniden boyutland�rabiliriz). Sonra kullan�c�ya bitene kadar (veya 30 giri� de�erine ula�ana kadar) veri girmesini
isteyebiliriz. Bir vekt�r�n uzunlu�u, kullan�lan ��e say�s�n� ifade etmek �zere oldu�undan, vekt�r� kullan�c�n�n ger�ekte girdi�i de�er say�s�na
yeniden boyutland�rabiliriz.

Bu yakla��m�n dezavantaj�, kullan�c�n�n 30 de�er girmekle s�n�rl� olmas� ve bu say�n�n �ok fazla m� yoksa �ok az m� oldu�unu bilmiyor olmam�zd�r.
Kullan�c� daha fazla de�er girmek isterse, �ok k�t�.

Bu sorunu, kullan�c�n�n maksimum de�er say�s�na ula�t���nda vekt�r� daha b�y�k hale getirmek i�in biraz mant�k ekleyerek ��zebiliriz. 
Ancak bu, art�k dizi boyutu y�netimini program mant���m�zla kar��t�rmam�z gerekti�i anlam�na gelir ve bu, program�m�z�n karma��kl���n� �nemli
�l��de art�racakt�r (bu ka��n�lmaz olarak hatalara yol a�acakt�r).

Ger�ek sorun burada, kullan�c�n�n ka� ��e girebilece�ini tahmin etmeye �al��mam�z, b�ylece vekt�r�n boyutunu uygun �ekilde y�netebilmemizdir.
Girilecek ��e say�s�n�n ger�ekten �nceden bilinmedi�i durumlar i�in, daha iyi bir yakla��m vard�r.

Ama oraya varmadan �nce, k�sa bir s�reli�ine yan konuya ge�memiz gerekiyor.

Bir y���n ( stach ) nedir ? 
---------------------------
Benze�im zaman�! Bir kafeteryadaki tabak y���n�n� d���n�n. Bilinmeyen bir nedenle, bu tabaklar ekstra a��rd�r ve sadece bir seferde bir tanesi 
kald�r�labilir. Tabaklar y���ld��� ve a��r oldu�u i�in, tabak y���n�n� yaln�zca iki �ekilde de�i�tirebilirsiniz:

1- Y���n�n �st�ne yeni bir tabak koyun (alt�ndaki taba�� gizler, e�er varsa)
2- Y���n�n en �st�ndeki taba�� ��kar�n (alt�ndaki taba�� a���a ��kar�r, e�er varsa)

Y���n�n ortas�ndan veya alt�ndan bir tabak eklemek veya ��karmak izin verilmez, ��nk� bu bir seferde birden fazla taba�� kald�rmay� gerektirir.
Bir y���na eklenen ve ��kar�lan ��elerin s�ras�, son giren ilk ��kar (LIFO) olarak tan�mlanabilir. Y���na eklenen son tabak, ��kar�lacak ilk tabak 
olacakt�r.

Programlamada Y���nlar
----------------------
Programlamada, bir y���n, ��elerin ekleme ve ��karma i�lemlerinin LIFO �eklinde ger�ekle�ti�i bir konteyner veri tipidir. Bu genellikle push ve pop
adl� iki i�lem arac�l���yla uygulan�r:

---------------------------------------------------------------------------------------------------------
| ��lem Ad� | Davran��                         | Gerekli mi? | Notlar                                   |
|-----------|----------------------------------|-------------|------------------------------------------|
| Push      | Y���n�n �st�ne yeni bir ��e koy  | Evet        |                                          |
| Pop       | Y���n�n en �st�ndeki ��eyi ��kar | Evet        | ��kar�lan ��eyi veya bo�luk d�nd�rebilir |
---------------------------------------------------------------------------------------------------------
Bir�ok y���n uygulamas�, iste�e ba�l� olarak di�er kullan��l� i�lemleri de destekler:

---------------------------------------------------------------------------------------------
| ��lem Ad�     | Davran��                                  | Gerekli mi?  | Notlar         |
|---------------|-------------------------------------------|--------------|----------------|
| Top veya Peek | Y���n�n en �st�ndeki ��eyi al             | �ste�e Ba�l� | ��eyi ��karmaz |
| Empty         | Y���n�n hi� ��esi olup olmad���n� belirle | �ste�e Ba�l� |                |
| Size          | Y���nda ka� tane ��e oldu�unu say         | �ste�e Ba�l� |                |
---------------------------------------------------------------------------------------------

Y���nlar programlamada yayg�nd�r. 3.9 dersinde -- Entegre bir hata ay�klay�c� kullanma: �a�r� y���n�, hangi fonksiyonlar�n �a�r�ld���n� takip eden
�a�r� y���n�ndan bahsettik. �a�r� y���n�... bir y���nd�r! (Biliyorum, bu a��klama hayal k�r�kl���na u�ratt�). Bir fonksiyon �a�r�ld���nda, 
o fonksiyon hakk�nda bilgi i�eren bir giri�, �a�r� y���n�n�n �st�ne eklenir. Fonksiyon d�nd���nde, o fonksiyon hakk�nda bilgi i�eren giri�,
�a�r� y���n�n�n �st�nden ��kar�l�r. Bu �ekilde, �a�r� y���n�n�n en �st� her zaman �u anda y�r�t�len fonksiyonu temsil eder ve her bir sonraki giri�
�nceki y�r�t�len fonksiyonu temsil eder.

�rne�in, bir y���nda nas�l push ve pop i�lemlerinin �al��t���n� g�steren k�sa bir dizi:

       (Y���n: bo�)
Push 1 (Y���n: 1)
Push 2 (Y���n: 1 2)
Push 3 (Y���n: 1 2 3)
Pop    (Y���n: 1 2)
Push 4 (Y���n: 1 2 4)
Pop    (Y���n: 1 2)
Pop    (Y���n: 1)
Pop    (Y���n: bo�)

C++'da Y���nlar
---------------
Baz� dillerde, bir y���n, kendi ayr� konteyner tipi olarak uygulan�r (di�er konteynerlerden ayr�). Ancak, bu olduk�a s�n�rlay�c� olabilir.
Bir y���ndaki t�m de�erleri yazd�rmak istedi�imiz durumu d���n�n, y���n� de�i�tirmeden. Saf bir y���n aray�z� bunu yapmak i�in do�rudan bir 
y�ntem sa�lamaz.

C++'da, y���n gibi i�lemler yerine (�ye fonksiyonlar olarak) bir u�ta ��elerin etkin bir �ekilde ekleme ve ��karma i�lemlerini destekleyen mevcut
standart k�t�phane konteyner s�n�flar�na eklendi (std::vector, std::deque ve std::list). Bu, bu konteynerlerin y���nlar olarak kullan�lmas�na
olanak sa�lar ve yerel yeteneklerine ek olarak bunu yapar.

Bir parantez i�inde�
---------------------
Tabak y���n� benzetmesi iyi bir �rnektir, ancak bir y���n�n bir dizi kullan�larak nas�l uygulanabilece�ini anlamam�za yard�mc� olacak daha iyi bir
benzetme yapabiliriz. �u anda ka� tabak tuttu�u de�i�ebilen bir tabak y���n� yerine, birbiri �zerine y���lm�� bir s�tun posta kutusu d���n�n.
Her posta kutusu sadece bir ��e tutabilir ve t�m posta kutular� bo� ba�lar. Her posta kutusu, alt�ndaki posta kutusuna �ivilenmi�tir ve s�tunun
�st� zehirli dikenlerle kapl�d�r, bu y�zden yeni posta kutular� hi�bir yere eklenemez.

Posta kutusu say�s�n� de�i�tiremiyorsak, y���n benzeri bir davran�� nas�l elde ederiz?
--------------------------------------------------------------------------------------
�ncelikle, y���n�n �st k�sm�n�n nerede oldu�unu takip etmek i�in bir i�aret�i (post-it notu gibi) kullan�r�z - bu her zaman en d���k bo� posta 
kutusu olacakt�r. Ba�lang��ta, y���n bo�tur, bu y�zden i�aret�i alt posta kutusuna gider.

Bir ��eyi posta kutusu y���n�m�za itti�imizde, onu i�aretli olan posta kutusuna (bu en d���k bo� posta kutusu) koyar�z ve i�aret�iyi bir posta
kutusu yukar� ta��r�z. Bir ��eyi y���ndan ��kard���m�zda, i�aret�iyi bir posta kutusu a�a�� ta��r�z (bu y�zden en �stteki dolu posta kutusunu
g�sterir) ve o posta kutusundaki ��eyi ��kar�r�z, b�ylece art�k bo�tur.

��aret�inin alt�ndaki ��eler �y���n �zerinde� olarak kabul edilir. ��aret�inin �zerinde veya �zerindeki ��eler y���n �zerinde de�ildir.
�imdi, i�aret�iyi uzunluk olarak adland�r�n ve posta kutular�n�n say�s�n� kapasite olarak adland�r�n�

Bu dersin geri kalan�nda, std::vector'�n y���n aray�z�n�n nas�l �al��t���n� inceleyece�iz ve sonra, dersin ba��nda tan�t�lan meydan okumay� nas�l
��zd���n� g�stererek sona erece�iz.

std::vector ile Y���n Davran���
-------------------------------
std::vector'deki y���n davran���, a�a��daki �ye fonksiyonlar arac�l���yla uygulan�r:
-----------------------------------------------------------------------------------------------------------------------------------------------
| Fonksiyon Ad� | Y���n ��lemi    | Davran��                                                | Notlar                                          |
|---------------|-----------------|---------------------------------------------------------|-------------------------------------------------|
| push_back()   | Itme            | Y���n�n �st�ne yeni bir ��e koyar                       | Vector�n sonuna ��eyi ekler                     |
| pop_back()    | ��karma         | Y���n�n �st�ndeki ��eyi ��kar�r                         | Void d�nd�r�r, vector�n sonundaki ��eyi ��kar�r |
| back()        | �st veya G�z At | Y���n�n �st�ndeki ��eyi al�r                            | ��eyi ��karmaz                                  |
| emplace_back()| Itme            | push_back()'�n daha verimli olabilecek alternatif formu | Vector�n sonuna ��eyi ekler                     |
-----------------------------------------------------------------------------------------------------------------------------------------------
Bu fonksiyonlar�n baz�lar�n� kullanan bir �rne�e bir g�z atal�m:

                #include <iostream>
                #include <vector>

                void printStack(const std::vector<int>& stack)
                {
                    if (stack.empty()) // e�er stack.size == 0 ise
                        std::cout << "Bo�";

                    for (auto element : stack)
                        std::cout << element << ' ';

                    // \t bir tab karakteridir, metni hizalamaya yard�mc� olur
                    std::cout << "\tKapasite: " << stack.capacity() << "  Uzunluk " << stack.size() << "\n";
                }

                int main()
                {
                    std::vector<int> stack{}; // bo� y���n

                    printStack(stack);

                    stack.push_back(1); // push_back() bir ��eyi y���na iter
                    printStack(stack);

                    stack.push_back(2);
                    printStack(stack);

                    stack.push_back(3);
                    printStack(stack);

                    std::cout << "�st: " << stack.back() << '\n'; // back() son ��eyi d�nd�r�r

                    stack.pop_back(); // pop_back() bir ��eyi y���ndan ��kar�r
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    return 0;
                }

                GCC veya Clang'da, bu �unlar� yazd�r�r:

                Bo�     Kapasite: 0  Uzunluk: 0
                1       Kapasite: 1  Uzunluk: 1
                1 2     Kapasite: 2  Uzunluk: 2
                1 2 3   Kapasite: 4  Uzunluk: 3
                �st:3
                1 2     Kapasite: 4  Uzunluk: 2
                1       Kapasite: 4  Uzunluk: 1
                Bo�     Kapasite: 4  Uzunluk: 0
Unutmay�n, uzunluk vectordeki ��e say�s�d�r, bu durumda, y���n�m�zdaki ��e say�s�d�r.
Alt dizin operat�r� operator[] veya at() �ye fonksiyonunun aksine, push_back() (ve emplace_back()) vector�n uzunlu�unu art�r�r ve kapasite,
de�eri eklemek i�in yeterli olmad���nda yeniden tahsisat yap�lmas�na neden olur.
Yukar�daki �rnekte, vector 3 kez yeniden tahsis edilir (kapasite 0'dan 1'e, 1'den 2'ye ve 2'den 4'e).

Anahtar nokta,push_back() ve emplace_back(), bir std::vector'�n uzunlu�unu art�r�r ve kapasite, de�eri eklemek i�in yeterli olmad���nda yeniden
tahsisat yap�lmas�na neden olur.

Bir ��eyi eklerken (`push_back`), `std::vector` genellikle bir sonraki ��e eklenirken ba�ka bir yeniden tahsis tetiklenmesini �nlemek i�in biraz
ekstra kapasite ay�r�r. Bu ekstra kapasitenin ne kadar oldu�u, `std::vector`'�n derleyicinin uygulamas�na ba�l�d�r ve farkl� derleyiciler
genellikle farkl� �eyler yapar:

- GCC ve Clang, mevcut kapasiteyi ikiye katlar. Son yeniden boyutland�rma tetiklendi�inde, kapasite 2'den 4'e ��kar.
- Visual Studio 2022, mevcut kapasiteyi 1.5 ile �arpar. Son yeniden boyutland�rma tetiklendi�inde, kapasite 2'den 3'e de�i�tirilir.

Sonu� olarak, �nceki program�n ��kt�s� kullan�lan derleyiciye ba�l� olarak biraz farkl� olabilir.

Bir vekt�r� yeniden boyutland�rmak, y���n davran���yla �al��maz
---------------------------------------------------------------
Bir vekt�r� yeniden tahsis etmek hesaplama a��s�ndan pahal�d�r (vekt�r�n uzunlu�una orant�l�), bu y�zden makul oldu�unda yeniden tahsislerden 
ka��nmak istiyoruz. Yukar�daki �rnekte, program�n ba��nda vekt�r� kapasitesi 3 olan bir vekt�re yeniden boyutland�r�rsak, vekt�r�n 3 kez yeniden
tahsis edilmesini �nleyebiliriz.
A�a��daki gibi 18. sat�r� de�i�tirirsek, program� tekrar �al��t�rd���m�zda a�a��daki ��kt�y� al�r�z:

                std::vector<int> stack(3); // parantez init vekt�r�n kapasitesini 3'e ayarlar

                ��kt�:


                0 0 0   Kapasite: 3  Uzunluk: 3
                0 0 0 1         Kapasite: 4  Uzunluk: 4
                0 0 0 1 2       Kapasite: 6  Uzunluk: 5
                0 0 0 1 2 3     Kapasite: 6  Uzunluk: 6
                �st: 3
                0 0 0 1 2       Kapasite: 6  Uzunluk: 5
                0 0 0 1         Kapasite: 6  Uzunluk: 4
                0 0 0   Kapasite: 6  Uzunluk: 3
Bu do�ru de�il - bir �ekilde y���n�m�z�n ba��nda bir s�r� 0 de�eri var! Buradaki sorun, parantez ba�latman�n (vekt�r�n ba�lang�� boyutunu ayarlamak
i�in) ve `resize()` fonksiyonunun hem kapasiteyi hem de uzunlu�u ayarlamas�d�r. Vekt�r�m�z kapasite 3 ile ba�l�yor (bu bizim istedi�imiz �ey), 
ancak uzunluk da 3 olarak ayarlan�yor. Bu y�zden vekt�r�m�z 0 de�erine sahip 3 elemanla ba�l�yor. Daha sonra �zerine ekledi�imiz elemanlar,
bu ba�lang�� elemanlar�n�n �zerine eklenir.

`resize()` �ye fonksiyonunun vekt�r�n uzunlu�unu de�i�tirmesi, elemanlara subscript olmak i�in indeksleri kullanmay� d���nd���m�zde iyidir (��nk� 
indekslerimizin ge�erli olmas� i�in uzunluktan daha k���k olmas� gerekir), ancak vekt�r� bir y���n olarak kulland���m�zda sorunlara neden olur.

Asl�nda istedi�imiz �ey, kapasiteyi de�i�tirebilecek (gelecekteki yeniden tahsisleri �nlemek i�in) ancak uzunlu�u de�i�tirmeyecek (y���na yeni 
elemanlar eklemenin yan etkisi) bir yol.

`reserve()` �ye fonksiyonu kapasiteyi de�i�tirir (ama uzunlu�u de�il)
---------------------------------------------------------------------
`reserve()` �ye fonksiyonu, mevcut uzunlu�u de�i�tirmeden bir `std::vector`'� yeniden tahsis etmek i�in kullan�labilir. ��te ayn� �rnek,
ancak kapasiteyi ayarlamak i�in eklenmi� bir `reserve()` �a�r�s� ile:

                #include <iostream>
                #include <vector>

                void printStack(const std::vector<int>& stack)
                {
                    if (stack.empty()) // if stack.size == 0
                        std::cout << "Bo�";

                    for (auto element : stack)
                        std::cout << element << ' ';

                    // \t bir sekme karakteridir, metni hizalamaya yard�mc� olur
                    std::cout << "\tKapasite: " << stack.capacity() << "  Uzunluk " << stack.size() << "\n";
                }

                int main()
                {
                    std::vector<int> stack{};

                    printStack(stack);

                    stack.reserve(6); // 6 eleman i�in yer ay�r (ama uzunlu�u de�i�tirme)
                    printStack(stack);

                    stack.push_back(1);
                    printStack(stack);

                    stack.push_back(2);
                    printStack(stack);

                    stack.push_back(3);
                    printStack(stack);

                    std::cout << "�st: " << stack.back() << '\n';

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    return 0;
                }


                Yazar�n makinesinde, bu �unu yazd�r�r:

                Bo�   Kapasite: 0  Uzunluk: 0
                Bo�   Kapasite: 6  Uzunluk: 0
                1       Kapasite: 6  Uzunluk: 1
                1 2     Kapasite: 6  Uzunluk: 2
                1 2 3   Kapasite: 6  Uzunluk: 3
                En �st: 3
                1 2     Kapasite: 6  Uzunluk: 2
                1       Kapasite: 6  Uzunluk: 1
                Bo�   Kapasite: 6  Uzunluk: 0
G�rd���n�z gibi, reserve(6) �a�r�ld���nda kapasite 6'ya de�i�tirildi, ancak uzunluk etkilenmedi. std::vector t�m eklenen ��eleri bar�nd�rmak i�in 
yeterince b�y�k oldu�u i�in daha fazla yeniden tahsisat yap�lmaz.

Anahtar nokta

*- resize() �ye fonksiyonu vekt�r�n uzunlu�unu ve gerekirse kapasitesini de�i�tirir.
*- reserve() �ye fonksiyonu sadece kapasiteyi (gerekirse) de�i�tirir.

�pucu

Bir std::vector'deki ��e say�s�n� art�rmak i�in:
*- Vekt�re indeksleme yoluyla eri�irken resize() kullan�n. Bu, vekt�r�n uzunlu�unu de�i�tirir, b�ylece indeksleriniz ge�erli olur.
*- Vekt�re y���n i�lemleri kullanarak eri�irken reserve() kullan�n. Bu, vekt�r�n uzunlu�unu de�i�tirmeden kapasite ekler.

push_back() vs emplace_back()
-----------------------------
Hem push_back() hem de emplace_back() bir ��eyi y���na iter. �telenen nesne zaten varsa, push_back() ve emplace_back() e�de�erdir ve push_back()
tercih edilir.
Ancak, vekt�re itmek i�in bir ge�ici nesne olu�turdu�umuz durumlarda, emplace_back() daha verimli olabilir:

                #include <iostream>
                #include <string>
                #include <string_view>
                #include <vector>

                class Foo
                {
                private:
                    std::string m_a{};
                    int m_b{};

                public:
                    Foo(std::string_view a, int b)
                        : m_a { a }, m_b { b }
                        {}
                };

                int main()
                {
                    std::vector<Foo> stack{};

                    // Zaten bir nesnemiz varsa, push_back benzer verimliliktedir
                    Foo f{ "a", 2 };
                    stack.push_back(f);    // bunu tercih edin
                    stack.emplace_back(f);

                    // Bir ge�ici nesne olu�turup itmeye ihtiyac�m�z oldu�unda, emplace_back daha verimlidir
                    stack.push_back({ "a", 2 });  // bir ge�ici nesne olu�turur ve sonra onu vekt�re kopyalar
                    stack.emplace_back("a", 2);   // arg�manlar� iletir, b�ylece nesne do�rudan vekt�rde olu�turulabilir (kopya yap�lmaz)

                    return 0;
                }

Yukar�daki �rnekte, Foo nesnelerinin bir vekt�r�ne sahibiz. push_back({ "a", 2 }) ile, bir Foo ge�ici nesnesi olu�turuyor ve ba�lat�yoruz,
bu daha sonra vekt�re kopyalan�r. Kopyalamas� pahal� t�rler (std::string gibi) i�in bu kopya, performans kayb�na neden olabilir.

emplace_back() ile, ge�mek i�in bir ge�ici nesne olu�turmam�za gerek yok. Bunun yerine, ge�ici nesneyi olu�turmak i�in kullan�lacak arg�manlar�
ge�eriz ve emplace_back() bunlar� vekt�re iletir (m�kemmel iletim ad� verilen bir �zellik kullanarak), burada vekt�r i�indeki nesneyi olu�turmak
ve ba�latmak i�in kullan�l�rlar. Bu, aksi takdirde yap�lm�� olacak bir kopyay� �nler.

C++20'den �nce, emplace_back() toplu ba�latmayla �al��maz.

*** BEST -> Konteynere eklemek i�in yeni bir ge�ici nesne olu�tururken emplace_back() tercih edin. Aksi takdirde push_back() tercih edin.

Y���n ��lemleri Kullanarak Sorunumuzu ��zme
-------------------------------------------
Dersin ba��nda tan�tt���m�z sorunu nas�l ele alaca��m�z art�k a��k olmal�. �nceden ka� ��enin std::vector'�m�ze eklenece�ini bilmiyorsak,
bu ��eleri eklemek i�in y���n fonksiyonlar�n� kullanmak yol olacakt�r.
��te bir �rnek:

                #include <iostream>
                #include <limits>
                #include <vector>

                int main()
                {
                    std::vector<int> scoreList{};

                    while (true)
                    {
                        std::cout << "Bir skor girin (veya bitirmek i�in -1): ";
                        int x{};
                        std::cin >> x;

                        if (!std::cin) // hatal� giri�i ele al
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }

                        // E�er bittiysek, d�ng�den ��k
                        if (x == -1)
                            break;

                        // Kullan�c� ge�erli bir ��e girdi, bu y�zden onu vekt�re itelim
                        scoreList.push_back(x);
                    }

                    std::cout << "Skorlar�n�z�n listesi: \n";

                    for (const auto& score : scoreList)
                        std::cout << score << ' ';

                    return 0;
                }
Bu program, kullan�c�n�n test puanlar�n� girmesine izin verir, her puan� bir vekt�re ekler. Kullan�c� puan eklemeyi bitirdikten sonra, 
vekt�rdeki t�m de�erler yazd�r�l�r.

Bu programda, hi�bir sayma, indeksleme veya dizi uzunluklar�yla u�ra�mam�z gerekmiyor! Sadece program�n ne yapmas�n� istedi�imiz mant���na
odaklanabiliriz ve vekt�r�n t�m depolama sorunlar�n� halletmesine izin verebiliriz.

16.12 � std::vector<bool>
-------------------------
O.1 dersinde -- Bit bayraklar� ve bit manip�lasyonu via std::bitset, std::bitset'in 8 Boolean de�erini bir byte'a s�k��t�rma yetene�ine sahip 
oldu�unu tart��t�k. Bu bitler, std::bitset'in �ye fonksiyonlar� arac�l���yla de�i�tirilebilir.

std::vector'�n kollar�nda ilgin� bir hile var. Boolean de�erler i�in daha fazla alan verimli olabilecek bir std::vector<bool> i�in �zel bir 
uygulama var, benzer �ekilde 8 Boolean de�erini bir byte'a s�k��t�r�yor.

Bit manip�lasyonu i�in tasarlanm�� olan std::bitset'in aksine, std::vector<bool> bit manip�lasyon �ye fonksiyonlar�ndan yoksundur.

std::vector<bool> Kullan�m�
---------------------------
�o�unlukla, std::vector<bool> normal bir std::vector gibi �al���r:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector<bool> v { true, false, false, true, true };

                    for (int i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Change the Boolean value with index 4 to false
                    v[4] = false;

                    for (int i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Yazar�n 64-bit makinesinde bu, �unu yazd�r�r:

                1 0 0 1 1
                1 0 0 1 0
std::vector<bool> �d�nle�imler ( tradeoffs )
--------------------------------------------
Ancak, std::vector<bool>'un kullan�c�lar�n fark�nda olmas� gereken baz� tavizleri vard�r. �lk olarak, std::vector<bool> olduk�a y�ksek miktarda bir 
overhead'e sahiptir (yazar�n makinesinde sizeof(std::vector<bool>) 40 byte'dir), bu y�zden mimarinizin overhead'inden daha fazla Boolean de�eri 
ay�rmad�k�a bellek tasarrufu sa�lamazs�n�z.

�kinci olarak, std::vector<bool>'un performans� uygulamaya olduk�a ba��ml�d�r (uygulamalar�n optimizasyon yapmak zorunda olmamas�, hatta iyi yapmak
zorunda olmamas�). Bu makaleye g�re, olduk�a optimize edilmi� bir uygulama, alternatiflerden �nemli �l��de daha h�zl� olabilir. Ancak, k�t� 
optimize edilmi� bir uygulama daha yava� olacakt�r.

���nc� ve en �nemlisi, std::vector<bool> bir vekt�r de�ildir (bellekte ard���k olmas� gerekmez), ne de bool de�erlerini tutar 
(bir bit koleksiyonunu tutar), ne de C++'�n bir konteynerin tan�m�n� kar��lar.

std::vector<bool> �o�u durumda bir vekt�r gibi davran�rken, standart k�t�phanenin geri kalan�yla tamamen uyumlu de�ildir. Di�er ��e t�rleriyle 
�al��an kod, std::vector<bool> ile �al��mayabilir.

�rne�in, a�a��daki kod, T herhangi bir t�r oldu�unda �al���r, ancak bool de�il:

                template<typename T>
                void foo( std::vector<T>& v )
                {
                    T& first = v[0]; // get a reference to the first element
                    // Do something with first
                }

std::vector<bool> Ka��n�n
-------------------------
Modern fikir birli�i, genellikle std::vector<bool>'un ka��n�lmas� gerekti�i y�n�ndedir, ��nk� performans kazan�mlar�n�n, uygun bir konteyner
olmamas� nedeniyle uyumluluk sorunlar�na de�meyece�i d���n�lmektedir.

Ne yaz�k ki, bu optimize edilmi� s�r�m std::vector<bool> varsay�lan olarak etkindir ve ger�ekten bir konteyner olan optimize edilmemi� bir s�r�m
lehine devre d��� b�rakman�n bir yolu yoktur. std::vector<bool>'un kullan�mdan kald�r�lmas� �a�r�lar� olmu�tur ve bool'un s�k��t�r�lm�� bir
vekt�r�n�n neye benzeyece�ini belirlemek i�in �al��malar devam etmektedir (belki gelecekteki bir std::dynamic_bitset olarak).

�nerimiz �u �ekildedir:

*- Derleme zaman�nda ihtiya� duydu�unuz bit say�s� bilindi�inde, saklamak i�in fazla say�da Boolean de�eriniz olmad���nda (�r. 64k alt�nda) ve s�n�rl�
   operat�r ve �ye fonksiyon seti (�r. yineleyici deste�i eksikli�i) gereksinimlerinizi kar��lad���nda (constexpr) std::bitset kullan�n.

*- Boolean de�erlerin yeniden boyutland�r�labilir bir konteynerine ihtiya� duydu�unuzda ve alan tasarrufu bir zorunluluk de�ilse std::vector<char>'�
   tercih edin. Bu t�r, normal bir konteyner gibi davran�r.
*- Bit i�lemleri yapman�z gereken bir dinamik bitset'e ihtiya� duydu�unuzda, bir 3. taraf�n dinamik bitset uygulamas�n�
   (�rne�in boost::dynamic_bitset) tercih edin. Bu t�rler, standart k�t�phane konteynerleri olmad�klar�nda bunlar�n standart k�t�phane
   konteynerleri oldu�unu iddia etmez.

*** BEST -> std::vector<bool>'dan ziyade constexpr std::bitset, std::vector<char> veya 3. taraf dinamik bitsetleri tercih edin.

16.x � B�l�m 16 �zeti
---------------------
Te�vik Edici S�zler
-------------------
Bu b�l�m kolay bir b�l�m de�il. �ok fazla materyal �zerinden ge�tik ve C++'�n baz� kusurlar�n� ortaya ��kard�k. Bunu ba�ard���n�z i�in tebrikler!
Diziler, C++ programlar�n�zdaki b�y�k miktarda g�c�n kilidini a�an anahtarlardan biridir.

B�l�m �ncelemesi
----------------
Bir konteyner, bir dizi isimsiz nesneyi (elementler olarak adland�r�l�r) saklamak i�in bir veri tipidir. Genellikle, bir dizi ilgili de�erle 
�al��mam�z gerekti�inde konteynerleri kullan�r�z.

Bir konteynerdeki elementlerin say�s� genellikle uzunluk olarak adland�r�l�r (bazen say�). C++'da, bir konteynerdeki elementlerin say�s� i�in boyut 
terimi de yayg�n olarak kullan�l�r. �o�u programlama dilinde (C++ dahil), konteynerler homojendir, yani bir konteynerin elementlerinin ayn� t�rde 
olmas� gerekir.

Konteynerler k�t�phanesi, baz� yayg�n konteyner t�rlerini uygulayan �e�itli s�n�f t�rlerini i�eren C++ standart k�t�phanesinin bir par�as�d�r.
Bir konteyneri uygulayan bir s�n�f t�r� bazen bir konteyner s�n�f� olarak adland�r�l�r.

Bir dizi, bir dizi de�eri ard���k olarak (yani her element, bo�luk olmadan biti�ik bir bellek konumuna yerle�tirilir) saklayan bir konteyner veri
tipidir. Diziler, herhangi bir elemente h�zl�, do�rudan eri�im sa�lar.

C++'da �� ana dizi tipi vard�r: (C tarz�) diziler, std::vector konteyner s�n�f� ve std::array konteyner s�n�f�.

std::vector, bir diziyi uygulayan C++ standart konteynerler k�t�phanesindeki konteyner s�n�flar�ndan biridir. std::vector, <vector> ba�l���nda bir
s�n�f �ablonu olarak tan�mlanm��t�r, bir �ablon t�r parametresi ile elementlerin t�r�n� tan�mlar. Bu nedenle, std::vector<int> bir std::vector'� 
tan�mlar ve elementlerin t�r� int'tir.

Konteynerler genellikle, bir ba�lat�c� listesi kullanarak konteynerin bir �rne�ini olu�turmam�za izin veren �zel bir yap�land�r�c�ya sahiptir.
Bir konteyneri, bu element de�erleriyle olu�turmak i�in bir ba�lat�c� de�erler listesi ile liste ba�latmay� kullan�n.

C++'da, dizi elementlerine eri�menin en yayg�n yolu, dizi ad�n� ve alt dizin operat�r�n� (operator[]) kullanmakt�r. Belirli bir elementi se�mek 
i�in, alt dizin operat�r�n�n k��eli parantezlerinin i�ine, hangi elementi se�mek istedi�imizi belirleyen bir tamsay� de�eri sa�lar�z. Bu tamsay�
de�eri bir alt dizin olarak adland�r�l�r (veya gayri resmi olarak, bir indeks). �lk element, indeks 0 kullan�larak eri�ilir, ikinci element,
indeks 1 kullan�larak eri�ilir, vb... Dizinleme 1 yerine 0 ile ba�lad��� i�in, C++'daki dizilerin s�f�r tabanl� oldu�unu s�yleriz.

operator[] herhangi bir s�n�rlama kontrol� yapmaz, yani indeksin 0 ile N-1 (dahil) aras�nda olup olmad���n� kontrol etmez. operator[]'a ge�ersiz 
bir indeks ge�irilirse, tan�ms�z bir davran��a neden olur.

Diziler, do�rudan ve e�it h�zda her ��eye eri�ime izin veren birka� konteyner t�r�nden biridir, yani konteynerdaki ��e say�s�na bak�lmaks�z�n.

Bir s�n�f tipi nesnesi olu�tururken, e�le�en bir liste yap�c�, di�er e�le�en yap�c�lardan se�ilir. Element de�erleri olmayan ba�lat�c�larla bir
konteyner (veya bir liste yap�c�s� olan herhangi bir tip) olu�tururken, do�rudan ba�latmay� kullan�n.

                std::vector v1 { 5 }; // `5` de�erini i�eren 1 ��eli bir vekt�r tan�mlar.
                std::vector v2 ( 5 ); // ��elerin de�er ba�lat�ld��� 5 ��eli bir vekt�r tan�mlar.
std::vector const yap�labilir ancak constexpr yap�lamaz.

Standart k�t�phane konteyner s�n�flar�n�n her biri, konteynerin uzunlu�u (ve destekleniyorsa indeksler) i�in kullan�lan tip i�in bir takma ad olan
size_type adl� bir i� i�e ge�mi� typedef �yesi tan�mlar (bazen T::size_type olarak yaz�l�r). size_type neredeyse her zaman std::size_t i�in bir 
takma add�r, ancak nadir durumlarda farkl� bir tip kullanmak �zere ge�ersiz k�l�nabilir. size_type'�n std::size_t i�in bir takma ad oldu�unu makul
bir �ekilde varsayabiliriz.

Bir konteyner s�n�f�n�n size_type �yesine eri�irken, onu konteyner s�n�f�n�n tam �ablonlu ad�yla kapsam belirtmeliyiz. �rne�in, 
std::vector<int>::size_type.

Bir konteyner s�n�f� nesnesinden uzunlu�unu size() �ye fonksiyonu kullanarak sorabiliriz, bu da uzunlu�u i�aretsiz size_type olarak d�nd�r�r. 
C++17'de, std::size() �ye olmayan fonksiyonunu da kullanabiliriz.

C++20'de, std::ssize() �ye olmayan fonksiyonu, uzunlu�u b�y�k bir i�aretli integral tip olarak d�nd�r�r (genellikle std::ptrdiff_t, ki bu 
genellikle std::size_t'nin i�aretli kar��l��� olarak kullan�lan tip).

Dizi ��elerine at() �ye fonksiyonu kullanarak eri�im, �al��ma zaman� s�n�rlama kontrol� yapar (ve s�n�rlar d���nda kal�rsa std::out_of_range 
tipinde bir istisna atar). �stisna yakalanmazsa, uygulama sonland�r�l�r.

Hem operator[] hem de at() �ye fonksiyonu, const olmayan indekslerle indekslemeyi destekler. Ancak, her ikisi de indeksin size_type tipinde 
olmas�n� bekler, bu da bir i�aretsiz integral tipidir. Bu, indeksler constexpr olmad���nda i�aret d�n���m� sorunlar�na neden olur.

std::vector tipinde bir nesne, di�er herhangi bir nesne gibi bir fonksiyona ge�irilebilir. Yani, bir std::vector'� de�er olarak ge�irirsek,
pahal� bir kopya yap�l�r. Bu nedenle, genellikle bu t�r kopyalar� �nlemek i�in std::vector'� (const) referans olarak ge�iririz.
Herhangi bir ��e tipiyle bir std::vector'� bir fonksiyona ge�irebilmek i�in bir fonksiyon �ablonu kullanabiliriz. Vekt�r�n do�ru uzunlukta oldu�unu
garanti etmek i�in bir assert() kullanabilirsiniz.

Kopya semanti�i terimi, nesnelerin kopyalar�n�n nas�l yap�ld���n� belirleyen kurallara at�fta bulunur. Kopya semanti�inin �a�r�ld���n� 
s�yledi�imizde, bir nesnenin bir kopyas�n� yapacak bir �ey yapt�k demektir.

Verinin sahipli�i bir nesneden di�erine aktar�ld���nda, verinin ta��nd���n� s�yleriz.
Ta��ma semanti�i, bir nesnenin verisinin ba�ka bir nesneye nas�l ta��nd���n� belirleyen kurallara at�fta bulunur. Ta��ma semanti�i �a�r�ld���nda,
ta��nabilecek herhangi bir veri �yesi ta��n�r ve ta��namayan herhangi bir veri �yesi kopyalan�r. Veriyi kopyalamak yerine ta��ma yetene�i, 
pahal� bir kopyay� ucuz bir ta��ma ile de�i�tirebildi�imizde, ta��ma semanti�ini kopya semanti�inden daha verimli hale getirebilir.

Normalde, bir nesne ayn� tip bir nesne ile ba�lat�l�yor veya atan�yorsa, kopya semanti�i kullan�l�r (kopyan�n elided olmad��� varsay�l�r).
Ta��ma semanti�i, nesnenin tipinin ta��ma semanti�ini destekledi�i ve ba�lat�c� veya atanm�� nesnenin bir rvalue oldu�unda otomatik olarak 
kullan�l�r.

Ta��nabilir t�rler (�rne�in `std::vector` ve `std::string` gibi) de�er olarak d�nd�r�lebilir. Bu t�rler, de�erlerini pahal� bir kopya yapmak yerine
ucuz bir �ekilde ta��yacakt�r.

Bir konteynerin her bir eleman�na belirli bir s�rayla eri�mek, konteyneri dola�ma veya konteynerden ge�me olarak adland�r�l�r. Dola�ma ayr�ca bazen
konteyner �zerinde yineleme veya konteynerden ge�me olarak adland�r�l�r.

Diziden ge�mek i�in genellikle d�ng�ler kullan�l�r, bir d�ng� de�i�keni indeks olarak kullan�l�r. Bir fazla hatalar�na dikkat edin, burada d�ng�
g�vdesi bir fazla veya bir eksik kez �al���r.

Aral�kl� bir d�ng� (bazen de her biri i�in d�ng� olarak adland�r�l�r), a��k indekslemeyi yapmadan bir konteynerin dola��lmas�na izin verir.
Konteynerleri dola��rken aral�kl� d�ng�leri d�zenli d�ng�ler �zerinde tercih edin.

Dizi eleman�n�n t�r�n� derleyicinin ��karabilmesi i�in aral�kl� d�ng�lerle t�r ��kar�m�n� (auto) kullan�n. Eleman bildirimi, normalde o eleman
t�r�n� (const) referans olarak ge�irece�iniz zaman bir (const) referans kullanmal�d�r. Kopyalarla �al��man�z gerekmeyen s�rece her zaman 
const auto& kullanmay� d���n�n. Bu, eleman t�r� daha sonra de�i�tirilse bile kopyalar�n yap�lmad���ndan emin olacakt�r.

Kapsams�z enumerasyonlar indeks olarak kullan�labilir ve indeksin anlam� hakk�nda bilgi sa�lamaya yard�mc� olabilir. Dizi uzunlu�unu temsil eden
bir enumerat�r gerekti�inde ek bir "say�m" enumerat�r� eklemek yararl�d�r. Bir dizinin uzunlu�unun say�m enumerat�r�ne e�it oldu�unu belirtmek veya
statik belirtmek i�in bir dizi, beklenen say�da ba�lat�c�yla ba�lat�ld���ndan emin olabilirsiniz.

Dizinin uzunlu�unun �rnekleme noktas�nda tan�mlanmas� ve daha sonra de�i�tirilememesi gereken dizilere sabit boyutlu diziler veya sabit uzunluklu
diziler denir. Bir dinamik dizi (veya yeniden boyutland�r�labilir dizi olarak da adland�r�l�r), boyutu �rneklemeden sonra de�i�tirilebilen bir 
dizidir. Yeniden boyutland�r�labilir olma yetene�i, `std::vector`'� �zel k�lar.

Bir `std::vector`, yeni istenen uzunlukla `resize()` �ye fonksiyonunu �a��rarak �rneklemeden sonra yeniden boyutland�r�labilir.

Bir `std::vector` ba�lam�nda, kapasite `std::vector`'�n ka� eleman i�in depolama ay�rd���d�r ve uzunluk �u anda kullan�lan elemanlar�n say�s�d�r.
Bir `std::vector`'�n kapasitesini `capacity()` �ye fonksiyonu arac�l���yla sorgulayabiliriz.

Bir `std::vector` y�netti�i depolama miktar�n� de�i�tirdi�inde, bu s�rece yeniden tahsis denir. Yeniden tahsis genellikle dizinin her eleman�n�n 
kopyalanmas�n� gerektirdi�inden, yeniden tahsis pahal� bir i�lemdir. Sonu� olarak, yeniden tahsislerden makul oldu�unca ka��nmak istiyoruz.

subscript operat�r�n�n (operator[]) ve `at()` �ye fonksiyonunun ge�erli indeksleri, vekt�r�n uzunlu�una dayal�d�r, kapasitesine de�il.

`std::vector`'�n, vekt�r�n kapasitesini uzunlu�una uyacak �ekilde k���ltme talebinde bulunan `shrink_to_fit()` ad�nda bir �ye fonksiyonu vard�r.
Bu talep ba�lay�c� de�ildir.

Bir y���nda eklenen ve ��kar�lan ��elerin s�ras�, son giren ilk ��kar (LIFO) olarak tan�mlanabilir. Y���na eklenen son tabak, ��kar�lan ilk tabak 
olacakt�r. Programlamada, bir y���n, elemanlar�n ekleme ve ��karma i�lemlerinin LIFO �eklinde ger�ekle�ti�i bir konteyner veri t�r�d�r. 
Bu genellikle `push` ve `pop` adl� iki i�lemle uygulan�r.

`std::vector` �ye fonksiyonlar� `push_back()` ve `emplace_back()`, bir `std::vector`'�n uzunlu�unu art�r�r ve kapasite, de�eri eklemek i�in yeterli
de�ilse bir yeniden tahsisin ger�ekle�mesine neden olur. Bir ��e eklerken yeniden tahsis tetiklendi�inde, `std::vector` genellikle bir sonraki ��e
eklenirken ba�ka bir yeniden tahsisin tetiklenmesini �nlemek i�in biraz ekstra kapasite ay�r�r.

                `resize()` �ye fonksiyonu, vekt�r�n uzunlu�unu ve gerekirse kapasiteyi de�i�tirir.
                `reserve()` �ye fonksiyonu yaln�zca kapasiteyi de�i�tirir (gerekirse)

Bir std::vector'deki ��e say�s�n� art�rmak i�in:

- Indeksleme yoluyla bir vekt�re eri�irken resize() kullan�n. Bu, vekt�r�n uzunlu�unu de�i�tirir, b�ylece indeksleriniz ge�erli olur.
- Vekt�re y���n i�lemleri kullanarak eri�irken reserve() kullan�n. Bu, vekt�r�n uzunlu�unu de�i�tirmeden kapasite ekler.
- Hem push_back() hem de emplace_back() bir ��eyi y���na iter. �telenen nesne zaten varsa, push_back() ve emplace_back() e�de�erdir.
  Ancak, bir ge�ici nesne olu�turup onu vekt�re itmeye ihtiya� duydu�umuz durumlarda, emplace_back() daha verimli olabilir. C++20 itibar�yla,
  push_back() yerine emplace_back() tercih etmek i�in pek bir neden yoktur.

Boolean de�erler i�in benzer �ekilde 8 Boolean de�erini bir byte'a s�k��t�ran std::vector<bool> i�in daha fazla alan verimli bir uygulama vard�r.

std::vector<bool> bir vekt�r de�ildir (bellekte ard���k olmas� gerekmez), ne de bool de�erleri tutar (bir bit koleksiyonu tutar), ne de C++'�n bir
konteynerin tan�m�n� kar��lar. std::vector<bool>, �o�u durumda bir vekt�r gibi davran�r, ancak standart k�t�phanenin geri kalan�yla tamamen uyumlu
de�ildir. Di�er ��e t�rleriyle �al��an kod, std::vector<bool> ile �al��mayabilir. Sonu� olarak, genellikle std::vector<bool> ka��n�lmal�d�r.
*/