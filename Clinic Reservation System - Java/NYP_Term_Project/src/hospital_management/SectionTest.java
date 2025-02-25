package hospital_management;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import java.util.LinkedList;

public class SectionTest {

    private Section section;
    private Doctor doctor1;
    private Doctor doctor2;

    @Before
    public void setUp() {
        section = new Section(1, "Cardiology");
        doctor1 = new Doctor("Yakup Gulcan", 10457, 20147, 3);
        doctor2 = new Doctor("Said Gunduz", 10369, 20497,5);
    }

    @Test
    public void testAddDoctor() throws DuplicateInfoException {
        section.addDoctor(doctor1);
        section.addDoctor(doctor2);

        LinkedList<Doctor> doctors = section.getDoctors();
        assertTrue(doctors.contains(doctor1));
        assertTrue(doctors.contains(doctor2));
    }

    @Test(expected = DuplicateInfoException.class)
    public void testAddDoctorWithSameDiploma() throws DuplicateInfoException {
        section.addDoctor(doctor1);
        section.addDoctor(doctor1); 
    }

    @Test
    public void testGetDoctor() throws DuplicateInfoException {
        section.addDoctor(doctor1);
        Doctor d = section.getDoctor(doctor1.getDiploma_id());
        assertEquals(doctor1, d);
    }
}
