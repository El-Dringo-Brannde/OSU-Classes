package Brandon_Dominion;

import static org.junit.Assert.*;

import org.junit.Test;

public class DeckTest {

	@Test
	public void testBuildActionDeck() {
		Deck.Build_Action_Deck(); //make sure that 13 different piles were created
		
		String[] CardNames = {"Adventurer", "Ambassador", "Baron","CouncilRoom", "CutPurse",
	    		"Embargo","Feast","Garden","GreatHall","Mine","Village","Workshop","Market"};
	    int CardCosts[] = {6,3,4,5,4,2,4,4,3,5,3,3,5}; //corresponds with Card cost values
	    int VictoryPoints[] = {0,0,0,0,0,0,0,0,1,0,0,0,0}; // Victory Point values
	    
	    
		assertEquals(Deck.getActionDeck().size(), 13);
		
		for (int i = 0; i < 13; i++) {// make sure there are 10 copies of each action card
			assertEquals(Deck.getActionDeck().get(i).size(), 10);
			assertEquals(Deck.getActionDeck().get(i).get(0).toString(),
					CardNames[i] + " " + CardCosts[i] + " " + VictoryPoints[i] + " " + "Action"+ " false");
		}
	}
	
	@Test
	public void testBuildMV(){ // this could use some more work
		Deck.Build_Money_Victory();
		assertEquals(Deck.getMoneyDeck().size(), 3);
		assertEquals(Deck.curseCards.size(), 10);
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
