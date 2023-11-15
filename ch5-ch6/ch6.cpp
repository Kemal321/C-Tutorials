// ch6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
void isEven(int x){
    if (x % 2 == 0) {
        std::cout << x << " is even";
    }
    else {
        std::cout << x << " is odd";
    }


}
int getNumber() {
    int x{};
    std::cout << "Enter an integer: ";
    
    std::cin >> x;

    return x;
}
int main()
{
    // Birle�ik i�lemler matematikte i�lemlere operat�r i�leme girenlere operand denir. 
    // 2 + 3   -> 2 ve 3 literalleri operand iken + i�aretide operat�rd�r.
    // 4 + 2 * 3 = 18 mi 10 mu peki C++ i�lem s�ras�n� nas�l bilebilir 
    
    
    /*
    
    Burada C++ �n yapt��� 2 �ey var;
    1- ) Derleme zaman�nda, derleyici ifadeyi ��z�mlemeli ve operat�rlerle nas�l grupland�r�ld���n��belirlemelidir.
    2- ) Sonras�nda derleme veya �al��ma zaman�nda i�lemciler de�erlendirilir ve i�lemler ger�ekle�tirilerek sonu� �retilir
    
    */
    // Operator Precedence - ��lem �nceli�i 
    /*
    7-4-1 nas�l grupland�r�l�r mesela. 
    Bir ifadede ayn� �ncelik seviyesine sahip iki operat�r yan yana geldi�inde, operat�r�n ili�kilendirilme kurallar� derleyiciye 
    operat�rleri soldan sa�a m� yoksa sa�dan sola m� de�erlendirmesi gerekti�ini s�yler. ��karma i�lemi �ncelik seviyesi 6'ya sahiptir
    ve �ncelik seviyesi 6'daki operat�rlerin ili�kilendirilme kurallar� soldan sa�a do�rudur. Bu nedenle, bu ifade soldan sa�a 
    gruplan�r:�(7�-�4)�-�1.*/

    // C++ de bir �ok operat�r level i var bunlar 1 den ba�layarak 17 ye kadar gidiyor ve () parantezler en y�kselerden biri 
    // o y�zden bile�ik i�lemler yapaca��m�z zaman parantez kullanarak bunu daha kolay okunabilir hale getirmek en iyi yoldur.

    /*
    (a * b) + (c * d) -> Fonksiyonlarda ve operantlar�n de�erlendirme s�ralar� belirtilmemi�tir. 
    Yani c++ yukar�da a *b veya c * d yi ilk olarak de�erlendirebilir bu biraz kar���kt�r. Bununla alakal� 6.1 konunun altlar�nda bir
    �rnek var. 
    Dikkatli olmak laz�m. 

    K�saca **** ��lemciler fonksiyon arg�manlar� ve alt ifadelerin de�erlendirme s�ras� her hangi bir s�ralamada olabilir. 
    Bundan ka��nman�n yollar� �u uyar�d�r. **** Yazd���m�z ifadelerin veya fonksiyon �a�r�lar�n�n operand veya arg�man de�erlendirme
    s�ras�na ba�l� olmad���ndan emin olmal�y�z.
    */

    /*
    UNARY OOPERATORS 
    Unary yani birli operat�rler isminden de belli oldu�u gibi tek bir operand al�rlar. Unary operat�rler + ve - dir 
    +x -x 
    - unary operat�r� operand�n� -1 ile �arparak return eder. 
    + operand�n de�erini d�nd�r�r. Gereksizdir sadece - operat�r�ne simetri sa�lamas� i�in eklenmi� bir operat�rd�r :d

    BINARY OPERATORS
    Klasik 2 i�lemcili operat�rlerdir bunlar + - / * % operat�rleridir. Burada + - * i�lemcileri ayn� normal hayattaki gibi �al���r 
    fakat b�lme ve mod i�lemine biraz de�inmek gerekir.
    
    / -> operat�r�nde 1 veya 2 taraf�n kayan noktal� say� olmas� b�l�m� de o �ekilde yapar ki ��kt�s�da kayan noktal� say� olur 
    e�er 2 i�lemci de integer de�er olursa b�l�m�n sonucu integer olur ve noktadan sonraki k�s�m D���L�R.

    Burada 2 tamsay� varsa x ve y olsun bunlar� yine de floating point olarak b�lmek istiyoruz dersen reis 
    static_cast<double>(x) / y veya her ikisini veya sadece y yi de�i�tirerek �stteki kurala g�re float b�lmesi yapabilirim.
    
    Burada 0 veya 0.0 a b�lmek tan�mlanmayan davran��a neden olabilir baz� derleyicilerde sistem mimarisinin tan�mlamas�na g�re
    NaN veya Inf d�n�t� alabiliriz. 

    Kalan alma i�lemi (%) ayn� bildi�imiz �ey sadece eksili say�larda her zaman ilk i�lemcinin i�aretini al�yor. 
    += -= *= /= %= leri de kullanabiliyoruz bu sa�daki de�i�keni soldaki ile i�leme sokarak sola tekrardan atar.

    kalan alma i�lemi ile i�lemler yaparken negatif say�lar sorun ��kartabilir burada 0 ile kar��la�t�rmak 
    daha mant�kl�d�r yap�labilece�i her yerde 0 ile kar��la�t�r.
    
    */

    // Quiz 6.3 exponentiation and remainder

    
    //isEven(getNumber());

    // Artt�r�m / Azalt�m Operat�rleri ve yan etkileri
    /*
    
    ++x -> X i artt�r ve x i geri d�nd�r
    --x -> X i azalt ve x i geri d�nd�r
    x++ -> x i kopyala, x i artt�r, x i d�nd�r ve kopyala
    x-- -> x i kopyala, x i azalt, x i d�nd�r ve kopyala
    

    Burada zaten ++x --x in �al��ma mant���n� biliyoruz klasik al�p de�erlendir ve artt�r sonras�nda kullan. 
    Ama postfix i�lemlerde ise x++ ve x-- ilk olarak x in bir kopyas� olu�turulur ve as�l de�er artt�r�l�r veya azalt�l�r
    Sonras�nda e�er de�er artt�r�l�r bunun etkisi nedir derseniz 
    int x { 5 } ;
    int y { ++x }; -> Burada y 6 olur yani prefix i�lemlerde �nce artt�r�m sonras�nda de�erlendirme olur. 
    int z { x++ }; -> Burada ise x in kopyas� olu�turulur ve orjinal artt�r�l�r bu s�rada z de�i�kenine x in kopyas� ile i�lem
    yap�l�r yani z 5 olarak atan�r. Sonras�nda x in de�eri bir artt�r�l�r. 
    Postfix de i�lemlerin fazlal��� belli yani performans konusunda prefix i�lemden daha k�t� oldu�unu bil.

    */
    /* Burada prefix i�lemler daha performansl� ve s�priz olu�turmaya daha uzak oldu�u i�in tercih edilebildi�i her yerde tercih
    edilmeli
    */


    /*
    Yan etkiler
    
    Bir fonksiyon veya ifade bir d�n�� de�eri �retmek d���nda g�zlemlenebilir bir etkiye sahipse, bu i�levin yan etkisi oldu�u s�ylenir.
    * Bana biraz sa�ma geldi aga bunlara neden yan etki diyoz amk kutuyu itersen kutu ileri gider zaten bunun i�in itersin 
    * Buna yan etki demek �ok garip geliyor. He ama� x = 5 yazmak sa bilemem ama x = 5 i zaten x e 5 atamak i�in yaz�yoz yani bu yan
    * etki olmaz bence amk b�yle mantalitenin.
    * ** Hocam burada yaz�lan kodda olu�an yan etki bazen emirlerin s�ras�nda bir hataya neden olabilri 
    * �rnek bir toplama fonksiyonna 2 de�er yolaya�m mesela 
    * int x { 5 };
    * add(x, ++x);
    * Burada add fonksiyonu 5 + 6 m� yapacak 6 + 6 m� undefined behaviour olur yani.
    
    ***  C++ fonksiyon arg�manlar� ve i�le�lerin i�lenenleri i�in bir de�erlendirme s�ras� tan�mlamaz.
    ***  �o�u durumda, C++ ayn� ifadede birden fazla kullan�lan bir yan etkisi olan bir nesnenin yan 
    ***  etkilerinin ne zaman uygulanmas� gerekti�ini de belirtmez. Bu, ayn� ifadede bir nesne daha fazla
    ***  kullan�ld���nda belirsiz davran��a�yol�a�abilir.    
    */
    /*
    Virg�l Operat�r�
    Virg�l operat�r� (,) bir ifade yerine birden fazla ifadeyi de�erlendirmenize olanak tan�r. Virg�l operat�r� sol operand�
    de�erlendirir, ard�ndan sa� operand� de�erlendirir ve son olarak sa� operand�n sonucunu d�nd�r�r.

    Genellikle, virg�l operat�r�n� kullanarak yaz�lan bir ifade, ayr� ifadeler olarak yaz�lm�� bir �ekilde daha iyi anla��l�r olur.
    Yani, bir�ok ifadeyi virg�l operat�r� ile bir arada yazmak yerine her bir ifadeyi ayr� ayr� yazmak, 
    kodun daha okunakl� ve anla��l�r olmas�n� sa�lar. �rne�in, verilen kod, a�a��daki gibi daha anla��l�r bir �ekilde�yaz�labilir:
    
    Tabi i�lem �nceli�inde en son seviye olmas�ndan dolay� da dikkatli olmak gerekir �rne�in
    �rnek
    z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated�and�discarded.


    �o�u yaz�l�mc� virg�l operat�r�n� kullanmaktan �ekinir. En iyi yakla��m da loop lar d���nda 
    virg�l operat�r�n� kullanmaktan �ekinmektir

    */

    /*
    int x{ 5 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n';
    */

    /*
    Ternary Operator - Arithmetic if -> ?: - Kullan�m� : (contidion) ? expression1 : expression2; 
    Bu kullan�ma g�re zaten aritmetik if olarak da bilinir. Condition do�ruysa expression1 �al��t�r�l�r. Aksi takdirde expression 2 �al��t�r�l�r. 
    �nemli bir nokta expression2 opsiyonel de�ildir. Yani kesinlikle de�er d�nd�rmelidir.

    Do�ruysa expression 1 �al���r yanl��sa expression 2 �al���r. 

    �rne�in -> int x = ( condition ) ? expression 1 : expression 2;
    �rne�in -> larger = (x > y) ? x : y;

    Tabi burada en �nemli �eylerden biri ko�ul operat�r�n�n i�lem seviyesi �ok d���kt�r o y�zden her zaman parantez ile kullan�lmas� en iyi harekettir
    
    Tabi burada kulland���m�z ifadelerin t�rleri birbirine e�it olmas� gerek ya da ortak bir t�re d�n��t�r�lebilir t�rler olmal� 
    �rnek -> std::cout<< (x != 5 ) ? x : "x is 5"); -> Bu derlenmez ��nk� bir tarafta x yani int de�i�keni var ikeN 
    di�er tarafta C-style string literali
    var t�rleri uyumsuz oldu�u i�in bu ifade derlenemeyecektir. Bu gibi durumlarda mecburen if else kal�b� kullan�lmal�d�r.

    */
    
    // ** Fonksiyonlar�n i�inde tan�mlanan de�i�kenler fonksiyonun sonunda yok oldu�u gibi if else i�inde tan�mlanan de�i�kenler de if yada else 
    // ** ifadesinin sonunda sona erer. Ko�ul ifadeleri bunun gibi durumlarda kullan�labilir. If else nin kullan�lamayaca�� yerler yani.
    
    /*
    Peki ko�ul operat�r�n� ne zaman kullanmal�y�z ? 
     
    ** Ko�ul operat�r�n� basit ko�ul oldu�u durumlarda.Sonucun kullan�labilece�i okunabilirli�i artt�rabilecek noktalarda kullanmak gerekir 
    * Aksi halde hata yapmaya yatk�n okunaks�z kodlar olu�turmu� oluruz.
    
    */

    // RELATIONAL OOERATORS AND FLOATING POINT COMPARISIONS
    
    /*Benim �evirim ili�kisel operat�rler ve kayan noktal� kar��la�t�rma
    > , < , >= , <= == != klasik matematiksel kar��la�t�rmad�r 
    �ok�a g�rd���m�z i�in �rne�ini yazmicam
    */

/*
Boolean ko�ul de�erleri

burada yeni ��renenler 
if (b1 == true ) -> gibi �eyler yap�yor ve bu gereksiz bir durum bunun yerine if(b1) yazabiliriz. ��nk� burada ekstra bir de�er sunmad���m�z
i�in bunu yazmak gereksiz oluyor o y�zden okumay� g��le�tiriyor. == != kar��la�t�rmalar�n� tekli ifadelerde kullanmamak ve onun yerine 
!b1 veya b1 -> false ve true i�in bunlar� kullanmak daha mant�kl�. 
*/
    
    /*
    Hesaplanan kayan noktal� say�lar�n kar��la�t�r�lmas� sorunlu olabilir. Bunun nedeni de yuvarlama hatalar�d�r 
    �rne�in 100.0 - 99.99 iile 10.0 - 9.99  ikisinin de sonucu 0.01 dir fakat C++ da olu�an yuvarlama hatalar�ndan dolay� kullan�m� tehlikelidir. 
    Bunu if else blo�u ile g�rebiliriz. 
    
    ** tabi bu hesaplanan de�erler aras�nda low-precision yani d���k hassasiyet varsa burda kar��la�t�rma yapma da her hangi bir sorun yok demektir. 

    Veya bir fonksiyonun d�n�� de�eri 0.0 ise burada direkt kar��la�t�rma yap�labilir 

    if (someFunc() == 0.0 ){
        do something 
    }  

    Gibisinden bir �rnek verilebilir. 

    ** Veya constexpr double gravity {9.8} gibi bir kayan noktal� say�; yani de�i�meyece�i garanti edilmi� bir literal ise burada da 
    * direkt kar��la�t�rma yap�labilir. �stteki fonksiyon �rne�i gibi. 
    *
    * Burada kar��la�t�rma yaparken belirli bir y�zde hatay� kabul ederim dersen sorun yok. Bunun i�in de klasik kar��la�t�rma ypa�yor hoca yani 
    * tolerans veriyor hoca. ApproximatelyEqual diyerek relAbs yani Knuth un algoritmas� ve normal algoritma yapt�. ��in d��erse 
    * 6.6 ch yi tekrar advanced okuyucular i�in olan b�l�m� okursun.
    
    */
    
    // CH 6.7 Logical Operators ye geldik
    /*
    C++ ta 3 tane mant�k operat�r� vard�r. ! Logical Not 
                                           && Logical AND
                                           || Logical OR
    Burada en �ok yap�lan hata Logical NOT operat�r�n�n i�lem �nceli�i seviyesinin y�ksekli�inden dolay�. Ne demek istedi�imi anlad�n
    Bu hatalardan ka��nmak i�in; E�er Logical Not operat�r�n� kullanacaksan kulland���n yerde parantezlerle durumu kontrol alt�na almal�s�n.


    Logical OR operat�r�nde yap�lan en b�y�k yanl�� ise ona benzeyen Bitwise or operat�r� ile kar��t�r�lmas�d�r. 
    || -> Lo. Op.
    |  -> Bi. Op.   Bu �ekildedir. �kisi farkl� fonksiyonlar� y�r�tt��� i�in sonu�lar�n yanl�� ��kmas�na sebep olabilir. 


    Logical AND operat�r�nde yap�lan en b�y�k yanl�� ise ona benzeyen Bitwise AND operat�r� ile kar��t�r�lmas�d�r.
    && -> Lo. Op.
    &  -> Bi. Op.   Bu �ekildedir. �kisi farkl� fonksiyonlar� y�r�tt��� i�in sonu�lar�n yanl�� ��kmas�na sebep olabilir.

    ** Burada hem Log. Or hem de Log. And kap�lar�n� bir den fazla olacak �ekilde kullanabiliriz. -> �rn: if (value > 10 && value < 20 && value�!=�16)

    ***K�sa devre de�erlendirmesi.
    * Burada Logical Or ve Logical And i�lemlerinde sol operat�r Or i�in true oldu�unda sonu� true olaca�� i�in sa� operat�r de�erlendirilmeden 
    * ge�ilir. Logical And de de sol operator false olursa sa� operat�r de�erlendirilmez buna K�sa devre de�erlendirmesi yani Short Circuit Evaluation
    * denir. Performansla alakal� yerlerde �ok iyi olur.
    * ** Burada dikkat edilmesi gereken en �nemli nokta yan etkili i�lemlerde �rne�in ++x x++ gibi i�lemlerde seri �eklinde logic devrelerde 
    * dikkatli olunmal� en mant�kl� hareket bunlar� ayn� seride kullanmamakt�r. 
    * �rn: if (x == 1 && ++y == 2)
               // do something

               Yukar�daki �rnekte g�rd���n gibi.

    Normalde her hangi bir s�ra ile de�erlendirme olurken Logical operat�rlerde standart a��k�a "ilk olarak sol operat�r de�erlendirilir" Demekte.

    Burada k�sa devre yerle�ik versiyonlarda olmakta yani overload ederek kendi tipimizi olu�turursak K�sa devre de yapmayacakt�r. Advanced reader.    
    */
    

    /*
    OR VE AND Kap�lar�n�n kar���k kullan�m�
    ---------------------------------------
    Burada yeniler AND ve OR kap�lar�n�n ayn� i�lem seviyesine sahip oldu�unu d���n�r + ve - gibi fakat bu noktada 
    yan�l�rlar.
    
    AND kap�s� OR kap�s�ndan daha y�ksek seviye i�lem �nceli�ine sahip oldu�u i�in hata yapmaya m�sait bir aland�r D�KKAT !!!!
    
    Buralarda parantezlerle sistemi kontrol etmek hem okunakl�l��� artt�r�r hem daja iyi kod yazm�� olursunuz ve hatalar� �nler.


    DE MORGAN IN KURALLARI ( Bi salmad�n bizi amk )
    -----------------------------------------------

    �o�u programc� !(x && y) ifadesinin  !x && !y Bu ifadeye e�it oldu�unu d���n�r. Fakat, not operat�r� i�lemler �zerine de da��l�r.

    !(x && y) => !x || !y
    !(x || y) => !x && !y  Bu �ekilde�da��l�r�yani
    

    Kan�t:
    x   	y	    !x  	!y	   !(x || y)  !x && !y
    false	false	true	true	true	    true
    false	true	true	false	false	    false
    true	false	false	true	false	    false
    true	true	false	false	false	    false



    LOG�CAL XOR
    -----------
    C++ mant�ksal bir XOR operat�r� sa�lamaz (operat�r^ mant�ksal bir XOR de�il, bit d�zeyinde bir XOR'dur).
    Mant�ksal VEYA veya mant�ksal VE'den farkl� olarak mant�ksal XOR, k�sa devre olarak de�erlendirilemez.
    Bu nedenle, mant�ksal OR ve mant�ksal AND operat�rlerinden mant�ksal bir XOR operat�r� olu�turmak zordur.
    Ancak e�itsizlik operat�r�n� (!=) kullanarak mant�ksal XOR'u kolayca taklit�edebilirsiniz:

    �RNE��N: f (a != b) ... // a XOR b, assuming a and b are�Booleans Bu birden �ok olabilir. Mesela a XOR b XOR c �eklinde de yapbiliriz
    sadece eklicez.
    *** Burada bilinmesi gereken tek �ey �u operandlar yani i�lenenler boolean olmal� integer olmaz.
    * 
    * �lla ba�ka bir type � kullancam dersen static_cast<bool>(i�lenen) yaparak bool a �evirirsin zaten hepsi �evriliyor.
    
    baz� klavyeler bu i�aretleri desteklemedi�i i�in 
    && -> and 
    || -> or
    !  -> not 

    kelimeleri kullan�labilir. 

    */


    /*
    
           �ZET
    -----------------
    
    �zeti ordan okumak daha mant�kl� geldi o y�zden yazmad�m. CH Optional veya CH 7 ye ge�ecez. 
    */
    
    
    
    
    
    
    
    
    





















    return 0;
}
