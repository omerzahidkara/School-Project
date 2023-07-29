package KoloniOdeviJava;


import java.io.IOException;

/**
 * 
 * @author Omer Zahid Kara
 */
public class Console 
{
	public static void clear()
	{
		try
		{
			if(System.getProperty("os.name").contains("Windows"))
			{
				new ProcessBuilder("cmd","/c","cls").inheritIO().start().waitFor();
			}
			else
			{
				Runtime.getRuntime().exec("clear");
			}
		}
		catch(IOException | InterruptedException ex)
		{
			
		}
	}
}
