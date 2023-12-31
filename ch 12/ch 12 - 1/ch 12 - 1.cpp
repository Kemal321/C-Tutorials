#include <iostream>

int main()
{

    
    return 0;
}
/*
                                                12.1 � Bile�ik Veri T�rlerine Giri�
                                                -----------------------------------


4.1 dersinde -- Temel veri t�rlerine giri�, C++'�n temel dil b�l�m� olarak sa�lad��� temel veri t�rlerini tan�tt�k.

Bu temel t�rleri �zellikle int veri t�r�n� �imdiye kadar programlar�m�zda s�k�a kullanm��t�k. Ve bu temel t�rler basit kullan�mlar i�in son derece
kullan��l� olsalar da, daha karma��k i�ler yapmaya ba�lad���m�zda t�m ihtiya�lar�m�z� kapsamazlar.

�rne�in, iki kesiri �arpmak i�in bir matematik program� yaz�yormu� gibi d���n�n. Program�n�zda bir kesiri nas�l temsil edersiniz? Muhtemelen bir
�ift tamsay� kullan�rd�n�z (pay i�in bir tane, payda i�in bir tane), �u �ekilde:

                    #include <iostream>

                    int main()
                    {
                        // �lk kesirimiz
                        int sayi1 {};
                        int payda1 {};

                        // �kinci kesirimiz
                        int sayi2 {};
                        int payda2 {};

                        // pay ve payda aras�ndaki slash'� (e�ik �izgi) kald�rmak i�in kullan�l�r
                        char yoket {};

                        // Kullan�c�dan ilk kesiri girmesini isteyen bir ��k��
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi1 >> yoket >> payda1;

                        // Kullan�c�dan ikinci kesiri girmesini isteyen bir ��k��
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi2 >> yoket >> payda2;

                        // �ki kesirin �arp�m�n� hesaplay�p ekrana yazd�ran bir ��k��
                        std::cout << "�ki kesirin �arp�m�: "
                            << sayi1 * sayi2 << '/' << payda1 * payda2 << '\n';

                        return 0;
                    }
                    ��kt�s�:
                    Bir kesir girin: 1/2
                    Bir kesir girin: 3/4
                    �ki kesirin �arp�m�: 3/8

Bu program �al��sa da, �zerinde iyile�tirmeler yapmam�z gereken baz� zorluklar� ortaya ��kar�r. �lk olarak, her �ift tamsay� aras�nda sadece 
gev�ek bir ba�lant� vard�r -- yorumlar ve kod i�inde nas�l kullan�ld�klar� ba�lam� d���nda, her pay ve payda �iftinin ili�kili oldu�una dair
pek bir �ey yoktur. �kinci olarak, DRY (kendini tekrar etme) ilkesini izleme konusunda, bir fonksiyon olu�turmal�y�z ki bu fonksiyon kullan�c�n�n
bir kesiri girmesini ele als�n (ve baz� hata i�leme i�lemleri de i�ersin). Ancak, fonksiyonlar yaln�zca tek bir de�er d�nd�rebilir, peki payy� ve
payday� �a��ran yere nas�l geri d�nd�rebiliriz?

�imdi ba�ka bir durumu d���n�n; �al��an kimliklerini tutan bir program yazman�z gerekiyor. Bunun i�in nas�l bir �ey denersiniz? Belki de ��yle 
bir �ey denersiniz:

                    int main()
                    {
                        int id1 { 42 };
                        int id2 { 57 };
                        int id3 { 162 };
                        // ave b�ylece devam edersiniz
                    }

Ancak, 100 �al��an�n�z olsayd� ne olurdu? �lk olarak, 100 de�i�ken ad�n� yazman�z gerekecekti. Ve e�er hepsini yazd�rmam�z veya bir i�leme
ge�irmemiz gerekiyorsa? Bu durumda �ok fazla yaz� yazmak zorunda kal�rd�k. Bu basit�e �l�eklenemez.

A��k�a temel veri tipleri bizi sadece belirli bir noktaya kadar g�t�recektir.

compound data types - Bile�ik veri t�rleri
------------------------------------------
Neyse ki, C++, bile�ik veri tipleri ad� verilen ikinci bir veri tipi k�mesini destekler. Bile�ik veri tipleri, temel veri tiplerinden (veya di�er
bile�ik veri tiplerinden) olu�turulabilen veri tipleridir. Her bile�ik veri tipinin kendi benzersiz �zellikleri vard�r.

Bu b�l�mde ve gelecekteki b�l�mlerde g�sterece�imiz gibi, bile�ik veri tiplerini yukar�da sundu�umuz t�m zorluklar� zarif bir �ekilde ��zmek i�in
kullanabiliriz.

C++ a�a��daki bile�ik t�rlerini destekler:

-Functions
-Arrays
-Pointer types:
   -Pointer to object
   -Pointer to function
-Pointer to member types:
   -Pointer to data member
   -Pointer to member function
-Reference types:
   -L-value references
   -R-value references
-Enumerated types:
   -Unscoped enumerations
   -Scoped enumerations
-Class types:
   -Structs
   -Classes
   -Unions

Zaten d�zenli olarak bir bile�ik t�r� kullan�yorsunuz: Fonksiyonlar. �rne�in �u fonksiyonu g�z �n�nde bulundurun:

                    void doSomething(int x, double y)
                    {
                    }

12.2 � De�er Kategorileri (L-de�erleri ve R-de�erleri)
------------------------------------------------------
1.10 dersinde -- �fadelerin Tan�t�m�, bir ifadeyi "birle�ik say�lar, de�i�kenler, operat�rler ve tek bir de�er �retebilmek 
i�in �al��t�r�labilir fonksiyon �a�r�lar�n�n bir kombinasyonu" olarak tan�mlam��t�k.

                    #include <iostream>

                    int main()
                    {
                        std::cout << 2 + 3 << '\n'; // 2 + 3 ifadesi 5 de�erini �retir

                        return 0;
                    }

Yukar�daki ifade de 2 + 3 ifadesi 5 de�erini �retir ve sonras�nda konsola yazd�r�r.ayr�ca ifadelerin, ifadeden daha uzun �m�rl� yan etkiler 
�retebilece�ini de belirttik:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        ++x; // Bu ifadenin yan etkisi x in artt�r�lmas�d�r
                        std::cout << x << '\n'; // Burada 6 yazar

                        return 0;
                    }


Yukar�daki programda, ifade ++x ifadesi x'in de�erini art�r�r ve bu de�er, ifadenin de�erlendirmesi tamamland�ktan sonra bile de�i�mi� olarak 
kal�r.

De�er �retmenin ve yan etkilere neden olman�n yan� s�ra, ifadeler bir �ey daha yapabilir: nesneleri veya fonksiyonlar� de�erlendirebilirler.


�fadelerin �zellikleri
----------------------

�fadelerin nas�l de�erlendirilmesi gerekti�ini ve nerede kullan�labileceklerini belirlemek i�in C++'taki t�m ifadelerin iki �zelli�i vard�r: 
bir t�r (type) ve bir de�er kategorisi (value category).

�fadelerin T�r�
---------------

Bir ifadenin t�r�, de�erlendirilen ifadeden elde edilen de�erin, nesnenin veya i�levin t�r�ne e�de�erdir. �rne�in:
                    int main()
                    {
                        auto v1 { 12 / 4 }; // int / int => int
                        auto v2 { 12.0 / 4 }; // double / int => double

                        return 0;
                    }


v1 i�in derleyici (derleme zaman�nda), iki int operat�r� ile yap�lan bir b�lmenin bir int sonucu �retece�ini belirleyecektir, bu nedenle bu 
ifadenin t�r� int'tir. T�r ��kar�m� yoluyla, int daha sonra v1'in t�r� olarak kullan�lacakt�r.

v2 i�in derleyici (derleme zaman�nda), bir double operat�r� ve bir int operat�r� ile yap�lan bir b�lmenin bir double sonu� �retece�ini 
belirleyecektir. Aritmetik operat�rlerin e�le�en t�rlerde operandlara ihtiyac� oldu�unu unutmay�n, bu nedenle bu durumda int operat�r�
double'a d�n��t�r�l�r ve bir kayan nokta b�lme i�lemi ger�ekle�tirilir. Bu nedenle bu ifadenin t�r� double'dir.

Derleyici, bir ifadenin t�r�n� kullanarak bir ifadenin belirli bir ba�lamda ge�erli olup olmad���n� belirleyebilir. �rne�in:

                    #include <iostream>

                    void print(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        print("foo"); // hata: print() bir int arg�man bekliyordu, biz bir string literal i g�ndermeye �al��t�k

                        return 0;
                    }


Yukar�daki programda, print(int) fonksiyonu bir int parametresi bekliyor. Ancak, ileti�imde bulundu�umuz ifadenin t�r� (string literal
"foo") e�le�miyor ve herhangi bir d�n���m bulunam�yor. Bu nedenle bir derleme hatas� meydana gelir.

Bir ifadenin t�r�, derleme zaman�nda belirlenebilmelidir (aksi takdirde t�r kontrol� ve t�r ��kar�m� �al��maz) - ancak bir ifadenin de�eri, 
ifade constexpr ise derleme zaman�nda veya de�ilse �al��ma zaman�nda belirlenebilir.

Bir ifadenin de�er kategorisi
------------------------------

�imdi a�a��daki program� d���n�n:

                    int main()
                    {
                        int x{};

                        x = 5; // ge�erli: x e 5 de�erini atayabiliriz
                        5 = x; // hata: x in de�erini 5 e atayamay�z

                        return 0;
                    }


Bir atama ifadesine hangi taraf�n ge�erli oldu�unu (de�i�ken x'e de�eri 5 atama) ve hangisinin ge�erli olmad���n� (x'in de�erini 5'in kendi 
anlam�na atamak ne anlama gelir?) belirlemek i�in derleyici nas�l bilir?

Cevap, ifadelerin ikinci �zelli�inde yatar: de�er kategorisi. Bir ifadenin (veya alt ifadenin) de�er kategorisi, bir ifadenin bir de�ere, 
bir fonksiyona veya bir nesneye ��z�n�p ��z�nmedi�ini g�sterir.

C++11 �ncesinde, yaln�zca iki olas� de�er kategorisi vard�: lvalue ve rvalue.

C++11'de, hareket semanti�ini ( move semantic ) desteklemek i�in �� ek de�er kategorisi (glvalue, prvalue ve xvalue) eklenmi�tir.

Lvalue ve rvalue ifadeleri
--------------------------

Lvalue (okunu�u "ell-value", "sol de�er ( left value )" veya "bulucu de�eri ( locater value )" i�in k�saltma, bazen "l-value" olarak yaz�l�r), 
tan�mlanabilir bir nesne veya i�levin (veya bit alan�n�n) de�erini d�nd�ren bir ifadedir.

kimlik( identity ) terimi  C++ standard�nda kullan�l�r, ancak iyi tan�mlanmam��t�r. Bir kimli�e sahip bir varl�k (�rne�in bir nesne veya fonksiyon),
genellikle varl���n adreslerini kar��la�t�rarak di�er benzer varl�klardan ay�rt edilebilir.

Kimli�e sahip varl�klar bir tan�mlay�c�, referans veya i�aret�i ( pointer ) arac�l���yla eri�ilebilir ve genellikle bir ifade veya
deyimden daha uzun bir �mre sahiptir.

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


Yukar�daki programda, x ifadesi bir lvalue ifadesidir ��nk� de�i�ken x'in de�erini de�erlendirir (ki bu bir tan�mlay�c�ya sahiptir).

Dilin i�ine sabitlerin tan�t�lmas�ndan bu yana, lvalues iki alt t�re ayr�lmaktad�r: de�i�tirilebilir bir lvalue, de�eri de�i�tirilebilen
bir lvalue'dir. De�i�tirilemez bir lvalue ise (��nk� lvalue const veya constexpr ise) de�eri de�i�tirilemeyen bir lvalue'dir.

                    int main()
                    {
                        int x{};
                        const double d{};
                        int y { x }; // x de�i�tirilebilir bir lvaluedir
                        const double e { d }; // d de�i�tirilemez bir lvaluedir

                        return 0;
                    }

Rvalue ("arr-value" olarak okunan, "right value"�n k�saltmas� ve bazen r-value olarak yaz�lan) bir ifade, bir lvalue olmayan bir ifadedir.
Rvalue ifadeler bir de�ere ��z�n�r. S�k�a kar��la��lan rvalue'ler aras�nda literaller bulunur (C tarz� dizge literalleri hari�, ��nk� bunlar
lvalue'dir) ve de�er ile d�nen fonksiyonlar�n ve operat�rlerin d�n�� de�erleri bulunur. Rvalue'lar tan�mlanabilir de�ildir (yani hemen
kullan�lmal�d�r) ve yaln�zca kullan�ld�klar� ifade kapsam�nda var olurlar.

                    int return5()
                    {
                        return 5;
                    }

                    int main()
                    {
                        int x{ 5 }; // 5 bir rvalue ifadesidir
                        const double d{ 1.2 }; // 1.2 bir rvalue ifadesidir

                        int y { x }; // x de�i�tirilebilir bir lvalue ifadesidir
                        const double e { d }; // d de�i�tirilemez bir lvalue ifadesidir
                        int z { return5() }; // return5(), sonu� de�eri ile d�nd�r�ld��� i�in bir rvalue ifadesidir

                        int w { x + 1 }; // x + 1 bir rvalue ifadesidir
                        int q { static_cast<int>(d) }; // d'yi int'e static_cast etmenin sonucu bir rvalue ifadesidir

                        return 0;
                    }

Belki de return5(), x + 1 ve static_cast<int>(d) ifadelerinin neden rvalue oldu�unu merak ediyorsunuz: cevap, bu ifadelerin tan�mlanabilir
nesneler olmayan ge�ici de�erler �retmesidir.

Ana �pucu

Lvalue ifadeler, tan�mlanabilir bir nesneye ��z�n�r.
Rvalue ifadeler, bir de�ere ��z�n�r.

�imdi x = 5'in neden ge�erli oldu�u ancak 5 = x'in neden ge�erli olmad��� sorusunu cevaplayabiliriz: atama i�lemi, ataman�n sol operand�n�n
de�i�tirilebilir bir lvalue ifadesi olmas�n� ve sa� operand�n bir rvalue ifadesi olmas�n� gerektirir. �kinci atama (5 = x) ba�ar�s�zd�r
��nk� sol operand ifadesi 5 bir lvalue de�ildir.

                    int main()
                    {
                        int x{};

                        // Atama i�lemi, sol operand�n de�i�tirilebilir bir lvalue ifadesi olmas�n� ve sa� operand�n bir rvalue ifadesi
                        olmas�n� gerektirir
                        x = 5; // ge�erli: x de�i�tirilebilir bir lvalue ifadesi ve 5 bir rvalue ifadesidir
                        5 = x; // hata: 5 bir rvalue ifadesi iken x de�i�tirilebilir bir lvalue ifadesidir

                        return 0;
                    }

��te lvalue ve rvalue ifadelerinin tam bir listesi https://en.cppreference.com/w/cpp/language/value_category . C++11'de rvalue'lar iki alt t�re 
ayr�lm��t�r: prvalue'lar ve xvalue'lar, bu nedenle burada bahsetti�imiz rvalue'lar, bu iki kategori toplam�n�n birle�imidir.

Tavsiye -> E�er bir ifadenin bir lvalue mi yoksa rvalue mi oldu�undan emin de�ilseniz, operator& kullanarak onun adresini almaya �al���n. 
           ��nk� operator&, operand�n�n bir lvalue olmas�n� gerektirir. E�er &(ifade); derlemesi ba�ar�l� oluyorsa, ifade bir lvalue olmal�d�r:

                    int foo()
                    {
                        return 5;
                    }

                    int main()
                    {
                        int x { 5 };
                        &x; // derlenebilir: x bir lvalue ifadesidir
                        // &5; // derlenmez: 5 bir rvalue ifadesidir
                        // &foo(); // derlenmez: foo() bir rvalue ifadesidir
                    }

Ana �pucu

Bir C tarz� string literali, C tarz� stringler (ki bunlar C tarz� arraylerdir) bir i�aret�iye d�n��mesinden dolay� bir lvalue'dir. D�n���m s�reci,
arrayin bir lvalue olmas� durumunda �al���r (ve bu nedenle i�aret�ide depolanabilecek bir adresi vard�r). C++ bunu geriye uyumluluk i�in miras
alm��t�r.

Lvalue'dan rvalue'ye d�n���m
----------------------------
Bu �rne�e tekrar bakal�m:

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


E�er x, de�i�ken x'e de�eri olan bir lvalue ifadesiyse, y neden de�eri 5 olur?

Cevap, lvalue ifadelerinin, bir rvalue beklenirken ancak bir lvalue sa�land���nda otomatik olarak rvalue ifadelere d�n��t�r�lmesidir. 
Bir int de�i�keninin ba�lat�c�s� bir rvalue ifadesi olmas� beklenir. Bu nedenle, lvalue ifadesi x, bir lvalue'den rvalue'ye d�n���m ge�irir,
bu da de�eri 5 olan bir de�ere ��z�n�r ve ard�ndan y'yi ba�latmak i�in kullan�l�r.

Yukar�da belirtildi�i gibi atama operat�r�n�n sa� operand�n�n bir rvalue ifadesi olmas�n� bekledik, peki neden bu t�r kod i�e yar�yor?

                    int main()
                    {
                        int x{ 1 };
                        int y{ 2 };

                        x = y; // y de�i�tirilebilir bir lvalue dir, bir rvalue de�il, Ama bu ge�erlidir

                        return 0;
                    }

Bu durumda, y bir lvalue ifadesidir, ancak bir lvalue-to-rvalue d�n���m�ne u�rar, bu da y'nin de�erini (2) ��z�nmesine yol a�ar, ard�ndan bu 
de�er x'e atan�r.

�imdi bu �rne�i d���nelim:

                    int main()
                    {
                        int x { 2 };

                        x = x + 1;

                        return 0;
                    }

Bu ifadede, de�i�ken x iki farkl� ba�lamda kullan�lmaktad�r. Atama operat�r�n�n sol taraf�nda, x de�i�ken x de�eri olan bir lvalue ifadesidir.
Atama operat�r�n�n sa��ndaysa, x + 1, de�eri 3 olan bir rvalue ifadesine ��z�nen bir ifadedir.

�imdi lvalue'lar� ele ald���m�za g�re, ilk bile�ik t�r�m�ze gelebiliriz: lvalue referans�.

Ana �pucu

Lvalue ve rvalue ifadelerini tan�mlamak i�in bir kural:

Lvalue ifadeler, ifade sona erdikten sonra varl���n� s�rd�rebilen de�i�kenlere veya di�er tan�mlanabilir nesnelere ��z�nenlerdir.
Rvalue ifadeler, ifade sona erdikten sonra at�lacak olan literalleri veya fonksiyonlar/operat�rler taraf�ndan d�nd�r�len de�erleri ��z�nenlerdir.

12.3 � Lvalue references
------------------------

C++ dilinde, bir referans mevcut bir nesnenin takma ad�d�r. Bir referans bir kez tan�mland���nda, referans �zerinde yap�lan herhangi bir i�lem,
referans yap�lan nesneye uygulan�r.

Kilit nokta; Bir referans, temelde �zerine referans yap�lan nesne ile �zde�tir.


Bu, bir referans� �zerine referans yap�lan nesneyi okumak veya de�i�tirmek i�in kullanabilece�imiz anlam�na gelir. Ba�ta referanslar sa�ma,
gereksiz veya gereksiz gibi g�r�nebilir, ancak C++'ta referanslar her yerde kullan�l�r (bunu birka� derste g�rece�iz).

Ayr�ca, fonksiyonlara referanslar da olu�turabilirsiniz, ancak bu daha az s�k yap�l�r.

Modern C++, iki t�r referans i�erir: lvalue referanslar� ve rvalue referanslar�. Bu b�l�mde, lvalue referanslar�n� tart��aca��z.

Lvalue referans t�rleri
-----------------------
Bir lvalue referans� (genellikle C++11'den �nce yaln�zca bir t�rde referans oldu�u i�in sadece referans olarak adland�r�l�r), mevcut bir lvalue
(�rne�in bir de�i�ken) i�in bir takma ad olarak hareket eder.

Bir lvalue referans t�r�n� bildirmek i�in, t�r bildiriminde bir ampersand (&) kullan�r�z:

                    int      // normal bir int t�r�
                    int&     // bir int nesnesine yap�lan bir lvalue referans
                    double&  // bir double nesnesine yap�lan bir lvalue referans


Lvalue referans de�i�kenleri
----------------------------
Lvalue referans t�r� ile yapabilece�imiz �eylerden biri, bir lvalue referans de�i�keni olu�turmakt�r. Bir lvalue referans de�i�keni, 
genellikle ba�ka bir de�i�kenin referans� olarak hareket eden bir de�i�kendir.

Bir lvalue referans de�i�keni olu�turmak i�in, basit�e bir de�i�keni bir lvalue referans t�r� ile tan�mlar�z:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };    // x, normal bir tamsay� de�i�kenidir
                        int& ref { x }; // ref, �imdi de�i�ken x i�in bir takma ad olarak kullan�labilen bir lvalue referans de�i�kenidir

                        std::cout << x << '\n';  // x'in de�erini yazd�r (5)
                        std::cout << ref << '\n'; // ref �zerinden x'in de�erini yazd�r (5)

                        return 0;
                    }

Yukar�daki �rnekte, int& t�r� ref'i bir int'e referans olan bir lvalue referans olarak tan�mlar�z, ard�ndan lvalue ifadesini x ile ba�lat�r�z.
Bundan sonra, ref ve x e�anlaml� olarak kullan�labilir. Bu program �u �ekilde ��kt� verir:

                    5
                    5

Derleyicinin bak�� a��s�ndan, ampersand'�n tip ad�na (int& ref) m� yoksa de�i�ken ad�na (int &ref) "ba�l�" olmas� �nemli de�ildir ve se�im tarza
ba�l�d�r. Modern C++ programc�lar�, referans�n tip bilgisinin bir par�as� oldu�unu, tan�mlanan de�i�kenin ad� olmad���n� daha a��k bir �ekilde
ifade etmek i�in genellikle ampersand'� tipin yan�na koymay� tercih eder.

*** BEST -> Bir referans tan�mlarken, ampersand'� referans de�i�keninin ad�n�n yan�na de�il, tipin yan�na koymak en iyisidir.


De�erleri bir lvalue referans �zerinden de�i�tirme
--------------------------------------------------
Yukar�daki �rnekte, bir referans� �zerine referans yap�lan nesnenin de�erini okumak i�in kullanabilece�imizi g�sterdik. Ayn� zamanda bir referans�
kullanarak �zerine referans yap�lan nesnenin de�erini de�i�tirebiliriz:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsay� de�i�keni
                        int& ref { x }; // ref, �imdi de�i�ken x i�in bir takma ad

                        std::cout << x << ref << '\n'; // 55 yazd�r

                        x = 6; // x'in de�eri �imdi 6

                        std::cout << x << ref << '\n'; // 66 yazd�r

                        ref = 7; // �zerine referans yap�lan nesne (x) �imdi de�eri 7

                        std::cout << x << ref << '\n'; // 77 yazd�r

                        return 0;
                    }
                    ��kt�:
                    55
                    66
                    77

Yukar�daki �rnekte, ref x i�in bir takma ad oldu�undan dolay� x'in de�erini ya x �zerinden ya da ref �zerinden de�i�tirebiliyoruz.

Lvalue referanslar�n�n ba�lat�lmas�
-----------------------------------

Sabitler gibi, t�m referanslar ba�lat�lmal�d�r.

                    int main()
                    {
                        int& invalidRef;   // hata: referanslar ba�lat�lmal�d�r

                        int x { 5 };
                        int& ref { x }; // tamam: int referans�, int de�i�kenine ba�lan�r

                        return 0;
                    }


Bir referans, bir nesne (veya fonksiyon) ile ba�lat�ld���nda, o referans�n o nesneye (veya fonksiyona) ba�land���n� s�yleriz. Bu t�r bir referans�n
ba�lanma s�recine referans ba�lama denir. Referans yap�lan nesne (veya fonksiyon) bazen referansta bulunan olarak adland�r�l�r.

Lvalue referanslar�, de�i�tirilebilir bir lvalue'a ba�lanmal�d�r.
                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // ge�erli: de�i�tirilebilir bir lvalue'a ba�lanan bir lvalue referans�

                        const int y { 5 };
                        int& invalidRef { y };  // ge�ersiz: de�i�tirilemez bir lvalue'a ba�lanamaz
                        int& invalidRef2 { 0 }; // ge�ersiz: bir rvalue'a ba�lanamaz

                        return 0;
                    }

Lvalue referanslar�, de�i�tirilemez lvalue'lara veya rvalue'lara ba�lanamaz (aksi takdirde referans arac�l���yla bu de�erleri de�i�tirebilir ve 
bu da const durumlar�na ayk�r� olurdu). Bu nedenle, lvalue referanslar� zaman zaman lvalue referanslar�na non-const (bazen non-const referans 
olarak k�salt�l�r) olarak adland�r�l�r.

�o�u durumda, referans�n t�r�, referansta bulunan nesnenin t�r� ile e�le�melidir (bu kural�n baz� istisnalar� vard�r, bunlar� miras konusunu
ele ald���m�zda tart��aca��z):

                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // tamam: int referans�, int de�i�kenine ba�lan�r

                        double y { 6.0 };
                        int& invalidRef { y }; // ge�ersiz; int referans�, double de�i�kenine ba�lanamaz
                        double& invalidRef2 { x }; // ge�ersiz: double referans�, int de�i�kenine ba�lanamaz

                        return 0;
                    }

Lvalue referanslar�ndan void'a izin verilmez (bu ne anlama gelir ki?).

Referanslar yeniden yerle�tirilemez (ba�ka bir nesneyi i�aret etmek �zere de�i�tirilemez)
------------------------------------------------------------------------------------------
C++'ta bir referans bir kez ba�lat�ld�ktan sonra yeniden yerle�tirilemez, yani ba�ka bir nesneye referans yapacak �ekilde de�i�tirilemez.

Yeni C++ programc�lar� genellikle referans� ba�ka bir de�i�kenle yer de�i�tirmek i�in atama kullanarak yeniden yerle�tirmeye �al���rlar. 
Bu derlenir ve �al���r ancak beklenen �ekilde i�lev g�stermez. A�a��daki program� d���n�n:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        int y { 6 };

                        int& ref { x }; // ref, �imdi x i�in bir takma ad

                        ref = y; // x'in (ref taraf�ndan referans yap�lan nesnenin) de�erini 6 (y'nin de�eri) olarak atar
                        // Yukar�daki sat�r, ref'i y de�i�kenine referans yapacak �ekilde DE���T�RMEZ!

                        std::cout << x << '\n'; // kullan�c� bunun 5'i yazd�rmas�n� bekliyor

                        return 0;
                    }
                    ��kt�:
                    6

Bir referans bir ifadede de�erlendirildi�inde, referans yapt��� nesneye ��z�l�r. Bu nedenle, ref = y, ref'i �imdi y'ye referans yapacak �ekilde
de�i�tirmez. Tam tersine, ��nk� ref x i�in bir takma ad, ifade, x = y �eklinde yaz�lm�� gibi de�erlendirilir -- ve ��nk� y'nin de�eri 6 ise,
x'e de�er 6 atan�r.

Lvalue reference kapsam and s�re
--------------------------------

Lvalue referans de�i�kenleri, normal de�i�kenlerin uygulad��� kapsama ve s�re kurallar�n� takip eder:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsay�
                        int& ref { x }; // de�i�kenin de�erine referans

                        return 0;
                    } // x ve ref burada sona erer

Referanslar ve referans yap�lan nesneler ba��ms�z �m�rlere sahiptir.
--------------------------------------------------------------------
Bir istisna d���nda (bunu bir sonraki derste ele alaca��z), bir referans�n �mr� ve referans yapt��� nesnenin �mr� ba��ms�zd�r. 
Ba�ka bir deyi�le, her ikisi de a�a��daki ifadeler do�rudur:

    1. Bir referans, ona referans yap�lan nesneden �nce yok edilebilir.
    2. Referans yap�lan nesne, referanstan �nce yok edilebilir.

Bir referans, referanstan �nce yok edildi�inde, referans yap�lan nesneyi etkilemez. A�a��daki program bunu g�stermektedir:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };

                        {
                            int& ref { x };   // ref, x'e referans yapan bir referanst�r
                            std::cout << ref << '\n'; // ref'in de�erini (5) yazd�r�r
                        } // ref burada yok edildi -- x bunun fark�nda de�il

                        std::cout << x << '\n'; // x'in de�erini (5) yazd�r�r

                        return 0;
                    } // x burada yok edildi
                    ��kt�:
                    5
                    5

"ref" �ld���nde, de�i�ken x normal �ekilde devam eder, ne�e i�inde, ona yap�lan bir referans�n yok edildi�inden habersiz.

As�l� referanslar
-----------------

Bir nesneye yap�lan bir referans�n, referans�n kendisinden �nce yok edildi�i durumda, referans art�k var olmayan bir nesneye i�aret eder durumda
kal�r. B�yle bir referansa "as�l� referans" denir. Bir as�l� referansa eri�mek, tan�ms�z davran��a yol a�ar.

As�l� referanslardan ka��nmak olduk�a basittir, ancak bunun pratikte nas�l ger�ekle�ebilece�ini 12.12 dersinde g�sterece�iz

Referanslar nesne de�ildir
--------------------------

Belki de �a��rt�c� bir �ekilde, C++ dilinde referanslar nesneler de�ildir. Bir referans�n var olmas� veya depolama alan�n� kaplamas� gerekmez.
M�mk�nse, derleyici, bir referans�n t�m �rneklerini referans yapan nesneyle de�i�tirerek referanslar� optimize etme e�ilimindedir. Ancak bu her 
zaman m�mk�n olmayabilir ve b�yle durumlarda referanslar depolama alan� gerektirebilir.

Bu ayn� zamanda "referans de�i�keni" teriminin biraz yan�lt�c� oldu�u anlam�na gelir, ��nk� de�i�kenler ad� olan nesnelerdir ve referanslar 
nesneler de�ildir.

��nk� referanslar nesneler de�il, ba�ka bir nesnenin ad� olan referanslar, nesne gereken herhangi bir yerde kullan�lamaz (�rne�in, bir referansa 
referans olamazs�n�z, ��nk� bir lvalue referans� tan�mlanabilir bir nesneye referans yapmal�d�r). Bir nesne veya tekrar yerle�tirilebilen bir 
referans gerekti�inde, std::reference_wrapper (ki bunu 23.3 dersinde ele alaca��z - Birle�tirme) bir ��z�m sunar.

Bir kenara not olarak...

A�a��daki de�i�kenleri d���n�n:

                    int var{};
                    int& ref1{ var };  // var'a ba�l� bir lvalue referans�
                    int& ref2{ ref1 }; // var'a ba�l� bir lvalue referans�

��nk� ref2 (bir referans) ref1 (bir referans) ile ba�lat�lm��t�r, ref2'nin bir referans�n referans� oldu�unu d���nebilirsiniz. Ancak �yle de�il.
ref1, var'a referans oldu�undan, bir ifadede (�rne�in bir ba�lat�c�da) kullan�ld���nda, ref1 var'a de�erlendirilir. Bu nedenle ref2, sadece var'a
ba�l� normal bir lvalue referans�d�r (t�r� int& olarak belirtilmi�tir).

Bir referans�n referans�na (bir int'e) sahip olmak i�in int&& syntax'� kullan�lmal�d�r - ancak C++, referanslar�n referans�n� desteklemedi�i i�in
bu syntax C++11'de bir sa� taraf de�eri referans�n� g�stermek i�in kullan�lm��t�r (ki bunu 22.2 dersinde ele al�yoruz - R de�eri referanslar�).

ref2'nin ref1 ile ba�lat�lmas�ndan dolay� ref2'nin bir referans�n referans� gibi alg�lanabilece�i ancak bu durumun ger�ekle�medi�i .
C++ dilinde referanslar�n referanslar�n� desteklemez. int&& syntax'� orijinalde bir referans�n referans�n� ifade ediyordu, ancak C++11'de
bu syntax, sa� taraf de�eri referans�n� (rvalue reference) ifade etmek i�in kullan�lmaya ba�land�.

12.4 - Lvalue referanslar�n� const lar ile kullan�m�
----------------------------------------------------
                    int main()
                    {
                        const int x{5};    // x, de�i�tirilemez (const) bir lvalue'dir
                        int& ref{x};       // hata: ref, de�i�tirilemez lvalue'a ba�lanamaz

                        return 0;
                    }

Bu durum, const bir de�i�keni (x) de�i�tirmemize izin verecek bir const olmayan referans (ref) �zerinden de�i�tirmemize izin vermemek amac�yla 
engellenmi�tir.

Ancak e�er bir const de�i�kene bir referans olu�turmak istiyorsak, normal bir lvalue referans� (const olmayan bir de�ere) yeterli olmayacakt�r.

Bir lvalue referans�n�n deklarasyonunda const anahtar kelimesini kullanarak, referans�n i�aret etti�i nesneyi const olarak ele almas�n� sa�lar�z.
Bu t�r bir referans, bir const de�ere sahip bir lvalue referans� olarak adland�r�l�r (bazen bir const referans� veya sadece const olarak da 
adland�r�l�r). Lvalue references to const, de�i�tirilemez lvalue'lara ba�lanabilir:

                    int main()
                    {
                        const int x{5};        // x, de�i�tirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const de�ere sahip bir lvalue referans�d�r

                        return 0;
                    }

��nk� lvalue referanslar�na const, �zerine referans yap�lan nesneyi const olarak ele ald�klar� i�in, referans yap�lan de�eri de�i�tirmek yerine 
sadece eri�mek i�in kullan�labilirler:

                    #include <iostream>

                    int main()
                    {
                        const int x{5};        // x, de�i�tirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const de�ere sahip bir lvalue referans�d�r

                        std::cout << ref << '\n'; // uygun: const nesneye eri�ebiliriz
                        ref = 6;                  // hata: const bir referans arac�l���yla bir nesneyi de�i�tiremeyiz

                        return 0;
                    }

Const ile ba�lat�lm��, de�i�tirilebilir bir lvalue referans�
------------------------------------------------------------

Lvalue referanslar� const ile modifiable (de�i�tirilebilir) lvaluelara ba�lanabilir. Bu durumda, referans arac�l���yla eri�ilen nesne const
olarak i�lenir (ancak temeldeki nesne const olmasa bile):

                    #include <iostream>

                    int main()
                    {
                        int x{5};               // x, de�i�tirilebilir bir lvalue'dir
                        const int& ref{x};      // tamam: de�i�tirilebilir bir lvalue'a bir const referans ba�layabiliriz

                        std::cout << ref << '\n'; // tamam: nesneye const referans arac�l���yla eri�ebiliriz
                        // ref = 7;               // hata: bir const referans arac�l���yla bir nesneyi de�i�tiremeyiz

                        x = 6;                   // tamam: x, de�i�tirilebilir bir lvalue'dir, hala orijinal tan�mlay�c� arac�l���yla
                                                    de�i�tirebiliriz

                        return 0;
                    }

Yukar�daki programda, const referans� ref'i de�i�tirilebilir lvalue x'e ba�lad�k. Ard�ndan ref'i kullanarak x'e eri�ebiliriz, ancak ref const
oldu�u i�in ref �zerinden x'in de�erini de�i�tiremeyiz. Ancak, x'in de�erini do�rudan (tan�mlay�c� x kullanarak) de�i�tirebiliriz.

*** BEST -> De�i�tirilmek istenen nesnenin modifikasyonu gerekmedi�i s�rece, const lvalue referanslar�n� lvalue referanslar�na tercih edin.

Const bir lvalue referans�n� rvalue ile ba�latma
------------------------------------------------
Belki de �a��rt�c� bir �ekilde, const lvalue referanslar� ayn� zamanda rvalue'larla da ba�lanabilir:

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // tamam: 5 bir rvalue'dir

                        std::cout << ref << '\n'; // 5'i yazd�r�r

                        return 0;
                    }

Bu durumda, ge�ici bir nesne olu�turulur ve rvalue ile ba�lat�l�r, ard�ndan const referans o ge�ici nesneye ba�lan�r.

Ge�ici bir nesne (bazen anonim nesne olarak da adland�r�l�r), bir ifade i�inde ge�ici olarak olu�turulan (ve sonra yok edilen) bir nesnedir.
Ge�ici nesnelerin hi�bir kapsam� yoktur (bu mant�kl�d�r, ��nk� kapsam bir tan�mlay�c�n�n �zelli�idir ve ge�ici nesnelerin bir tan�mlay�c�s�
yoktur). Bu, bir ge�ici nesnenin sadece olu�turuldu�u noktada do�rudan kullan�labilece�i anlam�na gelir, ��nk� bu noktadan �tesine referans
olu�turman�n bir yolu yoktur.

Const referanslar ge�ici nesnelere ba�land���nda, ge�ici nesnenin �mr� uzat�l�r
-------------------------------------------------------------------------------

Genellikle, ge�ici nesneler olu�turulduklar� ifadenin sonunda yok edilir.

Ancak yukar�daki �rnekte, rvalue 5'i tutmak i�in olu�turulan ge�ici nesnenin ref taraf�ndan ba�lat�lan ifadenin sonunda yok edilmesi durumunda
ne olaca��n� d���nelim. Referans ref, sallant�da (yok edilmi� bir nesneye referans) b�rak�l�r ve ref'e eri�meye �al��t���m�zda tan�ms�z davran��
elde ederiz.

Bu t�r durumlarda sallant� referanslar�ndan ka��nmak i�in C++'da �zel bir kural vard�r: Bir const lvalue referans� do�rudan bir ge�ici nesneye
ba�land���nda, ge�ici nesnenin �mr� referans�n �mr�yle e�le�ecek �ekilde uzat�l�r.

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // 5 de�erini tutan ge�ici nesnenin �mr�, ref ile e�le�ecek �ekilde uzat�l�r

                        std::cout << ref << '\n'; // Bu nedenle, burada g�venli bir �ekilde kullanabiliriz

                        return 0;
                    } // Hem ref hem de ge�ici nesne burada sona erer


Yukar�daki �rnekte, ref rvalue 5 ile ba�lat�ld���nda, bir ge�ici nesne olu�turulur ve ref bu ge�ici nesneye ba�lan�r. Ge�ici nesnenin �mr�,
ref'in �mr�yle e�le�ir. Bu nedenle, bir sonraki ifadede ref'in de�erini g�venli bir �ekilde yazd�rabiliriz. Ard�ndan, hem ref hem de ge�ici 
nesne, blo�un sonunda kapsam d���na ��k�p yok edilir.

Ana �pucu

- Lvalue referanslar� yaln�zca de�i�tirilebilir lvalue'lere ba�lanabilir.
- Const lvalue referanslar�, de�i�tirilebilir lvalue'lere, de�i�tirilemeyen lvalue'lere ve rvalue'lere ba�lanabilir. Bu, onlar� �ok daha 
  esnek bir referans t�r� yapar.


Constexpr lvalue referanslar
----------------------------

Referansa uyguland���nda, constexpr referans�n bu referans�n bir sabit ifadesinde kullan�lmas�na izin verir. Constexpr referanslar�n belirli
bir k�s�tlamas� vard�r: yaln�zca statik s�reye sahip nesnelere ba�lanabilirler (ya global ya da static yerel de�i�kenler). Bu, derleyicinin
statik nesnelerin bellekte hangi konumda olu�turulaca��n� bildi�i i�in o adresi derleme zaman�nda bir sabit olarak i�leyebilmesinden kaynaklan�r.

Constexpr referans, bir (non-static) yerel de�i�kene ba�lanamaz. Bu, yerel de�i�kenlerin adresinin, tan�mland�klar� fonksiyonun ger�ekten
�a�r�ld��� zamana kadar bilinmedi�i i�in ge�erlidir.

                    int g_x{5};

                    int main()
                    {
                        [[maybe_unused]] constexpr int& ref1{g_x}; // tamam, global de�i�kene ba�lanabilir

                        static int s_x{6};
                        [[maybe_unused]] constexpr int& ref2{s_x}; // tamam, static yerel de�i�kene ba�lanabilir

                        int x{6};
                        // [[maybe_unused]] constexpr int& ref3{x}; // derleme hatas�: non-static bir nesneye ba�lanamaz

                        return 0;
                    }

Bir const de�i�kenine bir constexpr referans tan�mlarken, hem referansa (constexpr, referansa uygulanan) hem de referans yap�lan tipe
(const, referans�n hedefledi�i tipe uygulanan) hem constexpr hem de const uygulamam�z gerekiyor.

                    int main()
                    {
                        static const int s_x { 6 }; // a const int
                        [[maybe_unused]] constexpr const int& ref2 { s_x }; // constexpr ve const ikiside gerekli

                        return 0;
                    }

Bu s�n�rlamalar g�z �n�ne al�nd���nda, constexpr referanslar� genellikle pek fazla kullan�lmaz.

12.5 � Sol de�er referans� arg�man olarak kullanma
--------------------------------------------------
Neden bir de�i�kenin kendisini kullanmak yerine bir de�i�ken i�in bir takma ad olu�turulsun ki?

Bu derste ve bundan sonraki derslerde bu konuyu a��klayaca��z. �lk olarak, biraz ba�lam. Daha �nceki 2.4 dersinde - Fonksiyon Parametreleri
ve Arg�manlar�na Giri�'te, de�erle ge�i�i tart��t�k; bir fonksiyona iletilen bir arg�man, fonksiyonun parametresine kopyalan�r:

                    #include <iostream>

                    void printDeger(int y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir

                    int main()
                    {
                        int x { 2 };

                        printDeger(x); // x, de�eri y parametresine (ucuz) aktar�l�r (kopyalan�r)

                        return 0;
                    }


Yukar�daki programda, printDeger(x) �a�r�ld���nda, x'in de�eri (2), parametre y i�ine kopyalan�r. Ard�ndan, fonksiyonun sonunda y nesnesi yok 
edilir.

Bu, fonksiyonu �a��rd���m�zda, arg�man�n de�erinden bir kopya olu�turdu�umuz ve ard�ndan k�sa bir s�re kullan�p yok etti�imiz anlam�na gelir!
Neyse ki, temel tiplerin kopyalanmas� ucuz oldu�undan, bu bir sorun te�kil etmez.

Baz� nesnelerin kopyalanmas� pahal� olabilir

Standart k�t�phanenin sa�lad��� �o�u t�r (�rne�in std::string) s�n�f t�rleridir. S�n�f t�rleri genellikle kopyalamak pahal�d�r. M�mk�nse,
�zellikle bu kopyalar� neredeyse hemen yok edece�imiz durumlarda, pahal� kopyalar�n gereksiz yarat�lmas�ndan ka��nmak istiyoruz.

Bu noktay� g�steren a�a��daki program� d���n�n:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir 

                    int main()
                    {
                        std::string x { "Hello, world!" }; // x bir std::string t�r�d�r

                        printValue(x); // x y parametresine de�er olarak ge�ildi ( pahal�d�r )

                        return 0;
                    }
                    ��kt�:
                    Hello, World!


Bu program bekledi�imiz gibi davran�yor gibi g�r�nse de, ayn� zamanda verimsizdir. �nceki �rnekle ayn� �ekilde, printValue() �a�r�ld���nda,
arg�man x printValue() parametresi y'e kopyalan�r. Ancak bu �rnekte, arg�man bir int yerine bir std::string'dir ve std::string, kopyalamas�
pahal� bir s�n�f t�r�d�r. Ve bu pahal� kopya, her printValue() �a�r�ld���nda yap�l�r!

Daha iyi yapabiliriz.

Referans ile arg�man aktarma
----------------------------
Bir fonksiyonu �a��r�rken arg�man�n pahal� bir kopyas�n� olu�turmaktan ka��nman�n bir yolu, de�er ile ge�i� yerine referans ile ge�i� kullanmakt�r.
Referans kullan�rken, bir fonksiyon parametresini normal bir t�r olarak de�il, bir referans t�r� olarak (veya sabit referans t�r� olarak)
tan�mlar�z. Fonksiyon �a�r�ld���nda, her referans parametresi uygun arg�mana ba�lan�r. Referans, arg�man i�in bir takma ad olarak hareket etti�i
i�in, arg�man�n bir kopyas� olu�turulmaz.

��te de�er ile ge�i� yerine referans ile ge�i� kullan�larak yukar�daki �rne�in ayn�s�:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string& y) // t�r std::string& olarak de�i�tirildi
                    {
                        std::cout << y << '\n';
                    } // y burada yok edildi

                    int main()
                    {
                        std::string x { "Hello, world!" };

                        printValue(x); // �imdi x de�eri y parametresine referans olarak ge�ildi ( aktar�ld� ) ( pahal� de�il )

                        return 0;
                    }


Bu program, t�r� std::string olan parametre y'nin std::string& (bir sol de�er referans�) olarak de�i�tirilmi� olan �ncekine benziyor. �imdi, 
printValue(x) �a�r�ld���nda, sol de�er referans parametresi y, arg�man x'e ba�lan�r. Bir referans� ba�lamak her zaman ucuzdur ve x'in bir kopyas�
yap�lmas�na gerek yoktur. Bir referans, referans edilen nesne i�in bir takma ad olarak hareket etti�i i�in, printValue() referans y'yi 
kulland���nda, ger�ek arg�man x'e eri�iyor (x'in bir kopyas� de�il).

Kilit nokta �udur ki; Referansa g�re aktarma, fonksiyon her �a�r�ld���nda bu arg�manlar�n kopyalar�n� olu�turmadan arg�manlar� bir fonksiyona
iletmemize olanak tan�r.

Referansa g�re ge�i�, bir arg�man�n de�erini de�i�tirmemize olanak tan�r

Bir nesne de�ere g�re iletildi�inde, i�lev parametresi arg�man�n bir kopyas�n� al�r. Bu, parametrenin de�erinde yap�lan herhangi bir de�i�ikli�in
arg�man�n kendisine de�il, arg�man�n kopyas�na yap�laca�� anlam�na gelir:

                    #include <iostream>

                    void addOne(int y) // y, x'in kopyas�d�r
                    {
                        ++y; // Buradaki de�i�im x'in kopyas�na olacakt�r, ger�ek x e de�il
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x de�i�tirilmedi

                        return 0;
                    }
Yukar�daki programda y de�er parametresi x'in kopyas� oldu�undan y'yi artt�rd���m�zda bu sadece y'yi etkiler. Bu program�n ��kt�s�:

                    value = 5
                    value = 5

Bununla birlikte, bir referans, referans verilen nesneyle ayn� �ekilde davrand���ndan, referansa g�re ge�i� kullan�ld���nda, referans
parametresinde yap�lan herhangi bir de�i�iklik ba��ms�z de�i�keni etkileyecektir:

                    #include <iostream>

                    void addOne(int& y) // y ger�ek x'e ba�l� ��nk� referans ediyor
                    {
                        ++y; // bu ger�ek x'i de�i�tirecek
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x de�i�ti

                        return 0;
                    }
                    ��kt�s�:
                    value = 5
                    value = 6


Yukar�daki �rnekte, x'in ba�lang��ta de�eri 5'tir. addOne(x) �a�r�ld���nda, referans parametresi y, arg�man x'e ba�lan�r. addOne() fonksiyonu
referans y'yi artt�rd���nda, asl�nda arg�man x'i 5'ten 6'ya artt�r�yor (x'in bir kopyas� de�il). Bu de�i�en de�er, addOne() i�lemi tamamland�ktan
sonra bile devam eder.

De�erleri const olmayanlara referansla iletmek, aktar�lan arg�manlar�n de�erini de�i�tiren fonksiyonlar yazmam�za olanak tan�r.

Fonksiyonlar�n iletilen arg�manlar�n de�erini de�i�tirebilme yetene�i olduk�a faydal� olabilir. Hayal edin ki bir canavar�n oyuncuya ba�ar�yla
sald�rd���n� belirleyen bir fonksiyon yazd�n�z. �yleyse, canavar oyuncunun sa�l���na bir miktar hasar vermelidir. E�er oyuncu nesnesini referans
olarak iletiyorsan�z, fonksiyon, iletilen ger�ek oyuncu nesnesinin sa�l���n� do�rudan de�i�tirebilir. E�er oyuncu nesnesini de�er olarak
iletiyorsan�z, yaln�zca bir kopyan�n sa�l���n� de�i�tirebilirsiniz ki bu pek faydal� de�ildir.


Referans ile ge�i�, yaln�zca de�i�tirilebilir sol de�er arg�manlar� kabul edebilir

��nk� bir referans, bir de�i�tirilebilir sol de�ere (temelde bir const olmayan de�i�ken) yaln�zca ba�lanabilir, bu nedenle referans ile ge�i�,
yaln�zca de�i�tirilebilir sol de�erlerle �al���r demektir. Pratikte, bu, referans ile ge�i�in const olmayanlara s�n�rl� faydas�n� �nemli �l��de
s�n�rlar, ��nk� const de�i�kenleri veya sabit ifadeleri iletimemiz m�mk�n de�ildir. �rne�in:

                    #include <iostream>

                    void printValue(int& y) // y sadece de�i�tirilebilir lvalue kabul eder
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir de�i�tirilebilir lvalue de�i�kendir

                        const int z { 5 };
                        printValue(z); // error: z bir de�i�tirilebilir lvalue de�i�ken de�ildir

                        printValue(5); // error: 5 bir rvalue dir

                        return 0;
                    }

Neyse ki bunu a�man�n kolay bir yolu var ve bunu bir sonraki derste tart��aca��z. Ayr�ca ne zaman de�ere g�re ge�ilece�ine ve ne zaman referansa 
g�re ge�ilece�ine de g�z ataca��z.

12.6 � Const sol de�er referans� ile ge�i�
------------------------------------------
Const olmayan bir referans�n aksine (yaln�zca de�i�tirilebilir sol de�erlere ba�lanabilirken), bir const referans, de�i�tirilebilir sol de�erlere,
de�i�tirilemez sol de�erlere ve sa� de�erlere ba�lanabilir. Bu nedenle, bir referans parametreyi const yaparsak, her t�rl� arg�mana ba�lanabilir 
hale gelecektir:

                    #include <iostream>

                    void printValue(const int& y) // �imdi y bir const referans
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir de�i�tirilebilir lvalue

                        const int z { 5 };
                        printValue(z); // ok: z bir de�i�tirilemez lvalue

                        printValue(5); // ok: 5 bir literal rvalue

                        return 0;
                    }

Const referans ile ge�i�, referans ile ge�i�in temel avantaj�n� (arg�man�n bir kopyas�n� olu�turmadan) sunarken, ayn� zamanda fonksiyonun 
referans yap�lan de�eri de�i�tiremeyece�ini garanti eder.

�rne�in, a�a��daki durum const oldu�u i�in izin verilmez:

                    void addOne(const int& ref)
                    {
                        ++ref; // �zin verilmemi�tir: Ref bir const ��nk�
                    }

�o�u durumda fonksiyonlar�m�z�n arg�manlar�n de�erini de�i�tirmesini istemeyiz.

*** BEST -> Aksini yapmak i�in �zel bir nedeniniz olmad�k�a (�rne�in, i�levin bir arg�man�n de�erini de�i�tirmesi gerekiyorsa), const referans� 
            ile ge�i�'i, const olmayan referans ile ge�i� yerine tercih edin.

Art�k sabit de�er referanslar�n�n de�erlere ba�lanmas�na izin vermenin motivasyonunu anlayabiliriz: bu yetenek olmasayd�, referans yoluyla ge�i�
kullanan i�levlere de�i�mez de�erleri (veya di�er de�erleri) aktarman�n bir yolu olmazd�!


De�er ile ge�i� ve referans ile ge�i�i kar��t�rma ( Birlikte kullanmak )
------------------------------------------------------------------------
�oklu parametreye sahip bir fonksiyon, her parametrenin ayr� ayr� de�er ile mi yoksa referans ile mi iletildi�ini belirleyebilir.

�rne�in:

                    #include <string>

                    void foo(int a, int& b, const std::string& c)
                    {
                    }

                    int main()
                    {
                        int x { 5 };
                        const std::string s { "Hello, world!" };

                        foo(5, x, s);

                        return 0;
                    }
Yukar�daki �rnekte, ilk arg�man de�ere g�re, ikincisi referansa g�re ve ���nc�s� const referans�na g�re iletilir.


(const) referans ile ge�i� ne zaman yap�lmal�d�r
------------------------------------------------
��nk� s�n�f t�rleri kopyalamak pahal� olabilir (bazen �nemli �l��de), genellikle s�n�f t�rleri arg�man�n pahal� bir kopyas�n� olu�turmaktan
ka��nmak i�in de�er yerine const referans ile iletilir. Temel tipler kopyalamak ucuz oldu�undan genellikle de�er ile iletilir.
*** BEST 
--------
�lke olarak, temel tipleri de�er ile, s�n�f (veya yap�) tiplerini ise const referans ile iletmek genellikle uygundur.

Di�er yayg�n tipleri de�er ile iletmek: numaraland�rma tipleri ve std::string_view.
Di�er yayg�n tipleri (const) referans ile iletmek: std::string, std::array ve std::vector.

Fonksiyon parametreleri i�in, �o�u durumda const std::string& yerine std::string_view'i tercih edin
---------------------------------------------------------------------------------------------------

Modern C++ i�inde s�k�a kar��la��lan bir soru: Bir string parametresine sahip bir fonksiyon yaz�l�rken, parametrenin t�r� const std::string& m�
yoksa std::string_view m� olmal�d�r?

�o�u durumda, std::string_view daha iyi bir tercih olacakt�r, ��nk� daha geni� bir arg�man t�r� yelpazesini verimli bir �ekilde i�leyebilir.

                    void doSomething(const std::string&);
                    void doSomething(std::string_view);   // �o�u durumda bunu tercih edin

const std::string& parametresini kullanman�n daha uygun olabilece�i birka� durum vard�r:

1 - E�er C++14 veya daha eski bir s�r�m kullan�yorsan�z, std::string_view mevcut de�ilse.

2 - E�er fonksiyonunuz, C tarz� bir diziyi veya std::string parametresi alan ba�ka bir fonksiyonu �a��rmas� gerekiyorsa, o zaman 
    const std::string& daha iyi bir se�enek olabilir, ��nk� std::string_view'�n null karakteri ile sona erdirilmi� (C tarz� dizi 
    i�levlerinin bekledi�i �ey) olmas� garanti edilmemi�tir ve std::string'e verimli bir �ekilde d�n��t�r�lmez.

std::string& yerine std::string_view (de�er olarak) kullanarak stringleri iletmeyi tercih edin, ancak fonksiyonunuzun C tarz� dizileri veya
std::string parametreleri gerektiren di�er fonksiyonlar� �a��rd��� durumlar hari�.

12.6 -> Geli�mi� geli�tiriciler i�in bir ka� not bulunmakta bunlar� 12 tamamen bitmesi ve di�er durumlarda inceleyece�im ��nk� �uan bakarak bir 
        �o�unu anlamayaca��z.
*/