
#include <iostream>

int main()
{
    return 0;
}
/*
                                                    Implicit Type D�n���m�

Tip d�n���m�ne giri�
--------------------
Bir nesnenin de�eri, bir dizi bit olarak saklan�r ve nesnenin veri t�r�, derleyiciye bu bitlerin anlaml� de�erlere nas�l �evrilece�ini belirtir. Farkl�
veri tipleri, ayn� say�y� farkl� �ekillerde temsil edebilir. �rne�in, tam say� de�eri 3, ikili olarak 0000 0000 0000 0000 0000 0000 0000 0011 olarak 
saklanabilirken, kayan noktal� say� de�eri 3.0 ikili olarak 0100 0000 0100 0000 0000 0000 0000 0000 olarak saklanabilir.

* Bu �ekilde bir �ey yapt���m�zda neler olur?

                    float f{ 3 }; // tam say� 3 ile kayan noktal� de�i�keni ba�lat

Bu durumda, derleyici sadece int de�eri 3'� float de�i�keni f i�in ayr�lan belle�e kopyalayamaz. Bunun yerine, tam say� de�eri 3'� kar��l�k gelen
kayan noktal� de�er 3.0'a d�n��t�rmesi gerekir ki bu de�er daha sonra f i�in ayr�lan bellekte depolanabilir.

Bir de�eri farkl� bir t�rden ba�ka bir t�re d�n��t�rme s�recine "d�n���m" denir.

D�n���mler, d�n��t�r�len de�eri veya t�r� de�i�tirmez. Bunun yerine, d�n���m�n bir sonucu olarak istenen t�rde yeni bir de�er olu�turulur.

T�r d�n���mleri iki �ekilde �a�r�labilir: ya dolayl� olarak (derleyici taraf�ndan ihtiya� duyuldu�unda) ya da a��k�a (programc� taraf�ndan istendi�inde)
Bu derste dolayl� t�r d�n���m�n� ele alaca��z ve �n�m�zdeki 10.6 dersinde a��k t�r d�n���mlerini (casting) ve static_cast'� i�leyece�iz.

Dolayl� t�r d�n���m� (ayn� zamanda otomatik t�r d�n���m� veya zorlamak olarak da adland�r�l�r), bir veri t�r� istendi�inde ancak farkl� bir veri t�r� 
sa�land���nda derleyici taraf�ndan otomatik olarak ger�ekle�tirilir. C++'taki t�r d�n���mlerinin b�y�k �o�unlu�u dolayl� t�r d�n���mleridir. �rne�in, 
dolayl� t�r d�n���m� a�a��daki durumlar�n hepsinde ger�ekle�ir:

Bir de�i�keni farkl� bir veri t�r�ndeki bir de�erle ba�latmak (veya bir de�er atamak) istendi�inde:

                    double d{ 3 }; // int de�eri 3, double t�r�ne dolayl� olarak d�n��t�r�l�yor
                    d = 6; // int de�eri 6, double t�r�ne dolayl� olarak d�n��t�r�l�yor

D�n�� de�erinin t�r�, fonksiyonun ilan edilmi� d�n�� t�r�nden farkl� oldu�unda:

                    float doSomething()
                    {
                        return 3.0; // double de�eri 3.0, float t�r�ne dolayl� olarak d�n��t�r�l�yor
                    }

Farkl� t�rlerdeki operandlar� kullan�rken belirli ikili operat�rler ile:

                    double division{ 4.0 / 3 }; // int de�eri 3, double t�r�ne dolayl� olarak d�n��t�r�l�yor

                    if (5) // int de�eri 5, bool t�r�ne dolayl� olarak d�n��t�r�l�yor
                    {
                    }

Farkl� t�rlerdeki operandlar� kullan�rken belirli ikili operat�rler ile:

                    void doSomething(long l)
                    {
                    }

                    doSomething(3); // int de�eri 3, long t�r�ne dolayl� olarak d�n��t�r�l�yor

T�r D�n���m� �a�r�ld���nda: Ne Olur ? 
-------------------------------------

Bir t�r d�n���m� �a�r�ld���nda (hem dolayl� olarak hem de a��k�a), derleyici mevcut t�rden istenen t�re de�eri d�n��t�r�p d�n��t�remeyece�ini
belirleyecektir. E�er ge�erli bir d�n���m bulunabilirse, derleyici istenen t�rde yeni bir de�er �retecektir. Unutulmamal�d�r ki t�r d�n���mleri, 
d�n��t�r�len de�erin de�erini veya t�r�n� de�i�tirmez.

E�er derleyici uygun bir d�n���m bulamazsa, derleme hatas� ile ba�ar�s�z olacakt�r. T�r d�n���mleri bir�ok nedenden dolay� ba�ar�s�z olabilir. 
�rne�in, derleyici bir de�eri orijinal t�r ile istenen t�r aras�nda nas�l d�n��t�rece�ini bilemeyebilir. Di�er durumlarda, ifadeler belirli
t�rlerdeki d�n���mleri yasaklayabilir. �rne�in:

                    int x { 3.5 }; // Ayra�la ba�latma, veri kayb�na neden olan d�n���mleri engeller

Ayr�ca, derleyici bir de�eri ba�ka bir t�re d�n��t�rebilece�i birka� olas� d�n���m aras�ndan hangisinin en iyi oldu�unu belirleyemeyebilir.
Bunun �rneklerini 10.12 dersinde g�rece�iz - Fonksiyon a��r� y�kleme ( overloading ) ��z�mleme ve belirsiz e�le�meler.

Peki, derleyici bir de�eri bir t�rden ba�ka bir t�re d�n��t�rebilip d�n��t�remeyece�ini nas�l belirler?

Standart D�n���mler
-------------------

C++ dil standard�, farkl� temel t�rlerin (ve baz� durumlarda bile�ik t�rlerin) di�er t�rlere nas�l d�n��t�r�lebilece�ini tan�mlar. Bu d�n���m
kurallar�na standart d�n���mler denir.

Standart d�n���mler genel olarak 4 kategoriye ayr�labilir, her biri farkl� t�rlerde d�n���mleri kapsar:

* - Say�sal y�kseltmeler (10.2 dersinde ele al�nm��t�r - Kayan nokta ve tamsay� y�kseltmeleri)
* - Say�sal d�n���mler (10.3 dersinde ele al�nm��t�r - Say�sal d�n���mler)
* - Aritmetik d�n���mler (10.5 dersinde ele al�nm��t�r - Aritmetik d�n���mler)
* - Di�er d�n���mler (bu, �e�itli i�aret�i ve referans d�n���mlerini i�erir)

Bir t�r d�n���m� gerekti�inde, derleyici, de�eri istenen t�re d�n��t�rmek i�in kullanabilece�i standart d�n���mleri kontrol eder. Derleyici, 
d�n���m s�recinde s�f�r, bir veya daha fazla standart d�n���m� uygulayabilir.

Ayr�ca...

S�f�r d�n���ml� bir t�r d�n���m� nas�l ger�ekle�ir? �rne�in, int ve long t�rlerinin ayn� boyuta ve aral��a sahip oldu�u mimarilerde, her iki 
t�r�n de�erlerini temsil etmek i�in ayn� bit dizisi kullan�l�r. Bu nedenle, bu t�rler aras�nda bir de�eri d�n��t�rmek i�in ger�ek bir d�n���m 
gerekmez - de�er basit�e kopyalanabilir.

T�r d�n���mlerinin nas�l �al��t���n� a��klayan tam kural seti hem uzun hem de karma��kt�r ve �o�u zaman t�r d�n���mleri "sadece �al���r". Bir
sonraki derste, t�r d�n���mleri hakk�nda bilmeniz gereken en �nemli konular� ele alaca��z. Nadir durumlar i�in daha ayr�nt�l� bilgi gerekiyorsa,
tam kurallar, dolayl� d�n���mler i�in teknik referans belgelerinde ayr�nt�l� olarak a��klanm��t�r.

Hadi ba�layal�m!
*/
/*
10.2 � Standart D�n���mler 1- Kayan nokta ve tamsay� y�kseltmeleri
------------------------------------------------------------------

4.3 dersinde, C++'�n her temel t�r i�in minimum boyut garantileri oldu�unu belirttik. Ancak, bu t�rlerin ger�ek boyutu derleyici ve mimariye ba�l�
olarak de�i�ebilir.  Bu de�i�kenlik, int ve double veri t�rlerinin performans� maksimize edecek �ekilde bir mimariye g�re boyutland�r�labilmesine
izin verilmi�tir. �rne�in, 32-bit bir bilgisayar genellikle bir seferde 32 bit veriyi i�leyebilir. Bu durumlarda, bir int genellikle 32 bit 
geni�li�inde ayarlan�r, ��nk� bu, CPU'nun i�lem yapt��� verinin "do�al" boyutudur (ve muhtemelen en performansl� olan�d�r).

Bir hat�rlatma

Bir veri t�r�n�n kulland��� bit say�s�na geni�lik (width) denir. Daha geni� bir veri t�r�, daha fazla bit kullan�rken, daha dar (narrower) bir veri
t�r� daha az bit kullan�r.

Ancak 32-bit bir CPU'nun bir char gibi 8-bit veya 16-bit bir de�eri de�i�tirmesi gerekti�inde ne olur? Baz� 32-bit i�lemciler (�rne�in, 32-bit x86 
i�lemciler) 8-bit veya 16-bit de�erleri do�rudan i�leyebilir. Ancak, bunu yapmak genellikle 32-bit de�erleri i�lemekten daha yava�t�r! Di�er 32-bit
i�lemciler (�rne�in, 32-bit PowerPC i�lemcileri), yaln�zca 32-bit de�erler �zerinde �al��abilir ve daha dar de�erleri i�lemek i�in ek hilelere ihtiya� 
vard�r.


Say�sal Y�kseltme - Numeric Promotions 
--------------------------------------

C++, geni� bir mimari yelpazesi �zerinde ta��nabilir ve performansl� olacak �ekilde tasarland���ndan, dil tasar�mc�lar� belirli bir CPU'nun, o CPU'nun
do�al veri boyutundan daha dar de�erleri verimli bir �ekilde i�leyebilece�ini varsaymak istememi�tir.

Bu zorlu�u ele almaya yard�mc� olmak i�in, C++, numeric promotions olarak adland�r�lan bir t�r d�n���m kategorisi tan�mlar. Numeric promotion, belirli
daha dar say�sal t�rlerin (�rne�in char) genellikle int veya double gibi daha geni� say�sal t�rlere d�n��t�r�lmesidir ve bu t�rler daha verimli bir
�ekilde i�lenebilir ve ta�ma olas�l��� daha d���kt�r.

T�m numeric promotions de�eri koruyucudur, yani d�n��t�r�len de�er her zaman kaynak de�erine e�it olacakt�r (sadece farkl� bir t�re sahip olacakt�r).
Kaynak t�r�n t�m de�erleri hedef t�rde tam olarak temsil edilebildi�i i�in, de�eri koruyucu d�n���mler "g�venli d�n���mler" olarak adland�r�l�r.

Promotion lar ( Y�kseltmeler ) g�venli oldu�undan, derleyici ihtiya� duydu�unda serbest�e
numeric promotion'� kullanacak ve bunu yaparken bir uyar� ��karmayacakt�r.

* Say�sal y�kseltme ( Numeric Promotion), tekrar� azalt�r.
*---------------------------------------------------------

Say�sal promosyon ayn� zamanda ba�ka bir sorunu da ��zer. Bir int t�r�ndeki bir de�eri yazd�rmak i�in bir i�lev yazmak istedi�inizi d���n�n:

                        #include <iostream>

                        void printInt(int x)
                        {
                            std::cout << x << '\n';
                        }

Bu basit bir ��z�m olabilir, ancak ayn� zamanda short veya char t�r�nde bir de�eri de yazd�rabilmek istersek ne olur? T�r d�n���mleri yoksa, short 
i�in farkl� bir yazd�rma i�levi ve char i�in ba�ka bir i�lev yazmak zorunda kal�rd�k. Ve unsigned char, signed char, unsigned short, wchar_t,
char8_t, char16_t ve char32_t i�in ba�ka bir versiyonu unutmay�n! Bu h�zla y�netilemez hale gelir.

��te burada say�sal y�kseltme devreye giriyor: int ve/veya double parametrelere sahip fonksiyonlar yazabiliriz 
(yukar�daki printInt() fonksiyonu gibi). Ayn� kod daha sonra say�sal olarak promosyon yap�labilen arg�man t�rleri ile �a�r�labilir,
b�ylece fonksiyon parametrelerinin t�rleriyle e�le�ebilir.

Say�sal y�kseltme kategorileri
------------------------------

Say�sal y�kseltme kurallar�, iki alt kategoriye ayr�l�r: tamsay� y�kseltmeleri ve kayan nokta y�kseltmeleri. Sadece bu kategorilerde listelenen
d�n���mler, say�sal y�kseltmeler olarak kabul edilir.

Kayan nokta y�kseltmeleri
-------------------------


Daha kolay olan� ile ba�layal�m.

Kayan nokta promosyon kurallar� kullan�larak, float t�r�ndeki bir de�er double t�r�ndeki bir de�ere d�n��t�r�lebilir.

Bu �u anlama gelir, bir double alan bir fonksiyon yazabiliriz ve ard�ndan bu fonksiyonu hem bir double hem de bir float de�eri ile �a��rabiliriz:

                        #include <iostream>

                        void printDouble(double d)
                        {
                            std::cout << d << '\n';
                        }

                        int main()
                        {
                            printDouble(5.0); // D�n���m gerekmez
                            printDouble(4.0f); // Floattan Doubleye say�sal y�kseltme gerekir. 

                            return 0;
                        }

printDouble() fonksiyonuna yap�lan ikinci �a�r�da, float 4.0f literal� double'a y�kseltme yap�l�r, b�ylece arg�man�n t�r� i�lev parametresinin
t�r�yle e�le�ir.

Tam say� y�kseltmeleri
----------------------

Tam say� y�kseltme kurallar� daha karma��kt�r.

Tam say� y�kseltme kurallar� kullan�larak �u d�n���mler yap�labilir:

*- signed char veya signed short, int'e y�kseltilebilir.
*- unsigned char, char8_t ve unsigned short, int t�r� t�m aral��� tutabiliyorsa int'e, aksi takdirde unsigned int'e y�kseltilebilir.
*- E�er char varsay�lan olarak signed ise, yukar�daki signed char y�kseltme kurallar�n� takip eder. Varsay�lan olarak unsigned ise, yukar�daki 
   unsigned char y�kseltme kurallar�n� takip eder.
*- bool, int'e y�kseltilebilir, false 0 olur ve true 1 olur.

8 bitlik bir byte ve genellikle 4 bayt veya daha b�y�k bir int boyutu varsay�ld���nda (bug�nlerde tipik olan), yukar�daki a��klamalar genellikle bool,
char, signed char, unsigned char, signed short ve unsigned short'un hepsinin int'e y�kseltilmesi anlam�na gelir.

Daha az s�k kullan�lan birka� ba�ka say�sal y�kseltme kural� da bulunmaktad�r. Bunlar 
https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion adresinde bulunabilir.

�o�u durumda, bu bize bir int parametre alan bir fonksiyon yazmam�za ve ard�ndan �e�itli say�sal t�rlerle kullanmam�za izin verir. �rne�in:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        printInt(2);

                        short s{ 3 }; // short literal suffix yok, bu y�zden bunun i�in bir de�i�ken kullanaca��z
                        printInt(s); // short'un int'e say�sal y�kseltilmesi

                        printInt('a'); // char'�n int'e say�sal y�kseltilmesi
                        printInt(true); // bool'un int'e say�sal y�kseltilmesi

                        return 0;
                    }

Burada dikkate de�er iki �ey bulunmaktad�r. �lk olarak, baz� mimarilerde (�rne�in 2 bayt int'lerle) baz� unsigned tamsay� tiplerinin int yerine
unsigned int'e y�kseltilmesi m�mk�nd�r.

�kinci olarak, baz� daha dar unsigned tipler (�rne�in unsigned char), daha b�y�k i�aretli tiplere (�rne�in int) y�kseltilebilir. Bu nedenle, 
integral y�kseltme de�eri korurken, t�r�n i�aretli olup olmama durumunu (signed/unsigned) zorunlu olarak korumaz.

T�m geni�leme d�n���mleri say�sal y�kseltmeler de�ildir
-------------------------------------------------------

Baz� geni�leme t�r d�n���mleri (�rne�in char'dan short'a veya int'ten long'a) C++'da say�sal y�kseltmeler olarak kabul edilmez (bunlar yak�nda ele 
alaca��m�z say�sal d�n���mlerd�r, 10.3 dersi -- Say�sal d�n���mler). Bu, bu t�r d�n���mlerin daha k���k tipleri daha verimli bir �ekilde i�leyebilen 
daha b�y�k tiplere d�n��t�rme amac�na hizmet etmedi�i i�indir.

Ay�r�m genellikle akademiktir. Ancak, belirli durumlarda derleyici, say�sal y�kseltmeleri say�sal d�n���mler �zerinde tercih edebilir. Fonksiyon
a��r� y�k ��z�n�rl���n� ele ald���m�zda (yak�nda ele al�nacak olan 10.12 dersinde -- Fonksiyon a��r� y�k ��z�n�rl��� ve belirsiz e�le�meler),
bu durumun fark yaratt��� �rnekleri g�rece�iz.

10.2 � Standart D�n���mler 1- Say�sal D�n���mler
------------------------------------------------

C++, ba�ka bir say�sal t�r d�n���m� kategorisini destekler, buna say�sal d�n���mler denir. Bu say�sal d�n���mler, temel tipler aras�ndaki 
ek tip d�n���mlerini kapsar.


Numeric promotion kurallar� (10.2 -- Ondal�k Nokta ve Tamsay� Y�kseltme) taraf�ndan kapsanan herhangi bir t�r d�n���m� bir say�sal y�kseltmedir, say�sal bir d�n���m de�ildir.

Be� temel say�sal d�n���m t�r� bulunmaktad�r.

1. Herhangi bir di�er integral t�r�ne tamsay� t�r�nden d�n��t�rme (tamsay� y�kseltmeleri hari�):
                        short s = 3;        // int'i short'a d�n��t�r
                        long l = 3;         // int'i long'a d�n��t�r
                        char ch = s;        // short'u char'a d�n��t�r
                        unsigned int u = 3; // int'i unsigned int'e 

2. Ondal�k say� t�r�n� ba�ka bir ondal�k say� t�r�ne d�n��t�rme (kayan noktal� say� y�kseltmeleri hari�):

                        float f = 3.0;       // double'� float'a d�n��t�r
                        long double ld = 3.0; // double'� long double'a d�n��t�r

3. Kayan noktal� say� tiplerini her hangi bir tam say� tipine d�n��t�rme:
                        
                        int i = 3.5; // double'� int'e d�n��t�r

4. Bir tamsay� t�r�n� herhangi bir ondal�k nokta t�r�ne d�n��t�rme:

                        double d = 3; // int'i double'a d�n��t�r

5. Bir tamsay� t�r�n� veya bir ondal�k say� t�r�n� bool'e d�n��t�rme:

                        bool b1 = 3;    // int'i bool'e d�n��t�r
                        bool b2 = 3.0;  // double'� bool'e d�n��t�r

Bir kenara not olarak...

Parantez ba�latma, baz� say�sal d�n���mleri kesinlikle engelledi�i i�in (bunu bir sonraki derste daha ayr�nt�l� olarak ele alaca��z),
�rnekleri basit tutmak i�in bu derste kopya ba�latmay� kullan�yoruz (bu t�r k�s�tlamalar� i�ermeyen).

G�venli ve Potansiyel Tehlikeli D�n���mler
------------------------------------------

Her zaman de�eri koruyan (ve bu nedenle her zaman "g�venli" olan) bir say�sal y�kseltmenin aksine, baz� say�sal d�n���mler belirli 
durumlarda de�eri korumaz. Bu t�r d�n���mlere "g�vensiz" denir (ger�ekte "potansiyel olarak g�vensiz" daha do�ru bir terimdir, ��nk� 
bu d�n���mler di�er durumlarda de�eri korur).

Say�sal d�n���mler �� g�venlik kategorisinden birine girer:

1- De�eri koruyan d�n���mler, hedef t�r�n kaynak t�rdeki t�m de�erleri tam olarak temsil edebildi�i g�venli say�sal d�n���mlerdir.

�rne�in, int'ten long'a ve short'tan double'a olan d�n���mler g�venli d�n���mlerdir, ��nk� kaynak de�er her zaman hedef t�rdeki e�de�er bir de�ere 
d�n��t�r�lebilir.

                        int main()
                        {
                            int n{ 5 };
                            long l = n;      // tamam, long de�eri 5 �retir

                            short s{ 5 };
                            double d = s;    // tamam, double de�eri 5.0 �retir

                            return 0;
                        }

Derleyiciler genellikle �rt�k de�eri koruyan d�n���mler i�in uyar� vermez.

De�eri koruyan bir d�n���m kullan�larak d�n��t�r�len bir de�er her zaman kaynak t�r�ne geri d�n��t�r�lebilir ve bu, orijinal de�ere e�de�er bir
de�eri �retir:

                        #include <iostream>

                        int main()
                        {
                            int n = static_cast<int>(static_cast<long>(3)); // int 3'� long'a ve geri d�n��t�r
                            std::cout << n << '\n';                         // 3'� yazd�r�r

                            char c = static_cast<char>(static_cast<double>('c')); // 'c'yi double'a �evir ve geri d�n��t�r
                            std::cout << c << '\n';                               // 'c'yi yazd�r�r

                            return 0;
                        }


2- Yorumlama D�n���mleri, sonucun kaynak t�r�n�n aral���n�n d���nda olabilece�i potansiyel olarak g�vensiz say�sal d�n���mlerd�r. i�aretli/i�aretsiz
d�n���mler bu kategoriye girer.
�rne�in, bir i�aretli int'i i�aretsiz int'e d�n��t�rd���m�zde:

                        int main()
                        {
                            int n1{ 5 };
                            unsigned int u1{ n1 };  // tamam: unsigned int 5'e d�n��t�r�lecek (de�er korunur)

                            int n2{ -5 };
                            unsigned int u2{ n2 };  // hatal�: i�aretli int'in aral���n�n d���nda b�y�k bir tamsay� elde edilecek

                            return 0;
                        }

u1 durumunda, i�aretli int de�eri 5, i�aretsiz int de�eri 5'e d�n��t�r�l�yor. Bu durumda de�er korunur.

u2 durumunda, i�aretli int de�eri -5, i�aretsiz int'e d�n��t�r�l�yor. ��nk� i�aretsiz bir int negatif say�lar� temsil edemez, sonu�
olarak b�y�k bir tamsay� de�eri elde edilir ve bu, i�aretli bir int'in aral���n�n d���nda kal�r. Bu durumda de�er korunmaz.

Bu t�r de�er de�i�iklikleri genellikle istenmeyen sonu�lara yol a�ar ve genellikle program�n beklenmeyen veya uygulama tan�ml� davran�� 
sergilemesine neden olabilir.

Uyar�

Yeniden yorumlama d�n���mleri potansiyel olarak g�vensiz olmalar�na ra�men, �o�u derleyici genellikle varsay�lan olarak i�levsiz i�aretli/i�aretsiz 
d�n���m uyar�lar�n� devre d��� b�rak�r.

Bu, modern C++'�n baz� alanlar�nda (�rne�in, standart k�t�phane dizileri ile �al���rken) i�aretli/imsiz d�n���mlerin ka��n�lmaz olabilece�i anlam�na
gelir. Ve pratikte, bu t�r d�n���mlerin �o�u asl�nda bir de�er de�i�ikli�ine neden olmaz. Bu nedenle, bu uyar�lar� etkinle�tirmek, asl�nda sorun 
olmayan i�aretli/imsiz d�n���mler i�in �ok say�da sahte uyar�ya neden olabilir (ge�erli uyar�lar� g�lgede b�rakabilir).

E�er bu t�r uyar�lar� devre d��� b�rakmay� se�erseniz, bu t�r t�rler aras�ndaki istenmeyen d�n���mlere kar�� dikkatli olun (�zellikle bir arg�man�,
ters i�arete sahip bir parametre alan bir i�leme ge�irirken).

Yeniden yorumlama d�n���mleri kullan�larak d�n��t�r�len de�erler, kaynak t�r�ne geri d�n��t�r�lebilir, bu da ba�lang��ta elde edilen de�eri kaynak 
t�r�n aral���ndaki bir de�ere e�de�er hale getirir (ba�lang��ta yap�lan d�n���m kaynak t�r�n aral���n�n d���nda bir de�er �retse bile).

                            #include <iostream>

                            int main()
                            {
                                int u = static_cast<int>(static_cast<unsigned int>(-5)); // '-5' de�erini i�aretsiz tamsay�ya d�n��t�r ve geri d�n��t�r
                                std::cout << u << '\n'; // -5'i yazd�r�r

                                return 0;
                            }


3 - Kay�pl� d�n���mler, d�n���m s�ras�nda baz� verilerin kaybedilebilece�i potansiyel olarak g�vensiz say�sal d�n���mlerdir.

�rne�in, double tipinden int tipine yap�lan bir d�n���m, veri kayb�na neden olabilecek bir d�n���md�r:

                            int i = 3.0; // ge�erli: int de�eri 3'e d�n��t�r�lecek (de�er korunur)
                            int j = 3.5; // veri kayb�: int de�eri 3'e d�n��t�r�lecek (kesirli de�er 0.5 kaybolacak)

Double'dan floata yap�lan d�n���m de veri kayb�na neden olabilir:

                            float f = 1.2;        // ge�erli: float de�eri 1.2'ye d�n��t�r�lecek (de�er korunur)
                            float g = 1.23456789; // veri kayb�: float 1.23457'ye d�n��t�r�lecek (kesirli de�er kaybolur)

Veri kayb� ya�am�� bir de�eri kaynak t�r�ne geri d�n��t�rmek, orijinal de�erden farkl� bir de�ere yol a�acakt�r:

                            #include <iostream>

                            int main()
                            {
                                double d { static_cast<double>(static_cast<int>(3.5)) }; // double 3.5'i int'e d�n��t�r ve geri double'a d�n��t�r 
                                                                                         // (veri kayb�)
                                std::cout << d << '\n'; // 3 yazd�r�r

                                double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // double 1.23456789'u floata d�n��t�r ve geri
                                                                                                   // double'a d�n��t�r (hassasiyet kayb�)
                                std::cout << d2 << '\n'; // 1.23457 yazd�r�r

                                return 0;
                            }

�rne�in, double de�eri 3.5'in int de�eri 3'e d�n��t�r�lmesi durumunda, kesirli bile�en olan 0.5 kaybolur. 3, double'a geri d�n��t�r�ld���nde sonu� 
3.0 olur, 3.5 de�il.

Derleyiciler genellikle �al��ma zaman�nda a��k�a belirgin bir veri kayb� d�n���m� yap�lacaksa bir uyar� (veya baz� durumlarda hata) bildirir.

Uyar�

Baz� d�n���mler, platforma ba�l� olarak farkl� kategorilere girebilir.

�rne�in, int'ten double'a d�n�� genellikle g�venli bir d�n���md�r, ��nk� int genellikle 4 bayt ve double genellikle 8 bayt oldu�u i�in,
bu t�r sistemlerde t�m olas� int de�erleri bir double olarak temsil edilebilir. Ancak int ve double'�n her ikisinin de 8 bayt oldu�u mimariler
vard�r. Bu t�r mimarilerde int'ten double'a d�n��, bir veri kayb� d�n���m�d�r!

Bunu, bir long long de�erini (en az 64 bit olmal�d�r) double'a d�n��t�rerek ve geri d�n��t�rerek g�sterebiliriz:

                            #include <iostream>

                            int main()
                            {
                                std::cout << static_cast<long long>(static_cast<double>(10000000000000001LL));

                                return 0;
                            }

                            Bu �u �ekilde yazd�r�l�r:

                            10000000000000000
                            Son basama��m�z�n kayboldu�una dikkat edin!


Say�sal d�n���mlerle ilgili �zel kurallar karma��k ve say�ca fazla oldu�u i�in, i�te hat�rlaman�z gereken en �nemli �eyler:

Her durumda, bir de�eri, o de�eri desteklemeyen bir t�r�ne d�n��t�rmek muhtemelen beklenmeyen sonu�lara yol a�acakt�r. �rne�in:

                            int main()
                            {
                                int i{ 30000 };
                                char c = i; // chars have range -128 to 127

                                std::cout << static_cast<int>(c) << '\n';

                                return 0;
                            }

Bu �rnekte, b�y�k bir tamsay�y� bir char t�r�ndeki bir de�i�kene atad�k (ki bu t�r�n aral��� -128 ile 127 aras�ndad�r). Bu, char'�n ta�mas�na 
neden olur ve beklenmeyen bir sonu� �retir:

                            ��kt� -> 48

Unutmay�n ki ta�ma i�lemi, i�aretsiz de�erler i�in tan�ml�d�r ve i�aretli de�erler i�in tan�ms�z davran��a neden olur.

Ayn� ailedeki daha b�y�k bir t�rden daha k���k bir t�re d�n��t�rme genellikle de�erin daha k���k t�r�n aral���na s��d��� s�rece �al��acakt�r. �rne�in:
        
                            int i{ 2 };
                            short s = i; // int -> short d�n���m�
                            std::cout << s << '\n';

                            double d{ 0.1234 };
                            float f = d;
                            std::cout << f << '\n';

Bu beklenen sonucu �retir:
                            2
                            0.1234   -> G�r�ld��� �zere �al���yor. 

Ondal�k say� de�erleri i�in, daha k���k bir t�rdeki hassasiyet kayb�ndan dolay� baz� yuvarlama olaylar� meydana gelebilir. �rne�in:

                            float f = 0.123456789; 
                            // double de�eri 0.123456789 9 �nemli rakam i�erir, ancak float t�r� yaln�zca yakla��k olarak 7 rakam� destekleyebilir
                            std::cout << std::setprecision(9) << f << '\n'; // iomanip ba�l�k dosyas�nda tan�ml� olan std::setprecision

Bu durumda, float t�r�n�n bir double kadar hassasiyeti tutamad���n� g�r�yoruz:
                            0.123456791

Bir tamsay�y� bir kayan nokta say�s�na d�n��t�rmek genellikle de�erin kayan nokta t�r�n�n aral���na s��mas� durumunda �al���r. �rne�in:

                            int i{ 10 };
                            float f = i;
                            std::cout << f << '\n';

Beklenen ��kt�y� �retir: 
                            10

Bir kayan nokta say�s�ndan bir tamsay�ya d�n��t�rmek, de�erin tamsay� aral���na s��mas� durumunda �al���r, ancak herhangi bir kesirli de�er kaybolur.
�rne�in:
                            int i = 3.5;
                            std::cout << i << '\n';

Bu �rnekte, kesirli de�er (.5) kaybolur, �u sonucu b�rak�r:
                            3

Say�sal d�n���m kurallar� korkutucu gibi g�r�nebilir, ancak ger�ekte derleyici genellikle tehlikeli bir �ey yapmaya �al��t���n�zda sizi uyaracakt�r
(baz� i�aretli/i�aretsiz d�n���mleri hari� tutarak).
*/
/*

10.4 � Daralt�c� d�n���mler, liste ba�latma ve constexpr ba�lat�c�lar
---------------------------------------------------------------------


C++ dilinde, daralt�c� d�n���m, hedef t�r�n kaynak t�r�n t�m de�erlerini tutamayabilece�i potansiyel olarak g�venli olmayan bir say�sal d�n���md�r.

A�a��daki d�n���mler daralt�c� olarak tan�mlanm��t�r:

*- Bir kayan nokta t�r�nden bir tam say� t�r�ne.
*- Bir kayan nokta t�r�nden daha dar veya daha d���k bir s�ralamal� kayan nokta t�r�ne, d�n��t�r�len de�er constexpr ise ve hedef t�r�n aral���nda ise
   (hedef t�r, say�n�n �nemli basamaklar�n�n tamam�n� depolam�yorsa bile).
*- Bir tam say�dan bir kayan nokta t�r�ne, d�n��t�r�len de�er constexpr ise ve de�er hedef t�rde tam olarak depolanabiliyorsa.
*- Bir tam say� t�r�nden, orijinal t�r�n t�m de�erlerini temsil edemeyen ba�ka bir tam say� t�r�ne, d�n��t�r�len de�er constexpr ise ve de�er hedef
   t�rde tam olarak depolanabiliyorsa. Bu, geni�ten daraya tam say� d�n���mlerini, ayn� zamanda i�aret d�n���mlerini (i�aretli t�rden i�aretsiz t�re 
   veya tersi) kapsar.

Genellikle, bilin�siz daralt�c� d�n���mler derleyici uyar�lar�na yol a�acakt�r, istisna olarak i�aretli/i�aretsiz d�n���mler (derleyicinizin nas�l
yap�land�r�ld���na ba�l� olarak uyar� �retebilir veya �retmeyebilir).

Bilin�siz daralt�c� d�n���mler m�mk�n oldu�unca ka��n�lmas� gereken bir durumdur, ��nk� potansiyel olarak g�vensizdir ve bu nedenle potansiyel 
hatalar�n kayna��d�r.

*** BEST -> G�venli olmad�klar� ve hatalar�n kayna�� olduklar� i�in m�mk�nse bilin�siz daralt�c� d�n���mlerden ka��n�n.

Bilin�li daralt�c� d�n���mleri kas�tl� olarak ( explicit ) yap�n
---------------------------------------------------------------- 

Narrowing conversions her zaman ka��n�lamaz; �zellikle fonksiyon �a�r�lar� i�in bu durum ge�erlidir, burada fonksiyon parametresi ve arg�man�n�n 
uyumsuz t�rlere sahip olmas� ve daralt�c� bir d�n���m gerektirmesi m�mk�nd�r.

Bu t�r durumlarda, daralt�c� bir d�n���m� a��k�a belirtmek i�in implicit (bilin�siz) bir daralt�c� d�n���m� static_cast kullanarak explicit (a��k) 
bir daralt�c� d�n���me �evirmek iyi bir fikirdir. Bu, daralt�c� d�n���m�n kas�tl� oldu�unu belgelemeye yard�mc� olur ve ayr�ca derleyici uyar�lar�n� 
veya hatalar�n� bast�r�r.

�rnek olarak:

                    void someFcn(int i)
                    {
                    }

                    int main()
                    {
                    double d{ 5.0 };

                    someFcn(d); // hatal�: bilin�siz daralt�c� d�n���m derleyici uyar�s� �retecektir

                    // iyi: daralt�c� d�n���m�n kas�tl� oldu�unu derleyiciye a��k�a belirtiyoruz
                    someFcn(static_cast<int>(d)); // uyar� �retilmez

                    return 0;
                    }

*** BEST -> E�er daralt�c� bir d�n���m yapman�z gerekiyorsa, static_cast kullanarak onu a��k bir d�n���me �evirin.

Parantez ba�latma (brace initialization) daralt�c� d�n���mleri engeller (bu ba�latma bi�iminin tercih edilme nedenlerinden biridir) ve b�yle 
bir d�n���m yapmaya �al��mak derleme hatas� �retecektir �rne�in:

                    int main()
                    {
                        int i { 3.5 }; // won't compile

                        return 0;
                    }

Visual studio �u hatay� �retir:
                    error C2397: conversion from 'double' to 'int' requires a narrowing conversion

E�er ger�ekten bir parantez ba�latma i�inde daralt�c� bir d�n���m yapmak istiyorsan�z, daralt�c� d�n���m� a��k bir d�n���me �evirmek i�in static_cast
kullan�n:

                    int main()
                    {
                        double d { 3.5 };

                        // static_cast<int>, double'� int'e �evirir, i'yi int sonucuyla ba�lat�r
                        int i { static_cast<int>(d) };

                        return 0;
                    }

Baz� constexpr d�n���mler daralt�c� olarak kabul edilmez. Bir daralt�c� d�n���m�n kaynak de�eri �al��ma zaman�na kadar bilinmiyorsa, d�n���m�n
sonucu da �al��ma zaman�na kadar belirlenemez. Bu t�r durumlarda, daralt�c� d�n���m�n de�eri koruyup korumad��� da �al��ma zaman�na kadar belirlenemez. �rne�in:

                    #include <iostream>

                    void print(unsigned int u) // not: unsigned
                    {
                        std::cout << u << '\n';
                    }

                    int main()
                    {
                        std::cout << "Enter an integral value: ";
                        int n{};
                        std::cin >> n; // 5 veya -5 girin
                        print(n);      // d�n���m, de�eri koruyabilir veya korumayabilir

                        return 0;
                    }

Yukar�daki programda, derleyici n i�in hangi de�erin girilece�ini bilmez. print(n) �a�r�ld���nda int'ten unsigned int'e olan d�n���m o an 
ger�ekle�ir ve sonu�lar, n i�in girilen de�ere ba�l� olarak de�eri koruyabilir veya korumayabilir. Bu nedenle, i�aretsiz/i�aretli uyar�lar�
etkinle�tirilmi� bir derleyici, bu durum i�in bir uyar� verecektir.

Ancak, �o�u daralt�c� d�n���m tan�m�n�n ba��nda "unless the value being converted is constexpr and ..." ile ba�layan bir istisna maddesi 
oldu�unu fark etmi� olabilirsiniz. �rne�in, bir d�n���m daralt�c�d�r ve "From an integral type to another integral type that cannot represent
all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type."
ifadesi ile belirtilir.

Bir daralt�c� d�n���m�n kaynak de�eri constexpr oldu�unda, d�n��t�r�lecek �zel de�er derleyici taraf�ndan bilinmelidir. Bu t�r durumlarda, 
derleyici d�n���m� kendisi ger�ekle�tirebilir ve ard�ndan de�erin korunup korunmad���n� kontrol edebilir. E�er de�er korunmam��sa, derleyici
hata ile derlemeyi durdurabilir. De�er korunmu�sa, d�n���m daralt�c� olarak kabul edilmez (ve derleyici, bunu g�venli oldu�unu bilerek tamamen 
d�n��t�r�lm�� sonu�la de�i�tirebilir).

�rne�in:

                    #include <iostream>

                    int main()
                    {
                        constexpr int n1{ 5 };   // not: constexpr
                        unsigned int u1 { n1 };  // tamam: d�n���m, daralt�c� olmad��� i�in sorun yok

                        constexpr int n2 { -5 }; // not: constexpr
                        unsigned int u2 { n2 };  // derleme hatas�: d�n���m, de�erin de�i�mesi nedeniyle daralt�c�d�r

                        return 0;
                    }


"Orijinal t�r�n t�m de�erlerini temsil edemeyen bir tamsay� t�r�nden ba�ka bir tamsay� t�r�ne d�n���m, d�n��t�r�len de�er constexpr ise ve de�eri 
hedef t�rde tam olarak depolanabiliyorsa daralt�c� de�ildir" kural�n� yukar�daki her iki d�n���me de uygulayal�m.

n1 ve u1 i�in, n1 bir int ve u1 bir unsigned int oldu�undan, bu, orijinal t�r�n t�m de�erlerini temsil edemeyen bir tamsay� t�r�nden ba�ka bir 
tamsay� t�r�ne d�n���md�r. Ancak n1 constexpr oldu�u i�in ve de�eri 5, hedef t�rde (unsigned de�er 5 olarak) tam olarak depolanabildi�i i�in, 
bu daralt�c� d�n���m olarak kabul edilmez ve n1'i kullanarak u1'i liste ba�latma yapabiliriz.

n2 ve u2 i�in durumlar benzerdir. N2 constexpr olsa da, de�eri -5 hedef t�rde tam olarak temsil edilemez, bu nedenle bu daralt�c� bir d�n���m
olarak kabul edilir ve liste ba�latma yapt���m�z i�in derleyici hata verecek ve derlemeyi durduracakt�r.

Ilgin� bir �ekilde, kayan nokta t�r�nden tamsay� t�r�ne yap�lan d�n���mlerde constexpr istisna maddesi bulunmamaktad�r. Bu nedenle, d�n��t�r�lecek 
de�er constexpr olsa ve hedef t�r�n aral���na s��sa bile, bu d�n���mler her zaman daralt�c� olarak kabul edilir:

                    int n { 5.0 }; // compile error: narrowing conversion

constexpr ba�lat�c�lara sahip liste ba�latma ve bunlar�n �zel durum maddeleri
-----------------------------------------------------------------------------
int veya double t�r�nden olmayan nesneleri liste ba�latma i�lemlerinde son derece kullan��l�d�r. ��nk� bir int veya double literali
(veya constexpr nesnesi) ba�latma de�eri kullanabiliriz.

Bu bize �unlardan ka��nma imkan� tan�r:

*- �o�u durumda literal eklerini kullanmak zorunda olmamak
*- Ba�latmalar�m�z� static_cast ile karma��k hale getirmemek
�rne�in:

                    int main()
                    {
                        // Soneklerle literalleri kullanmaktan ka��nabiliriz
                        unsigned int u { 5 }; // uygun ( `5u` kullanmam�za gerek yok)
                        float f { 1.5 };      // uygun ( `1.5f` kullanmam�za gerek yok)

                        // static_cast kullanmaktan ka��nabiliriz
                        constexpr int n{ 5 };
                        double d { n };       // uygun (burada static_cast'a ihtiyac�m�z yok)
                        short s { 5 };        // uygun (short i�in sonek yok, burada static_cast'a ihtiyac�m�z yok)
                            
                        return 0;
                    }

Bu, kopyalama ve do�rudan ba�latma ile de �al���r.

Dikkat edilmesi gereken bir husus: dar veya daha d���k s�ral� bir kayan nokta t�r�n�, hedef t�r�n aral���nda bir constexpr de�eri ile ba�latmak, 
hedef t�r�n de�eri kesin bir �ekilde depolamayacak kadar hassasiyeti olmasa bile izin verilir!

Anahtar �pucu

Kayan nokta t�rleri �u s�rayla s�ralan�r (b�y�kten k����e):

Long double
Double
Float
Bu nedenle, �una benzer bir �ey yasald�r ve bir hata �retmeyecektir:

                        int main()
                        {
                            float f { 1.23456789 }; // Daralt�c� bir d�n���m de�il, hatta hassasiyet kaybedilmi� olsa bile!

                            return 0;
                        }

Ancak, bu durumda derleyiciniz hala bir uyar� verebilir (GCC ve Clang, -Wconversion derleme bayra��n� kullan�rsan�z uyar� verebilir).

10.5 � Aritmetik D�n���mler
---------------------------

                        int x { 2 + 3 };

Bu durumda, operator+ �a�r�ld���nda, iki operand da int t�r�ndedir. Her iki operand da ayn� t�rde oldu�undan, bu t�r hesaplamay� ger�ekle�tirmek ve 
sonucu d�nd�rmek i�in kullan�l�r. Bu nedenle, 2 + 3 ifadesi int de�eri 5'e de�erlendirilecektir.

                        ??? y { 2 + 3.5 };

Bu durumda, operator+ bir tane int ve bir tane double t�r�ndeki operand ile �a�r�l�yor. Operat�r�n sonucu int, double veya belki tamamen farkl� 
bir �ey olarak d�nmeli mi? Bir de�i�ken tan�mlarken, onun hangi t�rde oldu�unu se�ebiliriz. Di�er durumlarda, �rne�in std::cout << kullan�l�rken, 
hesaplaman�n de�eri ��kt�n�n davran���n� de�i�tirir.

C++'da, belirli operat�rlerin operandlar�n�n ayn� t�rde olmas�n� gerektiren durumlar vard�r. Bu operat�rlerden biri, farkl� t�rlerdeki operandlarla 
�a�r�l�rsa, operandlardan biri veya her ikisi de, "usual arithmetic conversions" adl� bir kurallar k�mesi kullan�larak e�le�en tiplere �rt�l� olarak
d�n��t�r�l�r.

Ayn� t�rdeki operandlar� gerektiren operat�rler
-----------------------------------------------

Ayn� t�rdeki operandlar� gerektiren a�a��daki operat�rler:

1- �kili aritmetik operat�rler: +, -, *, /, %
2- �kili ili�kisel operat�rler: <, >, <=, >=, ==, !=
3- �kili bitwise aritmetik operat�rler: &, ^, |
4- ��l� ko�ul operat�r� ?: (beklenen tip bool t�r�nde olan ko�ulu hari�)

Genel aritmetik d�n���m kurallar�
---------------------------------


Genel aritmetik d�n���m kurallar� olduk�a basittir. Derleyicinin �ncelikli bir t�r listesi vard�r ve bu liste �una benzer:

    ->> long double (en y�ksek �ncelik)
    ->> double
    ->> float
    ->> unsigned long long
    ->> long long
    ->> unsigned long
    ->> long
    ->> unsigned int
    ->> int (en d���k �ncelik)
Sadece iki kural bulunmaktad�r:

1 -) En az bir operand�n t�r� �ncelikli listede ise, daha d���k �nceli�e sahip operand, daha y�ksek �nceli�e sahip operand�n t�r�ne d�n��t�r�l�r.
2 -) Aksi takdirde (her iki operand�n t�r� de listede de�ilse), her iki operand da say�sal olarak y�kseltilir (bkz. 10.2 - Kayan nokta ve tam
     say� y�kseltme)


Baz� �rnekler

operator+ i�lemi, operandlar�n�n ayn� t�re sahip olmas�n� gerektiren operat�rlerden biridir.

A�a��daki �rneklerde, sonu� t�r�n� g�stermek i�in <typeinfo> ba�l���nda bulunan typeid operat�r�n� kullanaca��z.

�lk olarak, bir int ve bir double ekleyelim:

                        #include <iostream>
                        #include <typeinfo> // for typeid()

                        int main()
                        {
                            int i{ 2 };
                            double d{ 3.5 };
                            std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // i + d nin type'�n� g�ster

                            return 0;
                        }

Bu durumda, double t�r�ndeki operand en y�ksek �nceli�e sahiptir, bu nedenle daha d���k �ncelikli operand (int t�r�nde) double de�eri 2.0'a 
d�n��t�r�l�r. Daha sonra 2.0 ve 3.5 double de�erleri eklenerek double sonu� 5.5 elde edilir.

Yazar�n bilgisayar�nda, bu �u �ekilde yazd�r�l�r:
                        double 5.5


Unutmay�n ki derleyiciniz, typeid.name()'in ��kt�s�n� belirlemekte serbest b�rak�ld���ndan, bu biraz farkl� bir �ey g�sterebilir.

�imdi short t�r�ndeki iki de�eri ekleyelim:

                        #include <iostream>
                        #include <typeinfo> // typeid() i�in

                        int main()
                        {
                            short a{ 4 };
                            short b{ 5 };
                            std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // a + b nin type'�n� g�ster

                            return 0;
                        }

��nk� her iki operand da �ncelikli listede bulunmaz, her iki operand da int t�r�ne integral y�kseltmeye tabi tutulur. �ki int'in toplam�n�n sonucu,
beklendi�i gibi bir int'tir:
           -> ��kt�:   int 9
                    
�mzal� ve �mzas�z Sorunlar
--------------------------

Bu �ncelik s�ras�, i�aretli ve i�aretsiz de�erleri kar��t�r�rken baz� sorunlara neden olabilir. �rne�in, a�a��daki kodu inceleyin:

                        #include <iostream>
                        #include <typeinfo> // typeid() i�in

                        int main()
                        {
                            std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u nun anlam� 5 unsigned integer olarak davran�r. 

                            return 0;
                        }

�fade 5u - 10'in -5 olarak de�erlendirilmesini bekleyebilirsiniz ��nk� 5 - 10 = -5. Ancak, i�te ger�ekte ortaya ��kan:

                        unsigned int 4294967291

�mzas�z int operand�n�n daha y�ksek �nceli�i oldu�undan, int operand� bir i�aretsiz int'e d�n��t�r�l�r. Ve ��nk� -5 de�eri i�aretsiz bir int'in 
aral���n�n d���nda oldu�u i�in, beklenmeyen bir sonu� elde ederiz.

��te kar��t bir sonu� g�steren ba�ka bir �rnek:

                        #include <iostream>

                        int main()
                        {
                            std::cout << std::boolalpha << (-3 < 5u) << '\n';

                            return 0;
                        }


5'in -3'ten daha b�y�k oldu�u bize a��k olsa da, bu ifade de�erlendirildi�inde -3, 5'ten daha b�y�k olan b�y�k bir i�aretsiz int'e d�n��t�r�l�r.
Bu nedenle, yukar�daki ifade beklenen sonu� olan true yerine false yazd�r�r.

Bu, i�aretsiz tamsay�lar� kullanmaktan ka��nman�n temel nedenlerinden biridir - onlar� i�aretli tamsay�larla aritmetik ifadelerde kar��t�rd���n�zda,
beklenmeyen sonu�lara kar�� risk alt�nda olursunuz. Ve derleyici muhtemelen uyar� bile vermez.

10.6 � Explicit t�r d�n���m� (casting) and static_cast
------------------------------------------------------

Bir�ok yeni C++ programc�s� ��yle bir �ey denemeye �al���r:

                        double d = 10 / 4; // tamsay� b�lme yapar, d'yi 2.0 de�eri ile ba�lat�r

��nk� 10 ve 4 her ikisi de int t�r�ndedir, tamsay� b�lme yap�l�r ve ifade int de�eri 2'ye de�erlendirilir. Bu de�er daha sonra de�i�ken d'yi 
ba�latmak i�in kullan�lmadan �nce double de�eri 2.0'ya say�sal d�n���me u�rar. B�y�k olas�l�kla, bu istenmeyen bir durumdur.

E�er literal operat�rler kullan�yorsan�z, bir veya her iki tamsay� literalini double literal ile de�i�tirmek, ondal�k b�lme i�lemine neden 
olacakt�r:

                        double d = 10.0 / 4.0; // ondal�k b�lme yapar, d'yi 2.5 de�eri ile ba�lat�r

Ancak literatller yerine de�i�kenler kullan�yorsan�z ne olacak? Bu durumu d���n�n:

                        int x { 10 };
                        int y { 4 };
                        double d = x / y; // tamsay� b�lme yapar, d'yi 2.0 de�eri ile ba�lat�r

��nk� burada tamsay� b�lme kullan�l�yor, de�i�ken "d" 2.0 de�eri ile ba�lat�lacakt�r. Bu durumda derleyiciye, bu durumda tamsay� b�lme yerine
ondal�k b�lme kullanmak istedi�imizi belirtmek i�in nas�l bir yol izleyebiliriz? Literal �nekleri de�i�kenlerle kullan�lamaz. Bir de�i�ken 
operand�n� ondal�k bir t�rde bir say�ya d�n��t�rmek i�in, derleyiciden bir t�r d�n���m� ger�ekle�tirmesini istemek i�in programc� taraf�ndan
kullan�lan �e�itli t�r d�n���m operat�rleri (daha yayg�n olarak "cast" olarak adland�r�l�r) C++ ile birlikte gelmektedir. ��nk� "cast"ler programc�
taraf�ndan yap�lan bilin�li talepler oldu�u i�in, bu t�r bir t�r d�n���m� genellikle kas�tl� ( veya bilin�li olarak �evirdim )
t�r d�n���m� olarak adland�r�l�r (derleyicinin otomatik olarak bir t�r d�n���m� ger�ekle�tirdi�i �rt�k t�r d�n���m�ne kar��).

T�r D�n���m�
------------


C++ 5 farkl� t�rde d�n���m� destekler:
1 - C tarz� d�n���mler
2 - static d�n���mler
3 - const d�n���mler
4 - dynamic d�n���mler 
5 - reinterpret d�n���mleri.

Son d�rt tanesi bazen adland�r�lm�� d�n���mler olarak an�l�r.

Bu derste C tarz� d�n���mler ve static d�n���mleri ele alaca��z.


const d�n���mleri ve reinterpret d�n���mleri genellikle ka��n�lmas� gereken t�rlerdir ��nk� nadir durumlar d���nda kullan��s�zd�r ve yanl��
kullan�ld���nda zararl� olabilir.

Uyar� -> onlar� kullanma konusunda �ok iyi bir nedeniniz yoksa, const d�n���mlerinden ve reinterpret d�n���mlerinden ka��n�n

C tarz� d�n���mler

Standart C programlamada d�n���mler () operat�r� arac�l���yla yap�l�r, bu operat�r�n i�ine d�n��t�r�lecek de�erin t�r�n�n ad� yerle�tirilir. 
Bu t�r d�n���mleri, C'den d�n��t�r�lm�� olan kodlarda (veya programc�lar taraf�ndan) h�l� g�rebilirsiniz.

�rne�in:


                        #include <iostream>

                        int main()
                        {
                            int x { 10 };
                            int y { 4 };

                            double d { (double)(x) / y }; // x'i bir double'a d�n��t�rerek ondal�k b�lme elde etmek i�in
                            std::cout << d << '\n'; // 2.5 yazd�r�r

                            return 0;
                        }

Yukar�daki programda, x'in bir double t�r�ne d�n��t�r�lmesini s�ylemek i�in bir C tarz� d�n���m kullan�yoruz. ��nk� "/" operat�r�n�n sol operand�
art�k bir ondal�k say� de�erine de�erlendirildi�i i�in, sa� operand da bir ondal�k say� de�erine d�n��t�r�lecek ve b�lme i�lemi ondal�k say�
b�lme olarak ger�ekle�tirilecektir!

C++ ayr�ca, C tarz� d�n���m� daha i�lev �a�r�s� benzeri bir s�zdizimiyle kullanman�za da izin verir.

                        double d { (double)(x) / y }; // x'i bir double'a d�n��t�rerek ondal�k b�lme elde etmek i�in


Bu, �nceki �rnekle ayn� �ekilde �al���r, ancak d�n��t�r�len de�eri parantez i�ine alarak (neyin d�n��t�r�ld���n� daha kolay anlamam�za olanak tan�yarak)
avantaj sa�lar. C tarz� bir d�n���m, tek bir d�n��m�� gibi g�r�nse de, ba�lam�na ba�l� olarak �e�itli farkl� d�n���mleri ger�ekle�tirebilir. Bu, bir 
static d�n���m, bir const d�n���m veya bir reinterpret d�n���m� i�erebilir (ki bunlardan son ikisini yukar�da ka��n�lmas� gerekenler olarak 
belirtmi�tik). Sonu� olarak, C tarz� d�n���mler, yanl��l�kla yanl�� kullan�lmaya ve beklenen davran��� �retmemeye y�nelik bir risk ta��r, ki bu da
C++ d�n���mlerini kullanarak kolayca �nlenebilir.

Ayr�ca, C tarz� d�n���mler yaln�zca bir t�r ad�, parantez ve de�i�ken veya de�er oldu�undan, bunlar� tan�mlamak zordur (kodunuzu daha zor okunur 
hale getirir) ve hatta daha da zor aranabilir hale getirir.

*** BEST -> C-Style cast lerden ka��nmak en iyi uygulama olacakt�r. 

Static cast
-----------

C++, bir t�r�n de�erini ba�ka bir t�r�n de�erine d�n��t�rmek i�in kullan�lan static_cast adl� bir d�n���m operat�r� tan�tm��t�r.
Daha �nce bir char'� int'e d�n��t�rmek i�in static_cast kullan�ld���n� g�rm��t�k, b�ylece std::cout, onu bir char yerine bir tamsay� olarak yazd�r�r:

                    #include <iostream>

                    int main()
                    {
                        char c { 'a' };
                        std::cout << c << ' ' << static_cast<int>(c) << '\n'; // 'a' karakterini ve kar��l�k gelen ASCII de�erini (97) yazd�r�r

                        return 0;
                    }

static_cast operat�r�, bir ifadeyi girdi olarak al�r ve i�indeki a��lm�� parantez i�inde belirtilen t�re d�n��t�r�lm�� de�eri d�nd�r�r. static_cast, 
bir temel t�r� ba�ka bir temel t�re d�n��t�rmek i�in en uygun olan�d�r.

                    #include <iostream>

                    int main()
                    {
                        int x { 10 };
                        int y { 4 };

                        // x'i bir double'a d�n��t�rerek ondal�k say� b�lmesi elde ediyoruz
                        double d { static_cast<double>(x) / y };
                        std::cout << d << '\n'; // 2.5 yazd�r�r

                        return 0;
                    }

`static_cast`'in temel avantaj�, derleme zaman�nda t�r denetimi sa�lamas�d�r; bu da yanl��l�kla hata yapmay� zorla�t�r�r

                    // C tarz� bir dizge literali bir tamsay�ya d�n��t�r�lemez, bu nedenle a�a��daki d�n���m ge�ersizdir ve derleme hatas� �retecektir
                    int x { static_cast<int>("Hello") }; // ge�ersiz: derleme hatas� 

static_cast ayr�ca (bilerek) C tarz� d�n���mlerden daha g��s�z olup, const'u yanl��l�kla kald�ramaz veya ama�lamad���n�z di�er i�lemleri
ger�ekle�tiremezsiniz.

                    int main()
                    {
                        const int x{ 5 };
                        int& ref{ static_cast<int&>(x) }; // ge�ersiz: derleme hatas� �retecek
                        ref = 6;

                        return 0;
                    }

*** BEST -> `static_cast`'i, bir de�eri bir t�rden ba�ka bir t�re d�n��t�rmeniz gerekti�inde tercih edin.

static_cast kullanarak daraltma d�n���mlerini a��k�a belirtin.
--------------------------------------------------------------

Derleyiciler, potansiyel olarak g�vensiz (daraltma) kas�ts�z t�r d�n���mleri ger�ekle�tirildi�inde genellikle uyar� mesajlar� verirler. 
�rne�in, a�a��daki program� d���n�n:

                    int i { 48 };
                    char ch = i; // implicit narrowing conversion

Bir tamsay�y� (2 veya 4 byte) bir char'a (1 byte) d�n��t�rmek potansiyel olarak g�vensizdir (��nk� derleyici, tamsay� de�erinin char'�n aral���n� 
a��p a�mayaca��n� bilemez), bu nedenle derleyici genellikle bir uyar� mesaj� verir. E�er liste ba�latma kullan�rsak, derleyici bir hata �retecektir.

Bunu a�mak i�in, tamsay�m�z� a��k�a bir char'a d�n��t�rmek i�in bir static_cast kullanabiliriz:

                    int i { 48 };

                    // int'ten char'a a��k�a d�n���m, b�ylece bir char de�i�kenine atan�r
                    char ch { static_cast<char>(i) };

Bunu yapt���m�zda, derleyiciye bu d�n���m�n ama�land���n� ve sonu�lar� (�rne�in, bir char'�n aral���n� a�ma durumu) kabul etti�imizi a��k�a 
belirtiyoruz. Bu static_cast'in ��k��� char t�r�nde oldu�undan, de�i�ken ch'nin ba�lat�lmas� herhangi bir t�r uyumsuzlu�una neden olmaz ve 
dolay�s�yla uyar� veya hata olu�maz.

��te ba�ka bir �rnek, derleyicinin genellikle bir double'� int'e d�n��t�rmenin veri kayb�na neden olabilece�ini bildirece�i bir durum:

                    int i { 100 };
                    i = i / 2.5;

Derleyiciye bunu a��k�a yapmay� ama�lad���m�z� belirtmek i�in:
                
                    int i { 100 };
                    i = static_cast<int>(i / 2.5);

*/