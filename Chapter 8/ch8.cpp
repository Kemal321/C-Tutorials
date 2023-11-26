/*
																CHAPTER 8 - Kontrol Ak���na Giri�	
Bir program �al��t�r�ld���nda, CPU main() fonksiyonunun ba��nda i�lemi ba�lat�r, belirli say�da ifadeyi (varsay�lan olarak s�ral� bir �ekilde) y�r�t�r ve ard�ndan 
program main() fonksiyonunun sonunda sona erer. CPU'nun y�r�tt��� belirli ifadeler dizisine program�n y�r�tme yolu - execution path -  (veya k�saca path) denir.

�rne�in:
			#include <iostream>

			int main()
			{
	5			std::cout << "Enter an integer: ";

	7			int x{};
	8			std::cin >> x;

	10			std::cout << "You entered " << x << '\n';

	12			return 0;
			}

Bu program�n y�r�tme yolu, s�ras�yla 5, 7, 8, 10 ve 12. sat�rlar� i�erir. Bu, bir do�rusal program �rne�idir. Do�rusal programlar, her �al��t�r�ld���nda ayn� yolu
izler (ayn� ifadeleri ayn� s�rayla y�r�t�r). Ancak genellikle bu istedi�imiz �ey de�ildir. �rne�in, kullan�c�dan giri� istedi�imizde ve kullan�c� ge�ersiz bir �ey 
girerse, ideal olarak kullan�c�dan ba�ka bir se�im yapmas�n� istemek isteriz. Bu, do�rusal bir programda m�mk�n de�ildir. Asl�nda, kullan�c� tekrar tekrar ge�ersiz 
giri� yapabilir, bu nedenle onlardan ba�ka bir se�im yapmalar�n� istememiz gereken kez say�s� �al��ma zaman�nda bilinemez. Neyse ki, C++, program�n normal y�r�tm
e yolunu de�i�tirmek i�in programc�n�n kullanmas�na izin veren bir dizi farkl� kontrol ak��� ifadesi (ayr�ca ak�� kontrol ifadeleri olarak da adland�r�l�r) sa�lar.
Zaten if ifadeleriyle (lesson 4.10 -- if �fadelerine Giri�'te tan�t�lan) bir �rnek g�rd�n�z; bu ifadeler bize bir ko�ul ifadesi do�ruysa yaln�zca bir ifadeyi y�r�tme
olana�� tan�r. Bir kontrol ak��� ifadesi, y�r�tme noktas�n� ard���k olmayan bir ifadeye ta��d���nda, buna dallanma (branching ) denir.

Ak�� kontrol� ifadelerinin kategorileri �unlard�r:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Kategori				|											Anlam														|	C++ ��inde Uygulanm�� Hali
Ko�ullu ifadeler		|	Ko�ullu ifadeler, bir ko�ul kar��land���nda yaln�zca belirli bir kod dizisini y�r�tmeye neden olur.	|	  if, switch
Atlamalar				|	Atlamalar, CPU'ya ba�ka bir konumda bulunan ifadeleri y�r�tmeye ba�lamas�n� s�yler.					|	  goto, break, continue
Fonksiyon �a�r�lar�		|	Fonksiyon �a�r�lar�, ba�ka bir konuma ve geriye d�nmek i�in atlama i�levine sahiptir.				|	  Fonksiyon �a�r�lar�, return
D�ng�ler				|	D�ng�ler, belirli bir ko�ul kar��lanana kadar bir kod dizisini s�f�r veya daha fazla				|
						|	kez tekrarlamak i�in program� y�nlendirir.															|	  while, do-while, for, ranged-for
Durdurmalar				|	Durdurmalar, program�n �al��mas�n� sonland�rmas�n� s�yler.											|	  std::exit(), std::abort()
�stisnalar				|	�stisnalar, hata i�leme amac�yla tasarlanm�� �zel bir ak�� kontrol yap�s�d�r.						|	  try, throw, catch
----------------------------------------------------------------------------------------------------------------------------------------------------------------------												


Bu b�l�m boyunca, istisnalar hari� (ha) t�m bu kategorileri detayl� bir �ekilde ele alaca��z ve istisnalar� (chapter 27'ye tamamen ay�rd���m�z) ilerleyen bir
b�l�me b�rakaca��z. Bu b�l�mden �nce, bir program�n yapabilece�i �eyler olduk�a s�n�rl�yd�. Program�n�z�n ak���n� kontrol edebilmek (�zellikle d�ng�ler kullanarak) 
bir dizi ilgin� �eyi m�mk�n k�lar! Art�k sadece oyuncak programlarla s�n�rl� kalmayacak, ger�ek fayda sa�layan programlar yazabileceksiniz.
��te ger�ek e�lence burada ba�l�yor. O zaman ba�layal�m!
*/

