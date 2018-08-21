package ch.makery.address.view;

import ch.makery.address.MainApp;
import ch.makery.address.model.Person;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class PersonOverviewController {

	
	//All private fields need @FXML annotation
	
	@FXML
	private TableView<Person> personTable;
	@FXML
	private TableColumn<Person,String> firstNameColumn;
	@FXML
	private TableColumn<Person,String> lastNameColumn;
	
	@FXML
	private Label firstNameLabel;
	@FXML
	private Label lastNameLabel;
	@FXML
	private Label streetLabel;
	@FXML
	private Label postalCodeLabel;
	@FXML
	private Label cityLabel;
	@FXML
	private Label birthdayLabel;
	
	
	//create reference to the main App
	private MainApp mainApp;
	
	
	/* Constructor
	 * is called before the initialize() method !!!
	 */
	public PersonOverviewController() {
		
	}
	
	
	/* Initializes the contoller class.
	 * 
	 */
	
	/*Is called automaticly after fxmls have been loadad.
	 *Ad this time, all FXML fields should have been initialized !!!
	 */
	
	@FXML
	private void initialize() {
		
		/* setCellValueFactory(...) is used to determine which field inside Person objects should be used for the pariculat column.
		 * The -> indicates that we're using Lambda
		 * 
		 */
		
		//initialize the person table with the two columns
		
		firstNameColumn.setCellValueFactory(cellData -> cellData.getValue().firstNameProperty());
		lastNameColumn.setCellValueFactory(cellData -> cellData.getValue().lastNameProperty());
		
	}
	
	
	/**
	 * Is called by the main application to give a reference back to itself.
	 * @param mainApp
	 */
	public void setMainApp(MainApp mainApp) {
		this.mainApp = mainApp;
		
		//Add observable list data to the table
		personTable.setItems(mainApp.getPersonData());
	
	}
	
	
	
}




































