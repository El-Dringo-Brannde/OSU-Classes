package dominion;


import java.util.*;


class Player{
	
	private final String Player_Name; 
	private int Player_Victory_Points;
	private int Player_Gold;
	private List<Cards> Player_Hand = new ArrayList<Cards>();
	private List<Cards> Player_Deck = new ArrayList<Cards>();
	private List<Cards> Player_Discard = new ArrayList<Cards>();	
	
	public int Player_Action_Turns; 
	public int Player_Buy_Turns; 
	
	
	Player(String Name){ this.Player_Name = Name; }
	
	
	public int safeActionDraw(){
		boolean safe = false;
		int safe_Num = 0;
		
		while (safe == false){
			int randVal = RandNumbers.getRand(Deck.getActionDeck().size());
			if (PlayDominion.CheckifPileIsEmpty(randVal) == true || Deck.getActionDeck().get(randVal).get(0).getCost() > 4)
				safe = false; 
			else {
				safe = true;
				safe_Num = randVal; 
			}
		}
		return safe_Num;
	}
	
	public int Get_Player_VP(){ return Player_Victory_Points;}
	
	public int get_Player_Gold(){ return Player_Gold; }
	
	public List<Cards> GetDeck(){ return Player_Deck; }
	public List<Cards> getDiscard(){ return Player_Discard;}
	
	public List<Cards> get_PlayHand (){
		return Player_Hand;
	}
	
	public void Hand_To_Discard(int index){
		Player_Discard.add(Player_Hand.remove(index));
	}
	
	public void PayPiper(int cost){
		System.out.println("COST OF CARD " + cost);
		int paid = 0, i = 0;
		do {
			if(Player_Hand.get(i).getName() == "Copper"){
				paid++;
				Hand_To_Discard(i);
				i--;
			}
			else if(Player_Hand.get(i).getName() == "Silver"){
				paid = paid + 2; 
				Hand_To_Discard(i);
				i--;
			}
			else if (Player_Hand.get(i).getName() == "Gold"){
				paid = paid + 3;
				Hand_To_Discard(i);
				i--;
			}
			i++;
		} while(paid < cost);
		// ^^^ This could be one of the bugs, it could over pay for a card.
		
	}
	
	
	// Function to look through player piles and count gold values and Victory Points
	public void Get_Player_Stats(){
		int Gold_Counter = 0;
		int Victory_Point_Counter = 0;
		for(int i = 0; i < Player_Deck.size(); i++ ){
			if (Player_Deck.get(i).getName() == "Copper")
				Gold_Counter++;
			else if (Player_Deck.get(i).getName() == "Silver")
				Gold_Counter = Gold_Counter + 2;
			else if (Player_Deck.get(i).getName() == "Gold")
				Gold_Counter = Gold_Counter + 3;
			else if (Player_Deck.get(i).getName() == "Estate")
				Victory_Point_Counter++;
			else if (Player_Deck.get(i).getName() == "GreatHall")
				Victory_Point_Counter++;
			else if (Player_Deck.get(i).getName() == "Duchy")
				Victory_Point_Counter = Victory_Point_Counter + 3;
			else if (Player_Deck.get(i).getName() == "Province")
				Victory_Point_Counter = Victory_Point_Counter + 6;
			else if (Player_Deck.get(i).getName() == "Curse")
				Victory_Point_Counter = Victory_Point_Counter - 1;
		}
		for (int i = 0; i < Player_Hand.size();i++){
			if (Player_Hand.get(i).getName() == "Copper")
				Gold_Counter++;
			else if (Player_Hand.get(i).getName() == "Silver")
				Gold_Counter = Gold_Counter + 2;
			else if (Player_Hand.get(i).getName() == "Gold")
				Gold_Counter = Gold_Counter + 3;
			else if (Player_Hand.get(i).getName() == "Estate")
				Victory_Point_Counter++;
			else if (Player_Hand.get(i).getName() == "GreatHall")
				Victory_Point_Counter++;
			else if (Player_Hand.get(i).getName() == "Duchy")
				Victory_Point_Counter = Victory_Point_Counter + 3;
			else if (Player_Hand.get(i).getName() == "Province")
				Victory_Point_Counter = Victory_Point_Counter + 6;
			else if (Player_Hand.get(i).getName() == "Curse")
				Victory_Point_Counter = Victory_Point_Counter - 1;
		}
		for (int i = 0; i < Player_Discard.size();i++){
			if (Player_Discard.get(i).getName() == "Copper")
				Gold_Counter++;
			else if (Player_Discard.get(i).getName() == "Silver")
				Gold_Counter = Gold_Counter + 2;
			else if (Player_Discard.get(i).getName() == "Gold")
				Gold_Counter = Gold_Counter + 3;
			else if (Player_Discard.get(i).getName() == "Estate")
				Victory_Point_Counter++;
			else if (Player_Discard.get(i).getName() == "GreatHall")
				Victory_Point_Counter++;
			else if (Player_Discard.get(i).getName() == "Duchy")
				Victory_Point_Counter = Victory_Point_Counter + 3;
			else if (Player_Discard.get(i).getName() == "Province")
				Victory_Point_Counter = Victory_Point_Counter + 6;
			else if (Player_Discard.get(i).getName() == "Curse")
				Victory_Point_Counter = Victory_Point_Counter - 1; 
		}
		
		this.Player_Victory_Points = Victory_Point_Counter;
		this.Player_Gold = Gold_Counter;
		
	}
	
