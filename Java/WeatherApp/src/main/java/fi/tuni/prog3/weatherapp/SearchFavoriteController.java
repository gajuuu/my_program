package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import java.io.IOException;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.DialogPane;
import javafx.scene.control.Hyperlink;
import javafx.scene.control.TextInputDialog;
import javafx.scene.layout.VBox;

public class SearchFavoriteController extends TextInputDialog {

    private VBox hyperlinkContainer;

    // User activity data.
    public UserActivityModel activityData = new UserActivityModel();
    public WeatherDataFetcher fetcher = new WeatherDataFetcher();
    public WeatherAppController controller;

    /**
     * Constructor with default value parameter.
     *
     * @param defaultValue
     * @param controller
     */
    public SearchFavoriteController(String defaultValue, WeatherAppController controller) {
        super(defaultValue);
        this.controller = controller;
        getFavoriteLocationInput();
    }

    /**
     * Alters input dialog by adding options to select favorite location.
     */
    private void getFavoriteLocationInput() {
        DialogPane dialogPane = getDialogPane();
        FXMLLoader loader = new FXMLLoader(getClass().getResource("searchFavoriteDialog.fxml"));

        try {
            Parent customVbox = loader.load();
            dialogPane.setExpandableContent(customVbox);
            // Expand the dialog pane by default
            dialogPane.setExpanded(true);

            // Get reference to the hyperlinkContainer
            hyperlinkContainer = (VBox) loader.getNamespace().get("hyperlinkContainer");

            // Customize the hyperlinkContainer
            if (hyperlinkContainer != null) {
                populateHyperlinks();
            }
        } catch (IOException e) {
            ErrorLogger.logError("Unable to render favorite locations" + e.getMessage());
        }
    }

    /**
     * Dynamically update favorite locations based on saved data.
     */
    private void populateHyperlinks() {
        JsonArray favoriteLocations = activityData.getFavoriteLocations();

        // Create and add hyperlinks dynamically
        for (int i = 0; i < favoriteLocations.size(); i++) {
            String location = favoriteLocations.get(i).getAsString();

            Hyperlink hyperlink = new Hyperlink(location);
            hyperlink.setId("favoriteLocation_" + i);
            hyperlink.setOnAction(event -> handleHyperlinkAction(location));

            hyperlinkContainer.getChildren().add(hyperlink);
        }
    }

    /**
     * Handle the action when a favorite location is clicked.
     *
     * @param location The favorite location.
     */
    private void handleHyperlinkAction(String location) {
        controller.displayAllDataForLocation(location);

        // Optionally, close the dialog or perform other actions
        close();
    }

}
