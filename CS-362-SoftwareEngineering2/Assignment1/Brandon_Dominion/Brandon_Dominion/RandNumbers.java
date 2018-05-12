package Brandon_Dominion;

import java.util.Random;

class RandNumbers{
	
	public static int getRand(int deck_size){
		Random r = new Random();
		return (r.nextInt(deck_size));
	}
	public static void main(String[] args){
		System.out.println(getRand(10));
	}
}