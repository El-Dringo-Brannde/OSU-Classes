package dominion;import java.util.*;

class Deck{

//----------------------------Money Card Deck ----------------
	private static List<List<Cards>> MoneyCardDeck = new ArrayList<List<Cards>>();
//----------------------------Monies--------------------------
	private static List<Cards> Coppers = new ArrayList<Cards>();
	private static List<Cards> Silvers = new ArrayList<Cards>();
	private static List<Cards> Golds = new ArrayList<Cards>();

//----------------------------Victory Card Deck --------------
	private static List<List<Cards>> VictoryCardDeck = new ArrayList<List<Cards>>();
//----------------------------Victory Cards ------------------
	private static List<Cards> Estates = new ArrayList<Cards>();
	private static List<Cards> Duchies = new ArrayList<Cards>();
	private static List<Cards> Provinces = new ArrayList<Cards>();
	private static List<Cards> Curses  = new ArrayList<Cards>();

//----------------------------Action Card Deck --------------------
	private static List<List<Cards>> ActionCardDeck = new ArrayList<List<Cards>>();
//----------------------------Action Cards ----------------
	private static List<Cards> Adventurers = new ArrayList<Cards>();
	private static List<Cards> Ambassadors = new ArrayList<Cards>();
	private static List<Cards> Barons = new ArrayList<Cards>();
	private static List<Cards> CouncilRooms = new ArrayList<Cards>();
	private static List<Cards> CutPurses = new ArrayList<Cards>();
	private static List<Cards> Embargos = new ArrayList<Cards>();
	private static List<Cards> Feasts = new ArrayList<Cards>();
	private static List<Cards> Gardens = new ArrayList<Cards>();
	private static List<Cards> GreatHalls = new ArrayList<Cards>();
	private static List<Cards> Mines = new ArrayList<Cards>();
	private static List<Cards> Villages = new ArrayList<Cards>();
	private static List<Cards> Workshops = new ArrayList<Cards>();
	private static List<Cards> Markets = new ArrayList<Cards>();

	public static List<Cards> curseCards = new ArrayList<Cards>();


	public static List<List<Cards>> getActionDeck(){return ActionCardDeck;}

	public static List<List<Cards>> getMoneyDeck(){return MoneyCardDeck;}

	public static List<List<Cards>> getVCDeck(){return VictoryCardDeck;}

    //ActionCardDeck -> Various Decks -> Each Respective card
	public static void Build_Action_Deck(){
	    String[] CardNames = {"Adventurer", "Ambassador", "Baron","CouncilRoom", "CutPurse",
	    		"Embargo","Feast","Garden","GreatHall","Mine","Village","Workshop","Market"};
	    int CardCosts[] = {6,3,4,5,4,2,4,4,3,5,3,3,5}; //corresponds with Card cost values
	    int VictoryPoints[] = {0,0,0,0,0,0,0,0,1,0,0,0,0}; // Victory Point values
	    Cards ActionCards = null;

	    ActionCardDeck.add(Adventurers);
	    ActionCardDeck.add(Ambassadors);
	    ActionCardDeck.add(Barons);
	    ActionCardDeck.add(CouncilRooms);
	    ActionCardDeck.add(CutPurses);
	    ActionCardDeck.add(Embargos);
	    ActionCardDeck.add(Feasts);
	    ActionCardDeck.add(Gardens);
	    ActionCardDeck.add(GreatHalls);
	    ActionCardDeck.add(Mines);
	    ActionCardDeck.add(Villages);
	    ActionCardDeck.add(Workshops);
	    ActionCardDeck.add(Markets);
	    int i = 0;
	    for( i = 0; i < CardNames.length; i++)
	    	for (int j = 0; j < 10; j++){
	    		ActionCards = new Cards(CardNames[i],CardCosts[i],VictoryPoints[i], "Action", false);
	    		ActionCardDeck.get(i).add(ActionCards);
	    	}
	    //Get rid of 3 of the cards to make it 'random' 
	    Collections.shuffle(ActionCardDeck);
	    for( i = 0; i < 3; i++){
	    	ActionCardDeck.get(0).clear();
	    	ActionCardDeck.remove(0);
	    }
	}



	public static void Build_Money_Victory(){
		Cards EstateCard = null;
		VictoryCardDeck.add(Estates);
		VictoryCardDeck.add(Duchies);
		VictoryCardDeck.add(Provinces);
		VictoryCardDeck.add(Curses);
		String[] Victory_Cards = {"Estate","Duchy", "Province","Curse"};
		int[] V_Card_Cost = {2,5,8,0};
		int[] V_Card_Points = {1,3,6,-1};
		int i = 0;
		for (i = 0; i < 3; i++)
			for (int j = 0; j < 12; j++){
				EstateCard = new Cards(Victory_Cards[i],V_Card_Cost[i],V_Card_Points[i], "Victory",false);
				VictoryCardDeck.get(i).add(EstateCard);
			}
		Cards Curse = null;
		int limit = 0;
		i = 0;
		if (PlayDominion.Players.size() == 3)
			limit = 20;
		else if (PlayDominion.Players.size() == 4)
			limit = 30;
		else
			limit = 10;
		while(i != limit){ // Add curse Cards to size of players playing
			Curse = new Cards("Curse",0,-1,"Victory",false);
			VictoryCardDeck.get(3).add(Curse);
			i++;
		}

		MoneyCardDeck.add(Coppers);
		MoneyCardDeck.add(Silvers);
		MoneyCardDeck.add(Golds);

		Cards CopperCard = null;
		for (i = 0; i < 60; i++){
			CopperCard = new Cards("Copper", 1,0, "Money",false);
			MoneyCardDeck.get(0).add(CopperCard);
		}

		Cards SilverCard = null;
		for (i = 0; i < 40; i++){
			SilverCard = new Cards("Silver", 3,0,"Money",false);
			MoneyCardDeck.get(1).add(SilverCard);
		}

		Cards GoldCard = null;
		for(i = 0; i < 30; i++){
			GoldCard = new Cards("Gold", 6, 0,"Money",false);
			MoneyCardDeck.get(2).add(GoldCard);
		}
	}
}
