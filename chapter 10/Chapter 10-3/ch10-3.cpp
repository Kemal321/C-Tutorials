#include <iostream>

int main()
{
    return 0;
}
/*
                                                10.10 � Fonksiyon A��r� Y�klemeye Giri�
                                                ---------------------------------------

�rneklerle inceleyerek ba�layal�m:

                            int add(int x, int y)
                            {
                                return x + y;
                            }

Bu basit fonksiyon, iki tamsay�y� ekler ve bir tamsay� sonu� d�nd�r�r. Ancak, iki ondal�kl� say�y� ekleyebilen bir fonksiyon da istesek, bu add() 
fonksiyonu uygun de�ildir, ��nk� herhangi bir ondal�kl� nokta parametresi, ondal�kl� say� arg�manlar�n�n kesirli de�erlerini kaybetmesine neden
olacak �ekilde tamsay�lara d�n��t�r�l�r.

Bu sorunu a�man�n bir yolu, birka� farkl� isme sahip �ok say�da fonksiyon tan�mlamakt�r:

                            int addInteger(int x, int y)
                            {
                                return x + y;
                            }

                            double addDouble(double x, double y)
                            {
                                return x + y;
                            }

Ancak, en iyi sonu� i�in, farkl� t�rlerde parametrelere sahip benzer fonksiyonlar i�in tutarl� bir fonksiyon adland�rma standard� belirlemeniz, 
bu fonksiyonlar�n isimlerini hat�rlaman�z ve ger�ekten do�ru olan� �a��rman�z gerekmektedir.

Ve sonra 2 yerine 3 tamsay� ekleyen benzer bir fonksiyona ihtiya� duydu�umuzda ne olur? Her fonksiyon i�in benzersiz isimleri y�netmek h�zl� bir
�ekilde y�k olu�turabilir.

Fonksiyon a��r�y�klemeye giri�
------------------------------

Neyse ki, C++ bu t�r durumlar� ele almak i�in zarif bir ��z�me sahiptir. Fonksiyon a��r� y�kleme, ayn� ad� ta��yan birden fazla fonksiyon olu�turmam�za
izin verir, yeter ki her biri ayn� ad� ta��yan fonksiyon farkl� parametre tiplerine sahip olsun (veya fonksiyonlar ba�ka �ekilde ay�rt edilebilsin).
Ayn� ad� payla�an her fonksiyon (ayn� kapsamda) a��r� y�klenmi� bir fonksiyon olarak adland�r�l�r (bazen k�saltma olarak bir a��r� y�kleme olarak 
adland�r�l�r).

add() fonksiyonumuzu a��r� y�klemek i�in, basit�e double parametreleri alan ba�ka bir add() fonksiyonu bildirebiliriz:

                            int add(int x, int y) // integer version
                            {
                                return x + y;
                            }

                            double add(double x, double y) // floating point version
                            {
                                return x + y;
                            }

                            int main()
                            {
                                return 0;
                            }

Art�k ayn� kapsamda add()'�n iki s�r�m�ne sahibiz:


Yukar�daki program derlenecektir. Bu fonksiyonlardan bir isim �ak��mas� bekleseniz de, burada durum b�yle de�ildir. Bu fonksiyonlar�n parametre tipleri
farkl� oldu�u i�in, derleyici bu fonksiyonlar� ay�rt edebilir ve bunlar� yaln�zca bir ad� payla�an ayr� fonksiyonlar olarak ele alacakt�r.

Anahtar Bilgi

Fonksiyonlar, her biri derleyici taraf�ndan ay�rt edilebiliyorsa a��r� y�klenebilir. A��r� y�klenmi� bir fonksiyon ay�rt edilemiyorsa, derleme hatas� 
al�n�r.


A��r� Y�kleme ��z�m� Giri�
--------------------------

Ayr�ca, bir a��r� y�klenmi� fonksiyona yap�lan bir �a�r�da, derleyici fonksiyon �a�r�s�n�, kullan�lan arg�manlara dayanarak uygun a��r� y�kleme ile 
e�le�tirmeye �al��acakt�r. Buna a��r� y�kleme ��z�m� denir. Bunu g�steren basit bir �rnek:

                            #include <iostream>

                            int add(int x, int y)
                            {
                                return x + y;
                            }

                            double add(double x, double y)
                            {
                                return x + y;
                            }

                            int main()
                            {
                                std::cout << add(1, 2); // calls add(int, int)
                                std::cout << '\n';
                                std::cout << add(1.2, 3.4); // calls add(double, double)

                                return 0;
                            }
Yukar�daki program sonucu derler ve �retir:
                            3
                            4.6

add(1, 2) �a�r�s�nda tamsay� arg�manlar� sa�lad���m�zda, derleyici add(int, int) fonksiyonunu �a��rmaya �al��t���m�z� belirleyecektir. Ve 
add(1.2, 3.4) �a�r�s�nda ondal�k say� arg�manlar� sa�lad���m�zda, derleyici add(double, double) fonksiyonunu �a��rmaya �al��t���m�z� belirleyecektir.

Derlenmesini sa�la
------------------
A��r� y�klenmi� fonksiyonlar� kullanan bir program�n derlenmesi i�in iki �eyin do�ru olmas� gerekir:

1 - Her a��r� y�klenmi� fonksiyonun di�erlerinden ay�rt edilebilmesi gerekir.
2 - Her a��r� y�klenmi� fonksiyona yap�lan her �a�r�n�n bir a��r� y�klenmi� fonksiyona ��z�mlenmesi gerekir.

E�er bir a��r� y�klenmi� fonksiyon ay�rt edilemiyorsa veya bir a��r� y�klenmi� fonksiyona yap�lan bir fonksiyon �a�r�s� bir a��r� y�klenmi� fonksiyona 
��z�mlenemiyorsa, derleme hatas� olu�ur.

Sonraki derste, a��r� y�klenmi� fonksiyonlar�n birbirinden nas�l ayr�labilece�ini ke�fedece�iz. Ard�ndan, bir sonraki derste, derleyicinin fonksiyon 
�a�r�lar�n� a��r� y�klenmi� fonksiyonlara nas�l ��z�mleyece�ini ke�fedece�iz.

Sonu�
-----
Fonksiyon a��r� y�kleme, program�n�z�n karma��kl���n� azaltmak i�in ihtiyac�n�z olan fonksiyon ad� say�s�n� azaltarak harika bir yol sa�lar. 
�zg�rce kullan�labilir ve kullan�lmal�d�r.

*** BEST -> Program�n�z� basitle�tirmek i�in fonksiyon a��r� y�klemeyi kullan�n.

10.11 � Fonksiyon A��r� Y�kleme Ay�rt Edilmesi
----------------------------------------------

Do�ru �ekilde ay�rt edilmemi� a��r� y�klenmi� fonksiyonlar, derleyicinin derleme hatas� vermesine neden olacakt�r.

A��r� y�klenmi� fonksiyonlar nas�l ay�rt edilir
-----------------------------------------------

Fonksiyon �zelli�i | Ay�rt Edilmesinde Kullan�m | Notlar                                                                                            |
----------------------------------------------------------------------------------------------------------------------------------------------------|
Parametre Say�s�   |         Evet               |                                                                                                   |
Parametre T�r�	   |         Evet	            | typedef'leri, t�r takma adlar�n� ve de�er parametrelerindeki const niteli�ini hari� tutar         |
D�n�� T�r�	       |         Hay�r              | Elipsleri i�erir.                                                                                 |
----------------------------------------------------------------------------------------------------------------------------------------------------

Unutmay�n ki bir fonksiyonun d�n�� t�r�, a��r� y�klenmi� fonksiyonlar� ay�rt etmek i�in kullan�lmaz.

Parametre say�s�na dayal� a��r� y�kleme
--------------------------------------- 
Her a��r� y�klenmi� fonksiyon, farkl� bir parametre say�s�na sahip oldu�u s�rece ay�rt edilir. �rne�in:

                    int add(int x, int y)
                    {
                        return x + y;
                    }

                    int add(int x, int y, int z)
                    {
                        return x + y + z;
                    }
Derleyici, iki tamsay� parametreli bir fonksiyon �a�r�s�n�n add(int, int)'e gitmesi gerekti�ini ve �� tamsay� 
parametreli bir fonksiyon �a�r�s�n�n add(int, int, int)'e gitmesi gerekti�ini kolayca anlayabilir.

Parametre t�r�ne dayal� a��r� y�kleme
-------------------------------------
Bir fonksiyon, her bir a��r� y�klenmi� fonksiyonun parametre t�r� listesinin farkl� oldu�u s�rece ay�rt edilebilir. �rne�in, a�a��daki t�m 
a��r� y�klemeler farkl�d�r:
                    int add(int x, int y); // integer version
                    double add(double x, double y); // floating point version
                    double add(int x, double y); // mixed version
                    double add(double x, int y); // mixed version

��nk� t�r takma adlar� (veya typedef'ler) ay�rt edici t�rler de�ildir, t�r takma adlar� kullan�larak yap�lan a��r� y�klemeler, t�r takma ad�
kullan�lan t�rden ay�rt edilmez. �rne�in, a�a��daki t�m a��r� y�klemeler ay�rt edilmez (ve derleme hatas�na neden olur):

                    typedef int Height; // typedef
                    using Age = int; // type alias

                    void print(int value);
                    void print(Age value); // print(int) ile ay�rt edilmez
                    void print(Height value); // print(int) ile ay�rt edilmez

De�er ile ge�ilen parametreler i�in const niteli�i de dikkate al�nmaz. Bu nedenle, a�a��daki fonksiyonlar ay�rt edildi�i kabul edilmez:

                    void print(int);
                    void print(const int); // print(int) ile ay�rt edilmez

Bir fonksiyonun d�n�� t�r�, a��r� y�klenmi� fonksiyonlar� ay�rt etme konusunda dikkate al�nmaz.

A�a��daki gibi bir durumu d���n�n: Rastgele bir say� d�nd�ren bir fonksiyon yazmak istiyorsunuz, ancak bir tane int d�nd�ren bir versiyona ve bir tane
de double d�nd�ren bir versiyona ihtiyac�n�z var. ��yle yapmaya y�nelebilirsiniz:
                    int getRandomValue();
                    double getRandomValue();
Visual Studio 2019'da bu, a�a��daki derleme hatas�na neden olur:
                    error C2556: 'double getRandomValue(void)': overloaded function differs only by return type from 'int getRandomValue(void)'
Bu mant�kl�. E�er derleyici olsayd�n�z ve �u ifadeyi g�rseydiniz:
                    getRandomValue();
�ki a��r� y�klenmi� fonksiyonun hangisini �a��r�rd�n�z? Bu belirsizdir.


Yan� s�ra...
Bu, bir fonksiyon �a�r�s�n�n davran���n�n, karma��k ifadelerin geri kalan�ndan ba��ms�z olarak belirlenebilmesini sa�lamak i�in bilin�li bir se�imdi, 
bu da karma��k ifadelerin anla��lmas�n� �ok daha basitle�tirir. Ba�ka bir deyi�le, bir fonksiyon �a�r�s�n�n hangi s�r�m�n�n yaln�zca fonksiyon 
�a�r�s�ndaki arg�manlara dayanarak belirlenebilece�ini her zaman s�yleyebiliriz. E�er d�n�� de�erleri ayr�m i�in kullan�lsayd�, o zaman bir fonksiyonun
hangi a��r� y�klemesinin �a�r�ld���n� anlaman�n kolay bir s�zdizimi yolu olmazd� - ayr�ca d�n�� de�erinin nas�l kullan�ld���n� anlamam�z gerekecekti, 
bu da daha fazla analiz gerektirir.

Bu sorunu ��zmenin en iyi yolu i�levlere farkl� adlar vermektir:

                    int getRandomInt();
                    double getRandomDouble();

T�r imzas�

Bir fonksiyonun t�r imzas� (genellikle bir imza olarak adland�r�l�r), fonksiyonun ayr�lmak i�in kullan�lan fonksiyon ba�l���n�n b�l�mlerini tan�mlar.
C++'da bu, fonksiyon ad�n�, parametre say�s�n�, parametre t�r�n� ve fonksiyon d�zeyindeki nitelikleri i�erir. �zellikle d�n�� t�r�n� i�ermez.


�sim kar��t�rma - Name Mangling
-------------------------------
Yan� s�ra 
Derleyici bir fonksiyonu derledi�inde, fonksiyonun derlenmi� ad�n� �e�itli kriterlere dayanarak (�rne�in, parametre say�s� ve t�r� gibi) de�i�tirir
("mangle" eder), b�ylece ba�lay�c� benzersiz adlarla �al��abilir.

�rne�in, int fcn() prototipi olan bir fonksiyon ad� __fcn_v'ye derlenmi� olabilir, oysa int fcn(int) fonksiyonu __fcn_i ad�na derlenmi� olabilir.
Bu nedenle kaynak kodunda iki a��r� y�klenmi� fonksiyon ayn� ad� payla�sa da, derlenmi� kodda adlar asl�nda benzersizdir.

Adlar�n nas�l mangle edilmesi gerekti�i konusunda standartla�ma olmad��� i�in, farkl� derleyiciler farkl� mangled adlar �retecektir.
*/

