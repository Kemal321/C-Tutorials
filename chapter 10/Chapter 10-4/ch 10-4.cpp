#include <iostream>
template <typename T> 
T max(T x, T y) {
    return (x < y) ? y : x;
}
int main()
{

    std::cout << max(1, 2) << '\n';
    return 0;
}
/*
10.15 � Fonksiyon �ablonlar� - Function templates
-------------------------------------------------

Diyelim ki iki say�n�n maksimumunu hesaplamak i�in bir fonksiyon yazmak istiyorsunuz. Bunu �u �ekilde yapabilirsiniz:

                    int max(int x, int y) {
                        return (x < y) ? y : x;
                        // Not: std::max, < yerine > kullan�r.
                    }

�a�r�c� farkl� de�erleri fonksiyona iletebilirken, parametre t�rleri sabit oldu�u i�in �a�r�c� yaln�zca int de�erlerini iletebilir. Bu, bu fonksiyonun
ger�ekten yaln�zca tam say�lar i�in iyi �al��t��� anlam�na gelir (ve int'e y�kseltilebilen t�rler i�in).

Peki, ileride iki double de�erinin maksimumunu bulmak istedi�inizde ne olur? ��nk� C++, t�m fonksiyon parametrelerinin t�r�n� belirtmemizi gerektirdi�i
i�in, ��z�m, double t�r�nde parametrelere sahip yeni bir a��r� y�klenmi� max s�r�m� olu�turmakt�r:

                    double max(double x, double y)
                    {
                        return (x < y) ? y: x;
                    }


Dikkat edin ki, maksimum i�leminin double versiyonunun uygulamas�, tam say� versiyonu i�in olan�yla tam olarak ayn�! Asl�nda, bu uygulama bir�ok farkl�
t�rde �al���r: int, double, long, long double ve hatta kendinizin olu�turdu�u yeni t�rler dahil (bu konuya gelecekteki derslerde nas�l yap�laca��n�
��renece�iz).

Her desteklemek istedi�imiz parametre t�rleri seti i�in ayn� uygulamaya sahip a��r� y�klenmi� fonksiyonlar olu�turmak, bak�m zorluklar�na, hatalar�n
kayna��na ve DRY (kendini tekrar etme) ilkesinin a��k bir ihlaline yol a�ar. Ayr�ca, burada daha az a��k bir zorluk da var: max fonksiyonunu kullanmak
isteyen bir programc�, max'�n yazar�n�n �ng�rmedi�i (ve bu nedenle a��r� y�klenmi� bir fonksiyon yazmad���) bir arg�man t�r�yle �a��rmak isteyebilir.

Ger�ekten eksik olan �ey, herhangi bir t�rdeki arg�manlarla �al��abilen tek bir max s�r�m� yazma yoludur (belki de max i�in kod yaz�l�rken �ng�r�lmeyen
t�rler dahil). Normal fonksiyonlar burada g�revin alt�ndan kalkamazlar. Neyse ki, C++ bu t�r bir problemi �zel olarak ��zmek i�in tasarlanm�� ba�ka bir
�zelli�i destekler.

C++ �ablon d�nyas�na ho� geldiniz.

C++ templatelerine giri�
------------------------
C++'da, �ablon sistemi farkl� veri t�rleriyle �al��abilen fonksiyonlar� (veya s�n�flar�) olu�turmay� kolayla�t�rmak amac�yla tasarlanm��t�r.

Farkl� t�rler i�in ayr� ayr� neredeyse ayn� fonksiyonlar� veya s�n�flar� manuel olarak olu�turmak yerine, tek bir �ablon olu�turulur. Normal bir tan�ma
benzer �ekilde, bir �ablon, bir fonksiyonun veya s�n�f�n nas�l g�r�nd���n� a��klar. Normal bir tan�m�n aksine (t�m t�rlerin belirtilmesi gerekti�i bir
yer), �ablonlarda bir veya daha fazla yer tutucu t�r kullan�labilir. Bir yer tutucu t�r, �ablonun yaz�ld��� zamanda bilinmeyen ancak daha sonra
sa�lanacak bir t�r� temsil eder.

Bir �ablon tan�mland���nda, derleyici �ablonu kullanarak ihtiya� duyulan kadar �ok a��r� y�klenmi� fonksiyonu (veya s�n�f�) �retebilir, her biri farkl�
ger�ek t�rleri kullanarak!

Sonu� ayn�d�r - neredeyse ayn� fonksiyon veya s�n�flara sahibiz (her bir farkl� t�r k�mesi i�in bir tane). Ancak sadece tek bir �ablon olu�turmak ve
s�rd�rmek zorunday�z ve derleyici t�m zor i�leri bizim i�in yapar.

Kilit nokta**

Derleyici, tek bir �ablonu kullanarak farkl� t�r k�mesini kullanan ilgili bir fonksiyon veya s�n�f ailesi olu�turabilir.

�te yandan...
�ablonlar�n ard�ndaki konsepti kelimelerle anlatmak zor olabilece�inden, bir benzetme deneyelim.

S�zl�kte "�ablon" s�zc���ne bakt���n�zda �una benzer bir tan�m bulursunuz: "�ablon, benzer nesneler olu�turmak i�in kal�p g�revi g�ren bir modeldir".
Anla��lmas� �ok kolay olan �ablon t�rlerinden biri stencillerdir. Bir stencil, �zerinde bir �ekil (�rne�in mutlu bir y�z) kesilmi� ince bir malzeme
par�as�d�r (bir karton veya plastik par�as� gibi). Stencil'i ba�ka bir nesnenin �zerine yerle�tirerek ve ard�ndan delikten boya p�sk�rterek kesilen
�ekli �ok h�zl� bir �ekilde kopyalayabilirsiniz. Stencilin kendisinin yaln�zca bir kez olu�turulmas� gerekir ve ard�ndan istedi�iniz say�da farkl�
renkte kesilmi� �ekli olu�turmak i�in istedi�iniz kadar yeniden kullan�labilir. Daha da iyisi, Stencilden olu�turulan �eklin renginin, stencil ger�ekten
kullan�l�ncaya kadar belirlenmesine gerek yoktur.

�ablon-template- asl�nda fonksiyonlar veya s�n�flar olu�turmaya y�nelik bir stencildir. �ablonu (kal�b�m�z� - stencil yani -) bir kez yarat�r�z ve ard�ndan
onu, belirli bir ger�ek t�r k�mesi i�in bir fonksiyoni veya s�n�f� kal�plamak i�in gerekti�i kadar kullanabiliriz. �ablon ger�ekten kullan�l�ncaya kadar
bu ger�ek t�rlerin belirlenmesine gerek yoktur.


��nk� ger�ek t�rler, �ablon bir programda kullan�ld���nda belirlenir (�ablon yaz�ld���nda de�il), �ablonun yazar� t�m kullan�labilecek ger�ek t�rleri
tahmin etmeye �al��mak zorunda de�ildir. Bu, �ablon kodunun, �ablon yaz�ld���nda bile var olmayan t�rlerle kullan�labilmesi anlam�na gelir! Bu, daha
sonra C++ standart k�t�phanesini ke�fetmeye ba�lad���m�zda ne kadar i�e yarayabilece�imizi g�rece�imiz bir konudur; ��nk� C++ standart k�t�phanesi,
tamamen �ablon koduyla doludur!

Kilit nokta**
�ablonlar, �ablon yaz�ld���nda mevcut olmayan t�rlerle bile �al��abilir. Bu, �ablon kodunun hem esnek hem de gelece�e haz�r olmas�na yard�mc� olur!

Fonksiyon �ablonlar� yani templateleri
--------------------------------------

Bir fonksiyon �ablonu, farkl� bir set ger�ek t�rlerle her biri a��r� y�klenmi� bir veya daha fazla fonksiyon olu�turmak i�in kullan�lan bir fonksiyon
benzeri tan�mlamad�r. Bu, bir�ok farkl� t�rle �al��abilen fonksiyonlar olu�turmam�za olanak tan�yacakt�r.

Fonksiyon �ablonumuzu olu�tururken, daha sonra belirtmek istedi�imiz herhangi bir parametre t�r�, d�n�� t�r� veya fonksiyon g�vdesinde kullan�lan 
t�r i�in yer tutucu t�rler (ayr�ca t�r �ablon parametreleri (type template parameters) veya gayri resmi olarak �ablon t�rleri ( template types ) olarak 
adland�r�l�r) kullan�r�z.


Fonksiyon �ablonlar� en iyi �rneklerle ��retilen bir konsepttir, bu y�zden yukar�daki �rnekteki normal max(int, int) fonksiyonumuzu bir fonksiyon
�ablonuna d�n��t�relim. �a��rt�c� derecede kolayd�r ve yol boyunca neler oldu�unu a��klayaca��z.

�ablonlu bir max fonksiyonu olu�turmak
--------------------------------------

max fonksuyonunun integer hali:

                    int max(int x, int y)
                    {
                        return (x < y) ? y : x;
                    }

Bu fonksiyonda int t�rini �� kez kullan�yoruz: bir kez x parametresi i�in, bir kez y parametresi i�in ve bir kez de fonksiyonun d�n�� t�ri i�in.

Bir fonksiyon �ablonu olu�turmak i�in iki �ey yapaca��z. �lk olarak, belirli t�rlerimizi t�r �ablon parametreleri ile de�i�tirece�iz. Bu durumda, 
yaln�zca bir t�r�n yerine konmas� gerekti�i i�in (int), yaln�zca bir tane t�r �ablon parametresine ihtiyac�m�z var (ki ona T diyece�iz):

��te tek bir �ablon t�r� kullanan yeni fonksiyonumuz:

                    T max(T x, T y) // Bu �uan derlenmeyecek ��nk� daha T yi tan�mlamad�k
                    {
                        return (x < y) ? y : x;
                    }

Bu iyi bir ba�lang�� -- ancak derleyici T'nin ne oldu�unu bilmedi�i i�in derlenmeyecek! Ve bu hala normal bir fonksiyon, bir fonksiyon �ablonu de�il.

�kinci olarak, derleyiciye bu fonksiyonun bir fonksiyon �ablonu oldu�unu ve T'nin herhangi bir t�r i�in yer tutucu olan bir t�r �ablon parametresi 
oldu�unu s�yleyece�iz. Bunu, bir �ablon parametre deklarasyonu olarak adland�r�lan bir �eyle yapar�z. Bir �ablon parametre deklarasyonunun kapsam�,
takip eden fonksiyon �ablonuna (veya s�n�f �ablonuna) s�n�rl�d�r. Bu nedenle, her fonksiyon �ablonu (veya s�n�f) kendi �ablon parametre deklarasyonuna
ihtiya� duyar.

                    template <typename T> // bu, �ablon parametre deklarasyonudur
                    T max(T x, T y) // bu, max<T> i�in fonksiyon �ablonu tan�m�d�r
                    {
                        return (x < y) ? y : x;
                    }

�ablon parametre deklarasyonumuzda, bir �ablon olu�turdu�umuzu belirten anahtar kelime olarak template kullan�r�z. Ard�ndan, �ablonumuzun i�inde
kullanaca��m�z t�m �ablon parametrelerini k��eli parantezler i�inde belirtiriz (<>). Her t�r �ablon parametresi i�in typename veya class anahtar
kelimesini kullan�r�z, ard�ndan t�r �ablon parametresinin ad� gelir (�rne�in, T).

Bir kenara not olarak...

Bu ba�lamda typename ve class anahtar kelimeleri aras�nda hi�bir fark yoktur. �nsanlar� genellikle dilin daha �nce tan�t�ld��� i�in class anahtar
kelimesini kullan�rken g�receksiniz. Ancak, daha yeni olan typename anahtar kelimesini tercih ediyoruz, ��nk� bu, t�r �ablon parametresinin yaln�zca 
s�n�f t�rleri de�il, ayn� zamanda temel t�rler gibi herhangi bir t�rle de de�i�tirilebilece�ini daha a��k bir �ekilde belirtir.


�nan�n veya inanmay�n, i�te bu kadar! �imdi, farkl� t�rlerdeki arg�manlar� kabul edebilen max fonksiyonumuzun �ablon versiyonunu olu�turduk.

Bu fonksiyon �ablonu, T adl� bir �ablon t�r�ne sahip oldu�u i�in ona max<T> olarak at�fta bulunaca��z. Bir sonraki derste, max<T> fonksiyon 
�ablonumuzu nas�l kullanaca��m�z� ve farkl� t�rlerdeki parametrelerle bir veya daha fazla max() fonksiyonunu nas�l olu�turaca��m�z� inceleyece�iz.

Template parametrelerinin adland�r�lmas�
----------------------------------------
Bir de�i�kenin ad�n� (�rne�in, x) basit durumlarda genellikle tek bir harfle adland�r�yorsak, bu t�rin anlam� basit veya a��k oldu�unda genellikle
tek bir b�y�k harf (T ile ba�layan) kullanmak al���lm�� bir uygulamad�r. �rne�in, max fonksiyon �ablonumuzda:

T'ye karma��k bir ad vermemize gerek yok, ��nk� a��k�a yaln�zca kar��la�t�r�lan de�erler i�in bir yer tutucu t�rd�r.

Genellikle fonksiyon �ablonlar�m�z bu isimlendirme kurallar�n� kullanacakt�r.

E�er bir t�r �ablon parametresinin a��k olmayan bir kullan�m� veya anlam� varsa, o zaman daha a��klay�c� bir isim gereklidir. Bu t�r isimlendirme i�in
iki yayg�n kural bulunmaktad�r:

Bir b�y�k harfle ba�lamak (�rne�in, Allocator). Standart k�t�phane bu isimlendirme kural�n� kullan�r.
T ile ba�lay�p sonra bir b�y�k harfle ba�lamak (�rne�in, TAllocator). Bu, t�r�n bir t�r �ablon parametresi oldu�unu daha kolay g�rmemizi sa�lar.

Hangisini se�ece�imiz bize kalm�� bir durumdur. 

*** BEST 
---------
Basit veya a��k bir �ekilde kullan�lan t�r �ablon parametrelerine T, U, V gibi tek bir b�y�k harf ba�lat�l�r.

E�er t�r �ablon parametresinin a��k olmayan bir kullan�m� veya anlam� varsa, o zaman daha a��klay�c� bir isim gerekir (�rne�in, Allocator veya 
TAllocator).

10.16 � Fonksiyon �ablonu �rneklemesi
-------------------------------------

Bu derste fonksiyon �ablonlar�n�n nas�l kullan�laca��na odaklanaca��z.

Fonksiyon �ablonlar� asl�nda fonksiyonlar de�ildir - kodlar� do�rudan derlenmez veya do�rudan y�r�t�lmez. Bunun yerine, fonksiyon �ablonlar�n�n bir 
g�revi vard�r: fonksiyonlar� �retmek (derlenip y�r�t�len).

max<T> fonksiyon �ablonumuzu kullanmak i�in a�a��daki s�zdizimiyle bir fonksiyon �a�r�s� yapabiliriz:

                    max<actual_type>(arg1, arg2); // actual_type bir t�rd�r, int veya double gibi           

Bu, normal bir fonksiyon �a�r�s�na olduk�a benziyor - temel fark, �ablon t�r� T'nin yerine kullan�lacak ger�ek t�r� belirten a��k parantez i�indeki
t�rd�r (bu bir �ablon arg�man� olarak adland�r�l�r).

Bunu basit bir �rnekte inceleyelim:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // �ablonu �rnekler ve max<int>(int, int) fonksiyonunu �a��r�r

                        return 0;
                    }

Derleyici, max<int>(1, 2) fonksiyon �a�r�s�n� kar��la�t���nda, max<int>(int, int) i�in bir fonksiyon tan�m�n�n zaten mevcut olmad���n� belirleyecektir.
Sonu� olarak, derleyici max<T> fonksiyon �ablonumuzu kullanarak bir tane olu�turacakt�r.

Fonksiyon �ablonlar�ndan (�ablon t�rleri ile) fonksiyonlar olu�turma s�recine "fonksiyon �ablonu �rneklemesi (veya k�saca �rnekleme) olu�turma" denir.
Bu s�re� bir fonksiyon �a�r�s� nedeniyle ger�ekle�ti�inde, buna "�rt�k �rnekleme" denir. Bir �rneklenmi� fonksiyon, genellikle bir fonksiyon �rne�i
(k�saca �rnek) veya bir �ablon fonksiyonu olarak adland�r�l�r. Fonksiyon �rnekleri her y�nden normal fonksiyonlard�r.

Bir fonksiyonun an�nda yap�lma s�reci basittir: derleyici temelde fonksiyon �ablonunu klonlar ve �ablon t�rini (T) belirtti�imiz ger�ek t�r ile 
de�i�tirir.

Bu nedenle max<int>(1, 2) �a�r�s�nda, an�nda olu�turulan fonksiyon �una benzer bir �eydir:

                    template<> // �uanl�k umursamay�n
                    int max<int>(int x, int y) // �rneklenmi� fonksiyon max<int>(int, int)
                    {
                        return (x < y) ? y : x;
                    }

Yukar�daki �rne�in ayn�s� a�a��da g�sterilmi�tir. Burada derleyicinin t�m anlamland�rmalar� yapt�ktan sonra asl�nda neyi derledi�ini g�steriyor:

                    #include <iostream>

                    // Fonksiyon �ablonumuzun bir deklarasyonu (art�k tan�m�na ihtiya� duymuyoruz)
                    template <typename T>
                    T max(T x, T y);

                    // Belirli bir t�r i�in �zel birle�tirilmi� (specialized) fonksiyon max<int>(int, int)
                    template <>
                    int max<int>(int x, int y) // olu�turulan fonksiyon max<int>(int, int)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // fonksiyon max<int>(int, int) instante edilir ve �a�r�l�r

                        return 0;
                    }

Kendi bilgisayar�n�zda derleyip �al��t�rabilir ve i�ledi�ini g�rebilirsiniz. Bir fonksiyon �ablonu, her �eviri biriminde bir fonksiyon �a�r�s� 
yap�ld���nda yaln�zca ilk kez an�nda olu�turulur. Fonksiyona yap�lan sonraki �a�r�lar, zaten olu�turulmu� olan fonksiyona y�nlendirilir.

Tersine, bir �eviri biriminde bir fonksiyon �ablonuna hi� �a�r� yap�lmazsa, o fonksiyon �ablonu o �eviri biriminde an�nda olu�turulmaz.

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y) // max(T, T) i�in bir fonksiyon �ablonu
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n';    // max<int>(int, int) �ablonunu an�nda olu�turur ve �a��r�r
                        std::cout << max<int>(4, 3) << '\n';    // zaten olu�turulmu� max<int>(int, int) fonksiyonunu �a��r�r
                        std::cout << max<double>(1, 2) << '\n'; // max<double>(double, double) �ablonunu an�nda olu�turur ve �a��r�r

                        return 0;
                    }

Bu C++ kodu, bir �nceki �rnekle benzer �ekilde �al���r, ancak bu sefer fonksiyon �ablonumuz iki fonksiyon olu�turmak i�in kullan�l�r: bir tanesi T'yi int 
ile de�i�tirerek, di�eri T'yi double ile de�i�tirerek. T�m anlamland�rmalar yap�ld�ktan sonra, program �u �ekilde g�r�necektir.

                    #include <iostream>

                    // Fonksiyon �ablonumuzun bir deklarasyonu (art�k tan�m�na ihtiya� duymuyoruz)
                    template <typename T>
                    T max(T x, T y);

                    // int t�r� i�in �zel birle�tirilmi� (specialized) max fonksiyonu tan�m�: max<int>(int, int)
                    template <>
                    int max<int>(int x, int y)
                    {
                        return (x < y) ? y : x;
                    }

                    // double t�r� i�in �zel birle�tirilmi� (specialized) max fonksiyonu tan�m�: max<double>(double, double)
                    template <>
                    double max<double>(double x, double y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n';    // max<int>(int, int) �ablonunu an�nda olu�turur ve �a��r�r
                        std::cout << max<int>(4, 3) << '\n';    // zaten olu�turulmu� max<int>(int, int) fonksiyonunu �a��r�r
                        std::cout << max<double>(1, 2) << '\n'; // max<double>(double, double) �ablonunu an�nda olu�turur ve �a��r�r

                        return 0;
                    }
****
Burada dikkat edilmesi gereken bir ba�ka �ey: max<double> �rneklemi yap�ld���nda, �rneklemi olu�turulan fonksiyonun parametreleri double t�r�ndedir.
��nk� int arg�manlar� sa�lad�k, bu arg�manlar otomatik olarak double t�r�ne d�n��t�r�l�r.

�ablon Arg�man ��kart�m�
------------------------
�o�u durumda, anlamland�rmak istedi�imiz t�rler genellikle fonksiyon parametrelerimizin t�rleriyle e�le�ir. �rne�in:

                    std::cout << max<int>(1, 2) << '\n'; // max<int> �a�r�s�n� yapmak istedi�imizi belirtiyoruz

Bu fonksiyon �a�r�s�nda, T'yi int ile de�i�tirmek istedi�imizi belirttik, ancak ayn� zamanda fonksiyonu int arg�manlar� ile �a��r�yoruz.

Arg�man t�rleri, istedi�imiz ger�ek t�rle e�le�ti�inde, ger�ek t�r� belirtmeye gerek yoktur. Bunun yerine, fonksiyon �a�r�s�ndaki arg�man
t�rlerinden ger�ek t�r�n ��kart�lmas� i�in �ablon arg�man ��karsamas�n� kullanabiliriz.

�rne�in, �u �ekilde bir fonksiyon �a�r�s� yapmak yerine:

                    std::cout << max<>(1, 2) << '\n';
                    std::cout << max(1, 2) << '\n';

Her iki durumda da derleyici, ger�ek bir t�r sa�lamad���m�z� g�recektir, bu nedenle bir max() fonksiyonu olu�turmak i�in fonksiyon arg�manlar�ndan bir
ger�ek t�r ��karmaya �al��acakt�r. Bu, template parametrelerinin t�r�yle sa�lanan arg�manlar�n t�r� e�le�en bir max() fonksiyonu olu�turmas�na izin
verecek. Bu �rnekte, derleyici, int t�r�n� kullanarak max<T> fonksiyon �ablonunu kullanarak, her iki template parametresinin t�r�n�n (int) sa�lanan
arg�manlar�n t�r�yle e�le�ti�i max<int>(int, int) fonksiyonunu olu�turman�n m�mk�n oldu�unu ��karacakt�r.

�ki durum aras�ndaki fark, derleyicinin a��r� y�klenmi� fonksiyonlar�n bir k�mesinden bir fonksiyon �a�r�s�n� nas�l ��zd��� ile ilgilidir. �stteki
durumda (bo� a��l� parantezlerle), derleyici, hangi a��r� y�klenmi� fonksiyonu �a��raca��n� belirlerken yaln�zca max<int> �ablon fonksiyon a��r� 
y�klemelerini g�z �n�ne alacakt�r. Altta (a��l� parantez olmadan) durumda, derleyici hem max<int> �ablon fonksiyon a��r� y�klemelerini hem de max
�ablon olmayan fonksiyon a��r� y�klemelerini g�z �n�ne alacakt�r.

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        std::cout << "max<int>(int, int) �a�r�ld�\n";
                        return (x < y) ? y : x;
                    }

                    int max(int x, int y)
                    {
                        std::cout << "max(int, int) �a�r�ld�\n";
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // max<int>(int, int) �a�r�l�r
                        std::cout << max<>(1, 2) << '\n';    // max<int>(int, int) ��kar�m yapar (template olmayan fonksiyonlar dikkate al�nmaz)
                        std::cout << max(1, 2) << '\n';      // max(int, int) �a�r�l�r

                        return 0;
                    }

Not etmek �nemlidir ki, alttaki durumdaki s�zdizimi normal bir fonksiyon �a�r�s�yla tamamen ayn� g�r�n�yor! �o�u durumda, bir fonksiyondan t�retilmi�
fonksiyonlari �a��rmak i�in normal fonksiyon �a�r�s� s�zdizimini kullan�r�z.

Bunun birka� nedeni vard�r:

* S�zdizimi daha �zd�r.
* E�le�en bir �ablon olmayan fonksiyon ve bir fonksiyon �ablonu genellikle nadiren olacakt�r.
* E�er e�le�en bir �ablon olmayan fonksiyon ve bir e�le�en fonksiyon �ablonumuz varsa, genellikle �ablon olmayan fonksiyone �ncelik veririz.

Bu son nokta a��k olmayabilir. Bir fonksiyon �ablonunun birden �ok t�rle �al��abilen bir uygulamas� vard�r - ancak bu nedenle geneldir. Bir �ablon
olmayan fonksiyonun yaln�zca belirli bir t�r kombinasyonuyla ba�a ��kma yetene�i vard�r. Bu, belirli t�rler i�in optimize edilmi� veya daha 
�zelle�tirilmi� bir uygulamaya sahip olabilir. �rne�in:

                    #include <iostream>

                    // Bu fonksiyon �ablonu bir�ok t�r� i�leyebilir, bu nedenle uygulamas� geneldir
                    template <typename T>
                    void print(T x)
                    {
                        std::cout << x; // T'yi normalde nas�l yazd�r�yorsa �yle yazd�r
                    }

                    // Bu fonksiyon sadece bir bool de�erini nas�l yazd�raca��n� d���nmek zorundad�r, bu nedenle bool yazd�rma �eklini �zelle�tirebilir
                    void print(bool x)
                    {
                        std::cout << std::boolalpha << x; // bool'� 1 veya 0 de�il, true veya false olarak yazd�r
                    }

                    int main()
                    {
                        print<bool>(true); // print<bool>(bool) �a��r�r -- 1'i yazd�r�r
                        std::cout << '\n';

                        print<>(true);     // print<bool>(bool) ��kar�m yapar (template olmayan fonksiyonlar dikkate al�nmaz) -- 1'i yazd�r�r
                        std::cout << '\n';

                        print(true);       // print(bool) �a��r�r -- true'yi yazd�r�r
                        std::cout << '\n';

                        return 0;
                    }

*** BEST -> Fonksiyon �ablonundan t�retilen bir fonksiyonu �a��r�rken normal fonksiyon �a�r�s� s�zdizimini tercih edin (e�le�en bir �ablon olmayan 
fonksiyonu ge�erli bir durumda tercih etmeniz gerekmiyorsa).

genellikle bir �ablon fonksiyonundan t�retilmi� bir fonksiyonun yan�nda ayn� parametrelerle �al��an bir �ablon olmayan fonksiyonun bulunma olas�l���n�n 
d���k oldu�udur. E�er b�yle bir durum varsa ve �ablondan t�retilmi� fonksiyonun spesifik durumlar� kontrol etmek i�in yaz�lm��sa, o durumda normal
fonksiyon �a�r�s� daha mant�kl�d�r.

Ayr�ca, e�er �ablon olmayan bir fonksiyon mevcut de�ilse, yani sadece �ablondan t�retilen bir fonksiyon varsa, normal fonksiyon �a�r�s� yapmak yine 
ayn� sonuca yol a�acakt�r. ��nk� derleyici, o parametrelerle �a�r�lan fonksiyon i�in �ablondan ��kar�m yaparak uygun �ablon t�rlerini belirleyecek
ve fonksiyonu ona g�re �retecektir.

Non-template parametreler ile Fonksiyon templateleri
----------------------------------------------------

Non-template parametreler i�eren fonksiyon �ablonlar� olu�turmak m�mk�nd�r. T�r �ablon parametreleri herhangi bir t�rle e�le�tirilebilir ve 
non-template parametreler, normal fonksiyonlar�n parametreleri gibi �al���r.

�rne�in:

                    // T, bir t�r �ablon parametresidir
                    // double, bir �ablon olmayan parametredir
                    template <typename T>
                    int birFonksiyon(T, double)
                    {
                        return 5;
                    }

                    int main()
                    {
                        birFonksiyon(1, 3.4); // someFcn(int, double) ile e�le�ir
                        birFonksiyon(1, 3.4f); // someFcn(int, double) ile e�le�ir -- float bir double'a d�n��t�r�l�r
                        birFonksiyon(1.2, 3.4); // someFcn(double, double) ile e�le�ir
                        birFonksiyon(1.2f, 3.4); // someFcn(float, double) ile e�le�ir
                        birFonksiyon(1.2f, 3.4f); // someFcn(float, double) ile e�le�ir -- float bir double'a d�n��t�r�l�r

                        return 0;
                    }

Bu fonksiyon �ablonunun �ablonlanm�� ilk parametresi bulunmakla birlikte, ikinci parametre t�ri double olarak sabittir. Geri d�n�� t�r�n�n de herhangi
bir t�r olabilece�ini unutmay�n. Bu durumda, fonksiyonumuz her zaman bir int de�eri d�nd�recektir.

�rneklenmi� fonksiyonlar her zaman derlenmeyebilir 
--------------------------------------------------
�u programa g�z atal�m:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }
Derleyici bunu etkili bir �ekilde derleyip y�r�tecektir:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x);

                    template<>
                    int addOne<int>(int x)
                    {
                        return x + 1;
                    }

                    template<>
                    double addOne<double>(double x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne(1) << '\n';   // addOne<int>(int) fonksiyonunu �a��r�r
                        std::cout << addOne(2.3) << '\n'; // addOne<double>(double) fonksiyonunu �a��r�r

                        return 0;
                    }
��kt� olarak ise:   2
                    3.3 
��kt�lar�n� verir 
Peki ya b�yle bir �ey denersek? 

                    #include <iostream>
                    #include <string>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::string hello { "Hello, world!" };
                        std::cout << addOne(hello) << '\n';

                        return 0;
                    }

Derleyici, addOne(hello) ifadesini ��zmeye �al��t���nda addOne(std::string) i�in �ablon olmayan bir fonksiyon e�le�mesi bulamayacak, ancak addOne(T) 
i�in fonksiyon �ablonumuzu bulacak ve ondan addOne(std::string) fonksiyonunu �retebilece�ini belirleyecektir. Bu nedenle, derleyici �unu �retecek ve
derleyecektir:

                    #include <iostream>
                    #include <string>

                    template <typename T>
                    T addOne(T x);

                    template<>
                    std::string addOne<std::string>(std::string x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::string hello{ "Hello, world!" };
                        std::cout << addOne(hello) << '\n';

                        return 0;
                    }

Ancak, bu, bir std::string t�r�nde bir arg�manla addOne() �a��rmak mant�kl� olmad��� i�in derleme hatas� �retecektir. Burada a��k bir ��z�m,
basit�e addOne()'� std::string t�r�nde bir arg�manla �a��rmamakt�r.

�rneklenmi� fonksiyonlar her zaman anlamsal olarak anlaml� olmayabilir
----------------------------------------------------------------------

Derleyici, bir fonksiyon �ablonunu ba�ar�yla derler, bu s�re�, sentaktik olarak anlaml� oldu�u s�rece ger�ekle�ir. Ancak, derleyicinin b�yle bir i�lemin 
semantik olarak anlaml� olup olmad���n� kontrol etme yetene�i yoktur.

�rne�in:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne("Hello, world!") << '\n';

                        return 0;
                    }

Bu �rnekte, bir C tarz� dize literali �zerinde addOne()'� �a��r�yoruz. Bu semantik olarak ne anlama geliyor? Kim bilir!

�a��rt�c� bir �ekilde, C++ sentaktik olarak bir tamsay� de�erini bir dize literaliyle toplamaya izin verdi�i i�in (bu konuyu ileriki ders 17.9'da ele 
alaca��z - ��aret�i aritmeti�i ve indeksleme), yukar�daki �rnek derlenir ve a�a��daki sonucu �retir:

              ��kt�: ello, world!

Uyar�

Derleyici, semantik olarak anlaml� olmayan fonksiyon �ablonlar�n� sentaktik olarak ge�erli olduklar� s�rece an�nda olu�turacak ve derleyecektir. Bu t�r 
fonksiyon �ablonlar�n� anlaml� arg�manlarla �a��rd���n�zdan emin olmak sizin sorumlulu�unuzdad�r.

Birden �ok dosyada Fonksiyon �ablonlar�n� kullanma
--------------------------------------------------

A�a��daki program� d���n�n, bu program do�ru �al��maz:

main.cpp: 
                    #include <iostream>

                    template <typename T>
                    T addOne(T x); // function template forward declaration

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }
add.cpp:
                    template <typename T>
                    T addOne(T x) // fonksiyon template tan�m�
                    {
                        return x + 1;
                    }

E�er addOne bir �ablon olmayan bir fonksiyon olsayd�, bu program sorunsuz �al��acakt�: main.cpp'de derleyici addOne'�n ileri bildiriminden memnun
olacak ve ba�lay�c�, main.cpp'deki addOne() �a�r�s�n� add.cpp'deki fonksiyon tan�m�na ba�layacakt�.

Ancak addOne bir �ablon oldu�u i�in, bu program �al��maz ve bir ba�lay�c� hatas� al�r�z:

1>Project6.obj : error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main
1>Project6.obj : error LNK2019: unresolved external symbol "double __cdecl addOne<double>(double)" (??$addOne@N@@YANN@Z) referenced in function _main

main.cpp'de addOne<int> ve addOne<double> �a��r�yoruz. Ancak, derleyici fonksiyon �ablonu addOne'�n tan�m�n� g�remedi�i i�in, bu fonksiyonlar� main.cpp 
i�inde �zelle�tiremez. Ancak addOne i�in ileri bildirimi g�r�r ve bu fonksiyonlar�n ba�ka bir yerde var oldu�unu ve daha sonra ba�lanacaklar�n� varsayar.

Derleyici add.cpp'yi derlerken, fonksiyon �ablonu addOne'�n tan�m�n� g�recek. Ancak, add.cpp'de bu �ablonun kullan�ld��� bir yer olmad���ndan,
derleyici hi�bir �ey �zelle�tirmeyecektir. Sonu� olarak, ba�lay�c�, addOne<int> ve addOne<double> �a�r�lar�n� main.cpp'de ger�ek fonksiyonlara
ba�layamaz, ��nk� bu fonksiyonlar hi�bir zaman �zelle�tirilmedi.

Yan� s�ra...

E�er add.cpp, bu fonksiyonlar� �zelle�tirmi� olsayd�, program sorunsuz derlenir ve ba�lan�rd�. Ancak, bu t�r ��z�mler k�r�lgand�r ve ka��n�lmal�d�r: 
e�er add.cpp'deki kod daha sonra bu fonksiyonlar� �zelle�tirmiyorsa, program yeniden ba�lant�da ba�ar�s�z olacakt�r. Ya da main.cpp add.cpp'de 
�zelle�tirilmemi� olan ba�ka bir addOne s�r�m�n� (�rne�in addOne<float>) �a��rsayd�, yine ayn� sorunla kar��la��r�z.

Bu sorunu ��zmenin en geleneksel yolu, t�m �ablon kodunuzu kaynak (.cpp) dosyas� yerine ba�l�k (.h) dosyas�na koymakt�r:

add.h:
                    #ifndef ADD_H
                    #define ADD_H

                    template <typename T>
                    T addOne(T x) // Fonksiyon template tan�m�
                    {
                        return x + 1;
                    }

                    #endif
main.cpp:
                    #include "add.h" // Fonksiyon template tan�m�n� i�eri aktar�r�z
                    #include <iostream>

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }

Bu �ekilde, �ablona eri�im sa�lamas� gereken herhangi bir dosya ilgili ba�l�k dosyas�n� #include edebilir ve �ablon tan�m� �n i�lemci taraf�ndan 
kaynak dosyas�na kopyalanacakt�r. Derleyici, ard�ndan gereken herhangi bir fonksiyona �zelle�tirebilecektir.

Bunu neden bir tan�m ihlali (ODR) olu�turmaz soruyor olabilirsiniz. ODR, t�rlerin, �ablonlar�n, i� i�e fonksiyonlar�n ve i� i�e de�i�kenlerin farkl�
dosyalarda ayn� tan�ma sahip olmalar�na izin verildi�ini s�yler. Bu nedenle, �ablon tan�m�n�n birden �ok dosyaya kopyalanmas� bir sorun te�kil etmez 
(her tan�m�n ayn� olmas� ko�uluyla).

Ancak �zelle�tirilmi� fonksiyonlar kendileri ne olacak? E�er bir fonksiyon birden �ok dosyada �zelle�tirilirse, bu ODR'nin ihlaline yol a�maz m�? Cevap, 
�ablondan �nceden �zelle�tirilmi� fonksiyonlar�n dolayl� olarak olarak inline oldu�udur. Ve bildi�iniz gibi,inline fonksiyonlar, tan�m�n her birinde ayn� 
oldu�u s�rece birden �ok dosyada tan�mlanabilir.

Temel Bilgi

�ablon tan�mlar�, sadece program ba��na tek bir tan�ma izin veren tek bir tan�ma kural�n�n bu k�sm�ndan muaf tutulmu�tur, bu nedenle ayn� �ablon
tan�m�n�n birden �ok kaynak dosyas�na #include edilmesi sorun olu�turmaz. Fonksiyon �ablonlar�ndan dolayl� olarak olarak �zelle�tirilen 
fonksiyonlar ise dolayl� olarak olarak inlinedir, bu nedenle her tan�m�n ayn� olmas� ko�uluyla birden �ok dosyada tan�mlanabilir.

�ablonlar kendileri i� i�e de�ildir, ��nk� i� i�e kavram� yaln�zca de�i�kenler ve fonksiyonlar i�in ge�erlidir.

��te bir ba�ka �rnek, bir ba�l�k dosyas�na yerle�tirilen bir fonksiyon �ablonu, b�ylece birden �ok kaynak dosyaya dahil edilebilir:

max.h:
                    #ifndef MAX_H
                    #define MAX_H

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    #endif
foo.cpp:
                    #include "max.h" // max<T>(T, T) i�in �ablon tan�m�n� i�e aktar
                    #include <iostream>

                    void foo()
                    {
                        std::cout << max(3, 2) << '\n';
                    }
main.cpp:
                    #include "max.h" // max<T>(T, T) i�in �ablon tan�m�n� i�e aktar
                    #include <iostream>

                    void foo(); // fonksiyon foo i�in ileri bildirim

                    int main()
                    {
                        std::cout << max(3, 5) << '\n';
                        foo();

                        return 0;
                    }
Yukar�daki �rnekte, hem main.cpp hem de foo.cpp "max.h" dosyas�n� #include eder, bu nedenle her iki dosyadaki kod da max<T>(T, T) fonksiyon �ablonundan
yararlanabilir.

*** BEST -> Birden �ok dosyada ihtiya� duyulan �ablonlar, bir ba�l�k dosyas�nda tan�mlanmal� ve ard�ndan gerekti�i yerde #include edilmelidir. Bu, 
            derleyicinin tam �ablon tan�m�n� g�rmesine ve �ablonu gerekti�inde �zelle�tirmesine olanak tan�r.

Generic Programlama
-------------------
�ablon t�rleri, herhangi bir ger�ek t�rle de�i�tirilebilece�inden, �ablon t�rleri bazen genel t�rler olarak adland�r�l�r. Ve ��nk� �ablonlar belirli 
t�rlerden ba��ms�z olarak yaz�labilir, �ablonlarla programlama bazen genel programlama ( jenerik programlama - generic programming )
olarak adland�r�l�r. C++ genellikle t�rler ve t�r denetimine odaklan�rken, genel programlama, algoritmalar�n mant��� ve veri yap�lar�n�n tasar�m�na 
odaklanmam�za, t�r bilgisiyle fazla ilgilenmeden �al��mam�za olanak tan�r.


Sonu�

Bir kere �ablon fonksiyon yazmay� al��t���n�zda, ger�ek t�rlerle olan fonksiyonlardan �ok daha uzun s�rmedi�ini fark edeceksiniz. Fonksiyon �ablonlar�,
yaz�lmas� ve bak�m� gereken kod miktar�n� minimize ederek kod bak�m�n� ve hatalar� �nemli �l��de azaltabilir.

Fonksiyon �ablonlar�n�n birka� dezavantaj� bulunmaktad�r ve bunlar� belirtmemek olmaz. �lk olarak, derleyici, her benzersiz arg�man t�r k�mesi ile 
yap�lan her fonksiyon �a�r�s� i�in bir fonksiyon olu�turacakt�r (ve derleyecektir). Bu nedenle, fonksiyon �ablonlar� yazmak kompakt olsa da, 
��lg�nca miktarda kod haline gelebilir, bu da kod �i�mesine ve yava� derleme s�relerine neden olabilir. Fonksiyon �ablonlar�n�n daha b�y�k bir 
dezavantaj�, genellikle ��lg�nca g�r�nen, s�n�rl� okunabilir hata mesajlar� �retmeye e�ilimli olmalar�d�r ve bunlar d�zenli fonksiyonlar�n hatalar�ndan
�ok daha zor ��z�lebilir. Bu hata mesajlar� olduk�a korkutucu olabilir, ancak size ne anlatmaya �al��t�klar�n� anlad���n�zda, i�aret ettikleri 
sorunlar�n genellikle olduk�a basit ��z�mlere sahip oldu�unu g�receksiniz.

Bu dezavantajlar, �ablonlar�n programlama ara� setinize getirdi�i g�� ve g�venlikle kar��la�t�r�ld���nda olduk�a k���kt�r, bu nedenle herhangi bir 
yerde t�r esnekli�ine ihtiya� duyuyorsan�z �ablonlar� �zg�rce kullan�n!

**** �yi bir kural, �nce normal fonksiyonlar olu�turmak, sonra farkl� parametre t�rleri i�in bir a��r� y�klemeye ihtiya� duyarsan�z bunlar� fonksiyon
     �ablonlar�na d�n��t�rmektir.

*** BEST -> �htiya� duydu�unuz her yerde geni� bir t�r yelpazesiyle �al��abilen genel kod yazmak i�in fonksiyon �ablonlar�n� kullan�n.


10.17 � Birden �ok �ablon T�r� ��eren Fonksiyon �ablonlar�
----------------------------------------------------------
Bir �nceki derste yazd���m�z �rne�in �zerinden devam edelim: 

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(1, 2) << '\n';   // max(int, int) ile �rneklenecek
                        std::cout << max(1.5, 2.5) << '\n'; // max(double, double) ile �rneklenecek

                        return 0;
                    }
�imdi benzer bir programa bakal�m:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';  // compile error

                        return 0;
                    }

Bu program�n derlenmeyece�ini g�rmek sizi �a��rtabilir. Bunun yerine, derleyici bir dizi (muhtemelen ��lg�nca g�r�nen) 
hata mesaj� verecektir. Visual Studio'da, yazar �unlar� ald�:
                    Project3.cpp(11,18): error C2672: 'max': no matching overloaded function found
                    Project3.cpp(11,28): error C2782: 'T max(T,T)': template parameter 'T' is ambiguous
                    Project3.cpp(4): message : see declaration of 'max'
                    Project3.cpp(11,28): message : could be 'double'
                    Project3.cpp(11,28): message : or       'int'
                    Project3.cpp(11,28): error C2784: 'T max(T,T)': could not deduce template argument for 'T' from 'double'
                    Project3.cpp(4): message : see declaration of 'max'
    
Fonksiyon �a�r�m�m�z max(2, 3.5) ile iki farkl� t�rde arg�manlar ge�iyoruz: biri int, di�eri double. K��eli parantez kullanmadan bir fonksiyon �a�r�s� 
yap�yoruz ��nk� ger�ek bir t�r belirtmiyoruz. Derleyici �nce max(int, double) i�in �ablon e�le�mesi olup olmad���n� kontrol eder. Bulamaz.

Daha sonra, derleyici, template argument deduction kullanarak (ki bunu lesson 10.16 -- Function template instantiation b�l�m�nde ele ald�k) bir 
fonksiyon �ablonu e�le�mesi bulup bulamayaca��n� kontrol eder. Ancak bu da basit bir nedenle ba�ar�s�z olacakt�r: T, yaln�zca tek bir t�r� temsil
edebilir. T'nin, derleyicinin max<T>(T, T) fonksiyon �ablonunu iki farkl� parametre t�r�ne sahip bir fonksiyona �zelle�tirmesine izin verecek bir
t�r� yoktur. Ba�ka bir deyi�le, fonksiyon �ablonundaki her iki parametre de T t�r�ndedir, bu nedenle ayn� ger�ek t�re ��z�lmelidir.

Hi�bir �ablon d��� e�le�me bulunamad��� ve hi�bir �ablon e�le�mesi bulunamad��� i�in, fonksiyon �a�r�s� ��z�lemiyor ve derleme hatas� al�yoruz.

Derleyicinin neden function max<double>(double, double) �retmedi�ini ve ard�ndan int arg�man�n� double'a d�n��t�rmek i�in say�sal d�n���m�
kullanmad���n� merak edebilirsiniz. Cevap basittir: t�r d�n���m�, fonksiyon a��r� y�klemeleri ��z�l�rken yap�l�r, �ablon arg�man ��kar�m� yap�l�rken 
de�il.

Bu t�r d�n���m eksikli�i en az iki nedenle kas�tl�d�r. �lk olarak, �eyleri basit tutmaya yard�mc� olur: ya fonksiyon �a�r� arg�manlar� ile �ablon t�r
parametreleri aras�nda tam bir e�le�me buluruz, ya da bulamay�z. �kinci olarak, iki veya daha fazla parametrenin ayn� t�re sahip olmas�n� istedi�imiz
durumlar i�in fonksiyon �ablonlar� olu�turmam�za izin verir (yukar�daki �rnekte oldu�u gibi).

Bu sorunu (en az�ndan) �� farkl� �ekilde ��zebiliriz.

Arg�manlar� e�le�en t�rlere d�n��t�rmek i�in static_cast kullan�n
-----------------------------------------------------------------
�lk ��z�m, �a��ran�n arg�manlar� e�le�en t�rlere d�n��t�rme y�k�n� ta��mas�n� sa�lamakt�r. �rne�in:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                       std::cout << max(static_cast<double>(2), 3.5) << '\n'; // int'i double'a d�n��t�rerek max(double, double) fonksiyonunu �a��r�yoruz

                       return 0;
                    }

�imdi her iki arg�man da double t�r�nde oldu�undan, derleyici bu fonksiyon �a�r�s�n� kar��layacak max(double, double) �ablonunu �zelle�tirebilecektir.

Ancak, bu ��z�m sakar ve okunmas� zordur.

A��k�a bir t�r �ablon arg�man� sa�lamak
---------------------------------------
E�er bir �ablon olmayan max(double, double) fonksiyonu yazm�� olsayd�k, o zaman max(int, double) �a�r�s�n� yapabilir ve implicit t�r d�n���m
kurallar�n�n int arg�man�m�z� double'a d�n��t�rmesine izin verebilirdik, b�ylece fonksiyon �a�r�s� ��z�lebilirdi:

                    #include <iostream>

                    double max(double x, double y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n'; // arg�man int t�r�nden double t�r�ne �evrilecekti.

                        return 0;
                    }

Ancak, derleyici �ablon arg�man ��karsamas� yaparken herhangi bir t�r d�n���m� yapmaz. Neyse ki, belirli bir t�r �ablon arg�man� belirledi�imizde �ablon
arg�man ��karsamas�n� kullanmak zorunda de�iliz:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        // T�r� a��k�a double olarak belirtti�imizden dolay�, derleyici �ablon arg�man ��karsamas�n� kullanmayacak
                        std::cout << max<double>(2, 3.5) << '\n';

                        return 0;
                    }

Yukar�daki �rnekte, max<double>(2, 3.5) �a�r�s�n� yapar�z. T'nin a��k�a double ile de�i�tirilmesini belirtti�imiz i�in, derleyici �ablon arg�man
��karsamas�n� kullanmayacak. Bunun yerine, sadece max<double>(double, double) fonksiyonunu �zelle�tirecek ve ard�ndan t�rleri e�le�meyen arg�manlar�
t�r d�n��t�recektir. int parametremiz otomatik olarak bir double'a d�n��t�r�lacakt�r.

Bu, static_cast kullanmaktan daha okunakl� olsa da, max fonksiyonini �a��r�rken hi� t�rleri d���nmememiz daha da g�zel olurdu.

Birden fazla �ablon t�r parametresine sahip fonksiyon �ablonlar�
----------------------------------------------------------------

Problemin k�keni, fonksiyon �ablonumuz i�in yaln�zca tek bir �ablon t�r�n� (T) tan�mlam�� olmam�z ve ard�ndan her iki parametrenin de bu ayn� t�rde 
olmas� gerekti�ini belirtmi� olmam�zd�r.

Bu sorunu ��zmenin en iyi yolu, parametrelerimizin farkl� t�rlere ��z�mlenebilece�i bir �ekilde fonksiyon �ablonumuzu yeniden yazmakt�r. 
Art�k yaln�zca bir �ablon t�r� parametresi (T) kullanmak yerine iki parametre kullanaca��z (T ve U):

                    #include <iostream>

                    template <typename T, typename U> // �ki tane T ve U ad�nda �ablon t�r parametresi kullan�yoruz
                    T max(T x, U y) // x, T t�r�ne ��z�mlenebilir ve y, U t�r�ne ��z�mlenebilir
                    {
                        return (x < y) ? y : x; // burada bir daralma d�n���m problemimiz var
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';

                        return 0;
                    }

��nk� x'i �ablon t�r� T ile ve y'yi �ablon t�r� U ile tan�mlad�k, x ve y �imdi ba��ms�z bir �ekilde t�rlerini ��zebilirler. max(2, 3.5) �a�r�s�n� 
yapt���m�zda, T bir int ve U bir double olabilir. Derleyici, bizim i�in max<int, double>(int, double) t�r�n� seve seve �z�mserecektir.

Ancak yukar�daki kodun hala bir sorunu var: normal aritmetik kurallar� (10.5 - Aritmetik d�n���mler) kullanarak, double int'in �st�nl���n� al�r, 
bu nedenle ko�ullu operat�r�m�z bir double d�nd�recektir. Ancak fonksiyonumuz bir T d�nd�rme �eklinde tan�mlanm��t�r - T bir int'e ��z�nd��� durumlarda,
double d�nd�rme de�erimiz bir int'e daraltma d�n���m�ne u�rayacakt�r, bu da bir uyar�ya (ve veri kayb�na) neden olabilir.

D�n�� t�r�n� U olarak yapmak da sorunu ��zmez, ��nk� T ve U'nun t�rlerini yer de�i�tirebilece�imiz bir durumda, t�rlerin s�ras�n� de�i�tirebiliriz.

Bu sorunu nas�l ��zebiliriz? Bu durum i�in otomatik d�n�� t�r� harika bir kullan�m �rne�idir - derleyiciye d�n�� t�r�n�n ne olmas� gerekti�ini d�nen 
ifadeden ��karsamas�na izin verece�iz.

                    #include <iostream>

                    template <typename T, typename U>
                    auto max(T x, U y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';

                        return 0;
                    }

Bu versiyonu ile max fonksiyonu, farkl� t�rlerdeki i�lemlerle sorunsuz bir �ekilde �al���r.


Kilit nokta

Her �ablon t�r parametresi, t�r�n� ba��ms�z bir �ekilde ��zer.

Bu, T ve U adl� iki t�r parametresine sahip bir �ablonun T ve U'nun farkl� t�rlerle ��z�nebilece�i anlam�na gelir, veya ayn� t�re ��z�nebilirler.


K�salt�lm�� fonksiyon �ablonlar�
--------------------------------
C++20, `auto` anahtar kelimesinin yeni bir kullan�m�n� tan�t�yor: Auto anahtar kelimesi, normal bir fonksiyonda bir parametre t�r� olarak 
kullan�ld���nda, derleyici otomatik olarak fonksiyonu, her `auto` parametresini ba��ms�z bir �ablon t�r parametresi haline getiren bir 
fonksiyon �ablonuna d�n��t�recektir. Bu y�ntemle olu�turulan fonksiyon �ablonuna "k�salt�lm�� fonksiyon �ablonu" denir.

�rne�in:
                    auto max(auto x, auto y)
                    {
                        return (x < y) ? y : x;
                    }

C++20'de a�a��dakilerin k�saltmas�d�r:

                    template <typename T, typename U>
                    auto max(T x, U y)
                    {
                        return (x < y) ? y : x;
                    }

Bu, yukar�da yazd���m�z max fonksiyon �ablonuyla ayn�d�r.

Her �ablon t�r parametresinin ba��ms�z bir t�r olmas�n� istedi�iniz durumlarda, bu form tercih edilir ��nk� �ablon parametre bildirimi sat�r�n�n 
kald�r�lmas�, kodunuzu daha �zl� ve okunabilir hale getirir.

Bir veya daha fazla `auto` parametresinin ayn� t�rde olmas�n� istedi�inizde, k�salt�lm�� fonksiyon �ablonlar�n� kullanman�n �zl� bir yolu
bulunmamaktad�r. Yani, ��yle bir durum i�in kolayca k�salt�lm�� bir fonksiyon �ablonu bulunmamaktad�r:

                    template <typename T>
                    auto max(T x, T y) // ayn� t�r�n iki parametresi
                    {
                        return (x < y) ? y : x;
                    }


Tek bir auto parametreli k�salt�lm�� fonksiyon �ablonlar�n� veya her auto parametresinin ba��ms�z bir t�r olmas�n� istedi�iniz durumlar� 
(ve dil standart�n�z C++20 veya daha yeni s�r�mde ise) �zg�rce kullanabilirsiniz.

10.18 � Non-type ( T�r d��� ) template parametreleri
----------------------------------------------------

�nceki derslerde, t�r �ablon parametrelerini kullanan fonksiyon �ablonlar�n� nas�l olu�turaca��m�z� tart��t�k. Bir t�r �ablon parametresi, bir �ablon
arg�man� olarak ge�irilen ger�ek bir t�r i�in bir yer tutucu olarak g�rev yapar.

t�r �ablon parametreleri, ��phesiz ki kullan�lan en yayg�n �ablon parametre t�r�d�r; ancak bilinmesi gereken ba�ka bir t�r de vard�r: t�r d��� �ablon
parametresi.

Non-type template parametreleri
-------------------------------

t�r d��� bir �ablon parametresi, bir �ablon arg�man� olarak ge�irilen bir constexpr de�eri temsil eden sabit bir t�re sahip bir �ablon parametresidir.

t�r d��� bir �ablon parametresi, a�a��daki t�rlerden herhangi biri olabilir:

* - Bir tamsay� t�ri
* - Bir numaraland�rma t�ri
* - std::nullptr_t
* - Bir kayan nokta t�ri (C++20'den itibaren)
* - Bir nesnenin i�aret�isi veya referans�
* - Bir fonksiyonin i�aret�isi veya referans�
* - Bir �ye fonksiyonin i�aret�isi veya referans�
* - Bir literal s�n�f t�ri (C++20'den itibaren)

�lk t�r d��� �ablon parametresi �rne�imizi, std::bitset'i ele ald���m�z O.1 dersinde g�rd�k:

                    #include <bitset>

                    int main()
                    {
                        std::bitset<8> bits{ 0b0000'0101 }; // <8> bir non-type template parameteresidir

                        return 0;
                    }

(C++'ta) std::bitset �rne�inde, t�r d��� �ablon parametresi, std::bitset'e ka� bit saklamak istedi�imizi bildirmek i�in kullan�l�r.

Kendi non-type template parametrelerimizi tan�mlama
---------------------------------------------------
��te bir int t�rinde t�r d��� �ablon parametresi kullanan basit bir fonksiyon �rne�i:

                    #include <iostream>

                    template <int N> // int t�r�nde N isminde bir t�r d��� �ablon parametresi tan�mla
                    void print()
                    {
                        std::cout << N << '\n'; // N'nin de�erini burada kullan
                    }

                    int main()
                    {
                        print<5>(); // 5, t�r d��� �ablon arg�man�m�zd�r

                        return 0;
                    }
          ��kt�m�z: 5

Sat�r 3'te, �ablon parametre deklarasyonumuzu bulunmaktad�r. Dik a��l� parantezler i�inde, int t�r�nde bir de�erin yerine konulaca�� bir t�r d���
�ablon parametresi olan N'yi tan�ml�yoruz. print() fonksiyonu i�inde, N'nin de�erini kullan�yoruz.

Sat�r 11'de, print() fonksiyonunu �a��r�yoruz ve bunun i�in t�r d��� �ablon arg�man� olarak int t�r�nde 5 de�erini kullan�yoruz. Derleyici bu 
�a�r�y� g�rd���nde, a�a��daki gibi bir fonksiyonu �zel olarak olu�turacakt�r:

                    template <>
                    void print<5>()
                    {
                        std::cout << 5 << '\n';
                    }

�al��ma zaman�nda, bu fonksiyon `main()` fonksiyonundan �a�r�ld���nda, 5'i ekrana yazd�r�r.

Ard�ndan program sona erer. Olduk�a basit, de�il mi?

Genellikle T, ilk t�r �ablon parametresi i�in kullan�ld��� gibi, N de bir int t�r d��� �ablon parametresinin ad� olarak yayg�n olarak kullan�l�r.

*** BEST -> N'yi bir int t�r d��� �ablon parametresinin ad� olarak kullan�n.

t�r d��� �ablon parametreleri ne i�e yarar?
-------------------------------------------

C++20'den itibaren, Fonksiyon parametreleri `constexpr` olamaz. Bu durum, normal fonksiyonlar i�in ge�erli oldu�u gibi, `constexpr` fonksiyonlar i�in
de do�rudur (��nk� bunlar �al��ma zaman�nda �al��t�r�labilir olmal�d�r) ve belki de �a��rt�c� bir �ekilde,`consteval` fonksiyonlar i�in bile 
ge�erlidir.

Dolay�s�yla, ��yle bir fonksiyonumuz oldu�unu d���nelim:

                    #include <cassert>
                    #include <cmath> // std::sqrt i�in
                    #include <iostream>

                    double getSqrt(double d)
                    {
                        assert(d >= 0.0 && "getSqrt(): d must be non-negative");

                        if (d >= 0)
                            return std::sqrt(d);

                        return 0.0;
                    }

                    int main()
                    {
                        std::cout << getSqrt(5.0) << '\n';
                        std::cout << getSqrt(-5.0) << '\n';

                        return 0;
                    }


�al��t�r�ld���nda, getSqrt(-5.0) �a�r�s� �al��ma zaman�nda bir assert hatas� �retecektir. Bu, hi� olmamas�ndan daha iyidir, ��nk� -5.0 bir sabit 
(ve dolayl� olarak constexpr olarak kabul edilir), ancak bu hatan�n derleme zaman�nda yakalanabilmesi i�in static_assert kullanmak daha iyi olacakt�r.
Ancak, static_assert bir sabit ifade gerektirir ve fonksiyon parametreleri constexpr olamaz...

Ancak, fonksiyon parametresini bir t�r olmayan �ablona d�n��t�r�rsek, istedi�imizi tam olarak yapabiliriz:

                    #include <cmath> // std::sqrt
                    #include <iostream>

                    template <double D> // kayan noktal� olmayan t�r �ablon parametresi i�in c++20 gereklidir
                    double getSqrt()
                    {
                        static_assert(D >= 0.0, "getSqrt(): D negatif olamaz");

                        if constexpr (D >= 0) // Bu �rnekte constexpr'� g�rmezden gelebiliriz
                            return std::sqrt(D); // Garip bir �ekilde, std::sqrt C++26'ya kadar bir constexpr fonksiyon de�il

                        return 0.0;
                    }

                    int main()
                    {
                        std::cout << getSqrt<5.0>() << '\n';   // Ge�erli, karek�k� hesaplar ve yazd�r�r.
                        std::cout << getSqrt<-5.0>() << '\n';  // Hata: Derleme zaman�nda bir assert hatas� �retecek.

                        return 0;
                    }

Bu s�r�m derlenemeyecek. Derleyici, `getSqrt<-5.0>()` �a�r�s�n� kar��la�t���nda, �u �ekilde bir fonksiyoni �rnekleyip �a��racakt�r:

                    template <>
                    double getSqrt<-5.0>()
                    {
                        static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

                        if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
                            return std::sqrt(-5.0);

                        return 0.0;
                    }

static_assert ko�ulu yanl�� oldu�u i�in, derleyici bu durumu kontrol eder ve uyar�da bulunur.

Kilit nokta
-----------
Non-type template parametreleri, bir sabit ifadeye ihtiya� duyan ba�lamlarda kullan�lacak constexpr de�erlerini fonksiyonlara (veya s�n�f t�rlerine) 
iletmek i�in kullan�l�r.

std::bitset s�n�f t�r�, depolanacak bit say�s�n� belirtmek i�in bir non-type template parametresi kullan�r ��nk� bit say�s� bir constexpr de�eri
olmal�d�r.

Yazar�n Notu

Fonksiyon parametrelerinin constexpr olamamas� k�s�tlamas�n� atlatmak i�in non-type template parametrelerini kullanmak pek ideal de�il. Bu t�r 
durumlar� ele almaya y�nelik bir�ok farkl� �neri de�erlendiriliyor. Gelecekteki bir C++ dil standard�nda bu t�r durumlar i�in daha iyi bir ��z�m
g�rebilece�imizi d���n�yorum.
    
Non-type template arguments i�in �rt�k d�n���mler
-------------------------------------------------
Baz� non-type template arg�manlar�, farkl� bir t�r�n non-type template parametresine uymak i�in �rt�k d�n���mlere tabi tutulabilir. �rne�in:

                    #include <iostream>

                    template <int N> // int non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // Hi�bir d�n���m gerekmez
                        print<'c'>(); // 'c' tipindeki de�er int'e d�n��t�r�l�r, 99 yazd�r�r

                        return 0;
                    }
��kt�s�: 
                    5
                    99
Yukar�daki �rnekte, 'c', print() fonksiyon �ablonunun non-type template parametresine uymak i�in int'e d�n��t�r�l�r, ard�ndan de�er int olarak yazd�r�l�r.

Bu ba�lamda, yaln�zca belirli t�rlerde constexpr d�n���mlere izin verilir. En yayg�n izin verilen d�n���m t�rleri �unlar� i�erir:

- Tamsay� promosyonlar� (�rne�in, char'tan int'e)
- Tamsay� d�n���mleri (�rne�in, char'dan long veya int'e)
- Kullan�c� tan�ml� d�n���mler (�rne�in, belirli bir program taraf�ndan tan�mlanan bir s�n�f�n int'e d�n��t�r�lmesi)
- Lvalue'den rvalue'ye d�n���mler (�rne�in, baz� de�i�ken x'in x'in de�erine d�n��t�r�lmesi)

Bu liste, listeleme ba�latma i�in izin verilen �rt�k d�n���m t�rlerinden daha az ho�g�r�l�d�r. �rne�in, bir constexpr int kullanarak bir double 
t�r�ndeki bir de�i�keni liste ba�latmak m�mk�nd�r, ancak constexpr int non-type template arg�man� bir double non-type template parametresine 
d�n��meyecektir.

�zin verilen t�m d�n���mlerin tam listesine buradan ula�abilirsiniz, "Converted constant expression" alt b�l�m�nde bulunabilir.

Normal fonksiyonlarde oldu�u gibi, fonksiyon �ablon �a�r�lar�n� fonksiyon �ablon tan�mlar�yla e�le�tirmek i�in kullan�lan algoritma karma��k de�ildir ve
belirli d�n���m t�r�ne (veya olmamas�na) dayal� olarak di�erlerine �ncelik vermez. Bu, bir fonksiyon �ablonunun farkl� t�rde non-type template
parametreleri i�in a��r� y�klendi�inde, �ok kolay bir belirsiz e�le�me sonucuna yol a�abilir.

                    #include <iostream>

                    template <int N> // int non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    template <char N> // char non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // Belirsiz e�le�me: int N = 5 ve char N = 5 ile uyu�an iki versiyon oldu�u i�in
                        print<'c'>(); // Belirsiz e�le�me: int N = 99 ve char N = 'c' ile uyu�an iki versiyon oldu�u i�in

                        return 0;
                    }

Beklenmedik bir �ekilde, print() fonksiyonuna yap�lan her iki �a�r� da belirsiz e�le�melere neden olur.

'auto' kullanarak non-type template parametreleri i�in t�r ��karsama
------------------------------------------------------------------
C++17'den itibaren, non-type template parametreleri, derleyicinin template arg�man�ndan non-type template parametresini ��karmas� i�in auto kullanabilir:

                    #include <iostream>

                    template <auto N> // template arg�man�ndan non-type template parametresini ��karmak i�in auto kullan�l�r
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // N, int `5` olarak ��kar�l�r
                        print<'c'>(); // N, char `c` olarak ��kar�l�r

                        return 0;
                    }
Bu, beklenen sonucu derler ve �retir:   
                    5
                    c

Ba�ard�n! Bu b�l�mdeki konular (�zellikle t�r takma adlar�, a��r� y�klenmi� i�levler ve i�lev �ablonlar�) C++ standart kitapl���n�n her yerinde g�r�n�r.
Art�k her �eyin nas�l �al��t���n� anlamaya bir ad�m daha yakla�t�n�z!
*/
/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                     GENEL �ZET

