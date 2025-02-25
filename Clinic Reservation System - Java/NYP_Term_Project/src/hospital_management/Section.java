package hospital_management;

import java.io.Serializable;
import java.util.LinkedList;


public class Section implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int id;
	private String name;
	private LinkedList<Doctor> doctors;
	
	
	
	
	public Section(int id, String name) {
		this.id = id;
		this.name = name;
		doctors = new LinkedList<Doctor>();
	}


	public void listDoctors() {
		// list with for each
		System.out.println("Doctor's in the Section : " + name + " is listed below : ");
		for(Doctor doctor : this.doctors)
			System.out.println(doctor);
	}
	
	public Doctor getDoctor(int diploma_id) {
		for(Doctor d : doctors) {
			if(d.getDiploma_id() == diploma_id) {
				return d;
			}
		}
		return null;
	}
	
	public synchronized void addDoctor(Doctor doctor) throws DuplicateInfoException {
		if(getDoctor(doctor.getDiploma_id()) != null) {
			throw new DuplicateInfoException("The doctor that you want to add has same diploma_id with another doctor.");
		}
		
		doctors.add(doctor);
	}


	public int getId() {
		return id;
	}


	public String getName() {
		return name;
	}


	public LinkedList<Doctor> getDoctors() {
		return doctors;
	}
	
	@Override
	public String toString() {
		return id + " - " + name;
	}

}
