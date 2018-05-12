package dominion;

import static org.junit.Assert.*;

import org.junit.Test;

public class DeckTest {


	@Test
	public void testBuildMV(){ // this could use some more work
		Deck.Build_Money_Victory();
		assertEquals(Deck.getMoneyDeck().size(), 3);
		assertEquals(Deck.getMoneyDeck().get(0).size(), 60);
		assertEquals(Deck.getMoneyDeck().get(1).size(), 40);
		assertEquals(Deck.getMoneyDeck().get(2).size(), 30);

	}

	@Test
	public void testGetAction(){
		assertEquals(Deck.getActionDeck(), Deck.getActionDeck());
	}

	@Test
	public void testMoney(){
		assertEquals(Deck.getMoneyDeck(),Deck.getMoneyDeck());
	}
	@Test
	public void testVC(){
		assertEquals(Deck.getVCDeck(),Deck.getVCDeck());
	}
}
