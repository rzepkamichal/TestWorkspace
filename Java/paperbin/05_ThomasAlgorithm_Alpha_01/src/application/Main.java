package application;
	
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.ScrollPane.ScrollBarPolicy;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
public class Main extends Application {
	//below there are all needed variables
	private GridPane RWelcomeGrid,RCalculateGrid,RButtonGrid;
	private VBox RCalculateVB;
	private ScrollPane SPane;
	private Scene scene;
	private Button BApproveNumOfEq,	BCalculate;
	private Label LAskNumOfEq,LTitle,LError1,LError2,LSolutionsText;
	private TextField TFNumOfEq;
	private TextField[] TFTabA, TFTabB,TFTabC,TFTabD;
	private Label[][] LTab;
	private Label[] LSolutions;
	private int NumberOfEq;
	private boolean check1, check2, check3;
	
	@Override
	public void start(Stage primaryStage) {
		try {
			RWelcomeGrid = new GridPane();//Create a GridPane for the "Welcome" layout
			RWelcomeGrid.setAlignment(Pos.CENTER);
			RWelcomeGrid.setHgap(20);//gap between columns
			RWelcomeGrid.setVgap(20);//gap between rows
			RWelcomeGrid.setPadding(new Insets(20,20,20,95));
			
				LAskNumOfEq=new Label("Podaj lczbê równañ:");//Set Label asking for the Number of Equations and add to GridPane
				LAskNumOfEq.setFont(new Font("Tahoma",20));
				RWelcomeGrid.add(LAskNumOfEq, 0, 4);
			
				TFNumOfEq=new TextField();//Set a Text Field to write the Number Of Equations into it and add to GridPane
				TFNumOfEq.setFont(new Font("Tahoma",15));
				TFNumOfEq.setMaxWidth(45);
				RWelcomeGrid.add(TFNumOfEq, 0, 5);
				RWelcomeGrid.setHalignment(TFNumOfEq, HPos.CENTER);
			
				BApproveNumOfEq=new Button("Zatwierd"+String.valueOf((char)(378)));//Set a button. On Click the app will get the Number Of Equations and will proove, if the user had given correct InputData
				BApproveNumOfEq.setFont(new Font("Tahoma",15));
				BApproveNumOfEq.setMinWidth(80);
				RWelcomeGrid.add(BApproveNumOfEq, 0, 6);
				RWelcomeGrid.setHalignment(BApproveNumOfEq, HPos.CENTER);
				
				LError1=new Label("");//Adding a Label, which will display an error, if the user gives a wrong value for the number of equations			
				LError1.setFont(new Font("Tahoma",14));
				LError1.setTextFill(Color.RED);
				RWelcomeGrid.setHalignment(LError1, HPos.CENTER);
				RWelcomeGrid.add(LError1, 0, 7);
				
			RCalculateGrid=new GridPane();//Create a GridPane for the "Calculate" Layout
			RCalculateGrid.setAlignment(Pos.TOP_LEFT);
			RCalculateGrid.setHgap(0);//gap between columns
			RCalculateGrid.setVgap(5);//gap between rows
			RCalculateGrid.setPadding(new Insets(10,0,0,1));
			
			RCalculateVB=new VBox();//Create a Vertical Box containing all elements of the "Calculate" Layout
			RCalculateVB.setPadding(new Insets(10));
			RCalculateVB.setSpacing(1);
			
			RButtonGrid=new GridPane();//Create a Grid Pane containing the "Calculate Button"
			RButtonGrid.setAlignment(Pos.TOP_LEFT);
			RButtonGrid.setHgap(0);//gap between columns
			RButtonGrid.setVgap(0);//gap between rows
			RButtonGrid.setPadding(new Insets(5,0,0,0));
				BCalculate=new Button("Licz!");//Set a button. On Click, the app will start to calculate and display the solutions
				BCalculate.setFont(new Font("Tahoma",13));
				BCalculate.setMinWidth(80);
				RButtonGrid.add(BCalculate, 0, 0);
						
			SPane=new ScrollPane(RWelcomeGrid);//Create a Scroll Pane which contains the other elements of the layout. It is needed when the number of equations is a great number.
			SPane.setVbarPolicy(ScrollBarPolicy.AS_NEEDED);
			
			scene = new Scene(SPane,370,400);// The Scroll Pane is the root of the scene. The Scroll Pane contains whether the "WelcomeGrid" or the "Calculate Vertical Box", the "Calculate VB" contains Labels including solutions and propmts for the user and also the GridPane in which the equation set is displayed
			primaryStage.setTitle("Thomas Algorithm");
			primaryStage.setScene(scene);
			primaryStage.show();
			
			check1=false;//if true, the user can go to the calculating section, if false, he will have to change the given "number of equations" to an integer
			check2=false;//if true, the the application can calculate solutions, if false, the user will have to change the values of coefficients, because they are wrong (when the are not numbers)
			check3=false;//if false, the app calculates and displays solutions for the first time, if true, the action gets repeated for the same amount of equations, so the labels which are representing the solutions only get changed and not added again					
			
			BApproveNumOfEq.setOnAction(new EventHandler<ActionEvent>(){//Starts method when the Approve Button is clicked
				@Override
				public void handle(ActionEvent arg0) {
					try{//check if the user has given an integer number of equations
						NumberApprover.checkout(Integer.parseInt(TFNumOfEq.getText()));
						check1=true;
					}catch(NumberFormatException e1){//display error if the user gives any other value than an integer number
						LError1.setText("B³¹d! Podaj liczbê"+"\n"+"ca³kowit¹ dodatni¹!");
						
					}
					
					//below, there is the main part of the body of the metod, which arranges and displays the set of equations, so that the user can give the appropriate values of coefficients
					
					if(check1){
						LError1.setText("");
						NumberOfEq=Integer.parseInt(TFNumOfEq.getText());//Initializing the value which comes from the first displayed textfield
						
						TFTabA=new TextField[NumberOfEq];//Declaring tables of text fields which will contain the value of each coefficient
						TFTabB=new TextField[NumberOfEq];
						TFTabC=new TextField[NumberOfEq];
						TFTabD=new TextField[NumberOfEq];
						LTab=new Label[NumberOfEq][6];//Declaring the table of labels, which will contain the set of unknowns and +/= signs for every equation
						
						for(int i=0;i<NumberOfEq;i++){//create instances of classes for every cell in each table and set prompt text(the number of the appropriate coefficient)
							TFTabA[i]=new TextField("a"+String.valueOf(i+1));
							TFTabB[i]=new TextField("b"+String.valueOf(i+1));
							TFTabC[i]=new TextField("c"+String.valueOf(i+1));
							TFTabD[i]=new TextField("d"+String.valueOf(i+1));
						}
						for(int i=0;i<NumberOfEq;i++){//Set width of Text Fields containing coefficients values
							TFTabA[i].setMaxWidth(45);
							TFTabB[i].setMaxWidth(45);
							TFTabC[i].setMaxWidth(45);
							TFTabD[i].setMaxWidth(45);
						}
						for(int i=0;i<NumberOfEq;i++){//create instances and set text for each label representing the unknowns
							if(i==0&&NumberOfEq==1){
								LTab[0][0]=new Label();
								LTab[0][1]=new Label(" x1 ");
								LTab[0][2]=new Label();
								LTab[0][3]=new Label();
								LTab[0][4]=new Label(" + ");
								LTab[0][5]=new Label(" = ");
							
							}else if(i==0&&NumberOfEq>1){
								LTab[0][0]=new Label();
								LTab[0][1]=new Label(" x1 ");
								LTab[0][2]=new Label(" x2 ");
								LTab[0][3]=new Label(" + ");
								LTab[0][4]=new Label(" + ");
								LTab[0][5]=new Label(" = ");
							
							}else if (i==NumberOfEq-1&&NumberOfEq>1){
								LTab[NumberOfEq-1][0]=new Label(" x"+String.valueOf(i)+" ");
								LTab[NumberOfEq-1][1]=new Label(" x"+String.valueOf(i+1)+" ");
								LTab[NumberOfEq-1][2]=new Label();
								LTab[NumberOfEq-1][3]=new Label();
								LTab[NumberOfEq-1][4]=new Label(" + ");
								LTab[NumberOfEq-1][5]=new Label(" = ");
							}else if(NumberOfEq>2){
						
								for(int j=0;j<6;j++){
									if(j<3)
										LTab[i][j]=new Label(" x"+String.valueOf(i+j)+" ");
									else if (j==3||j==4)
										LTab[i][j]=new Label(" + ");
									else
										LTab[i][j]=new Label(" = ");
								}		
							}
						}
						LError2=new Label("");//create the Label displaying "error", if the user gives wrong values of coefficients
						LError2.setFont(new Font("Tahoma",12));
						LTitle=new Label("Wprowad"+String.valueOf((char)(378))+" wspó³czynniki:");//create the Label which includes the prompt for the user to fill in text fields containing the values of coefficients
						LTitle.setFont(new Font("Tahoma",15));
						RCalculateVB.getChildren().add(LTitle);
					
						for(int i=0;i<NumberOfEq;i++){//Setting appropriate Text Fields and Labels for each equation into the scene
							if(i==0&&NumberOfEq==1){
								RCalculateGrid.add(TFTabB[0], 0, 1);
								RCalculateGrid.add(LTab[0][1], 1, 1);
								RCalculateGrid.add(LTab[0][5], 3, 1);
								RCalculateGrid.add(TFTabD[0], 4, 1);
							}else if(i==0&&NumberOfEq>1){
								RCalculateGrid.add(TFTabB[0], 0, 1);
								RCalculateGrid.add(LTab[0][1], 1, 1);
								RCalculateGrid.add(LTab[0][3], 2, 1);
								RCalculateGrid.add(TFTabC[0], 3, 1);
								RCalculateGrid.add(LTab[0][2], 4, 1);
								RCalculateGrid.add(LTab[0][5], 5, 1);
								RCalculateGrid.add(TFTabD[0], 6, 1);
							}else if(i==NumberOfEq-1&&NumberOfEq>1){
								RCalculateGrid.add(TFTabA[NumberOfEq-1], 0, NumberOfEq);
								RCalculateGrid.add(LTab[NumberOfEq-1][0], 1, NumberOfEq);
								RCalculateGrid.add(LTab[NumberOfEq-1][4], 2, NumberOfEq);
								RCalculateGrid.add(TFTabB[NumberOfEq-1], 3, NumberOfEq);
								RCalculateGrid.add(LTab[NumberOfEq-1][1], 4, NumberOfEq);
								RCalculateGrid.add(LTab[NumberOfEq-1][5], 5, NumberOfEq);
								RCalculateGrid.add(TFTabD[NumberOfEq-1], 6, NumberOfEq);
							}else if (NumberOfEq>2&&i<NumberOfEq-1){
								RCalculateGrid.add(TFTabA[i], 0, i+1);
								RCalculateGrid.add(LTab[i][0], 1, i+1);
								RCalculateGrid.add(LTab[i][3], 2, i+1);
								RCalculateGrid.add(TFTabB[i], 3, i+1);
								RCalculateGrid.add(LTab[i][1], 4, i+1);
								RCalculateGrid.add(LTab[i][4], 5, i+1);
								RCalculateGrid.add(TFTabC[i], 6, i+1);
								RCalculateGrid.add(LTab[i][2], 7, i+1);
								RCalculateGrid.add(LTab[i][5],8, i+1);
								RCalculateGrid.add(TFTabD[i], 9, i+1);
							}
						}	
						RCalculateVB.getChildren().add(RCalculateGrid);
						RCalculateVB.getChildren().add(RButtonGrid);
						RCalculateVB.getChildren().add(LError2);
						SPane.setContent(RCalculateVB);
						
						BCalculate.setOnAction(new EventHandler<ActionEvent>(){
							@Override
							public void handle(ActionEvent arg0) {
								try{//check if the user has only given numbers			
									for(int i=0;i<NumberOfEq;i++){
										if(i>1)
											IfDoubleApprover.check(Double.parseDouble(TFTabA[i].getText()));
								
										IfDoubleApprover.check(Double.parseDouble(TFTabB[i].getText()));
								
										if(i<NumberOfEq-1)
											IfDoubleApprover.check(Double.parseDouble(TFTabC[i].getText()));
										
										IfDoubleApprover.check(Double.parseDouble(TFTabD[i].getText()));
									
										if(i==NumberOfEq-1)
											check2=true;
									}
								}catch(NumberFormatException e2){//display error if the user gives wrong coefficients values, eg. a letter
									LError2.setText("B³¹d! Sprawd"+String.valueOf((char)(378))+", czy wszystkie wspó³czynniki"+"\n"+"zosta³y wpisane poprawnie!");
									LError2.setTextFill(Color.RED);
								}
								if(check2){
									LError2.setText("");
									Coefficients coeff=new Coefficients(NumberOfEq);
								
									for(int i=0;i<NumberOfEq;i++){
										if (i!=0)
											coeff.setCoeffa(i, Double.parseDouble(TFTabA[i].getText()));
									
										coeff.setCoeffb(i, Double.parseDouble(TFTabB[i].getText()));
									
										if(i!=NumberOfEq-1)
											coeff.setCoeffc(i, Double.parseDouble(TFTabC[i].getText()));
									
										coeff.setCoeffd(i, Double.parseDouble(TFTabD[i].getText()));
									}
									
									if(check3){
										LSolutionsText.setText("");
										for(int i=0;i<NumberOfEq;i++)
											LSolutions[i].setText("");
									}
									coeff.CalculateBetaGamma();//calculating the solutions
									coeff.CalculateSolution();
									if(!check3){
										LSolutions=new Label[NumberOfEq];
										LSolutionsText=new Label("Wyniki:");
										LSolutionsText.setFont(new Font("Tahoma",15));
										RCalculateVB.getChildren().add(LSolutionsText);
									}else
										LSolutionsText.setText("Wyniki:");
									
									for(int i=0;i<NumberOfEq;i++){
										if(!check3){
											LSolutions[i]=new Label("x"+String.valueOf(i+1)+" = "+String.valueOf(coeff.ExportSolution(i)));
											RCalculateVB.getChildren().add(LSolutions[i]);
										}else
											LSolutions[i].setText("x"+String.valueOf(i+1)+" = "+String.valueOf(coeff.ExportSolution(i)));
									}
									check3=true;
									check2=false;
								}
							}
						});
					}
				}});
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	public static void main(String[] args) {
		launch(args);
	}
}
