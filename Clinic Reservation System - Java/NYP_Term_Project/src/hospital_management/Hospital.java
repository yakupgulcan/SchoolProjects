package hospital_management;

import java.io.Serializable;
import java.util.LinkedList;


public class Hospital implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int id;
	private String name;
	private LinkedList<Section> sections;
	

	public LinkedList<Section> getSections() {
		return sections;
	}

	public Hospital(int id, String name) {
		this.id = id;
		this.name = name;
		sections = new LinkedList<Section>();
	}
	
	public Section getSection(int id) {
		for(Section s : sections) {
			if(s.getId() == id) {
				return s;
			}
		}
		return null;
	}
	
	public Section getSection(String name) {
		for(Section s : sections) {
			if(s.getName() == name) {
				return s;
			}
		}
		return null;
	}
	
	public synchronized void addSection(Section section) throws DuplicateInfoException{
		if(getSection(section.getName()) != null || getSection(section.getId()) != null) {
			throw new DuplicateInfoException("The section that you want to add has same id with another section.");
		}
		
		sections.add(section);
	}
	
	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	@Override
	public String toString() {
		return id + " - " + name;
	}

}
