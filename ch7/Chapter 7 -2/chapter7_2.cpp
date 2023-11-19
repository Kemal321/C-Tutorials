#include <iostream>

int main()
{
    /*
    Di�eri �ok uzam��t� o y�zden ikinci bir dosyaya ge�tim. 
                                                          7.12 - Using tan�mlamas� ve using direktifi
    K�sa bir tarih dersi

    C++'�n namespace deste�i olmadan �nce, �u anda std namespace i�inde bulunan t�m isimler global namespace i�indeydi. Bu durum, program tan�mlar�
    ile standart k�t�phane tan�mlar� aras�nda �ak��malara yol a�t�. Bir C++ s�r�m� alt�nda �al��an programlar, daha yeni bir C++ s�r�m� ile isim
    �ak��mas�na neden olabilir.

    1995 y�l�nda, namespace'ler standartla�t�r�ld� ve standart k�t�phanedeki t�m i�levsellik global namespace'ten ��kart�larak namespace std i�ine 
    ta��nd�. Bu de�i�iklik, hala std:: olmadan isimleri kullanan eski kodlar� bozdu.

    B�y�k bir kod taban�nda �al��an herkesin bildi�i gibi, kod taban�na yap�lan herhangi bir de�i�iklik (ne kadar k���k olursa olsun) program� bozmak 
    riskini ta��r. Art�k std namespace i�ine ta��nan her ismi std:: �neki ile kullanmaya g�ncelleme yapmak b�y�k bir riskti. Bir ��z�m talep edildi.

    G�n�m�ze geldi�imizde, e�er standart k�t�phaneyi �ok kullan�yorsan�z, standart k�t�phaneden kulland���n�z her �eyin �n�ne std:: yazmak
    tekrarlay�c� hale gelebilir ve baz� durumlarda kodunuzu okumay� zorla�t�rabilir.

    C++, bu sorunlara ��z�m olarak using ifadeleri �eklinde baz� ��z�mler sunar.

    Ancak �nce, iki terimi tan�mlayal�m.

    ** Nitelenmi� ve nitelenmemi� isimler

    Bir isim nitelenmi� veya nitelenmemi� olabilir.Bir nitelenmi� isim, bir ili�kilendirilmi� kapsam i�eren bir isimdir.
    Genellikle, isimler bir namespace ile kapsaml� olarak "::" kapsam ��z�m operat�r� kullan�larak nitelenir. �rne�in:
    std::cout // tan�mlay�c� cout, namespace std ile nitelendirilmi�tir
            ::foo // tan�mlay�c� foo, global namespace ile nitelendirilmi�tir
            �leri d�zey okuyucular i�in:

    Bir isim ayr�ca "::" kapsam ��z�m operat�r� kullan�larak bir s�n�f ad� taraf�ndan nitelendirilebilir veya bir s�n�f 
    nesnesi taraf�ndan �ye se�im operat�rleri (veya . veya ->) kullan�larak nitelendirilebilir. �rne�in:
            class C; // bir s�n�f

            C::s_member; // s_member, C s�n�f� taraf�ndan nitelendirilmi�tir
            obj.x; // x, s�n�f nesnesi obj taraf�ndan nitelendirilmi�tir
            ptr -> y; // y, s�n�f nesnesi i�aret�isi ptr taraf�ndan nitelendirilmi�tir
    Nitelenmemi� bir isim, bir kapsam belirleyici i�ermeyen bir isimdir. �rne�in, cout ve x nitelenmemi� isimlerdir, 
    ��nk� bunlar ili�kilendirilmi� bir kapsam i�ermez.
    Bu terimler, bir ismin kullan�ld��� yerdeki kapsama ve ba�lama ba�l� olarak anlam de�i�tirebilir. Bir terimin kullan�m 
    ba�lam�n� anlamak, nitelenmi� veya nitelenmemi� olarak adland�r�lmas�na yard�mc� olacakt�r.

    * Using Declaration �
    
    Tekrarlayan std:: ifadelerini azaltman�n bir yolu, using-declaration ifadesini kullanmakt�r. Using-declaration, bir nitelenmi� ismin
    (kapsaml� olmayan) bir takma ad�(std::cout -> cout a takma ad diyor yani ) olarak kullan�lmas�na izin verir. �rnek olarak hello world program�nda 
    hat�rlars�n, using std::cout; ve using std::endl; ifadeleri kullan�larak, cout ve endl'yi do�rudan std:: �n eki olmadan kullanabiliriz. 
    Bu, kodun daha okunabilir olmas�na ve std:: ifadelerinin tekrar�n�n azalmas�na olanak tan�r.
    
-------------------------------------------------------------------------------------------------------------------------------------------------------
�rnek:
    #include <iostream>

    int main()
    {
       using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
       cout << "Hello world!\n"; // so no std:: prefix is needed here!

       return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
    Kullan�lan using-declaration using std::cout;, derleyiciye, std isim alan�ndan cout nesnesini kullanaca��m�z� bildirir. Bu nedenle,
    her seferinde cout g�rd���nde, std::cout anlam�na geldi�ini varsayacakt�r. E�er std::cout ile cout'un ba�ka bir kullan�m� aras�nda 
    bir isim �ak��mas� varsa, std::cout tercih edilecektir.
    
    Bu basit �rnekte �ok fazla �aba tasarrufu sa�lamaz, ancak bir i�lev i�inde cout'u bir�ok kez kullan�yorsan�z, using-declaration kodunuzu 
    daha okunabilir hale getirebilir. Unutmay�n ki her isim i�in ayr� bir using-declaration'a ihtiyac�n�z olacak (�rne�in, std::cout i�in bir
    tane, std::cin i�in bir tane vb.).

    Bu y�ntem, std:: �neki kullanmaktan daha a��k olmamas�na ra�men, genellikle g�venli ve kabul edilebilir olarak de�erlendirilir (bir fonksiyon
    i�inde kullan�ld���nda).

    * Using Y�nergesi
    
    ��leri basitle�tirmenin ba�ka bir yolu da bir using y�nergesi kullanmakt�r. Biraz basitle�tirecek olursak, bir using y�nergesi,
    bir ad alan�ndaki t�m tan�mlay�c�lar�, using y�nergesinin kapsam�na aktar�r.


    For advanced readers

    Teknik nedenlerden dolay�, using-directive'ler asl�nda isimleri( namespacedeki isimler yani ) mevcut kapsama dahil etmez - bunun yerine isimleri d��
    bir kapsama dahil eder (hangi d�� kapsam�n se�ildi�i hakk�nda daha fazla ayr�nt�ya https://quuxplusone.github.io/blog/ buradan ula��labilir). 
    Bununla birlikte, bu isimlere d�� kapsamdan eri�ilemez - yaln�zca using-directive'in kapsam�ndan (veya i� i�e bir kapsamdan) yap�lan nitelenmemi�
    (�neklenmemi�) aramalar yoluyla eri�ilebilirler.
    Pratik etkisi, (i� i�e ge�mi� ad alanlar� i�inde birden �ok using-directive i�eren baz� tuhaf durumlar d���nda), using-directive'lerin 
    isimlerin mevcut kapsama dahil edilmi� gibi davrand���d�r. ��leri basit tutmak i�in, isimlerin mevcut kapsama dahil edildi�i basitle�tirmesi
    alt�nda devam edece�iz.
-------------------------------------------------------------------------------------------------------------------------------------------------------
�rne�in revizesi:
    #include <iostream>

    int main()
    {
       using namespace std; // this using directive tells the compiler to import all names from namespace std into the current
                            // namespace without qualification
       cout << "Hello world!\n"; // so no std:: prefix is needed here
       return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
    
    Using-directive, using namespace std; derleyiciye std ad alan�ndaki t�m isimleri mevcut kapsama (bu durumda main() fonksiyonunun kapsam�na) 
    dahil etmesini s�yler. Ard�ndan nitelenmemi� cout tan�mlay�c�s�n� kulland���m�zda, bu, i�e aktar�lan std::cout'a ��z�mlenecektir.

    Using-directive'ler, ad alan� �ncesi eski kod tabanlar� i�in bir ��z�m sunar ve standart kitapl�k i�levselli�i i�in nitelenmemi� isimler 
    kullan�ld���nda, her nitelenmemi� ismi nitelenmi� bir isme manuel olarak g�ncelleme zorunlulu�unu ortadan kald�r�r (bu riskliydi). Bunun yerine,
    her dosyan�n ba��na tek bir using-directive (using namespace std;) yerle�tirilebilir ve std ad alan�na ta��nm�� t�m isimler hala nitelenmemi� 
    olarak kullan�labilir.
       
    * Using y�nergeleriyle ilgili sorunlar (di�er bir deyi�le neden "namespace std kullanmaktan ka��nman�z gerekir?")
    
    Modern C++'ta, using-directive'ler genellikle riskle kar��la�t�r�ld���nda (baz� yazma i�lemi tasarrufu d���nda) pek bir fayda sa�lamaz.
    ��nk� using-directive'ler bir ad alan�ndaki t�m isimleri i�eri aktard���ndan (potansiyel olarak asla kullanmayaca��n�z bir�ok ismi i�erir),
    isim �ak��malar�n�n olma olas�l��� �nemli �l��de artar (�zellikle std ad alan�n� i�e aktar�rsan�z).
-------------------------------------------------------------------------------------------------------------------------------------------------------
A��klama ama�l� olarak, using-directive'lerin belirsizli�e neden oldu�u bir �rne�e bakal�m:
    #include <iostream>

    namespace a
    {
	    int x{ 10 };
    }

    namespace b
    {
	    int x{ 20 };
    }

    int main()
    {
	    using namespace a;
	    using namespace b;

	    std::cout << x << '\n';

	    return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
Yukar�daki �rnekte, derleyici main i�indeki x'in a::x'e mi yoksa b::x'e mi at�fta bulundu�unu belirleyemez. Bu durumda, "belirsiz sembol" hatas� ile derleme ba�ar�s�z olacakt�r. Bu sorunu ��zmek i�in using deyimlerinden birini kald�rabilir, bunun yerine using-declaration kullanabilir veya x'i a��k bir kapsam belirleyiciyle (a:: veya b::) nitelendirebiliriz.

��te daha karma��k bir �rnek:
    #include <iostream> // imports the declaration of std::cout

    int cout() // kendi "cout" umuzu tan�mlad�k
    {
        return 5;
    }

    int main()
    {
        using namespace std; // makes std::cout accessible as "cout"
        cout << "Hello, world!\n"; // Hangi cout u istiyoruz ? Yukar�da tan�mlad���m�z cout u mu yoksa ad alan� i�inde var olan cout u mu ?

        return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------

     
    Yukar�daki �rnekte, derleyici cout kullan�m�m�z�n std::cout'u mu yoksa tan�mlad���m�z cout fonksiyonunu mu ifade etti�ini belirleyemez ve 
    yine "belirsiz sembol" hatas� ile derleme ba�ar�s�z olacakt�r. Bu �rnek basit olsa da, std::cout'u �u �ekilde a��k�a �neklediysek:
-------------------------------------------------------------------------------------------------------------------------------------------------------
    std::cout << "Hello, world!\n"; // derleyiciye std::cout dan bahsetti�imizi s�yle
-------------------------------------------------------------------------------------------------------------------------------------------------------
    veya bir kullan�m y�nergesi yerine bir kullan�m bildirimi kullan�ld�:
    
   * using std::cout; // derleyiciye cout denilince std::cout dan bahsetti�imizi s�yle
   * cout << "Hello, world!\n"; // so this means std::cout


    E�er bir using-directive (namespace kullan�m y�nergesi) bug�n isim �ak��mas�na neden olmasa bile, kodunuzu gelecekteki �ak��malara kar�� daha 
    savunmas�z hale getirir. �rne�in, kodunuz g�ncellenen bir k�t�phanenin using-directive'ini i�eriyorsa, g�ncellenen k�t�phanede tan�t�lan t�m 
    yeni isimler, mevcut kodunuzla �ak��ma adaylar� olur.

    Bu durumda daha sinsice bir sorun da ortaya ��kabilir. G�ncellenen k�t�phane, sadece ayn� isme sahip olmakla kalmay�p, belirli bir fonksiyon 
    �a�r�s� i�in daha iyi bir e�le�me olu�turan bir fonksiyon tan�t�rsa, derleyici yeni fonksiyonu tercih edebilir ve program�n�z�n davran��� 
    beklenmedik bir �ekilde de�i�ebilir.

    S�radaki �rne�e bakarak mevzuyu daha iyi anlayal�m:
foolib.h (part of some third-party library):
    #ifndef FOOLIB_H
    #define FOOLIB_H

    namespace Foo
    {
        // burada kulland���m�z baz� yararl� kodlar varm�� gibi davranal�m
    }
    #endif

main.cpp:
    #include <iostream>
    #include <foolib.h> // 3.parti k�t�phane, bu y�zden k��eli parantez kullan�ld�.

    int someFcn(double)
    {
        return 1;
    }

    int main()
    {
        using namespace Foo; // ��nk� tembeliz ve Foo:: nitelenmi� adlara Foo:: �nekini yazmadan eri�mek istiyoruz
        std::cout << someFcn(0) << '\n'; // 0'�n ger�ek de�eri 0.0 olmal�d�r, ancak bu yap�lmas� kolay bir hatad�r

        return 0;
    }

    Bu program �al���r ve 1'i yazd�r�r.

    �imdi g�ncellenmi� bir Folib.h dosyas�n� i�eren Folib k�t�phanesini g�ncelledi�imizi varsayal�m. Program�m�z art�k �una benziyor:

Folib.h (baz� ���nc� taraf k�t�phanelerin bir par�as�):
    #ifndef FOOLIB_H
    #define FOOLIB_H

    namespace Foo
    {
        // Yeni tan�t�lan fonksiyon
        int someFcn(int)
        {
            return 2;
        }

        // burada kulland���m�z baz� yararl� kodlar varm�� gibi davranal�m
    }
    #endif
main.cpp:
    #include <iostream>
    #include <foolib.h>

    int someFcn(double)
    {
        return 1;
    }

    int main()
    {
        using namespace Foo; // ��nk� tembeliz ve Foo:: nitelenmi� adlara Foo:: �nekini yazmadan eri�mek istiyoruz
        std::cout << someFcn(0) << '\n'; // 0'�n ger�ek de�eri 0.0 olmal�d�r, ancak bu yap�lmas� kolay bir hatad�r

        return 0;
    }

    Ana main.cpp dosyam�z hi� de�i�medi, ancak bu program �imdi �al���yor ve 2 yazd�r�yor!

    Derleyici bir i�lev �a�r�s�yla kar��la�t���nda, i�lev �a�r�s�n� hangi i�lev tan�m�yla e�le�tirmesi gerekti�ini belirlemelidir.
    Potansiyel olarak e�le�en i�levlerden birini se�erken, arg�man d�n���mlerine ihtiya� duymayan bir i�levi, arg�man d�n���mleri 
    gerektiren bir i�leve tercih eder. ��nk� 0 say�s� bir tamsay� oldu�undan, C++, bu durumu yeni tan�t�lan someFcn(int) 
    (hi�bir d�n���m gerektirmez) ile e�le�tirmeyi someFcn(double) (int'ten double'a d�n���m gerektirir) �zerine tercih eder.
    Bu, program sonu�lar�m�zda beklenmeyen bir de�i�ikli�e neden olur.

    Bu sorun, using-declaration veya a��k bir kapsam belirleyici kullanm�� olsayd�k meydana gelmezdi.
    
    Son olarak, a��k kapsam �neklerinin olmay���, okuyucunun hangi i�levlerin kitapl���n par�as� oldu�unu ve neyin program�n�z�n par�as� oldu�unu s�ylemesini zorla�t�r�r. 
    �rne�in, bir kullan�m y�nergesi kullan�rsak:
    using namespace ns;

    int main()
    {
        foo(); // bu foo kullan�c� tan�ml� bir i�lev mi, yoksa ns k�t�phanesinin bir par�as� m�?
    }
    Modern IDE'ler, foo() �a�r�s�n�n ger�ekten ns::foo()'yu mu yoksa kullan�c� tan�ml� bir fonksiyon olan foo()'yu mu ifade etti�ini size g�stermeli;
    ancak her bir ismin kayna��n� g�rmek i�in her bir ismin �zerine gelmek s�k�c�d�r.

    Kullan�m direktifi olmadan, �ok daha a��kt�r:
    int main()
    {
        ns::foo(); // a��k�a ns k�t�phanesinin bir par�as�
        foo(); // muhtemelen kullan�c� tan�ml� bir fonksiyon
    }
    Bu versiyonda ns::foo() �a�r�s� a��k�a bir k�t�phane �a�r�s�d�r. Basit foo() �a�r�s� muhtemelen bir kullan�c� tan�ml� fonksiyonu �a�r�s�d�r 
    (baz� k�t�phaneler, belirli standart k�t�phane ba�l�klar� dahil, isimleri global ad alan�na yerle�tirir, bu y�zden kesin bir garanti de�ildir).

    baz� k�t�phanelerin, �zellikle belirli standart k�t�phane ba�l�klar�n�n, isimleri (fonksiyonlar, s�n�flar vb.) global ad alan�na 
    yerle�tirebilece�ini belirtiyor. Yani, bir k�t�phanenin bir ismi global ad alana eklemesi durumunda, belirli bir ismin global ad alan�nda
    bulunup bulunmad���n� tam olarak tahmin etmek zor olabilir. Bu nedenle, bir ismin hangi ad alan�na ait oldu�unu belirlemek i�in kesin bir garanti yoktur.
   
   "Baz� k�t�phaneler, �zellikle belirli standart k�t�phane ba�l�klar�, isimleri (fonksiyonlar, s�n�flar vb.) global ad alan�na yerle�tirebilirler."
    Bu ifade, bir k�t�phanenin belirli isimleri global ad alan�na ekleyebilece�i anlam�na gelir. Yani, bir fonksiyon veya s�n�f ad�, belirli bir 
    ba�l�k dosyas� i�inde tan�mlan�yorsa, bu isim global ad alan�nda da kullan�labilir.
    Ancak, "bu y�zden kesin bir garanti de�ildir" ifadesi, her k�t�phanenin bu �ekilde davranmad���n� veya bu durumun genel bir kural olmad���n�
    belirtiyor. Yani, bir ismin global ad alanda bulunup bulunmad���n� �nceden kesin bir �ekilde bilmenin her zaman m�mk�n olmad���n� ifade ediyor.
    Bu durum, belirli k�t�phanelerin veya ba�l�k dosyalar�n�n �zel davran��lar�na ba�l� olabilir.

    * Using-declaration ve using-direktiflerinin kapsam�
    E�er bir using-declaration veya using-directive bir blok i�inde kullan�l�yorsa, isimler sadece o blok i�in ge�erli olacakt�r (normal blok kapsam
    kurallar�n� takip eder). Bu durum, isim �ak��malar�n�n sadece o blok i�inde ger�ekle�me olas�l���n� azaltarak olumlu bir durumdur.

    E�er bir using-declaration veya using-directive global ad alan�nda kullan�l�yorsa, isimler dosyan�n geri kalan�na uygulan�r (dosya kapsam�na 
    sahiptirler).


    * Using ifadesini iptal etme veya de�i�tirme i�lemi 
    ---------------------------------------------------
    "Using-statement bir kere tan�mland�ktan sonra, tan�mland��� kapsam i�inde onu iptal etmek veya ba�ka bir using-statement ile de�i�tirmek
    m�mk�n de�ildir."

    int main()
    {
    using namespace Foo;

    // Foo ad alan�n� burada iptal edebilmek m�mk�n de�il
    // "using namespace Foo" i ba�ka bir using ifadesi ile de�i�tirmekte m�mk�n de�il

    return 0;
    } // using namespace Foo burada bitiyor


    Yapabilece�iniz en iyi �ey, blok kapsam belirleme kurallar�n� kullanarak, kullan�m ifadesinin kapsam�n� en ba�tan kas�tl� olarak s�n�rlamakt�r.

    int main()
    {
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // ad alan� kullan�ld���nda Foo'nun s�resi dolar

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // ad alan� kullan�ld���nda Goo'nun s�resi dolar

    return 0;
    }

    Elbette, t�m bu ba� a�r�lar�ndan ilk etapta kapsam ��z�mleme operat�r�n�n (::) a��k�a kullan�lmas�yla ka��n�labilir. :))
    */
    // BEST US�NG-STATEMENT KULLANIMI
    // �zellikle using namespace std; gibi using - directive'lerden ka��n�n, ancak belirli durumlarda (�rne�in using namespace std::literals 
    // kullanarak s ve sv literal soneklerine eri�mek gibi). Using-declaration'lar genellikle bloklar i�inde kullanmak g�venli kabul edilir.
    // Kullan�mlar�n� bir kod dosyas�n�n global ad alan�nda s�n�rlay�n ve bunlar� bir ba�l�k dosyas�n�n global ad alan�nda asla kullanmay�n.
    // **** BEST
    /*A��k�a belirtilmi� ad alanlar�n�(namespace) tercih edin : Ad alanlar�n� a��k�a belirterek, hangi ad alan�na ait oldu�unu
    net bir �ekilde ifade edin.

    Using ifadelerinden(using statements) m�mk�nse ka��n�n : Using ifadeleri, belirli bir ad alan�ndaki t�m elemanlar� kullan�labilir k�lar, 
    bu da isim �ak��malar�na yol a�abilir.Bu nedenle, sadece gerekli olan ad alanlar�n� belirtmek daha iyidir.

    Using - directive'leri m�mk�nse ka��n�n: Using-directive'ler, bir dosyan�n genel kapsam�n� etkiler ve isim �ak��malar�na neden olabilir.
    Bu nedenle, genellikle kullan�lmaktan ka��n�lmal�d�r.

    Using - declaration'lar� bloklar i�inde kullanabilirsiniz: Using-declaration'lar, belirli bir blok i�inde ge�erlidir,
    bu da isim �ak��malar�n� s�n�rlar ve daha g�venli kullan�m sa�lar.Bu nedenle, genellikle bloklar i�inde kullan�labilirler.

    The "using" kelimesi, using ifadeleri ile ilgisi olmayan t�r takma adlar� tan�mlamak i�in de kullan�l�r. T�r takma adlar�,
    10.7 dersinde ele al�nmaktad�r - Typedef'ler ve t�r takma adlar�.

    */  
/*                                                        7.13 � Ads�z ve sat�r i�i ad alanlar�
    * �simsiz ( anonim ) ad alanlar�
    --------------------------------
    isimsiz ad alanlar� ayn� zamanda anonim ad alan� olarak da adland�r�l�r. Bir ad alan�n�n tan�mlan�rken ismi olmadan tan�mlanmas�d�r. 
    �rne�in : 
        #include <iostream>

        namespace // isimsiz ad alan�
        {
            void doSomething() // sadece bu dosyadan eri�ilebilir.
            {
                std::cout << "v1\n";
            }
        }

        int main()
        {
            doSomething(); // �n ek olmadan doSomething() fonksiyonunu �a��rabiliriz. 

            return 0;
        }

        Bu ��kt� olarak : "v1" ��kt�s�n� verir. 
    �simsiz bir ad alan�nda tan�mlanan t�m i�erik, bir �st ad alan�n�n bir par�as�ym�� gibi ele al�n�r. Yani, doSomething() fonksiyonu isimsiz
    ad alan�nda tan�mlansa da, fonksiyon kendisi �st ad alandan (bu durumda genel ad alan�ndan) eri�ilebilir, bu nedenle main() i�inden herhangi
    bir nitelendirici olmadan doSomething() fonksiyonunu �a��rabiliyoruz.

    Bu, isimsiz ad alanlar�n� kullan��s�z gibi g�sterebilir. Ancak isimsiz ad alanlar�n�n di�er bir etkisi de, isimsiz bir ad alan� i�indeki t�m
    tan�mlay�c�lar�n i� ba�lant�ya sahipmi� gibi ele al�nmas�d�r. Bu, isimsiz bir ad alan�n�n i�eri�inin tan�mland��� dosyan�n d���nda g�r�lemedi�i 
    anlam�na gelir.

    Fonksiyonlar i�in, bu, isimsiz ad alan�ndaki t�m fonksiyonlar� static fonksiyonlar olarak tan�mlamakla ayn� etkiye sahiptir. A�a��daki program,
    etkili olarak yukar�dakiyle ayn�d�r:
    
        #include <iostream>

        static void doSomething() // can only be accessed in this file
        {
            std::cout << "v1\n";
        }

        int main()
        {
            doSomething(); // we can call doSomething() without a namespace prefix

            return 0;
        }


    Kullan�lmas� gereken yer heen belli zaten �simsiz ad alanlar� genellikle bir dosyada yerel kalmalar�n� istedi�iniz bir�ok i�eri�iniz 
    oldu�unda kullan�l�r, ��nk� bu i�erikleri tek tek static olarak i�aretlemekten daha kolayd�r. �simsiz ad alanlar�, program taraf�ndan
    tan�mlanan t�rleri (bunu daha sonraki bir dersimizde tart��aca��z) dosyada yerel tutacak ve bunun i�in alternatif e�de�er bir mekanizma
    bulunmayacakt�r.


    * Sat�r i�i ad alanlar�
    -----------------------
    �imdi s�radaki program� takip edelim:
        #include <iostream>

        void doSomething()
        {
            std::cout << "v1\n";
        }

        int main()
        {
            doSomething();

            return 0;
        }

    ayn� �ekilde "v1" ��kt�s�n� verir. 
    �ok basit bir program fakat varsayal�m ki doSomething()'den memnun de�ilsiniz ve onun davran���n� de�i�tiren bir �ekilde iyile�tirmek 
    istiyorsunuz. Ancak bunu yaparsan�z, eski s�r�m� kullanan mevcut programlar� bozma riskiyle kar��la��rs�n�z. Bu durumu nas�l y�netiriz ?

    Bir yol, fonksiyonun yeni bir s�r�m�n� farkl� bir adla olu�turmakt�r. Ancak bir�ok de�i�iklik boyunca neredeyse ayn� ad� ta��yan bir 
    dizi fonksiyonla sonu�lanabilirsiniz (doSomething, doSomething_v2, doSomething_v3, vb.).

    Alternatif olarak, Sat�r i�i bir ad alan� kullanmakt�r. Sat�r i�i ad alan�, i�eri�i s�r�mlemek i�in genellikle kullan�lan bir ad alan�d�r. 
    �simsiz bir ad alan� gibi, Sat�r i�i bir ad alan� i�inde bildirilen her �ey, ana ad alan�n�n bir par�as� olarak kabul edilir. Ancak, 
    isimsiz ad alanlar�ndan farkl� olarak, Sat�r i�i ad alanlar� ba�lant�y� etkilemez.
    Sat�r i�i ad alan�n� tan�mlamak i�in "inline" keyword �n� kullan�r�z. 
    �rne�in : 
        #include <iostream>

        inline namespace V1 // V1 ad�nda bir sat�r i�i ad alan� tan�mlad�k
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        namespace V2 // V2 ad�nda normal ad alan� tan�mlad�k
        {
            void doSomething()
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething in V1 versiyonunu �a��rd�k
            V2::doSomething(); // doSomething in V2 versiyonunu �a��rd�k

            doSomething(); // Sat�r i�in V1 ad alan� doSomething fonksiyonunu �a��rd�k.

            return 0;
        }
    Bu program bize : 
    * v1
    * v2
    * v1 
    ��kt�s�n� verdi 

    Yukar�daki �rnekte, doSomething() �a�r�lar� V1'i (sat�r i�i s�r�m�) alacakt�r. Daha yeni bir s�r�m� kullanmak isteyen �a�r� yapanlar,
    a��k�a V2::doSomething() �a�rabilirler. Bu, mevcut programlar�n i�levini korurken daha yeni programlar�n daha yeni/daha iyi varyasyonlardan
    yararlanmas�na olanak tan�r.

    Alternatif olarak, daha yeni s�r�m� y�klemek istiyorsan�z:

        #include <iostream>

        namespace V1 // declare a normal namespace named V1
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace V2 // declare an inline namespace named V2
        {
            void doSomething()
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // calls the V1 version of doSomething()
            V2::doSomething(); // calls the V2 version of doSomething()

            doSomething(); // calls the inline version of doSomething() (which is V2)

            return 0;
        }
    Bu �rnekte, doSomething() fonksiyonunu �a��ran herkes varsay�lan olarak v2 s�r�m�n� alacakt�r (daha yeni ve daha iyi s�r�m).
    H�l� eski doSomething() s�r�m�n� isteyen kullan�c�lar, eski davran��a eri�mek i�in V1::doSomething() �eklinde a��k�a �a�r� yapabilirler. 
    Bu, mevcut programlar�n V1 s�r�m�n� isteyenlerin genellikle doSomething yerine V1::doSomething'� global olarak de�i�tirmeleri gerekece�i 
    anlam�na gelir, ancak fonksiyonlar iyi adland�r�lm��sa genellikle sorun olmayacakt�r.

    Yeni versiyonu ise inline namespace V2 i�ine koyarak, bu versiyonun ana ad alan�nda oldu�unu ve varsay�lan olarak kullan�lmas� gerekti�ini
    belirtiyoruz. Yani, mevcut programlar de�i�iklik yapmadan do�rudan doSomething() �a�r�s� yapt�klar�nda, bu �a�r� otomatik olarak V2 ad 
    alan�ndaki fonksiyonu kullanacakt�r. Bu, mevcut programlar�n de�i�iklik yapmaks�z�n yeni davran��a ge�melerini sa�lar.

    Bu iki ad�m, eski ve yeni versiyonlar�n birbirinden net bir �ekilde ayr�lmas�n� ve ge�i�in kontrol alt�nda yap�lmas�n� sa�lar. 
    Eski davran��a ihtiya� duyan programlar, V1::doSomething() �eklinde a��k�a belirterek eski versiyonu kullanabilirler.


    * Sat�r i�i ve ads�z ad alanlar�n� kar��t�rma
    ---------------------------------------------
    Bir ad alan� hem inline hem de isimsiz olabilir. 
        #include <iostream>

        namespace V1 // V1 ad�nda normal bir ad alan� tan�mlar
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace // inline ads�z bir ad alan� tan�mlar
        {
            void doSomething() // has internal linkage
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething() in V1 versiyonunu �a��r�r
            // V2 yok o y�zden V2:: �n eki ile �a�r� yapamay�z

            doSomething(); // doSomething() in inline olan�n� �a��r�r yani anonim olan�n�.

            return 0;
        }

    Ancak, bu t�r durumlarda, muhtemelen bir i� i�e ge�mi� bir anonim ad alan�n� bir inline ad alan� i�ine yerle�tirmek daha iyidir.
    Bu, ayn� etkiye sahiptir (anonim ad alan� i�indeki t�m i�levler varsay�lan olarak i� ba�lant�ya sahiptir), ancak hala kullanabilece�iniz
    a��k bir ad alan� ad� sa�lar:
        #include <iostream>

        namespace V1 // normal V1 ad alan�n� bildir
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace V2 // V2 ad alan�n� i�eren bir inline ad alan�n� bildir
        {
            namespace // ad� olmayan ad alan
            {
                void doSomething() // i� ba�lant�ya sahip
                {
                    std::cout << "V2\n";
                }
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething() fonksiyonunun V1 s�r�m�n� �a��r�r
            V2::doSomething(); // doSomething() fonksiyonunun V2 s�r�m�n� �a��r�r

            ::doSomething(); // doSomething() fonksiyonunun i� i�e ge�mi� s�r�m�n� �a��r�r (ki bu V2'dir)

            return 0;
        }

*******************************************************************************************************************************************************
        CHapter 7 bitti. GENEL �ZET ve chapter7_3 -> Quiz ve ��z�mlerim i�in olu�turulacak.







*/




























































    return 0;
}
