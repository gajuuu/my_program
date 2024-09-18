package fi.tuni.prog3.weatherapp;

import javafx.application.Application;

import javafx.stage.Stage;
import java.io.IOException;
import static javafx.application.Application.launch;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;

/**
 * Loads a fxml file and Starts app.
 *
 * @author mikhail silaev
 */
public class WeatherAppXML extends Application {

    private static Scene scene;

    /**
     * Sets base format.
     *
     * @param stage
     * @throws java.io.IOException
     */
    @Override
    public void start(Stage stage) throws IOException {
        scene = new Scene(loadFXML("weather"), 500, 700);

        stage.setScene(scene);
        stage.setTitle("WeatherApp");
        stage.show();
    }

    /**
     * Loads a fxml file.
     */
    private static Parent loadFXML(String fxml) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(
                WeatherAppXML.class.getResource(fxml + ".fxml"));
        return fxmlLoader.load();
    }

    /**
     * Start app.
     */
    public static void main(String[] args) {
        launch();
    }
}
