// ch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Quizler yap�lm�� ama sanki bir atlama olmu� burada o y�zden chapter 2  yi tekrar i�licez ama quizleri yapmicaz sadece bi i�licez not tutcaz.
// �nemli bir konu. 

#include <iostream>
//#include "add.h"

//int add(int x, int y);

int main() {

    //std::cout << add(4, 3) << '\n'; -> OLDU KARDEEEE�
    /*
    Ayn� �ekilde ge�mi� ve di�er bilgilerimizle ayn� oldu�u i�in yazm�yorum. Sadece bilmedi�imi d���nd���m �eyleri yazacam kral. 
    C++ ba�l� fonksiyonlar� desteklemiyor yani bir fonksiyonun i�inde yeni bir fonksiyon tan�mlayamazs�n. 

    San�r�m bundan �nceki sefer de de okumu�uz ama sadece not almam���z. ��nk� �o�unu biliyoruz. Ho�umuza giden ayr�nt�lar� yazacaz sadece
    C++ 3 status code tan�ml�yor (main in d�n��� i�in) 0 , EXIT_SUCCESS, EXIT_FAILURE -> Ta��nabilirli�i artt�rmak a��s�ndan bunlar� kullanmak 
    laz�m. 
    
    D�n�� yapan fonksiyonlarda d�n�� yapmazsak tan�mlanamayan davran��lar ortaya ��kabilir. 
    Fonksiyonlarda var olup kullan�lmayan parametreler uyar� verir. 

    Yerel de�i�kenler.
    Yerel de�i�kenlerinizi, ilk kullanacaklar� yere m�mk�n oldu�unca yak�n bir �ekilde tan�mlay�n.

                                        FONKS�YONLARI ETK�L� KULLANMAK
    Yeni programc�lar�n kar��la�t��� en b�y�k zorluklardan biri (dilin ��renilmesi d���nda), ne zaman ve nas�l i�levleri etkili bir
    �ekilde kullanacaklar�n� anlamakt�r. ��te i�levler yazarken temel baz� kurallar:

    Bir programda birden fazla kez g�r�nen ifade gruplar� genellikle bir i�lev haline getirilmelidir. �rne�in, kullan�c�dan giri�leri ayn� 
    �ekilde birden fazla kez al�yorsak, bu, bir i�lev i�in harika bir adayd�r. Ayn� �ekilde bir �eyi birden fazla yerde ayn� �ekilde ��kar�yorsak,
    bu da bir i�lev i�in m�kemmel bir adayd�r.
    Belirli girdi ve ��kt�lar� olan kod, bir i�lev i�in iyi bir adayd�r (�zellikle karma��ksa). �rne�in, s�ralamak istedi�imiz bir 
    ��eler listemiz varsa, s�ralamay� yapmak i�in kod, yaln�zca bir kez yap�lsa bile harika bir i�lev olur. Giri� s�ralanmam�� liste,
    ��k�� s�ralanm�� listedir. Ba�ka bir olas� i�lev de 6 y�zl� bir zar�n at�lmas�n� sim�le eden kod olurdu. Mevcut program�n�z bunu
    yaln�zca bir kez kullanabilir, ancak i�lev haline getirirseniz, program�n�z� daha sonra geni�letirseniz veya gelecekteki bir programda
    yeniden kullan�ma haz�r olur.
    Bir i�lev genellikle bir (ve yaln�zca bir) g�revi yerine getirmelidir.
    Bir i�lev �ok uzun, karma��k veya anla��lmas� zor hale geldi�inde, birden �ok alt i�leve b�l�nebilir. Buna yeniden yap�land�rma denir.
    Genellikle C++ ��renirken, 3 alt g�revi i�eren programlar yazacaks�n�z:

    Kullan�c�dan giri�leri okuma
    Giri�lerden bir de�eri hesaplama
    Hesaplanan de�eri yazd�rma
    Basit programlar i�in (�rne�in 20 sat�r�n alt�nda), bunlar ya da t�m� main i�levinde yap�labilir. Ancak daha uzun programlar i�in
    (veya sadece prati�in bir par�as� olarak), her biri ayr� bir i�lev i�in iyi bir adayd�r.
    
    Yeni programc�lar genellikle bir de�eri hesaplama ve hesaplanan de�eri yazd�rma i�lemlerini tek bir i�levde birle�tirir. Bununla
    birlikte, bu i�levlerin "bir g�rev" kural�n� ihlal etti�ini unuturlar. Bir i�lev, bir de�eri hesaplamal� ve hesaplanan de�eri �a��ran
    ki�iye d�nd�rmeli ve hesaplanan de�eri yazmak gibi ne yap�laca��n� belirlemeli (�rne�in ba�ka bir i�leve �a�r�da bulunmak gibi) ve �a��ran
    ki�i hesaplanan de�eri yazmal�d�r.
    
    


    Programlar�n�zda derleme hatalar�n� veya uyar�lar�n� ��zerken, �nce listelenen ilk sorunu ��z�n ve ard�ndan tekrar derleyin.

                                                FORWARD DECLARATION
    Bir �n deklarasyon, tan�mlay�c�y� tan�mlamadan �nce tan�y�c� hakk�nda derleyiciye bilgi vermemizi sa�lar.

    Fonksiyonlar i�in, bu, derleyiciye fonksiyonun varl��� hakk�nda bilgi vermemize olanak tan�r, ancak fonksiyonun
    g�vdesini tan�mlamadan �nce. Bu �ekilde, derleyici, bir fonksiyonu arad���m�z� anlayacakt�r. Fonksiyonun nas�l 
    veya nerede tan�mland���n� hen�z bilmiyor olsa bile, fonksiyonu do�ru bir �ekilde �a��rd���m�z� kontrol etmek i�in kullanabilir.

    Bir fonksiyon i�in bir �n deklarasyon yazmak i�in, bir fonksiyon deklarasyon ifadesi (ayn� zamanda bir fonksiyon
    prototipi olarak da adland�r�l�r) kullan�r�z. Fonksiyon deklarasyonu, fonksiyonun d�n�� t�r�n�, ad�n� ve parametre
    t�rlerini i�erir ve bir noktal� virg�lle sona erer. Parametrelerin adlar� iste�e ba�l� olarak dahil edilebilir. 
    Fonksiyon g�vdesi deklarasyona dahil edilmez.
    


    Definition ve declaration ayn� �ey de�il t�m definition lar birer declarationdur fakat t�m declarationlar bir definition de�ildir.
    Definition	Implements a function or instantiates a variable.
    Definitions are also declarations.	void foo() { } // function definition
    int x; // variable definition
    Declaration	Tells compiler about an identifier and its associated type information.	void foo(); // function declaration
    int x; // variable declaration
    Pure declaration	A declaration that isn�t a definition.	void foo();


                                            ***** The one definition rule (ODR) ******
    
    Tek Tan�mlama Kural� (veya k�saca ODR), C++ i�inde iyi bilinen bir kurald�r. ODR'nin �� b�l�m� vard�r:

    Bir dosya i�inde, her bir fonksiyon, de�i�ken, t�r veya �ablon sadece bir tan�ma sahip olabilir. Farkl�
    kapsamlarda (�rne�in, farkl� i�levler i�inde tan�mlanan yerel de�i�kenler veya farkl� ad alanlar i�inde
    tan�mlanan i�levler) meydana gelen tan�mlar bu kural� ihlal etmez.

    Bir program i�inde, her bir fonksiyon veya de�i�ken yaln�zca bir tan�ma sahip olabilir. Bu kural, programlar�n 
    birden fazla dosyaya sahip olabilece�i i�in var. Linker'a g�r�nmeyen i�levler ve de�i�kenler bu kuraldan hari� 
    tutulur (bu, ders 7.6'da daha ayr�nt�l� olarak ele al�n�r).

    T�rler, �ablonlar, i� i�e i�levler ve i� i�e de�i�kenler, her bir tan�m�n ayn� oldu�u s�rece farkl� dosyalarda
    yinelemeli tan�mlara sahip olabilir. Bu konular�n �o�unu hen�z ele almad�k, bu nedenle �u an i�in bu konuyu dert
    etmeyin - ilgili oldu�unda tekrar ele alaca��z.

    ODR'nin 1. b�l�m�n� ihlal etmek, derleyicinin yeniden tan�mlama hatas� vermesine neden olur. ODR'nin 2. b�l�m�n�
    ihlal etmek, linkerin yeniden tan�mlama hatas� vermesine neden olur. ODR'nin 3. b�l�m�n� ihlal etmek, tan�ms�z davran��a neden olur.
                                            
    */

    /*
                                                PROJEYE DOSYA EKLEME
    Daha �nce forward declaration � anlat�rken mevzuya bi t�k�rt� i�in add() fonksiyonunu �rnek vermi�tik burada 
    farkl� bir dosya �zerinden bakacak olursak yani add() fonksiyonunu farkl� bir dosyaya koyduktan sonra �al��t�rsak
    acaba hata al�r m�y�z ? Cevap evet burada da ayn� cevab� al�r�z. Cpp add fonksiyonunun ne oldu�unu bilmiyor.
    Oysa derlemi�tik. 
    Unutmay�n, derleyici her dosyay� ayr� ayr� derler. Di�er kod dosyalar�n�n i�eri�ini bilmez veya �nceden
    derlenen kod dosyalar�nda g�rd��� �eyleri hat�rlamaz. Yani, derleyici fonksiyon add'�n tan�m�n� daha 
    �nce g�rm�� olabilir (e�er �nce add.cpp'yi derlediyse), ama hat�rlamaz.

    Bu s�n�rl� g�r�n�rl�k ve k�sa bellek bilin�li olarak tasarlanm��t�r ve birka� nedeni vard�r:

   1 Bir projenin kaynak dosyalar�n�n herhangi bir s�rayla derlenmesine izin verir.
   2 Bir kaynak dosyas�n� de�i�tirdi�imizde, yaln�zca o kaynak dosyas�n�n yeniden derlenmesi gerekir.
   3 Farkl� dosyalardaki tan�mlay�c�lar aras�ndaki isim �ak��malar�n�n olas�l���n� azalt�r.
    


    Sorunu yine forward declaration ile ��zd�k ama burada alman gereken key point �� 
    Bir tan�mlay�c� bir ifadede kullan�ld���nda, tan�mlay�c� kendi tan�m�na ba�l� olmal�d�r.

    E�er derleyici, derlenmekte olan dosyada tan�mlay�c� i�in ne bir forward declaration ne de bir tan�m� daha g�rmemi�se, 
    tan�mlay�c� kullan�ld��� noktada hata verecektir.

    E�er ayn� dosyada bir tan�m mevcutsa, derleyici tan�mlay�c�n�n kullan�m�n� tan�m�na ba�layacakt�r.

    Aksi takdirde, farkl� bir dosyada bir tan�m mevcutsa (ve ba�lay�c� i�in g�r�n�rse), ba�lay�c� tan�mlay�c�n�n kullan�m�n� tan�m�na ba�layacakt�r.
    Aksi takdirde, ba�lay�c� hata verecektir.
    
    

    Birden fazla dosya ile �al��maya ba�lad���n�zda i�lerin ters gidebilece�i pek �ok durum olabilir.
    Yukar�daki �rne�i denediyseniz ve bir hata ile kar��la�t�ysan�z, a�a��dakileri kontrol edin:

    E�er main.cpp dosyas�nda add i�levi i�in �nceden bildirimin eksik oldu�u bir derleyici hatas� al�rsan�z,
    add i�levi i�in �nceden bildirimi unuttu�unuz olabilir.
    E�er add i�levi tan�ms�z oldu�una dair bir ba�lay�c� hatas� al�rsan�z, �rne�in:
    unresolved external symbol "int __cdecl add(int,int)" (?add@@YAHHH@Z) referenced in function _main

    2a. ... muhtemelen add.cpp dosyas�n�n projenize do�ru �ekilde eklenmedi�i anlam�na gelir. Derledi�inizde,
    derleyicinin hem main.cpp hem de add.cpp'yi listeledi�ini g�rmelisiniz. E�er sadece main.cpp'yi g�r�yorsan�z,
    add.cpp kesinlikle derlenmiyor demektir. Visual Studio veya Code::Blocks kullan�yorsan�z, IDE'nin sol veya sa� 
    taraf�nda Solution Explorer/proje panelinde add.cpp'yi g�rmelisiniz. G�rm�yorsan�z, projenize sa� t�klayarak dosyay� 
    ekleyin ve ard�ndan yeniden derlemeyi deneyin. Komut sat�r�nda derliyorsan�z, komutunuzda main.cpp ve add.cpp'yi dahil 
    etmeyi unutmay�n.

    2b. ... add.cpp dosyas�n� yanl�� projeye eklemi� olma olas�l���n�z var.

    2c. ... dosyan�n derlenmemesi veya ba�lanmamas� i�in ayarland��� olas�l���n�z var. Dosya �zelliklerini kontrol edin
    ve dosyan�n derlenmesi/ba�lanmas� i�in yap�land�r�ld���ndan emin olun. Code::Blocks'da derleme ve ba�lant� ayr� onay
    kutular�d�r ve her ikisi de i�aretlenmelidir. Visual Studio'da "derlemeden hari� tut" se�ene�i, "hay�r" olarak ayarlanmal�
    veya bo� b�rak�lmal�d�r.

    Main.cpp dosyas�ndan "add.cpp" dosyas�n� #include etmeyin. Bu, �ni�lemcinin add.cpp i�eri�ini do�rudan main.cpp'ye 
    eklemesine neden olur ve bunlar� ayr� dosyalar olarak i�lememesini sa�lar.
    




    �ZET
    C++, her kaynak dosyas�n�n, di�er dosyalardaki bilgi hakk�nda hi�bir bilgi olmadan
    ba��ms�z olarak derlenebilecek �ekilde tasarlanm��t�r. Bu nedenle, dosyalar�n asl�nda
    hangi s�rayla derlendi�i �nemli olmamal�d�r.

    Nesne y�nelimli programlamaya girdi�imizde �ok say�da dosya ile �al��maya ba�layaca��z,
    bu y�zden �oklu dosya projelerini nas�l ekleyip derleyece�inizi anlad���n�zdan emin olman�z gereken bir zamand�r.

    Hat�rlatma: Her yeni kod (.cpp) dosyas� olu�turdu�unuzda, derlenmesi i�in projenize eklemeniz gerekecektir.


    */

    // std::cout << BasicMath::add(4, 3); bunu da denemi� olduk ba�ar�l�. 
    /*
                                                        INTRO TO PREPROCESSOR 
    Elbette! C++ derlemesi, belirli bir .cpp dosyas�n� tam olarak yazd���n�z gibi derlemek yerine, �nce bir �n i�leme (preprocessing) a�amas�ndan
    ge�er. Bu �n i�leme a�amas�nda, bir program olan �n i�lemci (preprocessor), kod dosyas�n�n metninde �e�itli de�i�iklikler yapar. Ancak �n i�lemci,
    asl�nda orijinal kod dosyalar�n� herhangi bir �ekilde de�i�tirmez. Yapt��� t�m de�i�iklikler, ge�ici bellekte veya ge�ici dosyalarda yap�l�r.

    �n i�leme a�amas�n�n amac�, derleme s�recini haz�rlamak ve kodun belirli gereksinimlerini kar��lamak i�in metni d�zenlemektir. �n i�lemci, �zel
    i�aretleme (directives) olarak adland�r�lan komutlar� ve metni i�ler. �rne�in, #include direktifi, ba�ka bir dosyadaki kodu mevcut dosyaya ekler.
    Bu, farkl� kod dosyalar�n� birle�tirmek i�in yayg�n olarak kullan�l�r.

    �n i�leme a�amas�, kodunun derlenmesinden �nce ger�ekle�ir ve kodunuzu derleyicinin kullanabilece�i bir �ekle d�n��t�r�r. Bu, programc�lara daha
    fazla esneklik ve metin i�leme yetene�i sa�lar. Derleme i�lemi s�ras�nda, derleyici bu �n i�lenmi� kodu kullanarak makine koduna �evirir ve
    nihayetinde �al��t�r�labilir bir program olu�turur.

    K�sacas�, �n i�leme, kodunuzu derlemeye haz�rlayan ve farkl� kod dosyalar�n� birle�tirmeye yard�mc� olan bir ara a�amad�r. Bu, C++'�n 
    geni�letilmi� yeteneklerini ve esnekli�ini sa�lar.
    
    Ge�mi�te �ni�lemci derleyiciden ayr� bir programd�, ancak modern derleyicilerde �ni�lemci do�rudan derleyicinin i�ine yerle�tirilebilir.
    
    �n i�lemcinin yapt��� i�lerin �o�u olduk�a s�k�c�d�r. �rne�in, yorumlar� (comments) kald�r�r ve her kod dosyas�n�n bir sat�r ile bitti�ini sa�lar.
    Ancak, �n i�lemcinin �ok �nemli bir rol� vard�r: #include direktiflerini i�lemesi (bu konuya birazdan daha fazla de�inece�iz).

    �n i�lemci, bir kod dosyas�n� i�ledikten sonra elde edilen sonuca "�eviri birimi"(translation unit) denir. Bu �eviri birimi, ard�ndan derleyici taraf�ndan derlenir.

    Bu �eviri birimi(translation unit), �n i�lemci taraf�ndan i�lenmi� haldeki kodun sonucunu temsil eder ve bu, derleyici taraf�ndan makine koduna 
    �evrilmek �zere kullan�l�r. Bu �ekilde, C++ kodu derlenmi� ve �al��t�r�labilir bir program haline gelir.

    �n i�leme, derleme ve ba�lama s�recinin tamam�na �eviri(translation) denir.
    
                                                            PREPROCESSOR DIRECTIVES
    Preprocessor �al��t���nda, kod dosyas� �zerinde yukar�dan a�a��ya do�ru tarar ve Preprocessor y�nergelerini arar.
    Preprocessor y�nergeleri(pre. directives)     (genellikle yaln�zca y�nergeler(directives) olarak adland�r�l�r) # sembol� ile ba�lay�p 
    bir sat�r sonuyla (noktal� virg�l DE��L) biter. Bu y�nergeler, Preprocessor belirli metin i�leme g�revlerini ger�ekle�tirmesini 
    s�yleyen talimatlar i�erir. �n i�leyici, C++ s�zdizimini anlamaz -- bunun yerine y�nergeler kendi s�zdizimlerine sahiptir
    (baz� durumlarda C++ s�zdizimine benzeyen ve baz� durumlarda benzemeyen).
    

    Zaten g�rd�n�z #include y�nergesini (genellikle #include <iostream>) kullan�rken. Bir dosyay� #include etti�inizde, �n i�leyici #include 
    y�nergesini dahil edilen dosyan�n i�eri�iyle de�i�tirir. Dahil edilen i�erik �n i�lemden ge�er (bu, ba�ka #include'lar�n daha fazla �n 
    i�leme tabi tutulmas�na neden olabilir), ard�ndan dosyan�n geri kalan� �n i�lemden ge�er.
    
    
    
     �n i�leyici (preprocessor), belirli bir kod dosyas�n� ve bu dosya i�inde kullan�lan t�m #include ile dahil edilen i�erikleri 
     i�ledikten sonra elde edilen sonuca "�eviri birimi" (translation unit) denir. Bu �eviri birimi, derlenmek �zere derleyiciye 
     g�nderilen i�lenebilir kodun son halini temsil eder. �eviri birimi, �n i�leme komutlar�n�n uyguland���, t�m i�eriklerin bir 
     araya getirildi�i ve sonunda derlemeye uygun hale getirilen bir dosyay� ifade eder.

    Bu �eviri birimleri, derleme i�lemi s�ras�nda derleyici taraf�ndan i�lenir ve makine koduna �evrilir, b�ylece �al��t�r�labilir
    bir program olu�turulur. Bu, C++ dilinde birden fazla dosyan�n bir araya getirilmesi ve ayr� ayr� derlenmesine olanak tan�r.
    Yani �eviri birimleri include dosyalar� dahil kod dosyas�ndaki kodlar�n hepsini i�erir.

                                                MACRO TANIMLAR
    #define y�nergesi, bir makro olu�turmak i�in kullan�labilir. C++ dilinde, bir makro, girdi metnin nas�l d�n��t�r�ld���n� belirleyen bir kurald�r.

    �ki temel t�rde makro bulunur: nesne benzeri makrolar ve i�lev benzeri makrolar.

    ��lev benzeri makrolar, i�levlere benzer �ekilde davran�r ve benzer bir ama� ta��r. Genellikle kullan�mlar� g�vensiz kabul edilir ve 
    neredeyse yapabildikleri her �ey, normal bir i�levle yap�labilir.

    Nesne benzeri makrolar iki �ekilde tan�mlanabilir:

    #define tan�mlay�c�
    #define tan�mlay�c� yerine_ge�me_metni

    �lk tan�m�n yerine ge�me metni yokken, ikinci tan�mda yerine ge�me metni vard�r. Bu, �n i�leyici y�nergeleri oldu�u i�in her iki 
    bi�im de noktal� virg�lle bitmez.

    Makro i�in kullan�lan tan�mlay�c�, normal tan�mlay�c�larla ayn� adland�rma kurallar�n� kullan�r: harf, rakam ve alt �izgi kullan�labilir, 
    bir rakamla ba�layamaz ve alt �izgi ile ba�lamamal�d�r. Geleneksel olarak, makro adlar� genellikle b�y�k harfle yaz�l�r ve alt �izgilerle ayr�l�r.
    

    ** Nesne benzeri makrolar.
    * #define MY_NAME "Alex"

    int main()
    {
    std::cout << "My name is: " << MY_NAME << '\n'; -> std::cout << "My name is: " << "Alex" << '\n'; E D�N��T�R�YOR 
    Substitution text ile birlikte olan obje benzeri makrolar (C'de) literallere isim atama ama�l� kullan�l�rd�.
    Ancak bu art�k C++'da gerekli de�ildir, ��nk� C++'da daha iyi y�ntemler bulunmaktad�r. Art�k object-like macros 
    with substitution text, genellikle yaln�zca eski kodlarda g�r�l�r.
    

    * Bir de substitution text olmayan object-like makrolar var onlarda text in yerine hi� bir �ey konmadan yap�lanlar. 
    * �ok gereksiz gibi geliyor fakat textli olana g�re kabul edilebilir kabul edilir.
    
    ** Ko�ullu Derleme 
    * Ad�ndan da belli ko�ula ba�l� olarak baz� kodlar�n derlenmesini sa�layan bu �zelli�imiz i�in bir �ok conditional compilation directive
    * i var ama ben sadece #ifdef #ifndef #endif i ��rencem.
    * Ko�ullu derleme �n i�lem y�nergeleri, belirli ko�ullara ba�l� olarak bir kod par�as�n�n derlenip derlenmeyece�ini kontrol etmek i�in kullan�l�r. Bu ba�lamda, en yayg�n kullan�lan �� y�nergeden bahsedece�iz: #ifdef, #ifndef ve #endif.

#ifdef �n i�lem y�nergesi belirli bir tan�mlay�c�n�n �nceden #define ile tan�mlan�p tan�mlanmad���n� kontrol eder. E�er tan�mlay�c� daha �nce tan�mland�ysa, #ifdef ve e�le�en #endif aras�ndaki kod derlenir. Tan�mlanmam��sa, kod g�rmezden gelinir.
��te bunu g�steren bir �rnek program:

    
    #include <iostream>
    
    #define ENABLE_FEATURE  // ENABLE_FEATURE tan�mlay�c�s�n� tan�mla
    
    int main() {
    #ifdef ENABLE_FEATURE  // ENABLE_FEATURE tan�mlay�c�s� tan�mland� m� diye kontrol et
        std::cout << "�zellik etkin." << std::endl;
    #else
        std::cout << "�zellik devre d���." << std::endl;
    #endif
    
        return 0;
    }
    Bu �rnekte, ENABLE_FEATURE �nceden tan�mland��� i�in #ifdef ENABLE_FEATURE ve #endif aras�ndaki kod derlenecektir.
    * ifndef de zaten bunun tersi e�er #define ile tan�mlanmam��sa blok �al��t�r�l�r. if else yap�s� ile ayn�d�r sadece c++ syntax�na daha �ok benzer demek o kadar
    
                                                                    #if 0 
    #if 0
        ��
        ���
        ����
    #endif       -> Burad if 0 ile endif aras�nda kalan yer derlenmez �oklu yorum sat�r� gibi �al���r yani if ile endif aras�ndaki alan derlenmez.
                    Burada o alan�n derlenmesini istersek e�er #if 0 -> #if 1 olarak de�i�tirmemiz yeterli olacakt�r. 
                -> �oklu yorum sat�r�n�n oldu�u yerde tekrar bir �oklu yorum sat�r� yapamayaca��m�z i�in bize uygun yol sa�lar. 
                �rne�in:*/
                      #if 0 // Don't compile anything starting here
                             std::cout << "Bob\n";
                            /* Some
                             * multi-line
                             * comment here
                             */
                             std::cout << "Steve\n";
                      #endif // until this point
    /*
        #define PRINT_JOE
                                ---> Burda PRINT_JOE hi�bir �ey ile de�i�tirilmez. Yani Object-like macrolar di�er directives leri etkilemez.
        #ifdef PRINT_JOE
    
    *   Program sonunda t�m preprocessorler ��z�mlenir ve ��kar�l�r ��nk� derleyici bunlarla ne yapaca��n� bilemez.
    */
    /*
                                                                The scope of #defines
    * Yer farketmeksizin tan�mland�klar� yerden dosyan�n sonuna kadar kapsam alan�na sahiptirler. Ayn� projede bile di�er dosyalar� etkilemezler.
    
                                                                Header ( Ba�l�k ) Dosyalar�
    Ba�l�k dosyalar� tan�mlamalar� bir dosyaya koyup onlar� istedi�imiz yerde import ederek kullanabilece�imiz bir dosyaya koymakt�r. Bu bizi bir 
    �ok yazma i�inden kurtar�r. Hele ki �ok dosyal� sistemlerde �ok i�e yarar bir �eydir :)


   **BEST Ba�l�k dosyalar�n�z� adland�r�rken .h sonekini tercih edin (projeniz zaten ba�ka bir kurala uymuyorsa).

   **BEST Bu, C++ ba�l�k dosyalar� i�in uzun s�redir devam eden bir kurald�r ve �o�u IDE, di�er se�eneklere g�re hala varsay�lan olarak .h'dir.

   **BEST Bir ba�l�k dosyas� bir kod dosyas�yla e�le�tirilmi�se (�rne�in, add.h ile add.cpp), her ikisinin de ayn� temel ad� (add) olmas� gerekir.
    
    Bu ba�l�k dosyas�n� main.cpp'de kullanmak i�in, onu #include etmemiz gerekir (k��eli ayra�lar de�il, t�rnak i�aretleri kullanarak). ADD.CPP �rne�inde,
    oldu�u gbi #include "add.h" yaparak ekleriz (kendi yazd�klar�m�z�)

    **Kaynak dosyalar, e�le�tirilmi� ba�l�k dosyalar�n� (varsa) #include etmelidir. 
    * B�yle zamanlarda diyelim ki elinde add.h add.cpp ve main.cpp olsun burada add.h i hem add.cpp hem de main.cpp de include etmen olabilecek hatalar� 
    * linking time da de�il de compile time da g�rmeni sa�lar. Hem complexity azal�r hem debugging h�zlan�r bu best practice dikkat et yani. 
    


    *** CPP KAYNAK DOSYALARINI INCLUDE ETMEKTEN KA�INMALIYIZ NEDENLER� ?
    * �sim �ak��malar�n� �nler: Birden fazla kaynak dosyas� ayn� isimli i�levleri veya de�i�kenleri tan�mlad���nda, 
    isim �ak��malar� meydana gelebilir. Ba�l�k dosyalar�, bu t�r isim �ak��malar�n� �nlemek i�in gerekli i�levleri ve 
    de�i�kenleri tan�mlamay� kolayla�t�r�r.

    ODR sorunlar�n� �nler: Bir kaynak dosyas�n�n birden fazla kaynak dosya taraf�ndan i�e aktar�lmas�, bir tan�mlama
    kural� ihlali (ODR) sorunlar�na neden olabilir. Ba�l�k dosyalar�, bu t�r sorunlar� �nlemek i�in gerekli �n bildirimleri sa�lar.

    Derlemeyi h�zland�r�r: Kaynak dosyalar� genellikle ba�l�k dosyalar�na g�re daha s�k de�i�ir. Kaynak dosyas�n� 
    de�i�tirdi�inizde, yaln�zca o kaynak dosyas�n�n yeniden derlenmesi gerekir. Ba�l�k dosyalar� daha az de�i�ti�inden,
    di�er kaynak dosyalar�n�n tekrar derlenmesi gerekmeyebilir.

    Geleneklere uygunluk: C++ topluluklar� ve projeler genellikle ba�l�k dosyalar�n�n kullan�lmas�n� te�vik eder ve bu,
    projenizin di�er geli�tiriciler veya ekibiniz i�in daha anla��l�r ve bak�m� daha kolay hale getirir.
    

                                                            SORUN ��ZME 
    Bu konudaki sorunlar �u iki madde ile bir �o�unu ��zebiliriz :D
    "add.h" Bulunamayan Derleyici Hatas�:

    Ba�l�k dosyas�n�n ger�ekten "add.h" ad�n� ta��d���ndan emin olun. Dosyan�n yanl�� bir �ekilde 
    adland�r�lm�� olmad���na, �rne�in "add" (uzant�s�z) veya ".txt" veya ".hpp" gibi farkl� bir uzant�yla adland�r�lm�� olmad���na dikkat edin.
    "add.h" dosyas�n�n di�er kaynak kod dosyalar�n�zla ayn� dizinde bulundu�undan emin olun.
    "add" Fonksiyonunun Tan�mlanmad��� Ba�lay�c� Hatas�:

    "add.cpp" dosyas�n� projenize ekledi�inizden emin olun, b�ylece "add" fonksiyonu ve tan�m� program�n�za ba�lanabilir.
    Bu ad�mlar� takip ederek, projenizdeki ba�l�k dosyalar� ve kaynak dosyalar�n�n varl��� ve dahil edilmesiyle ilgili
    yayg�n sorunlar� ��zebilirsiniz.




    Muhtemelen iostream i�in k��eli parantezler ve add.h i�in �ift t�rnaklar�n neden kullan�ld���n� merak ediyorsunuzdur.
    Ayn� ada sahip ba�l�k dosyalar�n�n birden fazla dizinde bulunma olas�l��� vard�r. K��eli parantezleri veya �ift t�rnaklar� 
    kullanmam�z, �n i�lemciye hangi ba�l�k dosyalar�n� aramas� gerekti�i konusunda bir ipucu verir.

    K��eli parantezleri kulland���m�zda, �n i�lemciye bu ba�l�k dosyas�n�n kendimiz taraf�ndan yaz�lmad���n� s�yl�yoruz. 
    �n i�lemci, ba�l��� yaln�zca i�erik dizinleri taraf�ndan belirtilen dizinlerde arayacakt�r. ��erik dizinleri, projeniz/IDE 
    ayarlar�n�z�n bir par�as� olarak yap�land�r�l�r ve genellikle derleyiciniz ve/veya i�letim sistemi ile birlikte gelen ba�l�k
    dosyalar�n� i�eren dizinlere varsay�lan olarak ayarlan�r. �n i�lemci, ba�l�k dosyas�n� projenizin kaynak kodu dizininde aramayacakt�r.

    �ift t�rnaklar� kulland���m�zda, �n i�lemciye bu ba�l�k dosyas�n�n kendimiz taraf�ndan yaz�ld���n� s�yl�yoruz. �n i�lemci, 
    �nce mevcut dizinde ba�l�k dosyas�n� arar. E�er uygun bir ba�l�k bulamazsa, ard�ndan i�erik dizinlerinde arama yapacakt�r.

    *******KURAL 
    * Yazd���n�z veya ge�erli dizinde bulunmas� beklenen ba�l�k dosyalar�n� dahil etmek i�in �ift t�rnak i�areti kullan�n. 
    Derleyicinizle, i�letim sisteminizle veya sisteminizin ba�ka bir yerine y�kledi�iniz ���nc� taraf kitapl�klarla birlikte
    gelen ba�l�klar� dahil etmek i�in a��l� parantezleri kullan�n.


    ****
    *  standart k�t�phane ba�l�k dosyalar�n� (#include <iostream> gibi) kullan�rken .h uzant�s�n� kullanmamam�z gerekti�i.
    Ancak, kullan�c� taraf�ndan olu�turulan (user-defined) ba�l�k dosyalar� i�in (.h uzant�l� olanlar), .h uzant�s�n� kullanmam�z 
    gerekti�i belirtiliyor. Yani standart k�t�phane ba�l�k dosyalar� i�in .h uzant�s� tercih edilmez, ama kullan�c� tan�ml�
    ba�l�k dosyalar� i�in .h uzant�s� kullan�l�r.



                                             BA�KA D�Z�NDE BULUNAN BA�LIK DOSYASINI EKLEMEK

    Bunu yapman�n (k�t�) bir yolu, #include sat�r�n�n bir par�as� olarak eklemek istedi�iniz ba�l�k dosyas�na g�reli bir yol eklemektir.
    �rne�in:

    #include "ba�l�klar/myHeader.h"
    #include "../moreHeaders/myOtherHeader.h"
    Bu derlenecek olsa da (dosyalar�n ilgili dizinlerde mevcut oldu�u varsay�l�rsa), bu yakla��m�n dezavantaj�, dizin yap�n�z� kodunuza
    yans�tman�z� gerektirmesidir. Dizin yap�n�z� g�ncellerseniz kodunuz art�k �al��maz.

    Daha iyi bir y�ntem, derleyicinize veya IDE'nize, ba�ka bir konumda bir grup ba�l�k dosyan�z�n bulundu�unu, b�ylece bunlar� ge�erli 
    dizinde bulamad���nda oraya bakaca��n� s�ylemektir. Bu genellikle IDE proje ayarlar�n�zda bir i�erme yolu veya arama dizini ayarlayarak
    yap�labilir.


    ** Hocam�z bu ayarlar� g�stermi�. Hani k�t� bir mantalite oldu�u i�in uzatmicam burada kals�n. 
                
                                                BA�KA BA�LIK DOSYALARINI ��EREN BA�LIK DOSYALARI
    Bir ba�l�k dosyas�n�n farkl� bir ba�l�k dosyas�nda bulunan bir bildirime veya tan�ma ihtiya� duymas� yayg�nd�r. Bu nedenle, ba�l�k 
    dosyalar� s�kl�kla di�er ba�l�k dosyalar�n� da i�erir.

    Kod dosyan�z #include ilk ba�l�k dosyas�n� i�erdi�inde, ilk ba�l�k dosyas�n�n i�erdi�i di�er ba�l�k dosyalar�n� da (ve bunlar� i�eren
    t�m ba�l�k dosyalar�n� vb.) al�rs�n�z. Bu ek ba�l�k dosyalar�na bazen ge�i�li i�ermeler(transitive includes) ad� verilir, ��nk� bunlar a��k bir �ekilde
    de�il �rt�l� olarak dahil edilir.


    ** BEST**Her dosya, derlemesi gereken t�m ba�l�k dosyalar�n� a��k�a #include etmelidir. Di�er ba�l�klardan ge�i�li olarak eklenen ba�l�klara
    g�venmeyin.
    
    BURADA ne demek istiyor. Mesela a.hpp yi include ediyorum diyelim ve a.hpp nin i�inde de iostream k�t�phanesini include etti�imi varsayal�m.
    Bu durumda iostream i main de kullanacaksam a.hpp den ayr� olarak tekrar include etmemin daha iyi olaca��ndan m� bahsediyor. 

                                                 BA�LIK DOSYALARININ SIRALAMASI
   
   
    Ba�l�k dosyalar�n�z do�ru �ekilde yaz�lm��sa ve ihtiya� duyduklar� her �eyi #include ediyorsa, dahil etme s�ras�n�n bir �nemi olmamal�d�r.

    �imdi a�a��daki senaryoyu d���n�n: Diyelim ki ba�l�k dosyas� A, ba�l�k dosyas� B'den gelen bildirimlere ihtiya� duyar, ancak B'yi dahil 
    etmeyi unutur. Kod dosyam�zda, ba�l�k B'yi ba�l�k A'dan �nce dahil edersek, kodumuz hala derlenecektir! Bu, derleyici taraf�ndan,
    bu bildirimlere ihtiya� duyan kodu derlemeden �nce B'den t�m bildirimleri derleyece�i i�in �al���r.

    Ancak �nce ba�l�k A'y� dahil edersek, derleyici bu sefer �ikayet edecektir ��nk� A'dan gelen kodu derlerken hen�z B'den gelen bildirimleri 
    g�rmemi�tir. Asl�nda bu daha tercih edilir ��nk� hata y�zeye ��kar�lm�� ve ard�ndan d�zeltilmesi gereken bir hata tespit edilir.
   
   
    Eksik i�eriklerin derleyici taraf�ndan i�aretlenme olas�l���n� en �st d�zeye ��karmak i�in #includes'�n�z� a�a��daki gibi s�ralay�n:

    E�le�tirilmi� ba�l�k dosyas�
    Projenizdeki di�er ba�l�klar
    3. taraf kitapl�k ba�l�klar�
    Standart kitapl�k ba�l�klar�
    Her grupland�rman�n ba�l�klar� alfabetik olarak s�ralanmal�d�r (3. taraf kitapl�k belgeleri size aksini s�ylemedi�i s�rece).

    Bu �ekilde, kullan�c� tan�ml� ba�l�klar�n�zdan birinde 3. taraf kitapl�k veya standart kitapl�k ba�l��� i�in #include eksikse, derleme hatas�na
    neden olma olas�l��� daha y�ksektir, b�ylece d�zeltebilirsiniz.


    Ba�l�k dosyalar� i�in en iyi uygulamalar

    ��te ba�l�k dosyalar� olu�tururken ve kullan�rken baz� �neriler.

    Her zaman ba�l�k koruyucular�n� i�ermelisiniz (sonraki ders).
    Ba�l�k dosyalar�nda de�i�kenleri ve i�levleri tan�mlamay�n (�u an i�in).
    Bir ba�l�k dosyas�na, ili�kilendirildi�i kaynak dosyan�n ad�n� verin (�rne�in, grades.h ile grades.cpp e�le�tirilmi�tir).
    Her ba�l�k dosyas� belirli bir g�reve sahip olmal� ve m�mk�n oldu�unca ba��ms�z olmal�d�r. �rne�in, A i�levselli�i ile ilgili
    t�m bildirimleri A.h'ye ve B i�levselli�i ile ilgili t�m bildirimleri B.h'ye yerle�tirebilirsiniz. Bu �ekilde, daha sonra sadece 
    A ile ilgilenseniz bile A.h'yi i�erebilir ve B ile ilgili olanlar hakk�nda hi�bir �ey almak zorunda kalmazs�n�z.
    Kulland���n�z kod dosyalar�ndaki i�levselli�i gerektiren ba�l�klara dikkat edin.
    Yazd���n�z her ba�l�k dosyas� kendi ba��na derlenmelidir (ihtiya� duydu�u her ba��ml�l��� #include etmelidir).
    Sadece ihtiyac�n�z olan� #include edin (her �eyi sadece yapabildi�iniz i�in #include etmeyin).
    .cpp dosyalar�n� #include etmeyin.
    Bir �eyin ne yapt���n� veya nas�l kullan�laca��n� belirten belgelemeyi ba�l��a koymay� tercih edin. Orada daha olas� g�r�n�r.
    Bir �eyin nas�l �al��t���n� a��klayan belgeleme kaynak dosyalarda kalmal�d�r.


                                                Header guards
    







    */

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    return 0;
}