Bir de�eri bir veri t�r�nden ba�ka bir veri t�r�ne d�n��t�rme s�recine "tip d�n���m�" denir.

Otamatik tip d�n���m� veya zorlamas� olarak da adland�r�lan i�sel tip d�n���m�, bir veri t�r� beklenirken, farkl� bir veri t�r� sa�land���nda 
ger�ekle�ir. Derleyici, iki t�r aras�ndaki d�n���m� nas�l ger�ekle�tirece�ini anlayabiliyorsa, bu d�n���m� ger�ekle�tirir. Bilmiyorsa, derleme hatas�
ile ba�ar�s�z olur.

C++ dilinde, temel t�rleri aras�nda (ve baz� geli�mi� t�rler i�in birka� d�n���m) tan�mlanan standart d�n���mler ad� verilen bir dizi yerle�ik d�n���m
bulunmaktad�r. Bunlar say�sal y�kseltmeleri, say�sal d�n���mleri ve aritmetik d�n���mleri i�erir.

Say�sal y�kseltme, belirli k���k say�sal t�rlerin belirli b�y�k say�sal t�rlere (genellikle int veya double) d�n��t�r�lmesidir, b�ylece CPU, i�lemcinin
do�al veri boyutuna uyan veri �zerinde �al��abilir. Say�sal y�kseltmeler, hem tamsay� y�kseltmelerini hem de kayan nokta y�kseltmelerini i�erir. 
Say�sal y�kseltmeler, de�eri koruyan yani de�er veya hassasiyet kayb� olmayan d�n���mlerdir. T�m geni�letme d�n���mleri y�kseltme de�ildir.

