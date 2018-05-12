package dominion;

import static org.junit.Assert.*;

import org.junit.Test;

public class CardsTest {

	@Test
	public void testCardsandString() {
		Cards C = new Cards("Test", 0,0,"Action",false);
		assertEquals(C.toString(), "Test 0 0 Action false");
	}
	
	@Test
	public void testGetName(){
		Cards C = new Cards("Test", 0,0,"Action",false);
		assertEquals(C.getName(), "Test");
	}
	
	@Test 
	public void testgetToken(){
		Cards good = new Cards("Test", 0,0,"Action",false);
		assertEquals(good.getToken(), false);
		Cards bad = new Cards("Test", 0,0,"Action",true);
		assertEquals(bad.getToken(), true);
	}
	
	@Test
	public void testCost(){
		Cards C = new Cards("Test", 0,0,"Action",false);
		assertEquals(C.getCost(), 0);
	}
	
	@Test
	public void testEmbargo(){
		Cards C = new Cards("Test", 0,0,"Action",false);
		assertEquals(C.getToken(),false);
		C.addEmbargo();
		assertEquals(C.getToken(),true);
	}
	
	@Test
	public void testType(){
		Cards C = new Cards("Test", 0,0,"Action",false);
		assertEquals(C.getType(), "Action");	
	}

}
