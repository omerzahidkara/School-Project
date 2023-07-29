/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class UretimHayvancilik extends Uretim
{
	int mahsul;
	public UretimHayvancilik()
	{
		uret();
	}
	public int uret()
	{
		Random random = new Random();
		mahsul = random.nextInt(4)+3;
		return mahsul;
	}
}
