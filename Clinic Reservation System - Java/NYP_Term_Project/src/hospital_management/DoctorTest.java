package hospital_management;

import static org.junit.Assert.*;
import org.junit.*;

public class DoctorTest {
	private Doctor aDoctor = new Doctor("Yakup Gulcan", 10457L, 20148, 6);
	
	@Test
	public void testScheduleNotNull() {
		assertNotNull(aDoctor.getDr_schedule());		
	}
	
	@Test
	public void testGetDiplomaId() {
		assertEquals(20148, aDoctor.getDiploma_id());		
	}
	
	@Test
	public void testToStringMethod() {
		String expected = "Dr. Yakup Gulcan - Diploma ID : 20148 - Max Patient Per Day : 6";
		assertEquals(expected, aDoctor.toString());		
	}
	

}