	public int Get_player_gold_in_hand(){
		int GoldCounter = 0;
		for(int i = 0; i < Player_Hand.size();i++){
			if (Player_Hand.get(i).getName() == "Copper")
				GoldCounter++;
			else if (Player_Hand.get(i).getName() == "Silver")
				GoldCounter = GoldCounter + 2;
			else if (Player_Hand.get(i).getName() == "Gold")
				GoldCounter = GoldCounter + 3;
		}
		return GoldCounter;
	}
	
	public void newHand(){
		while(Player_Hand.size() != 0)
			Player_Discard.add(Player_Hand.remove(0));
		// If the deck is less than 5 trash it. 
		if (Player_Deck.size() < 5){
			while (Player_Deck.size() != 0)
				Player_Discard.add(Player_Deck.remove(0));
			
			while (Player_Discard.size() != 0)
				Player_Deck.add(Player_Discard.remove(0));
			
			shuffle(Player_Deck);
		}
		
		for(int i = 0; i < 5; i++)
			Draw(0);
	}
	
	
	
	
	public void Play_Card(Cards CardInPlay,Player P1, Player P2){
		String cardName = CardInPlay.getName();
		switch(cardName){
		case ("Adventurer"):
			System.out.println("Reveal deck until you reveal 2 treasure cards, \n"
					+ "Put those cards into your hand and discard the rest");
			handleAdventurer();
			break;
		case("Ambassador"):
			System.out.println("Reveal a card from your hand, return up to 2 copies of it from your hand to the supply \n"
					+ "Then the other player gains a copy of it.");
			handle_Ambassador(P1,P2);
			break;
		
		case("Baron"):
			System.out.println("Get a Buy" + " Discard an estate for +4 gold, if you don't gain an estate");
			handle_Baron();
			break;
		case("CouncilRoom"):
			System.out.println("Gain 4 cards, and +1 for the buy phase, then each player draws a card\n");
			handle_CouncilRoom(P1,P2);
			break;
		case("CutPurse"):
			System.out.println("+2 gold, Each player discards a copper, or reveals hand if they have no coppers \n");
			if (Deck.getMoneyDeck().get(1).size() != 0)
				this.Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0)); //give him a silver
			handle_CutPurse(P1,P2);
			break;
		case("Embargo"):
			System.out.println("+2 gold, Trash card, put embargo token on supply pile, when a player buys a card "
					+ "he gains a curse card per Embargo token on pile\n"); 
			handle_Embargo();
			break;
		case("Feast"):
			System.out.println("Trash card and gain a card costing up to 5 gold \n"); 
			handleFeast();
			break;
		case("Garden"):
			System.out.println("Worth 1 VP per 10 cards you have, rounding down"); 
			handleGarden();
			break;
		case("GreatHall"):
			System.out.println("+1 cards, +1 action\n");
			handleGreathall();
			break;
		case("Mine"):
			System.out.println("Trash a money card from your hand and gain one costing up to 3 more gold than it \n");
			handleMine();
			break;
		case("Village"):
			System.out.println("+1 cards, +2 actions \n");
			handleVillage();
			break;
		case("Workshop"):
			System.out.println("Gain a card costing up to 4 gold\n");
			handleWorkshop();
			break;
		case("Market"):
			System.out.println("+1 card, +1 Action, +1 Buy, +1 gold \n");
			handleMarket();
			break;
		default: 
			System.out.println("How did this happen..? \n");
		}
	}
	
	private void handleMarket(){
		this.Player_Action_Turns++;
		this.Player_Buy_Turns++;
		if (Player_Deck.size() == 0)
			getNewDeck();
		System.out.println("Old Hand: " + this.Player_Hand.toString());
		
		Player_Hand.add(Player_Deck.remove(0));
		if (Deck.getMoneyDeck().get(0).size() != 0)
			Player_Hand.add(Deck.getMoneyDeck().get(0).remove(0));
		System.out.println("New Hand: " + this.Player_Hand.toString());
		
	}
	
	
	private void handleWorkshop(){
		Boolean Bought_Card = false;
		int rand = 0; 
		while (Bought_Card == false)	{
			
			rand = safeActionDraw();
			
			
			if (PlayDominion.CheckifPileIsEmpty(rand) == false){
				Cards Bought = Deck.getActionDeck().get(rand).remove(0);
				System.out.println("You got a " + Bought.toString());
				if (Bought.getToken() == true){
					System.out.println("This card has a token on it!! \n");
					if(Deck.getVCDeck().get(3).size() != 0)
						Player_Hand.add(Deck.getVCDeck().get(3).remove(0));
				}
				Player_Hand.add(Bought);
				System.out.println("New Hand " + this.Player_Hand.toString());
				Bought_Card = true;
				}
			else 
				System.out.println("Tried to draw from an empty deck\n");;
			}
		
		}
			
	
	
	private void handleVillage(){
		System.out.println("Old Hand: " + this.Player_Hand.toString());

		if (Player_Deck.size() <= 1)
			getNewDeck();
		Player_Hand.add(Player_Deck.remove(0));
		this.Player_Action_Turns += 2;
		System.out.println("New Hand: " + this.Player_Hand.toString());

	}
	
	private void handleMine(){
		System.out.println("Old Hand: " + this.Player_Hand.toString());

		for(int i = 0; i < Player_Hand.size();i++){
			if (Player_Hand.get(i).getName() == "Copper"){
				Player_Hand.remove(i);
				Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0)); // get silver
				System.out.println("New Hand: " + this.Player_Hand.toString());
				return;
			}
			if (Player_Hand.get(i).getName() == "Silver"){
				Player_Hand.remove(i);
				Player_Hand.add(Deck.getMoneyDeck().get(2).remove(0)); // get gold
				System.out.println("New Hand: " + this.Player_Hand.toString());
				return;
			}
		}
		System.out.println("You had no money in your hand.. \n");
	}
	
	private void handleGreathall(){
		System.out.println("Old Hand: " + this.Player_Hand.toString());

		if (Player_Deck.size() <= 1)
			getNewDeck();
		Player_Hand.add(Player_Deck.remove(0));
		System.out.println("New Hand: " + this.Player_Hand.toString());

		this.Player_Action_Turns++;
	}
	
	private void handleGarden(){
		int deckSize = Player_Deck.size();
		int getCopper = 0,getSilver = 0, getGold = 0; 
		System.out.println(deckSize);
		this.Get_Player_Stats();
		System.out.println("Player Has this many Victory Points" + this.toString());
		while (deckSize >= 60){
			deckSize = deckSize / 60;
			getGold++;
		}
		while(deckSize  >= 30){
			getSilver++;
			deckSize = deckSize / 30;
		}
		while (deckSize >= 10){
			getCopper++; 
			deckSize = deckSize / 10; 
		}
		for(int i = 0; i < getGold;i++){
			if (Deck.getMoneyDeck().get(2).size() != 0)
				this.Player_Hand.add(Deck.getMoneyDeck().get(2).remove(0));
		}
		for(int i = 0; i < getSilver;i++){
			if (Deck.getMoneyDeck().get(1).size() != 0)
				this.Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0));
		}
		for(int i = 0; i < getCopper;i++){
			if (Deck.getMoneyDeck().get(0).size() != 0)
				this.Player_Hand.add(Deck.getMoneyDeck().get(0).remove(0));
		}
		this.Get_Player_Stats();
		System.out.println("Player Has this many Victory Points " + this.toString());
	}
	
	//Need to trash this card as well. 
	private void handleFeast(){
		Boolean Bought_Card = false, safe = false;
		int rand = 0; 
		System.out.println("Old Hand: " + this.Player_Hand.toString());

		while (Bought_Card == false){
			rand = safeActionDraw();
			if (Deck.getActionDeck().get(rand).get(0).getCost() > 5)
				System.out.println("Cost not less than 5\n");
			else{
				Cards Bought = Deck.getActionDeck().get(rand).remove(0);
				System.out.println("You got a " + Bought.toString());
				if (Bought.getToken() == true)
					System.out.println("This card has a token on it!! \n");
				Player_Hand.add(Bought);
				System.out.println("New Hand " + this.Player_Hand.toString());
				Bought_Card = true;
			}
		}
		
	}
	//Need to trash the card
	private void handle_Embargo(){
		boolean safe = false;
		int rand = 0;
		if (PlayDominion.CheckMoneyPile(1) == false)
			this.Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0)); //get silver
		while (safe == false){
			int randomVal = RandNumbers.getRand(Deck.getActionDeck().size());
			if (PlayDominion.CheckifPileIsEmpty(randomVal) == true)
				safe = false; 
			else {
				safe = true;
				rand = randomVal; 
			}
		}
		System.out.println("This is the randomVal for the Token " + rand);
		System.out.println(Deck.getActionDeck().get(rand).get(0).toString());
		for (int i = 0; i < Deck.getActionDeck().get(rand).size(); i++) //add Embargo to entire stack
			Deck.getActionDeck().get(rand).get(i).addEmbargo();
		System.out.println(Deck.getActionDeck().get(rand).get(0).toString());		
		
	}
	
	
	private void handle_CutPurse(Player p1,Player p2){
		Player other; 
		if (this == p1)
			other = p2; 
		else
			other = p1;
		System.out.println(this.Player_Hand.toString());
		
		for(int i = 0; i < other.Player_Hand.size(); i++){
			if (other.Player_Hand.get(i).getName() == "Copper"){
				other.Player_Hand.remove(i); //get rid of a copper 
				System.out.println(other.Player_Hand.toString());
				return; 
			}
		}
		System.out.println("No copper in hand found! \n" + Player_Hand.toString());
	}
	
	private void handle_CouncilRoom(Player p1, Player p2){
		Player other;
		if (this == p1)
			other = p2;
		else 
			other = p1; 
		
		this.Player_Buy_Turns++;
		System.out.println(this.Player_Hand.toString());
		if (this.Player_Deck.size() < 5)
			getNewDeck();
		for (int i = 0; i < 4; i++)
			this.Draw(0);		
		if (other.Player_Deck.size() < 2)
			other.getNewDeck();
		other.Draw(0);
		System.out.println(this.Player_Hand.toString());

	}
	
	void getNewDeck(){
		for (int i = 0; i < this.Player_Deck.size(); i++)
			this.Player_Discard.add(this.Player_Deck.remove(0));
		for (int i = 0; i < this.Player_Discard.size();i++)
			this.Player_Deck.add(this.Player_Discard.remove(0));
		shuffle(this.Player_Deck);
	}
	
	private void handle_Baron(){
		this.Player_Buy_Turns++;
		System.out.println(this.Player_Hand.toString());
		for (int i = 0; i < Player_Hand.size(); i++){
			if (Player_Hand.size() != 0 && Player_Hand.get(i).getName() == "Estate"){
				System.out.println("Found an Estate \n");
				Player_Discard.add(Player_Hand.remove(i));
				if (Deck.getMoneyDeck().get(1).size() >= 2){
					Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0)); //get silver
					Player_Hand.add(Deck.getMoneyDeck().get(1).remove(0));	
				}
				System.out.println(this.Player_Hand.toString());
				return;
			}
		}
		System.out.println("No Estate cards found in hand\n");
		if (Deck.getMoneyDeck().get(0).size() != 0)
			Player_Hand.add(Deck.getMoneyDeck().get(0).remove(0));
		System.out.println(this.Player_Hand.toString());
	}
	
	
	
	private void handle_Ambassador(Player p1, Player p2){
		int randomVal = RandNumbers.getRand(Player_Hand.size());
		int found = 0,i = 0;
		Cards RandCard = Player_Hand.get(randomVal);
		Player_Deck.add(Player_Hand.remove(randomVal));
		System.out.println("Card Selected: " + RandCard.toString());

		
		while(i != Player_Hand.size()){
			if (Player_Hand.get(i).getName() == RandCard.getName()){
				Player_Deck.add(Player_Hand.remove(i));
				found++;
				i--;
			}
			if (found == 2)
				break;
			i++;
		}
		i = 0;
		while(i != Deck.getActionDeck().size()){
			if (Deck.getActionDeck().get(i).size() != 0){
				if (Deck.getActionDeck().get(i).get(0).getName() == RandCard.getName()){
					if (this == p1){
						p2.Player_Deck.add(Deck.getActionDeck().get(i).remove(0));
						System.out.println("Added: " + p2.Player_Deck.toString());
						i--;
						return;
					}
					p1.Player_Deck.add(Deck.getActionDeck().get(i).remove(0));
					System.out.println("Added: " + p1.Player_Deck.toString());
					i--;
					return;
				}
			}
			i++;
		}
		
		i = 0;
		while(i != Deck.getVCDeck().size()){
			if (Deck.getVCDeck().get(i).size() != 0){
				if (Deck.getVCDeck().get(i).get(0).getName() == RandCard.getName()){
					if (this == p1){
						p2.Player_Deck.add(Deck.getVCDeck().get(i).remove(0));
						System.out.println("Added: " + p2.Player_Deck.toString());
						i--;
						return;
					}
					p1.Player_Deck.add(Deck.getVCDeck().get(i).remove(0));
					System.out.println("Added: " + p1.Player_Deck.toString());
					i--;
					return;
				}
			}
			i++;
		}
		i = 0;
		String test = "Copper";
		while(i != Deck.getMoneyDeck().size()){
			if (Deck.getMoneyDeck().get(i).size() != 0)
				test = Deck.getMoneyDeck().get(i).get(0).getName();
			String test2 = RandCard.getName();
			if (test == test2 && Deck.getMoneyDeck().get(i).size() != 0){
				if (this == p1){
					p2.Player_Deck.add(Deck.getMoneyDeck().get(i).remove(0));
					System.out.println("Added: " + p2.Player_Deck.toString());
					break;
				}
				p1.Player_Deck.add(Deck.getMoneyDeck().get(i).remove(0));
				System.out.println("Added: " + p1.Player_Deck.toString());
				break;
			}
			i++;
		}
		
		
	}
	
	private void handleAdventurer(){
		int cardShown = 0;
		int i = Player_Deck.size() - 1;
		System.out.println(Player_Hand.toString());
		while (i >= 0){
			System.out.println(Player_Deck.get(i).toString());
			if (Player_Deck.get(i).getType() == "Money"){
				Player_Hand.add(Player_Deck.remove(i));
				cardShown++;
				i = Player_Deck.size() - 1;
			}
			else{
				Player_Discard.add(Player_Deck.remove(i));
				i = Player_Deck.size() - 1;
			}
			if (cardShown == 2)
				break;
		}
		System.out.println(Player_Hand.toString());
		
	}
	
	
	
	
	//Add a card to the hand from the player Deck.
	public void Draw(int index) { Player_Hand.add(Player_Deck.remove(0)); }
	
	//Add a card to the deck
	//public void Place(Player Play, Cards Card) { Play.Player_Deck.add(Card); }
	
	public static int Check_For_Action(Player P){
		for (int i = 0; i < P.Player_Hand.size(); i++) {
			//System.out.println(P.Player_Hand.get(i).toString());
			if (P.Player_Hand.get(i).getType() == "Action")
				return i;
		}
		return -1;
		
	}
	
	// Shuffle up the player deck
	public static void shuffle(List<Cards> Deck){
		  Collections.shuffle(Deck);
	 }
	
	
	// Shows the current values held by the player
	public String toString(){
		return Player_Name + "| Victory Points: " + Player_Victory_Points + "| Gold: " + Player_Gold;
		
	}
	
}
