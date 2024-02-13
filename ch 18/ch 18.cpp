#include <iostream>

int main()
{
    return 0;
}
/*
18.1 � Bir diziyi se�im s�ralamas� kullanarak s�ralama ( Selection Sort )
-------------------------------------------------------------------------
S�ralama i�in bir durum
-----------------------
Bir diziyi s�ralama, dizideki t�m ��eleri belirli bir s�raya g�re d�zenleme s�recidir. Bir diziyi s�ralaman�n faydal� olabilece�i bir�ok farkl�
durum vard�r. �rne�in, e-posta program�n�z genellikle e-postalar� al�nd��� zamana g�re g�sterir, ��nk� en son e-postalar genellikle daha alakal�
kabul edilir. Ki�i listesine gitti�inizde, isimler genellikle alfabetik s�radad�r, ��nk� arad���n�z ismi bu �ekilde bulmak daha kolayd�r.
Her iki sunum da verileri sunmadan �nce s�ralama i�lemi gerektirir.

Bir diziyi s�ralamak, bir diziyi aramay� sadece insanlar i�in de�il, bilgisayarlar i�in de daha verimli hale getirebilir. �rne�in, bir ismin bir
isim listesinde olup olmad���n� bilmek istedi�imiz bir durumu d���n�n. Bir ismin listede olup olmad���n� g�rmek i�in, dizideki her ��eyi kontrol 
etmemiz ve ismin orada olup olmad���n� g�rmemiz gerekir. Bir�ok ��esi olan bir dizi i�in, hepsini aramak pahal� olabilir.

Ancak, �imdi isimlerin alfabetik olarak s�raland��� bir dizimiz oldu�unu varsayal�m. Bu durumda, alfabetik olarak arad���m�zdan daha b�y�k bir
isimle kar��la�t���m�z noktaya kadar sadece arama yapmam�z gerekiyor. O noktada, ismi bulamad�ysak, geri kalan dizide olmad���n� biliyoruz,
��nk� dizide bakmad���m�z t�m isimlerin alfabetik olarak daha b�y�k oldu�u garanti edilir!

S�ralanm�� dizileri aramak i�in daha iyi algoritmalar oldu�u ortaya ��kt�. Basit bir algoritma kullanarak, 1.000.000 ��e i�eren bir diziyi sadece
20 kar��la�t�rma kullanarak arayabiliriz! Dezavantaj� tabii ki, bir diziyi s�ralaman�n nispeten pahal� olmas�d�r ve genellikle bir diziyi aramay� 
h�zland�rmak i�in bir diziyi s�ralamaya de�mez, aksi takdirde bir�ok kez arayacaks�n�z.

Baz� durumlarda, bir diziyi s�ralamak aramay� gereksiz k�lar. En iyi test skorunu bulmak istedi�imiz ba�ka bir �rne�i d���n�n. Dizi s�ralanmam��sa,
en y�ksek test skorunu bulmak i�in dizideki her ��eye bakmam�z gerekir. Liste s�ralanm��sa, en iyi test skoru ilk veya son pozisyonda olacakt�r
(artan veya azalan s�raya g�re s�ralad���m�za ba�l� olarak), bu y�zden hi� arama yapmam�za gerek yok!

S�ralaman�n nas�l �al��t���
---------------------------
S�ralama genellikle, dizi ��elerinin �iftlerini tekrar tekrar kar��la�t�rarak ve belirli bir kriteri kar��lad�klar�nda onlar� de�i�tirerek 
ger�ekle�tirilir. Bu ��elerin hangi s�rayla kar��la�t�r�ld���, hangi s�ralama algoritmas�n�n kullan�ld���na ba�l�d�r. Kriter, listenin nas�l
s�ralanaca��na (�r. artan veya azalan s�ra) ba�l�d�r.

�ki ��eyi de�i�tirmek i�in, C++ standart k�t�phanesinden std::swap() fonksiyonunu kullanabiliriz, bu fonksiyon utility ba�l���nda tan�mlanm��t�r.

                #include <iostream>
                #include <utility>

                int main()
                {
                    int x{ 2 };
                    int y{ 4 };
                    std::cout << "Takas �ncesi: x = " << x << ", y = " << y << '\n';
                    std::swap(x, y); // x ve y de�erlerini takas et
                    std::cout << "Takas sonras�:  x = " << x << ", y = " << y << '\n';

                    return 0;
                }

                Bu program �unu yazd�r�r:

                Takas �ncesi: x = 2, y = 4
                Takas sonras�:  x = 4, y = 2
Takas sonras�, x ve y'nin de�erlerinin de�i�tirildi�ini unutmay�n!

Se�im s�ralamas� ( Selection Sort )
-----------------------------------
Bir diziyi s�ralaman�n bir�ok yolu vard�r. Se�im s�ralamas� muhtemelen anlamas� en kolay s�ralamad�r, bu da onu daha yava� s�ralamalardan biri 
olmas�na ra�men ��retmek i�in iyi bir aday yapar.

Se�im s�ralamas�, bir diziyi en k���kten en b�y��e s�ralamak i�in a�a��daki ad�mlar� ger�ekle�tirir:

*- Dizi indeksi 0'dan ba�layarak, t�m diziyi en k���k de�eri bulmak i�in ara
*- Dizide bulunan en k���k de�eri, indeks 0'daki de�erle de�i�tir
*- Sonraki indeksten ba�layarak ad�mlar� 1 ve 2'yi tekrarla

Ba�ka bir deyi�le, dizideki en k���k ��eyi bulaca��z ve onu ilk konuma ta��yaca��z. Sonra bir sonraki en k���k ��eyi bulaca��z ve onu ikinci konuma
ta��yaca��z. Bu s�re�, ��elerimiz t�kenene kadar tekrarlanacak.

��te bu algoritman�n 5 ��e �zerinde �al��mas�n�n bir �rne�i. Bir �rnek diziyle ba�layal�m:

                { 30, 50, 20, 10, 40 }

�ncelikle, en k���k ��eyi buluyoruz, indeks 0'dan ba�layarak:

                { 30, 50, 20, 10, 40 }

Sonra bunu indeks 0'daki ��eyle de�i�tiriyoruz:

                { 10, 50, 20, 30, 40 }

Art�k ilk ��e s�raland���na g�re, onu g�rmezden gelebiliriz. �imdi, en k���k ��eyi buluyoruz, indeks 1'den ba�layarak:

                { 10, 50, 20, 30, 40 }

Ve bunu indeks 1'deki ��eyle de�i�tiriyoruz:

                { 10, 20, 50, 30, 40 }

Art�k ilk iki ��eyi g�rmezden gelebiliriz. �ndeks 2'den ba�layarak en k���k ��eyi bulun:

                { 10, 20, 50, 30, 40 }

Ve bunu indeks 2'deki ��eyle de�i�tirin:

                { 10, 20, 30, 50, 40 }

�ndeks 3'ten ba�layarak en k���k ��eyi bulun:

                { 10, 20, 30, 50, 40 }

Ve bunu indeks 3'teki ��eyle de�i�tirin:

                { 10, 20, 30, 40, 50 }

Son olarak, indeks 4'ten ba�layarak en k���k ��eyi bulun:

                { 10, 20, 30, 40, 50 }

Ve bunu indeks 4'teki ��eyle de�i�tirin (ki bu hi�bir �ey yapmaz):

                { 10, 20, 30, 40, 50 }

Bitti!
                { 10, 20, 30, 40, 50 }

Son kar��la�t�rman�n her zaman kendisiyle olaca��n� unutmay�n (ki bu gereksizdir), bu y�zden asl�nda dizinin sonundan 1 ��e �nce durabiliriz.

C++'da Se�im S�ralamas�
-----------------------
��te bu algoritman�n C++'da nas�l uyguland���:

                #include <iostream>
                #include <iterator>
                #include <utility>

                int main()
                {
	                int array[]{ 30, 50, 20, 10, 40 };
	                constexpr int length{ static_cast<int>(std::size(array)) };

	                // Dizinin her bir ��esinden ge�in
	                // (sonuncusu hari�, ��nk� oraya geldi�imizde zaten s�ralanm�� olacak)
	                for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	                {
		                // smallestIndex, bu iterasyonda kar��la�t���m�z en k���k ��enin indeksidir
		                // �lk olarak, en k���k ��enin bu iterasyonun ilk ��esi oldu�unu varsay�n
		                int smallestIndex{ startIndex };

		                // Sonra geri kalan dizide daha k���k bir ��e aray�n
		                for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
		                {
			                // E�er daha �nce buldu�umuz en k���kten daha k���k bir ��e bulmu�sak
			                if (array[currentIndex] < array[smallestIndex])
				                // o zaman onu takip edin
				                smallestIndex = currentIndex;
		                }

		                // smallestIndex �imdi kalan dizideki en k���k ��enin indeksidir
				                // ba�lang�� ��emizi en k���k ��emizle de�i�tirin (bu onu do�ru yere s�ralar)
		                std::swap(array[startIndex], array[smallestIndex]);
	                }

	                // Art�k t�m dizi s�raland���na g�re, i�e yarad���n�n kan�t� olarak s�ralanm�� dizimizi yazd�r�n
	                for (int index{ 0 }; index < length; ++index)
		                std::cout << array[index] << ' ';

	                std::cout << '\n';

	                return 0;
                }

Bu algoritman�n en kafa kar��t�r�c� k�sm�, bir d�ng�n�n i�inde ba�ka bir d�ng� (i� i�e d�ng� denir). D�� d�ng� (startIndex) her bir ��eyi tek tek
yinelemektedir. D�� d�ng�n�n her iterasyonu i�in, i� d�ng� (currentIndex) kalan dizideki en k���k ��eyi bulmak i�in kullan�l�r (startIndex+1'den
ba�layarak). smallestIndex, i� d�ng� taraf�ndan bulunan en k���k ��enin indeksini takip eder. Sonra smallestIndex, startIndex ile de�i�tirilir. 
Son olarak, d�� d�ng� (startIndex) bir ��e ilerler ve s�re� tekrarlan�r.

�pucu: E�er yukar�daki program�n nas�l �al��t���n� anlamakta zorlan�yorsan�z, bir �rnek durumu ka��da �izerek �al��mak yard�mc� olabilir.
Ba�lang��taki (s�ralanmam��) dizi elemanlar�n� ka��d�n �st k�sm�na yatay olarak yaz�n. Hangi elemanlar�n startIndex, currentIndex ve smallestIndex
taraf�ndan indekslendi�ini g�steren oklar �izin. Program� manuel olarak izleyin ve indeksler de�i�tik�e oklar� yeniden �izin. D�� d�ng�n�n her 
iterasyonu i�in, dizinin mevcut durumunu g�steren yeni bir sat�r ba�lat�n.

�simleri s�ralamak ayn� algoritmay� kullan�r. Sadece dizi t�r�n� int'ten std::string'e de�i�tirin ve uygun de�erlerle ba�lat�n.

std::sort
---------
Dizileri s�ralamak �ok yayg�n oldu�u i�in, C++ standart k�t�phanesi std::sort ad�nda bir s�ralama fonksiyonu i�erir. std::sort, <algorithm>
ba�l���nda bulunur ve bir dizi �zerinde �u �ekilde �a�r�labilir:

                #include <algorithm> // for std::sort
                #include <iostream>
                #include <iterator> // for std::size

                int main()
                {
                    int array[]{ 30, 50, 20, 10, 40 };

                    std::sort(std::begin(array), std::end(array));

                    for (int i{ 0 }; i < static_cast<int>(std::size(array)); ++i)
                        std::cout << array[i] << ' ';

                    std::cout << '\n';

                    return 0;
                }

Varsay�lan olarak, std::sort, eleman �iftlerini kar��la�t�rmak i�in operator< kullanarak ve gerekirse onlar� de�i�tirerek (yukar�daki se�im
s�ralama �rne�imiz gibi) artan s�ra ile s�ralar.

18.2 � �terat�rlere Giri�
-------------------------
Bir dizi (veya ba�ka bir yap�) veriyi yinelemek programlamada olduk�a yayg�n bir �eydir. Ve �imdiye kadar, bunu yapman�n bir�ok farkl� yolunu
ele ald�k: d�ng�ler ve bir indeks (for-d�ng�leri ve while d�ng�leri), i�aret�iler ve i�aret�i aritmeti�i ve aral�k tabanl� for-d�ng�leri ile:

                #include <array>
                #include <cstddef>
                #include <iostream>

                int main()
                {
                    // In C++17, the type of variable data is deduced to std::array<int, 7>
                    // If you get an error compiling this example, see the warning below
                    std::array data{ 0, 1, 2, 3, 4, 5, 6 };
                    std::size_t length{ std::size(data) };

                    // while-loop with explicit index
                    std::size_t index{ 0 };
                    while (index < length)
                    {
                        std::cout << data[index] << ' ';
                        ++index;
                    }
                    std::cout << '\n';

                    // for-loop with explicit index
                    for (index = 0; index < length; ++index)
                    {
                        std::cout << data[index] << ' ';
                    }
                    std::cout << '\n';

                    // for-loop with pointer (Note: ptr can't be const, because we increment it)
                    for (auto ptr{ &data[0] }; ptr != (&data[0] + length); ++ptr)
                    {
                        std::cout << *ptr << ' ';
                    }
                    std::cout << '\n';

                    // range-based for loop
                    for (int i : data)
                    {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';

                    return 0;
                }

Uyar�

Bu dersin �rnekleri, bir �ablon de�i�keninin ba�lat�c�s�ndan �ablon arg�manlar�n� ��karmak i�in C++17 �zelli�i olan s�n�f �ablonu arg�man
��kar�m�n� kullan�r. Yukar�daki �rnekte, derleyici std::array data{ 0, 1, 2, 3, 4, 5, 6 }; g�r�nce, std::array<int, 7> data { 0, 1, 2, 3, 4, 5, 6 };
istedi�imizi ��kar�r.

E�er derleyiciniz C++17'yi desteklemiyorsa, �data�dan �nce eksik �ablon arg�manlar�� gibi bir hata al�rs�n�z. Bu durumda, en iyi se�ene�iniz,
ders 0.12 -- Derleyicinizi Yap�land�rma: Bir dil standard� se�me b�l�m�ne g�re C++17'yi etkinle�tirmektir. E�er yapamazsan�z, s�n�f �ablonu arg�man
��kar�m�n� kullanan sat�rlar�, a��k �ablon arg�manlar� olan sat�rlarla de�i�tirebilirsiniz (�rne�in, std::array data{ 0, 1, 2, 3, 4, 5, 6 }; yerine
std::array<int, 7> data { 0, 1, 2, 3, 4, 5, 6 }; kullan�n).

�ndeksleri kullanarak d�ng� yapmak, yaln�zca indisi elemanlara eri�im i�in kullan�yorsak gere�inden fazla yaz�m gerektirir. Ayr�ca bu, yaln�zca
konteyn�r�n (�r. dizi) elemanlara do�rudan eri�im sa�lamas� durumunda �al���r (diziler bunu yapar, ancak listeler gibi di�er baz� konteyn�r t�rleri
yapmaz).

��aret�ilerle ve i�aret�i aritmeti�i ile d�ng� yapmak, ayr�nt�l�d�r ve i�aret�i aritmeti�inin kurallar�n� bilmeyen okuyucular i�in kafa kar��t�r�c�
olabilir. ��aret�i aritmeti�i de yaln�zca elemanlar haf�zada ard���k oldu�unda �al���r (bu diziler i�in do�ru, ancak listeler, tree'ler ve map'lar
gibi di�er konteyn�r t�rleri i�in do�ru de�il).

Aral�k tabanl� for-d�ng�leri biraz daha ilgin�tir, ��nk� konteyn�r�m�zdan ge�me mekanizmas� gizlidir - ve yine de, t�m �e�itli yap�lar i�in �al���r
(diziler, listeler, tree'ler, map'lar, vb...). Bunlar nas�l �al���r? �terat�rler kullan�rlar.

�terat�rler
-----------
Bir iterat�r, bir konteyn�r�n (�r. bir dizideki de�erler veya bir stringdeki karakterler) �zerinden ge�mek i�in tasarlanm�� bir nesnedir ve 
bu yolculuk boyunca her bir elemana eri�im sa�lar.

Bir konteyn�r, farkl� t�rlerde iterat�rler sa�layabilir. �rne�in, bir dizi konteyn�r�, dizinin ileri s�ras�nda y�r�yen bir ileri iterat�r ve
dizinin ters s�ras�nda y�r�yen bir ters iterat�r sunabilir.

Uygun t�rde bir iterat�r olu�turuldu�unda, programc� daha sonra iterat�r�n sa�lad��� aray�z� kullanabilir ve hangi t�rden bir gezinme yap�ld��� 
veya verilerin konteyn�rda nas�l sakland��� konusunda endi�elenmeden elemanlar� gezinebilir ve eri�ebilir. Ve ��nk� C++ iterat�rleri genellikle
gezinme (operator++ ile bir sonraki elemana ge�me) ve eri�im (operator* ile mevcut elemana eri�me) i�in ayn� aray�z� kullan�r, tutarl� bir y�ntemle
�e�itli farkl� konteyn�r t�rlerinden ge�ebiliriz.

��aret�iler bir iterat�r olarak
-------------------------------
En basit t�rde iterat�r bir i�aret�idir, bu (i�aret�i aritmeti�i kullanarak) haf�zada ard���k olarak saklanan veriler i�in �al���r. ��te bir 
i�aret�i ve i�aret�i aritmeti�i kullanarak basit bir dizi gezinmesine d�nelim:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array data{ 0, 1, 2, 3, 4, 5, 6 };

                    auto begin{ &data[0] };
                    // not edin ki bu, son elemandan bir ad�m �tesini g�sterir
                    auto end{ begin + std::size(data) };

                    // i�aret�i ile for-d�ng�s�
                    for (auto ptr{ begin }; ptr != end; ++ptr) // ++ bir sonraki elemana ge�mek i�in
                    {
                        std::cout << *ptr << ' '; // �ndireksiyon ile mevcut eleman�n de�erini al�r
                    }
                    std::cout << '\n';

                    return 0;
                }

                ��kt�:

                0 1 2 3 4 5 6
Yukar�da, iki de�i�ken tan�mlad�k: begin (konteyn�r�m�z�n ba�lang�c�n� g�sterir) ve end (bir biti� noktas�n� i�aretler). Diziler i�in,
biti� i�aret�isi genellikle konteyn�r�n bir eleman daha i�erdi�i durumda son eleman�n olaca�� yerdir.

��aret�i daha sonra ba�lang�� ve biti� aras�nda d�ng� yapar ve mevcut eleman, i�aret�inin dereferans� ile eri�ilebilir.

Uyar�

Biti� i�aret�isini adres operat�r� ve dizi s�zdizimi kullanarak hesaplamaya meyilli olabilirsiniz:

                int* end{ &data[std::size(data)] };

Ancak bu, tan�ms�z bir davran��a neden olur, ��nk� data[std::size(data)] a��k�a dizinin sonundaki bir eleman� dereferans eder.

Bunun yerine, kullan�n:

                int* end{ data.data() + std::size(data) }; // data() ilk elemana bir i�aret�i d�nd�r�r

Standart k�t�phane yineleyicileri
---------------------------------
Yineleme o kadar yayg�n bir i�lem ki, t�m standart k�t�phane konteynerleri yinelemeyi do�rudan destekler. Kendi ba�lang�� ve biti� noktalar�m�z�
hesaplamak yerine, konteynere ba�lang�� ve biti� noktalar�n�, uygun �ekilde begin() ve end() adl� �ye fonksiyonlar arac�l���yla sorabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Dizimizden ba�lang�� ve biti� noktalar�n� isteyin (begin ve end �ye fonksiyonlar� arac�l���yla).
                    auto begin{ array.begin() };
                    auto end{ array.end() };

                    for (auto p{ begin }; p != end; ++p) // Sonraki elemana ge�mek i�in ++.
                    {
                        std::cout << *p << ' '; // Mevcut eleman�n de�erini almak i�in indireksiyon.
                    }
                    std::cout << '\n';

                    return 0;
                }

                Bu, �unu yazd�r�r:

                1 2 3
Yineleyici ba�l��� ayr�ca kullan�labilen iki genel fonksiyon (std::begin ve std::end) i�erir.

�pucu -> C tarz� diziler i�in std::begin ve std::end, <iterator> ba�l���nda tan�mlanm��t�r.

Yineleyicileri destekleyen konteynerler i�in std::begin ve std::end, bu konteynerlerin ba�l�k dosyalar�nda tan�mlanm��t�r (�r. <array>, <vector>).

                #include <array>    // <iterator> dahil eder
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Ba�lang�� ve biti� noktalar�n� almak i�in std::begin ve std::end kullan�n.
                    auto begin{ std::begin(array) };
                    auto end{ std::end(array) };

                    for (auto p{ begin }; p != end; ++p) // Sonraki elemana ge�mek i�in ++
                    {
                        std::cout << *p << ' '; // Mevcut eleman�n de�erini almak i�in indireksiyon
                    }
                    std::cout << '\n';

                    return 0;
                }

                Bu da �unu yazd�r�r:

                1 2 3
�imdilik yineleyicilerin t�rleri hakk�nda endi�elenmeyin, daha sonraki bir b�l�mde yineleyicilere geri d�nece�iz. �nemli olan �ey, yineleyicinin
konteynerden ge�me ayr�nt�lar�n� halletmesidir. D�rt �eye ihtiyac�m�z var: ba�lang�� noktas�, biti� noktas�, sonraki elemana (veya sona) 
ge�mek i�in operator++, ve mevcut eleman�n de�erini almak i�in operator*.

Yineleyiciler i�in operator< vs operator!=
------------------------------------------
8.10 -- For ifadeleri dersinde, d�ng� ko�ulunda say�sal kar��la�t�rmalar yaparken operator< kullanman�n operator!='den tercih edildi�ini 
belirtmi�tik:

                for (index = 0; index < length; ++index)

Yineleyicilerle, yineleyicinin son elemana ula��p ula�mad���n� test etmek i�in genellikle operator!= kullan�l�r:

                for (auto p{ begin }; p != end; ++p)

Bu, baz� yineleyici t�rlerinin ili�kisel olarak kar��la�t�r�lamaz olmas�ndand�r. operator!=, t�m yineleyici t�rleriyle �al���r.

Aral�k tabanl� for d�ng�lerine geri d�n��
-----------------------------------------
Hem begin() hem de end() �ye fonksiyonlar�na sahip olan t�m t�rler, veya std::begin() ve std::end() ile kullan�labilen t�rler, ,
aral�k tabanl� for-d�ng�lerinde kullan�labilir.

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Bu, daha �nce kulland���m�z d�ng�yle tam olarak ayn� �eyi yapar.
                    for (int i : array)
                    {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';

                    return 0;
                }

Perde arkas�nda, aral�k tabanl� for-d�ng�s�, �zerinde yineleme yap�lacak t�r�n begin() ve end() fonksiyonlar�n� �a��r�r. std::array'�n begin ve
end �ye fonksiyonlar� vard�r, bu y�zden onu bir aral�k tabanl� d�ng�de kullanabiliriz. C tarz� sabit diziler, std::begin ve std::end
fonksiyonlar�yla kullan�labilir, bu y�zden onlar� da bir aral�k tabanl� d�ng� ile d�ng�ye alabiliriz. Ancak, dinamik C tarz� diziler
(veya bozunmu� C tarz� diziler) �al��maz, ��nk� onlar i�in bir std::end fonksiyonu yoktur (��nk� t�r bilgisi dizinin uzunlu�unu i�ermez).

Bu fonksiyonlar� kendi t�rlerinize nas�l ekleyece�inizi daha sonra ��reneceksiniz, b�ylece onlar da aral�k tabanl� for-d�ng�lerinde kullan�labilir.
Aral�k tabanl� for-d�ng�leri, yineleyicileri kullanan tek �ey de�ildir. Ayr�ca std::sort ve di�er algoritmalar�nda da kullan�l�rlar. Art�k onlar�n
ne oldu�unu bildi�inize g�re, standart k�t�phanede olduk�a fazla kullan�ld�klar�n� fark edeceksiniz.

�terat�r ge�ersizle�tirme (sallanan iterat�rler)
------------------------------------------------
��aret�iler ve referanslar gibi, iterat�rler de �zerinde yineleme yap�lan ��elerin adresi de�i�tirildi�inde veya yok edildi�inde "sallanabilir".
B�yle bir durumda, iterat�r�n ge�ersizle�tirildi�ini s�yleriz. Ge�ersizle�tirilmi� bir iterat�re eri�mek tan�ms�z davran��a neden olur.

Konteynerleri de�i�tiren baz� i�lemler (�rne�in bir std::vector'a bir ��e eklemek gibi) konteynerdaki ��elerin adreslerinin de�i�mesine neden
olabilir. B�yle bir durumda, bu ��elere olan mevcut iterat�rler ge�ersizle�tirilir. �yi bir C++ referans belgesi, hangi konteyner i�lemlerinin
iterat�rleri ge�ersizle�tirebilece�ini veya ge�ersizle�tirece�ini belirtmelidir. �rnek olarak, cppreference'deki std::vector'�n "Iterator
invalidation" b�l�m�ne bakabilirsiniz. https://en.cppreference.com/w/cpp/container/vector#Iterator_invalidation

Aral�k tabanl� for d�ng�leri arka planda iterat�rleri kulland���ndan, aktif olarak gezdi�imiz konteynerin iterat�rlerini ge�ersizle�tirecek 
bir �ey yapmamaya dikkat etmeliyiz:

                #include <vector>

                int main()
                {
                    std::vector v { 0, 1, 2, 3 };

                    for (auto num : v) // v �zerinde dolayl� olarak yineleme yapar
                    {
                        if (num % 2 == 0)
                            v.push_back(num + 1); // bu, v'nin iterat�rlerini ge�ersizle�tirdi�inde, tan�ms�z davran�� ortaya ��kar
                    }

                    return 0;
                }

��te iterat�r ge�ersizle�tirmenin ba�ka bir �rne�i:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

                    auto it{ v.begin() };

                    ++it; // ikinci ��eye ge�
                    std::cout << *it << '\n'; // tamam: 2 yazd�r�r

                    v.erase(it); // �u anda �zerinde yineleme yap�lan ��eyi sil

                    // erase() silinen ��eye (ve sonraki ��elere) olan iterat�rleri ge�ersizle�tirir
                    // bu y�zden "it" iterat�r� �imdi ge�ersizle�tirildi

                    ++it; // tan�ms�z davran��
                    std::cout << *it << '\n'; // tan�ms�z davran��

                    return 0;
                }

Ge�ersizle�tirilmi� iterat�rler, onlara ge�erli bir iterat�r atayarak (�r. begin(), end() veya bir iterat�r d�nd�ren ba�ka bir fonksiyonun
d�n�� de�eri) yeniden ge�erli hale getirilebilir.

Erase() fonksiyonu, silinen ��eden bir sonraki ��eye (veya son ��e kald�r�ld�ysa end() 'e) bir iterat�r d�nd�r�r. Bu nedenle, yukar�daki kodu �u 
�ekilde d�zeltebiliriz:

#include <iostream>
#include <vector>

                int main()
                {
                    std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

                    auto it{ v.begin() };

                    ++it; // ikinci ��eye ge�
                    std::cout << *it << '\n';

                    it = v.erase(it); // �u anda �zerinde yineleme yap�lan ��eyi sil, `it`'yi bir sonraki ��eye ayarla

                    std::cout << *it << '\n'; // �imdi tamam, 3 yazd�r�r

                    return 0;
                }

18.3 � Standart k�t�phane algoritmalar�na giri�
-----------------------------------------------
Yeni programc�lar genellikle, dizileri s�ralama veya sayma veya arama gibi nispeten basit g�revleri ger�ekle�tirmek i�in �ok fazla zaman harcarlar.
Bu d�ng�ler, bir hatay� ne kadar kolay yapabilece�iniz ve genel bak�m a��s�ndan sorunlu olabilir, ��nk� d�ng�ler anlamas� zor olabilir.

Arama, sayma ve s�ralama gibi i�lemler bu kadar yayg�n oldu�u i�in, C++ standart k�t�phanesi bu i�lemleri sadece birka� sat�r kodda yapmak i�in bir
dizi fonksiyonla gelir. Ek olarak, bu standart k�t�phane fonksiyonlar� �nceden test edilmi�tir, verimlidir, �e�itli farkl� konteyner t�rlerinde
�al���r ve bir�oklar� paralelle�tirme destekler (ayn� g�revi daha h�zl� tamamlamak i�in birden �ok CPU i� par�ac���n� ayn� g�reve ay�rma yetene�i).

Algoritmalar k�t�phanesinde sa�lanan i�levsellik genellikle �� kategoriye ayr�l�r:
----------------------------------------------------------------------------------
*- Denetleyiciler (Inspectors ) -- Bir konteynerdeki verileri g�r�nt�lemek (ancak de�i�tirmemek) i�in kullan�l�r. �rnekler arama ve saymay� i�erir.
*- De�i�tiriciler ( Mutators ) -- Bir konteynerdeki verileri de�i�tirmek i�in kullan�l�r. �rnekler s�ralama ve kar��t�rmay� i�erir.
*- Kolayla�t�r�c�lar ( Facilitators ) -- Veri �yelerinin de�erlerine dayal� bir sonu� olu�turmak i�in kullan�l�r. 
   �rnekler, de�erleri �arpan nesneleri veya ��e �iftlerinin hangi s�rayla s�ralanmas� gerekti�ini belirleyen nesneleri i�erir.

   Bu algoritmalar, "algorithms" k�t�phanesinde bulunur. Bu derste, daha yayg�n algoritmalar�n baz�lar�n� inceleyece�iz - ancak �ok daha fazlas�
   var ve ba�lant�l� referans� okuyarak her �eyi g�rmek i�in sizi te�vik ediyoruz!

Not: Bunlar�n hepsi yineleyicileri kullan�r, bu y�zden temel yineleyicilerle tan�d�k de�ilseniz, l�tfen 18.2 -- Yineleyicilere Giri� dersini g�zden
ge�irin.

Bir eleman� de�eriyle bulmak i�in std::find kullanma
----------------------------------------------------
std::find, bir de�erin bir konteyn�rda ilk olu�umunu arar. std::find 3 parametre al�r: dizinin ba�lang�� eleman�na bir yineleyici, dizinin biti�
eleman�na bir yineleyici ve aranacak bir de�er. Bulunan elemana (e�er bulunursa) veya konteyn�r�n sonuna (e�er eleman bulunamazsa) i�aret eden bir
yineleyici d�nd�r�r �rne�in:

                #include <algorithm>
                #include <array>
                #include <iostream>

                int main()
                {
                    std::array arr{ 13, 90, 99, 5, 40, 80 };

                    std::cout << "Aranacak ve yerine konulacak bir de�er girin: ";
                    int search{};
                    int replace{};
                    std::cin >> search >> replace;

                    // Giri� do�rulamas� atland�

                    // std::find, bulunan elemana (veya konteyn�r�n sonuna) i�aret eden bir yineleyici d�nd�r�r
                    // bunu bir de�i�kende saklayaca��z, yineleyicinin t�r�n� ��karmak i�in t�r ��kar�m�n� kullan�yoruz
                    // (��nk� umursam�yoruz)
                    auto found{ std::find(arr.begin(), arr.end(), search) };

                    // Arad�klar�n� bulamayan algoritmalar, son yineleyiciyi d�nd�r�r.
                    // Bunu end() �ye fonksiyonunu kullanarak eri�ebiliriz.
                    if (found == arr.end())
                    {
                        std::cout << search << " bulunamad�" << '\n';
                    }
                    else
                    {
                        // Bulunan eleman�n �zerine yaz.
                        *found = replace;
                    }

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }
                ��kt�lar:

                Aranacak ve yerine konulacak bir de�er girin: 5 234
                13 90 99 234 40 80
                Eleman bulunamad���nda �rnek �al��t�rma

                Aranacak ve yerine konulacak bir de�er girin: 0 234
                0 bulunamad�
                13 90 99 5 40 80
Bir eleman�n belirli bir ko�ulu kar��lay�p kar��lamad���n� bulmak i�in std::find_if kullanma
--------------------------------------------------------------------------------------------
Bazen, bir konteyn�rda belirli bir ko�ulu kar��layan bir de�er olup olmad���n� g�rmek istiyoruz (�r. belirli bir alt dizeyi i�eren bir dize) 
belirli bir de�erden ziyade. Bu t�r durumlarda, std::find_if m�kemmeldir.

std::find_if fonksiyonu, std::find'a benzer �ekilde �al���r, ancak aranacak belirli bir de�er yerine, �a�r�labilir bir nesne ge�iririz,
�rne�in bir fonksiyon i�aret�isi (veya bir lambda, daha sonra ele alaca��z). Yinelenecek her ��e i�in, std::find_if bu fonksiyonu �a��r�r 
(��eyi fonksiyona arg�man olarak ge�irir) ve fonksiyon, bir e�le�me bulunursa true d�nebilir veya aksi takdirde false d�nebilir.

��te, herhangi bir ��enin "nut" alt dizgesini i�erip i�ermedi�ini kontrol etmek i�in std::find_if'i kulland���m�z bir �rnek:

                #include <algorithm>
                #include <array>
                #include <iostream>
                #include <string_view>

                // Fonksiyonumuz, ��e e�le�irse true d�necektir
                bool containsNut(std::string_view str)
                {
                    // std::string_view::find, alt dizeyi bulamazsa std::string_view::npos d�nd�r�r
                    // Aksi takdirde, alt dizgenin str'de nerede oldu�unu d�nd�r�r.
                    return (str.find("nut") != std::string_view::npos);
                }

                int main()
                {
                    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

                    // Dizimizi taray�n ve herhangi bir ��enin "nut" alt dizgesini i�erip i�ermedi�ini g�r�n
                    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

                    if (found == arr.end())
                    {
                        std::cout << "F�nd�k yok\n";
                    }
                    else
                    {
                        std::cout << *found << " bulundu" << '\n';
                    }

                    return 0;
                }
                ��kt�

                Walnut bulundu

Yukar�daki �rne�i el ile yazmak isterseniz, en az �� d�ng�ye ihtiyac�n�z olurdu (diziyi d�ng�ye almak i�in bir ve alt dizeyi e�le�tirmek i�in iki).
Standart k�t�phane fonksiyonlar�, ayn� �eyi sadece birka� kod sat�r�yla yapmam�z� sa�lar!

std::count ve std::count_if kullanarak ka� tane �rne�in oldu�unu sayma
----------------------------------------------------------------------
std::count ve std::count_if, bir ��enin veya bir ko�ulu kar��layan bir ��enin t�m �rneklerini arar.
A�a��daki �rnekte, ka� ��enin "nut" alt dizesini i�erdi�ini sayaca��z:

                #include <algorithm>
                #include <array>
                #include <iostream>
                #include <string_view>

                bool containsNut(std::string_view str)
                {
                    return (str.find("nut") != std::string_view::npos);
                }

                int main()
                {
                    std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" };

                    auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };

                    std::cout << "Counted " << nuts << " nut(s)\n";

                    return 0;
                }

                ��kt�

                Counted 2 nut(s)

std::sort kullanarak �zel s�ralama
----------------------------------
Daha �nce std::sort'u bir diziyi artan s�rayla s�ralamak i�in kullanm��t�k, ancak std::sort daha fazlas�n� yapabilir. std::sort'un, istedi�imiz
gibi s�ralamam�za izin veren ���nc� bir parametre olarak bir i�lev alan bir s�r�m� vard�r. ��lev, iki parametreyi kar��la�t�r�r ve ilk arg�man�n 
ikinciden �nce s�ralanmas� gerekiyorsa true d�nd�r�r. Varsay�lan olarak, std::sort ��eleri artan s�rayla s�ralar.

Bir diziyi ters s�rayla s�ralamak i�in std::sort'u, greater adl� �zel bir kar��la�t�rma i�levi kullanarak kullanal�m:

                #include <algorithm>
                #include <array>
                #include <iostream>

                bool greater(int a, int b)
                {
                    // E�er @a, @b'den b�y�kse, @a'y� @b'den �nce s�rala.
                    return (a > b);
                }

                int main()
                {
                    std::array arr{ 13, 90, 99, 5, 40, 80 };

                    // greater'� std::sort'a ge�irin
                    std::sort(arr.begin(), arr.end(), greater);

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }

                ��kt�

                99 90 80 40 13 5
Bir kez daha, kendi �zel d�ng� i�levlerimizi yazmak yerine, dizimizi sadece birka� kod sat�r�nda istedi�imiz gibi s�ralayabiliriz!

Greater i�levimizin 2 arg�mana ihtiyac� var, ancak ona hi�bir �ey ge�miyoruz, bu y�zden nereden geliyorlar? Parantez olmadan bir i�levi () 
kullan�ld���nda, bu sadece bir i�lev i�aret�isidir, bir �a�r� de�ildir. Bunu, bir i�levi parantezsiz yazd�rmay� denedi�imizde ve std::cout'un
"1" yazd�rd��� durumdan hat�rlayabilirsiniz. std::sort, bu i�aret�iyi kullan�r ve ger�ek greater i�levini dizinin herhangi 2 ��esiyle �a��r�r.
Greater'�n hangi ��elerle �a�r�laca��n� bilmiyoruz, ��nk� std::sort'un alt�nda hangi s�ralama algoritmas�n� kulland��� tan�mlanmam��t�r. 
Daha sonraki bir b�l�mde i�lev i�aret�ileri hakk�nda daha fazla konu�uyoruz.

�pucu

Azalan s�rayla s�ralama o kadar yayg�nd�r ki, C++ bunun i�in de �zel bir t�r (std::greater adl�) sa�lar (bu, functional ba�l���n�n bir par�as�d�r).
Yukar�daki �rnekte, �unu de�i�tirebiliriz:

                std::sort(arr.begin(), arr.end(), greater); // �zel greater i�levimizi �a��r�n
�ununla:
                std::sort(arr.begin(), arr.end(), std::greater{}); // standart k�t�phane greater kar��la�t�rmas�n� kullan�n
                // C++17'den �nce, std::greater'� olu�tururken ��e t�r�n� belirtmemiz gerekiyordu
                std::sort(arr.begin(), arr.end(), std::greater<int>{}); // standart k�t�phane greater kar��la�t�rmas�n� kullan�n
std::greater{}'�n s�sl� parantezlere ihtiyac� oldu�unu unutmay�n ��nk� bu �a�r�labilir bir i�lev de�ildir. Bu bir t�rd�r ve onu kullanmak i�in,
bu t�rden bir nesne olu�turmam�z gerekiyor. S�sl� parantezler, bu t�rden anonim bir nesne olu�turur (daha sonra std::sort'a bir arg�man olarak 
ge�er).

Bir konteyn�r�n t�m elemanlar�na bir �ey yapmak i�in std::for_each kullanma
---------------------------------------------------------------------------
std::for_each, bir listeyi girdi olarak al�r ve her bir elemana �zel bir fonksiyon uygular. Bu, bir listesindeki her bir elemana ayn� i�lemi 
ger�ekle�tirmek istedi�imizde kullan��l�d�r.

��te bir �rnekte, std::for_each'i bir dizideki t�m say�lar� ikiye katlamak i�in kullan�yoruz:

                #include <algorithm>
                #include <array>
                #include <iostream>

                void doubleNumber(int& i)
                {
                    i *= 2;
                }

                int main()
                {
                    std::array arr{ 1, 2, 3, 4 };

                    std::for_each(arr.begin(), arr.end(), doubleNumber);

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }
                ��kt�

                2 4 6 8

Bu, genellikle yeni geli�tiriciler i�in en gereksiz algoritma gibi g�r�n�r, ��nk� aral�k tabanl� bir for d�ng�s� ile e�de�er kod daha k�sa ve daha
kolayd�r. Ancak std::for_each'in faydalar� vard�r. std::for_each'i bir aral�k tabanl� for d�ng�s� ile kar��la�t�ral�m.

                std::ranges::for_each(arr, doubleNumber); // C++20'den itibaren, begin() ve end() kullanmak zorunda de�iliz.
                // std::for_each(arr.begin(), arr.end(), doubleNumber); // C++20'den �nce

                for (auto& i : arr)
                {
                    doubleNumber(i);
                }
std::for_each ile niyetlerimiz a��kt�r. arr'�n her bir eleman� ile doubleNumber'� �a��r�n. Aral�k tabanl� for d�ng�s�nde, yeni bir de�i�ken
eklememiz gerekiyor, i. Bu, bir programc�n�n yorgun oldu�unda veya dikkat etmedi�inde yapabilece�i birka� hataya yol a�ar. �ncelikle, otomatik 
kullanmazsak bir a��k d�n���m olabilir. Ampersandi unutabiliriz ve doubleNumber diziyi etkilemez. Yanl��l�kla i d���nda bir de�i�keni
doubleNumber'a ge�irebiliriz. Bu hatalar std::for_each ile olamaz.

Ayr�ca, std::for_each, bir konteyn�r�n ba��ndaki veya sonundaki elemanlar� atlayabilir, �rne�in arr'�n ilk eleman�n� atlamak i�in, std::next
kullan�labilir ve ba�lang�c� bir sonraki elemana ilerletebilir.

                std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
                // �imdi arr [1, 4, 6, 8]. �lk eleman ikiye katlanmad�.
Bu, bir aral�k tabanl� for d�ng�s� ile m�mk�n de�ildir.

Bir�ok algoritma gibi, std::for_each paralelize edilebilir ve daha h�zl� i�lem sa�lar, bu da onu b�y�k projeler ve b�y�k veriler i�in bir aral�k
tabanl� for d�ng�s�nden daha uygun hale getirir.

Performans ve y�r�tme s�ras�
----------------------------
Algoritmalar k�t�phanesindeki bir�ok algoritma, nas�l �al��acaklar�na dair bir t�r garanti verir. Genellikle bunlar ya performans garantileri ya da
hangi s�rayla �al��acaklar�na dair garantilerdir. �rne�in, std::for_each, her bir eleman�n yaln�zca bir kez eri�ilece�ini ve elemanlar�n ileri
s�ral� s�rayla eri�ilece�ini garanti eder.

�o�u algoritma bir t�r performans garantisi sa�larken, daha az�n�n y�r�tme s�ras� garantileri vard�r. Bu t�r algoritmalar i�in, elemanlar�n hangi 
s�rayla eri�ilece�i veya i�lenece�i konusunda varsay�mlar yapmamaya dikkat etmemiz gerekiyor.

�rne�in, bir standart k�t�phane algoritmas�n� kullanarak ilk de�eri 1 ile, ikinci de�eri 2 ile, ���nc�y� 3 ile �arpmak vb. istiyorsak, ileri s�ral�
y�r�tme s�ras�n� garanti etmeyen herhangi bir algoritmay� kullanmaktan ka��nmak isteriz!

A�a��daki algoritmalar s�ral� y�r�tme garanti eder: std::for_each, std::copy, std::copy_backward, std::move ve std::move_backward. Bir�ok di�er 
algoritma (�zellikle ileri yineleyici kullananlar) ileri yineleyici gereksinimi nedeniyle dolayl� olarak s�ral�d�r.

*** BEST -> Belirli bir algoritmay� kullanmadan �nce, performans ve y�r�tme s�ras� garantilerinin belirli kullan�m durumunuz i�in �al��t���ndan
            emin olun.

C++20'de Aral�klar ( Ranges )
-----------------------------
Her algoritmaya a��k�a arr.begin() ve arr.end() ge�irmek biraz sinir bozucu. Ama korkmay�n - C++20, bize sadece arr'� ge�memizi sa�layan aral�klar
ekler. Bu, kodumuzu daha da k�sa ve okunabilir hale getirecektir.

Sonu�

Algoritmalar k�t�phanesi, kodunuzu daha basit ve daha sa�lam hale getirebilecek bir ton kullan��l� i�levsellik i�erir. Bu derste sadece k���k bir
alt k�mesini ele al�yoruz, ancak bu fonksiyonlar�n �o�u �ok benzer �ekilde �al��t��� i�in, birka��n�n nas�l �al��t���n� bildi�inizde, �o�unu
kullanabilirsiniz.

Not:
Bu https://www.youtube.com/watch?v=2olsGf6JIkU video, k�t�phanedeki �e�itli algoritmalar� �zl� bir �ekilde a��klama konusunda iyi bir i� ��kar�yor.

*** BEST ->  Ayn� �eyi yapmak i�in kendi i�levselli�inizi yazmak yerine algoritmalar k�t�phanesinden fonksiyonlar� kullanmay� tercih edin.

18.4 � Kodunuzu Zamanlama
-------------------------
Kodunuzu yazarken, bazen hangi y�ntemin daha performansl� olaca��ndan emin olmad���n�z durumlarla kar��la��rs�n�z. Peki, bunu nas�l anlars�n�z?
Bir yol, kodunuzu zamanlayarak ne kadar s�rede �al��t���n� g�rmektir. C++11, bunu yapmak i�in chrono k�t�phanesinde baz� i�levlerle birlikte gelir.
Ancak, chrono k�t�phanesini kullanmak biraz gizemlidir. �yi haber �u ki, ihtiyac�m�z olan t�m zamanlama i�levselli�ini kendi programlar�m�zda 
kullanabilece�imiz bir s�n�fa kolayca kaps�lleyebiliriz.

��te s�n�f:

                #include <chrono> // std::chrono i�levleri i�in

                class Timer
                {
                private:
                    // �� i�e ge�mi� t�rleri eri�meyi kolayla�t�rmak i�in t�r takma adlar�
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg { Clock::now() };

                public:
                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

��te bu! Kullanmak i�in, ana fonksiyonumuzun ba��nda (veya zamanlamaya ba�lamak istedi�imiz herhangi bir yerde) bir Timer nesnesi olu�turuyoruz 
ve ard�ndan program�n o noktaya kadar �al��mas�n�n ne kadar s�rd���n� bilmek istedi�imizde elapsed() �ye fonksiyonunu �a��r�yoruz.

                #include <iostream>

                int main()
                {
                    Timer t;

                    // Zamanlanacak kod buraya gider

                    std::cout << "Ge�en s�re: " << t.elapsed() << " saniye\n";

                    return 0;
                }
�imdi, bunu 10000 elemanl� bir dizi s�ralad���m�z ger�ek bir �rnekte kullanal�m. �nce, �nceki bir b�l�mde geli�tirdi�imiz se�im s�ralama
algoritmas�n� kullanal�m:

                #include <array>
                #include <chrono> // std::chrono i�levleri i�in
                #include <cstddef> // std::size_t i�in
                #include <iostream>
                #include <numeric> // std::iota i�in

                const int g_arrayElements { 10000 };

                class Timer
                {
                private:
                    // �� i�e ge�mi� t�rleri eri�meyi kolayla�t�rmak i�in t�r takma adlar�
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg{ Clock::now() };

                public:

                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

                void sortArray(std::array<int, g_arrayElements>& array)
                {

                    // Dizinin her bir eleman�ndan ge�in
                    // (sonuncusu hari�, oraya geldi�imizde zaten s�ralanm�� olacak)
                    for (std::size_t startIndex{ 0 }; startIndex < (g_arrayElements - 1); ++startIndex)
                    {
                        // smallestIndex, bu iterasyonda kar��la�t���m�z en k���k eleman�n indeksidir
                        // En k���k eleman�n bu iterasyonun ilk eleman� oldu�unu varsayarak ba�lay�n
                        std::size_t smallestIndex{ startIndex };

                        // Sonra geri kalan dizide daha k���k bir eleman aray�n
                        for (std::size_t currentIndex{ startIndex + 1 }; currentIndex < g_arrayElements; ++currentIndex)
                        {
                            // Daha �nce buldu�umuz en k���kten daha k���k bir eleman bulduysak
                            if (array[currentIndex] < array[smallestIndex])
                            {
                                // onu takip edin
                                smallestIndex = currentIndex;
                            }
                        }

                        // smallestIndex �imdi kalan dizideki en k���k elemand�r
                        // ba�lang�� eleman�m�z� en k���k eleman�m�zla de�i�tirin (bu onu do�ru yere s�ralar)
                        std::swap(array[startIndex], array[smallestIndex]);
                    }
                }

                int main()
                {
                    std::array<int, g_arrayElements> array;
                    std::iota(array.rbegin(), array.rend(), 1); // diziyi 10000'den 1'e kadar de�erlerle doldurun

                    Timer t;

                    sortArray(array);

                    std::cout << "Harcanan zaman: " << t.elapsed() << " saniye\n";

                    return 0;
                }


Yazar�n makinesinde, �� �al��ma 0.0507, 0.0506 ve 0.0498 zamanlamalar�n� �retti. Yani yakla��k 0.05 saniye diyebiliriz.

�imdi, ayn� testi standart k�t�phaneden std::sort kullanarak yapal�m.

                #include <algorithm> // std::sort i�in
                #include <array>
                #include <chrono> // std::chrono fonksiyonlar� i�in
                #include <cstddef> // std::size_t i�in
                #include <iostream>
                #include <numeric> // std::iota i�in

                const int g_arrayElements { 10000 };

                class Timer
                {
                private:
                    // �� i�e ge�mi� t�rleri daha kolay eri�ilebilir hale getirmek i�in t�r takma adlar�
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg{ Clock::now() };

                public:

                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

                int main()
                {
                    std::array<int, g_arrayElements> array;
                    std::iota(array.rbegin(), array.rend(), 1); // diziyi 10000'den 1'e kadar de�erlerle doldurun

                    Timer t;

                    std::ranges::sort(array); // C++20'den itibaren
                    // E�er derleyiciniz C++20 uyumlu de�ilse
                    // std::sort(array.begin(), array.end());

                    std::cout << "Ge�en s�re: " << t.elapsed() << " saniye\n";

                    return 0;
                }

Yazar�n makinesinde, bu sonu�lar� �retti: 0.000693, 0.000692 ve 0.000699. Yani temelde tam olarak 0.0007 civar�nda.

Ba�ka bir deyi�le, bu durumda, std::sort kendimizin yazd��� se�im s�ralamas�ndan 100 kat daha h�zl�d�r!

Program�n�z�n performans�n� etkileyebilecek �eyler
--------------------------------------------------
Program�n�z�n bir �al��mas�n� zamanlamak olduk�a basittir, ancak sonu�lar�n�z bir dizi �eyden �nemli �l��de etkilenebilir ve nas�l d�zg�n bir
�ekilde �l��lece�ini ve hangi �eylerin zamanlamay� etkileyebilece�ini bilmek �nemlidir.

�lk olarak, bir hata ay�klama hedefi olu�turmak yerine bir s�r�m hedefi olu�turdu�unuzdan emin olun. Hata ay�klama hedefleri genellikle
optimizasyonu kapat�r ve bu optimizasyon sonu�lar� �nemli �l��de etkileyebilir. �rne�in, bir hata ay�klama hedefi kullanarak, yukar�daki std::sort 
�rne�ini yazar�n makinesinde �al��t�rmak 0.0235 saniye s�rd� -- 33 kat daha uzun!

�kinci olarak, zamanlama sonu�lar�n�z sistemizin arka planda yapabilece�i di�er �eylerden etkilenebilir. Sisteminizin CPU, bellek veya sabit disk 
yo�un bir �ey yapmad���ndan emin olun (�r. bir oyun oynama, bir dosya arama, bir antivir�s taramas� �al��t�rma veya arka planda bir g�ncelleme
y�kleme). G�r�n��te masum �eyler, aktif sekme yeni bir reklam afi�i d�nd�rd���nde ve bir dizi javascript'i ayr��t�rmak zorunda kald���nda, 
bo�ta olan web taray�c�lar�n�z CPU kullan�m�n�z� ge�ici olarak %100'e ��karabilir. �l��m yapmadan �nce kapatabilece�iniz uygulama say�s� ne kadar 
fazla olursa, sonu�lar�n�zdaki varyans o kadar az olur.

���nc� olarak, program�n�z bir rastgele say� �reteci kullan�yorsa, �retilen rastgele say�lar�n belirli bir s�ras� zamanlamay� etkileyebilir.
�rne�in, rastgele say�larla dolu bir dizi s�ral�yorsan�z, sonu�lar muhtemelen �al��madan �al��maya de�i�ir ��nk� diziyi s�ralamak i�in gereken
takas say�s� �al��madan �al��maya de�i�ir. Program�n�z�n birden �ok �al��mas�nda daha tutarl� sonu�lar elde etmek i�in, rastgele say� �retecinizi 
ge�ici olarak bir literal de�erle (std::random_device veya sistem saati yerine) �ekirdekleyebilirsiniz, b�ylece her �al��mada ayn� say� dizisini
�retir. Ancak, program�n�z�n performans� �retilen belirli rastgele s�raya �ok ba�l�ysa, bu da genel olarak yan�lt�c� sonu�lara yol a�abilir.

D�rd�nc� olarak, kullan�c� giri�ini beklerken zamanlamad���n�zdan emin olun, ��nk� kullan�c�n�n bir �eyi ne kadar s�rede girdi�i zamanlama
d���ncelerinizin bir par�as� olmamal�d�r. Kullan�c� giri�i gerekiyorsa, kullan�c�y� beklemeyen bir giri� sa�lama yolu eklemeyi d���n�n 
(�r. komut sat�r�, bir dosyadan, giri�i �evreleyen bir kod yolu).

Performans �l��m�
-----------------
Program�n�z�n performans�n� �l�erken, en az 3 sonu� toplay�n. Sonu�lar benzerse, bunlar muhtemelen program�n�z�n o makinedeki ger�ek performans�n�
temsil eder. Aksi takdirde, benzer sonu�lar�n bir k�mesine sahip olana kadar �l��mler yapmaya devam edin (ve hangi di�er sonu�lar�n ayk�r� oldu�unu
anlay�n). Sisteminizin baz� �al��malar s�ras�nda arka planda bir �eyler yapmas� nedeniyle bir veya daha fazla ayk�r� de�ere sahip olmak al���lmad�k
bir durum de�ildir.

Sonu�lar�n�zda �ok fazla de�i�kenlik varsa (ve iyi bir �ekilde k�mele�miyorsa), program�n�z muhtemelen sistemde olup biten di�er �eylerden �nemli
�l��de etkileniyor veya uygulaman�zdaki rastgelele�tirme etkilerinden etkileniyordur.

Performans �l��mleri o kadar �ok �eyden etkilendi�i i�in (�zellikle donan�m h�z�, ama ayn� zamanda i�letim sistemi, �al��an uygulamalar, vb.),
mutlak performans �l��mleri (�r. "program 10 saniyede �al���r") genellikle yaln�zca program�n sizin �nemsedi�iniz bir makinede ne kadar iyi 
�al��t���n� anlamak d���nda pek kullan��l� de�ildir. Farkl� bir makinede, ayn� program 1 saniye, 10 saniye veya 1 dakika i�inde �al��abilir.
Farkl� donan�mlar aras�nda ger�ekten �l��m yapmadan bunu bilmek zordur.

Ancak, tek bir makinede, g�receli performans �l��mleri yararl� olabilir. Bir program�n �e�itli varyantlar�ndan performans sonu�lar� toplayabilir ve
hangi varyant�n en performansl� oldu�unu belirleyebiliriz. �rne�in, varyant 1 10 saniyede �al���yorsa ve varyant 2 8 saniyede �al���yorsa,
varyant 2 muhtemelen t�m benzer makinelerde mutlak makine h�z�ndan ba��ms�z olarak daha h�zl� olacakt�r.

�kinci varyant� �l�t�kten sonra, iyi bir mant�k kontrol� ilk varyant� tekrar �l�mektir. �lk varyant�n sonu�lar�, o varyant i�in ilk �l��mlerinizle
tutarl�ysa, her iki varyant�n sonucu makul �l��de kar��la�t�r�labilir olmal�d�r. �rne�in, varyant 1 10 saniyede �al���yor, varyant 2 8 saniyede 
�al���yor ve sonra varyant 1'i tekrar �l��yoruz ve 10 saniye al�yorsak, her iki varyant�n �l��mlerinin adil bir �ekilde �l��ld���n� ve varyant 2'nin
daha h�zl� oldu�unu makul bir �ekilde sonu�land�rabiliriz.

Ancak, ilk varyant�n sonu�lar� art�k o varyant i�in ilk �l��mlerinizle tutarl� de�ilse, makinede �imdi performans� etkileyen bir �ey olmu�tur ve
�l��mdeki farkl�l�klar�n varyanttan m� yoksa makinenin kendisinden mi kaynakland���n� anlamak zor olacakt�r. Bu durumda, mevcut sonu�lar� atmak 
ve yeniden �l�mek en iyisidir.
*/