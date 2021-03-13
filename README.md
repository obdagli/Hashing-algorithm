## Kitap öneri sistemi

### Programın çalışma mantığı

Program ilk çalıştırıldığı an hashReset() fonksiyonunu çağırarak hashTable() içerisindeki key değerlerini -1
yapar. Bu, bizim insert() fonksiyonunda eleman eklerken karşılaştırma yapılması için gerekli olan if
koşulumuzdur. hashTable.txt dosyamız var olduğu için, getHashTable() fonksiyonu kullanılarak bir
hashTable.txt dosyası içerisindeki kelimeleri hashTable’a aktarılır. Kullanıcıya böyle bir dosyanın var
olduğu bilgisi verilir. Bu dosya içerisinde arama yapmak ya da dökümandan kelime eklemesi yapmak gibi
seçenekleri kullanıcıya sorarak cevabı “choice” değişkeninde tutar ve bu seçime göre arama veya
dökümandan kelime ekleme yapılır.


 - ### Arama yapılması

> hornerForWord() fonksiyonumuzu çağırarak aranan kelime için hornerMethod
> uygulanır ve bir key değeri üretilir. Bu key değerini searchHashKey() fonksiyonuna gönderdikten sonra
> burada double hashing yapılır ve üretilen “finalHash” değerinden başlayarak hashTable içerisinde arama
> yapar. Modu alınmış iki sayının değeri aynıysa farklı bir bölmeye atanacağından, doğru kelimeyi bulmak
> için “i” değeri arttırılarak bakılır. Eşit olan değer bulunduğunda adım sayımız “i” olur ve ekrana yazdırılır.

 - ### Kelime eklenmesi(horner method)

> Arama kısmında yapılanın aksine tek bir kelime için değil tüm
> dokümandaki kelimeler için bu metod uygulanır. Temp dizisine tek tek char şeklinde karakterleri
> çekerek, aralarında boşluk olana değin ya da bir alt satıra geçme işlemi gelene değin charları bu diziye
> almaya devam ederek kelimeyi elde ederiz. Daha sonrasında bu kelimenin uzunluğunu kullanarak
> karakterlerini dönüştürür(non case-sensitivte) daha sonrasında key değerini formül ile birlikte elde eder
> ve insert işlemine yollarız. Gelen kelimeler için insert yaptıktan sonra temp dizisini tekrar null(‘\0’)
> yaparak ikinci kelimeye geçer ve bu böyle devam eder.

 - ### Özet
 

> Dökümandan alınan kelimeleri hornerMethod yöntemiyle sayıya
> dönüştürerek bu hashingTable’a eklenmesi için “insert” fonksiyonuna yollanır.
> Burada gerekli kontroller yapıldıktan sonra double-hashing sonucunda çıkan
> finalHashing değeri kullanılarak hash tablosunun gerekli boşluğuna yazdırma
> işlemi gerçekleştirilir. Her yazdırılan işlem için pointer kullanılarak loadfactor’e
> gidecek n(# of keys) bir bir arttırılır. Hash table’ına yazdırılması sonrasında
> dosyaya yazdırılıkmak üzere writeHash fonksiyonuna gönderilir. Burada fprintf
> yardımıyla dosyaya yazdırılır. Her bir kelime için bu yöntem uygulandıktan sonra
> LoadFactor değeri kullanıcıya command prompt üzerinde gösterilir.
> LoadFactor>0.8 olduğunda kullanıcıyı uyarır ve 1.0’a ulaşınca durması
> amaçlanır. Bunların dışında var olan hashing table dosyamızda arama yapmak
> için search fonksiyonu kullanılır. Girilen kelimenin hornerMethod’u ile sayısı
> alındıktan sonra arama fonksiyonuna gönderilerek double hashing yapılır ve
> çıkan finalHashing değeri ile bulunması amaçlanır.

### Ekran görüntüleri

![image](https://user-images.githubusercontent.com/56681549/111034595-7cf5b300-8427-11eb-8963-759049fc9ad3.png)
![image](https://user-images.githubusercontent.com/56681549/111034615-854dee00-8427-11eb-828a-14527ae5d5f8.png)

### complexity

![image](https://user-images.githubusercontent.com/56681549/111034621-8da62900-8427-11eb-9781-d607ced5cfff.png)

