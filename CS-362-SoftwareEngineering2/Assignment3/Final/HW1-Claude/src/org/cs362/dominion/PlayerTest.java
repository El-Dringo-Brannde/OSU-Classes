package org.cs362.dominion;

import static org.junit.Assert.*;
import java.util.ArrayList;
import java.util.List;
import org.junit.Before;
import org.junit.Test;

public class PlayerTest {
	private List<Card> cardList;
	private Player playerA;
	private Player playerB;
	private GameState gameState;
	
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

	
}
