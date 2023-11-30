#include <iostream>

int main() {
    return 0;
}
/*
                                                            KODLARI TEST ETMEYE G�R��

Program�n�z� yazd�n�z, derlediniz ve hatta �al��t� gibi g�r�n�yor! Peki, �imdi ne yapmal�s�n�z?

Cevap, duruma ba�l�d�r. E�er program�n�z� bir defa �al��t�r�p ard�ndan at�lmak �zere yazd�ysan�z, o zaman i�iniz bitmi� demektir. Bu durumda, program�n�z�n her
durum i�in �al��mamas�n�n bir �nemi olmayabilir. E�er sadece ihtiyac�n�z olan bir durumda �al���yorsa ve program� sadece bir kez �al��t�racaksan�z, i�iniz tamamlanm��
demektir. E�er program�n�z tamamen lineerse (if veya switch ifadeleri gibi ko�ullu ifadeler i�ermiyorsa), girdi alm�yorsa ve do�ru cevab� �retiyorsa, o zaman b�y�k 
ihtimalle i�iniz bitmi� demektir. Bu durumda, program� �al��t�rarak ve ��kt�y� do�rulayarak zaten t�m program� test etmi�siniz demektir. Program� farkl� sistemlerde
derleyip �al��t�rarak davran���n�n tutarl� olup olmad���n� kontrol etmek isteyebilirsiniz (e�er tutars�zl�k varsa, ba�lang�� sistemizde tesad�fen �al��an tan�ms�z 
davran�� �reten bir �ey yapm�� olabiliriz).
Ancak b�y�k olas�l�kla program�n�z� bir�ok kez �al��t�rmay�, d�ng�ler ve ko�ullu mant�k kullanan ve bir t�r kullan�c� girdisi kabul eden bir program yazd�n�z. 
Muhtemelen gelecekteki di�er programlarda yeniden kullan�labilir olmas� i�in i�levler yazd�n�z. Belki de kapsam art���(scope creep) ya�ad�n�z ve ba�lang��ta planlanmayan baz�
yeni yetenekler eklediniz. Belki de bu program� di�er ki�ilere da��tmay� d���n�yorsunuz (ki muhtemelen sizin d���nmedi�iniz durumlar� deneyeceklerdir). Bu durumda,
program�n�z�n geni� bir dizi ko�ul alt�nda d���nd���n�z gibi �al��t���n� do�rulamak i�in proaktif bir test yapman�z gerekmektedir.

Program�n�z�n bir set girdi i�in �al��mas�, program�n t�m durumlarda do�ru �al��aca�� anlam�na gelmez.

Yaz�l�m testi (ayn� zamanda yaz�l�m do�rulama olarak da adland�r�l�r), yaz�l�m�n beklenildi�i gibi �al���p �al��mad���n� belirleme s�recidir.


Test etme Problemi
------------------
Kapsaml� bir test neden zordur ? �u �rnek �zerinden d���nelim:

                                                #include <iostream>

                                                void compare(int x, int y)
                                                {
                                                    if (x > y)
                                                        std::cout << x << " is greater than " << y << '\n'; // case 1
                                                    else if (x < y)
                                                        std::cout << x << " is less than " << y << '\n'; // case 2
                                                    else
                                                        std::cout << x << " is equal to " << y << '\n'; // case 3
                                                }

                                                int main()
                                                {
                                                    std::cout << "Enter a number: ";
                                                    int x{};
                                                    std::cin >> x;

                                                    std::cout << "Enter another number: ";
                                                    int y{};
                                                    std::cin >> y;

                                                    compare(x, y);

                                                    return 0;
                                                }

Bir 4 baytl�k bir tamsay� varsay�ld���nda, bu program� her olas� giri� kombinasyonuyla a��k�a test etmek, program� 18,446,744,073,709,551,616 (yakla��k 18 kentilyon)
kez �al��t�rman�z� gerektirir. Bu a��k�a makul bir g�rev de�il!

Her kullan�c� girdisi istedi�imizde veya kodumuzda bir ko�ullu ifade oldu�unda, program�m�z�n �al��ma �eklinin olas� yollar�n� �o�altan bir �arpanla kar��la��r�z. 
En basit programlar i�in bile, her giri� kombinasyonunu a��k�a test etmek neredeyse hemen imkans�z hale gelir.

�imdi, yukar�daki program� 18 kentilyon kez �al��t�rman�z�n ger�ekten gerekmedi�ini sezginiz size s�ylemelidir. Mant�kl� bir �ekilde, durum 1'in x ve y de�erleri 
i�in x > y oldu�unda �al���yorsa, x > y olan herhangi bir x ve y �ifti i�in �al��mas� gerekti�ini sonu�land�rabilirsiniz. Bu durumda, program� ger�ekten sadece �� 
kez �al��t�rmam�z yeterli olur (compare() fonksiyonundaki �� durumu birer kez �al��t�rmak i�in), b�ylece istenildi�i gibi �al��t���na dair y�ksek bir g�ven d�zeyine
sahip olabiliriz. Test etmemiz gereken �eyin say�s�n� dramatik bir �ekilde azaltmak i�in kullanabilece�imiz ba�ka benzer hileler de vard�r, bu da test etmeyi
y�netilebilir hale getirir.

Test y�ntemleri hakk�nda yaz�lacak �ok �ey var - asl�nda, bunun �zerine bir b�l�m bile yazabiliriz. Ancak bu konu C++ ile s�n�rl� olmad���ndan, k�sa ve gayri resmi
bir tan�t�m ile yetinece�iz. Bir sonraki birka� alt b�l�mde, kodunuzu test ederken d���nmeniz gereken baz� pratik konular hakk�nda konu�aca��z.


Programlar�n�z� k���k par�alar halinde test edin
------------------------------------------------
�zel bir konsept arabas� �reten bir otomobil �reticisini d���n�n. A�a��dakilerden hangisini d���nd���n�z� d���n�n?
a) Her araba par�as�n� bireysel olarak in�a et (veya sat�n al) ve kurulumdan �nce her par�ay� ayr� ayr� test et. Par�an�n �al��t��� kan�tland�ktan sonra, onu 
arabaya entegre et ve entegrasyonun �al��t���ndan emin olmak i�in tekrar test et. Son olarak, her �eyin iyi g�r�nd���n� son do�rulama olarak t�m arabay� test et.
b) T�m bile�enlerden hemen bir araba olu�tur, ard�ndan t�m �eyi ilk kez tamamen test et.

Olas� a) se�ene�inin daha iyi bir se�enek oldu�u a��kt�r. Ve yine de, bir�ok yeni programc� kodlar�n� b) se�ene�i gibi yazar!

Durum b)'de, araba par�alar�ndan herhangi biri beklenildi�i gibi �al��mazsa, mekanik�i neyin yanl�� oldu�unu belirlemek i�in t�m arabay� te�his etmek zorunda
kalacakt�r - sorun her yerde olabilir. Bir semptomun bir�ok nedeni olabilir - �rne�in, araba ba�lam�yorsa, kusurlu bir buji, pil, yak�t pompas� veya ba�ka bir �ey mi?
Bu, problemlerin tam olarak nerede oldu�unu ve bunlarla ne yap�lmas� gerekti�ini belirlemeye y�nelik �ok zaman kayb�na neden olur. Ve e�er bir sorun bulunursa, 
sonu�lar� felaket olabilir - bir alandaki bir de�i�iklik, �ok say�da ba�ka yerde "dalga etkileri" (de�i�iklikler) yaratabilir. �rne�in, �ok k���k bir yak�t pompas�,
bir motor tasar�m�na, ard�ndan bir araba �asisinin tasar�m�na yol a�abilir. En k�t� durumda, ba�lang��ta k���k bir sorunu kar��lamak i�in arabay� geni� bir �ekilde 
yeniden tasarlam�� olabilirsiniz!

Durum a)'da �irket, s�rekli olarak test eder. E�er herhangi bir bile�en kutusundan ��kt���nda k�t�yse, hemen bilgi sahibi olabilir ve d�zeltebilir/de�i�tirebilir. 
Bir par�a yaln�zca kendi i�inde �al��t��� kan�tland�ktan sonra arabaya entegre edilir ve ard�ndan bu par�a hemen entegre olduktan sonra tekrar test edilir. Bu �ekilde,
beklenmedik sorunlar m�mk�n oldu�unca erken ke�fedilir, hen�z k���k ve kolayca d�zeltilebilecek sorunlard�r.

T�m arabay� monte etme a�amas�na geldiklerinde, arabay� �al��t�rman�n makul bir g�vene sahip olmalar� gerekir - sonu�ta, t�m par�alar izole edilmi� ve ba�lang��ta 
entegre edildi�i zaman test edilmi�tir. Bu noktada beklenmeyen sorunlar bulunabilir, ancak bu risk, �nceki t�m testlerle azalt�lm��t�r.

Yukar�daki benzetme, programlar i�in de ge�erlidir, ancak bir nedenden dolay�, yeni programc�lar bunun fark�na genellikle varmazlar. K���k i�levleri (veya s�n�flar�)
yazmak ve ard�ndan hemen derleyip test etmek, daha iyidir. Bu �ekilde, bir hata yaparsan�z, son derledi�iniz/test etti�inizden bu yana de�i�tirdi�iniz k���k kod
miktar�nda olmas� gerekti�ini bileceksiniz. Bu, daha az yer aramak ve �ok daha az zaman harcamak anlam�na gelir.

Bir "�nite" kodun do�ru oldu�undan emin olmak i�in kodunuzun k���k bir par�as�n� izole etmek ve test etmek, �nite testi ( unit testing ) olarak adland�r�l�r.
Her �nite testi ( unit test ), birimin belirli bir davran���n�n do�ru oldu�unu sa�lamak i�in tasarlanm��t�r.

*** BEST -> Program�n�z� k���k, iyi tan�mlanm�� birimlere (fonksiyonlar veya s�n�flar) yaz�n, s�k s�k derleyin ve kodunuzu geli�tirirken test edin.



E�er program k�sa ise ve kullan�c� giri�i kabul ediyorsa, �e�itli kullan�c� giri�lerini denemek yeterli olabilir. Ancak programlar giderek daha uzun hale geldik�e, 
bu yeterlilik azal�r ve par�alar� program�n geri kalan�na entegre etmeden �nce bireysel fonksiyonlar� veya s�n�flar� test etmek daha de�erli hale gelir.

Peki, kodumuzu birimler halinde nas�l test edebiliriz?


Informal testing
----------------
Kodu yazarken program�n�z� test etmenin bir yoludur. Bir kod birimini (bir fonksiyon, bir s�n�f veya di�er ayr�k kod "paketleri") yazd�ktan sonra, eklenen bu birimi 
test etmek i�in baz� kodlar� yazabilir ve test ba�ar�l� oldu�unda testi silebilirsiniz. A�a��daki isLowerVowel() fonksiyonu i�in �rnek olarak �u kodlar�
yazabilirsiniz:

                                        #include <iostream>

                                        // Test edilecek fonksiyon a�a��daki gibidir
                                        bool isLowerVowel(char c)
                                        {
                                            switch (c)
                                            {
                                            case 'a':
                                            case 'e':
                                            case 'i':
                                            case 'o':
                                            case 'u':
                                                return true;
                                            default:
                                                return false;
                                            }
                                        }

                                        int main()
                                        {
                                            // ��te ge�ici testlerimiz, do�ru �al��t���n� do�rulamak i�in
                                            std::cout << isLowerVowel('a') << '\n'; // ge�ici test kodu, 1 �retmeli
                                            std::cout << isLowerVowel('q') << '\n'; // ge�ici test kodu, 0 �retmeli

                                            return 0;
                                        }
E�er sonu�lar 1 ve 0 olarak d�nerse, i�te tamam! Fonksiyonunuzun temel durumlar i�in �al��t���n� biliyorsunuz ve kodu inceleyerek test etmedi�iniz durumlar
('e', 'i', 'o' ve 'u') i�in de �al��aca��n� makul bir �ekilde ��karabilirsiniz. Bu nedenle, ge�ici test kodunu silebilir ve programlamaya devam edebilirsiniz.


Testlerinizi korumak
--------------------
Ge�ici testler yazmak, baz� kodlar� h�zl� ve kolay bir �ekilde test etmenin bir yolu olsa da, ayn� kodu daha sonra tekrar test etmek isteyebilece�iniz ger�e�ini
hesaba katmaz. Belki bir fonksiyonu yeni bir yetenek eklemek i�in de�i�tirdiniz ve zaten �al��an bir �eyi bozmad���n�zdan emin olmak istiyorsunuz. Bu nedenle,
testlerinizi gelecekte tekrar �al��t�r�labilir olacak �ekilde korumak daha mant�kl� olabilir. �rne�in, ge�ici test kodunuzu silmek yerine, testleri bir testVowel()
fonksiyonuna ta��yabilirsiniz:

                    #include <iostream>

                    bool isLowerVowel(char c)
                    {
                        switch (c)
                        {
                        case 'a':
                        case 'e':
                        case 'i':
                        case 'o':
                        case 'u':
                            return true;
                        default:
                            return false;
                        }
                    }

                    // �u an hi�bir yerden �a�r�lm�yor
                    // Ancak daha sonra �eyleri tekrar test etmek istiyorsan�z burada
                    void testVowel()
                    {
                        std::cout << isLowerVowel('a') << '\n'; // ge�ici test kodu, 1 �retmeli
                        std::cout << isLowerVowel('q') << '\n'; // ge�ici test kodu, 0 �retmeli
                    }

                    int main()
                    {
                        return 0;
                    }

Daha fazla test olu�turduk�a bunlar� testVowel() i�levine ekleyebilirsiniz.

Test fonksiyonlar�n� otomatize etme
-----------------------------------
Test i�leviyle ilgili yukar�daki sorun, onu �al��t�rd���n�zda sonu�lar� manuel olarak do�rulaman�za dayanmas�d�r. Bu, en k�t� durumda beklenen cevab�n ne oldu�unu
hat�rlaman�z� gerektirir (belgelenmediyse), ve ger�ek sonu�lar� beklenen sonu�larla manuel olarak kar��la�t�rman�z� gerektirir.

Daha iyisini yapabiliriz, testleri ve beklenen cevaplar� i�eren ve bunlar� kar��la�t�rmam�za gerek olmayan bir test i�levi yazarak.


                        #include <iostream>

                        bool isLowerVowel(char c)
                        {
                            switch (c)
                            {
                            case 'a':
                            case 'e':
                            case 'i':
                            case 'o':
                            case 'u':
                                return true;
                            default:
                                return false;
                            }
                        }

                        // Ba�ar�s�z olan testin numaras�n� veya t�m testlerin ge�ti�ini belirtmek i�in 0'� d�nd�r�r
                        int testVowel()
                        {
                            if (!isLowerVowel('a')) return 1;
                            if (isLowerVowel('q')) return 2;

                            return 0;
                        }

                        int main()
                        {
                            int result { testVowel() };
                            if (result != 0)
                                std::cout << "testVowel() test " << result << " ba�ar�s�z.\n";
                            else
                                std::cout << "testVowel() testleri ge�ti.\n";

                            return 0;
                        }

Art�k herhangi bir zamanda testVowel()'� �a��rarak hi�bir �eyi bozmad���n�z� yeniden kan�tlayabilirsiniz ve test rutini sizin i�in t�m i�i yapacakt�r, ya 
bir "her �ey yolunda" sinyali (d�n�� de�eri 0) ya da ge�meyen test numaras� d�nd�rerek, neden bozuldu�unu inceleyebilirsiniz. Bu �zellikle eski kodlar�
de�i�tirirken, kazara bir �eyleri bozmad���n�zdan emin olmak i�in �ok kullan��l�d�r!

Unit Testing Frameworklar�
--------------------------

Di�er fonksiyonlar� �al��t�rmak i�in fonksiyonlar yazmak o kadar yayg�n ve kullan��l�d�r ki, bu i�lemi yazma, s�rd�rme ve y�r�tme s�recini basitle�tirmeye yard�mc� 
olacak �ekilde tasarlanm�� b�t�n �er�eveler (birim test �er�eveleri ( unit testing frameworks ) olarak adland�r�l�r) vard�r. Bunlar ���nc� taraf yaz�l�mlar�
i�erdi�inden, burada bunlar� ele almayaca��z, ancak var olduklar�n� bilmelisiniz.

Entegrasyon Testleri
--------------------

Her bir biriminiz izolasyon halinde test edildikten sonra, bunlar program�n�za entegre edilebilir ve do�ru bir �ekilde entegre edildiklerinden emin olmak i�in tekrar
test edilebilir. Bu, bir entegrasyon testi olarak adland�r�l�r. Entegrasyon testi genellikle daha karma��kt�r - �u anda, program�n�z� birka� kez �al��t�rma ve 
entegre birimin davran���n� g�zden ge�irme yeterli olacakt�r.
*/

