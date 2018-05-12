package dominion;

import java.util.*;

class PlayDominion{
	static Player p1 = new Player("Player1");
	static Player p2 = new Player("Player2");
	static Deck AllDecks = new Deck();
	static RandNumbers Randoms = new RandNumbers();
	static public List<Player> Players = new ArrayList<Player>();


	public static void genPlayers(){
		int i = 0;
		while (i < 2){
			i = Randoms.getRand(5);
		}
		for (int j = 0; j < i; j++){
			Player p = new Player("Player" + (j+1));
			Players.add(p);
		}
	}


	public static void Initialize_Game(){
		Cards Copper, Estate;
		genPlayers();


		for (int j = 0; j < Players.size(); j++){
			Player p = Players.get(j);
			for (int i = 0; i < 7; i++){
				Copper = new Cards("Copper",1,0, "Money",false);
				p.GetDeck().add(Copper);
			}
			for (int i = 0; i < 3; i++){
				Estate = new Cards("Estate",2,1, "Victory",false);
				p.GetDeck().add(Estate);
			}

			Player.shuffle(p.GetDeck());

			for(int i = 0; i < 5; i++)
				p.Draw(0);
			p.Get_Player_Stats();
		}

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
		System.out.println(Players.toString());


		while (CheckEndGame() == false){
			for(int j = 0; j < Players.size();j++){
				System.out.println("Turn: " + i);
				PlayerTurn(Players.get(j));
				i++;
			}
		}

		for (i = 0; i < Players.size(); i++){
			Players.get(i).Get_Player_Stats();
			System.out.println(Players.get(i).getName()+ " Stats: " + Players.get(i).toString());
		}
		System.out.println("Exiting");
	}


	public static void PlayerTurn(Player p){
		System.out.println("========================= " + p.getName() + " Turn ============================= \n");
		Boolean Bought_Card = false;
		int Action_Card_Present = Player.Check_For_Action(p);
		int PlayCard = RandNumbers.getRand(2);
		int buyAttempts = 0;
		p.Player_Action_Turns = 1;
		p.Player_Buy_Turns = 1;


		System.out.println(p.getName() + " Rolled " + PlayCard);
		System.out.println(p.getName() + ": GOLD IN HAND " + p.Get_player_gold_in_hand() + p.get_PlayHand().toString());
		System.out.println("-------------------------Action Phase ----------------- \n");

		for(int i = 0; i < p.Player_Action_Turns; i++){
			Action_Card_Present = Player.Check_For_Action(p);
		if (Action_Card_Present == -1)
			System.out.println("No Action Cards to play. Moving to buy phase. \n");
		else {
				System.out.printf(p.getName() + " plays %s \n", p.get_PlayHand().get(Action_Card_Present).toString());
				Cards PlayMe = p.get_PlayHand().remove(Action_Card_Present);
				p.Play_Card(PlayMe,p,p);
			}
		}
		p.Player_Action_Turns = 1;
		System.out.println("-------------------------Buy Phase -------------------- \n");
		boolean safe = false;
		int rand = 0;
		//Get the size of the action deck and make it a rand value
		for(int i = 0; i < p.Player_Buy_Turns;i++){
			do {
				if (Deck.getVCDeck().get(2).size() != 0 && p.Get_player_gold_in_hand() > 8){
					p.get_PlayHand().add(Deck.getVCDeck().get(2).remove(0));
					Bought_Card = true;
				}
				else if (Deck.getVCDeck().get(1).size() != 0 && p.Get_player_gold_in_hand() > 5){
					p.get_PlayHand().add(Deck.getVCDeck().get(1).remove(0));
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
				int PlayerGold = p.Get_player_gold_in_hand();
				if (PlayerGold < Deck.getActionDeck().get(rand).get(0).getCost()){
					buyAttempts++;
					if (buyAttempts > 30){
						if (CheckMoneyPile(0) == false)
							p.get_PlayHand().add(Deck.getMoneyDeck().get(0).remove(0)); //remove a copper
						return;
					}
				}
				else {
					Cards Bought = Deck.getActionDeck().get(rand).remove(0);
					if (Bought.getCost() != 0)
						p.PayPiper(Bought.getCost());
					p.get_PlayHand().add(Bought);
					Bought_Card = true;
				}
			}while(Bought_Card == false);
			Bought_Card = false;
			safe = false;
		}
		p.Player_Buy_Turns = 1;
		p.newHand();
	}


 public static void main(String[] args){ 
 	Initialize_Game();
		System.out.println("\nStarting Game!");
		Play_Game();
	}
}
