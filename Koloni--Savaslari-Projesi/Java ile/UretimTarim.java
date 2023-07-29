/**
 * @author Omer Zahid Kara G191210070 2/C
 */
package KoloniOdeviJava;
import java.util.Random;

public class UretimTarim extends Uretim
{
	int mahsul;
	public UretimTarim()
	{
		uret();
	}
	public int uret()
	{
		Random random = new Random();
		mahsul = random.nextInt(5)+6;
		return mahsul;
	}
}
