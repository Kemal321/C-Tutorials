#include <iostream>

int main()
{
    return 0;
}
/*
15.1 � Gizli �this� i�aret�isi ve �ye fonksiyon zincirleme
----------------------------------------------------------
Yeni programc�lar�n s�n�flar hakk�nda s�k�a sordu�u sorulardan biri, "Bir �ye fonksiyonu �a�r�ld���nda, C++'�n hangi nesnenin
�zerinde �a�r�ld���n� nas�l takip etti�i"dir.

�ncelikle, �al��abilece�imiz basit bir s�n�f tan�mlayal�m. Bu s�n�f, bir tam say� de�erini kapsular ve bu de�eri almak ve 
ayarlamak i�in baz� eri�im fonksiyonlar� sa�lar:

                #include <iostream>

                class Simple
                {
                private:
                    int m_id{};

                public:
                    Simple(int id)
                        : m_id{ id }
                    {
                    }

                    int getID() { return m_id; }
                    void setID(int id) { m_id = id; }

                    void print() { std::cout << m_id; }
                };

                int main()
                {
                    Simple simple{1};
                    simple.setID(2);

                    simple.print();

                    return 0;
                }

                Beklendi�i gibi, bu program sonucu �retir:

                2
Bir �ekilde, simple.setID(2); �a�r�s�n� yapt���m�zda, C++ setID() fonksiyonunun simple nesnesi �zerinde �al��mas� gerekti�ini ve 
m_id'nin asl�nda simple.m_id'ye at�fta bulundu�unu biliyor.

Cevap, C++'�n "this" ad�nda gizli bir i�aret�i kullanmas�d�r! Bu derste, bu konuyu daha ayr�nt�l� olarak inceleyece�iz.

Gizli this i�aret�isi
---------------------
Her �ye fonksiyonun i�inde, this anahtar kelimesi, mevcut implicit nesnenin adresini tutan bir const i�aret�idir.
�o�u zaman, this'i a��k�a belirtmeyiz, ama kan�tlamak i�in belirtebiliriz:

                #include <iostream>

                class Simple
                {
                private:
                    int m_id{};

                public:
                    Simple(int id)
                        : m_id{ id }
                    {
                    }

                    int getID() { return m_id; }
                    void setID(int id) { m_id = id; }

                    void print() { std::cout << this->m_id; } // `this` i�aret�isini kullanarak �rt�l� nesneye eri�in ve
                                                              // operator-> ile m_id �yesini se�in
                };

                int main()
                {
                    Simple simple{ 1 };
                    simple.setID(2);

                    simple.print();

                    return 0;
                }

                Bu, �nceki �rnekle ayn� �ekilde �al���r ve yazd�r�r:

                2
�nceki iki �rnekteki print() �ye fonksiyonlar�n�n tamamen ayn� �eyi yapt���na dikkat edin:


                void print() { std::cout << m_id; }       // this'in �rt�l� kullan�m�
                void print() { std::cout << this->m_id; } // this'in a��k kullan�m�

Ortaya ��kt��� �zere, birincisi ikincisinin k�sa yoludur. Programlar�m�z� derledi�imizde, derleyici, �rt�l� nesneyi referans 
veren herhangi bir �yeyi bu �ekilde �rt�l� olarak �ne al�r. Bu, kodumuzu daha �zl� tutmam�za yard�mc� olur ve this->'yi a��k�a
yazmak zorunda kalmadan tekrarlamay� �nler.

Bir hat�rlatma -> Bir nesneye i�aret eden bir i�aret�iden bir �yeyi se�mek i�in -> kullan�r�z. this->m_id, (*this).m_id ile 
e�de�erdir. ��aret�iler ve referanslarla �ye se�imi konusunu 13.10 dersinde ele al�yoruz.

Peki this nas�l ayarlan�r?
--------------------------
Bu fonksiyon �a�r�s�na daha yak�ndan bakal�m:

                simple.setID(2);
Fonksiyon setID(2)'ye yap�lan �a�r�n�n sadece bir arg�man� oldu�u gibi g�r�nse de, asl�nda iki arg�man� vard�r! Derlendi�inde,
derleyici simple.setID(2); ifadesini a�a��daki gibi yeniden yazar:

                Simple::setID(&simple, 2); // simple'�n bir nesne �nekinden bir fonksiyon arg�man�na d�n��t���ne dikkat edin!
Bu art�k sadece standart bir fonksiyon �a�r�s�d�r ve simple nesnesi (daha �nce bir nesne �neki olan) art�k fonksiyona bir arg�man 
olarak adres �zerinden ge�irilir.

Ama bu sadece yan�t�n yar�s�. Fonksiyon �a�r�s�n�n art�k ek bir arg�man� oldu�undan, �ye fonksiyon tan�m� da bu arg�man� bir 
parametre olarak kabul etmek (ve kullanmak) i�in de�i�tirilmelidir. ��te setID() i�in orijinal �ye fonksiyon tan�m�m�z:

                void setID(int id) { m_id = id; }
Derleyicinin fonksiyonlar� nas�l yeniden yazd���, uygulamaya �zg� bir ayr�nt�d�r, ancak sonu� �una benzer bir �eydir:

                static void setID(Simple* const this, int id) { this->m_id = id; }
setID fonksiyonumuzun yeni bir en sol parametresi olan this oldu�una dikkat edin, bu bir const i�aret�idir (yani yeniden 
i�aret edilemez, ancak i�aret�inin i�eri�i de�i�tirilebilir). m_id �yesi de this->m_id olarak yeniden yaz�lm��t�r, bu i�aret�iyi 
kullan�r.

�leri d�zey okuyucular i�in

Bu ba�lamda, static anahtar kelimesi, fonksiyonun s�n�f�n nesneleriyle ili�kili olmad��� anlam�na gelir, ancak bunun yerine 
s�n�f�n kapsam b�lgesindeki normal bir fonksiyonmu� gibi ele al�n�r. Statik �ye fonksiyonlar� 15.7 dersinde -- Statik �ye 
fonksiyonlar� konusunda ele al�yoruz.

Hepsini bir araya getirerek:

simple.setID(2) �a�r�s�n� yapt���m�zda, derleyici asl�nda Simple::setID(&simple, 2) �a�r�s�n� yapar ve simple fonksiyona adres 
�zerinden ge�irilir.
Fonksiyonun, simple'�n adresini alan this ad�nda gizli bir parametresi vard�r.
setID() i�indeki �ye de�i�kenler, simple'a i�aret eden this-> ile �ne al�n�r. Yani derleyici this->m_id'yi de�erlendirdi�inde,
asl�nda simple.m_id'yi ��z�ml�yor.
�yi haber �u ki, bunlar�n hepsi otomatik olarak ger�ekle�ir ve bunun nas�l �al��t���n� hat�rlaman�z�n veya hat�rlamaman�z�n
ger�ekten bir �nemi yoktur. Hat�rlaman�z gereken tek �ey, t�m statik olmayan �ye fonksiyonlar�n, fonksiyonun �a�r�ld��� nesneyi
referans veren bir this i�aret�isine sahip olmas�d�r.

Anahtar nokta �udur yani, T�m statik olmayan �ye fonksiyonlar, �rt�l� nesnenin adresini tutan bir this const i�aret�isinesahiptir.
this her zaman �zerinde i�lem yap�lan nesneyi g�sterir

Yeni programc�lar bazen ka� tane this i�aret�isi oldu�u konusunda kar���kl�k ya�arlar. Her �ye fonksiyonun, �rt�l� nesneyi 
g�steren tek bir this i�aret�i parametresi vard�r. Dikkate al�n:

                int main()
                {
                    Simple a{1}; // this = &a inside the Simple constructor
                    Simple b{2}; // this = &b inside the Simple constructor
                    a.setID(3); // this = &a inside member function setID()
                    b.setID(4); // this = &b inside member function setID()

                    return 0;
                }

this i�aret�isinin, a veya b nesnesinin adresini tuttu�una dikkat edin, bu da a veya b nesnesi �zerinde bir �ye fonksiyon �a�r�p 
�a��rmad���m�za ba�l�d�r. ��nk� this sadece bir fonksiyon parametresidir (ve bir �ye de�ildir), bu nedenle s�n�f�n�z�n �rneklerini
bellek a��s�ndan daha b�y�k yapmaz.

A��k�a this'e ba�vurma
----------------------
�o�u zaman, this i�aret�isine a��k�a ba�vurman�z gerekmez. Ancak, bunu yapman�n faydal� olabilece�i birka� durum vard�r:

�ncelikle, ayn� ad� ta��yan bir veri �yesi ve bir parametresi olan bir �ye fonksiyonunuz varsa, bunlar� this kullanarak ay�rt 
edebilirsiniz:

                struct Something
                {
                    int data{}; // m_ �neki kullan�lm�yor ��nk� bu bir yap�

                    void setData(int data)
                    {
                        this->data = data; // this->data �yedir, data yerel parametredir
                    }
                };

Bu Something s�n�f�n�n data ad�nda bir �yesi var. setData() fonksiyonunun da data ad�nda bir parametresi var. setData() fonksiyonu
i�inde, data fonksiyon parametresine at�fta bulunur (��nk� fonksiyon parametresi veri �yesini g�lgede b�rak�r), bu y�zden veri 
�yesine ba�vurmak istiyorsak, this->data kullan�r�z.

Baz� geli�tiriciler, bir �yeye ba�vurduklar�n� a��k�a belirtmek i�in t�m s�n�f �yelerine this-> eklemeyi tercih eder.
Bunu yapman�z� �nermiyoruz, ��nk� bu genellikle kodunuzu az fayda kar��l���nda daha az okunabilir hale getirir. "m_" �neki,
�zel �ye de�i�kenleri ile �ye olmayan (yerel) de�i�kenleri ay�rt etmenin daha �zl� bir yoludur.

*this'i d�nd�rme
----------------
�kincisi, bir �ye fonksiyonun d�n�� de�eri olarak �rt�l� nesneyi d�nd�rmesi bazen faydal� olabilir. Bunu yapman�n temel nedeni,
�ye fonksiyonlar�n "zincirlenmesine" izin vermek, b�ylece tek bir ifadede ayn� nesne �zerinde birka� �ye fonksiyon �a�r�labilir!
Bu, fonksiyon zincirleme (veya y�ntem zincirleme) olarak adland�r�l�r.

std::cout kullanarak birka� metin par�as�n� ��kt� olarak verdi�iniz bu yayg�n �rne�i d���n�n:

std::cout << "Hello, " << userName;
Derleyici, yukar�daki kod par�ac���n� �u �ekilde de�erlendirir:

(std::cout << "Hello, ") << userName;
�ncelikle, operator<<, std::cout ve "Hello, " dize sabitini kullanarak konsola "Hello, " yazd�r�r. Ancak, bu bir ifadenin par�as�
oldu�undan, operator<<'in de bir de�er (veya void) d�nd�rmesi gerekir. E�er operator<< void d�nd�r�rse, k�smen de�erlendirilmi�
ifade �u �ekilde olur:

void{} << userName;
bu a��k�a hi�bir anlam ifade etmez (ve derleyici bir hata atar). Bunun yerine, operator<<, bu durumda std::cout olan ge�irilen 
ak�� nesnesini d�nd�r�r. Bu �ekilde, ilk operator<< de�erlendirildikten sonra, �unu elde ederiz:

(std::cout) << userName;
bu da kullan�c�n�n ad�n� yazd�r�r.

Bu �ekilde, yaln�zca bir kez std::cout belirtmemiz gerekir ve ard�ndan istedi�imiz kadar metin par�as�n� operator<< kullanarak 
bir araya getirebiliriz. Her operator<< �a�r�s�, std::cout'u d�nd�r�r, b�ylece sonraki operator<< �a�r�s�, std::cout'u sol i�lenen
olarak kullan�r.

Bu t�r bir davran��� �ye fonksiyonlar�m�zda da uygulayabiliriz. A�a��daki s�n�f� d���n�n:

                class Calc
                {
                private:
                    int m_value{};

                public:

                    void add(int value) { m_value += value; }
                    void sub(int value) { m_value -= value; }
                    void mult(int value) { m_value *= value; }

                    int getValue() { return m_value; }
                };

E�er 5 eklemek, 3 ��karmak ve 4 ile �arpmak isterseniz, bunu yapman�z gerekir:

                #include <iostream>

                int main()
                {
                    Calc calc{};
                    calc.add(5); // void d�nd�r�r
                    calc.sub(3); // void d�nd�r�r
                    calc.mult(4); // void d�nd�r�r

                    std::cout << calc.getValue() << '\n';

                    return 0;
                }

Ancak, her fonksiyonun *this'i referans olarak d�nd�rmesi durumunda, �a�r�lar� bir araya getirebiliriz. ��te "zincirlenebilir" 
fonksiyonlara sahip Calc'�n yeni versiyonu:

                class Calc
                {
                private:
                    int m_value{};

                public:
                    Calc& add(int value) { m_value += value; return *this; }
                    Calc& sub(int value) { m_value -= value; return *this; }
                    Calc& mult(int value) { m_value *= value; return *this; }

                    int getValue() { return m_value; }
                };
add(), sub() ve mult()'un art�k *this'i referans olarak d�nd�rd���ne dikkat edin. Sonu� olarak, a�a��dakileri yapmam�za izin verir:

                #include <iostream>

                int main()
                {
                    Calc calc{};
                    calc.add(5).sub(3).mult(4); // method chaining

                    std::cout << calc.getValue() << '\n';

                    return 0;
                }
�� sat�r� etkili bir �ekilde tek bir ifadeye s�k��t�rd�k! Bunun nas�l �al��t���na daha yak�ndan bakal�m.

�ncelikle, calc.add(5) �a�r�l�r, bu da m_value'ye 5 ekler. add() daha sonra *this'i d�nd�r�r, bu da sadece calc'a referanst�r,
bu y�zden calc, sonraki de�erlendirmede kullan�lacak nesne olacakt�r. Sonraki ad�mda calc.sub(3) de�erlendirilir, 
bu da m_value'den 3 ��kar�r ve yine calc'� d�nd�r�r. Son olarak, calc.mult(4) m_value'yi 4 ile �arpar ve calc'� d�nd�r�r,
bu daha fazla kullan�lmaz ve bu nedenle g�z ard� edilir.
Her fonksiyon, calc'� �al��t�r�ld�k�a de�i�tirdi�inden, calc'�n m_value'si �imdi (((0 + 5) - 3) * 4) de�erini i�erir, bu da 8'dir.
Bu, this'in en yayg�n a��k kullan�m�d�r ve �ye fonksiyonlar�n zincirlenebilir olmas� mant�kl� oldu�unda bunu d���nmelisiniz.
��nk� this her zaman implicit nesneyi g�sterir, bu y�zden onu dereferans yapmadan �nce null i�aret�i olup olmad���n� kontrol 
etmemiz gerekmez.

Bir s�n�f� varsay�lan durumuna s�f�rlama
----------------------------------------
E�er s�n�f�n�z�n bir varsay�lan yap�c� fonksiyonu varsa, mevcut bir nesneyi varsay�lan durumuna geri d�nd�rme yolunu sa�lamakla
ilgilenebilirsiniz. �nceki derslerde belirtildi�i gibi (14.12 -- Yap�c�lar� Devretme), yap�c�lar yaln�zca yeni nesnelerin 
ba�lat�lmas� i�indir ve do�rudan �a�r�lmamal�d�r. Bunu yapmak beklenmeyen bir davran��a yol a�ar.

Bir s�n�f� varsay�lan bir duruma geri d�nd�rmenin en iyi yolu, bir reset() �ye fonksiyonu olu�turmak, bu fonksiyonun yeni bir 
nesne olu�turmas�n� (varsay�lan yap�c�y� kullanarak) ve daha sonra bu yeni nesneyi mevcut �rt�l� nesneye atamas�n� sa�lamakt�r:

                void reset()
                {
                    *this = {}; // yeni bir nesneyi de�er ba�lat�n ve �rt�l� nesnenin �zerine yaz�n
                }

��te bu reset() fonksiyonunu g�steren tam bir program:

                #include <iostream>

                class Calc
                {
                private:
                    int m_value{};

                public:
                    Calc& add(int value) { m_value += value; return *this; }
                    Calc& sub(int value) { m_value -= value; return *this; }
                    Calc& mult(int value) { m_value *= value; return *this; }

                    int getValue() { return m_value; }

                    void reset() { *this = {}; }
                };


                int main()
                {
                    Calc calc{};
                    calc.add(5).sub(3).mult(4);

                    std::cout << calc.getValue() << '\n'; // 8 yazd�r�r

                    calc.reset();

                    std::cout << calc.getValue() << '\n'; // 0 yazd�r�r

                    return 0;
                }
this ve const nesneler
----------------------
Statik olmayan �ye fonksiyonlar i�in, this bir const i�aret�isidir ve non-const bir de�ere i�aret eder (yani this ba�ka bir �eye 
i�aret edemez, ancak i�aret edilen nesne de�i�tirilebilir). Const �ye fonksiyonlar� ile this, const bir i�aret�iye const bir 
de�ere i�aret eder (yani i�aret�i ba�ka bir �eye i�aret edemez, ayr�ca i�aret edilen nesne de de�i�tirilemez).

Const olmayan bir �yeyi const bir nesne �zerinde �a��rmaya �al��mak, biraz karma��k hatalar olu�turabilir:

error C2662: 'int Something::getValue(void)': cannot convert 'this' pointer from 'const Something' to 'Something &'
error: passing 'const Something' as 'this' argument discards qualifiers [-fpermissive]

Const olmayan bir �ye fonksiyonu const bir nesne �zerinde �a��rd���m�zda, �rt�l� this fonksiyon parametresi non-const bir nesneye
const bir i�aret�idir. Ancak arg�man�n t�r� const bir nesneye const bir i�aret�idir. Const bir nesneye i�aret eden bir i�aret�iyi 
non-const bir nesneye i�aret eden bir i�aret�iye d�n��t�rmek, const niteli�inin at�lmas�n� gerektirir, bu da �rt�l� olarak 
yap�lamaz. Baz� derleyiciler taraf�ndan olu�turulan derleyici hatas�, derleyicinin b�yle bir d�n���m� ger�ekle�tirmek �zere talep
edildi�inden �ikayet etti�ini yans�t�r.

Bu nedenle this bir i�aret�i ve bir referans de�il

this i�aret�isi her zaman �rt�l� nesneyi g�sterir (ve e�er tan�ms�z bir davran��a neden olan bir �ey yapmad�ysak hi�bir zaman null
i�aret�i olamaz), bu y�zden this'in neden bir i�aret�i oldu�unu ve bir referans olmad���n� merak ediyor olabilirsiniz.
Cevap basit: this C++'a eklendi�inde, referanslar hen�z mevcut de�ildi.

E�er this bug�n C++ diline eklenseydi, hi� ��phesiz bir referans olurdu, bir i�aret�i de�il. Java ve C# gibi daha modern 
C++ benzeri dillerde, this bir referans olarak uygulanm��t�r.

15.2 � S�n�flar ve Ba�l�k Dosyalar�
-----------------------------------
�imdiye kadar yazd���m�z t�m s�n�flar, �ye fonksiyonlar� do�rudan s�n�f tan�m�n�n i�inde uygulayabilecek kadar basitti. �rne�in,
i�te t�m �ye fonksiyonlar�n Date s�n�f� tan�m�n�n i�inde tan�mland��� basit bir Date s�n�f�:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day)
                        : m_year { year }
                        , m_month { month }
                        , m_day { day}
                    {
                    }

                    void print() const { std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; };

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const { return m_day; }
                };

                int main()
                {
                    Date d { 2015, 10, 14 };
                    d.print();

                    return 0;
                }
Ancak, s�n�flar daha uzun ve karma��k hale geldik�e, t�m �ye fonksiyon tan�mlar�n�n s�n�f�n i�inde olmas�, s�n�f�n y�netilmesini
ve �al���lmas�n� zorla�t�rabilir. Zaten yaz�lm�� bir s�n�f� kullanmak, sadece onun genel aray�z�n� (genel �ye fonksiyonlar)
anlamay� gerektirir, s�n�f�n kaputunun alt�nda nas�l �al��t���n� de�il. �ye fonksiyon uygulamalar�, s�n�f�n kullan�lmas�yla 
ilgili olmayan ayr�nt�larla genel aray�z� kar��t�r�r.

Bu durumu ele almak i�in, C++ bize s�n�f�n "bildirim" k�sm�n� "uygulama" k�sm�ndan ay�rma olana�� sa�lar, yani �ye fonksiyonlar� 
s�n�f tan�m�n�n d���nda tan�mlar.

��te ayn� Date s�n�f�, yap�c� fonksiyon ve print() �ye fonksiyonlar� s�n�f tan�m�n�n d���nda tan�mlanm�� olarak. Bu �ye
fonksiyonlar�n prototiplerinin hala s�n�f tan�m�n�n i�inde var oldu�una dikkat edin (��nk� bu fonksiyonlar�n s�n�f tipi tan�m�n�n
bir par�as� olarak bildirilmesi gerekiyor), ancak ger�ek uygulama d��ar�ya ta��nd�:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day); // constructor declaration

                    void print() const; // print function declaration

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const  { return m_day; }
                };

                Date::Date(int year, int month, int day) // constructor definition
                    : m_year{ year }
                    , m_month{ month }
                    , m_day{ day }
                {
                }

                void Date::print() const // print function definition
                {
                    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
                };

                int main()
                {
                    const Date d{ 2015, 10, 14 };
                    d.print();

                    return 0;
                }
�ye fonksiyonlar, s�n�f tipinin d���nda tan�mlan�r, t�pk� �ye olmayan fonksiyonlar gibi. Tek fark, �ye fonksiyon adlar�n�n �n�ne
s�n�f tipinin ad�n� (bu durumda, Date::) eklememiz gerekti�idir, b�ylece derleyici, bir �ye olmayan� de�il, o s�n�f tipinin bir 
�yesini tan�mlad���m�z� bilir.

Eri�im fonksiyonlar�n�n s�n�f tan�m�n�n i�inde tan�mland���n� b�rakt���m�za dikkat edin. ��nk� eri�im fonksiyonlar� genellikle
sadece bir sat�rd�r, bu fonksiyonlar� s�n�f tan�m�n�n i�inde tan�mlamak, minimal d�zeyde kar���kl�k yarat�rken, onlar� s�n�f
tan�m�n�n d���na ta��mak, �ok fazla ekstra kod sat�r�na neden olur. Bu nedenle, eri�im fonksiyonlar�n�n tan�mlar� (ve di�er basit,
tek sat�rl�k fonksiyonlar) genellikle s�n�f tan�m�n�n i�inde b�rak�l�r.

*** BEST -> Basit, tek sat�rl�k bir uygulamaya sahip �ye fonksiyonlar, s�n�f tan�m�n�n i�inde tan�mlanabilir. Karma��k veya �ok
            sat�rl� bir uygulamaya sahip �ye fonksiyonlar, bir kaynak dosyas�nda, s�n�f tan�m�n�n d���nda tan�mlanmal�d�r.

S�n�f tan�mlar�n� bir ba�l�k dosyas�na koymak
---------------------------------------------
Bir s�n�f� bir kaynak (.cpp) dosyas�n�n i�inde tan�mlarsan�z, bu s�n�f yaln�zca o belirli kaynak dosyas� i�inde kullan�labilir.
Daha b�y�k programlarda, yazd���m�z s�n�flar� birden �ok kaynak dosyas�nda kullanmak yayg�nd�r.

2.11 -- Ba�l�k dosyalar� dersinde, fonksiyon bildirimlerini bir ba�l�k dosyas�na koyabilece�inizi ��rendiniz. Sonra bu fonksiyon
bildirimlerini birden �ok kod dosyas�na (veya hatta birden �ok projeye) #include edebilirsiniz. S�n�flar da farkl� de�ildir. Bir
s�n�f tan�mlamas� bir ba�l�k dosyas�na konabilir ve sonra s�n�f t�r�n� kullanmak isteyen herhangi bir dosyaya #include edilebilir.

Fonksiyonlar�n aksine, kullan�lmak �zere sadece bir ileri bildirime ihtiya� duyan, derleyici genellikle bir t�r�n kullan�labilmesi
i�in s�n�f�n (veya herhangi bir program tan�ml� t�r�n) tam tan�m�n� g�rmeye ihtiya� duyar. Bu, derleyicinin �yelerin nas�l
bildirildi�ini anlamas� ve bunlar�n do�ru bir �ekilde kullan�ld���ndan emin olmas� gerekti�i ve bir t�r�n nesnelerinin ne kadar
b�y�k oldu�unu hesaplayabilmesi i�in gereklidir. Bu y�zden ba�l�k dosyalar�m�z genellikle bir s�n�f�n tam tan�m�n� i�erir,
sadece s�n�f�n ileri bildirimini de�il.

S�n�f ba�l�k ve kod dosyalar�n�z� adland�rma
--------------------------------------------
�o�u zaman, s�n�flar s�n�f ile ayn� ad� ta��yan ba�l�k dosyalar�nda tan�mlan�r ve s�n�f�n d���nda tan�mlanan herhangi bir �ye 
fonksiyon, s�n�f ile ayn� ad� ta��yan bir .cpp dosyas�na konulur.

��te Date s�n�f�m�z� tekrar, bir .cpp ve .h dosyas�na b�l�nm�� olarak:

Date.h:

                #ifndef DATE_H
                #define DATE_H

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day); // constructor declaration

                    void print() const; // print function declaration

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const { return m_day; }
                };

                #endif
Date.cpp:

                #include "Date.h"

                Date::Date(int year, int month, int day) // constructor definition
                    : m_year{ year }
                    , m_month{ month }
                    , m_day{ day }
                {
                }

                void Date::print() const // print function definition
                {
                    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
                };

�imdi Date s�n�f�n� kullanmak isteyen herhangi bir ba�l�k veya kod dosyas� basit�e #include "Date.h" yapabilir. �ye fonksiyonlar�n
�a�r�lar�n� tan�mlamalar�na ba�layabilmesi i�in ba�lay�c�n�n Date.h'yi kullanan her projeye Date.cpp'nin de derlenmesi gerekti�ini
unutmay�n.

*** BEST -> S�n�f tan�mlar�n�z�, s�n�f ile ayn� ad� ta��yan bir ba�l�k dosyas�na koymay� tercih edin. �nemsiz �ye fonksiyonlar 
            (�rne�in eri�im fonksiyonlar�, bo� g�vdeleri olan yap�land�r�c�lar vb.) s�n�f tan�m�n�n i�inde tan�mlanabilir.
            S�n�f ile ayn� ad� ta��yan bir kaynak dosyada �nemsiz olmayan �ye fonksiyonlar� tan�mlamay� tercih edin.

Bir s�n�f� bir ba�l�k dosyas�nda tan�mlamak, ba�l�k birden fazla kez #include edilirse tek tan�mlama kural�n� (ODR) ihlal etmiyor 
mu?
----------------------------------------------------------------------------------------------------------------------------------
T�rler, bir programda yaln�zca bir tan�m olmas� gerekti�ini s�yleyen tek tan�mlama kural�n�n (ODR) bir b�l�m�nden muaf tutulmu�tur
Bu nedenle, s�n�f tan�mlar�n� birden �ok kod dosyas�na #include etmek bir sorun te�kil etmez. E�er �yle olsayd�, s�n�flar �ok 
fazla i�e yaramazd�.

Bir s�n�f tan�m�n� tek bir kaynak dosyas�na birden fazla kez dahil etmek hala bir ODR ihlalidir. Ancak, ba�l�k korumalar�
(veya #pragma once) bunun olmas�n� �nleyecektir.

�ye fonksiyonlar�n� header'da tan�mlamak tek-tan�mlama kural�n� ihlal eder mi?
------------------------------------------------------------------------------
Bu duruma ba�l�d�r. S�n�f tan�m�n�n i�inde tan�mlanan �ye fonksiyonlar dolayl� olarak inline'd�r. Inline fonksiyonlar, 
tek-tan�mlama kural�n�n program ba��na bir tan�mlama b�l�m�nden muaf tutulur. Bu, basit �ye fonksiyonlar�n
(�rne�in eri�im fonksiyonlar� gibi) s�n�f tan�m�n�n kendisi i�inde tan�mlanmas�nda bir sorun olmad��� anlam�na gelir.

S�n�f tan�m�n�n d���nda tan�mlanan �ye fonksiyonlar dolayl� olarak inline de�ildir (ve bu nedenle tek-tan�mlama kural�n�n program
ba��na bir tan�mlama b�l�m�ne tabidir). Bu nedenle, bu t�r fonksiyonlar genellikle bir kod dosyas�nda tan�mlan�r 
(burada t�m program boyunca yaln�zca bir tan�mlamalar� olacakt�r). Ancak, e�er inline olarak i�aretlenmi�lerse, header dosyas�nda
da tan�mlanabilirler (bu onlar� inline fonksiyon yapar).

Kilit nokta �udur ki, S�n�f tan�m�n�n i�inde tan�mlanan fonksiyonlar dolayl� olarak inline'd�r, bu da onlar�n ODR'yi ihlal etmeden
birden �ok kod dosyas�na dahil edilebilece�i anlam�na gelir.

S�n�f tan�m�n�n d���nda tan�mlanan fonksiyonlar dolayl� olarak inline de�ildir. Inline anahtar kelimesini kullanarak inline
yap�labilirler.

Peki, neden her �eyi bir header dosyas�na koymuyoruz?
-----------------------------------------------------
Header dosyan�za t�m �ye fonksiyon tan�mlar�n�z� koymak i�in cazip olabilirsiniz, ya s�n�f tan�m�n�n i�inde ya da s�n�f tan�m�n�n 
alt�nda inline fonksiyonlar olarak. Bu derlenecektir, ancak bunu yapman�n birka� dezavantaj� vard�r. �lk olarak, yukar�da
belirtildi�i gibi, s�n�f tan�m�n�n i�inde �yeleri tan�mlamak s�n�f tan�m�n�z� kar��t�r�r. �kincisi, e�er header'daki herhangi bir
kodu de�i�tirirseniz, o header'� i�eren her dosyay� yeniden derlemeniz gerekecektir. Bu, bir program�n tamam�n�n yeniden
derlenmesine neden olan bir dalga etkisi yaratabilir (bu yava� olabilir). E�er .cpp dosyas�ndaki kodu de�i�tirirseniz, sadece o
.cpp dosyas�n�n yeniden derlenmesi gereklidir!

S�n�f tan�m�n� bir header'a ve �nemsiz olmayan �ye fonksiyonlar� bir kod dosyas�na koyma en iyi uygulamas�n� ihlal etmek mant�kl�
olabilecek birka� durum vard�r.

�lk olarak, yaln�zca bir kod dosyas�nda kullan�lan ve genel olarak yeniden kullan�lmak �zere tasarlanmam�� k���k bir s�n�f i�in,
s�n�f� (ve t�m �ye fonksiyonlar�) do�rudan kullan�ld��� tek .cpp dosyas�nda tan�mlamay� tercih edebilirsiniz. Bu, s�n�f�n yaln�zca
o tek dosya i�inde kullan�ld���n� ve daha geni� bir kullan�m i�in tasarlanmad���n� a��k�a belirtir. Daha sonra, s�n�f� birden 
fazla dosyada kullanmak isterseniz veya s�n�f ve �ye fonksiyon tan�mlar�n�n kaynak dosyan�z� kar��t�rd���n� fark ederseniz,
s�n�f� ayr� bir header/kod dosyas�na ta��yabilirsiniz.

�kinci olarak, bir s�n�f�n yaln�zca k���k bir say�da �nemsiz olmayan �ye fonksiyonu varsa, yaln�zca bir veya iki tan�m i�eren bir 
.cpp dosyas� olu�turmak �aban�n kar��l���n� vermeyebilir. Bu t�r durumlarda, �ye fonksiyonlar� inline yapmak ve onlar� header'daki
s�n�f tan�m�n�n alt�na koymak tercih edilebilir.

���nc� olarak, modern C++'da, s�n�flar veya k�t�phaneler giderek daha fazla "header-only" olarak da��t�l�yor, yani s�n�f veya 
k�t�phane i�in t�m kod bir header dosyas�na yerle�tiriliyor. Bu, �ncelikle bu t�r dosyalar�n da��t�m�n� ve kullan�m�n� 
kolayla�t�rmak i�in yap�l�r, ��nk� bir header yaln�zca #include edilmesi gerekirken, bir kod dosyas�, derlenebilmesi i�in onu 
kullanan her projeye a��k�a eklenmelidir. Bilin�li bir �ekilde bir header-only s�n�f� veya k�t�phaneyi da��tmak i�in, t�m �nemsiz 
olmayan �ye fonksiyonlar inline yap�labilir ve s�n�f tan�m�n�n alt�ndaki header dosyas�na yerle�tirilebilir.

Son olarak, �ablon s�n�flar i�in, s�n�f�n d���nda tan�mlanan �ablon �ye fonksiyonlar hemen hemen her zaman header dosyas�n�n
i�inde, s�n�f tan�m�n�n alt�nda tan�mlan�r. �ye olmayan �ablon fonksiyonlar gibi, derleyicinin onu �rnekle�tirebilmesi i�in tam 
�ablon tan�m�n� g�rmesi gereklidir. �ablon �ye fonksiyonlar�, 15.5 dersinde -- �ye fonksiyonlar� olan s�n�f �ablonlar� konusunu 
ele al�yoruz.

Yazar�n notu

Gelecekteki derslerde, s�n�flar�m�z�n �o�u tek bir .cpp dosyas�nda tan�mlanacak ve t�m fonksiyonlar do�rudan s�n�f tan�m�nda 
uygulanacakt�r. Bu, �rneklerin �zl� ve kolay derlenebilir olmas�n� sa�lamak i�in yap�l�r. Ger�ek projelerde, s�n�flar�n kendi kod
ve header dosyalar�na konulmas� �ok daha yayg�nd�r ve bunu yapmaya al��mal�s�n�z.

�ye fonksiyonlar� i�in varsay�lan arg�manlar
--------------------------------------------
11.5 dersinde -- Varsay�lan arg�manlar, �ye olmayan fonksiyonlar�n varsay�lan arg�manlar� i�in en iyi uygulamay� tart��t�k:
"E�er fonksiyonun bir ileri bildirimi varsa (�zellikle bir ba�l�k dosyas�nda), varsay�lan arg�man� oraya koyun. Aksi takdirde,
varsay�lan arg�man� fonksiyon tan�m�na koyun."

�ye fonksiyonlar her zaman s�n�f tan�m�n�n bir par�as� olarak bildirildi�i (veya tan�mland���) i�in, �ye fonksiyonlar� i�in en iyi
uygulama asl�nda daha basittir: varsay�lan arg�man� her zaman s�n�f tan�m�n�n i�ine koyun.

*** BEST -> �ye fonksiyonlar� i�in herhangi bir varsay�lan arg�man� s�n�f tan�m�n�n i�ine koyun.

K�t�phaneler
------------
Programlar�n�z boyunca, std::string gibi standart k�t�phanenin bir par�as� olan s�n�flar� kulland�n�z. Bu s�n�flar� kullanmak i�in,
yaln�zca ilgili ba�l��� dahil etmeniz gerekir (�rne�in #include <string>). Not edin ki projelerinize herhangi bir kod dosyas� 
eklemeniz gerekmedi (�rne�in string.cpp veya iostream.cpp).

Ba�l�k dosyalar�, yazd���n�z programlar�n s�zdizimsel olarak do�ru oldu�unu do�rulamak i�in derleyicinin gerektirdi�i bildirimleri
sa�lar. Ancak, C++ standart k�t�phanesine ait s�n�flar�n uygulamalar�, ba�lama a�amas�nda otomatik olarak ba�lanan bir �nceden
derlenmi� dosyada bulunur. Kodu asla g�rmezsiniz.

Bir�ok a��k kaynakl� yaz�l�m paketi, program�n�za derlemek �zere hem .h hem de .cpp dosyalar� sa�lar. Ancak, �o�u ticari k�t�phane 
yaln�zca .h dosyalar� ve �nceden derlenmi� bir k�t�phane dosyas� sa�lar. Bunun birka� nedeni vard�r:
        1) Her seferinde yeniden derlemekten daha h�zl�d�r.
        2) �nceden derlenmi� bir k�t�phanenin tek bir kopyas� bir�ok uygulama taraf�ndan payla��labilir, 
        oysa derlenmemi� kod her kullan�lan uygulamaya derlenir (dosya boyutlar�n� �i�irir)
        3) Fikri m�lkiyet nedenleri (kodunuzun �al�nmas�n� istemezsiniz).

Ekte, 3. parti �nceden derlenmi� k�t�phaneleri projelerinize nas�l dahil edece�inizi tart���yoruz.

Muhtemelen bir s�reli�ine kendi k�t�phanelerinizi olu�turup da��tmayacaks�n�z, ancak s�n�flar�n�z� ba�l�k dosyalar� ve kaynak
dosyalar�na ay�rmak sadece iyi bir bi�im de�il, ayn� zamanda kendi �zel k�t�phanelerinizi olu�turmay� da kolayla�t�r�r.
Kendi k�t�phanelerinizi olu�turmak bu derslerin kapsam� d���ndad�r, ancak bildiriminizi ve uygulaman�z� ay�rmak, �nceden derlenmi�
ikililer da��tmak istiyorsan�z bunu yapman�n bir �n ko�uludur.

15.3 � �� ��e ( Nested - Ba�l� olarak da �evriliyor) T�rler (�ye T�rler)
------------------------------------------------------------------------
A�a��daki k�sa program� d���n�n:

                #include <iostream>

                enum class FruitType
                {
                    apple,
                    banana,
                    cherry
                };

                class Fruit
                {
                private:
                    FruitType m_type { };
                    int m_percentageEaten { 0 };

                public:
                    Fruit(FruitType type) :
                        m_type { type }
                    {
                    }

                    FruitType getType() { return m_type; }
                    int getPercentageEaten() { return m_percentageEaten; }

                    bool isCherry() { return m_type == FruitType::cherry; }

                };

                int main()
                {
                    Fruit apple { FruitType::apple };

                    if (apple.getType() == FruitType::apple)
                        std::cout << "I am an apple";
                    else
                        std::cout << "I am not an apple";

                    return 0;
                }

Bu programda hi�bir yanl��l�k yok. Ancak, enum class FruitType'�n Fruit s�n�f� ile birlikte kullan�lmas� ama�land���ndan,
s�n�ftan ba��ms�z olarak var olmas�, bunlar�n nas�l ba�lant�l� oldu�unu ��kar�m yapmam�z� gerektirir.

�� ��e T�rler (�ye T�rler)

�imdiye kadar, iki farkl� t�rde �yeye sahip s�n�f t�rlerini g�rd�k: veri �yeleri ve �ye fonksiyonlar. Yukar�daki �rnekteki
Fruit s�n�f�m�z�n her ikisi de var.

S�n�f t�rleri, ba�ka bir t�r �yeyi destekler: i� i�e t�rler (ayn� zamanda �ye t�rler olarak da adland�r�l�r). Bir i� i�e t�r 
olu�turmak i�in, t�r� s�n�f�n i�inde, uygun eri�im belirleyicisi alt�nda tan�mlaman�z yeterlidir.

��te yukar�daki program�n ayn�s�, Fruit s�n�f�n�n i�inde tan�mlanan bir i� i�e t�r kullan�larak yeniden yaz�lm�� hali:

                #include <iostream>

                class Fruit
                {
                public:
                    // FruitType, public eri�im belirleyicisi alt�nda s�n�f�n i�ine ta��nd�
                        // Ayr�ca onu Type olarak yeniden adland�rd�k ve bir enum yerine bir enum class yapt�k
                    enum Type
                    {
                        apple,
                        banana,
                        cherry
                    };

                private:
                    Type m_type {};
                    int m_percentageEaten { 0 };

                public:
                    Fruit(Type type) :
                        m_type { type }
                    {
                    }

                    Type getType() { return m_type;  }
                    int getPercentageEaten() { return m_percentageEaten;  }

                    bool isCherry() { return m_type == cherry; } // Fruit'�n �yeleri i�inde, art�k 
                                                                 // FruitType:: ile �ne koymam�za gerek yok
                };

                int main()
                {
                    // Not: S�n�f�n d���nda, numaraland�r�c�lar� art�k Fruit:: �neki ile eri�iyoruz
                    Fruit apple { Fruit::apple };

                    if (apple.getType() == Fruit::apple)
                        std::cout << "I am an apple";
                    else
                        std::cout << "I am not an apple";

                    return 0;
                }
Burada belirtmeye de�er birka� �ey var.

�lk olarak, FruitType'�n art�k s�n�f�n i�inde tan�mland���n� ve k�sa s�re sonra tart��aca��m�z nedenlerle Type olarak yeniden
adland�r�ld���n� belirtmek gerekir.

�kinci olarak, i� i�e t�r olan Type, s�n�f�n en �st�nde tan�mland�. �� i�e t�r adlar�, kullan�lmadan �nce tamamen tan�mlanmal�d�r,
bu y�zden genellikle ilk olarak tan�mlan�rlar.

*** BEST -> S�n�f t�r�n�z�n en �st�nde herhangi bir i� i�e t�r� tan�mlay�n.

���nc� olarak, i� i�e t�rler normal eri�im kurallar�na uyar. Type, t�r ad�n�n ve numaraland�r�c�lar�n do�rudan public
bir �ekilde eri�ilebilmesi i�in public eri�im belirleyicisi alt�nda tan�mland�.

D�rd�nc� olarak, s�n�f t�rleri, i�inde bildirilen adlar i�in bir kapsam b�lgesi olarak hareket eder, t�pk� ad alanlar�n�n
yapt��� gibi. Bu nedenle, Type'�n tam nitelikli ad� Fruit::Type ve apple numaraland�r�c�s�n�n tam nitelikli ad� Fruit::apple'dir.

S�n�f�n �yeleri i�inde, tam nitelikli ad� kullanmam�za gerek yoktur. �rne�in, isCherry() �ye fonksiyonunda, Fruit:: kapsam
belirleyicisi olmadan cherry numaraland�r�c�s�na eri�iriz.

S�n�f�n d���nda, tam nitelikli ad� kullanmal�y�z (�r. Fruit::apple). FruitType'� Type olarak yeniden adland�rd�k,
b�ylece ona Fruit::Type olarak eri�ebiliriz (daha fazla gereksiz olan Fruit::FruitType yerine).

Son olarak, numaraland�r�lm�� t�r�m�z� kapsaml�dan kapsams�za de�i�tirdik. Art�k s�n�f�n kendisi bir kapsam b�lgesi olarak
hareket etti�inden, kapsaml� bir numaraland�r�c� kullanmak biraz gereksizdir. Kapsams�z bir enum'a ge�i�, numaraland�r�c�lar�
Fruit::apple olarak eri�memizi sa�lar, bu da numaraland�r�c�n�n kapsaml� olmas� durumunda kullanmam�z gereken daha uzun
Fruit::Type::apple yerine.

�� i�e typedef'lar ve t�r takma adlar�
--------------------------------------
S�n�f t�rleri ayr�ca i� i�e typedef'lar� veya t�r takma adlar�n� da i�erebilir:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                public:
                    using IDType = int;

                private:
                    std::string m_name{};
                    IDType m_id{};
                    double m_wage{};

                public:
                    Employee(std::string_view name, IDType id, double wage)
                        : m_name { name }
                        , m_id { id }
                        , m_wage { wage }
                    {
                    }

                    const std::string& getName() { return m_name; }
                    IDType getId() { return m_id; } // s�n�f i�inde niteliksiz isim kullan�labilir
                };

                int main()
                {
                    Employee john { "John", 1, 45000 };
                    Employee::IDType id { john.getId() }; // s�n�f d���nda tam nitelikli isim kullan�lmal�d�r

                    std::cout << john.getName() << " has id: " << id << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                John has id: 1
S�n�f�n i�inde sadece IDType'� kullanabiliriz, ancak s�n�f�n d���nda tam nitelikli isim Employee::IDType'� kullanmal�y�z.

T�r takma adlar�n�n faydalar�n� 10.7 -- Typedefs and type aliases dersinde tart���yoruz ve burada ayn� amaca hizmet ediyorlar.
C++ standart k�t�phanesindeki s�n�flar�n i� i�e typedef'lar� kullanmas� �ok yayg�nd�r. Yazma zaman�nda, std::string on i� i�e
typedef tan�mlar!

�� i�e s�n�flar ve d�� s�n�f �yelerine eri�im
---------------------------------------------
S�n�flar�n ba�ka s�n�flar� i� i�e bir t�r olarak i�ermesi olduk�a nadirdir, ancak m�mk�nd�r. C++'da, i� i�e bir s�n�f, 
d�� (i�eren) s�n�f�n this i�aret�isine eri�emez, bu nedenle i� i�e s�n�flar d�� s�n�f�n �yelerine do�rudan eri�emez.
Bu, i� i�e bir s�n�f�n d�� s�n�ftan ba��ms�z olarak �rneklenebilece�i i�in b�yledir (ve b�yle bir durumda, eri�ilecek d�� s�n�f
�yeleri olmaz!)

Ancak, i� i�e s�n�flar d�� s�n�f�n �yeleri oldu�u i�in, kapsamdaki d�� s�n�f�n herhangi bir �zel �yesine eri�ebilirler.
Bir �rnekle a��klayal�m:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                public:
                    using IDType = int;

                    class Printer
                    {
                    public:
                        void print(const Employee& e) const
                        {
                            // Printer, Employee'�n `this` i�aret�isine eri�emez
                            // bu y�zden m_name ve m_id'yi do�rudan yazd�ramay�z
                            // Bunun yerine, kullanmak i�in bir Employee nesnesi ge�memiz gerekiyor
                            // ��nk� Printer, Employee'nin bir �yesidir,
                            // bu y�zden �zel �yeler e.m_name ve e.m_id'ye do�rudan eri�ebiliriz
                            std::cout << e.m_name << " has id: " << e.m_id << '\n';
                        }
                    };

                private:
                    std::string m_name{};
                    IDType m_id{};
                    double m_wage{};

                public:
                    Employee(std::string_view name, IDType id, double wage)
                        : m_name{ name }
                        , m_id{ id }
                        , m_wage{ wage }
                    {
                    }

                    // bu �rnekte eri�im fonksiyonlar�n� kald�rd�k (��nk� kullan�lm�yorlar)
                };

                int main()
                {
                    const Employee john{ "John", 1, 45000 };
                    const Employee::Printer p{}; // i� s�n�f�n bir nesnesini �rneklendir
                    p.print(john);

                    return 0;
                }

                Bu, �unu yazd�r�r:

                John has id: 1
�� i�e s�n�flar�n daha yayg�n olarak kullan�ld��� bir durum vard�r. Standart k�t�phanede, �o�u yineleyici s�n�f�,
�zerinde yinelemeyi tasarlad�klar� konteyn�r�n i� i�e bir s�n�f� olarak uygulan�r. �rne�in, std::string::iterator,
std::string'in i� i�e bir s�n�f� olarak uygulanm��t�r. Yineleyicileri gelecekteki bir b�l�mde ele alaca��z.

�� i�e t�rler ileri bildirilemez
--------------------------------
�� i�e t�rlerin bahsetmeye de�er bir ba�ka s�n�rlamas� daha var -- i� i�e t�rler ileri bildirilemez. 
Bu s�n�rlama, gelecekteki bir C++ s�r�m�nde kald�r�labilir.

15.4 � Y�k�c�lar'a (Destructors) Giri�
--------------------------------------
Temizleme Sorunu
----------------
Bir program yazd���n�z� ve bu program�n bir a� �zerinden baz� verileri g�ndermesi gerekti�ini varsayal�m. Ancak, sunucuya bir 
ba�lant� kurmak maliyetlidir, bu y�zden bir s�r� veri toplamak ve sonra hepsini bir seferde g�ndermek istersiniz. B�yle bir s�n�f
�u �ekilde yap�land�r�labilir:

                class NetworkData
                {
                private:
                    std::string m_serverName{};
                    DataStore m_data{};

                public:
                    NetworkData(std::string_view serverName)
                        : m_serverName { serverName }
                    {
                    }

                    void addData(std::string_view data)
                    {
                        m_data.add(data);
                    }

                    void sendData()
                    {
                        // sunucuya ba�lan
                        // t�m verileri g�nder
                        // verileri temizle
                    }
                };

                int main()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    n.sendData();

                    return 0;
                }

Ancak, bu NetworkData'n�n potansiyel bir sorunu var. Program kapat�lmadan �nce sendData() fonksiyonunun a��k�a �a�r�lmas�na 
ba�l�d�r. NetworkData'n�n kullan�c�s� bunu unutursa, veriler sunucuya g�nderilmeyecek ve program ��kt���nda kaybolacakt�r.
�imdi, "peki, bunu hat�rlamak zor de�il!" diyebilirsiniz ve bu �zel durumda hakl� olabilirsiniz. Ancak, biraz daha karma��k
bir �rne�i d���n�n, �rne�in bu fonksiyon gibi:

                bool someFunction()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    if (someCondition)
                        return false;

                    n.sendData();
                    return true;
                }

Bu durumda, e�er someCondition do�ruysa, fonksiyon erken d�necek ve sendData() �a�r�lmayacakt�r. Bu, sendData() �a�r�s�n�n mevcut 
oldu�u, ancak program�n her durumda ona y�nlendirmedi�i i�in daha kolay bir hata yapmakt�r.

Bu sorunu genelle�tirmek i�in, bir kaynak kullanan s�n�flar (�o�unlukla bellek, ancak bazen dosyalar, veritabanlar�, 
a� ba�lant�lar� vb.) genellikle s�n�f nesnesi yok edilmeden �nce a��k�a g�nderilmesi veya kapat�lmas� gereklidir.
Di�er durumlarda, nesnenin yok edilmesinden �nce baz� kay�tlar tutmak isteyebiliriz, �rne�in bir g�nl�k dosyas�na bilgi yazmak 
veya bir sunucuya bir telemetri par�as� g�ndermek. "Temizleme" terimi, genellikle bir s�n�f�n, s�n�f�n bir nesnesi yok edilmeden 
�nce beklenildi�i gibi davranmak i�in ger�ekle�tirmesi gereken herhangi bir g�rev k�mesine at�fta bulunmak i�in kullan�l�r.
E�er bu t�r bir s�n�f�n kullan�c�s�na, temizleme i�lemini ger�ekle�tiren fonksiyonun nesne yok edilmeden �nce �a�r�lmas�n�
sa�lamak zorunda kal�rsak, muhtemelen bir yerlerde hatalarla kar��la��r�z.

Ama neden kullan�c�dan bunu sa�lamas�n� bile istiyoruz? E�er nesne yok ediliyorsa, o zaman temizlemenin o noktada
ger�ekle�tirilmesi gerekti�ini biliyoruz. Bu temizleme otomatik olarak m� ger�ekle�meli?

Y�k�c�lar kurtarmaya ko�uyor
----------------------------
14.9 dersinde -- Yap�c�lar (Constructors) Hakk�nda Giri� konusunda, bir non-aggregate s�n�f t�r�n�n bir nesnesi olu�turuldu�unda
�a�r�lan �zel �ye fonksiyonlar� olan yap�c�lar� ele ald�k. Yap�c�lar, �ye de�i�kenlerini ba�latmak ve s�n�f�n nesnelerinin 
kullan�ma haz�r olmas�n� sa�lamak i�in gereken di�er t�m kurulum g�revlerini yapmak i�in kullan�l�r.

Benzer �ekilde, s�n�flar�n, bir non-aggregate s�n�f t�r�n�n bir nesnesi yok edildi�inde otomatik olarak �a�r�lan ba�ka bir t�r
�zel �ye fonksiyonu vard�r. Bu fonksiyona y�k�c� (destructor) denir. Y�k�c�lar, bir s�n�f�n, s�n�f�n bir nesnesi yok edilmeden
�nce herhangi bir gerekli temizlemeyi yapmas�na olanak sa�lar.

Y�k�c�lar�n �simlendirilmesi
----------------------------
Yap�c�lar gibi, y�k�c�lar�n da belirli isimlendirme kurallar� vard�r:

*- Y�k�c�n�n ad�, s�n�f�n ad�yla ayn� olmal� ve �n�nde bir tilde (~) olmal�d�r.
*- Y�k�c� arg�man alamaz.
*- Y�k�c�n�n d�n�� tipi yoktur.
*- Bir s�n�f�n yaln�zca tek bir y�k�c�s� olabilir.

Genellikle bir y�k�c�y� a��k�a �a��rmamal�s�n�z (��nk� nesne yok edildi�inde otomatik olarak �a�r�l�r), ��nk� bir nesneyi birden
fazla kez temizlemek isteyece�iniz nadir durumlar vard�r.

Y�k�c�lar, nesne y�k�c� �al��t�ktan sonra yok edilene kadar di�er �ye fonksiyonlar� g�venle �a��rabilir.

Bir y�k�c� �rne�i

                #include <iostream>

                class Simple
                {
                private:
                    int m_id {};

                public:
                    Simple(int id)
                        : m_id { id }
                    {
                        std::cout << "Constructing Simple " << m_id << '\n';
                    }

                    ~Simple() // i�te bizim y�k�c�
                    {
                        std::cout << "Destructing Simple " << m_id << '\n';
                    }

                    int getID() const { return m_id; }
                };

                int main()
                {
                    // Bir Simple tahsis et
                    Simple simple1{ 1 };
                    {
                        Simple simple2{ 2 };
                    } // simple2 burada �l�r

                    return 0;
                } // simple1 burada �l�r

                Bu program a�a��daki sonucu �retir:


                Constructing Simple 1
                Constructing Simple 2
                Destructing Simple 2
                Destructing Simple 1

Her Simple nesnesi yok edildi�inde, y�k�c� �a�r�l�r ve bir mesaj yazd�r�r. "Destructing Simple 1" ifadesi,
"Destructing Simple 2" ifadesinden sonra yazd�r�l�r ��nk� simple2, fonksiyonun sona ermesinden �nce yok edilmi�tir, oysa simple1, 
main() sona erene kadar yok edilmez.

Statik de�i�kenlerin (global de�i�kenler ve statik yerel de�i�kenler dahil) program ba�lang�c�nda olu�turuldu�unu ve program 
kapan���nda yok edildi�ini unutmay�n.

UserSettings program�n� iyile�tirme
-----------------------------------
Dersin ba��ndaki �rne�imize geri d�nersek, kullan�c�n�n a��k�a sendData() �a��rma ihtiyac�n�, bir y�k�c�n�n bu fonksiyonu 
�a��rmas�yla ortadan kald�rabiliriz:

                class NetworkData
                {
                private:
                    std::string m_serverName{};
                    DataStore m_data{};

                public:
                    NetworkData(std::string_view serverName)
                        : m_serverName { serverName }
                    {
                    }

                    ~NetworkData()
                    {
                        sendData(); // nesne yok edilmeden �nce t�m verilerin g�nderildi�inden emin olun
                    }

                    void addData(std::string_view data)
                    {
                        m_data.add(data);
                    }

                    void sendData()
                    {
                        // sunucuya ba�lan
                        // t�m verileri g�nder
                        // verileri temizle
                    }
                };

                int main()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    return 0;
                }

B�yle bir y�k�c� ile, NetworkData nesnemiz her zaman nesne yok edilmeden �nce sahip oldu�u t�m verileri g�nderecektir! 
Temizlik otomatik olarak ger�ekle�ir, bu da hatalar�n daha az olas�l���n� ve d���n�lmesi gereken daha az �ey anlam�na gelir.

Bir implicit y�k�c�
-------------------
E�er bir toplu olmayan s�n�f tipi nesnenin kullan�c� taraf�ndan bildirilen bir y�k�c�s� yoksa, derleyici bo� bir g�vdeye sahip
bir y�k�c� olu�turur. Bu y�k�c�ya implicit y�k�c� denir ve etkin olarak sadece bir yer tutucudur.

E�er s�n�f�n�z�n yok edilmesi s�ras�nda herhangi bir temizlik yapmas�na gerek yoksa, hi�bir y�k�c� tan�mlamaman�z ve derleyicinin
s�n�f�n�z i�in bir implicit y�k�c� olu�turmas�na izin vermeniz tamam.

std::exit() fonksiyonu hakk�nda bir uyar�

8.12 dersinde -- Duraklatmalar (program�n�z� erken sonland�rma), std::exit() fonksiyonunu tart��t�k, program�n�z� hemen
sonland�rmak i�in kullan�labilir. Program hemen sonland�r�ld���nda, program sadece sona erer. �ncelikle yerel de�i�kenler yok
edilmez ve bu nedenle hi�bir y�k�c� �a�r�lmaz. B�yle bir durumda y�k�c�lar�n�z�n gerekli temizlik i�lerini yapmas�na 
g�veniyorsan�z dikkatli olun.

15.5 � �ye Fonksiyonlar� olan S�n�f �ablonlar�
----------------------------------------------
11.6 -- Fonksiyon �ablonlar� dersinde, fonksiyon �ablonlar�na bir g�z att�k:

                template <typename T> // bu �ablon parametre bildirimidir
                T max(T x, T y) // bu max<T> i�in fonksiyon �ablonu tan�m�d�r
                {
                    return (x < y) ? y : x;
                }

Bir fonksiyon �ablonu ile, t�r �ablon parametrelerini (�r. typename T) tan�mlayabilir ve ard�ndan bunlar� fonksiyon
parametrelerimizin t�r� olarak kullanabiliriz (T x, T y).

13.11 -- S�n�f �ablonlar� dersinde, s�n�f �ablonlar�n� ele ald�k, bu da bize s�n�f t�rlerinin (struct, s�n�flar ve unions) 
veri �yelerinin t�r� i�in t�r �ablon parametrelerini kullanma imkan� verir:

                #include <iostream>

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                // ��te Pair i�in bir ��kar�m k�lavuzu (C++17 veya daha eski s�r�mlerde gereklidir)
                // T ve T t�r�ndeki arg�manlarla ba�lat�lan Pair nesneleri Pair<T> olarak ��kar�lmal�d�r
                template <typename T>
                Pair(T, T) -> Pair<T>;

                int main()
                {
                    Pair<int> p1{ 5, 6 };        // Pair<int> �rne�ini olu�turur ve p1 nesnesini olu�turur
                    std::cout << p1.first << ' ' << p1.second << '\n';

                    Pair<double> p2{ 1.2, 3.4 }; // Pair<double> �rne�ini olu�turur ve p2 nesnesini olu�turur
                    std::cout << p2.first << ' ' << p2.second << '\n';

                    Pair<double> p3{ 7.8, 9.0 }; // �nceki Pair<double> tan�m�n� kullanarak p3 nesnesini olu�turur
                    std::cout << p3.first << ' ' << p3.second << '\n';

                    return 0;
                }

�lgili i�erik

��kar�m k�lavuzlar�n� 13.12 -- S�n�f �ablonu Arg�man ��kar�m� (CTAD) ve ��kar�m K�lavuzlar� dersinde tart���yoruz.

Bu derste, hem fonksiyon �ablonlar�n�n hem de s�n�f �ablonlar�n�n unsurlar�n� birle�tirirken, �ye fonksiyonlar� olan s�n�f 
�ablonlar�na daha yak�ndan bakaca��z.

�ye Fonksiyonlarda T�r �ablon Parametreleri
-------------------------------------------
Bir s�n�f �ablonu parametre bildiriminin bir par�as� olarak tan�mlanan t�r �ablon parametreleri, hem veri �yelerinin t�r� olarak 
hem de �ye fonksiyon parametrelerinin t�r� olarak kullan�labilir.

A�a��daki �rnekte, yukar�daki Pair s�n�f �ablonunu yeniden yaz�yoruz, onu bir yap�dan bir s�n�fa d�n��t�r�yoruz:

                #include <ios>       // for std::boolalpha
                #include <iostream>

                template <typename T>
                class Pair
                {
                private:
                    T m_first{};
                    T m_second{};

                public:
                    // Bir �ye fonksiyonu s�n�f tan�m�n�n i�inde tan�mlad���m�zda,
                    // s�n�fa ait �ablon parametre bildirimi ge�erli olur
                    Pair(const T& first, const T& second)
                        : m_first{ first }
                        , m_second{ second }
                    {
                    }

                    bool isEqual(const Pair<T>& pair);
                };

                // Bir �ye fonksiyonu s�n�f tan�m�n�n d���nda tan�mlad���m�zda,
                // bir �ablon parametre bildirimini yeniden sa�lamam�z gerekiyor
                template <typename T>
                bool Pair<T>::isEqual(const Pair<T>& pair)
                {
                    return m_first == pair.m_first && m_second == pair.m_second;
                }

                int main()
                {
                    Pair p1{ 5, 6 }; // CTAD'yi kullanarak Pair<int> t�r�n� ��kar�r
                    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
                    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

                    return 0;
                }

Yukar�daki olduk�a basit olmal�, ancak belirtmeye de�er birka� �ey var.

�lk olarak, s�n�f�m�z�n �zel �yeleri oldu�u i�in, bir topluluk de�ildir ve bu nedenle topluluk ba�latmas�n� kullanamaz.
Bunun yerine, s�n�f nesnelerimizi bir yap�land�r�c� kullanarak ba�latmam�z gerekiyor.

S�n�f veri �yelerimiz T t�r�nde oldu�undan, yap�land�r�c�m�z�n parametrelerini const T& t�r�nde yapar�z, b�ylece kullan�c� ayn�
t�rde ba�latma de�erleri sa�layabilir. T'nin kopyalanmas� pahal� olabilece�inden, de�erden ziyade const referans ile ge�mek daha 
g�venlidir.

Bir �ye fonksiyonunu s�n�f �ablonu tan�m�n�n i�inde tan�mlad���m�zda, �ye fonksiyon i�in bir �ablon parametre bildirimi
sa�lamam�za gerek yoktur. Bu t�r �ye fonksiyonlar, s�n�f �ablonu parametre bildirimini dolayl� olarak kullan�r.

�kinci olarak, topluluk olmayan s�n�flarla CTAD'yi �al��t�rmak i�in ��kar�m k�lavuzlar�na ihtiyac�m�z yoktur.
E�le�en bir yap�land�r�c�, derleyiciye ba�lat�c�lar�ndan �ablon parametrelerini ��karmak i�in gereken bilgileri sa�lar.

���nc� olarak, bir s�n�f �ablonu i�in bir �ye fonksiyonu s�n�f �ablonu tan�m�n�n d���nda tan�mlad���m�z durumu daha yak�ndan
inceleyelim:

                template <typename T>
                bool Pair<T>::isEqual(const Pair<T>& pair)
                {
                    return m_first == pair.m_first && m_second == pair.m_second;
                }

Bu �ye fonksiyon tan�m�, s�n�f �ablonu tan�m�ndan ayr� oldu�u i�in, derleyicinin T'nin ne oldu�unu bilmesi i�in bir �ablon
parametre bildirimini (template <typename T>) yeniden sa�lamam�z gerekiyor.

Ayr�ca, bir �ye fonksiyonu s�n�f�n d���nda tan�mlad���m�zda, �ye fonksiyon ad�n� s�n�f �ablonunun tamamen �ablonlanm�� ad�yla
nitelendirmemiz gerekiyor (Pair<T>::isEqual, not Pair::isEqual).

S�n�f �ablonlar� ��in �ye Fonksiyonlar� Nerede Tan�mlanmal�
-----------------------------------------------------------
S�n�f �ablonlar� i�in �ye fonksiyonlarla, derleyicinin hem s�n�f tan�m�n� (�ye fonksiyon �ablonunun s�n�f�n bir par�as� olarak 
bildirildi�inden emin olmak i�in) hem de �ablon �ye fonksiyon tan�m�n� (�ablonu nas�l �rneklenece�ini bilmek i�in) 
g�rmesi gerekiyor. Bu nedenle, genellikle hem bir s�n�f� hem de �ye fonksiyon �ablonlar�n� ayn� yerde tan�mlamak istiyoruz.

Bir �ye fonksiyon �ablonu, s�n�f tan�m�n�n i�inde tan�mland���nda, �ablon �ye fonksiyon tan�m�, s�n�f tan�m�n�n bir par�as�d�r,
bu y�zden s�n�f tan�m�n�n g�r�lebildi�i her yerde, �ablon �ye fonksiyon tan�m� da g�r�lebilir. Bu, i�leri kolayla�t�r�r 
(s�n�f tan�m�m�z� kar��t�rma pahas�na).

Bir �ye fonksiyon �ablonu, s�n�f tan�m�n�n d���nda tan�mland���nda, genellikle s�n�f tan�m�n�n hemen alt�nda tan�mlanmal�d�r.
Bu �ekilde, s�n�f tan�m�n�n g�r�lebildi�i her yerde, s�n�f tan�m�n�n hemen alt�ndaki �ye fonksiyon �ablon tan�mlar� da g�r�lebilir

Bir s�n�f�n tipik olarak bir header dosyas�nda tan�mland��� durumda, bu, s�n�f�n d���nda tan�mlanan herhangi bir �ye fonksiyon
�ablonunun da ayn� header dosyas�nda, s�n�f tan�m�n�n alt�nda tan�mlanmas� gerekti�i anlam�na gelir.

Anahtar nokta �udur ki, 11.7 -- Function template instantiation dersinde, �ablonlardan dolayl� olarak �rneklendirilen
fonksiyonlar�n dolayl� olarak inline oldu�unu belirttik. Bu, hem �ye olmayan hem de �ye fonksiyon �ablonlar�n� i�erir.
Bu nedenle, header dosyalar�nda tan�mlanan �ye fonksiyon �ablonlar�n� birden �ok kod dosyas�na dahil etmede bir sorun yoktur,
��nk� bu �ablonlardan �rneklendirilen fonksiyonlar dolayl� olarak inline olacakt�r (ve linker bunlar� �o�altacakt�r).

*** BEST -> S�n�f tan�m�n�n d���nda tan�mlanan herhangi bir �ye fonksiyon �ablonu, s�n�f tan�m�n�n hemen alt�nda tan�mlanmal�d�r 
            (ayn� dosyada).

15.6 � Statik �ye De�i�kenler
-----------------------------
7.4 -- Global de�i�kenlere giri� dersinde, global de�i�kenleri ve 7.10 -- Statik yerel de�i�kenler dersinde statik yerel
de�i�kenleri tan�tt�k. Bu t�r de�i�kenlerin her ikisi de statik s�reye sahiptir, yani program�n ba��nda olu�turulur ve
program�n sonunda yok edilir. Bu t�r de�i�kenler, kapsamlar� d���na ��ksalar bile de�erlerini korurlar.
�rne�in:

                #include <iostream>

                int generateID()
                {
                    static int s_id{ 0 }; // statik yerel de�i�ken
                    return ++s_id;
                }

                int main()
                {
                    std::cout << generateID() << '\n';
                    std::cout << generateID() << '\n';
                    std::cout << generateID() << '\n';

                    return 0;
                }
                Bu program �unu yazd�r�r:
                1
                2
                3
Statik yerel de�i�ken s_id'nin birden �ok fonksiyon �a�r�s� boyunca de�erini korudu�unu unutmay�n.

S�n�f t�rleri, statik anahtar kelimesi i�in iki yeni kullan�m getirir: statik �ye de�i�kenler ve statik �ye fonksiyonlar.
Neyse ki, bu kullan�mlar olduk�a basittir. Bu derste statik �ye de�i�kenlerden bahsedece�iz ve bir sonraki derste 
statik �ye fonksiyonlardan bahsedece�iz.

Statik �ye De�i�kenler
----------------------
�ye de�i�kenlere uygulanan statik anahtar kelimesine girmeden �nce, a�a��daki s�n�f� d���n�n:

                #include <iostream>

                struct Something
                {
                    int value{ 1 };
                };

                int main()
                {
                    Something first{};
                    Something second{};

                    first.value = 2;

                    std::cout << first.value << '\n';
                    std::cout << second.value << '\n';

                    return 0;
                }

Bir s�n�f nesnesi olu�turdu�umuzda, her nesne t�m normal �ye de�i�kenlerinin kendi kopyas�n� al�r. Bu durumda, iki Something s�n�f
nesnesi bildirdi�imiz i�in, value'nun iki kopyas�na sahip oluruz: first.value ve second.value. first.value, second.value'dan 
farkl�d�r. Sonu� olarak, yukar�daki program �unu yazd�r�r:

                2
                1
Bir s�n�f�n �ye de�i�kenleri, static anahtar kelimesi kullan�larak statik yap�labilir. Normal �ye de�i�kenlerin aksine, 
statik �ye de�i�kenler t�m s�n�f nesneleri taraf�ndan payla��l�r. Yukar�dakine benzer a�a��daki program� d���n�n:

                #include <iostream>

                struct Something
                {
                    static int s_value; // �imdi statik
                };

                int Something::s_value{ 1 }; // s_value'yi 1'e ba�lat

                int main()
                {
                    Something first{};
                    Something second{};

                    first.s_value = 2;

                    std::cout << first.s_value << '\n';
                    std::cout << second.s_value << '\n';
                    return 0;
                }
                Bu program a�a��daki ��kt�y� �retir:

                2
                2
��nk� s_value bir statik �ye de�i�ken oldu�u i�in, s_value t�m s�n�f nesneleri aras�nda payla��l�r. Sonu� olarak, first.s_value,
second.s_value ile ayn� de�i�kendir. Yukar�daki program, first kullanarak ayarlad���m�z de�erin second kullan�larak 
eri�ilebildi�ini g�sterir!

Statik �yeler s�n�f nesneleriyle ili�kili de�ildir
--------------------------------------------------
Statik �yelere bir s�n�f�n nesneleri arac�l���yla eri�ebilirsiniz (yukar�daki �rnekte first.s_value ve second.s_value ile 
g�sterildi�i gibi), statik �yeler, s�n�f�n hi�bir nesnesi olu�turulmam�� olsa bile var olur! Bu mant�kl�d�r: program�n ba��nda 
olu�turulurlar ve program�n sonunda yok edilirler, bu y�zden �m�rleri normal bir �ye gibi bir s�n�f nesnesine ba�l� de�ildir.

Temelde, statik �yeler, s�n�f�n kapsam b�lgesi i�inde ya�ayan global de�i�kenlerdir. Bir s�n�f�n statik �yesi ile bir ad alan�
i�indeki normal bir de�i�ken aras�nda �ok az fark vard�r.

Anahtar nokta �udur ki, Statik �yeler, s�n�f�n kapsam b�lgesi i�inde ya�ayan global de�i�kenlerdir.

Statik �ye s_value, herhangi bir s�n�f nesnesinden ba��ms�z olarak var oldu�u i�in, s�n�f ad� ve kapsam ��z�mleme operat�r� 
kullan�larak do�rudan eri�ilebilir (bu durumda, Something::s_value):

                class Something
                {
                public:
                    static int s_value; // statik �ye de�i�kenini bildirir
                };

                int Something::s_value{ 1 }; // statik �ye de�i�kenini tan�mlar (bu b�l�m� a�a��da tart��aca��z)

                int main()
                {
                    // not: Something tipinde herhangi bir nesne olu�turmuyoruz

                    Something::s_value = 2;
                    std::cout << Something::s_value << '\n';
                    return 0;
                }
Yukar�daki par�ada, s_value bir nesne yerine Something s�n�f ad� taraf�ndan referans al�n�r. Something tipinde bir nesne bile
olu�turmad���m�z� not edin, ancak hala Something::s_value'ye eri�ebiliyor ve kullanabiliyoruz. Bu, statik �yelere eri�mek i�in 
tercih edilen y�ntemdir.

*** BEST -> Statik �yelere, s�n�f ad�n� ve kapsam ��z�mleme operat�r�n� (::) kullanarak eri�in.

Statik �ye De�i�kenlerin Tan�mlanmas� ve Ba�lat�lmas�
-----------------------------------------------------   
Bir s�n�f t�r� i�inde bir statik �ye de�i�keni bildirdi�imizde, derleyiciye bir statik �ye de�i�keninin varl��� hakk�nda bilgi
veriyoruz, ancak asl�nda onu tan�mlam�yoruz (t�pk� bir ileri bildirim gibi). Statik �ye de�i�kenler esasen global de�i�kenler
oldu�u i�in, statik �yeyi s�n�f�n d���nda, global kapsamda a��k�a tan�mlamal� ve iste�e ba�l� olarak ba�latmal�s�n�z.

Yukar�daki �rnekte, bunu bu sat�r arac�l���yla yap�yoruz:

                int Something::s_value{ 1 }; // statik �ye de�i�kenini tan�mlar

Bu sat�r iki amaca hizmet eder: statik �ye de�i�kenini olu�turur (t�pk� bir global de�i�ken gibi) ve onu ba�lat�r. Bu durumda,
ba�latma de�eri olarak 1'i sa�l�yoruz. Ba�lat�c� sa�lanmazsa, statik �ye de�i�kenler varsay�lan olarak s�f�ra ba�lat�l�r.

Bu statik �ye tan�m�n�n eri�im kontrollerine tabi olmad���n� unutmay�n: de�eri tan�mlayabilir ve ba�latabilirsiniz,
hatta s�n�fta �zel (veya korumal�) olarak bildirilmi� olsa bile.

E�er s�n�f bir ba�l�k (.h) dosyas�nda tan�mlanm��sa, statik �ye tan�m� genellikle s�n�f i�in ili�kili kod dosyas�na 
(�rne�in Something.cpp) yerle�tirilir. E�er s�n�f bir kaynak (.cpp) dosyas�nda tan�mlanm��sa, statik �ye tan�m� genellikle s�n�f�n
hemen alt�na yerle�tirilir. Statik �ye tan�m�n� bir ba�l�k dosyas�na koymay�n (global bir de�i�ken gibi, e�er bu ba�l�k dosyas�
birden fazla kez dahil edilirse, birden fazla tan�m�n�z olacak ve bu bir derleme hatas�na neden olacakt�r).

S�n�f tan�m� i�inde statik �ye de�i�kenlerinin ba�lat�lmas�
-----------------------------------------------------------
Yukar�dakilere birka� k�sayol vard�r. �lk olarak, statik �ye bir sabit integral tip (char ve bool dahil) veya const enum oldu�unda
statik �ye s�n�f tan�m� i�inde ba�lat�labilir:

                class Whatever
                {
                public:
                    static const int s_value{ 4 }; // bir static const int do�rudan tan�mlanabilir ve ba�lat�labilir
                };
Yukar�daki �rnekte, statik �ye de�i�keni bir const int oldu�u i�in, a��k bir tan�m sat�r�na gerek yoktur.

7.9 dersinde -- Global sabitleri birden �ok dosya aras�nda payla�ma (inline de�i�kenler kullanarak), birden �ok tan�ma sahip
olabilen de�i�kenler olan inline de�i�kenleri tan�tt�k. C++17, statik �yelerin inline de�i�ken olmas�na izin verir:

                class Whatever
                {
                public:
                    static inline int s_value{ 4 }; // bir static inline de�i�ken do�rudan tan�mlanabilir ve ba�lat�labilir
                };

Bu t�r de�i�kenler, sabit olup olmad�klar�na bak�lmaks�z�n s�n�f tan�m� i�inde ba�lat�labilir.
Bu, statik �yeleri tan�mlama ve ba�latma y�ntemidir.

��nk� constexpr �yeler implicit olarak inline'd�r (C++17 itibariyle), static constexpr �yeler de inline anahtar kelimesinin a��k�a
kullan�lmas�na gerek kalmadan s�n�f tan�m� i�inde ba�lat�labilir:

                #include <string_view>

                class Whatever
                {
                public:
                    static constexpr double s_value{ 2.2 }; // tamam
                    static constexpr std::string_view s_view{ "Hello" }; // bu, constexpr ba�latmay� 
                                                                         // destekleyen s�n�flar i�in bile �al���r
                };

*** BEST -> Statik �yelerinizi inline veya constexpr yap�n, b�ylece s�n�f tan�m� i�inde ba�lat�labilirler.

Statik �ye de�i�kenlerin bir �rne�i
-----------------------------------
Neden s�n�flar�n i�inde statik de�i�kenler kullan�l�r? Bir kullan�m�, her s�n�f �rne�ine benzersiz bir ID atamakt�r. 
��te bir �rnek:

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_idGenerator { 1 };
                    int m_id {};

                public:
                    // id olu�turucudan sonraki de�eri al
                    Something() : m_id { s_idGenerator++ }
                    {
                    }

                    int getID() const { return m_id; }
                };

                int main()
                {
                    Something first{};
                    Something second{};
                    Something third{};

                    std::cout << first.getID() << '\n';
                    std::cout << second.getID() << '\n';
                    std::cout << third.getID() << '\n';
                    return 0;
                }
                Bu program �unu yazd�r�r:
                1
                2
                3

��nk� s_idGenerator t�m Something nesneleri taraf�ndan payla��ld��� i�in, yeni bir Something nesnesi olu�turuldu�unda,
yap�c� m_id'yi s_idGenerator'un mevcut de�eriyle ba�lat�r ve sonra bir sonraki nesne i�in de�eri art�r�r. Bu, her olu�turulan
Something nesnesinin benzersiz bir id almas�n� garanti eder (olu�turma s�ras�na g�re art�r�l�r).

Her nesneye benzersiz bir ID vermek, hata ay�klamada yard�mc� olabilir, ��nk� aksi halde ayn� verilere sahip nesneleri ay�rt etmek
i�in kullan�labilir. Bu, veri dizileriyle �al���rken �zellikle do�rudur.

Statik �ye de�i�kenler ayr�ca s�n�f�n bir arama tablosunu kullanmas� gerekti�inde de yararl�d�r (�rne�in, bir dizi, bir dizi
�nceden hesaplanm�� de�erleri saklamak i�in kullan�l�r). Arama tablosunu statik yaparak, t�m nesneler i�in yaln�zca bir kopya
vard�r, her olu�turulan nesne i�in bir kopya yapmak yerine. Bu, �nemli miktarda bellek tasarrufu sa�layabilir.

Statik �ye Fonksiyonlar
-----------------------
15.6 -- Statik �ye De�i�kenler dersinde, statik �ye de�i�kenlerin s�n�fa de�il, s�n�f�n nesnelerine ait oldu�unu ��rendiniz. E�er
bir statik �ye de�i�ken public ise, s�n�f ad� ve kapsam ��z�mleme operat�r� kullan�larak do�rudan eri�ilebilir:

                #include <iostream>

                class Something
                {
                public:
                    static inline int s_value { 1 };
                };

                int main()
                {
                    std::cout << Something::s_value; // s_value public'tir, do�rudan eri�ebiliriz
                }
Peki ya bir statik �ye de�i�ken private ise? A�a��daki �rne�i d���n�n:

                #include <iostream>

                class Something
                {
                private: // �imdi private
                    static inline int s_value { 1 };
                };

                int main()
                {
                    std::cout << Something::s_value; // hata: s_value private ve s�n�f�n d���ndan do�rudan eri�ilemez
                }
Bu durumda, Something::s_value'ye main() fonksiyonundan do�rudan eri�emeyiz, ��nk� bu private'dir. Normalde private �yelere public
�ye fonksiyonlar arac�l���yla eri�iriz. s_value'ye eri�mek i�in normal bir public �ye fonksiyon olu�turabilirdik, ancak bu durumda
fonksiyonu kullanmak i�in s�n�f t�r�nde bir nesne olu�turmam�z gerekirdi!

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_value { 1 };

                public:
                    int getValue() { return s_value; }
                };

                int main()
                {
                    Something s{};
                    std::cout << s.getValue(); // �al���r, ancak getValue() �a�r�s�n� yapmak i�in bir nesne olu�turmay� gerektirir
                }
Daha iyisini yapabiliriz.

Statik �ye Fonksiyonlar
-----------------------
�ye de�i�kenler, statik yap�labilecek tek t�rde �ye de�ildir. �ye fonksiyonlar da statik yap�labilir. ��te yukar�daki �rnekle
bir statik �ye fonksiyon eri�imcisi:

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_value { 1 };

                public:
                    static int getValue() { return s_value; } // statik �ye fonksiyon
                };

                int main()
                {
                    std::cout << Something::getValue() << '\n';
                }
Statik �ye fonksiyonlar belirli bir nesneyle ili�kili olmad���ndan, s�n�f ad� ve kapsam ��z�mleme operat�r�n� 
(�r. Something::getValue()) kullanarak do�rudan �a�r�labilir. Statik �ye de�i�kenler gibi, s�n�f t�r�ndeki nesneler arac�l���yla
da �a�r�labilirler, ancak bu �nerilmez.

Statik �ye Fonksiyonlar�n�n *this ��aret�isi Yoktur
---------------------------------------------------
Statik �ye fonksiyonlar�n dikkate de�er iki ilgin� �zelli�i vard�r. �lk olarak, statik �ye fonksiyonlar bir nesneye ba�l�
olmad���ndan, *this i�aret�ileri yoktur! Bu, d���nd���n�zde mant�kl�d�r -- *this i�aret�isi her zaman �ye fonksiyonun �zerinde 
�al��t��� nesneyi g�sterir. Statik �ye fonksiyonlar bir nesne �zerinde �al��maz, bu y�zden *this i�aret�isine ihtiya� yoktur.

�kinci olarak, statik �ye fonksiyonlar di�er statik �yelere (de�i�kenler veya fonksiyonlar) do�rudan eri�ebilir, ancak statik 
olmayan �yelere eri�emezler. Bu, statik olmayan �yelerin bir s�n�f nesnesine ait olmas� gerekti�i ve statik �ye fonksiyonlar�n�n 
�al��acak bir s�n�f nesnesi olmad��� i�indir!

Ba�ka bir �rnek

Statik �ye fonksiyonlar da s�n�f bildiriminin d���nda tan�mlanabilir. Bu, normal �ye fonksiyonlar i�in oldu�u gibi ayn� �ekilde 
�al���r.

                #include <iostream>

                class IDGenerator
                {
                private:
                    static inline int s_nextID { 1 };

                public:
                     static int getNextID(); // ��te bir statik fonksiyon i�in bildirim
                };

                // ��te s�n�f�n d���ndaki statik fonksiyonun tan�m�. Burada statik anahtar kelimesini kullanm�yoruz.
                int IDGenerator::getNextID() { return s_nextID++; }

                int main()
                {
                    for (int count{ 0 }; count < 5; ++count)
                        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

                    return 0;
                }

                Bu program �unu yazd�r�r:

                The next ID is: 1
                The next ID is: 2
                The next ID is: 3
                The next ID is: 4
                The next ID is: 5
Not edin ki, bu s�n�ftaki t�m veri ve fonksiyonlar statik oldu�u i�in, i�levselli�inden yararlanmak i�in bir nesne olu�turmam�za
gerek yok! Bu s�n�f, atanacak bir sonraki ID'nin de�erini tutmak i�in bir statik �ye de�i�ken kullan�r ve bu ID'yi d�nd�rmek 
ve art�rmak i�in bir statik �ye fonksiyon sa�lar.

T�m statik �yelere sahip s�n�flar hakk�nda bir uyar�
----------------------------------------------------
T�m statik �yelere sahip s�n�flar� yazarken dikkatli olun. Bu t�r "saf statik s�n�flar" (veya "monostatlar") yararl� olabilir, 
ancak baz� potansiyel dezavantajlar� da vard�r.

�ncelikle, t�m statik �yeler yaln�zca bir kez �rneklendi�i i�in, saf bir statik s�n�f�n birden �ok kopyas�n� olu�turman�n bir yolu
yoktur (s�n�f� klonlamadan ve yeniden adland�rmadan). �rne�in, iki ba��ms�z IDGenerator'a ihtiyac�n�z varsa, bu saf bir statik
s�n�f ile m�mk�n olmaz.

�kincisi, global de�i�kenler dersinde, global de�i�kenlerin tehlikeli oldu�unu ��rendiniz ��nk� herhangi bir kod par�as� global
de�i�kenin de�erini de�i�tirebilir ve ba�ka bir g�r�n��te ilgisiz kod par�as�n� bozabilir. Ayn�s� saf statik s�n�flar i�in de 
ge�erlidir. T�m �yelerin s�n�fa (s�n�f�n nesnesi yerine) ait olmas� ve s�n�f bildirimlerinin genellikle global kapsama sahip
olmas� nedeniyle, saf bir statik s�n�f, global de�i�kenlerin t�m gerekli dezavantajlar�na sahip olan, global olarak eri�ilebilir
bir ad alan�nda fonksiyonlar ve global de�i�kenler bildirmenin esasen e�de�eridir.

T�m statik �yelere sahip bir s�n�f yazmak yerine, normal bir s�n�f yazmay� ve onun global bir �rne�ini olu�turmay� d���n�n
(global de�i�kenler statik s�reye sahiptir). Bu �ekilde, global �rnek uygun oldu�unda kullan�labilir, ancak yerel �rnekler
gerekti�inde hala �rneklenebilir.

Saf statik s�n�flar vs. ad alanlar�
-----------------------------------
Saf statik s�n�flar�n ad alanlar�yla �ok fazla �rt��mesi vard�r. Her ikisi de statik s�reye sahip de�i�kenleri ve kapsam
b�lgesindeki fonksiyonlar� tan�mlaman�za izin verir. Ancak, �nemli bir fark, s�n�flar�n eri�im kontrollerine sahip olmas�,
ad alanlar�n�n ise olmamas�d�r.

Genel olarak, statik veri �yelerine ve/veya eri�im kontrollerine ihtiyac�n�z varsa, statik bir s�n�f tercih edilir. Aksi takdirde,
bir ad alan�n� tercih edin.

C++ statik yap�land�r�c�lar� desteklemez
----------------------------------------
Normal �ye de�i�kenlerini bir yap�land�r�c� arac�l���yla ba�latabiliyorsan�z, o zaman statik �ye de�i�kenlerini bir statik
yap�land�r�c� arac�l���yla ba�latman�n mant�kl� oldu�unu d���nmek mant�kl�d�r. Ve baz� modern diller, tam da bu ama�la statik
yap�land�r�c�lar� desteklerken, ne yaz�k ki C++ bunlardan biri de�ildir.
Statik de�i�keninizi do�rudan ba�latabiliyorsan�z, bir yap�land�r�c�ya ihtiya� yoktur: statik �ye de�i�kenini tan�m noktas�nda 
ba�latabilirsiniz (�zel olsa bile). Bunu yukar�daki IDGenerator �rne�inde yap�yoruz. ��te ba�ka bir �rnek:

                #include <iostream>

                struct Chars
                {
                    char first{};
                    char second{};
                    char third{};
                    char fourth{};
                    char fifth{};
                };

                struct MyClass
                {
                    static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // statik de�i�keni tan�m noktas�nda ba�lat
                };

                int main()
                {
                    std::cout << MyClass::s_mychars.third; // i yazd�r

                    return 0;
                }
Statik �ye de�i�keninizi ba�latmak kodun �al��t�r�lmas�n� gerektiriyorsa (�rne�in bir d�ng�), bunu yapman�n bir�ok farkl�,
biraz karma��k yolu vard�r. T�m de�i�kenlerle, statik olsun veya olmas�n, �al��an bir yol, bir nesne olu�turmak, onu verilerle
doldurmak ve �a��ran ki�iye d�nd�rmek i�in bir fonksiyon kullanmakt�r. Bu d�nd�r�len de�er, ba�lat�lan nesneye kopyalanabilir.

                #include <iostream>

                struct Chars
                {
                    char first{};
                    char second{};
                    char third{};
                    char fourth{};
                    char fifth{};
                };

                class MyClass
                {
                private:
                    static Chars generate()
                    {
                        Chars c{}; // bir nesne olu�tur
                        c.first = 'a'; // onu istedi�iniz gibi de�erlerle doldurun
                        c.second = 'e';
                        c.third = 'i';
                        c.fourth = 'o';
                        c.fifth = 'u';

                        return c; // nesneyi d�nd�r
                    }

                public:
                    static inline Chars s_mychars { generate() }; // d�nd�r�len nesneyi s_mychars'a kopyala
                };

                int main()
                {
                    std::cout << MyClass::s_mychars.third; // i yazd�r

                    return 0;
                }
�lgili i�erik
Bunun i�in bir lambda da kullan�labilir.
Bu metodolojinin pratik bir �rne�ini 8.15 -- Global random numbers (Random.h) dersinde g�steriyoruz (bunu bir ad alan� yerine bir
statik s�n�f ile yap�yoruz, ayn� �ekilde �al���r)

15.8 � Friend Non-Member Fonksiyonlar
-------------------------------------
Bu b�l�m ve �nceki b�l�m boyunca, bir s�n�f�n �e�itli �yelerine kimin eri�ebilece�ini kontrol etmek i�in bir mekanizma sa�layan
eri�im kontrollerinin erdemlerini �vd�k. �zel �yeler yaln�zca s�n�f�n di�er �yeleri taraf�ndan eri�ilebilir ve genel �yeler
herkes taraf�ndan eri�ilebilir. 14.6 dersinde -- Eri�im Fonksiyonlar� konusunda, verilerinizi �zel tutman�n ve d�� �yeler
i�in bir genel aray�z olu�turman�n faydalar�n� tart��t�k.

Ancak, bu d�zenlemenin yeterli olmad��� veya ideal olmad��� durumlar vard�r.

�rne�in, baz� verileri y�netmeye odaklanan bir depolama s�n�f�n� d���n�n. �imdi diyelim ki bu verileri de g�stermek istiyorsunuz,
ancak g�sterimi y�neten kodun bir�ok se�ene�i vard�r ve bu nedenle karma��kt�r. Hem depolama y�netimi fonksiyonlar�n� hem de
g�sterim y�netimi fonksiyonlar�n� ayn� s�n�fa koyabilirsiniz, ancak bu i�leri kar��t�r�r ve karma��k bir aray�z olu�turur.
Ayr�ca onlar� ayr� tutabilirsiniz: depolama s�n�f� depolamay� y�netir ve ba�ka bir g�sterim s�n�f� t�m g�sterim yeteneklerini 
y�netir. Bu, g�zel bir sorumluluk ayr�m� yarat�r. Ancak g�sterim s�n�f�, daha sonra depolama s�n�f�n�n �zel �yelerine eri�emeyecek
ve i�ini yapamayabilir.

Alternatif olarak, s�zdizimsel olarak bir �ye fonksiyon yerine bir d�� �ye fonksiyonu kullanmay� tercih edebilece�imiz durumlar 
vard�r (bunu a�a��da bir �rnekle g�sterece�iz). Bu, genellikle operat�rlerin a��r� y�klenmesi durumunda ge�erlidir, bu konuyu 
gelecekteki derslerde tart��aca��z. Ancak d�� �ye fonksiyonlar ayn� soruna sahiptir - s�n�f�n �zel �yelerine eri�emezler.

E�er eri�im fonksiyonlar� (veya di�er genel �ye fonksiyonlar) zaten var ve uygulamaya �al��t���m�z yetenek i�in yeterliyse, 
o zaman harika - bunlar� kullanabiliriz (ve kullanmal�y�z). Ancak baz� durumlarda, bu fonksiyonlar mevcut de�ildir.
O zaman ne yapmal�?

Bir se�enek, s�n�fa yeni �ye fonksiyonlar eklemek olabilir, b�ylece di�er s�n�flar�n veya d�� �ye fonksiyonlar�n ba�ka t�rl� 
yapamayacaklar� i�i yapmalar�na izin verir. Ancak e�er s�n�f bizim de�ilse (belki bir ���nc� taraf k�t�phanesinin bir par�as�d�r),
muhtemelen s�n�f� de�i�tirmek istemeyiz (��nk� k�t�phaneyi g�ncellersek, bu eklemelerin �zerine yaz�l�r). Hatta s�n�f bizim olsa 
bile, belirli �eylerin genel halka a��k olmas�n� istemeyebiliriz.

Asl�nda ihtiyac�m�z olan �ey, eri�im kontrol sistemini duruma g�re a�man�n bir yoludur.

Arkada�l�k sihirlidir
---------------------
Bu zorlu�un cevab�, arkada�l�kt�r.

Bir s�n�f�n g�vdesi i�inde, bir arkada� bildirimi (friend anahtar kelimesi kullan�larak) derleyiciye ba�ka bir s�n�f�n veya
fonksiyonun art�k bir arkada� oldu�unu s�ylemek i�in kullan�labilir. C++, bir arkada�, ba�ka bir s�n�f�n �zel ve korumal� 
�yelerine tam eri�im hakk� verilmi� bir s�n�f veya fonksiyon (�ye veya d�� �ye) anlam�na gelir. Bu �ekilde, bir s�n�f di�er
s�n�flara veya fonksiyonlara �yelerine tam eri�im hakk� verebilir ve ba�ka hi�bir �eyi etkilemez.

Anahtar nokta �udur ki, Arkada�l�k her zaman �yelerine eri�ilecek olan s�n�f taraf�ndan sa�lan�r (eri�im isteyen s�n�f veya 
fonksiyon taraf�ndan de�il).Eri�im kontrolleri ve arkada�l�k verme aras�nda, bir s�n�f her zaman �yelerine kimlerin
eri�ebilece�ini kontrol etme yetene�ini korur.

�rne�in, depolama s�n�f�m�z g�sterim s�n�f�n� bir arkada� yapt�ysa, o zaman g�sterim s�n�f� depolama s�n�f�n�n t�m �yelerine
do�rudan eri�ebilir. G�sterim s�n�f�, bu do�rudan eri�imi depolama s�n�f�n�n g�sterimini uygulamak i�in kullanabilirken,
yap�sal olarak ayr� kalabilir.

Arkada� bildirimi, eri�im kontrollerinden etkilenmez, bu y�zden s�n�f g�vdesi i�inde nerede yer ald��� �nemli de�ildir.


Art�k arkada��n ne oldu�unu bildi�imize g�re, �ye olmayan i�levlere, �ye i�levlerine ve di�er s�n�flara arkada�l���n verildi�i
belirli �rneklere bakal�m. Bu derste �ye olmayan arkada�lar�n fonksiyonlar�n� tart��aca��z ve ard�ndan bir sonraki ders 
15.9 - Arkada� s�n�flar� ve arkada� �ye fonksiyonlar�nda arkada� s�n�flar�na ve arkada� �ye fonksiyonlar�na bir g�z ataca��z.

Friend Non-member Fonksiyonlar
------------------------------
Bir arkada� fonksiyon, bir s�n�f�n �zel ve korumal� �yelerine sanki o s�n�f�n bir �yesiymi� gibi eri�ebilen bir fonksiyondur
(�ye veya �ye olmayan). Di�er t�m konularda, arkada� fonksiyon normal bir fonksiyondur.

Bir s�n�f�n bir �ye olmayan fonksiyonu bir arkada� yapma �rne�ine bakal�m:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }

                    // ��te Accumulator'un arkada�� olan �ye olmayan fonksiyon void print(const Accumulator& accumulator) 
                    // i�in arkada� bildirimi
                    friend void print(const Accumulator& accumulator);
                };

                void print(const Accumulator& accumulator)
                {
                    // ��nk� print() Accumulator'un bir arkada��d�r
                    // Accumulator'un �zel �yelerine eri�ebilir
                    std::cout << accumulator.m_value;
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplay�c�ya 5 ekler

                    print(acc); // print() �ye olmayan fonksiyonunu �a��r�r

                    return 0;
                }

Bu �rnekte, Accumulator s�n�f�n�n bir nesnesini alan print() ad�nda bir �ye olmayan fonksiyon bildirdik. Print() Accumulator 
s�n�f�n�n bir �yesi olmad��� i�in, normalde �zel �ye m_value'ye eri�emezdi. Ancak, Accumulator s�n�f�n�n 
print(const Accumulator& accumulator) fonksiyonunu bir arkada� yapan bir arkada� bildirimi var, bu art�k m�mk�n.

Print() bir �ye olmayan fonksiyon oldu�u i�in (ve dolay�s�yla implicit bir nesnesi yok), print() ile �al��mak i�in a��k�a bir 
Accumulator nesnesi ge�memiz gerekti�ini unutmay�n.

Bir friend non-member bir s�n�f i�inde tan�mlama
------------------------------------------------
�stenirse �ye fonksiyonlar�n bir s�n�f i�inde tan�mlanabilece�i gibi, friend non-member fonksiyonlar da bir s�n�f i�inde 
tan�mlanabilir. A�a��daki �rnekte, arkada� �ye olmayan fonksiyon print() Accumulator s�n�f� i�inde tan�mlanm��t�r:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }

                    // S�n�f i�inde tan�mlanan arkada� fonksiyonlar �ye olmayan fonksiyonlard�r
                    friend void print(const Accumulator& accumulator)
                    {
                        // ��nk� print() Accumulator'un bir arkada��d�r
                        // Accumulator'un �zel �yelerine eri�ebilir
                        std::cout << accumulator.m_value;
                    }
                };

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplay�c�ya 5 ekler

                    print(acc); // print() �ye olmayan fonksiyonunu �a��r�r

                    return 0;
                }

Print() fonksiyonunun Accumulator i�inde tan�mland��� i�in, print() fonksiyonunun Accumulator'un bir �yesi oldu�unu
varsayabilirsiniz, ancak bu do�ru de�il. Print() bir arkada� olarak tan�mland��� i�in, bunun yerine bir non-member fonksiyon
olarak kabul edilir (sanki Accumulator d���nda tan�mlanm�� gibi).

S�zdizimsel olarak bir friend non-member fonksiyonu tercih etme
---------------------------------------------------------------
Bu dersin giri�inde, bazen bir �ye fonksiyon yerine bir �ye olmayan fonksiyonu tercih edebilece�imiz zamanlardan bahsetmi�tik.
�imdi bunun bir �rne�ini g�sterelim.

                #include <iostream>

                class Value
                {
                private:
                    int m_value{};

                public:
                    explicit Value(int v): m_value { v }  { }

                    bool isEqualToMember(const Value& v) const;
                    friend bool isEqualToNonmember(const Value& v1, const Value& v2);
                };

                bool Value::isEqualToMember(const Value& v) const
                {
                    return m_value == v.m_value;
                }

                bool isEqualToNonmember(const Value& v1, const Value& v2)
                {
                    return v1.m_value == v2.m_value;
                }

                int main()
                {
                    Value v1 { 5 };
                    Value v2 { 6 };

                    std::cout << v1.isEqualToMember(v2) << '\n';
                    std::cout << isEqualToNonmember(v1, v2) << '\n';

                    return 0;
                }
Bu �rnekte, iki Value nesnesinin e�it olup olmad���n� kontrol eden iki benzer fonksiyon tan�mlad�k. isEqualToMember() bir �ye
fonksiyonu ve isEqualToNonmember() bir �ye olmayan fonksiyondur. Bu fonksiyonlar�n nas�l tan�mland���na odaklanal�m.

isEqualToMember() fonksiyonunda, bir nesneyi dolayl� ve di�erini a��k�a ge�iriyoruz. Fonksiyonun uygulanmas� bunu yans�t�r 
ve m_value'nin dolayl� nesneye ait oldu�unu ve v.m_value'nin a��k parametreye ait oldu�unu zihinsel olarak uzla�t�rmam�z gerekir.

isEqualToNonmember() fonksiyonunda, her iki nesne de a��k�a ge�irilir. Bu, fonksiyonun uygulanmas�nda daha iyi bir paralellik
sa�lar, ��nk� m_value �yesi her zaman a��k�a bir a��k parametre ile �ne ��kar.

Hala v1.isEqualToMember(v2) �a�r� s�zdizimini isEqualToNonmember(v1, v2) �zerinde tercih edebilirsiniz. Ancak operat�r a��r� 
y�klemeyi ele ald���m�zda, bu konunun tekrar g�ndeme gelece�ini g�rece�iz.

�oklu Arkada�
-------------
Bir fonksiyon ayn� anda birden �ok s�n�f�n arkada�� olabilir. �rne�in, a�a��daki �rne�i d���n�n:

                #include <iostream>

                class Humidity; // Humidity'nin ileri bildirimi

                class Temperature
                {
                private:
                    int m_temp { 0 };
                public:
                    explicit Temperature(int temp) : m_temp { temp } { }

                    // bu sat�r i�in ileri bildirim gereklidir
                    friend void printWeather(const Temperature& temperature, const Humidity& humidity); 
                };

                class Humidity
                {
                private:
                    int m_humidity { 0 };
                public:
                    explicit Humidity(int humidity) : m_humidity { humidity } {  }

                    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
                };

                void printWeather(const Temperature& temperature, const Humidity& humidity)
                {
                    std::cout << "The temperature is " << temperature.m_temp <<
                       " and the humidity is " << humidity.m_humidity << '\n';
                }

                int main()
                {
                    Humidity hum { 10 };
                    Temperature temp { 12 };

                    printWeather(temp, hum);

                    return 0;
                }

Bu �rnekle ilgili belirtmeye de�er �� �ey var. �lk olarak, printWeather() hem Humidity hem de Temperature'� e�it derecede 
kulland��� i�in, bunun herhangi birine ait bir �ye olmas� mant�kl� de�ildir. �ye olmayan bir fonksiyon daha iyi �al���r. 
�kinci olarak, printWeather() hem Humidity hem de Temperature'�n arkada�� oldu�u i�in, her iki s�n�f�n nesnelerinden �zel verilere
eri�ebilir. Son olarak, �rne�in en �st�ndeki a�a��daki sat�ra dikkat edin:

                class Humidity;

Bu, Humidity s�n�f� i�in bir ileri bildirimdir. S�n�f ileri bildirimleri, fonksiyon ileri bildirimlerinin ayn� rol�n� oynar --
derleyiciye daha sonra tan�mlanacak bir tan�mlay�c� hakk�nda bilgi verirler. Ancak, fonksiyonlar�n aksine, s�n�flar�n d�n��
t�rleri veya parametreleri yoktur, bu y�zden s�n�f ileri bildirimleri her zaman sadece class ClassName �eklindedir
(e�er bunlar s�n�f �ablonlar� de�ilse).

Bu sat�r olmadan, derleyici bize Humidity'nin ne oldu�unu bilmedi�ini s�ylerken Temperature i�indeki arkada� bildirimini
ayr��t�r�rd�.

Arkada�l�k, veri gizleme ilkesini ihlal eder mi?
------------------------------------------------
Hay�r. Arkada�l�k, arkada��n �zel �yelerine eri�ece�i beklentisiyle veri gizlemeyi yapan s�n�f taraf�ndan verilir.
Bir arkada��, t�m ayn� eri�im haklar�na sahip olan s�n�f�n bir uzant�s� olarak d���n�n. Bu nedenle, eri�im beklenir, 
ihlal de�ildir.

Do�ru kullan�ld���nda, arkada�l�k, i�levselli�in tasar�m a��s�ndan mant�kl� oldu�unda ayr�lmas�na izin vererek bir program� 
daha bak�m� kolay hale getirebilir (eri�im kontrol� nedenleriyle bir arada tutmak zorunda kalmak yerine). Veya bir �ye fonksiyonu
yerine bir �ye olmayan fonksiyon kullanman�n daha mant�kl� oldu�u durumlarda.

Ancak, arkada�lar bir s�n�f�n uygulamas�na do�rudan eri�im hakk�na sahip oldu�u i�in, s�n�f�n uygulamas�ndaki de�i�iklikler 
genellikle arkada�larda da de�i�iklik yapmay� gerektirir. Bir s�n�f�n �ok say�da arkada�� varsa (veya bu arkada�lar�n arkada�lar�
varsa), bu bir dalga etkisi yaratabilir.

Bir arkada� fonksiyonu uygularken, m�mk�n oldu�unda do�rudan eri�im yerine s�n�f aray�z�n� kullanmay� tercih edin. Bu, arkada�
fonksiyonunuzu gelecekteki uygulama de�i�ikliklerinden koruyacak ve daha sonra de�i�tirilmesi ve/veya yeniden test edilmesi
gereken kod miktar�n� azaltacakt�r.

*** BEST -> Bir arkada� fonksiyonu, m�mk�n oldu�unda do�rudan eri�im yerine s�n�f aray�z�n� kullanmay� tercih etmelidir.

Arkada� fonksiyonlar� yerine Arkada� olmayan fonksiyonlar� tercih edin
----------------------------------------------------------------------
14.8 -- Veri gizlemenin faydalar� (kaps�lleme) dersinde, �ye olmayan fonksiyonlar� �ye fonksiyonlara tercih etmemiz gerekti�ini 
belirttik. Orada verilen ayn� nedenlerle, arkada� fonksiyonlar� yerine �ye olmayan fonksiyonlar� tercih etmeliyiz.

�rne�in, a�a��daki �rnekte, Accumulator'un uygulamas� de�i�tirilirse (�rne�in, m_value'yi yeniden adland�r�rsak), print()
fonksiyonunun uygulamas� da de�i�tirilmelidir:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 }; // e�er bunu yeniden adland�r�rsak

                public:
                    void add(int value) { m_value += value; } // bunu de�i�tirmemiz gerekecek

                    friend void print(const Accumulator& accumulator);
                };

                void print(const Accumulator& accumulator)
                {
                    std::cout << accumulator.m_value; // ve bunu da de�i�tirmemiz gerekecek
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplay�c�ya 5 ekleyin

                    print(acc); // print() �ye olmayan fonksiyonunu �a��r�n

                    return 0;
                }

Daha iyi bir fikir �u �ekildedir:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }
                    int value() const { return m_value; } // bu makul eri�im fonksiyonunu ekledik
                };

                void print(const Accumulator& accumulator) // art�k Accumulator'un arkada�� de�il
                {
                    std::cout << accumulator.value(); // do�rudan eri�im yerine eri�im fonksiyonunu kullan
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplay�c�ya 5 ekleyin

                    print(acc); // print() �ye olmayan fonksiyonunu �a��r�n

                    return 0;
                }

Bu �rnekte, print() fonksiyonu m_value'nin de�erini almak i�in value() eri�im fonksiyonunu kullan�r, m_value'ye do�rudan eri�mez.
�imdi Accumulator'un uygulamas� herhangi bir zaman de�i�tirilirse, print() fonksiyonunun g�ncellenmesi gerekmeyecektir.

*** BEST -> M�mk�n ve makul oldu�unda, bir fonksiyonu Arkada� olmayan bir fonksiyon olarak uygulamay� tercih edin.

Mevcut bir s�n�f�n genel aray�z�ne yeni �yeler eklerken dikkatli olun, ��nk� her fonksiyon (hatta basit olanlar bile) bir seviye 
karma��kl�k ve kar���kl�k ekler. Accumulator �rne�inde yukar�da, mevcut birikmi� de�eri almak i�in bir eri�im fonksiyonuna sahip
olman�n tamamen makul oldu�unu s�yleyebiliriz. Daha karma��k durumlarda, bir s�n�f�n aray�z�ne bir�ok yeni eri�im fonksiyonu
eklemek yerine arkada�l��� kullanmak tercih edilebilir.

15.9 � Arkada� S�n�flar ve Arkada� �ye Fonksiyonlar
---------------------------------------------------
Arkada� S�n�flar
----------------
Bir arkada� s�n�f, ba�ka bir s�n�f�n �zel ve korumal� �yelerine eri�ebilen bir s�n�ft�r.

��te bir �rnek:

                #include <iostream>

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                       : m_nValue { nValue }, m_dValue { dValue }
                    { }

                    // Display s�n�f�n� Storage'�n arkada�� yap
                    friend class Display;
                };

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                         : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    // ��nk� Display, Storage'�n arkada��d�r, Display �yeleri Storage'�n �zel �yelerine eri�ebilir
                    void displayStorage(const Storage& storage)
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // �nce double'� g�ster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }

                    void setDisplayIntFirst(bool b)
                    {
                         m_displayIntFirst = b;
                    }
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };

                    display.displayStorage(storage);

                    display.setDisplayIntFirst(true);
                    display.displayStorage(storage);

                    return 0;
                }
��nk� Display s�n�f�, Storage'�n bir arkada��d�r, Display �yeleri eri�im haklar�na sahip olduklar� herhangi bir Storage nesnesinin
�zel �yelerine eri�ebilir.

                Bu program a�a��daki sonucu �retir:

                6.7 5
                5 6.7
Arkada� s�n�flar hakk�nda birka� ek not
---------------------------------------
�lk olarak, Display, Storage'�n bir arkada�� olsa bile, Display'in Storage nesnelerinin *this i�aret�isine eri�imi yoktur 
(��nk� *this asl�nda bir fonksiyon parametresidir).

�kinci olarak, arkada�l�k kar��l�kl� de�ildir. Sadece Display, Storage'�n bir arkada��d�r diye Storage'�n da Display'in 
bir arkada�� oldu�u anlam�na gelmez. �ki s�n�f�n birbirinin arkada�� olmas�n� istiyorsan�z, her ikisi de di�erini bir arkada�
olarak bildirmelidir.

Yazar�n Notu -> E�er bu sizi canevinizden vurduysa �z�r dilerim.

S�n�f arkada�l��� da transitif de�ildir. E�er A s�n�f� B'nin bir arkada��ysa ve B, C'nin bir arkada��ysa, bu A'n�n C'nin
bir arkada�� oldu�u anlam�na gelmez.

Arkada� �ye Fonksiyonlar
------------------------
Bir s�n�f�n tamam�n� bir arkada� yapmak yerine, tek bir �ye fonksiyonu bir arkada� yapabilirsiniz. Bu, bir d�� �ye fonksiyonu 
bir arkada� yapmakla benzer �ekilde yap�l�r, tek fark �ye fonksiyonun ad�n�n kullan�lmas�d�r.

Ancak, asl�nda bu beklenenden biraz daha zor olabilir. �nceki �rne�i Display::displayStorage'� bir arkada� �ye fonksiyon yapacak
�ekilde d�n��t�relim. B�yle bir �ey deneyebilirsiniz:

                #include <iostream>

                class Display; // Display s�n�f� i�in ileri bildirim

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage �ye fonksiyonunu Storage s�n�f�n�n bir arkada�� yap
                    friend void Display::displayStorage(const Storage& storage); // hata: Storage, Display s�n�f�n�n tam 
                                                                                 // tan�m�n� g�rmedi
                };

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage)
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // �nce double'� g�ster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }


Ancak, bu i�e yaramayabilir. Bir �ye fonksiyonunu arkada� yapabilmek i�in, derleyicinin arkada� �ye fonksiyonunun s�n�f�n�n 
tam tan�m�n� g�rm�� olmas� gerekir (sadece ileri bildirim de�il). Storage s�n�f� hen�z Display s�n�f�n�n tam tan�m�n� g�rmedi�i
i�in, �ye fonksiyonunu arkada� yapmaya �al��t���m�z noktada derleyici hata verecektir.

Neyse ki, bu, Display s�n�f�n�n tan�m�n� Storage s�n�f�n�n tan�m�ndan �nceye ta��yarak kolayca ��z�l�r
(ayn� dosyada veya Display tan�m�n� bir ba�l�k dosyas�na ta��yarak ve Storage tan�mlanmadan �nce #include ederek).

                #include <iostream>

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage) // derleme hatas�: derleyici bir Storage'�n ne oldu�unu bilmiyor
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // �nce double'� g�ster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }
                };

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage �ye fonksiyonunu Storage s�n�f�n�n bir arkada�� yap
                    friend void Display::displayStorage(const Storage& storage); // �imdi tamam
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }
Ancak, �imdi ba�ka bir sorunumuz var. �ye fonksiyonu Display::displayStorage() Storage'� bir referans parametre olarak kullan�yor
ve biz sadece Storage tan�m�n� Display tan�m�n�n alt�na ta��d�k, derleyici bir Storage'�n ne oldu�unu bilmedi�inden �ikayet edecek
Bu sorunu, tan�m s�ras�n� yeniden d�zenleyerek ��zemeyiz, ��nk� o zaman �nceki d�zeltmemizi geri al�r�z.

Neyse ki, bu da birka� basit ad�mla d�zeltilebilir. �lk olarak, Storage s�n�f�n� bir ileri bildirim olarak ekleyebiliriz,
b�ylece derleyici, s�n�f�n tam tan�m�n� g�rmeden �nce bir Storage referans�yla iyi olacakt�r.

�kinci olarak, Display::displayStorage() tan�m�n� s�n�f�n d���na, Storage s�n�f�n�n tam tan�m�ndan sonraya ta��yabiliriz.

��te bu neye benziyor:

                #include <iostream>

                class Storage; // Storage s�n�f� i�in ileri bildirim

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage); // burada referans i�in Storage ileri bildirimi gereklidir
                };

                class Storage // Storage s�n�f�n�n tam tan�m�
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage �ye fonksiyonunu Storage s�n�f�n�n bir arkada�� yap
                    // S�n�f Display'�n tam tan�m�n� g�rmeyi gerektirir (��nk� displayStorage bir �ye)
                    friend void Display::displayStorage(const Storage& storage);
                };

                // �imdi Display::displayStorage'� tan�mlayabiliriz
                // Storage �yelerine eri�ti�imiz i�in Storage s�n�f�n�n tam tan�m�n� g�rmeyi gerektirir
                void Display::displayStorage(const Storage& storage)
                {
                    if (m_displayIntFirst)
                        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                    else // �nce double'� g�ster
                        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                }

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }
�imdi her �ey d�zg�n bir �ekilde derlenecek: Storage s�n�f�n�n ileri bildirimi, Display s�n�f� i�indeki Display::displayStorage()
bildirimini kar��lamak i�in yeterlidir. Display'�n tam tan�m�, Display::displayStorage()'� Storage'�n bir arkada�� olarak
bildirmeyi kar��lar. Ve Storage s�n�f�n�n tam tan�m�, �ye fonksiyonu Display::displayStorage()'�n tan�m�n� kar��lar.

E�er bu biraz kafa kar��t�r�c�ysa, program�n �zerindeki yorumlara bak�n. Anahtar noktalar, bir s�n�f ileri bildiriminin s�n�fa
olan referanslar� kar��lad���d�r. Ancak, bir s�n�f�n �yelerine eri�mek, derleyicinin tam s�n�f tan�m�n� g�rm�� olmas�n� gerektirir.

E�er bu biraz can s�k�c� gibi g�r�n�yorsa -- �yledir. Neyse ki, bu dans sadece her �eyi tek bir dosyada yapmaya �al��t���m�z
i�in gereklidir. Daha iyi bir ��z�m, her s�n�f tan�m�n� ayr� bir ba�l�k dosyas�na koymak ve �ye fonksiyon tan�mlar�n� kar��l�k 
gelen .cpp dosyalar�na koymakt�r. Bu �ekilde, t�m s�n�f tan�mlar� .cpp dosyalar�nda mevcut olur ve s�n�flar�n veya fonksiyonlar�n
yeniden d�zenlenmesi gerekmez!

15.10 � Ref Niteliklendiriciler ( Qualifiers )
----------------------------------------------
Yazar�n Notu

Bu bir se�meli derstir. Materyalle tan��mak i�in hafif bir okuma yapman�z� �neririz, ancak gelecek derslere devam etmek i�in
kapsaml� bir anlama gerekli de�ildir.

14.7 -- �ye Fonksiyonlar Veri �yelerine Referans D�nd�rme dersinde, veri �yelerine referans d�nd�ren eri�im fonksiyonlar�n�n
�a�r�lmas�n�n, dolayl� nesnenin bir rvalue oldu�unda tehlikeli olabilece�ini tart��t�k. ��te h�zl� bir �zet:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } //  getter const referans d�nd�r�r
                };

                // createEmployee() bir Employee'yi de�er olarak d�nd�r�r (bu, d�nd�r�len de�erin bir rvalue oldu�u anlam�na gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    // Durum 1: tamam: rvalue s�n�f nesnesinin �yesine d�nd�r�len referans� ayn� ifade i�inde kullan
                    std::cout << createEmployee("Frank").getName() << '\n';

                    // Durum 2: k�t�: rvalue s�n�f nesnesinin �yesine d�nd�r�len referans� daha sonra kullanmak �zere kaydet
                    const std::string& ref { createEmployee("Garbo").getName() }; // createEmployee()'nin d�nd�rd��� de�er yok 
                                                                                  // edildi�inde referans dangling olur
                    std::cout << ref << '\n'; // tan�ms�z davran��

                    return 0;
                }

Durum 2'de, createEmployee("Garbo")'dan d�nd�r�len rvalue nesne, ref'i ba�lat�ld�ktan sonra yok edilir, bu da ref'in yeni yok
edilen bir veri �yesine referans vermesine neden olur. ref'in sonraki kullan�m� tan�ms�z davran�� sergiler.

Bu, biraz bir ��kmaz sunar.

E�er getName() fonksiyonumuz de�er d�nd�r�rse, bu, dolayl� nesnemiz bir rvalue oldu�unda g�venlidir, ancak dolayl� nesnemiz bir
lvalue oldu�unda (ki bu en yayg�n durumdur) pahal� ve gereksiz bir kopya yapar.

E�er getName() fonksiyonumuz const referans d�nd�r�rse, bu verimlidir (std::string'in hi�bir kopyas� yap�lmaz), ancak dolayl�
nesne bir rvalue oldu�unda yanl�� kullan�labilir (bu, tan�ms�z davran��a neden olur).

�ye fonksiyonlar genellikle lvalue dolayl� nesneler �zerinde �a�r�ld���ndan, geleneksel se�enek const referans d�nd�rmektir ve 
sadece dolayl� nesne bir rvalue oldu�unda d�nd�r�len referans�n yanl�� kullan�lmas�ndan ka��nmakt�r.

Ref Niteliklendiriciler ( Qualifiers )
--------------------------------------
Yukar�da g�sterilen zorlu�un k�k�, yaln�zca bir fonksiyonun iki farkl� durumu hizmet etmesini istememizdir 
(dolayl� nesnemiz bir lvalue oldu�unda bir durum ve dolayl� nesnemiz bir rvalue oldu�unda bir durum). 
Bir durum i�in en uygun olan di�er durum i�in ideal de�ildir.

Bu t�r sorunlara yard�mc� olmak i�in, C++11, bir �ye fonksiyonun bir lvalue veya rvalue dolayl� nesne �zerinde �a�r�l�p 
�a�r�lmad���na dayal� olarak bir �ye fonksiyonu a��r� y�klememize izin veren az bilinen bir �zellik olan bir
ref-niteliklendirici tan�tt�. Bu �zelli�i kullanarak, getName() i�in iki versiyon olu�turabiliriz -- dolayl� nesnemiz 
bir lvalue oldu�unda bir durum ve dolayl� nesnemiz bir rvalue oldu�unda bir durum i�in biri.

�ncelikle, ref-qualify olmayan getName() versiyonumuzla ba�layal�m:


                auto& getName() const { return m_name; } // hem lvalue hem de rvalue implicit nesnelerle �a�r�labilir

Bu fonksiyonu ref-qualify etmek i�in, yaln�zca lvalue implicit nesneleri e�le�tirecek a��r� y�klemeye bir & nitelik ekleriz 
ve yaln�zca rvalue implicit nesneleri e�le�tirecek a��r� y�klemeye bir && nitelik ekleriz:

                //  & nitelik, yaln�zca lvalue implicit nesneleri e�le�tiren fonksiyonu a��r� y�kler, referans olarak d�nd�r�r
                const auto& getName() const &  { return m_name; } 

                // && nitelik, yaln�zca rvalue implicit nesneleri e�le�tiren fonksiyonu a��r� y�kler, de�er olarak d�nd�r�r
                auto        getName() const && { return m_name; } 

Bu fonksiyonlar farkl� a��r� y�klemeler oldu�u i�in, farkl� d�n�� t�rlerine sahip olabilirler! Lvalue-qualified a��r� y�klemimiz
const referans olarak d�nd�r�rken, rvalue-qualified a��r� y�klemimiz de�er olarak d�nd�r�r.

A�a��da bunun tam bir �rne�i verilmi�tir:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }

                    //  & nitelik, yaln�zca lvalue implicit nesneleri e�le�tiren fonksiyonu a��r� y�kler
                    const auto& getName() const &  { return m_name; } 
                    // && nitelik, yaln�zca rvalue implicit nesneleri e�le�tiren fonksiyonu a��r� y�kler
                    auto        getName() const && { return m_name; } 
                };

                // createEmployee() bir Employee'yi de�er olarak d�nd�r�r (bu, d�nd�r�len de�erin bir rvalue oldu�u anlam�na gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    Employee joe{};
                    joe.setName("Joe");
                    // Joe bir lvalue'dir, bu y�zden bu std::string& getName() & 'yi �a��r�r (bir referans d�nd�r�r)
                    std::cout << joe.getName() << '\n'; 

                    // Frank bir rvalue'dir, bu y�zden bu std::string getName() && 'yi �a��r�r (bir kopya yapar)
                    std::cout << createEmployee("Frank").getName() << '\n'; 

                    return 0;
                }

Bu, implicit nesnemiz bir lvalue oldu�unda performansl� �eyi yapmam�za ve implicit nesnemiz bir rvalue oldu�unda g�venli �eyi
yapmam�za olanak sa�lar.

Ref-qualified �ye fonksiyonlar hakk�nda baz� notlar
---------------------------------------------------
�ncelikle, ref-qualified olmayan a��r� y�klemeler ve ref-qualified a��r� y�klemeler bir arada bulunamaz. 
Birini veya di�erini kullan�n.

�kincisi, yaln�zca bir lvalue-qualified a��r� y�klem sa�lan�rsa (yani rvalue-qualified versiyon tan�mlanmam��sa),
bir rvalue implicit nesne ile fonksiyonun herhangi bir �a�r�s� bir derleme hatas� sonucunu verir. Bu, bir fonksiyonun rvalue
implicit nesnelerle kullan�lmas�n� tamamen �nlemenin kullan��l� bir yolunu sa�lar.

Peki neden ref-qualifiers kullanmay� �nermiyoruz?
-------------------------------------------------
Ref-qualifiers g�zel olsa da, bu �ekilde kullanman�n baz� dezavantajlar� vard�r.

*- Bir referans d�nd�ren her getter'a rvalue a��r� y�klemeler eklemek, s�n�fa kar���kl�k ekler, bu da �ok yayg�n olmayan ve iyi 
   al��kanl�klarla kolayca ka��n�labilen bir durumu hafifletir.

*- Bir rvalue a��r� y�klemesini de�er olarak d�nd�rmek, bir referans� g�venle kullanabilece�imiz durumlarda bile bir kopya
   (veya ta��ma) maliyetini �dememiz gerekti�i anlam�na gelir (�rne�in, dersin ba��ndaki �rnekteki durum 1).

Ayr�ca:

�o�u C++ geli�tiricisi bu �zelli�in fark�nda de�ildir (bu, kullan�mdaki hatalara veya verimsizliklere yol a�abilir).
Standart k�t�phane genellikle bu �zelli�i kullanmaz.
Yukar�daki t�m nedenlere dayanarak, ref-qualifiers kullanmay� en iyi uygulama olarak �nermiyoruz. Bunun yerine,
her zaman bir eri�im fonksiyonunun sonucunu hemen kullanmay� ve d�nd�r�len referanslar� daha sonra kullanmak i�in kaydetmemeyi
�neririz.

15.x � B�l�m 15 �zeti ve S�nav
------------------------------
B�l�m �ncelemesi

Her (statik olmayan) �ye fonksiyonun i�inde, this anahtar kelimesi, ge�erli �rt�k nesnenin adresini tutan bir const i�aret�idir.
Fonksiyonlar�n *this'i referans olarak d�nd�rmesine izin verebiliriz, b�ylece y�ntem zincirlemesi sa�lan�r, burada birka� �ye 
fonksiyon tek bir ifadede ayn� nesne �zerinde �a�r�labilir.

S�n�f tan�mlar�n�z�, s�n�f ile ayn� ad� ta��yan bir header dosyas�na koymay� tercih edin. �nemsiz �ye fonksiyonlar 
(�rne�in eri�im fonksiyonlar�, bo� g�vdeleri olan yap�land�r�c�lar vb.) s�n�f tan�m�n�n i�inde tan�mlanabilir.

�nemsiz olmayan �ye fonksiyonlar�, s�n�f ile ayn� ad� ta��yan bir kaynak dosyas�nda tan�mlamay� tercih edin.

Bir s�n�f t�r� i�inde tan�mlanan bir t�r, i� i�e t�r (veya �ye t�r) olarak adland�r�l�r. T�r takma adlar� da i� i�e olabilir.

Bir s�n�f �ablonu tan�m�n�n i�inde tan�mlanan �ye fonksiyonlar, s�n�f �ablonunun kendisinin �ablon parametrelerini kullanabilir.
S�n�f �ablonu tan�m�n�n d���nda tan�mlanan �ye fonksiyonlar, bir �ablon parametre bildirimini yeniden sa�lamal� ve s�n�f �ablonu
tan�m�n�n hemen alt�nda (ayn� dosyada) tan�mlanmal�d�r.

Statik �ye de�i�kenler, s�n�f�n t�m nesneleri taraf�ndan payla��lan statik s�reli �yelerdir. Statik �yeler, s�n�f�n hi�bir nesnesi
olu�turulmam�� olsa bile var olur. Onlara eri�mek i�in s�n�f ad�n�, kapsam ��z�mleme operat�r�n� ve �ye ad�n� kullanmay� tercih
edin.

Statik �yeleri inline yapmak, onlar�n s�n�f tan�m�n�n i�inde ba�lat�lmas�na olanak sa�lar.

Statik �ye fonksiyonlar, hi�bir nesne olmadan �a�r�labilen �ye fonksiyonlard�r. Bir *this i�aret�ileri yoktur ve statik olmayan
veri �yelerine eri�emezler.

Bir s�n�f�n g�vdesinin i�inde, bir arkada� bildirimi (friend anahtar kelimesi kullan�larak) derleyiciye ba�ka bir s�n�f�n veya 
fonksiyonun art�k bir arkada� oldu�unu s�ylemek i�in kullan�labilir. Bir arkada�, ba�ka bir s�n�f�n �zel ve korumal� �yelerine
tam eri�im hakk� verilmi� bir s�n�f veya fonksiyon (�ye veya d�� �ye) anlam�na gelir. Bir arkada� fonksiyon, bir s�n�f�n �zel
ve korumal� �yelerine, sanki o s�n�f�n bir �yesiymi� gibi eri�ebilen bir fonksiyon (�ye veya d�� �ye) anlam�na gelir. 
Bir arkada� s�n�f, ba�ka bir s�n�f�n �zel ve korumal� �yelerine eri�ebilen bir s�n�ft�r.
*/