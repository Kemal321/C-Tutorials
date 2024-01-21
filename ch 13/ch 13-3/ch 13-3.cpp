#include <iostream>

int main()
{
    return 0;
}
/*
13.5 � Structlara, memberlara ve member se�imine giri�
------------------------------------------------------
Programlama s�ras�nda bir�ok durumda, ilgi alan�n� temsil etmek i�in birden fazla de�i�kene ihtiya� duyar�z.
�nceki b�l�m�n giri�inde (12.1 -- Bile�ik veri t�rlerine giri�) tart��t���m�z gibi, bir kesirin pay� ve paydas� tek bir 
matematiksel nesneye ba�l�d�r.

Alternatif olarak, bir �irketteki �al��anlar hakk�nda bilgi saklamam�z gereken bir program yazmak isteyelim. �al��an�n ad�,unvan�,
ya��, �al��an kimli�i, y�netici kimli�i, �creti, do�um g�n�, i�e ba�lama tarihi vb. �zellikleri takip etmekle ilgilenebiliriz...

E�er bu t�m bilgileri takip etmek i�in ba��ms�z de�i�kenler kullan�rsak, bu �una benzer bir �ey olabilir:

 
                    std::string name;
                    std::string title;
                    int age;
                    int id;
                    int managerId;
                    double wage;
                    int birthdayYear;
                    int birthdayMonth;
                    int birthdayDay;
                    int hireYear;
                    int hireMonth;
                    int hireDay;
 
Ancak, bu yakla��mla bir dizi sorun var. �lk olarak, bu de�i�kenlerin ger�ekten ili�kili olup olmad��� hemen belli olmaz 
(yorumlar� okuman�z veya onlar�n ba�lamda nas�l kullan�ld���n� g�zlemlemeniz gerekir). �kinci olarak, �imdi y�netilmesi gereken
12 de�i�ken var. E�er bu �al��an� bir fonksiyona ge�mek istersek, 12 arg�man� (ve do�ru s�rayla) ge�memiz gerekir, bu da fonksiyon
prototiplerimizi ve fonksiyon �a�r�lar�m�z� kar��t�r�r. Ve bir fonksiyon sadece tek bir de�er d�nd�rebilir, o zaman bir fonksiyon 
nas�l bir �al��an� d�nd�r�r?

Ve birden fazla �al��ana ihtiyac�m�z olursa, her ek �al��an i�in 12 daha fazla de�i�ken tan�mlamam�z gerekir (her biri benzersiz
bir isim gerektirir)! Bu a��k�a hi� �l�eklenmiyor. Ger�ekten ihtiyac�m�z olan �ey, t�m bu ilgili veri par�alar�n� bir araya
getirmenin bir yoludur, b�ylece onlar� daha kolay y�netebiliriz.

Neyse ki, C++ bu t�r zorluklar� ��zmek i�in tasarlanm�� iki bile�ik t�rle birlikte gelir: Structlar (�imdi tan�taca��m�z) ve
s�n�flar (yak�nda ke�fedece�imiz). Bir Struct (structure k�saltmas�) bir program tan�ml� veri t�r�d�r (13.1 -- Program tan�ml�
(kullan�c� tan�ml�) t�rlerine giri�) ve bize birden �ok de�i�keni tek bir t�rde bir araya getirme olana�� sa�lar. Yak�nda
g�rece�iniz gibi, bu, ilgili de�i�ken setlerinin y�netimini �ok daha basit hale getirir!

Structlar� Tan�mlama
--------------------
Structlar bir program tan�ml� t�r oldu�u i�in, onu kullanmaya ba�lamadan �nce derleyiciye Struct t�r�m�z�n nas�l g�r�nd���n�
�ncelikle s�ylememiz gerekir. ��te basitle�tirilmi� bir �al��an i�in bir Struct tan�m�n�n bir �rne�i:

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };
 
Struct anahtar kelimesi, bir Struct tan�mlad���m�z� derleyiciye bildirmek i�in kullan�l�r, bunu Employee olarak adland�rd�k 
(��nk� program tan�ml� t�rler genellikle b�y�k harfle ba�layan isimlerle adland�r�l�r).

Sonra, bir �ift s�sl� parantez i�inde, her Employee nesnesinin i�erece�i de�i�kenleri tan�mlar�z. Bu �rnekte, olu�turdu�umuz her 
Employee 3 de�i�kene sahip olacak: bir int id, bir int age ve bir double wage. Struct'�n bir par�as� olan de�i�kenlere veri
memberlar� (veya member de�i�kenler) denir.

�pucu

G�nl�k dilde, bir member (�ye) bir gruba ait bir bireydir. �rne�in, basketbol tak�m�n�n bir member'i olabilirsiniz ve k�z 
karde�iniz koro member'i olabilir.

C++'da, bir member bir Struct'a (veya s�n�fa) ait bir de�i�ken, fonksiyon veya t�rd�r. T�m memberlar, Struct (veya s�n�f) tan�m� 
i�inde bildirilmelidir.

Gelecekteki derslerde member terimini �ok kullanaca��z, bu y�zden ne anlama geldi�ini unutmay�n.

Normal de�i�kenleri de�er ba�latmak i�in bo� bir set s�sl� parantez kullan�r�z, her member de�i�kenin ard�ndaki bo� s�sl� 
parantezler, bir Employee olu�turuldu�unda Employee i�indeki member de�i�kenlerin de�er ba�lat�ld���ndan emin olur.
Son olarak, tip tan�m�n� bir noktal� virg�lle bitiriyoruz.

Bir hat�rlatma olarak, Employee sadece bir tip tan�m�d�r - bu noktada asl�nda hi�bir nesne olu�turulmaz.

Struct nesneleri tan�mlama
--------------------------
Employee tipini kullanmak i�in, sadece Employee tipinde bir de�i�ken tan�mlar�z:
 
                Employee joe {}; // Employee tipidir, joe de�i�ken ad�d�r
 
Bu, joe ad�nda bir Employee tipinde de�i�ken tan�mlar. Kod �al��t�r�ld���nda, 3 veri member'ini i�eren bir Employee nesnesi 
�rneklendirilir. Bo� s�sl� parantezler, nesnemizin de�erle ba�lat�lmas�n� sa�lar.
Di�er her tipte oldu�u gibi, ayn� struct tipinde birden �ok de�i�ken tan�mlamak m�mk�nd�r:

                Employee joe {}; // Joe i�in bir Employee struct olu�tur
                Employee frank {}; // Frank i�in bir Employee struct olu�tur
 
memberlare eri�im
-----------------
A�a��daki �rne�i d���n�n:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};

                    return 0;
                }
 
Yukar�daki �rnekte, joe ad� t�m struct nesnesine (member de�i�kenleri i�erir) at�fta bulunur. Belirli bir member de�i�kenine
eri�mek i�in, struct de�i�ken ad� ve member ad� aras�nda member se�im operat�r�n� (operator.) kullan�r�z. �rne�in, 
Joe'nun ya� member'ine eri�mek i�in joe.age kullan�r�z.

Struct member de�i�kenleri normal de�i�kenler gibi �al���r, bu y�zden atama, aritmetik, kar��la�t�rma vb. normal i�lemleri yapmak
m�mk�nd�r...

                #include <iostream>

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};

                    joe.age = 32;  // member se�im operat�r�n� (.) kullanarak joe de�i�keninin age member'ini se�

                    std::cout << joe.age << '\n'; // joe'nun ya��n� yazd�r

                    return 0;
                }
                Bu, �unu yazd�r�r:
                32

Structlar�n en b�y�k avantajlar�ndan biri, her struct de�i�keni i�in yaln�zca bir yeni ad olu�turmam�z gerekti�idir
(member adlar� struct tipi tan�m�n�n bir par�as� olarak sabittir). A�a��daki �rnekte, iki Employee nesnesi �rneklendiriyoruz: 
joe ve frank.
 
                #include <iostream>

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};
                    joe.id = 14;
                    joe.age = 32;
                    joe.wage = 60000.0;

                    Employee frank {};
                    frank.id = 15;
                    frank.age = 28;
                    frank.wage = 45000.0;

                    int totalAge { joe.age + frank.age };

                    if (joe.wage > frank.wage)
                        std::cout << "Joe, Frank'ten daha fazla kazan�yor\n";
                    else if (joe.wage < frank.wage)
                        std::cout << "Joe, Frank'ten daha az kazan�yor\n";
                    else
                        std::cout << "Joe ve Frank ayn� miktarda kazan�yor\n";

                    // Frank terfi etti
                    frank.wage += 5000.0;

                    // Bug�n Joe'nun do�um g�n�
                    ++joe.age; // Joe'nun ya��n� 1 art�rmak i�in �n art�r�m� kullan

                    return 0;
                }
 
Yukar�daki �rnekte, hangi member de�i�kenlerin Joe'ya ait oldu�unu ve hangilerinin Frank'e ait oldu�unu anlamak �ok kolayd�r. Bu,
bireysel de�i�kenlerden �ok daha y�ksek bir organizasyon seviyesi sa�lar. Ayr�ca, Joe'nun ve Frank'in memberlar�nin ayn� adlara 
sahip olmas�, ayn� struct tipinde birden �ok de�i�keniniz oldu�unda tutarl�l�k sa�lar.

13.6 � Struct Toplu Ba�latma
----------------------------
�nceki derste (13.5 -- Struct'lara, �yelere ve �ye se�imine giri�), struct'lar� nas�l tan�mlayaca��m�z�, struct nesnelerini nas�l 
olu�turaca��m�z� ve �yelerine nas�l eri�ece�imizi konu�tuk. Bu derste, struct'lar�n nas�l ba�lat�ld���n� tart��aca��z.

Veri �yeleri varsay�lan olarak ba�lat�lmaz
------------------------------------------
Normal de�i�kenler gibi, veri �yeleri de varsay�lan olarak ba�lat�lmaz. A�a��daki struct'� d���n�n:

                #include <iostream>

                struct Employee
                {
                    int id; // not: burada bir ba�lat�c� yok
                    int age;
                    double wage;
                };

                int main()
                {
                    Employee joe; // not: burada da bir ba�lat�c� yok
                    std::cout << joe.id << '\n';

                    return 0;
                }
 
Herhangi bir ba�lat�c� sa�lamad���m�z i�in, joe olu�turuldu�unda, joe.id, joe.age ve joe.wage t�m� ba�lat�lmam�� olacak. 
Daha sonra joe.id'nin de�erini yazd�rmaya �al��t���m�zda tan�ms�z bir davran�� elde ederiz.

Ancak, bir struct'� nas�l ba�lataca��n�z� g�stermeden �nce, k�sa bir sapma yapal�m.

Bir topluluk (aggregate) nedir?
--------------------------------
Genel programlamada, bir topluluk veri t�r� (ayn� zamanda bir topluluk olarak da adland�r�l�r), birden �ok veri �yesi i�erebilen
herhangi bir t�rd�r. Topluluklar�n baz� t�rleri, �yelerin farkl� t�rlerde olmas�na izin verir (�r. struct'lar), di�erleri ise t�m
�yelerin tek bir t�rde olmas�n� gerektirir (�r. diziler).

C++'da, bir toplulu�un tan�m� daha dar ve olduk�a daha karma��kt�r.

Not: Bu e�itim serisinde, "toplu" (veya "toplu olmayan") terimini kulland���m�zda, C++ tan�m� olan toplu anlam�na gelecektir.
Kesin tan�m� bir kenara b�rakarak, bu noktada anlaman�z gereken �nemli �ey, yaln�zca veri �yelerine sahip struct'lar�n topluluklar
oldu�udur.

Bir struct'�n toplu ba�lat�lmas�
--------------------------------
Normal bir de�i�ken yaln�zca tek bir de�er tutabilir, bu y�zden yaln�zca tek bir ba�lat�c� sa�lamam�z gerekir:

                int x { 5 };
 
Ancak, bir struct birden �ok �yeye sahip olabilir:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };
 
Bir nesneyi bir struct t�r�yle tan�mlad���m�zda, ba�latma zaman�nda birden �ok �yeyi ba�latman�n bir yoluna ihtiyac�m�z vard�r:

                Employee joe; // joe.id, joe.age ve joe.wage'yi nas�l ba�lat�r�z?
 
Topluluklar, �yeleri do�rudan ba�latmam�za izin veren toplu ba�latma ad� verilen bir ba�latma formunu kullan�r. Bunu yapmak i�in,
bir ba�lat�c� listesi sa�lar�z, bu sadece virg�lle ayr�lm�� de�erlerin s�sl� parantezlerle listesidir.

Toplu ba�latman�n 2 ana formu vard�r:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee frank = { 1, 32, 60000.0 }; // s�sl� liste kullanarak kopya-liste ba�latma
                    Employee joe { 2, 28, 45000.0 };     // s�sl� liste kullanarak liste ba�latma (tercih edilir)

                    return 0;
                }
 
Bu ba�latma formlar�n�n her biri, bir �ye ba��na ba�latma yapar, bu da struct'daki her �yenin bildirildi�i s�rayla ba�lat�ld���
anlam�na gelir. Bu nedenle, Employee joe { 2, 28, 45000.0 }; �nce joe.id'yi 2 de�eriyle ba�lat�r, sonra joe.age'i 28 de�eriyle
ve son olarak joe.wage'i 45000.0 de�eriyle ba�lat�r.

*** BEST -> Topluluklar� ba�lat�rken (kopya olmayan) s�sl� liste formunu tercih edin.

C++20'de, parantezli bir de�er listesi kullanarak (baz�) topluluklar� da ba�latabiliriz:
 
                Employee robert ( 3, 45, 62500.0 );  // parantezli liste kullanarak do�rudan ba�latma (C++20)
 
Bu son formu m�mk�n oldu�unca ka��nman�z� �neririz, ��nk� �u anda brace elision kullanan topluluklarla (�zellikle std::array) 
�al��mamaktad�r.

Bir ba�lat�c� listesinde eksik ba�lat�c�lar
-------------------------------------------
Bir topluluk ba�lat�ld���nda, ancak ba�latma de�erlerinin say�s� �ye say�s�ndan az oldu�unda, t�m kalan �yeler de�erle ba�lat�l�r.
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 2, 28 }; // joe.wage 0.0 olarak de�erle ba�lat�l�r

                    return 0;
                }
 
Yukar�daki �rnekte, joe.id de�eri 2 ile ba�lat�l�r, joe.age de�eri 28 ile ba�lat�l�r ve joe.wage i�in a��k bir ba�lat�c� 
verilmedi�i i�in 0.0 olarak de�erle ba�lat�l�r.
Bu, bir struct'�n t�m �yelerini de�erle ba�latmak i�in bo� bir ba�latma listesi kullanabilece�imiz anlam�na gelir:
 
                Employee joe {}; // t�m �yeleri de�erle ba�lat
 
Const struct'lar
----------------
Bir struct tipindeki de�i�kenler const (veya constexpr) olabilir ve t�m const de�i�kenler gibi, bunlar�n ba�lat�lmas� gerekir.
 
                struct Rectangle
                {
                    double length {};
                    double width {};
                };

                int main()
                {
                    const Rectangle unit { 1.0, 1.0 };
                    const Rectangle zero { }; // t�m �yeleri de�erle ba�lat

                    return 0;
                }
 
Belirlenmi� ba�lat�c�lar C++20
------------------------------
Bir struct'� bir de�er listesinden ba�lat�rken, ba�lat�c�lar bildirme s�ras�na g�re �yelere uygulan�r.

                struct Foo
                {
                    int a {};
                    int c {};
                };

                int main()
                {
                    Foo f { 1, 3 }; // f.a = 1, f.c = 3

                    return 0;
                }
 
�imdi, bu struct tan�m�n� g�ncelleyip son �ye olmayan yeni bir �ye eklerseniz ne olaca��n� d���n�n:
 
                struct Foo
                {
                    int a {};
                    int b {}; // yeni eklendi
                    int c {};
                };

                int main()
                {
                    Foo f { 1, 3 }; // �imdi, f.a = 1, f.b = 3, f.c = 0

                    return 0;
                }
 
�imdi t�m ba�latma de�erleriniz kayd� ve daha k�t�s�, derleyici bunu bir hata olarak alg�lamayabilir (sonu�ta, s�zdizimi hala 
ge�erlidir). Bunu �nlemeye yard�mc� olmak i�in, C++20, struct �yelerini ba�latman�n yeni bir yolunu ekler: belirlenmi�
ba�lat�c�lar. Belirlenmi� ba�lat�c�lar, hangi ba�latma de�erlerinin hangi �yelere e�le�ti�ini a��k�a tan�mlaman�za olanak sa�lar.
�yeler, liste veya kopya ba�latma kullan�larak ba�lat�labilir ve struct'ta bildirildikleri ayn� s�rayla ba�lat�lmal�d�r, 
aksi takdirde bir uyar� veya hata olu�ur. Bir ba�lat�c� belirlenmeyen �yeler de�erle ba�lat�l�r.
 
                struct Foo
                {
                    int a{ };
                    int b{ };
                    int c{ };
                };

                int main()
                {
                    Foo f1{ .a{ 1 }, .c{ 3 } }; // tamam: f1.a = 1, f1.b = 0 (de�erle ba�lat�ld�), f1.c = 3
                    Foo f2{ .a = 1, .c = 3 };   // tamam: f2.a = 1, f2.b = 0 (de�erle ba�lat�ld�), f2.c = 3
                    Foo f3{ .b{ 2 }, .a{ 1 } }; // hata: ba�latma s�ras�, struct'taki bildirim s�ras�na uymuyor

                    return 0;
                }
 
Clang kullan�c�lar� i�in

Tek de�erlerin belirlenmi� ba�lat�c�lar�n� s�sl� parantezler kullanarak yaparken, Clang hatal� bir �ekilde "skaler ba�lat�c�
etraf�nda s�sl� parantezler" uyar�s� verir. Umar�m bu yak�nda d�zeltilecektir. Belirlenmi� ba�lat�c�lar g�zeldir ��nk� belirli bir
d�zeyde kendi belgelerini sa�larlar ve ba�latma de�erlerinizin s�ras�n� yanl��l�kla kar��t�rman�z� �nlerler. Ancak, belirlenmi�
ba�lat�c�lar ayn� zamanda ba�lat�c� listesini �nemli �l��de karma��kla�t�r�r, bu y�zden �u anda bunlar�n kullan�lmas�n� en iyi 
uygulama olarak �nermiyoruz.

Ayr�ca, belirlenmi� ba�lat�c�lar�n bir toplulu�un her yerinde ba�lat�ld���nda tutarl� bir �ekilde kullan�ld���na dair bir zorlama
olmad��� i�in, ba�lat�c�lar�n kaymas�n� �nlemek i�in mevcut bir topluluk tan�m�n�n ortas�na yeni �yeler eklemekten ka��nmak iyi
bir fikirdir.

*** BEST -> Bir toplulu�a yeni bir �ye eklerken, di�er �yelerin ba�lat�c�lar� kaymazsa, onu tan�m listesinin alt�na eklemek
            en g�venlisidir.

Bir ba�lat�c� listesiyle atama
------------------------------
�nceki derste g�sterildi�i gibi, struct'lar�n �yelerine tek tek de�er atayabiliriz:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };

                    joe.age  = 33;      // Joe'nun do�um g�n� oldu
                    joe.wage = 66000.0; // ve bir zam ald�

                    return 0;
                }
 
Tek �yeler i�in bu iyi, ancak bir�ok �yeyi g�ncellemek istedi�imizde harika de�il. Bir struct� bir ba�lat�c� listesiyle ba�latmaya
benzer �ekilde, bir ba�lat�c� listesi kullanarak Structlar�na da de�er atayabilirsiniz (bu, �ye baz�nda atamay� ger�ekle�tirir):

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };
                    joe = { joe.id, 33, 66000.0 }; // Joe'nun bir do�um g�n� oldu ve zam ald�

                    return 0;
                }
 
joe.id'yi de�i�tirmek istemedi�imiz i�in, �ye baz�nda ataman�n joe.id'yi joe.id'ye atayabilmesi i�in listemizde bir yer tutucu 
olarak joe.id i�in mevcut de�eri sa�lamam�z gerekti�ini unutmay�n. Bu biraz �irkin.

C++20 ile belirlenmi� ba�lat�c�larla atama
------------------------------------------
Belirlenmi� ba�lat�c�lar da bir liste atamas�nda kullan�labilir:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };
                    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe'nun bir do�um g�n� oldu ve zam ald�

                    return 0;
                }
 
Bu t�r bir atamada belirlenmemi� herhangi bir �ye, de�er ba�latma i�in kullan�lacak de�eri al�r. E�er joe.id i�in belirlenmi� bir
ba�lat�c� belirtmemi� olsayd�k, joe.id de�eri 0 olarak atan�rd�.

Ayn� t�rden ba�ka bir structyla bir struct� ba�latma
-------------------------------------------------
Bir struct, ayn� t�rden ba�ka bir struct kullan�larak da ba�lat�labilir:
 
                #include <iostream>

                struct Foo
                {
                    int a{};
                    int b{};
                    int c{};
                };

                int main()
                {
                    Foo foo { 1, 2, 3 };

                    Foo x = foo; // kopya ba�latma
                    Foo y(foo);  // do�rudan ba�latma
                    Foo z {foo}; // liste ba�latma

                    std::cout << x.a << ' ' << y.b << ' ' << z.c << '\n';

                    return 0;
                }
                ��kt�s�:
                1 2 3
Bunun, tan�d�k oldu�umuz standart ba�latma formlar�n� (kopya, do�rudan veya liste ba�latma) kullan�rken toplu ba�latma yerine 
kulland���n� unutmay�n. Bu, bir struct�, ayn� t�rden bir struct d�nd�ren bir fonksiyonun d�n�� de�eriyle ba�lat�rken en s�k g�r�l�r.

13.7 � �ye �lk De�er Atama
--------------------------
Bir struct (veya s�n�f) tipi tan�mlad���m�zda, tip tan�m�n�n bir par�as� olarak her �ye i�in varsay�lan bir ilk de�er sa�layabiliriz.
Bu i�leme statik olmayan �ye ilk de�er atama denir ve ilk de�er, varsay�lan �ye ilk de�eri olarak adland�r�l�r.�rne�in:
                struct BirSey
                {
                    int x;       // ilk de�er yok (k�t�)
                    int y {};    // varsay�lan olarak de�er-atamas� structl�yor
                    int z { 2 }; // a��k�a belirtilen varsay�lan de�er
                };

                int main()
                {
                    BirSey s1; // s1.x atanmam��, s1.y 0, ve s1.z 2

                    return 0;
                }
 
Yukar�daki BirSey tan�m�nda, x'in varsay�lan bir de�eri yok, y varsay�lan olarak de�er-atamas� structl�yor ve z'nin varsay�lan 
de�eri 2. Bu varsay�lan �ye ilk de�erler, kullan�c� BirSey tipinde bir nesne olu�tururken a��k bir ilk de�er sa�lamazsa
kullan�lacakt�r.

s1 nesnemizin bir ilk de�eri yok, bu y�zden s1'in �yeleri varsay�lan de�erlerine atan�r. s1.x'in varsay�lan bir ilk de�eri yok,
bu y�zden atanmam�� kal�r. s1.y varsay�lan olarak de�er-atamas� structl�yor, bu y�zden de�eri 0 al�r. Ve s1.z de�eri 2 ile atan�r.
s1.z i�in a��k bir ilk de�er sa�lamam�� olmam�za ra�men, sa�lanan varsay�lan �ye ilk de�eri nedeniyle s�f�r olmayan bir de�ere 
atan�r.

Anahtar Bilgi
-------------
Varsay�lan �ye ilk de�erlerini (veya daha sonra ele alaca��m�z di�er mekanizmalar�) kullanarak, Structlar ve s�n�flar hi�bir a��k
ilk de�er sa�lanmad���nda bile kendilerini ba�latabilir!

�leri Seviye Okuyucular ��in

A��k ilk de�erler, varsay�lan de�erlere �st�n gelir

Bir liste ilk de�er atamas�ndaki a��k de�erler, her zaman varsay�lan �ye ilk de�erlerine �st�n gelir.

                struct BirSey
                {
                    int x;       // varsay�lan ilk de�er yok (k�t�)
                    int y {};    // varsay�lan olarak de�er-atamas� structl�yor
                    int z { 2 }; // a��k�a belirtilen varsay�lan de�er
                };

                int main()
                {
                    BirSey s2 { 5, 6, 7 }; // s2.x, s2.y, ve s2.z i�in a��k ilk de�erler kullan�l�r (varsay�lan de�erler
                                           // kullan�lmaz)

                    return 0;
                }
 
Yukar�daki durumda, s2'nin her �yesi i�in a��k ilk de�erler var, bu y�zden varsay�lan �ye ilk de�erleri hi� kullan�lmaz. Bu, 
s2.x, s2.y ve s2.z'nin s�ras�yla 5, 6 ve 7 de�erlerine atanaca�� anlam�na gelir.

Varsay�lan de�erlerin oldu�u durumda, ilk de�er atama listesinde eksik ilk de�erler
-----------------------------------------------------------------------------------
�nceki derste (13.6 -- Struct �n toplu ilk de�er atamas�) bir toplulu�un ba�lat�ld���n� ancak ilk de�er atama say�s�n�n �ye
say�s�ndan az oldu�unu belirtmi�tik, o zaman t�m kalan �yeler de�er-atamas� structl�r. Ancak, belirli bir �ye i�in varsay�lan bir 
�ye ilk de�eri sa�lan�rsa, bu varsay�lan �ye ilk de�eri yerine kullan�l�r.

                struct BirSey
                {
                    int x;       // varsay�lan ilk de�er yok (k�t�)
                    int y {};    // varsay�lan olarak de�er-atamas� structl�yor
                    int z { 2 }; // a��k�a belirtilen varsay�lan de�er
                };

                int main()
                {
                    BirSey s3 {}; // s3.x'i de�er-atamas� yap, s3.y ve s3.z i�in varsay�lan de�erleri kullan

                    return 0;
                }
 
Yukar�daki durumda, s3 bo� bir liste ile liste-atamas� structl�yor, bu y�zden t�m ilk de�erler eksik. Bu, varsay�lan bir �ye ilk 
de�eri varsa kullan�laca�� ve aksi takdirde de�er-atamas� structlaca�� anlam�na gelir. Bu nedenle, s3.x (varsay�lan bir �ye ilk 
de�eri olmayan) 0'a de�er-atamas� structl�r, s3.y varsay�lan olarak 0'a de�er-atamas� structl�r ve s3.z varsay�lan olarak 2 de�erine
atan�r.

Ba�lang�� de�erlerinin �zetlenmesi
----------------------------------
Bir topluluk bir ba�lang�� listesi ile tan�mlanm��sa:

* - E�er a��k bir ba�lang�� de�eri varsa, bu a��k de�er kullan�l�r.
* - E�er bir ba�lat�c� eksik ve varsay�lan bir �ye ba�lat�c�s� varsa, varsay�lan de�er kullan�l�r.
* - E�er bir ba�lat�c� eksik ve varsay�lan bir �ye ba�lat�c�s� yoksa, de�er ba�latma ger�ekle�ir.

Bir topluluk ba�lang�� listesi olmadan tan�mlanm��sa:

* - E�er varsay�lan bir �ye ba�lat�c�s� varsa, varsay�lan de�er kullan�l�r.
* - E�er varsay�lan bir �ye ba�lat�c�s� yoksa, �ye ba�lat�lmadan kal�r.
* - �yeler her zaman bildirim s�ras�na g�re ba�lat�l�r.

A�a��daki �rnek t�m olas�l�klar� �zetler:

                struct BirSey
                {
                    int x;       // varsay�lan ba�lang�� de�eri yok (k�t�)
                    int y {};    // varsay�lan olarak de�er-ba�lat�ld�
                    int z { 2 }; // a��k varsay�lan de�er
                };

                int main()
                {
                    BirSey s1;             // Ba�lat�c� listesi yok: s1.x ba�lat�lmam��, s1.y ve s1.z varsay�lanlar� kullan�r
                    BirSey s2 { 5, 6, 7 }; // A��k ba�lat�c�lar: s2.x, s2.y ve s2.z a��k de�erleri kullan�r (varsay�lan de�erler 
                                           // kullan�lmaz)
                    BirSey s3 {};          // Eksik ba�lat�c�lar: s3.x de�er ba�lat�l�r, s3.y ve s3.z varsay�lanlar� kullan�r

                    return 0;
                }
 
Dikkat etmemiz gereken durum s1.x'tir. ��nk� s1'in bir ba�lat�c� listesi yok ve x'in varsay�lan bir �ye ba�lat�c�s� yok, bu y�zden
s1.x ba�lat�lmadan kal�r (bu k�t�d�r, ��nk� de�i�kenlerimizi her zaman ba�latmal�y�z).

�yeleriniz i�in her zaman varsay�lan de�erler sa�lay�n
------------------------------------------------------
Ba�lat�lmam�� �yelerin olas�l���n� �nlemek i�in, basit�e her �yenin bir varsay�lan de�eri oldu�undan emin olun (ya a��k bir 
varsay�lan de�er veya bo� bir s�sl� parantez �ifti). Bu �ekilde, �yelerimiz bir ba�lat�c� listesi sa�lay�p sa�lamad���m�za 
bak�lmaks�z�n bir de�erle ba�lat�lacakt�r. A�a��daki struct� d���n�n, t�m �yeleri varsay�lan de�erlere sahiptir:
 
                struct Kesir
                {
                    int pay { }; // burada { 0 } kullanmal�y�z, ama �rne�in u�runa de�er ba�latmay� kullanaca��z
                    int payda { 1 };
                };

                int main()
                {
                    Kesir f1;          // f1.pay de�er ba�lat�ld� ve 0 oldu, f1.payda 1'e varsay�land�
                    Kesir f2 {};       // f2.pay de�er ba�lat�ld� ve 0 oldu, f2.payda 1'e varsay�land�
                    Kesir f3 { 6 };    // f3.pay 6'ya ba�lat�ld�, f3.payda 1'e varsay�land�
                    Kesir f4 { 5, 8 }; // f4.pay 5'e ba�lat�ld�, f4.payda 8'e ba�lat�ld�

                    return 0;
                }
 
T�m durumlarda, �yelerimiz de�erlerle ba�lat�l�r.
*** BEST -> T�m �yeler i�in bir varsay�lan de�er sa�lay�n. Bu, de�i�ken tan�m�n�z bir ba�lat�c� listesi i�ermese bile �yelerinizin
            ba�lat�laca��n� garanti eder.

Topluluklar i�in varsay�lan ba�latma vs de�er ba�latma
------------------------------------------------------
Yukar�daki �rnekteki iki sat�r� tekrar g�zden ge�irelim:
 
                Kesir f1;          // f1.pay de�er ba�lat�ld� ve 0 oldu, f1.payda 1'e varsay�land�
                Kesir f2 {};       // f2.pay de�er ba�lat�ld� ve 0 oldu, f2.payda 1'e varsay�land�
 
F1'in varsay�lan ba�lat�ld���n� ve f2'nin de�er ba�lat�ld���n� not edeceksiniz, ancak sonu�lar ayn�d�r (pay 0'a ba�lat�l�r ve
payda 1'e ba�lat�l�r). Peki hangisini tercih etmeliyiz?
De�er ba�latma durumu (f2) daha g�venlidir, ��nk� varsay�lan de�erleri olmayan herhangi bir �yenin de�er ba�lat�lmas�n� sa�lar 
(ve her zaman �yeler i�in varsay�lan de�erler sa�lamal�y�z, ancak bu, bir tanesinin ka��r�ld��� durumu korur).De�er ba�latmay� 
tercih etmenin bir avantaj� daha var - di�er t�rlerin nesnelerini nas�l ba�latt���m�zla tutarl�d�r. Tutarl�l�k hatalar� �nlemeye
yard�mc� olur.

*** BEST -> Topluluklar i�in, varsay�lan ba�latmaya (s�sl� parantez olmadan) kar�� de�er ba�latmay� (bo� s�sl� parantez ba�lat�c�
            ile) tercih edin.

Bununla birlikte, programc�lar�n s�n�f t�rleri i�in de�er ba�latma yerine varsay�lan ba�latmay� kullanmalar� al���lmad�k bir durum 
de�ildir. Bu k�smen tarihsel nedenlerden dolay�d�r (��nk� de�er ba�latma C++11 ile tan�t�ld�) ve k�smen de varsay�lan ba�latman�n
daha verimli olabilece�i benzer bir durum (bu durumu 14.9 - structc�lar�na Giri� b�l�m�nde ele al�yoruz) vard�r.

Bu nedenle, bu e�itimlerde Structlar ve s�n�flar i�in de�er ba�latman�n kullan�lmas�n� zorla�t�rmayaca��z, ancak bunu �iddetle
�neriyoruz.

13.8 � Structlar� Ge�mek ve D�nd�rmek ( Pass and Return )
---------------------------------------------------------
3 serbest de�i�kenle temsil edilen bir �al��an� d���n�n:

                int main()
                {
                    int id { 1 };
                    int yas { 24 };
                    double maas { 52400.0 };

                    return 0;
                }
 
Bu �al��an� bir fonksiyona ge�irmek istiyorsak, �� de�i�keni ge�irmemiz gerekiyor:

                #include <iostream>

                void printEmployee(int id, int yas, double maas)
                {
                    std::cout << "ID:   " << id << '\n';
                    std::cout << "Ya�:  " << yas << '\n';
                    std::cout << "Maa�: " << maas << '\n';
                }

                int main()
                {
                    int id { 1 };
                    int yas { 24 };
                    double maas { 52400.0 };

                    printEmployee(id, yas, maas);

                    return 0;
                }
 
3 ayr� �al��an de�i�kenini ge�mek o kadar k�t� de�il, ancak 10 veya 12 �al��an de�i�kenini ge�memiz gereken bir fonksiyon d���n�n.
Her de�i�keni ba��ms�z olarak ge�mek zaman al�c� ve hata yapmaya e�ilimlidir. Ayr�ca, e�er �al��an�m�za yeni bir �zellik eklersek
(�r. isim), art�k t�m fonksiyon bildirimlerini, tan�mlamalar�n� ve fonksiyon �a�r�lar�n� yeni parametre ve arg�man� kabul etmek 
�zere de�i�tirmemiz gerekiyor!

Structlar� (Referans Olarak) Ge�mek
-----------------------------------
Structlar� bireysel de�i�kenler �zerinde kullanman�n b�y�k bir avantaj�, �yelerle �al��mas� gereken bir fonksiyona t�m struct� 
ge�irebilmemizdir. Structlar genellikle kopyalar� �nlemek i�in (const) referans olarak ge�irilir.
 
                #include <iostream>

                struct Calisan
                {
                    int id {};
                    int yas {};
                    double maas {};
                };

                void printEmployee(const Calisan& calisan) // burada referansla ge�i�i not edin
                {
                    std::cout << "ID:   " << calisan.id << '\n';
                    std::cout << "Ya�:  " << calisan.yas << '\n';
                    std::cout << "Maa�: " << calisan.maas << '\n';
                }

                int main()
                {
                    Calisan joe { 14, 32, 24.15 };
                    Calisan frank { 15, 28, 18.27 };

                    // Joe'nun bilgilerini yazd�r
                    printEmployee(joe);

                    std::cout << '\n';

                    // Frank'in bilgilerini yazd�r
                    printEmployee(frank);

                    return 0;
                }
 
Yukar�daki �rnekte, t�m bir Calisan'� printEmployee()'a ge�iriyoruz (iki kez, bir kez joe ve bir kez frank i�in).

                Yukar�daki program �unu ��kt�lar:

                ID:   14
                Ya�:  32
                Maa�: 24.15

                ID:   15
                Ya�:  28
                Maa�: 18.27
T�m struct nesnesini (bireysel �yeler yerine) ge�irdi�imiz i�in, struct nesnesinin ka� �yesi olursa olsun yaln�zca bir parametreye
ihtiyac�m�z var. Ve gelecekte, e�er Calisan structm�za yeni �yeler eklemeye karar verirsek, fonksiyon bildirimini veya fonksiyon 
�a�r�s�n� de�i�tirmemiz gerekmeyecek! Yeni �ye otomatik olarak dahil edilecektir.

Structlar� D�nd�rmek
--------------------
3 boyutlu Kartezyen uzayda bir noktay� d�nd�rmesi gereken bir fonksiyon oldu�unu d���n�n. B�yle bir noktan�n 3 �zelli�i vard�r:
bir x-koordinat�, bir y-koordinat� ve bir z-koordinat�. Ancak fonksiyonlar yaln�zca bir de�er d�nd�rebilir. Peki kullan�c�ya t�m
3 koordinat� nas�l geri d�nd�r�r�z?

Yayg�n bir yol, bir struct d�nd�rmektir:

                #include <iostream>

                struct Nokta3d
                {
                    double x { 0.0 };
                    double y { 0.0 };
                    double z { 0.0 };
                };

                Nokta3d sifirNoktayiAl()
                {
                    // Bir de�i�ken olu�turabilir ve de�i�keni d�nd�rebiliriz (bunu a�a��da geli�tirece�iz)
                    Nokta3d gecici { 0.0, 0.0, 0.0 };
                    return gecici;
                }

                int main()
                {
                    Nokta3d sifir{ sifirNoktayiAl() };

                    if (sifir.x == 0.0 && sifir.y == 0.0 && sifir.z == 0.0)
                        std::cout << "Nokta s�f�r\n";
                    else
                        std::cout << "Nokta s�f�r de�il\n";

                    return 0;
                }
 
                Bu ��kt�y� verir:

                Nokta s�f�r
Structlar genellikle de�er olarak d�nd�r�l�r, b�ylece as�l� bir referans d�nd�r�lmez.

Yukar�daki getZeroPoint() fonksiyonunda, yaln�zca onu d�nd�rebilmek i�in yeni bir adland�r�lm�� nesne (temp) olu�turuyoruz:

                Nokta3d sifirNoktayiAl()
                {
                    // Bir de�i�ken olu�turabilir ve de�i�keni d�nd�rebiliriz (bunu a�a��da geli�tirece�iz)
                    Nokta3d gecici { 0.0, 0.0, 0.0 };
                    return gecici;
                }
 Nesnenin ad� (temp) burada herhangi bir belgelendirme de�eri sa�lam�yor. Fonksiyonumuzu, ge�ici (isimsiz/anonim) bir nesne 
 d�nd�rerek biraz daha iyi hale getirebiliriz:

                Point3d getZeroPoint()
                {
                    return Point3d { 0.0, 0.0, 0.0 }; // isimsiz bir Point3d d�nd�r
                }
 
Bu durumda, ge�ici bir Point3d olu�turulur, �a��ran ki�iye geri kopyalan�r ve ifadenin sonunda yok edilir. Bu durumun ne kadar 
daha temiz oldu�una dikkat edin (iki sat�r yerine bir sat�r ve temp'in birden fazla kullan�l�p kullan�lmad���n� anlaman�za gerek 
yok).

D�n�� Tipini ��kar�m Yapma
--------------------------
Fonksiyonun a��k bir d�n�� tipi oldu�u durumda (�r. Point3d), d�n�� ifadesinde tipi bile atlayabiliriz:

Point3d getZeroPoint()
{
    // Tipi zaten fonksiyon bildiriminde belirttik
    // bu y�zden burada tekrar yapmam�za gerek yok
    return { 0.0, 0.0, 0.0 }; // isimsiz bir Point3d d�nd�r
}
Ayr�ca, bu durumda t�m s�f�r de�erlerini d�nd�rd���m�zden, de�er ba�lat�lm�� bir Point3d d�nd�rmek i�in bo� s�sl� parantezler
kullanabiliriz:

                Point3d getZeroPoint()
                {
                    // T�m �yeleri de�er ba�latmak i�in bo� s�sl� parantezleri kullanabiliriz
                    return {};
                }
 
Structlar �nemli bir yap� ta��d�r

Structlar kendi ba�lar�na yararl� olsa da, s�n�flar (C++ ve nesne y�nelimli programlaman�n kalbi olan) burada tan�tt���m�z
kavramlar�n do�rudan �zerine in�a eder. Structlar�n (�zellikle veri �yeleri, �ye se�imi ve varsay�lan �ye ba�latma)
iyi bir anlay���na sahip olmak, s�n�flara ge�i�inizi �ok daha kolay hale getirecektir.
*/
