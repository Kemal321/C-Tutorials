#include <iostream>

int main()
{
	return 0;
}
/*

Rvalue olarak ge�irilen bir const referans� const referans ile geri d�nd�rmek uygun bir davran��t�r
---------------------------------------------------------------------------------------------------
Bir const referans parametresi i�in bir arg�man bir rvalue oldu�unda, bu parametreyi yine const referans ile d�nd�rmek uygun bir 
davran��t�r. Bu, rvaluelar�n olu�turulduklar� tam ifadenin sonuna kadar yok edilmedi�i i�in ge�erlidir. �lk olarak, a�a��daki
�rne�e bir g�z atal�m:

                    #include <iostream>
                    #include <string>

                    std::string getHello()
                    {
                        return std::string{"Hello"};
                    }

                    int main()
                    {
                        const std::string s{ getHello() };

                        std::cout << s;

                        return 0;
                    }
Bu durumda, getHello() fonksiyonu bir std::string'i de�er olarak d�nd�r�yor, ki bu bir rvalue'dir. Bu rvalue daha sonra s'yi
ba�latmak i�in kullan�l�r. s'nin ba�lat�lmas�ndan sonra, rvalue'�n olu�turuldu�u ifade de�erlendirmeyi tamamlar ve rvalue yok 
edilir.

�imdi benzer bir �rne�e bakal�m:
                    #include <iostream>
                    #include <string>

                    const std::string& foo(const std::string &s)
                    {
                        return s;
                    }

                    std::string getHello()
                    {
                        return std::string{"Hello"};
                    }

                    int main()
                    {
                        const std::string s{ foo(getHello()) };

                        std::cout << s;

                        return 0;
                    }

Bu durumda tek fark, rvalue'�n const referans ile foo() fonksiyonuna iletilmesi ve ard�ndan s'yi ba�latmak i�in kullan�lmadan
�nce �a�r�y� geri d�nd�rmesidir. Di�er her �ey ayn� �ekilde �al���r.


�a��ran fonksiyon referans �zerinden de�erleri de�i�tirebilir

Bir arg�man, bir fonksiyona const olmayan referans ile iletildi�inde, fonksiyon referans� kullanarak arg�man�n de�erini 
de�i�tirebilir.

Benzer �ekilde, bir fonksiyondan const olmayan bir referans d�nd�r�ld���nde, �a��ran fonksiyon geri d�nd�r�len de�eri de�i�tirmek
i�in referans� kullanabilir.

��te bunu g�steren a��klay�c� bir �rnek:

                    #include <iostream>

                    // non-const ile 2 parametre al�yor, ve b�y�k olan parametreyi referans ile d�nd�r�yor
                    int& max(int& x, int& y)
                    {
                        return (x > y) ? x : y;
                    }

                    int main()
                    {
                        int a{ 5 };
                        int b{ 6 };

                        max(a, b) = 7; // a yada b den b�y�k olan�n� 7 olarak ayarlar

                        std::cout << a << b << '\n';

                        return 0;
                    }

Yukar�daki programda, max(a, b) ifadesi a ve b arg�manlar� ile max() fonksiyonunu �a��r�r. Referans parametre x, arg�man a'ya 
ba�lan�r ve referans parametre y, arg�man b'ye ba�lan�r. Fonksiyon daha sonra x (5) ve y (6) aras�nda hangisinin daha b�y�k
oldu�unu belirler. Bu durumda, bu y'dir, bu nedenle fonksiyon y'yi (hala b'ye ba�l� olan) �a��ran fonksiyona geri d�nd�r�r. 
�a��ran fonksiyon daha sonra bu d�nd�r�len referansa de�eri 7 olarak atar.

Bu nedenle, max(a, b) = 7 ifadesi etkili bir �ekilde b = 7'ye ��z�l�r.

Bu �u �ekilde yazd�r�l�r:
                    57
Adrese g�re d�n��
-----------------
Adrese g�re d�n��, neredeyse referansa g�re d�n��le ayn� �ekilde �al���r, ancak bir nesnenin referans� yerine bir nesnenin
i�aret�isi d�nd�r�l�r. Adrese g�re d�n���n referansa g�re d�n��le ayn� temel sak�ncas� vard�r -- adrese g�re d�nd�r�len nesnenin, 
adresi d�nd�ren fonksiyonun kapsam�ndan �nce ya�am�� olmas� gerekir, aksi takdirde �a�r�lan taraf bir sark�k i�aret�i alacakt�r.

Adrese g�re d�n���n referansa g�re d�n��e kar�� b�y�k avantaj�, fonksiyonun d�nd�r�lecek ge�erli bir nesne olmad���nda nullptr 
d�nd�rebilmemizdir. �rne�in, aramak istedi�imiz bir ��renci listemiz oldu�unu varsayal�m. ��renciyi listede bulursak, e�le�en
��renciyi temsil eden nesnenin bir i�aret�isini d�nd�rebiliriz. E�er e�le�en ��renci nesnesi bulunamazsa, nullptr d�nd�rerek
e�le�en ��renci nesnesinin bulunmad���n� belirtebiliriz.

Adrese g�re d�n���n b�y�k dezavantaj�, �a��ran taraf�n, de�eri dereference etmeden �nce nullptr kontrol� yapmay� hat�rlamas�
gerekmektedir; aksi takdirde bir null i�aret�i dereferans� meydana gelebilir ve tan�ms�z davran�� ortaya ��kabilir.Bu tehlikeden 
dolay�, "nesne yok" �zelli�i gerekmedi�i s�rece, adrese g�re d�n�� yerine referansla d�n�� tercih edilmelidir.
 
****BEST -> Nesne yok" (nullptr kullanarak) d�nd�rme yetene�i �nemli olmad��� s�rece, adrese g�re d�n�� yerine referansa g�re 
            d�n��� tercih edin.

IN ve OUT Parametreleri
-----------------------

Bir fonksiyon ve �a��ran�, iki mekanizma arac�l���yla ileti�im kurar: parametreler ve geri d�n�� de�erleri. Bir fonksiyon
�a�r�ld���nda, �a��ran taraf, fonksiyon taraf�ndan parametreleri arac�l���yla al�nan arg�manlar� sa�lar. Bu arg�manlar de�er, 
referans veya adrese g�re iletilmi� olabilir.

Genellikle, arg�manlar� de�er veya const referans ile iletece�iz. Ancak bazen ba�ka �ekilde yapmam�z gereken durumlar olabilir.

In parametreleri -> �o�u durumda, bir fonksiyon parametresi, �a��ran taraf�ndan gelen bir giri�i almak i�in kullan�l�r. 
Sadece �a��ran taraf�ndan gelen giri�i almak i�in kullan�lan parametreler bazen "in parameters" olarak adland�r�l�r.

                    #include <iostream>

                    void print(int x) // x bir in parametresi
                    {
                        std::cout << x << '\n';
                    }

                    void print(const std::string& s) // s bir in parametresi
                    {
                        std::cout << s << '\n';
                    }

                    int main()
                    {
                        print(5);
                        std::string s { "Hello, world!" };
                        print(s);

                        return 0;
                    }

In-Parametreler genellikle de�ere veya const referans�na g�re iletilir.

Out parametreler -> Fonksiyona (const olmayan) referans (veya adrese) iletilen bir fonksiyon arg�man�, fonksiyonun arg�man olarak
iletilen bir nesnenin de�erini de�i�tirmesine izin verir. Bu, bir fonksiyonun, bir return de�eri kullanman�n herhangi bir nedenle
yeterli olmad��� durumlarda veriyi �a��ran taraf�na geri d�nd�rmesi i�in bir yol sa�lar.

Sadece bilgiyi �a��ran tarafa geri d�nd�rmek amac�yla kullan�lan bir fonksiyon parametresine "out parameter" denir.

�rne�in:

                    #include <cmath>    // std::sin() ve std::cos() i�in
                    #include <iostream>

                    // sinOut ve cosOut out parametreleridir
                    void getSinCos(double degrees, double& sinOut, double& cosOut)
                    {
                        // sin() ve cos() derece de�il radyan al�yoruz, bu y�zden d�n��t�rmemiz gerekiyor
                        constexpr double pi { 3.14159265358979323846 }; // pi de�eri
                        double radians = degrees * pi / 180.0;
                        sinOut = std::sin(radians);
                        cosOut = std::cos(radians);
                    }

                    int main()
                    {
                        double sin { 0.0 };
                        double cos { 0.0 };

                        double degrees{};
                        std::cout << "Enter the number of degrees: ";
                        std::cin >> degrees;

                        // getSinCos sin ve cos de�i�kenlerinde sin ve cos de�erlerini d�nd�r�r
                        getSinCos(degrees, sin, cos);

                        std::cout << "The sin is " << sin << '\n';
                        std::cout << "The cos is " << cos << '\n';

                        return 0;
                    }
Bu fonksiyonun bir parametresi degrees (ki arg�man� de�er ile iletilir) olarak giri�, ve iki parametreyi (referans ile) ��k��
olarak "geri d�nd�r�yor". Bu ��k�� parametrelerini, "out" ekini kullanarak out parametre olduklar�n� belirttik. Bu, �a��ran 
tarafa, bu parametrelere iletilen ba�lang�� de�erinin �nemli olmad���n�, ve bunlar�n �zerine yaz�lmas�n� beklememiz gerekti�ini
hat�rlatmaya yard�mc� olur. Geleneksel olarak, ��k�� parametreleri genellikle en sa�daki parametrelerdir.

Bu nas�l �al��t���n� daha ayr�nt�l� olarak inceleyelim. �lk olarak, ana fonksiyon sin ve cos ad�nda yerel de�i�kenler olu�turur.
Bunlar, getSinCos() fonksiyonuna de�er yerine referans ile iletilir. Bu, getSinCos() fonksiyonunun main() i�indeki sin ve cos
de�i�kenlerine ger�ek eri�imi oldu�u anlam�na gelir, sadece kopyalar de�il. getSinCos() bu �ekilde sin ve cos'a yeni de�erler
atar (s�ras�yla referanslar sinOut ve cosOut arac�l���yla), bu da sin ve cos i�indeki eski de�erleri �zerine yazar. main()
fonksiyonu daha sonra bu g�ncellenmi� de�erleri yazd�r�r.

E�er sin ve cos, de�er yerine referans iletilmemi� olsayd�, getSinCos() kopyalar�n� de�i�tirecekti ve herhangi bir de�i�ikli�in
fonksiyonun sonunda at�lmas�na neden olacakt�. Ancak sin ve cos referans ile iletilmi� olduklar� i�in, sin veya cos'a yap�lan
herhangi bir de�i�iklik (referanslar arac�l���yla) fonksiyondan �teye ta��n�r. Bu nedenle, bu mekanizmay� �a��ran tarafa de�erleri
geri d�nd�rmek i�in kullanabiliriz.

Out parametreler, i�levsel olmalar�na ra�men birka� dezavantaja sahiptir
------------------------------------------------------------------------
�lk olarak, �a��ran taraf nesneleri olu�turmal� (ve ba�latmal�) ve bunlar� arg�man olarak iletmelidir, hatta kullanmay� niyet 
etmeseler bile. Bu nesneler atanabilir olmal�d�r, bu da onlar�n const olamayaca�� anlam�na gelir.

�kinci olarak, �a��ran taraf nesneleri iletmek zorunda oldu�u i�in, bu de�erler ge�ici olarak kullan�lamaz veya kolayca tek bir
ifadede kullan�lamaz.

A�a��daki �rnek, bu iki dezavantaj� g�stermektedir:

                    #include <iostream>

                    int getByValue()
                    {
                        return 5;
                    }

                    void getByReference(int& x)
                    {
                        x = 5;
                    }

                    int main()
                    {
                        // de�er d�nd�rme
                        [[maybe_unused]] int x{ getByValue() }; // objeyi ba�latmak i�in kullan�labilir
                        std::cout << getByValue() << '\n';      // ge�ici return de�erini ifadede kullanabiliriz

                        // out parametresi d�nd�rme
                        int y{};                // �nce atanabilir bir nesne ay�rmal�y�z
                        getByReference(y);      // ard�ndan i�levi kullanarak istenen de�eri atamak i�in ge�irilir
                        std::cout << y << '\n'; // ve ancak o zaman bu de�eri kullanabiliriz

                        return 0;
                    }
                    G�rd���n�z gibi, d�� parametreleri kullanman�n s�zdizimi biraz do�al de�il.

Referansa g�re Out parametreler, arg�manlar�n de�i�tirilece�ini a��k�a ortaya koymaz
------------------------------------------------------------------------------------
Bir fonksiyonun d�n�� de�erini bir nesneye atad���m�zda, nesnenin de�erinin de�i�tirildi�i a��kt�r:

                    x = getByValue(); // x'in de�i�tirildi�i a��k

Bu iyidir, ��nk� x'in de�erinin de�i�mesini beklememiz gerekti�ini a��k�a ortaya koymaktad�r. Ancak yukar�daki �rnekte 
getSinCos() i�levine yap�lan i�lev �a�r�s�na tekrar bakal�m:

                    getSinCos(degrees, sin, cos);
Bu i�lev �a�r�s�ndan derecelerin bir i� parametre oldu�u, ancak sin ve cos'un d�� parametreler oldu�u a��k de�ildir. Arayan ki�i
sin ve cos'un de�i�tirilece�ini fark etmezse, muhtemelen anlamsal bir hata ortaya ��kacakt�r.

Referansa g�re ge�i� yerine adrese g�re ge�i� kullanmak, baz� durumlarda arayan�n nesnelerin adresini arg�man olarak iletmesini
gerektirerek d�� parametrelerin daha belirgin olmas�na yard�mc� olabilir. A�a��daki �rne�i d���n�n:

                    void foo1(int x); // de�ere g�re aktar
                    void foo2(int& x); // referansa g�re ilet
                    void foo3(int* x); // adrese g�re ge�

                    int ana()
                    {
                         int i{};

                         foo1(i); // de�i�tiremiyorum
                         foo2(i); // i'yi de�i�tirebilirim
                         foo3(&i); // i'yi de�i�tirebilirim

                         int *ptr { &i };
                         foo3(ptr); // i'yi de�i�tirebilirim

                         0 de�erini d�nd�r;
                    }
foo3(&i) �a�r�s�nda i yerine &i'yi aktarmam�z gerekti�ine dikkat edin; bu, i'nin de�i�tirilmesini beklememiz gerekti�ini daha 
a��k hale getirmeye yard�mc� olur.

Ancak foo(ptr), foo()'nun i'yi de�i�tirmesine izin verdi�i ve arayan�n ptr adresini almas�n� gerektirmedi�i i�in bu kusursuz 
de�ildir.

Arayan ki�i ayn� zamanda buna izin verilmedi�inde ge�erli bir arg�man olarak nullptr veya bir bo� g�stericiyi iletebilece�ini
d���nebilir. Ve fonksiyonun art�k bo� i�aret�i kontrol� ve i�lemesi gerekiyor, bu da daha fazla karma��kl�k kat�yor. Eklenen bo�
i�aret�i kullan�m�na olan bu ihtiya�, genellikle yaln�zca referansa g�re ge�i�e ba�l� kalmaktan daha fazla soruna neden olur.

T�m bu nedenlerden dolay�, ba�ka iyi bir se�enek olmad��� s�rece, d�� parametrelerden ka��n�lmal�d�r.

*** BEST -> Out parametrelerden ka��n�n (daha iyi se�eneklerin bulunmad��� nadir durumlar hari�). �ste�e ba�l� olmayan
            Out parametreleri i�in referansa g�re ge�i�i tercih edin.

In/out parametreler

Nadiren, bir fonksiyon ger�ekten bir out-parametrenin de�erini �zerine yazmadan �nce bu de�eri kullanacakt�r. B�yle bir
parametreye in-out parametre denir. In-out parametreleri, out-parametreleriyle tamamen ayn� �ekilde �al���r ve ayn� zorluklara 
sahiptir.
Non-const referans ile iletim ne zaman kullan�lmal�d�r?
-------------------------------------------------------
E�er bir arg�man�n bir kopyas�n� olu�turmaktan ka��nmak i�in referans ile iletecekseniz, neredeyse her zaman const referans ile
iletmelisiniz.

Ancak, pass by non-const reference'�n daha iyi bir se�enek olabilece�i iki temel durum vard�r.

�lk olarak, bir parametre bir in-out parametresi oldu�unda non-const referans ile iletimi kullan�n. Zaten geri almak istedi�imiz 
nesneyi iletiyorsak, genellikle bu nesneyi do�rudan de�i�tirmek daha basit ve performansl� olabilir.

                    void someFcn(Foo& inout)
                    {
                        // modify inout
                    }

                    int main()
                    {
                        Foo foo{};
                        someFcn(foo); // foo bu �a�r�dan sonra de�i�tirildi, a��k olmayabilir

                        return 0;
                    }
Fonksiyona iyi bir ad vermek yard�mc� olabilir:

                    void modifyFoo(Foo& inout)
                    {
                        // modify inout
                    }

                    int main()
                    {
                        Foo foo{};
                        modifyFoo(foo); // foo bu �a�r�dan sonra de�i�tirildi, nispeten daha belirgin

                        return 0;
                    }

Alternatif olarak, nesneyi de�er veya const referans ile iletmek (genellikle al���lageldi�i gibi) ve 
ard�ndan �a��rana geri atayabilece�i yeni bir nesneyi de�er olarak d�nd�rmek m�mk�nd�r:

                    Foo someFcn(const Foo& in)
                    {
                        Foo foo{in}; // burada bir kopya olu�turuluyor
                        // foo'yu de�i�tir
                        return foo;
                    }

                    int main()
                    {
                        Foo foo{};
                        foo = someFcn(foo); // foo'nun de�i�tirildi�i a��k hale getirir, ancak burada ba�ka bir kopya olu�turulur

                        return 0;
                    }

Bu, daha geleneksel bir d�n�� s�zdizimi kullanman�n avantaj�na sahiptir, ancak 2 ekstra kopya yap�lmas�n� gerektirir
(bazen derleyici bu kopyalardan birini optimize edebilir).

�kinci olarak, bir fonksiyonun aksi takdirde bir nesneyi �a��ran taraf�na de�er olarak d�nd�rece�i, ancak bu nesnenin bir
kopyas�n� yapman�n son derece maliyetli oldu�u durumlarda pass by non-const reference kullan�n. �zellikle fonksiyon, kodun 
performans a��s�ndan kritik bir b�l�m�nde �ok kez �a�r�lacaksa.

                    void generateExpensiveFoo(Foo& out)
                    {
                        // out'u de�i�tir
                    }

                    int main()
                    {
                        Foo foo{};
                        generateExpensiveFoo(foo); // bu �a�r�dan sonra foo de�i�tirildi

                        return 0;
                    }

Bununla birlikte, Bu ifade, genellikle bir nesnenin kopyalanmas�n�n o kadar maliyetli olmad��� i�in, bu nesneleri geri
d�nd�rmek i�in al���lmad�k y�ntemlere ba�vurmak genellikle gereksizdir.

Type deduction with pointers, references, and const ( Pointerler, referanslar ve constlar ile T�r ��kar�m� )
------------------------------------------------------------------------------------------------------------
                    int getVal(); // int de�erini de�ere g�re d�nd�ren bir fonksiyon

                    int ana()
                    {
                         otomatik de�er { getVal() }; // val int t�r�nden ��kar�ld�

                         0 de�erini d�nd�r;
                    }
Bundan �nceki t�r ��kar�m� dersinde, t�r ��kar�m�n�n nas�l yap�laca��n�. Ayr�ca, varsay�lan olarak t�r kesintisinin 
const (ve constexpr) niteleyicilerini d���rece�ini de belirttik:

                    const double foo()
                    {
                        return 5.6;
                    }

                    int main()
                    {
                        const double cd{ 7.8 };

                        auto x{ cd };    // double (const d���r�ld�)
                        auto y{ foo() }; // double (const d���r�ld�)

                        return 0;
                    }

Const (veya constexpr), const (veya constexpr) niteleyicisinin tan�ma eklenmesiyle (yeniden) uygulanabilir:

                    const double foo()
                    {
                        return 5.6;
                    }

                    int main()
                    {
                        constexpr double cd{ 7.8 };

                        const auto x{ foo() };  // const double (const d���r�ld�, const tekrar uyguland�)
                        constexpr auto y{ cd }; // constexpr double (constexpr d���r�ld�, constexpr tekrar uyguland�)
                        const auto z { cd };    // const double (constexpr d���r�ld�, const uyguland�)

                        return 0;
                    }

T�r ��kar�m� referanslar� d���r
-------------------------------
const belirleyicileri d���rmenin yan� s�ra, t�r ��kar�m� ayr�ca referanslar� da d���r�r:

                    #include <string>

                    std::string& getRef(); // referans d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ref { getRef() }; // t�r std::string olarak ��kar�lm��t�r (std::string& de�il)

                        return 0;
                    }

Yukar�daki �rnekte, ref de�i�keni t�r ��kar�m�n� kullan�yor. getRef() fonksiyonu bir std::string& d�nd�rmesine ra�men,
referans belirleyici at�l�r, bu y�zden ref�in t�r� std::string olarak ��kar�l�r.

At�lan const belirleyicisi gibi, ��kar�lan t�r�n bir referans olmas�n� istiyorsan�z, tan�mlama noktas�nda referans� yeniden 
uygulayabilirsiniz:

                    #include <string>

                    std::string& getRef(); // referans d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ref1 { getRef() };  // std::string (referans d���r�ld�)
                        auto& ref2 { getRef() }; // std::string& (reference tekrar uyguland�)

                        return 0;
                    }

�st seviye const ve alt seviye const
------------------------------------
Bir �st seviye const, bir nesnenin kendisine uygulanan bir const belirleyicidir. �rne�in:

                    const int x;    // bu const x'e uygulan�r, bu y�zden �st seviyedir
                    int* const ptr; // bu const ptr'ye uygulan�r, bu y�zden �st seviyedir

Buna kar��l�k, bir alt seviye const, referans� al�nan veya i�aret edilen nesneye uygulanan bir const belirleyicidir:

                    const int& ref; // bu const referans� al�nan nesneye uygulan�r, bu y�zden alt seviyedir
                    const int* ptr; // bu const i�aret edilen nesneye uygulan�r, bu y�zden alt seviyedir

Bir const de�ere referans her zaman bir alt seviye const�tir. Bir pointer, �st seviye, alt seviye veya her iki t�r const�a sahip 
olabilir:

                    const int* const ptr; // sol taraftaki const alt seviye, sa� taraftaki const �st seviyedir

T�r ��kar�m�n�n const belirleyicilerini att���n� s�yledi�imizde, sadece �st seviye const�lar� atar. Alt seviye const�lar at�lmaz.
Bunun �rneklerini birazdan g�rece�iz.

T�r ��kar�m� ve const referanslar�
----------------------------------
Ba�lat�c� bir const referans� (veya constexpr) ise, �nce referans at�l�r (ve uygunsa yeniden uygulan�r), ard�ndan sonu�tan 
herhangi bir �st seviye const at�l�r.

                    #include <string>

                    const std::string& getConstRef(); // const bir referans d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ref1{ getConstRef() }; // std::string (referans at�ld�, ard�ndan �st seviye const sonu�tan at�ld�)

                        return 0;
                    }

Yukar�daki �rnekte, getConstRef() bir const std::string& d�nd�rd���nden, �nce referans at�l�r, bizi bir const std::string ile
b�rak�r. Bu const �imdi bir �st seviye const, bu y�zden ayr�ca at�l�r, ��kar�lan t�r std::string olarak kal�r.

Anahtar nokta

Bir referans� atmak, bir alt seviye const�u bir �st seviye const�a d�n��t�rebilir: const std::string& bir alt seviye const�t�r,
ancak referans� atmak const std::string verir, bu da bir �st seviye const�t�r.

Bunlardan birini veya her ikisini de yeniden uygulayabiliriz:

                    #include <string>

                    const std::string& getConstRef(); // const bir referans d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ref1{ getConstRef() };        // std::string (referans ve �st seviye const at�ld�)
                        const auto ref2{ getConstRef() };  // const std::string (referans at�ld�, const yeniden uyguland�)

                        auto& ref3{ getConstRef() };       // const std::string& (referans yeniden uyguland�, alt seviye const
                                                              at�lmad�)
                        const auto& ref4{ getConstRef() }; // const std::string& (referans ve const yeniden uyguland�)

                        return 0;
                    }

ref1 i�in durumu �nceki �rnekte ele ald�k. ref2 i�in, bu ref1 durumuna benzer, tek fark const belirleyicisini yeniden uyguluyoruz,
bu y�zden ��kar�lan t�r const std::string�dir.

ref3 ile i�ler daha ilgin� hale geliyor. Normalde �nce referans at�l�rd�, ancak referans� yeniden uygulad���m�zdan, at�lmaz.
Bu, t�r�n hala const std::string& oldu�u anlam�na gelir. Ve bu const bir alt seviye const oldu�undan, at�lmaz. Bu nedenle 
��kar�lan t�r const std::string&'dir.

ref4 durumu, ref3�e benzer �ekilde �al���r, tek fark const belirleyicisini de yeniden uygulam�� olmam�zd�r. T�r zaten const bir
referans olarak ��kar�ld���ndan, burada const�u yeniden uygulamam�z gereksizdir. Ancak, burada const kullanmak, sonucumuzun const 
olaca��n� a��k�a belirtir (oysa ref3 durumunda, sonucun const olmas� dolayl� ve a��k de�ildir).

**** BEST -> E�er const bir referans istiyorsan�z, kesinlikle gerekli olmasa bile const belirleyicisini yeniden uygulay�n, 
             ��nk� niyetinizi a��k�a belirtir ve hatalar� �nler.

constexpr referanslar� hakk�nda ne d���n�yorsunuz?
--------------------------------------------------
Bunlar const referanslar� gibi �al���r:

                    #include <string_view>

                    constexpr std::string_view hello { "Hello" };

                    constexpr const std::string_view& getConstRef()
                    {
                        return hello;
                    }

                    int main()
                    {
                        auto ref1{ getConstRef() };            // std::string_view (�st seviye const ve referans at�ld�)
                        constexpr auto ref2{ getConstRef() };  // constexpr std::string_view (constexpr yeniden uyguland�,
                                                                  referans at�ld�)

                        auto& ref3{ getConstRef() };           // const std::string_view& (referans yeniden uyguland�, 
                                                                  alt seviye const at�lmad�)
                        constexpr auto& ref4{ getConstRef() }; // constexpr const std::string_view& (referans yeniden uyguland�,
                                                                  alt seviye const at�lmad�, constexpr uyguland�)

                        return 0;
                    }

T�r ��kar�m� ve pointerlar
--------------------------
Referanslar�n aksine, t�r ��kar�m� pointerlar� atlamaz:

                    #include <string>

                    std::string* getPtr(); // bir pointer d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ptr1{ getPtr() }; // std::string*

                        return 0;
                    }

Ayr�ca bir y�ld�z� pointer t�r ��kar�m� ile birlikte de kullanabiliriz:

                    #include <string>

                    std::string* getPtr(); // bir pointer d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ptr1{ getPtr() };  // std::string*
                        auto* ptr2{ getPtr() }; // std::string*

                        return 0;
                    }

auto ve auto* aras�ndaki fark
-----------------------------
auto�yu bir pointer t�r ba�lat�c�s� ile kulland���m�zda, auto i�in ��kar�lan t�r pointer� i�erir. Yani yukar�daki ptr1 i�in,
auto yerine ge�en t�r std::string*'dir. auto* ile bir pointer t�r ba�lat�c�s� kulland���m�zda, auto i�in ��kar�lan t�r pointer�
i�ermez - t�r ��kar�ld�ktan sonra pointer yeniden uygulan�r. Yani yukar�daki ptr2 i�in, auto yerine ge�en t�r std::string�dir ve
sonra pointer yeniden uygulan�r.

�o�u durumda, pratik etki ayn�d�r (yukar�daki �rnekte ptr1 ve ptr2 her ikisi de std::string* olarak ��kar�l�r).
Ancak, auto ve auto* aras�nda pratikte birka� fark vard�r. �lk olarak, auto* bir pointer ba�lat�c�s�na ��z�lmelidir,
aksi takdirde bir derleme hatas� olu�ur:

                    #include <string>

                    std::string* getPtr(); // bir pointer d�nd�ren bir fonksiyon

                    int main()
                    {
                        auto ptr3{ *getPtr() };      // std::string (��nk� getPtr()'yi dereferans ettik)
                        auto* ptr4{ *getPtr() };     // derlenmiyor (ba�lat�c� bir pointer de�il)

                        return 0;
                    }

Bu mant�kl�d�r: ptr4 durumunda, auto std::string�e ��kar�l�r, sonra pointer yeniden uygulan�r. Bu nedenle ptr4��n t�r�
std::string*'dir ve bir pointer olmayan bir ba�lat�c� ile std::string*'i ba�latamay�z.

�kinci olarak, const�u denkleme dahil etti�imizde auto ve auto* nas�l davrand��� aras�nda farklar vard�r. Bunu a�a��da ele
alaca��z.

T�r ��kar�m� ve const pointerlar
--------------------------------
Pointerlar at�lmad���ndan, bunun hakk�nda endi�elenmemize gerek yok. Ancak pointerlarla, hem const pointer hem de const�a pointer
durumlar�n� d���nmemiz gerekiyor ve ayr�ca auto ve auto* var. Referanslarla oldu�u gibi, pointer t�r ��kar�m� s�ras�nda sadece 
�st seviye const at�l�r.

Basit bir durumla ba�layal�m:

                    #include <string>

                    std::string* getPtr(); // bir pointer d�nd�ren bir fonksiyon

                    int main()
                    {
                        const auto ptr1{ getPtr() };  // std::string* const
                        auto const ptr2 { getPtr() }; // std::string* const

                        const auto* ptr3{ getPtr() }; // const std::string*
                        auto* const ptr4{ getPtr() }; // std::string* const

                        return 0;
                    }

auto const veya const auto kulland���m�zda, ���kar�lan t�r�n ne olursa olsun const yap� diyoruz. Yani ptr1 ve ptr2 durumunda,
��kar�lan t�r std::string*'dir ve sonra const uygulan�r, son t�r std::string* const olur. Bu, const int ve int const��n ayn� 
anlama geldi�i gibidir.

Ancak, auto* kulland���m�zda, const belirleyicinin s�ras� �nemlidir. Soldaki bir const, ���kar�lan pointer t�r�n� const�a bir
pointer yap� anlam�na gelirken, sa�daki bir const, ���kar�lan pointer t�r�n� bir const pointer yap� anlam�na gelir. 
Bu nedenle ptr3 const�a bir pointer olarak sonu�lan�r ve ptr4 bir const pointer olarak sonu�lan�r.

�imdi ba�lat�c�n�n const bir pointer�a const oldu�u bir �rne�e bakal�m.

                    #include <string>

                    int main()
                    {
                        std::string s{};
                        const std::string* const ptr { &s };

                        auto ptr1{ ptr };  // const std::string*
                        auto* ptr2{ ptr }; // const std::string*

                        auto const ptr3{ ptr };  // const std::string* const
                        const auto ptr4{ ptr };  // const std::string* const

                        auto* const ptr5{ ptr }; // const std::string* const
                        const auto* ptr6{ ptr }; // const std::string*

                        const auto const ptr7{ ptr };  // hata: const belirleyici iki kez uygulanamaz
                        const auto* const ptr8{ ptr }; // const std::string* const

                        return 0;
                    }

ptr1 ve ptr2 durumlar� basittir. �st seviye const (pointer�n kendisindeki const) at�l�r. ��aret edilen nesnedeki alt seviye 
const at�lmaz. Bu y�zden her iki durumda da son t�r const std::string*'dir.

ptr3 ve ptr4 durumlar� da basittir. �st seviye const at�l�r, ancak yeniden uyguluyoruz. ��aret edilen nesnedeki alt seviye const
at�lmaz. Bu y�zden her iki durumda da son t�r const std::string* const�dir.

ptr5 ve ptr6 durumlar�, �nceki �rnekte g�sterdi�imiz durumlara benzer. Her iki durumda da �st seviye const at�l�r.
ptr5 i�in, auto* const �st seviye const�u yeniden uygular, bu y�zden son t�r const std::string* const�dir. ptr6 i�in,
const auto* const�u i�aret edilen t�re uygular (bu durumda zaten const idi), bu y�zden son t�r const std::string*'dir.

ptr7 durumunda, const belirleyiciyi iki kez uyguluyoruz, bu izin verilmez ve bir derleme hatas�na neden olur.

Ve son olarak, ptr8 durumunda, pointer�n her iki taraf�na da const uyguluyoruz (auto* bir pointer t�r� olmal�d�r, bu y�zden izin 
verilir), bu y�zden sonu� t�rleri const std::string* const�dir.

**** BEST -> E�er const bir pointer istiyorsan�z, kesinlikle gerekli olmasa bile const belirleyicisini yeniden uygulay�n,
             ��nk� niyetinizi a��k�a belirtir ve hatalar� �nler.

                                        B�l�m 12 �zeti H�zl� inceleme

Bile�ik veri t�rleri (veya bile�ik veri t�r� olarak da adland�r�l�r), temel veri t�rlerinden (veya di�er bile�ik veri t�rlerinden)
olu�turulabilen veri t�rleridir.

Bir ifadenin de�er kategorisi, bir ifadenin bir de�ere, bir i�leve veya bir t�r nesneye ��z�l�p ��z�lmedi�ini belirtir.

Bir lvalue, bir i�levi veya bir kimli�i olan bir nesneyi de�erlendiren bir ifadedir. Bir kimli�i olan bir nesne veya i�levin bir 
tan�mlay�c�s� veya tan�mlanabilir bir bellek adresi vard�r. Lvalue�lar iki alt tipe ayr�l�r: de�i�tirilebilir lvalue�lar
de�i�tirilebilen lvalue�lard�r ve de�i�tirilemeyen lvalue�lar de�erleri de�i�tirilemeyen lvalue�lard�r (genellikle const veya
constexpr olduklar� i�in).

Bir rvalue, bir l-de�eri olmayan bir ifadedir. Bu, literalleri (dize literalleri hari�) ve i�levlerin veya operat�rlerin d�n�� 
de�erlerini (de�er olarak d�nd�r�ld���nde) i�erir.

Bir referans, mevcut bir nesnenin takma ad�d�r. Bir referans tan�mland�ktan sonra, referansa uygulanan herhangi bir i�lem, 
referans� al�nan nesneye uygulan�r. C++'da iki t�r referans bulunur: lvalue referanslar� ve rvalue referanslar�. Bir lvalue 
referans� (genellikle sadece referans olarak adland�r�l�r) mevcut bir lvalue�nin (genellikle ba�ka bir de�i�kenin) takma ad�
olarak hareket eder. Bir lvalue referans de�i�keni, bir lvalue�ye (genellikle ba�ka bir de�i�ken) referans olarak hareket eden
bir de�i�kendir.

Bir referans bir nesneyle (veya i�levle) ba�lat�ld���nda, bu nesneye (veya i�leve) ba�land���n� s�yleriz. Referans� al�nan nesne 
(veya i�lev) bazen referans olarak adland�r�l�r.

Lvalue referanslar�, de�i�tirilemeyen lvalue�lara veya rvalue�lara ba�lanamaz (aksi takdirde bu de�erleri referans arac�l���yla
de�i�tirebilirsiniz, bu da const-ness�lar�n�n ihlali olurdu). Bu nedenle, lvalue referanslar� bazen const olmayan lvalue
referanslar� olarak adland�r�l�r (bazen k�salt�lm�� olarak non-const referans).

Bir kez ba�lat�ld�ktan sonra, C++'daki bir referans yeniden oturtulamaz, yani ba�ka bir nesneye referans olacak �ekilde 
de�i�tirilemez.

Bir nesne, ona bir referans verilmeden �nce yok edilirse, referans art�k var olmayan bir nesneyi referans olarak b�rak�r.
B�yle bir referansa as�l� referans denir. As�l� bir referansa eri�mek tan�ms�z davran��a yol a�ar.

Bir lvalue referans�n� bildirirken const anahtar kelimesini kullanarak, bir lvalue referans�na referans� al�nan nesneyi const 
olarak ele almas�n� s�yleriz. B�yle bir referansa const de�ere bir lvalue referans� denir (bazen const�a referans veya const
referans olarak adland�r�l�r). Const referanslar, de�i�tirilebilir lvalue�lara, de�i�tirilemeyen lvalue�lara ve rvalue�lara
ba�lanabilir.

Bir ge�ici nesne (ayn� zamanda isimsiz nesne veya anonim nesne olarak da adland�r�l�r), tek bir ifade i�inde ge�ici kullan�m i�in
olu�turulan (ve sonra yok edilen) bir nesnedir.

Referans ile ge�i� kullan�rken, bir i�lev parametresini normal bir de�i�ken yerine bir referans (veya const referans) olarak
bildiririz. ��lev �a�r�ld���nda, her referans parametresi uygun arg�mana ba�lan�r. Referans, arg�man�n takma ad� olarak hareket
etti�i i�in, arg�man�n bir kopyas� yap�lmaz.

Adres operat�r� (&), i�lecinin bellek adresini d�nd�r�r. Dereferans operat�r� (*), belirli bir bellek adresindeki de�eri bir
lvalue olarak d�nd�r�r.

Bir pointer, de�eri olarak bir bellek adresi (genellikle ba�ka bir de�i�kenin) tutan bir nesnedir. Bu, daha sonra kullanmak
�zere ba�ka bir nesnenin adresini saklamam�z� sa�lar. Normal de�i�kenler gibi, pointerlar da varsay�lan olarak ba�lat�lmaz.
Ba�lat�lmam�� bir pointer bazen wild pointer olarak adland�r�l�r. As�l� bir pointer, art�k ge�erli olmayan bir nesnenin adresini
tutan bir pointerd�r (�rne�in, ��nk� yok edilmi�tir).

Bir pointer, bir bellek adresinin yan� s�ra, tutabilece�i bir ek de�ere daha sahiptir: null de�eri. Null de�eri (genellikle k�saca
null), bir �eyin de�eri olmad��� anlam�na gelen �zel bir de�erdir. Bir pointer null de�eri tutuyorsa, bu pointer�n hi�bir �eye
i�aret etmedi�i anlam�na gelir. B�yle bir pointera null pointer denir. nullptr anahtar kelimesi, bir null pointer literalini
temsil eder. Bir pointer� a��k�a ba�latmak veya null de�ere atamak i�in nullptr kullanabiliriz.

Bir pointer, ya ge�erli bir nesnenin adresini tutmal�d�r, ya da nullptr�a ayarlanmal�d�r. Bu �ekilde, sadece pointerlar� null i�in
test etmemiz gerekir ve herhangi bir null olmayan pointer�n ge�erli oldu�unu varsayabiliriz.

Bir const de�ere pointer (k�saca const�a pointer olarak da adland�r�l�r), sabit bir de�ere i�aret eden bir (non-const) pointerd�r.

Bir const pointer, ba�lat�ld�ktan sonra adresi de�i�tirilemeyen bir pointerd�r.

Bir const de�ere const pointer, ne adresi de�i�tirilemez, ne de pointer arac�l���yla i�aret etti�i de�er de�i�tirilebilir.

Adres ile ge�i� kullan�rken, bir nesneyi arg�man olarak sa�lamak yerine, �a��ran ki�i bir nesnenin adresini (bir pointer 
arac�l���yla) sa�lar. Bu pointer (nesnenin adresini tutan) �a�r�lan i�levin bir pointer parametresine kopyalan�r (�imdi de 
nesnenin adresini tutar). ��lev daha sonra bu pointer� dereferans ederek ge�irilen adresin nesnesine eri�ebilir.

Referans ile d�nd�rme, d�nd�r�len nesneye ba�l� bir referans d�nd�r�r, bu da d�n�� de�erinin bir kopyas�n� yapmay� �nler. 
Referans ile d�nd�rme kullanman�n bir ana sak�ncas� vard�r: programc�n�n, referans� d�nd�ren i�levi a�an nesnenin referans 
al�nd���ndan emin olmas� gerekir. Aksi takdirde, d�nd�r�len referans as�l� kal�r (yok edilmi� bir nesneyi referans al�r) ve
bu referans�n kullan�lmas� tan�ms�z davran��a yol a�ar. Bir parametre bir i�leve referans olarak ge�irilirse, bu parametreyi
referans olarak d�nd�rmek g�venlidir.

Bir i�lev bir referans d�nd�r�rse ve bu referans, bir referans olmayan bir de�i�keni ba�latmak veya atamak i�in kullan�l�rsa,
d�n�� de�eri kopyalan�r (sanki de�er olarak d�nd�r�lm�� gibi).

De�i�kenler i�in t�r ��kar�m� (auto anahtar kelimesi arac�l���yla) ��kar�lan t�rden herhangi bir referans� veya �st seviye
const belirleyicilerini atar. Bu, de�i�ken bildiriminin bir par�as� olarak yeniden uygulanabilir.

Evet, adres ile d�nd�rme, referans ile d�nd�rme ile neredeyse ayn� �ekilde �al���r. Tek fark, bir nesnenin referans� yerine 
bir nesnenin pointer�n�n d�nd�r�lmesidir.
*/