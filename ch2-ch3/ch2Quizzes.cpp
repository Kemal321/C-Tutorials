// #include <iostream> Gerek yok zaten di�erinde ekli orada kullan�yoruz main fonksiyonu olarak zaten bir girdi ��kt� i�lemi ile u�ra�m�yoruz. 
#include "io.h"
/*Commented for quiz question 3
int readNumber();
void writeAnswer(int num1, int num2);
*/
int main()
{
    int num1{ readNumber() };
    int num2{ readNumber() };
    writeAnswer(num1, num2);
    return 0;

}
/*
int readNumber() {
    std::cout << "Enter an integer: ";
    int number{};
    std::cin >> number;

    return number;
}

void writeAnswer(int num1, int num2) {
    std::cout << "The answer is " << (num1 + num2 );
}*/

/*AUTHOR'S SOLUT�ON 
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The answer is " << x << '\n';
}

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x + y); // using operator+ to pass the sum of x and y to writeAnswer()
    return 0;
}*/