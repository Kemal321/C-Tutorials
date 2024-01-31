#include <iostream>
class Something {
    int m_x{};
public:
    Something(int x)
        : m_x{ x }
    {
        std::cout << "Constructor Cagirildi. \n";
    }
    Something(const Something& s)
        :m_x{ s.m_x }
    {
        std::cout << "Copy Constructor Cagirildi.\n";
    }
    void print() const {
        std::cout << "Something(" << m_x << ")\n";
    }
};
int main()
{
    Something s{ Something{5} };
    s.print();
    return 0;
}
/*
14.15 � S�n�f ba�latma ve kopya elision
---------------------------------------
1.4 -- De�i�ken atama ve ba�latma dersinde, temel t�rlerle nesneler i�in 6 temel ba�latma t�r�n� tart���yoruz:

                int a;         // ba�lat�c� yok (varsay�lan ba�latma)
                int b = 5;     // e�ittir i�aretinden sonra ba�lat�c� (kopya ba�latma)
                int c( 6 );    // parantez i�inde ba�lat�c� (do�rudan ba�latma)

                // Liste ba�latma y�ntemleri (C++11)
                int d { 7 };   // s�sl� parantezler i�inde ba�lat�c� (do�rudan liste ba�latma)
                int e = { 8 }; // e�ittir i�aretinden sonra s�sl� parantezler i�inde ba�lat�c� (kopya liste ba�latma)
                int f {};      // ba�lat�c� bo� s�sl� parantezler (de�er ba�latma)

Bu ba�latma t�rlerinin t�m�, s�n�f t�rleriyle nesneler i�in ge�erlidir:

                #include <iostream>

                class Foo
                {
                public:

                    // Varsay�lan yap�c�
                    Foo()
                    {
                        std::cout << "Foo()\n";
                    }

                    // Normal yap�c�
                    Foo(int x)
                    {
                        std::cout << "Foo(int) " << x << '\n';
                    }

                    // Kopya yap�c�
                    Foo(const Foo&)
                    {
                        std::cout << "Foo(const Foo&)\n";
                    }
                };

                int main()
                {
                    // Foo() varsay�lan yap�c�y� �a��r�r
                    Foo f1;           // varsay�lan ba�latma
                    Foo f2{};         // de�er ba�latma (tercih edilen)

                    // foo(int) normal yap�c�y� �a��r�r
                    Foo f3 = 3;       // kopya ba�latma (yaln�zca non-explicit yap�c�lar)
                    Foo f4(4);        // do�rudan ba�latma
                    Foo f5{ 5 };      // do�rudan liste ba�latma (tercih edilen)
                    Foo f6 = { 6 };   // kopya liste ba�latma (yaln�zca non-explicit yap�c�lar)

                    // foo(const Foo&) kopya yap�c�y� �a��r�r
                    Foo f7 = f3;      // kopya ba�latma
                    Foo f8(f3);       // do�rudan ba�latma
                    Foo f9{ f3 };     // do�rudan liste ba�latma (tercih edilen)
                    Foo f10 = { f3 }; // kopya liste ba�latma

                    return 0;
                }

Modern C++'ta, kopya ba�latma, do�rudan ba�latma ve liste ba�latma esasen ayn� �eyi yapar - bir nesneyi ba�lat�rlar.

Ba�latma t�rlerinin t�m� i�in:

Bir s�n�f t�r�n� ba�lat�rken, bu s�n�f�n yap�c�lar� k�mesi incelenir ve en iyi e�le�en yap�c�y� belirlemek i�in a��r� y�k 
��z�mlemesi kullan�l�r. Bu, arg�manlar�n a��k d�n���m�n� i�erebilir.
Bir s�n�f olmayan t�r� ba�lat�rken, a��k d�n���m kurallar�, bir a��k d�n���m�n var olup olmad���n� belirlemek i�in kullan�l�r.
Anahtar Bilgi

Ba�latma bi�imleri aras�nda �� anahtar fark vard�r:

Liste ba�latma, daralt�c� d�n���mleri reddeder.
Kopya ba�latma, yaln�zca non-explicit yap�c�lar�/d�n���m fonksiyonlar�n� dikkate al�r. Bunu, 14.16 -- D�n��t�rme yap�c�lar� ve
explicit anahtar kelimesi dersinde ele alaca��z.
Liste ba�latma, di�er e�le�en yap�c�lardan ziyade e�le�en liste yap�c�lar�na �ncelik verir. Bunu, 16.2 -- std::vector'a Giri�
ve liste yap�c�lar� dersinde ele alaca��z.
Ayr�ca belirli durumlarda, belirli ba�latma bi�imlerinin kullan�lmas�n�n yasakland���n� belirtmekte fayda var (�rne�in, bir yap�c�
�ye ba�lat�c� listesinde, yaln�zca do�rudan ba�latma bi�imlerini kullanabiliriz, kopya ba�latma de�il).

Gereksiz Kopyalar
-----------------
Bu basit program� d���n�n:

                #include <iostream>

                class Something
                {
                    int m_x{};

                public:
                    Something(int x)
                        : m_x{ x }
                    {
                        std::cout << "Normal constructor\n";
                    }

                    Something(const Something& s)
                        : m_x { s.m_x }
                    {
                        std::cout << "Copy constructor\n";
                    }

                    void print() const { std::cout << "Something(" << m_x << ")\n"; }
                };

                int main()
                {
                    Something s { Something { 5 } }; // bu sat�ra odaklan�n
                    s.print();

                    return 0;
                }

Yukar�daki s de�i�keninin ba�lat�lmas�nda, �nce de�eri 5 olan bir ge�ici Something olu�turuyoruz (bu, Something(int) yap�c�s�n�
kullan�r). Bu ge�ici daha sonra s'yi ba�latmak i�in kullan�l�r. Ge�ici ve s'nin ayn� t�rde olmas� (her ikisi de Something
nesneleri oldu�u i�in), Something(const Something&) kopya yap�c�s�n�n normalde burada, ge�ici i�indeki de�erleri s'ye kopyalamak 
i�in �a�r�lmas� gerekirdi. Sonu� olarak, s de�eri 5 ile ba�lat�l�r.

Optimizasyonlar olmadan, yukar�daki program �unu yazd�r�r:

                Normal constructor
                Copy constructor
                Something(5)

Ancak, bu program gereksiz yere verimsizdir, ��nk� iki yap�c� �a�r�s� yapmam�z gerekiyor: biri Something(int) i�in, di�eri
Something(const Something&) i�in. Yukar�daki sonucun, a�a��dakini yazm�� olsayd�k ayn� olaca��n� unutmay�n:

                Something s { 5 }; // yaln�zca Something(int)'i �a��r�r, kopya yap�c� yok

Bu versiyon ayn� sonucu �retir, ancak daha verimlidir, ��nk� yaln�zca Something(int)'e bir �a�r� yapar (kopya yap�c�ya gerek
yoktur).

Kopya Elision
-------------
Derleyicinin ifadeleri optimize etmek i�in yeniden yazma �zg�rl��� oldu�undan, derleyicinin gereksiz kopyay� optimize edip 
Something s { Something{5} };'yi ba�lang��ta Something s { 5 } yazm�� gibi ele al�p alamayaca��n� merak edebilirsiniz.

Cevap evet, ve bunu yapma s�recine kopya elision denir. Kopya elision, derleyicinin gereksiz nesne kopyalamalar�n� kald�rmas�na 
izin veren bir derleyici optimizasyon tekni�idir. Di�er bir deyi�le, derleyicinin normalde bir kopya yap�c�y� �a��raca�� 
durumlarda, derleyici kodu yeniden yazarak kopya yap�c�ya yap�lan �a�r�y� tamamen �nlemekte �zg�rd�r. Derleyici, kopya yap�c�ya
yap�lan �a�r�y� optimize ederse, yap�c�n�n elided oldu�unu s�yleriz.

Di�er optimizasyon t�rlerinin aksine, kopya elision "as-if" kural�ndan muaf tutulmu�tur. Yani, kopya elision, kopya yap�c�n�n
yan etkileri olsa bile (�rne�in, konsola metin yazd�rma) kopya yap�c�y� elide etmeye izin verir! Bu, kopya yap�c�lar�n
kopyalamadan ba�ka yan etkileri olmamas� gerekti�i nedenidir - e�er derleyici kopya yap�c�ya yap�lan �a�r�y� eliderse, 
yan etkiler ger�ekle�mez ve program�n g�zlemlenebilir davran��� de�i�ir!

Bunu yukar�daki �rnekte g�rebiliriz. Program� bir C++17 derleyicisinde �al��t�r�rsan�z, a�a��daki sonucu �retir:

                Normal constructor
                Something(5)

Derleyici, gereksiz bir kopyay� �nlemek i�in kopya yap�c�y� elided etmi�tir ve sonu� olarak, "Kopya yap�c�" yazd�ran ifade
�al��t�r�lmam��t�r! Program�m�z�n g�zlemlenebilir davran���, kopya elision nedeniyle de�i�ti!

De�erden Ge�me ve De�erden D�nme'de Kopya Elision
-------------------------------------------------
Kopya yap�c�, parametrenin ayn� t�rdeki bir arg�man�n de�erden ge�ti�i veya de�erden d�nme kullan�ld���nda normalde �a�r�l�r.
Ancak, belirli durumlarda, bu kopyalar elided olabilir. A�a��daki program, bu durumlar�n baz�lar�n� g�sterir:

                #include <iostream>
                class Something
                {
                public:
                    Something() = default;
                    Something(const Something&)
                    {
                        std::cout << "Copy constructor called\n";
                    }
                };

                Something rvo()
                {
                    return Something{}; // Something() ve kopya yap�c�y� �a��r�r
                }

                Something nrvo()
                {
                    Something s{}; // Something() �a��r�r
                    return s;      // kopya yap�c�y� �a��r�r
                }

                int main()
                {
                    std::cout << "Initializing s1\n";
                    Something s1 { rvo() }; // kopya yap�c�y� �a��r�r

                    std::cout << "Initializing s2\n";
                    Something s2 { nrvo() }; // kopya yap�c�y� �a��r�r

                        return 0;
                }

Optimizasyon olmadan, yukar�daki program kopya yap�c�y� 4 kez �a��r�r:

*- rvo, Something'i main'e d�nd�rd���nde bir kez.
*- rvo()'nun d�n�� de�eri s1'i ba�latmak i�in kullan�ld���nda bir kez.
*- nrvo, s'yi main'e d�nd�rd���nde bir kez.
*- nrvo()'nun d�n�� de�eri s2'yi ba�latmak i�in kullan�ld���nda bir kez.
Ancak, kopya elision nedeniyle, derleyicinizin bu kopya yap�c� �a�r�lar�n�n �o�unu veya t�m�n� elide etmesi muhtemeldir.
Visual Studio 2022, 3 durumu elider (nrvo()'nun de�erden d�nd��� durumu elide etmez) ve GCC hepsini elider.

Derleyicinin ne zaman kopya elision yapaca��n� / yapmayaca��n� ezberlemeniz �nemli de�ildir. Sadece, derleyicinizin bunu
yapabilece�i bir optimizasyon oldu�unu bilin ve kopya yap�c�n�z�n �a�r�lmas�n� bekliyorsan�z ve �a�r�lmazsa, muhtemelen nedeni
kopya elision'd�r.

Kopya elision hatalar�
----------------------
C++17'den �nce, kopya elision kesinlikle derleyicilerin yapabilece�i iste�e ba�l� bir optimizasyondu. C++17'de, kopya elision baz�
durumlarda zorunlu hale geldi.

�ste�e ba�l� elision durumlar�nda, eri�ilebilir bir kopya yap�c� mevcut olmal�d�r (�r. silinmemi�), ger�ek kopya yap�c� �a�r�s�
elided olsa bile.

Zorunlu elision durumlar�nda, eri�ilebilir bir kopya yap�c� mevcut olmak zorunda de�ildir (di�er bir deyi�le, zorunlu elision,
kopya yap�c� silinmi� olsa bile ger�ekle�ebilir).

14.16 � D�n��t�rme Yap�c�s� ve explicit anahtar kelimesi
--------------------------------------------------------
10.1 dersinde -- �mplicit t�r d�n���m�, t�r d�n���m�n� ve derleyicinin gerekti�i gibi bir t�r�n de�erini ba�ka bir t�r�n de�erine
implicit olarak d�n��t�rece�i implicit t�r d�n���m� kavram�n� tan�tt�k.

Bu, bize �unlar� yapma imkan� verir:

                #include <iostream>

                void printDouble(double d) // bir double parametresi var
                {
                    std::cout << d;
                }

                int main()
                {
                    printDouble(5); // bir int arg�man� sa�l�yoruz

                    return 0;
                }

Yukar�daki �rnekte, printDouble fonksiyonumuzun bir double parametresi var, ancak biz bir int arg�man� ge�iriyoruz. Parametrenin 
t�r� ile arg�man�n t�r� e�le�medi�inde, derleyici arg�man�n t�r�n� parametrenin t�r�ne d�n��t�r�p d�n��t�remeyece�ini g�recektir.
Bu durumda, say�sal d�n���m kurallar�n� kullanarak, int de�eri 5, double de�eri 5.0'a d�n��t�r�l�r ve de�eri ge�ti�imiz i�in,
parametre d bu de�erle kopya ba�lat�l�r.

Kullan�c� tan�ml� d�n���mler
----------------------------
�imdi a�a��daki benzer �rne�i d���n�n:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                public:
                    Foo(int x)
                        : m_x{ x }
                    {
                    }

                    int getX() const { return m_x; }
                };

                void printFoo(Foo f) // bir Foo parametresi var
                {
                    std::cout << f.getX();
                }

                int main()
                {
                    printFoo(5); // bir int arg�man� sa�l�yoruz

                    return 0;
                }

Bu versiyonda, printFoo'nun bir Foo parametresi var ama biz bir int arg�man� ge�iriyoruz. Bu t�rler e�le�medi�i i�in, 
derleyici int de�eri 5'i bir Foo nesnesine d�n��t�rmeye �al��acak, b�ylece fonksiyon �a�r�labilir.

�lk �rnekte oldu�u gibi, parametre ve arg�man t�rlerimiz her ikisi de temel t�rlerdi (ve bu nedenle yerle�ik say�sal 
tan�t�m/d�n���m kurallar�n� kullanarak d�n��t�r�lebilir), bu durumda t�rlerimizden biri bir program tan�ml� t�rd�r.
C++ standard�, derleyicinin de�erleri bir program tan�ml� t�re (veya ondan) nas�l d�n��t�rece�ini s�yleyen belirli kurallara sahip
de�ildir.

Bunun yerine, derleyici, b�yle bir d�n���m� ger�ekle�tirmek i�in kullanabilece�i baz� fonksiyonlar� tan�mlay�p tan�mlamad���m�z� 
g�rmek i�in bakar. B�yle bir fonksiyon, kullan�c� tan�ml� bir d�n���m olarak adland�r�l�r.

D�n��t�rme Yap�c�s�
-------------------
Yukar�daki �rnekte, derleyici int de�eri 5'i bir Foo nesnesine d�n��t�rmeyi sa�layan bir fonksiyon bulacak. Bu fonksiyon,
Foo(int) yap�c�s�d�r.

Bu noktaya kadar, genellikle yap�c�lar� nesneleri a��k�a olu�turmak i�in kullan�yoruz:

                Foo x { 5 }; // A��k�a int de�eri 5'i bir Foo'ya d�n��t�r

Bunu ne yapt���n� d���n�n: bir int de�eri (5) sa�l�yoruz ve kar��l���nda bir Foo nesnesi al�yoruz.

Bir fonksiyon �a�r�s� ba�lam�nda, ayn� problemi ��zmeye �al���yoruz:

                printFoo(5); // Implicit olarak int de�eri 5'i bir Foo'ya d�n��t�r

Bir int de�eri (5) sa�l�yoruz ve kar��l���nda bir Foo nesnesi istiyoruz. Foo(int) yap�c�s� tam olarak bunun i�in tasarland�!
Bu y�zden bu durumda, printFoo(5) �a�r�ld���nda, parametre f, 5 arg�man�yla Foo(int) yap�c�s� kullan�larak kopya ba�lat�l�r!
Bir implicit d�n���m ger�ekle�tirmek i�in kullan�labilecek bir yap�c�ya d�n��t�rme yap�c�s� denir. Varsay�lan olarak, 
t�m yap�c�lar d�n��t�rme yap�c�s�d�r.

Sadece bir kullan�c� tan�ml� d�n���m uygulanabilir. Ne demek istedi�imizi bir �rnekle anlatal�m.

A�a��daki �rne�i d���n�n:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                    }

                    const std::string& getName() const { return m_name; }
                };

                void printEmployee(Employee e) // bir Employee parametresi var
                {
                    std::cout << e.getName();
                }

                int main()
                {
                    printEmployee("Joe"); // bir string literal arg�man� sa�l�yoruz

                    return 0;
                }

Bu versiyonda, Foo s�n�f�m�z� bir Employee s�n�f� ile de�i�tirdik. printEmployee'�n bir Employee parametresi var ve biz bir
C-style string literal ge�iriyoruz. Ve bir d�n��t�r�c� yap�c�ya sahibiz: Employee(std::string_view).

Bu versiyonun derlenmedi�ini g�rmek sizi �a��rtabilir. Sebep basit: bir implicit d�n���m� ger�ekle�tirmek i�in sadece bir 
kullan�c� tan�ml� d�n���m uygulanabilir ve bu �rnekte iki tanesi gereklidir. �ncelikle, C-style string literalimizin bir
std::string_view'a d�n��t�r�lmesi gerekiyor (bir std::string_view d�n��t�r�c� yap�c� kullanarak), ve sonra std::string_view'imizin
bir Employee'ye d�n��t�r�lmesi gerekiyor (Employee(std::string_view) d�n��t�r�c� yap�c� kullanarak).

Bu �rne�i �al��t�rman�n iki yolu vard�r:

Bir std::string_view literal kullan�n:

                int main()
                {
                    using namespace std::literals;
                    printEmployee( "Joe"sv); // �imdi bir std::string_view literal

                    return 0;
                }

Bu �al���r ��nk� art�k sadece bir kullan�c� tan�ml� d�n���m gereklidir (std::string_view'dan Employee'ye).

Bir Employee'yi implicit olarak olu�turmak yerine explicit olarak olu�turun:

                int main()
                {
                    printEmployee(Employee{ "Joe" });

                    return 0;
                }

Bu da �al���r ��nk� art�k sadece bir kullan�c� tan�ml� d�n���m gereklidir (string literal'den Employee nesnesini ba�latmak i�in
kullan�lan std::string_view'a). Fonksiyona explicit olarak olu�turulmu� Employee nesnemizi ge�mek, ikinci bir d�n���m�n
ger�ekle�mesini gerektirmez.

Bu son �rnek, kullan��l� bir tekni�i ortaya ��kar�r: bir implicit d�n���m� explicit bir tan�ma d�n��t�rmek basittir. 
Bu dersin ilerleyen b�l�mlerinde bunun daha fazla �rne�ini g�rece�iz.

Anahtar nokta �udur, Bir implicit d�n���m, direkt liste ba�latma (veya direkt ba�latma) kullan�larak basit�e explicit bir tan�ma 
d�n��t�r�lebilir.

D�n��t�r�c� yap�c�lar yanl�� gitti�inde

A�a��daki program� d���n�n:


                #include <iostream>

                class Dollars
                {
                private:
                    int m_dollars{};

                public:
                    Dollars(int d)
                        : m_dollars{ d }
                    {
                    }

                    int getDollars() const { return m_dollars; }
                };

                void print(Dollars d)
                {
                    std::cout << "$" << d.getDollars();
                }

                int main()
                {
                    print(5);

                    return 0;
                }

print(5) �a�r�ld���nda, Dollars(int) d�n��t�r�c� yap�c�, 5'i bir Dollars nesnesine d�n��t�rmek i�in kullan�lacakt�r. Bu y�zden,
bu program �unu yazd�r�r:
                $5

Bu, �a��r�c�n�n niyeti olabilir, ancak �a��r�c�n�n bunu ger�ekten istedi�ine dair herhangi bir belirti sa�lamamas� nedeniyle bunu
anlamak zordur. �a��r�c�n�n bunun 5'i yazd�raca��n� varsayd��� ve derleyicinin bizim int de�erimizi sessizce ve implicit olarak
bir Dollars nesnesine d�n��t�rmesini, bu fonksiyon �a�r�s�n� kar��layabilecek �ekilde beklemedi�i tamamen m�mk�nd�r.

Bu �rnek basitken, daha b�y�k ve daha karma��k bir programda, derleyicinin beklenmedik bir implicit d�n���m ger�ekle�tirdi�i ve
�al��ma zaman�nda beklenmedik bir davran��a yol a�t��� olduk�a kolayd�r.

print(Dollars) fonksiyonumuzun yaln�zca bir Dollars nesnesi ile �a�r�labilmesi, herhangi bir de�erin implicit olarak Dollars'a 
d�n��t�r�lebilece�i (�zellikle int gibi temel bir t�r) daha iyi olurdu. Bu, istemeden hatalar�n olu�ma olas�l���n� azalt�r.

"explicit" anahtar kelimesi
---------------------------
Bu t�r sorunlar� ��zmek i�in, bir yap�c�y� d�n��t�rme yap�c�s� olarak kullan�lmamas� gerekti�ini derleyiciye s�ylemek i�in
explicit anahtar kelimesini kullanabiliriz.

Bir yap�c�y� explicit yapmak iki �nemli sonu� do�urur:

1- A��k bir yap�c�, kopya ba�latma veya kopya listesi ba�latma yapmak i�in kullan�lamaz.
2- A��k bir yap�c�, dolayl� d�n���mler yapmak i�in kullan�lamaz (��nk� bu, kopya ba�latma veya kopya listesi ba�latmay� kullan�r).

�nceki �rnekteki Dollars(int) yap�c�s�n� bir a��k yap�c� olacak �ekilde g�ncelleyelim:

                #include <iostream>

                class Dollars
                {
                private:
                    int m_dollars{};

                public:
                    explicit Dollars(int d) // �imdi a��k
                        : m_dollars{ d }
                    {
                    }

                    int getDollars() const { return m_dollars; }
                };

                void print(Dollars d)
                {
                    std::cout << "$" << d.getDollars();
                }

                int main()
                {
                    print(5); // derleme hatas� ��nk� Dollars(int) a��k

                    return 0;
                }

Derleyici art�k Dollars(int)'i bir d�n��t�rme yap�c�s� olarak kullanamad��� i�in, 5'i bir Dollars'a d�n��t�rmenin bir yolunu
bulamaz. Sonu� olarak, bir derleme hatas� olu�turacakt�r.

A��k yap�c�lar do�rudan ve liste ba�latma i�in kullan�labilir

Bir a��k yap�c� hala do�rudan ve do�rudan liste ba�latma i�in kullan�labilir:

                // Dollars(int)'in a��k oldu�unu varsayal�m
                int main()
                {
                    Dollars d1(5); // tamam
                    Dollars d2{5}; // tamam
                }
�imdi, �nceki �rne�imize d�nelim, burada Dollars(int) yap�c�m�z� a��k yapt�k ve bu nedenle a�a��daki bir derleme hatas� olu�turdu:

                print(5); // derleme hatas� ��nk� Dollars(int) a��k

Peki ya asl�nda print() fonksiyonunu int de�eri 5 ile �a��rmak istiyoruz ama yap�c� a��ksa ne yapmal�y�z ? 
��z�m basit: derleyicinin 5'i print()'e ge�irilebilecek bir Dollars'a dolayl� olarak d�n��t�rmesi yerine, Dollars nesnesini 
kendimiz a��k�a tan�mlayabiliriz:

                print(Dollars{5}); // tamam: Dollars olu�tur ve print()'e ge�ir (d�n���m gerekli de�il)

Bu, hala a��k yap�c�lar� liste ba�latma nesneleri i�in kullanabildi�imiz i�in m�mk�nd�r. Ve art�k a��k�a bir Dollars 
olu�turdu�umuzdan, arg�man t�r� parametre t�r�yle e�le�ir, bu y�zden d�n���m gerekmez!

Bu sadece derlenir ve �al���r, ayr�ca niyetimizi daha iyi belgeler, ��nk� bu fonksiyonu bir Dollars nesnesi ile �a��rmay� 
d���nd���m�z konusunda a��kt�r.

De�er d�nd�rme ve a��k yap�c�lar
--------------------------------
Bir fonksiyondan bir de�er d�nd�rd���m�zde, bu de�er fonksiyonun d�n�� t�r�yle e�le�miyorsa, dolayl� bir d�n���m ger�ekle�ir.
De�er ge�irme ile ayn� �ekilde, bu t�r d�n���mler a��k yap�c�lar� kullanamaz.

A�a��daki programlar, d�n�� de�erlerinde birka� varyasyonu ve sonu�lar�n� g�sterir:

                #include <iostream>

                class Foo
                {
                public:
                    explicit Foo() // not: a��k (sadece �rnek olmas� i�in)
                    {
                    }

                    explicit Foo(int x) // not: a��k
                    {
                    }
                };

                Foo getFoo()
                {
                    // explicit Foo() durumlar�
                    return Foo{ };   // tamam
                    return { };      // hata: ba�lat�c� listeyi Foo'ya dolayl� olarak d�n��t�remez

                    // explicit Foo(int) durumlar�
                    return 5;        // hata: int'i Foo'ya dolayl� olarak d�n��t�remez
                    return Foo{ 5 }; // tamam
                    return { 5 };    // hata: ba�lat�c� listeyi Foo'ya dolayl� olarak d�n��t�remez
                }

                int main()
                {
                    return 0;
                }

Belki de �a��rt�c� bir �ekilde, return { 5 } bir d�n���m olarak kabul edilir.

"explicit" kullan�m� i�in en iyi uygulamalar
--------------------------------------------
Modern en iyi uygulama, tek bir arg�man kabul edecek herhangi bir yap�land�r�c�y� varsay�lan olarak a��k yapmakt�r. 
Bu, �o�u veya t�m� varsay�lan de�erlere sahip olan birden fazla parametreli yap�land�r�c�lar� i�erir.

Bu, derleyicinin bu yap�land�r�c�y� implicit d�n���mler i�in kullanmas�n� engeller. Bir d�n���m gerekiyorsa, yaln�zca a��k olmayan
yap�land�r�c�lar dikkate al�n�r. D�n���m� ger�ekle�tirmek i�in hi�bir a��k olmayan yap�land�r�c� bulunamazsa, derleyici hata verir

B�yle bir d�n���m�n belirli bir durumda ger�ekten istenmesi durumunda, implicit d�n���m� liste ba�latma kullanarak a��k bir tan�ma
d�n��t�rmek basittir.

A�a��dakiler a��k yap�lmamal�d�r:

*- Kopya (ve ta��ma) yap�land�r�c�lar� (��nk� bunlar d�n���m ger�ekle�tirmez).
*- Parametresi olmayan varsay�lan yap�land�r�c�lar (��nk� bunlar yaln�zca {}'yi varsay�lan bir nesneye d�n��t�rmek i�in kullan�l�r,
   k�s�tlamam�z gereken bir �ey de�il).
*- Yaln�zca birden �ok arg�man kabul eden yap�land�r�c�lar (��nk� bunlar genellikle d�n���mler i�in aday de�ildir).
*- Tek arg�manl� bir yap�land�r�c�y� a��k olmayan yapmak anlaml� oldu�u baz� durumlar vard�r. A�a��dakilerin t�m� do�ru oldu�unda
   bu yararl� olabilir:

*- D�n��t�r�len de�er, arg�man de�eri ile semantik olarak e�de�erdir.
*- D�n���m performansl�d�r.
*- �rne�in, bir C-stil dize arg�man�n� kabul eden std::string_view yap�land�r�c�s� a��k de�ildir, ��nk� bir C-stil dizenin bir
   std::string_view olarak kabul edilmesi durumunda sorun olmayaca�� olas� bir durum olmas� pek olas� de�ildir.

Buna kar��l�k, bir std::string_view al�rken std::string yap�land�r�c�s� a��k olarak i�aretlenmi�tir, ��nk� bir std::string de�eri bir std::string_view de�eri ile semantik olarak e�de�er olsa da, bir std::string olu�turmak performansl� de�ildir.
*** BEST -> Tek bir arg�man kabul eden herhangi bir yap�land�r�c�y� varsay�lan olarak a��k yap�n. E�er t�rler aras�nda 
            hem semantik olarak e�de�er hem de performansl� bir implicit d�n���m varsa, yap�land�r�c�y� a��k olmayan yapmay� 
            d���nebilirsiniz. Kopya veya ta��ma yap�land�r�c�lar�n� a��k yapmay�n, ��nk� bunlar d�n���m ger�ekle�tirmez.

14.x - B�l�m 14 �zeti
---------------------
Bu b�l�mde, C++'�n etini ke�fettik - s�n�flar! Bu, ��retici serideki en �nemli b�l�md�r, ��nk� geriye kalan �ok �ey i�in sahneyi 
haz�rlar.

B�l�m �ncelemesi

��lemsel programlamada, odak noktam�z, program mant���m�z� uygulayan "prosed�rler" olu�turmakt�r (C++'da bunlara fonksiyonlar 
denir). Veri nesnelerini bu fonksiyonlara ge�eriz, bu fonksiyonlar veriler �zerinde i�lemler ger�ekle�tirir ve ard�ndan potansiyel
olarak bir sonu� d�nd�r�rler.

Nesne y�nelimli programlama (genellikle OOP olarak k�salt�l�r) ile odak noktam�z, hem �zellikler hem de iyi tan�mlanm�� 
davran��lar i�eren program tan�ml� veri t�rleri olu�turmakt�r.

Bir s�n�f de�i�mezi, bir nesnenin ge�erli bir durumda kalmas� i�in nesnenin �mr� boyunca do�ru olmas� gereken bir durumdur.
S�n�f de�i�mezli�i ihlal edilmi� bir nesne, ge�ersiz bir durumda oldu�u s�ylenir ve bu nesnenin daha fazla kullan�lmas�ndan 
beklenmedik veya tan�ms�z davran��lar ortaya ��kabilir.

Bir s�n�f, hem veri hem de bu veri �zerinde �al��an fonksiyonlar� paketleyen bir program tan�ml� bile�ik t�rd�r.

Bir s�n�f t�r�ne ait olan fonksiyonlara �ye fonksiyonlar denir. �ye fonksiyonun �a�r�ld��� nesne genellikle implicit nesne olarak
adland�r�l�r. �ye fonksiyon olmayan fonksiyonlara, �ye fonksiyonlardan ay�rt etmek i�in �ye olmayan fonksiyonlar denir. 
E�er s�n�f t�r�n�z�n veri �yeleri yoksa, bir ad alan� kullanmay� tercih edin.

Bir const �ye fonksiyonu, nesneyi de�i�tirmeyece�ini veya herhangi bir const olmayan �ye fonksiyonu �a��rmayaca��n� 
(��nk� bunlar nesneyi de�i�tirebilir) garanti eden bir �ye fonksiyondur. Bir �ye fonksiyon, nesnenin durumunu de�i�tirmiyor 
(ve asla de�i�tirmeyecek) ise, const yap�lmal�d�r, b�ylece hem const olmayan hem de const nesneler �zerinde �a�r�labilir.

Bir s�n�f t�r�n�n her bir �yesinin, o �yeye kimlerin eri�ebilece�ini belirleyen bir eri�im d�zeyi ad� verilen bir �zelli�i vard�r.
Eri�im d�zeyi sistemi bazen gayri resmi olarak eri�im kontrolleri olarak adland�r�l�r. Eri�im d�zeyleri, s�n�f baz�nda tan�mlan�r,
nesne baz�nda de�il.

Public �yeler, eri�imleri �zerinde herhangi bir k�s�tlama olmayan bir s�n�f t�r�n�n �yeleridir. Public �yelere herkes taraf�ndan
eri�ilebilir (kapsamlar� s�rece). Bu, ayn� s�n�f�n di�er �yelerini de i�erir. Public �yelere ayr�ca public taraf�ndan da
eri�ilebilir, bu da belirli bir s�n�f t�r�n�n �yeleri d���nda var olan kodu ifade eder. Public'in �rnekleri aras�nda �ye olmayan 
fonksiyonlar ve di�er s�n�f t�rlerinin �yeleri bulunur.

Varsay�lan olarak, bir struct'�n t�m �yeleri public �yelerdir.

Private �yeler, yaln�zca ayn� s�n�f�n di�er �yeleri taraf�ndan eri�ilebilen bir s�n�f t�r�n�n �yeleridir.

Varsay�lan olarak, bir s�n�f�n �yeleri private'dir. Private �yelere sahip bir s�n�f art�k bir topluluk de�ildir ve bu nedenle 
topluluk ba�latmas�n� kullanamaz. Private �yelerinizi, onlar� yerel de�i�kenlerin, fonksiyon parametrelerinin ve �ye
fonksiyonlar�n�n adlar�ndan ay�rt etmeye yard�mc� olmak i�in "m_" �nekiyle ba�layacak �ekilde adland�rmay� d���n�n.

�yelerimizin eri�im d�zeyini, bir eri�im belirleyici kullanarak a��k�a belirleyebiliriz. Struct'lar genellikle eri�im 
belirleyicilerini kullanmaktan ka��nmal�d�r, b�ylece t�m �yeler varsay�lan olarak public olur.

Bir eri�im fonksiyonu, private bir �ye de�i�kenin de�erini almak veya de�i�tirmek olan basit bir public �ye fonksiyonudur.
Eri�im fonksiyonlar� iki �e�ittir: getter'lar ve setter'lar. Getter'lar (bazen eri�im sa�lay�c�lar olarak da adland�r�l�r)
private bir �ye de�i�kenin de�erini d�nd�ren public �ye fonksiyonlar�d�r. Setter'lar (bazen de�i�tiriciler olarak da adland�r�l�r)
private bir �ye de�i�kenin de�erini ayarlayan public �ye fonksiyonlar�d�r.

Bir s�n�f t�r�n�n aray�z�, bir s�n�f t�r�n�n kullan�c�s�n�n s�n�f t�r�n�n nesneleriyle nas�l etkile�ime girece�ini tan�mlar.
Yaln�zca public �yelere s�n�f t�r�n�n d���ndan eri�ilebildi�inden, bir s�n�f t�r�n�n public �yeleri aray�z�n� olu�turur. 
Bu nedenle, public �yelerden olu�an bir aray�z bazen public aray�z olarak adland�r�l�r.

Bir s�n�f t�r�n�n uygulamas�, s�n�f�n ama�land��� gibi davranmas�n� sa�layan kodu i�erir. Bu, hem veri depolayan �ye de�i�kenleri 
hem de program mant���n� i�eren ve �ye de�i�kenleri manip�le eden �ye fonksiyonlar�n�n g�vdelerini i�erir.

Programlamada, veri gizleme (ayn� zamanda bilgi gizleme veya veri soyutlama olarak da adland�r�l�r) bir tekniktir ve
kullan�c�lar�n bir program tan�ml� veri t�r�n�n uygulamas�n� gizleyerek aray�z ve uygulaman�n ayr�m�n� sa�lar.

Encapsulation terimi bazen veri gizlemeyi ifade etmek i�in de kullan�l�r. Ancak, bu terim ayn� zamanda verilerin ve fonksiyonlar�n
bir araya getirilmesini (eri�im kontrollerine bak�lmaks�z�n) ifade etmek i�in de kullan�l�r, bu y�zden kullan�m� belirsiz olabilir

Bir s�n�f tan�mlarken, public �yelerinizi ilk olarak ve private �yelerinizi son olarak bildirmeyi tercih edin. Bu, public aray�z�
�ne ��kar�r ve uygulama ayr�nt�lar�n� �nemsizle�tirir.

Bir constructor, s�n�f t�r� nesnelerini ba�latmak i�in kullan�lan �zel bir �ye fonksiyondur. Bir non-aggregate s�n�f t�r� nesnesi
olu�turmak i�in e�le�en bir constructor bulunmal�d�r.

�ye ba�lat�c� listesi, bir constructor i�inde �ye de�i�kenlerinizi ba�latman�za olanak sa�lar. �ye ba�lat�c� listesindeki �ye 
de�i�kenler, s�n�fta tan�mland�klar� s�raya g�re listelenmelidir. �yelerinizi ba�latmak i�in �ye ba�lat�c� listesini kullanmay�,
constructor'�n g�vdesinde de�erler atamaya tercih edin.

Parametre almayan bir yap�c� (veya t�m varsay�lan parametrelere sahip olan) varsay�lan yap�c� olarak adland�r�l�r.
Varsay�lan yap�c�, kullan�c� taraf�ndan ba�latma de�erleri sa�lanmad���nda kullan�l�r. Bir topluluk olmayan s�n�f t�r� nesnesinin
kullan�c� taraf�ndan bildirilen yap�c�lar� yoksa, derleyici bir varsay�lan yap�c� olu�turur (b�ylece s�n�f de�er veya varsay�lan
ba�latma yap�labilir). Bu yap�c�ya dolayl� varsay�lan yap�c� denir.

Yap�c�lar, ba�latmay� ayn� s�n�f t�r�nden ba�ka bir yap�c�ya devretmeye izin verir. Bu s�rece bazen yap�c� zincirleme denir ve bu
t�r yap�c�lara devreden yap�c�lar denir. Yap�c�lar devredebilir veya ba�latabilir, ancak her ikisini birden yapamazlar.

Ge�ici bir nesne (bazen anonim nesne veya isimsiz nesne olarak adland�r�l�r) ismi olmayan ve yaln�zca tek bir ifade s�resince var
olan bir nesnedir.

Bir kopya yap�c�s�, bir nesneyi ayn� t�rden mevcut bir nesne ile ba�latmak i�in kullan�lan bir yap�c�d�r. S�n�flar�n�z i�in bir 
kopya yap�c�s� sa�lamazsan�z, C++ sizin i�in �ye ba�latma yapan genel bir dolayl� kopya yap�c�s� olu�turur.

As-if kural�, derleyicinin bir program� daha optimize bir kod �retmek i�in istedi�i gibi de�i�tirebilece�ini s�yler, yeter ki bu
de�i�iklikler bir program�n "g�zlemlenebilir davran���n�" etkilemesin. As-if kural�n�n bir istisnas� kopya elizyondur. Kopya 
elizyon, derleyicinin gereksiz nesne kopyalamalar�n� kald�rmas�na izin veren bir derleyici optimizasyon tekni�idir. Derleyici,
kopya yap�c�ya bir �a�r�y� optimize ederse, yap�c�n�n elizyon oldu�unu s�yleriz.

Bir de�eri bir program tan�ml� t�r�ne d�n��t�rmek i�in yazd���m�z bir fonksiyon, kullan�c� tan�ml� d�n���m olarak adland�r�l�r.
Dolayl� bir d�n���m ger�ekle�tirmek i�in kullan�labilecek bir yap�c�ya d�n��t�rme yap�c�s� denir. Varsay�lan olarak, t�m yap�c�lar
d�n��t�rme yap�c�s�d�r.

Derleyiciye bir yap�c�n�n d�n��t�rme yap�c�s� olarak kullan�lmamas� gerekti�ini s�ylemek i�in "explicit" anahtar kelimesini 
kullanabiliriz. B�yle bir yap�c�, kopya ba�latma veya kopya listesi ba�latma yapmak i�in kullan�lamaz, ayr�ca dolayl� d�n���mler 
yapmak i�in de kullan�lamaz.

Tek bir arg�man kabul eden herhangi bir yap�c�y� varsay�lan olarak explicit yap�n. E�er t�rler aras�nda hem semantik olarak
e�de�er hem de performansl� bir dolayl� d�n���m varsa (std::string'den std::string_view'a d�n���m gibi), yap�c�y� a��k olmayan
yapmay� d���nebilirsiniz. Kopya veya ta��ma yap�c�lar� a��k yapmay�n, ��nk� bunlar d�n���m yapmaz.
*/