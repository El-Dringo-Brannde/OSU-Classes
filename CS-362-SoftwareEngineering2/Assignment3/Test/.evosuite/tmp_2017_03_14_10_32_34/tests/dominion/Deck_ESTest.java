/*
 * This file was automatically generated by EvoSuite
 * Tue Mar 14 17:38:02 GMT 2017
 */

package dominion;

import org.junit.Test;
import static org.junit.Assert.*;
import static org.evosuite.runtime.EvoAssertions.*;
import dominion.Cards;
import dominion.Deck;
import dominion.PlayDominion;
import dominion.Player;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.NoSuchElementException;
import org.evosuite.runtime.EvoRunner;
import org.evosuite.runtime.EvoRunnerParameters;
import org.junit.runner.RunWith;

@RunWith(EvoRunner.class) @EvoRunnerParameters(mockJVMNonDeterminism = true, useVFS = true, useVNET = true, resetStaticState = true, separateClassLoader = true, useJEE = true) 
public class Deck_ESTest extends Deck_ESTest_scaffolding {

  @Test(timeout = 4000)
  public void test0()  throws Throwable  {
      Deck.Build_Money_Victory();
      Deck.Build_Action_Deck();
      Deck.getMoneyDeck();
      Deck.Build_Action_Deck();
      Deck.getVCDeck();
      Deck.getActionDeck();
      Deck.getActionDeck();
      Deck.getMoneyDeck();
      Deck.Build_Money_Victory();
      Deck.getMoneyDeck();
      Deck.getActionDeck();
      Deck.getActionDeck();
      Deck.curseCards = null;
      Deck deck0 = new Deck();
      Deck.Build_Money_Victory();
      PlayDominion.Players = null;
      Deck.getActionDeck();
      Deck.getVCDeck();
      Deck.Build_Action_Deck();
      Deck.getActionDeck();
      Deck.Build_Action_Deck();
      Deck.getMoneyDeck();
      Deck.getVCDeck();
      List<Cards> list0 = Deck.curseCards;
      // Undeclared exception!
      try { 
        Deck.Build_Money_Victory();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("dominion.Deck", e);
      }
  }

  @Test(timeout = 4000)
  public void test1()  throws Throwable  {
      Deck.Build_Money_Victory();
      Deck.getMoneyDeck();
  }

  @Test(timeout = 4000)
  public void test2()  throws Throwable  {
      Deck.Build_Action_Deck();
      LinkedList<Player> linkedList0 = new LinkedList<Player>();
      linkedList0.add((Player) null);
      linkedList0.add((Player) null);
      linkedList0.offerLast((Player) null);
      linkedList0.add((Player) null);
      PlayDominion.Players = (List<Player>) linkedList0;
      Deck.Build_Money_Victory();
      Deck.Build_Money_Victory();
      Deck deck0 = new Deck();
      Deck deck1 = new Deck();
      Deck.getActionDeck();
      Deck.Build_Action_Deck();
      List<Cards> list0 = Deck.curseCards;
  }

  @Test(timeout = 4000)
  public void test3()  throws Throwable  {
      Deck.Build_Money_Victory();
      Deck.getVCDeck();
      Deck.Build_Money_Victory();
      Deck.getMoneyDeck();
      List<Player> list0 = PlayDominion.Players;
      List<Cards> list1 = Deck.curseCards;
      Deck.getVCDeck();
      List<Cards> list2 = Deck.curseCards;
      Deck.getVCDeck();
      List<Cards> list3 = Deck.curseCards;
      PlayDominion.Players = list0;
      Deck.getMoneyDeck();
      Deck.Build_Money_Victory();
      Deck deck0 = new Deck();
      Deck.getVCDeck();
      Deck deck1 = new Deck();
      Deck deck2 = new Deck();
      Deck.getVCDeck();
  }

  @Test(timeout = 4000)
  public void test4()  throws Throwable  {
      List<Cards> list0 = Deck.curseCards;
      Deck.Build_Action_Deck();
      List<Cards> list1 = Deck.curseCards;
      Deck.Build_Money_Victory();
      Deck deck0 = new Deck();
      Deck.getMoneyDeck();
      List<Player> list2 = PlayDominion.Players;
      List<Player> list3 = PlayDominion.Players;
      Deck.Build_Money_Victory();
      Deck.Build_Action_Deck();
      Deck.getMoneyDeck();
      PlayDominion.Players = list3;
      Deck.getActionDeck();
      Deck.getActionDeck();
      LinkedList<Player> linkedList0 = new LinkedList<Player>();
      PlayDominion.Players = (List<Player>) linkedList0;
      Deck.getMoneyDeck();
      List<Player> list4 = PlayDominion.Players;
      Deck.getVCDeck();
      Deck.getVCDeck();
      Deck.getActionDeck();
      Deck.getActionDeck();
      List<Cards> list5 = Deck.curseCards;
      Deck.getVCDeck();
      Deck.getActionDeck();
  }

