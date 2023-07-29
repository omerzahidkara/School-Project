/**
*
* @author Ömer Zahid Kara omer.kara7@ogr.sakarya.edu.tr
* @since Programın yazıldığı tarih
* 23/04/2023
* Sınıf ile ilgili açıklama
* Örnek sınıf
*/
package odev;
import java.util.UUID;

public class GofretMakina {
	
	private String sistemNo;
	private boolean sistemDurum;
	private boolean firinDurum;
	private boolean gofretYaprakKremaMakinasiDurum;
	private boolean ambalajMakinasiDurum;
	/**
	* Gofret üretim makinası adına kurucu fonksiyon
	*/
	public GofretMakina() {
	this.sistemNo = UUID.randomUUID().toString(); 
	/* Başlangıçta false */firinDurum = false; gofretYaprakKremaMakinasiDurum = false; ambalajMakinasiDurum = false;		
	}
	/**
	* 
	* @param makinaNo UUID olarak makina id
	* @return makina instance
	*/
	public GofretMakina(String makinaNo) {
	/*
	* Varolan bir makina no ile oluşturuluyor.
	*/
	this.sistemNo = makinaNo;
	firinDurum = false; gofretYaprakKremaMakinasiDurum = false; ambalajMakinasiDurum = false;	 // robot çalışma durumları false yapılıyor
	}
	public void calistirFirin() {
	/**
	* firinStatus true yapılıyor
	*/
		firinDurum = true;
	}
	public void calistirYaprakKremaMakinasi() {
		/**
		* gofretYaprakKremaMakinasiStatus true yapılıyor
		*/
		gofretYaprakKremaMakinasiDurum = true;
		}
	public void calistirAmbalajMakinasi() {
		/**
		* ambalajMakinasiStatus true yapılıyor
		*/
		ambalajMakinasiDurum = true;
		}
	/**
	* Makinanın fırın kısmının durdurulması //
	*/
	public void durdurFirin() {
		firinDurum = false;
	}
	/**
	* Makinanın yaprak ve krema birleştirme robotu kısmının durdurulması //
	*/
	public void durdurYaprakKremaMakinasi() {
		gofretYaprakKremaMakinasiDurum = false;
	}
	/**
	* Makinanın  ambalaj makinasi kısmının durdurulması //
	*/
	public void durdurAmbalajMakinasi() {
		ambalajMakinasiDurum = false;
	}
	public String getMakinaNo() {
	// makina no getir
	return sistemNo;
	}
	@Override
	public String toString() {
	// sistem durumu belirlenmesi //
	String durum = sistemDurum ? "Sistem Çalışıyor." : "Sistem Çalışmıyor";
	return durum;
	}

}
