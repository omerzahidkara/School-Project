/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Oyun
{
    Scanner scanner = new Scanner(System.in);
    Random random = new Random();
	private List<Koloni> koloniler = new ArrayList<>();						//Kolonileri yonetmek adina koloniler ve nitleikleri listelerde saklanir.
	private List<Integer> nufuslar = new ArrayList<>();						//
	private List<String> semboller = new ArrayList<>();						//
	private int koloniSayisi = 0;											//
	public int turSayisi = 0;												//
	private int yokOlmusKoloniSayisi = 0;									//
	private int kalanKoloniSayisi = 0;										//
	public Oyun() throws InterruptedException
	{
		this.nufuslar = koloniVerileriAl();									//Kulalnicidan nufus veirleri istenir.
		this.koloniSayisi = nufuslar.size();								//Islemlerde kullanilmak uzere koloni sayisi tutulur.
		kalanKoloniSayisi = koloniSayisi;									//Oyunu sona erdierbilmek adina kalan koloni sayisi tutulur.
		butunSembolleriUret();												//Kolonilere atanacak sembolleruretilir.
		kolonileriGerceklestir();											//Koloni nesneleri uretilir.
	}
	
    private List<Integer> koloniVerileriAl() throws InterruptedException 
    {
        List<Integer> diziInt = new ArrayList<>();
        {
			System.out.print("Nufuslari gir (x > 0): ");
			String satir = scanner.nextLine();
			String[] elemanlar = satir.split(" ");

			for (String eleman : elemanlar) 
			{
			    int nufus = Integer.parseInt(eleman);
			    if(nufus > 0)											//Pozitif nufus degerleri alinir.
			    {
			    	diziInt.add(nufus);
			    }          
			}
		}
        return diziInt;
    }
    public int getYokOlmuslarSayisi()									//Yok olmus koloni sayisini gonder...
    {
    	return yokOlmusKoloniSayisi;
    }
    private String sembolUret(int karakterUzunlugu)						//Sembolleri uretcek ana fonksiyona ait yardimci fonksiyon. Parametre olarak uretilecek sembolun uzunlugunu alir. Boylece sonsuz varyasyonlu semboller uretilir.
    {
        char baslangic = 0x30;
        int karakterSayisi = 43;
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < karakterUzunlugu; i++) 
        {
            int rastgeleSayi = random.nextInt(karakterSayisi);
            char rastgeleKarakter = (char) (baslangic + rastgeleSayi);
            stringBuilder.append(rastgeleKarakter);
        }

        return stringBuilder.toString();
    }
    public int getKalanKoloniSayisi()								// Kalan koloni sayisini getir...
    {
    	return this.kalanKoloniSayisi;
    }
    public void setKalanKoloniSayisi()												//Kalan koloni sayisini duzenle...
    {	
    	this.kalanKoloniSayisi = this.koloniSayisi-this.yokOlmusKoloniSayisi;
    }
    private void butunSembolleriUret() 										//Koloni sayisi kadar sembol uretir ve gonderir.
    {
        int chMiktari = 1;
        int kontrolcu = 0;
        semboller.add(0,sembolUret(chMiktari));
        for (int i = 1; i < getKoloniSayisi(); i++) 
        {
        	kontrolcu = 0;
        	semboller.add(i,sembolUret(chMiktari));
        	while(kontrolcu != i)
        	{
        		String element1 = semboller.get(kontrolcu);
        		String element2 = semboller.get(i);
        		boolean isEqual = element1.equals(element2);
            	if(isEqual)
            	{
            		semboller.remove(i);
            		semboller.add(i,sembolUret(chMiktari));
            		kontrolcu = -1;
            	}
            	kontrolcu++;
        	}
            if (i % 42 == 0) 							//42 sembolde bir karakter sayisi artar.
            {
                chMiktari++;
            }
        }
    }
    private int ilkErzakAtamasi(int ilkNufusVerisi)				//Erzaklar nufuslarin akresi kadar atanir.
    {
    	return (ilkNufusVerisi*ilkNufusVerisi);
    }
    private void kolonileriGerceklestir()						//Kolonileri ureten fonksiyon.
    {
    	for(int i = 0;i<getKoloniSayisi();i++)
    	{
    		int erzakAta = ilkErzakAtamasi(nufuslar.get(i));
    		Koloni yeniKoloni = new Koloni(semboller.get(i),nufuslar.get(i),erzakAta);		//Kolonilere verileri uretildikten osnra gonderilir ve olusturulur.
    		koloniler.add(yeniKoloni);														// Oyun nesnesi tarafindan tutulan koloni nesnesi listesi...
    	}
    }
    private void yokOlmusKolonileriSay()												//Yok olmus koloni sayisini bul...
    {
    	int sayac = 0;
    	Koloni koloniTutucu;
    	for(int i = 0; i<this.getKoloniSayisi();i++)
    	{
    		koloniTutucu = this.koloniler.get(i);
    		if(koloniTutucu.getNufus() == 0 && koloniTutucu.getErzak() == 0)
    		{
    			sayac++;
    		}
    		this.yokOlmusKoloniSayisi = sayac;
    	}
    }
	public void kazananiGetir()																//Kim kazaniyor?
	{
		Koloni gezici = null;
		int canliSay = 0;
		for(int dongu = 0;dongu<this.koloniSayisi;dongu++)
		{
			gezici = this.koloniler.get(dongu);
			if(gezici.getNufus() != 0 && gezici.getErzak() != 0)
			{
				canliSay++;	
			}
			if(dongu == this.koloniSayisi-1)
			{
				for(int donguIc = 0;donguIc<this.koloniSayisi;donguIc++)
				{
					gezici = this.koloniler.get(donguIc);
					if (canliSay == 1)											//Son koloni tespit edilir.
					{
						if(gezici.getNufus() != 0 && gezici.getErzak() != 0)
						{
							System.out.printf("Kazanan koloni %s oldu!\n",gezici.getSembol());
						}
					}
					else													//Birden fazla ise henuz kazanan yok...
					{
						if(donguIc == this.koloniSayisi-1)
						{
							System.out.printf("Henuz kazanan belirsiz!\n") ;
						}
					}
				}
			}
		}
	}
	private void sabotajiKontrolEt(Koloni ilk,Koloni digeri)						//Sabotaj sartinin kontrolu...
	{
		if((ilk.getNufus()*4 > ilk.getErzak()) && (ilk.getNufus() > 10))
		{
			ilk.sabotajYap();
		}
		if((digeri.getNufus()*4 > digeri.getErzak()) && (digeri.getNufus() > 10))
		{
			digeri.sabotajYap();
		}
		if(ilk.getSavascilik() == digeri.getSavascilik())
		{
			while(ilk.getSavascilik() == digeri.getSavascilik()) 
			{
				ilk.setSavascilik(700);
				digeri.hucumYap();
			}
		}
	}
	private void savasSonuclandirma(Koloni ilk,Koloni digeri)						//Savas sonuclarinin gerceklenmesi...
	{
		int haracOrani = 0;
		int populasyonKaybi = 0;
		int populasyonYeni = 0;
		int erzakKontrolcusuHarac = 0;
		int erzakYenilen = 0;
		if(ilk.getSavascilik() > digeri.getSavascilik())							//ilk yenerse...
		{
			haracOrani = ((ilk.getSavascilik()-digeri.getSavascilik())*100)/1000;
			populasyonKaybi = ((digeri.getNufus()*haracOrani)/100);
			populasyonYeni = digeri.getNufus() - populasyonKaybi;
			erzakKontrolcusuHarac = (digeri.getErzak()*haracOrani)/100;
			erzakYenilen = digeri.getErzak()-erzakKontrolcusuHarac;
			if((populasyonYeni <= 1) || (erzakYenilen <= 1))					//Elenen koloni nitelikleri yok olur.
			{
				digeri.setNufus(0);
				digeri.setErzak(0);
				digeri.setKaybetme(0);
				digeri.setKazanma(0);
				ilk.setyokEttigiKoloniSayisi(ilk.getyokEttigiKoloniSayisi()+1);				
			}
			else
			{
				digeri.setNufus(populasyonYeni);
				digeri.setErzak(erzakYenilen);
				ilk.setErzak(ilk.getErzak()+erzakKontrolcusuHarac);
				digeri.setKaybetme(digeri.getKaybetme()+1);
				ilk.setKazanma(ilk.getKazanma()+1);	
			}
		}		
		else if(ilk.getSavascilik() < digeri.getSavascilik())						//Digeri yenerse...
		{
			haracOrani = ((digeri.getSavascilik()-ilk.getSavascilik())*100)/1000;
			populasyonKaybi = (ilk.getNufus()*haracOrani)/100;
			populasyonYeni = ilk.getNufus() - populasyonKaybi;
			erzakKontrolcusuHarac = (ilk.getErzak()*haracOrani)/100;
			erzakYenilen = ilk.getErzak()-erzakKontrolcusuHarac;
			if((populasyonYeni <= 1) || (erzakYenilen <= 1))						//Elenen koloni nitelikleri yok olur.
			{
				ilk.setNufus(0);
				ilk.setErzak(0);
				ilk.setKaybetme(0);
				ilk.setKazanma(0);			
				digeri.setyokEttigiKoloniSayisi(digeri.getyokEttigiKoloniSayisi()+1);				
			}
			else
			{
				ilk.setNufus(populasyonYeni);
				ilk.setErzak(erzakYenilen);
				digeri.setErzak(digeri.getErzak()+erzakKontrolcusuHarac);
				ilk.setKaybetme(ilk.getKaybetme()+1);
				digeri.setKazanma(digeri.getKazanma()+1);	
			}
		}
	}
	private void berbaerlikKontrol(Koloni ilk,Koloni digeri)					//Beraberlik durumunda uygulanacak metod...
	{
		if(ilk.getSavascilik() == digeri.getSavascilik())
		{
			while(ilk.getSavascilik() == digeri.getSavascilik())
			{
				ilk.setSavascilik(700);										//700 degeri hucum taktigine gore %50 sansla kazanilabilecek bir degerdir.
				ilk.setSavascilik(ilk.getSavascilik()+3);					// Dengesizlik yaratilir.
				digeri.hucumYap();
			}
		}
	}
    public void turAtla()////////////////     Uretim, tuketim, ureme ve savasma islemleri tur icinde yapilir. Savasma islemleri yapilirken yardimci metodlar kullanilir. Her islemde koloni varliklari niteliklerinin
    {					////////////////		0 olup olmamasina gore kontrol edilir.
    	//ERZAK URETIMI
		Koloni koloniTutucuEU = null;
    	for(int erzakUretimIndeks = 0; erzakUretimIndeks < this.getKoloniSayisi();erzakUretimIndeks++)
    	{
    		koloniTutucuEU = this.koloniler.get(erzakUretimIndeks);
        	if(koloniTutucuEU.getNufus() < 1)						//Koloni kontrol
        	{
        		koloniTutucuEU.setNufus(0);
        		koloniTutucuEU.setErzak(0);
        		koloniTutucuEU.setKaybetme(0);
        		koloniTutucuEU.setKazanma(0);
        		continue;
        	}
        	else if(koloniTutucuEU.getNufus()>0 && koloniTutucuEU.getNufus()<20)
        	{
        		koloniTutucuEU.avYap();
        	}
    		else if(koloniTutucuEU.getNufus() >= 20 && koloniTutucuEU.getNufus()<100)
    		{
    			koloniTutucuEU.cobanlikYap();
    		}
    		else if(koloniTutucuEU.getNufus() >= 100)
    		{
    			koloniTutucuEU.tarimYap();
    			if(this.turSayisi%10 == 0)										//
    			{																//10 turda bir tarimcilar kitlik yasar ve 1 erzak kazanabilir.
    				koloniTutucuEU.setErzak(koloniTutucuEU.getErzak()+1);		//
    			}	
    		}
    	}
    	//ERZAK TUKETIMI
    	Koloni koloniTutucuET = null;
    	for(int erzakTuketimIndeks = 0; erzakTuketimIndeks < this.getKoloniSayisi(); erzakTuketimIndeks++)
    	{
    		koloniTutucuET = this.koloniler.get(erzakTuketimIndeks);
    		if(koloniTutucuET.getNufus() <= 0)					//Koloni kontrol
    		{
    			koloniTutucuET.setNufus(0);
    			koloniTutucuET.setErzak(0);
    			koloniTutucuET.setKaybetme(0);
    			koloniTutucuET.setKazanma(0);
    			continue; 
    		}
    		int mevcutErzak = koloniTutucuET.getErzak();
    		int harcanacakErzak = koloniTutucuET.getNufus()*2;
    		int kalanErzak = mevcutErzak-harcanacakErzak;
    		if(mevcutErzak <= 0)									//Koloni kontrol
    		{
    			koloniTutucuET.setNufus(0);
    			koloniTutucuET.setErzak(0);
    			koloniTutucuET.setKaybetme(0);
    			koloniTutucuET.setKazanma(0);
    			continue; 
    		}
    		if(kalanErzak <= 0)									//Koloni kontrol
    		{
    			koloniTutucuET.setNufus(0);
    			koloniTutucuET.setErzak(0);
    			koloniTutucuET.setKaybetme(0);
    			koloniTutucuET.setKazanma(0);
    		}
    		else
    		{
    			koloniTutucuET.setErzak(kalanErzak);				//Koloni yasiyorsa erzak tuketir.
    		}		
    	}
    	//NUFUS ARTISI
		Koloni koloniTutucuNA = null;
		int artis = 0;
    	for(int nufusArtisIndeks = 0; nufusArtisIndeks < this.getKoloniSayisi(); nufusArtisIndeks++)
    	{
    		koloniTutucuNA = this.koloniler.get(nufusArtisIndeks);
    		artis = (koloniTutucuNA.getNufus()*20)/100;							//Koloniler yasiyorsa nufuslarinin yuzde 20 si kadar cogalirlar.
    		if(koloniTutucuNA.getNufus() > 0)									//Koloni kontrol
    		{     			
    			koloniTutucuNA.setNufus(koloniTutucuNA.getNufus()+artis); 
    		}		
    	}   	
    	//SAVASLAR
    	Koloni koloniTutucuSLDR = null;
    	for(int saldiran = 0; saldiran<this.getKoloniSayisi();saldiran++)
    	{
    		koloniTutucuSLDR = this.koloniler.get(saldiran);
    		if(koloniTutucuSLDR.getNufus() < 1 || koloniTutucuSLDR.getErzak() < 1) //Koloni kontrol
    		{
    			continue; 
    		}
    		if(saldiran == this.getKoloniSayisi()-1 )	//Dongunun hatali calismasini engellemek icin...
    		{
    			continue;
    		}
    		Koloni koloniTutucuSV = null;
    		for(int savunan = saldiran+1; savunan<this.getKoloniSayisi();savunan++)		//Ic ıce 2 dongu kullaniminda ilk indeks ikinci indeksten 1 azdir. Kolonilerin varligi kontrol edilir ve koloni indeksleri birer
    		{																			// kez savasacak sekilde denk gelir.
    			koloniTutucuSV = this.koloniler.get(savunan);
        		if(koloniTutucuSV.getNufus() < 1 || koloniTutucuSV.getErzak() < 1)
        		{
        				continue; 
        		}
        		if(koloniTutucuSLDR.getNufus() < 1 || koloniTutucuSLDR.getErzak() < 1)	//Ilk indeksteki koloni yok olursa ilk indeks tekrar secilmeli... (Bunu cok gec akil ettim.)
        		{
        			break; 
        		}
    			int birBucukKatiSLDR = (koloniTutucuSLDR.getNufus()*150)/100;			// Kendisinden cok buyuk veya biraz buyuk olma kontrolu 1.5 kat ile degerlendirilir...
    			int birBucukKatiSV = (koloniTutucuSV.getNufus()*150)/100;
    			if(koloniTutucuSLDR.getNufus() == koloniTutucuSV.getNufus())																// Sartlara gore savas fonksiyonlarinin cagrilmasi
    			{																															// esitlikte hucum,
    				koloniTutucuSLDR.hucumYap();																							//	
    				koloniTutucuSV.hucumYap();																								//	orta-kucuk de vurkac
    			}																															//
    			else if(koloniTutucuSLDR.getNufus() < koloniTutucuSV.getNufus() && birBucukKatiSLDR >= koloniTutucuSV.getNufus())			//	buyuk kucukte hucum-pusu
    			{																															//
    				koloniTutucuSLDR.vurkacYap();																							//
    				koloniTutucuSV.hucumYap();																								//
    			}																															//
    			else if(koloniTutucuSLDR.getNufus() < koloniTutucuSV.getNufus() && birBucukKatiSLDR <= koloniTutucuSV.getNufus())			//
    			{																															//
    				koloniTutucuSLDR.pusuYap();																								//
    				koloniTutucuSV.hucumYap();																								//																								
    			}																															//
    			else if(koloniTutucuSLDR.getNufus() > koloniTutucuSV.getNufus() && koloniTutucuSLDR.getNufus() <= birBucukKatiSV)			//
    			{																															//
    				koloniTutucuSLDR.hucumYap();																							//	
    				koloniTutucuSV.vurkacYap();																								//	
    			}																															//
    			else if(koloniTutucuSLDR.getNufus() > koloniTutucuSV.getNufus() && koloniTutucuSLDR.getNufus()  >= birBucukKatiSV)			//
    			{																															//
    				koloniTutucuSLDR.hucumYap();																							//	
    				koloniTutucuSV.pusuYap();																								//	
    			}																															//
				berbaerlikKontrol(koloniTutucuSLDR,koloniTutucuSV); 		//Gucler esit mi ?
				sabotajiKontrolEt(koloniTutucuSLDR,koloniTutucuSV);			//Savastan once kolonilerin sabotaj yapip yapmayacaklari kontrol edilir
				savasSonuclandirma(koloniTutucuSLDR,koloniTutucuSV);		//Savas basina savas sonuclandirma islemi yapilir
    		}
    	}
    	yokOlmusKolonileriSay();											//	Tur sonunda yok olan koloni sayimi
    	this.turSayisi++;													// Tur bitince tur sayisi artar
    }
    @Override
    public String toString()
    {
    	String tablo = "--------------------------------------------------------------------------------";
    	tablo += "\nTur: "+turSayisi+"\n";
    	tablo += "Koloni  Populasyon  Yemek Stogu   Kazanma+Yok etme       Kaybetme";
    	for(Koloni numara : koloniler )
    	{
    		tablo += "\n"+numara.toString();
    	}
    	tablo += "\n--------------------------------------------------------------------------------";
    	return tablo;
    }

	public int getKoloniSayisi() 
	{
		return koloniSayisi;
	}
}
