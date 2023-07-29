/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class TaktikVurkac extends Taktik
{
	Random random = new Random();
	int guc;
	int rastgeleSayi;
	public TaktikVurkac()
	{		
		savas();
	}
	public int savas()
	{
		guc = random.nextInt(500)+200;
		return guc;
	}
}
