package org.cs362.dominion;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.TreeMap;




//struct gameState {
//	  int numPlayers; //number of players
//	  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//	  int embargoTokens[treasure_map+1];
//	  int outpostPlayed;
//	  int outpostTurn;
//	  int whoseTurn;
//	  int phase;
//	  int numActions; /* Starts at 1 each turn */
//	  int coins; /* Use as you see fit! */
//	  int numBuys; /* Starts at 1 each turn */
//	  int hand[MAX_PLAYERS][MAX_HAND];
//	  int handCount[MAX_PLAYERS];
//	  int deck[MAX_PLAYERS][MAX_DECK];
//	  int deckCount[MAX_PLAYERS];
//	  int discard[MAX_PLAYERS][MAX_DECK];
//	  int discardCount[MAX_PLAYERS];
//	  int playedCards[MAX_DECK];
//	  int playedCardCount;
//	};

public class GameState {
	   public final List<Player> players = new ArrayList<Player>(); ;
	   public final List<Card> cards ;
	   public HashMap<Card, Integer> gameBoard = new HashMap<Card, Integer>();	
	   
	   
	   public GameState(List<Card> cards) {
		   this.cards=cards;
		   
	   }
	   public void addPlayer(Player player) {
		      players.add(player);
	   }  
	   public Player returnPlayer(String playerName){
		   for(int i =0; i<players.size(); i++){
			   Player a = players.get(i);
			   if(a.player_username == playerName){
				   return a;
			   }			   
		   }
		   return null;
	   }

	   /*	   initializing all supplies, and shuffling deck and
	   drawing starting hands for all players.  Check that 10 cards selected
	   are in fact (different) kingdom cards, and that numPlayers is valid.*/
	   
	   public void initializeGame(){		


			      //initialize supply 

			   //check number of players
			   if (players.size() > 4 || players.size() < 2)
			    {
				   System.err.println("the number of players mus be between 2 and 4 ");
			      return ;
			    }
			 //initialize supply for only two players
				  int selectedKindom=0;
				   int Kingdom_Cards_Selected=10;//assignming 10 kingdom cards
			         System.out.println("The kingdom cards chosen:");

		      while (selectedKindom < Kingdom_Cards_Selected) {
			         int random = (int)  Randomness.random.nextInt(cards.size());//
			         Card tmp = cards.get(random);
			         if(tmp.getType()!=Card.Type.ACTION) continue;
			         if(gameBoard.containsKey(tmp)) continue;
			         System.out.print(tmp.getCardName()+", ");
			         gameBoard.put(tmp, 10);
			         selectedKindom++;
			      }
		      System.out.println();
		        //set number of Curse cards the default number of players is 2			   
		      gameBoard.put(Card.getCard(cards, Card.CardName.Curse), 10);
		      
		      //set number of Victory cards
		      gameBoard.put(Card.getCard(cards, Card.CardName.Province), 8);
		      gameBoard.put(Card.getCard(cards, Card.CardName.Duchy), 8);
		      gameBoard.put(Card.getCard(cards, Card.CardName.Estate), 14);
		    //set number of Treasure cards
		      gameBoard.put(Card.getCard(cards, Card.CardName.Gold), 30);
		      gameBoard.put(Card.getCard(cards, Card.CardName.Silver), 40);
		      gameBoard.put(Card.getCard(cards, Card.CardName.Cooper), 60);
		   

		      for (Player player : players) {
			         for (int i = 0; i < 7; i++)
			            player.gain(Card.getCard(cards, Card.CardName.Cooper));
			         for (int i = 0; i < 3; i++)
			            player.gain(Card.getCard(cards,Card.CardName.Estate));
			         
			         player.numActions = 1;
			         player.coins = 0;
			         player.numBuys = 1;
			         
				      //Shuffle your starting 10 cards (7 Coppers & 3 Estates) and place them face-down as your Deck. Draw the top
				      //5 cards as your starting hand
				      for (int i = 0; i < 5; i++) {
				    	  player.drawCard();
				      }
			      }
	   
		   
		   
	   }
	   
	   public HashMap<Player, Integer>  play() {
			 
		   	  int turn =0;	
		      while (!isGameOver()) {
		    	  turn++;
		         for (Player player : players) {
		        	 	System.out.println("Player: "+ player.player_username + " is playing");
		        	 	System.out.println(player.player_username + "'s hand:"  );
		        	 	for (int i = 0; i < 5; i++) {
			        	 	System.out.print(player.hand.get(i).getCardName()+" ");
		  		      }
		        	 	System.out.println();
		        	 	//System.out.println("Player: "+ player.player_username+"has"+player.deck.size()+"cards in deck");
		        	 	//ystem.out.println("Player: "+ player.player_username+"has"+player.playedCards.size()+"cards in played");
 
		   				//player p plays action card
		        	 	player.playKingdomCard();
		        	 	//player plays treasure card
		   			    player.playTtreasureCard();
		   			    //player buy cards
		        	    player.buyCard();
		        	  //player ends turn
		        	    player.endTurn();
		         }
		         if(turn==15)
		        	 break;
		      }
		      return this.getWinners();
		   }
	   public boolean isGameOver() {
		 //if stack of Province cards is empty, the game ends
		   if((gameBoard.get(Card.getCard(cards, Card.CardName.Province))==null)||(gameBoard.get(Card.getCard(cards, Card.CardName.Province))== 0))
			   return true;
		 //if three supply pile are at 0, the game ends
		      int emptySupplyPile = 0;
		      for (int i : gameBoard.values()){
		         if (i == 0)
		        	 emptySupplyPile++;
		         if ( emptySupplyPile >= 3)
		         {
		           return true;
		         }
		      }
		         return false;
		   }
	   
	   /* Set HashMap  of each player and the score (remember ties!) */
	   public HashMap<Player, Integer>  getWinners() {
		   HashMap<Player, Integer> playerScore = new HashMap<Player, Integer>();

		    //get score for each player
		      for (Player p : players) {
		         int score = p.scoreFor();
		         playerScore.put(p, score);
		      }

		      return playerScore;
		   }
	   
	   @Override
	public String toString() {

		StringBuilder sb = new StringBuilder();
		if (gameBoard.isEmpty())
			sb.append("The board game is embty you need to intialize the game!!!!");
		else {
			for (Player player : players)
				sb.append(" --- " + player.toString() + "\n");
			sb.append(" --- gameBoard --- \n");
			sb.append("Cards on the table: \n");
			sb.append("Card Name \t\t NumberCards: \n");
			Map<Card, Integer> treeMap = new TreeMap<Card, Integer>(gameBoard);
			for (Card card : treeMap.keySet())
				sb.append("\t " + card.getCardName() + "\t\t "
						+ treeMap.get(card) + "\n");
		}
		return sb.toString();
	}   
	   
}
