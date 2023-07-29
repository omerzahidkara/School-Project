/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class TaktikSabotaj extends Taktik
{
	Random random = new Random();
	int guc;
	int rastgeleSayi;
	public TaktikSabotaj()
	{		
		savas();
	}
	public int savas()
	{
		int kahramaninSansi = random.nextInt(4);
		if(kahramaninSansi == 0)
		{
			guc = random.nextInt(101);
		}
		else if(kahramaninSansi == 1)
		{
			guc = random.nextInt(201)+200;
		}
		else if(kahramaninSansi == 2)
		{
			guc = random.nextInt(101)+300;
		}
		else if(kahramaninSansi == 3 )
		{
			guc = random.nextInt(251)+750;
		}
		else
		{
			guc = random.nextInt(101);
		}
		return guc;
	}
}
