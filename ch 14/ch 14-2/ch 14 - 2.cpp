#include <iostream>

int main()
{
    return 0;
}
/*
14.6 � Eri�im Fonksiyonlar�
---------------------------
�nceki ders 14.5 -- public ve private �yeler ve Eri�im Belirleyiciler'de, public ve private eri�im d�zeylerini tart��t�k.
Hat�rlatmak gerekirse, s�n�flar genellikle veri �yelerini private yapar ve private �yelere public taraf�ndan do�rudan eri�ilemez.

A�a��daki Date s�n�f�n� d���n�n:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{ 2020 };
                    int m_month{ 10 };
                    int m_day{ 14 };

                public:
                    void print() const
                    {
                        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
                    }
                };

                int main()
                {
                    Date d{};  // bir Date nesnesi olu�tur
                    d.print(); // tarihi yazd�r

                    return 0;
                }
Bu s�n�f, t�m tarihi yazd�rmak i�in bir print() member fonksiyonu sa�lar, ancak bu, kullan�c�n�n yapmak istedi�i �ey i�in yeterli
olmayabilir. �rne�in, bir Date nesnesinin kullan�c�s� year'� almak isterse ne olur? Ya da year'� farkl� bir de�ere de�i�tirmek 
isterse? Bunu yapamazlar, ��nk� m_yil �zeldir (ve bu nedenle public taraf�ndan do�rudan eri�ilemez).
Baz� s�n�flar i�in, �zel bir member de�i�kenin de�erini almak veya ayarlamak uygun olabilir (s�n�f�n ne yapt��� ba�lam�nda).

Eri�im Fonksiyonlar�
--------------------
Bir eri�im fonksiyonu, �zel bir member de�i�kenin de�erini almak veya de�i�tirmek i�in g�revi olan basit bir public member fonksiyonudur.
Eri�im fonksiyonlar� iki �e�ittir: getter'lar ve setter'lar. Getter'lar (bazen eri�imciler olarak da adland�r�l�r) �zel bir �ye
de�i�kenin de�erini d�nd�ren public member fonksiyonlard�r. Setter'lar (bazen de�i�tiriciler olarak da adland�r�l�r) �zel bir member 
de�i�kenin de�erini ayarlayan public member fonksiyonlard�r.

Getter'lar genellikle const yap�l�r, b�ylece hem const hem de non-const nesnelerde �a�r�labilirler. Setter'lar non-const olmal�d�r,
b�ylece veri �yelerini de�i�tirebilirler.

�rnekleme ama�l� olarak, Date s�n�f�m�z� tam bir getter ve setter setine sahip olacak �ekilde g�ncelleyelim:

                #include <iostream>

                class Date
                {
                private:
                    int m_year { 2020 };
                    int m_month { 10 };
                    int m_day { 14 };

                public:
                    void print()
                    {
                        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
                    }

                    int getYear() const { return m_year; }        // year i�in getter
                    void setYear(int year) { m_year = year; }     // year i�in setter

                    int getMonth() const  { return m_month; }     // month i�in getter
                    void setMonth(int month) { m_month = month; } // month i�in setter

                    int getDay() const { return m_day; }          // day i�in getter
                    void setDay(int day) { m_day = day; }         // day i�in setter
                };

                int main()
                {
                    Date d{};
                    d.setYear(2021);
                    std::cout << "The year is: " << d.getYear() << '\n';

                    return 0;
                }
                Bu, �unu yazd�r�r:

                The year is: 2021
Eri�im Fonksiyonu Adland�rma
----------------------------
Eri�im fonksiyonlar�n� adland�rmak i�in ortak bir kural yoktur. Ancak, di�erlerinden daha pop�ler olan birka� adland�rma kural�
vard�r.

"get" ve "set" ile �ne ��kanlar:
                int getDay() const { return m_day; }  // getter
                void setDay(int day) { m_day = day; } // setter
"get" ve "set" �neklerini kullanman�n avantaj�, bunlar�n eri�im fonksiyonlar� oldu�unu a��k�a belirtir (ve �a�r�lmas� ucuz
olmal�d�r).

�nek yok:
                int day() const { return m_day; }  // getter
                void day(int day) { m_day = day; } // setter
Bu stil daha �zl�d�r ve hem getter hem de setter i�in ayn� ad� kullan�r (ikisini ay�rt etmek i�in fonksiyon a��r� y�klemeye
g�venir). C++ standart k�t�phanesi bu kural� kullan�r.
�nek olmayan kural�n dezavantaj�, bu i�lemin g�n �yesinin de�erini ayarlad��� konusunda �zellikle a��k olmamas�d�r:

                d.day(5); // bu, g�n �yesinin de�erini 5'e ayarlad��� gibi g�r�n�yor mu?
Anahtar Bilgi
�zel veri �yelerini "m_" ile �ne ��karmak i�in en iyi nedenlerden biri, veri �yeleri ve getter'lar�n ayn� ad� ta��mas�n� 
�nlemektir (C++ bunu desteklemez, ancak Java gibi di�er diller yapar).

Yaln�zca "set" �neki:

                int day() const { return m_day; }     // getter
                void setDay(int day) { m_day = day; } // setter

Yukar�dakilerden hangisini se�ece�iniz ki�isel tercihinize ba�l�d�r. Ancak, setter'lar i�in "set" �nekini kullanman�z� �iddetle 
�neririz. Getter'lar ya "get" �neki veya hi� �nek kullanabilir.

�pucu

Setter'lar�n�za "set" �neki ekleyin, b�ylece nesnenin durumunu de�i�tirdikleri daha belirgin hale gelir.
Getter'lar de�eri veya const lvalue referans�n� d�nd�rmelidir.
Getter'lar verilere "salt okunur" eri�im sa�lamal�d�r. Bu nedenle, en iyi uygulama, �yenin bir kopyas�n� yapman�n ucuz olup
olmad���na ba�l� olarak ya de�eri ya da const lvalue referans�n� d�nd�rmeleridir.

Eri�im Fonksiyonlar�na �li�kin Endi�eler
----------------------------------------
Eri�im fonksiyonlar�n�n ne zaman kullan�lmas� veya ka��n�lmas� gerekti�i konusunda olduk�a fazla tart��ma vard�r. Bir�ok
geli�tirici, eri�im fonksiyonlar�n�n kullan�lmas�n�n iyi s�n�f tasar�m�n� ihlal etti�ini savunur (bu konu kolayl�kla t�m bir 
kitab� doldurabilir).
�imdilik, pragmatik bir yakla��m �neriyoruz. S�n�flar�n�z� olu�tururken a�a��dakileri g�z �n�nde bulundurun:

- S�n�f�n�z�n de�i�mezleri yoksa ve �ok say�da eri�im fonksiyonuna ihtiya� duyuyorsa, bir yap� kullanmay� d���n�n 
  (veri �yeleri geneldir) ve �yelere do�rudan eri�im sa�lay�n.
- Eri�im fonksiyonlar� yerine davran��lar� veya eylemleri uygulamay� tercih edin. �rne�in, setAlive(bool) setter'� yerine bir 
  kill() ve revive() fonksiyonu uygulay�n.
- Yaln�zca genelin makul bir �ekilde bir bireysel �yenin de�erini almas� veya ayarlamas� gereken durumlarda eri�im fonksiyonlar�
  sa�lay�n.

E�er public bir eri�im fonksiyonu sa�layacaksak verileri neden gizli tutal�m ki?

14.7 � Veri �yelerine referans d�nd�ren member i�levler
----------------------------------------------------
12.12 dersinde -- Referansla d�nme ve adresle d�nme, referansla d�nme konusunu ele ald�k. �zellikle, �Referansla d�nd�r�len 
nesnenin fonksiyon d�nd�kten sonra da var olmas� gerekti�ini� belirttik. Bu, yerel de�i�kenleri referans olarak d�nd�rmememiz 
gerekti�i anlam�na gelir, ��nk� yerel de�i�ken yok edildikten sonra referans sallan�r durumda kal�r. Ancak, genellikle referansla
d�nd�r�len fonksiyon parametreleri veya statik s�reye sahip de�i�kenler (statik yerel de�i�kenler veya global de�i�kenler) genellikle
fonksiyon d�nd�kten sonra yok edilmezler.

�rne�in:

                // �ki std::string nesnesi al�r, alfabetik olarak �nce geleni d�nd�r�r
                const std::string& firstAlphabetical(const std::string& a, const std::string& b)
                {
                    return (a < b) ? a : b; // std::string �zerinde operator< kullanarak hangisinin alfabetik olarak �nce geldi�ini
                                            // belirleyebiliriz
                }

                int main()
                {
                    std::string hello { "Hello" };
                    std::string world { "World" };

                    std::cout << firstAlphabetical(hello, world); // hello veya world referansla d�nd�r�l�r

                    return 0;
                }
member fonksiyonlar de referansla d�nd�rebilir ve referansla d�nd�rmenin g�venli oldu�u durumlar i�in member olmayan fonksiyonlarla ayn� 
kurallar� izlerler. Ancak, member fonksiyonlar�n tart��mam�z gereken bir ek durumu vard�r: veri �yelerini referansla d�nd�ren member 
fonksiyonlar.
Bu, en s�k getter eri�im fonksiyonlar�yla g�r�l�r, bu y�zden bu konuyu getter member fonksiyonlar� kullanarak �rneklendirece�iz. 
Ancak, bu konunun bir veri �yesine referans d�nd�ren herhangi bir member fonksiyon i�in ge�erli oldu�unu unutmay�n.

Veri �yelerini de�erle d�nd�rmek pahal� olabilir
------------------------------------------------
A�a��daki �rne�i d���n�n:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    std::string getName() const { return m_name; } //  getter de�erle d�nd�r�r
                };

                int main()
                {
                    Employee joe{};
                    joe.setName("Joe");
                    std::cout << joe.getName();

                    return 0;
                }

Bu �rnekte, getName() eri�im fonksiyonu std::string m_name'i de�erle d�nd�r�r. Bu yap�lacak en g�venli �ey olsa da, bu ayn� 
zamanda getName() her �a�r�ld���nda m_name'in pahal� bir kopyas�n�n yap�laca�� anlam�na gelir. Eri�im fonksiyonlar�n�n genellikle
�ok�a �a�r�ld��� g�z �n�ne al�nd���nda, bu genellikle en iyi se�enek de�ildir.

Veri �yelerini lvalue referans�yla d�nd�rme
-------------------------------------------
member fonksiyonlar, veri �yelerini de (const) lvalue referans�yla d�nd�rebilir.

Veri �yeleri, i�inde bulunduklar� nesnenin ayn� �mr�ne sahiptir. member fonksiyonlar her zaman bir nesne �zerinde �a�r�ld���ndan ve
bu nesnenin �a��ran�n kapsam�nda var olmas� gerekti�inden, bir member fonksiyonun bir veri �yesini (const) lvalue referans�yla d�nd�rmesi
genellikle g�venlidir (fonksiyon d�nd���nde �a��ran�n kapsam�nda hala var olan member referansla d�nd�r�l�r).

Yukar�daki �rne�i g�ncelleyelim, b�ylece getName() m_name'i const lvalue referans�yla d�nd�rs�n:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const std::string& getName() const { return m_name; } //  getter const referansla d�nd�r�r
                };

                int main()
                {
                    Employee joe{}; // joe fonksiyonun sonuna kadar var olur
                    joe.setName("Joe");

                    std::cout << joe.getName(); // joe.m_name'i referansla d�nd�r�r

                    return 0;
                }
�imdi joe.getName() �a�r�ld���nda, joe.m_name �a��rana referansla d�nd�r�l�r, b�ylece bir kopya yapma ihtiyac�n� ortadan kald�r�r.
�a��ran daha sonra bu referans� joe.m_name'i konsola yazd�rmak i�in kullan�r.
Joe, �a��ran�n kapsam�nda main() i�levinin sonuna kadar var oldu�u i�in, joe.m_name'e olan referans da ayn� s�re boyunca ge�erlidir.

Ana i�g�r�

Bir veri �yesine (const) lvalue referans� d�nd�rmek tamamd�r. Fonksion d�nd�kten sonra �a��ran�n kapsam�nda hala var olan i�sel 
nesne (veri �yesini i�eren), herhangi bir d�nd�r�len referans�n ge�erli olmas�n� sa�lar.
Bir member fonksiyonun bir veri �yesine referans d�nd�rmesi durumunda, d�n�� t�r� veri �yesinin t�r�yle e�le�melidir

public olarak, referansla d�nd�ren bir member fonksiyonun d�n�� t�r�, d�nd�r�len veri �yesinin t�r�yle e�le�melidir. Yukar�daki 
�rnekte, m_name std::string t�r�ndedir, bu y�zden getName() const std::string& d�nd�r�r.

Bir std::string_view d�nd�rmek, her fonksiyon �a�r�ld���nda ge�ici bir std::string_view olu�turulmas�n� ve d�nd�r�lmesini
gerektirir. Bu gereksiz yere verimsizdir. E�er �a��ran bir std::string_view istiyorsa, d�n���m� kendisi yapabilir.

**** BEST -> Bir referans d�nd�ren bir member fonksiyon, gereksiz d�n���mleri �nlemek i�in d�nd�r�len veri �yesiyle ayn� t�rde bir 
             referans d�nd�rmelidir.

Getter'lar i�in, derleyicinin d�nd�r�len �yeden d�n�� t�r�n� ��karmas�n� sa�lamak i�in auto kullanmak, d�n���m olmad���ndan emin 
olman�n kullan��l� bir yoludur:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } // `auto` kullanarak m_name'den d�n�� t�r�n� ��kar�r
                };

                int main()
                {
                    Employee joe{}; // joe, fonksiyonun sonuna kadar var olur
                    joe.setName("Joe");

                    std::cout << joe.getName(); // joe.m_name'i referans olarak d�nd�r�r

                    return 0;
                }
Ancak, bir auto d�n�� t�r� kullanmak, getter'�n d�n�� t�r�n� belgelendirme a��s�ndan belirsizle�tirir. �rne�in:

                const auto& getName() const { return m_name; } // `auto` kullanarak m_name'den d�n�� t�r�n� ��kar�r

Bu fonksiyonun asl�nda ne t�rde bir dize d�nd�rd��� belirsizdir (std::string, std::string_view, C tarz� dize veya tamamen farkl�
bir �ey olabilir!). Bu nedenle, genellikle a��k d�n�� t�rlerini tercih ederiz.

Rvalue Ge�ici Nesneler ve Referansla D�n��
------------------------------------------
Biraz dikkatli olmam�z gereken bir durum var. Yukar�daki �rnekte, joe fonksiyonun sonuna kadar var olan bir lvalue nesnesidir. 
Bu nedenle, joe.getName() taraf�ndan d�nd�r�len referans da fonksiyonun sonuna kadar ge�erli olacakt�r.

Peki ya ge�ici nesnemiz bir rvalue ise (�rne�in, de�er d�nd�ren bir fonksiyonun d�n�� de�eri gibi)? Rvalue nesneler,
olu�turulduklar� tam ifadenin sonunda yok edilir. Bir rvalue nesnesi yok edildi�inde, bu rvalue'un �yelerine olan herhangi bir
referans ge�ersiz k�l�n�r ve sallan�r kal�r ve bu t�r referanslar�n kullan�lmas� tan�ms�z davran��a yol a�ar.

Bu nedenle, bir rvalue nesnesinin bir �yesine olan bir referans, yaln�zca rvalue nesnesinin olu�turuldu�u tam ifade i�inde g�venle
kullan�labilir.

Uyar�

Bir rvalue nesnesi, olu�turuldu�u tam ifadenin sonunda yok edilir. Rvalue nesnesinin �yelerine olan herhangi bir referans o 
noktada sallan�r kal�r. Bir rvalue nesnesinin bir �yesine olan bir referans, yaln�zca rvalue nesnesinin olu�turuldu�u tam ifade 
i�inde g�venle kullan�labilir.
Bu konuyla ilgili baz� durumlar� inceleyelim:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } //  getter const referans olarak d�nd�r�r
                };

                // createEmployee() bir �al��an'� de�er olarak d�nd�r�r (bu, d�nd�r�len de�erin bir rvalue oldu�u anlam�na gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    // Durum 1: tamam: rvalue s�n�f nesnesinin �yesine d�nen referans� ayn� ifadede kullan
                    std::cout << createEmployee("Frank").getName();

                    // Durum 2: k�t�: rvalue s�n�f nesnesinin �yesine d�nen referans� daha sonra kullanmak �zere kaydet
                    const std::string& ref { createEmployee("Garbo").getName() }; // createEmployee()'�n d�n�� de�eri yok 
                                                                                  // edildi�inde referans dangling olur
                    std::cout << ref; // undefined behavior

                    // Durum 3: tamam: referansla d�nen de�eri daha sonra kullanmak �zere yerel de�i�kene kopyala
                    std::string val { createEmployee("Hans").getName() }; // referanslanan �yenin bir kopyas�n� yapar
                    std::cout << val; // okay: val is independent of referenced member

                    return 0;
                }

createEmployee() �a�r�ld���nda, bir Employee nesnesini de�er olarak d�nd�recektir. Bu d�nd�r�len Employee nesnesi, createEmployee()
�a�r�s�n� i�eren tam ifadenin sonuna kadar var olacakt�r. Bu rvalue nesnesi yok edildi�inde, bu nesnenin �yelerine olan herhangi
bir referans dangling olacakt�r.

Durum 1'de, createEmployee("Frank")'i �a��r�yoruz, bu bir rvalue Employee nesnesi d�nd�r�r. Daha sonra bu rvalue nesnesinde
getName() �a�r�s� yapar�z, bu m_name'e bir referans d�nd�r�r. Bu referans hemen ard�ndan konsola ismi yazd�rmak i�in kullan�l�r. 
Bu noktada, createEmployee("Frank") �a�r�s�n� i�eren tam ifade sona erer ve rvalue nesnesi ve �yeleri yok edilir. Bu noktadan
sonra rvalue nesnesi veya �yeleri kullan�lmad���ndan, bu durum sorunsuzdur.

Durum 2'de, sorunlarla kar��la��yoruz. �ncelikle, createEmployee("Garbo") bir rvalue nesnesi d�nd�r�r. Daha sonra getName() 
�a�r�s� yaparak bu rvalue'nin m_name �yesine bir referans al�r�z. Bu m_name �yesi daha sonra ref'i ba�latmak i�in kullan�l�r.
Bu noktada, createEmployee("Garbo") �a�r�s�n� i�eren tam ifade sona erer ve rvalue nesnesi ve �yeleri yok edilir. Bu, ref'in
dangling kalmas�na neden olur. Dolay�s�yla, sonraki ifadede ref'i kulland���m�zda, dangling bir referansa eri�iyoruz ve tan�ms�z
bir davran�� sonucu olu�ur.

Anahtar ��g�r�

Bir tam ifadenin de�erlendirilmesi, bu tam ifadenin bir ba�lat�c� olarak kullan�lmas�ndan sonra sona erer. Bu, nesnelerin ayn�
t�rden bir rvalue ile ba�lat�lmas�na izin verir (��nk� rvalue, ba�latma ger�ekle�tikten sonra yok edilmez).

Peki ya daha sonra kullanmak �zere bir �yeyi referansla d�nd�ren bir fonksiyondan bir de�er kaydetmek istiyorsak ne olur?
-------------------------------------------------------------------------------------------------------------------------
D�nd�r�len referans� yerel bir referans de�i�kenini ba�latmak yerine, d�nd�r�len referans� referans olmayan bir yerel de�i�keni
ba�latmak i�in kullanabiliriz.
Durum 3'te, d�nd�r�len referans� referans olmayan yerel de�i�ken val'i ba�latmak i�in kullan�yoruz. Bu, referanslanan �yenin val
i�ine kopyalanmas�na neden olur. Ba�latmadan sonra, val referanstan ba��ms�z olarak var olur. Bu nedenle, rvalue nesnesi sonradan
yok edildi�inde, val bu durumdan etkilenmez. Bu nedenle, val, gelecekteki ifadelerde sorunsuz bir �ekilde ��kt� olarak
kullan�labilir.

Referansla d�nd�ren member i�levlerini g�venli bir �ekilde kullanma
----------------------------------------------------------------
Rvalue i�sel nesnelerle potansiyel tehlikeye ra�men, getter'lar�n de�erle de�il, const referansla d�nd�rme konusunda pahal� olan
t�rleri d�nd�rmesi gelenekseldir.
Bu durumda, bu t�r i�levlerden d�nen de�erleri nas�l g�venli bir �ekilde kullanabilece�imizi konu�al�m. Yukar�daki �rnekteki �� 
durum, �� ana noktay� g�stermektedir:

Referansla d�nd�ren bir member fonksiyonun d�n�� de�erini hemen kullanmay� tercih edin (durum 1'de g�sterildi�i gibi). Bu, hem lvalue
hem de rvalue nesnelerle �al��t���ndan, bunu her zaman yaparsan�z, sorunlardan ka��nm�� olursunuz.

D�nd�r�len bir referans� daha sonra kullanmak i�in "kaydetmeyin" (durum 2'de g�sterildi�i gibi), i�sel nesnenin bir lvalue
oldu�undan emin olmad�k�a. E�er bunu bir rvalue i�sel nesne ile yaparsan�z, art�k sallanan referans� kulland���n�zda tan�ms�z bir
davran�� ortaya ��kar.

E�er d�nd�r�len bir referans� daha sonra kullanmak i�in saklaman�z gerekiyorsa ve i�sel nesnenin bir lvalue oldu�undan emin 
de�ilseniz, d�nd�r�len referans� bir referans olmayan yerel de�i�kenin ba�lat�c�s� olarak kullan�n, bu da referansla d�nd�r�len 
�yenin yerel de�i�kene bir kopyas�n� yapar (durum 3'te g�sterildi�i gibi).

**** BEST -> Bir member fonksiyonun d�n�� de�erini hemen kullanmay� tercih edin, i�sel nesne bir rvalue oldu�unda sallanan 
             referanslarla ilgili sorunlar� �nlemek i�in.

�zel veri �yelerine non-const referanslar� d�nd�rmeyin
------------------------------------------------------
Bir referans, referans� al�nan nesnenin ayn�s� gibi davrand���ndan, non-const bir referans d�nd�ren bir member i�lev, o �yeye
do�rudan eri�im sa�lar (member �zel olsa bile).

�rne�in:

                #include <iostream>

                class Foo
                {
                private:
                    int m_value{ 4 }; // �zel �ye

                public:
                    auto& value() { return m_value; } // non-const bir referans d�nd�r�r (bunu yapmay�n)
                };

                int main()
                {
                    Foo f{};                // f.m_value varsay�lan de�er 4'e ba�lat�l�r
                    f.value() = 5;          // m_value = 5'in e�de�eri
                    std::cout << f.value(); // 5 yazd�r�r

                    return 0;
                }

Value() fonksiyonu m_value'ya non-const bir referans d�nd�rd��� i�in, �a��ran bu referans� kullanarak m_value'ya do�rudan
eri�ebilir (ve m_value'nun de�erini de�i�tirebilir). Bu, �a��ran�n eri�im kontrol sistemini atlatmas�na izin verir.

Const member fonksiyonlar, veri �yelerine non-const referanslar� d�nd�remez
------------------------------------------------------------------------
Bir const member i�levin, �yelere non-const bir referans d�nd�rmesine izin verilmez. Bu mant�kl�d�r - bir const member i�levin,
nesnenin durumunu de�i�tirmesine izin verilmez, ne de nesnenin durumunu de�i�tirecek fonksiyonlar� �a��rmas�na izin verilir. Nesnenin
de�i�tirilmesine yol a�abilecek herhangi bir �ey yapmamal�d�r.

E�er bir const member i�levin, bir �yeye non-const bir referans d�nd�rmesine izin verilseydi, �a��raya o �yeyi do�rudan de�i�tirme
yolunu vermi� olurdu. Bu, bir const member fonksiyonun amac�na ayk�r�d�r.

14.8 � Veri Gizlemenin (Kaps�lleme) Faydalar�
---------------------------------------------
Bir �nceki dersimizde (14.5 -- Public ve private �yeler ve eri�im belirleyiciler), bir s�n�f�n member de�i�kenlerinin genellikle
private yap�ld���n� belirtmi�tik. S�n�flar hakk�nda ilk kez ��renen programc�lar, bunu neden yapmak isteyece�inizi anlamakta 
genellikle zorlan�rlar. Sonu�ta, de�i�kenlerinizi private yapmak, bunlar�n public eri�ime a��k olmamas� anlam�na gelir.
En iyi ihtimalle, s�n�flar�n�z� yazarken daha fazla i� yapman�z gerekecektir. En k�t� ihtimalle, bu tamamen anlams�z g�r�nebilir
(�zellikle private member verilerine public eri�im fonksiyonlar� sa�l�yorsak).

Bu sorunun yan�t� o kadar temel ki, bu konuda t�m bir dersi harcayaca��z!

Bir benzetmeyle ba�layal�m.

Modern hayatta, bir�ok mekanik veya elektronik cihaza eri�imimiz var. Televizyonunuzu bir uzaktan kumanda ile a��p kapat�rs�n�z.
Araban�z� gaz pedal�na basarak ileri hareket ettirirsiniz. I��klar�n�z� bir anahtar �evirerek a�ars�n�z. T�m bu cihazlar�n ortak
bir �zelli�i var: Size, anahtar eylemleri ger�ekle�tirmenizi sa�layan basit bir kullan�c� aray�z� (bir dizi d��me, bir pedal, bir
anahtar vb.) sunarlar.

Bu cihazlar�n nas�l �al��t��� sizden gizlenmi�tir. Uzaktan kumandan�zdaki d��meye bast���n�zda, kumandan�n televizyonunuzla nas�l
ileti�im kurdu�unu bilmenize gerek yoktur. Araban�zdaki gaz pedal�na bast���n�zda, i�ten yanmal� motorun tekerlekleri nas�l 
�evirdi�ini bilmenize gerek yoktur. Bir foto�raf �ekti�inizde, sens�rlerin ����� nas�l toplad���n� ve bu ����� pikselle�tirilmi� 
bir g�r�ntmember nas�l d�n��t�rd���n� bilmenize gerek yoktur.

Aray�z ve uygulaman�n ayr�lmas�, nesneleri nas�l �al��t�klar�n� anlamadan kullanmam�za izin verir - bunun yerine, onlarla nas�l
etkile�im kuraca��m�z� anlamam�z yeterlidir. Bu, bu nesneleri kullanman�n karma��kl���n� b�y�k �l��de azalt�r ve etkile�ime 
girebilece�imiz nesne say�s�n� art�r�r.

S�n�f t�rlerinde uygulama ve aray�zler
--------------------------------------
Benzer nedenlerle, aray�z ve uygulaman�n ayr�lmas� programlamada da yararl�d�r. Ancak �nce, s�n�f t�rleriyle ilgili olarak aray�z
ve uygulama ne demek, onu tan�mlayal�m.

Bir s�n�f t�r�n�n aray�z�, bir s�n�f t�r�n�n kullan�c�s�n�n s�n�f t�r�n�n nesneleriyle nas�l etkile�im kuraca��n� tan�mlar.
Yaln�zca public �yelere s�n�f t�r�n�n d���ndan eri�ilebildi�i i�in, bir s�n�f t�r�n�n public �yeleri, onun aray�z�n� olu�turur. 
Bu nedenle, public �yelerden olu�an bir aray�z bazen public aray�z olarak adland�r�l�r.

Bir aray�z, bir s�n�f�n yazar� ile s�n�f�n kullan�c�s� aras�nda implicit bir s�zle�medir. Mevcut bir aray�z herhangi bir �ekilde 
de�i�tirilirse, onu kullanan herhangi bir kod bozulabilir. Bu nedenle, s�n�f t�rlerimiz i�in aray�zlerin iyi tasarlanm�� ve stabil
(�ok fazla de�i�meyen) olmas�n� sa�lamak �nemlidir.

Bir s�n�f t�r�n�n uygulamas�, s�n�f�n istendi�i gibi davranmas�n� sa�layan kodu i�erir. Bu, hem verileri depolayan �ye
de�i�kenleri hem de program mant���n� i�eren ve member de�i�kenleri manip�le eden member fonksiyonlar�n�n g�vdelerini i�erir.

Veri Gizleme (Kaps�lleme)
-------------------------
Programlamada, veri gizleme (ayn� zamanda bilgi gizleme veya veri soyutlama olarak da adland�r�l�r), bir program tan�ml� veri 
t�r�n�n uygulamas�n� kullan�c�lardan gizleyerek aray�z ve uygulaman�n ayr�lmas�n� sa�lamak i�in kullan�lan bir tekniktir.

Terimler
--------
Kaps�lleme terimi bazen veri gizlemeyi ifade etmek i�in de kullan�l�r. Ancak, bu terim ayn� zamanda verilerin ve fonksiyonlar�n
bir araya getirilmesini (eri�im kontrollerine bak�lmaks�z�n) ifade etmek i�in de kullan�l�r, bu y�zden kullan�m� belirsiz olabilir.
Bu ders serisinde, t�m kaps�llenmi� s�n�flar�n veri gizlemeyi uygulad���n� varsayaca��z.
Veri gizleme, bir C++ s�n�f t�r�nde uygulamak basittir.

�ncelikle, s�n�f t�r�n�n veri �yelerinin �zel (private) oldu�undan emin oluruz (b�ylece kullan�c� bunlara do�rudan eri�emez).
member fonksiyonlar�n�n g�vdelerindeki ifadeler zaten kullan�c�lara do�rudan eri�ilemez, bu y�zden ba�ka bir �ey yapmam�za gerek yok.

�kinci olarak, member fonksiyonlar�n public (public) oldu�undan emin oluruz, b�ylece kullan�c� onlar� �a��rabilir.

Bu kurallar� takip ederek, bir s�n�f t�r�n�n kullan�c�s�n� nesneleri public aray�z� kullanarak manip�le etmeye zorlar�z ve onlar�
uygulama ayr�nt�lar�na do�rudan eri�mekten al�koyar�z.

C++'da tan�mlanan s�n�flar�n veri gizlemeyi kullanmas� gerekmektedir. Asl�nda, standart k�t�phane taraf�ndan sa�lanan t�m s�n�flar
tam olarak bunu yapar. Di�er yandan, yap�lar (structs) veri gizlemeyi kullanmamal�d�r, ��nk� public olmayan �yelere sahip olmak
onlar�n topluluklar (aggregates) olarak ele al�nmas�n� engeller.

S�n�flar� bu �ekilde tan�mlamak, s�n�f yazar� i�in biraz ekstra i� gerektirir. Ve s�n�f�n kullan�c�lar�n�n public aray�z�
kullanmas�n� gerektirmek, member de�i�kenlere do�rudan public eri�im sa�lamaktan daha zahmetli g�r�nebilir. Ancak bunu yapmak, 
s�n�f�n yeniden kullan�labilirli�ini ve bak�m�n� te�vik eden bir�ok yararl� fayda sa�lar. Bu faydalar� tart��mak i�in dersin geri
kalan�n� harcayaca��z.

Veri gizleme, s�n�flar� daha kolay kullan�labilir hale getirir ve karma��kl��� azalt�r
--------------------------------------------------------------------------------------
Bir s�n�f� kullanmak i�in, nas�l uyguland���n� bilmek zorunda de�ilsiniz. Yaln�zca aray�z�n� anlaman�z gerekir: hangi �ye
fonksiyonlar�n public olarak kullan�labilir oldu�u, hangi arg�manlar� ald�klar� ve hangi de�erleri d�nd�rd�kleri. �rne�in:

                #include <iostream>
                #include <string_view>

                int main()
                {
                    std::string_view sv{ "Merhaba, d�nya!" };
                    std::cout << sv.length();

                    return 0;
                }
Bu k�sa programda, std::string_view'in nas�l uyguland���na dair ayr�nt�lar bize a��klanmaz. Bir std::string_view'in ka� tane veri
�yesi oldu�unu, ne olduklar�n�, ne adland�r�ld�klar�n� veya ne t�r olduklar�n� g�remeyiz. length() member fonksiyonunun g�r�nt�lenen
dizenin uzunlu�unu nas�l d�nd�rd���n� bilmiyoruz.

Ve harika olan k�sm�, bilmemiz gerekmiyor! Program sadece �al���r. Tek ihtiyac�m�z olan, std::string_view t�r�nde bir nesneyi
nas�l ba�lataca��m�z� ve length() member fonksiyonunun ne d�nd�rd���n� bilmektir.

Bu t�r ayr�nt�lar hakk�nda endi�elenmek zorunda olmamak, programlar�n�z�n karma��kl���n� dramatik bir �ekilde azalt�r, bu da
hatalar� azalt�r. Di�er t�m nedenlerden daha fazla, bu, kaps�llemenin ana avantaj�d�r.

std::string, std::vector veya std::cout'un nas�l uyguland���n� anlaman�z gerekti�ini d���n�n, onlar� kullanabilmek i�in C++ ne
kadar daha karma��k olurdu!

Veri gizleme, de�i�mezleri korumam�za olanak sa�lar
---------------------------------------------------
S�n�flara giri� dersinde (14.2 -- S�n�flara Giri�), s�n�f de�i�mezleri kavram�n� tan�tt�k. Bunlar, bir nesnenin ge�erli bir durumda
kalabilmesi i�in nesnenin �mr� boyunca do�ru olmas� gereken ko�ullard�r.

A�a��daki program� d���n�n:

                #include <iostream>
                #include <string>

                struct Employee // �yeler varsay�lan olarak public'tir
                {
                    std::string name{ "John" };
                    char firstInitial{ 'J' }; // name'in ilk harfiyle e�le�melidir

                    void print() const
                    {
                        std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
                    }
                };

                int main()
                {
                    Employee e{}; // varsay�lan olarak "John" ve 'J'
                    e.print();

                    e.name = "Mark"; // employee'nin ad�n� "Mark" olarak de�i�tir
                    e.print(); // yanl�� harfi yazd�r�r

                    return 0;
                }

                Bu program �unu yazd�r�r:

                John has first initial J
                Mark has first initial J
Employee struct'�m�z�n bir s�n�f de�i�mezi vard�r ki bu da firstInitial'�n her zaman name'in ilk karakterine e�it olmas� 
gerekti�idir. E�er bu hi�bir zaman do�ru olmazsa, print() fonksiyonu hatal� �al���r.

Name �yesi public oldu�u i�in, main() i�indeki kod e.name'i "Mark" olarak ayarlayabilir ve firstInitial �yesi g�ncellenmez. 
De�i�mezimiz bozulmu� olur ve ikinci print() �a�r�m�z bekledi�imiz gibi �al��maz.

Kullan�c�lara bir s�n�f�n uygulamas�na do�rudan eri�im hakk� verdi�imizde, t�m de�i�mezleri korumaktan onlar sorumlu olur -- ki 
bunu do�ru bir �ekilde veya hi� yapmayabilirler. Bu, kullan�c� �zerinde �ok fazla karma��kl�k yarat�r.

Bu program� yeniden yazal�m, member de�i�kenlerimizi private yapal�m ve bir Employee'nin ad�n� ayarlamak i�in bir member fonksiyonu
a���a ��karal�m:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee // �yeler varsay�lan olarak private'tir
                {
                    std::string m_name{};
                    char m_firstInitial{};

                public:
                    void setName(std::string_view name)
                    {
                        m_name = name;
                        m_firstInitial = name.front(); // `name`in ilk harfini almak i�in std::string::front() kullan�r
                    }

                    void print() const
                    {
                        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
                    }
                };

                int main()
                {
                    Employee e{};
                    e.setName("John");
                    e.print();

                    e.setName("Mark");
                    e.print();

                    return 0;
                }
                
                Bu program art�k beklenildi�i gibi �al���r:
                John has first initial J
                Mark has first initial M
Kullan�c�n�n perspektifinden tek de�i�iklik, name'e do�rudan bir de�er atamak yerine, setName() member i�levini �a��r�yor olmalar�d�r,
bu fonksiyon hem m_name'i hem de m_firstInitial'� ayarlar. Kullan�c�n�n bu de�i�mezi koruma y�k� ortadan kalkar!

Veri gizleme, daha iyi hata tespiti (ve i�lemesi) yapmam�za olanak sa�lar
-------------------------------------------------------------------------
Yukar�daki programda, m_firstInitial'�n m_name'in ilk karakteriyle e�le�mesi gerekti�i de�i�mezi, m_firstInitial'�n m_name'den 
ba��ms�z olarak var olmas� nedeniyle vard�r. Bu belirli de�i�mezi, m_firstInitial'� ilk harfi d�nd�ren bir member i�levle 
de�i�tirerek kald�rabiliriz:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{ "John" };

                public:
                    void setName(std::string_view name)
                    {
                        m_name = name;
                    }

                    // `m_name`in ilk harfini almak i�in std::string::front() kullan�r
                    char firstInitial() const { return m_name.front(); }

                    void print() const
                    {
                        std::cout << "Employee " << m_name << " has first initial " << firstInitial() << '\n';
                    }
                };

                int main()
                {
                    Employee e{}; // varsay�lan olarak "John"
                    e.setName("Mark");
                    e.print();

                    return 0;
                }
Ancak, bu program�n ba�ka bir s�n�f de�i�mezi var. Bir an durun ve ne oldu�unu belirlemeye �al���n. Burada bekleriz ve bu kuru 
boyay� izleriz...

Cevap, m_name'in bo� bir string olmamas� gerekti�idir (��nk� her Employee'nin bir ad� olmal�d�r). E�er m_name bo� bir string 
olarak ayarlan�rsa, hemen k�t� bir �ey olmaz. Ancak daha sonra firstInitial() �a�r�l�rsa, std::string'in front() �yesi bo� 
stringin ilk harfini almay� deneyecek ve bu tan�ms�z bir davran��a yol a�acakt�r.b�deal olarak, m_name'in hi�bir zaman bo�
olmamas�n� isteriz.

E�er kullan�c�n�n m_name �yesine public eri�imi olsayd�, sadece m_name = "" diyebilirlerdi ve bunun olmas�n� engelleyecek hi�bir
�ey yapamazd�k.

Ancak, kullan�c�y� m_name'i public aray�z fonksiyonu setName() arac�l���yla ayarlamaya zorlad���m�z i�in, setName() kullan�c�n�n 
ge�erli bir ad ge�ti�ini do�rulayabilir. E�er ad bo� de�ilse, o zaman onu m_name'e atayabiliriz. E�er ad bo� bir string ise,
bir dizi �ey yapabiliriz mesela:

*- Ad� "" olarak ayarlamak i�in yap�lan iste�i g�rmezden gelin ve �a��raya d�n�n.
*- Assert ��k��� yap�n.
*- Bir istisna f�rlat�n.
*- Hokey pokey yap�n. Bekleyin, bu de�il. :))

Buradaki nokta, k�tmember kullanmay� tespit edebiliriz ve sonra onu en uygun oldu�unu d���nd���m�z �ekilde ele alabiliriz. Bu t�r
durumlar� nas�l etkili bir �ekilde ele alaca��m�z ba�ka bir g�n�n konusudur.

Veri gizleme, uygulama ayr�nt�lar�n� de�i�tirmeyi, mevcut programlar� bozmadan m�mk�n k�lar
-------------------------------------------------------------------------------------------
Bu basit �rne�i d���n�n:

                #include <iostream>

                struct Something
                {
                    int value1 {};
                    int value2 {};
                    int value3 {};
                };

                int main()
                {
                    Something something;
                    something.value1 = 5;
                    std::cout << something.value1 << '\n';
                }
Bu program iyi �al���rken, s�n�f�n uygulama ayr�nt�lar�n� �u �ekilde de�i�tirmeye karar verirsek ne olurdu?

                #include <iostream>

                struct Something
                {
                    int value[3] {}; // 3 de�erli bir dizi kullan�r
                };

                int main()
                {
                    Something something;
                    something.value1 = 5;
                    std::cout << something.value1 << '\n';
                }

Hen�z dizileri ele almad�k, ama bundan endi�elenmeyin. Buradaki nokta, bu program�n art�k derlenmemesi ��nk� value1 adl� member art�k
var olmamas� ve main() i�indeki bir ifadenin hala bu tan�mlay�c�y� kullan�yor olmas�d�r.

Veri gizleme, s�n�flar�n nas�l uyguland���n� de�i�tirme yetene�i sa�lar, bunu kullan�lan programlar� bozmadan yapar.
--------------------------------------------------------------------------------------------------------------------
��te m_value1'e eri�mek i�in fonksiyonlar� kullanan bu s�n�f�n orijinal s�r�m�n�n kaps�llenmi� versiyonu:

                #include <iostream>

                class Something
                {
                private:
                    int m_value1 {};
                    int m_value2 {};
                    int m_value3 {};

                public:
                    void setValue1(int value) { m_value1 = value; }
                    int getValue1() const { return m_value1; }
                };

                int main()
                {
                    Something something;
                    something.setValue1(5);
                    std::cout << something.getValue1() << '\n';
                }
�imdi, s�n�f�n uygulamas�n� bir diziye geri d�nd�relim:

                #include <iostream>

                class Something
                {
                private:
                    int m_value[3]; // not: bu s�n�f�n uygulamas�n� de�i�tirdik!

                public:
                    // Yeni uygulamay� yans�tacak �ekilde t�m member fonksiyonlar� g�ncellememiz gerekiyor
                    void setValue1(int value) { m_value[0] = value; }
                    int getValue1() const { return m_value[0]; }
                };

                int main()
                {
                    // Ama s�n�f� kullanan programlar�m�z� g�ncellememize gerek yok!
                    Something something;
                    something.setValue1(5);
                    std::cout << something.getValue1() << '\n';
                }

S�n�f�n public aray�z�n� de�i�tirmedi�imiz i�in, bu aray�z� kullanan program�m�z hi� de�i�medi ve hala ayn� �ekilde i�lev g�r�yor.

Benzer �ekilde, e�er gnomeler ( c�ce ) gece evinize s�z�p TV kumandan�z�n i�ini farkl� (ama uyumlu) bir teknolojiyle de�i�tirseydi, 
muhtemelen fark etmezdiniz!

Aray�zleri olan s�n�flar�n hata ay�klamas� daha kolayd�r
--------------------------------------------------------
Son olarak, kaps�lleme, bir �eylerin yanl�� gitti�i durumlarda bir program�n hata ay�klamas�na yard�mc� olabilir. Genellikle bir
program�n do�ru �al��mamas�n�n nedeni, member de�i�kenlerimizden birinin yanl�� bir de�er almas�d�r. Herkesin member de�i�keni do�rudan
ayarlayabilmesi durumunda, hangi kod par�as�n�n asl�nda member de�i�kenini yanl�� de�ere de�i�tirdi�ini bulmak zor olabilir. Bu, �ye
de�i�keni de�i�tiren her ifadeyi breakpoint'e getirebilir - ve bunlardan �ok say�da olabilir..

Ancak, bir member yaln�zca bir member fonksiyonu arac�l���yla de�i�tirilebiliyorsa, o zaman yaln�zca tek bir fonksiyonu kesme noktas�na
getirebilir ve her �a�r�n�n de�eri nas�l de�i�tirdi�ini izleyebilirsiniz. Bu, su�lunun kim oldu�unu belirlemeyi �ok daha
kolayla�t�rabilir.

member fonksiyonlar yerine Non-member fonksiyonlar� tercih edin
---------------------------------------------------------
Bir fonksiyon Non-member fonksiyon olarak uygulanabiliyorsa, onu bir member fonksiyon yerine Non-member fonksiyon olarak uygulamay� d���n�n.
Bu, bir�ok avantaj sa�lar:

*- Non-member fonksiyonlar, s�n�f�n�z�n aray�z�n�n bir par�as� de�ildir. Bu nedenle, s�n�f�n�z�n aray�z� daha k���k ve daha basit olacak,
   bu da s�n�f�n�z� anlamay� kolayla�t�racakt�r.
*- Non-member fonksiyonlar, kaps�llemeyi art�r�r, ��nk� bu t�r fonksiyonlar s�n�f�n public aray�z� arac�l���yla �al��mal�d�r.
   Uygulamaya do�rudan eri�me konusunda bir cazibe yoktur, sadece bu uygun oldu�u i�in.
*- Non-member fonksiyonlar, bir s�n�f�n uygulamas�na yap�lan de�i�iklikler yap�l�rken dikkate al�nmaz.
*- Non-member fonksiyonlar�n hata ay�klamas� genellikle daha kolayd�r.
Uygulamaya �zg� veri ve mant��� i�eren Non-member fonksiyonlar, s�n�f�n yeniden kullan�labilir b�l�mlerinden ayr�labilir.
**** BEST -> M�mk�n oldu�unda, Fonksiyonlar� Non-member olarak uygulamay� tercih edin (�zellikle uygulamaya �zg� veri veya mant���
             i�eren i�levler).

Yazar�n notu

�rneklerimizin bir�o�u, �rnekleri m�mk�n oldu�unca �zl� tutmak amac�yla bu en iyi uygulamay� uygulamamaktad�r.

��te en k�t�den en iyiye do�ru �� benzer �rnek:

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }

                    // En k�t�s�: print() member fonksiyonu, getter'�n var oldu�u halde m_flavor'a do�rudan eri�im kullan�r
                    void print() const
                    {
                        std::cout << "The yogurt has flavor " << m_flavor << '\n';
                    }
                };

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    y.print();

                    return 0;
                }
Yukar�daki en k�t� versiyondur. Print() member fonksiyonu, lezzet i�in zaten bir getter oldu�unda m_flavor'a do�rudan eri�im 
kullan�r. E�er s�n�f�n uygulamas� her zaman g�ncellenirse, print() de muhtemelen de�i�tirilmek zorunda kalacakt�r. Print() 
taraf�ndan yazd�r�lan string, uygulamaya �zg�d�r (bu s�n�f� kullanan ba�ka bir uygulama ba�ka bir �ey yazd�rmak isteyebilir, bu da
s�n�f�n klonlanmas�n� veya de�i�tirilmesini gerektirecektir).

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }

                    // Daha iyi: print() member i�levinin �yelere do�rudan eri�imi yok
                    void print(std::string_view prefix) const
                    {
                        std::cout << prefix << ' ' << getFlavor() << '\n';
                    }
                };

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    y.print("The yogurt has flavor");

                    return 0;
                }
Yukar�daki versiyon daha iyidir, ancak hala harika de�ildir. print() hala bir member fonksiyonu, ancak en az�ndan art�k hi�bir
veri �yesine do�rudan eri�im yapm�yor. E�er s�n�f�n uygulamas� her zaman g�ncellenirse, print()'in g�ncellenip g�ncellenmeyece�ini
belirlemek i�in de�erlendirilmesi gerekecektir (ama olmayacak). print() fonksiyonu i�in �nek art�k parametrize edilmi�tir, bu da
�neki Non-member fonksiyon main() i�ine ta��mam�za olanak sa�lar. Ancak fonksiyon hala �eylerin nas�l yazd�r�laca��na dair
k�s�tlamalar getirir (�r. her zaman �nek, bo�luk, lezzet, yeni sat�r olarak yazd�r�r). E�er bu, belirli bir uygulaman�n 
ihtiya�lar�n� kar��lam�yorsa, ba�ka bir fonksiyon eklenmesi gerekecektir.

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }
                };

                // En iyi: Non-member fonksiyon print() s�n�f aray�z�n�n bir par�as� de�ildir
                void print(const Yogurt& y)
                {
                        std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
                }

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    print(y);

                    return 0;
                }
Yukar�daki versiyon en iyisidir. print() art�k bir Non-member i�lev. Hi�bir �yeye do�rudan eri�im yapmaz. E�er s�n�f�n uygulamas�
her zaman de�i�irse, print()'in hi�bir �ekilde de�erlendirilmesine gerek kalmaz. Ek olarak, her uygulama kendi print() i�levini
sa�layabilir ve tam olarak o uygulaman�n istedi�i �ekilde yazd�rabilir.

S�n�f member bildiriminin s�ras�
--------------------------------
Bir s�n�f�n d���nda kod yazarken, onlar� kullanmadan �nce de�i�kenleri ve fonksiyonlar� bildirmemiz gereklidir. Ancak, bir s�n�f�n
i�inde, bu k�s�tlama yoktur. 14.3 -- member ��levler dersinde belirtildi�i gibi, �yelerimizi istedi�imiz herhangi bir s�rayla
s�ralayabiliriz.

Peki onlar� nas�l s�ralamal�y�z?
--------------------------------
Burada iki d���nce ekol� vard�r:

�nce �zel �yelerinizi listeler, ard�ndan public member i�levlerinizi listeler. Bu, kullanmadan �nce bildirme tarz�n� izler.
S�n�f kodunuza bakan herkes, veri �yelerinizi nas�l tan�mlad���n�z� g�r�r, bu da uygulama ayr�nt�lar�n� okumay� ve anlamay�
kolayla�t�rabilir.

�nce public �yelerinizi listeler ve �zel �yelerinizi en alta koyar. S�n�f�n�z� kullanan biri public aray�zle ilgilendi�i i�in, 
public �yelerinizi �nce koymak, onlar�n ihtiya� duyduklar� bilgileri en �ste koyar ve uygulama ayr�nt�lar�n� (en az �nemli 
olanlar�) sona koyar.

Modern C++'ta, ikinci y�ntem (public �yeler �nce gelir) genellikle di�er geli�tiricilerle payla��lacak kod i�in daha yayg�n olarak
�nerilir.

**** BEST -> �nce public �yeleri, ard�ndan protected �yeleri ve en son private �yeleri bildirin. Bu, public aray�z� �ne ��kar�r ve
             uygulama ayr�nt�lar�n� �nemsizle�tirir.

Yazar�n notu

Bu site �zerindeki �rneklerin �o�u, �nerilenin aksine bildirim s�ras�n� kullan�r. Bu k�smen tarihseldir, ancak ayr�ca bu s�ran�n,
dil mekaniklerini ��renirken ve i�lerin nas�l �al��t���n� ay�klarken daha sezgisel oldu�unu da buluyoruz.
*/