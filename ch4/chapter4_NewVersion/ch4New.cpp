// Chapter 4 tekrardan i�lenecek. D�zg�nce virg�l atlamadan not al�p devam edecez Di�er not ho�uma gitmedi.
#include <iostream>

int main()
{
    return 0;
}
/*
                                                     TEMEL VER� T�PLER� 
Bitler Byteler ve Adresleme
De�i�kenler, bilgi depolamak i�in kullan�lan belle�in belirli bir par�as�na isimlerdir, bu par�a rastgele eri�im belle�i (RAM) i�erisindedir.

Belle�in en k���k birimi, 0 veya 1 de�erini alabilen bir ikili say� olan "bit"tir. Bit, geleneksel bir ���k anahtar� gibi d���n�lebilir.

Bellek, ard���k birimlere sahip "bellek adresleri" veya "adresler" taraf�ndan organize edilmi�tir. Adresler, bellekte belirli bir konumdaki 
i�eriklere eri�memizi sa�lar.

Modern bilgisayar mimarilerinde her bitin kendi benzersiz bellek adresine sahip olmas� gerekmez. Bunun yerine, her bellek adresi 1 bayt veri
i�erir. Bayt, i�lem birimi olarak 8 ard���k bit i�erir.

Bilgisayar belle�i genellikle bitlerin yan� s�ra baytlarla �al���r. Baytlar, genellikle bir bilgi grubunu temsil eder ve birim olarak i�lenir.

Bellek adreslerinin say�s� s�n�rl�d�r ve genellikle veriye bitler halinde eri�me ihtiyac� nadirdir. Bu nedenle, modern bilgisayar mimarilerinde
her bitin kendi adresi olmaz.

Bellek, bilgisayar programlar� taraf�ndan kullan�lan bir kaynakt�r ve de�i�kenlerin de�erlerini depolar. Program �al��t�k�a bellek kullan�l�r 4
ve de�i�kenler bellekteki belirli adreslere yerle�tirilir.

Bayt, 8 bit i�eren bir veri birimidir ve genellikle bir karakterin temsil edildi�i temel bellek birimidir.
*C++'da genellikle "bayt boyutunda" veri y���nlar�yla �al���r�z. Baz� old bilgisayar mimarilerinde de�i�ebilir fakat endi�elenmeye gerek yok.
*/
/*
Veri tipleri 

Yani buradaki bilgiye g�re veri tiplerinden kast�m�z belle�in belirli bitlerini isimlendirmek. �rne�in bu 4 bit e integer diyecez diyerek tan�mlad�k
Bundan sonra onu integer olarak yorumlayaca��z. �rnek veriyorum tekrar 65 de�erini saklicaz bu bellekte 0100 0001 olarak tutulur. Kullanaca��m�z 
zaman tekrar 65 olarak f�n��t�r�l�r. Burada bizim d���nmemiz gereken tek �ey nesnemize en �ok uyan veri tipini se�memiz.

The _t Soneki

Daha yeni C++ s�r�mlerinde tan�mlanan bir�ok t�r (�rne�in std::nullptr_t) _t soneki kullan�r. Bu sonek, "t�r" anlam�na gelir ve modern t�rlere 
uygulanan yayg�n bir adland�rmad�r.E�er bir �ey _t soneki i�eriyorsa, muhtemelen bir t�rd�r. Ancak bir�ok t�rde _t soneki bulunmaz,
bu nedenle bu tutarl� bir �ekilde uygulanmaz.
*/
/*
Void 

Void, eksik bir t�r�n ilk �rne�idir. Bir eksik t�r, bildirilmi� ancak hen�z tan�mlanmam�� bir t�rd�r. Derleyici, bu t�rlerin varl���n� bilir,
ancak bu t�r�n nesneleri i�in ka� bellek ayr�laca��n� belirlemek i�in yeterli bilgiye sahip de�ildir. void, bilerek eksiktir ��nk� bir t�r�n 
eksikli�ini temsil eder ve bu nedenle tan�mlanamaz.

* - * void value; // �al��maz, de�i�kenler eksik t�rle tan�mlanamaz

Bunun d���nda de�er d�nd�rmeyen fonksiyonlar� tan�mlamak i�in kullan�l�r. C de de bir fonksiyonun parametresinin olmad���n� bildirmek i�in void 
kelimesi kullan�l�rd� fakat c++ da bu durum geri y�nl� uyumluluk nedeni ile desteklense de parametresi olmayan fonksiyona int main(void) gibi yazmak 
yerine bo� b�rakmak her zaman daha iyidir. 
*/
/*
                                                    4.3 � Nesne boyutlar� ve sizeof operat�r�
                                                    -----------------------------------------

Genellikle de�i�ken adlar� arac�l���yla belle�e eri�ti�imizden, y�ksek seviyeli programlama dillerinde derleyici, bir de�i�kenin ka� byte bellek 
kulland���n� bizden saklar. Yani, bir de�i�keni kullan�rken do�rudan bellek adreslerini d���nmemize gerek yoktur.

Ancak, bir nesnenin bellekte ne kadar yer kaplad���n� bilmek yine de �nemlidir. ��nk� bir nesnenin kullanaca�� bellek miktar�, i�inde
ta��yabilece�i bilgi miktar�n� belirler. Mesela, tek bir bit sadece 0 veya 1 de�erini alabilir.

Genelle�tirmek gerekirse, n bit i�eren bir veri t�r� 2^n benzersiz bilgi tutar ileride di�er veri tipleri ile beraber daha detayl� ��renece�iz.

Yeni programc�lar genellikle kodlar�n� m�mk�n olan en az belle�i kullanacak �ekilde optimize etmeye fazla odaklan�rlar. �o�u durumda, 
bu ihmal edilebilir bir fark yarat�r. Bak�m� kolay olan bir kod yazmaya odaklan�n ve yarar� �nemli olacak yerlerde ve zamanlarda optimize edin.


Temel veri tiplerinin boyutlar�yla ilgili bir sonraki soru �u olabilir: "Farkl� veri tiplerine sahip de�i�kenler ne kadar bellek kullan�r?"

Belki �a��rt�c� olabilir ancak C++ standard�, temel tiplerin tam boyutunu tan�mlamaz. Bunun yerine, sadece integral ve char tipleri i�in 
minimum boyutu (bit cinsinden) tan�mlar ve t�m tiplerin ger�ek boyutunu uygulama tan�ml� b�rak�r! C++ standard� ayr�ca bir bytenin 8 bit
oldu�unu varsaymaz.Bu ��retici serisinde, genellikle modern mimariler i�in genel olarak do�ru olan baz� makul varsay�mlar yaparak basitle�tirilmi� 
bir g�r�n�m alaca��z:

-* Bir byte 8 bittir.
-* Bellek, byte adreslenebilir, bu nedenle en k���k nesne 1 bytedir.
-* Ondal�k say� deste�i IEEE-754 uyumludur.
-* 32-bit veya 64-bit mimari �zerindeyiz.


Belirli bir makinedeki veri tiplerinin boyutunu belirlemek i�in, C++ sizeof adl� bir operat�r sa�lar. sizeof operat�r�, ya bir t�r� ya da
bir de�i�keni alan ve onun boyutunu byte cinsinden d�nd�ren bir tek operandl� operat�rd�r. A�a��daki program� derleyip �al��t�rarak veri 
tiplerinin boyutlar�n� ��renebilirsiniz: Tabi ki mimariden mimariye veya sistem ayarlar�na g�re de�i�ebilir. 
sizeof operat�r�, void gibi tamamlanmam�� (incomplete) tipler �zerinde kullan�lmaya �al���ld���nda derleme hatas� ile sonu�lan�r. void tipi, 
boyutu belirsiz olan bir tip olarak kabul edilir, ��nk� bellekte ka� byte yer kaplad��� belirli de�ildir.

genellikle modern makinelerde, temel veri tiplerine ait nesneler h�zl�d�r. Bu nedenle, bu tipleri kullan�rken veya kopyalarken performans 
endi�esi genellikle bir sorun olmamal�d�rbellek kullan�m� ile performans aras�ndaki ili�ki, genel sistem mimarisi, derleyici optimizasyonlar�
ve kullan�lan algoritmalar gibi bir�ok fakt�re ba�l�d�r. Optimize edilmi� ve okunabilir kod yazmak i�in genellikle tipik kullan�m senaryolar�n�
de�erlendirmek ve �l��m yapmak �nemlidir
*/
/*
                                                        SIGNED INTEGER

* Bir tamsay�, pozitif ve negatif tam say�lar�, 0'� da i�eren bir integral t�rd�r (�rne�in, -2, -1, 0, 1, 2). C++, kullan�m i�in kullan�labilir 
olan 4 temel tamsay� t�r�ne sahiptir: 
* Temel tamsay� t�rleri aras�ndaki temel fark, de�i�en boyutlara sahip olmalar�d�r - daha b�y�k tamsay�lar daha b�y�k say�lar� temsil edebilir.
C++, tamsay�lar�n belirli bir minimum boyuta sahip olaca��n�, ancak belirli bir boyuta sahip olaca��n� garanti etmez.

Ek bilgi olarak�
Teknik olarak, bool ve char t�rleri integral t�rler olarak kabul edilir (��nk� bu t�rler de�erlerini tamsay� olarak saklarlar). Birka� sonraki 
ders i�in, bu t�rleri tart��mam�zdan d��layaca��z.

�kili temsil i�inde, say�n�n i�aretini saklamak i�in tek bir bit kullan�l�r (i�aret biti olarak adland�r�l�r). ��aret olmayan bitler (b�y�kl�k
bitleri olarak adland�r�l�r) say�n�n b�y�kl���n� belirler. C++ dilinde, tamsay�lar varsay�lan olarak i�aretlidir, yani say�n�n i�areti say�n�n
bir par�as� olarak saklan�r. Bu nedenle, bir i�aretli tamsay� hem pozitif hem de negatif say�lar� (ve 0'�) tutabilir.

Signed t�rlerin tan�mlanmas� �rnekler ile: 
    short s;      // "short int" yerine "short" tercih edilir
    int i;
    long l;       // "long int" yerine "long" tercih edilir
    long long ll; // "long long int" yerine "long long" tercih edilir
Yani signed short int veya short int gibi tan�mlamalar da ge�erlidir. Fakat signed gereksizdir ��nk� integerler varsay�lan olarak zaten 
signed olarak tan�mlan�r. int yazmak da kafa kar���kl��� yapabilir ya da dikkatsizlik ile short unutulabilir. 

Menzilleri yani rangeleride yine 2^n form�l� ile bulunur �rne�in 8 bitlik i�aretli 2^8 = 256 => -128 ve 127 aral���n� tutar. Di�er t�rlerde bu 
�ekilde hesap edilir. Burada 7 bit b�y�kl��e 1 bit ise i�arete gitti�i i�in bu �ekilde. 

yani -(2n-1) ile 2n-1-1 aral�kt�r. Her hangi verinin tutabilece�i veri b�y�kl���.

*** ��ARETL� SAYILARDA TA�MA
----------------------------
C++20 standard� �u genel ifadeyi kullan�r: "Bir ifadenin de�erlendirilmesi s�ras�nda sonu� matematiksel olarak tan�mlanmam��sa veya t�r�n�n 
temsil edilebilir de�erler aral���nda bulunmuyorsa, davran�� tan�ms�zd�r." G�nl�k dilde buna ta�ma (overflow) denir.Bu nedenle, 140 de�erini
bir 8-bit i�aretli tamsay�ya atamak tan�ms�z davran��a neden olacakt�r.

*** Tam say� b�lmesi 
--------------------
Ek olarak tam say�larda b�lme i�lemi yapacak olursa �rne�in 20/5= 4 olur fakat 8/ 5 yaparsak burada cevap 1 olur geriye kalan k�s�m ise direktmen 
d���r�l�r yani yuvarlanmaz. E�er virg�ll� bir sonuca ihtiyac�m�z yoksa sorun olmaz fakat ihtiya� varsa bilgi kayb� olur dikkat et.
*/
/*
                                                      ��ARETS�Z TAM SAYILAR 

��aretsiz tam say�lar negatif olmayan say�lar� tutar. tan�mlamak i�in "unsigned" kelimesini de�i�kenin ba��na koymak yeterlidir:
    unsigned int a;
    unsigned short s;
    unsigned long long;
��aretsiz say�lar�n rangeleri hesap edilirken i�aret bitine ihtiya� olmad��� i�in hesaplama da d���� olmaz yani 0 ile 2^n-1 aras�nda olur.
Hi�bir negatif say� gerekmedi�inde, i�aretsiz tamsay�lar a� olu�turma ve az belle�e sahip sistemler i�in �ok uygundur, ��nk� i�aretsiz
tamsay�lar fazladan bellek kullanmadan daha fazla pozitif say� saklayabilir.
 

*** ��ARETS�Z SAYILARDA TA�MA
-----------------------------
�lgin� bir �ekilde, C++ standard� a��k�a "unsigned operat�rler i�eren bir hesaplama asla ta�maz (overflow) " der. Bu, genel
programlama uzla�mas�na ayk�r�d�r ��nk� genellikle tamsay� ta�mas�, i�aretli ve i�aretsiz kullan�m durumlar�n� i�erir (kaynak).
�RNE��N
Say� 280, 0 ile 255 aras�ndaki 1 byte'l�k aral���m�za s��acak kadar k���k de�ildir. T�r�n en b�y�k say�s�ndan bir fazlas� 256'd�r.
Bu nedenle, 280'i 256'ya b�leriz ve 1 kalan 24 elde ederiz. 24 kalan� saklanan de�erdir. Buna wrapping around veya modulo wrapping denir. 

-1 -2 gibi say�larda da ba�a d�nme var yani python daki tersten indeksleme gibi. -1 65535 olarak ba�a d�ner ve burdan de�erlendirilerek devam eder.

Bir�ok geli�tirici (ve baz� b�y�k yaz�l�m geli�tirme �irketleri, �rne�in Google gibi), genellikle geli�tiricilerin genellikle i�aretsiz tamsay�lardan ka��nmas� gerekti�ine inanmaktad�r.

Bu, genellikle iki problem yaratan iki davran��tan kaynaklanmaktad�r.

�lk olarak, i�aretli de�erlerle, aral���n �st�n� veya alt�n� kazara a�mak biraz �aba gerektirir ��nk� bu de�erler 0'dan uzakt�r. 
�mzas�z say�larda, aral���n alt�n� kazara a�mak �ok daha kolayd�r, ��nk� aral���n alt� 0'd�r ve bu de�er, de�erlerimizin �o�unun
bulundu�u yerden yak�nd�r.

�rne�in 2 - 3 gibi bir durum oldu�u gibi ta�ma olur �ok riskli hoceeeem.


�kinci olarak, daha da tehlikeli olan�, i�aretli ve i�aretsiz tamsay�lar� kar��t�rd���n�zda beklenmeyen davran��lar�n ortaya ��kabilmesidir.
C++ dilinde, matematiksel bir i�lem (�rne�in, aritmetik veya kar��la�t�rma) bir i�aretli tamsay� ve bir i�aretsiz tamsay� i�eriyorsa, 
genellikle i�aretli tamsay� i�aretsiz bir tamsay�ya d�n��t�r�l�r. Ve sonu� bu nedenle i�aretsiz olur. �rne�in:
Yani �rnekte g�r: 
    unsigned int u{ 2 };
    signed int s{ 3 };

    std::cout << u - s << '\n'; // 2 - 3 = 4294967295 -> u i�aretli bir say� olsayd� do�ru cevap ��kard� fakat olmad��� i�in s i�aretsiz say�ya 
    �evrildi ve cevap farkl� bir �ekilde geldi. 

*** BEST
* Miktarlar� (hatta non-negatif olmas� gereken miktarlar� bile) ve matematiksel i�lemleri tutmak i�in i�aretli say�lar� tercih edin. 
i�aretli ve i�aretsiz say�lar� kar��t�rmaktan ka��n�n.


O zaman ne zaman i�aretsiz say�lar� kullanmal�s�n�z?

C++ dilinde hala i�aretsiz say�lar� kullanman�n uygun/necessary (gerekli) oldu�u birka� durum vard�r.

�lk olarak, bit manip�lasyonu ile u�ra��ld���nda (O b�l�m�nde ele al�nan), i�aretsiz say�lar tercih edilir. Ayr�ca, iyi tan�mlanm�� d�ng�selli�in
gerekti�i durumlarda (�ifreleme ve rastgele say� �retimi gibi baz� algoritmalar i�in kullan��l�d�r).

�kinci olarak, i�aretsiz say�lar�n kullan�m� baz� durumlarda hala ka��n�lmazd�r, �zellikle dizi indeksleme ile ilgili durumlar. Diziler ve dizi
indeksleme derslerinde daha fazla bilgi verece�iz.

Ayr�ca, bir g�m�l� sistem i�in (�rne�in bir Arduino) veya baz� di�er i�lemci/bellek s�n�rl� ba�lamda, i�aretsiz say�lar�n kullan�m� performans
nedenleriyle daha yayg�n ve kabul edilebilir (ve baz� durumlarda ka��n�lmaz) olabilir.
*/
/*

                                            Sabit Geni�likli Tam say�lar ve size_t
hat�rlama: Bir �nceki derste c++ �n tam say�lar i�in belirli bir bellek alan� vermek yerine minimum bellek alan� ile tan�mlad���n� ve bu bellek 
alan�n�n hedef sisteme g�re de�i�ebilece�ini s�ylemi�tik. 

Neden tamsay� de�i�kenlerinin boyutu sabit de�il?
-------------------------------------------------
K�sa cevap, bu durumun C'ye dayanmas�ndan kaynaklan�r. Bilgisayarlar yava� oldu�unda ve performans en �nemli konu oldu�unda, C, derleyici 
uygulay�c�lar�n�n int i�in hedef bilgisayar mimarisinde en iyi performans� sergileyen bir boyut se�mesine izin vermek amac�yla tamsay�lar�n
boyutunu bilin�li bir �ekilde a��k b�rakm��t�r.

Bu durum k�t� m� ?
------------------

Bu durum �a�da� standartlara g�re evet, biraz tuhaf. Bir programc� olarak, belirsiz aral�klara sahip t�rlerle u�ra�mak biraz abs�rt.

int t�r�n� d���n�n. int i�in minimum boyut 2 byte'd�r, ancak modern mimarilerde genellikle 4 byte'd�r. Bir int'in muhtemelen 4 byte 
oldu�unu varsayarsan�z, program�n�z muhtemelen int'in asl�nda 2 byte oldu�u mimarilerde yanl�� davranacakt�r (��nk� muhtemelen 4 byte 
gerektiren de�erleri 2 byte bir de�i�kende sakl�yorsunuz, bu da ta�ma veya tan�ms�z davran��a neden olacakt�r). Maksimum uyumlulu�u 
sa�lamak i�in int'in yaln�zca 2 byte oldu�unu varsayarsan�z, int'in 4 byte oldu�u sistemlerde her bir tamsay� i�in 2 byte bo�a harcam��
olursunuz ve bellek kullan�m�n�z� iki kat�na ��karm�� olursunuz!

Yukar�daki sorunlar� ele almak i�in, C99, herhangi bir mimaride ayn� boyutta olmalar� garanti edilen bir dizi sabit geni�likte tamsay�y� 
(stdint.h ba�l��� i�inde) tan�mlam��t�r.
Tablo da g�rebilirsin:
Name	            Type	          Range         	                                Notes
std::int8_t	    1 byte signed	    -128 to 127	                    �o�u sistemde signed char gibi davran�yor tehlike. 
std::uint8_t	1 byte unsigned 	0 to 255	                    �o�u sistemde unsigned char gibi davran�yor tehlike. 
std::int16_t	2 byte signed   	-32,768 to 32,767
std::uint16_t	2 byte unsigned 	0 to 65,535
std::int32_t	4 byte signed	    -2,147,483,648 to 2,147,483,647
std::uint32_t	4 byte unsigned	    0 to 4,294,967,295
std::int64_t	8 byte signed   	-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
std::uint64_t	8 byte unsigned	    0 to 18,446,744,073,709,551,615


C++, resmi olarak bu sabit geni�likteki tamsay�lar� C++11'in bir par�as� olarak benimsemi�tir. Bunlara, <cstdint> ba�l���n� i�e aktararak
eri�ilebilir, burada std ad alan� i�inde tan�mlanm��lard�r. ��te bir �rnek:

        #include <cstdint> // for fixed-width integers
        #include <iostream>

        int main()
        {
            std::int16_t i{5};
            std::cout << i << '\n';
            return 0;
        }


Sabit geni�likteki tamsay�lar�n genellikle dile getirilen iki dezavantaj� bulunmaktad�r.

�lk olarak, sabit geni�likteki tamsay�lar�n t�m mimarilerde tan�ml� olmas� garanti edilmez. Yaln�zca geni�liklerine uyan temel t�rlerin ve 
belirli bir ikili temsilin bulundu�u sistemlerde var olurlar. Program�n�z, kulland���n�z sabit geni�likteki bir tamsay�y� desteklemeyen herhangi
bir mimaride derlenemez. Ancak, �o�u modern mimarinin 8/16/32/64-bit de�i�kenlere standartla�t��� g�z �n�ne al�nd���nda, bu, program�n�z�n 
ta��nabilir olmas� gerekiyorsa nadiren bir sorun olacakt�r, ancak belirli bir egzotik ana bilgisayara veya g�m�l� mimarilere ta��nmas� gerekiyorsa
bu durum de�i�ebilir.

�kinci olarak, sabit geni�likteki bir tamsay� kullan�rsan�z, baz� mimarilerde daha geni� bir t�rden daha yava� olabilir. �rne�in, 32 bit garanti
edilen bir tamsay�ya ihtiyac�n�z varsa, std::int32_t'yi kullanmaya karar verebilirsiniz, ancak CPU'nuz asl�nda 64 bit tamsay�lar� i�lemekte daha
h�zl� olabilir. Ancak, CPU'nuzun belirli bir t�r� daha h�zl� i�leyebilmesi, program�n�z�n genel olarak daha h�zl� olaca�� anlam�na gelmez - 
modern programlar genellikle bellek kullan�m�yla s�n�rl�d�r ve daha b�y�k bellek ayak izi, daha h�zl� CPU i�leme h�zland�rd���ndan daha fazla
yava�layabilir. Bu, ger�ekten �l�meden zor bilinir.

Fast ve Least Tam say�lar�
--------------------------
Yukar�daki dezavantajlar� ele almak i�in, C++ ayr�ca tan�mlanm�� olan iki alternatif tamsay� k�mesini de sa�lar.

H�zl� t�rler (std::int_fast#_t ve std::uint_fast#_t), en az # bit geni�li�inde en h�zl� imzal�/imzas�z tamsay� t�r�n� sa�lar 
(burada # = 8, 16, 32 veya 64). �rne�in, std::int_fast32_t size en az 32 bit olan en h�zl� imzal� tamsay� t�r�n� sa�lar. En h�zl� ifadesiyle,
CPU taraf�ndan en h�zl� �ekilde i�lenebilen tamsay� t�r�n� anl�yoruz.

En k���k t�rler (std::int_least#_t ve std::uint_least#_t), en az # bit geni�li�inde en k���k imzal�/imzas�z tamsay� t�r�n� sa�lar
(burada # = 8, 16, 32 veya 64). �rne�in, std::uint_least32_t size en az 32 bit olan en k���k imzas�z tamsay� t�r�n� sa�lar.

Burada baz� tam say� tipleri belirtildi�i geni�li�e sahip olmayabilir yani mesela int_fast16_t makineden makineye 32 olabilir bu o makinenin 32 biti
16 bitten h�zl� i�lemesinden kaynaklan�yordur. 
Ancak, bu h�zl� ve en k���k tamsay�lara ait kendi dezavantajlar� vard�r: �lk olarak, pek �ok programc� bunlar� ger�ekten kullanmaz ve bu da bilgi
eksikli�inden dolay� hatalara neden olabilir. �kinci olarak, h�zl� t�rler, ger�ek boyutlar� adlar�nda belirtilenden daha b�y�k olabilece�inden,
bellek israf�na neden olabilir. En ciddi dezavantaj� ise fast/least t�rlerinin geni�likleri de�i�ebilir bu durum da program�m�z�n mimariden mimariye
farkl� ��z�mlenmesinden dolay� farkl� davranmas�na ve hatalara neden olabilir. 

    #include <cstdint> // for fixed-width integers
    #include <iostream>

    int main()
    {
        std::uint_fast16_t sometype { 0 };
        --sometype; // intentionally overflow to invoke wraparound behavior

        std::cout << sometype << '\n';

        return 0;
    }

Burada i�aretsiz say�n�n ta�mas�n� sa�lamaya �al���lm�� denedi�imizde farkl� sonu�lar al�yoruz. Bu da g�steriyorki fast/least t�rlerini kullan�rken
mimarilerde dikkatli olmal� ve nas�l davrand���n� bilmemiz gerekiyor. 

std::int8_t ve std::uint8_t'nin (ve buna kar��l�k gelen fast ve least t�rlerin) �o�u derleyici taraf�ndan signed char ve 
unsigned char t�rleriyle ayn� �ekilde tan�mland��� ve i�lendi�i i�in, bu 8-bit t�rlerin di�er sabit geni�likli t�rlerden farkl� 
davran�� sergileyebilece�i anlam�na gelir. Bu durum hatalara yol a�abilir. Bu davran��, sistem ba��ml�d�r, bu nedenle bir mimaride do�ru
davranan bir program, ba�ka bir mimaride do�ru derlenmeyebilir veya do�ru davranmayabilir.

Bu konuda bir �rnek, 4.12 dersinde, t�r d�n���m�ne ve static_cast'a giri�te g�sterilmektedir.

Tamsay� de�erleri saklarken, genellikle std::int8_t ve std::uint8_t (ve ilgili h�zl� ve en k���k t�rlerden) ka��n�lmal� ve bunun yerine 
std::int16_t veya std::uint16_t kullan�lmal�d�r.

Temel tamsay� t�rlerinin, sabit geni�likli tamsay� t�rlerinin, fast/leasr t�rlerinin ve signed/unsigned zorluklar�n �e�itli 
avantajlar� ve dezavantajlar� g�z �n�ne al�nd���nda, integral en iyi uygulamalar konusunda pek az bir uzla�ma vard�r.

Bizim duru�umuz, h�zl� olmaktan ziyade do�ru olman�n ve �al��ma zaman�nda ba�ar�s�z olmaktansa derleme zaman�nda ba�ar�s�z olman�n daha
iyi oldu�udur. Bu nedenle, sabit bir boyutta bir integral t�r�ne ihtiyac�n�z varsa, fast/en k���k t�rlerden ziyade sabit geni�likli 
t�rleri tercih etmenizi �neririz. Daha sonra belirli bir sabit geni�likli t�r�n belirli bir platformda derlenmeyece�ini ke�federse, o
noktada program�n�z� nas�l ge�irece�inize (ve bunu dikkatlice yeniden test etmeye) karar verebilirsiniz.
*/
/*
                                                                size_t nedir 
            #include <iostream>

            int main()
            {
                std::cout << sizeof(int) << '\n';

                return 0;
            }
            Bu programa bakal�m yazar�n program�nda 4 ��kt�s�n� veriyor. 

Olduk�a basit, de�il mi? sizeof operat�r�n�n bir tamsay� de�eri d�nd�rd���n� ��karabiliriz - ancak bu d�n�� de�eri hangi tamsay� t�r�d�r? 
Bir int mi? Bir short mu? Cevap, sizeof (ve bir boyut veya uzunluk de�eri d�nd�ren bir�ok i�lev) de�erinin std::size_t t�r�nde oldu�udur. 
std::size_t, imzal� bir tamsay� t�r� olarak tan�mlanm��t�r ve genellikle nesnelerin boyutunu veya uzunlu�unu temsil etmek i�in kullan�l�r.

�lgin� bir �ekilde, sizeof operat�r�n� (std::size_t t�r�nde bir de�er d�nd�ren) std::size_t'in kendi boyutunu sormak i�in kullanabiliriz:

std::size_t, birka� farkl� ba�l�kta tan�mlanm��t�r. <cstddef>, di�er tan�mlanm�� kimlik say�s�n� en az i�erdi�i i�in dahil etmek i�in en iyi 
se�enektir. Bir tamsay� sisteme ba�l� olarak boyut de�i�tirebilece�i gibi, std::size_t de boyut de�i�tirebilir. std::size_t, garantili olarak
i�aretsiz ve en az 16 bit olacak �ekilde tan�mlanm��t�r, ancak �o�u sistemde genellikle uygulaman�n adres geni�li�ine e�de�er olacakt�r.
Yani, 32-bit uygulamalar i�in std::size_t genellikle 32 bit i�aretsiz bir tamsay� olacakt�r ve 64-bit uygulama i�in std::size_t genellikle
64 bit i�aretsiz bir tamsay� olacakt�r.

sizeof, bir nesnenin boyutunu (bayt cinsinden) std::size_t t�r�nde bir de�er kullanarak d�nd�rebilmelidir. Bu nedenle, bir sistemde
olu�turulabilir olan en b�y�k nesnenin boyutu (bayt cinsinden), std::size_t'nin tutabilece�i en b�y�k de�ere e�ittir. E�er daha b�y�k bir 
nesne olu�turmak m�mk�n olsayd�, sizeof, std::size_t'nin aral���n� a�aca�� i�in boyutunu d�nd�remezdi.

Bu nedenle, std::size_t t�r�ndeki bir nesnenin boyutu (bayt cinsinden), std::size_t t�r�ndeki bir nesnenin tutabilece�i en b�y�k de�erden
daha b�y�kse, bu durum hatal� kabul edilir ve bir derleme hatas�na neden olur.

�rne�in, 4 baytl�k i�aretsiz bir tamsay�n�n aral��� 0 ile 4.294.967.295 aras�ndad�r. Varsayal�m ki std::size_t'nin boyutu 4 bayt ise, 
o zaman std::size_t t�r�ndeki bir nesne, 0 ile 4.294.967.295 aras�nda bir tamsay� de�erini tutabilir. Bu, bu t�r bir sistemde olu�turulabilen
en b�y�k nesnenin 4.294.967.295 bayt oldu�u anlam�na gelir (ve bu nesnenin �zerinde sizeof �a�r�ld���nda tam olarak 4.294.967.295 d�necektir).

Bir not olarak...

std::size_t'nin boyutu, bir nesnenin boyutuna s�k� bir matematiksel �st s�n�r getirir. Uygulamada, olu�turulabilen en b�y�k nesne bu miktar�n
alt�nda olabilir (belki de �nemli �l��de).

Baz� derleyiciler, en b�y�k olu�turulabilir nesneyi std::size_t'nin maksimum de�erinin yar�s�yla s�n�rlayabilir (bu konuda bir a��klama burada
bulunabilir). Di�er fakt�rler de rol oynayabilir, �rne�in bilgisayar�n�z�n hangi miktarda ard���k belle�e sahip oldu�u gibi            
*/

