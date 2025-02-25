package hospital_management;

import java.util.LinkedList;


import java.io.Serializable;
import java.time.LocalDate;


public class Schedule implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private LinkedList<Rendezvous> sessions;
	private int maxPatientPerDay;
	
	
	public Schedule(int maxPatientPerDay) {
		this.maxPatientPerDay = maxPatientPerDay;
		sessions = new LinkedList<Rendezvous>();
	}
	
	public synchronized boolean addRendezvous(Patient p, LocalDate desired) {
		// burada her doktora göre de kontrol edilebilir ya da hastaya göre bakmamız lazım.
		int counter = 0;
		for(Rendezvous r : sessions) {
			if((r.getDateTime().getYear() == desired.getYear()) && 
					(r.getDateTime().getDayOfYear() == desired.getDayOfYear())) {
				counter++;
			}
			
		}
		
		if(counter >= maxPatientPerDay) {
			System.out.print("Cannot add rendezvous because maxPatientLimit Reached. ");
			return false;
		}
		
		Rendezvous rendezvous = new Rendezvous(p, desired);
		sessions.add(rendezvous);
		
		
		return true;
	}

	
	public int getMaxPatientPerDay() {
		return maxPatientPerDay;
	}
	
	public Rendezvous getLastRendezvous() {
		
		
		return sessions.getLast();
		
	}

	public LinkedList<Rendezvous> getSessions() {
		return sessions;
	}
}