  @Test(timeout = 4000)
  public void test5()  throws Throwable  {
      LinkedList<Player> linkedList0 = new LinkedList<Player>();
      Player player0 = null;
      linkedList0.push((Player) null);
      int int0 = 4;
      LinkedList<Player> linkedList1 = new LinkedList<Player>();
      // Undeclared exception!
      try { 
        linkedList1.removeLast();
        fail("Expecting exception: NoSuchElementException");
      
      } catch(NoSuchElementException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("java.util.LinkedList", e);
      }
  }

  @Test(timeout = 4000)
  public void test6()  throws Throwable  {
      List<Cards> list0 = Deck.curseCards;
      Deck.curseCards = list0;
      Deck.Build_Money_Victory();
      List<Player> list1 = PlayDominion.Players;
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      Deck.Build_Money_Victory();
      Deck.getVCDeck();
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      PlayDominion.Players = list1;
      Deck.Build_Money_Victory();
      Deck.Build_Action_Deck();
      Deck deck0 = new Deck();
      Deck.Build_Action_Deck();
      Deck.getMoneyDeck();
      Deck.curseCards = deck0.curseCards;
      Deck.Build_Money_Victory();
      Deck.getMoneyDeck();
      Deck.Build_Money_Victory();
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      List<Cards> list2 = Deck.curseCards;
      Deck deck1 = new Deck();
      Deck deck2 = new Deck();
      Deck.Build_Money_Victory();
      Deck.getActionDeck();
      Deck deck3 = new Deck();
      Deck deck4 = new Deck();
  }

  @Test(timeout = 4000)
  public void test7()  throws Throwable  {
      Deck.getMoneyDeck();
      List<Cards> list0 = Deck.curseCards;
      Deck.getVCDeck();
      Deck.getActionDeck();
      List<Cards> list1 = Deck.curseCards;
      Deck.getMoneyDeck();
      Deck.getMoneyDeck();
      Deck deck0 = new Deck();
      Deck deck1 = new Deck();
      Deck.Build_Action_Deck();
      Deck.getActionDeck();
      List<Cards> list2 = Deck.curseCards;
      Deck.getMoneyDeck();
      Deck.getMoneyDeck();
      Deck.getVCDeck();
      Deck.getMoneyDeck();
      List<Cards> list3 = Deck.curseCards;
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      Deck.Build_Money_Victory();
      List<Player> list4 = PlayDominion.Players;
      Deck.getVCDeck();
      Deck.Build_Money_Victory();
      Deck.Build_Action_Deck();
      List<Cards> list5 = Deck.curseCards;
      Deck.getVCDeck();
      Deck.getVCDeck();
  }

  @Test(timeout = 4000)
  public void test8()  throws Throwable  {
      List<List<Cards>> list0 = Deck.getMoneyDeck();
      assertTrue(list0.isEmpty());
      
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      Deck.Build_Money_Victory();
      Deck deck0 = new Deck();
      LinkedList<Player> linkedList0 = new LinkedList<Player>();
      linkedList0.add((Player) null);
      linkedList0.add((Player) null);
      linkedList0.pollFirst();
      linkedList0.add(0, (Player) null);
      linkedList0.addFirst((Player) null);
      PlayDominion.Players = (List<Player>) linkedList0;
      Deck.getActionDeck();
      Deck deck1 = new Deck();
      Deck.getActionDeck();
      Deck.getActionDeck();
      Deck.getActionDeck();
      Deck.Build_Money_Victory();
      Deck.getActionDeck();
      PlayDominion.Players = (List<Player>) linkedList0;
      Deck.getMoneyDeck();
      List<Cards> list1 = Deck.curseCards;
      Deck.Build_Action_Deck();
      Deck.Build_Action_Deck();
      Deck deck2 = new Deck();
      List<List<Cards>> list2 = Deck.getActionDeck();
      assertEquals(40, list2.size());
  }
}