/*
                                            10.12 � Fonksiyon a��r� y�k� ��z�n�rl��� ve belirsiz e�le�meler
                                            -----------------------------------------------------------

E�er bir a��r� y�klenmi� fonksiyon, ayn� isme sahip di�er a��r� y�klemelerden do�ru �ekilde ay�rt edilemiyorsa, derleyici bir derleme hatas� verir.

Ancak, ay�rt edilmi� a��r� y�klenmi� fonksiyonlara sahip olmak resmin yaln�zca yar�s�d�r. Herhangi bir fonksiyon �a�r�s� yap�ld���nda, derleyici ayn� 
zamanda e�le�en bir fonksiyon bildirimini bulabilmesini sa�lamal�d�r.

A��r� y�klenmi� olmayan fonksiyonlarda (benzersiz adlara sahip fonksiyonlar), bir fonksiyon �a�r�s�n� e�le�tirebilecek potansiyel bir fonksiyon vard�r.
Bu fonksiyon ya e�le�ir (veya t�r d�n���mleri uyguland�ktan sonra e�le�tirilebilir), ya da e�le�mez (ve bir derleme hatas� ortaya ��kar). 
A��r� y�klenmi� fonksiyonlarda, bir fonksiyon �a�r�s�na potansiyel olarak e�le�ebilecek bir�ok fonksiyon olabilir. ��nk� bir fonksiyon �a�r�s� 
yaln�zca bunlardan birine ��z�mlenebilir, derleyici en iyi e�le�en a��r� y�klenmi� fonksiyonu belirlemelidir. Fonksiyon �a�r�lar�n� belirli bir 
a��r� y�klenmi� fonksiyona e�le�tirme s�recine "a��r� y�kleme ��z�mleme" denir.

Fonksiyon arg�manlar�n�n t�r� ve fonksiyon parametrelerinin t�r� tam olarak e�le�ti�inde, bu (genellikle) basittir:

                    #include <iostream>

                    void print(int x)
                    {
                         std::cout << x << '\n';
                    }

                    void print(double d)
                    {
                         std::cout << d << '\n';
                    }

                    int main()
                    {
                         print(5); // 5 bir int oldu�u i�in bu, print(int) ile e�le�ir
                         print(6.7); // 6.7 bir double oldu�u i�in bu, print(double) ile e�le�ir

                         return 0;
                    }

Ancak, a��r� y�klenmi� fonksiyonlardan hi�birinin parametre t�rleriyle tam olarak e�le�meyen durumlarda ne olur? �rne�in:

                #include <iostream>

                void print(int x)
                {
                     std::cout << x << '\n';
                }

                void print(double d)
                {
                     std::cout << d << '\n';
                }

                int main()
                {
                     print('a'); // char, int veya double ile e�le�mez
                     print(5L); // long, int veya double ile e�le�mez

                     return 0;
                }

"Sadece burada tam bir e�le�me olmamas�, bir e�le�menin bulunamayaca�� anlam�na gelmez � sonu�ta, bir char veya long tipi, 
bir int veya double'a otomatik olarak t�r d�n��t�r�lebilir. Ancak her durumda en iyi d�n���m hangisi?"

A��r� y�klenmi� (overloaded) fonksiyon �a�r�ld���nda, derleyici a��r� y�klenmi� fonksiyonlar�n hangisinin (varsa) en iyi e�le�me
oldu�unu belirlemek i�in bir dizi kural� takip eder.

Her ad�mda, derleyici, fonksiyon �a�r�s�ndaki arg�man(lar)a �e�itli t�r d�n���mlerini uygular. Her uygulanan d�n���m i�in, derleyici a��r� 
y�klenmi� fonksiyonlardan herhangi birinin �imdi bir e�le�ip e�le�medi�ini kontrol eder. Farkl� t�r d�n���mleri uyguland�ktan ve e�le�me 
kontrol edildikten sonra ad�m tamamlan�r. Sonu�, �� olas� durumdan biri olacakt�r:

1. E�le�en fonksiyon bulunamad�. Derleyici, s�radaki ad�ma ge�er.
2. Tek bir e�le�en fonksiyon bulundu. Bu fonksiyon en iyi e�le�me olarak kabul edilir. E�le�me s�reci tamamlan�r ve sonraki ad�mlar ger�ekle�tirilmez.
3. Birden fazla e�le�en fonksiyon bulundu. Derleyici, belirsiz bir e�le�me derleme hatas� verecektir. Bu durumu biraz daha detayl� bir �ekilde
   tart��aca��z.

E�er derleyici, t�m dizi boyunca bir e�le�me bulamadan sona erirse, fonksiyon �a�r�s� i�in e�le�en a��r� y�klenmi� fonksiyon bulunamad���na dair 
bir derleme hatas� �retecektir.

Arg�man e�leme s�ras�
---------------------

Ad�m 1) Derleyici tam bir e�le�me bulmaya �al���r. Bu iki a�amada ger�ekle�ir. �lk olarak, derleyici, fonksiyon �a�r�s�ndaki arg�manlar�n t�r�n�n, 
a��r� y�klenmi� fonksiyonlardaki parametrelerin t�r�yle tam olarak e�le�ti�i bir a��r� y�klenmi� fonksiyon olup olmad���n� kontrol eder. �rne�in:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print(0);   // print(int) ile tam bir e�le�me
                        print(3.4); // print(double) ile tam bir e�le�me

                        return 0;
                    }

��nk� fonksiyon �a�r�s�ndaki 0 bir int oldu�undan, derleyici bir print(int) a��r� y�klemesi tan�mlanm�� m� diye bakacakt�r. Var ise, derleyici 
print(int) fonksiyonunu tam bir e�le�me olarak belirler.

�kinci olarak, derleyici, fonksiyon �a�r�s�ndaki arg�manlara bir dizi basit d�n���m uygular. Basit d�n���mler, e�le�me bulma amac�yla t�rleri 
(de�erleri de�i�tirmeden) de�i�tirecek belirli d�n���m kurallar�d�r. �rne�in, bir const olmayan t�r, basit�e bir const t�r�ne d�n��t�r�lebilir:

                    void print(const int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        int x { 0 };
                        print(x); // x, basit�e const int'ye d�n��t�r�l�r

                        return 0;
                    }

Yukar�daki �rnekte, print(x) �a�r�s�n� yapt�k, burada x bir int. Derleyici x'i int'ten const int'e basit�e d�n��t�recek, ard�ndan print(const int)
ile e�le�ecektir.

Basit d�n���mler arac�l���yla yap�lan e�le�meler tam e�le�me olarak kabul edilir.

Ad�m 2) E�er tam bir e�le�me bulunmazsa, derleyici arg�man(lar)a say�sal y�kseltme uygulayarak bir e�le�me bulmaya �al���r. 10.1 dersinde
(�rt�l� t�r d�n���m�) belirli dar tamsay�sal ve kayan noktal� t�rlerin otomatik olarak daha geni� t�rlere, �rne�in int veya double, 
y�kseltilebilece�ini ele alm��t�k. Say�sal y�kseltme sonras�nda bir e�le�me bulunursa, fonksiyon �a�r�s� ��z�l�r.

�rne�in:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print('a');    // print(int) ile e�le�ecek �ekilde y�kseltilir
                        print(true);   // print(int) ile e�le�ecek �ekilde y�kseltilir
                        print(4.5f);   // print(double) ile e�le�ecek �ekilde y�kseltilir

                        return 0;
                    }

print('a') i�in, print(char) i�in tam bir e�le�me bulunamad���ndan, derleyici char 'a'y� bir int'e y�kseltir ve e�le�me arar. Bu, print(int) ile
e�le�ir, bu nedenle fonksiyon �a�r�s� print(int) olarak ��z�l�r.

Ad�m 3) E�er say�sal y�kseltme arac�l���yla bir e�le�me bulunamazsa, derleyici arg�manlara say�sal d�n���mleri uygulayarak bir e�le�me bulmaya �al���r.

�rne�in:

                    #include <string> // for std::string

                    void print(double)
                    {
                    }

                    void print(std::string)
                    {
                    }

                    int main()
                    {
                        print('a'); // 'a', print(double) ile e�le�ecek �ekilde d�n��t�r�l�r

                        return 0;
                    }

Bu durumda, print(char) (tam e�le�me) ve print(int) (y�kseltme e�le�mesi) olmad��� i�in 'a', say�sal olarak bir double'ye d�n��t�r�l�r ve print(double)
ile e�le�ir.

Anahtar �pucu

Say�sal y�kseltmeler uygulayarak yap�lan e�le�meler, say�sal d�n���mler uygulayarak yap�lan e�le�melerin �st�ndedir.


Ad�m 4) E�er say�sal d�n���m arac�l���yla bir e�le�me bulunamazsa, derleyici herhangi bir kullan�c� tan�ml� d�n���m arac�l���yla bir e�le�me bulmaya 
�al���r. Hen�z kullan�c� tan�ml� d�n���mleri ele almad�k, ancak belirli tipler (�rne�in, s�n�flar) ba�ka tiplere d�n���mleri tan�mlayabilir ve bu 
d�n���mler, dolayl� olarak �a�r�labilir. ��te noktay� a��klamak i�in bir �rnek:

(Not: Burada, kullan�c� tan�ml� d�n���mleri i�lememi� olabiliriz, ancak konsepti anlatmak i�in basit bir �rnek kullan�l�yor.)

                    // S�n�flar� hen�z ele almad�k, bu nedenle bu anlams�z geliyorsa endi�elenmeyin
                    class X // this defines a new type called X
                    {
                    public:
                        operator int() { return 0; } // ��te X t�r�nden int'e olan kullan�c� tan�ml� d�n���m
                    };

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        X x; // Burada, X t�r�nde bir nesne olu�turuyoruz (isimlendirilmi� x)
                        print(x); // x, X'ten int'e olan kullan�c� tan�ml� d�n���m� kullanarak int t�r�ne d�n��t�r�l�yor

                        return 0;
                    }

Bu �rnekte, derleyici �nce `print(X)` i�in tam bir e�le�me olup olmad���n� kontrol eder. Biz b�yle bir e�le�me tan�mlamad�k. Daha sonra derleyici,
`x`'in say�sal olarak y�kseltilip y�kseltilmedi�ini kontrol eder, ancak bu m�mk�n de�ildir ��nk� kullan�c� tan�ml� bir t�r olan `X`'ten do�rudan
say�sal bir y�kseltme yoktur.

Ard�ndan, derleyici `x`'in say�sal olarak d�n��t�r�l�p d�n��t�r�lemedi�ini kontrol eder, ancak bu durumda da m�mk�n de�ildir.

Son olarak, derleyici herhangi bir kullan�c� tan�ml� d�n���me bakar. `X` s�n�f�ndaki `operator int()` kullan�c� tan�ml� d�n���m� bulur. Sonu� olarak,
`x` adl� `X` t�r�ndeki nesne, `int` t�r�ne kullan�c� tan�ml� d�n���m� kullanarak d�n��t�r�l�r ve `print(int)` ile e�le�mesi sa�lan�r.

Kullan�c� tan�ml� d�n���m uyguland�ktan sonra, derleyici e�le�me bulabilmek i�in ek implicit (otomatik) y�kseltmeler veya d�n���mler uygulayabilir.
Bu �rnekte, e�er kullan�c� tan�ml� d�n���m `int` yerine `char` t�r�ne yap�lm�� olsayd�, derleyici kullan�c� tan�ml� d�n���m� `char` t�r�ne kullanacak
ve ard�ndan sonucu `int` t�r�ne y�kseltecekti, b�ylece `print(int)` fonksiyonuyla e�le�ebilirdi.

Ad�m 5) E�er kullan�c� tan�ml� d�n���m arac�l���yla bir e�le�me bulunamazsa, derleyici �� nokta (...) kullanan bir e�le�en fonksiyon arayacakt�r.

Ad�m 6) E�er bu noktaya kadar hi�bir e�le�me bulunamazsa, derleyici vazge�er ve e�le�en bir fonksiyon bulunamad���na dair bir derleme hatas� verecektir.

Kar���k E�le�meler
------------------

Overloaded olmayan fonksiyonlarla, her fonksiyon �a�r�s� ya bir fonksiyona ��z�lecek ya da hi� e�le�me bulunamayacak ve derleyici bir derleme hatas� 
verecektir:

                    void foo()
                    {
                    }

                    int main()
                    {
                         foo(); // Tamam: E�le�me bulundu
                         goo(); // Derleme hatas�: E�le�me bulunamad�

                         return 0;
                    }

Overloaded fonksiyonlarla, ���nc� bir olas�l�k daha vard�r: belirsiz bir e�le�me bulunabilir. Belirsiz bir e�le�me, derleyicinin ayn� ad� ta��yan iki 
veya daha fazla fonksiyonu ayn� ad�mda e�le�tirebilece�i durumu ifade eder. Bu durumda, derleyici e�le�meyi durdurur ve belirsiz bir fonksiyon �a�r�s�
buldu�unu belirten bir derleme hatas� verir.

Her y�klenmi� fonksiyonun derlenebilmesi i�in diferansiyasyon yap�lmas� gerekti�inden, bir fonksiyon �a�r�s�n�n nas�l oluyor da birden fazla e�le�meye
neden olabilece�ini merak ediyor olabilirsiniz. Bunu g�steren bir �rne�e bakal�m:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print(5L); // 5L long t�r�d�r

                        return 0;
                    }

Evet, tabii ki! ��te metnin T�rk�e �evirisi:

"5L ifadesi tipi long oldu�undan, derleyici �nce print(long) i�in tam bir e�le�me bulup bulamayaca��n� kontrol edecektir, ancak b�yle bir e�le�me
bulamayacakt�r. Sonras�nda, derleyici say�sal y�kseltmeyi deneyecek, ancak long tipindeki de�erler y�kseltilmedi�i i�in burada da bir e�le�me
olmayacakt�r.

Bundan sonra, derleyici long arg�man� �zerinde say�sal d�n���mleri uygulayarak bir e�le�me bulmaya �al��acakt�r. Say�sal d�n���m kurallar�n� kontrol 
ederken, derleyici iki potansiyel e�le�me bulacakt�r. E�er long arg�man� bir int'e numerik olarak d�n��t�r�l�rse, fonksiyon �a�r�s� print(int) ile
e�le�ecektir. E�er long arg�man� bir double'a d�n��t�r�l�rse, o zaman print(double) ile e�le�ecektir. �ki farkl� say�sal d�n���m yoluyla iki potansiyel
e�le�me bulundu�u i�in, fonksiyon �a�r�s� belirsiz kabul edilir.

Visual Studio 2019'da, bu durum �u hata mesaj�na yol a�acakt�r:"

                    Hata C2668: 'print': a��r� y�klenmi� fonksiyona belirsiz �a�r�
                    mesaj�: 'void print(double)' olabilir
                    mesaj�: veya 'void print(int)' olabilir
                    mesaj�: '(long)' arg�man listesine e�le�meye �al���rken


Ana �pucu

E�er derleyici bir ad�mda birden fazla e�le�me bulursa, belirsiz bir fonksiyon �a�r�s� ortaya ��kar. Bu durumda, bir ad�mdan elde edilen hi�bir e�le�me,
ayn� ad�mdan di�er herhangi bir e�le�meden daha iyi kabul edilmez.

��te ba�ka bir �rnek, belirsiz e�le�melere neden olan:

                    void print(unsigned int)
                    {
                    }

                    void print(float)
                    {
                    }

                    int main()
                    {
                        print(0); // int, unsigned int'e veya floata say�sal olarak d�n��t�r�lebilir
                        print(3.14159); // double, unsigned int'e veya floata say�sal olarak d�n��t�r�lebilir

                        return 0;
                    }

0'�n `print(unsigned int)` olarak ��z�nmesini ve 3.14159'un `print(float)` olarak ��z�nmesini bekleyebilirsiniz, ancak her iki �a�r� da belirsiz 
e�le�melere neden olur. int de�eri 0, hem `unsigned int`'e hem de `float`'e say�sal olarak d�n��t�r�lebilir, bu nedenle her iki a��r� y�klenmi� 
fonksiyon da e�it derecede iyi e�le�ir ve sonu� belirsiz bir fonksiyon �a�r�s�d�r.

Ayn� durum, bir `double`'�n hem `float`'a hem de `unsigned int`'e d�n��t�r�lmesi i�in ge�erlidir. Her ikisi de say�sal d�n���mler oldu�undan, her
iki a��r� y�kleme de e�it derecede iyi e�le�ir ve sonu� yine belirsizdir.

Belirsiz e�le�meleri ��zme
--------------------------

"Belirsiz e�le�meler derleme zaman� hatas� oldu�u i�in program�n�z�n derlenmesi i�in bir belirsiz e�le�me ��z�lmelidir. Belirsiz e�le�meleri ��zmek 
i�in birka� yol vard�r:

Genellikle en iyi yol, do�rudan �a��rmaya �al��t���n�z fonksiyon i�in tam olarak ayn� t�rde parametrelere sahip yeni bir a��r� y�klenmi� fonksiyon 
tan�mlamakt�r. Bu durumda C++, fonksiyon �a�r�s� i�in tam bir e�le�me bulabilecektir.

Alternatif olarak, belirsiz arg�man(lar)� a��k�a istedi�iniz fonksiyon t�r�ne e�le�ecek �ekilde d�n��t�rebilirsiniz. �rne�in, yukar�daki �rnekte 
print(0)'� print(unsigned int) ile e�le�tirmek i�in �unu yapabilirsiniz:"

                    int x{ 0 };
                    print(static_cast<unsigned int>(x)); // print(unsigned int) � �a��racak

E�er arg�man�n�z bir literal ise, literal �neki kullanarak literalinizi do�ru t�r olarak yorumlanmas�n� sa�layabilirsiniz:

                    print(0u); // 'u' �neki unsigned int oldu�u i�in print(unsigned int) fonksiyonunu �a��racakt�r, bu nedenle bu �imdi tam bir e�le�me

Birden fazla ba��ms�z de�i�kene sahip fonksiyonlar i�in e�le�tirme
------------------------------------------------------------------
E�er birden �ok arg�man varsa, derleyici her arg�mana s�rayla e�le�me kurallar�n� uygular. Se�ilen fonksiyon, her bir arg�man�n en az di�er t�m
fonksiyonlarla ayn� derecede e�le�ti�i ve en az bir arg�man�n di�er t�m fonksiyonlardan daha iyi e�le�ti�i fonksiyondur. Ba�ka bir deyi�le, se�ilen
fonksiyon, en az bir parametre i�in di�er t�m aday fonksiyonlardan daha iyi bir e�le�me sa�lamal� ve di�er t�m parametreler i�in daha k�t� olmamal�d�r.

Bu t�r bir fonksiyon bulundu�unda, a��k�a ve belirsiz olmadan en iyi se�enek oldu�u anla��l�r. E�er b�yle bir fonksiyon bulunamazsa, �a�r� belirsiz
(veya uyu�maz) olarak kabul edilecektir.

�rne�in:

                    #include <iostream>

                    void print(char, int)
                    {
                        std::cout << 'a' << '\n';
                    }

                    void print(char, double)
                    {
                        std::cout << 'b' << '\n';
                    }

                    void print(char, float)
                    {
                        std::cout << 'c' << '\n';
                    }

                    int main()
                    {
                        print('x', 'a');

                        return 0;
                    }

Yukar�daki programda, t�m fonksiyonlar ilk arg�man� tam olarak e�le�tirir. Ancak, en �stteki fonksiyon ikinci parametreyi y�kseltme yoluyla 
e�le�tirirken, di�er fonksiyonlar bir d�n���me ihtiya� duyar. Bu nedenle, print(char, int) fonksiyonu belirsiz bir �ekilde en iyi e�le�medir.

10.13 � Fonksiyonlar� Silme
---------------------------

Belirli durumlarda, belirli tiplerdeki de�erlerle �a�r�ld���nda istenen �ekilde davranmayan fonksiyonlar yazmak m�mk�nd�r.

A�a��daki �rne�i d���n�n:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        printInt(5);    // tamam: 5'i yazd�r�r
                        printInt('a');  // 97 yazd�r�r -- bu mant�kl� m�?
                        printInt(true); // 1'i yazd�r�r -- bu mant�kl� m�?

                        return 0;
                    }

Bu �rnekte ��kt�:

                    5
                    97
                    1

printInt(5) a��k�a uygunken, printInt()'e yap�lan di�er iki �a�r� daha tart��mal�d�r. printInt('a') �a�r�s�nda derleyici, 'a'y� int de�eri 97'ye
y�kseltebilece�ini belirleyecek ve bu �ekilde fonksiyon �a�r�s�n� fonksiyon tan�m�yla e�le�tirecektir. Ayn� �ekilde, true de�erini int de�eri 1'e
y�kseltecektir. Ve bu i�lem uyar� vermeden ger�ekle�ecektir.

Varsayal�m ki printInt() fonksiyonuna char veya bool t�r�nden bir de�erle �a�r�lmas�n�n mant�kl� olmad���n� d���n�yoruz. Ne yapabiliriz?

Fonksiyonu = delete belirleyicisi kullanarak silme
--------------------------------------------------
Belirli bir fonksiyonun bilin�li olarak �a�r�lamamas�n� istedi�imiz durumlarda, bu fonksiyonu = delete belirleyicisini kullanarak silmek m�mk�nd�r. 
Derleyici, bir fonksiyon �a�r�s�n� silinmi� bir fonksiyonla e�le�tirirse, derleme, derleme hatas� ile durdurulacakt�r.

��te yukar�daki �rne�i bu s�zdizimini kullanarak g�ncelleyen bir versiyon:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    void printInt(char) = delete; // bu fonksiyona yap�lan �a�r�lar derlemeyi durduracakt�r
                    void printInt(bool) = delete; // bu fonksiyona yap�lan �a�r�lar derlemeyi durduracakt�r

                    int main()
                    {
                        printInt(97);   // tamam

                        printInt('a');  // derleme hatas�: fonksiyon silinmi�
                        printInt(true); // derleme hatas�: fonksiyon silinmi�

                        printInt(5.0);  // derleme hatas�: belirsiz e�le�me

                        return 0;
                    }

Hadi bunlara bir g�z atal�m. �lk olarak, printInt('a'), silinmi� olan printInt(char) i�in do�rudan bir e�le�medir. Bu nedenle derleyici bir derleme
hatas� �retir. printInt(true), silinmi� olan printInt(bool) i�in do�rudan bir e�le�medir ve bu nedenle ayn� �ekilde derleme hatas� �retir.

printInt(5.0) ilgin� bir durumdur ve belki de beklenmeyen sonu�lara neden olabilir. �lk olarak, derleyici, tam e�le�me olan printInt(double)'�n
varl���n� kontrol eder. Ancak b�yle bir fonksiyon yoktur. Sonraki ad�mda, derleyici en iyi e�le�meyi bulmaya �al���r. printInt(int) tek silinmeyen
fonksiyon olmas�na ra�men, silinmi� fonksiyonlar hala fonksiyon a��r� y�klenme ��z�mlemesinde aday olarak kabul edilir. Bu fonksiyonlardan hi�biri
a��k�a en iyi e�le�me de�ildir, bu nedenle derleyici belirsiz e�le�me derleme hatas� verecektir.

= delete, 'Bunu yasakl�yorum' anlam�na gelir, 'Bu mevcut de�il' anlam�na gelmez.

Silinmi� fonksiyonlar, fonksiyon a��r� y�kleme ��z�mlemesinin t�m a�amalar�nda (yaln�zca tam e�le�me a�amas�nda de�il) yer al�r. E�er bir silinmi�
fonksiyon se�ilirse, o zaman bir derleme hatas� ortaya ��kar.

10.14 � Varsay�lan Arg�manlar
-----------------------------
Bir varsay�lan arg�man, bir fonksiyon parametresi i�in sa�lanan varsay�lan bir de�erdir. �rne�in:

                    void print(int x, int y=10) // 10 is the default argument
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

Fonksiyon �a�r�s� yap�l�rken, �a�r�c� iste�e ba�l� olarak varsay�lan bir arg�man� olan herhangi bir fonksiyon parametresi i�in bir arg�man sa�layabilir.
�a�r�c� bir arg�man sa�larsa, fonksiyon �a�r�s�ndaki arg�man de�eri kullan�l�r. �a�r�c� bir arg�man sa�lamazsa, varsay�lan arg�man�n de�eri kullan�l�r.

A�a��daki program� d���n�n:

                    #include <iostream>

                    void print(int x, int y=4) // 4 varsay�lan arg�mand�r
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

                    int main()
                    {
                        print(1, 2); // y kullan�c� taraf�ndan sa�lanm�� 2 de�erini kullan�r.
                        print(3); // y varsay�lan arg�man olan 4 � kullan�r, print(3, 4) olarak �a��rm���z gibi.

                        return 0;
                    }
Bu program �u ��kt�y� verir:
                    x: 1
                    y: 2
                    x: 3
                    y: 4

�lk fonksiyon �a�r�s�nda, �a�r�c� her iki parametre i�in de a��k�a arg�man sa�lad�, bu nedenle bu arg�man de�erleri kullan�ld�. �kinci fonksiyon 
�a�r�s�nda, �a�r�c� ikinci arg�man� atlad�, bu nedenle varsay�lan de�er olan 4'�n de�eri kullan�ld�.

Varsay�lan bir arg�man� belirtmek i�in e�ittir i�aretini kullanman�z gerekti�ini unutmay�n. Parantez veya s�sl� parantez ba�latma kullanmak i�e yaramaz:

                    void foo(int x = 5);   // ok
                    void goo(int x ( 5 )); // compile error
                    void boo(int x { 5 }); // compile error


Belki de �a��rt�c� bir �ekilde, varsay�lan arg�manlar derleyici taraf�ndan �a�r� noktas�nda i�lenir. Yukar�daki �rnekte, derleyici print(3) ifadesini
g�rd���nde, bu fonksiyon �a�r�s�n� print(3, 4) olarak yeniden yazacak ve arg�man say�s� parametre say�s�yla e�le�ecektir. Yeniden yaz�lm�� fonksiyon
�a�r�s� ard�ndan normal �ekilde �al���r.

Varsay�lan arg�manlar� ne zaman kullanmal�s�n�z
-----------------------------------------------
Varsay�lan arg�manlar, bir fonksiyonun mant�kl� bir varsay�lan de�ere ihtiya� duydu�u durumlarda ve �a�r�c�ya bu de�eri iste�e ba�l� olarak ge�me
olana�� tan�mak istedi�iniz durumlarda m�kemmel bir se�enektir.

�rne�in, burada varsay�lan arg�manlar�n yayg�n olarak kullan�labilece�i birka� fonksiyon prototipi bulunmaktad�r:

                    int rollDie(int sides=6);
                    void openLogFile(std::string filename="default.log");

Yazar�n Notu:

Kullan�c�, belirli bir arg�man de�eri sa�lay�p sa�lamamay� se�ebildi�i i�in, bir varsay�lan de�erle sa�lanan bir parametre bazen "iste�e ba�l�
parametre" olarak adland�r�l�r. Ancak, "iste�e ba�l� parametre" terimi ayn� zamanda ba�ka t�rden parametreleri de ifade etmek i�in kullan�l�r
(�rne�in, adresle ge�irilen parametreler ve std::optional kullan�lan parametreler), bu nedenle bu terimi kullanmaktan ka��nman�z� �neririz.

Birden fazla varsay�lan arg�man
-------------------------------

Bir fonksiyon bir �ok varsay�lan arg�mana sahip olabilir:

                    #include <iostream>

                    void print(int x=10, int y=20, int z=30)
                    {
                        std::cout << "Values: " << x << " " << y << " " << z << '\n';
                    }

                    int main()
                    {
                        print(1, 2, 3); // t�m� kas�tl� arg�manlar
                        print(1, 2); // en sa�daki arg�man varsay�land�r
                        print(1); // en sa�dan ikisi varsay�lan arg�mand�r
                        print(); // t�m arg�manlar default olarak se�ilmi�tir

                        return 0;
                    }
��kt�:
                    Values: 1 2 3
                    Values: 1 2 30
                    Values: 1 20 30
                    Values: 10 20 30

C++ (en az�ndan C++20'ye kadar) print(,,3) gibi bir fonksiyon �a�r� s�zdizimini desteklemez (x ve y i�in varsay�lan arg�manlar� kullan�rken z
i�in a��k bir de�er sa�lama y�ntemi olarak). Bu iki �nemli sonu� do�urur:
1- E�er bir parametre varsay�lan bir arg�man al�yorsa, b�t�n sonraki parametreler (sa� taraftakiler) de varsay�lan arg�manlar almak zorundad�r.
A�a��daki �rnek izin verilmez:

                    void print(int x=10, int y); // not allowed
yani default arg�man tan�mlarken her zaman en sonda veya sa� taraf�ndaki t�m arg�manlar default olmal� Bu kurald�r.

2- E�er birden fazla parametre varsay�lan bir arg�man al�yorsa, sol taraftaki parametre genellikle kullan�c� taraf�ndan a��k�a belirlenecek olan
parametre olmal�d�r.

Varsay�lan arg�manlar yeniden bildirilemez
------------------------------------------

Bir kez bildirildikten sonra, bir varsay�lan arg�man ayn� dosyada tekrar bildirilemez. Yani, bir fonksiyonun �nceden bildirimi (forward declaration) 
ve bir fonksiyon tan�m� i�in, varsay�lan arg�man ya �nceden bildirimde ya da fonksiyon tan�m�nda bildirilebilir, ancak her ikisinde birden bildirilemez.

                    #include <iostream>

                    void print(int x, int y=4); // forward declaration

                    void print(int x, int y=4) // error: redefinition of default argument
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

*** BEST -> varsay�lan arg�man� �nceden bildiride (forward declaration) bildirmek, fonksiyon tan�m�nda bildirmektense daha iyidir, ��nk� �nceden
            bildiri, di�er dosyalar taraf�ndan daha olas� bir �ekilde g�r�lecektir (�zellikle bir ba�l�k dosyas�ndaysa).

foo.h da
                    #ifndef FOO_H
                    #define FOO_H
                    void print(int x, int y=4);
                    #endif
main.cpp de
                    #include "foo.h"
                    #include <iostream>

                    void print(int x, int y)
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

                    int main()
                    {
                        print(5);

                        return 0;
                    }


Yukar�daki �rnekte, print() fonksiyonu i�in varsay�lan arg�man� kullanabiliyoruz ��nk� main.cpp, varsay�lan arg�man� tan�mlayan bir �nceden bildirim
i�eren foo.h dosyas�n� i�eriyor.

*** BEST -> E�er bir fonksiyonun �nceden bildirimi varsa (�zellikle bir ba�l�k dosyas�nda ise), varsay�lan arg�man� oraya koyun. Aksi takdirde, 
            varsay�lan arg�man� fonksiyon tan�m�na koyun.

Varsay�lan Arg�manlar ve Fonksiyon A��r� Y�kleme
------------------------------------------------

Varsay�lan arg�manlara sahip fonksiyonlar a��r� y�klenebilir. �rne�in, a�a��daki gibi bir durum m�mk�nd�r:

                    #include <string>

                    void print(std::string)
                    {
                    }

                    void print(char=' ')
                    {
                    }

                    int main()
                    {
                        print("Hello, world"); // print(std::string) olarak ��z�l�r
                        print('a'); // print(char) olarak ��z�l�r
                        print(); // print(char) olarak ��z�l�r

                        return 0;
                    }

print() fonksiyonu �a�r�s�, kullan�c�n�n a��k�a print(' ') �eklinde �a��rd���n� varsayarak i�lev g�r�r ve bu da print(char) olarak ��z�l�r.

�imdi bu durumu d���nelim:

                    void print(int x);
                    void print(int x, int y = 10);
                    void print(int x, double y = 20.5);

Varsay�lan de�erlere sahip parametreler, bir fonksiyon a��r� y�klemesini ay�rt eder (yani yukar�daki �rnek derlenebilir).
Ancak, bu t�r fonksiyonlar potansiyel olarak belirsiz fonksiyon �a�r�lar�na neden olabilir. �rne�in:

                    print(1, 2);    // print(int, int) olarak ��z�l�r
                    print(1, 2.5);  // print(int, double) olarak ��z�l�r
                    print(1);       // belirsiz fonksiyon �a�r�s�

Son durumda, derleyiciye `print(1)` ifadesinin `print(int)` olarak m� yoksa ikinci parametresi varsay�lan bir de�ere sahip iki fonksiyondan birine 
mi ��z�lmesi gerekti�ini belirleme yetene�i yoktur. Sonu�, belirsiz bir fonksiyon �a�r�s�d�r.

�zet

Varsay�lan arg�manlar, kullan�c�n�n iste�e ba�l� olarak ge�ip ge�meyece�i parametreler i�in de�erler belirtmek i�in kullan��l� bir mekanizma sa�lar.
C++'da s�k�a kullan�l�rlar ve gelecek derslerde s�k�a kar��la�acaks�n�z.
*/