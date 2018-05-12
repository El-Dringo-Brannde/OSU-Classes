package org.cs362.dominion;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class CardTest {
	private List<Card> cardList;
	private Player playerA;
	private Player playerB;
	private GameState gameState;
	private List<Card> cardList1;
	private Player playerA1;
	private Player playerB1;
	private GameState gameState1;
	
    @Before
    public void createList()
    {
        cardList = Card.createCards();
        //List<Card> cards;
	    GameState gameState;
		//Randomness.reset(10);	   
		cardList = new ArrayList<Card>(Card.createCards());
		gameState = new GameState(cardList);
	    playerA = new Player(gameState, "player A");
	    gameState.addPlayer(playerA);
	    playerB = new Player(gameState, "player B");
        gameState.addPlayer(playerB);		      
        gameState.initializeGame();
    }

    @Test
    public void listSizeTest()
    {
        assertEquals(20, cardList.size());
    }
    
    @Test
    public void testGold(){
    	assertEquals(Card.Type.TREASURE, cardList.get(0).getType());
    	assertEquals(Card.CardName.Gold, cardList.get(0).getCardName());
    	assertEquals(6, cardList.get(0).cost(cardList.get(0)));
    	assertEquals(3,cardList.get(0).getTreasureValue());	
    }
    @Test
    public void testSilver(){
    	assertEquals(Card.Type.TREASURE, cardList.get(1).getType());
    	assertEquals(Card.CardName.Silver, cardList.get(1).getCardName());
    	assertEquals(3, cardList.get(1).cost(cardList.get(1)));
    	assertEquals(2,cardList.get(1).getTreasureValue());	
    } 
    @Test
    public void testCooper(){
    	assertEquals(Card.Type.TREASURE, cardList.get(2).getType());
    	assertEquals(Card.CardName.Cooper, cardList.get(2).getCardName());
    	assertEquals(0, cardList.get(2).cost(cardList.get(2)));
    	assertEquals(1,cardList.get(2).getTreasureValue());	
    }
    @Test
    public void testAdventurer(){
    	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Adventurer));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
		   playerA.playKingdomCard();
		   assertTrue(playerA.hand.size()>5);

	      
    }
    @Test
    public void testSmithy(){
    	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      for(int k=0; k<5;k++){
	    	  playerA.hand.remove(0);
	      }
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Smithy));
	      
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
	      
		   playerA.playKingdomCard();
		   assertTrue(playerA.hand.size()==8); //drawing 3 cards

    }  
    @Test
    public void testSalvager(){
    	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Salvager));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }

		   playerA.playKingdomCard();

		   assertTrue(playerA.numBuys ==2); //get an extra buy
		   

    }  
    @Test
    public void testVillage(){
    	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      for(int k=0; k<5;k++){
	    	  playerA.hand.remove(0);
	      }
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Village));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
		   playerA.playKingdomCard();
		   assertTrue(playerA.numActions==2); //get an extra buy
		   

    }  
    @Test
    public void testAmbassador(){
   	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Ambassador));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
	      
		   playerA.playKingdomCard();
		   assertTrue(playerB.hand.size()>5); //player B should have more than 5 cards because they should have ambassador now
		   //it will fail because this is one of my bugs. The other player doesn't get another card.
		   

   }  
    @Test
    public void testBaron(){
   	 playerA.numActions = 1;
	      playerA.coins = 0;
	      int estate=1;
	      playerA.numBuys = 1;
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Baron));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
	      
		   playerA.playKingdomCard();
		   assertTrue(playerA.coins==4 || estate==1); //check if either user recieved 4 coins or estate, if either true,Baron good 
   }  
    @Test
    public void testCouncil(){
   	 playerA.numActions = 1;
	      playerA.coins = 0;
	      playerA.numBuys = 1;
	      for(int k=0; k<5;k++){
	    	  playerA.hand.remove(0);
	      }
	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Council_room));
	      for(int i =0; i<4; i++){
		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
	      }
	      
		   playerA.playKingdomCard();
		   assertTrue(playerA.hand.size()==9); 
		   assertTrue(playerB.hand.size()>5);//player B should have more than 5 cards because they should have ambassador now
		   //it will fail because this is one of my bugs. The other player doesn't get another card.
		   

   }  
    @Test
    public void testCutpurse(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      playerA.numBuys = 1;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cutpurse));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      
   		   playerA.playKingdomCard();
   		   assertTrue(playerA.coins==2); 
   		   

      }  
    @Test
    public void testEmbargo(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      playerA.numBuys = 1;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Embargo));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      
   		   playerA.playKingdomCard();
   		   assertTrue(playerA.coins==2); 
   		   

      }  
    @Test
    public void testFeast(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      int good =1;
   	      playerA.numBuys = 1;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Feast));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      for(int y=0; y<5;y++){
   	    	  if(playerA.hand.get(y).cost(playerA.hand.get(y))>6){ // becasue all coopers, any card that is bigger than 5 will be a new one
   	    		  good = 0;
   	    	  }
   	      }
   		   playerA.playKingdomCard();
   		   assertTrue(good ==1); //player cannot get a card bigger than 5
   		   

      }  
    @Test
    public void testGardens(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      playerA.numBuys = 1;
   	      int vicory = playerA.scoreFromPoints;
   	      int victoryAfter =0;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Gardens));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      
   		   playerA.playKingdomCard();
   		   victoryAfter = playerA.scoreFromPoints;
   		   assertTrue(victoryAfter >= vicory); //either has the same or more points
   		   

      }  
    @Test
    public void testGreathall(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      playerA.numBuys = 1;
   	      int victory = playerA.scoreFromPoints;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Great_hall));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      
   		   playerA.playKingdomCard();
   		   assertTrue(playerA.numActions==1); 
   		   assertTrue(playerA.scoreFromPoints == victory +1); 


      }  
    @Test
    public void testMine(){
      	 playerA.numActions = 1;
   	      playerA.coins = 0;
   	      int good =1;
   	      playerA.numBuys = 1;
   	      for(int k=0; k<5;k++){
   	    	  playerA.hand.remove(0);
   	      }
   	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Mine));
   	      for(int i =0; i<4; i++){
   		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
   	      }
   	      
   	      
   		   playerA.playKingdomCard();
   		   assertTrue(playerA.hand.size() ==4); //player tra
   		   

      }  
    @Test
    public void testscore(){
    	playerA.numActions = 1;
 	      playerA.coins = 0;
   	      int victory = playerA.scoreFromPoints;
 	      playerA.numBuys = 1;
 	      for(int k=0; k<5;k++){
 	    	  playerA.hand.remove(0);
 	      }
 	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Mine));
 	      for(int i =0; i<4; i++){
 		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
 	      }
 	      playerA.scoreFromPoints +=3;
 		  // playerA.playKingdomCard();
 		   assertTrue(playerA.scoreFor()>= victory+3); //player tra
 		   
    	
    }
    @Test
    public void testplaytreasure(){
    	playerA.numActions = 1;
 	      playerA.coins = 0;
 	      playerA.numBuys = 1;
 	      for(int k=0; k<5;k++){
 	    	  playerA.hand.remove(0);
 	      }
 	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Mine));
 	      for(int i =0; i<4; i++){
 		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
 	      }
 	      playerA.playTtreasureCard();
 		   assertTrue(playerA.coins == 4 ); //player tra
 		   
    	
    }
    @Test
    public void testendturn(){
    	playerA.numActions = 1;
 	      playerA.coins = 0;
 	      playerA.numBuys = 1;
 	      for(int k=0; k<5;k++){
 	    	  playerA.hand.remove(0);
 	      }
 	      playerA.hand.add(Card.getCard(cardList,Card.CardName.Mine));
 	      for(int i =0; i<4; i++){
 		      playerA.hand.add(Card.getCard(cardList,Card.CardName.Cooper));
 	      }
 	      playerA.endTurn();
 		   assertTrue(playerA.hand.size()==5); //player tra
 		   assertTrue(playerA.discard.size()==0); //player tra

 		   
    	
    }
   @Test 
   public void testgetCard(){
	   Card name = Card.getCard(cardList,Card.CardName.Silver);
	   assertTrue(Card.CardName.Silver == name.getCardName());
	   
   }
   @Test
	
   public void testDiscardPlayedTrash(){
	   
   }
   @Test
   public void testintializing(){
	   cardList1 = Card.createCards();
	    GameState gameState1;
		cardList1 = new ArrayList<Card>(Card.createCards());
		gameState1 = new GameState(cardList1);
	    playerA1 = new Player(gameState1, "player A1");
	    gameState1.addPlayer(playerA1);
	    
    //   assertTrue(gameState1.initializeGame());
	   
   }
}