Say�sal d�n���m, say�sal bir y�kseltme olmayan temel t�rler aras�ndaki bir t�r d�n���m�d�r. Daraltma d�n���m�, de�er veya hassasiyet kayb�na neden 
olabilecek bir say�sal d�n���md�r.

C++'da, baz� ikili operat�rlerin operanlar�n�n ayn� t�rden olmas�n� gerektirdi�i durumlar vard�r. Farkl� t�rlerden operat�rler sa�lan�rsa, operanlardan
biri veya her ikisi de genel aritmetik d�n���mler ad� verilen bir dizi kural� kullanarak e�le�en t�rlere otomatik olarak d�n��t�r�l�r.

Belirli bir veri t�r�nden ba�ka bir veri t�r�ne d�n���m� talep etmek i�in programc� taraf�ndan a��k�a istendi�inde a��k tip d�n���m� ger�ekle�ir.
Bir d�n���m, programc�n�n a��k�a bir tip d�n���m� yap�lmas�n� talep etti�i bir istek olarak temsil eder. C++, C tarz� d�n���mler, static_cast, 
const_cast, dynamic_cast ve reinterpret_cast olmak �zere 5 tip d�n���m� destekler. Genellikle C tarz� d�n���mlerden, const d�n���mlerden ve reinterpret 
d�n���mlerinden ka��n�lmal�d�r. static_cast, bir t�rden ba�ka bir t�re bir de�eri d�n��t�rmek i�in kullan�l�r ve C++'taki en yayg�n kullan�lan
d�n���md�r.

