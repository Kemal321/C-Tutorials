// ch4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// learncpp.com -> Chapter 4 my solutions and class notes.


/*

Integers range -> The calculation is according to bits are used to hold math -> -(2^n-1) to (2^n-1) - 1 
8 bits -> 7 for numbers and 1 for sign ( positive or negative )
2^8 -> 256 = [-128,127]


** Signed integer overflow will result in undefined behaviour.
* 
** In C++ integer division C++ drops the fractional portion. !!! NOT ROUNDED, DROPPED.
*/
#include <iostream>
#include <string>
#include <cstdint> // for std::uint8_t
#include <string_view>
/*
void print(int x) {
	std::cout << x;
}
*/
std::string getName()
{
	std::string s { "Alex" };
	return s;
}
double star(double x, double y) {
	return (x * y);
}
double extraction(double x, double y) {
	return (x - y);
}
double division(double x, double y) {
	return (x / y);
}
double addition(double x, double y) {
	return (x + y);
}

double freeFall(double h,double t) {
	constexpr double gravity{ 9.8 };
	constexpr double timeConstant{ 0.5 };

	if (h > gravity * t * t * timeConstant) {
		h = h - (gravity * t * t);
		std::cout << "At " << t << " seconds, the ball is at height: " << h << "meters"<<'\n';
		t = t + 1;
		freeFall(h, t);
	}
	else{
		std::cout << "At " << t << " seconds, the ball is on the ground.";
	}
	return 3.3;
}
int main()
{

	// Modulo writing if there is an overflow. Compiler will wrap around the range. 
	//For example 1 byte is 0-255 = 256 then if we store 280 -> 280/256 = 24 this value will be stored.
	/*
	MODULO WRAPPING EXAMPLE
	unsigned short x{65535};
	std::cout << "x was: " << x << '\n';

	x = 65536;
	std::cout << "x is now: " << x << '\n';

	x = 65537;
	std::cout << "x is now: " << x << '\n';

	*/
	// 4-6 Fixed-width integers and size_t


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// CHARS //



	// Multiliteral character e.g '43' bunlardan ka��n bunlar c++ standartlar�nda yok normalde o y�zden 
	// farkl� sistemlerde farkl� �ekilde tan�mlanm�� olabilirler ve kodlar�n sonu�lar�nda beklenmedik 
	// etkilere neden olabilirler.
	/*
	int y{ 4 };
	print(y);


	Burada yine de 5 yazacak ��nk� optimizasyon i�in cpp inisiyatif alarak 5.0 � 5 ile ayn� lojik olarak ayn� sayacak
	ama y nin bir double a d�n��t�r�lerek ve bu de�er ile YEN� B�R DE���KEN �retildi�i ve fonksiyona bu �ekilde 
	iletildi�ini unutmamak gerekiyor.

	Sonradan �rnekleri de�i�tirirken de�i�en par�alar� yoruma �evirip yenisini yaz�yorum unutma kafan kar��mas�n.

	print(5);
	*/


	/*print(static_cast<int>(5.5));


	// B�ylece uyar� mesaj� olmadan devam etmi� olduk fakat �unu unutma
	// static cast yaparken 1 kullan�lan t�re veya de�i�kene her hangi bir zarar verilmiyor 
	// 2- Burada static cast yaparken mesela unsigned bir t�r� signed a �evirirsen
	// �rn: int s { static_cast<int>(u) }; -> Burada u bir unsigned olursa 
	// static cast onun rangesine yani menziline depo miktar�na bakmaz 
	// O y�zden b�yle bir i�lem yaparken e�er ta�ma olursa beklenmedik sonu�larla kar��la�abiliriz.
	*/


	/*
	std::int8_t myInt {65}; 
	std::cout << myInt << '\n';

	// Burada int8_t ve uint8_t char gibi davran�yor bu baz� yerlerde u �ekilde ama normalde g�rd���n gibi 
	// int yaz�lm�� yani burada seni kand�r�yorlar buna dikkat etmen gerekiyor bunun gibi yerlerde 
	// static_cast<gerekliT�r>() i kullanman gerekebilir.
	// Bu durum ayn� zamanda input al�rken de sorunlar yaratabilir dikkatli olmakta fayda var. 
	// Di�er fixed_width t�rler ise her zaman tam say� de�erli olarak yaz�l�r ve giri� al�rlar. 

	*/
	
	/*// QUIZ - QUESTINO 1
	char ch{};
	std::cout << "Enter a single character: ";
	
	std::cin >> ch;

	std::cout << "You entered " << "'" << ch << "', " << "which has ASCII code " << static_cast<int>(ch) << ".";
	*/

	/* QUEST�ON 2 - OK
	char ch{};
	std::cout << "Enter a single character: ";

	std::cin >> ch;

	std::cout << "You entered " << "'" << ch << "', " << "which has ASCII code ";
	print(ch);
	std::cout << ".\n";
	*/
	// bir �ok yolu varm�� biz birini yapt�k en zekice olan� bir say� ile �arpmak 1 ile mesela yada 1 ��kart�p eklemek gibi
	// veya int fonksiyondan return almak felan filan.


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Compile time contants 
	//int x{ 3 + 4 };
//	std::cout << x;
	// Mesela burada kodu bir kere �al��t�rd�ktan sonra 3 + 4 de�i�meyece�i ve bilinen �eyler oldu�u i�in sonucu 
	// da bilinen bir �eydir o anlamda bir sabit ifadedir. Bir kere derlendikten sonra. Tekrar tekrar hesaplanmas�na gerek
	// olmad��� i�in bilgisayar birinci defadan sonra int x { 7 } diyerek devam eder bir nevi. Bu optimizasyon sa�lar asl�nda.

	// bunlar sabir ifadelerdir yani constant expression Bir de compile-time constant lar var bunlarda de�eri bilinen sabitlerdir
	// yani literaller �rne�in say�lar veya stringler de�erleri bilinir. BUnalra compile-time constant denir. 
	// de�i�kenlerde de bu durum g�z�kebilir tabi bunun olmas� i�in ba�lat�cc�s�n�n bir const olmas� gerekir 
	// yani de�i�kenin de�i�meyece�ini bilmemiz gerekir const int x { 7 }; gibi

	/*
	const int x { 6 };
	const int y { 4 };

	const int z { x + y };

	Mesela burada x ve y bilinen ve sabit ifadeler oldu�u i�in z de de�i�meyecektir bu y�zden z de bir comp.-time const olur.
	bu compile-time constlar genellikle sembolik sabitler olarak kullan�l�r. 
		
	*/

	/*
	Burada derleme zaman� sabitlerinin derleyiciye �al��ma zaman�nda de�il de derleme s�ras�nda optimize edilebilecek
	optimizasyonlar yapma yetene�i verir.
	�rne�in bir sabit yerine bir de�i�ken kullan�ld���nda derleyici bu sabiti do�rudan de�eriyle de�i�tirebilir b�ylece kod h�zl� �al���r.

	�rne�in const double gravity { 9.8 } derleyici burada gravity g�rd���nde gidip adresten almak yerine 9.8 kabul ederek devam eder.
	*/



	/*
	Burada runtime const lar ise runtime a kadar de�erleri bilinmeyen constlard�r. Bunalrda i�te runtime expression olmu� olur.
	---------------------------------------------------------------------------------------------------------------------------
	Herhangi bir de�i�ken, ba�lat�mdan sonra de�i�tirilmemeli ve ba�lat�c� derleme zaman�nda biliniyorsa constexpr olarak
	bildirilmelidir.
	Herhangi bir de�i�ken, ba�lat�mdan sonra de�i�tirilmemeli ve ba�lat�c� derleme zaman�nda bilinmiyorsa const olarak bildirilmelidir.

	Not: Gelecekte, �u an constexpr ile uyumlu olmayan baz� t�rleri 
	(std::string, std::vector gibi dinamik bellek tahsisi kullanan t�rler dahil) tart��aca��z.
	Bu t�rlerin sabit nesneleri i�in�const�kullan�n.
	

	// Hoca devam� var fakat biraz kafa kar��t�r�c� oludu�u i�in tekrar okursun sonraki zamnalarda. Performans a��s�ndan buralar� 
	// bilmek iyi olur gibi. 




	// Kodalarda b�y�l� say�lar yani ne oldu�u bilinmez say�lar kullanmamak en iyisidir. Onun yerine constexpr kullanmak en iyisi 
	// mesela gravity diyip constexpr yan�mlamak varken 9.8 ile �arparsan karde�im bizde sorar�z bu nerden geldi be amk. diye. ehehhehe



	// std::cin>> bo�luklarda kesiyor ve sonraki cin e aktar�yordu. Bundan dolay� std::string ler i�in burada std::getline()
	// � kullanaca��z. Tabi input manip�lat�r� ile std::ws ile std::getline(std::cin >> std::ws , stringName ); Bu �ekilde kullan�m� var.

	/*
	Burada stringlerin uzunlu�unu sorarken member fonksiyon diye bir fonksiyon tipi var onu kullan�yoruz
	std::string name{"Kemaleddin"};
	burada uzunluk bilgisi i�in name.length() yap�yoruz ayn� python gibi.

	normalde function(object) idi bu sefer object.function() olmu� oldu sadece buna da member function diyoz 
	dok�manlarda std::string::length() olarak da ge�er �zel bir fonksiyondur.
	
	*/
	/*
	Burada stringlerin boyunu lenth() fonksiyonu ile al�rken bize unsigned int d�ner s�k�nt� ��karmamas� i�in static_cast<int>() ile
	d�n���m sa�lamam�z laz�m. Ayr�ca C++20 de std::ssize() fonksiyonu da signed int olarak uzunlu�u verir.	
	*/

	/*QUIZ - STD::STRINGS - basarili :D
	* 

	std::string name{};
	int age{};

	std::cout << " Enter your full name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter your age: ";
	std::cin >> age;

	int lengthOfName{ static_cast<int>(name.length()) };


	std::cout << "Your age + length of name is: " << age + lengthOfName ;
	

	*/


	/*
	std::string_view -> bize sadece salt okunur yani read-only �ekilde kullan�lan bir string olarak gelir c++17 den geliyor string_view
	ba�l��� alt�nda gelir bu ayn� string gibi std::string_view objeAd�{} �eklinde tan�mlan�r fakat bunu modify edemeyiz 
	sadece kullanabiliriz. BU y�zden kopyalama i�lemleri olmad��� i�in daha h�zl� �ekilde i�lem yapar�z 
	Bunu �zellikle fonksiyonlar�n parametrelerinde ve kullanabilece�imiz her yerde kullanak bize performas olarak �ok daha 
	i�e yarar avantaj katar.
	
	
	*en iyi �zelli�i bir �ok �ekilde ba�lat�labilir string ile c-style string ile veya ba�ka bir string_view ile ba�lat�labilir.
	* Fonksiyonlarda da yine ayn� �ekilde bu 3 t�r� de kabul edecek ve bilin�siz d�n���m yapar yani implicit casting yapacacakt�r.
	* std::string_view objesi std::string e d�n��meyecektir *** Bunun i�in 2 yol var
	1 std::String i std::string_view ile ba�latarak olu�tururuz 
	2 veya std::string_view i static_cast ile d�n��t�r�r�z 




	std::string ve std::string_view t�rlerinin ikiside constexpr i tam olarak destekler burada string sembolik sabitler laz�m oldu�unda 
	kullan�labilir. 
	*/

/*Imporoper use of std::string_view*/
/*
	std::string_view sv{};
	{
		std::string s {"Hello world!"};
		sv = s;

	}
	
	std::cout << sv << '\n';

	*/
	/*

	std::string_view name { getName() }; // name initialized with return value of function
	std::cout << name << '\n'; // undefined�behavior
	*/
/*
	std::string s { "Hello, world!" };
	std::string_view sv { s }; // sv is now viewing s

	s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
	std::cout << sv << '\n';   // undefined�behavior

*/

//	Yani burada s i sonradan de�i�tirmemiz s e bakan string_view ler invalid olmu� oluyor sonradan tekrar tan�mlamad���m�z s�rece 
	//	invalid bir �ekilde devam edecekler.




/*
Fonksiyonlar� return ederken string view kullan�m�nda 1 e�er bir string e bakan bir string view return edersek bu s�k�nt�l� bir durum
olur ��nk� stringler fonksiyon tamamland���nda silinir b�ylece tan�mlanmayan ve beklenmedik sonu�lar ortaya ��kabilir.
Bir std::string_view'in g�venli bir �ekilde d�nd�r�lebilece�i iki ana durum vard�r. �lk olarak, C tarz� dize de�i�mezleri program�n 
tamam� i�in mevcut oldu�undan, std::string_view d�n�� t�r�ne sahip bir i�levden C tarz� dize de�i�mezlerini d�nd�rmek�uygundur.

2- �kincisi, std::string_view t�r�nde bir fonksiyon parametresinin d�nd�r�lmesi genellikle�uygundur:


e�er stringview ge�ici bir nesneye bak�yorsa ge�ici nesne yok olmadan kullan�lmal� yoksa s�k�nt�lar ��kabilir. 




*/
/*
* Yapt�k gardeeeeeeeeeeeeee�

// CH4 REV�EW QU�Z 1

double x{};
double y{};
char c{};

std::cout << "Enter a double value: ";
std::cin >> x;

std::cout << "Enter a double value: ";
std::cin >> y;

std::cout << "Enter one of the following: +, -, *, or /: ";
std::cin >> c;

if (c == '*')
	std::cout << x <<" " << c << " " << y << " is: " << star(x, y);
else if(c == '/')
	std::cout << x << " " << c << " " << y << "is: " << division(x, y);
else if(c == '+')
	std::cout << x << " " << c <<" " << y << "is: " << addition(x, y);
else
	std::cout << x << " " << c << " " << y << "is: " << extraction(x, y);


*/

/*
* 
* Hoca garip yapm�� yav neyse 
* buradan ��renilen best practice her fonksiyon tek bir g�revi �stlensin ******
// CH4 REV�EW QU�Z2
int height{};
int t{ 1 };
std::cout << "Enter the height of the tower in meters: ";
std::cin >> height;

freeFall(height, t);
*/



	std::cout << "How old are you?\n";

	std::uint8_t age{};
	std::cin >> age;

	std::cout << "Allowed to drive a car in Texas [";

	if (age >= 16)
		std::cout << "x";
	else
		std::cout << " ";

	std::cout << "]\n";



































	return 0;
}



