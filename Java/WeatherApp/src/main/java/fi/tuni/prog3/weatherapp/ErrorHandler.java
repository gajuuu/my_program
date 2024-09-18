package fi.tuni.prog3.weatherapp;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

/**
 * Display an error message to the user.
 *
 * @author biswa.upreti
 */
public class ErrorHandler {

    /**
     * Creates alert for error message.
     *
     * @param errorMessage The error message to show in the alert.
     */
    public static void showError(String errorMessage) {
        Alert alert = new Alert(AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText(null);
        alert.setContentText(errorMessage);
        alert.showAndWait();
    }
}
