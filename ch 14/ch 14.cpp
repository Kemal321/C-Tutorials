#include <iostream>
class DateClass {
public:
    int m_day{};
    int m_month{};
    int m_year{};
};
void printDate(const DateClass& date) {
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year << '\n';
}
struct quizIntPair {
    int one{};
    int two{};
    void print() {
        std::cout << "First: " << one << "\nSecond: " << two << '\n';
    }
    bool isEqual(const quizIntPair p) {
        return (one == p.one && two == p.two);
    }
};
struct Date {
    int day{};
    int month{};
    int year{};

    void print() 
    {
        std::cout << day << '/' << month << '/' << year << '\n';
    }
    
};


int main()
{
    quizIntPair p1{ 1, 2 };
    quizIntPair p2{ 3, 4 };

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
    std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

    DateClass dateClass{ 4,10,21 };
    printDate(dateClass);

    // Struct member fonksiyon �rne�i
    Date date{ 28,04,1999 };
    date.print();
    
    return 0;
}
/*
14.1 � Nesne y�nelimli programlamaya giri�

Yordamsal programlama (Procedural programming)
----------------------------------------------
Ders 1.3 -- Nesneler ve de�i�kenlere giri�te, C++'daki bir nesneyi �de�er saklamak i�in kullan�labilecek bir bellek par�as�� 
olarak tan�mlad�k. Bir ismi olan nesneye de�i�ken denir. C++ programlar�m�z, bilgisayara veri tan�mlayan (nesneler arac�l���yla) 
ve bu veriler �zerinde i�lemler ger�ekle�tiren (ifadeler ve deyimler i�eren fonksiyonlar arac�l���yla) talimatlar�n ard���k 
listelerinden olu�mu�tur.

�imdiye kadar, yordamsal programlama ad� verilen bir programlama t�r�n� ger�ekle�tirdik. Yordamsal programlamada, program
mant���m�z� uygulayan "yordamlar" olu�turmak �zerinde durulur (C++'da bunlara fonksiyon denir). Bu fonksiyonlara veri nesnelerini 
ge�eriz, bu fonksiyonlar veriler �zerinde i�lemler ger�ekle�tirir ve ard�ndan potansiyel olarak �a��ran taraf�ndan kullan�lacak
bir sonu� d�nd�r�r.

Yordamsal programlamada, fonksiyonlar ve bu fonksiyonlar�n �zerinde i�lem yapt��� veriler ayr� varl�klard�r. Programc�, 
fonksiyonlar� ve verileri bir araya getirerek istenen sonucu �retmekten sorumludur. Bu, �u �ekilde bir koda yol a�ar:

                eat(you, apple);

�imdi etraf�n�za bir bak�n -- her yerde nesneler var: kitaplar, binalar, yiyecekler ve hatta siz. Bu nesnelerin iki ana 
bile�eni vard�r: 
1) Bir dizi ili�kili �zellik (�r. a��rl�k, renk, boyut, kat�l�k, �ekil, vb...), ve
2) Sergileyebilecekleri bir dizi davran�� (�r. a��lma, ba�ka bir �eyi �s�tma, vb...). Bu �zellikler ve davran��lar ayr�lmaz.

Programlamada, �zellikler nesneler taraf�ndan, davran��lar ise fonksiyonlar taraf�ndan temsil edilir. Ve b�ylece, yordamsal 
programlama, �zellikleri (nesneler) ve davran��lar� (fonksiyonlar) ay�rarak ger�e�i olduk�a k�t� temsil eder.

Nesne y�nelimli programlama nedir?
----------------------------------
Nesne y�nelimli programlamada (genellikle OOP olarak k�salt�l�r), odak noktas�, hem �zellikleri hem de iyi tan�mlanm�� bir 
davran�� setini i�eren program tan�ml� veri t�rlerini olu�turmakt�r. OOP'deki �nesne� terimi, bu t�rlerden �rnekleyebilece�imiz
nesnelere at�fta bulunur.

Bu, kodun daha �ok �u �ekilde g�r�nmesine yol a�ar:

                you.eat(apple);

Bu, kimin nesne oldu�unu (you), hangi davran���n �a�r�ld���n� (eat()), ve hangi nesnelerin bu davran��a aksesuar oldu�unu (apple) 
daha net hale getirir.

�zellikler ve davran��lar art�k ayr� olmad��� i�in, nesneleri mod�lerle�tirmek daha kolayd�r, bu da programlar�m�z� yazmay� ve
anlamay� kolayla�t�r�r ve ayr�ca daha y�ksek bir kod yeniden kullan�labilirli�i sa�lar. Bu nesneler, nesnelerle nas�l etkile�im
kurdu�umuzu ve onlar�n di�er nesnelerle nas�l etkile�im kurdu�unu tan�mlayarak verilerimizle �al��may� daha sezgisel hale getirir.
Bu t�r nesneleri nas�l olu�turaca��m�z� bir sonraki derste tart��aca��z.
Yordamsal vs OOP benzeri bir �rnek
----------------------------------
��te bir hayvan�n ad�n� ve bacak say�s�n� yazd�ran yordamsal programlama tarz�nda yaz�lm�� k�sa bir program:

                #include <iostream>
                #include <string_view>

                enum AnimalType
                {
                    cat,
                    dog,
                    chicken,
                };

                constexpr std::string_view animalName(AnimalType type)
                {
                    switch (type)
                    {
                    case cat: return "cat";
                    case dog: return "dog";
                    case chicken: return "chicken";
                    default:  return "";
                    }
                }

                constexpr int numLegs(AnimalType type)
                {
                    switch (type)
                    {
                    case cat: return 4;
                    case dog: return 4;
                    case chicken: return 2;
                    default:  return 0;
                    }
                }
                int main()
                {
                    constexpr AnimalType animal{ cat };
                    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

                    return 0;
                }
Bu programda, bir hayvan�n bacak say�s�n� almak ve bir hayvan�n ad�n� almak gibi �eyleri yapmam�za izin veren fonksiyonlar yazd�k.
Bu, olduk�a iyi �al���rken, hayvan�m�z�n art�k bir y�lan oldu�unu g�ncellemek istedi�imizde ne olaca��n� d���n�n. Kodumuza bir
y�lan eklemek i�in, AnimalType, numLegs(), animalName()'i de�i�tirmemiz gerekecek. E�er bu daha b�y�k bir kod taban� olsayd�,
AnimalType'� kullanan herhangi bir di�er fonksiyonu da g�ncellememiz gerekecekti -- e�er AnimalType bir�ok yerde kullan�l�yorsa,
bu, dokunulmas� gereken �ok fazla kod olabilir (ve potansiyel olarak bozulabilir).
�imdi, ayn� program� (ayn� ��kt�y� �reten) daha �ok bir OOP zihniyeti kullanarak yazal�m:

                #include <iostream>
                #include <string_view>

                struct Cat
                {
                    std::string_view name{ "cat" };
                    int numLegs{ 4 };
                };

                struct Dog
                {
                    std::string_view name{ "dog" };
                    int numLegs{ 4 };
                };

                struct Chicken
                {
                    std::string_view name{ "chicken" };
                    int numLegs{ 2 };
                };

                int main()
                {
                    constexpr Cat animal;
                    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

                    return 0;
                }
Bu �rnekte, her hayvan kendi program tan�ml� tipidir ve bu tip, o hayvanla ilgili her �eyi y�netir (bu durumda, sadece ad� ve 
bacak say�s�n� takip etmek). �imdi, hayvan�m�z� bir y�lana g�ncellemek istedi�imiz durumu d���n�n. Tek yapmam�z gereken bir Snake
tipi olu�turmak ve onu Cat yerine kullanmakt�r. �ok az mevcut kodun de�i�tirilmesi gerekiyor, bu da zaten �al��an bir �eyi bozma
riskinin �ok daha az olmas� anlam�na gelir.

Sunulan �ekliyle, Cat, Dog ve Chicken �rne�imiz yukar�da �ok fazla tekrar i�eriyor (her biri tamamen ayn� �ye setini tan�ml�yor).
Bu gibi bir durumda, ortak bir Animal struct olu�turmak ve her hayvan i�in bir �rnek olu�turmak tercih edilebilir. Ama ya di�er
hayvanlara uygulanmayan Chicken'a yeni bir �ye eklemek istiyorsak (�r. wormsPerDay)? Ortak bir Animal struct ile, t�m hayvanlar
bu �yeyi al�r. OOP modelimizle, bu �yeyi Chicken nesneleriyle s�n�rlayabiliriz.

OOP, masaya ba�ka faydalar da getirir
-------------------------------------
Okulda, programlama �devlerinizi teslim etti�inizde, i�iniz esasen bitmi�tir. Profes�r�n�z veya ��retim g�revliniz kodunuzu 
�al��t�r�r ve do�ru sonucu �retip �retmedi�ini g�r�r. Ya yapar ya da yapmaz ve buna g�re notland�r�l�rs�n�z. Kodunuz muhtemelen 
bu noktada at�l�r.

Di�er taraftan, kodunuzu di�er geli�tiriciler taraf�ndan kullan�lan bir depoya veya ger�ek kullan�c�lar�n kulland��� bir 
uygulamaya g�nderdi�inizde, tamamen farkl� bir oyun s�z konusudur. Yeni bir i�letim sistemi veya yaz�l�m s�r�m� kodunuzu 
bozacakt�r. Kullan�c�lar yapt���n�z baz� mant�k hatalar�n� bulacak. Bir i� orta�� yeni bir yetenek talep edecek. Di�er
geli�tiriciler kodunuzu bozmadan geni�letmek zorunda kalacak. Kodunuzun, belki de �nemli �l��de, evrim ge�irebilmesi ve bunu 
minimal zaman yat�r�m�, minimal ba� a�r�s� ve minimal k�r�lma ile yapabilmesi gerekiyor.

Bunlar� en iyi �ekilde ele alman�n yolu, kodunuzu olabildi�ince mod�ler (ve tekrars�z) tutmakt�r. Bu konuda yard�mc� olmak i�in, 
OOP ayr�ca miras, kaps�lleme, soyutlama ve �ok bi�imlilik gibi bir dizi di�er faydal� kavram� da masaya getirir.

Yazar�n notu
Dil tasar�mc�lar�n�n bir felsefesi var: b�y�k bir kelime yapacaksa, asla k���k bir kelime kullanma.

Ayr�ca neden k�saltma kelimesi bu kadar uzun?
---------------------------------------------
T�m bunlar�n ne oldu�unu ve kodunuzu daha az tekrarl� hale getirmeye, de�i�tirmeyi ve geni�letmeyi kolayla�t�rmaya nas�l yard�mc� 
olabilece�ini zamanla anlataca��z. OOP ile do�ru �ekilde tan��t���n�zda ve t�klad���nda, muhtemelen saf yordamsal programlamaya
geri d�nmek istemeyeceksiniz.

Bu s�ylenmi�ken, OOP yordamsal programlamay� de�i�tirmez -- daha ziyade, gerekti�inde karma��kl��� y�netmek i�in programlama ara�
�antan�za ek ara�lar verir.
�Object� terimi
---------------
�Object� teriminin biraz a��r� y�klendi�ini ve bu durumun bir miktar kafa kar���kl���na neden oldu�unu unutmay�n. Geleneksel
programlamada, bir nesne de�erleri saklamak i�in bir bellek par�as�d�r. Nesne y�nelimli programlamada, bir �nesne�,
hem geleneksel programlama anlam�nda bir nesne oldu�unu, hem de hem �zellikleri hem de davran��lar� birle�tirdi�ini ima eder.
Bu derslerde, nesne teriminin geleneksel anlam�n� tercih edece�iz ve OOP nesnelerine �zellikle at�fta bulunurken �s�n�f nesnesi�
terimini tercih edece�iz.

14.2 � S�n�flara Giri�
----------------------
�nceki b�l�mde, structlar� ele ald�k ve birden �ok �ye de�i�kenini tek bir nesneye toplayabilme, ba�latma ve bir birim olarak
ta��ma konusunda ne kadar iyi olduklar�n� tart��t�k. Ba�ka bir deyi�le, structlar, ilgili veri de�erlerini depolamak ve ta��mak
i�in uygun bir paket sa�lar.
A�a��daki struct� d���n�n:

                #include <iostream>

                struct Date
                {
                    int day{};
                    int month{};
                    int year{};
                };

                void printDate(const Date& date)
                {
                    std::cout << date.day << '/' << date.month << '/' << date.year; // DMY format�n� varsayal�m
                }

                int main()
                {
                    Date date{ 4, 10, 21 }; // toplu ba�latma kullanarak ba�lat
                    printDate(date);        // t�m struct� fonksiyona ge�irebilir

                    return 0;
                }
Yukar�daki �rnekte, bir Datenesnesi olu�turuyoruz ve ard�ndan onu tarihi yazd�ran bir fonksiyona ge�iriyoruz. Bu program �unu 
yazd�r�r:
                4/10/21
Bir hat�rlatma

Bu derslerde, t�m structlar�m�z topluluklard�r. topluluklard�r ders 13.6 -- struct toplulu�u ba�latma dersinde tart���yoruz.

structlar ne kadar kullan��l� olursa olsun, structlar�n b�y�k, karma��k programlar olu�tururken (�zellikle birden �ok geli�tirici
taraf�ndan �al���lanlar) zorluklar sunabilecek bir dizi eksikli�i vard�r.

S�n�f de�i�mezlik sorunu
------------------------
Belki de structlar�n en b�y�k zorlu�u, s�n�f de�i�mezliklerini belgelemek ve uygulamak i�in etkili bir yol sa�lamamalar�d�r. 
Ders 9.6 -- Assert ve static_assert'te, bir de�i�mezi, "bir bile�enin �al���rken do�ru olmas� gereken bir durum" olarak tan�mlad�k.
S�n�f t�rleri ba�lam�nda (structlar�, s�n�flar� ve unionlar� i�erir), bir s�n�f de�i�mezi, bir nesnenin ge�erli bir durumda 
kalmas� i�in bir nesnenin �mr� boyunca do�ru olmas� gereken bir durumdur. De�i�mezli�i ihlal edilmi� bir nesne, ge�ersiz bir 
durumda oldu�u s�ylenir ve bu nesnenin daha fazla kullan�lmas�ndan beklenmeyen veya tan�mlanmam�� davran��lar ortaya ��kabilir.

�ncelikle, a�a��daki struct� d���n�n:

                struct Cift
                {
                    int ilk {};
                    int ikinci {};
                };

�lk ve ikinci �yeler herhangi bir de�ere ba��ms�z olarak ayarlanabilir, bu y�zden Cift yap�s�n�n bir de�i�mezi yoktur.

�imdi a�a��daki neredeyse ayn� struct� d���n�n:

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 };
                };

Matematikten biliyoruz ki, paydas� 0 olan bir kesir matematiksel olarak tan�ms�zd�r (��nk� bir kesirin de�eri pay�n�n paydas�na 
b�l�nmesidir -- ve 0'a b�lme matematiksel olarak tan�ms�zd�r). Bu nedenle, bir Kesir nesnesinin payda �yesinin asla 0'a 
ayarlanmamas�n� sa�lamak istiyoruz. E�er �yleyse, o Kesir nesnesi ge�ersiz bir durumdad�r ve bu nesnenin daha fazla
kullan�lmas�ndan tan�mlanmam�� davran��lar ortaya ��kabilir.
�rne�in:

                #include <iostream>

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 }; // s�n�f de�i�mezi: asla 0 olmamal�
                };

                void kesirDegeriniYazdir(const Kesir &k)
                {
                     std::cout << k.pay / k.payda << '\n';
                }

                int main()
                {
                    Kesir k { 5, 0 };   // paydas� s�f�r olan bir Kesir olu�tur
                    kesirDegeriniYazdir(k); // s�f�ra b�lme hatas� olu�tur

                    return 0;
                }

Yukar�daki �rnekte, Kesir'in de�i�mezli�ini belgelemek i�in bir yorum kullan�yoruz. Ayr�ca, kullan�c� bir ba�latma de�eri
sa�lamazsa paydan�n 1'e ayarlanmas�n� sa�lamak i�in varsay�lan bir �ye ba�lat�c�s� sa�l�yoruz. Bu, kullan�c�n�n bir Kesir 
nesnesini de�er ba�latmaya karar vermesi durumunda Kesir nesnemizin ge�erli olaca��n� garanti eder. Bu, iyi bir ba�lang��t�r.

Ama hi�bir �ey bizi bu s�n�f de�i�mezini a��k�a ihlal etmekten al�koymaz: Kesir f'yi olu�tururken, paydan�n a��k�a 0'a
ba�lat�lmas� i�in toplu ba�latmay� kullan�r�z. Bu hemen bir soruna neden olmasa da, nesnemiz art�k ge�ersiz bir durumdad�r ve
nesnenin daha fazla kullan�lmas� beklenmeyen veya tan�ms�z davran��lara neden olabilir.
Ve bu tam olarak kesirDegeriniYazdir(f)'yi �a��rd���m�zda g�rd���m�z �ey: program, s�f�ra b�lme hatas� nedeniyle sona erer.

Bir parantez a�al�m�

kesirDegeriniYazdir'nin g�vdesinin ba��nda assert(f.payda != 0); eklemek k���k bir iyile�tirme olurdu. Bu, kodun belgelendirme
de�erini art�r�r ve hangi �nc�l ko�ulun ihlal edildi�i daha belirgin hale gelir. Ancak, davran��sal olarak, bu ger�ekten bir �eyi
de�i�tirmez. Bu sorunlar� sorunun kayna��nda (�ye k�t� bir de�erle ba�lat�ld���nda veya atanm�� oldu�unda) yakalamak istiyoruz, 
de�il mi? Sorunun a�a�� ak���nda (k�t� de�er kullan�ld���nda).

Kesir �rne�inin g�receli basitli�i g�z �n�ne al�nd���nda, ge�ersiz Kesir nesneleri olu�turman�n basit�e ka��n�lmas� �ok zor
olmamal�d�r. Ancak, bir�ok struct� kullanan daha karma��k bir kod taban�nda, bir�ok �yesi olan structlar veya �yeleri karma��k 
ili�kiler olan structlar, hangi de�er kombinasyonunun baz� s�n�f de�i�mezini ihlal edebilece�ini anlamak o kadar a��k olmayabilir.

Daha karma��k bir s�n�f de�i�mezi
---------------------------------
Kesir i�in s�n�f de�i�mezi basit bir tanedir -- payda �yesi 0 olamaz. Bu, kavramsal olarak anlamas� kolay ve ka��nmas� �ok zor
de�il. S�n�f de�i�mezleri, bir yap�n�n �yelerinin ili�kili de�erlere sahip olmas� gerekti�inde daha fazla bir meydan okuma haline
gelir.

                #include <string>

                struct Calisan
                {
                    std::string isim { };
                    char ilkHarf { }; // her zaman `isim`in ilk karakterini tutmal� (veya `0`)
                };

Yukar�daki (k�t� tasarlanm��) struct da, ilkHarf �yesinde saklanan karakter de�eri, her zaman isim'in ilk karakteriyle 
e�le�melidir.

Bir Calisan nesnesi ba�lat�ld���nda, kullan�c� s�n�f de�i�mezinin korunmas�n� sa�lamaktan sorumludur. Ve e�er isme yeni 
bir de�er atan�rsa, kullan�c� ayn� zamanda FirstInitial'in g�ncellenmesini sa�lamaktan da sorumludur.. Bu ili�ki, bir Calisan 
nesnesini kullanan bir geli�tirici i�in a��k olmayabilir ve hatta e�er �yleyse, bunu yapmay� unutabilir.

Calisan nesneleri olu�turmak ve g�ncellemek i�in bize yard�mc� olacak fonksiyonlar yazsak bile (ilkHarf'in her zaman isim'in ilk 
karakterinden ayarland���ndan emin olmak), hala kullan�c�n�n bu fonksiyonlar�n fark�nda olmas�na ve bunlar� kullanmas�na
g�veniyoruz.
K�sacas�, bir nesnenin kullan�c�s�na s�n�f de�i�mezlerini koruma g�revini vermek, sorunlu kod olu�turma olas�l���n� art�r�r.

Anahtar i�g�r�

Bir nesnenin kullan�c�s�na s�n�f de�i�mezlerini koruma g�revini vermek, sorunlara yol a�ma olas�l���n� y�kseltir.

�deal olarak, s�n�f t�rlerimizi kur�un ge�irmez hale getirmeyi �ok isterdik, b�ylece bir nesne ya ge�ersiz bir duruma getirilemez
ya da e�er �yleyse hemen sinyal verebilir (gelecekteki baz� rastgele bir noktada tan�ms�z davran���n meydana gelmesine izin vermek
yerine).

structlar (topluluk ( aggregrate ) olarak) bu sorunu zarif bir �ekilde ��zmek i�in gereken mekaniklere sahip de�il.

S�n�flara giri�
---------------
C++'� geli�tirirken, Bjarne Stroustrup, geli�tiricilerin daha sezgisel bir �ekilde kullan�labilecek program tan�ml� t�rler 
olu�turmas�na olanak sa�layacak yetenekler sunmak istedi. Ayr�ca, b�y�k, karma��k programlar� (�zellikle daha �nce bahsedilen 
s�n�f de�i�mezlik sorunu gibi) s�k s�k rahats�z eden ve bak�m zorluklar�na zarif ��z�mler bulmakla da ilgileniyordu.

Di�er programlama dilleriyle (�zellikle de ilk nesne y�nelimli programlama dili olan Simula ile) deneyiminden yola ��kan Bjarne,
neredeyse her �ey i�in kullan�labilecek genel ve g��l� bir program tan�ml� t�r geli�tirmenin m�mk�n oldu�una ikna oldu. Simula'ya ,
bir g�nderme olarak, bu t�r� bir s�n�f olarak adland�rd�. structlar gibi, bir s�n�f da bir�ok �ye de�i�keni farkl� t�rlerde
olabilen bir program tan�ml� bile�ik t�rd�r.

Kilit nokta
Teknik a��dan bak�ld���nda, structlar ve s�n�flar neredeyse ayn�d�r -- bu nedenle, bir struct kullan�larak uygulanan herhangi bir
�rnek, bir s�n�f kullan�larak veya tam tersi uygulanabilir. Ancak, pratik a��dan bak�ld���nda, structlar� ve s�n�flar� farkl�
�ekillerde kullan�r�z.

Teknik ve pratik farkl�l�klar� 14.5 -- Public ve private �yeler ve eri�im belirleyicileri dersinde ele al�yoruz.

Bir s�n�f� tan�mlama
--------------------
Bir s�n�f, bir program tan�ml� veri t�r� oldu�u i�in, kullan�lmadan �nce tan�mlanmal�d�r. S�n�flar, struct yerine class anahtar
kelimesini kullanarak structlarla benzer �ekilde tan�mlan�r. �rne�in, basit bir �al��an s�n�f� i�in bir tan�m a�a��dad�r:

                class Calisan
                {
                    int m_id {};
                    int m_yas {};
                    double m_wage {};
                };


S�n�flar�n ve yap�lar�n ne kadar benzer olabilece�ini g�stermek i�in a�a��daki program dersin ba��nda sundu�umuz program�n 
e�de�eridir, ancak Date art�k bir struct yerine bir s�n�ft�r:

                #include <iostream>

                class Date      // struct'� class ile de�i�tirdik
                {
                public:          // ve bu sat�r� ekledik, buna eri�im belirleyici denir ( ileride g�recez 14.5 )
                    int m_day{}; // ve her bir �ye ad�na "m_" �neklerini ekledik
                    int m_month{};
                    int m_year{};
                };

                void printDate(const Date& date)
                {
                    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
                }

                int main()
                {
                    Date date{ 4, 10, 21 };
                    printDate(date);

                    return 0;
                }

                Bu, �unu yazd�r�r:

                4/10/21

C++ standart k�t�phanesinin �o�u s�n�ft�r
-----------------------------------------
Zaten belki de bilmeden s�n�f nesnelerini kullan�yordunuz. Hem std::string hem de std::string_view birer s�n�f olarak
tan�mlanm��t�r. Asl�nda, standart k�t�phanedeki takma ad� olmayan t�rlerin �o�u s�n�f olarak tan�mlanm��t�r!

S�n�flar ger�ekten C++'�n kalbi ve ruhudur -- o kadar temeldirler ki, C++ ba�lang��ta "s�n�flarla C" olarak adland�r�ld�! 
S�n�flarla tan��t�ktan sonra, C++'da ge�irdi�iniz �ok zaman� onlar� yazmak, test etmek ve kullanmak i�in harcayacaks�n�z.

14.3 � �ye Fonksiyonlar
-----------------------
Ders 13.5 -- structlara, �yelere ve �ye se�imine giri�te, �ye de�i�kenler i�erebilen bir program tan�ml� t�r olan struct� tan�tt�k.
��te bir tarihi tutmak i�in kullan�lan bir struct �rne�i:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};
                };

�imdi, e�er tarihi ekrana yazd�rmak istiyorsak (muhtemelen �ok s�k yapmak istedi�imiz bir �ey), bunu yapmak i�in bir fonksiyon 
yazman�n mant�kl� oldu�unu g�r�yoruz. ��te tam bir program:

                #include <iostream>

                struct Date
                {
                    // i�te �ye de�i�kenlerimiz
                    int year {};
                    int month {};
                    int day {};
                };

                void print(const Date& date)
                {
                    // �ye de�i�kenler �ye se�im operat�r� (.) kullan�larak eri�ilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // struct� toplu ba�latma

                    today.day = 16; // �ye de�i�kenler �ye se�im operat�r� (.) kullan�larak eri�ilir
                    print(today);   // �ye olmayan fonksiyon normal �a�r� s�zdizimi kullan�larak eri�ilir

                    return 0;
                }

                Bu program �unu yazd�r�r:

                2020/10/16
�zelliklerin ve eylemlerin ( properties and actions ) ayr�lmas�
---------------------------------------------------------------
Etraf�n�za bir bak�n -- her yerde nesneler var: kitaplar ve binalar ve yiyecekler ve hatta siz. Ger�ek hayattaki nesnelerin iki 
ana bile�eni vard�r: 
1) Bir dizi g�zlemlenebilir �zellik (�r. a��rl�k, renk, boyut, kat�l�k, �ekil vb.), ve
2) Bu �zelliklere dayal� olarak ger�ekle�tirebilecekleri veya �zerlerinde ger�ekle�tirilebilecekleri bir dizi eylem
   (�r. a��lma, ba�ka bir �eye zarar verme vb.). Bu �zellikler ve eylemler ayr�lmaz.

Programlamada, �zellikleri de�i�kenlerle, eylemleri ise fonksiyonlarla temsil ederiz.

Yukar�daki Date �rne�inde, �zelliklerimizi (Date'in �ye de�i�kenleri) ve bu �zellikleri kullanarak ger�ekle�tirdi�imiz eylemleri
(print() fonksiyonu) ayr� ayr� tan�mlad���m�z� not edin. Date ve print() aras�ndaki ba�lant�y�, yaln�zca print()'�n
const Date& parametresine dayanarak ��kar�r�z.

Her ikisini de bir ad alan�na koyabilirdik (ikisinin birlikte paketlenmesi gerekti�ini daha belirgin hale getirmek i�in), ancak bu,
program�m�za daha fazla isim ekler ve daha fazla ad alan� �neki ekler, kodumuzu karma��kla�t�r�r.
�zelliklerimizi ve eylemlerimizi tek bir paket olarak birlikte tan�mlayabilece�imiz bir yol olmas� g�zel olurdu.

�ye Fonksiyonlar
----------------
�ye de�i�kenlere ek olarak, s�n�f t�rleri (structlar�, s�n�flar� ve unionlar� i�erir) kendi fonksiyonlar�na da sahip olabilir! 
Bir s�n�f t�r�ne ait olan fonksiyonlara �ye fonksiyonlar denir.

Bir parantez a�al�m�
Di�er nesne y�nelimli dillerde (Java ve C# gibi), bunlara y�ntemler( methods ) denir. C++'da "y�ntem" terimi kullan�lmamas�na
ra�men, ilk �nce bu di�er dilleri ��renen programc�lar hala bu terimi kullanabilir.

�ye fonksiyon olmayan fonksiyonlara, onlar� �ye fonksiyonlardan ay�rt etmek i�in �ye olmayan fonksiyonlar (veya ara s�ra serbest
fonksiyonlar) denir. Yukar�daki print() fonksiyonu bir �ye olmayan fonksiyondur.
Yazar�n notu
Bu derste, �ye fonksiyonlar�n �rneklerini g�stermek i�in structlar� kullanaca��z -- ancak burada g�sterdi�imiz her �ey s�n�flar
i�in de e�it derecede ge�erlidir. Nedenlerini oraya vard���m�zda a��k�a g�rece�iz, gelecek derslerde 
(14.5 -- Public ve private �yeler ve eri�im belirleyicileri) s�n�flar�n �ye fonksiyonlar�na �rnekler g�sterece�iz.

�ye fonksiyonlar, s�n�f t�r� tan�m�n�n i�inde bildirilmeli ve s�n�f t�r� tan�m�n�n i�inde veya d���nda tan�mlanabilir. 
Hat�rlatma olarak, bir tan�m ayn� zamanda bir bildirimdir, bu y�zden bir �ye fonksiyonunu s�n�f�n i�inde tan�mlarsak,
bu bir bildirim olarak say�l�r.

�imdilik i�leri basit tutmak i�in, �ye fonksiyonlar�m�z� s�n�f t�r� tan�m�n�n i�inde tan�mlayaca��z.

�ye Fonksiyon �rne�i
--------------------
Dersin ba��ndaki Date �rne�ini yeniden yazal�m, print()'i bir �ye olmayan fonksiyondan bir �ye fonksiyonuna d�n��t�relim:

                // �ye fonksiyon versiyonu
                #include <iostream>

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() // yazdir ad�nda bir �ye fonksiyon tan�mlar
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // struct� toplu ba�latma

                    today.day = 16; // �ye de�i�kenler �ye se�im operat�r� (.) kullan�larak eri�ilir
                    today.print();  // �ye fonksiyonlar da �ye se�im operat�r� (.) kullan�larak eri�ilir

                    return 0;
                }

                Bu program derlenir ve yukar�dakiyle ayn� sonucu verir:

                2020/10/16
�ye olmayan ve �ye �rnekler aras�nda �� anahtar fark vard�r:

*- print() fonksiyonunu nerede bildiriyoruz (ve tan�ml�yoruz)
*- print() fonksiyonunu nas�l �a��r�yoruz
*- print() fonksiyonunun i�inde �yelere nas�l eri�iyoruz
Her birini s�rayla inceleyelim.

�ye Fonksiyonlar S�n�f T�r� Tan�m�n�n ��inde Bildirilir
-------------------------------------------------------
�ye olmayan �rnekte, print() �ye olmayan fonksiyonu, Date yap�s�n�n d���nda, global ad alan�nda tan�mlan�r. Varsay�lan olarak, 
d�� ba�lant�s� vard�r, bu y�zden di�er kaynak dosyalardan (uygun ileri bildirimle) �a�r�labilir.

�ye �rnekte, print() �ye fonksiyonu, Date yap�s� tan�m�n�n i�inde bildirilir (ve bu durumda, tan�mlan�r). print()'in Date'in bir
par�as� olarak bildirildi�i i�in, bu derleyiciye print()'in bir �ye fonksiyon oldu�unu s�yler.

S�n�f t�r� tan�m�n�n i�inde tan�mlanan �ye fonksiyonlar, dolayl� olarak sat�r i�idir, bu y�zden s�n�f t�r� tan�m� birden �ok kod
dosyas�na dahil edilirse, bir tan�m kural�n� ihlal etmezler.

�ye Fonksiyonlar� �a��rma (ve Dolayl� Nesne (implicit object))
--------------------------------------------------------------
�ye olmayan �rnekte, print(today)'i �a��r�yoruz, burada today (a��k�a) bir arg�man olarak ge�irilir. �ye �rnekte, today.print()'i
�a��r�yoruz. Bu s�zdizimi, �ye de�i�kenlere nas�l eri�ti�imizle (�r. today.day = 16;) tutarl�d�r.

T�m (statik olmayan) �ye fonksiyonlar, o s�n�f t�r�n�n bir nesnesi kullan�larak �a�r�lmal�d�r. Bu durumda, today, print()'in 
�zerinde �a�r�ld��� nesnedir. �ye fonksiyon durumunda, today'i bir arg�man olarak ge�irmemize gerek yok. Bir �ye fonksiyonun 
�zerinde �a�r�ld��� nesne, �ye fonksiyona dolayl� olarak ge�irilir. Bu nedenle, bir �ye fonksiyonun �zerinde �a�r�ld��� nesne
genellikle dolayl� nesne olarak adland�r�l�r.
Ba�ka bir deyi�le, today.print()'i �a��rd���m�zda, today dolayl� nesnedir ve print() �ye fonksiyonuna dolayl� olarak ge�irilir.

��te print()'in �ye olmayan versiyonu tekrar:

                // �ye olmayan print versiyonu
                void print(const Date& date)
                {
                    // �ye de�i�kenler �ye se�im operat�r� (.) kullan�larak eri�ilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }
Bu print() versiyonunun const Date& date referans parametresi vard�r. Fonksiyonun i�inde, �yelere bu referans parametresi
�zerinden eri�iriz, yani date.year, date.month ve date.day. print(today) �a�r�ld���nda, date referans parametresi today arg�man�na
ba�lan�r ve date.year, date.month ve date.day s�ras�yla today.year, today.month ve today.day olarak de�erlendirilir.
�imdi print() �ye fonksiyonunun tan�m�na tekrar bakal�m:
�ye Fonksiyon �rne�i

                void print() // yazdir ad�nda bir �ye fonksiyon tan�mlar
                {
                    std::cout << yil << '/' << ay << '/' << gun;
                }
�ye �rne�inde, �yelere yil, ay ve gun olarak eri�iriz.

Bir �ye fonksiyonun i�inde, �ye se�im operat�r� (.) ile �neki olmayan her �ye tan�mlay�c�, dolayl� nesne ile ili�kilendirilir.
Ba�ka bir deyi�le, today.print() �a�r�ld���nda, today dolayl� nesnemizdir ve yil, ay ve gun (�nekli olmayanlar) s�ras�yla
today.yil, today.ay ve today.gun de�erlerine kar��l�k gelir.

Anahtar nokta �udur ki, �ye olmayan fonksiyonlarla, �zerinde �al��mak i�in bir nesneyi fonksiyona a��k�a ge�irmeliyiz ve �yelere
a��k�a eri�iriz. �ye fonksiyonlarla, �zerinde �al��mak i�in bir nesneyi dolayl� olarak fonksiyona ge�iririz ve �yelere dolayl� 
olarak eri�iriz.

Ba�ka Bir �ye Fonksiyon �rne�i
------------------------------
��te biraz daha karma��k bir �ye fonksiyonla bir �rnek:
                #include <iostream>
                #include <string>

                struct Person
                {
                    std::string name{};
                    int age{};

                    void kisses(const Person& person)
                    {
                        std::cout << name << " kisses " << person.name << '\n';
                    }
                };

                int main()
                {
                    Person joe{ "Joe", 29 };
                    Person kate{ "Kate", 27 };

                    joe.kisses(kate);

                    return 0;
                }
                Bu, ��kt�y� �retir:

                Joe kisses Kate
Bunun nas�l �al��t���n� inceleyelim. �ncelikle, iki Person struct� tan�ml�yoruz, joe ve kate. Sonra, joe.kisses(kate)'i 
�a��r�yoruz. joe burada dolayl� nesnedir ve kate a��k bir arg�man olarak ge�irilir.

kisses() �ye fonksiyonu �al��t���nda, isim tan�mlay�c�s� �ye se�im operat�r�n� (.) kullanmaz, bu y�zden dolayl� nesneye, yani
joe'ya ba�vurur. Bu, joe.isim'e ��z�l�r. person.name, �ye se�im operat�r�n� kullan�r, bu y�zden dolayl� nesneye ba�vurmaz. person,,
kate i�in bir referans oldu�undan, bu kate.name'e ��z�l�r.

Anahtar nokta �udur ki, Bir �ye fonksiyon olmadan, kisses(joe, kate)'i yazm�� olurduk. Bir �ye fonksiyonla, joe.kisses(kate)'i 
yaz�yoruz. �kincisinin ne kadar daha iyi okundu�una ve hangi nesnenin eylemi ba�latt���n�n ve hangisinin destek oldu�unun ne kadar
a��k oldu�una dikkat edin.

�ye De�i�kenler ve Fonksiyonlar Herhangi Bir S�rayla Tan�mlanabilir
-------------------------------------------------------------------
C++ derleyicisi normalde kodu yukar�dan a�a��ya derler. Her isimle kar��la�t���nda, derleyici zaten o isim i�in bir bildirim
g�rm�� olup olmad���n� belirler, b�ylece uygun tip kontrol�n� yapabilir.

Bu, bir �ye olmayan fonksiyonun i�inde, en az�ndan bildirilmemi� bir de�i�kene eri�emez veya bir fonksiyonu �a��ramazs�n�z
anlam�na gelir:
                void x()
                {
                    y(); // hata: y hen�z bildirilmedi, bu y�zden derleyici ne oldu�unu bilmiyor
                }

                int y()
                {
                    return 5;
                }
Ancak, �ye fonksiyonlar (ve �ye veri ba�lat�c�lar�) ile, bu s�n�rlama ge�erli de�ildir ve �yelerimizi istedi�imiz herhangi bir
s�rayla tan�mlayabiliriz. �rne�in:

                struct Foo
                {
                    int m_x{ y() };   // burada y()'yi �a��rmak tamam, ��nk� y() daha sonra tan�mlan�r

                    void x() { y(); } // burada y()'yi �a��rmak tamam, ��nk� y() daha sonra tan�mlan�r
                    int y()  { return 5; }
                };

�ye Fonksiyonlar A��r� Y�klenebilir
------------------------------------
�ye olmayan fonksiyonlar gibi, �ye fonksiyonlar da a��r� y�klenebilir, yeter ki her �ye fonksiyon ay�rt edilebilsin.
��te a��r� y�klenmi� print() �ye fonksiyonlar�na sahip bir Date yap�s� �rne�i:

                #include <iostream>
                #include <string_view>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print()
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }

                    void print(std::string_view prefix)
                    {
                        std::cout << prefix << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 };

                    today.print(); // Tarih::print() �a��r�r
                    std::cout << '\n';

                    today.print("Date: "); // Tarih::yazdir(std::string_view) �a��r�r
                    std::cout << '\n';

                    return 0;
                }
                Bu, �unu yazd�r�r:

                2020/10/14
                Tarih: 2020/10/14
structlar ve �ye Fonksiyonlar
-----------------------------
C'de, structlar�n yaln�zca veri �yeleri vard�r, �ye fonksiyonlar� yoktur. C++'da, s�n�flar tasarlan�rken, Bjarne Stroustrup,
structlar�n (C'den miras al�nan) �ye fonksiyonlara sahip olma yetene�ine sahip olup olmamas� gerekti�ini d���nmek i�in bir miktar
zaman harcad�. D���nd�kten sonra, bunun gerekti�ine karar verdi.
Bir parantez a�al�m�
Bu karar, structlar�n hangi yeni C++ yeteneklerine eri�im hakk� olmas� gerekti�i hakk�nda ba�ka sorular�n ortaya ��kmas�na neden
oldu. Bjarne, structlar�n s�n�rl� bir yetenek alt k�mesine eri�im hakk� vermenin, dilin karma��kl���n� ve kenar durumlar�n�
art�raca��ndan endi�e ediyordu. Basitlik i�in, sonu�ta Bjarne, structlar�n ve s�n�flar�n birle�ik bir kural setine sahip olmas�na 
karar verdi (yani structlar, s�n�flar�n yapabildi�i her �eyi yapabilir ve tam tersi), ve gelenek, structlar�n nas�l
kullan�laca��n� belirleyebilir.

Modern C++'da, structlar�n �ye fonksiyonlara sahip olmas� uygundur. Bu, bizim gelecek ders 14.9 -- Yap�c�lar�na ( constructor )
Giri�'te ele alaca��m�z private bir �ye fonksiyon t�r� olan yap�c�lar� d��lar. Bir yap�c�ya sahip bir s�n�f t�r� art�k bir topluluk
de�ildir ve structlar�m�z�n topluluk olarak kalmas�n� istiyoruz.

*** BEST -> �ye fonksiyonlar, hem structlarla hem de s�n�flarla kullan�labilir. Ancak, structlar, yap�c� �ye fonksiyonlar�n� 
            tan�mlamaktan ka��nmal�d�r, ��nk� bunu yapmak onlar� bir topluluk olmaktan ��kar�r.

Veri �yesi Olmayan S�n�f T�rleri
--------------------------------
Veri �yesi olmayan bir s�n�f t�r� olu�turmak m�mk�nd�r (�r. yaln�zca �ye fonksiyonlara sahip s�n�f t�rleri). Ayr�ca, b�yle bir 
s�n�f t�r�n�n nesnelerini �rnekle�tirmek de m�mk�nd�r:
#include <iostream>

                struct Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo f{};
                    f.printHi(); // �a��rmak i�in nesne gerektirir

                    return 0;
                }
Ancak, bir s�n�f t�r�n�n hi� veri �yesi yoksa, bir s�n�f t�r�n� kullanmak muhtemelen gereksizdir. Bu t�r durumlarda, bunun yerine
bir ad alan� kullanmay� d���n�n (�ye olmayan fonksiyonlar� i�erir). Bu, okuyucuya hi�bir verinin y�netilmedi�ini (ve fonksiyonlar�
�a��rmak i�in bir nesnenin �rnekle�tirilmesini gerektirmedi�ini) daha a��k hale getirir.

                #include <iostream>

                namespace Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo::printHi(); // Hi� bir nesne gerekli de�il

                    return 0;
                }
*** BEST -> S�n�f t�r�n�z�n hi� veri �yesi yoksa, bir ad alan� kullanmay� tercih edin.

14.4 � Const S�n�f Nesneleri ve Const �ye Fonksiyonlar
------------------------------------------------------
5.1 -- Sabit de�i�kenler (isimli sabitler) dersinde, temel bir veri t�r�n�n (int, double, char, vb.) nesnelerinin const anahtar
kelimesi ile sabit yap�labilce�ini ��rendiniz. T�m const de�i�kenler olu�turulduklar� anda ba�lat�lmal�d�r.

                const int x;      // derleme hatas�: ba�lat�lmad�
                const int y{};    // tamam: de�er ba�lat�ld�
                const int z{ 5 }; // tamam: liste ba�lat�ld�

Benzer �ekilde, s�n�f t�r� nesneleri (structlar, s�n�flar ve unionlar) de const anahtar kelimesi kullan�larak sabit yap�labilir.
Bu t�r nesneler de olu�turulduklar� anda ba�lat�lmal�d�r.

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const s�n�f t�r� nesne

                    return 0;
                }

Normal de�i�kenlerle oldu�u gibi, s�n�f t�r� nesnelerinizi de genellikle olu�turulduktan sonra de�i�tirilmediklerini garanti etmek
istedi�inizde const (veya constexpr) yapmak istersiniz.

Sabit nesnelerin veri �yelerini de�i�tirmek yasakt�r
----------------------------------------------------
Bir const s�n�f t�r� nesnesi ba�lat�ld�ktan sonra, nesnenin veri �yelerini de�i�tirmeye y�nelik herhangi bir giri�im yasakt�r,
��nk� bu, nesnenin const-�zelli�ini ihlal eder. Bu, hem �ye de�i�kenleri do�rudan de�i�tirmeyi (e�er onlar public ise), hem de �ye
de�i�kenlerin de�erini ayarlayan �ye fonksiyonlar� �a��rmay� i�erir.

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void incrementDay()
                    {
                        ++day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.day += 1;        // derleme hatas�: const nesnenin �yesini de�i�tiremez
                    today.incrementDay();  // derleme hatas�: const nesnenin �yesini de�i�tiren �ye fonksiyonu �a��ramaz

                    return 0;
                }

Sabit nesneler, sabit olmayan �ye fonksiyonlar� �a��ramaz
---------------------------------------------------------
Bu kodun da bir derleme hatas� olu�turdu�unu g�rmek sizi �a��rtabilir:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print()
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.print();  // derleme hatas�: sabit olmayan �ye fonksiyonu �a��ramaz

                    return 0;
                }

print() bir �ye de�i�keni de�i�tirmeye �al��masa bile, today.print() �a�r�m�z hala bir const ihlalidir. Bu, print() �ye
fonksiyonunun kendisinin const olarak bildirilmedi�i i�in olur. Derleyici, const bir nesne �zerinde sabit olmayan bir �ye
fonksiyonu �a��rmam�za izin vermez.

Sabit �ye Fonksiyonlar
----------------------
Yukar�daki sorunu ��zmek i�in, print()'i bir const �ye fonksiyon yapmam�z gerekiyor. Bir const �ye fonksiyon, nesneyi 
de�i�tirmeyece�ini veya herhangi bir sabit olmayan �ye fonksiyonlar� �a��rmayaca��n� (��nk� onlar nesneyi de�i�tirebilir) garanti
eden bir �ye fonksiyondur.
print()'i bir const �ye fonksiyon yapmak kolayd�r - sadece const anahtar kelimesini, parametre listesinden sonra, ancak fonksiyon 
g�vdesinden �nce fonksiyon prototipine ekleriz:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // �imdi bir const �ye fonksiyon
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.print();  // tamam: const nesne const �ye fonksiyonu �a��rabilir

                    return 0;
                }

Yukar�daki �rnekte, print() bir const �ye fonksiyon haline getirildi, bu da onu const nesnelerde (�rne�in today gibi) 
�a��rabilece�imiz anlam�na gelir.
Bir �ye fonksiyonun const olarak i�aretlenmesi, bu fonksiyonun nesneyi de�i�tirmeyece�ini veya herhangi bir const olmayan �ye
fonksiyonlar� �a��rmayaca��n� (��nk� onlar nesneyi de�i�tirebilir) garanti eder. �rne�in:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void incrementDay() const // const olarak i�aretlendi
                    {
                        ++day; // derleme hatas�: const fonksiyon �yeyi de�i�tiremez
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.incrementDay();

                    return 0;
                }

Bu �rnekte, incrementDay() const bir �ye fonksiyon olarak i�aretlenmi�tir, ancak gun'u de�i�tirmeye �al���r. Bu bir derleme hatas�
olu�turacakt�r.

Sabit �ye Fonksiyonlar Sabit Olmayan Nesneler �zerinde �a�r�labilir
-------------------------------------------------------------------
Sabit �ye fonksiyonlar, sabit olmayan nesneler �zerinde de �a�r�labilir:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const

                    today.print();  // tamam: sabit olmayan nesne �zerinde const �ye fonksiyonu �a��rabilir

                    return 0;
                }
��nk� const �ye fonksiyonlar hem const hem de non-const nesneler �zerinde �a�r�labilir, bir �ye fonksiyonun nesnenin durumunu
de�i�tirmemesi durumunda, bu fonksiyonun const yap�lmas� gerekir.
*** BEST -> Bir �ye fonksiyonun nesnenin durumunu de�i�tirmemesi (ve hi�bir zaman de�i�tirmeyece�i) durumunda, bu fonksiyonun
const yap�lmas� gerekir, b�ylece hem const hem de non-const nesneler �zerinde �a�r�labilir.

Hangi �ye fonksiyonlara const uygulayaca��n�za dikkat edin. Bir �ye fonksiyon bir kez const olarak yap�ld���nda, bu fonksiyon 
const nesneler �zerinde �a�r�labilir. Bir �ye fonksiyonun const'unun daha sonra kald�r�lmas�, const bir nesne �zerinde bu �ye 
fonksiyonu �a��ran herhangi bir kodu bozacakt�r.

Const Referans Yoluyla Const Nesneler
-------------------------------------
Const yerel de�i�kenlerin �rnekle�tirilmesi, const nesneler olu�turman�n bir yoludur, ancak daha yayg�n bir yol, bir nesneyi const
referans yoluyla bir fonksiyona ge�irmektir. 12.5 -- Lvalue referans� ile ge�i� dersinde, s�n�f t�r� arg�manlar�n� de�er yerine 
const referans olarak ge�irmenin avantajlar�n� ele ald�k. Tekrarlamak gerekirse, bir s�n�f t�r� arg�man�n� de�er olarak ge�irmek,
s�n�f�n bir kopyas�n�n yap�lmas�na neden olur (bu yava�t�r) - �o�u zaman, bir kopyaya ihtiyac�m�z yoktur, orijinal arg�mana bir 
referans i�imizi g�r�r ve bir kopya yapmay� �nler. Fonksiyonun const lvalue arg�manlar� ve rvalue arg�manlar� (�r. literaller ve 
ge�ici nesneler) kabul etmesine izin vermek i�in referans� genellikle const yapar�z.

A�a��daki kodda neyin yanl�� oldu�unu anlayabilir misiniz?

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() // non-const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                void doSomething(const Date &date)
                {
                    date.print();
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const
                    today.print();

                    doSomething(today);

                    return 0;
                }
                
Cevap, doSomething() fonksiyonunun i�inde, date const bir nesne olarak ele al�n�r (��nk� const referans ile ge�irilmi�tir).
Ve bu const date ile, const olmayan �ye fonksiyonu yazdir()'i �a��r�yoruz. Const nesneler �zerinde const olmayan �ye fonksiyonlar�
�a��ramayaca��m�z i�in, bu bir derleme hatas� olu�turacakt�r.

D�zeltme basittir: print()'i const yap�n:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // now const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                void doSomething(const Date &date)
                {
                    date.print();
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const
                    today.print();

                    doSomething(today);

                    return 0;
                }
�imdi doSomething() fonksiyonunda, const date ba�ar�yla const �ye fonksiyonu print()'i �a��rabilecektir.

�ye Fonksiyonun Const ve Non-Const A��r� Y�klemesi
--------------------------------------------------
Son olarak, �ok s�k yap�lmamas�na ra�men, bir �ye fonksiyonun const ve non-const versiyonunu a��r� y�klemek m�mk�nd�r. Bu, const
nitelikleyicinin fonksiyonun imzas�n�n bir par�as� olarak kabul edildi�i i�in �al���r, bu y�zden yaln�zca const'lar� farkl� olan
iki fonksiyon farkl� kabul edilir.

                #include <iostream>

                struct Something
                {
                    void print()
                    {
                        std::cout << "non-const\n";
                    }

                    void print() const
                    {
                        std::cout << "const\n";
                    }
                };

                int main()
                {
                    Something s1{};
                    s1.print(); // calls print()

                    const Something s2{};
                    s2.print(); // calls print() const

                    return 0;
                }
                Bu, �unu yazd�r�r:

                non-const
                const
Bir fonksiyonun const ve non-const versiyonu ile a��r� y�kleme genellikle d�n�� de�erinin const'l�kta farkl� olmas� gerekti�inde
yap�l�r. Bu olduk�a nadirdir.

14.5 � Public ve Private �yeler ve Eri�im Belirleyiciler
--------------------------------------------------------
Bir sonbahar g�n�nde caddede y�r�yorsunuz ve bir burrito yiyorsunuz. Oturacak bir yer ar�yorsunuz, etraf�n�za bak�yorsunuz.
Solunuzda �imleri bi�ilmi�, g�lgelik a�a�lar� olan, birka� rahats�z edici bank� ve yak�ndaki oyun alan�nda ba��ran �ocuklar� olan
bir park var. Sa��n�zda bir yabanc�n�n evi var. Pencereden, rahat bir koltuk ve ��t�rdayan bir ��mine g�r�yorsunuz.

A��r bir i� �ekerek, park� se�iyorsunuz.

Se�iminizin ana belirleyicisi, park�n bir public alan olmas�, evin ise private olmas�d�r. Siz (ve herkes) public alanlara serbest�e
eri�ebilirsiniz. Ancak evin �yeleri (veya a��k�a izin verilen ki�iler) private konuta eri�ebilir.

�ye Eri�imi
-----------
Benzer bir kavram, bir s�n�f t�r�n�n �yelerine de uygulan�r. Bir s�n�f t�r�n�n her �yesinin, kimin o �yeye eri�ebilece�ini
belirleyen bir eri�im d�zeyi ad� verilen bir �zelli�i vard�r.

C++'da �� farkl� eri�im d�zeyi vard�r: public, private ve protected. Bu derste, en yayg�n kullan�lan iki eri�im d�zeyini ele 
alaca��z: public ve private.
Bir �yeye eri�ildi�inde, derleyici �yenin eri�im d�zeyinin o �yeye eri�ime izin verip vermedi�ini kontrol eder. Eri�ime izin 
verilmezse, derleyici bir derleme hatas� olu�turur. Bu eri�im d�zeyi sistemine bazen gayri resmi olarak eri�im kontrolleri denir.
Bir yap�n�n �yeleri varsay�lan olarak public'tir
------------------------------------------------
Public eri�im d�zeyine sahip �yelere public �yeler denir. Public �yeler, nas�l eri�ilece�i konusunda herhangi bir k�s�tlama 
olmayan bir s�n�f t�r�n�n �yeleridir. A��l�� analojimizdeki park gibi, public �yelere herkes (kapsam dahilinde olduklar� s�rece)
eri�ebilir.

Public �yelere, ayn� s�n�f�n di�er �yeleri taraf�ndan eri�ilebilir. �zellikle, public �yelere public taraf�ndan da eri�ilebilir,
bu da belirli bir s�n�f t�r�n�n �yelerinin d���nda bulunan kodu ifade ederiz. Public �rnekleri aras�nda �ye olmayan fonksiyonlar 
ve di�er s�n�f t�rlerinin �yeleri bulunur.

Anahtar nokta �udur ki, Bir yap�n�n �yeleri varsay�lan olarak public'tir. Public �yelere, s�n�f t�r�n�n di�er �yeleri ve public 
taraf�ndan eri�ilebilir.

"Public" terimi, belirli bir s�n�f t�r�n�n �yelerinin d���nda bulunan kodu ifade etmek i�in kullan�l�r. Bu, �ye olmayan 
fonksiyonlar� ve di�er s�n�f t�rlerinin �yelerini i�erir. Varsay�lan olarak, bir struct'�n t�m �yeleri public �yelerdir.
A�a��daki struct'� d���n�n:

                #include <iostream>

                struct Date
                {
                    // struct �yeleri varsay�lan olarak public'tir, herkes taraf�ndan eri�ilebilir
                    int year {};       // varsay�lan olarak public
                    int month {};      // varsay�lan olarak public
                    int day {};        // varsay�lan olarak public

                    void print() const // varsay�lan olarak public
                    {
                        // public �yelere s�n�f tipinin �ye fonksiyonlar�nda eri�ilebilir
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                // �ye olmayan fonksiyon main "public" k�sm�n�n bir par�as�d�r
                int main()
                {
                    Date today { 2020, 10, 14 }; // struct'�m�z� topluca ba�lat�yoruz

                    // public �yelere public taraf�ndan eri�ilebilir
                    today.day = 16; // tamam: day �yesi public
                    today.print();  // tamam: print() �ye fonksiyonu public

                    return 0;
                }
Bu �rnekte, �yelere �� yerde eri�ilir:

*- �ye fonksiyonu print() i�inde, implicit nesnenin year, month ve day �yelerine eri�iriz.
*- main() i�inde, today.day'a do�rudan eri�iriz ve de�erini ayarlar�z.
*- main() i�inde, today.print() �ye fonksiyonunu �a��r�r�z.
Bu �� eri�ime de izin verilir ��nk� public �yelere her yerden eri�ilebilir. main() Date'in bir �yesi olmad��� i�in, public'in bir
par�as� olarak kabul edilir. Ancak, public'in public �yelere eri�im hakk� oldu�u i�in, main() Date'in �yelerine (today.print() 
�a�r�s�n� i�erir) do�rudan eri�ebilir.

Bir s�n�f�n �yeleri varsay�lan olarak private'dir
-------------------------------------------------
Private eri�im seviyesine sahip �yelere private �yeler denir. Private �yeler, yaln�zca ayn� s�n�f�n di�er �yeleri taraf�ndan 
eri�ilebilen bir s�n�f tipinin �yeleridir.
A�a��daki �rne�i d���n�n, bu �rnek yukar�daki �rnekle neredeyse ayn�d�r:

                #include <iostream>

                class Date // art�k bir struct yerine bir s�n�f
                {
                    // s�n�f �yeleri varsay�lan olarak private'dir, yaln�zca di�er �yeler taraf�ndan eri�ilebilir
                    int m_year {};     // varsay�lan olarak private
                    int m_month {};    // varsay�lan olarak private
                    int m_day {};      // varsay�lan olarak private

                    void print() const // varsay�lan olarak private
                    {
                        // private �yelere �ye fonksiyonlarda eri�ilebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // derleme hatas�: art�k toplu ba�latma kullan�lamaz

                    // private �yelere public taraf�ndan eri�ilemez
                    today.m_day = 16; // derleme hatas�: m_day �yesi private
                    today.print();    // derleme hatas�: print() �ye fonksiyonu private

                    return 0;
                }
Bu �rnekte, �yelere ayn� �� yerde eri�ilir:
*- �ye fonksiyonu print() i�inde, implicit nesnenin m_year, m_month ve m_day �yelerine eri�iriz.
*- main() i�inde, today.m_day'a do�rudan eri�iriz ve de�erini ayarlar�z.
*- main() i�inde, today.print() �ye fonksiyonunu �a��r�r�z.
Ancak, bu program� derlerseniz, �� derleme hatas� olu�tu�unu g�receksiniz.

main() i�inde, today.m_day = 16 ve today.print() ifadeleri art�k derleme hatalar� olu�turur. Bu, main()'in public'in bir par�as� 
olmas� ve public'in private �yelere do�rudan eri�imine izin verilmemesi nedeniyledir.

print() i�inde, m_year, m_month ve m_day �yelerine eri�ime izin verilir. Bu, print()'in s�n�f�n bir �yesi olmas� ve s�n�f�n
�yelerinin private �yelere eri�imine izin verilmesi nedeniyledir.

Peki ���nc� derleme hatas� nereden geliyor? Belki de �a��rt�c� bir �ekilde, today'�n ba�lat�lmas� art�k bir derleme hatas� 
olu�turuyor. Ders 13.6 -- Struct aggregate initialization'da, bir toplulu�un "private veya protected olmayan statik olmayan veri 
�yeleri olmamas� gerekti�ini" belirttik. Date s�n�f�m�z�n private veri �yeleri var (��nk� s�n�flar�n �yeleri varsay�lan olarak 
private), bu y�zden Date s�n�f�m�z bir topluluk olarak nitelendirilmiyor. Bu y�zden, art�k onu ba�latmak i�in toplu ba�latma
kullanamay�z.

S�n�flar� (genellikle topluluk olmayanlar�) nas�l d�zg�n bir �ekilde ba�lataca��m�z�, yakla�an ders 14.9 -- Constructorlara
Giri�'te tart��aca��z.

*** Ana Fikir
Bir s�n�f�n �yeleri varsay�lan olarak private'dir. Private �yelere s�n�f�n di�er �yeleri taraf�ndan eri�ilebilir, ancak public
taraf�ndan eri�ilemez. Private �yelere sahip bir s�n�f art�k bir topluluk de�ildir ve bu nedenle toplu ba�latma kullanamaz.

Private �ye De�i�kenlerinizi Adland�rma
---------------------------------------
C++'da, private veri �yelerini "m_" �nekiyle ba�layacak �ekilde adland�rma yayg�n bir uygulamad�r. Bu, birka� �nemli nedenle
yap�l�r. Bir s�n�f�n a�a��daki �ye fonksiyonunu d���n�n:

                // Private �ye m_name'i name parametresinin de�erine ayarlayan bir �ye fonksiyon
                void setName(std::string_view name)
                {
                    m_name = name;
                }
�ncelikle, "m_" �neki, bir �ye fonksiyonu i�indeki veri �yelerini fonksiyon parametrelerinden veya yerel de�i�kenlerden kolayca
ay�rt etmemizi sa�lar. "m_name" in bir �ye oldu�unu ve "name" in olmad���n� kolayca g�rebiliriz. Bu, bu fonksiyonun s�n�f�n
durumunu de�i�tirdi�ini a��k�a belirtir. Ve bu �nemlidir ��nk� bir veri �yesinin de�erini de�i�tirdi�imizde, bu de�i�iklik �ye 
fonksiyonun kapsam�n�n �tesinde kal�r (fonksiyon parametrelerine veya yerel de�i�kenlere yap�lan de�i�iklikler genellikle bu
�ekilde olmaz).

Bu, yerel statik de�i�kenler i�in "s_" �neklerini ve global de�i�kenler i�in "g_" �neklerini kullanmay� �nermemizin ayn� nedenidir.
�kincisi, "m_" �neki, private �ye de�i�kenler ile yerel de�i�kenlerin, fonksiyon parametrelerinin ve �ye fonksiyonlar�n�n adlar�
aras�nda ad �ak��malar�n� �nlemeye yard�mc� olur.

E�er private �yemizi m_name yerine name olarak adland�rm�� olsayd�k:
Name fonksiyon parametremiz, name private veri �yesini g�lgede b�rak�rd�.
E�er name ad�nda bir �ye fonksiyonumuz olsayd�, name tan�mlay�c�s�n�n yeniden tan�mlanmas� nedeniyle bir derleme hatas� al�rd�k.
*** BEST -> Private �yelerinizi, onlar� yerel de�i�kenlerin, fonksiyon parametrelerinin ve �ye fonksiyonlar�n adlar�ndan ay�rt 
etmeye yard�mc� olmak i�in "m_" �nekiyle ba�layacak �ekilde adland�rmay� d���n�n.

Eri�im Seviyelerini Eri�im Belirleyicileri ile Ayarlama
-------------------------------------------------------
Varsay�lan olarak, struct'lar�n (ve unionlar�n) �yeleri public'tir ve s�n�flar�n �yeleri private'dir.
Ancak, �yelerimizin eri�im seviyesini bir eri�im belirleyicisi kullanarak a��k�a ayarlayabiliriz. Bir eri�im belirleyicisi,
belirleyiciyi takip eden t�m �yelerin eri�im seviyesini ayarlar. C++ �� eri�im belirleyicisi sa�lar: public:, private: ve protected

A�a��daki �rnekte, print() �ye fonksiyonunun public taraf�ndan kullan�labilmesini sa�lamak i�in public: eri�im belirleyicisini ve
veri �yelerimizi private yapmak i�in private: eri�im belirleyicisini kullan�yoruz.

                class Date
                {
                // Burada tan�mlanan herhangi bir �ye varsay�lan olarak private olurdu

                public: // i�te bizim public eri�im belirleyicimiz

                    void print() const // yukar�daki public: belirleyici nedeniyle public
                    {
                        // �yeler di�er private �yelere eri�ebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }

                private: // i�te bizim private eri�im belirleyicimiz

                    int m_year { 2020 };  // yukar�daki private: belirleyici nedeniyle private
                    int m_month { 14 }; // yukar�daki private: belirleyici nedeniyle private
                    int m_day { 10 };   // yukar�daki private: belirleyici nedeniyle private
                };

                int main()
                {
                    Date d{};
                    d.print();  // tamam, main() public �yelere eri�ebilir

                    return 0;
                }
Bu �rnek derlenir. Print() public: eri�im belirleyicisi nedeniyle bir public �ye oldu�u i�in, main() (public'in bir par�as� olan)
ona eri�ebilir. Private �yelere sahip oldu�umuz i�in, d'yi topluca ba�latamay�z. Bu �rnekte, bunun yerine varsay�lan �ye 
ba�latmas�n� kullan�yoruz (ge�ici bir ��z�m olarak).

S�n�flar private eri�ime varsay�lan olarak sahip oldu�u i�in, �nc� private: eri�im belirleyicisini atlayabilirsiniz:

                Class Foo
                {
                // s�n�flar varsay�lan olarak private �yelere sahip oldu�u i�in burada private eri�im belirleyicisine gerek yok
                    int m_something {};  // varsay�lan olarak private
                };
Ancak, s�n�flar ve struct'lar farkl� eri�im seviyesi varsay�lanlar�na sahip oldu�u i�in, bir�ok geli�tirici a��k olmay� tercih 
eder:

                class Foo
                {
                private: // gereksiz, ancak ard�ndan gelenlerin private oldu�unu a��k�a belirtir
                    int m_something {};  // varsay�lan olarak private
                };
Bu teknik olarak gereksiz olsa da, explicit private: belirleyicisinin kullan�lmas�, ard�ndan gelen �yelerin private oldu�unu 
a��k�a belirtir, Foo'nun bir s�n�f m� yoksa bir struct m� olarak tan�mland���na dayanarak varsay�lan eri�im seviyesini ��karmadan.

Eri�im Seviyesi �zeti
---------------------
��te farkl� eri�im seviyelerinin h�zl� bir �zeti:

Bir s�n�f tipi, herhangi bir s�rayla herhangi bir say�da eri�im belirleyicisini kullanabilir ve bunlar tekrar tekrar 
kullan�labilir (�rne�in, baz� public �yeleriniz, ard�ndan baz� private olanlar, ard�ndan daha fazla public olanlar olabilir).

�o�u s�n�f, �e�itli �yeler i�in hem private hem de public eri�im belirleyicilerini kullan�r. Bu konuda bir �rne�i bir sonraki 
b�l�mde g�rece�iz.
| Eri�im D�zeyi | Eri�im Belirleyici | �ye Eri�imi | T�retilmi� S�n�f Eri�imi  |
|---------------|---------------------|-------------|--------------------------|
| Public        | `public:`           | evet        | evet                     |
| Protected     | `protected:`        | evet        | evet                     |
| Private       | `private:`          | evet        | hay�r                    |

Struct'lar ve S�n�flar i�in Eri�im Seviyesi En �yi Uygulamalar�
---------------------------------------------------------------
Art�k eri�im seviyelerinin ne oldu�unu anlad���m�za g�re, nas�l kullanaca��m�z� konu�al�m.
Struct'lar tamamen eri�im belirleyicilerinden ka��nmal�d�r, yani t�m struct �yeleri varsay�lan olarak public olacakt�r.
Struct'lar�m�z�n topluluklar olmas�n� istiyoruz ve topluluklar yaln�zca public �yelere sahip olabilir. Public: eri�im
belirleyicisinin kullan�lmas� varsay�lanla gereksiz olurdu ve private: veya protected: kullanmak struct'� bir topluluk olmaktan 
��kar�rd�.

S�n�flar genellikle yaln�zca private (veya protected) veri �yelerine sahip olmal�d�r (varsay�lan private eri�im seviyesini
kullanarak veya private: (veya protected) eri�im belirleyicisini kullanarak). Bunun gerek�esini bir sonraki ders olan
14.6 -- Eri�im Fonksiyonlar�'nda tart��aca��z.

S�n�flar normalde public �ye fonksiyonlar�na sahip olur (bu nedenle bu �ye fonksiyonlar, nesne olu�turulduktan sonra public 
taraf�ndan kullan�labilir). Ancak, nadiren �ye fonksiyonlar private (veya protected) yap�l�r e�er public taraf�ndan kullan�lmalar�
ama�lanmam��sa.

*** BEST -> S�n�flar genellikle �ye de�i�kenlerini private (veya protected) yapmal� ve �ye fonksiyonlar�n� public yapmal�d�r.
Struct'lar genellikle eri�im belirleyicilerini kullanmaktan ka��nmal�d�r (t�m �yeler varsay�lan olarak public olacakt�r).

Eri�im Seviyeleri S�n�f Baz�nda �al���r
---------------------------------------
C++ eri�im seviyelerinin s�kl�kla ka��r�lan veya yanl�� anla��lan bir inceli�i, �yelere eri�imin s�n�f baz�nda tan�mland���,
nesne baz�nda tan�mlanmad���d�r.

Bir �ye fonksiyonun do�rudan private �yelere eri�ebilece�ini zaten biliyorsunuz. Ancak, eri�im seviyeleri s�n�f baz�nda oldu�u 
i�in, bir �ye fonksiyonu ayn� s�n�f tipinden olan ve kapsamda olan herhangi bir di�er nesnenin private �yelerine de do�rudan
eri�ebilir.Bunu bir �rnekle g�sterelim:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Person
                {
                private:
                    std::string m_name{};

                public:
                    void kisses(const Person& p) const
                    {
                        std::cout << m_name << " kisses " << p.m_name << '\n';
                    }

                    void setName(std::string_view name)
                    {
                        m_name = name;
                    }
                };

                int main()
                {
                    Person joe;
                    joe.setName("Joe");

                    Person kate;
                    kate.setName("Kate");

                    joe.kisses(kate);

                    return 0;
                }
                Bu, �unu yazd�r�r:

                Joe kisses Kate
Burada dikkat edilmesi gereken birka� �ey var.

�ncelikle, m_name private yap�ld�, bu y�zden yaln�zca Person s�n�f�n�n �yeleri taraf�ndan eri�ilebilir (public taraf�ndan de�il).
�kincisi, s�n�f�m�z�n private �yeleri oldu�u i�in, bir topluluk de�ildir ve Person nesnelerimizi ba�latmak i�in toplu ba�latma
kullanamay�z. Bu soruna uygun bir ��z�m bulana kadar, Person nesnelerimize bir isim atamam�za izin veren setName() ad�nda bir
public �ye fonksiyon olu�turduk.

���nc�s�, kisses() bir �ye fonksiyon oldu�u i�in, private �ye m_name'e do�rudan eri�im hakk�na sahiptir. Ancak, p.m_name'e de
do�rudan eri�im hakk�na sahip oldu�unu g�rmek sizi �a��rtabilir! Bu, p'nin bir Person nesnesi oldu�u ve kisses()'in kapsamda olan
herhangi bir Person nesnesinin private �yelerine eri�ebilece�i i�in �al���r!
Bu konuyu operat�r a��r� y�kleme b�l�m�nde daha fazla �rneklerle g�rece�iz.

Teknik ve pratik a��dan struct'lar ve s�n�flar aras�ndaki fark
--------------------------------------------------------------
Art�k eri�im seviyelerini ele ald���m�za g�re, struct'lar ve s�n�flar aras�ndaki teknik farklar� nihayet tart��abiliriz.
Haz�r m�s�n�z?
Bir s�n�f �yelerini varsay�lan olarak private yapar, oysa bir struct �yelerini varsay�lan olarak public yapar.
Evet, bu kadar. :))

Yazar�n Notu

Titiz olmak gerekirse, bir tane daha k���k bir fark var -- struct'lar di�er s�n�f t�rlerinden public olarak miras al�r ve s�n�flar
private olarak miras al�r. Bu konunun ne anlama geldi�ini, miras b�l�m�nde ele alaca��z, ancak bu belirli nokta pratik olarak 
�nemsizdir ��nk� zaten miras i�in varsay�lanlara g�venmemelisiniz.
Pratikte, struct'lar� ve s�n�flar� farkl� �ekillerde kullan�r�z.

Bir kural olarak, a�a��dakilerin t�m� do�ru oldu�unda bir struct kullan�n:

*- K�s�tl� eri�imden fayda sa�lamayan basit bir veri koleksiyonunuz var.
*- Toplu ba�latma yeterlidir.
*- S�n�f de�i�mezleriniz, kurulum ihtiya�lar�n�z veya temizleme ihtiya�lar�n�z yok.
*- Struct'lar�n kullan�labilece�i birka� �rnek: constexpr global program verileri, bir nokta struct'�
   (private yap�lmalar�ndan fayda sa�lamayan basit bir int �ye koleksiyonu), bir fonksiyondan bir veri seti d�nd�rmek i�in
   kullan�lan struct'lar.

Aksi takdirde bir s�n�f kullan�n.

Struct'lar�m�z�n topluluklar olmas�n� istiyoruz. Yani, struct'�n�z� bir topluluk olmaktan ��karacak herhangi bir �zellik
kullan�yorsan�z, muhtemelen bir s�n�f kullanmal�s�n�z (ve s�n�flar i�in t�m en iyi uygulamalar� takip etmelisiniz).
*/