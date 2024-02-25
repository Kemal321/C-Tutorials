#include <iostream>
#include <string_view>
/*
Soru #1
Ad� MonsterType olan bir numaraland�rma t�r� tan�mla, �u �rklar aras�nda se�im yaps�n: 
*- orc, goblin, troll, ogre, and skeleton.

*//*
// Soru #1 Cevap
enum MonsterType {
	orc,
	goblin,
	troll,
	ogre,
	skeleton,
};
*/
/*
Soru #2
MonsterType numaraland�rmas�n� bir ad alan�na yerle�tirin. Ard�ndan bir main() i�levi olu�turun ve bir trol ba�lat�n.
Program derlenmelidir.
*//*
//Soru #2 Cevap
namespace Monster {
	enum MonsterType {
		orc,
		goblin,
		troll,
		ogre,
		skeleton,
	};
}
*/
/*
Soru #3
Numaraland�r�c�lar verilen bir tamsay� de�eri olabilir ? - Do�ru, Temelde belirlenen bir tam say� de�eri yoksa int say�l�r.
Verilen a��k bir de�er de�ildir. - Do�ru sadece implicit olarak d�n��t�r�l�rler. Fakat enum class lar bu d�n���me u�ramazlar.
*/
/*
Soru #4
�u hayvanlar� i�eren Animal ad�nda bir numaraland�rma s�n�f� tan�mlay�n: domuz, tavuk, ke�i, kedi, k�pek, �rdek. 
Bir Animal parametresi alan ve bu hayvan�n ad�n� std::string_view (veya C++14 kullan�yorsan�z std::string) olarak 
d�nd�rmek i�in bir switch ifadesi kullanan getAnimalName() ad�nda bir i�lev yaz�n. Her hayvan�n y�r�d��� bacak say�s�n�
yazd�rmak i�in switch ifadesini kullanan printNumberOfLegs() ad�nda ba�ka bir i�lev yaz�n. Her iki i�levin de hata mesaj�
yazd�ran varsay�lan bir b�y�k/k���k harfe sahip oldu�undan emin olun. Bir kedi ve tavukla birlikte main() ��esinden
printNumberOfLegs() ��esini �a��r�n. ��kt�n�z ��yle g�r�nmeli:

'''A cat has 4 legs.
   A chicken has 2 legs.'''
*//*
enum class Animal {
	pig,
	chicken,
	goat,
	cat,
	dog,
	duck,
};
std::string_view getAnimalName(Animal animal) {
	switch (animal)
	{
	case Animal::pig:
		return "pig";
	case Animal::chicken:
		return "chicken";
	case Animal::goat:
		return "goat";
	case Animal::cat:
		return "cat";
	case Animal::dog:
		return "dog";
	case Animal::duck:
		return "duck";
	default:
		std::cout << "This is not an animal :) Sorry." << '\n';
		return "No-Animal";
	}
}
void printNumberOfLegs(Animal animal) {
	switch (animal)
	{
	case Animal::pig:
		std::cout << "A pig has 4 legs." << '\n';
		break;
	case Animal::chicken:
		std::cout << "A chicken has 4 legs." << '\n';
		break;
	case Animal::goat:
		std::cout << "A goat has 4 legs." << '\n';
		break;
	case Animal::cat:
		std::cout << "A cat has 4 legs." << '\n';
		break;
	case Animal::dog:
		std::cout << "A dog has 4 legs." << '\n';
		break;
	case Animal::duck:
		std::cout << "A duck has 4 legs." << '\n';
		break;
	default:
		std::cout << "Sorry this is not an animal." << '\n';
		break;
	}
}*/
/*
Soru #5
Bir web sitesi i�letiyorsunuz ve reklam gelirinizi hesaplamaya �al���yorsunuz. 3 par�a veri girmenizi sa�layan bir program yaz�n:

Ka� reklam izlendi?
Kullan�c�lar�n y�zde ka�� bir reklama t�klad�?
T�klanan reklam ba��na ortalama kazan�.
Bu 3 de�eri bir yap�da saklay�n. Bu yap�y�, de�erlerin her birini yazd�ran ba�ka bir i�leve iletin. Yazd�rma i�levi ayn� 
zamanda o g�n i�in ne kadar kazand���n�z� da yazd�rmal�d�r (3 alan� birlikte �arp�n).
*//*
struct Advertising {
	int howManyAdds{};
	int howManyClick{};
	double earningPerClick{};
};
void howMuchEarned(const Advertising& website) {
	std::cout << "Today " << website.howManyAdds << " adds watched." << '\n';
	std::cout << "Today " << website.howManyClick << " adds clicked." << '\n';
	std::cout << (website.earningPerClick * website.howManyAdds * website.howManyClick) << " $ Earned by adds"<<'\n';
}
// Hoca da vard� ben direktmen kullan�c� olarak d���nemedim. 
/*
Advertising getAdvertising()
{
	Advertising temp{};
	std::cout << "How many ads were shown today? ";
	std::cin >> temp.adsShown;
	std::cout << "What percentage of ads were clicked on by users? ";
	std::cin >> temp.clickThroughRatePercentage;
	std::cout << "What was the average earnings per click? ";
	std::cin >> temp.averageEarningsPerClick;

	return temp;
}
*/

