package Dominion;

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
		assertEquals(PlayDominion.CheckifPileIsEmpty(0), false);
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
	public void testInitGame() {
		assertEquals(PlayDominion.p1.get_Player_Gold(), 7);
		assertEquals(PlayDominion.p2.get_Player_Gold(), 7);
		assertEquals(PlayDominion.p1.Get_Player_VP(), 3);
		assertEquals(PlayDominion.p2.Get_Player_VP(), 3);
		assertEquals(PlayDominion.p1.get_PlayHand().size(), 5);
		assertEquals(PlayDominion.p2.get_PlayHand().size(), 5);
		assertEquals(Deck.getActionDeck().size(), 13);
		assertEquals(Deck.getMoneyDeck().size(), 3);
		assertEquals(Deck.getVCDeck().size(), 4);
		assertEquals(PlayDominion.p1.GetDeck().size(), 5);
		assertEquals(PlayDominion.p2.GetDeck().size(), 5);
	}
	
	@SuppressWarnings("static-access")
	@Test 
	public void testEndGame(){
		Deck.Build_Money_Victory();
		assertEquals(PlayDominion.CheckEndGame(), false);
		Deck.getVCDeck().get(2).clear();
		assertEquals(PlayDominion.CheckEndGame(),true); //Tests to see if game ends when Provinces are gone
		
		for(int i = 0; i < 4; i++)
			Deck.getVCDeck().get(i).clear();
		Deck.getVCDeck().clear();
		Deck.Build_Money_Victory();
		
		assertEquals(PlayDominion.CheckEndGame(), false);
		
		PlayDominion.AllDecks.Build_Action_Deck();
		
		for (int i = 0; i < 3; i++)
			PlayDominion.AllDecks.getActionDeck().get(i).clear(); //remove three action card piles 
		assertEquals(PlayDominion.CheckEndGame(),true);
		
		cleanPiles();
	}
	
	@Test
	public void testPlay2(){
		PlayDominion.AllDecks.Build_Action_Deck();
		PlayDominion.AllDecks.Build_Money_Victory();
		
		cleanPiles();
	}
	


}