/*
																	IF STATEMENTS AND BLOCKS

If else yap�lar�nda blok olu�turmazsak sadece tek bir sat�r if else sistemine ba�l� olacakt�r. Yani �u �ekilde;
if(condition)
	statement 
else									Buradaki gibi her hangi bir compound statement koymad���m�z i�in yani blok koymad���m�z i�in burada else in alt�ndaki statement 
	statement1							statement 2 hep �al���r birden �ok statement y�r�tmek istiyorsak blok kullanaca��z.
	statement2 
Tekli ifadelerde blok kullanmak veya kullanmamak
------------------------------------------------
Bu konuda kom�nite ve baz� deneyimli c++ geli�tiricileri 2 ye ayr�lm��. Kom�nite her durumda kullan�n diyor. Kullanmamay� savunan geli�tiricilerin arg�man� ise 
kodu dikey olarak uzatt��� i�in bir seferde daha az kod g�rece�imiz y�n�nde bu da ba�ka hatalar� vs. g�zden ka��raca��m�z� ileri s�r�yor. 
*** BEST -> En iyi hareket Bu if veya else ile ili�kilendirilmi� tek ifadeleri bloklara koymay� d���n�n (�zellikle ��renme a�amas�ndayken). Daha deneyimli C++
			geli�tiricileri, dikey bo�lu�u s�k�la�t�rmak lehine, bazen bu uygulamay� g�z ard� edebilirler.

Orta bir yol alternatifi, tek sat�rlar� if veya else ile ayn� sat�ra koymakt�r: yani :
			if (age >= minDrinkingAge) purchaseBeer(); -> Bunun gibi
Bu, yukar�da bahsedilen her iki olumsuz durumu da �nlerken, okunabilirlik a��s�ndan baz� k���k maliyetlerle birlikte gelir.

Programc� bir if ifadesinin veya else ifadesinin ifade k�sm�nda bir blok bildirmezse, derleyici �rt�l� olarak bir blok beyan edecektir. B�ylece:
											if ( condition )
											{	
			if (condition)						true_statement;
				true_statement;		->		}
			else							else
				false_statement;									{
												false_statement;
											}
				
Genel If-Else hatalar�
----------------------
Bir if else yap�s�n� bir birine ba�layabiliriz �rne�in:
	
				if (x >= 0) // outer if statement
					// if i bu �ekilde ba�lamak k�t� bir kod stili
					if (x <= 20) // inner if statement
						std::cout << x << " is between 0 and 20\n";

				// Bu else hangi if e ait
				else
					std::cout << x << " is negative\n";

Yukar�daki program, bir potansiyel belirsizlik kayna�� olan "dangling else" problemine yol a�ar. Yukar�daki programdaki else ifadesi, d��taki 
if ifadesiyle mi yoksa i�teki if ifadesiyle mi e�le�mi�tir?

Cevap �udur: Bir else ifadesi, ayn� bloktaki son e�le�memi� if ifadesi ile e�le�ir. Bu nedenle, yukar�daki programda else ifadesi, i�teki if ifadesi
ile e�le�ir; sanki program �u �ekilde yaz�lm�� gibi davran�r:

					if (condition1)
					{
						if (condition2)
							statement1;
						else
							statement2;
					}

Bu durumu �nlemek i�in bloklar� ekleyerek ifadeleri a��k�a belirtmek iyi bir uygulamad�r.
�� i�e ge�mi� if ifadeleri kullan�rken bu t�r belirsizlikleri �nlemek i�in iyi bir fikir, i�teki if ifadesini a��k�a bir blok i�ine almak. 
Bu, bir else ifadesini her iki ifadeye de belirsizlik olmadan eklememize olanak tan�r:

						#include <iostream>

						int main()
						{
							std::cout << "Bir say� girin: ";
							int x{};
							std::cin >> x;

							if (x >= 0)
							{
								if (x <= 20)
									std::cout << x << " 0 ile 20 aras�ndad�r\n";
								else // i�teki if ifadesine ba�l�
									std::cout << x << " 20'den b�y�kt�r\n";
							}
							else // d��taki if ifadesine ba�l�
								std::cout << x << " negatiftir\n";

							return 0;
						}

Bloktaki else ifadesi i�teki if ifadesine ba�l�d�r ve blok d���ndaki else ifadesi d��taki if ifadesine ba�l�d�r.

veya else if kullanarak daha iyi ��zerik ( Buna da flattened if else deniyor. ) burada logical operat�rler kullanarak durumlar� teke indirmek gibi bir mant�k var. 

Null statement - ge�tim 
== operat�r� ile = operat�r�n� kar��t�rmamak laz�m ��nk� program burada her hangi bir hata �retmeden kodu �al��t�rabilir fakat istedi�imiz �ekilde �al��mayabilir.
*/
/*
																CONSTEXPR IF IFADES�

Genellikle, bir if ifadesinin ko�ulu �al��ma zaman�nda de�erlendirilir.

Ancak, ko�ul bir sabit ifade ise, a�a��daki �rnekte oldu�u gibi, durum �u �ekilde d���n�lebilir:

			#include <iostream>

			int main()
			{
				constexpr double gravity{ 9.8 };

				// reminder: low-precision floating point literals of the same type can be tested for equality
				if (gravity == 9.8) // constant expression, always true
					std::cout << "Gravity is normal.\n";   // will always be executed
				else
					std::cout << "We are not on Earth.\n"; // will never be executed

				return 0;
			}

��nk� gravity sabit ifadesi olarak tan�mlanm�� ve de�eri 9.8 ile ba�lat�lm��t�r, gravity == 9.8 ko�ulu her zaman do�ru de�eri verecektir. Sonu� olarak, 
else ifadesi hi�bir zaman �al��t�r�lmayacakt�r. Bir constexpr ko�ulu �al��ma zaman�nda de�erlendirmek israf olabilir (��nk� sonu� hi�bir zaman de�i�meyecek).
Ayr�ca, hi�bir zaman �al��t�r�lamayacak kodu y�r�t�lebilir bir programa dahil etmek de israf olacakt�r.
			
			
ko�ulun sabit bir ifade olmas�n� gerektiren constexpr if ifadesini tan�t�r. Bir constexpr-if-ifadesinin ko�ulu derleme zaman�nda de�erlendirilir.

E�er constexpr ko�ulu true de�erine de�erlendirilirse, t�m if-else ifadesi true-ifadesi ile de�i�tirilecektir. E�er constexpr ko�ulu false de�erine 
de�erlendirilirse, t�m if-else ifadesi false-ifadesi ile (varsa) veya hi�bir �eyle (else yoksa) de�i�tirilecektir.

Bir constexpr-if-ifadesi kullanmak i�in, if ifadesinden sonra constexpr anahtar kelimesini ekleriz:
			
				#include <iostream>

				int main()
				{
					constexpr double gravity{ 9.8 };

					if constexpr (gravity == 9.8) // now using constexpr if
						std::cout << "Gravity is normal.\n";
					else
						std::cout << "We are not on Earth.\n";

					return 0;
				}			
			
Yukar�daki kod derlendi�inde, derleyici ko�ulu derleme zaman�nda de�erlendirecek, her zaman do�ru oldu�unu g�recek ve yaln�zca tek bir ifadeyi olan 
`std::cout << "Gravity is normal.\n";` ifadesini koruyacakt�r.
Ba�ka bir deyi�le, bu kodu derleyecektir:

				int main()
				{
					std::cout << "Gravity is normal.\n";

					return 0;
				}
*** Best -> Ko�ullu sabit bir ifade oldu�unda constexpr if ifadelerini constexpr olmayan if ifadelerine tercih edin.
* 
Modern derleyiciler ve sabit if ifadeleri
-----------------------------------------
Optimizasyon ama�lar�yla, modern derleyiciler genellikle, constexpr ko�ullar� olan non-constexpr if ifadelerini adeta constexpr-if-ifadeleri gibi ele alacakt�r.
Ancak, bunu yapmak zorunda de�illerdir.

Derleyici, constexpr ko�ulu olan bir non-constexpr if ifadesi ile kar��la�t���nda, size if constexpr kullanman�z� �neren bir uyar� verebilir. Bu, derleme zaman�nda
de�erlendirmenin ger�ekle�mesini sa�lar (optimizasyonlar devre d��� b�rak�lsa bile).
*/
/*
																	SWITCH STATEMENTS

Bir de�i�ken veya ifadeyi uzun bir if else zincirine sokmak hem okunakl�l��� azalt�r hem de �ok etkisiz bir y�ntem olmu� olur. 
Bir de�i�keni veya ifadeyi bir dizi farkl� de�ere kar�� test etmek yayg�n oldu�undan, C++, bu ama� i�in �zel olarak tasarlanm�� bir switch ifadesi ad�nda alternatif
bir ko�ul ifadesi sa�lar. ��te ayn� program�, bir switch kullanarak, yukar�dakiyle ayn� �ekilde:

										#include <iostream>

										void printDigitName(int x)
										{
											switch (x)
											{
												case 1:
													std::cout << "One";
													return;
												case 2:
													std::cout << "Two";
													return;
												case 3:
													std::cout << "Three";
													return;
												default:
													std::cout << "Unknown";
													return;
											}
										}

										int main()
										{
											printDigitName(2);
											std::cout << '\n';

											return 0;
										}


Switch ifadesinin temel fikri basittir: bir ifade (bazen ko�ul olarak adland�r�l�r) bir de�er �retmek �zere de�erlendirilir. E�er ifadenin de�eri, herhangi bir
case etiketinden sonraki de�ere e�itse, e�le�en case etiketi sonras�ndaki ifadeler y�r�t�l�r. E�er e�le�en bir de�er bulunamazsa ve bir default etiketi varsa,
default etiketinin sonras�ndaki ifadeler y�r�t�l�r.

Orijinal if ifadesine k�yasla, switch ifadesinin bir avantaj� sadece bir kez ifadeyi de�erlendirmesidir (bu da daha verimli yapar), ayr�ca switch ifadesi,
her durumda e�itlik testine tabi tutulan ifadenin ayn� oldu�unu okuyucuya daha a��k bir �ekilde belirtir.

*** BEST -> Bir se�enek oldu�unda if-else zincirleri yerine switch ifadelerini tercih edin.
* 
Switch  i ba�latma
------------------

Switch ifadesini kullanmaya ba�lamak i�in switch anahtar kelimesini kullan�r�z. Bu anahtar kelimenin ard�ndan, i�inde de�erlendirmek istedi�imiz ko�ulu i�eren
parantezleri kullan�r�z. Genellikle ifade sadece tek bir de�i�ken olacakt�r, ancak bu ge�erli bir ifade olabilir.

Tek bir k�s�tlama vard�r: ko�ulun bir integral t�r�ne de�erlendirilmesi gerekir (hangi temel t�rlerin integral t�r olarak kabul edildi�ini hat�rlamak i�in 4.1
dersine bakabilirsiniz) veya bir numaraland�rma t�r� olmal�d�r (gelecekteki 13.2 dersinde ele al�nacak olan ba�lant�s�z numaraland�rmalar). veya buna 
d�n��t�r�lebilir olmal�d�r. Y�zen nokta t�rlerine, dizgilere ve �o�u di�er integral olmayan t�rlere de�erlendirilen ifadeler burada kullan�lamaz.
Ko�ul ifadesini takiben bir blok tan�mlar�z. Blok i�inde, e�itlik testi yapmak istedi�imiz t�m de�erleri tan�mlamak i�in etiketleri kullan�r�z. 
�ki t�r etiket bulunmaktad�r.
	1 - Case etiketi
	2 - Default etiketi
Case label
----------
�lk t�r etiket, case anahtar kelimesi kullan�larak bildirilen bir durum etiketidir ve bir sabit ifade ile takip edilir. Sabit ifade, ko�ulun t�r�yle e�le�melidir
veya o t�re d�n��t�r�lebilir olmal�d�r. Ko�ul ifadesinin de�eri, bir durum etiketinden sonraki ifadeye e�itse, y�r�tme o durum etiketinden sonraki 
ilk ifadeyle ba�lar ve ard�ndan s�ral� olarak devam eder.

��te ko�ulun bir durum etiketiyle e�le�ti�i bir �rnek:

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x, de�eri 2'yi �retmek �zere de�erlendirilir
					{
						case 1:
							std::cout << "Bir";
							return;
						case 2: // burada case ifadesi ile e�le�en
							std::cout << "�ki"; // bu y�zden y�r�tme buradan ba�lar
							return; // ve ard�ndan �a�r�y� yapana geri d�neriz
						case 3:
							std::cout << "��";
							return;
						default:
							std::cout << "Bilinmeyen";
							return;
					}
				}

				int main()
				{
					printDigitName(2);
					std::cout << '\n';

					return 0;
				}
				Bu kod : 2 �ki ��kt�s�n� verir. 

Yukar�daki programda x, de�eri 2'yi �retmek �zere de�erlendirilir. De�er 2 olan bir case etiketi oldu�u i�in, y�r�tme bu e�le�en case etiketi alt�ndaki ifadeye ge�er.
Program �ki'yi yazd�r�r ve ard�ndan return ifadesi y�r�t�lerek �a�r�c�ya geri d�ner.

Switch i�inde sahip olabilece�iniz durum etiketlerine pratik bir s�n�rlama yoktur, ancak bir switch i�indeki t�m durum etiketleri benzersiz olmal�d�r. Yani �unu 
yapamazs�n�z:

			switch (x)
			{
				case 54:
				case 54:  // error: zaten var olan de�er 54 !
				case '6': // error: '6', halihaz�rda kullan�lan 54 tamsay� de�erine d�n��t�r�l�yor
			}

Ko�ullu ifade case etiketlerinden herhangi biriyle e�le�miyorsa hi�bir case y�r�t�lmez. Bunun bir �rne�ini birazdan g�sterece�iz.


Default Etiketi
---------------
�kinci t�r etiket ise default etiketi (genellikle default case olarak adland�r�l�r) olup, default anahtar kelimesi kullan�larak bildirilir.
E�er ko�ullu ifade hi�bir case etiketi ile e�le�mezse ve bir default etiketi varsa, y�r�tme default etiketinin hemen sonras�ndaki ilk ifadede ba�lar.

��te ko�ulun default etiketi ile e�le�ti�i bir �rnek:

					#include <iostream>

					void printDigitName(int x)
					{
						switch (x) // x, de�eri 5'i �retmek i�in de�erlendirilir
						{
							case 1:
								std::cout << "Bir";
								return;
							case 2:
								std::cout << "�ki";
								return;
							case 3:
								std::cout << "��";
								return;
							default: // ki hi�bir case etiketi ile e�le�mez
								std::cout << "Bilinmeyen"; // bu nedenle y�r�tme buradan ba�lar
								return; // ve ard�ndan �a��ran konuma d�n�l�r
						}
					}

					int main()
					{
						printDigitName(5);
						std::cout << '\n';

						return 0;
					}

					Bu kodun ��kt�s�: "Bilinmeyen" OLUR 
Varsay�lan etiket iste�e ba�l�d�r ve bir switch ifadesinde yaln�zca bir varsay�lan etiket olabilir. Geleneksel olarak, varsay�lan durum switch blo�unun
en sonuna yerle�tirilir.

*** BEST -> Switch blo�undaki varsay�lan durumu en sona yerle�tiriniz
*/

