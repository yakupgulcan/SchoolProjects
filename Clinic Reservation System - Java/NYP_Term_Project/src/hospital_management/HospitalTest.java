package hospital_management;

import static org.junit.Assert.*;
import org.junit.*;


public class HospitalTest {
    private Hospital hospital;
    
    @Before
    public void setUp() {
        hospital = new Hospital(247, "Medicana");
    }
    
    @Test
    public void testAddSection() throws Exception {
        Section section = new Section(567, "HeartIssues");
        hospital.addSection(section);
        assertEquals(section, hospital.getSection(567));
        assertEquals(1, hospital.getSections().size());
    }
    
    @Test
    public void testGetSectionID() throws Exception {
        Section section = new Section(567, "HeartIssues");
        hospital.addSection(section);
        Section s = hospital.getSection("HeartIssues");
        assertEquals(567, s.getId());
    }
    
    @Test(expected = DuplicateInfoException.class) 
    public void testAddingWithSameID() throws Exception {
        Section section = new Section(567, "HeartIssues");
        Section section_2 = new Section(567, "Cancer Issues");
        
        hospital.addSection(section);
        hospital.addSection(section_2);
    }
}