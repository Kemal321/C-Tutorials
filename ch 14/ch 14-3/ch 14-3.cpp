#include <iostream>
class Deneme {
private: 
    int m_x{};
    int m_y{};
public:
    
    Deneme(int x = 0, int y = 0)  
        :m_x{ x }, m_y{ y }
    {
        std::cout << "baslatici(" << x << ", " << y << ") constructed\n";
    }
    void kontrol() {
            std::cout << "baslatici(" << m_x << "," << m_y << ")\n";
    }
};
int main()
{
    Deneme denem{};
    denem.kontrol();
    return 0;
}
/*
Bir s�n�f tipi bir topluluk oldu�unda, s�n�f tipini do�rudan toplu ba�latma ile ba�latabiliriz:

                struct Foo // Foo bir topluluktur
                {
                    int x {};
                    int y {};
                };

                int main()
                {
                    Foo foo { 6, 7 }; // toplu ba�latmay� kullan�r

                    return 0;
                }

Toplu ba�latma, �yeleri ba�latmay� �ye baz�nda yapar (�yeler tan�mland�klar� s�rayla ba�lat�l�r). Bu y�zden yukar�daki �rnekte foo
�rneklendi�inde, foo.x 6'ya ve foo.y 7'ye ba�lat�l�r. Ancak, herhangi bir �ye de�i�kenini private yapar yapmaz (verilerimizi 
gizlemek i�in), s�n�f tipimiz art�k bir topluluk de�ildir (��nk� topluluklar private �yelere sahip olamaz). Ve bu, art�k toplu 
ba�latmay� kullanamayaca��m�z anlam�na gelir:

                class Foo // Foo bir topluluk de�ildir (private �yelere sahip)
                {
                    int m_x {};
                    int m_y {};
                };

                int main()
                {
                    Foo foo { 6, 7 }; // derleme hatas�: toplu ba�latma kullan�lamaz

                    return 0;
                }
Private �yelere sahip s�n�f tiplerinin toplu ba�latma ile ba�lat�lmas�na izin verilmemesi, bir dizi nedenle mant�kl�d�r:

Toplu ba�latma, s�n�f�n uygulamas� hakk�nda bilgi gerektirir (��nk� �yelerin ne oldu�unu ve hangi s�rayla tan�mland���n�
bilmelisiniz), ki bu, veri �yelerimizi gizledi�imizde kas�tl� olarak ka��nmaya �al��t���m�z bir �eydir. E�er s�n�f�m�z�n baz�
t�rden de�i�mezleri olsayd�, kullan�c�n�n s�n�f�, de�i�mezi koruyacak bir �ekilde ba�latmas�na g�veniyor olurduk. Peki private �ye
de�i�kenlere sahip bir s�n�f� nas�l ba�lat�r�z? �nceki �rnekte derleyici taraf�ndan verilen hata mesaj� bir ipucu sa�lar:
�hata: �Foo� ba�latmas� i�in e�le�en bir yap�land�r�c� yok�

E�le�en bir yap�land�r�c�ya ihtiyac�m�z olmal�. Ama bu ne demek?

Yap�land�r�c�lar ( Constructor )
--------------------------------
Bir yap�land�r�c�, bir topluluk olmayan bir s�n�f tipi nesnesi olu�turulduktan sonra otomatik olarak �a�r�lan �zel bir �ye
fonksiyonudur. Bir topluluk olmayan bir s�n�f tipi nesnesi tan�mland���nda, derleyici, �a��ran�n sa�lad��� ba�latma de�erleri 
(varsa) i�in eri�ilebilir bir e�le�en yap�land�r�c� bulup bulamayaca��n� g�rmek i�in bakar.

E�er eri�ilebilir bir e�le�en yap�land�r�c� bulunursa, nesne i�in bellek ayr�l�r ve sonra yap�land�r�c� fonksiyonu �a�r�l�r.
E�er eri�ilebilir bir e�le�en yap�land�r�c� bulunamazsa, bir derleme hatas� olu�turulur.

Ana Fikir �udur ki, Bir�ok yeni programc�, yap�land�r�c�lar�n nesneleri olu�turup olu�turmad��� konusunda kar���kl��a d��er. 
Onlar olu�turmaz -- derleyici, yap�land�r�c� �a�r�s�ndan �nce nesne i�in bellek ay�r�m�n� ayarlar. Yap�land�r�c� daha sonra 
ba�lat�lmam�� nesne �zerinde �a�r�l�r.

Ancak, bir dizi ba�lat�c� i�in e�le�en bir yap�land�r�c� bulunamazsa, derleyici hata verir. Yani yap�land�r�c�lar nesneleri 
olu�turmaz, ancak e�le�en bir yap�land�r�c�n�n eksikli�i bir nesnenin olu�turulmas�n� engeller.

Bir nesnenin nas�l olu�turulabilece�ini belirlemenin �tesinde, yap�land�r�c�lar genellikle iki i�levi yerine getirir:

*- Genellikle �ye de�i�kenlerinin ba�lat�lmas�n� ger�ekle�tirirler (bir �ye ba�latma listesi arac�l���yla)
*- Di�er kurulum i�levlerini ger�ekle�tirebilirler (yap�land�r�c�n�n g�vdesindeki ifadeler arac�l���yla). Bu, ba�latma 
   de�erlerinin hata kontrol�n�, bir dosyan�n veya veritaban�n�n a��lmas�n� vb. i�erebilir...
   Yap�land�r�c� y�r�tmeyi bitirdikten sonra, nesnenin "olu�turuldu�unu" s�yleriz ve nesne art�k tutarl�, kullan�labilir bir durumda
   olmal�d�r.

Not edin ki topluluklar�n yap�land�r�c�lara sahip olmas�na izin verilmez -- yani bir toplulu�a bir yap�land�r�c� eklerseniz,
art�k bir topluluk olmaz.

Yap�land�r�c�lar�n Adland�r�lmas�
---------------------------------
Normal �ye fonksiyonlar�n aksine, yap�land�r�c�lar adland�r�lmal�d�r:

Yap�land�r�c�lar, s�n�f ile ayn� ada (ayn� b�y�k/k���k harf kullan�m�yla) sahip olmal�d�r. �ablon s�n�flar i�in bu ad, �ablon 
parametrelerini i�ermez.

Yap�land�r�c�lar�n d�n�� tipi yoktur (hatta void bile de�il).
Yap�land�r�c�lar genellikle s�n�f�n�z�n aray�z�n�n bir par�as�d�r, bu y�zden genellikle public olurlar.

Temel Bir Yap�land�r�c� �rne�i
------------------------------
Yukar�daki �rne�imize temel bir yap�land�r�c� ekleyelim:
                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo(int x, int y) // iki ba�lat�c� alan yap�land�r�c� fonksiyonumuz burada
                    {
                        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 }; // Foo(int, int) yap�land�r�c�s�n� �a��r�r
                    foo.print();

                    return 0;
                }

Bu program art�k derlenecek ve sonucu �retecek:

                Foo(6, 7) constructed
                Foo(0, 0)
Derleyici Foo foo{ 6, 7 } tan�m�n� g�rd���nde, iki int arg�man� kabul edecek bir Foo yap�land�r�c�s� arar. Foo(int, int) bir 
e�le�medir, bu y�zden derleyici tan�ma izin verir.

�al��ma zaman�nda, foo �rneklendi�inde, foo i�in bellek ayr�l�r ve ard�ndan Foo(int, int) yap�land�r�c�s�, x parametresi 6'ya ve
y parametresi 7'ye ba�lat�larak �a�r�l�r. Yap�land�r�c� fonksiyonunun g�vdesi daha sonra y�r�t�l�r ve Foo(6, 7) constructed yazar.

Print() �ye fonksiyonunu �a��rd���m�zda, m_x ve m_y �yelerinin de�eri 0 oldu�unu not edeceksiniz. Bu, Foo(int, int) yap�land�r�c�
fonksiyonumuz �a�r�ld�, ancak asl�nda �yeleri ba�latmad�. Bunu nas�l yapaca��m�z� bir sonraki derste g�sterece�iz.

Yap�land�r�c� Arg�manlar�n�n Implicit D�n���m�
----------------------------------------------
Ders 10.1 -- Implicit T�r D�n���m�'nde, derleyicinin bir fonksiyon �a�r�s�ndaki arg�manlar�n implicit d�n���m�n� 
ger�ekle�tirece�ini belirttik (gerekirse), parametrelerin farkl� bir t�r oldu�u bir fonksiyon tan�m�na uyacak �ekilde:

                void foo(int, int)
                {
                }

                int main()
                {
                    foo('a', true); // foo(int, int) ile e�le�ir

                    return 0;
                }
Bu, yap�land�r�c�lar i�in de farkl� de�ildir: Foo(int, int) yap�land�r�c�s�, arg�manlar�n�n int'e implicit d�n��t�r�lebilir oldu�u
herhangi bir �a�r�yla e�le�ir:

                class Foo
                {
                public:
                    Foo(int x, int y)
                    {
                    }
                };

                int main()
                {
                    Foo foo{ 'a', true }; // Foo(int, int) yap�land�r�c�s� ile e�le�ir

                    return 0;
                }

Yap�land�r�c�lar const Olmamal�d�r
----------------------------------
Bir yap�land�r�c�n�n, olu�turulan nesneyi ba�latabilmesi gereklidir -- bu nedenle, bir yap�land�r�c� const olmamal�d�r.

                #include <iostream>

                class Something
                {
                private:
                    int m_x{};

                public:
                    Something() // yap�land�r�c�lar const olmamal�d�r
                    {
                        m_x = 5; // const olmayan yap�land�r�c�da �yeleri de�i�tirmek tamam
                    }

                    int getX() const { return m_x; } // const
                };

                int main()
                {
                    const Something s{}; // const nesne, implicit olarak (const olmayan) yap�land�r�c�y� �a��r�r

                    std::cout << s.getX(); // 5 yazar

                    return 0;
                }
Normalde bir const olmayan �ye fonksiyonu, bir const nesne �zerinde �a�r�lamaz. Ancak, yap�land�r�c� implicit olarak �a�r�ld���
i�in, bir const nesne �zerinde const olmayan bir yap�land�r�c� �a�r�labilir.

Yap�land�r�c�lar vs Ayarlay�c�lar ( setter lar )
------------------------------------------------
Yap�land�r�c�lar, bir nesnenin t�m�n� olu�turma an�nda ba�latmak �zere tasarlanm��t�r. Ayarlay�c�lar, mevcut bir nesnenin tek bir 
�yesine bir de�er atamak �zere tasarlanm��t�r.

14.10 � �ye Ba�latma Listeleri ile Yap�land�r�c�lar
---------------------------------------------------
�ye Ba�latma, bir �ye Ba�latma Listesi ile
------------------------------------------
Bir yap�land�r�c�n�n �yeleri ba�latmas�n� sa�lamak i�in, bir �ye ba�latma listesi (genellikle "�ye ba�latma listesi" olarak
adland�r�l�r) kullan�r�z. Bu terimi, bir de�erler listesi ile topluluklar� ba�latmak i�in kullan�lan "ba�lat�c� listesi" ile
kar��t�rmay�n.

�ye ba�latma listeleri, en iyi �ekilde �rnek �zerinden ��renilir. A�a��daki �rnekte, Foo(int, int) yap�land�r�c�m�z, m_x ve m_y'yi
ba�latmak i�in bir �ye ba�latma listesi kullanacak �ekilde g�ncellenmi�tir:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo(int x, int y)
                        : m_x { x }, m_y { y } // i�te �ye ba�latma listemiz
                    {
                        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
�ye ba�latma listesi, yap�land�r�c� parametrelerinden sonra tan�mlan�r. Bir iki nokta �st �ste (:) ile ba�lar ve ard�ndan ba�latma
de�eri ile birlikte ba�lat�lacak her �yeyi listeler, virg�lle ayr�l�r. Burada do�rudan bir ba�latma formu kullanmal�s�n�z 
(tercihen s�sl� parantezler kullanarak, ancak parantezler de i�e yarar) -- e�ittir ile kopya ba�latma burada i�e yaramaz. Ayr�ca 
�ye ba�latma listesinin bir noktal� virg�lle sona ermedi�ini unutmay�n.

Bu program a�a��daki ��kt�y� �retir:

                Foo(6, 7) constructed
                Foo(6, 7)
Foo �rneklendi�inde, ba�latma listesindeki �yeler belirtilen ba�latma de�erleri ile ba�lat�l�r. Bu durumda, �ye ba�latma listesi
m_x'i x'in de�eri olan 6'ya ve m_y'yi y'nin de�eri olan 7'ye ba�lat�r. Ard�ndan yap�land�r�c�n�n g�vdesi �al���r.

Print() �ye fonksiyonunu �a��rd���n�zda, m_x'in hala 6 de�erine ve m_y'nin hala 7 de�erine sahip oldu�unu g�rebilirsiniz.

�ye Ba�latma Listesi Bi�imlendirme
----------------------------------
C++, �ye ba�latma listelerinizi tercih etti�iniz gibi bi�imlendirmeniz i�in size �ok fazla �zg�rl�k sa�lar, ��nk� iki nokta �st
�ste, virg�l veya bo�luklar�n�z� nereye koydu�unuz konusunda umursamaz.
A�a��daki stiller t�m� ge�erlidir (ve uygulamada hepsini g�rmek olas�d�r):

                Foo(int x, int y) : m_x { x }, m_y { y }
                {
                }
                Foo(int x, int y) :
                    m_x { x },
                    m_y { y }
                {
                }
                Foo(int x, int y)
                    : m_x { x }
                    , m_y { y }
                {
                }
�nerimiz, yukar�daki ���nc� stili kullanmakt�r:

�ki nokta �st �steyi, yap�land�r�c� ad�ndan sonraki sat�ra koyun, ��nk� bu, �ye ba�latma listesini fonksiyon prototipinden temiz 
bir �ekilde ay�r�r. �ye ba�latma listenizi girintili yap�n, fonksiyon adlar�n� g�rmeyi kolayla�t�r�r. E�er �ye ba�latma listesi
k�sa/trivial ise, t�m ba�lat�c�lar tek bir sat�rda olabilir:

                Foo(int x, int y)
                    : m_x { x }, m_y { y }
                {
                }
Aksi takdirde (veya tercih ederseniz), her �ye ve ba�lat�c� �ifti ayr� bir sat�ra konabilir (hizalamay� korumak i�in virg�lle 
ba�layarak):

                Foo(int x, int y)
                    : m_x { x }
                    , m_y { y }
                {
                }

�ye Ba�latma S�ras�
-------------------
C++ standard�na g�re, bir �ye ba�latma listesindeki �yeler her zaman s�n�f i�inde tan�mland�klar� s�raya g�re ba�lat�l�r (�ye
ba�latma listesinde tan�mland�klar� s�raya de�il).

Yukar�daki �rnekte, m_x s�n�f tan�m�nda m_y'den �nce tan�mland��� i�in, m_x ilk olarak ba�lat�l�r (�ye ba�latma listesinde
ilk s�rada listelenmemi� olsa bile).

De�i�kenlerin intuitif olarak soldan sa�a ba�lat�lmas�n� bekledi�imiz i�in, bu, ince hatalar�n olu�mas�na neden olabilir.
A�a��daki �rne�i d���n�n:

                #include <algorithm> // std::max i�in
                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    Foo(int x, int y)
                        : m_y{ std::max(x, y) }, m_x{ m_y } // bu sat�rda sorun var
                    {
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
Yukar�daki �rnekte, amac�m�z, ge�irilen ba�latma de�erlerinin daha b�y���n� hesaplamak (std::max(x, y) arac�l���yla) ve bu de�eri 
hem m_x hem de m_y'yi ba�latmak i�in kullanmakt�r. Ancak, yazar�n makinesinde, a�a��daki sonu� yazd�r�l�r:

                Foo(-858993460, 7)
Ne oldu? M_y, �ye ba�latma listesinde ilk s�rada listelenmi� olsa bile, m_x s�n�fta ilk tan�mland��� i�in, m_x ilk olarak 
ba�lat�l�r. Ve m_x, hen�z ba�lat�lmam�� olan m_y'nin de�erine ba�lat�l�r. Son olarak, m_y, ba�latma de�erlerinin daha b�y���ne 
ba�lat�l�r.

Bu t�r hatalar� �nlemek i�in, �ye ba�latma listesindeki �yeler, s�n�fta tan�mland�klar� s�raya g�re listelenmelidir. �yelerin 
s�ras� d���nda ba�lat�lmas� durumunda, baz� derleyiciler bir uyar� verecektir.

*** BEST -> Bir �ye ba�latma listesindeki �ye de�i�kenler, s�n�fta tan�mland�klar� s�raya g�re listelenmelidir.

Ayr�ca, �yeleri di�er �yelerin de�erini kullanarak ba�latmaktan ka��nmak da iyi bir fikirdir (m�mk�nse). Bu �ekilde, ba�latma
s�ras�nda bir hata yaparsan�z, ba�latma de�erleri aras�nda hi�bir ba��ml�l�k olmad��� i�in �nemli olmamal�d�r.

�ye Ba�latma Listesi vs Varsay�lan �ye Ba�lat�c�lar�
----------------------------------------------------
�yeler, birka� farkl� �ekilde ba�lat�labilir:

Bir �ye, �ye ba�latma listesinde listelenmi�se, o ba�latma de�eri kullan�l�r
Aksi takdirde, �yenin bir varsay�lan �ye ba�lat�c�s� varsa, o ba�latma de�eri kullan�l�r
Aksi takdirde, �ye varsay�lan olarak ba�lat�l�r.
Bu, bir �yenin hem bir varsay�lan �ye ba�lat�c�s� hem de yap�land�r�c� i�in �ye ba�latma listesinde listelenmi�se, �ye ba�latma
listesi de�eri �nceli�i al�r demektir.

��te t�m �� ba�latma y�ntemini g�steren bir �rnek:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};    // varsay�lan �ye ba�lat�c� (g�z ard� edilecek)
                    int m_y{ 2 }; // varsay�lan �ye ba�lat�c� (kullan�lacak)
                    int m_z;      // ba�lat�c� yok

                public:
                    Foo(int x)
                        : m_x{ x } // �ye ba�latma listesi
                    {
                        std::cout << "Foo constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6 };
                    foo.print();

                    return 0;
                }

Yazar�n makinesinde, bu ��kt�y� verir:

                Foo constructed
                Foo(6, 2, -858993460)
��te burada olanlar. Foo olu�turuldu�unda, yaln�zca m_x �ye ba�latma listesinde g�r�n�r, bu y�zden m_x ilk olarak 6'ya ba�lat�l�r.
M_y, �ye ba�latma listesinde de�ildir, ancak bir varsay�lan �ye ba�lat�c�s� vard�r, bu y�zden 2'ye ba�lat�l�r. M_z ne �ye ba�latma
listesinde ne de varsay�lan bir �ye ba�lat�c�s� vard�r, bu y�zden varsay�lan olarak ba�lat�l�r (ki bu, temel tipler i�in,
ba�lat�lmam�� oldu�u anlam�na gelir). Bu y�zden, m_z'nin de�erini yazd�rd���m�zda, tan�mlanmam�� davran�� elde ederiz.

Yap�land�r�c� Fonksiyon G�vdeleri
---------------------------------
Yap�land�r�c� fonksiyonlar�n g�vdeleri genellikle bo� b�rak�l�r. Bunun nedeni, yap�land�r�c�y� �o�unlukla ba�latma i�in
kullanmam�zd�r, bu da �ye ba�latma listesi arac�l���yla yap�l�r. E�er yapmam�z gereken tek �ey bu ise, yap�land�r�c�n�n g�vdesinde
herhangi bir ifadeye ihtiyac�m�z yoktur.

Ancak, yap�land�r�c�n�n g�vdesindeki ifadeler, �ye ba�latma listesi y�r�t�ld�kten sonra y�r�t�l�r, bu y�zden ba�ka herhangi bir 
kurulum g�revi gerektiren ifadeler ekleyebiliriz. Yukar�daki �rneklerde, yap�land�r�c�n�n y�r�t�ld���n� g�stermek i�in konsola
bir �eyler yazd�r�yoruz, ancak ba�ka �eyler de yapabilirdik, �rne�in bir dosya veya veritaban� a�abilir, bellek ay�rabiliriz,vb...

Yeni programc�lar bazen yap�land�r�c�n�n g�vdesini �yelere de�er atamak i�in kullan�r:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    Foo(int x, int y)
                    {
                        m_x = x; // yanl��: bu bir atama, ba�latma de�il
                        m_y = y; // yanl��: bu bir atama, ba�latma de�il
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
Bu basit durumda bu, beklenen sonucu verecektir, ancak �yelerin ba�lat�lmas� gerekti�i durumlarda (�rne�in, const veya referans
olan veri �yeleri i�in) atama i�lemi �al��mayacakt�r.
*** BEST -> �yelerinizi ba�latmak i�in �ye ba�latma listesini kullanmay�, yap�land�r�c�n�n g�vdesinde de�er atamay� tercih edin.

14.11 � Varsay�lan Yap�land�r�c�lar ve Varsay�lan Arg�manlar
------------------------------------------------------------
Bir varsay�lan yap�land�r�c�, hi�bir arg�man kabul etmeyen bir yap�land�r�c�d�r. Genellikle, bu, hi�bir parametre ile tan�mlanm��
bir yap�land�r�c�d�r.

��te varsay�lan bir yap�land�r�c�ya sahip bir s�n�f�n �rne�i:

                #include <iostream>

                class Foo
                {
                public:
                    Foo() // varsay�lan yap�land�r�c�
                    {
                        std::cout << "Foo default constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // Hi�bir ba�latma de�eri yok, Foo'nun varsay�lan yap�land�r�c�s�n� �a��r�r

                    return 0;
                }
Yukar�daki program �al��t�r�ld���nda, Foo tipinde bir nesne olu�turulur. Hi�bir ba�latma de�eri sa�lanmad���ndan, varsay�lan 
yap�land�r�c� Foo() �a�r�l�r, bu da �unu yazd�r�r:

                Foo default constructed
S�n�f Tipleri i�in De�er Ba�latma vs Varsay�lan Ba�latma
--------------------------------------------------------
Bir s�n�f tipi bir varsay�lan yap�land�r�c�ya sahipse, hem de�er ba�latma hem de varsay�lan ba�latma varsay�lan yap�land�r�c�y�
�a��r�r. Bu nedenle, yukar�daki �rnekteki Foo s�n�f� gibi bir s�n�f i�in, a�a��dakiler esasen e�de�erdir:

                Foo foo{}; // de�er ba�latma, Foo() varsay�lan yap�land�r�c�s�n� �a��r�r
                Foo foo2;  // varsay�lan ba�latma, Foo() varsay�lan yap�land�r�c�s�n� �a��r�r

Ancak, zaten 13.7 -- Varsay�lan �ye Ba�latma dersinde ele ald���m�z gibi, de�er ba�latma topluluklar i�in daha g�venlidir.
Bir s�n�f tipinin bir topluluk olup olmad���n� anlamak zor oldu�undan, her �ey i�in sadece de�er ba�latmay� kullanmak ve bunun 
hakk�nda endi�elenmemek daha g�venlidir.
*** BEST -> T�m s�n�f tipleri i�in varsay�lan ba�latmay� de�er ba�latmaya tercih edin.

Varsay�lan Arg�manlara Sahip Yap�land�r�c�lar
---------------------------------------------
T�m fonksiyonlarda oldu�u gibi, yap�land�r�c�lar�n en sa�daki parametreleri varsay�lan arg�manlara sahip olabilir. �rne�in:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x { };
                    int m_y { };

                public:
                    Foo(int x=0, int y=0) // varsay�lan arg�manlara sahip
                        : m_x { x }
                        , m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo1{};     // Foo(int, int) yap�land�r�c�s�n� varsay�lan arg�manlar� kullanarak �a��r�r
                    Foo foo2{6, 7}; // Foo(int, int) yap�land�r�c�s�n� �a��r�r

                    return 0;
                }
                Bu, �unu yazd�r�r:

                Foo(0, 0) constructed
                Foo(6, 7) constructed
Bir yap�land�r�c�n�n t�m parametreleri varsay�lan arg�manlara sahipse, yap�land�r�c� bir varsay�lan yap�land�r�c�d�r
(��nk� hi�bir arg�man olmadan �a�r�labilir).

A��r� Y�klenmi� Yap�land�r�c�lar
--------------------------------
Yap�land�r�c�lar fonksiyonlar oldu�u i�in, a��r� y�klenebilirler. Yani, farkl� �ekillerde nesneler olu�turabilmek i�in birden
fazla yap�land�r�c�m�z olabilir:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() // varsay�lan yap�land�r�c�
                    {
                        std::cout << "Foo constructed\n";
                    }

                    Foo(int x, int y) // varsay�lan olmayan yap�land�r�c�
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo1{};     // Foo() yap�land�r�c�s�n� �a��r�r
                    Foo foo2{6, 7}; // Foo(int, int) yap�land�r�c�s�n� �a��r�r

                    return 0;
                }
Yukar�dakinden ��kan bir sonu�, bir s�n�f�n yaln�zca bir varsay�lan yap�land�r�c�s� olmas� gerekti�idir. Birden fazla varsay�lan 
yap�land�r�c� sa�lan�rsa, derleyici hangisinin kullan�laca��n� belirleyemez:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() // varsay�lan yap�land�r�c�
                    {
                        std::cout << "Foo constructed\n";
                    }

                    Foo(int x=1, int y=2) // varsay�lan yap�land�r�c�
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // derleme hatas�: belirsiz yap�land�r�c� fonksiyon �a�r�s�

                    return 0;
                }
Yukar�daki �rnekte, foo'yu hi�bir arg�man olmadan �rneklendiriyoruz, bu y�zden derleyici bir varsay�lan yap�land�r�c� arar. 
�kisini bulur ve hangi yap�land�r�c�n�n kullan�laca��n� belirleyemez. Bu, bir derleme hatas�na neden olur.

Implicit Varsay�lan Yap�land�r�c�
---------------------------------
Bir topluluk olmayan bir s�n�f tipi nesnesinin kullan�c� taraf�ndan bildirilen bir yap�land�r�c�s� yoksa, derleyici bir public
varsay�lan yap�land�r�c� olu�turur (b�ylece s�n�f, de�er veya varsay�lan olarak ba�lat�labilir). Bu yap�land�r�c�ya implicit 
varsay�lan yap�land�r�c� denir.

A�a��daki �rne�i d���n�n:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                    // Not: hi�bir yap�land�r�c� bildirilmedi
                };

                int main()
                {
                    Foo foo{};

                    return 0;
                }
Bu s�n�f�n kullan�c� taraf�ndan bildirilen bir yap�land�r�c�s� yok, bu y�zden derleyici bizim i�in bir implicit varsay�lan
yap�land�r�c� olu�turur. Bu yap�land�r�c�, foo{}'yu �rneklendirmek i�in kullan�l�r.

Implicit varsay�lan yap�land�r�c�, hi�bir parametresi olmayan, �ye ba�latma listesi olmayan ve yap�land�r�c�n�n g�vdesinde hi�bir
ifadesi olmayan bir yap�land�r�c�ya e�de�erdir. Di�er bir deyi�le, yukar�daki Foo s�n�f� i�in, derleyici bunu olu�turur:
                public:
                    Foo() // implicit olarak olu�turulan varsay�lan yap�land�r�c�
                    {
                    }
Implicit varsay�lan yap�land�r�c�, �o�unlukla veri �yeleri olmayan s�n�flar i�in yararl�d�r. E�er bir s�n�f�n veri �yeleri varsa,
muhtemelen onlar� kullan�c�n�n sa�lad��� de�erlerle ba�lat�labilir yapmak isteyece�iz ve implicit varsay�lan yap�land�r�c� bunun 
i�in yeterli de�ildir.

Varsay�lan bir Yap�land�r�c� Olu�turmak i�in = default Kullanma
---------------------------------------------------------------
Varsay�lan bir yap�land�r�c� yazaca��m�z durumlarda, bu yap�land�r�c� implicit olarak olu�turulan varsay�lan yap�land�r�c�ya 
e�de�erse, derleyicinin bizim i�in bir implicit varsay�lan yap�land�r�c� olu�turmas�n� s�yleyebiliriz. A�a��daki s�zdizimini 
kullanarak:
                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() = default; // bir implicit varsay�lan yap�land�r�c� olu�tur

                    Foo(int x, int y)
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // Foo() varsay�lan yap�land�r�c�s�n� �a��r�r

                    return 0;
                }
Yukar�daki �rnekte, kullan�c� taraf�ndan bildirilen bir yap�land�r�c�m�z var (Foo(int, int)), bu y�zden normalde bir implicit 
varsay�lan yap�land�r�c� olu�turulmaz. Ancak, derleyiciye b�yle bir yap�land�r�c� olu�turmas�n� s�yledi�imiz i�in, olu�turur. 
Bu yap�land�r�c�, daha sonra foo{}'nun �rneklendirilmesi i�in kullan�l�r.

Implicit Varsay�lan Yap�land�r�c� vs Bo� Kullan�c� Yap�land�r�c�s�
------------------------------------------------------------------
Implicit varsay�lan yap�land�r�c�n�n bo� bir kullan�c�n�n sa�lad��� yap�land�r�c�dan farkl� davrand��� en az bir durum vard�r. 
Bir s�n�f� de�er ba�lat�rken, s�n�f�n kullan�c� taraf�ndan sa�lanan bir varsay�lan yap�land�r�c�s� varsa, nesne varsay�lan olarak 
ba�lat�l�r. Ancak, s�n�f�n kullan�c� taraf�ndan sa�lanmayan bir varsay�lan yap�land�r�c�s� varsa (yani, ya implicit tan�ml� bir 
yap�land�r�c� veya =default kullan�larak olu�turulan bir varsay�lan yap�land�r�c�), nesne varsay�lan ba�latma �ncesinde s�f�ra
ba�lat�l�r.
                #include <iostream>

                class User
                {
                private:
                    int m_a; // not: varsay�lan ba�latma de�eri yok
                    int m_b {};

                public:
                    User() {} // kullan�c� taraf�ndan sa�lanan bo� yap�land�r�c�

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                class Default
                {
                private:
                    int m_a; // not: varsay�lan ba�latma de�eri yok
                    int m_b {};

                public:
                    Default() = default; // a��k�a varsay�lan varsay�lan yap�land�r�c�

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                class Implicit
                {
                private:
                    int m_a; // not: varsay�lan ba�latma de�eri yok
                    int m_b {};

                public:
                    // implicit varsay�lan yap�land�r�c�

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                int main()
                {
                    User user{}; // varsay�lan ba�lat�l�r
                    std::cout << user.a() << ' ' << user.b() << '\n';

                    Default def{}; // s�f�ra ba�lat�l�r, sonra varsay�lan ba�lat�l�r
                    std::cout << def.a() << ' ' << def.b() << '\n';

                    Implicit imp{}; // s�f�ra ba�lat�l�r, sonra varsay�lan ba�lat�l�r
                    std::cout << imp.a() << ' ' << imp.b() << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu ��kt�y� verir:

                782510864 0
                0 0
                0 0
Not edin ki, user.a varsay�lan ba�latma �ncesinde s�f�ra ba�lat�lmad� ve bu nedenle ba�lat�lmam�� oldu. Pratikte, t�m veri �yeleri
i�in varsay�lan �ye ba�lat�c�lar� sa�laman�z gerekti�i i�in bu �nemli olmamal�d�r!

*** BEST -> Bo� bir g�vdeye sahip varsay�lan bir yap�land�r�c� yerine a��k�a varsay�lan bir varsay�lan yap�land�r�c� (=default)
            tercih edin.
Yaln�zca Mant�kl� Oldu�unda Bir Varsay�lan Yap�land�r�c� Olu�turun
------------------------------------------------------------------
Bir varsay�lan yap�land�r�c�, kullan�c� taraf�ndan sa�lanan ba�latma de�erleri olmadan bir topluluk olmayan s�n�f tipi nesneleri 
olu�turmam�za izin verir. Bu nedenle, bir s�n�f yaln�zca bir s�n�f tipi nesnelerinin t�m varsay�lan de�erler kullan�larak
olu�turulmas�n�n mant�kl� oldu�u durumlarda bir varsay�lan yap�land�r�c� sa�lamal�d�r.
�rne�in:
                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    Fraction() {}
                    Fraction(int numerator, int denominator)
                        : m_numerator{ numerator }
                        , m_denominator{ denominator }
                    {
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f1 {3, 5};
                    f1.print();

                    Fraction f2 {}; // will get Fraction 0/1
                    f2.print();

                    return 0;
                }
Bir kesiri temsil eden bir s�n�f i�in, kullan�c�n�n ba�lat�c� olmadan Kesir nesneleri olu�turmas�na izin vermek mant�kl�d�r 
(bu durumda, kullan�c� kesir 0/1'i al�r). �imdi bu s�n�f� d���n�n:
                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{ };
                    int m_id{ };

                public:
                    Employee(std::string_view name, int id)
                        : m_name{ name }
                        , m_id{ id }
                    {
                    }

                    void print() const
                    {
                        std::cout << "Employee(" << m_name << ", " << m_id << ")\n";
                    }
                };

                int main()
                {
                    Employee e1 { "Joe", 1 };
                    e1.print();

                    Employee e2 {}; // compile error: no matching constructor
                    e2.print();

                    return 0;
                }
Bir �al��an� temsil eden bir s�n�f i�in, ismi olmayan �al��anlar�n olu�turulmas�na izin vermek mant�kl� de�ildir. Bu nedenle,
b�yle bir s�n�f�n bir varsay�lan yap�land�r�c�s� olmamal�d�r, b�ylece s�n�f�n kullan�c�s� bunu yapmaya �al���rsa bir derleme
hatas� olu�ur.

14.12 � Yap�land�r�c�lar� Delege Etme
-------------------------------------
M�mk�n oldu�unda, gereksiz kodu azaltmak istiyoruz (DRY prensibini takip ederek -- Kendinizi Tekrarlamay�n). 
A�a��daki fonksiyonlar� d���n�n:

                void A()
                {
                    // G�rev A'y� yapan ifadeler
                }

                void B()
                {
                    // G�rev A'y� yapan ifadeler
                    // G�rev B'yi yapan ifadeler
                }

Her iki fonksiyonda da tamamen ayn� �eyi yapan bir ifade k�mesi var (g�rev A). Bu durumda, �u �ekilde yeniden d�zenleyebiliriz:

                void A()
                {
                    // G�rev A'y� yapan ifadeler
                }

                void B()
                {
                    A();
                    // G�rev B'yi yapan ifadeler
                }

Bu �ekilde, A() ve B() fonksiyonlar�nda bulunan gereksiz kodu kald�rm�� oluruz. Bu, kodumuzu daha kolay bak�m yap�labilir hale
getirir, ��nk� de�i�iklikler yaln�zca bir yerde yap�lmal�d�r.

Bir s�n�f�n birden �ok yap�land�r�c�s� oldu�unda, her yap�land�r�c�n�n kodunun benzer hatta ayn� olmas� son derece yayg�nd�r,
�ok fazla tekrar vard�r. M�mk�n oldu�unda yap�land�r�c� tekrar�n� da kald�rmak isteriz. A�a��daki �rne�i d���n�n:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Her yap�land�r�c�n�n g�vdesi ayn� �eyi yazd�r�r.

Yap�land�r�c�lar, di�er fonksiyonlar� �a��rabilir, s�n�f�n di�er �ye fonksiyonlar�n� da i�erir. Bu y�zden �u �ekilde yeniden
d�zenleyebiliriz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                    void printCreated() const
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        printCreated();
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        printCreated();
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Bu, �nceki versiyondan daha iyidir, ancak yeni bir fonksiyonun tan�t�lmas�n� gerektirir, bu da ideal de�ildir.

Daha iyisini yapabilir miyiz?

A��k ��z�m i�e yaram�yor

Yukar�daki �rnekte oldu�u gibi, fonksiyon B()'nin fonksiyon A()'y� �a��rmas�na benzer �ekilde, a��k ��z�m, Employee 
yap�land�r�c�lar�ndan birinin di�er yap�land�r�c�y� �a��rmas� olacakt�r. Ancak bu, beklenildi�i gibi �al��mayacakt�r,
��nk� yap�land�r�c�lar, ba�ka bir fonksiyonun g�vdesinden (di�er yap�land�r�c�lar da dahil olmak �zere) do�rudan �a�r�lmak
�zere tasarlanmam��t�r! �rne�in, bunu denemeyi d���nebilirsiniz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        Employee(name); // derleme hatas�
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Bu i�e yaramaz ve bir derleme hatas�na neden olur. Daha tehlikeli bir durum, herhangi bir arg�man olmadan bir yap�land�r�c�y�
a��k�a �a��rmay� denedi�imizde ortaya ��kar. Bu, varsay�lan yap�land�r�c�ya bir fonksiyon �a�r�s� yapmaz -- aksine, ge�ici 
(isimsiz) bir nesne olu�turur ve onu de�er ba�lat�r! ��te bunu g�steren sa�ma bir �rnek:
                #include <iostream>
                struct Foo
                {
                    int x{};
                    int y{};

                public:
                    Foo()
                    {
                        x = 5;
                    }

                    Foo(int value): y { value }
                    {
                        // niyet: Foo() fonksiyonunu �a��rmak
                        // ger�ek: value, isimsiz ge�ici Foo'yu ba�lat�r (daha sonra at�l�r)
                        Foo(); // not: bu, Foo{} yazman�n e�de�eridir
                    }
                };

                int main()
                {
                    Foo f{ 9 };
                    std::cout << f.x << ' ' << f.y; // 0 9 yazd�r�r
                }
Bu �rnekte, Foo(int) yap�c�s� Foo() ifadesine sahip ve Foo() yap�c�s�n� �a��r�p x �yesine 5 de�erini atamay� bekliyor.
Ancak bu s�zdizimi, asl�nda isimsiz ge�ici bir Foo olu�turur ve ard�ndan onu de�er ba�lat�r (Foo{} yazm���z gibi). x = 5 ifadesi
�al��t���nda, de�eri atanacak olan x, ge�ici Foo'nun x �yesidir. Ge�ici nesne kullan�lmad��� i�in, yap�m� tamamland�ktan sonra
at�l�r.

Foo(int) yap�c�s�n�n i�sel nesnesinin x �yesine hi�bir de�er atanmaz. Bu y�zden daha sonra main() i�inde de�erini yazd�rd���m�zda,
beklenen 5 yerine 0 al�r�z.

Bu durumun bir derleme hatas� olu�turmad���n� unutmay�n - sadece beklenen sonu�lar� sessizce �retmeyi ba�aramaz!

*** Uyar� -> Yap�c�lar, ba�ka bir fonksiyonun g�vdesinden do�rudan �a�r�lmamal�d�r. Bunu yapmak ya bir derleme hatas�na yol a�ar
             ya da bir ge�ici nesneyi de�er ba�lat�r ve ard�ndan onu atar (ki bu muhtemelen istedi�iniz �ey de�ildir).

Yap�c�lar�n Delege Edilmesi
---------------------------
Yap�c�lar, ba�latmay� ayn� s�n�f t�r�nden ba�ka bir yap�c�ya devretmeye (sorumluluk aktarmaya) izin verir. Bu s�rece bazen yap�c�
zincirleme denir ve bu t�r yap�c�lara delege eden yap�c�lar denir.

Bir yap�c�n�n ba�latmay� ba�ka bir yap�c�ya devretmesini sa�lamak i�in, sadece �ye ba�lat�c� listesinde yap�c�y� �a��r�n.
Yukar�daki �rne�imize uyguland���nda:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : Employee{ name, 0 } // ba�latmay� Employee(std::string_view, int) yap�c�s�na devreder
                    {
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id } // �yeleri ger�ekten ba�lat�r
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
e1 { "James" } ba�lat�ld���nda, parametre ad� "James" olarak ayarlanm�� olan Employee(std::string_view) yap�c�s� �a�r�l�r. 
Bu yap�c�n�n �ye ba�lat�c� listesi, ba�latmay� ba�ka bir yap�c�ya devreder, bu y�zden Employee(std::string_view, int) daha sonra 
�a�r�l�r. Ad�n de�eri ("James") ilk arg�man olarak ge�irilir ve 0 de�eri ikinci arg�man olarak ge�irilir. Delege edilen yap�c�n�n
�ye ba�lat�c� listesi daha sonra �yeleri ba�lat�r. Delege edilen yap�c�n�n g�vdesi daha sonra �al���r. Daha sonra kontrol,
ba�lang��taki yap�c�ya d�ner, onun (bo�) g�vdesi �al���r. Son olarak, kontrol �a��r�c�ya d�ner.

Bu y�ntemin dezavantaj�, bazen ba�latma de�erlerinin �o�alt�lmas�n� gerektirmesidir. Employee(std::string_view, int) yap�c�s�na 
yap�lan delegasyonda, int parametresi i�in bir ba�latma de�erine ihtiyac�m�z var. Varsay�lan �ye ba�lat�c�s�na ba�vurman�n bir 
yolu olmad��� i�in, 0 de�erini elle girmek zorunda kald�k.

Delege eden yap�c�lar hakk�nda birka� ek not. �lk olarak, ba�ka bir yap�c�ya delegasyon yapan bir yap�c�, kendi ba��na herhangi
bir �ye ba�latmas� yapamaz. Yani yap�c�lar�n�z ya delegasyon yapabilir ya da ba�latabilir, ama her ikisini birden yapamaz.
Yan Not�

Daha az parametreye sahip olan Employee(std::string_view) yap�land�r�c�s�n�n, daha fazla parametreye sahip olan
Employee(std::string_view name, int id) yap�land�r�c�s�na delege etti�ini unutmay�n. Daha az parametreye sahip olan
yap�land�r�c�n�n, daha fazla parametreye sahip olan yap�land�r�c�ya delege etmesi yayg�nd�r.

E�er Employee(std::string_view name, int id) yap�land�r�c�s�n�n Employee(std::string_view)'a delege etmesini se�mi� olsayd�k,
bu durumda m_id'yi id kullanarak ba�latamazd�k, ��nk� bir yap�land�r�c� yaln�zca delege edebilir veya ba�latabilir, her ikisini
birden yapamaz.

�kincisi, bir yap�land�r�c�n�n ba�ka bir yap�land�r�c�ya delege etmesi m�mk�nd�r, bu yap�land�r�c� da ilk yap�land�r�c�ya delege 
eder. Bu, sonsuz bir d�ng� olu�turur ve program�n�z�n y���n alan�n�n t�kenmesine ve ��kmesine neden olur. Bunu, t�m 
yap�land�r�c�lar�n�z�n bir delege etmeyen yap�land�r�c�ya ��z�lmesini sa�layarak �nleyebilirsiniz.

*** BEST -> Birden �ok yap�land�r�c�n�z varsa, gereksiz kodu azaltmak i�in delege eden yap�land�r�c�lar� kullan�p
            kullanamayaca��n�z� d���n�n.

Varsay�lan Arg�manlar� Kullanarak Yap�land�r�c�lar� Azaltma
-----------------------------------------------------------
Varsay�lan de�erler, bazen birden �ok yap�land�r�c�y� daha az yap�land�r�c�ya indirgemek i�in kullan�labilir. �rne�in, id
parametremize bir varsay�lan de�er koyarak, bir isim arg�man� gerektiren ancak iste�e ba�l� olarak bir id arg�man� kabul edecek 
tek bir Employee yap�land�r�c�s� olu�turabiliriz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 }; // varsay�lan �ye ba�lat�c�

                public:

                    Employee(std::string_view name, int id = 0) // id i�in varsay�lan arg�man
                        : m_name{ name }, m_id{ id }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }

Varsay�lan de�erler, bir fonksiyon �a�r�s�ndaki en sa�daki parametrelere eklenmelidir, bu y�zden s�n�flar� tan�mlarken iyi bir
uygulama, kullan�c�n�n ba�latma de�erleri sa�lamas� gereken �yeleri ilk olarak tan�mlamakt�r (ve bunlar� yap�land�r�c�n�n en 
solundaki parametreler yapar). Kullan�c�n�n iste�e ba�l� olarak sa�layabilece�i �yeler (��nk� varsay�lan de�erler kabul edilebilir)
ikinci olarak tan�mlanmal�d�r (ve bunlar� yap�land�r�c�n�n en sa�daki parametreleri yapar).

Bu y�ntem ayr�ca m_id i�in varsay�lan ba�latma de�erinin ('0') �o�alt�lmas�n� gerektirir: bir kez varsay�lan �ye ba�lat�c� olarak
ve bir kez varsay�lan arg�man olarak.

Bir �kilem: Gereksiz Yap�land�r�c�lar vs Gereksiz Varsay�lan De�erler

Yukar�daki �rneklerde, yap�land�r�c� tekrar�n� azaltmak i�in delege eden yap�land�r�c�lar� ve ard�ndan varsay�lan arg�manlar�
kulland�k. Ancak her iki y�ntem de �yelerimiz i�in ba�latma de�erlerini �e�itli yerlerde �o�altmam�z� gerektirdi. Maalesef,
�u anda bir delege eden yap�land�r�c�n�n veya varsay�lan arg�man�n varsay�lan �ye ba�lat�c� de�erini kullanmas� gerekti�ini
belirtmenin bir yolu yok.

Daha az yap�land�r�c�ya sahip olman�n (ba�latma de�erlerinin �o�alt�lmas�yla) m� yoksa daha fazla yap�land�r�c�ya sahip olman�n
(ba�latma de�erlerinin �o�alt�lmamas�yla) m� daha iyi oldu�u konusunda �e�itli g�r��ler var. G�r���m�z, genellikle daha az 
yap�land�r�c�n�n olmas�n�n, ba�latma de�erlerinin �o�alt�lmas�na yol a�sa bile, daha basit oldu�udur.

14.13 � Ge�ici s�n�f nesneleri
------------------------------
A�a��daki �rne�i d���n�n:

                #include <iostream>

                int add(int x, int y)
                {
                    int sum{ x + y }; // x + y'yi bir de�i�kende saklar
                    return sum;       // bu de�i�kenin de�erini d�nd�r�r
                }

                int main()
                {
                    std::cout << add(5, 3) << '\n';

                    return 0;
                }
add() fonksiyonunda, sum de�i�keni x + y ifadesinin sonucunu saklamak i�in kullan�l�r. Bu de�i�ken daha sonra return ifadesinde
de�erlendirilir ve d�nd�r�lecek de�eri �retir. Bu, ara s�ra hata ay�klama i�in yararl� olabilir (b�ylece sum de�erini 
istedi�imizde inceleyebiliriz), ancak asl�nda fonksiyonu gerekti�inden daha karma��k hale getirir ��nk� yaln�zca bir kez
kullan�lan bir nesne tan�mlar.

Bir de�i�kenin yaln�zca bir kez kullan�ld��� �o�u durumda, asl�nda bir de�i�kene ihtiyac�m�z yoktur. Bunun yerine,
de�i�kenin kullan�ld��� yerde de�i�keni ba�latmak i�in kullan�lan ifadeyi yerle�tirebiliriz. ��te bu �ekilde yeniden yaz�lm��
add() fonksiyonu:

                #include <iostream>

                int add(int x, int y)
                {
                    return x + y; // sadece x + y'yi do�rudan d�nd�r
                }

                int main()
                {
                    std::cout << add(5, 3) << '\n';

                    return 0;
                }
Bu, yaln�zca return de�erleriyle de�il, ayn� zamanda �o�u fonksiyon arg�man�yla da �al���r. �rne�in, bunun yerine:

                #include <iostream>

                void printValue(int value)
                {
                    std::cout << value;
                }

                int main()
                {
                    int sum{ 5 + 3 };
                    printValue(sum);

                    return 0;
                }
Bunu yazabiliriz:

                #include <iostream>

                void printValue(int value)
                {
                    std::cout << value;
                }

                int main()
                {
                    printValue(5 + 3);

                    return 0;
                }

Kodumuzu ne kadar temiz tuttu�una dikkat edin. Bir de�i�keni tan�mlamak ve bir isim vermek zorunda de�iliz. Ve bu de�i�kenin ba�ka
bir yerde ger�ekten kullan�l�p kullan�lmad���n� belirlemek i�in t�m fonksiyonu tarayamay�z. ��nk� 5 + 3 bir ifade oldu�u i�in,
yaln�zca o bir sat�rda kullan�ld���n� biliyoruz.

Bunun yaln�zca bir rvalue ifadesinin kabul edildi�i durumlarda �al��t���n� unutmay�n. Bir lvalue ifadesi gerekti�inde, bir 
nesnemiz olmal�d�r:

                #include <iostream>

                void addOne(int& value) // non-const referanslar� ge�mek lvalue gerektirir
                {
                    ++value;
                }

                int main()
                {
                    int sum { 5 + 3 };
                    addOne(sum);   // tamam, sum bir lvalue

                    addOne(5 + 3); // derleme hatas�: bir lvalue de�il

                    return 0;
                }
Ge�ici s�n�f nesneleri
----------------------
Ayn� sorun, s�n�f t�rleri ba�lam�nda da ge�erlidir.

Yazar�n notu

Burada bir s�n�f kullanaca��z, ancak bu dersin her �eyi, toplu ba�latma kullan�larak ba�lat�lan yap�lar i�in de ge�erlidir.
A�a��daki �rnek, yukar�dakilere benzer, ancak int yerine program taraf�ndan tan�mlanan s�n�f t�r� IntPair kullan�r:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const { return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                int main()
                {
                    // Durum 1: De�i�keni ge�
                    IntPair p { 3, 4 };
                    print(p); // (3, 4) yazar

                    return 0;
                }

Durum 1'de, IntPair p de�i�kenini �rnekliyoruz ve ard�ndan p'yi print() fonksiyonuna ge�iriyoruz. Ancak, p yaln�zca bir kez 
kullan�l�yor ve print() fonksiyonu rvalue'leri kabul edece�i i�in, burada bir de�i�ken tan�mlamak i�in ger�ekten bir neden yok.
O zaman p'den kurtulal�m.

Bunu, adland�r�lm�� bir de�i�ken yerine ge�ici bir nesne ge�irerek yapabiliriz. Ge�ici bir nesne (bazen anonim nesne veya isimsiz
nesne olarak adland�r�l�r), ad� olmayan ve yaln�zca tek bir ifade s�resince var olan bir nesnedir.

Ge�ici s�n�f tipi nesneler olu�turman�n iki yayg�n yolu vard�r:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const{ return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                int main()
                {
                    // Durum 1: De�i�keni ge�
                    IntPair p { 3, 4 };
                    print(p);

                    // Durum 2: Ge�ici IntPair olu�tur ve fonksiyona ge�
                    print(IntPair { 5, 6 } );

                    // Durum 3: { 7, 8 }'i ge�ici bir Intpair'a d�n��t�r ve fonksiyona ge�
                    print( { 7, 8 } );

                    return 0;
                }

Durum 2'de, derleyiciye bir IntPair nesnesi olu�turmas�n� ve bunu { 5, 6 } ile ba�latmas�n� s�yl�yoruz. Bu nesnenin bir ad�
olmad��� i�in bu bir ge�icidir. Ge�ici nesne daha sonra print() fonksiyonunun p parametresine ge�irilir. Fonksiyon �a�r�s�
d�nd���nde, ge�ici nesne yok edilir.

Durum 3'te, print() fonksiyonuna ge�mek �zere bir ge�ici IntPair nesnesi olu�turuyoruz. Ancak, hangi t�r� olu�turaca��m�z� a��k�a
belirtmedi�imiz i�in, derleyici gerekli t�r� (IntPair) fonksiyon parametresinden ��kar�r ve ard�ndan { 7, 8 }'i bir IntPair,
nesnesine d�n��t�r�r.

�zetlemek gerekirse:

                IntPair p { 1, 2 }; // p ad�nda bir nesne olu�tur ve { 1, 2 } de�eriyle ba�lat
                IntPair { 1, 2 };   // { 1, 2 } de�eriyle ba�lat�lan ge�ici bir nesne olu�tur
                { 1, 2 };           // derleyici { 1, 2 } de�erini ge�ici bir nesneye d�n��t�rmeye �al��acak

Bu son durumu, 14.16 -- D�n��t�rme yap�c�lar� ve explicit anahtar kelimesi dersinde daha ayr�nt�l� olarak tart��aca��z.

Ge�ici nesnelerin return de�erleriyle kullan�lmas� muhtemelen daha yayg�nd�r:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const { return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                // Durum 1: Adland�r�lm�� de�i�ken olu�tur ve return et
                IntPair ret1()
                {
                    IntPair p { 3, 4 };
                    return p;
                }

                // Durum 2: Ge�ici IntPair olu�tur ve return et
                IntPair ret2()
                {
                    return IntPair { 5, 6 };
                }

                // Durum 3: { 7, 8 }'i IntPair'a d�n��t�r ve return et
                IntPair ret3()
                {
                    return { 7, 8 };
                }

                int main()
                {
                    print(ret1());
                    print(ret2());
                    print(ret3());

                    return 0;
                }

Bu �rnekteki durumlar, �nceki �rnekteki durumlara benzer.

Birka� not

Birincisi, bir int'in durumunda oldu�u gibi, bir ifade i�inde kullan�ld���nda, ge�ici bir s�n�f nesnesi bir rvalue'dir.
Bu nedenle, bu t�r nesneler yaln�zca rvalue ifadelerinin kabul edildi�i yerlerde kullan�labilir.

�kincisi, ge�ici nesneler tan�mland��� noktada olu�turulur ve tan�mland�klar� tam ifadenin sonunda yok edilir. Tam bir ifade, 
bir alt ifade olmayan bir ifadedir.

14.14 � Kopya yap�c�ya giri�
----------------------------
A�a��daki program� d���n�n:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    void print()
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };  // Fraction(int, int) yap�c�s�n� �a��r�r
                    Fraction fCopy { f }; // Burada hangi yap�c� kullan�l�yor?

                    f.print();
                    fCopy.print();

                    return 0;
                }
Bu program�n sorunsuz bir �ekilde derlendi�ini ve �u sonucu �retti�ini g�rmek sizi �a��rtabilir:

                Fraction(5, 3)
                Fraction(5, 3)
                
Bu program�n nas�l �al��t���n� daha yak�ndan inceleyelim. f de�i�keninin ba�lat�lmas�, Fraction(int, int) yap�c�s�n� �a��ran 
standart bir s�sl� parantez ba�latmas�d�r. Peki ya sonraki sat�r? fCopy de�i�keninin ba�lat�lmas� da a��k�a bir ba�latmad�r ve 
s�n�flar� ba�latmak i�in yap�c� fonksiyonlar�n kullan�ld���n� biliyorsunuz. 

*- Peki bu sat�r hangi yap�c�y� �a��r�yor?
*- Cevap: kopya yap�c�.

Kopya Yap�c�
------------
Bir kopya yap�c�, bir nesneyi ayn� t�rdeki mevcut bir nesne ile ba�latmak i�in kullan�lan bir yap�c�d�r. Kopya yap�c� �al��t�ktan
sonra, yeni olu�turulan nesne, ba�lat�c� olarak ge�irilen nesnenin bir kopyas� olmal�d�r.

A��k Kopya Yap�c�
-----------------
S�n�flar�n�z i�in bir kopya yap�c� sa�lamazsan�z, C++ sizin i�in genel bir a��k kopya yap�c� olu�turur. Yukar�daki �rnekte,
Fraction fCopy { f }; ifadesi, fCopy'yi f ile ba�latmak i�in a��k kopya yap�c�y� �a��r�yor.

Varsay�lan olarak, a��k kopya yap�c� �yeleri ba�latma yapar. Bu, her �yenin ba�lat�c� olarak ge�irilen s�n�f�n kar��l�k gelen
�yesi kullan�larak ba�lat�laca�� anlam�na gelir. Yukar�daki �rnekte, fCopy.m_numerator, f.m_numerator (de�er 5 olan) kullan�larak
ba�lat�l�r ve fCopy.m_denominator, f.m_denominator (de�er 3 olan) kullan�larak ba�lat�l�r.

Kopya yap�c� �al��t�ktan sonra, f ve fCopy'nin �yeleri ayn� de�erlere sahiptir, bu y�zden fCopy, f'nin bir kopyas�d�r.
Bu nedenle, her ikisinde de print() �a�r�s� ayn� sonucu verir.

Kendi Kopya Yap�c�n�z� Tan�mlama
--------------------------------
Kendi kopya yap�c�m�z� da a��k�a tan�mlayabiliriz. Bu derste, kopya yap�c�m�z�n kopyalar olu�turuldu�unda ger�ekten �al��t���n�
g�sterebilmek i�in kopya yap�c�m�za bir mesaj yazd�raca��z.

Kopya yap�c�, bekledi�iniz gibi g�r�n�r:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Copy constructor
                    Fraction(const Fraction& fraction)
                        // Initialize our members using the corresponding member of the parameter
                        : m_numerator{ fraction.m_numerator }
                        , m_denominator{ fraction.m_denominator }
                    {
                        std::cout << "Copy constructor called\n"; // just to prove it works
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
                    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

                    f.print();
                    fCopy.print();

                    return 0;
                }

                Bu program �al��t�r�ld���nda, �unu al�rs�n�z:


                Copy constructor called
                Fraction(5, 3)
                Fraction(5, 3)
Yukar�da tan�mlad���m�z kopya yap�c�, varsay�lan olarak alaca��m�zla i�levsel olarak e�de�erdir, tek fark, kopya yap�c�n�n
ger�ekten �a�r�ld���n� kan�tlamak i�in bir ��kt� ifadesi eklemi� olmam�zd�r. Bu kopya yap�c�, fCopy'nin f ile ba�lat�ld���
zaman �a�r�l�r.

Bir hat�rlatma

Eri�im kontrolleri s�n�f baz�nda �al���r (nesne baz�nda de�il). Bu, bir s�n�f�n �ye fonksiyonlar�n�n ayn� t�rdeki herhangi bir
s�n�f nesnesinin �zel �yelerine eri�ebilece�i anlam�na gelir (sadece a��k nesne de�il).

Yukar�daki Fraction kopya yap�c�s�nda bunu avantaj�m�za kullan�yoruz, b�ylece fraction parametresinin �zel �yelerine do�rudan 
eri�ebiliyoruz. Aksi takdirde, bu �yelere do�rudan eri�imimiz olmazd� (eri�im fonksiyonlar� eklemek d���nda, bunu yapmak 
istemeyebiliriz).

Bir kopya yap�c�n�n bir nesneyi kopyalamaktan ba�ka bir �ey yapmamas� gerekir. Bu, derleyicinin belirli durumlarda kopya yap�c�y�
optimize edebilece�i i�indir. Kopya yap�c�ya, sadece kopyalamadan ba�ka bir davran�� i�in g�veniyorsan�z, bu davran�� olabilir 
veya olmayabilir. Bunu, 14.15 -- S�n�f ba�latma ve kopya elision dersinde daha ayr�nt�l� olarak tart��aca��z.

*** BEST -> Kopya yap�c�lar, kopyalaman�n �tesinde hi�bir yan etkiye sahip olmamal�d�r.

A��k Kopya Yap�c�y� Tercih Edin
-------------------------------
Hi�bir �ey yapmayan (ve bu y�zden nadiren istedi�imiz �ey olan) a��k varsay�lan yap�c�dan farkl� olarak, a��k kopya yap�c�n�n 
ger�ekle�tirdi�i �ye ba�latma genellikle tam olarak istedi�imiz �eydir. Bu nedenle, �o�u durumda, a��k kopya yap�c�y� kullanmak 
m�kemmel bir se�enektir.

*** BEST -> Kendi olu�turman�z i�in belirli bir nedeniniz olmad�k�a, a��k kopya yap�c�y� tercih edin.

Kopya Yap�c�n�n Parametresi Bir Referans Olmal�d�r
--------------------------------------------------
Bir kopya yap�c�n�n parametresinin bir lvalue referans� veya const lvalue referans� olmas� gereklili�idir. ��nk� kopya yap�c�n�n
parametreyi de�i�tirmemesi gerekti�i i�in, const lvalue referans� kullanmak tercih edilir.

*** BEST -> Kendi kopya yap�c�n�z� yazarsan�z, parametre const lvalue referans� olmal�d�r.

De�erden Ge�me (ve De�erden D�nme) ve Kopya Yap�c�
--------------------------------------------------
Bir nesne de�erden ge�ti�inde, arg�man parametreye kopyalan�r. Arg�man ve parametre ayn� s�n�f t�r� oldu�unda, kopya,
kopya yap�c�s�n� a��k�a �a��rarak yap�l�r. Benzer �ekilde, bir nesne de�erden d�nd�r�ld���nde, kopya yap�c�s� kopyay� yapmak
i�in a��k�a �a�r�l�r.

A�a��daki �rnekte her ikisini de g�r�yoruz:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator = 0, int denominator = 1)
                        : m_numerator{ numerator }, m_denominator{ denominator }
                    {
                    }

                    // Copy constructor
                    Fraction(const Fraction& fraction)
                        : m_numerator{ fraction.m_numerator }
                        , m_denominator{ fraction.m_denominator }
                    {
                        std::cout << "Copy constructor called\n";
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                void printFraction(Fraction f) // f is pass by value
                {
                    f.print();
                }

                Fraction generateFraction(int n, int d)
                {
                    Fraction f{ n, d };
                    return f;
                }

                int main()
                {
                    Fraction f{ 5, 3 };

                    printFraction(f); // f, kopya yap�c�s� kullan�larak fonksiyon parametresine kopyalan�r

                    Fraction f2{ generateFraction(1, 2) }; // Fraction, kopya yap�c�s� kullan�larak d�nd�r�l�r

                    printFraction(f2); // f, kopya yap�c�s� kullan�larak fonksiyon parametresine kopyalan�r

                    return 0;
                }

Yukar�daki �rnekte, printFraction(f) �a�r�s�, f'yi de�erden ge�iriyor. Kopya yap�c�, f'yi main'den printFraction fonksiyonunun
f parametresine kopyalamak i�in �a�r�l�r.

generateFraction, main'e bir Fraction d�nd�rd���nde, kopya yap�c�s� tekrar a��k�a �a�r�l�r. Ve f2, printFraction'a ge�irildi�inde,
kopya yap�c�s� ���nc� kez �a�r�l�r.

                Yazar�n makinesinde, bu �rnek �unu yazd�r�r:


                Copy constructor called
                Fraction(5, 3)
                Copy constructor called
                Copy constructor called
                Fraction(1, 2)

Yukar�daki �rne�i derleyip �al��t�r�rsan�z, kopya yap�c�n�n yaln�zca iki kez �a�r�ld���n� g�rebilirsiniz. Bu, kopya elision olarak
bilinen bir derleyici optimizasyonudur. Kopya elision'�, 14.15 -- S�n�f ba�latma ve kopya elision dersinde daha ayr�nt�l� olarak 
tart��aca��z.

Bir s�n�f�n kopya yap�c�s� yoksa, derleyici bizim i�in a��k�a bir tane olu�turur. Tercih edersek, = default s�zdizimini kullanarak
derleyiciden bizim i�in varsay�lan bir kopya yap�c� olu�turmas�n� a��k�a isteyebiliriz:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Explicitly request default copy constructor
                    Fraction(const Fraction& fraction) = default;

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };
                    Fraction fCopy { f };

                    f.print();
                    fCopy.print();

                    return 0;
                }

= delete kullanarak kopyalar� �nleme
------------------------------------
Bazen, belirli bir s�n�f�n nesnelerinin kopyalanabilir olmas�n� istemeyiz. Kopya yap�c� fonksiyonu silinmi� olarak i�aretleyerek 
bunu �nleyebiliriz, = delete s�zdizimini kullan�r�z:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Delete the copy constructor so no copies can be made
                    Fraction(const Fraction& fraction) = delete;

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };
                    Fraction fCopy { f }; // compile error: copy constructor has been deleted

                    return 0;
                }
�rnekte, derleyici fCopy'yi f ile ba�latmak i�in bir yap�c� bulmaya gitti�inde, kopya yap�c�n�n silindi�ini g�recektir.
Bu, derleyicinin bir derleme hatas� yay�nlamas�na neden olacakt�r.

Bir not�

Kopya yap�c�s�n� �zel yaparak da public s�n�f nesnesinin kopyalar�n� yapmas�n� �nleyebilirsiniz (��nk� �zel fonksiyonlar public 
taraf�ndan �a�r�lamaz). Ancak, bir �zel kopya yap�c�, s�n�f�n di�er �yelerinden �a�r�labilir, bu y�zden bu ��z�m, istenilen
durum d���nda tavsiye edilmez.
*/