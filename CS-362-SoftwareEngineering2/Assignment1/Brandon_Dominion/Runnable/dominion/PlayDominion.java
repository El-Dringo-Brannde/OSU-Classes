package dominion;
class PlayDominion{
	static Player p1 = new Player("Player1");
	static Player p2 = new Player("Player2");	
	static Deck AllDecks = new Deck();
	RandNumbers Randoms = new RandNumbers();

	
	
	
	public static void Initialize_Game(){
		Cards Copper, Estate; 
		for (int i = 0; i < 7; i++){			
			Copper = new Cards("Copper",1,0, "Money",false);	
			p1.GetDeck().add(Copper);
			p2.GetDeck().add(Copper);
		}
		for (int i = 0; i < 3; i++){
			Estate = new Cards("Estate",2,1, "Victory",false);
			p1.GetDeck().add(Estate);
			p2.GetDeck().add(Estate);
		}
			
		Player.shuffle(p1.GetDeck());
		Player.shuffle(p2.GetDeck());

		for(int i = 0; i < 5; i++){
			p1.Draw(0);
			p2.Draw(0);
		}
		
		p1.Get_Player_Stats();
		p2.Get_Player_Stats();
		
		Deck.Build_Money_Victory();
		Deck.Build_Action_Deck();
	}
	
	
	public static boolean CheckifPileIsEmpty(int rand){
		if (Deck.getActionDeck().get(rand).size() == 0)
			return true;
		else 
			return false;
	}
	
	public static boolean CheckMoneyPile(int rand){
		if (Deck.getMoneyDeck().get(rand).size() == 0)
			return true;
		return false;
	}
	
	public static boolean CheckEndGame(){
		int EmptyCounter = 0; 
		for (int i = 0; i < Deck.getActionDeck().size(); i++){
			if(Deck.getActionDeck().get(i).size() == 0)
				EmptyCounter++;
		}
		if (EmptyCounter >= 3 || Deck.getVCDeck().get(2).size() == 0)
			return true;
		else 
			return false; 
	}
	
	// Just a wrapper function
	public static void Play_Game(){		
		int i = 0;
		while (CheckEndGame() == false){
			System.out.println("Turn: " + i);
			Player1Turn();
			Player2Turn();
			i++;
		}
		
		p1.Get_Player_Stats();
		p2.Get_Player_Stats();
		System.out.println("Player 1 Stats: " + p1.toString());
		System.out.println("Player 2 Stats: " + p2.toString());
		System.out.println("Exiting");
	}	
	

	// I could merge the 2 player turns into one function.. But nah. 
	public static void Player2Turn(){
		System.out.println("========================= Player 2 Turn ============================= \n");
		Boolean Bought_Card = false;
		int Action_Card_Present = Player.Check_For_Action(p2);
		int PlayCard = RandNumbers.getRand(2);
		int buyAttempts = 0;
		p2.Player_Action_Turns = 1; 
		p2.Player_Buy_Turns = 1; 
		
		
		System.out.println("Player 2 Rolled " + PlayCard);
		System.out.println("Player 2: GOLD IN HAND " + p2.Get_player_gold_in_hand() + p2.get_PlayHand().toString());
		System.out.println("-------------------------Action Phase ----------------- \n");
		
		for(int i = 0; i < p2.Player_Action_Turns; i++){
			Action_Card_Present = Player.Check_For_Action(p2);
		if (Action_Card_Present == -1)
			System.out.println("No Action Cards to play. Moving to buy phase. \n");
		else {
				System.out.printf("Player 2 plays %s \n", p2.get_PlayHand().get(Action_Card_Present).toString());
				Cards PlayMe = p2.get_PlayHand().remove(Action_Card_Present);
				p2.Play_Card(PlayMe,p1,p2);
			}	
		}
		p2.Player_Action_Turns = 1; 
		
		
		System.out.println("-------------------------Buy Phase -------------------- \n");
		boolean safe = false; 
		int rand = 0;
		//Get the size of the action deck and make it a rand value
		for(int i = 0; i < p2.Player_Buy_Turns;i++){
			do {
				if (Deck.getVCDeck().get(2).size() != 0 && p2.Get_player_gold_in_hand() > 8){
					p2.get_PlayHand().add(Deck.getVCDeck().get(2).remove(0));
					Bought_Card = true;
				}
				else if (Deck.getVCDeck().get(1).size() != 0 && p2.Get_player_gold_in_hand() > 5){
					p2.get_PlayHand().add(Deck.getVCDeck().get(1).remove(0));
					Bought_Card = true;
				}
				while(safe == false){
					int randomVal = RandNumbers.getRand(Deck.getActionDeck().size());
					if (CheckifPileIsEmpty(randomVal) == true)
						safe = false;
					else{ 
						safe = true;
						rand = randomVal;
					}
				}
				CheckifPileIsEmpty(rand);
				int Player_2_Gold = p2.Get_player_gold_in_hand();
				if (Player_2_Gold < Deck.getActionDeck().get(rand).get(0).getCost()){
				//System.out.println("Not enough Gold");
					buyAttempts++;
					if (buyAttempts > 30){
						if (CheckMoneyPile(0) == false)
							p2.get_PlayHand().add(Deck.getMoneyDeck().get(0).remove(0)); //remove a copper
						return;
					}
				}

				else {
					Cards Bought = Deck.getActionDeck().get(rand).remove(0);
					if (Bought.getCost() != 0)
						p2.PayPiper(Bought.getCost());
					p2.get_PlayHand().add(Bought);
					Bought_Card = true;
				}
			
			}while(Bought_Card == false);
			Bought_Card = false;
			safe = false;
		}
		p2.Player_Buy_Turns = 1;
		p2.newHand();
	}
	
	
	
