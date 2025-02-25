package hospital_management;

import static org.junit.Assert.*;

import org.junit.*;

import java.time.LocalDate;

public class ScheduleTest {

    private Schedule schedule;
    private Patient patient1;
    private Patient patient2;
    private LocalDate date;

    @Before
    public void setUp() {
        schedule = new Schedule(2); 
        patient1 = new Patient("Yakup Gulcan", 30);
        patient2 = new Patient("Said Gunduz", 28);
        date = LocalDate.of(2025, 1, 15);
    }

    @Test
    public void testAddRendezvous() {
        assertTrue(schedule.addRendezvous(patient1, date));
        assertTrue(schedule.addRendezvous(patient2, date));
        assertEquals(2, schedule.getSessions().size());
    }

    @Test
    public void testAddRendezvousMaxPatient() {
        schedule.addRendezvous(patient1, date);
        schedule.addRendezvous(patient2, date);

        Patient patient3 = new Patient("Ahmet Colak", 40);
        assertFalse(schedule.addRendezvous(patient3, date));
        assertEquals(2, schedule.getSessions().size());
    }
}
