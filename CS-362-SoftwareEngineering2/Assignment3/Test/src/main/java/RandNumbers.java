package dominion;
import java.util.Random;

class RandNumbers{
	public static int getRand(int deck_size){
		Random r = new Random();
		return (r.nextInt(deck_size));
	}

}