Typedef'ler ve tip takma adlar�, programc�n�n bir veri t�r� i�in bir takma ad olu�turmas�na olanak tan�r. Bu takma adlar yeni t�rler de�ildir ve takma 
adland�r�lan t�rle ayn� �ekilde davran�r. Typedef'ler ve tip takma adlar�, herhangi bir t�r g�venli�i sa�lamaz ve takma ad�n as�l t�rden farkl� 
oldu�unu varsaymamak �nemlidir.

auto anahtar kelimesinin birka� kullan�m� vard�r. �lk olarak, auto, bir de�i�kenin t�r�n� ba�lat�c�s�ndan ��karacak olan t�r ��karsama (ayn� zamanda 
t�r ��karsama olarak da adland�r�l�r) i�in kullan�labilir. T�r ��karsama, const ve referanslar� d���r�r, bu nedenle bunlar� geri eklemek istiyorsan�z 
eklemelisiniz.

Auto ayr�ca bir fonksiyonun d�n�� t�r�n� belirlemek i�in de kullan�labilir. Ancak bu, normal fonksiyonlar i�in ka��n�lmas� gereken bir durumdur. Auto,
takip eden return s�zdizimi k�sm�n�n bir par�as� olarak kullan�l�r.

Fonksiyon a��r� y�kleme, ayn� isme sahip birden �ok fonksiyon olu�turmam�za olanak tan�r, ad� ge�en fonksiyonlar�n her biri farkl� bir parametre t�r� 
setine sahip olmal�d�r (veya fonksiyonlar ba�ka �ekilde ay�rt edilebilmelidir). B�yle bir fonksiyon bir a��r� y�klenmi� fonksiyon (veya k�saca a��r�
y�kleme) olarak adland�r�l�r. D�nd�rme t�rleri farkl�la�t�rma i�in kullan�lmaz.

