package org.cs362.dominion;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.spi.CalendarDataProvider;

	public final class Card implements Comparable<Card> {
		public enum Type {
			ACTION, TREASURE, VICTORY, CURSE;
		}

		public static enum CardName {
			/** The Treasure cards */
			Gold, Silver, Cooper,
			/** The Victory cards */
			Province, Duchy, Estate, Curse,
			/** The Kingdom cards */
			Adventurer, Village, Ambassador, Baron, Council_room, Cutpurse, Embargo, Feast, Gardens, Great_hall, Mine, Salvager,Smithy;
		}

		/**
		 * @param enum
		 *            CardName the name of the card (GOLD, SILVER, COPPER,
		 * @param enum
		 *            Type the type of the card (Victory, Treasure, or Kingdom
		 * @param int
		 *            cost the cost of the card
		 * @param int
		 *            score the score of the card, when the game is finished
		 * @param treasureValue
		 *            the treasure value of the treasure cards (cooper, silver, and
		 *            gold cards)
		 */
		private final Type realType;
		private final CardName cardName;
		private final int cost, score, treasureValue;

		Card(CardName cardName, Type type, int cost, int score, int treasureValue) {
			this.cost = cost;
			this.score = score;
			this.treasureValue = treasureValue;
			this.realType = type;
			this.cardName = cardName;
		}

		/**
		 * Returns the type
		 */
		public Type getType() {
			return realType;
		}

		/**
		 * Returns the cardName
		 */
		public CardName getCardName() {
			return cardName;
		}

		public int getTreasureValue() {
			return treasureValue;
		}
		public int cost(Card card){
			return cost;
		}
		public int score() {
			return score;
		}

		static List<Card> createCards() {
			List<Card> ret = new LinkedList<Card>();

			/** The Treasure cards */
			Card o = new Card(CardName.Gold, Type.TREASURE, 6, 0, 3);
			ret.add(o);
			o = new Card(CardName.Silver, Type.TREASURE, 3, 0, 2);
			ret.add(o);
			o = new Card(CardName.Cooper, Type.TREASURE, 0, 0, 1);
			ret.add(o);

			/** The Victory cards */
			o = new Card(CardName.Province, Type.VICTORY, 8, 6, 0);
			ret.add(o);
			o = new Card(CardName.Duchy, Type.VICTORY, 5, 3, 0);
			ret.add(o);
			o = new Card(CardName.Estate, Type.VICTORY, 2, 1, 0);
			ret.add(o);
			o = new Card(CardName.Curse, Type.CURSE, 0, -1, 0);
			ret.add(o);
			/** The Kingdom cards , it should more than 10 cards */

			o = new Card(CardName.Adventurer, Type.ACTION, 6, 0, 0);
			ret.add(o);
			o = new Card(CardName.Smithy, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Salvager, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Village, Type.ACTION, 3, 0, 0);
			ret.add(o);
			// the cards I added (first 10), adventurer is already here
			o = new Card(CardName.Ambassador, Type.ACTION, 3, 0, 0);
			ret.add(o);
			o = new Card(CardName.Baron, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Council_room, Type.ACTION, 5, 0, 0);
			ret.add(o);
			o = new Card(CardName.Cutpurse, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Embargo, Type.ACTION, 2, 0, 0);
			ret.add(o);
			o = new Card(CardName.Feast, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Gardens, Type.ACTION, 4, 0, 0);
			ret.add(o);
			o = new Card(CardName.Great_hall, Type.ACTION, 3, 0, 0);
			ret.add(o);
			o = new Card(CardName.Mine, Type.ACTION, 5, 0, 0);
			ret.add(o);
			// need to add random 3(maybe use the givven 2 before)
			return ret;
		}

		public void play(Player player, GameState state) {

			switch (this.cardName) {
			case Adventurer:
				// Reveal cards from your deck until you reveal 2 Treasure cards.
				// Put those Treasure cards into your hand and discard the other
				// revealed cards.
	 			List<Card> needToDiscard = new ArrayList<Card>();

				int decksize= player.deck.size(); // getting the deck size
				int numberOfTreasure = 0; // setting a counter for number of needed cards
				System.out.println("Adventurer: showing deck cards until showed 2 treasure cards");
				for (int i=0; i<decksize; i++){ // checking all the cards in the deck not hand
					 Card current = player.deck.get(i); // geting card unfo
					 System.out.printf("The card is: %s\n",current.cardName); //printing it out to show

					 if(current.realType == Type.TREASURE){//if it's a treasure, add 1 to the counter
						 numberOfTreasure++;
						 player.hand.add(current);
						 System.out.println("Player added treasure card to hand");
						 //System.out.print("in hand after hand.add");
						 //System.out.print(player.hand);
						 needToDiscard.add(current);
						// player.hand.add(Card.getCard(player.deck, current.cardName));//add that treasure card to the player's hand
					 }
					 
					 else {
						 
						 player.discard.add(current);//if not treseaure, discard card
						 needToDiscard.add(current);
					 }
					 
					 
					 //player.deck.remove(current);
					 //delete al card form deck
					 if (numberOfTreasure==2){//if found 2 treasure cards, exit for loop. I am sure that there is a better way but I don't know it. 
						 i = decksize+1;
					 }			 				 
				}
				for(int k=0; k<needToDiscard.size();k++){
		  			player.deck.remove(needToDiscard.get(k));
				}
				return;
			case Smithy:
				System.out.println("Smithy: Drowing 3 cards from deck");
				//draw three cards
				Card temp;
				for(int i = 0; i<3;i++){
					temp = player.drawCard();
					//System.out.println("player draw: " + temp.getCardName());

				}
				
				return;
			case Salvager:
				System.out.println("Salvager: get +1 buy, trasha card and get it's cost value in coins");

				player.numBuys+= 1;//get extra buy
				System.out.println("player got +1 to buy");
				Card cardTotrash;
				int number = player.hand.size();
				int value =0 ;
				Random rand = new Random();
				int  n = rand.nextInt(number);
				cardTotrash=player.hand.get(n);
				System.out.println("player trashed: " + cardTotrash.getCardName());
				value = cardTotrash.treasureValue;
				player.coins += value;
				System.out.println("Player got " + value + "coins");
				
				
				return;

			case Village:
				System.out.println("Village: player draw +1 Card, gets +2 play Actions ");
				Card temp1;
				temp1 = player.drawCard();
				System.out.println("player draw: " + temp1.getCardName());
				player.numActions+=2;
				player.played(getCard(player.hand, CardName.Village));

				System.out.println("player recieved +2 action " );
				return;

			case Ambassador:
				System.out.println("Ambassador: reveal a card from hand, other player get a copy of it ");

				// reaveal a card from hand, return up to 2 copies of the supply.
				// Each player gains a copy of it-- where? hand or deck?.
				Card current = player.hand.get(0);
				System.out.println("Showing card: " +current.cardName);// show the card
				player.discard(current);//chose to rerurn none
				System.out.println("Other player got a copy of "+ current.cardName);
				
				//how to get the card to the next player?
				return;

			case Baron:
				System.out.println("Baron: Can choose between discarding an estate and recieve 4 coins or gain an estate");
				rand = new Random();
				n = rand.nextInt(2) + 1;// getting a random number between 1 and 2
				if(n == 1){//chose to discard an estate and get 4 coins
					for(int i = 0; i<player.hand.size(); i++){//go over all cads in hand
						Card currCard = player.hand.get(i);
						if (currCard.cardName == CardName.Estate){//if an estate
							player.discard(currCard);//discard that card
							System.out.println("Player dicard an estate");
							i = player.hand.size() +1;//get out of the loop
						}
					}
					player.addCoins(4);// player get 4 coins after dicarding the card
					System.out.println("Player gained 4 coins");

				}
				else {//if chose to get an estate instead
					player.hand.add(Card.getCard(state.cards, Card.CardName.Estate));//add card to hand
					System.out.println("Player gained an estate");
				}
				// you may dicard an estate (randomly choose if to or not.) If yes,
				// you get +4 coins? (what's +4?)
				// otherwise, gain an estate card.
				// if yes
				// get 4 coins
				// if not
				// get astate
				return;
			case Council_room:
				System.out.println("Council_room: draw 4 cards, get an extra buy");

				// get 4 cards, can buy one ore card
				Card temp2;
				for(int i = 0; i<4;i++){
					temp = player.drawCard();
					System.out.println("player draw: " + temp.getCardName());

				}
				player.numBuys++;
				System.out.println("Player got an extra buy");

				
				
				//other user get an extra card- how to do that?
				

				// can buy 1 more (buy option +1)
				// other user draw a card (player2.drewCard())
				return;
			case Cutpurse:
				System.out.println("Cutpurse: player gain 2 coins");

				player.coins +=2;
				System.out.println("Player got an extra 2 coins");

				
				
				// get 2 more coins.
				// each other player discards a copper card/ or reveals hand with no
				// copper
				return;
			case Embargo:
				System.out.println("Embargo: player get 2 coins, trash this card, put an embargo on a supply pile");
				player.coins +=2;
				System.out.println("Player got an extra 2 coins");

				//player.trash();
				for(int i = 0; i<player.hand.size(); i++){//go over all cads in hand
					Card currCard = player.hand.get(i);
					if (currCard.cardName == CardName.Embargo){//if an estate
						player.trash(currCard);//discard that card
						//System.out.println("Player trashed Embargo");

						i = player.hand.size() +1;//get out of the loop
					}
				}
				
				// get two coins. trash this card, put an embargo token on top of a
				// suplly pile
				// when a player buys a card, he gains a curse card per embargo
				// token on that pile
				return;
			case Feast:
				System.out.println("Feast: Trash this card, get a card costing up to 5.");
				for(int i = 0; i<player.hand.size(); i++){//go over all cads in hand becasue I odn't know how to 
					//send feast into trash() without getting it first
					Card currCard = player.hand.get(i);
					if(currCard.cardName == CardName.Feast){// if the card is feast
						player.trash.add(currCard);//trash it
						//System.out.println("Player trashed Feast");

						i = player.hand.size()+1;//get out of the for loop
					}
				}
				//find a card that is up to 5 coins and buy it. Just get the first card that satisfy
				for(int i=0; i<state.cards.size();i++){
					Card currentCard = state.cards.get(i);
					if(currentCard.cost <6){//check that is under 5 coins
						player.gain(currentCard);//player gain the card
						//System.out.println("player gained: " + currentCard.getCardName());
						i = state.cards.size()+1;//get out of the for loop
					}
				}
				
				// trash this card (trash?) gain a card costing up to 5 coins.
				// find all card cost up to 5
				// choose 1-> player gains it
				return;
			case Gardens:
				System.out.println("Gardens: gain 1 victory point for every 10 cards in your deck.");

				// gain 1 estate for every 10 cards in your deck
				// does deck counts for cards in hand?
				// choose if to use or not if you have less then 10
				// for deck/10 -> get 1 estate.
				int numberOfCards = player.deck.size();//get the number of cards in deck
				int estateCards = numberOfCards/10; // 
				for( int j=0; j<estateCards; j++){
					player.scoreFromPoints +=1;
				}
				System.out.println("Player gained " +estateCards+ " victory points");
				
				
				return;
			case Great_hall:
				System.out.println("Great Hall: +1 vp, draw a card, numAction +1");
				player.addScore(1);
				System.out.println("player got victory point");
				//Card temp3;
				//temp3 = player.drawCard();
				//System.out.println("player draw: " +temp3.getCardName());
				player.numActions +=1;
				player.played(getCard(player.hand, CardName.Great_hall));
				System.out.println("player got +1 actions");

				// get one more card- to hand or deck?
				// get to do one more action or get one more actin card?
				// get 1 estate?
				return;
			case Mine:
				System.out.println("Mine: trash a treasure card, gain a treasure card costing up to 3 coins more");
				int value1 =0;
				for(int i = 0; i<player.hand.size(); i++){//go over all cads in hand becasue I odn't know how to 
					//send feast into trash() without getting it first
					Card currCard = player.hand.get(i);
					if(currCard.realType == Type.TREASURE){// if the card is feast
						value1 = currCard.treasureValue +3;
						player.trash(currCard);//trash it
						i = player.hand.size()+1;//get out of the for loop 
					}
				}
				for(int j=0; j<state.cards.size();j++){
					Card getcard = state.cards.get(j);
					if (value1 >=6){
						if(getcard.cardName == CardName.Gold){
							player.gain(getcard);
							j = state.cards.size()+1;
						}
					}
					else if(value1 >=3 ){
						if(getcard.cardName == CardName.Silver){
							player.gain(getcard);
							j = state.cards.size()+1;
						}	
					} 
					}
					
				
				// trash a treasure card from your hand, gain a treasure card
				// costing up to 3 coins more. Put it into your hand!
				// trash one card that is of type treasure(if you want smart look
				// for smallest one)
				// choose a card that is treasure that is worth up to 3 more (choose
				// on that doesn't exeed 3, for smart choose biggest one possible)
				return;

			// do the extra 3, look that you already got two from tacher

			default:
				return;
			}
		}

		public static Card getCard(List<Card> cards, CardName cardName) {
			for (int i = 0; i < cards.size(); i++) {
				if (cards.get(i).cardName.equals(cardName))
					return cards.get(i);
			}

			return null;

		}

		public static List<Card> filter(Iterable<Card> cards, Type target) {
			List<Card> out = new ArrayList<Card>();
			for (Card c : cards)
				if (c.getType() == target)
					out.add(c);
			return out;
		}

		// this method will print out all the constant cards ENUM
		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();

			sb.append(" \t" + this.getCardName());
			sb.append("-" + this.getType() + " ");
			sb.append("\t\t Cost: " + this.cost + " ");
			sb.append("\t\t Score: " + this.score + " ");
			sb.append("\tTreasure Value: " + this.treasureValue);

			return sb.toString();

		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (!super.equals(obj))
				return false;
			if (!(obj instanceof Card))
				return false;

			return cardName.equals(((Card) obj).cardName);
		}

		@Override
		public int compareTo(Card o) {
			// TODO Auto-generated method stub
			return cardName.compareTo(o.cardName);
		}


}
