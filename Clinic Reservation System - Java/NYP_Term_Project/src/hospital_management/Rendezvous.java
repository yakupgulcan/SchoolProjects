package hospital_management;

import java.io.Serializable;
import java.time.LocalDate;

public class Rendezvous implements Serializable {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private LocalDate dateTime;
	private Patient patient;

    public Rendezvous(Patient patient, LocalDate dateTime) {
    	this.patient = patient;
        this.dateTime = dateTime;
    }

    public LocalDate getDateTime() {
        return dateTime;
    }

    public void setDateTime(LocalDate dateTime) {
        this.dateTime = dateTime;
    }

	public Patient getPatient() {
		return patient;
	}
	
	
	@Override
	public String toString() {
	    return "Rendezvous : " + "Time = " + dateTime + " - Patient = " + patient;
	}

}

