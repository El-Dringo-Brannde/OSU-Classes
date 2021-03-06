/*
 * This file was automatically generated by EvoSuite
 * Thu Mar 16 00:05:03 GMT 2017
 */

package org.cs362.dominion;

import org.junit.Test;
import static org.junit.Assert.*;
import static org.evosuite.runtime.EvoAssertions.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.Vector;
import org.cs362.dominion.Card;
import org.cs362.dominion.GameState;
import org.cs362.dominion.Player;
import org.evosuite.runtime.EvoRunner;
import org.evosuite.runtime.EvoRunnerParameters;
import org.junit.runner.RunWith;

@RunWith(EvoRunner.class) @EvoRunnerParameters(mockJVMNonDeterminism = true, useVFS = true, useVNET = true, resetStaticState = true, separateClassLoader = true, useJEE = true) 
public class Player_ESTest extends Player_ESTest_scaffolding {

  @Test(timeout = 4000)
  public void test00()  throws Throwable  {
      Player player0 = new Player((GameState) null, "2t:");
      player0.addCoins(5);
      player0.toString();
  }

  @Test(timeout = 4000)
  public void test01()  throws Throwable  {
      Player player0 = new Player((GameState) null, "]75u'DlrCrJ");
      player0.scoreFromPoints = 2530;
      player0.addScore((-1932));
  }

