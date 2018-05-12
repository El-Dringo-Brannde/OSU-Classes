package org.cs362.dominion;

//package dominion;


import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
//import java.Card.Type;
import java.util.Random;

import org.cs362.dominion.Card.CardName;
import org.cs362.dominion.Card.Type;


public class Player {
	List<Card> hand = new ArrayList<Card>();// int hand[MAX_PLAYERS][MAX_HAND];
	//LinkedList<Card> deck = new LinkedList<Card>();// int
	List<Card>	deck = new ArrayList<Card>();											// deck[MAX_PLAYERS][MAX_DECK];
	List<Card> discard = new ArrayList<Card>(); // int
												// discard[MAX_PLAYERS][MAX_DECK];
	List<Card> playedCards = new ArrayList<Card>();
	List<Card> trash = new ArrayList<Card>();

	String player_username;

	int numActions;
	int numBuys;
	int coins;
	int scoreFromPoints;//some cards will give you points without a victory card
	final GameState gameState;

	public Player(GameState gameState,String player_username) {
		this.player_username = player_username;
		this.gameState=gameState;
	}

	final Card drawCard() {
		if (deck.isEmpty()) {// Deck is empty
			// Step 1 Shuffle the discard pile back into a deck
			System.out.println("reshuffle the deck of the player "
					+ player_username + " to draw FIVE cards");
			while (discard.size() > 0) {
				int ndx = (int) Randomness.nextRandomInt(discard.size());
				// Move discard to deck
				deck.add(discard.remove(ndx));
			}
		}
		

		//Card toDraw = deck.poll();
		Card toDraw = deck.get(0);//will keep gving you the fisrt one
		hand.add(toDraw);// Add card to hand and hand count automatically will
							// be incremented since we use List
		deck.remove(0);
		System.out.println("draw " + toDraw.getCardName()+ ": cost: " +toDraw.cost(toDraw)+" score: "+ toDraw.score() + " treasure value: " + toDraw.getTreasureValue());
		Collections.sort(hand);
		return toDraw;
	}
	
	
	   final void initializePlayerTurn() {
		   //initialize first player's turn
//		   state->numnumActions = 1;
//		   state->numnumBuys = 1;
		      numActions = 1;
		      coins = 0;
		      //scoreFromPoints = 0;
		      numBuys = 1;
		      //Shuffle your starting 10 cards (7 Coppers & 3 Estates) and place them face-down as your Deck. Draw the top
		      //5 cards as your starting hand
		      for (int i = 0; i < 5; i++) {
		    	  drawCard();
		      }
		   }

	 //card goes in discard,
	   final boolean gain(Card card) {
		   //	gameState.cards.remove(card);
		     discard.add(card);
		   //  gameState.gameBoard.increment(card); 
		     //gameState.gameBoard.put(card, gameState.gameBoard.get(card) - 1);
		     System.out.println("Player: "+this.player_username+" gains "+card.getCardName());
		     return true;
		   }		   
		 //Discard hand
	   public void discard(Card card) {
		      hand.remove(card);
		      discard.add(card);
		      System.out.println("Player:  "+player_username+" discards "+card.getCardName());
		   }
	   public void played(Card card) {
		     hand.remove(card);//remove
		      playedCards.add(card);
		      System.out.println("Player:  "+player_username+" play "+card.getCardName());
		   }
	   public void trash(Card card){
		   hand.remove(card);
		   trash.add(card);
		   System.out.println("Player:  "+player_username+" trashed "+card.getCardName());
	   }
	   public void playKingdomCard() {
		      while (numActions > 0) {
		         List<Card> actionCards = Card.filter(hand, Type.ACTION);
		   
		         if (actionCards.size() == 0)
		            return;
		         
		         Card c = (Card)actionCards.get(0);
		         if (c == null)
			           return;
			 	System.out.println(" --- --------------------------- --- ");

		         System.out.println("Player.actionPhase Card :" + c.getCardName());

		         c.play(this, gameState);

			      playedCards.add(c);
			      numActions -= 1;

		      }
		   }
	   final int scoreFor() { 
		   int score = 0;
		   //score from hand
		      for (Card c : hand)
		    	  score += c.score();
		      //score from discard
		      for (Card c : discard) 
		    	  score += c.score();
		      //score from deck
		      for (Card c : deck)
		    	  score += c.score();
		      score += scoreFromPoints;		      
		    
		      return score;
	   }    
	   