/*
Soru #6
Bir kesri tutacak bir yap� olu�turun. Yap�n�n bir tamsay� pay ve bir tamsay� payda �yesi olmas� gerekir.

Kullan�c�dan bir Kesirde okunacak bir fonksiyon yaz�n ve bunu iki kesir nesnesini okumak i�in kullan�n.
�ki Kesri birbiriyle �arpmak ve sonucu Kesir olarak d�nd�rmek i�in ba�ka bir fonksiyon yaz�n (kesri azaltman�za gerek
yoktur). Kesir yazd�ran ba�ka bir fonksiyon yaz�n.
*//*
struct Fraction {
	int numerator{};
	int denominator{ 1 };
};

Fraction getFraction() {
	Fraction temp{};
	std::cout << "Enter a value for the numerator: ";
	std::cin >> temp.numerator;
	std::cout << "Enter a value for the denominator: ";
	std::cin >> temp.denominator;
	return temp;
}
void printFraction(const Fraction& fraction1, const Fraction& fraction2) {
	std::cout << "Your fractions multiplied together: ";
	std::cout << (fraction1.numerator * fraction2.numerator) << '/' << (fraction1.denominator * fraction2.denominator);

}

/*
Soru #7
�nceki test sorusunun ��z�m�nde getFraction() neden referans yerine de�ere g�re d�n�yor?

*- Cevap: Temp Fraction'�m�z yerel bir de�i�ken oldu�undan, fonksiyonun sonunda kapsam d���na ��kacakt�r.
Temp'i referans olarak d�nd�recek olsayd�k, arayan ki�iye sarkan bir referans� geri d�nd�r�rd�k.
*/

/*
Soru #8 
Bir oyun tasarlarken canavarlara sahip olmak istedi�imize karar veririz ��nk� herkes canavarlarla sava�may� sever. �yle bir yap� bildirin ki
senin canavar�n� temsil ediyor. Canavar a�a��dakilerden biri olabilecek bir t�re sahip olmal�d�r: bir dev, bir ejderha, bir ork,
dev bir �r�mcek veya bir bal��k. Bunun i�in bir enum s�n�f� kullan�n.

Her bir canavar�n ayr�ca bir ad� (std::string veya std::string_view kullan�n) ve bir miktar sa�l��� olmal�d�r.
bu �lmeden �nce ne kadar hasar alabileceklerini temsil ediyor. ��kt�y� yazd�ran printMonster() ad�nda bir i�lev yaz�n
yap�n�n t�m �yeleri. Bir dev ve bir bal��k �rne�i olu�turun, bunlar� bir ba�lat�c� listesi kullanarak ba�lat�n ve iletin
Monster()'� yazd�rmak i�in.

Your program should produce the following output:

enum class Monsters {
	ogre,
	dragon,
	orc,
	giantSpider,
	slime,
};
struct Monster{
	
	Monsters myMonster{};
	std::string_view monstersName{};
	int health{};
};
std::string_view printMonsterType(Monsters mons) {
	switch (mons)
	{
	case Monsters::ogre:
		return "Ogre";
	case Monsters::dragon:
		return "Dragon";
	case Monsters::orc:
		return "Orc";
	case Monsters::giantSpider:
		return "Giant Spider";
	case Monsters::slime:
		return "Slime";
	default:
		return "Unknown Monster";
	}
}
void printMonster(const Monster& monster) {
	std::cout << "This " << printMonsterType(monster.myMonster);
	std::cout<< " is named " << monster.monstersName << " and has " << monster.health << " health." << '\n';
}*/

/*
Soru #9 - Klasik sorulardan biriydi o y�zden cevaplamayaca��m.

Verilen t�rlerin her birindeki nesnelerin de�ere, sabit adrese veya sabit referansa g�re iletilmesi gerekip
gerekmedi�ini belirtin. Bu t�rleri alan i�levin bunlar� de�i�tirmedi�ini varsayabilirsiniz.
*/

/*
Soru #10

Ayn� �ablon t�r�nden 3 �yeye sahip Triad adl� bir s�n�f �ablonu olu�turun. Ayr�ca Triad'� yazd�rabilen print
adl� bir i�lev �ablonu da olu�turun. A�a��daki program derlenmelidir:

int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}


*/
// Triad(T,T,T) -> Triad<T,T,T>  -> This is only if you are using C++17, This property is added to C++ in C++20
template <typename T>
struct Triad{
	T t1{};
	T t2{};
	T t3{};
};

template <typename T>
void print(const Triad<T>& triad) {
	std::cout << '[' << triad.t1 << ',' << triad.t2 << ',' << triad.t3 << ']';
}
int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);
	/*
	Monster::MonsterType monster{ Monster::troll };
	std::cout << "Bu bir : " << monster << " dur." << '\n';
	*/

	/*
	// Soru 4
	Animal cat{ Animal::cat };
	Animal chicken{ Animal::chicken };
	printNumberOfLegs(cat);
	printNumberOfLegs(chicken);
	*/

	/*
	//Soru 5
	Advertising reklam{ 3,2,1 };
	howMuchEarned(reklam);
	*/
	
	/*
	//Soru 6
	Fraction usersFraction{ getFraction() };
	Fraction usersSecondFraction{ getFraction() };
	printFraction(usersFraction, usersSecondFraction);
	*/

	/*
	//Soru 8
	Monster myMonster�m{ {Monsters::ogre},"Torg",145 };
	Monster myMonster�m2{ {Monsters::slime},"Blurp",23 };

	printMonster(myMonster�m);
	printMonster(myMonster�m2);
	*/



	return 0;
}
