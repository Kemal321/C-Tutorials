#include <iostream>
#include <string_view>
#include <cmath>
/*
Soru #1
#include <iostream>
#include <string_view>

enum AnimalType
{
    cat,
    dog,
    chicken,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    default:  return 0;
    }
}


int main()
{
    constexpr AnimalType animal{ cat };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

    return 0;
}
Yukar�daki hayvan prosed�r� �rne�ini g�ncelleyin ve kedi yerine y�lan� �rnekleyin.
*//*
//Cevap #1
enum AnimalType
{
    cat,
    dog,
    chicken,
    snake,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    case snake: return "snake";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    case snake: return 0;
    default:  return 0;
    }
}
*/
/*
#include <iostream>
#include <string_view>

struct Cat
{
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog
{
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken
{
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};

int main()
{
    constexpr Cat animal;
    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

    return 0;
}
Soru #2
Yukar�daki hayvan OOP benzeri �rne�i g�ncelleyin ve kedi yerine y�lan� �rnekleyin.
*/
/*
//Cevap #2
struct Cat
{
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog
{
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken
{
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};
struct Snake
{
    std::string_view name{ "snake" };
    int numLegs{ 0 };
};*/
/*
Soru #3

�ki tamsay�y� tutan IntPair ad�nda bir yap� olu�turun. �ki tam say�n�n de�erini yazd�ran print adl� bir �ye i�levi ekleyin.

A�a��daki program i�levi derlenmelidir:

#include <iostream>

// Provide the definition for IntPair and the print() member function here

int main()
{
    IntPair p1 {1, 2};
    IntPair p2 {3, 4};

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    return 0;
}
*/
/*
Cevap #3
struct IntPair {
    int firstNum{};
    int secondNum{};

    void print() {
        std::cout << "Pair(" << firstNum << ',' << secondNum <<')' << '\n';
    }
    bool isEqual(IntPair pair) {
        return (firstNum == pair.firstNum && secondNum == pair.secondNum) ? true : false;
    }
};
*/
/*
Soru #4 
Ball ad�nda bir s�n�f yaz�n. Topun biri rengi, di�eri yar��ap� tutacak iki �zel �ye de�i�keni olmal�d�r. Ayr�ca topun 
rengini ve yar��ap�n� yazd�ran bir fonksiyon yaz�n�z.

A�a��daki �rnek program derlenmelidir:
                int main()
                {
                    Ball blue{ "blue", 10.0 };
                    print(blue);

                    Ball red{ "red", 12.0 };
                    print(red);

                    return 0;
                }
Ve �u ��kt�y� �retmeli
                Ball(blue, 10)
                Ball(red, 12)
*//*
class Ball {
private:
    std::string m_color{};
    int m_radius{};
public:
    Ball(std::string_view color, auto radius)
        : m_color{ color }, m_radius{ static_cast<int>(radius) }
    {

    }
    std::string_view getColor() const { return m_color;  }
    int getRadius() const { return m_radius; }

};
void print(const Ball& ball) {
    std::cout << "Ball(" << ball.getColor() << ',' << ball.getRadius() << ")\n";
}*/

/*
Soru #5
Ball ad�nda bir s�n�f yaz�n. Topun iki �zel �ye de�i�keni olmal�d�r; biri rengi tutacak (varsay�lan de�er: siyah) ve di�eri 
yar��ap� tutacak (varsay�lan de�er: 10,0). A�a��daki her durumu ele alacak bir tane olmak �zere 4 kurucu ekleyin:
                int main()
                {
                    Ball def{};
                    Ball blue{ "blue" };
                    Ball twenty{ 20.0 };
                    Ball blueTwenty{ "blue", 20.0 };

                    return 0;
                }
Ve �u ��kt�y� vermeli
                Ball(black, 10)
                Ball(blue, 10)
                Ball(black, 20)
                Ball(blue, 20)
*/
/*
Cevap #5
class Ball {
private: 
    std::string m_color{"black"};
    double m_radius{10.0};
public:
    Ball()
    {
        print();
    }   
    Ball(std::string_view color, double radius)
        :m_color{ color }, m_radius{ radius } 
    {
        print();
    }
    Ball(double radius)
        :m_radius{ radius } // Delegeting with Ball{"black",radius};
    {
        print();
    }
    Ball(std::string_view color)
        :m_color{color}
    {
        print();
    }
    void print()
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
    }
};*/
/*
Soru #6
Varsay�lan arg�manlar� kullanarak ve kuruculara yetki vererek yukar�daki programdaki kurucular�n say�s�n� azalt�n.
*/

