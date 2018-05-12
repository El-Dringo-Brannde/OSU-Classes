/*
 * This file was automatically generated by EvoSuite
 * Tue Mar 14 18:44:59 GMT 2017
 */

package dominion;

import org.junit.Test;
import static org.junit.Assert.*;
import static org.evosuite.runtime.EvoAssertions.*;
import dominion.Deck;
import dominion.PlayDominion;
import dominion.Player;
import dominion.RandNumbers;
import java.util.List;
import org.evosuite.runtime.EvoRunner;
import org.evosuite.runtime.EvoRunnerParameters;
import org.junit.runner.RunWith;

@RunWith(EvoRunner.class) @EvoRunnerParameters(mockJVMNonDeterminism = true, useVFS = true, useVNET = true, resetStaticState = true, separateClassLoader = true, useJEE = true) 
public class PlayDominion_ESTest extends PlayDominion_ESTest_scaffolding {

  @Test(timeout = 4000)
  public void test00()  throws Throwable  {
      PlayDominion playDominion0 = new PlayDominion();
      // Undeclared exception!
      try { 
        PlayDominion.CheckMoneyPile((-233));
        fail("Expecting exception: ArrayIndexOutOfBoundsException");
      
      } catch(ArrayIndexOutOfBoundsException e) {
         //
         // no message in exception (getMessage() returned null)
         //
      }
  }

  @Test(timeout = 4000)
  public void test01()  throws Throwable  {
      PlayDominion.Players = null;
      RandNumbers randNumbers0 = PlayDominion.Randoms;
      // Undeclared exception!
      try { 
        PlayDominion.Play_Game();
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.evosuite.runtime.System", e);
      }
  }

  @Test(timeout = 4000)
  public void test02()  throws Throwable  {
      PlayDominion.p2 = null;
      Player player0 = PlayDominion.p1;
      Player player1 = PlayDominion.p2;
      // Undeclared exception!
      try { 
        PlayDominion.PlayerTurn((Player) null);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("dominion.PlayDominion", e);
      }
  }

  @Test(timeout = 4000)
  public void test03()  throws Throwable  {
      Player player0 = PlayDominion.p2;
      PlayDominion.p2 = player0;
      PlayDominion.PlayerTurn(player0);
  }

  @Test(timeout = 4000)
  public void test04()  throws Throwable  {
      Deck deck0 = PlayDominion.AllDecks;
      PlayDominion.AllDecks = deck0;
      PlayDominion.CheckMoneyPile(0);
      String[] stringArray0 = new String[5];
      String string0 = "Silver";
      stringArray0[0] = string0;
      String string1 = ":_B.n$TBqEq|~0mVF";
      stringArray0[1] = string1;
      String string2 = "";
      stringArray0[2] = string2;
      String string3 = "dominion.PlayDominion";
      stringArray0[3] = string3;
      String string4 = "{Z.Xj4?\\YizdW~";
      stringArray0[4] = string4;
      // Undeclared exception!
      PlayDominion.main(stringArray0);
  }

  @Test(timeout = 4000)
  public void test05()  throws Throwable  {
      PlayDominion.CheckEndGame();
      PlayDominion.CheckEndGame();
      // Undeclared exception!
      PlayDominion.genPlayers();
  }

  @Test(timeout = 4000)
  public void test06()  throws Throwable  {
      Player player0 = PlayDominion.p1;
      String[] stringArray0 = new String[9];
      stringArray0[0] = "";
      stringArray0[1] = "";
      stringArray0[2] = "";
      stringArray0[3] = "U#\u0005{;&=V$";
      stringArray0[4] = "";
      stringArray0[5] = "No Estate cards found in hand\n";
      stringArray0[6] = "";
      stringArray0[7] = "";
      stringArray0[8] = "| Victory Points: ";
      // Undeclared exception!
      PlayDominion.main(stringArray0);
  }

  @Test(timeout = 4000)
  public void test07()  throws Throwable  {
      Deck deck0 = PlayDominion.AllDecks;
      RandNumbers randNumbers0 = PlayDominion.Randoms;
      PlayDominion.Randoms = randNumbers0;
      List<Player> list0 = PlayDominion.Players;
      PlayDominion.Players = list0;
      Player player0 = PlayDominion.p2;
      PlayDominion.p2 = player0;
      // Undeclared exception!
      PlayDominion.genPlayers();
  }

  @Test(timeout = 4000)
  public void test08()  throws Throwable  {
      int int0 = (-2620);
      // Undeclared exception!
      try { 
        PlayDominion.CheckifPileIsEmpty((-2620));
        fail("Expecting exception: ArrayIndexOutOfBoundsException");
      
      } catch(ArrayIndexOutOfBoundsException e) {
         //
         // no message in exception (getMessage() returned null)
         //
      }
  }

  @Test(timeout = 4000)
  public void test09()  throws Throwable  {
      List<Player> list0 = PlayDominion.Players;
      PlayDominion.Players = list0;
      Deck deck0 = PlayDominion.AllDecks;
      PlayDominion playDominion0 = new PlayDominion();
      PlayDominion.Players = list0;
      // Undeclared exception!
      try { 
        PlayDominion.CheckifPileIsEmpty(635);
        fail("Expecting exception: IndexOutOfBoundsException");
      
      } catch(IndexOutOfBoundsException e) {
         //
         // Index: 635, Size: 60
         //
         verifyException("java.util.ArrayList", e);
      }
  }

  @Test(timeout = 4000)
  public void test10()  throws Throwable  {
      PlayDominion playDominion0 = new PlayDominion();
      Player player0 = PlayDominion.p1;
      PlayDominion.PlayerTurn(player0);
      PlayDominion playDominion1 = new PlayDominion();
      PlayDominion.p2 = player0;
      // Undeclared exception!
      PlayDominion.genPlayers();
  }

  @Test(timeout = 4000)
  public void test11()  throws Throwable  {
      PlayDominion.Play_Game();
      List<Player> list0 = PlayDominion.Players;
      PlayDominion.Play_Game();
      int int0 = 703;
      // Undeclared exception!
      try { 
        PlayDominion.CheckifPileIsEmpty(int0);
        fail("Expecting exception: IndexOutOfBoundsException");
      
      } catch(IndexOutOfBoundsException e) {
         //
         // Index: 703, Size: 60
         //
         verifyException("java.util.ArrayList", e);
      }
  }

  @Test(timeout = 4000)
  public void test12()  throws Throwable  {
      // Undeclared exception!
      PlayDominion.Initialize_Game();
  }
}