/*
Case veya Default de�er ile e�le�medi�i durum da ne olur
--------------------------------------------------------
E�er ko�ullu ifadenin de�eri herhangi bir case etiketi ile e�le�miyorsa ve varsay�lan bir durum belirlenmediyse, switch blo�undaki hi�bir case �al��t�r�lmaz.
��lem, switch blo�unun sonundan sonra devam eder.

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x, de�eri 5 �retmek i�in de�erlendirilir
					{
					case 1:
						std::cout << "Bir";
						return;
					case 2:
						std::cout << "�ki";
						return;
					case 3:
						std::cout << "��";
						return;
					// e�le�en bir case bulunmuyor ve varsay�lan durum da yok
					}

					// bu nedenle y�r�tme buradan devam eder
					std::cout << "Merhaba";
				}

				int main()
				{
					printDigitName(5);
					std::cout << '\n';

					return 0;
				}

Yukar�daki �rnekte, x'in de�eri 5 olarak de�erlendirilir, ancak 5'e e�le�en bir case etiketi bulunmamakta ve varsay�lan bir durum da bulunmamaktad�r. 
Sonu� olarak, hi�bir case �al��t�r�lmaz. Y�r�tme, switch blo�unun sonras�nda devam eder ve "Merhaba" yazd�r�l�r.

Break keyword�n� kullanmak. 
---------------------------

Yukar�daki �rneklerde etiketlerden sonraki ifadelerin y�r�t�lmesini durdurmak i�in return ifadelerini kulland�k. Ancak bu ayn� zamanda t�m fonksiyondan ��k���
sa�lar. Break ifadesi (break anahtar kelimesi kullan�larak tan�mlanan), derleyiciye switch i�indeki ifadeleri tamamlad���m�z� ve y�r�tmenin switch blo�unun 
sonundaki ifadeyle devam etmesi gerekti�ini s�yler. Bu, switch ifadesinden ��kmam�za, ancak t�m fonksiyondan ��kmam�za izin vermeden switch ifadesinden ��k��
yapmam�za olanak tan�r.
A�a��da, return ifadeleri yerine break kullan�larak biraz de�i�tirilmi� bir �rnek verilmi�tir:

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x 3'e e�itlenir
					{
						case 1:
							std::cout << "Bir";
							break;
						case 2:
							std::cout << "�ki";
							break;
						case 3:
							std::cout << "��"; // buradan y�r�tme ba�lar
							break; // switch blo�unun sonuna atlar
						default:
							std::cout << "Bilinmiyor";
							break;
					}

					// y�r�tme buradan devam eder
					std::cout << " Ah-Ah-Ah!";
				}

				int main()
				{
					printDigitName(3);
					std::cout << '\n';

					return 0;
				}
Yukar�daki program:  �� Ah-Ah-Ah !
Her bir etiket alt�ndaki ifadeler, bir break ifadesi veya bir return ifadesi ile sonlanmal�d�r. Bu, switch'in en sonundaki etiket alt�ndaki ifadeleri de kapsar.
E�er bir etiket alt�ndaki ifadeleri bir break veya return ifadesi ile sonland�rmazsan�z ne olaca��n� bir sonraki derste ke�fedece�iz.
*/
/*
Switch d����� (fallthrough) ve kapsam (scoping)
-----------------------------------------------

D���� (Fallthrough)

Bir switch ifadesi bir case etiketi veya iste�e ba�l� bir varsay�lan etiketi ile e�le�ti�inde, y�r�tme e�le�en etiketi takip eden ilk ifadeden ba�lar.
Y�r�tme ard�ndan �u sonland�rma ko�ullar�ndan biri ger�ekle�ene kadar s�ral� olarak devam eder:

* Switch blo�unun sonuna ula��l�r.
* Ba�ka bir kontrol ak�� ifadesi (genellikle bir break veya return), switch blo�unu veya fonksiyonu ��kart�r.
* Ba�ka bir �ey program�n normal ak���n� kesintiye u�rat�r (�rne�in, i�letim sistemi program� kapat�r, evren ��ker, vb.).
* Ba�ka bir case etiketinin varl���, bu sonland�rma ko�ullar�ndan biri de�ildir - bu nedenle bir break veya return olmadan y�r�tme, sonraki case'lere ta�acakt�r.

��te bu davran��� sergileyen bir program �rne�i:

					#include <iostream>

					int main()
					{
						switch (2)
						{
						case 1: // E�le�mez
							std::cout << 1 << '\n'; // Atland�
						case 2: // E�le�me!
							std::cout << 2 << '\n'; // Y�r�tme burada ba�lar
						case 3:
							std::cout << 3 << '\n'; // Bu da y�r�t�l�r
						case 4:
							std::cout << 4 << '\n'; // Bu da y�r�t�l�r
						default:
							std::cout << 5 << '\n'; // Bu da y�r�t�l�r
						}

						return 0;
					}
					Bu program�n ��kt�s� 2 3 4 5 
Bu muhtemelen istedi�imiz sonu� de�il! Bir etiket alt�ndaki bir ifadeden sonraki ifadelere ak�� ger�ekle�ti�inde, buna d���� (fallthrough) denir.
Bir case veya default etiketi alt�ndaki ifadeler bir kere y�r�t�lmeye ba�lad���nda, bunlar ard���k case'lere ta�abilir (fallthrough). Bu durumu
engellemek i�in genellikle break veya return ifadeleri kullan�l�r.
D���� (fallthrough) genellikle istenmeyen veya kas�tl� olarak yap�lmayan bir durum oldu�u i�in, bir�ok derleyici ve kod analiz arac� d����� bir uyar� olarak i�aretler.

[[fallthrough]] �zniteli�i
--------------------------

Kas�tl� d����� belirtmek i�in yorum eklemek, d�����n ama�land���n� di�er geli�tiricilere bildirmek i�in yayg�n bir uygulamad�r. Bu di�er geli�tiriciler i�in i�e yarar,
ancak derleyici ve kod analiz ara�lar� yorumlar� nas�l yorumlayacaklar�n� bilmedi�i i�in uyar�lar� ortadan kald�rmaz.
Bu durumu ele almak i�in, C++17 yeni bir �znitelik ekler, bu �znitelik [[fallthrough]] olarak adland�r�l�r.
�znitelikler, programc�n�n kod hakk�nda derleyiciye ek bilgi sa�lamas�na olanak tan�yan modern bir C++ �zelli�idir. Bir �znitelik belirtmek i�in �znitelik ad� �ift
k��eli parantez aras�na yerle�tirilir. �znitelikler ifadeler de�ildir - bunun yerine, ba�lamsal olarak ilgili olduklar� hemen hemen her yerde kullan�labilirler.

[[fallthrough]] �zniteli�i, d�����n kas�tl� oldu�unu belirtmek i�in bir null statement'i de�i�tirir (ve uyar�lar�n tetiklenmemesi gerekir):

					#include <iostream>

					int main()
					{
						switch (2)
						{
						case 1:
							std::cout << 1 << '\n';
							break;
						case 2:
							std::cout << 2 << '\n'; // Y�r�tme burada ba�lar
							[[fallthrough]]; // Kas�tl� d���� - null ifadeyi belirtmek i�in noktal� virg�l kullan�lmal�d�r
						case 3:
							std::cout << 3 << '\n'; // Bu da y�r�t�l�r
							break;
						}

						return 0;
					} -> Bu program 2 3 ��kt�s�n� verir. Ve fallthrough hakk�nda bir uyar� olu�turmaz.

Bu �rnek, C++17'de tan�t�lan [[fallthrough]] �zniteli�ini kullanarak kas�tl� d����� g�stermektedir. Bu �znitelik, derleyiciye d�����n kas�tl� oldu�unu belirtir ve
uyar�lar�n tetiklenmemesi gerekti�ini ifade eder.

*** Best -> Kas�tl� d����� belirtmek i�in [[fallthrough]] �zniteli�ini (bir null ifade ile birlikte) kullan�n.





S�ral� Case labeller.
---------------------
Unutmay�n ki y�r�tme, e�le�en bir case etiketinden sonraki ilk ifade ile ba�lar. Case etiketleri ifadeler de�ildir (etiketlerdir), bu nedenle say�lmazlar.

Yukar�daki programdaki t�m case ifadelerinden sonraki ilk ifade return true oldu�u i�in, herhangi bir case etiketi e�le�irse, fonksiyon true de�erini d�nd�recektir.

Bu nedenle, t�m bu case etiketlerini ayn� ifadeler k�mesini payla�acak �ekilde "y���p" (stack) kullanabiliriz. Bu, d���� (fallthrough) davran��� olarak kabul
edilmez, bu nedenle burada yorum veya [[fallthrough]] kullan�m�na gerek yoktur.

* if else ler gibi switc-case yap�s�nda caselerin bir scop u yoktur hepsi switch in scopunda say�l�rlar. 
* case 'a':
* case 'b': -> bu �ekilde b�rakt���nda bu fallthrough say�lmaz o y�zden uyar� vermez bu logical or gibi durumlar� kullanmak yerine de tercih edilebilecek bir yol. 
* case 'c':

Switch i�inde de�i�ken bildirimi ve ba�lat�lmas�
------------------------------------------------
Switch i�inde, case etiketlerinden �nce ve sonra de�i�kenleri bildirebilir veya tan�mlayabilirsiniz (ancak ba�latamazs�n�z):

			switch (1)
			{
				int a; // uygun: case etiketlerinden �nce tan�mlama izin verilir
				int b{ 5 }; // hatal�: case etiketlerinden �nce ba�latma izin verilmez

				case 1:
					int y; // uygun fakat iyi bir uygulama de�il: bir case i�inde tan�mlama izin verilir
					y = 4; // uygun: atama izin verilir
					break;

				case 2:
					int z{ 4 }; // hatal�: ba�ka case'ler varsa ba�latma izin verilmez
					y = 5; // uygun: y yukar�da bildirildi�i i�in burada da kullanabiliriz
					break;

				case 3:
					break;
			}

Her ne kadar de�i�ken y, case 1'de tan�mlanm�� olsa da, case 2'de de kullan�lm��t�r. Switch i�indeki t�m ifadeler ayn� kapsam�n bir par�as� olarak kabul edilir.
Bu nedenle, bir case i�inde tan�mlanan bir de�i�ken, o de�i�kenin tan�mland��� case hi� �al��t�r�lmasa bile (��nk� switch onu atlad�) daha sonraki bir case i�inde
kullan�labilir!

Ancak, de�i�kenlerin ba�lat�lmas�, tan�m�n �al��t�r�lmas�n� gerektirir (��nk� ba�lat�c�n�n de�eri o noktada belirlenmelidir). De�i�kenlerin ba�lat�lmas�, ba�lat�c�
atlanabilece�i i�in son case d���nda herhangi bir case'te izin verilmez (bu, de�i�kenin ba�lat�lmam�� kalmas�na neden olabilir). Ba�latma, ayr�ca switch'in bunlara
ula�ma �ans� olmad��� i�in ilk case'ten �nce de izin verilmez.

Bir case, yeni bir de�i�ken tan�mlamaya ve/veya ba�latmaya ihtiya� duyuyorsa, en iyi uygulama, bunu case ifadesinin alt�nda a��k bir blok i�inde yapmakt�r:

			switch (1)
			{
				case 1:
				{ // burada a��k bir blok eklemenin fark�na bak�n
					int x{ 4 }; // uygun, de�i�kenler bir case i�indeki bir blok i�inde ba�lat�labilir
					std::cout << x;
					break;
				}
				default:
					std::cout << "varsay�lan durum\n";
					break;
			}


E�er bir case ifadesinde kullan�lan de�i�kenleri tan�ml�yorsan�z, bunu case i�inde bir blok i�inde yap�n.

Goto ifadesi
------------
�nceleyece�imiz bir sonraki kontrol ak�� ifadesi, ko�ulsuz atlama ifadesidir. Ko�ulsuz atlama, y�r�tmenin kod i�inde ba�ka bir noktaya atlamas�na neden olur.
"Ko�ulsuz" terimi, atlaman�n her zaman ger�ekle�ti�i anlam�na gelir (bir if ifadesi veya switch ifadesinin aksine, atlama yaln�zca bir ifadenin sonucuna ba�l�
olarak ko�ullu olarak ger�ekle�ir).

C++'ta, ko�ulsuz atlama ifadeleri, bir goto ifadesi arac�l���yla uygulan�r ve atlaman�n yap�laca�� konum, bir ifade etiketi kullan�larak belirlenir. A�a��daki �rnek,
bir goto ifadesi ve ifade etiketi kullan�m�n� g�stermektedir:

			#include <iostream>
			#include <cmath> // sqrt() fonksiyonu i�in

			int main()
			{
				double x{};
			tryAgain: // bu bir ifade etiketidir
				std::cout << "Bir non-negatif say� girin: ";
				std::cin >> x;

				if (x < 0.0)
					goto tryAgain; // bu goto ifadesidir

				std::cout << x << " say�s�n�n karek�k� " << std::sqrt(x) << '\n';
				return 0;
			}

Bu programda, kullan�c�ya non-negatif bir say� girmesi istenir. Ancak, e�er bir negatif say� girilirse, program tryAgain etiketine geri d�nmek i�in bir goto ifadesini
kullan�r. Kullan�c�ya tekrar yeni bir say� girmesi istenir. Bu �ekilde, kullan�c� ge�erli bir giri� yapana kadar s�rekli olarak kullan�c�dan giri� isteyebiliriz.

Output bu �ekilde: 
			Bir non-negatif say� girin: -4
			Bir non-negatif say� girin: 4
			4 say�s�n�n karek�k� 2

�fade etiketlerinin fonksiyon kapsam� vard�r
--------------------------------------------

Nesne kapsam�yla ilgili (7. b�l�mdeki) b�l�mde, iki t�r kapsam� ele alm��t�k: yerel (blok) kapsam ve dosya (global) kapsam. �fade etiketleri, ���nc� bir kapsam t�r�n�
kullan�r: fonksiyon kapsam�, yani etiket, bildirim noktas�ndan �nce bile fonksiyon boyunca g�r�n�r. Goto ifadesi ve ilgili ifade etiketi ayn� fonksiyonda g�r�nmelidir.

Yukar�daki �rnek, geriye do�ru atlama yapan bir goto ifadesini g�sterir (fonksiyon i�inde �nceki bir noktaya). Goto ifadeleri ayn� zamanda ileri do�ru da atlayabilir:

			#include <iostream>

			void printCats(bool skip)
			{
				if (skip)
					goto end; // ileri do�ru atlama; ifade etiketi 'end' burada fonksiyon kapsam�na sahip oldu�u i�in g�r�n�r

				std::cout << "kedi\n";
			end:
				; // ifade etiketleri bir ifade ile ili�kilendirilmelidir
			}

			int main()
			{
				printCats(true);  // yazd�rma ifadesini atlar ve hi�bir �ey yazd�rmaz
				printCats(false); // "kedi" yazd�r�r

				return 0;
			}

��kt�m�z : kedi


�leri atlama �tesinde, yukar�daki programda de�inmeye de�er birka� ilgin� nokta bulunmaktad�r.

�lk olarak, ifade etiketlerinin bir ifade ile ili�kilendirilmesi gerekti�ini unutmay�n (bu nedenle adlar�: bir ifadeyi etiketlerler). Fonksiyonun sonunda bir ifade
olmad���ndan, bir ifadeye etiket eklemek i�in bir null ifadesi kullanmak zorunda kald�k. �kinci olarak, ifade etiketlerinin fonksiyon kapsam�na sahip olmalar�
nedeniyle, hen�z etiket bildirmemi� olmam�za ra�men etiketlenmi� ifadeye atlamay� ba�arabildik. �leriye do�ru ifade etiketlerinin �nceden bildirilmesine gerek yoktur.
���nc�s�, yukar�daki program�n iyi bir �rnek olmad���n� a��k�a belirtmek �nemlidir - yazd�rmay� atlamak i�in bir goto ifadesi yerine bir if ifadesi kullanmak daha 
iyiydi. Atlaman�n iki temel k�s�tlamas� vard�r: Bir fonksiyonun s�n�rlar� i�inde yaln�zca atlama yapabilirsiniz (bir fonksiyondan ba�ka bir fonksiyona atlama 
yapamazs�n�z) ve ileri atlama yaparsan�z, atlama yap�lan konumda hala kapsamda olan herhangi bir de�i�kenin ba�lat�lmas�n�n �zerine atlama yapamazs�n�z. �rne�in:

				int main()
				{
					goto skip;   // hata: bu atlama yasa d���d�r ��nk�...
					int x { 5 }; // bu ba�lat�lm�� de�i�ken, 'skip' ifade etiketinde hala kapsamdad�r
				skip:
					x += 3;      // x ba�lat�lmam�� olsayd� bu ne de�erlendirilirdi ki?
					return 0;
				}

Dikkat edin ki, bir de�i�ken ba�lat�m�n�n �zerine geriye do�ru atlayabilirsiniz ve ba�lat�m ger�ekle�tirildi�inde de�i�ken yeniden ba�lat�lacakt�r.

go to kullan�m�ndan ka��n
-------------------------
C++ (ve di�er modern y�ksek seviyeli dillerde de) goto ifadesi kullan�m� ka��n�lmal�d�r. Edsger W. Dijkstra, �nl� ama okunmas� zor olan "Go To Statement Considered
Harmful" adl� bir makalede goto ifadesinden ka��n�lmas�n� savunmu�tur. Goto'nun temel sorunu, bir programc�n�n kod i�inde istedi�i yere rastgele atlamas�na izin 
vermesidir. Bu, bilgi ak���n� takip etmeyi son derece zorla�t�ran "spaghetti code" olarak da bilinen bir �eyi yarat�r. Spaghetti code, bir taba�� and�ran (t�m�yle
kar���k ve dolanm��) bir y�r�tme yoluna sahip olan kodu ifade eder, bu da b�yle bir kodun mant���n� takip etmeyi son derece zorla�t�r�r.

Dijkstra, biraz mizahi bir dille, "programc�lar�n kalitesi, �rettikleri programlardaki goto ifadelerinin yo�unlu�unun azalan bir fonksiyonudur" diyor.

Goto ifadesi kullan�larak yaz�lan neredeyse herhangi bir kod, C++'taki di�er yap�larda daha a��k bir �ekilde yaz�labilir, �rne�in if ifadeleri ve d�ng�ler gibi. 
Bir istisna, i� i�e ge�mi� bir d�ng�den ��kman�z gerekti�inde, ancak t�m fonksiyondan ��kmaman�z gerekti�inde ortaya ��kar - bu durumda, d�ng�lerin hemen �tesine
gitmek i�in bir goto muhtemelen en temiz ��z�md�r.

*** BEST -> Goto ifadelerinden ka��n�n (alternatifler kodun okunabilirli�i a��s�ndan �nemli �l��de daha k�t� de�ilse).
*/
/*
												8.8 LOOPLAR ( D�NG�LER ) VE WH�LE �FADELER�

While D�ng�leri 
---------------
while (condition)
	statement;

�eklinde tan�mlanan C++ �n sa�lad��� 3 d�ng�den biridir. Condition true oldu�u s�rece while blo�undaki ifadeler �al��acakt�r. condition her zaman true ise while her 
zaman �al��acakt�r buna sonsuz d�ng� denir. Kas�tl� olarak d�ng�y� loop a sokabiliriz.
Kas�tl� sonsuz d�ng�:  -> while(True) ... �eklindedir. 

burada d�ng� �art�nda kullan�lan de�i�kenlere d�ng� de�i�keni denir. Fortran dan kalan bir gelenek olarak i j k harfleri kullan�lsa da bu de�i�kenleri arad���m�zda 
i j k harfi her hangi biri ile alak� bir ge�tikleri t�m yerler gelebilri o y�zden baz� programc�lar iii jjj kkk isimlendirmelerini kullanmay� tercih ediyorlar.
Tamsay� d�ng� de�i�kenleri genellikle i�aretli olmal�d�r, ��nk� i�aretsiz tamsay�lar beklenmeyen sorunlara yol a�abilir. A�a��daki kodu d���n�n:
				#include <iostream>

				int main()
				{
					unsigned int count{ 10 }; // not: unsigned

					// 10'dan 0'a kadar say
					while (count >= 0)
					{
						if (count == 0)
						{
							std::cout << "blastoff!";
						}
						else
						{
							std::cout << count << ' ';
						}
						--count;
					}

					std::cout << '\n';

					return 0;
				}

Yukar�daki �rne�e bir g�z at�n ve hatay� fark edebiliyor musunuz? Bu konuda daha �nce g�rmemi�seniz pek a��k de�il.

Bu program�n asl�nda sonsuz bir d�ng� oldu�u ortaya ��k�yor. �stenildi�i gibi, 10 9 8 7 6 5 4 3 2 1 blastoff! yazd�rmaya ba�lar, ancak sonra d�ng� de�i�keni count
ta�ar ve 4294967295'ten (32 bit tamsay�lar varsay�larak) geri saymaya ba�lar. Neden? ��nk� d�ng� ko�ulu count >= 0 asla false olmayacak! Count 0 oldu�unda, 0 >= 0
true'dir. Ard�ndan --count �al��t�r�l�r ve count 4294967295'e geri d�ner. Ve ��nk� 4294967295 >= 0 true'dir, program devam eder. Count i�aretsiz oldu�undan, negatif
olamaz ve negatif olamad���ndan d�ng� sona ermez.

*** BEST -> Tamsay� d�ng� de�i�kenleri genellikle i�aretli bir tamsay� t�r� olmal�d�r
* 
* 
�� i�e d�ng�ler
---------------
Ayr�ca, di�er d�ng�lerin i�ine g�m�lm�� d�ng�ler kullanmak da m�mk�nd�r. A�a��daki �rnekte, i� i�e ge�mi� d�ng� (i� d�ng� olarak adland�rd���m�z) ve d�� d�ng�
her birinin kendi sayac�na sahiptir. �� d�ng�n d�ng� ifadesinin, d�� d�ng�n sayac�n� da kullanmas� dikkat �ekicidir!

				#include <iostream>

				int main()
				{
					// d�� d�ng� 1 ile 5 aras�nda
					int outer{ 1 };
					while (outer <= 5)
					{
						// Her d�� d�ng� iterasyonu i�in, d�ng� g�vdesindeki kod bir kez �al���r

						// i� d�ng� 1 ile d�� d�ng� aras�nda
						int inner{ 1 };
						while (inner <= outer)
						{
							std::cout << inner << ' ';
							++inner;
						}

						// her sat�r�n sonunda yeni bir sat�r yazd�r
						std::cout << '\n';
						++outer;
					}

					return 0;
				}

program ��kt�s� 
					1
					1 2
					1 2 3
					1 2 3 4
					1 2 3 4 5


Do While ifadesi
----------------
Bir `do-while` ifadesi, bir `while` d�ng�s� gibi �al��an bir d�ng� yap�s�d�r, ancak ifade her zaman en az bir kez �al���r. �fade y�r�t�ld�kten sonra,
do-while d�ng�s� ko�ulu kontrol eder. E�er ko�ul true olarak de�erlendirilirse, y�r�tme yolu do-while d�ng�s�n�n ba��na atlar ve tekrar y�r�t�l�r.

Pratikte, do-while d�ng�leri genellikle kullan�lmaz. Ko�ulu d�ng�n�n alt�nda bulundurmak, d�ng� ko�ulunu belirsiz k�labilir ve bu da hatalara neden olabilir.
Bir�ok geli�tirici, bu nedenle do-while d�ng�lerinden ka��nmay� �nerir. Biz daha yumu�ak bir tav�r alacak ve e�it bir se�enek oldu�unda while d�ng�lerini do-while
d�ng�lerine tercih etmeyi savunaca��z.
Kullan�m� 
			do{
			statements
			}
			while(condition);

Bunlar� hat�rlad���m�z i�in �ok not almad�m. �ok �zel konular de�il �o�u programlama dilinde ortak olan genel ama �ok efektif yap�lard�r. Anlamad���n veya
hat�rlamad���n bir �ey olursa tekrar siteden kontrol etmen de fayda var. 

For �fadeleri 
-------------
�ok uzun zamand�r, C++ dilinde en �ok kullan�lan d�ng� ifadesi for ifadesidir. For ifadesi (ayn� zamanda for d�ng�s� olarak adland�r�l�r), a��k bir d�ng�
de�i�kenimiz oldu�unda tercih edilir ��nk� bize d�ng� de�i�kenlerini tan�mlama, ba�latma, test etme ve de�erini de�i�tirme imkan� tan�r, bunu kolayca ve 
�zl� bir �ekilde yapmam�za olanak sa�lar.

C++11'den itibaren iki farkl� t�rde for d�ng�s� bulunmaktad�r. Bu derste klasik for ifadesini ele alaca��z ve gelecekteki bir derste (16.7 -- Aral�k tabanl� 
for d�ng�leri (for-each)) diziler ve iteratorlar gibi di�er �nceden gereken konular� ele ald�ktan sonra daha yeni olan aral�k tabanl� for ifadesini ele alaca��z.

Kullan�m�:
			for (init-statement; condition; end-expression)
			   statement;
for d�ng�s�n�z daha iyi anlamak i�in for d�ng�s�n� bir while d�ng�s�ne d�n��t�relim:
					{ // buradaki blo�a dikkat edin
						init-ifadesi; // d�ng�de kullan�lan de�i�kenleri tan�mlamak i�in kullan�l�r
						while (ko�ul)
						{
							ifade;
							son-ifade; // ko�ulun tekrar de�erlendirilmeden �nce d�ng� de�i�kenini de�i�tirmek i�in kullan�l�r
						}
					} // d�ng� i�inde tan�mlanan de�i�kenler burada kapsam d���na ��kar

for-d�ng�s�n�n de�erlendirilmesi 3 k�s�mda ger�ekle�ir:

�lk olarak, init-ifadesi y�r�t�l�r. Bu, d�ng� ba�lat�ld���nda yaln�zca bir kez ger�ekle�ir. Init-ifadesi genellikle de�i�ken tan�mlama ve ba�latma i�in kullan�l�r.
Bu de�i�kenlere "d�ng� kapsam�" denir, bu asl�nda bu de�i�kenlerin tan�m noktas�ndan d�ng� ifadesinin sonuna kadar var oldu�u bir blok kapsam� bi�imidir. While d�ng�
e�de�erimizde init-ifadesinin, d�ng�y� i�eren bir blo�un i�inde oldu�unu g�rebilirsiniz, bu nedenle init-ifadesinde tan�mlanan de�i�kenler, d�ng�y� i�eren blo�un 
sona erdi�i noktada kapsam d���na ��kar.

�kinci olarak, her d�ng� iterasyonu i�in ko�ul de�erlendirilir. Bu, true olarak de�erlendirilirse ifade y�r�t�l�r. Bu, false olarak de�erlendirilirse d�ng� sona 
erer ve y�r�tme, d�ng�den sonraki sonraki ifade ile devam eder.

Son olarak, ifade y�r�t�ld�kten sonra end-ifadesi de�erlendirilir. Genellikle bu ifade, init-ifadesinde tan�mlanan d�ng� de�i�kenlerini art�rmak veya azaltmak
i�in kullan�l�r. End-ifadesi de�erlendirildikten sonra y�r�tme ikinci ad�ma geri d�ner (ve ko�ul tekrar de�erlendirilir).

Hadi �rnek bir for d�ng�s�ne bakal�m ve nas�l �al��t���n� tart��al�m:
						#include <iostream>

						int main()
						{
							for (int i{ 1 }; i <= 10; ++i)
								std::cout << i << ' ';

							std::cout << '\n';

							return 0;
						}


�lk olarak, i ad�nda bir d�ng� de�i�keni bildiriyoruz ve ona 1 de�erini at�yoruz.

�kinci olarak, i <= 10 de�erlendirilir ve ��nk� i'nin de�eri 1'dir, bu true olarak de�erlendirilir. Sonu� olarak, ifade y�r�t�l�r, bu da 1 ve bir bo�luk yazd�r�r.

Son olarak, ++i de�erlendirilir, bu da i'yi 2'ye art�r�r. Ard�ndan d�ng� ikinci ad�ma geri d�ner.

�imdi, i <= 10 tekrar de�erlendirilir. i'nin de�eri 2 oldu�u i�in bu true olarak de�erlendirilir, bu nedenle d�ng� tekrar iter. �fade 2 ve bir bo�luk yazd�r�r ve i 3'e artt�r�l�r. D�ng�, sonunda i 11'e art�r�ld���nda, i <= 10 false olarak de�erlendirilir ve d�ng� ��kar.

Bu nedenle, bu program �u sonucu yazd�r�r:

1 2 3 4 5 6 7 8 9 10
�rnek olmas� a��s�ndan yukar�daki for d�ng�s�n� e�de�er bir while d�ng�s�ne �evirelim:
						#include <iostream>

						int main()
						{
							{ // Buradaki blok, i i�in blok kapsam�n� sa�lar
								int i{ 1 }; // �lk ifademiz
								while (i <= 10) // Ko�ulumuz
								{
									std::cout << i << ' '; // �fademiz
									++i; // Biti� ifademiz
								}
							}

							std::cout << '\n';
						}
Tabii ki, i�te �evirisi:

"Bu kadar da k�t� g�r�nm�yor, de�il mi? Dikkat edin ki, d��taki s�sl� parantezler burada gereklidir ��nk� i, d�ng� sona erdi�inde kapsam d���na ��kar.

For d�ng�leri, yeni programc�lar i�in okunmas� zor olabilir -- ancak, deneyimli programc�lar bunlar� sever ��nk� bunlar, d�ng� de�i�kenleri, d�ng� ko�ullar�
ve d�ng� de�i�keni de�i�tiricileri hakk�nda gereken t�m bilgileri �nde sunan �ok kompakt bir d�ng� yapma yoludur. Bu, hatalar� azaltmaya yard�mc� olur."

Burada i yi bir artt�rd���m�z �rnekleri g�rd�k s�rekli olarak fakat bunu sabit olarak d���nme. �rne�in i yi 2 artt�rd���m�z �rne�e bakal�m:
						#include <iostream>

						int main()
						{
							for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
								std::cout << i << ' ';

							std::cout << '\n';

							return 0;
						}
Ayn� zaman da azaltabiliriz. Kendini bu konuda k�s�tlamadan syntax ve semanti�e uydu�un s�rece bozmadan oynayabilece�in bir oyuncak gibi d���n :D

for-d�ng� ko�ullar�nda operator!='�n tehlikeleri
------------------------------------------------
Bir d�ng� ko�ulu yazarken, genellikle ko�ulu bir�ok farkl� �ekilde ifade edebiliriz. A�a��daki iki d�ng� de ayn� �ekilde �al���r:
						#include <iostream>

						int main()
						{
							for (int i { 0 }; i < 10; ++i) // < operat�r�n� kullan�r.
								 std::cout << i;

							for (int i { 0 }; i != 10; ++i) // != operat�r�n� kullan�r.
								 std::cout << i;

							 return 0;
						}
Hangi tercih edilmelidir? �lk se�enek tercih edilmelidir ��nk� i'nin de�eri 10'u ge�se bile d�ng� sona erer, oysa ikinci se�enek b�yle bir durumu sonland�rmaz.
A�a��daki �rnek bunu g�stermektedir:

						#include <iostream>

						int main()
						{
							for (int i { 0 }; i < 10; ++i) // uses <, still terminates
							{
									std::cout << i;
									if (i == 9) ++i; // jump over value 10
							}

							for (int i { 0 }; i != 10; ++i) // uses !=, sonsuz d�ng�
							{
									std::cout << i;
									if (i == 9) ++i; // 10 de�erini atlar 11 != 10 sorgusu da true de�eri d�nece�i i�in devam edecektir.
							}

								return 0;
						}
*** BEST -> For-d�ng� ko�ulu i�inde say�sal kar��la�t�rmalar yaparken != (e�it de�il) operat�r�nden ka��n�lmal�d�r.

Bir Hata ile Bir Kay�p" veya "Bir Eksik Hata -> Off-by-one error 
----------------------------------------------------------------
Yeni programc�lar�n for d�ng�leri (ve sayac� kullanan di�er d�ng�ler) ile en b�y�k sorunlar�ndan biri, bir fazla veya bir eksik i�lemle istenen sonucu �reten
off-by-one hatalar�d�r. Bir �rnek g�relim:

			#include <iostream>

			int main()
			{
				// oops, <= yerine < operat�r�n� kulland�k.
				for (int i{ 1 }; i < 5; ++i)
				{
					std::cout << i << ' ';
				}

				std::cout << '\n';

				return 0;
			}
Bu program�n 1 2 3 4 5 yazd�rmas� bekleniyordu, ancak yanl�� ili�kisel operat�r� kulland���m�z i�in sadece 1 2 3 4 yazd�r�yor.

Bu hatalar�n en yayg�n nedeni yanl�� ili�kisel operat�r� kullanmakt�r, ancak bazen post-art�rma veya post-azaltma yerine pre-art�rma veya pre-azaltma 
kullanarak veya tam tersiyle de meydana gelebilirler.

Atlanan ifadeler - Omitted Expressions
--------------------------------------
"For loops" i�inde herhangi bir veya t�m ifadeleri atlayan d�ng�ler yazmak m�mk�nd�r. �rne�in, a�a��daki �rnekte init-ifadesini ve end-ifadesini atlayarak 
sadece ko�ulu b�rakaca��z:
				#include <iostream>

				int main()
				{
					int i{ 0 };
					for ( ; i < 10; ) // init-statement yok veya end-expression yok
					{
						std::cout << i << ' ';
						++i;
					}

					std::cout << '\n';

					return 0;
				}

Bu for d�ng�s�	"0 1 2 3 4 5 6 7 8 9" sonucunu �retir. 
D�ng� de�i�keninin ba�lat�lmas�n� ve art�r�lmas�n� for d�ng�s�ne b�rakmak yerine bunu manuel olarak ger�ekle�tirdik. Bu �rnekte bunu sadece akademik ama�larla yapt�k,
ancak zaten bir d�ng� de�i�keniniz varsa (��nk� ba�ka bir yerde tan�mlanm�� olabilir) veya ba�ka bir �ekilde art�rm�yorsan�z, d�ng� de�i�kenini bildirmemek veya 
end-ifadesinde art�rmamak istedi�iniz durumlar olabilir.

�ok s�k kar��la��lmamakla birlikte, �u �rnek sonsuz bir d�ng� olu�turur:

				for (;;)
					ifade;
Yukar�daki �rnek, �u ifade ile e�de�erdir:

				while (true)
					ifade;

Bu biraz beklenmedik olabilir, ��nk� genellikle atlanan bir ko�ul ifadesinin false olarak ele al�nmas� beklenir. Ancak, C++ standard� atlanan bir ko�ul ifadesinin 
for d�ng�s�nde true olarak ele al�nmas� �eklinde a��k�a (ve tutars�z bir �ekilde) tan�mlar.
Bu t�r bir for d�ng�s� bi�iminden ka��n�lmas�n� ve bunun yerine while(true) kullan�lmas�n� �neririz.

�ok saya�l� for d�ng�leri
-------------------------

For-d�ng�leri genellikle yaln�zca bir de�i�ken �zerinde d�ner, ancak bazen for-d�ng�leri birden �ok de�i�kenle �al��mak zorunda kalabilir. Bu durumu desteklemek
i�in programc�, init-ifadesinde birden �ok de�i�keni tan�mlayabilir ve end-ifadesinde virg�l operat�r�n� kullanarak birden �ok de�i�kenin de�erini de�i�tirebilir:

						#include <iostream>

						int main()
						{
							for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
								std::cout << x << ' ' << y << '\n';

							return 0;
						}
Bu d�ng�, iki yeni de�i�keni tan�mlar ve ba�lat�r: x ve y. x'i 0 ile 9 aras�nda bir aral�kta d�nd�r�r ve her iterasyonun ard�ndan x artt�r�l�rken y azalt�l�r.

Bu program a�a��daki sonucu �retir:
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0


Bu, C++ dilinde ayn� ifadede birden �ok de�i�ken tan�mlaman�n ve virg�l operat�r�n�n kullan�lmas�n�n kabul edilebilir bir uygulama olarak d���n�ld��� neredeyse
tek yerdir.

*** BEST -> Bir for ifadesi i�inde birden �ok de�i�ken tan�mlamak (init-ifadesinde) ve virg�l operat�r�n� (end-ifadesinde) kullanmak kabul edilebilir bir uygulamad�r.


�� i�e for d�ng�leri
--------------------

Di�er d�ng� t�rleri gibi, for d�ng�leri de ba�ka d�ng�lerin i�ine yerle�tirilebilir. A�a��daki �rnekte, bir for d�ng�s�n� ba�ka bir for d�ng�s�n�n i�ine
yerle�tiriyoruz:


						#include <iostream>

						int main()
						{
							for (char c{ 'a' }; c <= 'e'; ++c) // harfler �zerinde d�� d�ng�
							{
								std::cout << c; // �nce harfimizi yazd�r

								for (int i{ 0 }; i < 3; ++i) // t�m say�lar �zerinde i� i�e d�ng�
									std::cout << i;

								std::cout << '\n';
							}

							return 0;
						}

Her d�� d�ng� iterasyonu i�in i�teki d�ng� tamamen �al���r. Sonu� olarak ��kt� �u �ekildedir:
a012
b012
c012
d012
e012
Buradaki olay ��yle a��klanabilir: D��taki d�ng� ilk olarak �al���r ve char c 'a' olarak ba�lat�l�r. Ard�ndan c <= 'e' de�erlendirilir, bu do�ru oldu�undan d�ng�
g�vdesi �al��t�r�l�r. c 'a' olarak ayarland���ndan, ilk olarak 'a' yazd�r�l�r. Ard�ndan i�teki d�ng� tamamen �al���r (0, 1 ve 2'yi yazd�r�r). Sonra bir sat�r 
sonland�r�c�s� (\n) yazd�r�l�r. �imdi d��taki d�ng� g�vdesi tamamlanm��t�r, bu nedenle d��taki d�ng� tekrar en ba�a d�ner, c 'b' olarak artt�r�l�r ve d�ng� ko�ulu 
yeniden de�erlendirilir. D�ng� ko�ulu hala do�ru oldu�undan, d��taki d�ng�n�n bir sonraki iterasyonu ba�lar. Bu, b012\n'yi yazd�r�r. Ve b�yle devam eder.




																				�ZET
																				----

`for` ifadeleri, C++ dilinde en yayg�n kullan�lan d�ng� t�r�d�r. S�zdizimi genellikle yeni programc�lara biraz karma��k g�r�nse de, onlar� o kadar s�k g�receksiniz ki k�sa s�rede anlayacaks�n�z!

`for` ifadeleri, bir saya� de�i�keniniz oldu�unda m�kemmel bir performans g�sterir. E�er bir sayaca sahip de�ilseniz, `while` ifadesi muhtemelen daha iyi bir se�enektir.

**** BEST
* -A��k bir d�ng� de�i�keni varsa `for` d�ng�lerini tercih edin.
* - A��k bir d�ng� de�i�keni yoksa `while` d�ng�lerini tercih edin.

*/














































































































































































































































































































































































































/*
Write a function called calculate() that takes two integers and a char representing one of the following mathematical operations: +, -, *, /, or % (remainder).
Use a switch statement to perform the appropriate mathematical operation on the integers, and return the result. If an invalid operator is passed into the function, 
the function should print an error message. For the division operator, do an integer division, and don�t worry about divide by zero.

Hint: �operator� is a keyword, variables can�t be named �operator�.
*/