/*
* Cevap 6
class Ball
{
private:
    std::string m_color{ "black" };
    double m_radius{ 10.0 };

public:
    // Handles Ball(radius)
    Ball(double radius)
        : Ball{ "black", radius }
    {
    }

    // Handles Ball(color, radius), Ball(color), and Ball()
    Ball(std::string_view color = "black", double radius = 10.0)
        : m_color{ color }
        , m_radius{ radius }
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
    }
};*/
/*
Soru #7 & 8
a) Point2d ad�nda bir s�n�f yaz�n. Point2d, double t�r�nde iki �ye de�i�ken i�ermelidir: m_x ve m_y; her ikisi de
varsay�lan olarak 0,0'd�r.

Bir yap�c� ve print() i�levi sa�lay�n.

A�a��daki program �al��mal�d�r:

                #include <iostream>

                int main()
                {
                    Point2d first{};
                    Point2d second{ 3.0, 4.0 };

                    // Point2d third{ 4.0 }; // should error if uncommented

                    first.print();
                    second.print();

                    return 0;
                }
Ve �u ��kt�y� �retmesi gerekiyor. 
                Point2d(0, 0)
                Point2d(3, 4)

b) �imdi ba�ka bir Point2d'yi parametre olarak alan ve aralar�ndaki mesafeyi hesaplayan distanceTo() ad�nda bir �ye
i�lev ekleyin. Verilen iki nokta (x1, y1) ve (x2, y2), aralar�ndaki mesafe
std::sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)).form�l� kullan�larak hesaplanabilir. Std::sqrt i�levi ba�l�k
cmath'inde bulunur.

A�a��daki program �al��mal�d�r:
                Point2d first{};
                Point2d second{ 3.0, 4.0 };

                first.print();
                second.print();

                std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

                return 0;
Ve �u ��kt�y� versin.
                Point2d(0, 0)
                Point2d(3, 4)
                Distance between two points: 5
*//*
Cevap #7 & 8
class Point2d {
private:
    double m_x{0.0};
    double m_y{0.0};
public:
    Point2d() = default;
    Point2d(double first, double second)
        :m_x{ first }, m_y{ second }
    {

    }
    void print() const {
        std::cout << "Point2d(" << m_x << ',' << m_y << ")\n";
    }
    int distanceTo(const Point2d& point) {
        return (std::sqrt((m_x - point.m_x) * (m_x - point.m_x) + (m_y - point.m_y) * (m_y - point.m_y)));
    }
};*/

/*
Soru #9

Ders 13.8 - Yap�lar� ge�me ve d�nd�rmede, Kesir yap�s�n� kullanarak k�sa bir program yazd�k. Referans ��z�m� �una benzer:
#include <iostream>

struct Fraction
{
    int numerator{ 0 };
    int denominator{ 1 };
};

Fraction getFraction()
{
    Fraction temp{};
    std::cout << "Enter a value for numerator: ";
    std::cin >> temp.numerator;
    std::cout << "Enter a value for denominator: ";
    std::cin >> temp.denominator;
    std::cout << '\n';

    return temp;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
    return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
}

void printFraction(const Fraction& f)
{
    std::cout << f.numerator << '/' << f.denominator << '\n';
}

int main()
{
    Fraction f1{ getFraction() };
    Fraction f2{ getFraction() };

    std::cout << "Your fractions multiplied together: ";

    printFraction(multiply(f1, f2));

    return 0;
}

Standart en iyi uygulamalar� takip ederek Fraction'� bir yap�dan s�n�fa d�n��t�r�n. T�m i�levleri �ye i�levlere d�n��t�r�n
*/

/*
Cevap #9
class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    explicit Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    void getFraction()
    {
        std::cout << "Enter a value for numerator: ";
        std::cin >> m_numerator; // this is a member function, so we can access members directly
        std::cout << "Enter a value for denominator: ";
        std::cin >> m_denominator;
        std::cout << '\n';
    }

    Fraction multiply(const Fraction& f) const
    {
        return Fraction{ m_numerator * f.m_numerator, m_denominator * f.m_denominator };
    }

    void printFraction() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
};
*/

int main()
{
    /*Soru 1 Cevap-Test
    constexpr AnimalType animal{ snake };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";
    */
    /*Soru 2 Cevap-Test
    constexpr Snake animal;
    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";
    */
   /*
  //  Soru 3 Cevap-Test
    IntPair p1{ 1, 2 };
    IntPair p2{ 3, 4 };

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
    std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");
    */
    /*
    A const before the function name applies to the return type.
A const after the function name applies to the member function itself.*/
   /*
    Cevap #4
    Ball blue{"blue", 10.0};
    print(blue);

    Ball red{ "red", 12.0 };
    print(red);*/
    /*
    Cevap #5
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };
    */

    /*
    Cevap #7
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();
    */

    /*
    Cevap #8
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
    */

    /*
    Cevap #9

    Fraction f1{};
    f1.getFraction();

    Fraction f2{};
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";

    f1.multiply(f2).printFraction(); 
    */

    return 0;
}