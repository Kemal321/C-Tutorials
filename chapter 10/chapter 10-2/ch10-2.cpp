
#include <iostream>

int main()
{
    return 0;
}
/*
                                                        *10.7 � Typedefs ve T�r Takma Adlar�*
                                                        * --------------------------------- *

C++ dilinde, using kelimesi mevcut bir veri tipi i�in bir takma ad olu�turan bir anahtar kelimedir.

                    using Mesafe = double; // Mesafe'yi double t�r� i�in bir takma ad olarak tan�mla

Bir kez tan�mland�ktan sonra, bir t�r takma ad�, bir t�r gerekti�inde herhangi bir yerde kullan�labilir.

                    Mesafe milesToDestination{ 3.4 }; // double t�r�nde bir de�i�ken tan�mlar

Derleyici bir t�r takma ad� ismiyle kar��la�t���nda, takma ad�n yerine takma ad yap�lan t�r� yerine koyacakt�r. 

                    #include <iostream>

                    int main()
                    {
                        using Mesafe = double; // Mesafe'yi double t�r� i�in bir takma ad olarak tan�mla

                        Mesafe milesToDestination{ 3.4 }; // double t�r�nde bir de�i�ken tan�mlar

                        std::cout << milesToDestination << '\n'; // bir double de�eri yazd�r�r

                        return 0;
                    }
             ��kt�: 3.4

Yukar�daki programda, �nce Distance'� double t�r� i�in bir takma ad olarak tan�ml�yoruz.

Daha sonra, Distance t�r�nde milesToDestination ad�nda bir de�i�ken tan�ml�yoruz. Derleyici Distance'�n bir t�r takma ad� oldu�unu bildi�i i�in,
takma ad yap�lan t�r� kullanacak, yani double. Bu nedenle, milesToDestination de�i�keni asl�nda bir double t�r�nde derlenir ve her a��dan bir double
gibi davranacakt�r.

Son olarak, milesToDestination de�erini yazd�r�yoruz, bu da bir double de�eri olarak yazd�r�lacakt�r.

T�r takma adlar�n� adland�rma
-----------------------------
Tarih boyunca, t�r takma adlar�n�n adland�r�lmas�nda tutarl�l�k eksikli�i olmu�tur. �� yayg�n adland�rma kural� bulunmaktad�r (ve bunlar�n hepsine
rastlayacaks�n�z):

- Bir " _t " eki ile biten t�r takma adlar� ("_t", "type" kelimesinin k�saltmas�d�r). Bu kural genellikle standart k�t�phane taraf�ndan genel kapsaml�
t�r adlar� i�in kullan�l�r (�rne�in size_t ve nullptr_t gibi).
Bu kural, C'den miras al�nm�� olup, kendi t�r takma adlar�n�z� (ve bazen di�er t�rleri) tan�mlarken eskiden en pop�ler olan�yd�, ancak modern C++'da 
tercih edilen bir kural de�ildir. POSIX, "_t" eki i�in genel kapsaml� t�r adlar�n� ay�rd���ndan, bu kural�n kullan�lmas� POSIX sistemlerinde t�r ad� 
�ak��malar�na neden olabilir.

- Bir " _type " eki ile biten t�r takma adlar�. Bu kural, baz� standart k�t�phane t�rleri (�rne�in std::string) taraf�ndan kullan�l�r ve g�m�l� t�r 
takma adlar�n� (�rne�in std::string::size_type) adland�rmak i�in kullan�l�r.
Ancak bir�ok g�m�l� t�r takma ad� hi�bir ek kullanmaz (�rne�in std::string::iterator), bu nedenle bu kullan�m en iyi durumda tutars�zd�r.

- Hi�bir ek kullan�lmayan t�r takma adlar�.
Modern C++'da, genellikle kendiniz tan�mlad���n�z t�r takma adlar�n� (veya ba�ka herhangi bir t�r�) b�y�k harfle ba�latarak ve hi�bir ek kullanmadan
adland�rma konvansiyonu benimsenmi�tir. B�y�k harf, t�r adlar�n� de�i�ken ve fonksiyon adlar�ndan (ki bunlar k���k harfle ba�lar) ay�rmaya yard�mc� 
olur ve aralar�ndaki ad �ak��malar�n� �nler.

Bu adland�rma kural�n� kullan�rken �u kullan�m� s�k�a g�rmek yayg�nd�r:

                    void printDistance(Mesafe mesafe); // Mesafe, tan�mlanm�� bir t�rd�r

Bu durumda, Mesafe t�rd�r ve mesafe parametre ad�d�r. C++ case-sensitive bir dildir, bu nedenle bu kullan�m uygundur.

*** BEST -> T�r takma adlar�n�z� b�y�k harfle ba�lat�n ve bir ek kullanmaktan ka��n�n (e�er ba�ka bir nedeniniz yoksa).

T�r takma adlar�, ayr� t�rler de�ildir
--------------------------------------

Bir takma ad, asl�nda yeni ve ayr� bir t�r tan�mlamaz (di�er t�rlerden ayr� bir �ekilde d���n�len bir t�r) - yaln�zca mevcut bir t�r i�in yeni
bir tan�mlay�c� tan�t�r. Bir t�r takma ad�, tamamen takma ad yap�lan t�rle de�i�tirilebilir.

Bu, s�zdizimi a��s�ndan ge�erli ancak anlams�z olan �eyleri yapmam�za olanak tan�r. �rne�in:

                    int main()
                    {
                        using Miles = long; // Miles'i long t�r� i�in bir takma ad olarak tan�mla
                        using Speed = long; // Speed'� long t�r� i�in bir takma ad olarak tan�mla

                        Miles distance { 5 }; // distance asl�nda sadece bir long
                        Speed mhz  { 3200 };  // mhz asl�nda sadece bir long

                        // A�a��daki s�zdizimi a��s�ndan ge�erli (ancak anlams�z) bir durumdur
                        distance = mhz;

                        return 0;
                    }

Kavramsal olarak Miles ve Speed'in farkl� anlamlar� olmas�n� ama�lasak da, her ikisi de sadece long t�r� i�in takma adlard�r. Bu, etkili bir �ekilde
Miles, Speed ve long'un t�m�n�n birbirinin yerine kullan�labilece�i anlam�na gelir. Ve ger�ekten de, bir Speed t�r�nden bir de�eri bir Miles t�r�ndeki
bir de�i�kene atad���m�zda, derleyici yaln�zca bir long t�r�nden bir de�eri bir long t�r�ndeki bir de�i�kene atad���m�z� g�r�r ve herhangi bir uyar�
yapmaz.

Derleyici, t�r takma adlar� i�in bu t�r semantik hatalar� �nlemez, bu nedenle takma adlar�n t�r g�venli olmad���n� s�yleriz. Buna ra�men, bunlar hala 
kullan��l�d�r.

!!! Dikkat edilmelidir ki, semantik olarak farkl� olmas� ama�lanan takma ad de�erlerini kar��t�rmamaya �zen g�sterilmelidir.

Bir not olarak...

Baz� diller, g��l� bir t�r ad� (ya da g��l� t�r takma ad�) kavram�n� destekler. G��l� bir t�r ad�, asl�nda t�m orijinal �zelliklere sahip olan yeni
bir t�r olu�turur, ancak derleyici, takma ad t�r� ile orijinal t�r�n de�erlerini kar��t�rmaya �al���rsan�z bir hata f�rlat�r. C++20'ye kadar, C++
do�rudan g��l� t�r adlar�n� desteklemez (ancak 13.4 dersinde ele al�nan t�rlerle benzer olan enum class'lar mevcuttur), ancak g��l� t�r ad� benzeri
davran��� uygulayan bir�ok ���nc� taraf C++ k�t�phanesi bulunmaktad�r.

T�r takma ad�n�n kapsam�
------------------------

��nk� kapsam bir tan�mlay�c�n�n �zelli�idir, t�r takma ad� tan�mlay�c�lar� de�i�ken tan�mlay�c�lar�yla ayn� kapsama kurallar�n� takip eder: bir blok 
i�inde tan�mlanan bir t�r takma ad�n�n blok kapsam� vard�r ve yaln�zca o blok i�inde kullan�labilir, global ad alan�nda tan�mlanan bir t�r takma ad�n�n 
ise global kapsam� vard�r ve dosyan�n sonuna kadar kullan�labilir. Yukar�daki �rnekte, Miles ve Speed sadece main() fonksiyonunda kullan�labilir.

E�er bir veya daha fazla t�r takma ad�n� birden fazla dosya �zerinde kullanman�z gerekiyorsa, bunlar bir ba�l�k dosyas�nda tan�mlanabilir ve tan�m�
kullanmak isteyen t�m kod dosyalar�na #include edilebilir:

                        mytypes.h:
                        #ifndef MYTYPES_H
                        #define MYTYPES_H

                            using Miles = long;
                            using Speed = long;

                        #endif

Bu �ekilde #include edilen t�r takma adlar�, global ad al�n�na i�e aktar�lacak ve dolay�s�yla global kapsama sahip olacakt�r.

Typedefs
--------

Typedef ("type definition" k�saltmas�) bir t�r i�in takma ad olu�turman�n eski bir yoludur. Bir typedef takma ad� olu�turmak
i�in typedef anahtar kelimesini kullan�r�z:

                        // A�a��daki takma adlar �zde�tir
                        typedef long Miles;
                        using Miles = long;

Typedef'ler, geriye d�n�k uyumluluk nedenleriyle h�l� C++ dilinde bulunmaktad�r, ancak modern C++'ta genellikle t�r takma adlar�
taraf�ndan b�y�k �l��de yer de�i�tirmi�tir.

Typedef'lerin birka� s�zdizimi sorunu vard�r. �lk olarak, typedef'in ad�n�n m� yoksa takma ad yap�lacak t�r�n m� �nce gelece�ini
unutmak kolayd�r. Hangisi do�rudur?

                        typedef Distance double; // incorrect (typedef name first)
                        typedef double Distance; // correct (aliased type name first)

Bu durumu kar��t�rmak kolayd�r. Neyse ki, bu t�r durumlarda derleyici uyar� verecektir.

�kinci olarak, typedef'lerin s�zdizimi daha karma��k t�rlerle birlikte �irkinle�ebilir. �rne�in, okunmas� zor bir typedef a�a��da
verilmi� olup, buna kar��l�k gelen ve biraz daha okunabilir olan bir t�r takma ad� da bulunmaktad�r:

                        typedef int (*FcnType)(double, char); // FcnType'� bulmas� zordur 
                        using FcnType = int(*)(double, char); // FcnType' easier to find'� bulmas� kolayd�r 

Yukar�daki typedef tan�m�nda, yeni t�r�n ad� (FcnType) tan�m�n ortas�na g�m�lm��t�r, oysa t�r takma ad�nda yeni t�r�n ad� ve geri kalan 
tan�m bir e�ittir i�areti ile ayr�lm��t�r.

���nc� olarak, "typedef" ad�, yeni bir t�r�n tan�mland���n� d���nd�rse de, bu do�ru de�ildir. Bir typedef sadece bir takma ad'd�r.

*** BEST -> Type aliases � typedef e tercih etmek en iyisidir. 

Terminoloji

C++ standard�, hem typedef'lerin hem de t�r takma adlar�n�n adlar� i�in "typedef adlar� ( Typedef names )" terimini kullan�r.

T�r takma adlar�n� ne zaman kullanmal�y�z?
------------------------------------------
---> Platform-independent kodlama i�in t�r takma adlar� kullanmak

T�r takma adlar�n�n temel kullan�mlar�ndan biri, platforma �zg� ayr�nt�lar� gizlemektir. Baz� platformlarda bir int 2 bayt iken, di�erlerinde 4 baytt�r.
Bu nedenle, platform ba��ms�z kod yazarken int'i 2 bayttan fazla bilgi depolamak potansiyel olarak tehlikeli olabilir.

char, short, int ve long'un boyutu hakk�nda hi�bir bilgi vermemesi nedeniyle, �apraz platformlu programlar�n, t�r�n boyutunu bit cinsinden i�eren 
takma adlar� tan�mlamak i�in t�r takma adlar�n� kullanmas� olduk�a yayg�nd�r. �rne�in, int8_t bir 8-bit i�aretsiz tamsay�y�, int16_t bir 16-bit
i�aretsiz tamsay�y� ve int32_t bir 32-bit i�aretsiz tamsay�y� tan�mlar. Bu �ekilde t�r takma adlar� kullanmak, hatalar� �nlemeye yard�mc� olur ve
de�i�kenin boyutuyla ilgili hangi t�r varsay�mlar�n yap�ld���n� daha net hale getirir.

Bu t�r takma adlar�n�n her birinin do�ru boyutta bir t�rle ��z�lmesini sa�lamak i�in, genellikle bu t�r takma adlar� �ni�lemci y�nergeleri ile birlikte 
kullan�l�r:

                        #ifdef INT_2_BYTES
                        using int8_t = char;
                        using int16_t = int;
                        using int32_t = long;
                        #else
                        using int8_t = char;
                        using int16_t = short;
                        using int32_t = int;
                        #endif

Makinelerde tamsay�lar yaln�zca 2 bayt oldu�unda, INT_2_BYTES #define edilebilir (derleyici/�n i�lemci ayar� olarak), ve program �stteki t�r takma 
adlar� seti ile derlenir. Tamsay�lar�n 4 bayt oldu�u makinelerde, INT_2_BYTES'in tan�ms�z b�rak�lmas�, alttaki t�r takma adlar� setinin kullan�lmas�na
neden olacakt�r. Bu �ekilde, INT_2_BYTES do�ru bir �ekilde #define edildi�i s�rece, int8_t 1 bayt tamsay�s�na, int16_t 2 bayt tamsay�s�na ve int32_t 4
bayt tamsay�s�na ��z�mlenecektir (program�n derlendi�i makine i�in uygun olan char, short, int ve long kombinasyonunu kullanarak).

Sabit geni�likte tamsay� t�rleri (std::int16_t ve std::uint32_t gibi) ve size_t t�r� (her ikisi de 4.6 dersinde ele al�nan Sabit Geni�likte Tamsay�lar
ve size_t) asl�nda �e�itli temel t�rlere y�nlendiren t�r takma adlar�d�r.

Bu ayn� zamanda, bir 8-bit sabit geni�likli tamsay�y� std::cout kullanarak yazd�rd���n�zda neden muhtemelen bir karakter de�eri elde etti�inizi a��klar. �rne�in:

                        #include <cstdint> // sabit geni�likte tamsay�lar i�in
                        #include <iostream>

                        int main()
                        {
                            std::int8_t x{ 97 }; // int8_t genellikle signed char i�in bir t�r takma ad�d�r
                            std::cout << x << '\n';

                            return 0;
                        }
                ��kt� : a

��nk� std::int8_t genellikle signed char i�in bir t�r takma ad�d�r, de�i�ken x b�y�k olas�l�kla signed char olarak tan�mlanacakt�r. Ve char t�rleri,
de�erlerini tamsay� de�erleri olarak de�il, ASCII karakterleri olarak yazd�r�r.

---> Karma��k t�rleri daha okunabilir hale getirmek i�in t�r takma adlar�n� kullanmak

�imdiye kadar sadece basit veri tipleriyle u�ra�t�k, ancak geli�mi� C++'ta, tipler karma��k ve klavyenizden manuel olarak girmesi uzun olabilir.
�rne�in, bir fonksiyonu ve de�i�keni �u �ekilde tan�mlanm�� g�rebilirsiniz:

                        #include <string> // for std::string
                        #include <vector> // for std::vector
                        #include <utility> // for std::pair

                        bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
                        {
                            // some code here
                            return false;
                        }

                        int main()
                        {
                             std::vector<std::pair<std::string, int>> pairlist;

                             return 0;
                        }

std::vector<std::pair<std::string, int>> t�r�n� her kullanman�z gerekti�inde yazmak zahmetli ve yaz�m
hatas� yapma olas�l��� y�ksektir. Bir t�r takma ad� kullanmak �ok daha kolayd�r:

                        #include <string> // std::string i�in
                        #include <vector> // std::vector i�in
                        #include <utility> // std::pair i�in

                        using VectPairSI = std::vector<std::pair<std::string, int>>; // VectPairSI'� bu karma��k t�r i�in bir takma ad yap

                        bool hasDuplicates(VectPairSI pairlist) // VectPairSI'� bir fonksiyon parametresinde kullan
                        {
                            // burada baz� kodlar
                            return false;
                        }

                        int main()
                        {
                             VectPairSI pairlist; // VectPairSI t�r�nde bir de�i�ken olu�tur

                             return 0;
                        }

�ok daha iyi! �imdi std::vector<std::pair<std::string, int>> yerine sadece VectPairSI yazmam�z gerekiyor.

E�er hen�z std::vector, std::pair veya t�m bu ��lg�n a��l� parantezleri bilmiyorsan�z endi�elenmeyin. Burada ger�ekten anlaman�z gereken tek �ey, 
t�r takma adlar�n�n karma��k t�rleri alman�za ve onlara daha basit bir isim vermenize olanak tan�d���d�r, bu da kodunuzu daha okunabilir hale getirir
ve yazma i�leminden tasarruf sa�lar.

Bu muhtemelen t�r takma adlar�n�n en iyi kullan�m�d�r.

---> Bir de�erin anlam�n� belgelemek i�in t�r takma adlar� kullanmak
T�r takma adlar�, kod belgeleri ve anlama katk� sa�lamak i�in de yard�mc� olabilir.

De�i�kenlerle, de�i�kenin tan�mlay�c�s�, de�i�kenin amac�n� belgelemeye yard�mc� olur. Ancak bir fonksiyonun d�n�� de�eri durumunu d���nelim. char,
int, long, double ve bool gibi veri tipleri, bir fonksiyonun ne t�r bir de�er d�nd�rd���n� belirtir, ancak daha s�k olarak bir d�n�� de�erinin anlam�n� 
bilmek istiyoruz.

�rne�in, a�a��daki fonksiyonu d���n�n:

                        int gradeTest();    

D�n�� de�erinin bir tamsay� oldu�unu g�rebiliriz, ancak bu tamsay� ne anlama geliyor? Bir harf notu mu? Ka� sorunun yanl�� oldu�u mu? ��rencinin
kimlik numaras� m�? Bir hata kodu mu? Kim bilir! int t�r�ndeki d�n�� t�r� bize pek �ok �ey s�ylemez. �ansl�ysak, fonksiyon i�in bir yerlerde belgeleme
bulunabilir. �anss�zsak, kodu okumak ve amac� ��karmak zorunda kalabiliriz.

�imdi bir t�r takma ad� kullanarak e�de�er bir versiyon yapal�m:

                        using TestScore = int;
                        TestScore gradeTest();

TestScore'un d�n�� t�r�, fonksiyonun bir test skorunu temsil eden bir t�r� d�nd�rd���n� biraz daha a��k hale getirir.

Deneyimimize g�re, yaln�zca tek bir i�levin d�n�� t�r�n� belgelemek i�in bir t�r takma ad� olu�turmak (onun yerine bir yorum kullan�n) de�mez. Ancak
birden fazla i�levin b�yle bir t�r� ge�mesi veya d�nd�rmesi durumunda, bir t�r takma ad� olu�turmak faydal� olabilir.

---> T�r takma adlar�n� kullanarak kod bak�m�n� kolayla�t�rma

T�r takma adlar� ayr�ca bir nesnenin temel t�r�n� de�i�tirmenizi sa�lar ve bunu yaparken �ok say�da sabit t�r� g�ncelleme zorunlulu�undan kurtar�r.
�rne�in, bir ��renci kimlik numaras�n� tutmak i�in bir short kullan�yorsan�z, ancak daha sonra bunun yerine bir long'a ihtiyac�n�z oldu�una karar 
verirseniz, �ok say�da kodu g�zden ge�irip short'u long ile de�i�tirmeniz gerekebilir. short t�r�ndeki hangi nesnelerin kimlik numaralar�n� tutmak 
i�in kullan�ld���n� ve hangilerinin ba�ka ama�lar i�in kullan�ld���n� belirlemek muhtemelen zor olacakt�r.

Ancak, t�r takma adlar� kullan�yorsan�z, t�rleri g�ncellemek, yaln�zca t�r takma ad�n� g�ncellemek kadar basit hale gelir (�rne�in, StudentId = short;
kullan�yorsan�z, StudentId = long; olarak g�ncellemek).

Bu g�zel bir avantaj gibi g�r�nse de, bir t�r de�i�tirildi�inde dikkatli olunmal�d�r, ��nk� program�n davran��� da de�i�ebilir. Bu �zellikle bir t�r 
takma ad�n�n t�r ailesinde farkl� bir t�r (�rne�in, bir tamsay�dan bir kayan nokta de�erine veya bir i�aretsizden bir i�aretli de�ere) de�i�tirilirse 
ge�erlidir! Yeni t�r�n kar��la�t�rma veya tamsay�/kayan nokta b�lme sorunlar� veya eski t�r�n olmayan di�er sorunlar� olabilir. Mevcut bir t�r� ba�ka 
bir t�re de�i�tiriyorsan�z, kodunuz kapsaml� bir �ekilde yeniden test edilmelidir.


Dezavantajlar ve Sonu�
**********************

T�r takma adlar� baz� avantajlar sunsa da, ayn� zamanda kodunuza anla��lmas� gereken ba�ka bir tan�mlay�c� ekler. E�er bu, okunabilirlik veya anlama
a��s�ndan bir faydayla dengelemezse, t�r takma ad� daha �ok zarar verir.

K�t� bir �ekilde kullan�lan bir t�r takma ad�, tan�d�k bir t�r� (�rne�in, std::string gibi) �zel bir ismin arkas�na gizleyebilir ve bunun ara�t�r�lmas� 
gerekebilir. Baz� durumlarda (gelecekte ele alaca��m�z ak�ll� i�aret�iler gibi), t�r bilgisini gizlemek, t�r�n nas�l �al��mas� gerekti�ini anlama 
konusunda da zararl� olabilir.

Bu nedenle, t�r takma adlar�, kodun okunabilirli�i veya bak�m� a��s�ndan a��k bir faydas� oldu�u durumlarda kullan�lmal�d�r. Bu konu, bir sanattan 
�ok bir bilimdir. T�r takma adlar�, kodunuzun bir�ok yerinde kullan�ld���nda daha etkilidir, daha az yerde de�il.

*** BEST -> T�r takma adlar�n�, kodun okunabilirli�ini veya bak�m�n� net bir �ekilde art�rd�klar�nda �l��l� bir �ekilde kullan�n.

10.8 � auto Anahtar Kelimesi Kullanarak Nesneler ��in T�r ��kar�m�
------------------------------------------------------------------

Bu basit de�i�ken tan�m�nda gizli bir tekrarl�l�k bulunmaktad�r:
                            double d{ 5.0 };
��nk� C++, g��l� t�rleme (strongly-typed) bir dil oldu�u i�in, t�m nesneler i�in a��k bir t�r sa�lamak zorunday�z. Bu nedenle, de�i�ken d'nin double 
t�r�nde oldu�unu belirttik.

Ancak, d'yi ba�latmak i�in kullan�lan 5.0 rakam� da t�r� double olan bir literalden (anlam� bi�imsel olarak belirlenen) dolayl� olarak tespit edilir.

De�i�kenin ve ba�lat�c�s�n�n ayn� t�re sahip olmas�n� istedi�imiz durumlarda, ayn� t�r bilgisini etkili bir �ekilde iki kez sa�l�yoruz.

Ba�lat�lan De�i�kenler ��in T�r ��kar�m�
----------------------------------------
T�r ��kar�m�( Type deduction ) (bazen t�r ��kar�m� ( type inference ) olarak da adland�r�l�r), derleyicinin bir nesnenin t�r�n� nesnenin ba�lat�c�s�ndan
��karmas�na izin veren bir �zelliktir. T�r ��kar�m�n� kullanmak i�in, "auto" anahtar kelimesi de�i�kenin t�r�n�n yerine kullan�l�r:

                            int main()
                            {
                                auto d{ 5.0 };   // 5.0 bir double literald�r, bu nedenle d double t�r�nde olacakt�r
                                auto i{ 1 + 2 }; // 1 + 2 bir int de�erini de�erlendirdi�i i�in i int t�r�nde olacakt�r
                                auto x{ i };     // i bir int oldu�u i�in x de int t�r�nde olacakt�r

                                return 0;
                            }


�lk durumda, ��nk� 5.0 bir double literald�r, derleyici de�i�ken d'nin double t�r�nde olmas� gerekti�ini ��karacakt�r. �kinci durumda, 1 + 2 ifadesi
bir int sonucu verdi�i i�in de�i�ken i int t�r�nde olacakt�r. ���nc� durumda, i �nceden int t�r�nde ��kar�lm��t�, bu nedenle x'in de int t�r�nde
��kar�lmas� gerekecektir.

Fonksiyon �a�r�lar� ge�erli ifadeler oldu�u i�in, ba�lat�c�m�z bir fonksiyon �a�r�s� oldu�unda bile t�r ��kar�m�n� kullanabiliriz:

                            int add(int x, int y)
                            {
                                return x + y;
                            }

                            int main()
                            {
                                auto sum{ add(5, 6) }; // add() bir int d�nd�rd��� i�in sum'un t�r� int olarak ��kar�lacakt�r
                                return 0;
                            }

add() fonksiyonu bir int de�eri d�nd�rd��� i�in derleyici de�i�ken sum'un int t�r�nde olmas� gerekti�ini ��karacakt�r.

T�r ��kar�m�, ba�lat�c�s� olmayan veya bo� ba�lat�c�lara sahip nesneler i�in �al��maz. Bu nedenle, a�a��daki ge�erli de�ildir:

                            int main()
                            {
                                auto x;   // Derleyici x'in t�r�n� ��karamaz
                                auto y{ }; // Derleyici y'nin t�r�n� ��karamaz

                                return 0;
                            }

Temel veri tipleri i�in t�r ��kar�m�n� kullanmak yaln�zca birka� (e�er hi�) tu� vuru�u tasarrufu sa�lasa da, gelecekteki derslerde t�rlerin 
karma��k ve uzun oldu�u �rnekleri g�rece�iz (ve baz� durumlarda, anlamak zor olabilir). Bu durumlarda, auto kullanmak �ok yaz�m (ve yaz�m hatalar�)
tasarrufu sa�layabilir.

T�r ��kar�m�, const / constexpr nitelendiricilerini d���r�r.
------------------------------------------------------------

�o�u durumda, t�r ��kar�m� const veya constexpr nitelendiricisini ��kar�r. �rne�in:

                            int main()
                            {
                                const int x { 5 }; // x'in t�r� const int
                                auto y { x };      // y'nin t�r� int olacakt�r (const d���r�ld�)

                                return 0;
                            }

Yukar�daki �rnekte, x'in t�r� const int'dir, ancak x'i ba�lat�c� olarak kullanarak de�i�ken y i�in bir t�r ��kar�ld���nda, t�r ��kar�m� t�r� const 
int yerine int olarak ��kar�r.

E�er bir ��kar�lan t�r�n const veya constexpr olmas�n� istiyorsan�z, const veya constexpr anahtar kelimesini auto anahtar�yla birlikte kullanmal�s�n�z:

                            int main()
                            {
                                const int x { 5 };         // x'in t�r� const int (derleme zaman�nda const)
                                auto y { x };              // y'nin t�r� int olacakt�r (const d���r�ld�)

                                constexpr auto z { x };    // z'nin t�r� constexpr int olacakt�r (constexpr tekrar uyguland�)

                                return 0;
                            }

Bu �rnekte x'ten t�retilen t�r int olacakt�r (const b�rak�lm��t�r), ancak z de�i�keninin tan�m� s�ras�nda constexpr niteleyicisini yeniden ekledi�imiz 
i�in z de�i�keni bir constexpr int olacakt�r.

String literals i�in Type deduction
-----------------------------------

Tarihsel nedenlerden dolay�, C++ dilinde string literallerinin tuhaf bir t�r� vard�r. Bu nedenle, a�a��daki �rne�in beklenildi�i gibi �al��mas� 
muhtemel de�ildir:

                        auto s { "Hello, World!" }; // s'nin t�r� const char* olacak, std::string de�il

E�er bir string literalinden t�retilen tipin std::string veya std::string_view olmas�n� istiyorsan�z, s veya sv literal �neklerini kullanman�z gerekecek
(5.4 dersinde ele al�nm��t�r):

                        #include <string>
                        #include <string_view>

                        int main()
                        {
                            using namespace std::literals; // s ve sv �neklerine eri�im i�in en kolay yol

                            auto s1 { "goo"s };  // "goo"s bir std::string literal oldu�u i�in s1, std::string olarak ��kar�lacakt�r
                            auto s2 { "moo"sv }; // "moo"sv bir std::string_view literal oldu�u i�in s2, std::string_view olarak ��kar�lacakt�r

                            return 0;
                        }
T�r deduction avantajlar� ve dezavantajlar�
-------------------------------------------
T�r deduction yaln�zca kullan��l� olmakla kalmaz, ayn� zamanda bir dizi ba�ka faydaya da sahiptir.

�lk olarak, s�ral� sat�rlarda iki veya daha fazla de�i�ken tan�mlan�rsa de�i�kenlerin adlar� s�ralanacak ve okunabilirli�in artmas�na yard�mc� olacakt�r:

                        // daha zor okunabilir
                        int a { 5 };
                        double b { 6.7 };

                        // daha kolay okunabilir
                        auto c { 5 };
                        auto d { 6.7 };

�kinci olarak, t�r ��kar�m� yaln�zca ba�lat�c�ya sahip olan de�i�kenlerde �al���r; bu nedenle, t�r ��kar�m�n� kullanma al��kanl���n�z varsa, istenmeyen 
durumlarda ba�lat�lmam�� de�i�kenleri �nlemeye yard�mc� olabilir.

                        int x; // ups, x'in ba�lat�lmas�n� unuttuk, ancak derleyici uyar� vermeyebilir
                        auto y; // derleyici, y i�in bir t�r ��kar�lamad���ndan hata verecek

���nc� olarak, istenmeyen performans etkileyen d�n���mlerin olmayaca��na garanti verilir.

                        std::string_view getString();   // std::string_view d�nd�ren bir fonksiyon

                        std::string s1{ getString() };  // k�t�: std::string_view'dan std::string'e pahal� d�n���m (bu istemedi�iniz varsay�l�rsa)
                        auto s2{ getString() };         // iyi: d�n���m gerekmiyor

T�r ��kar�m�n�n birka� dezavantaj� vard�r.

�lk olarak, t�r ��kar�m�, bir nesnenin t�r bilgisini kod i�inde gizler. �yi bir IDE'nin size ��kar�lan t�r� g�sterebilmesi gerekse de (�rne�in,
bir de�i�kenin �zerine gelindi�inde), t�r ��kar�m� kullan�rken t�rle ilgili hatalar yapmak biraz daha kolayd�r.

�rne�in:
                        auto y { 5 }; // oops, we wanted a double here but we accidentally provided an int literal

Yukar�daki kod �rne�inde, e�er y'yi a��k�a bir double t�r� olarak belirtmi� olsayd�k, y bir int literali ba�lat�c�s� versek bile yine double olacakt�. 
Ancak t�r ��kar�m� kullan�ld���nda, y'nin t�r� int olarak ��kar�lacakt�r.

��te ba�ka bir �rnek:

                        #include <iostream>

                        int main()
                        {
                                auto x { 3 };
                                auto y { 2 };

                                std::cout << x / y << '\n'; // hata, burada ondal�k say� b�lme istemi�tik

                                return 0;
                        }
Bu �rnekte, bir tam say� b�lme yerine ondal�k say� b�lmesi ald���m�z� anlamak daha az a��kt�r.

�kinci olarak, ba�lat�c�n�n t�r� de�i�ti�inde, t�r ��kar�m� kullanarak bir de�i�kenin t�r� de de�i�ecektir, belki de beklenmedik bir �ekilde.
A�a��daki �rne�i d���n�n:

                        auto sum { add(5, 6) + gravity };

E�er `add` fonksiyonunun d�n�� t�r� int'ten double'a de�i�irse veya gravity'nin t�r� int'ten double'a de�i�irse, sum de�i�keninin t�r� de int'ten 
double'a de�i�ecektir.

Genel olarak, modern g�r�� genellikle t�r ��kar�m�n�n nesneler i�in genellikle g�venli oldu�u ve bunun kullan�lmas�n�n kodunuzu daha okunabilir 
hale getirebilece�i y�n�ndedir. T�r bilgisini �nemsizle�tirerek kod mant���n� daha belirgin hale getirebilirsiniz.

*** BEST -> De�i�kenleriniz i�in t�r ��kar�m�n� kullan�n, ancak belirli bir t�re ba�l� kalmaya ihtiyac�n�z varsa belirli bir t�r� a��k�a belirtin.

!! Gelecekteki derslerde, t�r bilgisini g�stermek, bir kavram� veya �rne�i anlamak i�in yard�mc� oldu�unda, a��k t�rleri kullanmaya devam edece�iz.

10.9 � Fonksiyonlarda T�r ��kar�m� - Type deduction for functions
-----------------------------------------------------------------
Bir �rne�i inceleyerek ba�layal�m:
 
                        int add(int x, int y)
                        {
                            return x + y;
                        }


Bu fonksiyon derlendi�inde, derleyici x + y'nin bir int de�erini de�erlendirdi�ini belirler, ard�ndan d�nen de�erin t�r�n�n, fonksiyonun beyan edilen
d�n�� t�r�yle e�le�ti�inden veya d�n�� de�eri t�r�n�n beyan edilen d�n�� t�r�ne d�n��t�r�lebilece�inden emin olur.

��nk� derleyici zaten d�n�� t�r�n� return ifadesinden ��karmak zorunda oldu�undan, C++14'te auto anahtar kelimesi, fonksiyon d�n�� t�r� ��kar�m� yapmak
�zere geni�letildi. Bu, auto anahtar kelimesini fonksiyonun d�n�� t�r� yerine kullanarak �al���r.

�rne�in:
                        auto add(int x, int y)
                        {
                            return x + y;
                        }


��nk� return ifadesi bir int de�eri d�nd�r�yor, derleyici bu fonksiyonun d�n�� t�r�n�n int oldu�unu ��karacakt�r.

Auto d�n�� t�r� kullan�l�rken, fonksiyon i�indeki t�m return ifadelerinin ayn� t�rde de�er d�nd�rmesi gerekir, aksi takdirde bir hata olu�acakt�r. 
�rne�in:

                        auto someFcn(bool b)
                        {
                            if (b)
                                return 5; // return type int
                            else
                                return 6.7; // return type double
                        }

Yukar�daki fonksiyonda, iki return ifadesi farkl� t�rlerde de�er d�nd�rd���nden dolay� derleyici hata verecektir.

E�er bu t�r bir durum bir nedenle isteniyorsa, ya fonksiyonunuz i�in a��k�a bir d�n�� t�r� belirtirsiniz (bu durumda derleyici, uyanmayan herhangi 
bir return ifadesini a��k�a belirtilen d�n�� t�r�ne �rt�k olarak d�n��t�rmeye �al��acakt�r), ya da t�m return ifadelerinizi a��k�a ayn� t�re 
d�n��t�r�rs�n�z. Yukar�daki �rnekte, ikinci se�enek 5'i 5.0'a de�i�tirerek ger�ekle�tirilebilir, ancak static_cast, literat olmayan t�rler i�in de 
kullan�labilir.

Auto d�n�� t�r� kullanan fonksiyonlar�n b�y�k bir dezavantaj�, bu t�r fonksiyonlar�n kullan�lmadan �nce tamamen tan�mlanm�� olmalar� gereklili�idir 
(bir ileri bildirim yeterli de�ildir). �rne�in:

                        #include <iostream>

                        auto foo();

                        int main()
                        {
                            std::cout << foo() << '\n'; // Bu noktada derleyici sadece bir ileri y�nl� tan�mlama g�rmekte

                            return 0;
                        }

                        auto foo()
                        {
                            return 5;
                        }
Yazar�n bilgisayar�nda, bu �u derleme hatas�n� verir:
                        error C3779: 'foo': a function that returns 'auto' cannot be used before it is defined.

Bu mant�kl�: bir ileri bildirim, derleyicinin fonksiyonun d�n�� t�r�n� ��karmak i�in yeterli bilgiye sahip olmamas� anlam�na gelir. Bu, normalde 
auto d�nd�ren fonksiyonlar�n genellikle tan�mland�klar� dosya i�indeki i�eriden �a�r�labilir oldu�u anlam�na gelir.

Nesneler i�in t�r ��kar�m� kullan�l�rken, ba�lat�c� her zaman ayn� ifadenin bir par�as� olarak bulunur, bu nedenle hangi t�r�n ��kar�laca��n� 
belirlemek genellikle a��r� y�k olu�turmaz. Fonksiyonlar i�in durum b�yle de�ildir - bir fonksiyonun prototipine bak�ld���nda, fonksiyonun hangi
t�r� d�nd�rd���n� belirlemek i�in yard�mc� olacak bir ba�lam yoktur. �yi bir programlama IDE'si, fonksiyonun ��kar�lan t�r�n� a��k�a g�stermelidir,
ancak buna eri�im olmad���nda, bir kullan�c�n�n ger�ekten fonksiyon g�vdesine inmesi gerekebilir. Hatalar yapma olas�l��� daha y�ksektir. Ve bu t�r
fonksiyonlar�n ileri bildirimde bulunamamas�, �oklu dosya i�eren programlarda kullan�labilirliklerini s�n�rlar.

*** BEST -> Normal fonksiyonlar i�in otomatik t�r ��kar�m� yerine a��k d�n�� t�rlerini tercih edin.

Geriye d�n�k d�n�� t�r� s�zdizimi
---------------------------------

auto anahtar kelimesi, geriye d�n�k bir s�zdizimi kullanarak fonksiyonlar� bildirmek i�in de kullan�labilir, burada d�n�� t�r� geri kalan
fonksiyon prototipi sonras�nda belirtilir.

A�a��daki fonksiyonu d���n�n:

                        int add(int x, int y)
                        {
                            return (x + y);
                        }
Geriye d�n�k s�zdizimi kullanarak, bu e�de�er olarak �u �ekilde yaz�labilir:

                        auto add(int x, int y) -> int
                        {
                          return (x + y);
                        }

Bu durumda, auto t�r ��kar�m� ger�ekle�tirmiyor; sadece geriye d�n�k bir d�n�� t�r� kullanma s�zdiziminin bir par�as�d�r.

Bunu neden kullanmak istersiniz?

Bir g�zel yan� da t�m fonksiyon adlar�n�z�n hizalanmas�n� sa�lamas�d�r:

                        auto add(int x, int y) -> int;
                        auto divide(double x, double y) -> double;
                        auto printSomething() -> void;
                        auto generateSubstring(const std::string &s, int start, int len) -> std::string;

Geriye d�n�k d�n�� t�r� s�zdizimi, C++'�n baz� geli�mi� �zellikleri i�in de gereklidir, �rne�in lambda ifadeleri (bu, 20.6
dersinde kapsayaca��m�z anonim fonksiyonlara bir giri�tir).

�u an i�in, geriye d�n�k d�n�� t�r� s�zdizimine ihtiya� duyulan durumlar d���nda, geleneksel fonksiyon d�n�� t�r� s�zdizimini 
kullanmaya devam etmenizi �neririz.

T�r ��kar�m� fonksiyon parametre t�rleri i�in kullan�lamaz
----------------------------------------------------------
T�r ��kar�m�n� ��renen bir�ok yeni programc�, ��yle bir �ey denemeye �al���r:

                        #include <iostream>

                        void addAndPrint(auto x, auto y)
                        {
                            std::cout << x + y << '\n';
                        }

                        int main()
                        {
                            addAndPrint(2, 3); // Durum 1: addAndPrint fonksiyonunu int parametreleriyle �a��rma
                            addAndPrint(4.5, 6.7); // Durum 2: addAndPrint fonksiyonunu double parametreleriyle �a��rma

                            return 0;
                        }


Maalesef, t�r ��kar�m� fonksiyon parametreleri i�in �al��maz ve C++20'den �nce yukar�daki program derlenmez (auto t�r�ne sahip olamayan bir hata
al�rs�n�z).

C++20'de, auto anahtar kelimesi yukar�daki program�n derlenmesine ve do�ru �al��mas�na izin vermek �zere geni�letildi - ancak bu durumda auto, t�r 
��kar�m�n� �a��rm�yor. Bunun yerine, asl�nda bu t�r durumlar� ele almak �zere tasarlanm�� bir �zellik olan "fonksiyon �ablonlar�"n� tetikliyor.
*/