A��r� y�kl� fonksiyonlar� ��zerken, e�er tam e�le�me bulunamazsa, derleyici say�sal y�kseltmeleri gerektiren a��r� y�klenmi� fonksiyonlar�, 
gerektirmeyenlere g�re tercih eder. Bir i�lev �a�r�s�, a��r� y�klenmi� bir i�leve e�le�mesi i�in kullan�lan arg�manlara dayanarak uygun a��r� y�klenmi�
i�levi bulmaya �al���r. Buna a��r� y�k ��z�mleme denir.

Belirli bir i�lev �a�r�s� ��z�mlenirken, a��r� y�klenmi� i�levlerden e�le�en biri bulunamazsa, derleyici say�sal y�kseltme gerektiren a��r� y�klenmi�
i�levleri, gerektirmeyenlere g�re tercih eder. Bir i�lev �a�r�s� yap�l�rken, derleyici, i�lev �a�r�s�nda kullan�lan arg�manlara dayanarak uygun a��r� 
y�klenmi� i�levi bulmaya �al���r. Buna a��r� y�k ��z�mleme denir.

Belirsiz bir e�le�me, derleyicinin bir i�lev �a�r�s�n� bir a��r� y�klenmi� i�leve e�le�tirmek i�in iki veya daha fazla i�lev bulmas� durumunda ortaya
��kar ve hangisinin en iyi oldu�unu belirleyemez.

