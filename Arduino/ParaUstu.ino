/*
GENEL BAKIS
------------
bilgileri almak txt den
para yukleme
hizmet secimi
para sikisma
para uzeri verme
degisen bilgileri geri yazma
*/


#include <SD.h>

#define led_1 5
#define led_2 6


// Degiskenler
int bilgiler_dizisi[25], i, j, para_miktari, islem_tutari=0, para_uzeri=0;
int secilen_hizmetler[4], k=1 , banknotlar[5] = {5, 10, 20, 50, 100}, degerler_yedek[9];
char buton='0';
File myFile;


// Fonksiyonlar
void dosya_okuma()
{
    // txt icindeki degerleri bir sayi dizisinin degerlerini guncelleyerek olusturan bir fonksiyon

    if (!SD.begin(4))
    {
        Serial.println(F("SD kart hata!!"));
        while (1);
    }
    Serial.println(F("SD kart hazir."));    
    
    // bilgileri almak txt den
    myFile = SD.open("hzmetler.txt");
    if (myFile)
    {
        // birinci satiri okuma
        for ( i = 0; i < 4; i++)
            bilgiler_dizisi[i] = myFile.readStringUntil(',').toInt();
        bilgiler_dizisi[4] = myFile.readStringUntil('\n').toInt();

        // kalan satirlari okuma
        for ( i = 1; i <= 4; i++)
        {
            bilgiler_dizisi[i*5+0] = myFile.readStringUntil(',').toInt();
            myFile.readStringUntil(',');
            bilgiler_dizisi[i*5+1] = i;
            bilgiler_dizisi[i*5+2] = myFile.readStringUntil(',').toInt();
            bilgiler_dizisi[i*5+3] = myFile.readStringUntil('\n').toInt();
            bilgiler_dizisi[i*5+4] = 0;
        }
        myFile.close();
    }
    else
        Serial.println(F("Hata hzmetler.txt acilamadi."));

    /*
    olusturulan dizi formati
    // ilk 5 eleman
    {5TL adeti, 10TL adeti, 20TL adeti, 50TL adeti, 100TL adeti}
    // son 20 eleman
    4 * {HizmetID bilgisi, hizmet ad bilgisi(ID ile ayni deger donduruluyor), kalan hizmet bilgisi, hizmet fiyat bilgisi, 0}
    */
}

void para_yukleme()
{
    // para yukleme kisminda basilan butona gore para miktarini arttiriyoruz.
    if (buton == '1'){
        para_miktari += 5;
        k = 1;
    }
    else if(buton == '2'){
        para_miktari += 10;
        k = 1;
    }
    else if(buton == '3'){
        para_miktari += 20;
        k = 1;
    }
    else if(buton == '4'){
        para_miktari += 50;
        k = 1;
    }
    else if(buton == '5'){
        para_miktari += 100;
        k = 1;
    }
    else if(buton == '7'){
        para_miktari = 0;
        Serial.print(F("\rParaniz iade ediliyor.\r\r"));
        k = 1;
    }

    // kullaniciyi bilgilendirmek icin
    if(k==1)
    {
        Serial.print(F("Anlik yuklenen para miktari : "));
        Serial.println(para_miktari);
        k = 0;
    }
}

void hizmet_secimi()
{
    // girilen butona gore secilen hizmetler dizisindeki hizmet sayisini bir arttiran fonksiyon.
    if (buton == '1')
    {
        secilen_hizmetler[0] += 1;
        Serial.println(F("Kopukleme sectiniz."));
    }
    else if(buton == '2')
    {
        secilen_hizmetler[1] += 1;
        Serial.println(F("Yikama sectiniz."));
    }
    else if(buton == '3')
    {
        secilen_hizmetler[2] += 1;
        Serial.println(F("Kurulama sectiniz."));
    }
    else if(buton == '4')
    {
        secilen_hizmetler[3] += 1;
        Serial.println(F("Cilalama sectiniz."));
    }
    else if(buton == '5')
    {
        for ( i = 0; i < 4; i++)
            secilen_hizmetler[i] = 0;
        Serial.println(F("Secimleriniz Resetlendi."));
    }
}

int para_sikisti_mi()
{
    randomSeed(analogRead(0));
    i = random(1,5); 
    if(i == 2)
        return 1;
    return 0;
}

void para_uzeri_verme()
{
    // kasaya verilen para >> para_miktari
    // toplam islem tutari >> islem_tutari
    // para uzeri >> para_uzeri
    // azalan paralari ve yapilan islemleri bilgiler_dizisinde guncelleme
    // degerler_yedek dizisinin amaci eger kasada yeterli para olmaz ise bilgiler_dizisi ndeki degismis degerleri eski haline getirmek.

    islem_tutari = 0;
    
    // degisme ihtimali olanlari yedekleme
    for ( i = 0; i < 5; i++)
        degerler_yedek[i] = bilgiler_dizisi[i];
    
    degerler_yedek[5] = bilgiler_dizisi[7];
    degerler_yedek[6] = bilgiler_dizisi[12];
    degerler_yedek[7] = bilgiler_dizisi[17];
    degerler_yedek[8] = bilgiler_dizisi[22];

    // islem_tutari ve para_uzeri hesaplama kisimi. Ayrica kalan hizmet miktarini da azaltiyoruz.
    for ( i = 0; i < 4; i++)
    {
        islem_tutari += secilen_hizmetler[i] * bilgiler_dizisi[(i+1)*5 + 3];
        bilgiler_dizisi[(i+1)*5 + 2] -= secilen_hizmetler[i];
    }
    para_uzeri = para_miktari - islem_tutari;

    // kullaniciya mesaj
    Serial.print(F("para_miktari : "));
    Serial.println(para_miktari);
    Serial.print(F("islem_tutari : "));
    Serial.println(islem_tutari);
    Serial.print(F("para_uzeri : "));
    if (para_uzeri < 0)
        Serial.println(0);
    else
        Serial.println(para_uzeri);
    
    // en az banknot ile para uzeri verebilmeyi hesaplayan kisim
    for ( i = 4; i >= 0; i--)
    {
        while ((para_uzeri >= banknotlar[i]) && (bilgiler_dizisi[i] > 0)  )
        {
            bilgiler_dizisi[i] = bilgiler_dizisi[i] - 1;
            para_uzeri = para_uzeri - int(banknotlar[i]);
        }
    }

    // kasada yeterli para yoksa yedekledigimiz bilgileri degisenlerin uzerine yaziyoruz.
    if (para_uzeri != 0)
    {
        Serial.println(F("Kasada yeterli para yok veya yuklediginiz para hizmetleri karsilamiyor. Islemleriniz yapilamiyor. Paranizin hepsi geri veriliyor."));
        for ( i = 0; i < 5; i++)
            bilgiler_dizisi[i] = degerler_yedek[i];
        bilgiler_dizisi[7] = degerler_yedek[5];
        bilgiler_dizisi[12] = degerler_yedek[6];
        bilgiler_dizisi[17] = degerler_yedek[7];
        bilgiler_dizisi[22] = degerler_yedek[8];
    }
    else
        Serial.println(F("\rHer sey yolunda. Para uzerinizi almayi unutmayin.\r"));
}

