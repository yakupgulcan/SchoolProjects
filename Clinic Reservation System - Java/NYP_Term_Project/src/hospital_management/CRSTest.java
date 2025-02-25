package hospital_management;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import java.time.LocalDate;

public class CRSTest {

    private CRS crs;
    private Patient patient;
    private Hospital hospital;
    private Section section;
    private Doctor doctor;

    @Before
    public void setUp() {
        crs = new CRS();

        patient = new Patient("Mehmet Ucum", 123478);
        hospital = new Hospital(1, "Asema");
        section = new Section(1, "Cardiology");
        doctor = new Doctor("Said Gunduz", 10389, 20487, 2);

        section.addDoctor(doctor);
        hospital.addSection(section);
        crs.addHospital(hospital);
        crs.addPatient(patient);
    }

    @Test
    public void testMakeRendezvous() throws IDException {
        LocalDate date = LocalDate.of(2025, 1, 15);

        assertTrue(crs.makeRendezvous(123478, 1, 1, 20487, date));
    }

    @Test(expected = IDException.class)
    public void testMakeRendezvousWithNonExistingPatient() {
        LocalDate date = LocalDate.of(2025, 1, 15);
        
        crs.makeRendezvous(89665653, 1, 1, 20487, date);
    }


    @Test
    public void testMakeRendezvousReachingMaxPatient() throws IDException {
        LocalDate date = LocalDate.of(2025, 1, 15);

        crs.makeRendezvous(123478, 1, 1, 20487, date);
        crs.makeRendezvous(123478, 1, 1, 20487, date);

        assertFalse(crs.makeRendezvous(123478, 1, 1, 20487, date));
    }
}
