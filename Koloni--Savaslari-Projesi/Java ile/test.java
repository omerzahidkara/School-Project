/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.io.IOException;
import java.util.Scanner;
/*While dongusu ile menuye girilir,
 * Oyun nesnesi oyunu baslatir baslatmaz kullanicidan sayi istenir.
 *  Sayilar alininca koloni yapıları nufusariyla olusur ve nitelikleri varsayilan kurallara gore atanir. (erzak = nufus*nufus) (sembol: rastgele)
 *  Tur atlatilmasi icin kullanicidan enter tuslamasi istenir.
 *  Tur sirasinda koloniler uretim, tuketim, populasyon artisi islemlerini gerceklestirir ve var olan koloniler birbirleriyle savasir.
 *  Savaslara gore kazanma kaybetme skorlari guncellenir. Koloniler nufuslarina gore uretim politikalarini belirlerler.
 *  1-20 nufuslu koloni avci toplayici bir kolonidir ve az urun kazanir. 20-100 hayvancilik yapar ve orta halli mahsul edinir.100+ tarim toplumuna gecer ve 
 *  yuksek mahsul kazanir fakat 10 turda bir kitlik oldugu icin 1 kazanir.
 *  Koloniler savasacaklari dusmanlarina gore veya erzak-nufus durumlarina gore 4 cesit farkli taktik arasindan tercih yapar.
 *  Pusu taktigi kendisine gore cok kalabalik bir dusmana karsi tercih edilir ve sansi dusuktur.
 *  Vurkac taktigini kendisinden buyuk ama yakin nufusta olan koloniye karsi tercih eder.
 *  Kendisinden kucuk veya esit bir dusmana karsi topluca hucum etme taktigi yaparlar.
 *  Ayrica erzaklari cok azalmis koloniler sabotaj taktigi yaparak yuksek riskli bir taktik dener.
 *  Koloniler erzaklari ve nufuslari kalmadikca elenir.
 *  Tur gerceklesirken yok olan koloni eger bir koloni tarafindan yok edildiyse konsolda bunun istatistigi de gosterilir. Yok olan koloni diger kolonilerle savasmayacaktir. Bu yuzden her koloni ayni sayida savasmaz.
 *  Sona kalan koloni oyunun kazani olur.
 */
 
public class test {

	public static void main(String[] args) throws InterruptedException, IOException 
	{
		Scanner scannerTest = new Scanner(System.in);	// Konsolu temizlemeyle ilgili bir hata aliyordum dolayisiyla birden fazla scanner kullanmayi denedim.
		Scanner scanner2Test = new Scanner(System.in);	// Hata o yuzden mi halen bilmiyorum :D 
		Scanner scanner3Test = new Scanner(System.in);	// Sanirim o yuzden cunku duzeldi.
		
		char islemKararci = 'e';						//Tekrar oynama imkani veren menu yapmak istedim,
		char islemKararci2 = 'e';						// Menuyu yoneten 2 adet char tipi sart degiskenleri ayarladim. 2 adet olma sebebi evet veya hayir disinda komut verilirse uyari verebilemsi icin.
														//	Ana islem yapilmadan dongu donmesini saglamak icin islemKararci sarti false yapilirken ana menu sarti true yapilir. Boylece uyari tekrar edilebilir.

		while (islemKararci2 == 'e')									
		{
			if (islemKararci == 'e')
			{
				Oyun yeniOyun = new Oyun();
				while(true)
				{
					System.out.println(yeniOyun);
					if(yeniOyun.getKalanKoloniSayisi() == 1)   					//Son koloni kalirsa oyun biter ve ana menu sorgusu gerceklesir.
					{															//
						yeniOyun.kazananiGetir();								//
						scannerTest.nextLine();									//
						Console.clear();										//
						break;													//
					}
					else
					{
						yeniOyun.turAtla();										//Oyun bitmezse turlar devam eder.
						if(yeniOyun.getKalanKoloniSayisi() != 2)				//Son iki koloni kalinca ona ozel uyari verilir.
						{														//
							yeniOyun.kazananiGetir();							//2 den fazla koloni varken kazananin belli olmadigi mesaji veirlir.
						}
						if(yeniOyun.getKalanKoloniSayisi() == 2)
						{
							System.out.printf("Son iki koloni kaldi\n");
						}
						System.out.printf("Diger tur icin enter...\n");
						scanner2Test.nextLine();
						Console.clear();
						yeniOyun.setKalanKoloniSayisi();						// Tur bitisinde kalan koloniler hesaplanir.
					}
				}
				islemKararci2 = 'a';
			}
			else if (islemKararci == 'h')
			{
				break;
			}
			else
			{
				System.out.printf("Yanlış karakter girdiniz!Evet için e, hayır için h tuşlayınız.\n");		//e veya h girilerek ana menude kara verilir.
			}
			System.out.printf("\nTekrar oynamak ister misiniz?(e/h): ");
			islemKararci = scanner3Test.next().charAt(0);
			Console.clear();
			if (islemKararci == 'e')				//oyun islemi karari e
			{										//
				islemKararci2 = 'e';				//menu dongusu karari e
			}
			else if (islemKararci == 'h')			//oyun islemi iptal
			{										//
				islemKararci2 = 'a';				//donguden cikilir, program sona erer
			}
			else
			{										//yanlis karakter girilirse
				islemKararci = 'c';					// oyun islemi yapilmaz
				islemKararci2 = 'e';				// dongu devam eder ve devamlilik karakeri tekrar istenir
			}
		}
		scannerTest.close();
		scanner2Test.close();
		scanner3Test.close();
	}
}
