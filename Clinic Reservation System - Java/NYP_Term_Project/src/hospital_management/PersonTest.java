package hospital_management;

import static org.junit.Assert.*;
import org.junit.*;

public class PersonTest {
	private Person person;
	
	@Before
    public void setUp() {
        person = new Person("Yakup", 10457);
    }
	
	@Test
    public void testGetName() {
        setUp();
        assertEquals("Yakup", person.getName());
    }
	
	@Test
    public void testGetID() {
        setUp();
        assertEquals(10457, person.getNational_id());
    }
	
}
