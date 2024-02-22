#include <iostream>
/*
1a) What is the output of this program and why? -> Bu program�n ��kt�s� nedir ve neden bu ��kt�y� vermekte

#include <iostream>

void print(int x)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    short s { 5 };
    print(s);

    return 0;
}
Cevap: ��kt� int 5 olacakt�r ��nk� short un int t�r�ne d�n���m� bir n�merik y�kseltmedir oysa double t�r�ne d�n���m� bir n�meric
d�n���md�r n�merik y�kseltme n�meric d�n���mden �nce gelir yani daha y�ksek �nceli�e sahiptir.

1b) Why won�t the following compile? -> A�a��daki kod neden derlenmez

#include <iostream>

void print()
{
    std::cout << "void\n";
}

void print(int x=0)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5.0f);
    print();

    return 0;
}
Cevap: print() �a�r�s� hem print() ile hem de print(int) ile e�le�ir ��nk� varsay�lan de�er olarak x = 0 ibaresinin �a�r�m� da 
print() dir bu y�zden belirsiz e�le�me olur ve derlenemez.

1c) Why won�t the following compile? -> A�a��daki kod neden derlenmez

#include <iostream>

void print(long x)
{
    std::cout << "long " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5);

    return 0;
}

Cevap: int 5 de�eri hem long a hem de double t�r�ne d�n��ebilir fakat bu d�n���m n�merik d�n���m olaca��ndan dolay� ikiside e�it 
derecede makuld�r bu da bir belirsiz e�le�me meydana getirir.Derleyici hangi e�le�menin daha iyi oldu�una karar veremez.
*/
template <typename T>
auto add(T x, T y) {
    return (x + y);
}

template <typename T>
T mult(T x, int y) {
    return (x * y);
}

template <typename T, typename U>
auto sub(T x, U y) {
    return (x - y);
}
int main()
{
    // Question 2
    /*
    Kullan�c�lar�n ayn� t�rden 2 de�er eklemesine olanak tan�yan add() ad�nda bir i�lev �ablonu yaz�n. A�a��daki program 
    �al��mal�d�r:*/
    std::cout << add(2, 3) << '\n';
    std::cout << add(1.2, 3.4) << '\n';
    
    
    /*Kullan�c�n�n herhangi t�rden bir de�eri (ilk parametre) ve bir tamsay�y� (ikinci parametre) �arpmas�na olanak tan�yan 
    mult() ad�nda bir i�lev �ablonu yaz�n. ��lev, ilk parametreyle ayn� t�r� d�nd�rmelidir. A�a��daki program �al��mal�d�r:*/
    std::cout << mult(2, 3) << '\n';
    std::cout << mult(1.2, 3) << '\n';


    /*Kullan�c�n�n farkl� t�rden iki de�eri ��karmas�na olanak tan�yan sub() ad�nda bir i�lev �ablonu yaz�n. A�a��daki program 
    �al��mal�d�r:*/
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';

    /*
    What is the output of this program and why? - Bu program�n ��kt�s� nedir ve neden?

    #include <iostream>

    template <typename T>
    int count(T) // This is the same as int count(T x), except we're not giving the parameter a name since we don't use the
                    parameter
    {
        static int c { 0 };
        return ++c;
    }

    int main()
    {
        std::cout << count(1) << '\n';
        std::cout << count(1) << '\n';
        std::cout << count(2.3) << '\n';
        std::cout << count<double>(1) << '\n';

        return 0;
    }
    Cevab�m: 
    0
    1
    2
    3
    ��nk� static int c{0} static local de�i�keni static keyword�nden dolay� global kapsam a sahip olmu�tur static local
    de�i�kenlerin �zelli�i bir kere ba�lat�ld�ktan sonra global de�i�ken gibi davranmas�d�r. Bu durumda 0 ile ba�lat�ld�ktan sonra
    fonksiyon 4 kez �a�r�lm��t�r bu her defas�nda g�ncel de�erin yazd�r�lmas� ile sonu�lanacak bir i�lem y���n�n� olu�turur ve 
    bu ��kt�y� verir. Ve cevab�m yanl�� ��kt� nedeni count(1) �a�r�ld���nda, derleyici count<int>(int) i�levini ba�latacak ve 
    onu �a��racakt�r. Bu, 1 de�erini d�nd�recektir.

    count(1) tekrar �a�r�ld���nda, derleyici count<int>(int)'in zaten mevcut oldu�unu g�recek ve onu tekrar arayacakt�r. 
    Bu, 2 de�erini d�nd�recektir.

    count(2.3) �a�r�ld���nda, derleyici i�levi count<double>(double) prototipiyle ba�latacak ve �a��racakt�r. 
    Bu, kendi statik c de�i�kenine sahip yeni bir fonksiyondur, dolay�s�yla 1 de�erini d�nd�recektir.

    count<double>(1) �a�r�ld���nda, derleyici bizim a��k�a count()'un double versiyonunu istedi�imizi g�recektir. 
    Bu i�lev �nceki ifade nedeniyle zaten mevcuttur, dolay�s�yla count<double>(double) �a�r�lacak
    ve int arg�man� �rt�l� olarak double'a d�n��t�r�lecektir. Bu fonksiyon 2 de�erini d�nd�recektir.*/

    /*Question 4
    What is the output of this program? - Bu program�n ��kt�s� nedir

    #include <iostream>

    int foo(int n)
    {
        return n + 10;
    }

    template <typename T>
    int foo(T n)
    {
        return n;
    }

    int main()
    {
        std::cout << foo(1) << '\n'; // #1

        short s { 2 };
        std::cout << foo(s) << '\n'; // #2

        std::cout << foo<int>(4) << '\n'; // #3

        std::cout << foo<int>(s) << '\n'; // #4

        std::cout << foo<>(6) << '\n'; // #5

        return 0;
    },
    cevab�m
    11
    12
    4
    2
    6
    12 ��kt�s� yanl��m�� nedeni 
    2. durumda, foo(s), �ablon olmayan foo(int) i�leviyle tam olarak e�le�mez, ancak s arg�man� bir int'ye d�n��t�r�lebilir,
    b�ylece foo(int) bir aday olur. Ancak derleyici foo<T>(T) i�lev �ablonunu foo<short>(short) ile tam e�le�meyi kal�plamak
    i�in kullanmay� tercih edecektir. Yani buna foo<short>(short) denir.*/
    return 0;


}
