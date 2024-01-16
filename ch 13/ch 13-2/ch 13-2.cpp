#include <iostream>
int main()
{
    return 0;
}
/*
13.3 � Kapsams�z numaraland�rma giri�i ve ��kt�s�
-----------------------------------------------------
�nceki derste (13.2 � Kapsams�z numaraland�rmalar), numaraland�r�c�lar�n sembolik sabitler oldu�unu belirtmi�tik. Ancak, size
o zaman s�ylemedi�imiz �ey, numaraland�r�c�lar�n tamsay� sembolik sabitler oldu�udur. Sonu� olarak, numaraland�r�lm�� t�rler 
asl�nda bir tamsay� de�eri tutar.

Bu, charlarla yani karakterlerle olan duruma benzer. Dikkate al�n:
                    char ch { 'A' };

Bir karakter asl�nda sadece 1 baytl�k bir tamsay� de�eridir ve karakter �A� bir tamsay� de�erine (bu durumda, 65) d�n��t�r�l�r ve
saklan�r.

Bir numaraland�r�c� tan�mlad���m�zda, her numaraland�r�c� otomatik olarak numaraland�r�c� listesindeki konumuna dayal� bir tamsay�
de�eri atan�r. Varsay�lan olarak, ilk numaraland�r�c� tamsay� de�eri 0 atan�r ve her bir sonraki numaraland�r�c�, �nceki
numaraland�r�c�dan bir fazla de�ere sahiptir:
                    enum Color
                    {
                        black, // assigned 0
                        red, // assigned 1
                        blue, // assigned 2
                        green, // assigned 3
                        white, // assigned 4
                        cyan, // assigned 5
                        yellow, // assigned 6
                        magenta, // assigned 7
                    };

                    int main()
                    {
                        Color shirt{ blue }; // Bu asl�nda tamsay� de�eri 2'yi saklar

                        return 0;
                    }

Numaraland�r�c�lar�n de�erini a��k�a tan�mlamak m�mk�nd�r. Bu tamsay� de�erleri pozitif veya negatif olabilir ve di�er
numaraland�r�c�larla ayn� de�eri payla�abilir. Herhangi bir Kapsams�z numaraland�r�c�, �nceki numaraland�r�c�dan bir fazla
de�er verilir.

                    enum Animal
                    {
                        cat = -3,
                        dog,         // assigned -2
                        pig,         // assigned -1
                        horse = 5,
                        giraffe = 5, // shares same value as horse
                        chicken,      // assigned 6
                    };

Bu durumda, at ve z�rafa ayn� de�er verilmi�tir. Bu oldu�unda, numaraland�r�c�lar ay�rt edilemez hale gelir - temelde, at ve z�rafa birbirinin yerine ge�ebilir. C++ bunu sa�lasa da, ayn� numaraland�rmada iki numaraland�r�c�ya ayn� de�eri atamaktan genellikle ka��n�lmal�d�r.

*** BEST -> Numaraland�r�c�lar�n�za a��k�a de�er atamaktan ka��n�n, bunu yapmak i�in ge�erli bir nedeniniz olmad�k�a.

Kapsams�z numaraland�rmalar, tamsay� de�erlerine dolayl� olarak d�n��t�r�l�r

A�a��daki program� d���n�n:

                    #include <iostream>

                    enum Color
                    {
                        black, // assigned 0
                        red, // assigned 1
                        blue, // assigned 2
                        green, // assigned 3
                        white, // assigned 4
                        cyan, // assigned 5
                        yellow, // assigned 6
                        magenta, // assigned 7
                    };

                    int main()
                    {
                        Color shirt{ blue };

                        std::cout << "Your shirt is " << shirt << '\n'; // bu ne yapar?

                        return 0;
                    }

Numaraland�r�lm�� t�rler tamsay� de�erlerini tuttu�u i�in, bekledi�iniz gibi, bu �u ��kt�y� verir:

                    Your shirt is 2 
Bir numaraland�r�lm�� t�r, bir i�lev �a�r�s�nda veya bir operat�rle kullan�ld���nda, derleyici ilk olarak
numaraland�r�lm�� t�rle e�le�en bir i�lev veya operat�r bulmaya �al���r. �rne�in, derleyici 
                    std::cout << shirt 
derlemeye �al��t���nda, derleyici ilk olarak operator<<'in Color t�r�nden bir nesneyi (��nk� shirt Color t�r�ndedir) std::cout�a 
nas�l yazd�raca��n� bilip bilmedi�ini g�rmek i�in bakar. Bilmez.

Derleyici bir e�le�me bulamazsa, derleyici daha sonra Kapsams�z bir numaraland�rmay� veya numaraland�r�c�y� kar��l�k gelen
tamsay� de�erine dolayl� olarak d�n��t�r�r. ��nk� std::cout bir tamsay� de�erini yazd�rmay� bilir, shirt�teki de�er bir tamsay�ya 
d�n��t�r�l�r ve tamsay� de�eri 2 olarak yazd�r�l�r.

Numaraland�r�c� isimlerini yazd�rma
-----------------------------------
�o�u zaman, bir numaraland�rmay� bir tamsay� de�eri olarak yazd�rmak (�rne�in 2) istedi�imiz �ey de�ildir. Bunun yerine,
genellikle numaraland�r�c�n�n temsil etti�i ne olursa olsun ismini yazd�rmak isteriz (blue). Ancak bunu yapmak i�in, 
numaraland�rman�n tamsay� de�erini (2) numaraland�r�c� ad�na e�le�en bir dizeye (�blue�) d�n��t�rmenin bir yoluna ihtiyac�m�z var.

C++20 itibariyle, C++ bunu yapman�n kolay bir yolunu sunmuyor, bu y�zden kendi ��z�m�m�z� bulmam�z gerekiyor. Neyse ki, bu �ok zor
de�il. Bunu yapman�n tipik yolu, bir numaraland�r�lm�� t�r� parametre olarak alan ve ard�ndan kar��l�k gelen dizeyi ��kt� olarak
veren (veya dizeyi �a��r�c�ya d�nd�ren) bir i�lev yazmakt�r.

Bunu yapman�n tipik yolu, numaraland�rmam�z� her olas� numaraland�r�c�ya kar�� test etmektir.

                    // Bunun i�in if-else kullanmak verimsizdir
                    void renkYaz(Color renk)
                    {
                        if (renk == black) std::cout << "siyah";
                        else if (renk == red) std::cout << "red";
                        else if (renk == blue) std::cout << "blue";
                        else std::cout << "???";
                    }
Ancak, bunun i�in bir dizi if-else ifadesi kullanmak verimsizdir, ��nk� bir e�le�me bulunmadan �nce birden �ok kar��la�t�rma 
yap�lmas� gerekir. Ayn� �eyi yapman�n daha verimli bir yolu, bir switch ifadesi kullanmakt�r. A�a��daki �rnekte, Color'umuzu da
bir std::string olarak d�nd�rece�iz, b�ylece �a��ran ki�iye ad�yla (yazd�rmak dahil) istediklerini yapma esnekli�i verece�iz:

                    #include <iostream>
                    #include <string>

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };


                    // Bunu C++17 i�in daha iyi bir versiyonunu a�a��da g�sterece�iz
                    std::string getRenk(Color renk)
                    {
                        switch (renk)
                        {
                        case black: return "siyah";
                        case red:   return "red";
                        case blue:  return "blue";
                        default:    return "???";
                        }
                    }

                    int main()
                    {
                        Color gomlek { blue };

                        std::cout << "G�mle�iniz " << getRenk(gomlek) << '\n';

                        return 0;
                    }
                    �u ��kt�y� verir:

                    G�mle�iniz blue
Bu, if-else zincirinden muhtemelen daha iyi performans g�sterir (switch ifadeleri genellikle if-else zincirlerinden daha verimlidir)
ve okumas� da daha kolayd�r. Ancak, bu versiyon hala verimsizdir, ��nk� her fonksiyon �a�r�ld���nda bir std::string olu�turup
d�nd�rmemiz gerekiyor.

C++17'de, daha verimli bir se�enek, std::string'i std::string_view ile de�i�tirmektir. std::string_view, string literallerini 
kopyalamas� �ok daha az maliyetli bir �ekilde d�nd�rmemize olanak sa�lar.

                    #include <iostream>
                    #include <string_view> // C++17

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    constexpr std::string_view getRenk(Color renk) // C++17
                    {
                        switch (renk)
                        {
                        case black: return "siyah";
                        case red:   return "red";
                        case blue:  return "blue";
                        default:    return "???";
                        }
                    }

                    int main()
                    {
                        constexpr Color gomlek{ blue };

                        std::cout << "G�mle�iniz " << getRenk(gomlek) << '\n';

                        return 0;
                    }

Bir numaraland�r�c�y� nas�l yazd�raca��n� ��retme
-------------------------------------------------
Yukar�daki �rnek iyi i�lev g�rse de, numaraland�r�c� ad�n� almak i�in olu�turdu�umuz fonksiyonun ad�n� hala hat�rlamam�z gerekiyor.
Bu genellikle �ok zor olmasa da, bir�ok numaraland�rman�z varsa daha sorunlu hale gelebilir. Operat�r a��r� y�klemeyi kullanarak
(fonksiyon a��r� y�klemeye benzer bir yetenek), asl�nda program taraf�ndan tan�mlanan bir numaraland�rman�n de�erini nas�l 
yazd�raca��n� ��retebiliriz! Bunun nas�l �al��t���n� hen�z a��klamad�k, bu y�zden �imdilik biraz sihir olarak d���n�n:

                    #include <iostream>

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    // Operator<<'e bir Color nas�l yazd�r�laca��n� ��ret
                    // Bunun nas�l �al��t���n� hen�z a��klamad���m�z i�in �imdilik bunu sihir olarak d���n�n
                    // std::ostream, std::cout'un t�r�d�r
                    // D�n�� t�r� ve parametre t�r� referanslard�r (kopyalar�n yap�lmas�n� �nlemek i�in)!
                    std::ostream& operator<<(std::ostream& out, Color renk)
                    {
                        switch (renk)
                        {
                        case black: return out << "siyah";
                        case red:   return out << "red";
                        case blue:  return out << "blue";
                        default:    return out << "???";
                        }
                    }

                    int main()
                    {
                        Color gomlek{ blue };
                        std::cout << "G�mle�iniz " << gomlek << '\n'; // i�e yar�yor!

                        return 0;
                    }
                    �u ��kt�y� verir:

                    G�mle�iniz blue
Ders 21.4�te I/O operat�rlerinin a��r� y�klenmesini ele al�yoruz � I/O operat�rlerinin a��r� y�klenmesi. �imdilik bu kodu 
kopyalayabilir ve Color�u kendi numaraland�r�lm�� tipinizle de�i�tirebilirsiniz.

Numaraland�rma boyutu ve altta yatan tip (taban) ( ( underlying type or base )  )
---------------------------------------------------------------------------------
Bir numaraland�rman�n numaraland�r�c�lar� integral sabitlerdir. Numaraland�r�c�lar� temsil etmek i�in kullan�lan belirli integral
tipine altta yatan tip (veya taban ( underlying type or base ) ) denir.

Kapsams�z numaraland�r�c�lar i�in, C++ standard� altta yatan tip olarak hangi belirli integral tipinin kullan�lmas� gerekti�ini 
belirtmez. �o�u derleyici, numaraland�r�c� de�erlerini saklamak i�in daha b�y�k bir tip gerektirmedik�e, altta yatan tip olarak
int tipini kullan�r (bu, kapsams�z bir enum�un bir int ile ayn� boyutta olaca�� anlam�na gelir).

Farkl� bir altta yatan tip belirtmek m�mk�nd�r. �rne�in, baz� bant geni�li�i hassas ba�lamlarda (�r. bir a� �zerinden veri
g�nderme) daha k���k bir tip belirtmek isteyebilirsiniz:

                    #include <cstdint>  // for std::int8_t
                    #include <iostream>

                    // Use an 8-bit integer as the enum underlying type
                    enum Color : std::int8_t
                    {
                        black,
                        red,
                        blue,
                    };

                    int main()
                    {
                        Color c{ black };
                        std::cout << sizeof(c) << '\n'; // prints 1 (byte)

                        return 0;
                    }

*** BEST -> Bir numaraland�rman�n taban tipini sadece gerekli oldu�unda belirtin.

*** Uyar� -> std::int8_t ve std::uint8_t genellikle char tipleri i�in tip takma adlar�d�r, bu nedenle bu tiplerden herhangi birini
             enum taban� olarak kullanmak, numaraland�r�c�lar�n b�y�k olas�l�kla int de�erleri yerine char de�erleri olarak 
             yazd�r�lmas�na neden olacakt�r.

Tamsay�dan kapsams�z numaraland�r�c�ya d�n���m
----------------------------------------------
Derleyici, kapsams�z numaraland�r�c�lar� bir tamsay�ya a��k�a d�n��t�r�rken, bir tamsay�y� kapsams�z bir numaraland�r�c�ya a��k�a
d�n��t�rmez. A�a��dakiler bir derleyici hatas� �retecektir:

                    enum Pet // no specified base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
                        pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

                        return 0;
                    }

Bunu a�man�n iki yolu vard�r.

�lk olarak, derleyiciyi bir tamsay�y� kapsams�z bir numaraland�r�c�ya d�n��t�rmeye zorlayabilirsiniz static_cast kullanarak:

                    enum Pet // no specified base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
                        pet = static_cast<Pet>(3);       // our pig evolved into a whale!

                        return 0;
                    }

Birazdan bunun nerede kullan��l� olabilece�ine dair bir �rnek g�rece�iz.

�kincisi, C++17�de, kapsams�z bir numaraland�rman�n belirtilmi� bir taban� varsa, derleyici bir tamsay�y� kullanarak kapsams�z bir
numaraland�rmay� liste ba�latman�za izin verecektir:

                    enum Pet: int // we've specified a base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet1 { 2 }; // ok: integer ile liste ba�latma yapabilir
                        Pet pet2 (2);   // compile error: Direkt olarak integer ile ba�lat�lamaz
                        Pet pet3 = 2;   // compile error: Direkt olarak integer ile ba�lat�lamaz

                        pet1 = 3;       // compile error: �nteger ile atama yap�lamaz

                        return 0;
                    }

Kapsams�z numaraland�r�c� giri�i
--------------------------------
Pet, bir program taraf�ndan tan�mlanan bir tip oldu�u i�in, dil std::cin kullanarak bir Pet girmeyi bilmez:

                    #include <iostream>

                    enum Pet
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { pig };
                        std::cin >> pet; // compile error, std::cin Pet e nas�l girdi yapaca��n� bilmez

                        return 0;
                    }

Bunu a�mak i�in, bir tamsay�y� okuyabiliriz ve uygun numaraland�r�lm�� tipin bir numaraland�r�c�s�na d�n��t�rmek i�in static_cast
kullanabiliriz:

                    #include <iostream>

                    enum Pet
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };
                    int main()
                    {
                        Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
                        pet = static_cast<Pet>(3);       // our pig evolved into a whale!

                        return 0;
                    }

13.4 � Kapsaml� numaraland�rmalar ( enum class )
------------------------------------------------
C++'da kapsams�z numaraland�rmalar ayr�k t�rler olmas�na ra�men, t�r g�venli de�illerdir ve baz� durumlarda mant�kl� olmayan 
�eyler yapman�za izin verebilirler. A�a��daki durumu d���n�n:

                    #include <iostream>

                    int main()
                    {
                        enum Renk
                        {
                            red, // red
                            blue, // blue
                        };

                        enum Meyve
                        {
                            muz, // banana
                            elma, // apple
                        };

                        Renk renk { red }; // red
                        Meyve meyve { muz }; // banana

                        if (renk == meyve) // Derleyici renk ve meyveyi tam say�lar olarak kar��la�t�racak
                            std::cout << "renk ve meyve e�ittir\n"; // ve bunlar�n e�it oldu�unu bulacak!
                        else
                            std::cout << "renk ve meyve e�it de�ildir\n";

                        return 0;
                    }
                    ```
                    Bu, �unu yazd�r�r:

                    renk ve meyve e�ittir
Renk ve meyve kar��la�t�r�ld���nda, derleyici bir Renk ve Meyve'yi nas�l kar��la�t�raca��n� bilmek i�in bakar. Bilmiyor. Sonra,
Renk ve/veya Meyve'yi tam say�lara d�n��t�rmeyi dener ve bir e�le�me bulup bulamayaca��n� g�r�r. Sonunda derleyici, her ikisini de
tam say�lara d�n��t�r�rse, kar��la�t�rmay� yapabilece�ini belirler. Renk ve meyve, tam say� de�eri 0'a d�n��t�ren 
numaraland�r�c�lara ayarland���ndan, renk meyveye e�it olacakt�r.

Bu, semantik olarak mant�kl� de�ildir ��nk� renk ve meyve farkl� numaraland�rmalardan gelir ve kar��la�t�r�labilir olmalar�
ama�lanmam��t�r. Standart numaraland�r�c�larla, bunu �nlemenin kolay bir yolu yoktur.

Bu t�r zorluklar nedeniyle, ayr�ca ad alan� kirlili�i sorunu (kapsams�z numaraland�rmalar, numaraland�r�c�lar�n� k�resel ad 
alan�na koyarak k�resel kapsamda tan�mlan�r), C++ tasar�mc�lar�, numaraland�rmalar i�in daha temiz bir ��z�m�n faydal� olaca��n� 
belirledi.

Kapsaml� numaraland�rmalar
--------------------------
Bu ��z�m, kapsaml� numaraland�rma (C++'da genellikle enum class olarak adland�r�l�r, nedenleri k�sa s�re sonra a��k olacakt�r).
Kapsaml� numaraland�rmalar, kapsams�z numaraland�rmalara benzer �ekilde �al���r, ancak iki ana fark� vard�r: A��k�a tam say�lara
d�n��t�rmezler ve numaraland�r�c�lar sadece numaraland�rman�n kapsam b�lgesine yerle�tirilir (numaraland�rman�n tan�mland���
kapsam b�lgesine de�il).

Kapsaml� bir numaraland�rma yapmak i�in, enum class anahtar kelimelerini kullan�r�z. Kapsaml� numaraland�rma tan�m�n�n geri kalan�,
kapsams�z bir numaraland�rma tan�m�yla ayn�d�r. ��te bir �rnek:

                    #include <iostream>
                    int main()
                    {
                        enum class Renk // "enum class" bunu kapsams�z bir numaraland�rma yerine kapsaml� bir numaraland�rma 
                                        // olarak tan�mlar
                        {
                            red, // red, Renk'in kapsam b�lgesinin bir par�as� olarak kabul edilir
                            blue, // blue
                        };

                        enum class Meyve
                        {
                            muz, // muz, Meyve'nin kapsam b�lgesinin bir par�as� olarak kabul edilir
                            elma, // apple
                        };

                        Renk renk { Renk::red }; // not: red do�rudan eri�ilebilir de�il, 
                                                     // Renk::red kullanmam�z gerekiyor
                        Meyve meyve { Meyve::muz }; // not: muz do�rudan eri�ilebilir de�il, Meyve::muz kullanmam�z gerekiyor

                        if (renk == meyve) // derleme hatas�: derleyici, farkl� t�rler Renk ve Meyve'yi nas�l kar��la�t�raca��n�
                                           // bilmiyor
                            std::cout << "renk ve meyve e�ittir\n";
                        else
                            std::cout << "renk ve meyve e�it de�ildir\n";

                        return 0;
                    }

Bu program, kapsaml� numaraland�rman�n ba�ka bir t�rle kar��la�t�r�lacak herhangi bir t�re d�n��t�rmeyece�i i�in 19. sat�rda bir 
derleme hatas� olu�turur.

Bir kenara not:
S�n�f anahtar kelimesi (statik anahtar kelimesiyle birlikte), C++ dilinde en �ok a��r� y�klenmi� anahtar kelimelerden biridir ve
ba�lama ba�l� olarak farkl� anlamlara gelebilir. Kapsaml� numaraland�rmalar s�n�f anahtar kelimesini kullanmas�na ra�men, bir 
"s�n�f t�r�" olarak kabul edilmezler (bu, yap�lar, s�n�flar ve birlikler ( struct, classes and unions ) i�in ayr�lm��t�r).

Bu ba�lamda "enum struct" da �al���r ve enum class ile ayn� �ekilde davran�r. Ancak, enum struct'�n kullan�m� gayriidiomatiktir,
bu y�zden kullan�m�ndan ka��n�n.

Kapsaml� numaraland�rmalar kendi kapsam b�lgelerini tan�mlar
------------------------------------------------------------
Kapsams�z numaraland�rmalar, numaraland�r�c�lar�n� numaraland�rman�n kendisiyle ayn� kapsama yerle�tirirken, kapsaml�
numaraland�rmalar numaraland�r�c�lar�n� yaln�zca numaraland�rman�n kapsam b�lgesine yerle�tirir. Ba�ka bir deyi�le, kapsaml� 
numaraland�rmalar numaraland�r�c�lar� i�in bir ad alan� gibi davran�r. Bu yerle�ik ad alan�, kapsaml� numaraland�rmalar�n k�resel 
kapsamda kullan�ld���nda k�resel ad alan� kirlili�ini azalt�r ve ad �ak��malar�n�n potansiyelini azalt�r.

Bir kapsaml� numaraland�r�c�ya eri�mek i�in, ona sanki kapsaml� numaraland�rman�n ayn� ad�n� ta��yan bir ad alan�nda gibi
davran�r�z:
                        #include <iostream>

                        int main()
                        {
                            enum class Renk // "enum class" bunu kapsams�z bir enum yerine kapsaml� bir enum olarak tan�mlar
                            {
                                red, // red Color �n kapsam b�lgesinin bir par�as� olarak d���n�l�r
                                blue,
                            };

                            std::cout << red << '\n';        // derleme hatas�: red bu kapsam b�lgesinde tan�mlanmam��
                            std::cout << Renk::red << '\n'; // derleme hatas�: std::cout bunu nas�l yazd�raca��n� bilmiyor 
                                                                // (a��k�a int'e d�n��t�rmez)

                            Renk renk { Renk::blue }; // tamam

                            return 0;
                        }

Kapsaml� numaraland�rmalar, numaraland�r�c�lar� i�in kendi i�sel ad alanlar�n� sundu�undan, kapsaml� numaraland�rmalar� ba�ka bir
kapsam b�lgesine (�rne�in bir ad alan�na) koyman�n bir gereklili�i yoktur, aksi takdirde gereksiz olurdu.

Kapsaml� numaraland�rmalar a��k�a tam say�lara d�n��t�rmez

Kapsams�z numaraland�r�c�lar�n aksine, kapsaml� numaraland�r�c�lar a��k�a tam say�lara d�n��t�rmez. �o�u durumda, bu iyi bir �eydir
��nk� nadiren mant�kl�d�r ve farkl� numaraland�rmalardan numaraland�r�c�lar� kar��la�t�rmak veya red + 5 gibi semantik hatalar�
�nlemeye yard�mc� olur.

Ayn� kapsaml� numaraland�rma i�indeki numaraland�r�c�lar� hala kar��la�t�rabilece�inizi unutmay�n (��nk� ayn� t�rdendirler):

                    #include <iostream>
                    int main()
                    {
                        enum class Renk
                        {
                            red, 
                            blue, 
                        };

                        Renk shirt { Renk::red }; 

                        if (shirt == Renk::red) // bu Renk ile Renk::red kar��la�t�rmas� tamam
                            std::cout << "shirt red!\n";
                        else if (shirt == Renk::blue)
                            std::cout << "shirt blue!\n";

                        return 0;
                    }

Bazen, bir kapsaml� numaraland�r�c�y� bir tamsay� de�eri olarak ele alman�n yararl� oldu�u durumlar vard�r. Bu durumlarda, bir
kapsaml� numaraland�r�c�y� bir tamsay�ya a��k�a d�n��t�rebilirsiniz, bunun i�in static_cast kullanabilirsiniz. C++23'te daha iyi
bir se�enek, std::to_underlying()'i (<utility> ba�l���nda tan�mlanm��t�r) kullanmakt�r, bu da bir numaraland�r�c�y�
numaraland�rman�n alt�nda yatan t�r�n bir de�erine d�n��t�r�r.

                    #include <iostream>
                    #include <utility> // for std::to_underlying() (C++23)

                    int main()
                    {
                        enum class Renk
                        {
                            red, // red
                            blue, // blue
                        };

                        Renk renk { Renk::blue }; // blue

                        std::cout << renk << '\n'; // �al��maz, ��nk� a��k bir d�n���m int'e yok
                        std::cout << static_cast<int>(renk) << '\n';   // a��k d�n���m int'e, 1 yazd�r�r
                        std::cout << std::to_underlying(renk) << '\n'; // alt�nda yatan t�re d�n��t�r, 1 yazd�r�r (C++23)

                        return 0;
                    }

Tersine, bir tamsay�y� bir kapsaml� numaraland�r�c�ya da static_cast yapabilirsiniz, bu kullan�c�dan giri� yaparken yararl�
olabilir:

                #include <iostream>

                int main()
                {
                    enum class EvcilHayvan
                    {
                        kedi, // assigned 0
                        k�pek, // assigned 1
                        domuz, // assigned 2
                        balina, // assigned 3
                    };

                    std::cout << "Bir evcil hayvan girin (0=kedi, 1=k�pek, 2=domuz, 3=balina): ";

                    int giri�{};
                    std::cin >> giri�; // bir tamsay� girin

                    EvcilHayvan evcilHayvan{ static_cast<EvcilHayvan>(giri�) }; // tamsay�m�z� bir EvcilHayvan'a static_cast yap�n

                    return 0;
                }

C++17 itibariyle, bir tamsay� de�eri kullanarak bir kapsaml� numaraland�rmay� liste ba�latma i�lemi yapabilirsiniz ve static_cast 
gerektirmez (ve kapsams�z bir numaraland�rman�n aksine, bir taban( base ) belirtmeniz gerekmez).

*** BEST -> Kapsams�z numaraland�rmalar yerine kapsaml� numaraland�rmalar� tercih edin, aksi takdirde bunu yapmak i�in ge�erli bir
            neden varsa.

Kapsaml� numaraland�rmalar�n sundu�u avantajlara ra�men, kapsams�z numaraland�rmalar hala C++'da yayg�n olarak kullan�l�yor ��nk�
bazen a��k�a int'e d�n���m� istiyoruz (�ok fazla static_cast yapmak can s�k�c� olabilir) ve ek ad alan�na ihtiyac�m�z yok.

using enum kullanma C++20
-------------------------
C++20'de tan�t�lan bir using enum ifadesi, bir enum'daki t�m numaraland�r�c�lar� mevcut kapsama aktar�r. Bir enum class t�r�yle
kullan�ld���nda, bu bize enum class numaraland�r�c�lar�na her birini enum class ad� ile �ne koymadan eri�memizi sa�lar.

Bu, switch ifadesi i�indeki gibi bir�ok ayn�, tekrarlanan �nekler olaca�� durumlarda yararl� olabilir:

                #include <iostream>
                #include <string_view>

                enum class Renk
                {
                    siyah,
                    k�rm�z�,
                    mavi,
                };

                constexpr std::string_view getRenk(Renk renk)
                {
                    using enum Renk; // t�m Renk numaraland�r�c�lar�n� mevcut kapsama getirin (C++20)
                    // Art�k Renk numaraland�r�c�lar�na Renk:: �neki kullanmadan eri�ebiliriz

                    switch (renk)
                    {
                    case siyah: return "siyah"; // not: siyah yerine Renk::siyah
                    case k�rm�z�:   return "k�rm�z�";
                    case mavi:  return "mavi";
                    default:    return "???";
                    }
                }

                int main()
                {
                    Renk g�mlek{ Renk::mavi };

                    std::cout << "G�mle�iniz " << getRenk(g�mlek) << '\n';

                    return 0;
                }

Yukar�daki �rnekte, Renk bir enum class, bu y�zden normalde numaraland�r�c�lar� tam nitelikli bir ad� kullanarak eri�iriz
(�r. Renk::mavi). Ancak, getColor() fonksiyonu i�inde, using enum Renk; ifadesini ekledik, bu da bize bu numaraland�r�c�lar�
Renk:: �neki olmadan eri�memizi sa�lar.

Bu, switch ifadesi i�inde birden �ok, gereksiz, a��k �nekler olmas�n� �nler.
*/
