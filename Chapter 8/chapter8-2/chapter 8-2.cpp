#include <iostream>

int main()
{
    return 0;
}
/*
Break ve Continue
-----------------
Break

Switch ifadeleri ba�lam�nda break ifadesini zaten g�rd�n�z (8.5 -- Switch ifadesi temelleri), ancak bu ifade di�er kontrol ak�� ifadeleriyle de kullan�labilir,
bu nedenle daha detayl� bir a��klamay� hak ediyor. break ifadesi, bir while d�ng�s�, do-while d�ng�s�, for d�ng�s� veya switch ifadesini sonland�r�r ve k�r�lan
d�ng� veya switch ifadesinden sonra gelen bir sonraki ifadeyle devam eder

Brak ile switch kullan�m�
-------------------------
Switch ifadesi ba�lam�nda, bir break genellikle her durumun sonunda kullan�l�r ve bu durumun bitti�ini belirtmek i�in kullan�l�r
(bu, ard���k durumlara ge�i�in �nlenmesini sa�lar):
                #include <iostream>

                void printMath(int x, int y, char ch)
                {
                    switch (ch)
                    {
                    case '+':
                        std::cout << x << " + " << y << " = " << x + y << '\n';
                        break; // ard���k durumlara ge�me
                    case '-':
                        std::cout << x << " - " << y << " = " << x - y << '\n';
                        break; // ard���k durumlara ge�me
                    case '*':
                        std::cout << x << " * " << y << " = " << x * y << '\n';
                        break; // ard���k durumlara ge�me
                    case '/':
                        std::cout << x << " / " << y << " = " << x / y << '\n';
                        break;
                    }
                }

                int main()
                {
                    printMath(2, 3, '+');

                    return 0;
                }

Bir loop ile break in kullan�m�
--------------------------------
D�ng� ba�lam�nda, bir `break` ifadesi d�ng�y� erken sonland�rmak i�in kullan�labilir. ��lem, d�ng�n�n sonundan sonraki ifadeyle devam eder.
                #include <iostream>

                int main()
                {
                    int sum{ 0 };

                    // Kullan�c�ya 10'a kadar say� girmesine izin ver
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        std::cout << "Eklemek i�in bir say� girin veya ��kmak i�in 0 girin: ";
                        int num{};
                        std::cin >> num;

                        // Kullan�c� 0 girdiyse d�ng�den ��k
                        if (num == 0)
                            break; // d�ng�den �imdi ��k

                        // Aksi takdirde say�y� toplam�m�za ekleyin
                        sum += num;
                    }

                    // break'ten sonra i�lem buradan devam edecek
                    std::cout << "Girdi�iniz t�m say�lar�n toplam�: " << sum << '\n';

                    return 0;
                }

Bu program, kullan�c�n�n 10'a kadar say� girmesine izin verir ve giri� yap�lan t�m say�lar�n toplam�n�
sonunda g�r�nt�ler. Kullan�c� 0 girdi�inde, break, d�ng�n�n erken sona ermesine (10 say� girilmeden �nce) neden olur.
��kt� : 
                Bir say� eklemek i�in girin veya ��kmak i�in 0 girin: 5
                Bir say� eklemek i�in girin veya ��kmak i�in 0 girin: 3
                Bir say� eklemek i�in girin veya ��kmak i�in 0 girin: 8
                Bir say� eklemek i�in girin veya ��kmak i�in 0 girin: 0
                Girdi�iniz t�m say�lar�n toplam�: 16

`break`, iste�e ba�l� olarak sonsuz bir d�ng�den ��kmak i�in yayg�n olarak kullan�lan bir y�ntemdir yukar�daki i�lemin ayn�s� bir if blo�u ile yap�labilir. 

Break vs return 
---------------
`Break` ve `return` ifadeleri aras�ndaki fark� anlamak yeni programc�lar i�in bazen zor olabilir. Bir `break` ifadesi, switch veya d�ng�y� sonland�r�r ve i�lem,
switch veya d�ng�n�n �tesindeki ilk ifadeyle devam eder. Bir `return` ifadesi ise i�inde bulundu�u fonksiyonu tamamen sonland�r�r ve i�lem, fonksiyonun �a�r�ld��� 
noktada devam eder.

                        #include <iostream>

                        int breakOrReturn()
                        {
                            while (true) // sonsuz d�ng�
                            {
                                std::cout << "'b' girmek i�in veya 'r' girmek i�in: ";
                                char ch{};
                                std::cin >> ch;

                                if (ch == 'b')
                                    break; // i�lem, d�ng�n�n �tesindeki ilk ifadeyle devam edecektir

                                if (ch == 'r')
                                    return 1; // return, fonksiyonun hemen �a�r�ld��� yere (bu durumda main()) geri d�necektir
                            }

                            // d�ng�y� k�rmak, i�lemin buradan devam etmesine neden olur

                            std::cout << "D�ng�den ��kt�k\n";

                            return 0;
                        }

                        int main()
                        {
                            int returnValue{ breakOrReturn() };
                            std::cout << "breakOrReturn fonksiyonu �unu d�nd�rd�: " << returnValue << '\n';

                            return 0;
                        }

Bu program�n iki �al��t�rmas�:

                        'b' girmek i�in veya 'r' girmek i�in: r
                        breakOrReturn fonksiyonu 1 d�nd�rd�

                        'b' girmek i�in veya 'r' girmek i�in: b
                        D�ng�den ��kt�k
                        breakOrReturn fonksiyonu 0 d�nd�rd�

`Continue` ifadesi
------------------
`continue` ifadesi, mevcut d�ng� iterasyonunu sonland�rmadan t�m d�ng�y� sonland�rmak i�in uygun bir yol sa�lar.

��te `continue` kullan�m�n�n bir �rne�i:

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // e�er say� 4'e b�l�nebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue; // bir sonraki iterasyona git

                        // E�er say� 4'e b�l�nebiliyorsa, devam et
                        std::cout << count << '\n';

                        // continue ifadesi buraya atlar
                    }

                    return 0;
                }

Yani bu program 4 e b�l�nemeyen say�lar� yazd�r�r
                    1
                    2
                    3
                    5
                    6
                    7
                    9
`continue` ifadesi, mevcut y�r�tme noktas�n� mevcut d�ng�n�n alt�na atarak �al���r.

Bir for-d�ng�s� durumunda, for-d�ng�s�n�n end ifadesi (yukar�daki �rnekte `++count`), continue'dan sonra hala �al���r (��nk� bu, d�ng� g�vdesinin sonundan sonra 
ger�ekle�ir).

Dikkatli olun, bir continue ifadesini while veya do-while d�ng�leri ile kullan�rken. Bu d�ng�ler genellikle d�ng� g�vdesi i�inde kullan�lan de�i�kenlerin de�erini 
de�i�tirir. E�er continue ifadesi, bu sat�rlar�n atlanmas�na neden oluyorsa, d�ng� sonsuz olabilir!

break ve continue kullan�m� �zerine yap�lan tart��ma
----------------------------------------------------
Bir�ok kaynak, break ve continue ifadelerinin d�ng�lerde kullan�lmas�ndan ka��n�lmas� gerekti�i konusunda okuyucular� uyar�r, ��nk� bu ifadeler, y�r�tme ak���n�n
atlamas�na neden olabilir ve mant�k ak���n� takip etmeyi zorla�t�rabilir. �rne�in, karma��k bir mant�k par�as�nda ortas�nda bir break, ya atlanabilir ya da ne 
ko�ullar alt�nda tetiklenmesi gerekti�i a��k olmayabilir.

Ancak, dikkatli bir �ekilde kullan�ld���nda, break ve continue, d�ng�leri daha okunabilir hale getirmeye yard�mc� olabilir. Bu ifadeler, i� i�e ge�mi� bloklar�n 
say�s�n� azaltarak ve karma��k d�ng� mant���na duyulan ihtiyac� azaltarak, d�ng�leri daha anla��l�r hale getirebilir.
�rne�in: 
            #include <iostream>

            int main()
            {
                int count{ 0 }; // d�ng�n�n ka� kez tekrarland���n� say
                bool keepLooping { true }; // d�ng�n�n bitip bitmedi�ini kontrol eder
                while (keepLooping)
                {
                    std::cout << "Bu d�ng�den ��kmak i�in 'e' girin veya devam etmek i�in herhangi bir karakter girin: ";
                    char ch{};
                    std::cin >> ch;

                    if (ch == 'e')
                        keepLooping = false;
                    else
                    {
                        ++count;
                        std::cout << "Biz " << count << " kez tekrarlad�k\n";
                    }
                }

                return 0;
            }

Bu program, d�ng�n�n devam edip etmeyece�ini kontrol etmek i�in bir Boolean de�i�keni ve kullan�c� ��k�� yapmazsa yaln�zca �al��an i� i�e ge�mi� bir blok kullan�r.
Break kullan�larak olu�turulmu� haline bakal�m bir de:
                    #include <iostream>

                    int main()
                    {
                        int count{ 0 }; // d�ng�n�n ka� kez tekrarland���n� say
                        while (true) // kullan�c� sonland�rana kadar d�ng�y� s�rd�r
                        {
                            std::cout << "Bu d�ng�den ��kmak i�in 'e' girin veya devam etmek i�in herhangi bir karakter girin: ";
                            char ch{};
                            std::cin >> ch;

                            if (ch == 'e')
                                break;

                            ++count;
                            std::cout << "Biz " << count << " kez tekrarlad�k\n";
                        }

                        return 0;
                    }

Bu versiyonda, tek bir break ifadesi kullanarak bir Boolean de�i�kenin kullan�m�n� (ve ama�lanan kullan�m�n�n ne oldu�unu ve nerede de�erinin de�i�ti�ini anlaman�n
gereklili�ini), bir else ifadesini ve i� i�e ge�mi� bir bloku �nledik.

continue ifadesi, bir ko�ul kar��land���nda d�ng� iterasyonlar�n� atlamak i�in en etkili �ekilde bir for-d�ng�s�n�n ba��nda kullan�l�r. Bu, i� i�e ge�mi� bir bloku
�nlememize olanak tan�yabilir.

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // e�er say� 4'e b�l�nm�yorsa...
                        if ((count % 4) != 0) // i� i�e ge�mi� blok
                        {
                                // Say�y� yazd�r
                                std::cout << count << '\n';
                        }
                    }

                    return 0;
                }


Bunun yerine bunu yazabiliriz:

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // e�er say� 4'e b�l�nebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue;

                        // i� i�e ge�mi� bir blok gerekli de�il

                        std::cout << count << '\n';
                    }

                    return 0;
                }

De�i�kenlerin say�s�n� en aza indirme ve i� i�e ge�mi� bloklar�n say�s�n� azaltma, kodun anla��l�rl���n� art�r�rken, bir break veya continue kullanman�n 
bu anla��l�rl��� bozmas�ndan daha etkilidir. Bu nedenle, break veya continue'nin �l��l� bir �ekilde kullan�lmas�n� kabul edilebilir buluyoruz.

*** BEST -> Loop mant���n�z� basitle�tirmek i�in break ve continue kullan�n.

Early return ( break ve continue ye benzer bir durum du hat�rlamak iyidir )
----------------------------------------------------------------------------
Erken d�n��lerin kullan�m�na dair benzer bir arg�man da return ifadeleri i�in yap�labilir. Bir fonksiyon i�indeki son ifade olmayan bir return ifadesine erken 
d�n�� denir. Bir�ok programc�, erken d�n��lerden ka��n�lmas� gerekti�ine inan�r. Fonksiyonu sadece bir return ifadesi olan ve bu ifadenin fonksiyonun alt�nda
bulundu�u bir yap�, basitlik ta��r - fonksiyonun arg�manlar� alaca��n�, uygulad��� mant��� ger�ekle�tirece�ini ve sapma olmadan bir sonu� d�nd�rece�inizi 
varsayabilirsiniz. Ekstra d�n�� ifadeleri, mant��� karma��kla�t�r�r.

Kar�� arg�man ise erken d�n��lerin fonksiyonunuzu hemen bitirmesine olanak tan�d���n�, bu sayede gereksiz mant�k okuma ve ko�ullu i� i�e ge�mi� bloklar� en aza 
indirdi�ini ve kodunuzu daha okunabilir hale getirdi�ini savunur.

Baz� geli�tiriciler orta bir yol izler ve erken d�n��leri yaln�zca fonksiyonun ba��nda parametre do�rulama (ge�ersiz arg�manlar�n yakalanmas�) i�in kullan�r, 
ard�ndan tek bir d�n�� ifadesi kullan�r.

Bizim duru�umuz erken d�n��lerin daha �ok yard�mc� oldu�u y�n�ndedir, ancak bunun prati�inde bir miktar sanat oldu�unu kabul ediyoruz.

*** BEST -> Erken d�n��ler, fonksiyonunuzun mant���n� basitle�tiriyorsa kullan�n.

                                                        8.12 Halts (Program�n�z� Erken Sonland�rma)
                                                        -------------------------------------------


Bu b�l�mde ele alaca��m�z ak�� kontrol ifadesi kategorisi, "halt"tir. Bir "halt", program� sonland�ran bir ak�� kontrol ifadesidir. C++'da, "halt"lar fonksiyonlar 
olarak uygulan�r (anahtar kelimeler olarak de�il), bu nedenle "halt" ifadelerimiz fonksiyon �a�r�lar� olacakt�r.

K�saca, bir program normal olarak sona erdi�inde neler oldu�unu �zetleyelim. main() fonksiyonu d�nd���nde (fonksiyonun sonuna ula�arak veya bir return ifadesi 
arac�l���yla), bir dizi farkl� �ey ger�ekle�ir.

�lk olarak, fonksiyondan ��k�ld��� i�in t�m yerel de�i�kenler ve fonksiyon parametreleri (normalde oldu�u gibi) yok edilir.

Sonras�nda, main() fonksiyonundan d�nen de�er (durum kodu) ile std::exit() adl� �zel bir fonksiyon �a�r�l�r. Peki std::exit() nedir?
std::exit() nedir 
-----------------

std::exit() i�levi, program�n normal bir �ekilde sona ermesine neden olan bir fonksiyondur. Normal sonlanma, program�n beklenen bir �ekilde sonland��� anlam�na
gelir. Normal sonlanma terimi, program�n ba�ar�l� olup olmad��� konusunda bir �ey ifade etmez (bu, durum kodu i�indir). �rne�in, kullan�c�n�n i�lem yapmak i�in
bir dosya ad� yazmas�n� bekledi�iniz bir program yaz�yorsan�z, e�er kullan�c� ge�erli olmayan bir dosya ad� yazarsa, program�n�z muhtemelen ba�ar�s�zl�k durumunu
g�stermek i�in bir s�f�r olmayan durum kodu d�nd�recektir, ancak hala normal bir sona erme olacakt�r.

std::exit(), bir dizi temizlik i�levini ger�ekle�tirir. �lk olarak, statik depolama s�resine sahip nesneler yok edilir. Ard�ndan, e�er dosyalar kullan�ld�ysa,,
ba�ka baz� dosya temizli�i yap�l�r. Son olarak, kontrol, std::exit() 'e iletilen arg�man olarak kullan�lan durum koduyla birlikte i�letim sistemine geri d�ner.


std::exit i a��k�a kullanma
---------------------------
std::exit() fonksiyonu, main() fonksiyonu sona erdi�inde dolayl� olarak �a�r�lsa da, std::exit() ayr�ca program�n normal olarak sona ermeden �nce program�
durdurmak i�in a��k�a �a�r�labilir. Bu �ekilde std::exit() �a�r�ld���nda, cstdlib ba�l�k dosyas�n� i�ermelisiniz.

��te std::exit() 'i a��k�a kullanman�n bir �rne�i:
                                                #include <cstdlib> // std::exit() i�in
                                                #include <iostream>

                                                void cleanup()
                                                {
                                                    // Gerekli her t�rl� temizlik i�in burada kod bulunabilir
                                                    std::cout << "cleanup!\n";
                                                }

                                                int main()
                                                {
                                                    std::cout << 1 << '\n';
                                                    cleanup();

                                                    std::exit(0); // program� sonland�r ve i�letim sistemine durum kodu 0 d�nd�r

                                                    // A�a��daki ifadeler hi�bir zaman �al��t�r�lmaz
                                                    std::cout << 2 << '\n';

                                                    return 0;
                                                }




bu program �u ��kt�y� verir :
                                                        1
                                                        cleanup!

Unutmay�n ki, std::exit() �a�r�s�ndan sonra gelen ifadeler �al��t�r�lmaz ��nk� program zaten sona ermi�tir.

Yukar�daki programda std::exit()'i main() fonksiyonundan �a��r�yor olsak da, std::exit() herhangi bir fonksiyondan �a�r�labilir ve program� o noktada sonland�rabilir.
std::exit()'i a��k�a �a��rma konusunda �nemli bir not: std::exit(), herhangi bir yerel de�i�keni (hem mevcut fonksiyonda hem de �a�r� y���n�ndaki di�er fonksiyonlarda)
temizlemez. Bu nedenle, genellikle std::exit() �a�r�s�ndan ka��n�lmas� daha iyidir.

*** UYARI -> std::exit() fonksiyonu, mevcut fonksiyondaki veya �a�r� y���n�ndaki di�er fonksiyonlardaki yerel de�i�kenleri temizlemez.

std::atexit()
-------------
��nk� std::exit(), program� hemen sonland�r�r, sonland�rmadan �nce manuel olarak baz� temizleme i�lemleri yapmak isteyebilirsiniz. Bu ba�lamda, temizleme,
veritaban� veya a� ba�lant�lar�n� kapatma, ayr�lm�� belle�i serbest b�rakma, bir g�nl��e bilgi yazma vb. gibi i�leri i�erir...

Yukar�daki �rnekte, temizleme g�revlerimizi ele almak i�in cleanup() fonksiyonunu �a��rd�k. Ancak, her exit() �a�r�s�ndan �nce manuel olarak bir temizleme 
fonksiyonunu �a��rmay� hat�rlamak, programc�ya ek bir y�k getirir.

Bu konuda yard�mc� olmas� i�in, C++, std::exit() arac�l���yla program sonland�r�ld���nda otomatik olarak �a�r�lacak bir i�levi belirtmenizi sa�layan std::atexit() 
i�levini sunar.

Bir �rnek:
                        #include <cstdlib> // std::exit() i�in
                        #include <iostream>

                        void cleanup()
                        {
                            // burada herhangi bir temizleme i�lemi kodu
                            std::cout << "temizleme!\n";
                        }

                        int main()
                        {
                            // std::exit() �a�r�ld���nda otomatik olarak cleanup() fonksiyonunu kaydet
                            std::atexit(cleanup); // not: �u an cleanup() fonksiyonunu �a��rm�yoruz, bu nedenle cleanup yerine cleanup() kullanm�yoruz

                            std::cout << 1 << '\n';

                            std::exit(0); // program� sonland�r ve i�letim sistemine durum kodu 0 d�nd�r

                            // A�a��daki ifadeler asla �al��maz
                            std::cout << 2 << '\n';

                            return 0;
                        }
bir �nceki programla ayn� ��kt�y� verir: 
                                      1
                                      temizleme!

Neden bunu yapmak istersiniz? Bu size bir temizleme i�levini belirleme �ans� tan�r (muhtemelen main fonksiyonunda) ve ard�ndan std::exit() fonksiyonunu a��k�a 
�a��rmadan �nce bu i�levi �a��rmay� hat�rlamak zorunda kalmazs�n�z.

��te std::atexit() ve cleanup fonksiyonu hakk�nda birka� not: �lk olarak, main() sona erdi�inde std::exit() �a�r�ld���ndan, bu durumda program�n ��k�� yapmas� 
std::atexit() taraf�ndan kaydedilen i�levleri �a��r�r. �kinci olarak, kaydedilen i�levin parametre almad���n� ve geri d�n�� de�eri olmad���n� belirtmelisiniz. 
Son olarak, std::atexit() kullanarak birden �ok temizleme i�levini kaydedebilirsiniz ve bunlar, kay�t s�ras�n�n tersine (en son kaydedilen ilk �a�r�lan) �a�r�l�r.


geli�mi� okuyucular i�in :
    �oklu i� par�ac�kl� programlarda, `std::exit()` �a��rmak program�n�z�n ��kmesine neden olabilir (��nk� `std::exit()`'i �a��ran i� par�ac���, di�er i� 
    par�ac�klar� taraf�ndan h�l� eri�ilebilecek olan statik nesneleri temizler). Bu nedenle, C++, `std::exit()` ve `std::atexit()` gibi benzer i�levlere
    benzer �ekilde �al��an `std::quick_exit()` ve `std::at_quick_exit()` adl� ba�ka bir ikili fonksiyon �iftini tan�tm��t�r. `std::quick_exit()`, program�
    normal bir �ekilde sonland�r�r, ancak statik nesneleri temizlemez ve ba�ka t�rden temizlik i�lemlerini yapabilir veya yapmayabilir. `std::at_quick_exit()`,
    `std::quick_exit()` ile sonland�r�lan programlar i�in `std::atexit()`'in ayn� rol�n� yerine getirir.

std::abort ve std::terminate
----------------------------
C++ iki ba�ka durdurma ile ilgili fonksiyon i�erir.

std::abort() fonksiyonu program�n�z�n anormal bir �ekilde sonlanmas�na neden olur. Anormal sonlanma, program�n ola�and��� bir �al��ma zaman� hatas� ile 
kar��la�mas� ve program�n �al��maya devam edememesi anlam�na gelir. �rne�in, 0'a b�lmeye �al��mak bir anormal sonlanmaya neden olacakt�r. std::abort() 
herhangi bir temizlik i�lemi yapmaz.

                    #include <cstdlib> // for std::abort()
                    #include <iostream>

                    int main()
                    {
                        std::cout << 1 << '\n';
                        std::abort();

                        // Sonraki ifadeler asla �al��t�r�lmaz.
                        std::cout << 2 << '\n';

                        return 0;
                    }

Bu b�l�mde (8.18 -- Assert ve static_assert) ilerleyen k�s�mlarda std::abort'un dolayl� olarak �a�r�ld��� durumlar� g�rece�iz.

std::terminate() fonksiyonu genellikle exceptions ile birlikte kullan�l�r (exceptions daha sonraki bir b�l�mde ele alaca��z). Her ne kadar std::terminate() 
a��k�a �a�r�labilecek olsa da, genellikle bir istisna i�lenmedi�inde (ve birka� ba�ka exceptions-related durumda) dolayl� olarak �a�r�l�r. 
Varsay�lan olarak, std::terminate() fonksiyonu std::abort() fonksiyonunu �a��r�r.

Ne zaman halt kullanmal�y�z ? 
-----------------------------
K�sa cevap  "neredeyse hi�bir zaman" olacakt�r. Yerel nesneleri imha etmek, C++'�n �nemli bir b�l�m�n� olu�turur (�zellikle s�n�flara ge�ti�imizde), 
yukar�da bahsedilen fonksiyonlardan hi�biri yerel de�i�kenleri temizlemez. Hata durumlar�yla ba�a ��kmak i�in exceptions, daha iyi ve g�venli bir mekanizmad�r.

*** BEST -> Yaln�zca main fonksiyonundan normal bir �ekilde d�nmenin g�venli bir yolu yoksa halt kullan�n. E�er exceptions lar� devre d��� b�rakmad�ysan�z,
            hatalar� g�venli bir �ekilde i�lemek i�in exceptions tercih edin.






*/
