package hospital_management;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import java.time.LocalDate;

public class RendezvousTest {

    private Rendezvous rendezvous;
    private Patient patient;
    private LocalDate dateTime;

    @Before
    public void setUp() {
        patient = new Patient("Mehmet Normal", 30); 
        dateTime = LocalDate.of(2025, 1, 15);
        rendezvous = new Rendezvous(patient, dateTime);
    }

    @Test
    public void testGetDateTime() {
        assertEquals(dateTime, rendezvous.getDateTime());
    }

    @Test
    public void testGetPatient() {
        assertEquals(patient, rendezvous.getPatient());
    }

    @Test
    public void testToString() {
        String expected = "Rendezvous : Time = " + dateTime + " - Patient = " + patient;
        assertEquals(expected, rendezvous.toString());
    }
}