void dosya_yazma()
{
    // bilgileri son hali ile txt ye yazma fonksiyonu
    // var olan txt yi silip yeniden uretiyoruz.
    SD.remove("hzmetler.txt");
    
    myFile = SD.open("hzmetler.txt", FILE_WRITE);
    if (myFile)
    {
        Serial.print(F("Yaziliyor hzmetler.txt..."));

        // birinci satiri yazma
        for ( i = 0; i < 4; i++)
        {
            myFile.print(bilgiler_dizisi[i]);
            myFile.print(',');
        }
        myFile.println(bilgiler_dizisi[4]);

        // kalan satirlari yazma
        for ( i = 1; i <= 4; i++)
        {
            myFile.print(bilgiler_dizisi[i*5+0]);
            myFile.print(',');
            if (i == 1)
                myFile.print("kopukleme");
            else if (i == 2)
                myFile.print("yikama");
            else if (i == 3)
                myFile.print("kurulama");
            else if (i == 4)
                myFile.print("cilalama");
            myFile.print(',');
            myFile.print(bilgiler_dizisi[i*5+2]);
            myFile.print(',');
            myFile.println(bilgiler_dizisi[i*5+3]);
        }
        myFile.close();
        Serial.println(F("Bitti."));
    }
    else
        Serial.println(F("Hata! hzmetler.txt ye yazilamadi."));
    /*
    ornek yazilan txt
    10,10,16,43,17
    1,kopukleme,541,15
    2,yikama,532,10
    3,kurulama,521,5
    4,cilalama,541,50
    */
}
   
void setup() {
    Serial.begin(9600);

    // bilgileri txt den alma
    dosya_okuma();
    
    // ledler icin
    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);
}

void loop() {
    Serial.println("\r\r\rHosgeldiniz\r\r");

    // para yukleme
    Serial.println(F("Hangi banknotlardan yukleyeceginizi giriniz."));
    Serial.println(F("1. Buton - 5TL sayisi"));
    Serial.println(F("2. Buton - 10TL sayisi"));
    Serial.println(F("3. Buton - 20TL sayisi"));
    Serial.println(F("4. Buton - 50TL sayisi"));
    Serial.println(F("5. Buton - 100TL sayisi"));
    Serial.println(F("6. Buton - Bitis"));
    Serial.println(F("7. Buton - Reset"));

    para_miktari = 0;
    buton = Serial.read();
    
    while (buton != '6')
    {
        para_yukleme();
        buton = Serial.read();
    }
    Serial.print(para_miktari);
    Serial.println(F(" TL para attiniz.\r"));
    
    // hizmet secimi
    Serial.println(F("Hangi hizmetlerden istiyorsunuz."));
    Serial.println(F("1. Buton - Kopukleme"));
    Serial.println(F("2. Buton - Yikama"));
    Serial.println(F("3. Buton - Kurulama"));
    Serial.println(F("4. Buton - Cilalama"));
    Serial.println(F("5. Buton - Reset"));
    Serial.println(F("6. Buton - Bitis"));

    for ( i = 0; i < 4; i++)
        secilen_hizmetler[i] = 0;

    buton = Serial.read();
    while (buton != '6')
    {
        hizmet_secimi();
        buton = Serial.read();
    }

    // Para sikisma
    // if else sayesinde para sikisma durumunda bilgiler degismiyor ve yazdirilmiyor.
    // loop un basinda tekrardan dosyadan okumaya da gerek kalmiyor.
    if (para_sikisti_mi())
    {
        // Kirmizi led yakma
        digitalWrite(led_1, HIGH);
        Serial.println(F("Makineye para sikisti. Paraniz iade ediliyor."));
        delay(1500);
        digitalWrite(led_1, LOW);
    }
    else
    {
        // Yesil led yakma
        digitalWrite(led_2, HIGH);
        Serial.println(F("\rHer sey yolunda.\r"));
        delay(1000);
        digitalWrite(led_2, LOW);

        // para uzeri verme
        // bu fonksiyon ayni zamanda bilgiler_dizisini guncelliyor txt ye yazdirilmasi kaliyor geriye
        para_uzeri_verme();

        // degisen bilgileri geri yazma txt ye
        // Eger para yetersiz ise para_uzeri_verme fonksiyonunda bilgiler degismiyor.
        dosya_yazma();
    }
}
