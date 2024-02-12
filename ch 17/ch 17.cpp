#include <iostream>

int main()
{
    return 0;
}
/*
17.1 � std::array'a Giri�
-------------------------
16.1 -- Konteynerlere ve dizilere giri� dersinde, konteynerleri ve dizileri tan�tt�k. �zetlemek gerekirse:

Konteynerler, isimsiz nesnelerin (elementler olarak adland�r�l�r) bir koleksiyonu i�in depolama sa�lar.
Diziler, elementlerini haf�zada ard���k olarak tahsis eder ve herhangi bir elemente alt dizinleme yoluyla h�zl�, do�rudan eri�im sa�lar.
C++'da yayg�n olarak kullan�lan �� farkl� dizi tipi vard�r: std::vector, std::array ve C tarz� diziler.
16.10 -- std::vector yeniden boyutland�rma ve kapasite dersinde, dizilerin iki kategoriye ayr�ld���n� belirttik:

*- Sabit boyutlu diziler (ayn� zamanda sabit uzunluklu diziler olarak da adland�r�l�r), dizinin uzunlu�unun �rnekleme noktas�nda bilinmesini
   gerektirir ve bu uzunluk daha sonra de�i�tirilemez. C tarz� diziler ve std::array her ikisi de sabit boyutlu dizilerdir.
*- Dinamik diziler, �al��ma zaman�nda yeniden boyutland�r�labilir. std::vector bir dinamik dizidir.

�nceki b�l�mde, std::vector'a odakland�k, ��nk� h�zl�, nispeten kolay kullan�l�r ve �ok y�nl�d�r. Bu, bir dizi konteynerine ihtiya� duydu�umuzda 
ba�vuraca��m�z tipi yapar.

Peki neden her �ey i�in dinamik dizileri kullanm�yoruz?
-------------------------------------------------------
Dinamik diziler g��l� ve kullan��l�d�r, ancak hayattaki her �ey gibi, sunduklar� faydalar i�in baz� �d�nler verirler.

*- std::vector, sabit boyutlu dizilere g�re biraz daha az performansl�d�r. �o�u durumda fark� muhtemelen fark etmeyeceksiniz 
   (a��r� yeniden tahsislara neden olan d�zensiz kod yazmad���n�z s�rece).
*- std::vector, sadece �ok s�n�rl� ba�lamlarda constexpr'i destekler.
Modern C++'da, asl�nda bu son nokta �nemlidir. Constexpr dizileri, daha sa�lam kod yazma yetene�i sunar ve ayr�ca derleyici taraf�ndan daha y�ksek
optimize edilebilir. Her zaman bir constexpr dizisi kullanabilece�imiz zaman, kullanmal�y�z -- ve e�er bir constexpr dizisine ihtiyac�m�z varsa,
kullanmam�z gereken konteyner s�n�f� std::array'dir.

*** BEST -> Constexpr diziler i�in std::array, non-constexpr diziler i�in std::vector kullan�n.

Bir std::array Tan�mlama
------------------------
std::array, <array> ba�l���nda tan�mlanm��t�r. std::vector'a benzer �ekilde �al��acak �ekilde tasarlanm��t�r ve g�receksiniz ki, ikisi aras�nda 
daha �ok benzerlik vard�r.

�kisi aras�ndaki farklardan biri, bir std::array nas�l bildirdi�imizdir:

                #include <array>  // for std::array
                #include <vector> // for std::vector

                int main()
                {
                    std::array<int, 5> a {};  // 5 int'lik bir std::array

                    std::vector<int> b(5);    // 5 int'lik bir std::vector (kar��la�t�rma i�in)

                    return 0;
                }
std::array bildirimimizde iki �ablon arg�man� vard�r. �lki (int), dizi eleman�n�n tipini tan�mlayan bir tip �ablon arg�man�d�r. �kincisi (5),
dizi uzunlu�unu tan�mlayan integral bir non-tip �ablon arg�man�d�r.

Bir std::array'�n uzunlu�u bir sabit ifade olmal�d�r
----------------------------------------------------
Bir std::vector'�n aksine, �al��ma zaman�nda yeniden boyutland�r�labilen, bir std::array'�n uzunlu�u bir sabit ifade olmal�d�r. �o�unlukla,
uzunluk i�in sa�lanan de�er bir tam say� literali, constexpr de�i�keni veya kapsams�z bir numaraland�r�c� olacakt�r.

                #include <array>

                int main()
                {
                    std::array<int, 7> a {}; // Bir literel sabiti kullanarak

                    constexpr int len { 8 };
                    std::array<int, len> b {}; // Bir constexpr de�i�keni kullanarak

                    enum Colors
                    {
                         red,
                         green,
                         blue,
                         max_colors
                    };

                    std::array<int, max_colors> c {}; // Bir numaraland�r�c� kullanarak

                #define DAYS_PER_WEEK 7
                    std::array<int, DAYS_PER_WEEK> d {}; // Bir makro kullanarak (bunu yapmay�n, yerine bir constexpr de�i�keni kullan�n)

                    return 0;
                }
Not: Non-const de�i�kenler ve �al��ma zaman� sabitleri uzunluk i�in kullan�lamaz:
---------------------------------------------------------------------------------

                #include <array>
                #include <iostream>

                void foo(const int length) // length bir �al��ma zaman� sabitidir
                {
                    std::array<int, length> e {}; // hata: length bir sabit ifade de�il
                }

                int main()
                {
                    // non-const bir de�i�ken kullanarak
                    int numStudents{};
                    std::cin >> numStudents; // numStudents non-constant

                    std::array<int, numStudents> {}; // hata: numStudents bir sabit ifade de�il

                    foo(7);

                    return 0;
                }

Bir std::array'�n Toplu Ba�lat�lmas�
------------------------------------
Belki de �a��rt�c� bir �ekilde, std::array bir topluluktur. Bu, hi�bir yap�c�ya sahip olmad��� ve bunun yerine toplu ba�latma kullan�larak
ba�lat�ld��� anlam�na gelir. H�zl� bir �zet olarak, toplu ba�latma, topluluklar�n �yelerini do�rudan ba�latmam�za izin verir. Bunu yapmak i�in,
bir ba�lat�c� listesi sa�lar�z, bu da virg�lle ayr�lm�� ba�latma de�erlerinin s�sl� parantezlerle �evrili listesidir.

                #include <array>

                int main()
                {
                    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // s�sl� liste kullanarak kopya-liste ba�latma
                    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // s�sl� liste kullanarak liste ba�latma (tercih edilen)

                    return 0;
                }
Bu ba�latma formlar�n�n her biri, dizi �yelerini s�rayla ba�lat�r, 0. elemandan ba�lar.

Bir std::array, bir ba�lat�c� olmadan tan�mlan�rsa, elemanlar varsay�lan olarak ba�lat�l�r. �o�u durumda, bu, elemanlar�n ba�lat�lmam��
b�rak�lmas� sonucunu do�urur. Genellikle elemanlar�m�z�n ba�lat�lmas�n� istedi�imiz i�in, std::array, ba�lat�c� olmadan tan�mland���nda de�er
ba�lat�lmal�d�r (bo� s�sl� parantezler kullanarak).

                #include <array>
                #include <vector>

                int main()
                {
                    std::array<int, 5> a;   // �yeler varsay�lan olarak ba�lat�l�r (int elemanlar ba�lat�lmam�� b�rak�l�r)
                    std::array<int, 5> b{}; // �yeler de�er ba�lat�l�r (int elemanlar s�f�r ba�lat�l�r) (tercih edilen)

                    std::vector<int> v(5);  // �yeler de�er ba�lat�l�r (int elemanlar s�f�r ba�lat�l�r) (kar��la�t�rma i�in)

                    return 0;
                }

Bir ba�lat�c� listesinde tan�mlanan dizi uzunlu�undan daha fazla ba�lat�c� sa�lan�rsa, derleyici hata verecektir. Bir ba�lat�c� listesinde 
tan�mlanan dizi uzunlu�undan daha az ba�lat�c� sa�lan�rsa, ba�lat�c� olmayan kalan elemanlar de�er ba�lat�l�r:

                #include <array>

                int main()
                {
                    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // derleme hatas�: �ok fazla ba�lat�c�
                    std::array<int, 4> b { 1, 2 };          // arr[2] ve arr[3] de�er ba�lat�l�r

                    return 0;
                }

Const ve constexpr std::array
-----------------------------
Bir std::array const olabilir:

                #include <array>

                int main()
                {
                    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

                    return 0;
                }

Bir const std::array'�n elemanlar� a��k�a const olarak i�aretlenmemi� olsa bile, hala const olarak ele al�n�rlar (��nk� t�m dizi const).
std::array ayr�ca constexpr i�in tam deste�e sahiptir:

                #include <array>

                int main()
                {
                    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

                    return 0;
                }
Bu constexpr deste�i, std::array'� kullanma ana nedenidir.
*** BEST -> std::array'�n�z� m�mk�n oldu�unda constexpr olarak tan�mlay�n. E�er std::array'�n�z constexpr de�ilse, bunun yerine bir std::vector 
            kullanmay� d���n�n.

C++17'de std::array i�in S�n�f �ablon Arg�man ��kar�m� (CTAD)
-------------------------------------------------------------
C++17'deki CTAD (class template argument deduction) kullanarak, derleyicinin bir std::array'�n hem eleman tipini hem de dizi uzunlu�unu bir
ba�lat�c� listesinden ��karmas�n� sa�layabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // Tip, std::array<int, 5> olarak ��kar�l�r
                    constexpr std::array a2 { 9.7, 7.31 };     // Tip, std::array<double, 2> olarak ��kar�l�r

                    return 0;
                }
Bu s�zdizimini, pratik oldu�unda tercih ederiz. Derleyiciniz C++17 uyumlu de�ilse, tip ve uzunluk �ablon arg�manlar�n� a��k�a sa�laman�z
gerekecektir.

*** BEST -> Derleyicinin bir std::array'�n tipini ve uzunlu�unu ba�lat�c�lar�ndan ��karmas�n� sa�lamak i�in s�n�f �ablon arg�man ��kar�m�n� (CTAD)
            kullan�n.

C++, �ablon parametrelerinin k�smi atlanmas�n� desteklemez (C++20 itibariyle), bu y�zden bir std::array'�n sadece uzunlu�unu veya sadece tipini
atlamak i�in �ekirdek dil �zelli�i kullanman�n bir yolu yoktur:

                #include <iostream>

                int main()
                {
                    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // hata: �ok az �ablon arg�man� (uzunluk eksik)
                    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // hata: �ok az �ablon arg�man� (tip eksik)

                    return 0;
                }

Sadece Dizi Uzunlu�unu Atlayarak std::to_array Kullanma C++20
-------------------------------------------------------------
C++20'den itibaren, std::to_array yard�mc� fonksiyonunu kullanarak bir std::array'�n dizi uzunlu�unu atlamak m�mk�n olmu�tur:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Tipi ve boyutu belirt
                    constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };    // Sadece tipi belirt, boyutu ��kar
                    constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };         // Tipi ve boyutu ��kar

                    return 0;
                }
Ne yaz�k ki, std::to_array kullanmak, bir std::array'� do�rudan olu�turmaktan daha pahal�d�r, ��nk� istenen std::array'� kopya ba�latmak i�in
kullan�lan ge�ici bir std::array olu�turmay� i�erir. Bu nedenle, std::to_array, tipin ba�lat�c�lardan etkili bir �ekilde belirlenemedi�i 
durumlarda kullan�lmal� ve bir dizi bir�ok kez olu�turuldu�unda (�r. bir d�ng� i�inde) ka��n�lmal�d�r.

Operator[] Kullanarak Dizi Elemanlar�na Eri�im
----------------------------------------------
Bir std::vector gibi, bir std::array'�n elemanlar�na eri�menin en yayg�n yolu, alt dizin operat�r�n� (operator[]) kullanmakt�r:

                #include <array> // for std::array
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3]; // indeksi 3 olan eleman�n de�erini yazd�r (7)
                    std::cout << prime[9]; // ge�ersiz indeks (tan�ms�z davran��)

                    return 0;
                }
Bir hat�rlatma olarak, operator[] s�n�rlar�n kontrol�n� yapmaz. Ge�ersiz bir indeks sa�lan�rsa, tan�ms�z davran�� sonucu olu�ur.
Bir std::array'a birka� ba�ka �ekilde indeksleme hakk�nda bir sonraki derste tart��aca��z.

17.2 � std::array uzunlu�u ve indeksleme
----------------------------------------
16.3 dersinde -- std::vector ve unsigned uzunluk ve subscript problemi, standart k�t�phane konteyner s�n�flar�n�n uzunluklar ve indeksler i�in
unsigned de�erler kullanma karar�n� tart��t�k. ��nk� std::array bir standart k�t�phane konteyner s�n�f�d�r, ayn� sorunlara tabidir.

Bu derste, bir std::array'�n indeksini alman�n ve uzunlu�unu alman�n yollar�n� �zetleyece�iz. ��nk� std::vector ve std::array benzer aray�zlere
sahip oldu�u i�in, bu, std::vector i�in ele ald���m�z �eyi paralel hale getirecektir. Ancak sadece std::array'�n constexpr i�in tam deste�i
oldu�undan, biraz daha ona odaklanaca��z.

Devam etmeden �nce, �constexpr olmad�k�a, i�aret d�n���mleri daralt�c� d�n���mlerdir� �zerinde haf�zan�z� tazelemek iyi bir zaman olabilir 

Bir std::array'�n uzunlu�u std::size_t tipindedir
-------------------------------------------------
std::array, �u �ekilde g�r�nen bir �ablon struct olarak uygulanm��t�r:

                template<typename T, std::size_t N> // N is a non-type template parameter
                struct array;

G�rd���n�z gibi, dizi uzunlu�unu temsil eden non-type �ablon parametresi (N) std::size_t tipindedir. Ve muhtemelen �imdiye kadar fark�ndas�n�zd�r,
std::size_t b�y�k bir unsigned integral tipidir. Dolay�s�yla, bir std::array tan�mlad���m�zda, uzunluk non-type �ablon arg�man� ya std::size_t
tipinde olmal�d�r, ya da std::size_t tipinde bir de�ere d�n��t�r�lebilir olmal�d�r. Bu de�er constexpr olmal�d�r, bu y�zden bir signed integral 
de�er kulland���m�zda i�aret d�n���m� sorunlar�yla kar��la�may�z, ��nk� derleyici, bir signed integral de�eri derleme zaman�nda std::size_t'ye
d�n��t�rmeyi seve seve kabul eder ve bu daralt�c� bir d�n���m olarak kabul edilmez.

Bir kenara NOT�
---------------
C++23'ten �nce, C++'�n bile std::size_t i�in bir literal soneki yoktu, ��nk� genellikle constexpr bir std::size_t'ye ihtiya� duydu�umuz durumlar 
i�in int'ten std::size_t'ye implicit derleme zaman� d�n���m� yeterli olur.

Sonek, esas olarak tip ��kar�m� ama�lar� i�in eklendi, ��nk� constexpr auto x { 0 } size bir int yerine bir std::size_t verecektir.
Bu t�r durumlarda, a��k bir static_cast kullanmak zorunda kalmadan 0 (int) ile 0UZ (std::size_t) aras�nda ayr�m yapabilme yetene�i yararl�d�r.

std::array'�n uzunlu�u ve indeksleri size_type tipindedir, bu her zaman std::size_t'dir
---------------------------------------------------------------------------------------
Bir std::vector gibi, std::array de size_type ad�nda bir i� i�e ge�mi� typedef �yesi tan�mlar, bu da konteynerin uzunlu�u 
(ve destekleniyorsa indeksler) i�in kullan�lan tip i�in bir takma add�r. std::array durumunda, size_type her zaman std::size_t i�in bir takma add�r

std::array'�n uzunlu�unu tan�mlayan non-type �ablon parametresinin, size_type yerine a��k�a std::size_t olarak tan�mland���na dikkat edin. 
Bu, size_type'�n std::array'�n bir �yesi oldu�u ve o noktada tan�mlanmad��� i�indir. Bu, std::size_t'yi a��k�a kullanan tek yerdir -- 
her yerde ba�ka size_type kullan�l�r.

Bir std::array'�n uzunlu�unu almak
----------------------------------
Bir std::array nesnesinin uzunlu�unu alman�n �� yayg�n yolu vard�r.

�lk olarak, size() �ye fonksiyonunu kullanarak bir std::array nesnesinden uzunlu�unu sorabiliriz (bu, uzunlu�u unsigned size_type olarak d�nd�r�r):

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
                    std::cout << "uzunluk: " << arr.size() << '\n'; // uzunlu�u `size_type` tipinde d�nd�r�r (alias for `std::size_t`)
                    return 0;
                }

                Bu, �unu yazd�r�r:

                uzunluk: 5
std::string ve std::string_view'in aksine, hem length() hem de size() �ye fonksiyonuna sahipken (ayn� i�i yapan), std::array (ve C++'daki di�er 
�o�u konteyner tipi) sadece size()'a sahiptir.

�kinci olarak, C++17'de, std::size() non-member fonksiyonunu kullanabiliriz (bu, std::array i�in sadece size() �ye fonksiyonunu �a��r�r,
b�ylece uzunlu�u unsigned size_type olarak d�nd�r�r).

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr{ 9, 7, 5, 3, 1 };
                    std::cout << "uzunluk: " << std::size(arr); // C++17, uzunlu�u `size_type` tipinde d�nd�r�r (alias for `std::size_t`)

                    return 0;
                }

Son olarak, C++20'de, uzunlu�u b�y�k bir signed integral tip olarak d�nd�ren std::ssize() non-member fonksiyonunu kullanabiliriz
(genellikle std::ptrdiff_t):

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr { 9, 7, 5, 3, 1 };
                    std::cout << "uzunluk: " << std::ssize(arr); // C++20, uzunlu�u b�y�k bir signed integral tip olarak d�nd�r�r

                    return 0;
                }

Bu, uzunlu�u signed tip olarak d�nd�ren �� fonksiyondan sadece biridir.

Bir std::array'�n uzunlu�unu constexpr bir de�er olarak almak
-------------------------------------------------------------
Bir std::array'�n uzunlu�u constexpr oldu�u i�in, yukar�daki fonksiyonlar�n her biri bir std::array'�n uzunlu�unu constexpr bir de�er olarak 
d�nd�recektir (non-constexpr bir std::array nesnesi �zerinde �a�r�lsa bile)! Bu, bu fonksiyonlar�n herhangi birini sabit ifadelerde 
kullanabilece�imiz ve d�nd�r�len uzunlu�un daralt�c� bir d�n���m olmadan bir int'e d�n��t�r�lebilece�i anlam�na gelir:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array arr { 9, 7, 5, 3, 1 }; // not: bu �rnekte constexpr de�il
                    constexpr int uzunluk{ std::size(arr) }; // tamam: d�n�� de�eri constexpr std::size_t ve int'e d�n��t�r�lebilir,
                                                             // daralt�c� bir d�n���m de�il

                    std::cout << "uzunluk: " << uzunluk << '\n';

                    return 0;
                }

Visual Studio kullan�c�lar� i�in
--------------------------------
Visual Studio, yukar�daki �rnekte hatal� bir �ekilde C4365 uyar�s�n� tetikler. Sorun Microsoft'a bildirildi.

Uyar�

Bir dil hatas� nedeniyle, yukar�daki fonksiyonlar, (const) referansla ge�irilen bir std::array fonksiyon parametresi �zerinde �a�r�ld���nda
non-constexpr bir de�er d�nd�recektir:

                #include <array>
                #include <iostream>

                void foo(const std::array<int, 5> &arr)
                {
                    constexpr int uzunluk{ std::size(arr) }; // derleme hatas�!
                    std::cout << "uzunluk: " << uzunluk << '\n';
                }

                int main()
                {
                    std::array arr { 9, 7, 5, 3, 1 };
                    constexpr int uzunluk{ std::size(arr) }; // tamam
                    std::cout << "uzunluk: " << uzunluk << '\n';

                    foo(arr);

                    return 0;
                }

Bu hata, P2280 ile C++23'te ele al�nm��t�r. Yazma zaman�nda, az say�da derleyici bu �zelli�i desteklemektedir.

Bir ��z�m yolu, foo()'yu, dizi uzunlu�unun bir non-type �ablon parametresi oldu�u bir fonksiyon �ablonu yapmakt�r. Bu non-type �ablon parametresi
daha sonra fonksiyonun i�inde kullan�labilir. Bunu, 17.3 dersinde -- std::array'� ge�mek ve d�nd�rmek konusunda daha fazla tart���yoruz.

std::array'� operator[] veya at() �ye fonksiyonunu kullanarak subscripting
--------------------------------------------------------------------------
�nceki derste 17.1 -- std::array'a Giri�, bir std::array'� indekslemenin en yayg�n yolunun subscript operat�r�n� (operator[]) kullanmak oldu�unu 
belirttik. Bu durumda hi�bir s�n�rlama kontrol� yap�lmaz ve ge�ersiz bir indeks ge�irilirse tan�ms�z davran��a neden olur.

std::vector gibi, std::array'�n da �al��ma zaman�nda s�n�rlama kontrol� yapan bir at() �ye fonksiyonu vard�r. Genellikle indeksleme �ncesi 
s�n�rlama kontrol� yapmak veya derleme zaman�nda s�n�rlama kontrol� yapmak istedi�imiz i�in bu fonksiyonun kullan�lmas�n� �nermiyoruz.
Bu iki fonksiyon da indeksin size_type (std::size_t) tipinde olmas�n� bekler.

Bu fonksiyonlardan herhangi biri constexpr bir de�erle �a�r�l�rsa, derleyici bir constexpr d�n���m�n� std::size_t'ye yapar. Bu, daralt�c� bir
d�n���m olarak kabul edilmez, bu y�zden burada i�aret problemleriyle kar��la�mazs�n�z. Ancak, bu fonksiyonlardan herhangi biri non-constexpr bir
signed integral de�erle �a�r�l�rsa, std::size_t'ye d�n���m daralt�c� olarak kabul edilir ve derleyiciniz bir uyar� yay�nlayabilir. 

std::get() constexpr indeksler i�in derleme zaman�nda s�n�rlama kontrol� yapar
------------------------------------------------------------------------------
Bir std::array'�n uzunlu�u constexpr oldu�u i�in, indeksimiz de bir constexpr de�eri ise, derleyicinin derleme zaman�nda constexpr indeksimizin 
dizinin s�n�rlar� i�inde oldu�unu do�rulayabilece�ini ve constexpr indeksin s�n�rlar�n d���nda oldu�u durumda derlemeyi durdurabilece�ini
s�yleyebiliriz. Ancak, operator[] tan�m gere�i hi�bir s�n�rlama kontrol� yapmaz ve at() �ye fonksiyonu sadece �al��ma zaman�nda s�n�rlama kontrol� 
yapar. Ve fonksiyon parametreleri constexpr olamaz (constexpr veya consteval fonksiyonlar bile), bu y�zden nas�l constexpr bir indeks ge�eriz?

constexpr bir indeksimiz oldu�unda derleme zaman�nda s�n�rlama kontrol� almak i�in, indeksi bir non-type �ablon arg�man� olarak alan std::get()
fonksiyon �ablonunu kullanabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array prime{ 2, 3, 5, 7, 11 };

                    std::cout << std::get<3>(prime); // indeks 3 olan eleman�n de�erini yazd�r
                    std::cout << std::get<9>(prime); // ge�ersiz indeks (derleme hatas�)

                    return 0;
                }

std::get()'in uygulamas�n�n i�inde, non-type �ablon arg�man�n�n dizi uzunlu�undan daha k���k oldu�unu kontrol eden bir static_assert vard�r. 
�ablon arg�manlar� constexpr olmal�d�r, bu y�zden std::get() yaln�zca constexpr indekslerle �a�r�labilir. E�er de�ilse, static_assert derleme 
s�recini derleme hatas�yla durdurur.


17.3 � std::array'� ge�mek ve d�nd�rmek
---------------------------------------
std::array tipinde bir nesne, di�er herhangi bir nesne gibi bir fonksiyona ge�irilebilir. Bu, bir std::array'� de�er olarak ge�irirsek,
pahal� bir kopya yap�laca�� anlam�na gelir. Bu nedenle, genellikle bu t�r kopyalar� �nlemek i�in std::array'� (const) referans olarak ge�iririz.

Bir std::array ile hem eleman tipi hem de dizi uzunlu�u nesnenin tip bilgilerinin bir par�as�d�r. Bu nedenle, bir std::array'� bir fonksiyon 
parametresi olarak kulland���m�zda, hem eleman tipini hem de dizi uzunlu�unu a��k�a belirtmemiz gerekir:

                #include <array>
                #include <iostream>

                void passByRef(const std::array<int, 5>& arr) // burada <int, 5> belirtmeliyiz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD tipi std::array<int, 5> olarak ��kar�r
                    passByRef(arr);

                    return 0;
                }

CTAD (�u anda) fonksiyon parametreleriyle �al��maz, bu y�zden burada sadece std::array belirtebiliriz ve derleyicinin �ablon arg�manlar�n� 
��karmas�n� bekleyemeziz. 

Farkl� eleman tipleri veya uzunluklara sahip std::array'� ge�mek i�in fonksiyon �ablonlar�n� kullanma
-----------------------------------------------------------------------------------------------------
Her t�rl� eleman tipi veya herhangi bir uzunlukta std::array kabul edebilen bir fonksiyon yazmak i�in, std::array'�m�z�n hem eleman tipini
hem de uzunlu�unu parametrize eden bir fonksiyon �ablonu olu�turabiliriz ve sonra C++ bu fonksiyon �ablonunu kullanarak ger�ek tipler ve
uzunluklarla ger�ek fonksiyonlar� �rneklendirecektir.

std::array �u �ekilde tan�mlanm��t�r:

                template<typename T, std::size_t N> // N is a non-type template parameter
                struct array;

Ayn� �ablon parametre bildirimini kullanan bir fonksiyon �ablonu olu�turabiliriz:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N> // not: bu �ablon parametre bildirimi std::array i�in olanla ayn�
                void passByRef(const std::array<T, N>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'� std::array<int, 5> ��karmak i�in kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) �rne�ini olu�turacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'� std::array<int, 6> ��karmak i�in kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) �rne�ini olu�turacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'� std::array<double, 5> ��karmak i�in kullan
                    passByRef(arr3); // tamam: derleyici passByRef(const std::array<double, 5>& arr) �rne�ini olu�turacak

                    return 0;
                }

Yukar�daki �rnekte, std::array<T, N> tipinde bir parametreye sahip olan passByRef() ad�nda tek bir fonksiyon �ablonu olu�turduk. 
T ve N, �nceki sat�rdaki �ablon parametre bildiriminde tan�mlanm��t�r: template <typename T, std::size_t N>. T, �a��ran�n eleman tipini,
belirtmesine izin veren standart bir tip �ablon parametresidir. N, �a��ran�n dizi uzunlu�unu belirtmesine izin veren std::size_t 
tipinde bir non-type �ablon parametresidir.

Uyar�

std::array i�in non-type �ablon parametresinin tipinin std::size_t olmas� gerekti�ine dikkat edin, int de�il! Bu, 
std::array'�n template<class T, std::size_t N> struct array; olarak tan�mlanm�� olmas�ndand�r. E�er non-type �ablon parametresinin tipi olarak
int kullan�rsan�z, derleyici std::array<T, std::size_t> tipindeki arg�man� std::array<T, int> tipindeki parametreyle e�le�tiremez (ve �ablonlar
d�n���m yapmaz).

Bu nedenle, main() i�erisinden passByRef(arr) �a�r�s� yapt���m�zda (arr, std::array<int, 5> olarak tan�mlanm��t�r), derleyici 
void passByRef(const std::array<int, 5>& arr) �a�r�s�n� yapacak ve �rneklendirecektir. Benzer bir s�re� arr2 ve arr3 i�in de ger�ekle�ir.

B�ylece, her t�rl� eleman tipi ve uzunlu�a sahip std::array arg�manlar�n� i�leyebilecek fonksiyonlar� �rneklendirebilen tek bir fonksiyon �ablonu
olu�turduk! �stenirse, iki �ablon parametresinden sadece birini �ablonla�t�rmak da m�mk�nd�r. A�a��daki �rnekte, yaln�zca std::array'�n uzunlu�unu
parametrize ediyoruz, ancak eleman tipi a��k�a int olarak tan�mlanm��t�r:

                #include <array>
                #include <iostream>

                template <std::size_t N> // not: burada sadece uzunluk �ablonla�t�r�ld�
                void passByRef(const std::array<int, N>& arr) // eleman tipini int olarak tan�mlad�k
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'� std::array<int, 5> ��karmak i�in kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) �rne�ini olu�turacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'� std::array<int, 6> ��karmak i�in kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) �rne�ini olu�turacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'� std::array<double, 5> ��karmak i�in kullan
                    passByRef(arr3); // hata: derleyici e�le�en fonksiyonu bulam�yor

                    return 0;
                }

Auto non-type �ablon parametreleri C++20
----------------------------------------
Kendi fonksiyon �ablonlar�n�z i�in bir �ablon parametre bildiriminde kullanabilece�iniz bir non-type �ablon parametresinin tipini hat�rlamak 
(veya ara�t�rmak) can s�k�c�d�r.

C++20'de, bir non-type �ablon parametresinin arg�mandan tipini ��karmas�n� sa�lamak i�in bir �ablon parametre bildiriminde auto kullanabiliriz:

                #include <array>
                #include <iostream>

                template <typename T, auto N> // �imdi auto'yu N'nin tipini ��karmak i�in kullan�yoruz
                void passByRef(const std::array<T, N>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'� std::array<int, 5> ��karmak i�in kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) �rne�ini olu�turacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'� std::array<int, 6> ��karmak i�in kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) �rne�ini olu�turacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'� std::array<double, 5> ��karmak i�in kullan
                    passByRef(arr3); // tamam: derleyici passByRef(const std::array<double, 5>& arr) �rne�ini olu�turacak

                    return 0;
                }
E�er derleyiciniz C++20 yetenekliyse, bunu kullanmakta bir sak�nca yoktur.

Dizi Uzunlu�unda Static Assert Kullanma
---------------------------------------
Yukar�da sunulanlara benzer bir �ablon fonksiyonu d���n�n:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr);

                    return 0;
                }

printElement3() bu durumda iyi �al���rken, bu programda dikkatsiz bir programc�y� bekleyen potansiyel bir hata var. G�rd�n�z m�?

Yukar�daki program, dizinin indeksi 3 olan eleman�n�n de�erini yazd�r�r. Bu, dizinin indeksi 3 olan ge�erli bir eleman� oldu�u s�rece iyidir.
Ancak, derleyici, indeksi 3'�n s�n�rlar�n d���nda oldu�u dizileri ge�irmenize seve seve izin verecektir. �rne�in:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << arr[3] << '\n'; // ge�ersiz indeks
                }

                int main()
                {
                    std::array arr{ 9, 7 }; // 2 elemanl� bir dizi (ge�erli indeksler 0 ve 1)
                    printElement3(arr);

                    return 0;
                }

Bu, tan�ms�z davran��a yol a�ar. �deal olarak, b�yle bir �ey yapmaya �al��t���m�zda derleyicinin bizi uyarmas�n� isteriz!

�ablon parametrelerinin fonksiyon parametrelerine g�re bir avantaj�, �ablon parametrelerinin derleme zaman� sabitleri olmas�d�r. 
Bu, sabit ifadeler gerektiren yeteneklerden yararlanabilece�imiz anlam�na gelir.

Bu y�zden bir ��z�m, std::get()'i kullanmakt�r (derleme zaman�nda s�n�rlama kontrol� yapar) operator[] yerine (s�n�rlama kontrol� yapmaz):

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << std::get<3>(arr) << '\n'; // derleme zaman�nda indeks 3'�n ge�erli oldu�unu kontrol eder
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr); // tamam

                    std::array arr2{ 9, 7 };
                    printElement3(arr2); // derleme hatas�

                    return 0;
                }

Derleyici, printElement3(arr2) �a�r�s�na ula�t���nda, printElement3(const std::array<int, 2>&) fonksiyonunu �rneklendirir ve �a��r�r.Bu fonksiyonun
g�vdesindeki sat�r std::get<3>(arr)'dir. Dizi parametresinin uzunlu�u 2 oldu�undan, bu ge�ersiz bir eri�imdir ve derleyici bir hata yay�nlar.

Alternatif bir ��z�m, bir �nko�ulu kendimiz do�rulamak i�in static_assert kullanmakt�r:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    // �nko�ul: dizi uzunlu�u 3'ten b�y�k olmal�d�r, b�ylece eleman 3 var olur
                    static_assert (N > 3);

                    // bu noktadan itibaren dizi uzunlu�unun 3'ten b�y�k oldu�unu varsayabiliriz

                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr); // tamam

                    std::array arr2{ 9, 7 };
                    printElement3(arr2); // derleme hatas�

                    return 0;
                }

Derleyici, printElement3(arr2) �a�r�s�na ula�t���nda, printElement3(const std::array<int, 2>&) fonksiyonunu �rneklendirir ve �a��r�r. Bu fonksiyonun
g�vdesindeki sat�r static_assert (N > 3)'tir. N �ablon non-type parametresinin de�eri 2'dir ve 2 > 3 yanl��t�r, bu y�zden derleyici bir hata
yay�nlar.

Ana Fikir

Yukar�daki �rnekte, neden static_assert (N > 3); yerine static_assert (std::size(arr) > 3) kulland���m�z� merak ediyor olabilirsiniz. �kincisi, 
�nceki derste (17.2 -- std::array uzunlu�u ve indeksleme) bahsedilen dil hatas� nedeniyle C++23'ten �nce derlenmez.

Bir std::array'� D�nd�rme
-------------------------
S�zdizimi bir yana, bir std::array'� bir fonksiyona ge�irmek kavramsal olarak basittir - (const) referans olarak ge�irin. Ancak, bir std::array
d�nd�rmesi gereken bir fonksiyonumuz varsa? ��ler biraz daha karma��kla��yor. std::vector'�n aksine, std::array ta��nabilir de�ildir,
bu y�zden bir std::array'� de�er olarak d�nd�rmek, dizinin bir kopyas�n� yapar. Dizinin i�indeki elemanlar, ta��nabilirlerse ta��n�r,
aksi takdirde kopyalan�r.

Burada iki geleneksel se�enek vard�r ve hangisini se�ece�iniz duruma ba�l�d�r.

Bir std::array'� De�er Olarak D�nd�rme
--------------------------------------
A�a��dakilerin t�m� do�ru oldu�unda bir std:array'� de�er olarak d�nd�rmek tamam:

*- Dizi �ok b�y�k de�il.
*- Eleman tipi kopyalamak ucuz (veya ta��nabilir).
*- Kod, performans a��s�ndan hassas bir ba�lamda kullan�lm�yor.
Bu t�r durumlarda, std::array'�n bir kopyas� yap�l�r, ancak yukar�daki t�m durumlar do�ruysa, performans kayb� k���k olacakt�r ve �a��ran ki�iye
veri d�nd�rmenin en geleneksel yolunu s�rd�rmek en iyi se�enek olabilir.

                #include <array>
                #include <iostream>

                // de�er olarak d�nd�r
                template <typename T, std::size_t N>
                std::array<T, N> inputArray() // de�er olarak d�nd�r
                {
                    std::array<T, N> arr{};
                    std::size_t index { 0 };
                    while (index < N)
                    {
                        std::cout << "Enter value #" << index << ": ";
                        std::cin >> arr[index];

                        if (!std::cin) // hatal� giri�i i�le
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        ++index;
                    }

                    return arr;
                }

                int main()
                {
                    std::array<int, 5> arr { inputArray<int, 5>() };

                    std::cout << "Element 2'nin de�eri " << arr[2] << '\n';

                    return 0;
                }

Bu y�ntem hakk�nda birka� g�zel �ey var:

*- �a��ran ki�iye veri d�nd�rmenin en geleneksel yolunu kullan�r.
*- Fonksiyonun bir de�er d�nd�rd��� a��kt�r.
*- Bir dizi tan�mlayabilir ve onu tek bir ifadeyle ba�latabiliriz.
Ayr�ca birka� dezavantaj� da var:

*- Fonksiyon, dizinin ve t�m elemanlar�n�n bir kopyas�n� d�nd�r�r, bu ucuz de�ildir.
*- Fonksiyonu �a��rd���m�zda, parametrelerden ��kar�lamayan �ablon arg�manlar�n� a��k�a belirtmemiz gerekir.

Bir std::array'� Bir Out Parametresi Arac�l���yla D�nd�rme
----------------------------------------------------------
De�er olarak d�nd�rme �ok pahal�ysa, bunun yerine bir out-parametresi kullanabiliriz. Bu durumda, �a��ran ki�i, std::array'� non-const referans
olarak (veya adres olarak) ge�irmekten sorumludur ve fonksiyon daha sonra bu diziyi de�i�tirebilir.

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void inputArray(std::array<T, N>& arr) // non-const referans olarak ge�ir
                {
                    std::size_t index { 0 };
                    while (index < N)
                    {
                        std::cout << "Enter value #" << index << ": ";
                        std::cin >> arr[index];

                        if (!std::cin) // hatal� giri�i i�le
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        ++index;
                    }

                }

                int main()
                {
                    std::array<int, 5> arr {};
                    inputArray(arr);

                    std::cout << "Element 2'nin de�eri " << arr[2] << '\n';

                    return 0;
                }

Bu y�ntemin birincil avantaj�, dizinin hi�bir zaman kopyalanmamas�d�r, bu y�zden bu verimlidir.

Ayr�ca birka� dezavantaj� da var:

*- Bu veri d�nd�rme y�ntemi geleneksel de�ildir ve fonksiyonun arg�man� de�i�tirdi�i kolayca anla��lamaz.
*- Bu y�ntemi yaln�zca dizinin de�erlerini atamak i�in kullanabiliriz, onu ba�latamay�z.
*- B�yle bir fonksiyon, ge�ici nesneler �retmek i�in kullan�lamaz.

Bir std::vector D�nd�rme
------------------------
std::vector ta��nabilir ve pahal� kopyalar yapmadan de�er olarak d�nd�r�lebilir. Bir std::array'� de�er olarak d�nd�r�yorsan�z, std::array'�n�z ,
muhtemelen constexpr de�ildir ve std::vector kullanmay� (ve d�nd�rmeyi) d���nmelisiniz. Bir std::array, yaln�zca temel t�rlerin elemanlar�yla
s�n�rl� de�ildir. Daha ziyade, bir std::array'�n elemanlar�, bile�ik t�rler de dahil olmak �zere herhangi bir nesne t�r� olabilir. Bu,
bir std::array'� i�aret�ilerle veya bir std::array'� structlarla (veya s�n�flarla) olu�turabilece�iniz anlam�na gelir.

Ancak, bir std::array'� structlar veya s�n�flarla ba�latmak genellikle yeni programc�lar� zorlar, bu y�zden bu konuyu a��k�a ele alaca��z.

Yazar�n notu -> Bu derste noktalar�m�z� �rneklendirmek i�in yap�lar� kullanaca��z. Materyal s�n�flar i�in de e�it derecede ge�erlidir.

Bir std::array'� structlarla tan�mlama ve atama
-----------------------------------------------
Basit bir yap�yla ba�layal�m:

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };
Bir std::array'� House tan�mlamak ve elemanlar� atamak bekledi�iniz gibi �al���r:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    std::array<House, 3> houses{};

                    houses[0] = { 13, 1, 7 };
                    houses[1] = { 14, 2, 5 };
                    houses[2] = { 15, 2, 4 };

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                                  << " has " << (house.stories * house.roomsPerStory)
                                  << " rooms.\n";
                    }

                    return 0;
                }

                Yukar�daki, a�a��dakileri ��kt�lar:

                House number 13 has 7 rooms.
                House number 14 has 10 rooms.
                House number 15 has 8 rooms.
Bir std::array'� structlarla ba�latma
-------------------------------------
Bir dizi yap�lar� ba�latmak da, eleman t�r�n� a��k�a belirtti�iniz s�rece bekledi�iniz gibi �al���r:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    constexpr std::array houses { // CTAD'� �ablon arg�manlar� <House, 3> ��karmak i�in kullan
                            House{ 13, 1, 7 },
                            House{ 14, 2, 5 },
                            House{ 15, 2, 4 }
                        };

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                            << " has " << (house.stories * house.roomsPerStory)
                            << " rooms.\n";
                    }

                    return 0;
                }

Yukar�daki �rnekte, std::array'�n tipini std::array<House, 3> olarak ��karmak i�in CTAD'� kullan�yoruz. Daha sonra, 3 House nesnesini ba�lat�c�lar
olarak sa�l�yoruz, bu da gayet iyi �al���yor.

Her ba�lat�c� i�in eleman t�r�n� a��k�a belirtmeden ba�latma
------------------------------------------------------------
Yukar�daki �rnekte, her ba�lat�c�n�n eleman t�r�n� listelememiz gerekti�ini not edeceksiniz:

                constexpr std::array houses {
                        House{ 13, 1, 7 }, // burada House belirtiyoruz
                        House{ 14, 2, 5 }, // ve burada
                        House{ 15, 2, 4 }  // ve burada
                    };
Ama atama durumunda ayn�s�n� yapmak zorunda kalmad�k:

                // Derleyici, houses'�n her eleman�n�n bir House oldu�unu biliyor
                // bu y�zden her ataman�n sa� taraf�n� bir House'a otomatik olarak d�n��t�r�r
                houses[0] = { 13, 1, 7 };
                houses[1] = { 14, 2, 5 };
                houses[2] = { 15, 2, 4 };

Bu y�zden �unu denemeyi d���nebilirsiniz:


                // �al��maz
                constexpr std::array<House, 3> houses { // derleyiciye her eleman�n bir House oldu�unu s�yl�yoruz
                        { 13, 1, 7 }, // ama burada belirtmiyoruz
                        { 14, 2, 5 },
                        { 15, 2, 4 }
                    };
Belki de �a��rt�c� bir �ekilde, bu �al��maz. Nedenini inceleyelim.
Bir std::array, uygulama taraf�ndan tan�mlanan ad� olan tek bir C tarz� dizi �yesi i�eren bir yap� olarak tan�mlan�r:

                template<typename T, std::size_t N>
                struct array
                {
                    T implementation_defined_name[N]; // N elemanl� tip T olan bir C tarz� dizi
                }

Yazar�n notu

Hen�z C tarz� dizileri ele almad�k, ancak bu dersin amac� i�in, T implementation_defined_name[N];'in T tipinde N elemanl� sabit boyutlu bir dizi
oldu�unu (t�pk� std::array<T, N> implementation_defined_name; gibi) bilmelisiniz.

C tarz� dizileri yakla�an 17.7 dersinde -- C tarz� dizilere giri� konusunda ele al�yoruz.

Yukar�daki gibi evleri ba�latmaya �al��t���m�zda, derleyici ba�latmay� �u �ekilde yorumlar:

                // �al��maz
                constexpr std::array<House, 3> houses { // evler i�in ba�lat�c�
                    { 13, 1, 7 }, // C tarz� dizi �yesi i�in ba�lat�c� implementation_defined_name
                    { 14, 2, 5 }, // ?
                    { 15, 2, 4 }  // ?
                };

Derleyici, { 13, 1, 7 }'yi evlerin ilk �yesi i�in ba�lat�c� olarak yorumlar, bu da uygulama taraf�ndan tan�mlanan ad� olan C tarz� dizidir. 
Bu, C tarz� dizi eleman� 0'� { 13, 1, 7 } ile ba�lat�r ve geri kalan �yeler s�f�r ba�lat�l�r. Sonra derleyici, iki ba�latma de�eri daha 
sa�lad���m�z� ({ 14, 2, 7 } ve { 15, 2, 5 }) ke�feder ve �ok fazla ba�latma de�eri sa�lad���m�z� belirten bir derleme hatas� olu�turur.

Yukar�dakini do�ru bir �ekilde ba�latman�n yolu, ek bir set s�sl� parantez eklemektir:

                // Bu beklenildi�i gibi �al���r
                constexpr std::array<House, 3> houses { // evler i�in ba�lat�c�
                    { // C tarz� dizi �yesini ba�latmak i�in ekstra bir set s�sl� parantez
                        { 13, 4, 30 }, // dizi eleman� 0 i�in ba�lat�c�
                        { 14, 3, 10 }, // dizi eleman� 1 i�in ba�lat�c�
                        { 15, 3, 40 }, // dizi eleman� 2 i�in ba�lat�c�
                     }
                };

Gerekli olan ek s�sl� parantez setine dikkat edin (std::array yap� i�indeki C tarz� dizi �yesinin ba�lat�lmas�n� ba�latmak i�in). 
Bu s�sl� parantezlerin i�inde, daha sonra her bir eleman� kendi s�sl� parantezlerinin i�inde ba�latabiliriz.

Bu, eleman t�r� bir de�er listesi gerektirdi�inde ve ba�lat�c�lar�n bir par�as� olarak eleman t�r�n� a��k�a sa�lamad���m�zda std::array 
ba�lat�c�lar�na ek bir s�sl� parantez seti g�rece�iniz neden budur.

Ana Fikir

Bir std::array'� bir yap�, s�n�f veya dizi ile ba�lat�rken ve her ba�lat�c�yla eleman t�r�n� sa�lam�yorsan�z, derleyicinin neyi ba�lataca��n�
do�ru bir �ekilde yorumlamas� i�in ek bir s�sl� parantez �iftine ihtiyac�n�z olacakt�r.

Bu, toplu ba�latman�n bir �zelli�idir ve di�er standart k�t�phane konteyner t�rleri (liste yap�land�r�c�lar� kullananlar) bu durumlarda �ift s�sl� 
parantez gerektirmez.

��te tam bir �rnek:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    constexpr std::array<House, 3> houses {{ // �ift s�sl� parantezlere dikkat edin
                        { 13, 1, 7 },
                        { 14, 2, 5 },
                        { 15, 2, 4 }
                    }};

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                                  << " has " << (house.stories * house.roomsPerStory)
                                  << " rooms.\n";
                    }

                    return 0;
                }

Topluluklar i�in S�sl� Parantez Elizyonu
----------------------------------------
Yukar�daki a��klamay� g�z �n�nde bulundurarak, yukar�daki durumun neden �ift s�sl� parantez gerektirdi�ini, ancak g�rd���m�z t�m di�er durumlar�n 
yaln�zca tek s�sl� parantez gerektirdi�ini merak ediyor olabilirsiniz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // tek s�sl� parantezler

                    for (const auto n : arr)
                        std::cout << n << '\n';

                    return 0;
                }
Ortaya ��kt���na g�re, bu t�r diziler i�in �ift s�sl� parantez sa�layabilirsiniz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // �ift s�sl� parantezler

                    for (const auto n : arr)
                        std::cout << n << '\n';

                    return 0;
                }

Ancak, C++'daki topluluklar, birden �ok s�sl� parantezin ne zaman atlanabilece�ine dair baz� kurallar koyan bir kavram olan s�sl� parantez
elizyonunu destekler. Genellikle, bir std::array'� skalar (tek) de�erlerle ba�lat�rken veya t�r�n her elemanla a��k�a adland�r�ld��� s�n�f t�rleri
veya dizilerle ba�lat�rken s�sl� parantezleri atlayabilirsiniz.

Bir std::array'� her zaman �ift s�sl� parantezlerle ba�latmada bir sak�nca yoktur, ��nk� bu, s�sl� parantez elizyonunun belirli bir durumda
uygulanabilir olup olmad���n� d���nmek zorunda kalmam�z� �nler. Alternatif olarak, tek s�sl� parantezle ba�latmay� deneyebilir ve derleyici
genellikle bunu ��zemediyse �ikayet eder. Bu durumda, h�zl�ca ek bir s�sl� parantez seti ekleyebilirsiniz.

��te bir �rnek daha, burada bir std::array'� Student structlar� ile ba�lat�yoruz.

                #include <array>
                #include <iostream>
                #include <string_view>

                // Her ��rencinin bir kimli�i ve bir ad� vard�r
                struct Student
                {
                    int id{};
                    std::string_view name{};
                };

                // 3 ��rencimizin dizisi (her ba�lat�c�da Student'� belirtti�imiz i�in tekli s�sl�)
                constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

                const Student* findStudentById(int id)
                {
                    // T�m ��rencilere bak
                    for (auto& s : students)
                    {
                        // E�le�en kimli�i olan ��renciyi d�nd�r
                        if (s.id == id) return &s;
                    }

                    // E�le�en kimlik bulunamad�
                    return nullptr;
                }

                int main()
                {
                    constexpr std::string_view nobody { "nobody" };

                    const Student* s1 { findStudentById(1) };
                    std::cout << "Buldu�unuz: " << (s1 ? s1->name : nobody) << '\n';

                    const Student* s2 { findStudentById(3) };
                    std::cout << "Buldu�unuz: " << (s2 ? s2->name : nobody) << '\n';

                    return 0;
                }

                Bu, a�a��dakileri yazd�r�r:

                Buldu�unuz: Joe
                Buldu�unuz: nobody
Not: std::array students constexpr oldu�u i�in, findStudentById() fonksiyonumuz bir const pointer d�nd�rmelidir, bu da main() i�indeki Student 
pointerlar�n�n da const olmas� gerekti�i anlam�na gelir.

17.5 � std::reference_wrapper arac�l���yla referans dizileri
------------------------------------------------------------
�nceki derste, dizilerin herhangi bir nesne t�r�n�n ��elerine sahip olabilece�ini belirttik. Bu, temel t�rlerdeki (�r. int) nesneleri ve bile�ik
t�rlerdeki (�r. int'e i�aret�i) nesneleri i�erir.

                #include <array>
                #include <iostream>
                #include <vector>

                int main()
                {
                    int x { 1 };
                    int y { 2 };

                    [[maybe_unused]] std::array valarr { x, y };   // int de�erlerinin bir dizisi
                    [[maybe_unused]] std::vector ptrarr { &x, &y }; // int i�aret�ilerinin bir vekt�r�

                    return 0;
                }
Ancak, referanslar nesne olmad��� i�in, bir referans dizisi olu�turamazs�n�z. Bir dizinin ��eleri de atanabilir olmal�d�r ve referanslar yeniden
oturtulamaz.

                #include <array>
                #include <iostream>

                int main()
                {
                    int x { 1 };
                    int y { 2 };

                    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // derleme hatas�: referanslar�n bir dizisini tan�mlayamaz

                    int& ref1 { x };
                    int& ref2 { y };
                    [[maybe_unused]] std::array valarr { ref1, ref2 }; // tamam: bu asl�nda bir std::array<int, 2>, bir referans dizisi de�il

                    return 0;
                }

Bu derste, �rneklerde std::array kullanaca��z, ancak bu t�m dizi t�rlerine e�it derecede uygulanabilir.
Ancak, bir referans dizisi istiyorsan�z, bir ��z�m yolu vard�r.

std::reference_wrapper
----------------------
std::reference_wrapper, <functional> ba�l���nda ya�ayan bir standart k�t�phane s�n�f �ablonudur. Bir T t�r �ablon arg�man� al�r ve sonra T'ye 
modifiye edilebilir bir lvalue referans� gibi davran�r.

std::reference_wrapper hakk�nda birka� �eyi not etmekte fayda var:

*- Operator= bir std::reference_wrapper'� yeniden oturtur (referans verilen nesneyi de�i�tirir).
*- std::reference_wrapper<T> T&'a do�rudan d�n��t�r�l�r.
*- get() �ye fonksiyonu bir T& almak i�in kullan�labilir. Bu, referans verilen nesnenin de�erini g�ncellemek istedi�imizde yararl�d�r.
��te basit bir �rnek:

                #include <array>
                #include <functional> // std::reference_wrapper i�in
                #include <iostream>

                int main()
                {
                    int x { 1 };
                    int y { 2 };
                    int z { 3 };

                    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };

                    arr[1].get() = 5; // dizinin 1. ��esindeki nesneyi de�i�tir

                    std::cout << arr[1] << y << '\n'; // arr[1] ve y'nin de�i�tirildi�ini g�sterir, 55 yazd�r�r

                    return 0;
                }

                Bu �rnek a�a��dakileri yazd�r�r:

                55
arr[1].get() = 5 kullanmam�z ve arr[1] = 5 kullanmamam�z gerekti�ini unutmay�n. �kincisi belirsizdir, ��nk� derleyici,
std::reference_wrapper<int>'i de�er 5'e yeniden oturtmay� m� (zaten yasad��� olan bir �ey) yoksa referans verilen de�eri de�i�tirmeyi mi 
ama�lad���m�z� anlayamaz. get() kullanmak bunu belirsizle�tirir.

arr[1]'i yazd�r�rken, derleyici bir std::reference_wrapper<int>'i yazd�ramayaca��n� anlar, bu y�zden onu bir int&'ye d�n��t�r�r, 
ki bu yazd�r�labilir. Yani burada get() kullanmam�za gerek yok.

std::ref ve std::cref
---------------------
C++17'den �nce, CTAD (s�n�f �ablonu arg�man ��kar�m�) mevcut de�ildi, bu y�zden bir s�n�f t�r� i�in t�m �ablon arg�manlar� a��k�a listelenmeliydi.
Bu nedenle, bir std::reference_wrapper<int> olu�turmak i�in bunlardan birini yapabilirdiniz:

                int x { 5 };

                std::reference_wrapper<int> ref1 { x };        // C++11
                auto ref2 { std::reference_wrapper<int>{ x }}; // C++11

Uzun isim ve �ablon arg�manlar�n� a��k�a listeleme zorunlulu�u nedeniyle, bir�ok referans wrapper olu�turmak zor olabilirdi.
��leri kolayla�t�rmak i�in, std::ref() ve std::cref() fonksiyonlar�, std::reference_wrapper ve const std::reference_wrapper nesnelerini olu�turmak
i�in k�sayollar olarak sa�land�. Bu fonksiyonlar�n �ablon arg�man�n� a��k�a belirtmek zorunda kalmadan auto ile kullan�labilece�ini unutmay�n.

                int x { 5 };
                auto ref { std::ref(x) };   // C++11, std::reference_wrapper<int> olarak ��kar�r
                auto cref { std::cref(x) }; // C++11, std::reference_wrapper<const int> olarak ��kar�r

Tabii ki, �imdi C++17'de CTAD'ye sahip oldu�umuza g�re, bunu da yapabiliriz:

                std::reference_wrapper ref1 { x };        // C++17
                auto ref2 { std::reference_wrapper{ x }}; // C++17

Ama std::ref() ve std::cref() yazmas� daha k�sa oldu�u i�in, std::reference_wrapper nesneleri olu�turmak i�in hala yayg�n olarak kullan�l�yorlar.

17.6 � std::array ve en�meratorlar
----------------------------------
16.9 dersinde -- Dizinin indekslenmesi ve uzunlu�u en�meratorlar kullan�larak, diziler ve en�meratorlar hakk�nda konu�tuk. Art�k ara� setimizde
constexpr std::array oldu�una g�re, bu tart��may� s�rd�rece�iz ve birka� ek hile g�sterece�iz.

Dizi ba�lat�c�lar�n�n uygun say�s�n� sa�lamak i�in statik assert kullanma
-------------------------------------------------------------------------
Bir constexpr std::array'� CTAD kullanarak ba�lat�rken, derleyici dizi ba�lat�c�lar�n�n say�s�ndan dizinin ne kadar uzun olmas� gerekti�ini ��kar�r
Beklenenden daha az ba�lat�c� sa�lan�rsa, dizi beklenenden daha k�sa olacak ve onu indekslemek tan�ms�z davran��a yol a�abilir �rne�in:

                #include <array>
                #include <iostream>

                enum StudentNames
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_students // 5
                };

                int main()
                {
                    constexpr std::array testScores { 78, 94, 66, 77 }; // hata, sadece 4 de�er

                    std::cout << "Cartman'�n notu " << testScores[StudentNames::cartman] << '\n'; // ge�ersiz indeks nedeniyle tan�ms�z davran��

                    return 0;
                }
Bir constexpr std::array'deki ba�lat�c�lar�n say�s� makul bir �ekilde kontrol edilebiliyorsa, bunu bir statik assert kullanarak yapabilirsiniz:

                #include <array>
                #include <iostream>

                enum StudentNames
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_students // 5
                };

                int main()
                {
                    constexpr std::array testScores { 78, 94, 66, 77 };

                    // Test notlar�n�n say�s�n�n ��renci say�s�yla ayn� oldu�unu do�rula
                    static_assert(std::size(testScores) == max_students); // derleme hatas�: static_assert ko�ulu ba�ar�s�z oldu

                    std::cout << "Cartman'�n notu " << testScores[StudentNames::cartman] << '\n';

                    return 0;
                }
Bu �ekilde, daha sonra yeni bir en�merator ekler ama testScores'a kar��l�k gelen bir ba�lat�c� eklemeyi unutursan�z, program derlenmeyecektir.
Ayr�ca, iki farkl� constexpr std::array'�n ayn� uzunlu�a sahip oldu�unu sa�lamak i�in bir statik assert kullanabilirsiniz.

Daha iyi bir numaraland�rma giri�i ve ��k��� i�in constexpr dizilerini kullanma
-------------------------------------------------------------------------------
13.3 dersinde -- Kapsam d��� numaraland�rma giri�i ve ��k���, numaraland�r�c�lar�n adlar�n� ��kt� olarak vermenin birka� yolunu ve bir
numaraland�r�lm�� de�eri bir tamsay� olarak giri� yapman�n bir yolunu ele ald�k. Bu i�levleri biraz geli�tirelim. A�a��daki �rnekte, her 
numaraland�r�c�n�n ad�n� bir std::string_view olarak tutmak i�in bir dizi kullan�yoruz. Ard�ndan bu diziyi iki ama� i�in kullan�yoruz:

*- Numaraland�r�c�lar�n ad�n� bir dize olarak kolayca ��kt� almak.
*- Numaraland�r�c�lar�n ad�n� bir dize olarak aramak.
Sonuncusu, bize operator>>'nin bir numaraland�r�c�y� isimle (tamsay� yerine) nas�l giri� yapaca��n� ��retmemizi sa�lar!

                #include <array>
                #include <iostream>
                #include <string>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullan�n, b�ylece std::array tipi std::string_view olarak ��kar�r
                    using namespace std::string_view_literals; // sv soneki i�in
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // T�m renklerimiz i�in dize tan�mlad���m�zdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nas�l yazd�r�laca��n� ��retin
                // �imdilik bunu sihir olarak d���n�n ��nk� hen�z kulland��� hi�bir kavram� a��klamad�k
                // std::ostream, std::cout'un tipidir
                // D�n�� tipi ve parametre tipi referanslard�r (kopyalar�n yap�lmas�n� �nlemek i�in)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                // operator>>'e bir Color'� isimle nas�l giri� yapaca��n� ��retin
                // �imdilik bunu sihir olarak d���n�n
                // Color'� sabit olmayan bir referansla ge�iriyoruz, b�ylece i�levin de�erini de�i�tirmesine izin verebiliriz
                std::istream& operator>> (std::istream& in, Color::Type& color)
                {
                    std::string input {};
                    std::getline(in >> std::ws, input);

                    // Bir e�le�me bulup bulamayaca��m�z� g�relim
                    for (std::size_t index=0; index < Color::colorName.size(); ++index)
                    {
                        if (input == Color::colorName[index])
                        {
                            color = static_cast<Color::Type>(index);
                            return in;
                        }
                    }

                    // Bir e�le�me bulamad�k, bu y�zden giri� ge�ersiz olmal�yd�
                    // bu y�zden giri� ak���n� hata durumuna getirece�iz
                    in.setstate(std::ios_base::failbit);
                    return in;
                }

                int main()
                {
                    auto shirt{ Color::blue };
                    std::cout << "Your shirt is " << shirt << '\n';

                    std::cout << "Enter a new color: ";
                    std::cin >> shirt;
                    if (!std::cin)
                        std::cout << "Invalid\n";
                    else
                        std::cout << "Your shirt is now " << shirt << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Your shirt is blue
                Enter a new color: red
                Your shirt is now red

Aral�k tabanl� for-d�ng�leri ve numaraland�rmalar
-------------------------------------------------
Bazen, bir numaraland�rman�n numaraland�r�c�lar� �zerinde yinelemek i�in kullan��l� olabilecek durumlarla kar��la��r�z. Bunu bir for-d�ng�s�
kullanarak bir tam say� indeksi ile yapabiliriz, ancak bu muhtemelen tam say� indeksimizi numaraland�rma t�r�m�ze statik olarak d�kme
gerektirecektir.

                #include <array>
                #include <iostream>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullan�n, b�ylece std::array tipi std::string_view olarak ��kar�r
                    using namespace std::string_view_literals; // sv soneki i�in
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // T�m renklerimiz i�in stringler tan�mlad���m�zdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nas�l yazd�r�laca��n� ��retin
                // �imdilik bu sihir olarak d���n�n ��nk� hen�z kulland��� kavramlar� a��klamad�k
                // std::ostream, std::cout'un tipidir
                // D�n�� tipi ve parametre tipi referanslard�r (kopyalar�n yap�lmas�n� �nlemek i�in)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                int main()
                {
                    // T�m renklerimiz �zerinde yinelemek i�in bir for d�ng�s� kullan�n
                    for (int i=0; i < Color::max_colors; ++i )
                        std::cout << getColorName(static_cast<Color::Type>(i)) << '\n'; // burada �irkin static_cast

                    return 0;
                }
Ne yaz�k ki, aral�k tabanl� for-d�ng�leri, bir numaraland�rman�n numaraland�r�c�lar� �zerinde yinelemenize izin vermez:

                #include <array>
                #include <iostream>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullan�n, b�ylece std::array tipi std::string_view olarak ��kar�r
                    using namespace std::string_view_literals; // sv soneki i�in
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // T�m renklerimiz i�in stringler tan�mlad���m�zdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nas�l yazd�r�laca��n� ��retin
                // �imdilik bu sihir olarak d���n�n ��nk� hen�z kulland��� kavramlar� a��klamad�k
                // std::ostream, std::cout'un tipidir
                // D�n�� tipi ve parametre tipi referanslard�r (kopyalar�n yap�lmas�n� �nlemek i�in)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                int main()
                {
                    for (auto c: Color::Type) // derleme hatas�: numaraland�rmay� ge�emez
                        std::cout << c < '\n';

                    return 0;
                }
Bunun i�in bir�ok yarat�c� ��z�m var. Bir dizi �zerinde bir aral�k tabanl� for-d�ng�s� kullanabildi�imizden, en basit ��z�mlerden biri, 
numaraland�r�c�lar�m�z�n her birini i�eren bir constexpr std::array olu�turmak ve ard�ndan bunun �zerinde yinelemektir. Bu y�ntem,
numaraland�r�c�lar�n 0'dan ba�layarak s�ral� de�erlere sahip olmas� durumunda �al���r (ancak �o�u numaraland�rma bunu yapar).

Bir std::array'�n elemanlar�, Color::types'�n eleman t�r� Color::Type oldu�undan, c de�i�keni bir Color::Type olarak ��kar�lacakt�r, ki bu tam
olarak istedi�imiz �eydir!

Bu, a�a��dakileri yazd�r�r:

                black
                red
                blue

17.7 � C Tarz� Dizilere Giri�
-----------------------------
Art�k std::vector ve std::array'� ele ald���m�za g�re, dizilerin kapsam�n� son dizi t�r� olan C tarz� dizileri ele alarak tamamlayaca��z.
16.1 dersinde -- Konteynerlere ve dizilere giri� konusunda belirtildi�i gibi, C tarz� diziler C dilinden miras al�nm��t�r ve C++'�n �ekirdek
diline yerle�iktir (di�er t�m dizi t�rlerinin aksine, bunlar standart k�t�phane konteyner s�n�flar�d�r). Bu, onlar� kullanmak i�in bir ba�l�k 
dosyas�n� #include etmemiz gerekti�i anlam�na gelir.

Bir parantez i�inde...
----------------------
Dil taraf�ndan yerel olarak desteklenen tek dizi t�r� olduklar� i�in, standart k�t�phane dizi konteyner t�rleri (�r. std::array ve std::vector)
genellikle bir C tarz� dizi kullan�larak uygulan�r.

Bir C Tarz� Dizi Bildirme
-------------------------
�ekirdek dilin bir par�as� olduklar� i�in, C tarz� dizilerin kendi �zel bildirim s�zdizimleri vard�r. Bir C tarz� dizi bildiriminde,
bir nesnenin bir C tarz� dizi oldu�unu derleyiciye s�ylemek i�in k��eli parantezler ([]) kullan�r�z. K��eli parantezlerin i�inde, iste�e ba�l� 
olarak dizinin uzunlu�unu sa�layabiliriz, bu, derleyiciye dizide ka� eleman oldu�unu s�yleyen std::size_t t�r�nde bir integral de�erdir.
A�a��daki tan�m, 30 adet int eleman� i�eren testScore ad�nda bir C tarz� dizi de�i�keni olu�turur:

                int main()
                {
                    // testScore ad�nda 30 de�er ba�lat�lm�� int eleman� i�eren bir C tarz� dizi tan�mlar (include gerekmez)
                    int testScore[30] {};      

                    // Kar��la�t�rma i�in, i�te 30 de�er ba�lat�lm�� int eleman� i�eren bir std::array (requires #including <array>)
                    std::array<int, 30> arr{}; 

                    return 0;
                }

Bir C tarz� dizinin uzunlu�u en az 1 olmal�d�r. Dizi uzunlu�u s�f�r, negatif veya integral olmayan bir de�erse derleyici hata verecektir.

Bir c-style dizinin uzunlu�u sabit bir ifade olmal�d�r
------------------------------------------------------
std::array gibi, bir C-style dizi tan�mlarken, dizinin uzunlu�u bir sabit ifade olmal�d�r (tipi std::size_t olsa da, bu genellikle �nemli de�ildir)

�pucu -> Baz� derleyiciler, C99 �zelli�i olan de�i�ken uzunluklu diziler (VLAs) ile uyumluluk i�in constexpr olmayan uzunluklarda diziler 
         olu�turmay� kabul edebilir.

De�i�ken uzunluklu diziler  C++ da ge�erli de�ildir ve C++ programlar�nda kullan�lmamal�d�r. E�er derleyiciniz bu dizilere izin veriyorsa, 
muhtemelen derleyici uzant�lar�n� devre d��� b�rakmay� unuttunuz (bkz. 0.10 -- Derleyicinizi yap�land�rma: Derleyici uzant�lar�).

Bir C-style diziyi alt dizinleme
--------------------------------
std::array ile oldu�u gibi, C-style diziler de alt dizin operat�r� (operator[]) kullan�larak indekslenebilir:

                #include <iostream>

                int main()
                {
                    int arr[5]; // 5 int de�erinin bir dizisini tan�mla

                    arr[1] = 7; // alt dizin operat�r�n� kullanarak dizi ��esi 1'i indeksle
                    std::cout << arr[1]; // 7 yazd�r�r

                    return 0;
                }
Standart k�t�phane konteyner s�n�flar�n�n aksine (sadece unsigned indeksleri kullan�r), bir C-style dizinin indeksi ya bir signed ya da
bir unsigned tam say� veya kapsams�z bir numaraland�rma olabilir. Bu, C-style dizilerin standart k�t�phane konteyner s�n�flar�n�n t�m i�aret
d�n���m indeksleme sorunlar�na tabi olmad��� anlam�na gelir!

                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };

                    int s { 2 };
                    std::cout << arr[s] << '\n'; // signed indeks kullanmak tamam

                    unsigned int u { 2 };
                    std::cout << arr[u] << '\n'; // unsigned indeks kullanmak tamam

                    return 0;
                }

�pucu -> C-style diziler signed veya unsigned indeksleri (veya kapsams�z numaraland�rmalar�) kabul eder.
operator[] herhangi bir s�n�r kontrol� yapmaz ve s�n�rlar�n d���nda bir indeks ge�mek tan�ms�z davran��a yol a�ar.

Bir parantez a�mak gerekirse, Bir dizi tan�mlarken (�r. int arr[5]), [] kullan�m� bildirim s�zdiziminin bir par�as�d�r, alt dizin operat�r�
operator[]'nin bir �a�r�s� de�ildir.

C-style dizilerin toplu ba�lat�lmas�
------------------------------------
std::array gibi, C-style diziler de topluluktur, bu da onlar�n toplu ba�latma ile ba�lat�labilece�i anlam�na gelir. H�zl� bir hat�rlatma olarak, 
toplu ba�latma, topluluklar�n �yelerini do�rudan ba�latmam�z� sa�lar. Bunu yapmak i�in, bir ba�lat�c� listesi sa�lar�z, bu bir virg�lle ayr�lm�� 
ba�latma de�erlerinin s�sl� parantezlerle �evrili listesidir.

                int main()
                {
                    int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // s�sl� liste kullanarak kopya-liste ba�latma
                    int prime[5] { 2, 3, 5, 7, 11 };         // s�sl� liste kullanarak liste ba�latma (tercih edilir)

                    return 0;
                }
Bu ba�latma formlar�n�n her biri, dizi �yelerini s�rayla ba�lat�r,Varsay�lan olarak 0 ��esiyle ba�lar. E�er bir C-style dizi i�in bir ba�lat�c� 
sa�lamazsan�z, ��eler varsay�lan olarak ba�lat�l�r. �o�u durumda, bu ��elerin ba�lat�lmam�� b�rak�lmas� sonucunu do�urur. Genellikle ��elerimizin 
ba�lat�lmas�n� istedi�imiz i�in, ba�lat�c�lar� olmayan C-style diziler tan�mland���nda de�er ba�latmal�d�r (bo� s�sl� parantezler kullanarak).

                int main()
                {
                    int arr1[5];    // �yeler varsay�lan olarak ba�lat�l�r int ��eleri ba�lat�lmam�� b�rak�l�r)
                    int arr2[5] {}; // �yeler de�er ba�lat�l�r (int ��eleri s�f�r ba�lat�l�r) (tercih edilir)

                    return 0;
                }
E�er bir ba�lat�c� listesinde tan�mlanan dizi uzunlu�undan daha fazla ba�lat�c� sa�lan�rsa, derleyici hata verecektir. E�er bir ba�lat�c�
listesinde tan�mlanan dizi uzunlu�undan daha az ba�lat�c� sa�lan�rsa, ba�lat�c�s� olmayan kalan ��eler de�er ba�lat�l�r:

                int main()
                {
                    int a[4] { 1, 2, 3, 4, 5 }; // derleme hatas�: �ok fazla ba�lat�c�
                    int b[4] { 1, 2 };          // arr[2] ve arr[3] de�er ba�lat�l�r

                    return 0;
                }
Bir C-style dizi kullanman�n bir dezavantaj�, ��enin t�r�n�n a��k�a belirtilmesi gerekti�idir. CTAD �al��maz ��nk� C-style diziler s�n�f �ablonlar�
de�ildir. Ve bir dizinin ��e t�r�n� ba�lat�c�lar listesinden ��karmaya �al��mak i�in auto kullanmak da i�e yaramaz:

                int main()
                {
                    auto squares[5] { 1, 4, 9, 16, 25 }; // derleme hatas�: C tarz� dizilerde t�r ��kar�m� kullan�lamaz

                    return 0;
                }

Uzunluk Atlanm��
----------------
A�a��daki dizi tan�m�nda ince bir fazlal�k var. G�rd�n�z m�?

                int main()
                {
                    const int prime[5] { 2, 3, 5, 7, 11 }; // prime'�n uzunlu�u 5

                    return 0;
                }

Derleyiciye dizinin uzunlu�unun 5 oldu�unu a��k�a s�yl�yoruz ve ard�ndan onu 5 elemanla ba�lat�yoruz. Bir C tarz� diziyi bir ba�lat�c� listesiyle
ba�latt���m�zda, uzunlu�u (dizi tan�m�nda) atlayabilir ve derleyicinin dizinin uzunlu�unu ba�lat�c�lar�n say�s�ndan ��karmas�na izin verebiliriz.

A�a��daki dizi tan�mlar� ayn� �ekilde davran�r:

                int main()
                {
                    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 a��k�a uzunlu�u 5 olarak tan�mland�
                    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 derleyici taraf�ndan uzunlu�u 5 olarak ��kar�ld�

                    return 0;
                }
Bu, yaln�zca t�m dizi �yeleri i�in ba�lat�c�lar a��k�a sa�land���nda �al���r.

                int main()
                {
                    int bad[] {}; // hata: derleyici bunu izin verilmeyen bir s�f�r uzunluklu dizi olarak ��karacak!

                    return 0;
                }
Bir C tarz� dizinin t�m elemanlar�n� bir ba�lat�c� listesiyle ba�lat�rken, uzunlu�u atlamak ve derleyicinin dizinin uzunlu�unu hesaplamas�na 
izin vermek tercih edilir. Bu �ekilde, ba�lat�c�lar eklenir veya kald�r�l�rsa, dizinin uzunlu�u otomatik olarak ayarlan�r ve tan�mlanan dizi 
uzunlu�u ve sa�lanan ba�lat�c�lar�n say�s� aras�nda bir uyumsuzluk riski yoktur.

*** BEST -> Her dizi eleman�n� bir de�erle a��k�a ba�lat�rken, bir C tarz� dizinin uzunlu�unu atlamay� tercih edin.

Const ve constexpr C tarz� diziler
----------------------------------
std::array gibi, C tarz� diziler de const veya constexpr olabilir. Di�er const de�i�kenler gibi, const diziler ba�lat�lmal�d�r ve elemanlar�n 
de�eri sonradan de�i�tirilemez.

                #include <iostream>

                namespace ProgramData
                {
                    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // constexpr int dizisi
                }

                int main()
                {
                    const int prime[5] { 2, 3, 5, 7, 11 }; // const int dizisi
                    prime[0] = 17; // derleme hatas�: const int de�i�tirilemez

                    return 0;
                }

C tarz� bir dizinin sizeof'u
----------------------------
�nceki derslerde, sizeof() operat�r�n� bir nesnenin veya tipin boyutunu bayt cinsinden almak i�in kulland�k. Bir C tarz� diziye uyguland���nda, 
sizeof() t�m dizinin kulland��� bayt say�s�n� d�nd�r�r:

                #include <iostream>

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 }; // derleyici prime'�n uzunlu�unu 5 olarak ��karacak

                    std::cout << sizeof(prime); // 20 yazd�r�r (4 baytl�k int varsay�l�rsa)

                    return 0;
                }
4 baytl�k int varsay�l�rsa, yukar�daki program 20 yazd�r�r. Prime dizisi, her biri 4 bayt olan 5 int eleman� i�erir, bu y�zden 5 * 4 = 20 bayt.
Burada hi�bir fazlal�k yok. Bir dizi nesnesi, elemanlar�n� ve ba�ka hi�bir �ey i�ermez.

C-stil bir dizinin uzunlu�unu alma
----------------------------------
C++17'de, <iterator> ba�l���nda tan�mlanan std::size() kullanabiliriz, bu da dizinin uzunlu�unu std::size_t t�r�nde bir unsigned integral de�er 
olarak d�nd�r�r. C++20'de, std::ssize() kullanabiliriz, bu da dizinin uzunlu�unu b�y�k bir signed integral t�r�nde bir de�er olarak d�nd�r�r 
(muhtemelen std::ptrdiff_t).

                #include <iostream>
                #include <iterator> // std::size ve std::ssize i�in

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };   // derleyici prime'�n uzunlu�unu 5 olarak ��kar�r

                    std::cout << std::size(prime) << '\n';  // C++17, unsigned integral de�er 5 d�nd�r�r
                    std::cout << std::ssize(prime) << '\n'; // C++20, signed integral de�er 5 d�nd�r�r

                    return 0;
                }

C-stil bir dizinin uzunlu�unu alma (C++14 veya daha eski)
---------------------------------------------------------
C++17'den �nce, C-stil bir dizinin uzunlu�unu almak i�in standart bir k�t�phane fonksiyonu yoktu.
E�er C++11 veya C++14 kullan�yorsan�z, bunun yerine bu fonksiyonu kullanabilirsiniz:

                #include <iostream>

                template <typename T, std::size_t N>
                constexpr std::size_t length(const T(&)[N]) noexcept
                {
                    return N;
                }

                int main() {

                    int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
                    std::cout << "Dizinin: " << length(array) << " eleman� var\n";

                    return 0;
                }
Bu, bir C-stil dizisini referans olarak alan ve ard�ndan dizinin uzunlu�unu temsil eden non-type template parametresini d�nd�ren bir fonksiyon
�ablonu kullan�r. �ok daha eski kod tabanlar�nda, bir C-stil dizisinin uzunlu�unun, t�m dizinin boyutunu bir dizi eleman�n�n boyutuna b�lerken
belirlendi�ini g�rebilirsiniz:

                #include <iostream>

                int main()
                {
                    int array[8] {};
                    std::cout << "Dizinin: " << sizeof(array) / sizeof(array[0]) << " eleman� var\n";

                    return 0;
                }
                Bu, �unu yazd�r�r:

                Dizinin: 8 eleman� var
Bu nas�l �al���r? �lk olarak, t�m dizinin boyutunun, dizinin uzunlu�u ile bir eleman�n boyutunun �arp�m�na e�it oldu�unu not edin.
Daha kompakt bir �ekilde ifade edersek: dizi boyutu = uzunluk * eleman boyutu.

Cebir kullanarak, bu denklemi yeniden d�zenleyebiliriz: uzunluk = dizi boyutu / eleman boyutu. Eleman boyutu i�in genellikle sizeof(array[0])
kullan�r�z. Bu nedenle, uzunluk = sizeof(array) / sizeof(array[0]). Bunu bazen sizeof(array) / sizeof(*array) olarak yaz�ld���n� da g�rebilirsiniz, 
bu ayn� �eyi yapar. Ancak, size bir sonraki derste g�sterece�imiz gibi, bu form�l (bir decayed array ge�irildi�inde) olduk�a kolay bir �ekilde 
ba�ar�s�z olabilir, program� beklenmedik bir �ekilde bozabilir. C++17'nin std::size() ve yukar�da g�sterilen length() fonksiyon �ablonu her iki
durumda da derleme hatalar�na neden olur, bu y�zden g�venli bir �ekilde kullan�labilirler.

17.8 � C-stil array decay
-------------------------
C-stil dizisi ge�irme zorlu�u
-----------------------------
C dilinin tasar�mc�lar� bir sorunla kar��la�t�. A�a��daki basit program� d���n�n:

                #include <iostream>

                void print(int val)
                {
                    std::cout << val;
                }

                int main()
                {
                    int x { 5 };
                    print(x);

                    return 0;
                }

print(x) �a�r�ld���nda, x arg�man�n�n de�eri (5) val parametresine kopyalan�r. Fonksiyonun g�vdesi i�inde, val'in de�eri (5) konsola yazd�r�l�r.
X'in kopyalanmas� ucuz oldu�u i�in burada bir sorun yok.

�imdi, tek bir int yerine 1000 elemanl� bir C-stil int dizisi kullanan benzer bir program� d���n�n:

                #include <iostream>

                void printElementZero(int arr[1000])
                {
                    std::cout << arr[0]; // ilk eleman�n de�erini yazd�r
                }

                int main()
                {
                    int x[1000] { 5 };   // 1000 elemanl� bir dizi tan�mla, x[0] 5'e ba�lat�l�r
                    printElementZero(x);

                    return 0;
                }
Bu program da derlenir ve beklenen de�eri (5) konsola yazd�r�r. Bu �rnekteki kod, �nceki �rnekteki koda benzerken, mekanik olarak bekledi�inizden 
biraz farkl� �al���r (bunu a�a��da a��klayaca��z). Ve bu, C tasar�mc�lar�n�n iki b�y�k zorlu�u ��zmek i�in buldu�u ��z�mden kaynaklanmaktad�r.

�lk olarak, her fonksiyon �a�r�ld���nda 1000 elemanl� bir diziyi kopyalamak pahal�d�r (�zellikle elemanlar pahal� bir kopya t�r�yse), 
bu y�zden bunu �nlemek istiyoruz. Ama nas�l? C'nin referanslar� yok, bu y�zden fonksiyon arg�manlar�n�n bir kopyas�n� yapmaktan ka��nmak i�in
referans ile ge�me se�ene�i yok.

�kinci olarak, farkl� uzunluklarda dizi arg�manlar�n� kabul edebilecek tek bir fonksiyon yazabilmek istiyoruz. �deal olarak, yukar�daki �rnekteki 
printElementZero() fonksiyonumuz, herhangi bir uzunluktaki dizi arg�manlar�yla �a�r�labilir olmal�d�r (��nk� eleman 0'�n var oldu�u garantilidir).
Her olas� dizi uzunlu�u i�in farkl� bir fonksiyon yazmak zorunda kalmak istemiyoruz. Ama nas�l? C'nin "herhangi bir uzunlukta" dizileri belirtmek 
i�in bir s�zdizimi yok, �ablonlar� desteklemiyor, ne de bir uzunluktaki diziler ba�ka bir uzunlu�a d�n��t�r�lebiliyor (muhtemelen bunun pahal� bir
kopya yapmay� gerektirece�i i�in).

C dilinin tasar�mc�lar�, her iki sorunu da ��zen zekice bir ��z�m buldular (uyumluluk nedenleriyle C++ taraf�ndan miras al�nd�):

                #include <iostream>

                void printElementZero(int arr[1000]) // bir kopya yapmaz
                {
                    std::cout << arr[0]; // ilk eleman�n de�erini yazd�r
                }

                int main()
                {
                    int x[7] { 5 };      // 7 elemanl� bir dizi tan�mla
                    printElementZero(x); // bir �ekilde �al���yor!

                    return 0;
                }
Bir �ekilde, yukar�daki �rnek, herhangi bir kopya yap�lmadan, 1000 elemanl� bir dizi bekleyen bir fonksiyona 7 elemanl� bir dizi ge�irir. 
Bu dersimizde, bunun nas�l �al��t���n� inceleyece�iz. Ayr�ca, C tasar�mc�lar�n�n se�ti�i ��z�m�n neden tehlikeli oldu�una ve modern 
C++ i�in uygun olmad���na bakaca��z.

Ama �nce, iki alt konuyu kapsamam�z gerekiyor.

Diziden ��aret�iye D�n���mler (Dizi ��r�mesi)
---------------------------------------------
�o�u durumda, bir C tarz� dizi bir ifadede kullan�ld���nda, dizi, ilk eleman�n (indeks 0 olan) adresiyle ba�lat�lan eleman t�r�ne bir i�aret�iye
otomatik olarak d�n��t�r�l�r. Bu, halk aras�nda dizi bozunmas� (veya k�saca bozunma ( decay )) olarak adland�r�l�r.

Bunu a�a��daki programda g�rebilirsiniz:

                #include <iomanip> // std::boolalpha i�in
                #include <iostream>

                int main()
                {
                    int arr[5]{ 9, 7, 5, 3, 1 }; // dizimizin elemanlar� int t�r�nde

                    // �ncelikle, arr'�n bir int* i�aret�isine ��r�d���n� kan�tlayal�m

                    auto ptr{ arr }; // de�erlendirme arr'�n ��r�mesine neden olur, t�r ��kar�m� t�r�n int* oldu�unu ��karmal�
                    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // ptr'nin t�r� int* ise true yazd�r�r

                    // �imdi i�aret�inin dizinin ilk eleman�n�n adresini tuttu�unu kan�tlayal�m

                    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�:

                true
                true

Bir dizi bozundu�unda i�aret�i hakk�nda �zel bir �ey yoktur. Bu, ilk eleman�n adresini tutan normal bir i�aret�idir.
Benzer �ekilde, bir const dizisi (�r. const int arr[5]) bir const'a i�aret eden i�aret�iye (const int*) bozunur.

�pucu -> C++'da, bir C tarz� dizinin bozunmad��� birka� yayg�n durum vard�r:

*- sizeof() veya typeid() arg�man� olarak kullan�ld���nda.
*- Dizinin adresini operator& kullanarak al�rken.
*- Bir s�n�f t�r�n�n �yesi olarak ge�irildi�inde.
*- Referans olarak ge�irildi�inde.

C tarz� dizilerin �o�u durumda bir i�aret�iye bozunmas� nedeniyle, dizilerin i�aret�iler oldu�una inanmak yayg�n bir yan�lg�d�r. Bu do�ru de�il.
Bir dizi nesnesi bir eleman dizisidir, oysa bir i�aret�i nesnesi sadece bir adresi tutar.

Bir dizi ve bozunmu� bir dizi aras�ndaki t�r bilgisi farkl�d�r. Yukar�daki �rnekte, arr dizisinin t�r� int[5]'tir, bozunmu� dizinin t�r� ise
int*'dir. �zellikle, dizi t�r� int[5] uzunluk bilgisi i�erirken, bozunmu� dizi i�aret�i t�r� int* bunu i�ermez.

Ana Fikir

Bir bozunmu� dizi i�aret�isi, i�aret etti�i dizinin ne kadar uzun oldu�unu bilmez. "Bozunma" terimi, bu uzunluk t�r� bilgisinin kayb�n� g�sterir.
Bir C Tarz� Diziyi Alt dizinlemek Asl�nda bozunmu� ��aret�iye operator[] Uygular

Bir C tarz� dizi de�erlendirildi�inde bir i�aret�iye bozunur, bu y�zden bir C tarz� dizi altdizinlendi�inde, altdizin asl�nda bozunmu� dizi i�aret�isi �zerinde i�lem yapar:

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    std::cout << arr[2]; // bozunmu� diziyi altdizinleme ile eleman 2'yi al�r, 5 yazd�r�r

    return 0;
}
```
Ayr�ca operator[]'yi do�rudan bir i�aret�i �zerinde de kullanabiliriz. E�er bu i�aret�i ilk eleman�n adresini tutuyorsa, sonu� ayn� olacakt�r:

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr };  // arr bir i�aret�iye bozunur
    std::cout << ptr[2];    // ptr'yi altdizinleme ile eleman 2'yi al�r, 5 yazd�r�r

    return 0;
}
```
Birazdan bunun nerede kullan��l� oldu�unu g�rece�iz ve asl�nda bunun nas�l �al��t���na (ve i�aret�inin ilk eleman�n adresinden ba�ka bir �eyi tuttu�unda ne oldu�una) bir sonraki derste 17.9 -- ��aret�i aritmeti�i ve altdizinleme konusunda daha derinlemesine bakaca��z.

Dizi ��r�mesi, C-style dizi ge�irme sorunumuzu ��zer

Dizi ��r�mesi, dersin ba��nda kar��la�t���m�z her iki zorlu�u da ��zer.

Bir C-style diziyi bir arg�man olarak ge�irirken, dizi bir i�aret�iye bozunur veya bozulur ve dizinin ilk ��esinin adresini tutan i�aret�i,
fonksiyona ge�irilen �eydir. Yani, C-style diziyi de�er olarak ge�irdi�imiz gibi g�r�nse de, asl�nda onu adres olarak ge�iriyoruz! Bu, C-style dizi
arg�man�n�n bir kopyas�n�n yap�lmas�n�n nas�l �nlendi�idir.

Anahtar nokta �udur ki; C-style diziler, de�er olarak ge�irildikleri gibi g�r�nseler bile, adres olarak ge�irilirler.

�imdi, ayn� ��e t�r�ne ama farkl� uzunluklara sahip iki farkl� dizi d���n�n (�r. int[5] ve int[7]). Bunlar, birbirleriyle uyumsuz olan ayr�
t�rlerdir. Ancak, her ikisi de ayn� i�aret�i t�r�ne (�r. int*) bozunur. Onlar�n bozunmu� s�r�mleri birbirinin yerine ge�ebilir! T�rden uzunluk 
bilgisini atmak, t�r uyumsuzlu�u olmadan farkl� uzunluklarda dizileri ge�irmemize olanak sa�lar.

Anahtar nokta, Ayn� ��e t�r�ne ama farkl� uzunluklara sahip iki C-style dizi, ayn� i�aret�i t�r�ne bozunur.

A�a��daki �rnekte, iki �eyi g�sterece�iz:

*- Farkl� uzunluklarda dizileri tek bir fonksiyona ge�irebiliriz (��nk� her ikisi de ayn� i�aret�i t�r�ne bozunur).
*- Diziyi alan fonksiyon parametremizin, dizinin ��e t�r�n�n bir (const) i�aret�isi olabilir.

                #include <iostream>

                void printElementZero(const int* arr) // const adresi ile ge�ir
                {
                    std::cout << arr[0];
                }

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };
                    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

                    printElementZero(prime);   // prime bir const int* i�aret�isine bozunur
                    printElementZero(squares); // squares bir const int* i�aret�isine bozunur

                    return 0;
                }

                Bu �rnek gayet iyi �al���r ve �unu yazd�r�r:

                2
                1
main() i�inde, printElementZero(prime) �a�r�s�n� yapt���m�zda, prime dizisi const int[5] t�r�nden bir diziden, prime'�n ilk ��esinin adresini tutan
const int* t�r�nde bir i�aret�iye bozunur. Benzer �ekilde, printElementZero(squares) �a�r�s�n� yapt���m�zda, squares dizisi const int[8] t�r�nde
bir diziden, squares'�n ilk ��esinin adresini tutan const int* t�r�nde bir i�aret�iye bozunur. Bu const int* t�r�ndeki i�aret�iler, asl�nda 
fonksiyona bir arg�man olarak ge�irilen �eylerdir.

��aret�ileri const int* t�r�nde ge�irdi�imizden, printElementZero() fonksiyonumuzun ayn� i�aret�i t�r�nde bir parametreye sahip olmas� gerekiyor.
Bu fonksiyon i�inde, se�ili dizi ��esine eri�mek i�in i�aret�iyi alt dizinliyoruz.Bir C-style dizi adres olarak ge�irildi�inden, fonksiyon do�rudan
ge�irilen diziye (bir kopya de�il) eri�ir ve ��elerini de�i�tirebilir. Bu nedenle, fonksiyonunuzun dizi ��elerini de�i�tirmeyi ama�lamamas�
durumunda, fonksiyon parametrenizin const olmas�n� sa�lamak iyi bir fikirdir.

C-style dizi fonksiyon parametre s�zdizimi
------------------------------------------
Fonksiyon parametresini int* arr olarak bildirmenin bir sorunu, arr'�n tek bir tam say�ya de�il, de�erlerin bir dizisine i�aret eden bir i�aret�i 
olmas� gerekti�inin a��k olmamas�d�r. Bu nedenle, bir C-style dizi ge�irirken, int arr[] alternatif bildirim formunu kullanmak tercih edilir:

                #include <iostream>

                void printElementZero(const int arr[]) // const int* ile ayn� �ekilde ele al�n�r
                {
                    std::cout << arr[0];
                }

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };
                    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

                    printElementZero(prime);  // prime bir i�aret�iye bozunur
                    printElementZero(squares); // squares bir i�aret�iye bozunur

                    return 0;
                }

Bu program, �ncekiyle ayn� �ekilde davran�r, ��nk� derleyici, fonksiyon parametresi const int arr[]'yi const int* ile ayn� �ekilde yorumlar.
Ancak, bu, arr'�n tek bir de�ere de�il, bozunmu� bir C-style dizi olmas� beklenen bir i�aret�i oldu�unu �a��r�c�ya iletmek gibi bir avantaja
sahiptir. K��eli parantezler aras�nda uzunluk bilgisine gerek yoktur (zaten kullan�lmad��� i�in). E�er bir uzunluk sa�lan�rsa, bu g�z ard� edilir.

*** BEST -> Bir C tarz� dizi t�r� bekleyen bir fonksiyon parametresi, dizi s�zdizimini (�r. int arr[]) kullanmal�d�r, pointer s�zdizimi yerine 
            (�r. int *arr).

Bu s�zdizimini kullanman�n dezavantaj�, arr'�n bozundu�unun daha az belirgin olmas�d�r (pointer s�zdizimiyle olduk�a a��kt�r), bu y�zden bozunmu�
bir diziyle beklenildi�i gibi �al��mayan herhangi bir �ey yapmamaya ekstra �zen g�stermeniz gerekecektir bunlardan baz�lar�n� birazdan ele alaca��z

Dizi Bozunmas�n�n Sorunlar�
---------------------------
Dizi ��r�mesi, farkl� uzunluklarda C tarz� dizilerin pahal� kopyalar yapmadan bir fonksiyona ge�irilebilmesini sa�lamak i�in ak�ll�ca bir ��z�md�,
ancak dizi uzunlu�u bilgisinin kaybolmas�, birka� t�r hatan�n yap�lmas�n� kolayla�t�r�r.

�ncelikle, sizeof() diziler ve bozunmu� diziler i�in farkl� de�erler d�nd�recektir:

                #include <iostream>

                void printArraySize(int arr[])
                {
                    std::cout << sizeof(arr) << '\n'; // 4 yazd�r�r (32 bit adresler varsay�l�rsa)
                }

                int main()
                {
                    int arr[]{ 3, 2, 1 };

                    std::cout << sizeof(arr) << '\n'; // 12 yazd�r�r (4 baytl�k int varsay�l�rsa)

                    printSize(arr);

                    return 0;
                }

Bu, bir C tarz� dizide sizeof() kullanman�n potansiyel olarak tehlikeli oldu�u anlam�na gelir, ��nk� bunu yaln�zca ger�ek dizi nesnesine 
eri�ebildi�inizde, bozunmu� dizi veya pointer olmadan kullanman�z gerekti�inden emin olmal�s�n�z.

�nceki derste (17.7 -- C tarz� dizilere giri�), sizeof(arr)/sizeof(*arr)'�n tarihsel olarak bir C tarz� dizinin boyutunu almak i�in bir hile olarak
kullan�ld���n� belirttik. Bu hile tehlikelidir ��nk� e�er arr bozunmu�sa, sizeof(arr) bir pointer'�n boyutunu d�nd�recektir, bu da sonu�ta yanl�� 
dizi uzunlu�unu �retir, muhtemelen program�n yanl�� �al��mas�na neden olur.

Neyse ki, C++17'nin daha iyi yerine ge�eni std::size() (ve C++20'nin std::ssize()) bir pointer de�eri ge�irildi�inde derlemeyi ba�ar�s�z olacakt�r:

                #include <iostream>

                int printArrayLength(int arr[])
                {
                    std::cout << std::size(arr) << '\n'; // derleme hatas�: std::size() bir pointer �zerinde �al��maz
                }

                int main()
                {
                    int arr[]{ 3, 2, 1 };

                    std::cout << std::size(arr) << '\n'; // 3 yazd�r�r

                    printArrayLength(arr);

                    return 0;
                }

�kinci olarak, ve belki de en �nemlisi, dizi bozunmas�, yeniden d�zenlemeyi (uzun fonksiyonlar� daha k�sa, daha mod�ler fonksiyonlara ay�rmay�)
zorla�t�rabilir. Bozunmayan bir diziyle beklenildi�i gibi �al��an kod, ayn� kod bozunmu� bir dizi kullan�ld���nda derlenmeyebilir 
(veya daha k�t�s�, sessizce yanl�� �al��abilir).

���nc�s�, uzunluk bilgisine sahip olmamak birka� programlama zorlu�u yarat�r. Uzunluk bilgisi olmadan, dizinin uzunlu�unu mant�kl� bir �ekilde 
kontrol etmek farkl�d�r. Kullan�c�lar kolayca beklenenden daha k�sa dizileri (veya hatta tek bir de�ere pointerlar�) ge�irebilir, bu da onlar 
ge�ersiz bir indeksle abone oldu�unda tan�ms�z davran��a neden olur.

                #include <iostream>

                void printElement2(int arr[])
                {
                    // arr'�n en az �� elemana sahip oldu�unu nas�l sa�lar�z?
                    std::cout << arr[2] << '\n';
                }

                int main()
                {
                    int a[]{ 3, 2, 1 };
                    printElement2(a);  // tamam

                    int b[]{ 7, 6 };
                    printElement2(b);  // derlenir ama tan�ms�z davran�� �retir

                    int c{ 9 };
                    printElement2(&c); // derlenir ama tan�ms�z davran�� �retir

                    return 0;
                }

Dizi uzunlu�una sahip olmamak ayr�ca diziyi dola��rken zorluklar yarat�r - sona ne zaman ula�t���m�z� nas�l bilebiliriz? Bu sorunlara ��z�mler var,
ancak bu ��z�mler bir programa hem karma��kl�k hem de k�r�lganl�k ekler.

Dizi uzunluk sorunlar�n� ��zme
------------------------------
Tarihsel olarak, programc�lar dizi uzunlu�u bilgisinin eksikli�ini iki y�ntemden biriyle ��zm��t�r.

�lk olarak, hem diziyi hem de dizi uzunlu�unu ayr� arg�manlar olarak iletebiliriz:

                #include <cassert>
                #include <iostream>

                void printElement2(const int arr[], int length)
                {
                    assert(length > 2 && "printElement2: Dizi �ok k�sa"); // length �zerinde static_assert kullanamay�z

                    std::cout << arr[2] << '\n';
                }

                int main()
                {
                    constexpr int a[]{ 3, 2, 1 };
                    printElement2(a, static_cast<int>(std::size(a)));  // tamam

                    constexpr int b[]{ 7, 6 };
                    printElement2(b, static_cast<int>(std::size(b)));  // assert tetikleyecek

                    return 0;
                }

Ancak, bu hala bir dizi sorunlar� i�erir:

*- �a��ran�n dizinin ve dizi uzunlu�unun e�le�ti�inden emin olmas� gerekiyor -- e�er length i�in yanl�� bir de�er ge�irilirse, fonksiyon hala hatal�
   �al��acakt�r.
*- E�er std::size() kullan�yorsan�z veya uzunlu�u std::size_t olarak d�nd�ren bir fonksiyon kullan�yorsan�z, potansiyel i�aret d�n���m sorunlar�
   vard�r.
*- Runtime assertler yaln�zca runtime'da kar��la��ld���nda tetiklenir. E�er test yolumuz fonksiyona yap�lan t�m �a�r�lar� kapsam�yorsa, m��teriye
   bir �eyi test etmedi�imizde assert ��karacak bir program g�nderme riskimiz vard�r. Modern C++'da, constexpr dizilerin dizi uzunlu�unu derleme
   zaman�nda do�rulamak i�in static_assert kullanmak isteriz, ancak bunu yapman�n kolay bir yolu yoktur (��nk� fonksiyon parametreleri constexpr 
   olamaz, hatta constexpr veya consteval fonksiyonlarda bile!).

*- Bu y�ntem yaln�zca a��k bir fonksiyon �a�r�s� yap�yorsak �al���r. E�er fonksiyon �a�r�s� implicit ise (�rne�in, diziyi bir operand olarak
   kullanarak bir operat�r� �a��r�yorsak), uzunlu�u ge�irme f�rsat� yoktur.

�kinci olarak, e�er semantik olarak ge�erli olmayan bir eleman de�eri varsa (�rne�in, -1 olan bir test skoru), bunun yerine bu de�ere sahip bir 
eleman� kullanarak dizinin sonunu i�aretleyebiliriz. Bu �ekilde, dizinin uzunlu�u, dizinin ba�lang�c� ve bu sonland�r�c� eleman aras�nda ka� eleman
oldu�unu sayarak hesaplanabilir. Dizi ayr�ca, ba�lang��tan ba�lay�p sonland�r�c� elemana ula�ana kadar yineleyerek de ge�ilebilir.
Bu y�ntemin g�zel yan�, implicit fonksiyon �a�r�lar�yla bile �al��mas�d�r.

Anahtar nokta �udur ki; C-stil dizeleri (ki bunlar C-stil dizilerdir) dizenin sonunu i�aretlemek i�in bir null-sonland�r�c� kullan�r, 
b�ylece onlar decay olmu� olsalar bile ge�ilebilirler.

Ama bu y�ntemin de bir dizi sorunu vard�r:

*- E�er sonland�r�c� eleman mevcut de�ilse, ge�i� dizinin sonundan do�ruca y�r�yecek, tan�ms�z davran��a neden olacakt�r.
*- Diziyi ge�en fonksiyonlar�n sonland�r�c� eleman i�in �zel bir i�lem yapmas� gereklidir (�rne�in, bir C-stil dize yazd�rma fonksiyonunun
   sonland�r�c� eleman� yazd�rmamas� gerekti�ini bilmelidir).
*- Ger�ek dizi uzunlu�u ve semantik olarak ge�erli elemanlar�n say�s� aras�nda bir uyumsuzluk vard�r. E�er yanl�� uzunluk kullan�l�rsa, semantik
   olarak ge�ersiz sonland�r�c� eleman "i�lenmi�" olabilir.

Bu yakla��m yaln�zca semantik olarak ge�ersiz bir de�er varsa �al���r, ki bu genellikle durum de�ildir. �o�u durumda C tarz� dizilerden
ka��n�lmal�d�r

Standart d��� ge�i� semanti�i (adrese g�re ge�i�, de�ere g�re ge�i� yerine kullan�l�r) ve bozulmu� dizilerin uzunluk bilgilerini kaybetme riskleri
nedeniyle, C tarz� diziler genellikle tercih edilmez hale gelmi�tir. M�mk�n oldu�unca bunlardan ka��nman�z� �neririz.

*** BEST -> Pratik oldu�unda C tarz� dizilerden ka��n�n.
--------------------------------------------------------
*- Salt okunur dizeler i�in (string literal sembolik sabitleri ve string parametreleri) std::string_view'� tercih edin.
*- De�i�tirilebilir dizeler i�in std::string'i tercih edin.
*- Global olmayan constexpr diziler i�in std::array'i tercih edin.
*- constexpr olmayan diziler i�in std::vector'� tercih edin.
*- Global constexpr diziler i�in C tarz� dizileri kullanmak tamam. Bunu birazdan tart��aca��z.

Bir parantez a�al�m...
----------------------
C++'da, diziler referans olarak ge�irilebilir, bu durumda dizi arg�man� bir fonksiyona ge�irildi�inde bozulmaz (ancak diziye olan referans
de�erlendirildi�inde hala bozulur). Ancak, bunu tutarl� bir �ekilde uygulamay� unutmak kolayd�r ve ka��r�lan bir referans, bozulmu� arg�manlara yol
a�ar. Ayr�ca, dizi referans parametrelerinin sabit bir uzunlu�u olmal�d�r, yani fonksiyon yaln�zca belirli bir uzunluktaki dizileri i�leyebilir. 
Farkl� uzunluktaki dizileri i�leyebilen bir fonksiyon istiyorsak, o zaman fonksiyon �ablonlar�n� da kullanmal�y�z. Ancak, C tarz� dizileri
"d�zeltmek" i�in bu iki �eyi yapacaksan�z, o zaman zaten std::array'i kullanabilirsiniz!

Peki modern C++'da C tarz� diziler ne zaman kullan�l�r?
-------------------------------------------------------
Modern C++'da, C tarz� diziler genellikle iki durumda kullan�l�r:

1- constexpr global (veya constexpr statik local) program verisini saklamak i�in. Bu t�r dizilere program�n her yerinden do�rudan eri�ilebildi�i i�in,
diziyi ge�irmemize gerek yoktur, bu da bozulma ile ilgili sorunlar� �nler. C tarz� dizileri tan�mlamak i�in s�zdizimi, std::array'den biraz daha az
garip olabilir. Daha da �nemlisi, bu t�r dizilerin indekslenmesi, standart k�t�phane konteyner s�n�flar�n�n yapt��� gibi i�aret d�n���m sorunlar�na
sahip de�ildir.

2- constexpr olmayan C tarz� string arg�manlar�n� do�rudan i�lemek isteyen fonksiyonlara veya s�n�flara parametre olarak. Bunun i�in iki olas� 
neden vard�r: �lk olarak, constexpr olmayan bir C tarz� string'i bir std::string_view'a d�n��t�rmek, C tarz� string'in uzunlu�unu belirlemek i�in 
string'i ge�mek gerektirir. E�er fonksiyon, performans� kritik bir kod b�l�m�nde ve uzunluk gerekmiyorsa (�rne�in, ��nk� fonksiyon zaten string'i 
ge�ecekse) o zaman d�n���mden ka��nmak yararl� olabilir. �kincisi, e�er fonksiyon (veya s�n�f) C tarz� string'leri bekleyen di�er fonksiyonlar� 
�a��r�yorsa, bir std::string_view'a d�n��t�rmek i�in sadece geri d�n��t�rmek suboptimal olabilir (std::string_view istemek i�in ba�ka nedenleriniz
olmad�k�a).

17.9 � Pointer aritmeti�i ve subscripting ( Alt dizinleme )
-----------------------------------------------------------
Ders 16.1 -- Konteynerlara ve dizilere giri�te, dizilerin ard���k olarak bellekte sakland���n� belirtmi�tik. Bu derste, dizilerin indeksleme
matemati�inin nas�l �al��t���na daha derinlemesine bakaca��z.

Gelecekteki derslerde indeksleme matemati�ini kullanmayaca��z, ancak bu dersin konular�, aral�k tabanl� for d�ng�lerinin asl�nda nas�l �al��t���na
dair size i�g�r� sa�layacak ve daha sonra yineleyicileri ele ald���m�zda i�e yarayacak.

��aret�i Aritmeti�i Nedir?
--------------------------
��aret�i aritmeti�i, belirli tam say� aritmetik operat�rlerini (toplama, ��karma, art�rma veya azaltma) bir i�aret�iye uygulayarak yeni 
bir bellek adresi �retmemize olanak sa�layan bir �zelliktir.

Baz� ptr i�aret�isi verildi�inde, ptr + 1, bellekteki bir sonraki nesnenin adresini d�nd�r�r (i�aret edilen tipe dayan�r). Yani ptr bir int* ise 
ve bir int 4 byte ise, ptr + 1, ptr'den 4 byte sonraki bellek adresini d�nd�recek ve ptr + 2, ptr'den 8 byte sonraki bellek adresini d�nd�recektir.

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'l�k int'leri varsayal�m

                    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�:

                00AFFD80 00AFFD84 00AFFD88

Her bellek adresinin bir �ncekinden 4 byte daha b�y�k oldu�una dikkat edin.
Daha az yayg�n olmas�na ra�men, i�aret�i aritmeti�i ��karma ile de �al���r. Baz� ptr i�aret�isi verildi�inde, ptr - 1, bellekteki bir �nceki 
nesnenin adresini d�nd�r�r (i�aret edilen tipe dayan�r).

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'l�k int'leri varsayal�m

                    std::cout << ptr << ' ' << (ptr - 1) << ' ' << (ptr - 2) << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�:

                00AFFD80 00AFFD7C 00AFFD78

Bu durumda, her bellek adresi bir �ncekinden 4 byte daha azd�r.

Ana Fikir, ��aret�i aritmeti�i, bir sonraki/�nceki adresi de�il, bir sonraki/�nceki nesnenin adresini (i�aret edilen tipe dayanarak) d�nd�r�r.
Art�rma (++) ve azaltma (--) operat�rlerini bir i�aret�iye uygulamak, s�ras�yla i�aret�i toplama ve i�aret�i ��karmayla ayn� �eyi yapar,
ancak i�aret�inin tuttu�u adresi ger�ekten de�i�tirir.

Baz� int de�eri x verildi�inde, ++x, x = x + 1'in k�sa yoludur. Benzer �ekilde, baz� ptr i�aret�isi verildi�inde, ++ptr, ptr = ptr + 1'in k�sa 
yoludur, bu i�aret�i aritmeti�i yapar ve sonucu ptr'ye atar.

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'l�k int'leri varsayal�m

                    std::cout << ptr << '\n';

                    ++ptr; // ptr = ptr + 1
                    std::cout << ptr << '\n';

                    --ptr; // ptr = ptr - 1
                    std::cout << ptr << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�:

                00AFFD80 00AFFD84 00AFFD80

Altdizinleme ��aret�i Aritmeti�i Arac�l���yla Uygulan�r
-------------------------------------------------------
�nceki derste (17.8 -- C tarz� dizi ��r�mesi), operator[]'nin bir i�aret�iye uygulanabilece�ini belirttik:

                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 7, 5, 3, 1 };

                    const int* ptr{ arr }; // eleman 0'�n adresini tutan normal bir i�aret�i
                    std::cout << ptr[2];   // ptr'yi altdizinleme ile eleman 2'yi al�r, 5 yazd�r�r

                    return 0;
                }

Burada neler oldu�una daha derinlemesine bakal�m. Ortaya ��kt��� gibi, ptr[n] altdizin i�lemi, *((ptr) + (n)) ifadesine e�de�er olan daha a��k bir
s�zdizimine e�ittir. Bu, sadece i�aret�i aritmeti�idir, do�ru s�rayla de�erlendirmeyi sa�lamak i�in baz� ek parantezler ve adresindeki nesneyi
almak i�in bir implicit dereference vard�r.

�ncelikle, ptr'yi arr ile ba�lat�r�z. arr bir ba�lat�c� olarak kullan�ld���nda, eleman 0'�n adresini tutan bir i�aret�iye bozunur.
Yani ptr �imdi eleman 0'�n adresini tutar. Sonraki ad�mda, ptr[2]'yi yazd�r�r�z. ptr[2], *((ptr) + (2))'ye e�de�erdir, bu da *(ptr + 2)'ye 
e�de�erdir. ptr + 2, ptr'den iki nesne sonras�ndaki nesnenin adresini d�nd�r�r, bu da indeks 2 olan elemand�r. O adresin nesnesi daha sonra �a��ran
ki�iye d�nd�r�l�r.

Bir ba�ka �rne�e bakal�m:

                #include <iostream>

                int main()
                {
                    const int arr[] { 3, 2, 1 };

                    // �ncelikle, dizi ��elerimizin adreslerini ve de�erlerini almak i�in alt dizinlemeyi kullanal�m
                    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
                    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

                    // �imdi ayn�s�n� i�aret�i aritmeti�i kullanarak yapal�m
                    std::cout << arr<< ' ' << (arr+ 1) << ' ' << (arr+ 2) << '\n';
                    std::cout << *arr<< ' ' << *(arr+ 1) << ' ' << *(arr+ 2) << '\n';

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�r�ld�:

                00AFFD80 00AFFD84 00AFFD88
                3 2 1
                00AFFD80 00AFFD84 00AFFD88
                3 2 1
ptr'nin 00AFFD80 adresini tuttu�unu, (ptr + 1)'in 4 byte sonraki bir adresi d�nd�rd���n� ve (ptr + 2)'nin 8 byte sonraki bir adresi d�nd�rd���n�
not edeceksiniz. Bu adresleri dereferans ederek bu adreslerdeki ��eleri alabiliriz.

Dizi ��eleri her zaman bellekte ard���k oldu�u i�in, e�er ptr bir dizinin 0. ��esine i�aret eden bir i�aret�iyse, *(ptr + n) dizinin n. ��esini
d�nd�recektir. Bu, dizilerin 0 tabanl� yerine 1 tabanl� olmas�n�n temel nedenidir. Matemati�i daha verimli hale getirir (��nk� derleyicinin her alt
dizinleme i�lemi s�ras�nda 1 ��karmas�na gerek yoktur)!

Bir parantez a�ma...
--------------------
Bir i�aret�iyi alt dizinleme s�ras�nda derleyicinin ptr[n]'i *((ptr) + (n))'a d�n��t�rd��� i�in, bu, bir i�aret�iyi n[ptr] olarak da alt
dizinleyebilece�imiz anlam�na gelir! Derleyici bunu *((n) + (ptr))'a d�n��t�r�r, bu da *((ptr) + (n)) ile davran��sal olarak ayn�d�r.
Ancak bunu ger�ekten yapmay�n, ��nk� bu kafa kar��t�r�c�d�r.

��aret�i aritmeti�i ve alt dizinleme g�receli adreslerdir
---------------------------------------------------------
Dizi alt dizinlemesi hakk�nda ilk ��rendi�inizde, indeksin dizideki sabit bir ��eyi temsil etti�ini varsaymak do�ald�r: �ndeks 0 her zaman ilk
��edir, indeks 1 her zaman ikinci ��edir, vb... Bu bir yan�lsamad�r. Dizi indeksleri asl�nda g�receli pozisyonlard�r. �ndeksler sadece sabit
g�r�n�r ��nk� neredeyse her zaman dizinin ba��ndan (0. ��e) indeksleriz!

Bir i�aret�i ptr verildi�inde, hem *(ptr + 1) hem de ptr[1] bellekteki sonraki nesneyi d�nd�r�r (i�aret edilen tipe dayal�). Sonraki,
mutlak bir terim de�ildir, g�receli bir terimdir. Bu nedenle, e�er ptr 0. ��eye i�aret ediyorsa, o zaman hem *(ptr + 1) hem de ptr[1] 1. ��eyi
d�nd�recektir. Ama e�er ptr 3. ��eye i�aret ediyorsa, o zaman hem *(ptr + 1) hem de ptr[1] 4. ��eyi d�nd�recektir!

A�a��daki �rnek bunu g�sterir:

                #include <array>
                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };
                    const int *ptr { arr }; // arr 0. ��eye i�aret eden bir i�aret�iye bozunur

                    // 0. ��eye i�aret etti�imizi kan�tlayal�m
                    std::cout << *ptr << ptr[0] << '\n'; // 99 yazd�r�r
                    // ptr[1]'in 1. ��e oldu�unu kan�tlayal�m
                    std::cout << *(ptr+1) << ptr[1] << '\n'; // 88 yazd�r�r

                    // �imdi ptr'yi 3. ��eye i�aret etmek �zere ayarlayal�m
                    ptr = &arr[3];

                    // 3. ��eye i�aret etti�imizi kan�tlayal�m
                    std::cout << *ptr << ptr[0] << '\n'; // 66 yazd�r�r
                    // ptr[1]'in 4. ��e oldu�unu kan�tlayal�m!
                    std::cout << *(ptr+1) << ptr[1] << '\n'; // 55 yazd�r�r

                    return 0;
                }
Ancak, ptr[1]'in her zaman 1. ��e oldu�unu varsayamazsak program�m�z�n �ok daha kar���k oldu�unu da not edeceksiniz. Bu nedenle, sadece dizinin 
ba��ndan (0. ��e) indeksleme yaparken alt dizinlemeyi kullanman�z� �neririz. Sadece g�receli konumland�rma yaparken i�aret�i aritmeti�ini kullan�n.

*** BEST -> Dizinin ba��ndan (0. ��e) indeksleme yaparken alt dizinlemeyi tercih edin, b�ylece dizi indeksleri ��e ile ayn� hizada olur.
            Belirli bir ��eden g�receli konumland�rma yaparken i�aret�i aritmeti�ini tercih edin.

Negatif �ndisler
----------------
Son derste, (standart k�t�phane konteyner s�n�flar�n�n aksine) bir C tarz� dizinin indeksinin ya bir unsigned integer ya da bir signed integer
olabilece�ini belirttik. Bu, sadece kolayl�k i�in yap�lmad� - asl�nda bir C tarz� diziyi negatif bir alt dizinle indekslemek m�mk�n. Komik geliyor,
ama mant�kl�.

*(ptr+1)'in bellekteki sonraki nesneyi d�nd�rd���n� yeni ��rendik. Ve ptr[1] bunu yapmak i�in sadece uygun bir s�zdizimi.

Bu dersin ba��nda, *(ptr-1)'in bellekteki �nceki nesneyi d�nd�rd���n� belirttik. Alt dizinin e�de�erini tahmin etmek ister misiniz? Evet, ptr[-1].

                #include <array>
                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };

                    // ptr'yi eleman 3'e i�aret edecek �ekilde ayarla
                    const int* ptr { &arr[3] };

                    // ptr'nin eleman 3'e i�aret etti�ini kan�tla
                    std::cout << *ptr << ptr[0] << '\n'; // 66 yazd�r�r
                    // ptr[-1]'in eleman 2 oldu�unu kan�tla!
                    std::cout << *(ptr-1) << ptr[-1] << '\n'; // 77 yazd�r�r

                    return 0;
                }

Pointer Aritmeti�i Bir Diziyi Gezmek ��in Kullan�labilir
--------------------------------------------------------
Pointer aritmeti�inin en yayg�n kullan�mlar�ndan biri, a��k�a indeksleme yapmadan bir C tarz� diziyi yinelemektir. A�a��daki �rnek, bunun nas�l
yap�ld���n� g�sterir:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    const int* begin{ arr };                // begin ba�lang�� eleman�na i�aret eder
                    const int* end{ arr + std::size(arr) }; // end bir-sonraki-son elemana i�aret eder

                    for (; begin != end; ++begin)           // begin'den ba�layarak (ama hari�) end'e kadar yinele
                    {
                        std::cout << *begin << ' ';     // d�ng� de�i�kenimizi dereferans yaparak mevcut eleman� al
                    }

                    return 0;
                }

Yukar�daki �rnekte, gezinmeye begin taraf�ndan i�aret edilen elemanda (bu durumda dizi'nin 0. eleman�) ba�l�yoruz. Hen�z begin != end oldu�undan,
d�ng� g�vdesi �al���r. D�ng� i�inde, mevcut eleman� *begin ile eri�iriz, bu sadece bir pointer dereferans�d�r. D�ng� g�vdesinden sonra, ++begin 
yapar�z, bu pointer aritmeti�i kullanarak begin'i sonraki elemana i�aret etmek �zere art�r�r. Begin != end oldu�undan, d�ng� g�vdesi tekrar �al���r.
Bu, begin != end yanl�� oldu�unda, yani begin == end oldu�unda devam eder.

Dolay�s�yla, yukar�daki �unu yazd�r�r:

9 7 5 3 1
End'in dizinin sonundan bir sonraki elemana ayarland���n� unutmay�n. End'in bu adresi tutmas� iyidir (end'i dereferans etmedi�imiz s�rece, ��nk� o
adreste ge�erli bir eleman yok). Bunu, matemati�imizi ve kar��la�t�rmalar�m�z� olabildi�ince basit hale getirmek i�in yap�yoruz (hi�bir yerde 1 
eklemeye veya ��karmaya gerek yok).

�nceki derste 17.8 -- C tarz� dizi bozunmas�, dizi bozunmas�n�n fonksiyonlar� yeniden d�zenlemeyi zorla�t�rd���n� belirttik ��nk� belirli �eyler
bozunmayan dizilerle �al���r ancak bozunmu� dizilerle �al��maz (std::size gibi). Bu �ekilde bir dizi gezinmesi hakk�nda g�zel bir �ey,
yukar�daki �rne�in d�ng� k�sm�n� oldu�u gibi ayr� bir fonksiyona yeniden d�zenleyebiliriz ve hala �al���r:

                #include <iostream>

                void printArray(const int* begin, const int* end)
                {
                    for (; begin != end; ++begin)   // begin'den ba�layarak (ama hari�) end'e kadar yinele
                    {
                        std::cout << *begin << ' '; // d�ng� de�i�kenimizi dereferans yaparak mevcut eleman� al
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    const int* begin{ arr };                // begin ba�lang�� eleman�na i�aret eder
                    const int* end{ arr + std::size(arr) }; // end bir-sonraki-son elemana i�aret eder

                    printArray(begin, end);

                    return 0;
                }
Bu program, diziyi a��k�a fonksiyona ge�irmedi�imiz halde derlenir ve do�ru sonucu �retir! Ve arr'� ge�irmedi�imiz i�in printArray()'da bozunmu�
bir arr ile u�ra�mak zorunda de�iliz. Bunun yerine, begin ve end diziyi gezinmek i�in ihtiya� duydu�umuz t�m bilgileri i�erir.

Gelecekteki derslerde (iterat�rleri ve algoritmalar� ele ald���m�zda), standart k�t�phanenin, fonksiyonun hangi konteyner elemanlar� �zerinde
i�lem yapmas� gerekti�ini tan�mlamak i�in bir ba�lang�� ve biti� �ifti kullanan bir�ok fonksiyon oldu�unu g�rece�iz.

C-stil diziler �zerinde range-based for d�ng�lerinin pointer aritmeti�i kullan�larak uyguland��� A�a��daki range-based for d�ng�s�n� d���n�n:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    for (auto e : arr)         // `begin`den (`end` dahil olmamak �zere) yukar�ya do�ru yinele
                    {
                        std::cout << e << ' '; // d�ng� de�i�kenimizi dereference ederek mevcut eleman� al�n
                    }

                    return 0;
                }
E�er range-based for d�ng�lerinin belgelerine bakarsan�z, genellikle bunlar�n a�a��daki gibi uyguland���n� g�receksiniz:

                {
                    auto __begin = begin-expr;
                    auto __end = end-expr;

                    for ( ; __begin != __end; ++__begin)
                    {
                        range-declaration = *__begin;
                        loop-statement;
                    }
                }

�nceki �rnekteki range-based for d�ng�s�n� bu uygulama ile de�i�tirelim:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    auto __begin = arr;                // arr bizim begin-expr'imizdir
                    auto __end = arr + std::size(arr); // arr + std::size(arr) bizim end-expr'imizdir

                    for ( ; __begin != __end; ++__begin)
                    {
                        auto e = *__begin;         // e bizim range-declaration'�m�zd�r
                        std::cout << e << ' ';     // buras� bizim loop-statement'�m�zd�r
                    }

                    return 0;
                }

�nceki b�l�mde yazd���m�z �rne�e ne kadar benzedi�ine dikkat edin! Tek fark, *__begin'i e'ye atay�p e'yi kullanmam�z ve sadece *__begin'i do�rudan
kullanmam�zd�r!

17.10 � C-stil dizeleri ( stringler )
-------------------------------------
17.7 dersinde -- C-stil dizilere giri�, C-stil dizileri tan�tt�k, bu da bize ard���k bir eleman koleksiyonu tan�mlama imkan� verir:

                int testScore[30] {}; // 30 int'in bir dizisi, indeksler 0'dan 29'a

5.2 dersinde -- Literaller, bir dizeyi ard���k karakterlerin bir koleksiyonu olarak (�rne�in �Merhaba, d�nya!�) tan�mlad�k ve C-stil dize 
literallerini tan�tt�k. Ayr�ca, C-stil dize literalinin �Merhaba, d�nya!�'n�n const char[14] tipinde oldu�unu (13 a��k karakter art� 1 gizli
null-terminator karakter) belirttik.

E�er daha �nce noktalar� birle�tirmemi�seniz, �imdi C-stil dizelerin sadece eleman tipi char veya const char olan C-stil diziler oldu�u a��k olmal�!
C-stil dize literallerinin kodumuzda kullan�lmas� sorun olmasa da, C-stil dize nesneleri modern C++'da kullan�lmaz hale geldi ��nk� onlar� 
kullanmak zor ve tehlikelidir (std::string ve std::string_view modern yerine ge�enlerdir). Bununla birlikte, eski kodlarda hala C-stil dize 
nesnelerinin kullan�ld���n� g�rebilirsiniz ve onlar� hi� ele almam�� olmam�z eksiklik olurdu.

Bu y�zden, bu derste, modern C++'daki C-stil dize nesneleri hakk�ndaki en �nemli noktalara bakaca��z.

C-stil dizeleri tan�mlama
-------------------------
Bir C-stil dize de�i�keni tan�mlamak i�in, sadece char (veya const char / constexpr char) t�r�nde bir C-stil dizi de�i�keni bildirin:

                char str1[8]{};                    // 8 char'�n bir dizisi, indeksler 0'dan 7'ye

                const char str2[]{ "string" };     // 7 char'�n bir dizisi, indeksler 0'dan 6'ya
                constexpr char str3[] { "hello" }; // 5 const char'�n bir dizisi, indeksler 0'dan 4'e

Hat�rlay�n ki, implicit null-terminator i�in ekstra bir karaktere ihtiyac�m�z var. Bir ba�lat�c� ile C-stil dizeleri tan�mlarken, 
dizinin uzunlu�unu atlay�p derleyicinin uzunlu�u hesaplamas�na izin vermenizi �iddetle �neririz. Bu �ekilde, e�er ba�lat�c� gelecekte de�i�irse,
uzunlu�u g�ncellemeyi hat�rlaman�z gerekmez ve null-terminator tutmak i�in ekstra bir eleman eklemeyi unutma riski yoktur.

C tarz� dizeler bozulur
-----------------------
17.8 -- C tarz� dizi bozulmas� dersinde, C tarz� dizilerin �o�u durumda bir i�aret�iye bozulaca��n� tart��t�k. C tarz� dizeler C tarz� diziler 
oldu�u i�in onlar da bozulur. Ve bir C tarz� dize bir i�aret�iye bozuldu�unda, dizenin uzunlu�u (tip bilgisinde kodlanm��) kaybolur.

Bu uzunluk bilgisi kayb�, C tarz� dizelerin null-terminator olmas�n�n nedenidir. Dizenin uzunlu�u, dizenin ba�lang�c� ile null-terminator 
aras�ndaki eleman say�s�n� sayarak (verimsiz bir �ekilde) yeniden olu�turulabilir. Alternatif olarak, dize, ba�lang��tan itibaren yineleyerek ve
null-terminatora ula��ncaya kadar ge�ilebilir.

Bir C tarz� dizeyi ��kt� olarak verme
-------------------------------------
Bir C tarz� dizeyi ��kt� olarak verirken, std::cout, null-terminatorla kar��la�ana kadar karakterleri ��kt�lar. Bu null-terminator, dizenin sonunu
i�aretler, b�ylece bozulmu� dizeler (uzunluk bilgilerini kaybetmi� olanlar) hala yazd�r�labilir.

                #include <iostream>

                void print(char ptr[])
                {
                    std::cout << ptr << '\n'; // dizeyi ��kt� olarak ver
                }

                int main()
                {
                    char str[]{ "string" };
                    std::cout << str << '\n'; // stringi ��kt� olarak ver

                    print(str);

                    return 0;
                }
E�er null-terminatoru olmayan bir dizeyi yazd�rmay� denerseniz (�rne�in, null-terminator bir �ekilde �zerine yaz�ld�ysa), sonu� tan�ms�z davran��
olacakt�r. Bu durumda en olas� sonu�, dizinin t�m karakterlerinin yazd�r�lmas� ve ard�ndan biti�ik bellek slotlar�ndaki her �eyi (bir karakter 
olarak yorumlan�r) yazd�rmaya devam etmesi olacakt�r, ta ki 0 i�eren bir bellek bayt�na rastlayana kadar (bu, bir null-terminator olarak yorumlan�r)

C tarz� dizeleri giri� olarak alma
----------------------------------
Kullan�c�dan istedi�i kadar zar atmas�n� ve at�lan say�lar� bo�luk b�rakmadan girmesini istedi�imiz bir durumu d���n�n (�rne�in, 524412616).
Kullan�c� ka� karakter girecek? Hi�bir fikrimiz yok.

��nk� C tarz� dizeler sabit boyutlu dizilerdir, ��z�m, muhtemelen hi� ihtiya� duymayaca��m�zdan daha b�y�k bir dizi tan�mlamakt�r:

                #include <iostream>

                int main()
                {
                    char rolls[255] {}; // 254 karakter + null-terminator tutacak kadar b�y�k bir dizi tan�mla
                    std::cout << "Enter your rolls: ";
                    std::cin >> rolls;
                    std::cout << "You entered: " << rolls << '\n';

                    return 0;
                }
C++20'den �nce, std::cin >> rolls, m�mk�n oldu�unca �ok karakteri rolls'a ��kar�rd� (ilk �nc� olmayan bo�lu�a kadar dururdu).
Kullan�c�n�n 254'ten fazla karakter girmesini engelleyen hi�bir �ey yok (ister istemeden, ister k�t� niyetle). Ve e�er bu olursa,
kullan�c�n�n giri�i rolls dizisini ta��racak ve tan�ms�z davran�� sonucu olacakt�r.

Anahtar nokta �udur ki; Dizi ta�mas� veya tampon ta�mas�, daha fazla verinin depolama alan�na kopyaland��� durumlarda ortaya ��kan bir bilgisayar 
g�venlik sorunudur. Bu t�r durumlarda, depolama alan�n�n hemen �tesindeki bellek �zerine yaz�l�r, bu da tan�ms�z davran��a yol a�ar. K�t� niyetli
akt�rler, potansiyel olarak bu t�r kusurlar�, program�n davran���n� baz� avantajl� bir �ekilde de�i�tirmeyi umarak, belle�in i�eri�ini �zerine 
yazmak i�in kullanabilirler.

C++20'de, operator>> de�i�tirildi ve yaln�zca bozulmam�� C tarz� dizeleri giri� olarak almak i�in �al���r. Bu, operator>>'n�n,
C tarz� dizenin uzunlu�unun izin verece�i kadar �ok karakteri ��karmas�na olanak sa�lar, ta�may� �nler. Ancak bu ayn� zamanda art�k operator>>'yi
bozulmu� C tarz� dizelere giri� olarak kullanamayaca��n�z anlam�na gelir.

C tarz� dizeleri std::cin kullanarak okuman�n �nerilen yolu a�a��daki gibidir:

                #include <iostream>
                #include <iterator> // std::size i�in

                int main()
                {
                    char rolls[255] {}; // 254 karakter + null-terminator tutacak kadar b�y�k bir dizi tan�mla
                    std::cout << "Enter your rolls: ";
                    std::cin.getline(rolls, std::size(rolls));
                    std::cout << "You entered: " << rolls << '\n';

                    return 0;
                }
`cin.getline()` �a�r�s�, 254 karaktere kadar (bo�luklar dahil) `rolls` i�ine okur. Fazla karakterler at�l�r. `getline()` bir uzunluk al�r,
bu y�zden kabul edilecek maksimum karakter say�s�n� sa�layabiliriz. Bozunmayan bir diziyle, bu kolayd�r - dizinin uzunlu�unu almak i�in 
`std::size()` kullanabiliriz. bozunmu� bir diziyle, uzunlu�u ba�ka bir �ekilde belirlememiz gerekir. Ve yanl�� bir uzunluk sa�larsak,
program�m�z hatal� �al��abilir veya g�venlik sorunlar� olabilir.

Modern C++'da, kullan�c�dan gelen metni saklarken, `std::string` kullanmak daha g�venlidir, ��nk� `std::string` gerekti�i kadar �ok karakteri
tutacak �ekilde otomatik olarak ayarlan�r.

C Tarz� Dizeleri De�i�tirme
---------------------------
Not etmek i�in �nemli bir nokta, C tarz� dizelerin C tarz� dizilerle ayn� kurallar� izlemesidir. Bu, diziyi olu�tururken ba�latabilece�iniz,
ancak sonras�nda atama operat�r�n� kullanarak de�er atayamayaca��n�z anlam�na gelir!

                char str[]{ "string" }; // tamam
                str = "rope";           // tamam de�il!

Bu, C tarz� dizeleri kullanmay� biraz zorla�t�r�r. 
C tarz� dizeler diziler oldu�undan, dizedeki tek tek karakterleri de�i�tirmek i�in `[]` operat�r�n� kullanabilirsiniz:

                #include <iostream>

                int main()
                {
                    char str[]{ "string" };
                    std::cout << str << '\n';
                    str[1] = 'p';
                    std::cout << str << '\n';

                    return 0;
                }

                Bu program �unu yazd�r�r:

                string
                spring

Bir C Tarz� Dizenin Uzunlu�unu Alma
-----------------------------------
C tarz� dizeler C tarz� diziler oldu�undan, dizinin uzunlu�unu almak i�in `std::size()` (veya C++20'de `std::ssize()`) kullanabilirsiniz.
Burada iki uyar� var:

1 - Bu, bozunmu� dizilerde �al��maz.
2 - Dizenin de�il, C tarz� dizinin ger�ek uzunlu�unu d�nd�r�r.

                #include <iostream>

                int main()
                {
                    char str[255]{ "string" }; // 6 karakter + null sonland�r�c�
                    std::cout << "length = " << std::size(str) << '\n'; // length = 255 yazd�r�r

                    char *ptr { str };
                    std::cout << "length = " << std::size(ptr) << '\n'; // derleme hatas�

                    return 0;
                }
Alternatif bir ��z�m, `<cstring>` ba�l�k dosyas�nda bulunan `strlen()` fonksiyonunu kullanmakt�r. `strlen()` bozunmu� dizilerde �al���r ve tutulan
dizenin uzunlu�unu d�nd�r�r, null-terminator'u hari� tutar:

                #include <cstring> // std::strlen i�in
                #include <iostream>

                int main()
                {
                    char str[255]{ "string" }; // 6 karakter + null sonland�r�c�
                    std::cout << "length = " << std::strlen(str) << '\n'; // length = 6 yazd�r�r

                    char *ptr { str };
                    std::cout << "length = " << std::strlen(ptr) << '\n';   // length = 6 yazd�r�r

                    return 0;
                }
Ancak, `std::strlen()` yava�t�r, ��nk� t�m diziyi ge�er, null-terminatora ula�ana kadar karakterleri sayar.

Di�er C Tarz� Dizi Manip�lasyon Fonksiyonlar�
---------------------------------------------
C tarz� dizeler C dilindeki birincil dizi t�r� oldu�undan, C dili C tarz� dizeleri manip�le etmek i�in bir�ok fonksiyon sa�lar. Bu fonksiyonlar,
`<cstring>` ba�l�k dosyas�n�n bir par�as� olarak C++ taraf�ndan miras al�nm��t�r.

��te eski kodda g�rebilece�iniz en yararl� birka��:

`strlen()` -- bir C tarz� dizenin uzunlu�unu d�nd�r�r
`strcpy(), strncpy(), strcpy_s()` -- bir C tarz� dizeyi ba�ka biriyle �zerine yazar
`strcat(), strncat()` -- Bir C tarz� diziyi ba�ka birinin sonuna ekler
`strcmp(), strncmp()` -- �ki C tarz� dizeyi kar��la�t�r�r (e�itse 0 d�nd�r�r)
`strlen()` d���nda, bu t�rleri genellikle ka��nman�z� �neririz.

Non-const C Tarz� Dize Nesnelerinden Ka��n�n
--------------------------------------------
Belirli, zorlay�c� bir nedeniniz olmad�k�a, non-const C tarz� dizelerden ka��nmak en iyisidir, ��nk� bunlarla �al��mak zordur ve
ta�maya e�ilimlidirler, bu da tan�ms�z davran��a neden olur (ve potansiyel g�venlik sorunlar�d�r).

Nadir durumlarda, C tarz� dizelerle veya sabit tampon boyutlar�yla (�r. bellek s�n�rl� cihazlar i�in) �al��man�z gerekiyorsa, bu ama� i�in
tasarlanm�� iyi test edilmi� 3. taraf sabit uzunluklu dize k�t�phanesini kullanman�z� �neririz.

*** BEST -> Non-const C tarz� dizE nesnelerinden ka��n�n ve `std::string`'i tercih edin.

17.11 � C tarz� dize sembolik sabitleri
---------------------------------------
�nceki derste (17.10 -- C tarz� dizeler), C tarz� dize nesnelerini nas�l olu�turaca��m�z� ve ba�lataca��m�z� tart��t�k:

                #include <iostream>

                int main()
                {
                    char name[]{ "Alex" }; // C tarz� dize
                    std::cout << name << '\n';

                    return 0;
                }
C++, C tarz� dize sembolik sabitlerini olu�turmak i�in iki farkl� yol destekler:

                #include <iostream>

                int main()
                {
                    const char name[] { "Alex" };        // durum 1: C tarz� dize sabiti, C tarz� dize sabiti ile ba�lat�l�r
                    const char* const color{ "Orange" }; // durum 2: C tarz� dize sabitine const i�aret�i

                    std::cout << name << ' ' << color << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                Alex Orange

Yukar�daki iki y�ntem ayn� sonu�lar� �retirken, C++ bu konuda bellek tahsisini biraz farkl� �ekilde ele al�r.

Durum 1'de, "Alex" muhtemelen salt okunur bir bellekte bir yere konulur. Daha sonra program, bir C tarz� dizE i�in bellek ay�r�r ve uzunlu�u 5'tir
(d�rt a��k karakter art� null-terminator) ve bu belle�i "Alex" dizesi ile ba�lat�r. Bu y�zden "Alex"in 2 kopyas�yla sonu�lan�r�z - biri global
bellekte bir yerde, di�eri ise `name` taraf�ndan sahip olunan. `name` const oldu�undan (ve asla de�i�tirilmeyecektir), bir kopya yapmak verimsizdir

Durum 2'de, derleyicinin bunu nas�l ele ald��� uygulamaya ba�l�d�r. Genellikle olan �ey, derleyicinin "Orange" dizesini salt okunur bir bellekte
bir yere yerle�tirmesi ve daha sonra i�aret�iyi dizenin adresiyle ba�latmas�d�r.

Optimizasyon ama�lar� i�in, birden �ok dize sabiti tek bir de�ere birle�tirilebilir. �rne�in:

                const char* name1{ "Alex" };
                const char* name2{ "Alex" };

Bunlar, ayn� de�ere sahip iki farkl� dize sabitidir. Bu sabitler sabit oldu�undan, derleyici bu sabitleri tek bir payla��lan dize sabitine 
birle�tirerek bellekten tasarruf etmeyi se�ebilir ve hem `name1` hem de `name2` ayn� adrese i�aret eder.

Const C Tarz� Dizelerle T�r ��kar�m�
------------------------------------
C tarz� bir dize sabiti kullanarak t�r ��kar�m� olduk�a basittir:

                auto s1{ "Alex" };  // t�r, const char* olarak ��kar�l�r
                auto* s2{ "Alex" }; // t�r, const char* olarak ��kar�l�r
                auto& s3{ "Alex" }; // t�r, const char(&)[5] olarak ��kar�l�r

Farkl� t�rlerdeki i�aret�ileri `std::cout`'un nas�l ele ald��� hakk�nda ilgin� bir �ey fark etmi� olabilirsiniz.

A�a��daki �rne�i d���n�n:

                #include <iostream>

                int main()
                {
                    int narr[]{ 9, 7, 5, 3, 1 };
                    char carr[]{ "Merhaba!" };
                    const char* ptr{ "Alex" };

                    std::cout << narr << '\n'; // narr int* t�r�ne bozunur
                    std::cout << carr << '\n'; // carr char* t�r�ne bozunur
                    std::cout << ptr << '\n'; // ptr zaten char* t�r�nde

                    return 0;
                }

                Yazar�n makinesinde, bu yazd�:

                003AF738
                Merhaba!
                Alex

Neden int dizisi bir adresi yazd�rd�, ancak karakter dizileri dize olarak yazd�r�ld�?

Cevap, ��kt� ak��lar�n�n (�r. `std::cout`) niyetiniz hakk�nda baz� varsay�mlar yapmas�d�r. E�er ona bir char olmayan bir i�aret�i ge�irirseniz,
sadece o i�aret�inin i�eri�ini (i�aret�inin tuttu�u adresi) yazd�r�r. Ancak, e�er ona `char*` veya `const char*` t�r�nde bir nesne ge�irirseniz,
bir dizeyi yazd�rmay� ama�lad���n�z� varsayar. Sonu� olarak, i�aret�inin de�erini (bir adresi) yazd�rmak yerine, i�aret edilen dizeyi yazd�r�r!

Bu �o�u zaman istenen durumdur, ancak beklenmeyen sonu�lara yol a�abilir. A�a��daki durumu d���n�n:

                #include <iostream>

                int main()
                {
                    char c{ 'Q' };
                    std::cout << &c;

                    return 0;
                }
Bu durumda, programc� `c` de�i�keninin adresini yazd�rmay� ama�l�yor. Ancak, `&c`'nin t�r� `char*` oldu�u i�in `std::cout` bunu bir dize olarak
yazd�rmay� dener! Ve `c` null ile sonland�r�lmad��� i�in, tan�ms�z bir davran�� elde ederiz.

                Yazar�n makinesinde, bu yazd�:

                Q??????4;�?A

Bunu neden yapt�? �lk olarak, `&c`'nin (t�r� `char*` olan) bir C tarz� dize oldu�unu varsayd�. Yani 'Q'yu yazd�rd� ve devam etti. Bellekte bir
sonraki yerde bir s�r� ��p vard�. Sonunda, 0 de�erini tutan bir belle�e rastlad�, bunu bir null-terminator olarak yorumlad�, bu y�zden durdu.
`c` de�i�keninden sonraki bellekte ne oldu�una ba�l� olarak g�rd���n�z �ey farkl� olabilir.

Bu durum, ger�ek hayatta biraz olas�d�r (��nk� ger�ekten bellek adreslerini yazd�rmak istemeyeceksinizdir), ancak kaputun alt�nda i�lerin nas�l
�al��t���n� ve programlar�n nas�l istemeden raydan ��kabilece�ini g�sterir.

E�er ger�ekten bir char i�aret�isinin adresini yazd�rmak istiyorsan�z, onu `const void*` t�r�ne `static_cast` yap�n:

                #include <iostream>

                int main()
                {
                    const char* ptr{ "Alex" };

                    std::cout << ptr << '\n';                           // ptr'yi C tarz� dize olarak yazd�r
                    std::cout << static_cast<const void*>(ptr) << '\n'; // ptr taraf�ndan tutulan adresi yazd�r

                    return 0;
                }
void*`'� ders 19.5 -- Void i�aret�ileri'nde ele al�yoruz. Burada kullanmak i�in nas�l �al��t���n� bilmeniz gerekmez.

C Tarz� Dize Sembolik Sabitleri ��in `std::string_view`'i Tercih Edin
---------------------------------------------------------------------
Modern C++'da C tarz� dize sembolik sabitlerini kullanmak i�in pek bir neden yoktur. Bunun yerine, genellikle ayn� h�zda (hatta daha h�zl�) ve daha
tutarl� davranan `constexpr std::string_view` nesnelerini tercih edin.

*** BEST -> `constexpr std::string_view`'i tercih ederek C tarz� dize sembolik sabitlerinden ka��n�n.

�ok Boyutlu C Tarz� Diziler
---------------------------
�rne�in, Tic-tac-toe gibi bir oyunu d���n�n. Bu oyunun standart tahtas� 3x3'l�k bir �zgarad�r, oyuncular s�rayla 'X' ve 'O' sembollerini yerle�tirir
�st �ste �� sembol alan ilk oyuncu kazan�r.

Tahta verilerini 9 ayr� de�i�ken olarak saklayabilirdiniz, ancak birden �ok ��e �rne�iniz oldu�unda, bir dizi kullanman�n daha iyi oldu�unu
biliyoruz:

                int ttt[9]; // int'lerden olu�an bir C tarz� dizi (de�er 0 = bo�, 1 = oyuncu 1, 2 = oyuncu 2)

Bu, bellekte s�ral� olarak d�zenlenmi� 9 elemanl� bir C tarz� dizi tan�mlar. Bu elemanlar� tek bir sat�r de�erleri olarak d�zenlenmi� olarak hayal
edebiliriz:

// ttt[0] ttt[1] ttt[2] ttt[3] ttt[4] ttt[5] ttt[6] ttt[7] ttt[8]
Bir dizinin boyutu, bir ��eyi se�mek i�in gereken indeks say�s�d�r. Yaln�zca tek bir boyutu i�eren bir dizi, tek boyutlu dizi veya bir boyutlu dizi
olarak adland�r�l�r (bazen 1d dizi olarak k�salt�l�r). Yukar�daki `ttt`, tek boyutlu bir dizi �rne�idir, ��nk� ��eler tek bir indeksle se�ilebilir
(�r. `ttt[2]`).

Ancak, tek boyutlu dizimizin tic-tac-toe tahtas�na �ok benzemedi�ini unutmay�n, ��nk� tahta iki boyutta bulunur. Daha iyisini yapabiliriz.

�ki Boyutlu Diziler
-------------------
�nceki derslerde, bir dizinin ��elerinin herhangi bir nesne t�r�nde olabilece�ini belirttik. Bu, bir dizinin ��e t�r�n�n ba�ka bir dizi olabilece�i
anlam�na gelir! B�yle bir dizi tan�mlamak basittir:

                int a[3][5]; // int'lerden olu�an 5 ��eli dizinin 3 ��eli bir dizisi

Dizilerden olu�an bir dizi, iki boyutlu dizi olarak adland�r�l�r (bazen 2d dizi olarak k�salt�l�r) ��nk� iki alt dizine sahiptir.

�ki boyutlu bir diziyle, ilk (sol) alt dizinin sat�r� se�ti�ini ve ikinci (sa�) alt dizinin s�tunu se�ti�ini d���nmek uygundur. Kavramsal olarak,
bu iki boyutlu diziyi �u �ekilde d�zenlenmi� olarak hayal edebiliriz:

                // col 0    col 1    col 2    col 3    col 4
                // a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
                // a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
                // a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2
Bir iki boyutlu dizinin ��elerine eri�mek i�in, sadece iki alt dizi kullan�r�z:

                a[2][3] = 7; // a[row][col], where row = 2 and col = 3

Bu nedenle, bir Tic-tac-toe tahtas� i�in, bir 2d dizi �u �ekilde tan�mlayabiliriz:

                int ttt[3][3];

Ve �imdi, sat�r ve s�tun indekslerini kullanarak kolayca manip�le edebilece�imiz 3x3'l�k bir ��e �zgaras�na sahibiz!

�ok Boyutlu Diziler
-------------------
Bir boyuttan fazla olan dizilere �ok boyutlu diziler denir. C++ hatta 2'den fazla boyutlu �ok boyutlu dizileri bile destekler:

                int threedee[4][4][4]; // 4x4x4'l�k bir dizi (4 int'lerden olu�an 4 dizinin bir dizisi)

�rne�in, Minecraft'taki arazi 16x16x16 bloklara (chunk sections olarak adland�r�l�r) b�l�nm��t�r. 3'ten daha y�ksek boyutlara sahip diziler
desteklenir, ancak nadirdir.

2d Dizilerin Bellekte Nas�l D�zenlendi�i
----------------------------------------
Bellek do�rusal (1 boyutlu) oldu�u i�in, �ok boyutlu diziler asl�nda bir dizi ��eler olarak saklan�r. 
A�a��daki dizinin bellekte nas�l sakland���na dair iki olas� yol vard�r:

                // col 0   col 1   col 2   col 3   col 4
                // [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
                // [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
                // [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
C++ sat�r b�y�k s�ras�n� kullan�r ( row-major order ), burada ��eler bellekte sat�r sat�r s�ral� olarak yerle�tirilir, 
soldan sa�a, yukar�dan a�a��ya s�ralan�r:

                [0][0] [0][1] [0][2] [0][3] [0][4] [1][0] [1][1] [1][2] [1][3] [1][4] [2][0] [2][1] [2][2] [2][3] [2][4]
Baz� di�er diller (�rne�in Fortran) s�tun b�y�k s�ras�n� kullan�r, ��eler bellekte s�tun s�tun s�ral� olarak yerle�tirilir, yukar�dan a�a��ya,
soldan sa�a:

                [0][0] [1][0] [2][0] [0][1] [1][1] [2][1] [0][2] [1][2] [2][2] [0][3] [1][3] [2][3] [0][4] [1][4] [2][4]
C++'da, bir dizi ba�lat�l�rken, ��eler sat�r b�y�k s�ras�nda ba�lat�l�r. Ve bir diziyi ge�erken, ��eleri bellekte d�zenlendikleri s�rayla eri�mek
en verimli olan�d�r.

�ki Boyutlu Dizileri Ba�latma
-----------------------------
Bir iki boyutlu diziyi ba�latmak i�in, her bir say� setinin bir sat�r� temsil etti�i i� i�e ge�mi� parantezler kullanmak en kolay olan�d�r:

                int array[3][5]
                {
                  { 1, 2, 3, 4, 5 },     // sat�r 0
                  { 6, 7, 8, 9, 10 },    // sat�r 1
                  { 11, 12, 13, 14, 15 } // sat�r 2
                };

Baz� derleyiciler i� parantezleri atman�za izin verebilir, ancak okunabilirlik ama�lar� i�in yine de onlar� eklemenizi �iddetle �neririz.
�� parantezler kullan�l�rken, eksik ba�lat�c�lar de�er ba�lat�l�r:

                int array[3][5]
                {
                  { 1, 2 },          // sat�r 0 = 1, 2, 0, 0, 0
                  { 6, 7, 8 },       // sat�r 1 = 6, 7, 8, 0, 0
                  { 11, 12, 13, 14 } // sat�r 2 = 11, 12, 13, 14, 0
                };

Ba�lat�lm�� bir �ok boyutlu dizi, sol taraftaki uzunluk belirtimini (yaln�zca) atlayabilir:

                int array[][5]
                {
                  { 1, 2, 3, 4, 5 },
                  { 6, 7, 8, 9, 10 },
                  { 11, 12, 13, 14, 15 }
                };

Bu t�r durumlarda, derleyici ba�lang��taki say�lar�n say�s�ndan sol taraftaki uzunlu�un ne oldu�unu hesaplamak i�in matemati�i yapabilir.
Sol taraftaki olmayan boyutlar� atlamak izin verilmez:

                int array[][]
                {
                  { 1, 2, 3, 4 },
                  { 5, 6, 7, 8 }
                };

Normal diziler gibi, �ok boyutlu diziler de a�a��daki gibi 0'a ba�lat�labilir:

                int array[3][5] {};

�ki Boyutlu Diziler ve D�ng�ler
-------------------------------
Tek boyutlu bir diziyle, dizideki t�m ��eleri yinelemek i�in tek bir d�ng� kullanabiliriz:

                #include <iostream>

                int main()
                {
                    int arr[] { 1, 2, 3, 4, 5 };

                    // indeksli for d�ng�s�
                    for (std::size_t i{0}; i < std::size(arr); ++i)
                        std::cout << arr[i] << ' ';

                    std::cout << '\n';

                    // aral�k tabanl� for d�ng�s�
                    for (auto e: arr)
                        std::cout << e << ' ';

                    std::cout << '\n';

                    return 0;
                }
�ki boyutlu bir diziyle, birini sat�r� se�mek ve di�erini s�tunu se�mek i�in iki d�ng�ye ihtiyac�m�z vard�r. Ve iki d�ng�yle, hangi d�ng�n�n
d�� d�ng� ve hangisinin i� d�ng� olaca��n� belirlememiz gerekiyor. ��elere, bellekte d�zenlendikleri s�rayla eri�mek en verimli olan�d�r.
C++ sat�r b�y�k s�ras�n� kulland���ndan, sat�r se�ici d�� d�ng� olmal� ve s�tun se�ici i� d�ng� olmal�d�r.

                #include <iostream>

                int main()
                {
                    int arr[3][4] {
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }};

                    // indeksli �ift for d�ng�s�
                    for (std::size_t row{0}; row < std::size(arr); ++row) // std::size(arr) sat�r say�s�n� d�nd�r�r
                    {
                        for (std::size_t col{0}; col < std::size(arr[0]); ++col) // std::size(arr[0]) s�tun say�s�n� d�nd�r�r
                            std::cout << arr[row][col] << ' ';

                        std::cout << '\n';
                    }

                    // aral�k tabanl� �ift for d�ng�s�
                    for (const auto& arow: arr)   // her dizi sat�r�n� al
                    {
                        for (const auto& e: arow) // sat�rdaki her ��eyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }

                    return 0;
                }


�ki Boyutlu Dizi �rne�i
-----------------------
Bir iki boyutlu dizinin pratik bir �rne�ine bakal�m:

                #include <iostream>

                int main()
                {
                    constexpr int numRows{ 10 };
                    constexpr int numCols{ 10 };

                    // 10x10'luk bir dizi tan�mla
                    int product[numRows][numCols]{};

                    // Bir �arp�m tablosu hesapla
                    // 0 ile �arpma her zaman 0 oldu�u i�in sat�r ve s�tun 0'� hesaplamam�za gerek yok
                    for (std::size_t row{ 1 }; row < numRows; ++row)
                    {
                        for (std::size_t col{ 1 }; col < numCols; ++col)
                        {
                            product[row][col] = static_cast<int>(row * col);
                        }
                     }

                    for (std::size_t row{ 1 }; row < numRows; ++row)
                    {
                        for (std::size_t col{ 1 }; col < numCols; ++col)
                        {
                            std::cout << product[row][col] << '\t';
                        }

                        std::cout << '\n';
                     }


                    return 0;
                }

Bu program, 1 ve 9 (dahil) aras�ndaki t�m de�erler i�in bir �arp�m tablosunu hesaplar ve yazd�r�r. Tabloyu yazd�r�rken, for d�ng�lerinin 0 
yerine 1'den ba�lad���n� unutmay�n. Bu, sadece bir dizi 0 olan 0 s�tunu ve 0 sat�r�n� yazd�rmamak i�indir! ��te ��kt�:

                1    2    3    4    5    6    7    8    9
                2    4    6    8    10   12   14   16   18
                3    6    9    12   15   18   21   24   27
                4    8    12   16   20   24   28   32   36
                5    10   15   20   25   30   35   40   45
                6    12   18   24   30   36   42   48   54
                7    14   21   28   35   42   49   56   63
                8    16   24   32   40   48   56   64   72
                9    18   27   36   45   54   63   72   81

Kartezyen Koordinatlar vs Dizi �ndeksleri
-----------------------------------------
Geometride, bir nesnenin konumunu tan�mlamak i�in genellikle Kartezyen koordinat sistemi kullan�l�r. �ki boyutta, "x" ve "y" olarak adland�r�lan
iki koordinat ekseni vard�r. "x" yatay eksendir ve "y" dikey eksendir.

Kartezyen Koordinat Sistemi Diyagram�
-------------------------------------
�ki boyutta, bir nesnenin Kartezyen konumu, bir { x, y } �ifti olarak tan�mlanabilir, burada x-koordinat ve y-koordinat, bir nesnenin 
x-ekseninin sa��na ve y-ekseninin �zerine ne kadar uzakta oldu�unu belirten de�erlerdir. Bazen y-ekseni ters �evrilir (yani y-koordinat,
y-ekseninin ne kadar alt�nda oldu�unu tan�mlar).

�imdi C++'daki 2d dizi d�zenimize bir g�z atal�m:

                // col 0   col 1   col 2   col 3   col 4
                // [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
                // [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
                // [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2

Bu da bir ��enin konumunun [row][col] olarak tan�mlanabilece�i iki boyutlu bir koordinat sistemidir (burada col-ekseni ters �evrilmi�tir).
Her bir koordinat sistemi ba��ms�z olarak anlamak olduk�a kolayken, Kartezyen { x, y }'dan Dizi indekslerine [row][col] d�n��t�rmek biraz kar�� 
sezgiseldir. Ana fikir, bir Kartezyen sistemindeki x-koordinat�n, dizi indeksleme sisteminde hangi s�tunun se�ildi�ini tan�mlamas�d�r. 
Tersine, y-koordinat hangi sat�r�n se�ildi�ini tan�mlar. Bu nedenle, bir { x, y } Kartezyen koordinat�, bir [y][x] dizi koordinat�na d�n���r, 
bu da beklentimizin tersidir!

Bu, �u �ekilde g�r�nen 2d d�ng�lere yol a�ar:

                for (std::size_t y{0}; y < std::size(arr); ++y) // d�� d�ng� sat�rlar / y
                {
                    for (std::size_t x{0}; x < std::size(arr[0]); ++x) // i� d�ng� s�tunlar / x
                        std::cout << arr[y][x] << ' '; // �nce y (sat�r) ile indeksle, sonra x (s�tun)
                }

Bu durumda, diziyi a[y][x] olarak indeksleriz, bu da muhtemelen bekledi�iniz alfabetik s�ralaman�n tersidir.

17.13 � �ok boyutlu std::array
------------------------------
�nceki derste (17.12 -- �ok Boyutlu C Tarz� Diziler), C tarz� �ok boyutlu dizileri tart��t�k:

                // C tarz� 2d dizi
                int arr[3][4] {
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 }};

Ama bildi�iniz gibi, genellikle C tarz� dizilerden ka��nmak istiyoruz (e�er global verileri saklamak i�in kullan�lm�yorsa).
Bu derste, �ok boyutlu dizilerin `std::array` ile nas�l �al��t���na bakaca��z.

Standart K�t�phanede �ok Boyutlu Dizi S�n�f� Yok
------------------------------------------------
`std::array`'in tek boyutlu bir dizi olarak uyguland���n� unutmay�n. Yani ilk sordu�unuz soru, "�ok boyutlu diziler i�in bir standart k�t�phane
s�n�f� var m�?" olmal�. Ve cevap... hay�r. �ok k�t�. Womp womp. 

�ki Boyutlu `std::array`
------------------------
`std::array`'in iki boyutlu bir dizi olu�turman�n kanonik yolu, �ablon t�r arg�man�n�n ba�ka bir `std::array` oldu�u bir `std::array` olu�turmakt�r.
Bu, �una benzer bir �eye yol a�ar:

                std::array<std::array<int, 4>, 3> arr {{  // �ift paranteze dikkat edin
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 }}};

Bu hakk�nda birka� "ilgin�" �ey not etmek var:

*- �ok boyutlu bir `std::array` ba�lat�rken, �ift parantez kullanmam�z gerekiyor (nedenini ders 17.4 -- s�n�f t�rlerinin `std::array`'i ve brace 
   elision'da tart���yoruz).
*- S�zdizimi a��r ve okumas� zor.
*- �ablonlar�n i� i�e ge�me �ekli nedeniyle, dizi boyutlar� de�i�tirilir. 4 ��eli 3 sat�rl� bir dizi istiyoruz, bu y�zden `arr[3][4]` do�ald�r. 
   `std::array<std::array<int, 4>, 3>` tersine �evrilmi�tir.

Bir iki boyutlu `std::array` ��esini indekslemek, bir iki boyutlu C tarz� dizi indekslemesi gibi �al���r:

                std::cout << arr[1][2]; // sat�r 1, s�tun 2'deki ��eyi yazd�r

Ayr�ca bir iki boyutlu `std::array`'i, bir boyutlu bir `std::array` gibi bir fonksiyona da ge�irebiliriz:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t Row, std::size_t Col>
                void printArray(std::array<std::array<T, Col>, Row> &arr)
                {
                    for (const auto& arow: arr)   // her dizi sat�r�n� al
                    {
                        for (const auto& e: arow) // sat�rdaki her ��eyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }
                }

                int main()
                {
                    std::array<std::array<int, 4>, 3>  arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    printArray(arr);

                    return 0;
                }
I�ren�. Ve bu, bir iki boyutlu `std::array` i�in. �� boyutlu veya daha y�ksek bir `std::array` daha da a��rd�r!

�ok Boyutlu `std::array`'i Kullanmay� Kolayla�t�rmak i�in Takma Ad �ablonlar�
-----------------------------------------------------------------------------
Ders 10.7 -- Typedefs ve type aliases'de, takma adlar� tan�tt�k ve takma adlar�n bir kullan�m�n�n karma��k t�rleri daha basit hale getirmek
oldu�unu belirttik. Ancak, normal bir t�r takma ad�yla, t�m �ablon arg�manlar�n� a��k�a belirtmemiz gerekir. �rne�in:

                using Array2dint34 = std::array<std::array<int, 4>, 3>;

Bu, bir 3�4 iki boyutlu `std::array` of int istedi�imiz her yerde `Array2dint34` kullanmam�za olanak sa�lar. Ancak, kullanmak istedi�imiz her 
��e t�r� ve boyut kombinasyonu i�in b�yle bir takma ada ihtiyac�m�z olaca��n� unutmay�n!

Bu, bir t�r takma ad� i�in ��e t�r�n�, sat�r uzunlu�unu ve s�tun uzunlu�unu �ablon arg�manlar� olarak belirtmemize izin veren bir takma ad �ablonu
kullanman�n m�kemmel bir yeridir!

                // �ki boyutlu bir std::array i�in bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

Daha sonra, bir 3�4 iki boyutlu `std::array` of int istedi�imiz her yerde `Array2d<int, 3, 4>` kullanabiliriz. Bu �ok daha iyi!

��te tam bir �rnek:

                #include <array>
                #include <iostream>

                // �ki boyutlu bir std::array i�in bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

                // Array2d'yi bir fonksiyon parametresi olarak kullan�rken, �ablon parametrelerini yeniden belirtmemiz gerekiyor
                template <typename T, std::size_t Row, std::size_t Col>
                void printArray(Array2d<T, Row, Col> &arr)
                {
                    for (const auto& arow: arr)   // her dizi sat�r�n� al
                    {
                        for (const auto& e: arow) // sat�rdaki her ��eyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }
                }

                int main()
                {
                    // 3 sat�r ve 4 s�tunlu bir int'in iki boyutlu dizisini tan�mla
                    Array2d<int, 3, 4> arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    printArray(arr);

                    return 0;
                }

Ne kadar daha �zl� ve kullan�m� kolay oldu�una dikkat edin! Takma ad �ablonumuz hakk�nda g�zel bir �ey, �ablon parametrelerimizi istedi�imiz
s�rayla tan�mlayabilece�imizdir. `std::array` �nce ��e t�r�n� ve ard�ndan boyutu belirtti�inden, bu d�zene ba�l� kal�r�z. Ancak `Row` veya `Col`'u
ilk tan�mlama esnekli�ine sahibiz. C tarz� dizi tan�mlar� sat�r �ncelikli tan�mland���ndan, takma ad �ablonumuzu `Row`'dan �nce `Col` ile tan�mlar�z

Bu y�ntem, daha y�ksek boyutlu `std::array`'a da g�zel bir �ekilde �l�eklenir:

                // �� boyutlu bir std::array i�in bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
                using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;

�ki Boyutlu Bir Dizinin Boyutsal Uzunluklar�n� Alma
---------------------------------------------------
Bir iki boyutlu dizinin uzunlu�unu almak biraz sezgisel de�ildir.

                #include <array>
                #include <iostream>

                // �ki boyutlu bir std::array i�in bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

                int main()
                {
                    // 3 sat�r ve 4 s�tunlu bir int'in iki boyutlu dizisini tan�mla
                    Array2d<int, 3, 4> arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    std::cout << "Rows: " << arr.size() << '\n';    // ilk boyutun (sat�rlar) uzunlu�unu al
                    std::cout << "Cols: " << arr[0].size() << '\n'; // ikinci boyutun (s�tunlar) uzunlu�unu al

                    return 0;
                }
Birinci boyutun uzunlu�unu almak i�in, dizimizde `size()`'� �a��rmam�z yeterlidir. Peki ya ikinci boyut? �kinci boyutun uzunlu�unu almak i�in, 
o boyuttan bir ��eye ihtiyac�m�z var. Bu nedenle, alt diziyi almak i�in �nce `arr[0]`'� �a��r�r�z (��e 0'�n var oldu�u garantilidir),
ard�ndan onun �zerinde `size()`'� �a��r�r�z.

3 boyutlu bir dizinin ���nc� boyutunun uzunlu�unu almak i�in, `arr[0][0].size()`'� �a��rabiliriz.

�ki Boyutlu Bir Diziyi D�zle�tirme
----------------------------------
�ki veya daha fazla boyutlu diziler baz� zorluklarla kar��la��r:

- Tan�mlamalar� ve �al��malar� daha ayr�nt�l�d�r.
- �lk boyuttan daha b�y�k boyutlar�n uzunlu�unu almak garip.
- �zerlerinde yinelemek giderek daha zor hale gelir (her boyut i�in bir d�ng� daha gerektirir).

�ok boyutlu dizilerle �al��may� kolayla�t�rman�n bir yakla��m�, onlar� d�zle�tirmektir. Bir diziyi d�zle�tirmek, bir dizinin boyutsall���n� azaltma
s�recidir (genellikle tek bir boyuta indirgenir).

�rne�in, `Row` sat�r ve `Col` s�tunlu olan iki boyutlu bir dizi olu�turmak yerine, `Row * Col` ��esi olan tek boyutlu bir dizi olu�turabiliriz.
Bu, tek bir boyut kullanarak bize ayn� miktarda depolama alan� sa�lar.

Ancak, tek boyutlu dizimizin yaln�zca tek bir boyutu oldu�u i�in, onunla �ok boyutlu bir dizi olarak �al��amay�z. Bunu ��zmek i�in, �ok boyutlu bir
diziyi taklit eden bir aray�z sa�layabiliriz. Bu aray�z, iki boyutlu koordinatlar� kabul eder ve ard�ndan bunlar� tek boyutlu dizide benzersiz bir 
konuma e�ler.

C++11 veya daha yeni s�r�mlerde �al��an bu yakla��m�n bir �rne�i a�a��dad�r:

                #include <array>
                #include <iostream>
                #include <functional>

                // �ki boyut kullanarak tek boyutlu bir std::array tan�mlamam�za izin veren bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using ArrayFlat2d = std::array<T, Row * Col>;

                // ArrayFlat2d ile iki boyutta �al��mam�za izin veren bir de�i�tirilebilir g�r�n�m
                // Bu bir g�r�n�m oldu�u i�in, g�r�nt�lenen ArrayFlat2d'nin kapsamda kalmas� gerekir
                template <typename T, std::size_t Row, std::size_t Col>
                class ArrayView2d
                {
                private:
                    // m_arr'yi bir ArrayFlat2d referans� yapma e�iliminde olabilirsiniz,
                    // ancak bu, g�r�n�m�n kopyalanabilir olmamas�n� sa�lar ��nk� referanslar yeniden oturtulamaz.
                    // std::reference_wrapper kullanmak bize referans semanti�i ve kopyalanabilirli�i sa�lar.
                    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

                public:
                    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr)
                        : m_arr { arr }
                    {}

                    // Tek alt dizin arac�l���yla ��eyi al (operator[] kullanarak)
                    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
                    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

                    // 2d alt dizin arac�l���yla ��eyi al (operator() kullanarak, ��nk� operator[] C++23'ten �nce birden �ok boyutu desteklemiyor)
                    T& operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
                    const T& operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

                    // C++23'te, bunlar� yorumdan ��karabilirsiniz ��nk� �ok boyutlu operator[] desteklenir
                //    T& operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
                //    const T& operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

                    int rows() const { return static_cast<int>(Row); }
                    int cols() const { return static_cast<int>(Col); }
                    int length() const { return static_cast<int>(Row * Col); }
                };

                int main()
                {
                    // Bir int'in tek boyutlu std::array'ini tan�mla (3 sat�r ve 4 s�tun ile)
                    ArrayFlat2d<int, 3, 4> arr {
                        1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12 };

                    // Tek boyutlu dizimize iki boyutlu bir g�r�n�m tan�mla
                    ArrayView2d<int, 3, 4> arrView { arr };

                    // dizi boyutlar�n� yazd�r
                    std::cout << "Rows: " << arrView.rows() << '\n';
                    std::cout << "Cols: " << arrView.cols() << '\n';

                    // tek boyut kullanarak diziyi yazd�r
                    for (int i=0; i < arrView.length(); ++i)
                        std::cout << arrView[i] << ' ';

                    std::cout << '\n';

                    // iki boyut kullanarak diziyi yazd�r
                    for (int row=0; row < arrView.rows(); ++row)
                    {
                        for (int col=0; col < arrView.cols(); ++col)
                            std::cout << arrView(row, col) << ' ';
                        std::cout << '\n';
                    }

                    std::cout << '\n';

                    return 0;
                }

                Bu, a�a��dakileri yazd�r�r:

                Rows: 3
                Cols: 4
                1 2 3 4 5 6 7 8 9 10 11 12
                1 2 3 4
                5 6 7 8
                9 10 11 12

C++23'ten �nce `operator[]` yaln�zca tek bir alt dizin kabul edebilir, bu y�zden iki alternatif yakla��m vard�r:

- Bunun yerine `operator()` kullan�n, bu birden �ok alt dizin kabul eder. Bu, tek indeks indekslemesi i�in `[]` ve �ok boyutlu indeksleme i�in `()`
  kullanman�za olanak sa�lar. Yukar�da bu yakla��m� se�tik.

- `operator[]`'nin bir alt g�r�n�m d�nd�rmesine izin verin, b�ylece `operator[]`'yi zincirleyebilirsiniz. Bu daha karma��k ve daha y�ksek boyutlara
   iyi �l�eklenmez.

C++23'te, `operator[]` birden �ok alt dizin kabul etmek �zere geni�letildi, bu y�zden hem tek hem de �oklu alt dizinleri i�lemek i�in onu a��r� 
y�kleyebilirsiniz (birden �ok alt dizin i�in `operator()` kullanmak yerine).

`std::mdspan` C++23
-------------------
C++23'te tan�t�lan `std::mdspan`, s�rekli bir ��e dizisi i�in �ok boyutlu bir dizi aray�z� sa�layan bir de�i�tirilebilir g�r�n�md�r.
De�i�tirilebilir g�r�n�m derken, bir `std::mdspan`'in sadece salt okunur bir g�r�n�m (`std::string_view` gibi) olmad���n� kastediyoruz 
temel ��e dizisi sabit de�ilse, bu ��eler de�i�tirilebilir.

A�a��daki �rnek, �nceki �rnekle ayn� ��kt�y� yazd�r�r, ancak kendi �zel g�r�n�m�m�z yerine `std::mdspan` kullan�r:

                #include <array>
                #include <iostream>
                #include <mdspan>

                // �ki boyut kullanarak tek boyutlu bir std::array tan�mlamam�za izin veren bir takma ad �ablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using ArrayFlat2d = std::array<T, Row * Col>;

                int main()
                {
                    // Bir int'in tek boyutlu std::array'ini tan�mla (3 sat�r ve 4 s�tun ile)
                    ArrayFlat2d<int, 3, 4> arr {
                        1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12 };

                    // Tek boyutlu dizimize iki boyutlu bir span tan�mla
                    // std::mdspan'a bir ��e dizisine i�aret�i ge�irmemiz gerekiyor
                    // bunu, bir C tarz� dizinin bozunmas� veya std::array veya std::vector'�n data() �ye fonksiyonunu kullanarak yapabiliriz
                    std::mdspan mdView { arr.data(), 3, 4 };

                    // dizi boyutlar�n� yazd�r
                    // std::mdspan bunlara extents der
                    std::size_t rows { mdView.extents().extent(0) };
                    std::size_t cols { mdView.extents().extent(1) };
                    std::cout << "Rows: " << rows << '\n';
                    std::cout << "Cols: " << cols << '\n';

                    // tek boyutlu olarak diziyi yazd�r
                    // data_handle() �ye, bize bir ��e dizisine i�aret�i verir
                    // daha sonra bunu indeksleyebiliriz
                    for (std::size_t i=0; i < mdView.size(); ++i)
                        std::cout << mdView.data_handle()[i] << ' ';
                    std::cout << '\n';

                    // iki boyutlu olarak diziyi yazd�r
                    // ��elere eri�mek i�in �ok boyutlu [] kullan�r�z
                    for (std::size_t row=0; row < rows; ++row)
                    {
                        for (std::size_t col=0; col < cols; ++col)
                            std::cout << mdView[row, col] << ' ';
                        std::cout << '\n';
                    }
                    std::cout << '\n';

                    return 0;
                }

Bu olduk�a basit olmal�, ancak not etmeye de�er birka� �ey var:

- `std::mdspan` bize istedi�imiz kadar boyutla bir g�r�n�m tan�mlama imkan� verir.
- `std::mdspan`'�n yap�c�s�na ilk parametre olarak bir dizi verisi i�aret�isi olmal�d�r. Bu, bir C tarz� dizinin bozunmas� olabilir veya 
  `std::array` veya `std::vector`'�n `data()` �ye fonksiyonunu kullanarak bu veriyi alabiliriz.
- Bir `std::mdspan`'i tek boyutlu olarak indekslemek i�in, dizinin verisine i�aret�iyi almal�y�z, bunu `data_handle()` �ye fonksiyonunu kullanarak
  yapabiliriz. Daha sonra bunu alt dizinleyebiliriz.
- C++23'te, `operator[]` birden �ok indeks kabul eder, bu y�zden indeksimiz olarak `[row][col]` yerine `[row, col]` kullan�r�z.
- C++26, `std::array` ve `std::mdspan`'i sahip olan �ok boyutlu bir diziye d�n��t�ren `std::mdarray`'i i�erecek!

**B�l�m �ncelemesi**
--------------------
Sabit boyutlu diziler (veya sabit uzunluklu diziler), dizinin uzunlu�unun �rnekleme noktas�nda bilinmesini ve bu uzunlu�un daha sonra
de�i�tirilememesini gerektirir. C tarz� diziler ve `std::array` her ikisi de sabit boyutlu dizilerdir. Dinamik diziler �al��ma zaman�nda
yeniden boyutland�r�labilir. `std::vector` bir dinamik dizidir.

Bir `std::array`'in uzunlu�u bir sabit ifade olmal�d�r. �o�u zaman, uzunluk i�in sa�lanan de�er bir tam say� literali, `constexpr` de�i�keni 
veya kapsams�z bir numarat�r olacakt�r.

`std::array` bir topluluktur. Bu, hi�bir yap�c�ya sahip olmad��� ve bunun yerine toplu ba�latma kullan�larak ba�lat�ld��� anlam�na gelir.

`std::array`'inizi m�mk�n oldu�unda `constexpr` olarak tan�mlay�n. `std::array`'iniz `constexpr` de�ilse, bunun yerine bir `std::vector` 
kullanmay� d���n�n.

Derleyicinin bir `std::array`'in t�r�n� ve uzunlu�unu ba�lat�c�lar�ndan ��karmas�n� sa�lamak i�in s�n�f �ablon arg�man ��kar�m�n� (CTAD) kullan�n.

`std::array`, a�a��daki gibi bir �ablon yap� olarak uygulanm��t�r:

                template<typename T, std::size_t N> // N, bir t�r olmayan �ablon parametresidir
                struct array;

Dizi uzunlu�unu temsil eden t�r olmayan �ablon parametresi (`N`) `std::size_t` t�r�ndedir.

Bir `std::array`'in uzunlu�unu almak i�in:

- Bir `std::array` nesnesinden uzunlu�unu `size()` �ye fonksiyonunu kullanarak sorabiliriz (bu, uzunlu�u `unsigned size_type` olarak d�nd�r�r).
- C++17'de, `std::size()` adl� �ye olmayan fonksiyonu kullanabiliriz (bu, `std::array` i�in sadece `size()` �ye fonksiyonunu �a��r�r, 
  b�ylece uzunlu�u `unsigned size_type` olarak d�nd�r�r).
- C++20'de, uzunlu�u b�y�k bir imzal� integral t�r olarak d�nd�ren `std::ssize()` adl� �ye olmayan fonksiyonu kullanabiliriz
  (genellikle `std::ptrdiff_t`).
- Bu �� fonksiyonun t�m�, uzunlu�u bir `constexpr` de�eri olarak d�nd�recektir, ancak bir `std::array` referans olarak ge�irildi�inde �a�r�ld���nda
  bu ge�erli olmayacakt�r. Bu kusur, P2280 taraf�ndan C++23'te ele al�nm��t�r.

Bir `std::array`'i indekslemek i�in:

- Alt dizin operat�r�n� (`operator[]`) kullan�n. Bu durumda hi�bir s�n�rlama kontrol� yap�lmaz ve ge�ersiz bir indeks ge�irilirse tan�ms�z
  davran��a neden olur.
- �al��ma zaman�nda s�n�rlama kontrol� yapan `at()` �ye fonksiyonunu kullan�n. Genellikle indekslemeden �nce s�n�rlama kontrol� yapmak istedi�imiz
  veya derleme zaman� s�n�rlama kontrol� yapmak istedi�imiz i�in bu fonksiyonu kullanmaman�z� �neririz.
- Derleme zaman� s�n�rlama kontrol� yapan ve indeksi t�r olmayan bir �ablon arg�man� olarak alan `std::get()` fonksiyon �ablonunu kullan�n.
- Farkl� ��e t�rleri ve uzunluklara sahip bir `std::array`'i, �ablon parametre bildirimi `template <typename T, std::size_t N>` olan bir fonksiyon
  �ablonuna ge�irebilirsiniz. Veya C++20'de, `template <typename T, auto N>` kullan�n.

Bir `std::array`'i de�er olarak d�nd�rmek, diziyi ve t�m ��eleri kopyalar, ancak bu, dizi k���k ve ��elerin kopyalanmas� pahal� de�ilse kabul
edilebilir olabilir. Baz� ba�lamlarda, bunun yerine bir ��k�� parametresi kullanmak daha iyi bir se�enek olabilir.

Bir `std::array`'i bir struct, s�n�f veya dizi ile ba�lat�rken ve her ba�lat�c�yla ��e t�r�n� sa�lamazsan�z, derleyicinin neyi ba�lataca��n� do�ru
bir �ekilde yorumlamas� i�in ekstra bir �ift paranteze ihtiyac�n�z olacakt�r. Bu, toplu ba�latman�n bir kal�nt�s�d�r ve di�er standart k�t�phane 
konteyner t�rleri (liste yap�land�r�c�lar� kullananlar) bu durumlarda �ift parantez gerektirmez.

C++'daki topluluklar, birden �ok parantezin atlanabilece�i durumlar� belirleyen brace elision adl� bir kavram� destekler. Genellikle, bir 
`std::array`'i skalar (tek) de�erlerle veya t�r�n her ��e ile a��k�a adland�r�ld��� s�n�f t�rleri veya dizilerle ba�lat�rken parantezleri
atlayabilirsiniz.

Referanslar�n bir dizisi olamaz, ancak `std::reference_wrapper`'�n bir dizisi olabilir, bu da de�i�tirilebilir bir lvalue referans� gibi davran�r.

`std::reference_wrapper` hakk�nda not edilmesi gereken birka� �ey var:

- `Operator=` bir `std::reference_wrapper`'� yeniden oturtur (referans verilen nesneyi de�i�tirir).
- `std::reference_wrapper<T>` otomatik olarak `T&`'ye d�n��t�r�l�r.
- `get()` �ye fonksiyonu, bir `T&` almak i�in kullan�labilir. Bu, referans verilen nesnenin de�erini g�ncellemek istedi�imizde yararl�d�r.
- `std::ref()` ve `std::cref()` fonksiyonlar�, `std::reference_wrapper` ve `const std::reference_wrapper` sar�l� nesneleri olu�turmak i�in
   k�sayollar olarak sa�land�.

M�mk�n oldu�unda, CTAD kullanarak bir `constexpr std::array`'in do�ru say�da ba�lat�c�ya sahip oldu�unu garantilemek i�in `static_assert` kullan�n.

C tarz� diziler, C dilinden miras al�nd� ve C++'�n �ekirdek dilinin bir par�as�d�r. �ekirdek dilin bir par�as� olduklar� i�in, C tarz� dizilerin
kendi �zel bildirim s�zdizimleri vard�r. Bir C tarz� dizi bildiriminde, bir nesnenin bir C tarz� dizi oldu�unu derleyiciye bildirmek i�in k��eli
parantezler (`[]`) kullan�r�z. K��eli parantezlerin i�inde, dizinin uzunlu�unu iste�e ba�l� olarak sa�layabiliriz, bu `std::size_t` t�r�nde bir 
integral de�erdir ve derleyiciye dizide ka� ��enin oldu�unu s�yler. Bir C tarz� dizinin uzunlu�u bir sabit ifade olmal�d�r.

C tarz� diziler topluluktur, bu da onlar�n toplu ba�latma kullan�larak ba�lat�labilece�i anlam�na gelir. Bir C tarz� dizinin t�m ��elerini bir 
ba�lat�c� listesi kullanarak ba�lat�rken, uzunlu�u atlamak ve derleyicinin dizinin uzunlu�unu hesaplamas�na izin vermek tercih edilir.

C tarz� diziler `operator[]` arac�l���yla indekslenebilir. Bir C tarz� dizinin indeksi, bir imzal� veya imzas�z tam say� veya kapsams�z bir
numarasyon olabilir. Bu, C tarz� dizilerin, standart k�t�phane konteyner s�n�flar�n�n sahip oldu�u t�m i�aret d�n���m� indeksleme sorunlar�na 
tabi olmad��� anlam�na gelir!

C tarz� diziler `const` veya `constexpr` olabilir.

Bir C tarz� dizinin uzunlu�unu almak i�in:

- C++17'de, uzunlu�u `unsigned std::size_t` olarak d�nd�ren `std::size()` adl� �ye olmayan fonksiyonu kullanabiliriz.
- C++20'de, uzunlu�u genellikle `std::ptrdiff_t` olan b�y�k bir imzal� integral t�r olarak d�nd�ren `std::ssize()` adl� �ye olmayan fonksiyonu 
  kullanabiliriz.
- �o�u durumda, bir C tarz� dizi bir ifadede kullan�ld���nda, dizi otomatik olarak ��e t�r�ne bir i�aret�iye d�n��t�r�l�r ve ilk ��enin (indeks 0)
  adresiyle ba�lat�l�r. Bu, halk aras�nda dizi bozunmas� (veya k�saca bozunma) olarak adland�r�l�r.

��aret�i aritmeti�i, belirli tam say� aritmetik operat�rlerini (toplama, ��karma, art�rma veya azaltma) bir i�aret�iye uygulama �zelli�idir ve yeni
bir bellek adresi �retir. Belirli bir i�aret�i `ptr` verildi�inde, `ptr + 1` bellekteki sonraki nesnenin adresini d�nd�r�r
(i�aret edilen t�re dayan�r).

- Dizinin ba��ndan (��e 0) indeksleme yaparken alt dizinlemeyi kullan�n, b�ylece dizi indeksleri ��e ile ayn� hizada olur.
- Belirli bir ��eden g�receli konumland�rma yaparken i�aret�i aritmeti�i kullan�n.

C tarz� dizeler, ��e t�r� `char` veya `const char` olan C tarz� dizilerdir. Bu nedenle, C tarz� dizeler bozunur.

Bir dizinin boyutu, bir ��eyi se�mek i�in gereken indeks say�s�d�r.

Yaln�zca tek bir boyut i�eren bir diziye tek boyutlu dizi veya bir boyutlu dizi (bazen 1d dizi olarak k�salt�l�r) denir.
Dizilerin bir dizisi, iki alt dizine sahip oldu�u i�in iki boyutlu dizi (bazen 2d dizi olarak k�salt�l�r) olarak adland�r�l�r. 
Birden fazla boyuta sahip dizilere �ok boyutlu diziler denir. Bir diziyi d�zle�tirmek, bir dizinin boyutsall���n� azaltma s�recidir
(genellikle tek bir boyuta indirgenir).

C++23'te, `std::mdspan` s�rekli bir ��e dizisi i�in �ok boyutlu bir dizi aray�z� sa�layan bir g�r�n�md�r.
*/