package Dominion;
import java.util.*;

import static org.junit.Assert.*;

import org.junit.Test;

import Dominion.Cards;
import Dominion.Deck;
import Dominion.Player;

public class playerTest {

	@Test
	public void testSafeDraw() {
		Player p = new Player("p1");
		Deck.Build_Action_Deck();
		int pa = p.safeActionDraw();
		System.out.println("SAFE ACTION DRAW \n\n\n" + Deck.getActionDeck().size());
		assertTrue(pa <= 14); //make sure that it is drawing within range
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
		Player p = new Player("p1");
		Cards Copper; 
		for (int i = 0; i < 5; i++){			
			Copper = new Cards("Copper",1,0, "Money",false);	
			p.get_PlayHand().add(Copper);
		}
		assertEquals(p.Get_player_gold_in_hand(),5);
		p.PayPiper(5);
		assertEquals(p.Get_player_gold_in_hand(),0);
		
		for (int i = 0; i < 4; i++){	//NOT COPPER SILVER		
			Copper = new Cards("Silver",2,0, "Money",false);	
			p.get_PlayHand().add(Copper);
		}
		assertEquals(p.Get_player_gold_in_hand(),8);
		p.PayPiper(8);
		assertEquals(p.Get_player_gold_in_hand(),0);
		
		for (int i = 0; i < 4; i++){	//NOT COPPER GOLD
			Copper = new Cards("Gold",6,0, "Money",false);	
			p.get_PlayHand().add(Copper);
		}
		assertEquals(p.Get_player_gold_in_hand(),12);
		p.PayPiper(12);
		assertEquals(p.Get_player_gold_in_hand(),0);
	}
	
	
	@Test 
	public void testPlayStats(){
		Player p = new Player("p1");
		Cards c, v; 
		assertEquals(p.get_Player_Gold(),0);
		
		p.get_PlayHand().add(c = new Cards("Copper",0,1,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),1);
		
		p.get_PlayHand().add(c = new Cards("Silver",3,2,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),3);
		
		p.get_PlayHand().add(c = new Cards("Gold",6,3,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),6);
		
		p.GetDeck().add(c = new Cards("Copper",0,1,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),7);		
		
		p.GetDeck().add(c = new Cards("Silver",3,2,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),9);		
		
		p.GetDeck().add(c = new Cards("Gold",6,3,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),12);
		
		p.getDiscard().add(c = new Cards("Copper",0,1,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),13);		
		
		p.getDiscard().add(c = new Cards("Silver",3,2,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),15);		
		
		p.getDiscard().add(c = new Cards("Gold",6,3,"Money",false));
		p.Get_Player_Stats();
		assertEquals(p.get_Player_Gold(),18);
		
		p.get_PlayHand().add(v = new Cards("Estate", 2, 1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(),1);
		
		p.get_PlayHand().add(v = new Cards("Duchy", 5, 3, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 4);

		p.get_PlayHand().add(v = new Cards("Province", 8, 6, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 10);
		
		p.GetDeck().add(v = new Cards("Estate", 2, 1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(),11);
		
		p.GetDeck().add(v = new Cards("Duchy", 5, 3, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 14);

		p.GetDeck().add(v = new Cards("Province", 8, 6, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 20);
		
		p.getDiscard().add(v = new Cards("Estate", 2, 1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(),21);
		
		p.getDiscard().add(v = new Cards("Duchy", 5, 3, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 24);

		p.getDiscard().add(v = new Cards("Province", 8, 6, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 30);
		
		p.get_PlayHand().add(v = new Cards("Curse", 0, -1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 29);
		
		p.GetDeck().add(v = new Cards("Curse", 0, -1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 28);
		
		p.getDiscard().add(v = new Cards("Curse", 0, -1, "Victory", false));
		p.Get_Player_Stats();
		assertEquals(p.Get_Player_VP(), 27);
	}
	
	@Test 
	public void testNewHand(){
		Cards c,d;
		Player p = new Player("p1");
		List<Cards> old = new ArrayList(); 
		p.get_PlayHand().clear();
		p.GetDeck().clear();
		for (int i = 0; i < 5; i++){
			c = new Cards("Gold",6,0, "Money",false);
			d = new Cards("Gold",6,0, "Money",false);
			p.get_PlayHand().add(c);
			old.add(d);
		}
		for (int i = 0; i < 4; i++)
			p.GetDeck().add(c = new Cards("Estate",0,1, "Victory",false));
		List<Cards> newer = new ArrayList();
		p.newHand();
		newer = p.get_PlayHand();
		assertFalse(old.equals(newer));	
	}
	
	@Test
	public void testAdventurer(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Cards c; 
		assertEquals(p1.GetDeck().size(),0);
		for (int i = 0; i < 2; i++)
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
		for (int i = 0; i < 3; i++)
			p1.GetDeck().add(c = new Cards("Estate",0,0,"Victory",false));
		c = new Cards("Adventurer",0,0,"Action",false);
		p1.Play_Card(c,p1,p2);

		assertEquals(p1.get_PlayHand().size(),2);
		assertEquals(p1.getDiscard().size(),3);
	}	
	
	@Test
	public void testAmbassador(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Cards c; 
		Deck.Build_Money_Victory();
		Deck.Build_Action_Deck();
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Copper",0,0,"Money",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Silver",0,0,"Money",false));
		c = new Cards("Ambassador",0,0,"Victory",false);
		assertEquals(p1.get_PlayHand().size(), 5);
		p1.Play_Card(c, p1, p2);
		assertFalse(p1.get_PlayHand().size() == 5);
		p1.get_PlayHand().clear();
		assertEquals(p2.GetDeck().size(),1);
		
		
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Duchy",0,0,"Victory",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Estate",0,0,"Victory",false));
		c = new Cards("Ambassador",0,0,"Victory",false);
		assertEquals(p1.get_PlayHand().size(), 5);
		p1.Play_Card(c, p1, p2);
		assertFalse(p1.get_PlayHand().size() ==  5);
		p1.get_PlayHand().clear();
		assertEquals(p2.GetDeck().size(),2);
		
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Garden",0,0,"Victory",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Mine",0,0,"Victory",false));
		c = new Cards("Ambassador",0,0,"Victory",false);
		assertEquals(p1.get_PlayHand().size(), 5);
		p1.Play_Card(c, p1, p2);
		assertFalse(p1.get_PlayHand().size() ==  5);
		p1.get_PlayHand().clear();
		assertEquals(p2.GetDeck().size(),3);
	}
	
	@Test 
	public void testBaron(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Cards c;
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Duchy",0,0,"Victory",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Estate",0,0,"Victory",false));
		c = new Cards("Baron",2,0,"Action",false); 
		Deck.Build_Action_Deck();
		Deck.Build_Money_Victory();
		p1.Play_Card(c, p1, p2);
		assertEquals(p1.get_PlayHand().size(), 6);
		p1.get_PlayHand().clear();
		
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Garden",0,0,"Victory",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Mine",0,0,"Victory",false));
		c = new Cards("Baron",2,0,"Action",false); 
		p1.Play_Card(c, p1, p2);
		assertEquals(p1.get_PlayHand().size(), 6);
	}
	
	@Test 
	public void testNewDeck(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Cards c;
		for (int i = 0; i < 2; i++){
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			p2.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
		}
		for (int i = 0; i < 3; i++){
			p1.GetDeck().add(c = new Cards("Estate",0,0,"Victory",false));
			p2.GetDeck().add(c = new Cards("Estate",0,0,"Victory",false));
		}
		p1.getNewDeck();
		assertFalse(p1.GetDeck().equals(p2.GetDeck()));
	}
	
	@Test 
	public void testCouncilRoom(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Cards c;
		for (int i = 0; i < 2; i++)
			p1.get_PlayHand().add(c = new Cards("Duchy",0,0,"Victory",false));
		for (int i = 0; i < 3; i++)
			p1.get_PlayHand().add(c = new Cards("Estate",0,0,"Victory",false));
		for (int i = 0; i < 5; i++)
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
		
		for (int i = 0; i < 3; i++)
			p2.GetDeck().add(c = new Cards("Estate",0,0,"Victory",false));
		
		c = new Cards("CouncilRoom",2,0,"Action",false);

		assertEquals(p1.get_PlayHand().size(), 5);
		assertEquals(p1.GetDeck().size(), 5);
			
		p1.Play_Card(c, p1, p2);
		assertEquals(p1.get_PlayHand().size(), 9);
		assertEquals(p1.GetDeck().size(), 1);
		assertEquals(p2.get_PlayHand().size(),1);
	}
	
	@Test 
	public void testCutPurse(){
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
		
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Deck.Build_Action_Deck();
		Deck.Build_Money_Victory();
		Cards c;
		for (int i = 0; i < 5; i++)
			p1.get_PlayHand().add(c = new Cards("Copper",0,0,"Money",false));
		for (int i = 0; i < 5; i++)
			p2.get_PlayHand().add(c = new Cards("Copper",0,0,"Money",false));
		c = new Cards("CutPurse",2,0,"Action",false);
		p1.Get_Player_Stats();
		assertEquals(p1.get_Player_Gold(),5);
		p2.Get_Player_Stats();
		assertEquals(p2.get_Player_Gold(),5);
		p1.Play_Card(c, p1, p2);
		p1.Get_Player_Stats();
		assertEquals(p1.get_Player_Gold(),7);
		
		p2.Get_Player_Stats();
		assertEquals(p2.get_Player_Gold(),4);
		
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
	}
	
	@Test 
	public void testEmbargo(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Deck.Build_Action_Deck();
		Deck.Build_Money_Victory();
		Cards c;
		c = new Cards("Embargo",2,0,"Action",false);
		
		p1.Play_Card(c, p1, p2);
		p1.Get_Player_Stats();
		assertEquals(p1.get_Player_Gold(),2);
		//Tested add Embargo and safe rand picker earlier. Assuming
		// that a loop works no need to go through a hassle of finding the deck with the token
		
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
	}
	
	@Test public void testFeast(){
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Deck.Build_Action_Deck();
		Deck.Build_Money_Victory();
		Cards c;
		c = new Cards("Feast",2,0,"Action",false);
		
		p1.Play_Card(c, p1, p2);
		assertEquals(p1.get_PlayHand().size(),1);
		for (int i = 0; i < 13; i++)
			Deck.getActionDeck().get(i).clear();
		Deck.getActionDeck().clear();
	}
	 @Test public void testGarden(){
			Player p1 = new Player("p1");
			Player p2 = new Player("p2");
			Deck.Build_Action_Deck();
			Deck.Build_Money_Victory();
			Cards c;

			for(int i = 0; i < 60; i++)
				p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Garden",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),63);
			p1.GetDeck().clear();
			for(int i = 0; i < 30; i++)
				p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Garden",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),35);
			
			
			p1.GetDeck().clear();
			for(int i = 0; i < 10; i++)
				p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Garden",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),16);
			
			
			for (int i = 0; i < 13; i++)
				Deck.getActionDeck().get(i).clear();
			Deck.getActionDeck().clear();
	 }
	 
	 @Test 
	 public void testGreatHall(){
		 Player p1 = new Player("p1");
			Player p2 = new Player("p2");
			Deck.Build_Action_Deck();
			Deck.Build_Money_Victory();
			Cards c;
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("GreatHall",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_PlayHand().size(),1);
	 }
	 @Test public void testMine(){
		 Player p1 = new Player("p1");
			Player p2 = new Player("p2");
			Deck.Build_Action_Deck();
			Deck.Build_Money_Victory();
			Cards c;
			for (int i = 0; i < 3; i++)
				p1.get_PlayHand().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Mine",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),4);
			p1.get_PlayHand().clear();
			for (int i = 0; i < 3; i++)
				p1.get_PlayHand().add(c = new Cards("Silver",0,0,"Money",false));
			c = new Cards("Mine",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),7);
	 }
	 
	 @Test public void testVillage(){
		 Player p1 = new Player("p1");
			Player p2 = new Player("p2");
			Deck.Build_Action_Deck();
			Deck.Build_Money_Victory();
			Cards c;
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Village",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			assertEquals(p1.get_PlayHand().size(),1);
	 }
	 
	 @Test public void testWorkshop(){
		Player p1 = new Player("p1");
		Player p2 = new Player("p2");
		Deck.Build_Action_Deck();
		Deck.Build_Money_Victory();
		Cards c = new Cards("Workshop",2,0,"Action",false);
		p1.Play_Card(c, p1, p2);
		assertEquals(p1.get_PlayHand().size(),1);
		assertTrue(p1.get_PlayHand().get(0).getCost() <= 4);
	 }
	 
	 @Test public void testMarket(){
			Player p1 = new Player("p1");
			Player p2 = new Player("p2");
			Deck.Build_Action_Deck();
			Deck.Build_Money_Victory();
			Cards c;
			p1.GetDeck().add(c = new Cards("Copper",0,0,"Money",false));
			c = new Cards("Market",2,0,"Action",false);
			p1.Play_Card(c, p1, p2);
			p1.Get_Player_Stats();
			assertEquals(p1.get_Player_Gold(),2);
	 }

}
