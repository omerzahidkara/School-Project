/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class TaktikPusu extends Taktik
{
	Random random = new Random();
	int guc;
	int rastgeleSayi;
	public TaktikPusu()
	{		
		savas();
	}
	public int savas()
	{
		guc = random.nextInt(501);
		return guc;
	}
}
