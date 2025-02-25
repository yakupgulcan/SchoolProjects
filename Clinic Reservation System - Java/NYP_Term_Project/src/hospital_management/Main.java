package hospital_management;

import java.util.Scanner;

import javax.swing.SwingUtilities;


public class Main {
	public static void main(String[] args) {
		try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("Gui mode or not? enter true or false : ");
			boolean choice = scanner.nextBoolean();
			scanner.nextLine();
			
			if(choice) {
				SwingUtilities.invokeLater(() -> {
			        new GUI().setVisible(true);
			    });
				
			}else {
				CRS.launchCLI();
			}
		}
	}
}