/*
BEST en iyi uygulama
En iyi uygulama

- �nteger'�n boyutu �nemli de�ilse (�rne�in, say� her zaman 2 byte'l�k bir i�aretli integer'a s��acaksa), `int` tercih edin. �rne�in, kullan�c�dan ya�lar�n� girmesini istiyorsan�z veya 1'den 10'a kadar say�yorsan�z, `int`'in 16 veya 32 bit olup olmad��� �nemli de�ildir (say�lar her iki durumda da s��acakt�r). Bu, kar��la�ma ihtimalinizin �ok y�ksek oldu�u durumlar�n �o�unu kapsayacakt�r.
- Bir miktar� depolamak i�in garantili bir aral��a ihtiya� duyuluyorsa, `std::int#_t` tercih edin.
- Bit manip�lasyonu yap�l�yorsa veya tan�ml� bir wrap-around davran��� gerekiyorsa, `std::uint#_t` tercih edin.
- M�mk�nse a�a��dakilerden ka��n�n:
  - `short` ve `long` integer'lar - bunun yerine sabit geni�likli bir tip kullan�n.
  - Unsigned tipleri miktarlar� tutmak i�in kullanmay�n.
  - 8-bit sabit geni�likli integer tipleri.
  - Fast ve least sabit geni�likli tipler.
  - Herhangi bir derleyici �zel sabit geni�likli integer'� - �rne�in, Visual Studio `__int8`, `__int16`, vb. tan�mlar.
*/
// Scientific g�sterimi ge�tim. 
/* 
                                            4.8 Floating Point Number - Kayan noktal� say�lar 


float fValue;          |                                                             4       
double dValue;         |-> �eklinde tan�mlanan 3 t�rden olu�ur minimum geni�likleri  8       -> byte olabilir. 
long double ldValue;   |                                                             8 12 16    

Kayan noktal� say�lar� kullan�rken virg�lden sonra 0 bile olsa " . , " hangisi ise kullanmak laz�m. ��nk� derleyici bunu bir tamsay� olarak g�rebilir. 
Varsay�lan olarak derleyicide kayan noktal� say�lar double olarak tan�mlan�r o y�zden float bir say� tan�mlan�rken sonuna "f" suffix i getirilir. 

Her zaman literallerinizin t�r�n�n, atanacaklar� veya ba�lat�lacaklar� de�i�kenin t�r�yle e�le�ti�inden emin olun. Aksi takdirde gereksiz bir 
d�n���m meydana gelebilir ve bu da olas� bir hassasiyet kayb�na neden olabilir.


Floating point range
--------------------
4 bytes                         	    �1.18 x 10-38 to �3.4 x 1038 and 0.0	    6-9 significant digits, typically 7
8 bytes	                                �2.23 x 10-308 to �1.80 x 10308 and 0.0	    15-18 significant digits, typically 16
80-bits (typically uses 12 or 16 bytes)	�3.36 x 10-4932 to �1.18 x 104932 and 0.0	18-21 significant digits
16 bytes	                            �3.36 x 10-4932 to �1.18 x 104932 and 0.0	33-36 significant digits


80-bit kayan nokta tipi bir t�r olarak tarihsel bir ayk�r�l�kt�r. Modern i�lemcilerde genellikle 12 veya 16 byte kullan�larak uygulan�r 
(bu, i�lemcilerin i�lemesi i�in daha do�al bir boyuttur).

80-bit kayan nokta tipinin, 16-byte kayan nokta tipi ile ayn� aral��a sahip olmas� biraz garip g�r�nebilir. Bu, �s i�in ayr�lan bit 
say�s�n�n ayn� olmas�ndan kaynaklan�r - ancak 16-byte say� daha fazla anlaml� basamaklar� depolayabilir.

Float say�lar�n hassasiyeti
---------------------------
D���n�n ki kesir 1/3. Bu say�n�n ondal�k g�sterimi 0.33333333333333... �eklinde, sonsuza kadar devam eden 3'lerle. E�er bu say�y�
bir ka��da yaz�yorsan�z, bir noktada kolunuz yorulacak ve yazmay� b�rakacaks�n�z. Ve geriye kalan say�, 0.3333333333...
(3'ler sonsuza kadar devam ediyor) ile yakla��k olarak olacakt�r, ancak tam olarak de�il.

Bir bilgisayarda sonsuz uzunluktaki bir say�y� depolamak i�in sonsuz belle�e ihtiya� duyulur, ancak genellikle sadece 4 veya 8 byte'a sahibiz.
Bu s�n�rl� bellek, kayan nokta say�lar�n�n yaln�zca belli bir say�da anlaml� basamak depolayabilmesi anlam�na gelir - ve herhangi ek anlaml� 
basamak kaybolur. Ger�ekte depolanan say�, istenen say�ya yak�n olacakt�r, ancak tam olarak de�il.

Bir kayan nokta say�s�n�n hassasiyeti, bilgi kayb� olmadan temsil edebilece�i anlaml� basamak say�s�n� belirler.

Kayan nokta say�lar�n� ��kt� olarak verirken, std::cout'un varsay�lan hassasiyeti 6'd�r - yani, t�m kayan nokta de�i�kenlerini yaln�zca
6 basama�a kadar anlaml� kabul eder (float'�n minimum hassasiyeti), bu nedenle sonras�ndaki her �eyi kesecektir.

A�a��daki program, std::cout'un 6 basama�a kadar kesti�ini g�stermektedir:
    #include <iostream>
    int main()
    {
        std::cout << 9.87654321f << '\n';
        std::cout << 987.654321f << '\n';
        std::cout << 987654.321f << '\n';
        std::cout << 9876543.21f << '\n';
        std::cout << 0.0000987654321f << '\n';

        return 0;
    }
    ��kt�:
    9.87654
    987.654
    987654
    9.87654e+006
    9.87654e-005

Her birinin sadece 6 anlaml� basama�� oldu�una dikkat edin.

Ayr�ca, std::cout'un baz� durumlarda say�lar� bilimsel nota �evirmeye ge�ece�ini unutmay�n. Derleyiciye ba�l� olarak, �s genellikle bir 
minimum basamak say�s�na kadar doldurulur. Endi�elenmeyin, 9.87654e+006, 9.87654e6 ile ayn�d�r, sadece baz� dolgu 0'lar� vard�r. �s�n en 
az ka� basamakl� g�sterilece�i derleyiciye �zg�d�r (Visual Studio 3 kullan�r, di�erleri C99 standard�na g�re 2 kullan�r).

Bir kayan nokta de�i�keninin sahip oldu�u kesinlik say�s�, boyuta (float'lar double'lardan daha az kesinli�e sahiptir) ve depolanan belirli
de�ere ba�l�d�r (baz� de�erler di�erlerinden daha fazla kesinli�e sahiptir). Float de�erlerinin 6 ila 9 aras�nda kesin basama�� vard�r, 
�o�u float de�eri en az 7 anlaml� basama�a sahiptir. Double de�erlerinin 15 ila 18 aras�nda kesin basama�� vard�r, �o�u double de�eri en az
16 anlaml� basama�a sahiptir. Long double'�n 15, 18 veya 33 anlaml� basama�a sahip olma minimum kesinli�i, ka� byte yer kaplad���na ba�l�d�r.

std::setprecision() adl� bir ��k�� d�zenleyici i�levini kullanarak std::cout'un g�sterdi�i varsay�lan kesinli�i ge�ersiz k�labiliriz.
��k�� d�zenleyicileri, verilerin nas�l ��kt�land���n� de�i�tirir ve iomanip ba�l�k dosyas�nda tan�mlan�r.

��k�� manip�lat�rleri (ve giri� manip�lat�rleri) yap��kand�r; yani onlar� ayarlarsan�z ayarl� kal�rlar.
Burada dikkat etmen gereken di�er bir durum floatlar 7 basama�a kadar hassast�rlar sonras�nda 8.bir basamak daha saklamak istedi�imizde bunu 
d�zg�nce saklayamaz ve bu durum bize hatal� sonu�lar verebilir. Buna rounding error deriz yani yuvarlama hatas�. 

*** Yani best : Yer �nemli de�ilse, genellikle float'taki kesinlik eksikli�i nedeniyle do�ruluk kay�plar�na yol a�abilece�inden dolay� 
double'� tercih edin.

Yuvarlama hatalar� Float say�lar�n kar��la�t�rmas�n� biraz zorla�t�r�r
----------------------------------------------------------------------
Kayan noktal� say�larla �al��mak, verilerin nas�l depoland��� (ikili sistem) ile onlar�n nas�l d���nd���m�z (onlu sistem) aras�ndaki a��k 
olmayan farklar nedeniyle zordur. �rne�in, kesir 1/10'u ele alal�m. Onlu sistemde bunu kolayca 0.1 olarak temsil edebiliriz ve 0.1'i 1 
anlaml� hane i�eren kolayca temsil edilebilen bir say� olarak d���nmeye al�����z. Ancak ikili sistemde ondal�k de�er 0.1, sonsuz diziyi
temsil eden �u �ekildedir: 0.00011001100110011... Bu nedenle, bir kayan noktal� say�ya 0.1'i atad���m�zda, hassasiyet sorunlar�yla kar��la��r�z.

Yani mesela 1/10 asl�nda 0.1 olarak d���n�r�z ama sonsuza dek gidiyor binary yaz�mda burada float say� olarak kaydedildi�inde ise yuvarlama hatas�
ile 0.1 0.1000001 olarak kaydediliyor olabilir. 
sl�nda tam olarak 0.1 olmad���n� g�r�yoruz! Bu, double'�n s�n�rl� belle�i nedeniyle yakla��m� budanmak zorunda kald��� anlam�na gelir. 
Sonu�, 16 anlaml� haneye kadar kesin bir say�d�r (ki bu double t�r� taraf�ndan garanti edilir), ancak say� tam olarak 0.1 de�ildir. 
Yuvarlama hatalar�, budaman�n nerede ger�ekle�ti�ine ba�l� olarak bir say�y� biraz daha k���k veya biraz daha b�y�k yapabilir.

Mevzu
-----
Yuvarlama hatalar�, bir say�n�n tam olarak depolanamad��� durumlarda ortaya ��kar. Bu, basit say�larla bile, �rne�in 0.1 ile ger�ekle�ebilir.
Bu nedenle, yuvarlama hatalar� ger�ekle�ebilir ve genellikle ger�ekle�ir. Yuvarlama hatalar� istisna de�ildir, kurald�r. Asla kayan nokta
say�lar�n�z�n tam oldu�unu varsaymay�n.

Bu kural�n bir sonucu olarak: finansal veya para birimi verileri i�in kayan nokta say�lar�n� kullan�rken dikkatli olun.

Kayar nokta say�lar�n�n iki �zel kategorisi vard�r. �lk olarak, "Inf" (sonsuz) sonsuzlu�u temsil eder. Inf hem pozitif hem de negatif olabilir. 
�kincisi, "NaN", "Not a Number" (Say� De�il) anlam�na gelir. NaN'�n birka� farkl� t�r� vard�r (ki burada tart��mayaca��z). NaN ve Inf, derleyici
kayan nokta say�lar� i�in belirli bir bi�imi (IEEE 754) kullan�yorsa yaln�zca mevcuttur. Ba�ka bir bi�em kullan�l�yorsa, a�a��daki kod tan�ms�z
davran�� �retir.
******Derleyici desteklese bile 0 a b�l�nmeden ka��nmak en iyi davran��t�r. ****
*/

