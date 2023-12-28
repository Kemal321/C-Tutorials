#include <iostream>

int main()
{
    return 0;
}
/*
                                         Opsiyonel Chapterdi ama ��renmek laz�m gibi hissettik

Modern bilgisayar mimarilerinde, haf�zan�n en k���k adreslenebilir birimi bir baytt�r. T�m nesnelerin benzersiz haf�za adreslerine
sahip olmas� gerekti�i i�in, bu nesnelerin en az bir bayt boyutunda olmas� gerekti�i anlam�na gelir. �o�u de�i�ken t�r� i�in bu
uygundur. Ancak, Boolean de�erler i�in bu biraz israft�r . Boolean t�rleri yaln�zca iki duruma sahiptir:do�ru (1) veya yanl�� (0).
Bu durum setinin saklanmas� yaln�zca bir bit gerektirir. Ancak, bir de�i�kenin en az bir bayt olmas� gerekiyorsa ve bir bayt 8 bit
ise, bu, bir Boolean'�n 1 biti kullan�p di�er 7'sini kullanmad��� anlam�na gelir.

�o�u durumda, bu uygundur - genellikle haf�zada 7 israf biti hakk�nda endi�elenmemiz gerektirecek kadar s�k� �al��mak durumunda de�iliz
(anla��l�rl�k ve bak�m kolayl��� i�in optimize etmek daha iyidir). Ancak, baz� depolama yo�unlu�u y�ksek durumlarda, depolama
verimlili�i ama�lar� i�in 8 ayr� Boolean de�erini tek bir bayta koyarak paket �eklinde kullanmak yararl� olabilir.
Bu i�lemleri yapabilmemiz i�in nesneleri bit d�zeyinde manip�le edebilmemiz gerekmektedir. Neyse ki, C++ bize bunu yapmak
i�in ara�lar sunar. Bir nesnenin i�indeki tekil bitleri de�i�tirmeye bit manip�lasyonu denir.

Bit manip�lasyonu belirli programlama ba�lamlar�nda (�rne�in, grafikler, �ifreleme, s�k��t�rma, optimizasyon) �ok kullan�l�r, 
ancak genel programlamada o kadar fazla kullan�lmaz.

Bu nedenle bu b�l�m�n tamam� iste�e ba�l� olarak okunacakt�r. Atlamaktan veya g�zden ge�irmekten �ekinmeyin ve daha sonra tekrar gelin.

Bit bayraklar� ( Bit Flags )
----------------------------
Bu noktaya kadar de�i�kenleri tek de�erleri tutmak i�in kulland�k:

                    int foo { 5 }; // foo'ya 5 de�erini atar (muhtemelen 32 bit depolama kullan�r)
                    std::cout << foo; // 5 de�erini yazd�r�r;

Ancak, nesneleri tek bir de�er ta��yan olarak de�il, bunun yerine bireysel bitlerin bir koleksiyonu olarak g�rebiliriz. Bir nesnenin bireysel 
bitleri Boolean de�erler olarak kullan�ld���nda, bu bitlere "bit bayraklar�" denir.

Not- Hesaplamada bayrak, bir programda baz� ko�ullar mevcut oldu�unda sinyal veren bir de�erdir. Bit bayra��yla true de�eri, ko�ulun var oldu�u 
anlam�na gelir.

Benzer �ekilde, Amerika Birle�ik Devletleri'nde bir�ok posta kutusunun yan taraf�nda k���k (genellikle k�rm�z�) fiziksel bayraklar bulunur. 
Giden posta ta��y�c� taraf�ndan al�nmay� beklerken, giden postan�n oldu�unu belirtmek i�in bayrak kald�r�l�r.

Bir bit bayra�� k�mesini tan�mlamak i�in genellikle uygun boyutta i�aretsiz bir tamsay� (sahip oldu�umuz bayrak say�s�na ba�l� olarak 8 bit, 
16 bit, 32 bit vb.) veya std::bitset kullan�r�z.

                    #include <bitset> // std::bitset i�in

                    std::bitset<8> mybitset {}; // 8 bit boyutu 8 flag i�in yer demektir

*** BEST -> Bit manip�lasyonu, i�aretsiz tamsay�lar� (veya std::bitset) a��k�a kullanman�z gereken birka� durumdan biridir.

Bu derste, std::bitset arac�l���yla bit manip�lasyonunun kolay yoldan nas�l yap�laca��n� g�sterece�iz. Bir sonraki ders setinde 
bunu daha zor ama �ok y�nl� bir �ekilde nas�l yapaca��m�z� ke�fedece�iz.
                    
Bit numaraland�rma ve bit konumlar�
-----------------------------------
Bir bit dizisi verildi�inde, genellikle bitleri 0'dan (1 de�il) ba�layarak sa�dan sola do�ru numaraland�r�r�z. Her say� bir bit konumunu belirtir.

                    76543210  Bit konumlar�
                    00000101  Bit dizisi
0000 0101 bit dizisi verildi�inde, 0 ve 2 konumundaki bitlerin de�eri 1, di�er bitlerin de�eri ise 0'd�r.
                    
Bitleri std::bitset arac�l���yla i�lemek
----------------------------------------
std::bitset, bit manip�lasyonu yapmak i�in yararl� olan 4 temel �ye fonksiyon sa�lar:

                    test(), bir bitin 0 m� yoksa 1 mi oldu�unu sorgulamam�z� sa�lar.
                    set() , bir biti a�mam�za ( 1 yapmak ) izin verir (e�er bit zaten a��ksa bu hi�bir �ey yapmaz).
                    reset() bir bit i kapatmam�za ( 0 yapmak ) izin verir (e�er bit zaten kapal�ysa bu hi�bir i�e yaramaz).
                    flip(), bir bit de�erini 0'dan 1'e veya tam tersi �ekilde �evirmemize olanak tan�r.

Bu i�levlerin her biri, �zerinde �al��mak istedi�imiz bitin konumunu tek arg�man olarak al�r. �rne�in:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<8> me{ 0b0000'0101 }; // 8 bit'e ihtiyac�m�z var, bit deseni 0000 0101 ile ba�l�yoruz
                        me.set(3);   // 3. pozisyondaki biti 1 olarak ayarla (�imdi 0000 1101)
                        me.flip(4);  // 4. biti ters �evir (�imdi 0001 1101)
                        me.reset(4); // 4. biti tekrar 0'a s�f�rla (�imdi 0000 1101)

                        std::cout << "T�m bitler: " << me << '\n';
                        std::cout << "3. bitin de�eri: " << me.test(3) << '\n';
                        std::cout << "4. bitin de�eri: " << me.test(4) << '\n';

                        return 0;
                    }

                    T�m bitler: 00001101
                    3. bitin de�eri: 1
                    4. bitin de�eri: 0

Bitlerimizin adlar�n� vermek kodumuzu daha okunakl� hale getirmeye yard�mc� olabilir:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr int  isHungry   { 0 }; // A� m�y�m
                        [[maybe_unused]] constexpr int  isSad      { 1 }; // �zg�n m�y�m
                        [[maybe_unused]] constexpr int  isMad      { 2 }; // K�zg�n m�y�m
                        [[maybe_unused]] constexpr int  isHappy    { 3 }; // Mutlu muyum
                        [[maybe_unused]] constexpr int  isLaughing { 4 }; // G�l�yor muyum
                        [[maybe_unused]] constexpr int  isAsleep   { 5 }; // Uykuda m�y�m
                        [[maybe_unused]] constexpr int  isDead     { 6 }; // �l� m�y�m
                        [[maybe_unused]] constexpr int  isCrying   { 7 }; // A�l�yor muyum

                        std::bitset<8> me{ 0b0000'0101 }; // 8 bit'e ihtiyac�m�z var, bit deseni 0000 0101 ile ba�l�yoruz
                        me.set(isHappy);      // 3. pozisyondaki biti 1 olarak ayarla (�imdi 0000 1101)
                        me.flip(isLaughing);  // 4. biti ters �evir (�imdi 0001 1101)
                        me.reset(isLaughing); // 4. biti tekrar 0'a s�f�rla (�imdi 0000 1101)

                        std::cout << "T�m bitler: " << me << '\n';
                        std::cout << "Mutlu muyum: " << me.test(isHappy) << '\n';
                        std::cout << "G�l�yor muyum: " << me.test(isLaughing) << '\n';

                        return 0;
                    }

Ayn� anda birden fazla bit almak veya ayarlamak istersek ne olur?
-----------------------------------------------------------------
std::bitset bunu kolayla�t�rm�yor. Bunu yapabilmek i�in veya std::bitset yerine i�aretsiz tamsay� bit bayraklar� kullanmak 
istiyorsak daha geleneksel y�ntemlere y�nelmemiz gerekiyor.

Std::bitset'in boyutu
---------------------
std::bitset'in h�z i�in optimize edilmi� olmas�d�r, bellek tasarrufu de�il. Bir std::bitset'in boyutu, genellikle bitleri tutmak i�in gerekli
olan bayt say�s�d�r, en yak�n sizeof(size_t)'e yuvarlanm��t�r. Bu, 32-bit makinelerde 4 bayt ve 64-bit makinelerde 8 baytt�r.

Bu nedenle, bir std::bitset<8>, teknik olarak sadece 8 biti saklamak i�in 1 bayt'a ihtiya� duydu�u halde, genellikle 4 veya 8 bayt bellek 
kullanacakt�r. Dolay�s�yla, std::bitset, bellek tasarrufu de�il, kullan�m kolayl��� istedi�imizde daha faydal� olacakt�r

std::bitset Sorgulama
---------------------
S�kl�kla kullan��l� olan birka� ba�ka �ye fonksiyon bulunmaktad�r:

                    - `size()`, bit k�mesindeki bit say�s�n� d�nd�r�r.
                    - `count()`, bit k�mesinde true olarak ayarlanan bitlerin say�s�n� d�nd�r�r. Bu, t�m bitlerin 0 oldu�unu veya herhangi bir
                                 bitin 1 oldu�unu belirlemek i�in kullan�labilir.
                    - `all()`, t�m bitlerin true olarak ayarlan�p ayarlanmad���n� belirten bir Boolean de�er d�nd�r�r.
                    - `any()`, herhangi bir bitin true olarak ayarlan�p ayarlanmad���n� belirten bir Boolean de�er d�nd�r�r.
                    - `none()`, hi�bir bitin true olarak ayarlan�p ayarlanmad���n� belirten bir Boolean de�er d�nd�r�r.

#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'1101 };
    std::cout << bits.size() << " bit bitset i�inde bulunmaktad�r\n"; // Bitset i�indeki bit say�s�n� yazd�r�r
    std::cout << bits.count() << " bit true olarak ayarlanm��t�r\n"; // True olarak ayarlanm�� bit say�s�n� yazd�r�r

    std::cout << std::boolalpha; // Bool de�erlerini yazarken "true" veya "false" yerine "true" veya "false" olarak yazd�rmak i�in kullan�l�r

    std::cout << "T�m bitler true olarak ayarlanm�� m�: " << bits.all() << '\n'; // T�m bitlerin true olarak ayarlan�p ayarlanmad���n� kontrol eder
    std::cout << "Baz� bitler true olarak ayarlanm�� m�: " << bits.any() << '\n'; // Herhangi bir bitin true olarak ayarlan�p ayarlanmad���n� kontrol eder
    std::cout << "Hi�bir bit true olarak ayarlanm�� m�: " << bits.none() << '\n'; // Hi�bir bitin true olarak ayarlan�p ayarlanmad���n� kontrol eder

    return 0;
}

8 bit bitset i�inde bulunmaktad�r
3 bit true olarak ayarlanm��t�r
T�m bitler true olarak ayarlanm�� m�: false
Baz� bitler true olarak ayarlanm�� m�: true
Hi�bir bit true olarak ayarlanm�� m�: false

Bit i�lemcileri (bitwise operators)
-----------------------------------

| Operat�r        | Sembol | Form�l  | ��lem                                                                       |
|-----------------|--------|---------|-----------------------------------------------------------------------------|
| Sol Kayd�rma    | <<     | x << y  | x i�indeki t�m bitler y bit sola kayd�r�l�r                                 |
| Sa� Kayd�rma    | >>     | x >> y  | x i�indeki t�m bitler y bit sa�a kayd�r�l�r                                 |
| Bitwise NOT     | ~      | ~x      | x i�indeki t�m bitler ters �evrilir                                         |
| Bitwise AND     | &      | x & y   | x i�indeki her bir bit, y i�indeki ilgili bit ile AND i�lemine tabi tutulur |
| Bitwise OR      | |      | x | y   | x i�indeki her bir bit, y i�indeki ilgili bit ile OR i�lemine tabi tutulur  |
| Bitwise XOR     | ^      | x ^ y   | x i�indeki her bir bit, y i�indeki ilgili bit ile XOR i�lemine tabi tutulur |
--------------------------------------------------------------------------------------------------------------------

A�a��daki �rneklerde b�y�k �l��de 4-bit ikili de�erlerle �al��aca��z. Bu, kolayl�k ve �rnekleri basit tutma amac�yla yap�lm��t�r. Ger�ek
programlarda, kullan�lan bit say�s� nesnenin boyutuna ba�l�d�r (�rne�in, 2 byte bir nesne 16 bit saklar).

Okunabilirlik a��s�ndan, 0b �nekini (�rne�in, 0b0101 yerine sadece 0101 kullanaca��z) kod �rneklerinin d���nda atlayaca��z.

Bit i�lemcileri, tamsay� tipleri ve std::bitset i�in tan�mlanm��t�r. �rneklerimizde ��kt�y� ikili bi�imde yazd�rmak daha kolay oldu�u i�in
std::bitset kullanaca��z.

��aretli operat�rlerle i�lem yaparken C++20'den �nce bir�ok operat�r, uygulamaya �zg� sonu�lar d�nd�rebilir veya di�er potansiyel sorunlara yol
a�abilir. Bu t�r sorunlar� �nlemek i�in i�aretsiz operat�rleri (veya std::bitset) kullanmak genellikle daha iyidir.

S�rprizleri �nlemek i�in, bit i�lemcilerini i�aretsiz i�lemciler veya std::bitset ile kullan�n.

Bit baz�nda sola kayd�rma (<<) ve bit baz�nda sa�a kayd�rma (>>) operat�rleri
-----------------------------------------------------------------------------

Bitwise left shift (<<) operat�r�, bitleri sola kayd�r�r. Sol operand, bitleri kayd�rmak i�in ifadeyi temsil eder ve sa� operand, sola ka�
bit kayd�r�laca��n� belirten bir tamsay�d�r.

Yani x << 1 dedi�imizde, "de�i�ken x i�indeki bitleri bir yer sola kayd�r" diyoruz. Sa� taraftan kayd�r�lan yeni bitlere 0 de�eri atan�r.

�rne�in:

0011 << 1, 0110'd�r.
0011 << 2, 1100'dir.
0011 << 3, 1000'dir.
���nc� durumda dikkat edilmesi gereken �nemli bir nokta, say�n�n sonundan bir bitin kayd�r�lmas�d�r! Binary say�n�n sonundan kayd�r�lan bitler
kal�c� olarak kaybolur.

Bitwise right shift (>>) operat�r� ise bitleri sa�a kayd�r�r.

�rne�in:

1100 >> 1, 0110'd�r.
1100 >> 2, 0011'dir.
1100 >> 3, 0001'dir.
���nc� durumda dikkat edilmesi gereken bir ba�ka �nemli nokta, say�n�n sa� ucundan bir bitin kayd�r�lmas�d�r ve bu bit kaybolur.

��te bir bit kayd�rma �rne�i:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> x{0b1100};

                        std::cout << x << '\n'; // x'i binary olarak yazd�r
                        std::cout << (x >> 1) << '\n'; // 1 sa�a kayd�r, sonu�: 0110
                        std::cout << (x << 1) << '\n'; // 1 sola kayd�r, sonu�: 1000

                        return 0;
                    }
                    ��kt�: 
                    1100
                    0110
                    1000

Nas�l!? operator<< ve operator>> giri� ve ��k�� i�in kullan�lm�yor mu?
----------------------------------------------------------------------

Evet, kesinlikle.

G�n�m�zde, programlar genellikle bitleri kayd�rmak i�in biti�ik sola ve sa�a kayd�rma operat�rlerini �ok�a kullanmazlar. Bunun yerine,
genellikle bitwise sola kayd�rma operat�r�, std::cout (veya di�er ak�� nesneleri) ile metin ��kt�s� almak i�in kullan�l�r. A�a��daki 
program� d���n�n:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        unsigned int x{0b0100};
                        x = x << 1; // Sol kayd�rma i�in operator<< kullan
                        std::cout << std::bitset<4>{x} << '\n'; // ��kt� i�in operator<< kullan

                        return 0;
                    }
                    ��kt�s�:
                    1000


Yukar�daki programda, operator<<'in bir durumda bitleri kayd�rmak, di�er durumda ise x'i ��kt� olarak g�stermek i�in nas�l �al��t���n� nas�l
anl�yor? Cevap �udur: std::cout, operator<<'in a��r� y�klenmi� (alternatif bir tan�m sa�lam��) versiyonuna sahiptir ve bu versiyon, bit kayd�rma
yerine konsol ��kt�s� yapar.

Derleyici, operator<<'in sol operand�n�n std::cout oldu�unu g�rd���nde, std::cout taraf�ndan a��r� y�klenmi� olan ve ��kt� yapmak i�in kullan�lan
operator<< versiyonunu �a��rmas� gerekti�ini bilir. E�er sol operand integral bir t�r ise, operator<<, genellikle yapt��� bit kayd�rma
davran���n� ger�ekle�tirmesi gerekti�ini bilir.

Ayn�s� operator>> i�in de ge�erlidir.

Unutmay�n ki hem ��kt� hem de sola kayd�rma i�in operator<< kullan�yorsan�z, parantez i�ine almak gereklidir:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> x{ 0b0110 };

                        std::cout << x << 1 << '\n'; // x'in de�erini (0110) yazd�r, ard�ndan 1'i ekle ve yeni sat�ra ge�
                        std::cout << (x << 1) << '\n'; // x'i 1 sola kayd�r�lm�� halini (1100) yazd�r ve yeni sat�ra ge�

                        return 0;
                    }

                    ��kt�s�:
                    01101
                    1100    

�lk sat�r, x'in de�erini (0110) ve ard�ndan 1 say�s�n� yazd�r�r. �kinci sat�r ise x'in 1 sola kayd�r�lm�� de�erini (1100) yazd�r�r.

Operator a��r� y�klenmesi hakk�nda daha fazla bilgi, kendi ama�lar�n�z i�in operat�rleri nas�l a��r� y�kleyece�iniz konusunda
gelecekteki bir b�l�mde tart���lacakt�r.

Bitwise NOT
-----------
Bitwise NOT (~) operat�r�, belki de t�m bitwise operat�rlerin en kolay anla��labileni olabilir. Bu operat�r, her bir biti basit�e 0'dan 1'e veya
tam tersine �evirir. Unutmay�n ki bitwise NOT'un sonucu veri tipinizin boyutuna ba�l�d�r.

4 bit �evirme:
~0100, 1011'dir

8 bit �evirme:
~0000 0100, 1111 1011'dir

Hem 4 bit hem de 8 bit durumlar�nda, ayn� say�yla ba�lar�z (binary 0100, decimal 7'nin 07 ile ayn� oldu�u gibi), ancak farkl� bir sonu� elde ederiz.

Bunu a�a��daki programda g�rebiliriz:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << ~std::bitset<4>{ 0b0100 } << ' ' << ~std::bitset<8>{ 0b0100 } << '\n';

                        return 0;
                    }
                    ��kt� olarak:
                    1011 11111011
Bitwise OR
----------

Bitwise OR (|) mant�ksal OR operat�r�n�n benzer �ekilde �al���r. Ancak, OR operat�r�n� kullanarak operat�rleri tek bir sonu� �retmek yerine,
bitwise OR her bir bite uygular! �rne�in, ifade 0b0101 | 0b0110'� d���n�n.

Herhangi bir bitwise i�lemi yapmak i�in, iki operand� �u �ekilde hizalamak en kolayd�r:

                    0 1 0 1 OR
                    0 1 1 0

Ve sonra i�lemi her bit s�tununa uygula.

Hat�rlarsan�z, mant�ksal OR, sol operand�n, sa� operand�n veya her ikisinin de do�ru (1) oldu�u durumda do�ru (1) olarak de�erlendirilir ve aksi
takdirde 0'd�r. Bitwise OR ise sol, sa� veya her ikisi de 1 oldu�unda 1'e ve aksi takdirde 0'a de�erlendirilir. Bu nedenle, ifade �u �ekilde
de�erlendirilir:

                    0 1 0 1 OR
                    0 1 1 0
                    -------
                    0 1 1 1

                    Sonucumuz 0111 ikilisidir.

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0101 } | std::bitset<4>{ 0b0110 }) << '\n';

                        return 0;
                    }
                    ��kt� olarak:
                    0111

Ayn� �eyi 0b0111 | gibi OR ifadelerini bile�ik hale getirmek i�in de yapabiliriz. 0b0011 | 0b0001. Bir s�tundaki bitlerden herhangi biri 1 ise 
o s�tunun sonucu 1 olur.

                    0 1 1 1 OR
                    0 0 1 1 OR
                    0 0 0 1
                    --------
                    0 1 1 1
                    ��te yukar�dakilerin kodu:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0111 } | std::bitset<4>{ 0b0011 } | std::bitset<4>{ 0b0001 }) << '\n';

                        return 0;
                    }
                    ��kt�:
                    0111
                    
Bitwise AND
-----------

Bitwise AND (&) yukar�dakine benzer �ekilde �al���r. Mant�ksal AND, sol operand ve sa� operand ikisi de do�ru (1) oldu�unda do�ru olarak
de�erlendirilir. Bitwise AND ise s�tundaki her iki bit de 1 ise 1'e de�erlendirilir. 0b0101 & 0b0110 ifadesini d���n�n. Her bir biti hizalay�p
her bit s�tunu i�in AND i�lemi uygulayarak:

                    0 1 0 1 AND
                    0 1 1 0
                    --------
                    0 1 0 0

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0101 } & std::bitset<4>{ 0b0110 }) << '\n';

                        return 0;
                    }
                    ��kt�:
                    0100

Benzer �ekilde, 0b0001 & 0b0011 & 0b0111 gibi AND ifadelerini bile�ik hale getirmek i�in de ayn� �eyi yapabiliriz. Bir s�tundaki t�m bitler 1 
ise o s�tunun sonucu 1 olur.

                    0 0 0 1 AND
                    0 0 1 1 AND
                    0 1 1 1
                    --------
                    0 0 0 1

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0001 } & std::bitset<4>{ 0b0011 } & std::bitset<4>{ 0b0111 }) << '\n';

                        return 0;
                    }
                    ��kt�:
                    0001

Bitwise XOR
-----------

Son operat�r, bitwise XOR (^) veya di�er ad�yla exclusive or (�zel veya) olarak bilinen operat�rd�r.

�ki operand� de�erlendirirken, XOR, operandlardan biri ve sadece biri do�ru (1) ise do�ru olarak de�erlendirilir. E�er ikisi de 
do�ru veya ikisi de yanl�� ise 0 olarak de�erlendirilir. 0b0110 ^ 0b0011 ifadesini d���n�n:

                    0 1 1 0 XOR
                    0 0 1 1
                    -------
                    0 1 0 1

0b0001 ^ 0b0011 ^ 0b0111 gibi bile�ik XOR ifadesi s�tun stilini de de�erlendirmek m�mk�nd�r. Bir s�tunda �ift say�da 1 bit varsa sonu� 0
olur. Bir s�tunda tek say�da 1 bit varsa sonu� 1 olur.
                    0 0 0 1 XOR
                    0 0 1 1 XOR
                    0 1 1 1
                    --------
                    0 1 0 1

Bitsel atama operat�rleri
-------------------------
Aritmetik atama operat�rlerine benzer �ekilde C++, de�i�kenlerin kolay de�i�tirilmesini kolayla�t�rmak i�in bit d�zeyinde atama operat�rleri sa�lar.

| Operat�r                   | Sembol | Form      | ��lem                                       |
|----------------------------|--------|-----------|---------------------------------------------|
| Sol kayd�rma atama         | <<=    | x <<= y   | x'i y bit sola kayd�r                       |
| Sa� kayd�rma atama         | >>=    | x >>= y   | x'i y bit sa�a kayd�r                       |
| Bitwise OR atama           | |=     | x |= y    | x'i x | y'ye atar                           |
| Bitwise AND atama          | &=     | x &= y    | x'i x & y'ye atar                           |
| Bitwise XOR atama          | ^=     | x ^= y    | x'i x ^ y'ye atar                           |
|----------------------------|--------|-----------|---------------------------------------------|

�rne�in x = x >> 1; yazmak yerine x >>= 1; yazabilirsiniz.

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> bits { 0b0100 };
                        bits >>= 1;
                        std::cout << bits << '\n';

                        return 0;
                    }
                    ��kt�:
                    0010

Bitwise NOT atama operat�r� yoktur. Bu, di�er bitwise operat�rlerinin ikili (binary) olmas�na kar��n, bitwise NOT'un tekil (unary) olmas�
nedeniyledir (yani bir ~= operat�r�n�n sa� taraf�nda ne olacakt�r?). E�er t�m bitleri �evirmek istiyorsan�z, burada normal atama
kullanabilirsiniz: x = ~x;

�zet

Bitwise operasyonlar� s�tun y�ntemini kullanarak nas�l de�erlendirece�imizi �zetleyerek:

Bitwise OR de�erlendirilirken, bir s�tundaki herhangi bir bit 1 ise, o s�tunun sonucu 1'dir.
Bitwise AND de�erlendirilirken, bir s�tundaki t�m bitler 1 ise, o s�tunun sonucu 1'dir.
Bitwise XOR de�erlendirilirken, bir s�tunda tek say�da 1 biti varsa, o s�tunun sonucu 1'dir.
Bir sonraki derste, bu operat�rlerin nas�l bit maskeleriyle birlikte kullan�labilece�ini ve bit manip�lasyonunu nas�l kolayla�t�rd���n�
ke�fedece�iz

O.3 � Bitsel operat�rler ve bit maskeleriyle bit manip�lasyonu
--------------------------------------------------------------
Bu ders operat�rlerin nas�l daha yayg�n bir �ekilde kullan�ld���na bir g�z atal�m.

Bit Maskeleri
-------------

Bireysel bitleri manip�le etmek (�rne�in, a�mak veya kapatmak) i�in belirli bitleri tan�mlaman�n bir yolu olmal�d�r. Ne yaz�k ki, bitwise
operat�rler bit pozisyonlar�yla nas�l �al��acaklar�n� bilmezler. Bunun yerine, bit maskeleri ile �al���rlar.

Bir bit maskesi, ard���k i�lemler taraf�ndan de�i�tirilecek belirli bitleri se�mek i�in kullan�lan �nceden tan�mlanm�� bir bit k�mesidir.

Ger�ek bir �rnek d���n�n: Bir pencere �er�evesini boyamak istiyorsunuz. Dikkatli olmazsan�z, sadece pencere �er�evesini de�il, ayn� zamanda cam�
da boyama riskiyle kar��la��rs�n�z. Cam� ve boyanmas�n� istemedi�iniz di�er k�s�mlar� belirleyip maskeleme band� uygulayabilirsiniz. Sonra 
boyad���n�zda, maskeleme band� boyanmas�n� istemedi�iniz her �eyi engeller. Sonu� olarak, sadece maskeleme yap�lmayan k�s�mlar
(boyanmas�n� istedi�iniz k�s�mlar) boyan�r.

Bir bit maskesi, bitler i�in esasen ayn� i�levi yerine getirir. Bit maskesi, bitwise operat�rleri istenmeyen bitlere dokunmaktan al�koyar ve
de�i�tirmek istedi�imizlere eri�im sa�lar.

�nce basit birka� bit maskesini nas�l tan�mlayaca��m�z� ke�fedin, ard�ndan onlar� nas�l kullanaca��n�z� g�sterece�iz.

C++14'te Bit Maskelerini Tan�mlama
----------------------------------

En basit bit maskesi seti, her bir bit pozisyonu i�in bir bit maskesi tan�mlamakt�r. �lgilenmedi�imiz bitleri maskelemek i�in 0'lar� kullan�r�z ve
de�i�tirmek istedi�imiz bitleri belirtmek i�in 1'leri kullan�r�z.

Bit maskeleri literal olabilir, ancak genellikle anlaml� bir isim verilebilmesi ve kolayca yeniden kullan�labilmesi i�in sembolik sabitler olarak
tan�mlan�rlar.

C++14, ikili literalleri destekledi�i i�in bu bit maskelerini tan�mlamak kolayd�r:

                    #include <cstdint>

                    // Bit maskelerini tan�mla
                    constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                    constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                    constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                    constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                    constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                    constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                    constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                    constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

Art�k her bit konumunu temsil eden bir dizi sembolik sabitimiz var. Bunlar� bitleri de�i�tirmek i�in kullanabiliriz (bunun nas�l yap�laca��n�
birazdan g�sterece�iz).

C++11 veya daha �nceki s�r�mlerde Bit Maskelerini Tan�mlama
-----------------------------------------------------------

C++11, ikili literalleri desteklemedi�i i�in sembolik sabitleri ayarlamak i�in ba�ka y�ntemler kullanmam�z gerekiyor. Bu i�i yapman�n
iki iyi y�ntemi bulunmaktad�r.

�lk y�ntem, onalt�l�k literalleri kullanmakt�r.

Hexadecimal	   0	 1	      2	      3      4       5        6       7	      8	      9	      A       B	      C	      D	      E	      F
Binary	     0000	0001	0010	0011	0100	0101	0110	0111	1000	1001	1010	1011	1100	1101	1110	1111

Bu nedenle, bit maskelerini onalt�l�k say� kullanarak �u �ekilde tan�mlayabiliriz:

                    constexpr std::uint8_t mask0{ 0x01 }; // 0000 0001 i�in onalt�l�k
                    constexpr std::uint8_t mask1{ 0x02 }; // 0000 0010 i�in onalt�l�k
                    constexpr std::uint8_t mask2{ 0x04 }; // 0000 0100 i�in onalt�l�k
                    constexpr std::uint8_t mask3{ 0x08 }; // 0000 1000 i�in onalt�l�k
                    constexpr std::uint8_t mask4{ 0x10 }; // 0001 0000 i�in onalt�l�k
                    constexpr std::uint8_t mask5{ 0x20 }; // 0010 0000 i�in onalt�l�k
                    constexpr std::uint8_t mask6{ 0x40 }; // 0100 0000 i�in onalt�l�k
                    constexpr std::uint8_t mask7{ 0x80 }; // 1000 0000 i�in onalt�l�k


Bazen �nceden gelen onalt�l�k 0'lar atlanabilir (�rne�in, 0x01 yerine sadece 0x1 g�r�rs�n�z). Her iki durumda da, bu, onalt�l�k-birlik d�n���ne 
a�ina de�ilseniz biraz zor okunabilir olabilir.

Daha kolay bir y�ntem, tek bir biti uygun konuma kayd�rmak i�in sol kayd�rma operat�r�n� kullanmakt�r:

                    constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
                    constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
                    constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
                    constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
                    constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
                    constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
                    constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
                    constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000

Bir biti test etme (a��k veya kapal� oldu�unu kontrol etme)
-----------------------------------------------------------

Art�k bir dizi bit maskemiz oldu�una g�re, bu maskeleri bit bayrak de�i�keniyle birle�tirerek bit bayraklar�m�z� de�i�tirebiliriz.

Bir bitin a��k veya kapal� olup olmad���n� belirlemek i�in, uygun bit maskesi ile biti�ikte bitwise AND kullan�r�z:

#include <cstdint>
#include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bit boyutunda, 8 bayrak i�in yer var

                        std::cout << "bit 0 " << (static_cast<bool>(flags & mask0) ? "a��k\n" : "kapal�\n");
                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "a��k\n" : "kapal�\n");

                        return 0;
                    }
                    ��kt�:
                    bit 0 is a��k
                    bit 1 is kapal�

Bunu nas�l �al��t���n� inceleyelim.

flags & mask0 durumunda, 0000'0101 & 0000'0001'e sahibiz. Bunlar� hizalayal�m:
                    flags:   0000 0101 &
                    mask0:   0000 0001
                    -----------------
                    sonu�:   0000 0001

Sonra 0000'0001'i bir bool'e d�n��t�r�yoruz. ��nk� herhangi bir s�f�r olmayan say� true'ya d�n���r ve bu de�er bir s�f�r olmayan bir basama�a
sahip oldu�u i�in bu, true olarak de�erlendirilir.

flags & mask1 durumunda, 0000'0101 & 0000'0010'a sahibiz. Bunlar� hizalayal�m:

                    0000'0101 &
                    0000'0010
                    ---------
                    0000'0000

S�f�r de�eri false de�erine d�n��t���nden ve bu de�er yaln�zca s�f�r basamaktan olu�tu�undan, bu false olarak de�erlendirilir.

Bir bit i a�mak ( Set )
-----------------------
Bir biti (de�eri 1'e �evirmek) a�mak i�in, uygun bit i�in bit maskesi ile bitwise OR equals (operator |=) kullan�r�z:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bitlik bir alan, 8 bayrak i�in yer

                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "a��k\n" : "kapal�\n");

                        flags |= mask1; // 1. bit'i a�

                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "a��k\n" : "kapal�\n");

                        return 0;
                    }
                    ��kt�:
                    bit 1 is kapal�
                    bit 1 is a��k

Bitwise OR kullanarak ayn� anda birden fazla biti de a�abiliriz:

                    flags |= (mask4 | mask5); // 4 ve 5. bitleri ayn� anda a��yoruz

Bir bit i kapatmak ( resetting ) 
--------------------------------
Bir biti (0 de�erine) kapatmak (temizlemek) i�in Bitwise AND ve Bitwise NOT'u birlikte kullan�r�z:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // bit 0'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // bit 1'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // bit 2'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // bit 3'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // bit 4'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // bit 5'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // bit 6'� temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // bit 7'� temsil eder 

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bit boyutu, 8 bayrak i�in yer anlam�na gelir

                        std::cout << "bit 2: " << (static_cast<bool>(flags & mask2) ? "a��k\n" : "kapal�\n");

                        flags &= ~mask2; // bit 2 yi kapat

                        std::cout << "bit 2: " << (static_cast<bool>(flags & mask2) ? "a��k\n" : "kapal�\n");

                        return 0;
                    }

                    ��kt�:
                    bit 2: a��k
                    bit 2: kapal�

Ayn� anda birden fazla biti kapatabiliriz:

                    flags &= ~(maske4 | maske5); // 4 ve 5. bitleri ayn� anda kapat�yoruz

Baz� derleyiciler bu durumda uyar� verebilir ��nk� signed bir de�eri unsigned de�ere d�n��t�r�yoruz bu da narrowing conversion olur. 
Bu durumu atlatmak i�in static_cast<>() yaparak ��zebiliriz. 

Bir biti �evirme
----------------
Bir bit durumunu (0'dan 1'e veya 1'den 0'a) de�i�tirmek i�in Bitwise XOR kullan�r�z:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bitlik boyut, 8 bayrak i�in yer demektir

                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "a��k\n" : "kapal�\n");
                        flags ^= mask2; // 2. bit'i �evir
                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "a��k\n" : "kapal�\n");
                        flags ^= mask2; // 2. bit'i �evir
                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "a��k\n" : "kapal�\n");

                        return 0;
                    }
                    ��kt�:
                    bit 2 a��k
                    bit 2 kapal�
                    bit 2 a��k

Ayn� anda birden fazla biti �evirebiliriz:
                    flags ^= (mask4 | mask5); // 4 ve 5. bitleri ayn� anda �evir

Bit maskeleri ve std::bitset
----------------------------
std::bitset, tam bir bit i�lemcisi setini destekler. Bu nedenle, bireysel bitleri de�i�tirmek i�in fonksiyonlar� (test, set, reset ve flip) 
kullanmak daha kolay olsa da, isterseniz bit i�lemcileri ve bit maskelerini kullanabilirsiniz.

Neden istersiniz? Fonksiyonlar yaln�zca bireysel bitleri de�i�tirmenize izin verir. Bit i�lemcileri size ayn� anda birden �ok biti
de�i�tirme olana�� tan�r.

                    #include <bitset>
                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::bitset<8> mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::bitset<8> flags{ 0b0000'0101 }; // 8 bitlik boyut, 8 bayrak i�in yer demektir
                        std::cout << "1. bit " << (flags.test(1) ? "a��k\n" : "kapal�\n");
                        std::cout << "2. bit " << (flags.test(2) ? "a��k\n" : "kapal�\n");

                        flags ^= (mask1 | mask2); // 1. ve 2. bitleri �evir
                        std::cout << "1. bit " << (flags.test(1) ? "a��k\n" : "kapal�\n");
                        std::cout << "2. bit " << (flags.test(2) ? "a��k\n" : "kapal�\n");

                        flags |= (mask1 | mask2); // 1. ve 2. bitleri a�
                        std::cout << "1. bit " << (flags.test(1) ? "a��k\n" : "kapal�\n");
                        std::cout << "2. bit " << (flags.test(2) ? "a��k\n" : "kapal�\n");

                        flags &= ~(mask1 | mask2); // 1. ve 2. bitleri kapat
                        std::cout << "1. bit " << (flags.test(1) ? "a��k\n" : "kapal�\n");
                        std::cout << "2. bit " << (flags.test(2) ? "a��k\n" : "kapal�\n");

                        return 0;
                    }

                    ��kt�:
                    bit 1 kapal�
                    bit 2 a��k
                    bit 1 a��k
                    bit 2 kapal�
                    bit 1 a��k
                    bit 2 a��k
                    bit 1 kapal�
                    bit 2 kapal�

Bit maskelerini anlaml� hale getirme

Bit maskelerimize "mask1" veya "mask2" gibi isimler vermek bize hangi bitin manip�le edildi�ini s�yler, ancak bu bit bayra��n�n asl�nda ne
i�in kullan�ld���na dair herhangi bir g�sterge vermez.

*** BEST -> bit bayraklar�n�n anlam�n� belgeleme amac�yla bit maskelerine anlaml� isimler vermektedir. ��te yazabilece�imiz bir oyundan �rnek:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        // Bir dizi fiziksel/duygusal durumu tan�mla
                        [[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
                        [[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
                        [[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
                        [[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
                        [[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
                        [[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
                        [[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
                        [[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

                        std::uint8_t me{}; // Ba�lang��ta t�m bayraklar/konfig�rasyonlar kapal�
                        me |= (isHappy | isLaughing); // Mutlu ve g�l�yorum
                        me &= ~isLaughing; // Art�k g�l�msemiyorum

                        // Birka� durumu sorgula
                        // (Sonu�lar� boolean bir de�er olarak yorumlamak i�in static_cast<bool> kullanaca��z)
                        std::cout << std::boolalpha; // 1 veya 0 yerine true veya false yazd�r
                        std::cout << "Mutluyum mu? " << static_cast<bool>(me & isHappy) << '\n';
                        std::cout << "G�l�yor muyum? " << static_cast<bool>(me & isLaughing) << '\n';

                        return 0;
                    }
Std::bitset kullan�larak uygulanan ayn� �rnek:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        // Bir dizi fiziksel/duygusal durumu tan�mla
                        [[maybe_unused]] constexpr std::bitset<8> isHungry   { 0b0000'0001 };
                        [[maybe_unused]] constexpr std::bitset<8> isSad      { 0b0000'0010 };
                        [[maybe_unused]] constexpr std::bitset<8> isMad      { 0b0000'0100 };
                        [[maybe_unused]] constexpr std::bitset<8> isHappy    { 0b0000'1000 };
                        [[maybe_unused]] constexpr std::bitset<8> isLaughing { 0b0001'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isAsleep   { 0b0010'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isDead     { 0b0100'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isCrying   { 0b1000'0000 };

                        std::bitset<8> me{}; // Ba�lang��ta t�m bayraklar/konfig�rasyonlar kapal�
                        me |= (isHappy | isLaughing); // Mutlu ve g�l�yorum
                        me &= ~isLaughing; // Art�k g�l�msemiyorum

                        // Birka� durumu sorgula (any() fonksiyonunu kullanarak herhangi bir bitin ayarl� olup olmad���n� kontrol ediyoruz)
                        std::cout << std::boolalpha; // 1 veya 0 yerine true veya false yazd�r
                        std::cout << "Mutluyum mu? " << (me & isHappy).any() << '\n';
                        std::cout << "G�l�yor muyum? " << (me & isLaughing).any() << '\n';

                        return 0;
                    }

�ki not burada: �lk olarak, std::bitset, bit maskelerini kullanarak bit sorgulamak i�in g�zel bir fonksiyona sahip de�ildir. Bu nedenle,
konumsal dizinler yerine bit maskelerini kullanmak istiyorsan�z, Bitwise AND'i kullanarak bitleri sorgulaman�z gerekecek. �kinci olarak,
any() fonksiyonunu kullan�yoruz, bu fonksiyon herhangi bir bit ayarl�ysa true d�nd�r�r ve aksi takdirde false d�nd�r�r, b�ylece sorgulad���m�z
bitin a��k veya kapal� olup olmad���n� kontrol edebiliriz.

Bit bayraklar� en �ok benzer bayrak de�i�kenlerinizin �ok say�da oldu�u durumlarda anlam kazan�r. Yukar�daki �rneklerde dikkat eden okuyucular,
asl�nda hi�bir bellek tasarrufu yap�lmad���n� fark edebilirler. Normalde 8 ayr� boolean de�eri 8 byte al�rd�. Ancak yukar�daki �rnekler 
(std::uint8_t kullanarak) 9 byte kullan�yor - 8 byte bit maskeleri tan�mlamak i�in ve 1 byte bayrak de�i�keni i�in!

Bit bayraklar�, bir�ok benzer bayrak de�i�keniniz oldu�unda en mant�kl�d�r. �rne�in, yukar�daki �rnekte oldu�u gibi, bir ki�i (ben) yerine 100
ki�inizin oldu�unu hayal edin. Her bir ki�i i�in 8 booleen kullan�rsan�z (her bir olas� durum i�in bir tane), 800 byte bellek kullan�rd�n�z.
Bit bayraklar� kullanarak, 8 byte'l�k bit maskeleri ve 100 byte'l�k bit bayrak de�i�kenleri kullan�rs�n�z, toplamda 108 byte bellek kullan�m�
olur - yakla��k olarak 8 kat daha az bellek.

�o�u program i�in, bit bayraklar� kullanarak tasarruf edilen bellek miktar�, eklenen karma��kl��� hakl� ��karmaz. Ancak on binlerce veya 
milyonlarca benzer nesnenin bulundu�u programlarda, bit bayraklar� kullanmak bellek kullan�m�n� �nemli �l��de azaltabilir. �htiya� duyuldu�unda 
kullan�labilen yararl� bir optimizasyon arac�d�r.

Bit bayraklar� ve bit maskelerinin mant�kl� olabilece�i ba�ka bir durum daha vard�r. Diyelim ki 32 farkl� se�ene�i alabilen bir fonksiyonunuz
var. Bu fonksiyonu yazman�n bir yolu, 32 ayr� boolean parametre kullanmakt�r.
�rnek: 

void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8, bool option9, 
bool option10, bool option11, bool option12, bool option13, bool option14, bool option15, bool option16, bool option17, bool option18, 
bool option19, bool option20, bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27,
bool option28, bool option29, bool option30, bool option31, bool option32);


Umuyorum ki parametrelerinize daha a��klay�c� isimler verirsiniz, ancak buradaki ama� parametre listesinin ne kadar uzun oldu�unu g�stermektir.

Sonra fonksiyonu 10 ve 32 numaral� se�eneklerin true olarak ayarland��� bir �a�r� yapmak istedi�inizde, bunu �u �ekilde yapman�z gerekirdi:

someFunction(false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false, false, false, false, false, true);


Bu okumas� olduk�a zor (true olarak ayarlanan se�enek 9, 10 veya 11 mi?), ve ayn� zamanda hangi arg�man�n hangi se�ene�e kar��l�k geldi�ini
hat�rlaman�z� gerektirir ("d�zenleme bayra��n�" 9., 10. veya 11. parametre mi ayarl�yoruz?).

Bunun yerine, e�er fonksiyonu �u �ekilde bit bayraklar� kullanarak tan�mlarsan�z:

                        void someFunction(std::bitset<32> options);

Daha sonra yaln�zca istedi�iniz se�enekleri iletmek i�in bit bayraklar�n� kullanabilirsiniz:

                        someFunction(option10 | option32);


Bu �ok daha okunakl�.

Bu, OpenGL'in, say�s�z ard���k Boolean parametre yerine bit bayrak parametrelerini kullanmay� tercih etti�i nedenlerden biridir.

��te OpenGL'den bir �rnek fonksiyon �a�r�s�:

                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // rengi ve derinlik arabelle�ini temizle

GL_COLOR_BUFFER_BIT ve GL_DEPTH_BUFFER_BIT, a�a��daki gibi tan�mlanan bit maskeleridir (gl2.h dosyas�nda):

                        #define GL_DEPTH_BUFFER_BIT               0x00000100
                        #define GL_STENCIL_BUFFER_BIT             0x00000400
                        #define GL_COLOR_BUFFER_BIT               0x00004000

�oklu bitleri i�eren bit maskeleri
----------------------------------
Genellikle bit maskeleri tek bir biti se�mek i�in kullan�lsa da, ayn� zamanda birden �ok biti se�mek i�in de kullan�labilirler. Bunu yaparken
biraz daha karma��k bir �rne�e bakal�m.

TV'ler ve monit�rler gibi renkli g�r�nt� cihazlar�, her biri bir renk noktas�n� g�r�nt�leyebilen milyonlarca pikselden olu�ur. Her renk noktas�,
�� ���n kombinasyonunun bir sonucudur: bir k�rm�z�, bir ye�il ve bir mavi (RGB). Bu ���nlar�n yo�unlu�u, farkl� renkleri �retmek i�in de�i�tirilir.

Genellikle, belirli bir piksel i�in R, G ve B'nin yo�unlu�u 8 bitlik i�aretsiz bir tamsay� taraf�ndan temsil edilir. �rne�in, k�rm�z� bir pikselin
R=255, G=0, B=0 olabilir. Mor bir pikselin R=255, G=0, B=255 olabilir. Orta gri bir pikselin R=127, G=127, B=127 olabilir.

Bir piksele renk de�erleri atand���nda, R, G ve B'nin yan� s�ra genellikle bir 4. de�er olan A da kullan�l�r. "A", "alfa"n�n k�saltmas�d�r ve 
rengin ne kadar saydam oldu�unu kontrol eder. E�er A=0 ise, renk tamamen �effaft�r. E�er A=255 ise, renk opakt�r.

Genellikle, R, G, B ve A bir tamsay�da tek bir 32 bitlik tamsay� olarak depolan�r, her bir bile�en i�in 8 bit kullan�l�r:

                    | Bits 31-24 | Bits 23-16 | Bits 15-8 | Bits 7-0     |
                    |------------|------------|-----------|--------------|
                    | RRRRRRRR   | GGGGGGGG   | BBBBBBBB  | AAAAAAAAA    |
                    | Red        | Green      | Blue      | Alpha        |


A�a��daki program, kullan�c�dan 32 bitlik onalt�l�k bir de�er girmesini ister ve ard�ndan R, G, B ve A i�in 8 bitlik renk de�erlerini ��kar�r.

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        // K�rm�z� (Red), Ye�il (Green), Mavi (Blue) ve Alfa (Alpha) bile�enlerini maskelemek i�in kullan�lan bit maskeleri
                        constexpr std::uint32_t redBits{ 0xFF000000 };
                        constexpr std::uint32_t greenBits{ 0x00FF0000 };
                        constexpr std::uint32_t blueBits{ 0x0000FF00 };
                        constexpr std::uint32_t alphaBits{ 0x000000FF };

                        // Kullan�c�dan 32-bit RGBA renk de�erini onalt�l�k (hexadecimal) olarak girmesini isteyen bir ��k��
                        std::cout << "Onalt�l�k (hexadecimal) olarak bir 32-bit RGBA renk de�eri girin (�rn. FF7F3300): ";
                        std::uint32_t pixel{};
                        std::cin >> std::hex >> pixel; // std::hex, onalt�l�k bir de�eri okumam�za izin verir

                        // Bitwise AND kullanarak verilen rengin piksellerini izole etmek,
                        // ard�ndan de�eri alt 8 bit i�ine sa�a kayd�rmak i�in kullan�l�r
                        std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
                        std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
                        std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
                        std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

                        // Kullan�c�n�n rengini i�erdi�i mesaj�
                        std::cout << "Renk i�eriyor:\n";
                        std::cout << std::hex; // A�a��daki de�erleri onalt�l�k olarak yazd�rmak i�in

                        // Hat�rlatma: std::uint8_t muhtemelen bir char olarak yazd�r�l�r
                        // Bu, onu bir tam say� olarak yazd�rmak i�in static_cast kullanmam�z� sa�lar
                        std::cout << static_cast<int>(red)   << " k�rm�z�\n";
                        std::cout << static_cast<int>(green) << " ye�il\n";
                        std::cout << static_cast<int>(blue)  << " mavi\n";
                        std::cout << static_cast<int>(alpha) << " alfa\n";

                        return 0;
                    }
                    ��kt�:
                    Onalt�l� olarak 32 bitlik bir RGBA renk de�eri girin (�r. FF7F3300): FF7F3300
                    Renginiz �unlar� i�erir:
                    ff k�rm�z�
                    7f ye�il
                    33 mavi
                    0 alfa

Yukar�daki programda, ilgilendi�imiz 8 bitlik k�meyi sorgulamak i�in bitsel AND kullan�yoruz ve ard�ndan bunlar� 8
bitlik bir de�ere sa�a kayd�r�yoruz, b�ylece bunlar� onalt�l�k de�erler olarak geri yazd�rabiliriz.

                                                                �ZET
Bit bayraklar�n� ayarlamak, temizlemek, ters �evirmek ve sorgulamak i�in �zetleme:

Bit durumlar�n� sorgulamak i�in, bit i�lemcisini (bitwise AND) kullan�r�z:

                    if (flags & option4) ... // e�er option4 ayarland�ysa bir �eyler yap�n

Bitleri ayarlamak (a�mak) i�in bitwise OR kullan�r�z:

                    flags |= option4; //option4'� a��n.
                    flags |= (option4 | option6); // 4 ve 5 numaral� optionlar� a��n.

Bitleri temizlemek (kapatmak) i�in bitsel AND ile bitsel NOT'u kullan�r�z:

                    flags &= ~option4; //option4'� kapat
                    flags &= ~(option4 | option5); // 4 ve 5 numaral� optionlar� kapat�yoruz

Bit durumlar�n� �evirmek i�in bitsel XOR kullan�r�z:

                    flags ^= option4; // option4'� a��ktan kapal�ya veya tam tersi �ekilde �evirin
                    flags ^= (option4 | option5); // 4 ve 5 numaral� optionlar� �evir

0.4 � �kilik ve ondal�k g�sterim aras�nda tamsay�lar� d�n��t�rme
----------------------------------------------------------------
D���n�n ki ondal�k bir tam say� de�eri var, �rne�in 5623. Sezgisel olarak, bu rakamlar�n (5 * 1000) + (6 * 100) + (2 * 10) + (3 * 1) anlam�na
geldi�ini anlar�z. Her bir soldaki basama��n de�eri 10 kat artt���ndan, 10 ondal�k rakam�m�z oldu�unu d���n�yoruz.

�kili say�lar da ayn� �ekilde �al���r, ancak yaln�zca 2 ikili rakam (0 ve 1) oldu�u i�in, her basama��n de�eri 2 kat artar. B�y�k bir 
ondal�k say�y� okunabilir k�lmak i�in virg�l kullan�ld��� gibi (�rne�in 1.427.435), ikili say�lar� genellikle okunabilir olmalar� i�in 4
bitlik gruplar halinde yazar�z (�rne�in 1101 0101).
A�a��daki tablo, ondal�k ve ikili olarak 15'e kadar sayar:

+--------+--------+
| Decimal| Binary |
+--------+--------+
|   0    |   0000 |
|   1    |   0001 |
|   2    |   0010 |
|   3    |   0011 |
|   4    |   0100 |
|   5    |   0101 |
|   6    |   0110 |
|   7    |   0111 |
|   8    |   1000 |
|   9    |   1001 |
|   10   |   1010 |
|   11   |   1011 |
|   12   |   1100 |
|   13   |   1101 |
|   14   |   1110 |
|   15   |   1111 |
+--------+--------+
*/
/*
Say�lar�n �evirimi vard� ikiliden onlu sisteme onludan ikiliye unsigned signed mevzusu vard� o y�zden yazmad�m temel olarak zaten bir 
�o�una vak�f�z tamam�na da a�ina oldu�umuz i�in laz�m olunca hat�rlamazsak a�ar bakar�z. 

*/