	public static void Player1Turn(){
		System.out.println("========================= Player 1 Turn ============================== \n");
		int Action_Card_Present;
		int buyAttempts = 0;
		int rand = 0;
		p1.Player_Action_Turns = 1; 
		p1.Player_Buy_Turns = 1;

		
		System.out.println("-------------------------Action Phase ----------------- \n");
		for(int i = 0; i < p1.Player_Action_Turns; i++){
			Action_Card_Present = Player.Check_For_Action(p1);
		if (Action_Card_Present == -1)
			System.out.println("No Action Cards to play. Moving to buy phase. \n");
		else {
				System.out.printf("Player 1 plays %s \n", p1.get_PlayHand().get(Action_Card_Present).toString());
				Cards PlayMe = p1.get_PlayHand().remove(Action_Card_Present);
				p1.Play_Card(PlayMe,p1,p2);
			}	
		}
		p1.Player_Action_Turns = 1; 

		System.out.println("-------------------------Buy Phase -------------------- \n");
		
		Boolean Bought_Card = false, safe = false;
		//Get the size of the action deck and make it a rand value
		for(int i = 0; i < p1.Player_Buy_Turns;i++){
			do {
				if (Deck.getVCDeck().get(2).size() != 0 && p1.Get_player_gold_in_hand() > 8){
					p1.get_PlayHand().add(Deck.getVCDeck().get(2).remove(0));
					Bought_Card = true;
				}
				else if (Deck.getVCDeck().get(1).size() != 0 && p1.Get_player_gold_in_hand() > 5){
					p1.get_PlayHand().add(Deck.getVCDeck().get(1).remove(0));
					Bought_Card = true;
				}
				while(safe == false){
					int randomVal = RandNumbers.getRand(Deck.getActionDeck().size());
					if (CheckifPileIsEmpty(randomVal) == true)
						safe = false;
					else{ 
						safe = true;
						rand = randomVal;
					}
				}
				CheckifPileIsEmpty(rand);
				int Player_1_Gold = p1.Get_player_gold_in_hand();
				if (Player_1_Gold < Deck.getActionDeck().get(rand).get(0).getCost()){
				//System.out.println("Not enough Gold");
					buyAttempts++;
					if (buyAttempts > 30){
						if (CheckMoneyPile(0) == false)
							p1.get_PlayHand().add(Deck.getMoneyDeck().get(0).remove(0)); //remove a copper
						return;
					}
				}

				else {
					Cards Bought = Deck.getActionDeck().get(rand).remove(0);
					if (Bought.getCost() != 0)
						p1.PayPiper(Bought.getCost());
					p1.get_PlayHand().add(Bought);
					Bought_Card = true;
				}
			
			}while(Bought_Card == false);
			Bought_Card = false;
			safe = false;
		}
		p1.Player_Buy_Turns = 1;
		p1.newHand();

	}
	
	public static void main(String[] args){
		Initialize_Game();
		System.out.println("\nStarting Game!");
		Play_Game();
	}
}