  @Test(timeout = 4000)
  public void test02()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.addScore(1);
  }

  @Test(timeout = 4000)
  public void test03()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.endTurn();
      player0.playKingdomCard();
      player0.playTtreasureCard();
      player0.endTurn();
  }

  @Test(timeout = 4000)
  public void test04()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.scoreFromPoints = 9;
      player0.endTurn();
      player0.endTurn();
      player0.playKingdomCard();
      player0.endTurn();
  }

  @Test(timeout = 4000)
  public void test05()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      Card.CardName card_CardName0 = Card.CardName.Cooper;
      Card card0 = Card.getCard(list0, card_CardName0);
      player0.gain(card0);
      player0.numActions = (-230);
      // Undeclared exception!
      try { 
        player0.endTurn();
        fail("Expecting exception: IndexOutOfBoundsException");
      
      } catch(IndexOutOfBoundsException e) {
         //
         // Index: 0, Size: 0
         //
         verifyException("java.util.ArrayList", e);
      }
  }

  @Test(timeout = 4000)
  public void test06()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.addScore((-2356));
      player0.initializePlayerTurn();
      player0.endTurn();
      player0.endTurn();
      player0.playKingdomCard();
      player0.buyCard();
  }

  @Test(timeout = 4000)
  public void test07()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      player0.numBuys = (-3325);
      player0.buyCard();
  }

  @Test(timeout = 4000)
  public void test08()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.coins = (-16);
      player0.playTtreasureCard();
  }

  @Test(timeout = 4000)
  public void test09()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.scoreFromPoints = 606;
      player0.scoreFor();
  }

  @Test(timeout = 4000)
  public void test10()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      player0.trash = (List<Card>) vector0;
      Card.CardName card_CardName0 = Card.CardName.Province;
      Card.Type card_Type0 = Card.Type.CURSE;
      Card card0 = new Card(card_CardName0, card_Type0, 1055, (-1010), 1055);
      player0.trash(card0);
      player0.gain(card0);
      player0.deck = (List<Card>) vector0;
      player0.drawCard();
      player0.scoreFor();
  }

  @Test(timeout = 4000)
  public void test11()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      Card.CardName card_CardName0 = Card.CardName.Cooper;
      Card card0 = Card.getCard(list0, card_CardName0);
      player0.gain(card0);
      player0.numActions = (-230);
      player0.scoreFor();
  }

  @Test(timeout = 4000)
  public void test12()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.scoreFor();
  }

  @Test(timeout = 4000)
  public void test13()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.numActions = (-230);
      player0.playKingdomCard();
  }

  @Test(timeout = 4000)
  public void test14()  throws Throwable  {
      ArrayList<Card> arrayList0 = new ArrayList<Card>();
      GameState gameState0 = new GameState((List<Card>) arrayList0);
      Player player0 = new Player(gameState0, "");
      Card.CardName card_CardName0 = Card.CardName.Mine;
      Card.Type card_Type0 = Card.Type.ACTION;
      Card card0 = new Card(card_CardName0, card_Type0, 2037, 2037, 2037);
      player0.gain(card0);
      player0.addScore(2037);
      // Undeclared exception!
      try { 
        player0.initializePlayerTurn();
        fail("Expecting exception: IndexOutOfBoundsException");
      
      } catch(IndexOutOfBoundsException e) {
         //
         // Index: 0, Size: 0
         //
         verifyException("java.util.ArrayList", e);
      }
  }

  @Test(timeout = 4000)
  public void test15()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.drawCard();
  }

  @Test(timeout = 4000)
  public void test16()  throws Throwable  {
      Player player0 = new Player((GameState) null, "");
      Card.CardName card_CardName0 = Card.CardName.Great_hall;
      Card.Type card_Type0 = Card.Type.TREASURE;
      Card card0 = new Card(card_CardName0, card_Type0, 89, 0, (-1516));
      player0.gain(card0);
      player0.drawCard();
  }

  @Test(timeout = 4000)
  public void test17()  throws Throwable  {
      Player player0 = new Player((GameState) null, "H0G*]U*iq-027T");
      // Undeclared exception!
      try { 
        player0.trash((Card) null);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test18()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      vector0.add((Card) null);
      player0.deck = (List<Card>) vector0;
      // Undeclared exception!
      try { 
        player0.scoreFor();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test19()  throws Throwable  {
      Player player0 = new Player((GameState) null, "");
      // Undeclared exception!
      try { 
        player0.printStateGame();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test20()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "Adventurer: showing deck cards until showed 2 treasure cards");
      // Undeclared exception!
      try { 
        player0.played((Card) null);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test21()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState((List<Card>) null);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.endTurn();
      player0.playedCards = null;
      // Undeclared exception!
      try { 
        player0.playKingdomCard();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test22()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      vector0.add((Card) null);
      player0.deck = (List<Card>) vector0;
      // Undeclared exception!
      try { 
        player0.initializePlayerTurn();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test23()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      player0.deck = (List<Card>) vector0;
      // Undeclared exception!
      try { 
        player0.initializePlayerTurn();
        fail("Expecting exception: ArrayIndexOutOfBoundsException");
      
      } catch(ArrayIndexOutOfBoundsException e) {
         //
         // Array index out of range: 0
         //
         verifyException("java.util.Vector", e);
      }
  }

  @Test(timeout = 4000)
  public void test24()  throws Throwable  {
      Player player0 = new Player((GameState) null, "2t:");
      // Undeclared exception!
      try { 
        player0.gain((Card) null);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test25()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.discard = list0;
      // Undeclared exception!
      player0.endTurn();
  }

  @Test(timeout = 4000)
  public void test26()  throws Throwable  {
      GameState gameState0 = new GameState((List<Card>) null);
      Player player0 = new Player(gameState0, "_gH$fzXl`f");
      player0.discard = null;
      // Undeclared exception!
      try { 
        player0.endTurn();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test27()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      player0.deck = (List<Card>) vector0;
      // Undeclared exception!
      try { 
        player0.endTurn();
        fail("Expecting exception: ArrayIndexOutOfBoundsException");
      
      } catch(ArrayIndexOutOfBoundsException e) {
         //
         // Array index out of range: 0
         //
         verifyException("java.util.Vector", e);
      }
  }

  @Test(timeout = 4000)
  public void test28()  throws Throwable  {
      GameState gameState0 = new GameState((List<Card>) null);
      Player player0 = new Player(gameState0, (String) null);
      player0.discard = null;
      // Undeclared exception!
      try { 
        player0.drawCard();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test29()  throws Throwable  {
      Stack<Card> stack0 = new Stack<Card>();
      GameState gameState0 = new GameState((List<Card>) stack0);
      Player player0 = new Player(gameState0, (String) null);
      player0.deck = (List<Card>) stack0;
      // Undeclared exception!
      try { 
        player0.drawCard();
        fail("Expecting exception: ArrayIndexOutOfBoundsException");
      
      } catch(ArrayIndexOutOfBoundsException e) {
         //
         // Array index out of range: 0
         //
         verifyException("java.util.Vector", e);
      }
  }

  @Test(timeout = 4000)
  public void test30()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "");
      // Undeclared exception!
      try { 
        player0.discard((Card) null);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test31()  throws Throwable  {
      Stack<Card> stack0 = new Stack<Card>();
      GameState gameState0 = new GameState((List<Card>) stack0);
      Player player0 = new Player(gameState0, " to draw FIVE cards");
      Card.CardName card_CardName0 = Card.CardName.Cooper;
      Card.Type card_Type0 = Card.Type.VICTORY;
      Card card0 = new Card(card_CardName0, card_Type0, (-1), (-1), 17);
      player0.played(card0);
      assertEquals(17, card0.getTreasureValue());
  }

  @Test(timeout = 4000)
  public void test32()  throws Throwable  {
      Player player0 = new Player((GameState) null, "te:");
      Card.CardName card_CardName0 = Card.CardName.Council_room;
      Card.Type card_Type0 = Card.Type.VICTORY;
      Card card0 = new Card(card_CardName0, card_Type0, 5, 5, 5);
      player0.discard(card0);
      assertEquals(5, card0.score());
  }

  @Test(timeout = 4000)
  public void test33()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.initializePlayerTurn();
      player0.playKingdomCard();
      assertEquals(15, list0.size());
  }

  @Test(timeout = 4000)
  public void test34()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.endTurn();
      player0.playKingdomCard();
      player0.initializePlayerTurn();
      player0.endTurn();
      assertEquals(16, list0.size());
  }

  @Test(timeout = 4000)
  public void test35()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.initializePlayerTurn();
      // Undeclared exception!
      try { 
        player0.buyCard();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Player", e);
      }
  }

  @Test(timeout = 4000)
  public void test36()  throws Throwable  {
      Vector<Card> vector0 = new Vector<Card>();
      GameState gameState0 = new GameState((List<Card>) vector0);
      Player player0 = new Player(gameState0, "YCyv<+a3LZL5?)&(%");
      player0.printStateGame();
  }

  @Test(timeout = 4000)
  public void test37()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.addScore((-2356));
      String string0 = player0.toString();
      assertEquals(" ---  ---  --- --------------------------- --- Hand: []Discard: []Deck: []Played Cards: []numActions: 0coinss: 0numBuys: 0\n", string0);
  }

  @Test(timeout = 4000)
  public void test38()  throws Throwable  {
      List<Card> list0 = Card.createCards();
      GameState gameState0 = new GameState(list0);
      Player player0 = new Player(gameState0, "");
      player0.deck = list0;
      player0.endTurn();
      player0.playTtreasureCard();
      player0.buyCard();
      assertEquals(15, list0.size());
  }
}
