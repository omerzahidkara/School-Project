	--- Proje, Ömer Zahid KARA (2A - g191210070) tarafından yapıldı.

* Projenin program bazında amacı girdi dosyasında bulunan komutların anlaşılıp bu komutların işlevlerine göre çıktı dosyası elde edimidir.
Ders bazında amacı dosya işlemlerinin ve sistem programlama mantığının temel olarak anlaşılması olabilir.

* Projede libfdr kütüphanesi ve temel c kütüphaneleri kullanıldı. libfdr kütüphanesi manuel olarak kurulup make ile derlendi.

* Ekstra struct olarak dinamik dizi tasarlandı fakat main.c içinde tutuldu. Dinamik diziyi çalıştıran özel iki adet yardımcı fonksiyon ve onları kullanan ana ekleme ve silme fonksiyonları bulunuyor.
Komutlar main fonksiyonda fark edildikten sonra bahsedilen diğer fonksiyonlarla "dur:" komutuna kadar düzenlemek üzere oluşturulan dinamik dizi yapısına saklamak üzere çalıştırılıyor.

* 4 adet komutun çalıştırılma kombinasyonlarının oluşturacağı durumlar test edildi ve sağlandığı görüldü. Örneğin ilk başta silme komutu çalıştırılamaz, kullanıcı uyarılır. Program bu gibi durumlarda uyarı verir. dur: komutu diğer yazma komutlarından önce gelirse dur: komutuna kadar kısım işlenir gerisi işlenmez. Fazla sayıda silme isteği yapılırsa ve sona gidilmezse diğer yazma komutlarında yazılanların başa yazıldığı görülebilir veya ortaya yazılabilir.Ayrıca formata uymayan kod içeriklerinde nerenin uymadığının uyarısı verilir.

* Kod-girdi dosyası Türkçe karaktere hassas değildir. Bu aşamanın şart olduğu görülmediği için atlandı.

* Kodlama mantığı olabilidiğince basit tutuldu, bazı str fonskiyonları kullanıldı (strcmp). Çoğu eşleştirme if ile kontrol edildi. 

"* yaz:" ve "sil:" komutlarının içeriklerinin kontrol edilebilmesi için ödev şartında bulunan adet ve karakter bilgisi yazımı çifter olarak kontrol edildi.
İlk elemanın integer olması ikinci elemanın da şartları sağlanması gözlendi.

* Main kaynak dosyası yorumlarla açıklanmıştır.

* Programa ait çıktı örnekleri doc klasöründedir.     11 Mayıs 2024