// Temel olarak hat�rlamam�z gereken 2 �ey vard�r. 
/*
�zetle, kayan nokta say�lar� hakk�nda hat�rlaman�z gereken iki �ey:

Kayan nokta say�lar�, �ok b�y�k veya �ok k���k say�lar�, bunlar aras�nda kesirli bile�enler bulunanlar� saklamak i�in kullan��l�d�r.
Kayan nokta say�lar� genellikle k���k yuvarlama hatalar�na sahiptir, hatta say� daha az �nemli basama�a sahipse. �o�u zaman bunlar 
�ok k���k olduklar� ve say�lar ��kt� i�in k�rp�ld��� i�in fark edilmez. Ancak, kayan nokta say�lar� �zerinde matematiksel i�lemler
ger�ekle�tirmek, yuvarlama hatalar�n� daha b�y�k hale getirecektir.*/
/*
                                                            CHARS
CHAR veri tipi karakter verilerini tutmak i�in �retilmi�tir. karakter dedi�imiz �ey bir harf i�aret sembol veya bo�luk olabilir. char veri tipi bir 
integral veri tipi olarak kabul edilir. Yani temel de�er bir tam say� olarak depolan�r ayn� boolean de�erleri gibi ( false = 0 gibi )
charlarda saklanan de�erler ASCII karakteri olarak yorumlan�r. 
ascii nin ne oldu�unu biliyoz ge�tim  

Ba�latma �ekli -> char ch2{'a'} // tercih edilen ba�latma �ekli budur. 
               -> char ch2{97} // ayn� �ekilde 'a' karakterine kar��l�k gelir ama tercih edilen bir ba�latma de�ildir. 
                                Burada dikkat edilmesi gereken ise normal say� ile karakter olan say� kar��t�r�lmamal� '5' ile 5 ayn� de�ildir. 
yazd�rma �eklide ayn� zaten cout a ver yazd�rs�n :d 

input olarak al�rken std::cin>> i kullanabiliriz burada bilmemiz gereken tek �ey 'cin' bir den �ok girdi alabiliyor mesela kemalettin ismini 
cin e girdi olarak verebilirim ama char veri tipi sadece 1 karakter al�yor yan� k harfini alacak ve geriye kalacak olan 'emalettin' buffer da 
beklemeye devam edecektir yeni bir cin ile onu ba�ka karakter veya veriye aktararak �ekebiliriz. Bu mevzunun dikkatinde ol. 

Char size range and default sign
--------------------------------
char, C++ taraf�ndan her zaman 1 byte boyutunda olacak �ekilde tan�mlanm��t�r. Varsay�lan olarak bir char i�aretlenebilir veya i�aretsiz 
olabilir (ancak genellikle i�aretli olur). E�er char'lar� ASCII karakterlerini tutmak i�in kullan�yorsan�z bir i�aret belirtmenize gerek 
yoktur (��nk� hem i�aretli hem de i�aretsiz char'lar 0 ile 127 aras�ndaki de�erleri tutabilir).

E�er k���k tamsay�lar� tutmak i�in (bunu yaln�zca �zellikle yer tasarrufu i�in optimize etmiyorsan�z yapmal�s�n�z) bir char kullan�yorsan�z,
her zaman i�aretli mi yoksa i�aretsiz mi oldu�unu belirtmelisiniz. Bir i�aretli char, -128 ile 127 aras�nda bir say�y� tutabilir. Bir 
i�aretsiz char, 0 ile 255 aras�nda bir say�y� tutabilir.

ka��� dizilerini atlad�m. 

*** �ift t�rnak ve tek t�rnak : Ba��ms�z karakterleri tek t�rnak i�ine al�n (�rne�in, 't' veya '\n', "t" veya "\n" de�il). Bu, derleyicinin
                                daha etkili bir �ekilde optimizasyon yapmas�na yard�mc� olur.

�oklu
Geriye d�n�k uyumluluk nedeniyle, bir�ok C++ derleyicisi �oklu karakterli sabitleri destekler. Bu, birden �ok karakter i�eren char sabitleridir 
(�rne�in '56'). Destekleniyorsa, bunlar bir uygulama tan�ml� de�ere sahiptir (bu, derleyiciye ba�l� olarak de�i�ir). ��nk� bunlar C++ standard�n�n
bir par�as� de�ildir ve de�erleri kesin olarak tan�mlanmam��t�r, �oklu karakterli sabitlerden ka��n�lmal�d�r.
( San�r�m multicharacter dedi�i tek t�rnak i�inde olanlara deniyor.)

wchar_t tipi neredeyse t�m durumlarda ka��n�lmas� gereken bir tiptir (Windows API ile etkile�imde bulunulmas� haricinde). 
Boyutu uygulamaya �zg�d�r ve g�venilir de�ildir. Genellikle terkedilmi�tir.

"Deprecated" terimi, "h�l� destekleniyor ancak daha iyi bir �eyle de�i�tirildi�i veya art�k g�venli kabul edilmedi�i i�in kullan�m� �nerilmeyen"
anlam�na gelir.
C++11'e char16_t ve char32_t, 16 bitlik ve 32 bitlik Unicode karakterlere a��k destek sa�lamak �zere eklenmi�tir. char8_t, C++20'de eklenmi�tir.
Bu char t�rleri s�ras�yla std::uint_least16_t, std::uint_least32_t ve std::uint_least8_t ile ayn� boyuta sahiptir (ancak farkl� t�rlerdir).
Teorik olarak, char#_t t�rleri # taraf�ndan belirtilen bit say�s�ndan daha b�y�k olabilir (ancak esoterik bir mimari �zerinde �al��m�yorsan�z
ayn� olmal�d�r).

char8_t, char16_t veya char32_t'yi yaln�zca program�n�z� Unicode uyumlu hale getirmeyi planl�yorsan�z kullanman�z gerekir. Unicode ve
yerelle�tirme genellikle bu ��reticilerin kapsam�n�n d���nda oldu�u i�in daha fazla a��klama yapmayaca��z.

Bu arada, karakterlerle (ve dizelerle) �al���rken yaln�zca ASCII karakterlerini kullanmal�s�n�z. Di�er karakter setlerinden karakterler kullanmak,
karakterlerinizin yanl�� g�r�nt�lenmesine neden olabilir.
*/
/*                                                      TYPE D�N���M� ve static_cast

�o�u durumda, C++, bir temel t�rden di�er bir temel t�re de�erleri d�n��t�rmemize izin verir. Bir de�eri bir t�rden ba�ka bir t�re d�n��t�rme 
s�recine "t�r d�n���m�" denir.

Derleyicinin bizden a��k�a istemeden t�r d�n���m� ger�ekle�tirdi�inde, buna "�rt�k t�r d�n���m�" diyoruz. �rnek olarak bir fonksiyon 
arg�man olarka double t�r� istedi�i zaman biz ona integer verirsek temel veri tiplerinden oldu�u i�in compiler burada hatay� farkeder ve 
otomatik olarak t�r d�n���m� yapar buna implicit conversion yani �rt�k, bilin�siz t�r d�n���m� deriz. 

T�r d�n���m�, ad�ndan da anla��laca�� gibi, d�n��t�r�len de�erin de�erini veya t�r�n� ger�ekten de�i�tirmez. Bunun yerine, d�n��t�r�lecek de�er
giri� olarak kullan�l�r ve d�n���m, hedef t�rde yeni bir de�er olu�turur (do�rudan ba�latma arac�l���yla).

Yukar�daki �rnekte d�n���m, de�i�ken y'nin t�r�n� int'ten double'a de�i�tirmez. Bunun yerine, d�n���m, y'nin de�erini (5) giri� olarak kullanarak
yeni bir double de�eri (5.0) olu�turur. Bu double de�eri daha sonra print fonksiyonuna iletilir.
yani; 
T�r d�n���m�, farkl� bir t�rdeki bir de�erin de�erinden hedef t�rde yeni bir de�er olu�turmak i�in do�rudan ba�latmay� kullan�r.

Baz� t�r d�n���mleri her zaman g�venlidir ve de�eri de�i�tirmez (�rne�in, int'ten double'a d�n���m), ancak baz�lar� de�erin d�n���m s�ras�nda
de�i�mesine neden olabilir (�rne�in, double'dan int'e d�n���m). G�vensiz, a��k�a istenmeyen t�r d�n���mleri genellikle derleyici uyar�s� �retecek
veya (parantez ba�latma durumunda) bir hata ortaya ��karacakt�r.

Parantez ba�latma tercih edilen ba�latma bi�imi olarak kabul edilir, ��nk� bu ba�latma bi�imi, de�erin d�n���m s�ras�nda kaybolmas�na neden
olabilecek bir ba�lat�c� ile de�i�keni ba�latmaya �al��mad���m�z� sa�lar.

static_cast ile explicit type conversion
----------------------------------------
C++, explicit (a��k) t�r d�n���m� olarak adland�r�lan bir ikinci t�r d�n���m� destekler. Explicit t�r d�n���m�, (programc� olarak) de�eri bir
t�rden ba�ka bir t�re a��k�a d�n��t�rmek istedi�imizi ve bu d�n���m�n sonucundan tam sorumluluk �stlendi�imizi (yani d�n���m�n de�er kayb�na
neden olursa bu bizim hatam�zd�r) belirtmemize olanak tan�r.

A��k�a bir t�r d�n���m� yapmak i�in �o�u durumda static_cast operat�r�n� kullan�r�z. Statik d�n���m�n s�zdizimi biraz garip g�r�n�yor:

static_cast<new_type>(expression)

static_cast, bir ifadenin de�erini girdi olarak al�r ve bu de�eri new_type taraf�ndan belirtilen t�re d�n��t�r�lm�� olarak geri d�nd�r�r
(�rne�in int, bool, char, double).

Herhangi bir C++ s�zdizimi (�n i�lemci hari�) g�rd���n�zde ve bu s�zdizimi a��lm�� parantezleri (<> i�areti) i�eriyorsa, a��lm�� parantezler
aras�ndaki �ey muhtemelen bir t�r olacakt�r. Bu genellikle C++'�n parametreli bir t�r gerektiren kodlarla ba�a ��kmas�n�n bir yoludur.

char de�i�kenlerinde E�er karakterin de�il de tamsay� de�erini yazd�rmak istiyorsak, bunu bir char'dan bir int'e d�n��t�rmek i�in static_cast 
kullanarak yapabiliriz.
�rnek: 
        #include <iostream>

        int main()
        {
            char ch{ 97 }; // 97 is ASCII code for 'a'
            std::cout << ch << " has value " << static_cast<int>(ch) << '\n'; // print value of variable ch as an int

            return 0;
        }
De�eri d�n��t�r�lecek ifade static_cast'a arg�man olarak verildi�inde, bu ifade de�erlendirilir. Bir de�i�keni ge�ti�imizde, bu de�i�kenin 
de�eri �retilir ve bu de�er daha sonra yeni t�r�ne d�n��t�r�l�r. De�i�kenin kendisi, de�erini yeni bir t�re d�n��t�rmekten etkilenmez. 
Yukar�daki �rnekte, ch adl� de�i�ken hala bir char'd�r ve de�eri, de�erini int'e d�n��t�rd�kten sonra bile ayn� kal�r.


Bir i�aretsiz say�y� i�aretli bir say�ya d�n��t�rmek i�in de static_cast operat�r�n� kullanabilirsiniz:

        #include <iostream>

        int main()
        {
            unsigned int u { 5 };
            int s { static_cast<int>(u) }; // return value of variable u as an int

            std::cout << s << '\n';
            return 0;
        }

static_cast operat�r� herhangi bir aral�k kontrol� yapmaz, bu nedenle bir de�eri, o de�eri i�ermeyen bir t�r i�in d�n��t�r�rseniz tan�ms�z 
davran�� olu�ur. Bu nedenle, yukar�da yap�lan i�aretsiz int'ten i�aretli int'e d�n���m�, i�aretsiz int'in de�eri, i�aretli int'in tutabilece�i
maksimum de�erden b�y�kse �ng�r�lemeyen sonu�lar verecektir.

Buna dikkat et i�te **** Static_cast operat�r�, d�n��t�r�len de�er yeni t�r�n aral���na uymuyorsa tan�ms�z davran�� �retecektir.

std::int8_t ve std::uint8_t'nin, ayn� zamanda ilgili h�zl� ve en k���k sabit geni�likli t�rlerle birlikte (fast ve least fixed-width types)
genellikle signed char ve unsigned char t�rleriyle ayn� �ekilde tan�mland���n� ve i�lendi�ini belirtildi�i gibi, chars t�rleri gibi davrand���n�
g�stermi�tik. �imdi bu durumun neden sorunlu olabilece�ini g�sterebiliriz:

        #include <cstdint>
        #include <iostream>

        int main()
        {
            std::int8_t myInt{65};      // initialize myInt with value 65
            std::cout << myInt << '\n'; // you're probably expecting this to print 65

            return 0;
        }



��nk� std::int8_t kendisini bir int olarak tan�mlar, yukar�daki program�n integral de�eri 65'i yazd�raca��n� d���nebilirsiniz.
Ancak, �o�u sistemde bu program, myInt'i bir signed char olarak i�leyerek A'y� yazd�racakt�r. Ancak bu garantilenmi� de�ildir 
(baz� sistemlerde asl�nda 65'i yazd�rabilir).

Bir std::int8_t veya std::uint8_t nesnesinin bir tam say� olarak i�lenmesini sa�lamak istiyorsan�z, de�eri static_cast kullanarak 
bir tam say�ya d�n��t�rebilirsiniz:

di�er 8 bitlik integer tiplerinde de ayn� durum olur ( fast ve least t�rler dahil )















*/