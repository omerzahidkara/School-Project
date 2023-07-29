/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;

public class Koloni  
{
	private String sembol;
	private int nufus;
	private int erzak;
	private int kazanmaSayisi = 0;
	private int kaybetmeSayisi = 0;
	private int savasmaEtkisi = 0;
	private int yokEttigiKoloniSayisi = 0;
	public Koloni(String sembol,int nufus,int erzak)
	{
		this.sembol = sembol;
		this.setNufus(nufus);
		this.setErzak(erzak);
	}
	@Override
	public String toString()
	{
		char arti = '+';
		String satir = String.format("%-10s %-10d %-15d %-2d %-2c %-17d %-10d", this.getSembol(), this.getNufus(), this.getErzak(), this.getKazanma(),arti, this.getyokEttigiKoloniSayisi(),this.getKaybetme());
		return satir;
	}	
	public int getyokEttigiKoloniSayisi() 											// KOLONIYE AIT GEREKLI GET-SET FONKSIYONLARI
	{
		return yokEttigiKoloniSayisi;												// URETIM VE TAKTIK FONKSYIONLARI
	}
	public void setyokEttigiKoloniSayisi(int yokEttigiKoloniSayisi) 
	{
		this.yokEttigiKoloniSayisi = yokEttigiKoloniSayisi;
	}
	public String getSembol()
	{
		return sembol;
	}
	public int getNufus() 
	{
		return nufus;
	}
	public void setNufus(int nufus) 
	{
		this.nufus = nufus;
	}
	public int getErzak() 
	{
		return erzak;
	}
	public void setErzak(int erzak) 
	{
		this.erzak = erzak;
	}
	public int getKazanma() 
	{
		return kazanmaSayisi;
	}
	public void setKazanma(int zafer) 
	{
		this.kazanmaSayisi = zafer;
	}
	public int getKaybetme() 
	{
		return kaybetmeSayisi;
	}
	public void setKaybetme(int yenilgi) 
	{
		this.kaybetmeSayisi = yenilgi;
	}
	public void avYap()
	{
		UretimAvciToplayici av = new UretimAvciToplayici();
		this.erzak += av.uret();
	}
	public void cobanlikYap()
	{
		UretimHayvancilik coban = new UretimHayvancilik();
		this.erzak += coban.uret();
	}
	public void tarimYap()
	{
		UretimTarim ciftci = new UretimTarim();
		this.erzak += ciftci.uret();
	}
	public int getSavascilik() 
	{
		return this.savasmaEtkisi;
	}
	public void setSavascilik(int avantaj) 
	{
		this.savasmaEtkisi = avantaj;
	}
	public void pusuYap()
	{
		TaktikPusu ceteci = new TaktikPusu();
		this.savasmaEtkisi = ceteci.savas();
	}
	public void sabotajYap()
	{
		TaktikSabotaj ajan = new TaktikSabotaj();
		this.savasmaEtkisi = ajan.savas();
	}
	public void hucumYap()
	{
		TaktikTopluHucum ordu = new TaktikTopluHucum();
		this.savasmaEtkisi = ordu.savas();
	}
	public void vurkacYap()
	{
		TaktikVurkac atliOkcu = new TaktikVurkac();
		this.savasmaEtkisi = atliOkcu.savas();
	}
}
