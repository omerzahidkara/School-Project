/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class TaktikTopluHucum extends Taktik
{
	Random random = new Random();
	int guc;
	int rastgeleSayi;
	public TaktikTopluHucum()
	{		
		savas();
	}
	public int savas()
	{
		guc = random.nextInt(601)+400;
		return guc;
	}
}
