#include <iostream>

int main()
{
    return 0;
}
/*

13.1 � Program Tan�ml� (Kullan�c� Tan�ml�) T�rlerin Giri�i 
----------------------------------------------------------
Temel t�rler, C++ dilinin �ekirdek par�as� olarak tan�mland���ndan, hemen kullan�labilirler. �rne�in, bir de�i�keni int veya
double t�r�nde tan�mlamak istiyorsak, bunu hemen yapabiliriz:

                    int x; // 'int' temel t�r�nde de�i�ken tan�mla
                    double d; // 'double' temel t�r�nde de�i�ken tan�mla

Bu, temel t�rlerin basit geni�lemeleri olan bile�ik t�rler (fonksiyonlar, i�aret�iler, referanslar ve diziler dahil) i�in de 
ge�erlidir:

                    void fcn(int) {}; // 'void()(int)' t�r�nde bir fonksiyon tan�mla
                    int* ptr; // 'int'e i�aret eden' bile�ik t�r�nde de�i�ken tan�mla
                    int& ref { x }; // 'int'e referans' bile�ik t�r�nde de�i�ken tan�mla (x ile ba�lat�ld�)
                    int arr[5]; // 5 tam say�dan olu�an bir dizi tan�mla, t�r� 'int[5]' (bunu gelecekteki bir b�l�mde ele alaca��z)

Bu, C++ dilinin bu t�rler i�in t�r adlar�n� (ve sembollerini) ne anlama geldi�ini zaten bildi�i i�in �al���r - herhangi bir tan�m
sa�lamam�z veya i�e aktarmam�z gerekmez.

Ancak, mevcut bir t�r i�in yeni bir ad tan�mlamam�za izin veren bir t�r takma ad�n�n (10.7 dersinde tan�t�lan Typedefs ve t�r
takma adlar�) durumunu d���n�n. Bir t�r takma ad�, programa yeni bir tan�mlay�c� ekledi�i i�in, bir t�r takma ad� kullan�lmadan
�nce tan�mlanmal�d�r:

                    #include <iostream>

                    using length = int; // 'length' tan�mlay�c�s� olan bir t�r takma ad� tan�mla

                    int main()
                    {
                        length x { 5 }; // 'length'i burada kullanabiliriz ��nk� onu yukar�da tan�mlad�k
                        std::cout << x << '\n';

                        return 0;
                    }

E�er length tan�m�n� atlat�rsak, derleyici bir length�in ne oldu�unu bilmez ve bu t�r� kullanarak bir de�i�ken tan�mlamay�
denedi�imizde �ikayet eder. Length i�in tan�m bir nesne olu�turmaz � sadece derleyiciye bir length�in ne oldu�unu s�yler, b�ylece
daha sonra kullan�labilir.

Kullan�c� Tan�ml� / Program Tan�ml� T�rler Nedir?
-------------------------------------------------
�nceki b�l�m�n giri�inde (12.1 � Bile�ik Veri T�rlerine Giri�), bir kesiri, kavramsal olarak birbirine ba�l� olan bir pay ve payda
ile saklama iste�ini tan�tt�k. Bu derste, bir kesirin pay ve paydas�n� ba��ms�z olarak saklamak i�in iki ayr� tam say� kullanman�n
zorluklar�n� tart��t�k.

E�er C++'ta yerle�ik bir kesir t�r� olsayd�, bu m�kemmel olurdu � ama yok. Ve C++'ta, birinin ihtiya� duyabilece�i her �eyi 
�nceden tahmin etmek (hele bunlar� uygulamak ve test etmek) m�mk�n olmad��� i�in, potansiyel olarak yararl� y�zlerce di�er t�r
de dahil de�il.

Bunun yerine, C++ bu t�r sorunlar� farkl� bir �ekilde ��zer: programlar�m�zda kullanmak �zere tamamen yeni, �zel t�rler
olu�turmam�za izin vererek! Bu t�r t�rler genellikle kullan�c� tan�ml� t�rler olarak adland�r�l�r (ancak program tan�ml� t�rler
teriminin daha iyi oldu�unu d���n�yoruz � bu dersin ilerleyen k�sm�nda fark� tart��aca��z). C++'ta bunu sa�layan iki kategori
bile�ik t�r vard�r: numaraland�r�lm�� t�rler (kapsams�z ve kapsaml� numaraland�rmalar dahil (unscoped and scoped enumerations) ve
s�n�f t�rleri (yap�lar(structs),s�n�flar (classes) ve birlikler (unions) dahil).

                    // Derleyicinin bir Fraction'�n ne oldu�unu anlamas� i�in Fraction ad�nda bir program tan�ml� t�r tan�mlay�n
                    // (Bir struct'�n ne oldu�unu ve nas�l kullan�laca��n� bu b�l�m�n ilerleyen k�sm�nda a��klayaca��z)
                    // Bu sadece bir Fraction t�r�n�n neye benzedi�ini tan�mlar, bir tane olu�turmaz
                    struct Fraction
                    {
	                    int pay {};
	                    int payda {};
                    };

                    // �imdi Fraction t�r�m�z� kullanabiliriz
                    int main()
                    {
	                    Fraction f{ 3, 4 }; // Bu asl�nda f ad�nda bir Fraction nesnesi olu�turur

	                    return 0;
                    }

Bu �rnekte, yeni bir program tan�ml� t�r olan Fraction�� tan�mlamak i�in struct anahtar kelimesini kullan�yoruz (global kapsamda,
b�ylece dosyan�n geri kalan�nda her yerde kullan�labilir). Bu herhangi bir bellek ay�rmaz � sadece derleyiciye bir Fraction��n
neye benzedi�ini s�yler, b�ylece daha sonra Fraction t�r�nde nesneler ay�rabiliriz. Daha sonra, main() i�inde, f ad�nda bir
Fraction t�r�nde de�i�ken olu�turuyoruz (ve ba�lat�yoruz).

Program tan�ml� t�r tan�mlar� her zaman noktal� virg�lle biter. T�r tan�m�n�n sonunda noktal� virg�l� eklememek yayg�n bir
programc� hatas�d�r ve hata ay�klamas� zor olabilir ��nk� derleyici genellikle t�r tan�m�ndan sonraki sat�rda hata verir. �rne�in,
yukar�daki �rnekte Fraction tan�m�n�n sonundaki noktal� virg�l� ��kar�rsan�z (8. sat�r), derleyici muhtemelen main() tan�m�
hakk�nda (11. sat�r) �ikayet eder.

*** Uyar� -> T�r tan�mlar�n�z� bir noktal� virg�lle bitirmeyi unutmay�n, aksi takdirde derleyici genellikle bir sonraki kod
             sat�r�nda hata verir.

Program Tan�ml� T�rlerin Adland�r�lmas�
---------------------------------------
Geleneksel olarak, program tan�ml� t�rler b�y�k harfle ba�lar ve bir sonek kullanmazlar (�r. Fraction, fraction, fraction_t veya 
Fraction_t de�il).

*** BEST -> Program tan�ml� t�rlerinizi b�y�k harfle ba�lat�n ve bir sonek kullanmay�n.

Yeni programc�lar bazen a�a��daki gibi de�i�ken tan�mlar�n� t�r ad� ve de�i�ken ad� aras�ndaki benzerlik nedeniyle kafa
kar��t�r�c� bulabilirler:

                    Fraction fraction {}; // Fraction t�r�nde fraction ad�nda bir de�i�ken olu�turur

Bu, di�er herhangi bir de�i�ken tan�m�ndan farkl� de�ildir: �nce t�r (Fraction) gelir (ve Fraction b�y�k harfle ba�lad��� i�in, 
bunun bir program tan�ml� t�r oldu�unu biliyoruz), ard�ndan de�i�ken ad� (fraction) ve ard�ndan iste�e ba�l� bir ba�lat�c�. 
C++ b�y�k/k���k harfe duyarl� oldu�u i�in burada bir adland�rma �ak��mas� yok!

�ok Dosyal� Bir Program Boyunca Program Tan�ml� T�rlerin Kullan�lmas�
---------------------------------------------------------------------
Bir program tan�ml� t�r� kullanan her kod dosyas�, t�r�n kullan�ld��� yerden �nce tam t�r tan�m�n� g�rmelidir. �leri bildirim
yeterli de�ildir. Bu, derleyicinin o t�rden nesneler i�in ne kadar bellek ay�rmas� gerekti�ini bilmesi gereklidir.

T�r tan�mlar�n� ihtiya� duyan kod dosyalar�na yaymak i�in, program tan�ml� t�rler genellikle ba�l�k dosyalar�nda tan�mlan�r ve 
ard�ndan o t�r tan�m�n� gerektiren her kod dosyas�na #include edilir. Bu ba�l�k dosyalar� genellikle program tan�ml� t�rle ayn�
ad� al�r (�r. Fraction ad�nda bir program tan�ml� t�r, Fraction.h�de tan�mlan�r)

En �yi Uygulama

Yaln�zca bir kod dosyas�nda kullan�lan bir program tan�ml� t�r, m�mk�n oldu�unca ilk kullan�m noktas�na yak�n bir yerde o kod 
dosyas�nda tan�mlanmal�d�r.

Birden �ok kod dosyas�nda kullan�lan bir program tan�ml� t�r, program tan�ml� t�rle ayn� ad� ta��yan bir ba�l�k dosyas�nda 
tan�mlanmal� ve ard�ndan her kod dosyas�na gerekti�i gibi #include edilmelidir.

��te Fraction t�r�m�z� bir ba�l�k dosyas�na (Fraction.h ad�nda) ta��y�p birden �ok kod dosyas�na dahil edilebilecek �ekilde neye 
benzeyece�i hakk�nda bir �rnek:

Fraction.h:
                    #ifndef FRACTION_H
                    #define FRACTION_H

                    // Fraction ad�nda yeni bir t�r tan�mlay�n
                    // Bu sadece bir Fraction'�n neye benzedi�ini tan�mlar, bir tane olu�turmaz
                    // Bu bir tam tan�md�r, ileri bildirim de�il
                    struct Fraction
                    {
                        int pay {};
                        int payda {};
                    };

                    #endif

Fraction.cpp:
                    #include "Fraction.h" // Bu kod dosyas�na Fraction tan�m�m�z� dahil edin

                    // �imdi Fraction t�r�m�z� kullanabiliriz
                    int main()
                    {
                        Fraction f{ 3, 4 }; // Bu asl�nda f ad�nda bir Fraction nesnesi olu�turur

                        return 0;
                    }

T�r tan�mlar�, bir tan�mlama kural� olan (ODR) k�smen muaf tutulmu�tur

2.7 dersinde -- �leri Bildirimler ve Tan�mlar, bir tan�mlama kural�n�n her fonksiyon ve global de�i�kenin program ba��na yaln�zca
bir tan�m�na sahip olmas�n� gerektirdi�ini tart��t�k. Tan�m� i�ermeyen bir dosyada belirli bir fonksiyonu veya global de�i�keni 
kullanmak i�in, bir ileri bildirime (genellikle bir ba�l�k dosyas� arac�l���yla yayd���m�z) ihtiyac�m�z var. Bu, fonksiyonlar ve
non-constexpr de�i�kenler s�z konusu oldu�unda derleyiciyi tatmin etmek i�in bildirimlerin yeterli oldu�u i�in �al���r ve 
ba�lay�c� daha sonra her �eyi ba�lar.

Ancak, t�rler i�in ileri bildirimleri benzer bir �ekilde kullanmak i�e yaramaz, ��nk� derleyici genellikle belirli bir t�r�
kullanmak i�in tam tan�m� g�rmeye ihtiya� duyar. Her kod dosyas�na tam t�r tan�m�n� yayabilmeliyiz.

Bunu sa�lamak i�in, t�rler bir tan�mlama kural�ndan ( ODR ) k�smen muaf tutulur: belirli bir t�r, birden �ok kod dosyas�nda 
tan�mlanabilir. Bu yetene�i zaten kullanm�� olabilirsiniz (muhtemelen fark�nda olmadan): program�n�zda <iostream> 'u i�eren iki
kod dosyas� varsa, t�m giri�/��k�� t�r tan�mlar�n� her iki dosyaya da i�e aktar�yorsunuz.

Bilmeye de�er iki uyar� var.
* - �lk olarak, hala her kod dosyas� ba��na yaln�zca bir t�r tan�m�na sahip olabilirsiniz (bu genellikle bir sorun olmaz ��nk� 
    ba�l�k korumalar� bunu �nler). 
* - �kincisi, belirli bir t�r i�in t�m t�r tan�mlar� ayn� olmal�d�r, aksi takdirde tan�ms�z davran�� sonucu olur.( inline gibi )

Terimler: kullan�c� tan�ml� t�rler vs program tan�ml� t�rler
------------------------------------------------------------
"Kullan�c� tan�ml� t�r" terimi bazen g�ndelik konu�malarda ortaya ��kar ve C++ dil standard�nda da belirtilir (ancak tan�mlanmaz).
G�ndelik konu�malarda, terim genellikle "kendi programlar�n�zda tan�mlanan bir t�r" anlam�na gelir (yukar�daki Fraction t�r �rne�i
gibi).

C++ dil standard�, "kullan�c� tan�ml� t�r" terimini geleneksel olmayan bir �ekilde kullan�r. Dil standard�nda, bir "kullan�c� 
tan�ml� t�r", sizin, standart k�t�phanenin veya uygulaman�n (�r. dil geni�lemelerini desteklemek i�in derleyici taraf�ndan 
tan�mlanan t�rler) tan�mlad��� herhangi bir s�n�f t�r� veya numaraland�r�lm�� t�rd�r. Belki de kar�� sezgisel olarak, bu,
std::string'in (standart k�t�phanede tan�mlanan bir s�n�f t�r�) bir kullan�c� tan�ml� t�r olarak kabul edildi�i anlam�na gelir!

Ek ayr�m sa�lamak i�in, C++20 dil standard�, standart k�t�phane, uygulama veya �ekirdek dilin bir par�as� olarak tan�mlanmayan
s�n�f t�rlerini ve numaraland�r�lm�� t�rleri ifade etmek i�in "program tan�ml� t�r" terimini tan�mlar. Di�er bir deyi�le,
"program tan�ml� t�rler" yaln�zca bizim (veya bir ���nc� taraf k�t�phanesi) taraf�ndan tan�mlanan s�n�f t�rlerini ve enum 
t�rlerini i�erir.

Sonu� olarak, yaln�zca kendi programlar�m�zda tan�mlad���m�z s�n�f t�rleri ve enum t�rleri hakk�nda konu�urken, "program tan�ml�"
terimini tercih ederiz, ��nk� daha kesin bir tan�m� vard�r.

T�r                Anlam                                                                             �rnekler
----------------------------------------------------------------------------------------------------------------------------------
Temel              �ekirdek C++ diline yerle�ik bir t�r                                          int, std::nullptr_t
Bile�ik            Temel t�rlerden olu�turulan bir t�r                                   int&, double*, std::string, Fraction
Kullan�c� Tan�ml�  Bir s�n�f t�r� veya numaraland�r�lm�� t�r                                    std::string, Fraction
                   (Standart k�t�phanede veya uygulamada tan�mlananlar� i�erir)
                   (G�ndelik kullan�mda, genellikle program tan�ml� t�rler anlam�na gelir)    
Program Tan�ml�    Bir s�n�f t�r� veya numaraland�r�lm�� t�r
                   (Standart k�t�phane veya uygulamada tan�mlananlar� hari� tutar)                    Fraction
----------------------------------------------------------------------------------------------------------------------------------

13.2 Kapsams�z Numaraland�r�lm�� t�rler ( Unscoped enumerations )
-----------------------------------------------------------------
C++ bir�ok kullan��l� temel ve bile�ik veri t�r� i�erir. Ancak bu t�rler, yapmak istedi�imiz �eyler i�in her zaman yeterli
olmayabilir. �rne�in, bir elman�n k�rm�z�, sar� veya ye�il olup olmad���n� veya bir g�mle�in rengini (�nceden belirlenmi� bir
renk listesinden) takip etmesi gereken bir program yaz�yorsunuz diyelim. E�er sadece temel t�rler mevcut olsayd�, bunu nas�l
yapard�n�z?

Rengi bir tam say� de�eri olarak saklayabilir, baz� t�rden bir i�sel e�lemeyi kullanabilirsiniz (0 = k�rm�z�, 1 = ye�il, 2 = mavi):
                    int main()
                    {
                        int elmaRengi{ 0 }; // elma k�rm�z�
                        int gomlekRengi{ 1 }; // g�mlek ye�il

                        return 0;
                    }

Ama bu hi� de sezgisel de�il ve sihirli say�lar�n neden k�t� oldu�unu zaten tart��t�k. Sembolik sabitleri kullanarak sihirli 
say�lardan kurtulabiliriz:

                    constexpr int kirmizi{ 0 };
                    constexpr int yesil{ 1 };
                    constexpr int mavi{ 2 };

                    int main()
                    {
                        int elmaRengi{ kirmizi };
                        int gomlekRengi{ yesil };

                        return 0;
                    }

Bu, okuma i�in biraz daha iyidir, ancak programc� hala elmaRengi ve gomlekRengi�nin (int t�r�nde olan) renk sembolik sabitlerinden
birini tutmas� gerekti�ini ��karmak zorundad�r (bu sabitler muhtemelen ba�ka bir yerde, muhtemelen ayr� bir dosyada tan�mlanm��t�r)
Bu program� biraz daha a��k hale getirmek i�in bir t�r takma ad� kullanabiliriz:

using Renk = int; // Renk ad�nda bir t�r takma ad� tan�mla

// A�a��daki renk de�erleri bir Renk i�in kullan�lmal�d�r
constexpr Renk kirmizi{ 0 };
constexpr Renk yesil{ 1 };
constexpr Renk mavi{ 2 };

int main()
{
    Renk elmaRengi{ kirmizi };
    Renk gomlekRengi{ yesil };

    return 0;
}

Daha yakla��yoruz. Bu kodu okuyan biri hala bu renk sembolik sabitlerinin Renk t�r�ndeki de�i�kenlerle kullan�lmas� gerekti�ini
anlamal�, ancak en az�ndan t�r�n art�k benzersiz bir ad� var, b�ylece Renk arayan biri ili�kili sembolik sabitler k�mesini,
bulabilir.

Ancak, Renk sadece bir int i�in bir takma ad oldu�u i�in, bu renk sembolik sabitlerinin uygun kullan�m�n� zorlayan hi�bir �ey yok.
Hala ��yle bir �ey yapabiliriz:

Renk gozRengi{ 8 }; // s�zdizimsel olarak ge�erli, anlamsal olarak anlams�z

Ayr�ca, bu de�i�kenlerin herhangi birini hata ay�klay�c�m�zda hata ay�klarsak, yaln�zca rengin tam say� de�erini (�r. 0) g�r�r�z,
sembolik anlam�n� (k�rm�z�) de�il, bu da program�m�z�n do�ru olup olmad���n� anlamay� zorla�t�rabilir.

Neyse ki, daha iyisini yapabiliriz.

�lham kayna�� olarak, bool t�r�n� d���n�n. Bool�u �zellikle ilgin� k�lan �ey, yaln�zca iki tan�ml� de�eri olmas�d�r: true ve false.
True veya false�u do�rudan (literaller olarak) kullanabiliriz, ya da bir bool nesnesi olu�turabilir ve onun bu de�erlerden birini
tutmas�n� sa�layabiliriz. Ayr�ca, derleyici bool�u di�er t�rlerden ay�rt edebilir. Bu, fonksiyonlar� a��r� y�kleyebilece�imiz ve
bu fonksiyonlar�n bir bool de�eri ge�irildi�inde nas�l davranaca��n� �zelle�tirebilece�imiz anlam�na gelir.

Kendi �zel t�rlerimizi tan�mlama yetene�imiz olsayd�, bu t�rle ili�kilendirilmi� adland�r�lm�� de�erler k�mesini tan�mlayabilirdik,
o zaman yukar�daki zorlu�u zarif bir �ekilde ��zmek i�in m�kemmel bir arac�m�z olurdu�

Numaraland�rmalar ( Enumerations )
----------------------------------
Bir numaraland�rma (ayn� zamanda bir numaraland�r�lm�� t�r veya bir enum olarak da adland�r�l�r), de�erleri adland�r�lm�� sembolik
sabitler k�mesiyle (numaraland�r�c�lar olarak adland�r�l�r) s�n�rl� bir bile�ik veri t�r�d�r.

C++ iki t�r numaraland�rmay� destekler: kapsams�z numaraland�rmalar ve kapsaml� numaraland�rmalar.

Numaraland�rmalar, program tan�ml� t�rler oldu�u i�in 13.1 � Program Tan�ml� (Kullan�c� Tan�ml�) T�rlerin Giri�i,
her numaraland�rman�n tam olarak tan�mlanmas� gerekiyor, kullanmadan �nce (bir ileri bildirim yeterli de�il).

Kapsams�z Numaraland�rmalar ( Unscoped Enumerations )
-----------------------------------------------------
Kapsams�z numaraland�rmalar, enum anahtar kelimesi arac�l���yla tan�mlan�r.

Numaraland�r�lm�� t�rler en iyi �rneklerle ��retilir, bu y�zden baz� renk de�erlerini tutabilecek bir kapsams�z numaraland�rma
tan�mlayal�m. Nas�l �al��t���n� a�a��da a��klayaca��z.
                    // Color ad�nda yeni bir enum tan�mla
                    enum Color
                    {
                        // ��te enum de�erleri
                        // Bu sembolik sabitler, bu tipin alabilece�i t�m de�erleri tan�mlar
                        // Her enum de�eri virg�lle ayr�l�r, noktal� virg�lle de�il
                        red,
                        green,
                        blue, // son enum de�erinden sonra virg�l opsiyonel ama tavsiye edilir
                    }; // enum tan�m� noktal� virg�lle bitmeli

                    int main()
                    {
                        // Color tipinde birka� de�i�ken tan�mla
                        Color apple { red };   // elma k�rm�z�
                        Color shirt { green }; // g�mlek ye�il
                        Color cup { blue };    // bardak mavi

                        Color socks { white }; // hata: white, Color'�n bir enum de�eri de�il
                        Color hat { 2 };       // hata: 2, Color'�n bir enum de�eri de�il

                        return 0;
                    }

�rne�imize, enum anahtar kelimesini kullanarak derleyiciye Color ad�nda bir enum tan�mlad���m�z� s�yleyerek ba�l�yoruz.

Bir �ift s�sl� parantez i�inde, Color tipi i�in enum de�erlerini tan�ml�yoruz: red, green ve blue. Bu enum de�erleri, 
Color tipinin s�n�rl� oldu�u belirli de�erleri tan�mlar. Her enum de�eri virg�lle ayr�lmal�d�r (noktal� virg�lle de�il) -
son enum de�erinden sonra virg�l opsiyonel ama tutarl�l�k i�in tavsiye edilir.

Color i�in tip tan�m� bir noktal� virg�lle biter. Art�k Color adl� enum tipini tamamen tan�mlad�k!

main() i�inde, Color tipinde �� de�i�ken olu�turuyoruz: apple, red rengiyle ba�lat�l�yor; shirt, green rengiyle ba�lat�l�yor;
ve cup, blue rengiyle ba�lat�l�yor. Bu nesneler i�in bellek ayr�l�r. Bir enum tipinin ba�lat�c�s�, o tip i�in tan�mlanan enum
de�erlerinden biri olmal�d�r. Socks ve hat de�i�kenleri derleme hatalar�na neden olur ��nk� ba�lat�c�lar white ve 2, 
Color'�n enum de�erleri de�ildir.

Enum de�erleri implisit ( bilin�siz - otomatik ) olarak constexpr'dir.

Hat�rlatma

Terimler �zerinde h�zl�ca bir �zet yapal�m:

Bir enum veya enum tipi, program taraf�ndan tan�mlanan tipin kendisidir (�r. Color).
Bir enum de�eri, enum'a ait belirli bir adland�r�lm�� de�erdir (�r. red).
Enum ve enum de�erlerinin adland�r�lmas�

Geleneksel olarak, enum tiplerinin adlar� b�y�k harfle ba�lar (t�m program taraf�ndan tan�mlanan tipler gibi).

*** Uyar� -> Enum'lar�n adland�r�lmas� zorunlu de�ildir, ancak modern C++'da isimsiz enum'lar�n kullan�lmas� ka��n�lmal�d�r.

Enum de�erlerine isim verilmelidir. Ne yaz�k ki, enum de�erlerinin isimleri i�in ortak bir adland�rma kural� yoktur. Yayg�n
se�enekler aras�nda k���k harfle ba�lama (�r. red), b�y�k harfle ba�lama (Red), t�m b�y�k harfler (RED), bir �nek ile t�m b�y�k 
harfler (COLOR_RED) veya "k" ile �ne ��kan ve b�y�k harfle ba�layan (kColorRed) bulunur.

Modern C++ kurallar� genellikle t�m b�y�k harfli adland�rma kurallar�ndan ka��nmay� �nerir, ��nk� t�m b�y�k harfler genellikle
�ni�lemci makrolar� i�in kullan�l�r ve �ak��abilir. B�y�k harfle ba�layan kurallardan ka��nmay� da �neririz, ��nk� b�y�k harfle
ba�layan isimler genellikle program taraf�ndan tan�mlanan tipler i�in ayr�lm��t�r.

*** BEST -> Enum tiplerinizi b�y�k harfle ba�layarak adland�r�n. Enum de�erlerinizi k���k harfle ba�layarak adland�r�n.

Enum tipleri ayr� tiplerdir

Olu�turdu�unuz her enum tipi, derleyicinin di�er tiplerden ay�rt edebilece�i ayr� bir tip olarak kabul edilir 
(typedef'ler veya tip takma adlar� aksine, bunlar takma ad olduklar� tiplerle ayn� kabul edilir).

��nk� enum tipleri ayr�d�r, bir enum tipinin par�as� olarak tan�mlanan enum de�erleri, ba�ka bir enum tipinin nesneleriyle
kullan�lamaz:

                    enum Pet
                    {
                        cat,
                        dog,
                        pig,
                        whale,
                    };

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    int main()
                    {
                        Pet myPet { black }; // derleme hatas�: black, Pet'in bir enum de�eri de�il
                        Color shirt { pig }; // derleme hatas�: pig, Color'�n bir enum de�eri de�il

                        return 0;
                    }

Muhtemelen zaten domuzlu bir g�mlek istemezdiniz.

Numaraland�rmalar� Kullanma ( Putting Enumerations to use )
-----------------------------------------------------------
Numaraland�rmalar a��klay�c� oldu�u i�in, kod belgelerini ve okunabilirli�ini art�rmak i�in yararl�d�rlar. Numaraland�r�lm�� 
t�rler, k���k bir ilgili sabitler k�mesine sahip oldu�unuzda ve nesnelerin ayn� anda yaln�zca bu de�erlerden birini tutmas� 
gerekti�inde en iyi �ekilde kullan�l�r.

Genellikle tan�mlanan numaraland�r�lmalar aras�nda haftan�n g�nleri, ana y�nler ve bir kart destesindeki tak�mlar bulunur:

                    enum HaftaninG�nleri
                    {
                        pazar,
                        pazartesi,
                        sali,
                        carsamba,
                        persembe,
                        cuma,
                        cumartesi,
                    };

                    enum AnaY�nler
                    {
                        kuzey,
                        dogu,
                        g�ney,
                        bati,
                    };

                    enum KartTakimlari
                    {
                        kul�pler,
                        elmaslar,
                        kalpler,
                        ma�alar,
                    };

Bazen fonksiyonlar, fonksiyonun ba�ar�yla y�r�t�l�p y�r�t�lmedi�ini veya bir hata ile kar��la��p kar��la�mad���n� belirtmek i�in
bir durum kodunu �a��r�c�ya d�nd�r�r. Geleneksel olarak, farkl� olas� hata kodlar�n� temsil etmek i�in k���k negatif say�lar 
kullan�l�rd�. �rne�in:

                    int dosyaIceriginiOku()
                    {
                        if (!dosyayiAc())
                            return -1;
                        if (!dosyayiOku())
                            return -2;
                        if (!dosyayiAyristir())
                            return -3;

                        return 0; // ba�ar�
                    }

Ancak, bu t�r sihirli say�lar� kullanmak �ok a��klay�c� de�ildir. Daha iyi bir y�ntem, bir numaraland�r�lm�� t�r kullanmakt�r:

                    enum DosyaOkumaSonucu
                    {
                        okumaSonucuBasari,
                        okumaSonucuHataDosyaAcma,
                        okumaSonucuHataDosyaOkuma,
                        okumaSonucuHataDosyaAyristirma,
                    };

                    DosyaOkumaSonucu dosyaIceriginiOku()
                    {
                        if (!dosyayiAc())
                            return okumaSonucuHataDosyaAcma;
                        if (!dosyayiOku())
                            return okumaSonucuHataDosyaOkuma;
                        if (!dosyayiAyristir())
                            return okumaSonucuHataDosyaAyristirma;

                        return okumaSonucuBasari;
                    }

Daha sonra �a��r�c�, fonksiyonun d�n�� de�erini uygun numaraland�r�c�ya kar�� test edebilir, bu da d�n�� sonucunu belirli bir tam
say� de�eri i�in test etmekten daha kolay anla��l�r.

                    if (dosyaIceriginiOku() == okumaSonucuBasari)
                    {
                        // bir �ey yap
                    }
                    else
                    {
                        // hata mesaj� yazd�r
                    }

numaraland�r�lm�� t�rler, oyunlarda da iyi bir �ekilde kullan�labilir, farkl� t�rdeki ��eleri, canavarlar� veya arazileri
tan�mlamak i�in. Temel olarak, k���k bir ilgili nesneler k�mesi olan her �ey.

�rne�in:

                    enum ��eT�r�
                    {
                        k�l��,
                        me�ale,
                        iksir,
                    };

                    int main()
                    {
                        ��eT�r� tutulan{ me�ale };

                        return 0;
                    }

numaraland�r�lm�� t�rler, kullan�c�n�n iki veya daha fazla se�enek aras�nda bir se�im yapmas� gerekti�inde yararl� i�lev 
parametreleri yapabilir:

                    enum S�ralamaD�zeni
                    {
                        alfabetik,
                        alfabetikTers,
                        say�sal,
                    };

                    void veriyiS�rala(S�ralamaD�zeni d�zen)
                    {
                        switch (d�zen)
                        {
                            case alfabetik:
                                // veriyi ileri alfabetik s�rayla s�rala
                                break;
                            case alfabetikTers:
                                // veriyi geri alfabetik s�rayla s�rala
                                break;
                            case say�sal:
                                // veriyi say�sal olarak s�rala
                                break;
                        }
                    }

Bir�ok dil, Boole'lar� tan�mlamak i�in numaraland�r�lmalar� kullan�r - sonu�ta, bir Boole, temelde yaln�zca 2 numaraland�r�c�ya
sahip bir say�land�rmad�r: false ve true! Ancak, C++'da, true ve false, numaraland�rmalar yerine anahtar kelimeler olarak 
tan�mlanm��t�r.

numaraland�r�lmalar k���k ve kopyalamas� ucuz oldu�u i�in, onlar� de�er olarak ge�mek (ve d�nd�rmek) iyidir.

Ders O.1 -- Bit bayraklar� ve bit manip�lasyonu via std::bitset, konusunda bit bayraklar�n� tart��t�k. numaraland�r�lmalar,
std::bitset ile kullan�lmak �zere ilgili bit bayrak pozisyonlar�n�n bir koleksiyonunu tan�mlamak i�in de kullan�labilir:

                    #include <bitset>
                    #include <iostream>

                    namespace Bayraklar
                    {
                        enum Durum
                        {
                            ac,
                            uzgun,
                            kizgin,
                            mutlu,
                            guluyor,
                            uyuyor,
                            olu,
                            agliyor,
                        };
                    }

                    int main()
                    {
                        std::bitset<8> ben{};
                        ben.set(Bayraklar::mutlu);
                        ben.set(Bayraklar::gulu);

                        std::cout << std::boolalpha; // bool'u true/false olarak yazd�r

                        // Birka� durumu sorgula (herhangi bir bitin ayarl� olup olmad���n� g�rmek i�in any() fonksiyonunu
                           kullan�r�z)
                        std::cout << "Mutlu muyum? " << ben.test(Bayraklar::mutlu) << '\n';
                        std::cout << "G�l�yor muyum? " << ben.test(Bayraklar::gulu) << '\n';

                        return 0;
                    }
Bir tam say� de�erinin beklendi�i yerde bir numaraland�r�c�y� nas�l kullanabilece�imizi merak ediyorsan�z, kapsams�z
numaraland�r�c�lar otomatik olarak tam say� de�erlerine d�n��t�r�l�r. Bunu bir sonraki derste (13.3 � Kapsams�z numaraland�rma 
giri�i ve ��k���) daha ayr�nt�l� olarak inceleyece�iz.

Kapsams�z Numaraland�rmalar�n Kapsam�

Kapsams�z numaraland�rmalar, numaraland�r�c� adlar�n� numaraland�rma tan�m�n�n kendisiyle ayn� kapsama koyarlar 
(bir ad alan�n�n yapt��� gibi yeni bir kapsam b�lgesi olu�turmak yerine).

�rne�in, bu program� verelim:

                    enum Renk // bu enum global ad alan�nda tan�mlanm��t�r
                    {
                        kirmizi, // bu y�zden kirmizi global ad alan�na konulur
                        yesil,
                        mavi,
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma k�rm�z�

                        return 0;
                    }
Renk numaraland�rmas� global kapsamda tan�mlanm��t�r. Bu nedenle, t�m numaraland�rma adlar� (k�rm�z�, ye�il ve mavi) de global
kapsama girer. Bu, global kapsam� kirletir ve ad �ak��ma olas�l���n� �nemli �l��de art�r�r.

Bunun bir sonucu olarak, bir numaraland�r�c� ad� ayn� kapsamdaki birden �ok numaraland�rmada kullan�lamaz:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alan�na konulur
                    };

                    enum Duygu
                    {
                        mutlu,
                        yorgun,
                        mavi, // hata: yukar�daki mavi ile ad �ak��mas�
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma k�rm�z�
                        Duygu ben { mutlu }; // �u anda mutluyum (program�m derlenmiyor olsa bile)

                        return 0;
                    }

Yukar�daki �rnekte, her iki kapsams�z numaraland�rma (Renk ve Duygu) ayn� ad� ta��yan numaraland�r�c�lar� global kapsama koyar.
Bu, bir ad �ak��mas�na ve ard�ndan derleme hatas�na yol a�ar.

Kapsams�z numaraland�rmalar ayr�ca numaraland�r�c�lar� i�in adland�r�lm�� bir kapsam b�lgesi sa�lar (bir ad alan�n�n i�indeki
adlar� i�eren bir adland�r�lm�� kapsam b�lgesi gibi). Bu, bir kapsams�z numaraland�rman�n numaraland�r�c�lar�na �u �ekilde
eri�ebilece�imiz anlam�na gelir:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alan�na konulur
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // tamam, numaraland�r�c�y� global ad alan�ndan eri�iyor
                        Renk ahududu { Renk::kirmizi }; // ayr�ca tamam, numaraland�r�c�y� Renk kapsam�ndan eri�iyor

                        return 0;
                    }

�o�u zaman, kapsams�z numaraland�r�c�lar kapsam ��z�mleme operat�r�n� kullanmadan eri�ilir.

Numaraland�r�c� Ad �ak��malar�n� �nlemek
----------------------------------------
Kapsams�z numaraland�r�c� ad �ak��malar�n� �nlemenin olduk�a yayg�n birka� yolu vard�r. Bir se�enek, her numaraland�r�c�y�
numaraland�rman�n ad�yla �ne koymakt�r:

                    enum Renk
                    {
                        renk_kirmizi,
                        renk_mavi,
                        renk_yesil,
                    };

                    enum Duygu
                    {
                        duygu_mutlu,
                        duygu_yorgun,
                        duygu_mavi, // art�k renk_mavi ile ad �ak��mas� yok
                    };

                    int main()
                    {
                        Renk boya { renk_mavi };
                        Duygu ben { duygu_mavi };

                        return 0;
                    }

Bu hala ad alan�n� kirletir ama adlar� daha uzun ve daha benzersiz yaparak ad �ak��ma olas�l���n� azalt�r. Daha iyi bir se�enek,
numaraland�r�lm�� t�r�, ayr� bir kapsam b�lgesi sa�layan bir �eyin i�ine koymakt�r, �rne�in bir ad alan�:

                    namespace Renk
                    {
                        // Renk, k�rm�z�, mavi ve ye�il adlar�, Renk ad alan� i�inde tan�mlan�r
                        enum Renk
                        {
                            kirmizi,
                            yesil,
                            mavi,
                        };
                    }

                    namespace Duygu
                    {
                        enum Duygu
                        {
                            mutlu,
                            yorgun,
                            mavi, // Duygu::mavi, Renk::mavi ile �ak��maz
                        };
                    }

                    int main()
                    {
                        Renk::Renk boya{ Renk::mavi };
                        Duygu::Duygu ben{ Duygu::mavi };

                        return 0;
                    }

Bu, art�k numaraland�rma ve numaraland�r�c� adlar�m�z� kapsam b�lgesinin ad�yla �ne koymam�z gerekti�i anlam�na gelir.
�lgili bir se�enek, kendi kapsam b�lgesini tan�mlayan bir kapsaml� numaraland�rma kullanmakt�r g�rece�iz.
*** BEST -> Numaraland�rmalar�n�z�, numaraland�r�c�lar�n global ad alan�n� kirletmemesi i�in adland�r�lm�� bir kapsam b�lgesi 
            i�ine koymay� tercih edin (�rne�in bir ad alan� veya s�n�f).

Alternatif olarak, bir numaraland�rma yaln�zca tek bir fonksiyonun g�vdesinde kullan�l�yorsa, numaraland�rma fonksiyonun i�inde 
tan�mlanmal�d�r. Bu, numaraland�rman�n ve numaraland�r�c�lar�n�n kapsam�n� yaln�zca o fonksiyona s�n�rlar. Bu t�r bir 
numaraland�rman�n numaraland�r�c�lar�, global kapsamda tan�mlanan ayn� adl� numaraland�r�c�lar� g�lgede b�rak�r.

Numaraland�r�c�larla Kar��la�t�rma
----------------------------------
Bir numaraland�rman�n belirli bir numaraland�r�c�n�n de�erine sahip olup olmad���n� test etmek i�in e�itlik operat�rlerini
(operator== ve operator!=) kullanabiliriz.

                    #include <iostream>

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi,
                    };

                    int main()
                    {
                        Renk gomlek{ mavi };

                        if (gomlek == mavi) // e�er g�mlek maviyse
                            std::cout << "G�mle�iniz mavi!";
                        else
                            std::cout << "G�mle�iniz mavi de�il!";

                        return 0;
                    }
Yukar�daki �rnekte, bir if-deyimi kullanarak gomle�in numaraland�r�c� maviye e�it olup olmad���n� test ediyoruz. Bu, program�m�z�n
davran���n�, numaraland�rmam�z�n hangi numaraland�r�c�y� tuttu�una dayal� olarak ko�ulland�rmam�z i�in bir yol sa�lar.

Bunu bir sonraki derste daha fazla kullanaca��z.
*/