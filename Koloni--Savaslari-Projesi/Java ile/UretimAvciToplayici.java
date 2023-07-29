/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class UretimAvciToplayici extends Uretim
{
	int mahsul;
	public UretimAvciToplayici()
	{
		uret();
	}
	public int uret()
	{
		Random random = new Random();
		mahsul = random.nextInt(3)+1;
		return mahsul;
	}
}
