package dominion;

import static org.junit.Assert.*;

import org.junit.Test;

public class playDominionTest {

	//KEEP GETTING ERRORS ABOUT INDEX OUT OF RANGE
	@SuppressWarnings("static-access")
	public void cleanPiles(){
		for(int i = 0; i < 13; i++) // clear out action card pile
			PlayDominion.AllDecks.getActionDeck().get(i).clear();
		PlayDominion.AllDecks.getActionDeck().clear();
		for(int i = 0; i < 4; i++) // clear out VC card pile
			PlayDominion.AllDecks.getVCDeck().get(i).clear();
		PlayDominion.AllDecks.getVCDeck().clear();
		for(int i = 0; i < 3; i++) // clear out VC card pile
			PlayDominion.AllDecks.getMoneyDeck().get(i).clear();
		PlayDominion.AllDecks.getMoneyDeck().clear();
	}
	@Test
	public void testCheckEmptyPile(){
		PlayDominion.Initialize_Game();
		Deck.getActionDeck().get(0).clear();
		assertEquals(PlayDominion.CheckifPileIsEmpty(0),true);
	}

	@Test
	public void testCheckMoneyPile(){
		Deck.Build_Money_Victory();
		assertEquals(PlayDominion.CheckMoneyPile(0),false);
		Deck.getMoneyDeck().get(0).clear();
		assertEquals(PlayDominion.CheckMoneyPile(0),true);

		for(int i = 0; i < 3; i++)
			Deck.getMoneyDeck().get(i).clear();
		for(int i = 0; i < 4; i++)
			Deck.getVCDeck().get(i).clear();

		Deck.getMoneyDeck().clear();
		Deck.getVCDeck().clear();
	}


	@Test
	public void testPlay(){
		String [] args = new String[2];
		args[0] = "Hello";
		args[1] = "world";
		PlayDominion.main(args);
	}

}