/*
                                                                 8.14 Code Coverage ( Kod Kapsam� )


Bu derste, kodunuzun do�ru oldu�unu sa�lamak i�in hangi t�rde testlerin yaz�lmas�n�n yararl� oldu�unu tart��aca��z."Code Coverage" ( Kod kapsam� ) terimi, bir
program�n test edilirken kaynak kodun ne kadar�n�n y�r�t�ld���n� tan�mlar.  Kod kapsam� i�in bir�ok farkl� metrik bulunmaktad�r. Daha kullan��l� ve pop�ler
olanlardan birka��n� a�a��daki b�l�mlerde ele alaca��z.

Statement coverage ( Deyim Kapsam )
-----------------------------------
Deyim kapsam� terimi, test rutinleriniz taraf�ndan y�r�t�len kodunuzdaki ifadelerin y�zdesini ifade eder.

                            int foo(int x, int y)
                            {
                                int z{ y };
                                if (x > y)
                                {
                                    z = x;
                                }
                                return z;
                            }

Bu fonksiyonu foo(1, 0) olarak �a��rmak, bu fonksiyon i�in tam deyim kapsam� sa�lar, ��nk� fonksiyondaki her deyim y�r�t�l�r.


isLower() fonksiyonumuz i�in:
                            bool isLowerVowel(char c)
                            {
                                switch (c) // statement 1
                                {
                                case 'a':
                                case 'e':
                                case 'i':
                                case 'o':
                                case 'u':
                                    return true; // statement 2
                                default:
                                    return false; // statement 3
                                }
                            }
Bu fonksiyonun t�m deyimleri test etmek i�in iki �a�r�ya ihtiya� duyacakt�r, ��nk� ayn� fonksiyon �a�r�s�nda deyim 2'ye ve 3'e ula�man�n bir yolu yoktur.

%100 deyim kapsam�n� hedeflemek iyi bir �ey olsa da, do�rulu�u sa�lamak genellikle yeterli de�ildir.

Branch Coverage ( �ube - Dal Kapsam� )
--------------------------------------

�ube kapsam�, y�r�t�len �ube y�zdesini ifade eder, her bir olas� �ube ayr� ayr� say�l�r. Bir if ifadesinin iki �ubesi vard�r - ko�ul do�ru oldu�unda y�r�t�len bir 
�ube ve ko�ul yanl�� oldu�unda y�r�t�len bir �ube (ko�ula kar��l�k gelen bir else ifadesi olmasa bile). Bir switch ifadesinin �ok say�da �ubesi olabilir.

Bir �nceki �rnekte var olan Foo fonksiyonunu d���nelim. �nceki foo(1, 0) �a�r�s� bize %100 deyim kapsam�n� sa�lad� ve x > y durumunu test etti, ancak bu sadece bize
%50 �ube kapsam�n� sa�lar. if ifadesinin y�r�t�lmedi�i durumu test etmek i�in foo(0, 1) i�in bir �a�r�ya daha ihtiyac�m�z var.

isLower() �rne�imizi inceleyelim. isLowerVowel() fonksiyonunda, %100 �ube kapsam�n� sa�lamak i�in iki �a�r�ya ihtiya� duyulacakt�r: biri (�rne�in isLowerVowel('a')) 
ilk durumlar� test etmek i�in ve di�eri (�rne�in isLowerVowel('q')) varsay�lan durumu test etmek i�in. Ayn� g�vdeye beslenen birden �ok durumu ayr� ayr� test
etmek gerekmez - biri �al���yorsa, hepsi �al��mal�d�r.

�imdi s�radaki �rne�e bakal�m:
                            void compare(int x, int y)
                            {
                                if (x > y)
                                    std::cout << x << " is greater than " << y << '\n'; // case 1
                                else if (x < y)
                                    std::cout << x << " is less than " << y << '\n'; // case 2
                                else
                                    std::cout << x << " is equal to " << y << '\n'; // case 3
                            }

Burada %100 �ube kapsam�n� elde etmek i�in 3 �a�r�ya ihtiya� vard�r: compare(1, 0), ilk if ifadesi i�in pozitif kullan�m durumunu test eder. compare(0, 1), ilk if 
ifadesi i�in negatif kullan�m durumunu ve ikinci if ifadesi i�in pozitif kullan�m durumunu test eder. compare(0, 0), ilk ve ikinci if ifadesi i�in negatif kullan�m
durumunu test eder ve else ifadesini y�r�t�r. Bu nedenle, bu fonksiyonun g�venilir bir �ekilde 3 �a�r� ile test edildi�ini s�yleyebiliriz (bu, 18 quintilliondan
biraz daha iyidir).

*** BEST -> Kodunuzun %100 �ube kapsam�n� hedefleyin. �ubeden kas�t ak�� kontrol 
* "Branch" terimi, programdaki kontrol ak���ndaki dallanmalar� ifade eder. Bu dallanmalar genellikle �u t�r ifadelerle ili�kilidir: if, else if, 
else, switch, while, for gibi kontrol yap�lar�. Her bir kontrol yap�s�n�n i�indeki her bir �art (veya durum), bir "branch" olarak adland�r�l�r.
�rne�in: 
                            if (x > y)
                            {
                                // Branch 1
                                // ...
                            }
                            else if (x < y)
                            {
                                // Branch 2
                                // ...
                            }
                            else
                            {
                                // Branch 3
                                // ...
                            }
Loop coverage ( D�ng� Kapsam� )
-------------------------------
D�ng� Kapsam� (bilinen ad�yla 0, 1, 2 testi olarak da adland�r�l�r), kodunuzda bir d�ng� varsa, d�ng�n�n s�f�r, bir ve iki kez d�nd���nde d�zg�n
�al��t���ndan emin olman�z gerekti�ini belirtir. E�er 2 kez d�nme durumu do�ru �al���yorsa, bu durum t�m 2'den b�y�k iterasyonlar i�in de do�ru
�al��acakt�r. Bu �� test, b�ylece t�m olas�l�klar� kapsar (��nk� bir d�ng� negatif say�da kez �al��t�r�lamaz).

�rne�in:
                            #include <iostream>

                            void spam(int timesToPrint)
                            {
                                for (int count{ 0 }; count < timesToPrint; ++count)
                                        std::cout << "Spam! ";
                            }

Bu fonksiyon i�indeki d�ng�y� do�ru bir �ekilde test etmek i�in �� kez �a�r� yapmal�s�n�z: s�f�r iterasyon durumunu test etmek i�in spam(0),
bir iterasyon durumunu test etmek i�in spam(1), ve iki iterasyon durumunu test etmek i�in spam(2). E�er spam(2) �al���yorsa, o zaman spam(n) 
�al��mal�d�r, burada n > 2.

*** BEST -> D�ng�lerinizin farkl� iterasyon say�lar�yla do�ru bir �ekilde �al��t���ndan emin olmak i�in 0, 1, 2 testini kullan�n.

Farkl� girdi kategorilerini test etme
-------------------------------------

Parametre alan fonksiyonlar yazarken veya kullan�c� girdisi al�rken, farkl� giri� kategorilerinin nas�l i�lendi�ini d���n�n. Bu ba�lamda, 
"kategori" terimini, benzer karakteristiklere sahip bir giri� k�mesini ifade etmek i�in kullan�yoruz.

�rne�in, bir tamsay�n�n karek�k�n� �reten bir fonksiyon yazsam, hangi de�erlerle test etmek mant�kl� olurdu? Muhtemelen normal bir de�erle 
ba�lard�n�z, mesela 4. Ancak 0 ve negatif bir say� ile de test etmek iyi bir fikir olacakt�r.

��te kategori testi i�in temel y�nergeler:

    Tamsay�lar i�in, fonksiyonunuzun negatif de�erleri, s�f�r� ve pozitif de�erleri nas�l i�ledi�ini d���nm�� oldu�unuzdan emin olun. Ayr�ca, 
    bu konuyla ilgiliyse ta�ma durumunu kontrol etmelisiniz.

    Ondal�k say�lar i�in, fonksiyonunuzun beklenenden biraz daha b�y�k veya k���k olan hassasiyet sorunlar�na sahip de�erleri nas�l i�ledi�ini
    d���nm�� oldu�unuzdan emin olun. Denemek i�in iyi �ift tip de�erler, 0.1 ve -0.1 (beklenenden biraz daha b�y�k olan say�lar� test etmek i�in) ve
    0.6 ve -0.6 (beklenenden biraz daha k���k olan say�lar� test etmek i�in) olabilir.

    Diziler i�in, fonksiyonunuzun bo� bir dize, alfasay�sal bir dize, bo�luk i�eren dizeler (�nceki, sonraki ve i� dizeler) ve sadece bo�luklardan 
    olu�an dizeleri nas�l i�ledi�ini d���nm�� oldu�unuzdan emin olun.

    Fonksiyonunuz bir i�aret�i al�yorsa, nullptr'� da test etmeyi unutmay�n (bu anlam ifade etmiyorsa endi�elenmeyin, hen�z bu konuyu ele almad�k).

*** BEST -> Unit testimizin d�zg�nce �stesinden geldi�inden emin olmak i�in Farkl� kategorilerde olan girdi de�erlerini test et.


C++ daki genel semantic hatalar 
-------------------------------

S�zdizimi ve Semantik Hatalar�nda, C++ dilinin gramerine uygun olmayan kod yazd���n�zda olu�an s�zdizimi hatalar�n� ele ald�k. Derleyici, bu t�r 
hatalar� size bildirecek, bu nedenle bunlar� tespit etmek genellikle kolay ve genellikle d�zeltmesi basittir.

Ayr�ca, niyet etti�iniz �eyi yapmayan kod yazd���n�zda olu�an semantik hatalar� da ele ald�k. Derleyici genellikle semantik hatalar� tespit etmez 
(ancak baz� durumlarda ak�ll� derleyiciler uyar� olu�turabilir).

Semantik hatalar, program�n yanl�� sonu�lar �retmesine, d�zensiz davran��a neden olmas�na, program verilerini bozmas�na, program�n ��kmesine neden
olmas�na veya hi�bir etkisi olmamas�na yol a�abilir, �o�u durumda tan�mlanmam�� davran���n ayn� belirtilerini g�sterebilirler.

Programlar yazarken, neredeyse ka��n�lmaz bir �ekilde semantik hatalar yapacaks�n�z. Bunlardan baz�lar�n� program� kullanarak fark edebilirsiniz: 
�rne�in, bir labirent oyunu yaz�yorsan�z ve karakteriniz duvarlardan ge�ebiliyorsa. Program�n�z� test etmek (8.13 - Kodunuzu Teste Tan�tma) ayn� 
zamanda semantik hatalar� ortaya ��karmaya yard�mc� olabilir.

Ancak ba�ka bir �ey daha yard�mc� olabilir - ve bu, en yayg�n semantik hatalar�n hangi t�rlerinin oldu�unu bilmek, b�ylece bu durumlar�n do�ru 
oldu�undan emin olmak i�in biraz daha fazla zaman harcayabilirsiniz.

Bu derste, C++'da meydana gelen en yayg�n semantik hata t�rlerini (�o�u ak�� kontrol� ile ilgili olan) ele alaca��z.

Ko�ulsal Mant�k hatalar�
------------------------

En yayg�n semantik hata t�rlerinden biri, bir ko�ullu mant�k hatas�d�r. Ko�ullu mant�k hatas�, programc�n�n ko�ullu bir ifade veya d�ng�
�art�n�n mant���n� yanl�� kodlad���nda ortaya ��kar. ��te basit bir �rnek:

�rne�in x>5 yerine x>= 5 yazmak gibi ve bunlar�n looplar ile kullan�m�nda olu�an hatalar �rnek olarak verilebilir. 

- Sonsuz D�ng� hatalar� burada en s�k yap�lan hatalardan biri d�ng� sayac�n�n eklenmemesi veya artt�rma, azaltma gibi i�lemlerin unutulmas�
veya unsigned int de�erler kullanarak ta�maya neden olmak en genel hatalard�r. 

- For d�ng�s�nde bahsetti�imiz off-by-one hatalar� burada da yanl�� operat�r se�imi yani < >= bunlardan kaynaklanan hatad�r loop un 1 tane eksik 
veya fazla d�nmesi gibi. 

- Operat�r �ncelik s�ras�nda yap�lan yanl��lar. Mesela mant�ksal AND in mant�ksal OR dan �st�n olmas� gibi veya mant�ksal NOT �n > operat�r�nden
y�ksek �nceli�e sahip olmas�ndan bundan ka��nmak kolay parantezler kullanarak ka��nabiliriz.

- Float say�lar�n hassasiyet sorunlar�, float de�i�keni say�n�n tamam�n� depolamak i�in yeterli duyarl�l��a sahip de�ildir. Kar��la�t�rma 
i�lemlerinde float say� kullanmaktan ka��nmak gerekiyor aksi halde hassasiyetten sonra gelen say�larda yuvarlama hatalar�ndan dolay� program 
d�zg�n �al��mayabilir. 

- Tam say� b�lme hatas�, bir b�lme i�leminde operandlar�n her ikisi de tam say� olursa bu b�lmeye integer division yani tam say� b�lme i�lemi denir
Bu i�lemde olu�acak olan ondal�k bir say� varsa ondal�k k�sm� D���R�L�R. D��mesini istemiyorsak operandlar�n birini float veya double olarak 
yapmam�z gerekir. bunun i�inde static_cast<float>()  i kullanabiliz.

- Yanl��l�klar kullan�lan null ifadesi, Yayg�n if ifadesi problemlerinde, hi�bir �ey yapmayan ifadeler olan bo� ifadeleri ( null statement )
ele ald�k. Hat�rlayal�m if ( condition );
                             statements ->>> Burada bu ifade her t�rl� y�r�t�lecektir ��nk� noktal� virg�l kullanarak null statement yapt�k 
                                             Bu program�n ak���n� veya hesaplar� belki de bir roketi ate�leyebilir. :))

- Gerekti�inde bile�ik ifade kullanmamak, Bu hata da yine if ifadeleri ile alakal� dangling else problemini olu�turan sebep if ifadesinden 
sonra blok olu�turmazsak sadece 1 statement if e ba�l� olur bunu farketmeden 2.ifadeyi koydu�umuzda 2.ifade her t�rl� durumda y�r�t�lecektir.
Roket ate�lendi :D
*/
/*
                                            8.16 Hata tespiti ve Hatalarla u�ra�ma

Ders 8.15'te, C++'ta yayg�n semantik hatalar� inceledik. Yeni C++ programc�lar�n�n dil �zelliklerini yanl��l�kla yanl�� kullanmas�n�n bir sonucu
olarak ortaya ��kan hatalar kolayca d�zeltilebilir.

Ancak bir programdaki �o�u hata, genellikle programc� taraf�ndan yap�lan hatal� varsay�mlar veya uygun hata alg�lama/i�leme eksikli�i nedeniyle
meydana gelmez. �rne�in, bir ��rencinin notunu aramak i�in tasarlanm�� bir i�levde �unlar� varsaym�� olabilirsiniz:

        Aranan ��rencinin var olaca��.
        T�m ��renci adlar�n�n benzersiz olaca��.
        S�n�f�n harf notu sistemini kullanaca�� (ge�ti/kald� yerine).
Bu varsay�mlardan herhangi biri ger�ek de�ilse ne olur? E�er programc� bu durumlar� �nceden d���nmediyse, program bu durumlar ortaya ��kt���nda
(genellikle i�lev yaz�ld�ktan sonra uzun bir s�re sonra) muhtemelen ar�zalanacak veya ��kecektir.

* Bir i�lev bitti�inde, programc� �a�r�lan i�lemin ba�ar�l� oldu�unu varsayabilir, ancak bu do�ru de�ildir.
* Bir program giri� al�rken (kullan�c�dan veya bir dosyadan), programc� giri�in do�ru bi�imde ve semantik olarak ge�erli oldu�unu varsayabilir,
  ancak bu do�ru de�ildir.
* Bir i�lev �a�r�ld���nda, programc� arg�manlar�n semantik olarak ge�erli olaca��n� varsayabilir, ancak bu do�ru de�ildir.

Bir�ok yeni programc�, yaln�zca hata olmayan durumlar� i�eren "mutlu yolu" test eder. Ancak ayr�ca, i�lerin ters gidebilece�i "�zg�n yollar�"
da planlamal� ve test etmelisiniz. 3.10 dersinde belirtildi�i gibi, savunmac� programlama ( defensive programming ), yaz�l�m�n hem son
kullan�c�lar hem de geli�tiriciler (programc�lar kendileri veya di�erleri) taraf�ndan yanl�� kullan�lma olas�l�klar�n�n t�m�n� d���nme prati�idir.
Bir yanl�� kullan�m� �ng�rd���n�zde (veya ke�fetti�inizde), bir sonraki ad�m bununla ba�a ��kmakt�r.

Bu ders kapsam�nda, bir i�lev i�inde bir �eyler ters gitti�inde (yani, hatal� durumlar) ne yap�laca��n� tart��aca��z. Ard�ndan, kullan�c� giri�ini
do�rulama hakk�nda konu�acak ve ard�ndan varsay�mlar� belgeleme ve do�rulamaya yard�mc� olan kullan��l� bir arac� tan�taca��z.

Fonksiyonlarda olu�an hatalarla u�ra�ma
---------------------------------------
Fonksiyonlar bir�ok nedenle ba�ar�s�z olabilir; �a��ran, ge�ersiz bir de�erle bir arg�man iletebilir veya fonksiyonun i�inde bir �eyler ba�ar�s�z 
olabilir. �rne�in, bir dosyay� okumak i�in a�an bir fonksiyon, dosya bulunamazsa ba�ar�s�z olabilir.

Bu durumda, birka� se�ene�iniz vard�r. Bir hatay� i�lemenin en iyi yolu yoktur - ger�ekten sorunun do�as�na ve sorunun d�zeltilip 
d�zeltilemeyece�ine ba�l�d�r.

4 Genel strateji vard�r:
    1 - Hatay� fonksinun i�inde ��zmek
    2 - Hatay� ��zmek i�in hatay� fonksiyonu �a��rana iletmek
    3 - Program� durdurmak
    4 - Bir istisna f�rlatmak veya saymak .d    

1 Numaral� durum 
----------------
M�mk�nse, hatan�n meydana geldi�i fonksiyonda hatadan kurtulmak, hatan�n fonksiyon d���ndaki herhangi bir kodu etkilemeden s�n�rlan�p 
d�zeltilmesini sa�lar. Burada iki se�enek bulunmaktad�r: ba�ar� elde edilene kadar tekrar denemek veya ger�ekle�tirilen i�lemi iptal etmek.

E�er hata program�n kontrol� d���ndaki bir �eyden kaynaklanm��sa, program ba�ar� elde edilene kadar tekrar deneyebilir. �rne�in, e�er program�n
bir internet ba�lant�s�na ihtiyac� varsa ve kullan�c� ba�lant�s�n� kaybetti ise, program bir uyar� g�sterebilir ve ard�ndan bir d�ng� kullanarak
periyodik olarak internet ba�lant�s�n� yeniden kontrol edebilir. Alternatif olarak, e�er kullan�c� ge�ersiz bir giri� yapm��sa, program 
kullan�c�dan tekrar denemesini isteyebilir ve kullan�c� ge�erli bir giri� yapana kadar d�ng� i�inde kalabilir. Ge�ersiz giri�i i�leme ve d�ng� 
kullanarak tekrar deneme �rneklerini bir sonraki derste (8.17 -- std::cin ve ge�ersiz giri� i�leme) g�sterece�iz.

Alternatif bir strateji ise hatay� sadece yok saymak ve/veya i�lemi iptal etmektir. �rne�in:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                    }


Yukar�daki �rnekte, e�er kullan�c� y i�in ge�ersiz bir de�er g�nderirse, b�lme i�leminin sonucunu yazd�rmama talebini sadece yok sayar�z. Bunu
yapman�n ba�l�ca zorlu�u, �a��r�c� veya kullan�c�n�n bir �eyin yanl�� gitti�ini belirleme yolunun olmamas�d�r. Bu durumda, bir hata mesaj� 
yazd�rmak faydal� olabilir:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                        else
                            std::cout << "Error: Could not divide by zero\n";
                    }

Ancak, �a�r�lan fonksiyonun �a��ran fonksiyondan bir d�n�� de�eri �retmesi veya baz� faydal� yan etkileri olmas� bekleniyorsa, hatay� sadece yok
saymak bir se�enek olmayabilir.

2 Numaral� durum
----------------
�o�u durumda, hatayla kar��la��ld��� fonksiyonda hatay� makul bir �ekilde i�lemek m�mk�n olmayabilir. �rne�in, a�a��daki fonksiyonu d���n�n:

                    double doDivision(int x, int y)
                    {
                        return static_cast<double>(x) / y;
                    }
E�er y 0 ise, ne yapmal�y�z? Program mant���n� sadece atlayamay�z, ��nk� fonksiyon bir de�er d�nd�rmelidir. Kullan�c�dan yeni bir y de�eri
girmesini istememeliyiz ��nk� bu bir hesaplama fonksiyonu ve bunun i�ine giri� rutinlerini eklemek, bu fonksiyonu �a��ran program i�in uygun 
olabilir veya olmayabilir.

Bu t�r durumlarda, hatay� �a�rana iletmek ve umut etmek ki �a��ran bununla ba�a ��kabilir.

Bunu nas�l yapabiliriz?

E�er fonksiyonun void d�n�� t�r� varsa, ba�ar� veya ba�ar�s�zl��� g�steren bir Boole t�r� d�nd�rmek i�in de�i�tirilebilir. �rne�in, �u yerine:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                        else
                            std::cout << "Error: Could not divide by zero\n";
                    }

Bunu yapabiliriz: 
                    bool printDivision(int x, int y)
                    {
                        if (y == 0)
                        {
                            std::cout << "Error: could not divide by zero\n";
                            return false;
                        }

                        std::cout << static_cast<double>(x) / y;

                        return true;
                    }

Bu �ekilde, �a��ran fonksiyon, fonksiyonun bir nedenle ba�ar�s�z olup olmad���n� kontrol edebilir.

E�er fonksiyon normal bir de�er d�nd�r�yorsa, i�ler biraz daha karma��k hale gelir. Baz� durumlarda, d�n�� de�erlerinin tam aral��� kullan�lmaz. 
Bu t�r durumlarda, normalde normal olarak meydana gelmeyecek bir hata durumunu g�stermek i�in kullan�lamayacak bir d�n�� de�eri kullanabiliriz.
�rne�in, a�a��daki fonksiyonu d���n�n:

                    // x'in tersi 1/x dir.
                    double reciprocal(double x)
                    {
                        return 1.0 / x;
                    }

Bir say�n�n tersi, 1/x olarak tan�mlan�r ve bir say�n�n tersi ile �arp�lmas� sonucunda 1 elde edilir.

Ancak, e�er kullan�c� bu fonksiyonu reciprocal(0.0) olarak �a��r�rsa, s�f�ra b�lme hatas� ve program ��kmesi al�r�z, bu nedenle a��k�a bu duruma
kar�� korunmal�y�z. Ancak bu fonksiyon bir double de�eri d�nd�rmelidir, bu durumda ne t�r bir de�er d�nd�rmeliyiz? Bu fonksiyonun me�ru bir sonu�
olarak 0.0 �retmeyece�i ortaya ��kt���ndan, bir hata durumunu g�stermek i�in 0.0'� d�nd�rebiliriz.

                    // The reciprocal of x is 1/x, returns 0.0 if x=0
                    double reciprocal(double x)
                    {
                        if (x == 0.0)
                            return 0.0;

                        return 1.0 / x;
                    }

Ancak, tam d�n�� de�eri aral���na ihtiya� duyuluyorsa ve d�n�� de�eriyle bir hata g�sterimi yapmak m�mk�n de�ilse (��nk� �a��ran, d�n�� de�erinin
ge�erli bir de�er mi yoksa bir hata de�eri mi oldu�unu anlayamaz), o zaman bu durumu i�aretlemek zor olacakt�r.

Bu t�r bir durumda, `std::optional`'� kullanmak iyi bir se�enek olabilir. �u anda `std::optional`'� ele alm�yoruz ancak gelecekteki bir
g�ncellemede bunu yapmay� d���n�yoruz.

�l�mc�l Hatalar ( Fatal Errors )
--------------------------------
E�er hata program�n d�zg�n �al��maya devam edemeyecek kadar k�t�yse, bu duruma kurtar�lamaz hata (ayr�ca �l�mc�l hata olarak da adland�r�l�r)
denir. Bu t�r durumlarda en iyi �ey, program� sonland�rmakt�r. E�er kodunuz `main()` i�inde veya do�rudan `main()` taraf�ndan �a�r�lan bir 
fonksiyon i�inde ise, en iyi ��z�m `main()`'in bir d�nd�rme kodu ile sonlanmas�na izin vermektir. Ancak, e�er derinlemesine i� i�e ge�mi� bir
alt fonksiyonda bulunuyorsan�z, hatay� `main()`'e kadar iletmek uygun veya m�mk�n olmayabilir. Bu durumda, bir durma ifadesi 
(�rne�in `std::exit()`) kullan�labilir.

�rne�in:
                    double doDivision(int x, int y)
                    {
                        if (y == 0)
                        {
                            std::cout << "Error: Could not divide by zero\n";
                            std::exit(1);
                        }
                        return static_cast<double>(x) / y;
                    }
Exceptions ( �stisnalar diye �evirdim ama :))
---------------------------------------------
��nk� bir fonksiyondan �a��rana bir hata d�nd�rmek karma��kt�r (ve bunu yapman�n bir�ok farkl� yolu tutars�zl�kla sonu�lanabilir ve tutars�zl�k 
hatalara yol a�abilir), C++, hatalar� �a��rana iletmek i�in tamamen ayr� bir yol sunar: istisnalar.

Temel fikir, bir hata meydana geldi�inde bir istisna "f�rlat�lmas�"d�r. E�er mevcut fonksiyon hata durumunu "yakalamazsa", fonksiyonu �a��ran ki�i 
hatay� yakalama �ans�na sahiptir. E�er �a��ran ki�i hata durumunu yakalamazsa, �a��ran�n �a��r�c�s� hata durumunu yakalama �ans�na sahiptir. Hata,
�a�r� y���n� boyunca giderek yukar� do�ru hareket eder ve ya yakalan�r ve i�lenir (bu noktada y�r�tme normal �ekilde devam eder), ya da main() 
hatay� i�leyemezse (bu noktada program bir istisna hatas� ile sonland�r�l�r).

Bu konuyu, bu ��retici serisinin 27. b�l�m�nde ele al�yoruz.


std::cout, std::cerr ve loglama -> Ne zaman hangisini kullanmal�y�z
-------------------------------------------------------------------

Belki de std::cerr'�, std::cout'� ve bir metin dosyas�na loglama yapmay� ne zaman kullanman�z gerekti�ini merak ediyorsunuzdur.

Varsay�lan olarak, hem std::cout hem de std::cerr metni konsola yazd�r�r. Ancak, modern i�letim sistemleri ��k�� ak��lar�n� dosyalara y�nlendirmek
i�in bir yol sa�lar, b�ylece ��kt� daha sonra incelenmek veya otomatik i�leme tabi tutulmak �zere yakalanabilir.

Bu tart��ma i�in, iki t�r uygulamay� ay�rt etmek faydal�d�r:

* Etkile�imli uygulamalar, kullan�c�n�n ba�latmadan sonra etkile�imde bulunaca�� uygulamalard�r. Standalone ( ba��ms�z ve kendi ba��na �al��abilir )
  uygulamalar�n �o�u, oyunlar ve m�zik uygulamalar� gibi, genellikle bu kategoriye girer.
* Etkile�imsiz uygulamalar ise kullan�c� etkile�imi gerektirmeyen uygulamalard�r. Bu programlar�n ��kt�lar�, genellikle ba�ka bir uygulama i�in 
  giri� olarak kullan�labilir.

Etkile�imsiz uygulamalar i�inde iki t�r bulunmaktad�r:

1. **Ara�lar (Tools):**
   - Ara�lar, genellikle belirli bir hemen sonu� �retmek �zere ba�lat�lan ve bu sonucu �rettikten sonra sona eren etkile�imsiz uygulamalard�r.
   - Bir �rne�i, Unix'in "grep" komutudur. Bu, metni belirli bir desene g�re arayan bir yard�mc� programd�r.

2. **Servisler (Services):**
   - Servisler, genellikle arka planda sessizce �al��arak s�rekli bir i�levi yerine getiren etkile�imsiz uygulamalard�r.
   - Bir �rne�i, bir vir�s taray�c�s� olabilir. Bu, s�rekli olarak bilgisayar sistemini tarayarak vir�sleri kontrol eder.


Etkile�imsiz uygulamalar i�inde iki t�r bulunmaktad�r:

Ara�lar (Tools):
Ara�lar, genellikle belirli bir hemen sonu� �retmek �zere ba�lat�lan ve bu sonucu �rettikten sonra sona eren etkile�imsiz uygulamalard�r.
Bir �rne�i, Unix'in "grep" komutudur. Bu, metni belirli bir desene g�re arayan bir yard�mc� programd�r.

Servisler (Services):
Servisler, genellikle arka planda sessizce �al��arak s�rekli bir i�levi yerine getiren etkile�imsiz uygulamalard�r.
Bir �rne�i, bir vir�s taray�c�s� olabilir. Bu, s�rekli olarak bilgisayar sistemini tarayarak vir�sleri kontrol eder.

Bu iki t�r etkile�imsiz uygulama, farkl� kullan�m senaryolar�na ve i�levlere sahiptir. Ara�lar anl�k sonu�lar �retir ve sonra sonlan�rken, 
servisler s�rekli bir i�levi yerine getirerek uzun s�re �al��abilirler.


��te baz� k�yaslamalar:

* T�m geleneksel, kullan�c�ya y�nelik metinler i�in std::cout kullan�n.

* Etkile�imli bir program i�in, std::cout'u normal kullan�c�ya y�nelik hata mesajlar� i�in kullan�n (�rne�in, "Giri�iniz ge�ersizdi"). std::cerr
  veya bir log dosyas�n�, te�his sorunlar� i�in yard�mc� olabilecek ancak normal kullan�c�lar i�in muhtemelen ilgin� olmayan durum ve te�his
  bilgileri i�in kullan�n. Bu, teknik uyar�lar ve hatalar (�rne�in, fonksiyon x'e k�t� giri�), durum g�ncellemeleri (�rne�in, dosya x ba�ar�yla
  a��ld�, internet servisi x'e ba�lan�lamad�), uzun g�revlerin y�zde tamamlanmas� (�rne�in, kodlama %50 tamamland�) gibi �eyleri i�erebilir...

* Etkile�imsiz bir program (ara� veya servis) i�in, std::cerr'i yaln�zca hata ��kt�s� i�in kullan�n (�rne�in, dosya x a��lamad�). Bu, hatalar�n 
  normal ��kt�dan ayr� bir �ekilde g�r�nt�lenmesine veya ayr��t�r�lmas�na izin verir.
   
* ��lemeli bir do�aya sahip olan (�rne�in, belirli olaylar� i�leyen bir web taray�c�s� veya etkile�imsiz bir web sunucusu gibi) herhangi bir 
  uygulama t�r� i�in, olaylar�n incelenebilecek bir i�lem g�nl��� �retmek i�in bir log dosyas�n� kullan�n. �rne�in, �u anda hangi dosyay� 
  i�ledi�ini, tamamlanma y�zdesini, belirli bir hesaplama a�amas�na ne zaman ba�lad���n�, uyar�lar� ve hata mesajlar�n� ��kt�lamak.

| Kullan�m Durumu                                      | Uygun ��k�� Mekanizmalar�                     |
|------------------------------------------------------|-----------------------------------------------|
| Geleneksel, kullan�c�ya y�nelik metin ��kt�lar�      | std::cout                                     |
| Etkile�imli program, hata mesajlar�                  | std::cout (normal hata mesajlar�), std::cerr  |
| Etkile�imli program, durum g�ncellemeleri            | std::cerr, log dosyas�                        |
| Etkile�imsiz program (ara� veya servis), hata ��kt�s�| std::cerr                                     |
| ��lemeli uygulama (web taray�c�s�, web sunucusu vb.) | log dosyas�                                   |
*/