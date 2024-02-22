/*Quesiton 1

Determine what values the following program prints
by yourself (do not compile the program). -> A�a��daki program ne yazd�r�r kendi ba��n�za yap�n derlemeden g�r�n

#include <iostream>

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n';

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << ref << '\n';

    x = 4;

    std::cout << x << ref << '\n';

    return 0;
}
Cevab�m:
11
22
44

Soru #1

1a) Can we determine whether a pointer is a null pointer or not? If so, how?
1a) Bir pointerin null olup olmad���na karar verebilir miyiz e�er verebiliyorsak nas�l karar veririz ?
Cevap: Evet bir pointerin null pointer olup olmad���na karar verebiliriz. Her nesne gibi pointerlerde boolean de�erlere d�n��ebilir 
bir null pointer boolean de�erine d�n��t���nde false olarak d�n���r null olmayanlar ise true olarak d�n���r. Bir ko�ul ifadesi ile bunu 
kontrol edebiliriz.

1b) Can we determine whether a non-null pointer is valid or dangling? If so, how?
1b) Bir non-null pointerin ge�erli bir de�ere i�aret etti�ini veya etmedi�ine karar verebilir miyiz E�er �yleyse nas�l ?
Cevap: Bir non-null pointerin sark�k olup olmad���na karar veremeyiz. 
---------------------------------------------------------------------------------------------------------------------------------------------------
Soru #2
Her alt ��e i�in, a��klanan eylemin tahmin edilebilir, tan�ms�z veya muhtemelen tan�ms�z bir davran��la sonu�lan�p sonu�lanmayaca��n� yan�tlay�n.
Yan�t �muhtemelen tan�ms�z� ise ne zaman oldu�unu a��klay�n.

2a) Assigning a new address to a non-const pointer - Non-const pointer e yeni adres atama
*- tahmin edilebilir
2b) Assigning nullptr to a pointer  - Bir pointer e null pointer atama
*- Tahmin edilebilir
2c) Dereferencing a pointer to a valid object - Ge�erli bir nesneye i�aret eden bir pointer i dereferans etmek
*- Tahmin edilebilir 
2d) Dereferencing a dangling pointer - Sark�k pointeri dereferense etmek
*- Tan�ms�z Davra��na neden olur
2e) Dereferencing a null pointer - Null pointer i dereferense etmek
*- Tan�ms�z davran��a neden olur
2f) Dereferencing a non-null pointer
*- Muhtemelen tan�ms�z bir davran��, ��nk� e�er pointerin i�aret etti�i nesne pointerden �nce yok edilirse. Bu durumda pointer dangling olur. 
Ve dereferans i�lemleri tan�ms�z davran��a neden olur.

Soru #3

Why should we set pointers that aren�t pointing to a valid object to �nullptr�?
Ge�erli bir nesneye i�aret etmeyen i�aret�ileri neden 'nullptr' olarak ayarlamal�y�z?

Cevap: B�ylece sark�k pointerlardan kurtulmu� oluruz. Bir non-null pointerin sark�k m� de�il mi diye kontrol etmek zor bir durumdur. Ama bir 
nullptr null de�ere i�aret etti�inden dolay� tan�ms�z davran��a neden olmadan �nce kontrol�n� sa�layabiliriz. 


Soru #4

<< operat�r�n�n sa� taraf�ndaki a�a��daki ifadelerin her biri i�in, ifadenin bir lvalue veya rvalue oldu�unu belirtin:

std::cout << 5;  - rvalue

int x { 5 };
std::cout << x;  - lvalue

int x { 5 };
std::cout << x + 1; - rvalue

int foo() { return 5; }
std::cout << foo(); - rvalue

int& max(int &x, int &y) { return x > y ? x : y; }
int x { 5 };
int y { 6 };
std::cout << max(x, y);  - Burada d�n�� de�eri lvalue referans� oldu�u i�in cevap lvalue olur. 

Soru #5

What is the output of this program? - Bu program�n ��kt�s� nedir ?

#include <iostream>

int main()
{
    int x{ 4 };
    int y{ 6 };

    int& ref{ x };
    ++ref;
    ref = y;
    ++ref;

    std::cout << x << ' ' << y;

    return 0;
}
Cevap: 7 6 ��nk� ref = y de olu�an durum referans� al�nan nesnenin de�erinin de�i�tirilmesidir. Referans olunan nesnenin de�i�tirilmesi de�ildir.

Soru #6

Name two reasons why we prefer to pass arguments by const reference instead of by non-const reference whenever possible.
Arg�manlar� const referans ile ge�menin m�mk�n oldu�u yerde const ref ile ge�mek i�in 2 neden s�yleyin. 

Cevap: Ba��ms�z de�i�kenin de�erini de�i�tirmek i�in const olmayan bir referans parametresi kullan�labilir. Bu yetene�e ihtiyac�m�z yoksa,
arg�man� kazara de�i�tirmemek i�in const referans�n� ge�mek daha iyidir.
Const olmayan bir referans parametresi yaln�zca de�i�tirilebilir bir lvalue'yi arg�man olarak kabul edebilir. Bir const referans parametresi,
de�i�tirilebilir bir lvalue'yu, de�i�tirilemeyen bir lvalue'yu veya bir rvalue'yi ba��ms�z de�i�ken olarak kabul edebilir.


Soru #4
Const i�aret�isi ile const i�aret�isi aras�ndaki fark nedir?

Cevap: Const i�aret�isi, adresi de�i�tirilemeyen bir i�aret�idir (ba�ka bir nesneye yeniden i�aret edilemez). Ancak i�aret edilen nesnenin de�eri
de�i�tirilebilir.
Const i�aret�isi, de�eri i�aret�i arac�l���yla de�i�tirilemeyen bir nesneyi i�aret eden bir i�aret�idir. Ancak i�aret�i ba�ka bir nesneye yeniden
y�nlendirilebilir.


Soru #5

Arayan�n 2 int de�i�keni arg�man olarak iletmesine olanak tan�yan sort2 ad�nda bir i�lev yaz�n. ��lev geri d�nd���nde, ilk arg�man iki de�erden
k���k olan�, ikinci arg�man ise iki de�erden b�y�k olan� tutmal�d�r.

A�a��daki kod, yorumlarda belirtilen de�erleri �al��t�rmal� ve yazd�rmal�d�r:

#include <iostream>

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}
Cevap hemen a�a��dad�r:
*/
void sort2(int& num1, int& num2) {
    int temp{};
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
#include <iostream>

int main()
{
    int x{ 7 };
    int y{ 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7
    return 0;
}