Varsay�lan bir arg�man, bir i�lev parametresi i�in sa�lanan bir varsay�lan de�erdir. Varsay�lan arg�manlara sahip parametreler her zaman en sa�da 
olmal�d�r ve a��r� y�klenmi� i�levleri ��z�mlemede kullan�lmazlar.

Fonksiyon �ablonlar�, ilgili fonksiyonlar� olu�turmak i�in bir �ablon olarak hizmet eden bir fonksiyon benzeri tan�m� olu�turmam�za olanak tan�r. Bir 
fonksiyon �ablonunda, daha sonra belirtilmesi istenen herhangi bir t�r i�in tip �ablon parametreleri olarak kullan�l�r. Derleyiciye bir �ablon 
tan�mlad���m�zda ve �ablon t�rlerini bildirdi�imizde fonksiyonlar� olu�turma s�recine fonksiyon �ablonu anlam�na gelen �ablonun anlam�na gelir.

Fonksiyon �ablonu �a�r�ld���nda (fonksiyon �ablonu arg�manlar� belirtildi�inde), bu s�rece fonksiyon �ablonu anlam�na gelen anlam�na gelir. Bu s�re� 
bir fonksiyon �a�r�s� nedeniyle ger�ekle�irse, bu s�re� '�rt�k anlamland�rma' olarak adland�r�l�r ve �rnekleme bir fonksiyon �rne�i (veya k�sacas�
bir �rnek veya bazen bir �ablon fonksiyonu) olarak adland�r�l�r.

�ablon arg�man ��karsama, derleyicinin bir fonksiyon �a�r�s�n�n arg�manlar�ndan �ablonun anlam�n� ��karma yetene�idir. �ablon arg�man ��karsama, tip 
d�n���m� ger�ekle�tirmez.

�ablon t�rleri bazen generic t�rler olarak adland�r�l�r ve �ablonlar kullan�larak programlama bazen generic programlama olarak adland�r�l�r.

C++20'de auto anahtar kelimesi, bir normal fonksiyonda bir parametre t�r� olarak kullan�ld���nda, derleyici otomatik olarak her auto parametreyi 
ba��ms�z bir �ablon t�r parametre haline getirecek ve bunu yapmak i�in bu t�rde bir fonksiyon �ablonu olu�turacakt�r. Bu y�nteme k�salt�lm�� bir 
fonksiyon �ablonu denir.

Bir non-type template parametresi, bir sabit ifade olarak bir �ablon arg�man� olarak iletilen bir sabit t�r�ne sahip olan bir �ablon parametresidir.




























*/