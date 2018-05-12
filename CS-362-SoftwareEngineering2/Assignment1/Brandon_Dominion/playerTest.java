package Brandon_Dominion;
import java.util.*;

import static org.junit.Assert.*;

import org.junit.Test;

public class playerTest {

	@Test
	public void testSafeDraw() {
		Player p = new Player("p1");
		Deck.Build_Action_Deck();
		assertTrue(p.safeActionDraw() < 13); //make sure that it is drawing within range
		for (int i = 0; i < 11; i++) // remove 12 cards so that it has to find the safe number 
			Deck.getActionDeck().get(i).clear();
		assertTrue(p.safeActionDraw() >= 11);
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
	}
	
	@Test 
	public void testGetPVP(){
		Player p = new Player("p1");
		assertEquals(p.Get_Player_VP(), 0); //get starting gold
	}
	
	@Test 
	public void testGetPGold(){
		Player p = new Player("p1");
		assertEquals(p.get_Player_Gold(), 0);
	}
	
	@Test 
	public void testGetDeck(){
		Player p = new Player("p1");
		Cards Copper, Estate; 
		for (int i = 0; i < 7; i++){			
			Copper = new Cards("Copper",1,0, "Money",false);	
			p.GetDeck().add(Copper);
		}
		List<Cards> Deck = new ArrayList<Cards>();
		for (int i = 0; i < 7; i++){
			Estate = new Cards("Copper",1,0, "Money",false); //Not estate didn't want to rename stuff
			Deck.add(Estate);
		}
		assertEquals(p.GetDeck().toString(), Deck.toString());	
	}
	
	
	@Test 
	public void testGetHand(){
		Player p = new Player("p1");
		Cards Copper, Estate; 
		for (int i = 0; i < 7; i++){			
			Copper = new Cards("Copper",1,0, "Money",false);	
			p.get_PlayHand().add(Copper);
		}
		List<Cards> Hand = new ArrayList<Cards>();
		for (int i = 0; i < 7; i++){
			Estate = new Cards("Copper",1,0, "Money",false); //Not estate didn't want to rename stuff
			Hand.add(Estate);
		}
		assertEquals(p.get_PlayHand().toString(), Hand.toString());
	}
	
	@Test 
	public void testHandToDiscard(){
		Player p = new Player("p1");
		p.get_PlayHand().add(new Cards("Junk",0,1,"Money",false));
		assertEquals(p.get_PlayHand().size(),1);
		assertEquals(p.getDiscard().size(),0);
		p.Hand_To_Discard(0);
		assertEquals(p.get_PlayHand().size(),0);
		assertEquals(p.getDiscard().size(),1);
	}
	
	@Test 
	public void testPayPiper(){	
	}
	
	 

}
