#include <iostream>
int main()
{

    
    return 0;

}
/*
Pass by address
---------------

C++, bir fonksiyona de�er iletimi i�in ���nc� bir yol sa�lar, bu da "adres iletimi" olarak adland�r�l�r. Adres iletimi ile, bir nesneyi arg�man
olarak sa�lamak yerine, �a�r�c� bir nesnenin adresini (bir i�aret�i arac�l���yla) sa�lar. Bu i�aret�i (nesnenin adresini tutan) �a�r�lan
fonksiyonun bir i�aret�i parametresine kopyalan�r (bu parametre �imdi ayn� zamanda nesnenin adresini de tutar). Fonksiyon daha sonra o 
i�aret�iyi dereference ederek ge�ilen adresi �zerinden eri�ebilir ve nesneye ula�abilir.

��te yukar�daki program�n bir adres iletimi varyasyonunu ekleyen bir versiyonu:

                    #include <iostream>
                    #include <string>

                    void printByValue(std::string val) // Fonksiyon parametresi str'nin bir kopyas�d�r
                    {
                        std::cout << val << '\n'; // kopya �zerinden de�eri yazd�r
                    }

                    void printByReference(const std::string& ref) // Fonksiyon parametresi, str'ye ba�lanan bir referanst�r
                    {
                        std::cout << ref << '\n'; // referans �zerinden de�eri yazd�r
                    }

                    void printByAddress(const std::string* ptr) // Fonksiyon parametresi, str'nin adresini tutan bir i�aret�idir
                    {
                        std::cout << *ptr << '\n'; // dereferans edilmi� i�aret�i �zerinden de�eri yazd�r
                    }

                    int main()
                    {
                        std::string str{ "Hello, world!" };

                        printByValue(str); // str'yi de�erle ileterek, str'nin bir kopyas�n� olu�turur
                        printByReference(str); // str'yi referansla ileterek, str'nin bir kopyas�n� olu�turmaz
                        printByAddress(&str); // str'yi adresle ileterek, str'nin bir kopyas�n� olu�turmaz

                        return 0;
                    }
Bu versiyonlar�n ���n�n de ne kadar benzer oldu�una dikkat edin. Adrese g�re ge�i� s�r�m�n� daha ayr�nt�l� olarak inceleyelim.

�lk olarak, printByAddress() fonksiyonumuzun adrese g�re ge�i� kullanmas�n� istedi�imiz i�in fonksiyon parametremizi ptr ad�nda bir i�aret�i 
yapt�k. printByAddress() y�ntemi ptr'yi salt okunur bir �ekilde kullanaca��ndan, ptr bir const de�erinin i�aret�isidir.

                    void printByAddress(const std::string* ptr)
                    {
                         std::cout << *ptr << '\n'; // de�eri referans� al�nm�� i�aret�i arac�l���yla yazd�r�yoruz
                    }
printByAddress() fonksiyonu i�inde, i�aret edilen nesnenin de�erine eri�mek i�in ptr parametresinin referans�n� kald�r�r�z.

�kincisi, fonksiyon �a�r�ld���nda sadece str nesnesini ge�emeyiz, str adresini de aktarmam�z gerekir. Bunu yapman�n en kolay yolu,
str adresini tutan bir i�aret�i elde etmek i�in adres operat�r�n� (&) kullanmakt�r:

                    printByAddress(&str); // str'nin i�aret�iyi tutan adresini almak i�in (&) operat�r�n�n adresini kullan�n

Bu �a�r� y�r�t�ld���nde &str, str adresini tutan bir i�aret�i yaratacakt�r. Bu adres daha sonra fonksiyon �a�r�s�n�n bir par�as� olarak ptr
fonksiyon parametresine kopyalan�r. Ptr art�k str'nin adresini tuttu�u i�in, fonksiyon ptr'yi dereference yapt���nda yani �a��rd���nda,
fonksiyonun konsola yazd�rd��� str de�erini alacakt�r.

Bu kadar.

Yukar�daki �rnekte str adresini almak i�in adres operat�r�n� kullanmam�za ra�men, e�er str adresini tutan bir i�aret�i de�i�kenimiz zaten varsa,
bunun yerine bunu kullanabiliriz:

                    int main()
                    {
                        std::string str{ "Hello, world!" };

                        printByValue(str);     // str'yi de�erle ileterek, str'nin bir kopyas�n� olu�turur
                        printByReference(str); // str'yi referansla ileterek, str'nin bir kopyas�n� olu�turmaz
                        printByAddress(&str); // str'yi adresle ileterek, str'nin bir kopyas�n� olu�turmaz

                        std::string* ptr { &str }; // str'nin adresini tutan bir i�aret�i de�i�keni tan�mla
                        printByAddress(ptr); // pass str by address, does not make a copy of str

                        return 0;
                    }

Adres iletimi, i�aret edilen nesnenin bir kopyas�n� olu�turmaz
--------------------------------------------------------------
A�a��daki ifadeleri g�z �n�nde bulundurun:

                    std::string str{ "Merhaba d�nya!" };
                    printByAddress(&str); // str'nin i�aret�iyi tutan adresini almak i�in (&) operat�r�n�n adresini kullan�n


12.5 -- Lvalue reference b�l�m�nde belirtildi�i gibi, bir std::string'in kopyalanmas� pahal� bir i�lemdir, bu nedenle bunu ka��nmak istiyoruz.
Bir std::string'i adrese dayal� iletti�imizde, asl�nda std::string nesnesini kopyalam�yoruz - sadece �a�r�c�dan �a�r�lan fonksiyona bir 
i�aret�i (nesnenin adresini tutan) kopyal�yoruz. Bir adres genellikle yaln�zca 4 veya 8 bayt oldu�undan, bir i�aret�i de yaln�zca 4 veya
8 bayt oldu�undan, bir i�aret�iyi kopyalamak her zaman h�zl�d�r.

Bu nedenle, referansla iletim gibi, adresle iletim de h�zl�d�r ve arg�man nesnesinin bir kopyas�n� olu�turmaktan ka��n�r.

Adres iletimi, fonksiyona arg�man�n de�erini de�i�tirme izni verir
------------------------------------------------------------------
Bir nesneyi adrese dayal� iletti�imizde, fonksiyon iletilen nesnenin adresini al�r ve bu adresi dereferans arac�l���yla eri�ebilir. 
��nk� bu, iletilen nesnenin as�l arg�man nesnesinin adresidir (nesnenin bir kopyas� de�il), e�er fonksiyon parametresi bir i�aret�iye
ve const olmayan bir i�aret�iye ise, fonksiyon arg�man� i�aret�i parametresi �zerinden de�i�tirebilir:

                    #include <iostream>

                    void changeValue(int* ptr) // Not: Bu �rnekte ptr, const olmayan bir i�aret�idir.
                    {
                        *ptr = 6; // De�eri 6'ya de�i�tir
                    }

                    int main()
                    {
                        int x{ 5 };

                        std::cout << "x = " << x << '\n';

                        changeValue(&x); // x'in adresini fonksiyona iletiyoruz

                        std::cout << "x = " << x << '\n';

                        return 0;
                    }
                    ��kt�:
                    x = 5
                    x = 6

G�rd���n�z gibi, arg�man de�i�tirildi ve bu de�i�iklik, changeValue() fonksiyonu �al��may� tamamlad�ktan sonra bile devam eder.
E�er bir fonksiyonun iletilen nesneyi de�i�tirmesi gerekmeyen durumlar varsa, fonksiyon parametresi bir const i�aret�i yap�labilir:

                    void changeValue(const int* ptr) // Not: ptr art�k bir const i�aret�isidir.
                    {
                        *ptr = 6; // hata: const de�eri de�i�tirilemez
                    }

Null Kontrol�
-------------
�imdi bu olduk�a masum g�r�nen program� d���n�n:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };
                        print(&x);

                        int* myPtr {};
                        print(myPtr);

                        return 0;
                    }

Bu program �al��t�r�ld���nda, de�er 5'i yazd�racak ve ard�ndan muhtemelen ��kecektir.

print(myPtr) �a�r�s�nda myPtr bir null i�aret�isidir, bu nedenle fonksiyon parametresi ptr da bir null i�aret�isi olacakt�r. Bu null i�aret�isi,
fonksiyonun i�inde dereferans edildi�inde tan�ms�z davran��a neden olur.

Bir parametreyi adrese dayal� iletim yaparken, de�eri dereferans etmeden �nce i�aret�inin null bir i�aret�i olmad���ndan emin olmak �nemlidir.
Bunu yapman�n bir yolu, bir ko�ul ifadesi kullanmakt�r:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        if (ptr) // E�er ptr bir null pointer de�ilse �al��t�r
                        {
                            std::cout << *ptr << '\n';
                        }
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

Yukar�daki programda, ptr'yi dereferans etmeden �nce onun null olmad���ndan emin olmak i�in bir test yap�yoruz. Bu basit bir fonksiyon i�in
uygun olsa da, daha karma��k fonksiyonlarda bu, gereksiz mant�k (ptr'nin birden �ok kez null olup olmad���n� test etme) veya temel mant���n
i� i�e ge�mesine (bir blok i�inde ise) neden olabilir.

�o�u durumda, etkili olan� yapmak, fonksiyon parametresinin null olup olmad���n� �nko�ul olarak kontrol etmek (9.6 -- Assert ve static_assert)
ve negatif durumu hemen ele almak olacakt�r:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        if (!ptr) // E�er ptr bir null i�aret�isi ise, �a�r�c�ya erken d�n
                            return;

                        // Bu noktaya ula�t�ysak, ptr'nin ge�erli oldu�unu varsayabiliriz
                        // bu nedenle ba�ka test veya i� i�e ge�me gerekmez

                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

E�er bir null i�aret�isi fonksiyona asla iletilmemesi gerekiyorsa, bunun yerine (veya ayr�ca) bir assert kullan�labilir
(ki bunu 9.6 -- Assert ve static_assert dersinde inceledik) (��nk� assert'ler, asla ger�ekle�memesi gereken durumlar� belgelemek i�in 
tasarlanm��t�r):

                    #include <iostream>
                    #include <cassert>

                    void print(const int* ptr) // art�k bir const int i�aret�isi
                    {
                        assert(ptr); // bir null i�aret�isi iletilirse program� hata vererek sonland�r (��nk� bu asla ger�ekle�memelidir)

                        // (iste�e ba�l�) bunu �retim modunda bir hata durumu olarak ele al, b�ylece ger�ekle�irse ��kme olmaz
                        if (!ptr)
                            return;

                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

pass by const reference tercih edin
-----------------------------------
Yukar�daki �rnekteki print() fonksiyonunun null de�erleri �ok iyi ele almad���n� unutmay�n - etkili bir �ekilde fonksiyonu iptal eder.
Bu durumda, neden kullan�c�ya hi� null bir de�eri iletmeye izin verelim? Adrese dayal� iletimin ayn� avantajlara sahip olmas�na ra�men,
yanl��l�kla bir null i�aret�isini dereference etme riski olmaks�z�n ge�i�i sa�lar.

const referans iletimi, adres iletimine g�re birka� avantaja sahiptir.

�lk olarak, bir adrese dayal� iletilen bir nesnenin bir adresi olmal�d�r, bu nedenle yaln�zca lvalue'lar bir adrese dayal� iletilmi� olabilir
(��nk� rvalue'lar adreslere sahip de�ildir). const referans iletimi daha esnek olup, lvalue'lar� ve rvalue'lar� kabul edebilir:

                    #include <iostream>

                    void printByValue(int val) // Fonksiyon parametresi arg�man�n bir kopyas�d�r
                    {
                        std::cout << val << '\n'; // kopya �zerinden de�eri yazd�r
                    }

                    void printByReference(const int& ref) // Fonksiyon parametresi, arg�mana ba�lanan bir referanst�r
                    {
                        std::cout << ref << '\n'; // referans �zerinden de�eri yazd�r
                    }

                    void printByAddress(const int* ptr) // Fonksiyon parametresi, arg�man�n adresini tutan bir i�aret�idir
                    {
                        std::cout << *ptr << '\n'; // dereferans edilmi� i�aret�i �zerinden de�eri yazd�r
                    }

                    int main()
                    {
                        printByValue(5);     // ge�erli (ancak bir kopya olu�turur)
                        printByReference(5); // ge�erli (��nk� parametre bir const referanst�r)
                        printByAddress(&5);  // hata: r-value'�n adresi al�namaz

                        return 0;
                    }

�kinci olarak, referansla iletimin s�zdizimi do�ald�r, ��nk� sadece literalleri veya nesneleri iletebiliriz. Adrese dayal� iletimle,
kodumuz s�rekli olarak ampersand'lar (&) ve asterisk'ler (*) ile dolup ta�ar.

Modern C++'ta, adresle iletilen bir�ok �ey, genellikle ba�ka y�ntemlerle daha iyi ger�ekle�tirilebilir. Bu yayg�n kural� takip edin:
"Referansla iletebildi�inizde referansla iletimi tercih edin, adresle iletebildi�inizde adresle iletimi tercih edin."

**** BEST -> Bir nedeniniz olmad�k�a referansla iletimi tercih edin ve adresle iletimi yaln�zca belirli bir nedeniniz oldu�unda kullan�n.


"Optional" arg�manlar i�in adres �zerinden ge�me

Adres �zerinden ge�me, i�levin "iste�e ba�l�" bir arg�man� kabul etmesine izin vermek i�in daha yayg�n kullan�lan y�ntemlerden biridir. 
Bu, a��klamaktan �ok �rnek ile daha kolay anlat�labilir:

                    #include <iostream>
                    #include <string>

                    void greet(std::string* name=nullptr)
                    {
                        std::cout << "Hello ";
                        std::cout << (name ? *name : "guest") << '\n';
                    }

                    int main()
                    {
                        greet(); // user in kim oldu�unu bilmiyoruz

                        std::string joe{ "Joe" };
                        greet(&joe); // User in Joe oldu�unu biliyoruz

                        return 0;
                    }
                    ��kt�:
                    Hello guest
                    Hello Joe

Bu programda, greet() fonksiyonu, adres �zerinden ge�ilen ve varsay�lan olarak nullptr olan bir parametreye sahiptir. main() i�inde bu
fonksiyonu iki kez �a��r�yoruz. �lk �a�r�da kullan�c� kim oldu�unu bilmiyoruz, bu nedenle greet() fonksiyonunu arg�man olmadan �a��r�yoruz.
name parametresi varsay�lan olarak nullptr'a atan�r ve greet fonksiyonu ad� "guest" ile de�i�tirir. �kinci �a�r� i�in art�k ge�erli bir 
kullan�c�m�z var, bu nedenle greet(&joe) �eklinde �a��r�yoruz. name parametresi joe'nun adresini al�r ve bunu kullanarak ad� "Joe" olarak 
yazd�rmak i�in kullanabilir.

Ancak, bir�ok durumda, ayn� sonuca ula�mak i�in fonksyion a��r� y�klemenin (function overloading) daha iyi bir alternatif oldu�u unutulmamal�d�r:

                    #include <iostream>
                    #include <string>
                    #include <string_view>

                    void greet(std::string_view name)
                    {
                        std::cout << "Hello " << name << '\n';
                    }

                    void greet()
                    {
                        greet("guest");
                    }

                    int main()
                    {
                        greet(); // we don't know who the user is yet

                        std::string joe{ "Joe" };
                        greet(joe); // we know the user is joe

                        return 0;
                    }

Bunun bir tak�m avantajlar� var: Art�k bo� referanslar konusunda endi�elenmemize gerek yok ve e�er istersek bir dizge de�i�mezini iletebiliriz.
Bir i�aret�i parametresinin neyi i�aret etti�ini de�i�tirme
-----------------------------------------------------------
Bir i�leve bir adres ge�ti�imizde, bu adres, arg�mandan i�levin i�indeki i�aret�i parametresine kopyalan�r (bu, bir adresi kopyalaman�n h�zl�
olmas� nedeniyle sorun de�ildir). �imdi a�a��daki program� d���n�n:

                    #include <iostream>

                    // [[maybe_unused]] ptr2'nin ayarlanmas�na ra�men kullan�lmamas�na ili�kin derleyici uyar�lar�ndan kurtulur
                    void nullify([[maybe_unused]] int* ptr2)
                    {
                        ptr2 = nullptr; // Fonksiyon parametresini bo� g�sterici yap
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x }; // ptr x'i g�steriyor

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

                        nullify(ptr);

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
                        return 0;
                    }
                    ��kt�:
                    ptr is non-null
                    ptr is non-null

G�rd���n�z gibi, i�aret�i parametrenin tuttu�u adresi de�i�tirmenin, arg�man�n tuttu�u adres �zerinde herhangi bir etkisi olmad� 
(ptr hala x'e i�aret ediyor). nullify() fonksiyonu �a�r�ld���nda, ptr2, i�ine ge�irilen adresin bir kopyas�n� al�r (bu durumda, ptr taraf�ndan
tutulan adres, yani x'in adresi). Fonksiyon ptr2'nin neye i�aret etti�ini de�i�tirdi�inde, bu sadece ptr2 taraf�ndan tutulan kopyay� etkiler.

Peki, bir fonksiyona bir i�aret�i arg�man�n neye i�aret etti�ini de�i�tirmesine izin vermek istersek ne yapmal�y�z?

Pass by address� by reference?
------------------------------

Evet, bu m�mk�n. S�radan bir de�i�keni referans ile ge�ebildi�imiz gibi, i�aret�ileri de referans ile ge�ebiliriz. ��te yukar�daki program�n
ptr2'nin bir adres referans� olacak �ekilde de�i�tirilmi� hali:

                    #include <iostream>

                    void nullify(int*& refptr) // refptr �imdi bir pointer referans� oldu yani pointer e referans
                    {
                        refptr = nullptr; // Fonksiyon parametresini bir null i�aret�i yap
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x }; // ptr, x'e i�aret ediyor

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

                        nullify(ptr);

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
                        return 0;
                    }
                    ��kt�:
                    ptr is non-null
                    ptr is null

Refptr art�k bir i�aret�iye referans oldu�undan, ptr arg�man olarak iletildi�inde refptr, ptr'ye ba�lan�r. Bu, refptr'de yap�lan herhangi bir
de�i�ikli�in ptr'ye de yap�laca�� anlam�na gelir.

Ek bilgi olarak, i�aret�ilere referanslar genellikle nadir kullan�ld���ndan, s�zdizimini kar��t�rmak kolay olabilir (int*& m� yoksa int&* mi?).
�yi haber �u ki, tersini yapt���n�zda derleyici hata verecektir, ��nk� bir referansa i�aret�i olu�turamazs�n�z (��nk� i�aret�iler bir nesnenin
adresini tutmal�d�r ve referanslar nesneler de�ildir). Ard�ndan, d�zeltebilmeniz i�in s�zdizimini de�i�tirebilirsiniz.

Sadece de�erle ge�irme var

Referans, adres ve de�erle ge�irme aras�ndaki temel farklar� anlad���n�z� varsayal�m, �imdi biraz basitle�tirelim. :)

Derleyici genellikle referanslar� tamamen optimize edebilir, ancak bu m�mk�n olmayan durumlar vard�r ve bir referans asl�nda gereklidir.
Referanslar genellikle derleyici taraf�ndan i�aret�iler kullan�larak uygulan�r. Bu, arka planda referans�n bir adresle ge�ildi�i (referansa
eri�im yap�l�rken ima edilen bir dolayl� adresleme) anlam�na gelir.

Ve �nceki dersimizde, adresle ge�i�in sadece bir adresi �a��ran i�levden �a�r�lan i�leme kopyalad���n� s�ylemi�tik - ki bu sadece bir de�eri
ge�irmek demektir.
Bu nedenle, C++'�n asl�nda her �eyi de�erle ge�irdi�ini s�yleyebiliriz! Adresle (ve referansla) ge�i�in �zellikleri, ge�ilen adresi de�i�tirmek
i�in ge�ilen adrese dolayl� bir eri�im yapabilmemizden kaynaklan�r, ki bunu normal bir de�er parametresiyle yapamay�z!

Neden 0 veya NULL kullan�m�n�n art�k tercih edilmedi�ini a��klayal�m (iste�e ba�l�)
-----------------------------------------------------------------------------------
Bu alt b�l�mde, 0 veya NULL kullan�m�n�n neden art�k tercih edilmedi�ini a��klayaca��z.

Say�sal 0 hem bir tam say� literali olarak hem de bir null i�aret�i literali olarak yorumlanabilir. Baz� durumlarda, hangisini ama�lad���m�z
belirsiz olabilir - ve bu durumlardan baz�lar�nda derleyici, birini kastetti�imizi d���nerek di�erini d���nebilir - bu da program�m�z�n
davran���nda istenmeyen sonu�lara neden olabilir.

�ni�lemci makrosu NULL'�n tan�m� dil standard� taraf�ndan belirlenmemi�tir. 0, 0L, ((void*)0) veya ba�ka bir �ey olarak tan�mlanabilir.

11.1 Dersinde - Fonksiyon a��r� y�kleme konusuna giri�, fonksiyonlar�n a��r� y�klenebilece�ini tart��t�k (�ok say�da fonksiyon ayn� ismi
ta��yabilir, yeter ki parametrelerin say�s� veya t�r� ile ay�rt edilebilsin). Derleyici, fonksiyon �a�r�s�n�n bir par�as� olarak iletilen
arg�manlarla hangi a��r� y�klenmi� fonksiyonu istedi�inizi ��zebilir.

0 veya NULL kullan�rken bu sorunlara neden olabilir:

                    #include <iostream>
                    #include <cstddef> // NULL i�in

                    void print(int x) // bu fonksiyon bir tamsay�y� kabul eder
                    {
                        std::cout << "print(int): " << x << '\n';
                    }

                    void print(int* ptr) // bu fonksiyon bir tamsay� i�aret�isini kabul eder
                    {
                        std::cout << "print(int*): " << (ptr ? "null de�il\n" : "null\n");
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x };

                        print(ptr);  // her zaman print(int*)'i �a��r�r, ��nk� ptr tipi int* (iyi)
                        print(0);    // her zaman print(int)'i �a��r�r, ��nk� 0 bir tamsay� literali (umar�m bu bekledi�imiz �eydir)

                        print(NULL); // bu ifade a�a��dakilerden herhangi birini yapabilir:
                        // print(int)'i �a��r (Visual Studio bunu yapar)
                        // print(int*)'i �a��r
                        // belirsiz bir i�lev �a�r�s� derleme hatas�na neden olabilir (gcc ve Clang bunu yapar)

                        print(nullptr); // her zaman print(int*)'i �a��r�r

                        return 0;
                    }
                    Yazar�n makinesinde (Visual Studio kullanarak), bu �u �ekilde yazd�r�r:

                    print(int*): non-null
                    print(int): 0
                    print(int): 0
                    print(int*): null

0 olarak ge�irilen bir tam say� de�eri parametre olarak kullan�ld���nda, derleyici print(int*) yerine print(int) 'i tercih eder. Bu durum, 
print(int*) 'in bir null i�aret�i arg�man� ile �a�r�lmas�n� ama�lam��ken beklenmeyen sonu�lara yol a�abilir.

E�er NULL de�eri 0 olarak tan�mlanm��sa, print(NULL) ifadesi de bekledi�iniz gibi print(int*) 'i de�il, print(int) 'i �a��racakt�r. E�er NULL 0
olarak tan�mlanmam��sa, ba�ka davran��lar ortaya ��kabilir, �rne�in print(int*) 'i �a��rma veya derleme hatas� alabilirsiniz.

nullptr kullanmak bu belirsizli�i ortadan kald�r�r (her zaman print(int*) 'i �a��racakt�r), ��nk� nullptr sadece bir i�aret�i t�r� ile 
e�le�ecektir.


std::nullptr_t (iste�e ba�l�)

��nk� nullptr, i�lev a��r� y�klemelerinde tam say� de�erlerinden ay�rt edilebilece�inden, farkl� bir tipe sahip olmal�d�r. Peki nullptr'�n tipi
nedir? Cevap �udur: nullptr'�n tipi std::nullptr_t'dir (header <cstddef>'de tan�mlanm��t�r). std::nullptr_t yaln�zca bir de�eri tutabilir:
nullptr! Bu biraz sa�ma g�r�nebilir, ancak bir durumda kullan��l�d�r. E�er sadece bir nullptr literal arg�man�n� kabul eden bir fonksiyon 
yazmak istiyorsak, parametreyi std::nullptr_t yapabiliriz.

                    #include <iostream>
                    #include <cstddef> // std::nullptr_t i�in

                    void print(std::nullptr_t)
                    {
                        std::cout << "in print(std::nullptr_t)\n";
                    }

                    void print(int*)
                    {
                        std::cout << "in print(int*)\n";
                    }

                    int main()
                    {
                        print(nullptr); // print(std::nullptr_t) � �a��r�r

                        int x { 5 };
                        int* ptr { &x };

                        print(ptr); // print(int*) � �a��r�r

                        ptr = nullptr;
                        print(ptr); // print(int*) � �a��r�r (��nk� ptr int* t�r�ne sahip)

                        return 0;
                    }

Yukar�daki �rnekte, print(nullptr) fonksiyon �a�r�s�, d�n���m gerektirmedi�i i�in print(std::nullptr_t)'ye kar�� print(int*) fonksiyonunu ��zer.

Biraz kar��t�r�c� olabilecek tek durum, ptr de�eri nullptr olan bir durumda print(ptr) �a��rd���m�zda ortaya ��kabilir. Unutmay�n ki fonksiyon
a��r� y�klemeleri tiplere g�re e�le�ir, de�erlere de�il, ve ptr'nin tipi int* oldu�u i�in print(int*) e�le�ecektir. Bu durumda 
print(std::nullptr_t) bile dikkate al�nmaz, ��nk� i�aret�i tipleri otomatik olarak std::nullptr_t'ye d�n��mez.

Muhtemelen bunu hi� kullanman�z gerekmez, ancak her ihtimale kar�� bilmenizde fayda var.

Return by reference ve return by address
----------------------------------------
Fonksiyonlara de�er ile ge�me konusunda s�n�f tiplerinin maliyetli oldu�undan bahsettik. Ayn� durumu return ile de kar��la��yoruz:
fonksiyonun geri d�n�� de�erinin bir kopyas� �a��ran tarafa geri g�nderilir. E�er fonksiyonun geri d�n�� tipi bir s�n�f tipiyse,
bu maliyetli olabilir.

                    std::string returnByValue(); // Bir std::string'in kopyas�n� d�nd�r�r (maliyetli)

Referans ile d�n��

�a��rana bir s�n�f tipi d�nd�rd���m�z durumlarda, d�n�� yapmay� (yapmamay�) d���nebiliriz. Referans ile d�n��, d�nd�r�len nesneye ba�l� bir 
referans d�nd�r�r ve bu, d�n�� de�erinin bir kopyas�n� yapmaktan ka��n�r. Referans ile d�nmek i�in, fonksiyonun d�n�� de�erini referans t�r�
olarak tan�mlamak yeterlidir:

                    std::string& returnByReference();                 // Mevcut bir std::string'e referans d�nd�r�r (ucuz)
                    const std::string& returnByReferenceToConst();    // Mevcut bir std::string'e const referans d�nd�r�r (ucuz)

Referans yoluyla geri d�n�� mekani�ini g�steren akademik bir program:

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName() // bir const referans� d�nd�r�r
                    {
                        static const std::string s_programName { "Calculator" }; // statik s�reye sahiptir, program�n sonunda yok edilir

                        return s_programName;
                    }

                    int main()
                    {
                        std::cout << "This program is named " << getProgramName();

                        return 0;
                    }

                    Bu program �unlar� yazd�r�r:
                    This program is named Calculator

getProgramName() bir const referans� d�nd�rd��� i�in, return s_programName sat�r� �al��t�r�ld���nda getProgramName() s_programName'e bir const
referans� d�nd�recektir (b�ylece bir kopya yapmaktan ka��n�lm�� olur). Bu const referans� daha sonra �a��ran taraf�ndan yazd�r�lan
s_programName de�erine eri�mek i�in kullan�labilir.

Referans ile d�nd�r�len nesne, fonksiyon geri d�nd�kten sonra var olmal�d�r
---------------------------------------------------------------------------

Referans ile d�nme kullanman�n �nemli bir sak�ncas� vard�r: programc�, referans�n d�nd�r�len fonksiyondan sonra referans yap�lan nesnenin
ya�ad���ndan emin olmal�d�r. Aksi takdirde, d�nd�r�len referans u�uk (yok edilmi� bir nesneyi i�aret eden) olarak kalacak ve bu referans�n
kullan�m� tan�ms�z davran��a yol a�acakt�r.

Yukar�daki programda, s_programName'in statik s�resi oldu�undan, s_programName program�n sonuna kadar var olacakt�r. Main() d�nd�r�len
referansa eri�ti�inde, asl�nda s_programName'e eri�iyor, ki bu sorun de�ildir, ��nk� s_programName daha sonra yok edilene kadar var
olmayacakt�r.

�imdi yukar�daki program� de�i�tirerek, fonksiyonumuzun u�uk bir referans d�nd�rd��� durumu g�sterelim:

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName()
                    {
                        const std::string programName { "Calculator" }; // �imdi statik olmayan bir de�i�ken var, Bu y�zden fonksiyon sonunda 
                                                                           bu de�i�ken yok edilecek

                        return programName;
                    }

                    int main()
                    {
                        std::cout << "This program is named " << getProgramName(); // tan�ms�z davran��

                        return 0;
                    }

Bu program�n sonucu tan�ms�zd�r. getProgramName() �a�r�ld���nda, yerel bir de�i�kene ba�l� bir referans d�nd�r�l�r. Ard�ndan,program�n sonunda
programName yok edilir ��nk� programName otomatik s�reli bir yerel de�i�kendir . Bu, d�nd�r�len referans�n �u anda u�uk oldu�u anlam�na gelir
ve main() fonksiyonundaki programName'in kullan�m� tan�ms�z davran��a yol a�ar.

Modern derleyiciler, genellikle bir referans ile yerel bir de�i�keni d�nd�rmeye �al��t���n�zda bir uyar� veya hata �retir (bu nedenle
yukar�daki program bile derlenmeyebilir), ancak derleyiciler bazen daha karma��k durumlar� alg�lamakta zorlanabilir.

Uyar� olarak k�saca ��yle diyebiliriz ; 

Referans ile d�nd�r�len nesneler, referans� d�nd�ren fonksiyonun kapsam�n�n �tesinde ya�amal�d�r, aksi takdirde bir u�uk referans elde edilir.
Asla (static olmayan) bir yerel de�i�keni veya ge�ici de�i�keni referans ile d�nd�rmeyin.

�m�r uzatma i�lemi fonksiyon s�n�rlar� a�an durumlarda �al��maz
---------------------------------------------------------------
Hadi bir �rne�e bakal�m, burada bir ge�ici de�eri referans olarak d�nd�r�yoruz:

                    #include <iostream>

                    const int& returnByConstReference()
                    {
                        return 5; //Ge�ici bir nesneye const int referans� d�ner
                    }

                    int main()
                    {
                        const int& ref { returnByConstReference() };

                        std::cout << ref; // tan�ms�z davran��

                        return 0;
                    }

Yukar�daki programda, returnByConstReference() fonksiyonu bir tamsay� literali d�nd�r�yor, ancak fonksiyonun d�n�� tipi const int& olarak 
belirlenmi�. Bu durum, de�eri 5 olan bir ge�ici nesneye ba�l� bir ge�ici referans�n olu�turulmas�na yol a�ar. Bu ge�ici referans daha sonra
d�nd�r�l�r. Ge�ici nesne daha sonra kapsam d���na ��kar ve referans� sallant�da b�rak�r.

D�n�� de�eri (main() fonksiyonundaki di�er bir const referansa ba�land���nda) ba�ka bir const referansa ba�land���nda, ge�ici nesnenin
�mr�n� uzatmak i�in �ok ge�tir - ��nk� zaten yok edilmi�tir. Bu nedenle, ref isimli referans bir sallant� referans�na ba�l� olacakt�r ve ref
de�erinin kullan�lmas� tan�ms�z davran��a neden olacakt�r.

��te benzer �ekilde �al��mayan daha az a��k bir �rnek:

                    #include <iostream>

                    const int& returnByConstReference(const int& ref)
                    {
                        return ref;
                    }

                    int main()
                    {
                        // Durum 1: Direkt ba�lanma
                        const int& ref1 { 5 }; // �m�r uzat�m�
                        std::cout << ref1 << '\n'; // Tamam uygun

                        // Durum 2: Dolayl� ba�lanma
                        const int& ref2 { returnByConstReference(5) }; // sallant�daki referansa ba�lanma
                        std::cout << ref2 << '\n'; // tan�ms�z davran��

                        return 0;
                    }

Durum 2'de, de�eri 5 olan bir ge�ici nesne olu�turulur ve fonksiyon parametresi olan ref bu nesneye ba�lan�r. Fonksiyon sadece bu referans� 
�a�r�c�ya geri d�nd�r�r, ard�ndan �a�r�c� bu referans� ref2'yi ba�latmak i�in kullan�r. Bu, do�rudan ge�ici nesneye ba�lanm�� bir durum
olmad���ndan (referans fonksiyon arac�l���yla ge�irildi�i i�in), �m�r uzatma i�lemi uygulanmaz. Bu durumda, ref2 sallant�da kal�r ve sonraki 
kullan�m� tan�ms�z davran��a neden olur.

Uyar� -> Referans �m�r uzatmas� fonksiyon s�n�rlar� a�an durumlarda �al��maz.

Const olmayan statik yerel de�i�kenleri referans olarak d�nd�rmeyin
-------------------------------------------------------------------
De�i�tirilemeyen (const) statik yerel de�i�kenleri referans olarak d�nd�rmek, referans ile d�n�� mekanizmas�n� basit bir �ekilde g�stermek
amac�yla yap�lan �rneklerde kullan��l�d�r. Ancak, genel olarak de�i�tirilemeyen (const) olmayan statik yerel de�i�kenleri referans olarak 
d�nd�rmek pek yayg�n olmayan bir y�ntemdir ve genellikle ka��n�lmal�d�r. ��te b�yle bir durumda ortaya ��kabilecek bir problemi g�steren 
basitle�tirilmi� bir �rnek:

                    #include <iostream>
                    #include <string>

                    const int& getNextId()
                    {
                        static int s_x{ 0 }; // not: de�i�ken de�i�tirilemeyen (const) de�ildir
                        ++s_x; // bir sonraki kimli�i olu�tur
                        return s_x; // ve ona bir referans d�nd�r
                    }

                    int main()
                    {
                        const int& id1 { getNextId() }; // id1 bir referanst�r
                        const int& id2 { getNextId() }; // id2 bir referanst�r

                        std::cout << id1 << id2 << '\n';

                        return 0;
                    }
                    ��kt�:
                    22

Bu durum, id1 ve id2'nin ayn� nesneye (static de�i�ken s_x) referans olmas�ndan kaynaklanmaktad�r, bu nedenle herhangi bir �ey
(�rne�in getNextId()) de�eri de�i�tirdi�inde t�m referanslar de�i�tirilmi� de�eri kullanmaktad�r.

Bir di�er yayg�n sorun ise, non-const static yerel de�i�kenleri referans olarak d�nd�ren programlarda s_x'i varsay�lan durumuna s�f�rlamak i�in
standartla�t�r�lm�� bir yolun olmamas�d�r. Bu t�r programlar, genellikle non-idiomatik bir ��z�m (�rne�in bir s�f�rlama fonksiyon parametresi)
kullanmak zorunda kal�r veya program� sonland�r�p yeniden ba�latarak s�f�rlayabilir.

Yukar�daki �rnek biraz sa�ma olsa da, programc�lar bazen optimizasyon ama�lar�yla denedikleri yukar�daki benzer varyasyonlar nedeniyle 
beklenmedik sonu�lar alabilirler.

*** BEST -> Non-const yerel static de�i�kenlere referans d�nd�rmekten ka��n�n.

E�er d�nd�r�len referans ile bir const yerel static de�i�kenine referans olu�turmak gerekiyorsa, bu nadiren yap�l�r. Bu durum, d�nd�r�len yerel
de�i�kenin her fonksiyon �a�r�s�nda olu�turulmas� maliyetli oldu�unda kullan�labilir ancak bu durum nadirdir.
Bir const yerel static de�i�kenine referans d�nd�rmek, bazen bir global de�i�kenin eri�imini kaps�le etmek i�in kullan�l�r. Bu kullan�m,
istenildi�i takdirde dikkatlice ve ama�l� bir �ekilde yap�labilir.

Bir normal de�i�keni bir geri d�nen referans ile atamak/initialize etmek bir kopya olu�turur
--------------------------------------------------------------------------------------------

E�er bir fonksiyon bir referans d�nd�r�yorsa ve bu referans bir referans olmayan bir de�i�keni initialize etmek veya atamak i�in kullan�l�yorsa,
d�n�� de�eri kopyalan�r (sanki de�er olarak d�nd�r�lm�� gibi).

                    #include <iostream>
                    #include <string>

                    const int& sonrakiIdyiAl()
                    {
                        static int s_x{ 0 };
                        ++s_x;
                        return s_x;
                    }

                    int main()
                    {
                        // id1 �u anda normal bir de�i�ken ve sonrakiIdyiAl fonksiyonunun referans ile d�nd�rd��� de�erin bir kopyas�n� al�r
                        const int id1 { sonrakiIdyiAl() };
                        // id2 �u anda normal bir de�i�ken ve sonrakiIdyiAl fonksiyonunun referans ile d�nd�rd��� de�erin bir kopyas�n� al�r
                        const int id2 { sonrakiIdyiAl() }; 

                        std::cout << id1 << id2 << '\n';

                        return 0;
                    }

Yukar�daki �rnekte, getNextId() bir referans d�nd�r�yor ancak id1 ve id2 referans olmayan de�i�kenler. Bu durumda, d�nd�r�len referans�n
de�eri normal de�i�kenlere kopyalan�r. Bu nedenle, bu program �u �ekilde yazd�r�r:
                    12
Tabii ki, bu ayn� zamanda bir de�eri referans ile d�nd�rmenin amac�n� da bo�a ��kar�r.

Ayr�ca, e�er bir program bir ge�ersiz referans d�nd�r�yorsa, kopya yapmadan �nce referans�n ge�ersiz kalaca��n� unutmay�n. Bu durum,
tan�ms�z davran��a yol a�acakt�r.

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName() // bir const referans d�nd�recek
                    {
                        const std::string programName{ "Calculator" };

                        return programName;
                    }

                    int main()
                    {
                        std::string name { getProgramName() }; // bir as�l� referans�n kopyas�n� olu�turur
                        std::cout << "This program is named " << name << '\n'; // tan�ms�z davran��

                        return 0;
                    }

Referans parametrelerini referans olarak d�nd�rmek sorun de�ildir
-----------------------------------------------------------------
Referans ile ge�ilen nesnelerin referans olarak d�nd�r�lmesi mant�kl� olan birka� durum vard�r ve bunlarla ilgili bir�ok durumla ilerleyen 
derslerde kar��la�aca��z. Ancak �u anda g�sterebilece�imiz kullan��l� bir �rnek var.

E�er bir parametre referans ile bir fonksiyona iletilmi�se, o parametreyi referans olarak d�nd�rmek g�venlidir. Bu mant�kl�d�r: Bir arg�man�
bir fonksiyona iletmek i�in, arg�man �a��r�c�n�n kapsam�nda var olmal�d�r. �a�r�lan fonksiyon geri d�nd���nde, bu nesne hala �a�r�c�n�n 
kapsam�nda var olmal�d�r.

��te b�yle bir fonksiyonun basit bir �rne�i:

                    #include <iostream>
                    #include <string>

                    // �ki std::string nesnesini al�r, alfabetik s�rayla hangisinin �nce geldi�ini d�nd�r�r
                    const std::string& firstAlphabetical(const std::string& a, const std::string& b)
                    {
                        // std::string �zerinde operator<'� kullanabiliriz, hangisinin alfabetik olarak �nce geldi�ini belirlemek i�in
                        return (a < b) ? a : b;
                    }

                    int main()
                    {
                        std::string hello { "Hello" };
                        std::string world { "World" };

                        std::cout << firstAlphabetical(hello, world) << '\n';

                        return 0;
                    }
                    ��kt�:
                    Hello


Yukar�daki fonksiyonda, �a�r�c� iki std::string nesnesini const referans olarak iletiyor ve bu nesnelerden hangisi alfabetik olarak �nce
gelirse, o nesne const referans olarak geri d�nd�r�l�yor. E�er de�er ile iletim ve de�er ile d�n�� kullanm�� olsayd�k, std::string i�in
toplamda 3 kopya yapm�� olacakt�k (her bir parametre i�in bir tane, d�n�� de�eri i�in bir tane). Referans ile iletim ve referans ile d�n��
kullanarak, bu kopyalardan ka��nabiliriz.
*/