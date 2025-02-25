package hospital_management;

import java.util.LinkedList;


public class Doctor extends Person {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int diploma_id;
	private int maxPatientPerDay;
	private Schedule dr_schedule;
	
	public Doctor(String name, long national_id, int diploma_id, int maxPatientPerDay) {
		super(name, national_id);
		this.diploma_id = diploma_id;
		this.dr_schedule = new Schedule(maxPatientPerDay);
		this.maxPatientPerDay = maxPatientPerDay;
	}

	public Schedule getDr_schedule() {
		return dr_schedule;
	}

	public int getDiploma_id() {
		return diploma_id;
	}

	@Override
	public String toString() {
		return "Dr. " + this.getName() + " - Diploma ID : " + diploma_id + " - Max Patient Per Day : " + maxPatientPerDay ;
	}

	public void showSchedule() {
		System.out.println("Schedule for doctor :");
		LinkedList<Rendezvous> rendezvous = dr_schedule.getSessions();
		for(Rendezvous r : rendezvous) {
			System.out.println("Patient : " + r.getPatient() + " - Date : " + r.getDateTime() );
		}
	}
	

}
