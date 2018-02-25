package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class Main extends Application {

    VBox vbox;
    Label command;
    TextField field;
    Button approve;

    @Override
    public void start(Stage primaryStage) throws Exception{

        vbox=new VBox();
        vbox.setSpacing(10);
        vbox.setPadding(new Insets(20,20,20,20));
        command =new Label("Proszę podać poprawne wyrażenie nawiasowe");
        command.setFont(new Font("Tahoma",18));

        vbox.getChildren().add(command);

        field=new TextField();
        field.setMinWidth(380);

        vbox.getChildren().add(field);

        approve=new Button("Tłumacz!");
        vbox.getChildren().add(approve);



        primaryStage.setTitle("To ONP Translator by Michal Rzepka");
        primaryStage.setScene(new Scene(vbox, 410, 200));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