	   public void playTtreasureCard() {
		System.out.println(" --- --------------------------- --- ");
  		System.out.println("Choose Ttreasure Cards ");
			List<Card> cardsToplay = new ArrayList<Card>();

  		for (int counter = 0; counter<hand.size(); counter++ ){
  			Card currCard = hand.get(counter);
			if (currCard.getCardName() == CardName.Cooper){//if an estate
				this.coins +=1;
				//discard(currCard);
				//played(currCard);
				cardsToplay.add(currCard);
			}
			else if(currCard.getCardName() == CardName.Silver){
				this.coins +=2;
				//discard(currCard);
				//played(currCard);
				cardsToplay.add(currCard);

			}
			else if(currCard.getCardName() == CardName.Gold){
				this.coins +=3;	
				//discard(currCard);
				//played(currCard);
				cardsToplay.add(currCard);

			}
  		}
  		for(int k=0; k<cardsToplay.size();k++){
  			played(cardsToplay.get(k));
  		}
		System.out.println(this.player_username + " has: " +this.coins + " coins");

  		System.out.println(" --- --------------------------- --- ");

  		}
	   
	   public void buyCard() {
		   System.out.println(" --- --------------------------- --- ");
 			System.out.println("Buy "); 
 			//for(int i = 0; i<this.numBuys; i++){
 	  			//System.out.print("in num buy");
 		
 			List<Card> canBuy = new ArrayList<Card>();
 			while(this.numBuys > 0){
 				if(this.coins > 0){
 					for(int numCards = 0; numCards < gameState.cards.size();numCards++){
 	 	  				Card currCard = gameState.cards.get(numCards);
 	 					if(currCard.cost(currCard)<=this.coins){
 	 						canBuy.add(currCard);
 	 					}
 					}
 					Random rand = new Random();
 	 				int  n = rand.nextInt(canBuy.size());//0 until size-1
 	 				Card chosen = canBuy.get(n);
 	 				gain(chosen);
 	 				this.coins = coins-chosen.cost(chosen);
 				}
 				else{
 	 				this.gain(Card.getCard(gameState.cards, Card.CardName.Cooper));
 			       //  player.hand.add(Card.getCard(cards,Card.CardName.Adventurer));

 				}
 				this.numBuys= numBuys-1;
 			}
 			
 			
 			
 			
 			
 			
 			System.out.println(" --- --------------------------- --- ");  
 			
	   }
	   final void endTurn() {
		   System.out.println(" --- --------------------------- --- ");
			System.out.println("TO-DO endTurn "); 
			while (discard.size() > 0) {
				int ndx = (int) Randomness.nextRandomInt(discard.size());
				// Move discard to deck
				deck.add(discard.remove(ndx));
				}
			while (hand.size() > 0) {
				int ndx = (int) Randomness.nextRandomInt(hand.size());
				// Move discard to deck
				deck.add(hand.remove(ndx));
				}
			while (playedCards.size() > 0) {
				int ndx = (int) Randomness.nextRandomInt(playedCards.size());
				// Move discard to deck
				deck.add(playedCards.remove(ndx));
				}
			this.initializePlayerTurn();
			
			System.out.println(" --- --------------------------- --- ");      
	   }
	   //adding coins
	   public void addCoins(int numberOfCoins){
		   this.coins = this.coins+numberOfCoins;
	   }
	   public void addScore(int score){
		   this.scoreFromPoints += score;
	   }
	   
	   
	   public void printStateGame(){
		   System.out.println(" --- " + this.player_username + " --- ");
		   System.out.println(" --- --------------------------- --- ");
   		System.out.println(this.gameState.toString()); 
   		System.out.println(" --- --------------------------- --- ");
	   }
	   @Override
		public String toString() {
		     StringBuilder sb = new StringBuilder();
		     
     	 sb.append(" --- " + this.player_username + " --- ");
     	 sb.append(" --- --------------------------- --- ");

     	 sb.append("Hand: " + this.hand);
     	 sb.append("Discard: " + this.discard);
     	 sb.append("Deck: " + this.deck);
     	 sb.append("Played Cards: " + this.playedCards);
     	 sb.append("numActions: " + this.numActions);
     	 sb.append("coinss: " + this.coins);
     	 sb.append("numBuys: " + this.numBuys);
     	 sb.append("\n");     

		     return sb.toString();

		}
	   
}