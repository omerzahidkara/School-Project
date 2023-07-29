/**
*
* @author Ömer Zahid Kara omer.kara7@ogr.sakarya.edu.tr
* @since Programın yazıldığı tarih
* 23/04/2023
* Sınıf ile ilgili açıklama
* ana program, aldığı sınıfın fonksiyonlarının yorum tiplerine göre sayılarını tespit eder ve yazdırır. Yorumları tiplerine göre ait oldukları fonksiyonun adı altında ayrı txt dosyalarında saklar.
*/
package odev;

import java.io.*;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

	//String tekSatirYorum = "firinDurum";
	//String cokSatirYorum = "firinDurum";
	//String javadoc = "firinDurum";

public class Program {
	public static void main(String[] args) throws IOException
	{		
		String sinifIcerigi = new String(Files.readAllBytes(Paths.get("src","odev","GofretMakina.java")),StandardCharsets.UTF_8);//Programın çalışacağı sınıf string olarak saklanması.
		//yorumsuz sinifin tamamı bir stringde
		
		String yorumsuzTamSinif = sinifIcerigi.replaceAll( "//.*|(\"(?:\\[^\"]|\"|.)*?\")|(?s)/\\*.*?\\*/", "$1 " );
		
		
		// sınıf adi yazdırılması kodu 
		
		String sinifAdiBul = "public\s*class{1} [a-zA-Z_0-9]* ";	
		Pattern sinifAdiKalibi = Pattern.compile(sinifAdiBul);
		Matcher eslesmeSinifAdi = sinifAdiKalibi.matcher(sinifIcerigi);			
		String bulunanSinifAdi = "";
		if(eslesmeSinifAdi.find())
		{
			bulunanSinifAdi = eslesmeSinifAdi.group();
		}
		String sinifAdiCikarilacak = "public\s*class";
		Pattern sinifAdiCikarilacakKalip = Pattern.compile(sinifAdiCikarilacak);
		Matcher eslesmeSinifAdiCikarilacak = sinifAdiCikarilacakKalip.matcher(bulunanSinifAdi);
		String bulunanHasSinifAdi = "";
		if(eslesmeSinifAdiCikarilacak.find())
		{
			bulunanHasSinifAdi = bulunanSinifAdi.replaceAll(sinifAdiCikarilacak, "");
		}			
		System.out.println("Sınıf :"+bulunanHasSinifAdi);
		
		//yalın fonksiyon dizisi
				String fonkinator = "public\\s*.*[(].*[)]\\s*[{][^}]*[}]";
				Pattern patternFonki = Pattern.compile(fonkinator);	
				Matcher matcher = patternFonki.matcher(yorumsuzTamSinif);	
				int ifonKi = 0;
				while(matcher.find())
				{
					ifonKi++;
				}
				String tumFonksDizisi[] = new String[ifonKi];
				Matcher matcherReal = patternFonki.matcher(yorumsuzTamSinif);
				String tutan = "";
				int ifonKi2 = 0;
				while(matcherReal.find())
				{
					tutan = matcherReal.group();
					tumFonksDizisi[ifonKi2] = tutan;
					ifonKi2++;
				}
				//yorumlu fonksiyon dizisi
				String fonkinatorYorumlu = "public\\s*.*[(].*[)]\\s*[{][^}]*[}]";
				Pattern patternFonkiYorumlu = Pattern.compile(fonkinatorYorumlu);	
				Matcher matcherYorumlu = patternFonkiYorumlu.matcher(sinifIcerigi);	
				int ifonKiYorumlu = 0;
				while(matcherYorumlu.find())
				{
					ifonKiYorumlu++;
				}
				String tumFonksDizisiYorumlu[] = new String[ifonKi];
				Matcher matcherRealYorumlu = patternFonkiYorumlu.matcher(sinifIcerigi);
				String tutanYorumlu = "";
				int ifonKi2Yorumlu = 0;
				while(matcherRealYorumlu.find())
				{
					tutanYorumlu = matcherRealYorumlu.group();
					tumFonksDizisiYorumlu[ifonKi2Yorumlu] = tutanYorumlu;
					ifonKi2Yorumlu++;
				}		
		//fonksiyon adlarının saklanmasının kodu 
		int fonksiyonSayisi = 0;
				
		String fonksiyonAdiBul = "public\s*.*[(].*[)]\s*[{]";
		Pattern fonksiyonAdiKalibi = Pattern.compile(fonksiyonAdiBul);
		Matcher eslesmeFonksiyonAdi = fonksiyonAdiKalibi.matcher(sinifIcerigi);			
		String bulunanFonksiyonAdi = "";
		while(eslesmeFonksiyonAdi.find())
		{
			fonksiyonSayisi++;
		}
		Matcher eslesmeFonksiyonAdi2 = fonksiyonAdiKalibi.matcher(sinifIcerigi);			
		String bulunanFonksiyonAdi2 = "";
		String bulunanFonksiyonAdiListe[] = new String[fonksiyonSayisi];
		int indeks = 0;
		while(eslesmeFonksiyonAdi2.find())
		{
			bulunanFonksiyonAdi2 = eslesmeFonksiyonAdi2.group();
			bulunanFonksiyonAdiListe[indeks] = bulunanFonksiyonAdi2; 
			indeks++;
		}		
		String fonksiyonAdiCikarilacakParantezli = "\s*[a-zA-Z_0-9]*\s*[(].*[)].*[{]";
		String cikarilacakParantez = "[(].*[)].*[{]";
		Pattern fonksiyonAdiIndirgeme = Pattern.compile(fonksiyonAdiCikarilacakParantezli);		
		String parantezliHasFonksiyonAdi = "";
		String bulunanFonksiyonAdiListe2[] = new String[fonksiyonSayisi];
		String bulunanFonksiyonAdi3 = bulunanFonksiyonAdiListe[0];
		String bulunanHasFonksiyonAdi = "";
		int indeks3 = 0;
		while(indeks3 != fonksiyonSayisi )
		{
			 Matcher eslesmeFonskiyonAdiCikarilacakParantezli = fonksiyonAdiIndirgeme.matcher(bulunanFonksiyonAdi3);
			 if(eslesmeFonskiyonAdiCikarilacakParantezli.find())
			 {
				 parantezliHasFonksiyonAdi = eslesmeFonskiyonAdiCikarilacakParantezli.group();				
			 }			 
			 bulunanHasFonksiyonAdi = parantezliHasFonksiyonAdi.replaceAll(cikarilacakParantez,"");
			 bulunanFonksiyonAdiListe2[indeks3] = bulunanHasFonksiyonAdi;
			 if(indeks3 != fonksiyonSayisi-1)
			 {
				 bulunanFonksiyonAdi3 = bulunanFonksiyonAdiListe[indeks3+1];  
			 }			 
			 indeks3++;
		}	
		//teklisatir yorumların saklanmasının kodu
		int sayacTekSatir = 0;
    	String teksatir =  "/{2,3} ([a-zA-Z_0-9çüğışö]* [a-zA-Z_0-9çüğışö]*)*" ;
    	Pattern theClassPatternSayac = Pattern.compile(teksatir);
    	Matcher classMatcherSayac = theClassPatternSayac.matcher(sinifIcerigi);
    	
		while(classMatcherSayac.find())
		{
			sayacTekSatir++;
		} 

    	Pattern theClassPattern = Pattern.compile(teksatir);    	
    	Matcher classMatcher = theClassPattern.matcher(sinifIcerigi);   	
    	String storageVehicle = "";
    	String storage[] = new String[sayacTekSatir];
    	int indeks0 = 0;
		while(classMatcher.find())
		{
			storageVehicle = classMatcher.group();
			storage[indeks0] = storageVehicle; 
			indeks0++;
		}
		
		String cikarilacakTekliYorumKarakterleri = "//";		
		String tekliYorumTasiyici2 = "";
		String hasTekliSatirYorumlari[] = new String[sayacTekSatir];
		String tekliYorumTasiyici = "";
		int indeksTekliYorum = 0;
		while(indeksTekliYorum != sayacTekSatir )
		{
			tekliYorumTasiyici = storage[indeksTekliYorum];
			tekliYorumTasiyici2 = tekliYorumTasiyici.replaceAll(cikarilacakTekliYorumKarakterleri,"");
			hasTekliSatirYorumlari[indeksTekliYorum] = tekliYorumTasiyici2;
			indeksTekliYorum++;
		}

		//coksatir yorumların saklanması kodu
		int sayacCokSatir = 0;
    	String coksatir =  "(?s)/(\\*)[^*]{1}.*?(\\*/)" ;
    	Pattern theClassPatternSayac2 = Pattern.compile(coksatir);
    	Matcher classMatcherSayac2 = theClassPatternSayac2.matcher(sinifIcerigi);
    	
		while(classMatcherSayac2.find())
		{
			sayacCokSatir++;
		} 
		
    	Pattern theClassPattern2 = Pattern.compile(coksatir);    	
    	Matcher classMatcher2 = theClassPattern2.matcher(sinifIcerigi);   	
    	String storageVehicle2 = "";
    	String storage2[] = new String[sayacCokSatir];
    	int indeks4 = 0;
		while(classMatcher2.find())
		{
			storageVehicle2 = classMatcher2.group();
			storage2[indeks4] = storageVehicle2; 
			indeks4++;
		}
		String cikarilacakCokluYorumKarakterleri = "/*\\**";		
		String cokluYorumTasiyici2 = "";
		String hasCokluSatirYorumlari[] = new String[sayacCokSatir];
		String cokluYorumTasiyici = "";
		int indeksCokluYorum = 0;
		while(indeksCokluYorum != sayacCokSatir )
		{
			cokluYorumTasiyici = storage2[indeksCokluYorum];
			cokluYorumTasiyici2 = cokluYorumTasiyici.replaceAll(cikarilacakCokluYorumKarakterleri,"");
			hasCokluSatirYorumlari[indeksCokluYorum] = cokluYorumTasiyici2;
			indeksCokluYorum++;
		}
		//javadok yorumların saklanması kodu
		int sayacjavadoc = 0;
	  	String javadocsatir =  "(?s)/(\\*\\*)[^*]{1}.*?(\\*/)" ;
		Pattern theClassPatternSayac3 = Pattern.compile(javadocsatir);
		Matcher classMatcherSayac3 = theClassPatternSayac3.matcher(sinifIcerigi);
		
		while(classMatcherSayac3.find())
		{
			sayacjavadoc++;
		} 
				
		Pattern theClassPattern3 = Pattern.compile(javadocsatir);    	
		Matcher classMatcher3 = theClassPattern3.matcher(sinifIcerigi);   	
		String storageVehicle3 = "";
		String storage3[] = new String[sayacjavadoc];
		int indeks6 = 0;
		while(classMatcher3.find())
		{
			storageVehicle3 = classMatcher3.group();
			storage3[indeks6] = storageVehicle3; 
			indeks6++;
		}
		String cikarilacakJavadocYorumKarakterleri = "/*\\**";		
		String javadocYorumTasiyici2 = "";
		String hasJavadocSatirYorumlari[] = new String[sayacjavadoc];
		String javadocYorumTasiyici = "";
		String hasJavadocYorum = "";
		int indeksJavadocYorum = 0;
		while(indeksJavadocYorum != sayacjavadoc )
		{
			javadocYorumTasiyici = storage3[indeksJavadocYorum];
			hasJavadocYorum = javadocYorumTasiyici.replaceAll(cikarilacakJavadocYorumKarakterleri,"");
			hasJavadocSatirYorumlari[indeksJavadocYorum] = hasJavadocYorum;
			indeksJavadocYorum++;
		}
		int topYorumSayisi = sayacTekSatir + sayacCokSatir + sayacjavadoc;

		
		//fonksiyonlardaki yorum sayılarının bulunması kodu
		
		/*bilgiler   	
		* 				 fonksiyonSayisi, sayacTekSatir, sayacCokSatir, sayacjavadoc ,teksatir(pattern), coksatir(pattern), javadocsatir(pattern),hasTekliSatirYorumlari,
		*     			hasCokluSatirYorumlari, hasJavadocSatirYorumlari, bulunanFonksiyonAdiListe2, topYorumSayisi, yorumsuzTamSinif, tumFonksDizisi, tumFonksDizisiYorumlu	
		*/
		
		//genel yazdırma
				
		String teksatirGecirici = ""; 
		String coksatirGecirici = "";
		String javadocGecirici = "";
		int teksatirFonkNoTutucuDizi [] = new int[fonksiyonSayisi];
		String fonkTutucu = "";
		String fonkTutucu2 = "";
		int coksatirFonkNoTutucuDizi [] = new int[fonksiyonSayisi];
		int javadocFonkNoTutucuDizi [] = new int[fonksiyonSayisi];					
		String fonkAdiTut = "";
		int fonksiyonelIndeks = 0;
		int tasiyanTek = 0;
		int tasiyanCok = 0;
		int tasiyanJavadoc = 0;
		
		while(fonksiyonelIndeks != fonksiyonSayisi)
		{

			int donguIndeksi2 = 0;
			int donguindeksi3 = 0;
			int donguIndeksi4 = 0;
			
			fonkAdiTut = bulunanFonksiyonAdiListe2[fonksiyonelIndeks];
			System.out.println("         Fonksiyon: "+fonkAdiTut);
			
			fonkTutucu = tumFonksDizisiYorumlu[fonksiyonelIndeks];//yorumlu fonksiyon alınır
			while(donguIndeksi2 != sayacTekSatir )//alınan yorumlu fonksiyon teksatır dizesiyle karşılaştırılır ve eşleşme olursa fonksiyon numarasına yazılır(her yoruma ayrı kayıt)
			{
				
				
				Pattern tekPTTRN1 = Pattern.compile(teksatir);
				Matcher tekMTCHR1 = tekPTTRN1.matcher(fonkTutucu);
					if(tekMTCHR1.find())
					{
						teksatirFonkNoTutucuDizi[fonksiyonelIndeks]++;
						tasiyanTek++;
					}
					donguIndeksi2++;							
			}
			teksatirFonkNoTutucuDizi[fonksiyonelIndeks] /= 3;
			tasiyanTek /= 3;
			while(donguindeksi3 != sayacCokSatir )
			{
				
				coksatirGecirici = hasCokluSatirYorumlari[donguindeksi3];
				Pattern cokPTTRN1 = Pattern.compile(coksatir);
				Matcher cokMTCHR1 = cokPTTRN1.matcher(fonkTutucu);
					if(cokMTCHR1.find())
					{
						coksatirFonkNoTutucuDizi[fonksiyonelIndeks]++;
						tasiyanCok++;
					}
					donguindeksi3++;							
			}
			coksatirFonkNoTutucuDizi[fonksiyonelIndeks] /= 2;
			tasiyanCok /= 2;
			while(donguIndeksi4 != sayacjavadoc )
			{
				
				javadocGecirici = hasJavadocSatirYorumlari[donguIndeksi4];
				Pattern javadocPTTRN1 = Pattern.compile(javadocsatir);
				Matcher javadocMTCHR1 = javadocPTTRN1.matcher(fonkTutucu);
					if(javadocMTCHR1.find())
					{
						javadocFonkNoTutucuDizi[fonksiyonelIndeks]++;
						tasiyanJavadoc++;
					}
					donguIndeksi4++;							
			}
			javadocFonkNoTutucuDizi[fonksiyonelIndeks]/= 9;
			tasiyanJavadoc /= 9;
			System.out.println("                Tek Satır Yorum Sayısı:"+tasiyanTek);
			System.out.println("                Cok Satır Yorum Sayısı:"+tasiyanCok);
			System.out.println("                Javadoc Yorum Sayısı:  "+tasiyanJavadoc);				
							
			System.out.println("-------------------------------------------");
			 tasiyanTek = 0;
			 tasiyanCok = 0;
			 tasiyanJavadoc = 0;

			fonksiyonelIndeks++;
		}
		//dosya okuma ve yazma metotları ve txt lerin oluşturulması kodu
		
				File tekSatirliYorumDosya = new File("teksatir.txt ");
				if(!tekSatirliYorumDosya.exists())
				{
					tekSatirliYorumDosya.createNewFile();
				}
				FileWriter tekSatirliYorumYazici = new FileWriter(tekSatirliYorumDosya,false);
				BufferedWriter tekSBuffer = new BufferedWriter(tekSatirliYorumYazici);
										
				File cokSatirliYorumDosya = new File("coksatir.txt ");
				if(!cokSatirliYorumDosya.exists())
				{
					cokSatirliYorumDosya.createNewFile();
				}
				FileWriter cokSatirliYorumYazici = new FileWriter(cokSatirliYorumDosya,false);
				BufferedWriter cokSBuffer = new BufferedWriter(cokSatirliYorumYazici);
						
				File javadocYorumDosya = new File("javadoc.txt ");
				if(!javadocYorumDosya.exists())
				{
					javadocYorumDosya.createNewFile();
				}
				FileWriter javadocYorumYazici = new FileWriter(javadocYorumDosya,false);
				BufferedWriter javadocSBuffer = new BufferedWriter(javadocYorumYazici);
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
				


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}