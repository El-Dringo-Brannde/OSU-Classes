/*
 * This file was automatically generated by EvoSuite
 * Thu Mar 16 00:04:29 GMT 2017
 */

package org.cs362.dominion;

import org.junit.Test;
import static org.junit.Assert.*;
import static org.evosuite.runtime.EvoAssertions.*;
import java.util.List;
import org.cs362.dominion.Randomness;
import org.evosuite.runtime.EvoRunner;
import org.evosuite.runtime.EvoRunnerParameters;
import org.evosuite.runtime.Random;
import org.junit.runner.RunWith;

@RunWith(EvoRunner.class) @EvoRunnerParameters(mockJVMNonDeterminism = true, useVFS = true, useVNET = true, resetStaticState = true, separateClassLoader = true, useJEE = true) 
public class Randomness_ESTest extends Randomness_ESTest_scaffolding {

  @Test(timeout = 4000)
  public void test0()  throws Throwable  {
      Random.setNextRandom((-2877));
      int int0 = Randomness.nextRandomInt((-562));
      assertEquals(67, int0);
  }

  @Test(timeout = 4000)
  public void test1()  throws Throwable  {
      Randomness.random = null;
      // Undeclared exception!
      try { 
        Randomness.nextRandomInt(0);
        fail("Expecting exception: NullPointerException");
      
      } catch(NullPointerException e) {
         //
         // no message in exception (getMessage() returned null)
         //
         verifyException("org.cs362.dominion.Randomness", e);
      }
  }

  @Test(timeout = 4000)
  public void test2()  throws Throwable  {
      // Undeclared exception!
      try { 
        Randomness.nextRandomInt(0);
        fail("Expecting exception: ArithmeticException");
      
      } catch(ArithmeticException e) {
         //
         // no message in exception (getMessage() returned null)
         //
      }
  }

  @Test(timeout = 4000)
  public void test3()  throws Throwable  {
      // Undeclared exception!
      try { 
        Randomness.randomMember((List<String>) null);
        fail("Expecting exception: IllegalArgumentException");
      
      } catch(IllegalArgumentException e) {
         //
         // Expected non-empty list
         //
         verifyException("org.cs362.dominion.Randomness", e);
      }
  }

  @Test(timeout = 4000)
  public void test4()  throws Throwable  {
      int int0 = Randomness.nextRandomInt((-3478));
      assertEquals(0, int0);
  }

  @Test(timeout = 4000)
  public void test5()  throws Throwable  {
      Randomness.reset((-1680L));
  }
}