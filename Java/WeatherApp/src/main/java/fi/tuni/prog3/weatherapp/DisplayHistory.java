package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Hyperlink;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 * Displays search history.
 *
 * @author biswa.upreti
 */
public class DisplayHistory {

    /**
     * The weatherAppController that handles view logic.
     */
    public WeatherAppController controller;
    
    /**
     * The UserActivityModel that saves data to JSON file.
     */
    private final UserActivityModel activityData;

    /**
     * Default constructor.
     *
     * @param controller
     */
    public DisplayHistory(WeatherAppController controller) {
        super();
        this.controller = controller;
        activityData = new UserActivityModel();
    }

    /**
     * Load and display search history data.
     */
    public void displaySearchHistory() {
        // Always empty container before adding new content.
        controller.searchHistoryContainer.getChildren().clear();

        JsonArray historyData = activityData.getSearchHistory();

        try {
            // Loop through historyData and set date and city to FXML elements
            for (JsonElement item : historyData) {
                JsonObject searchItem = item.getAsJsonObject();
                String city = searchItem.get("city").getAsString();
                String datetime = searchItem.get("datetime").getAsString();

                // Create HBox container
                HBox searchHistoryItem = new HBox();
                searchHistoryItem.setAlignment(Pos.CENTER_LEFT);
                searchHistoryItem.setPrefWidth(455);
                searchHistoryItem.setStyle(
                        "-fx-border-color: #cccccc; -fx-border-width: 0 0 1 0;");

                // Create Label and set datetime
                Label dateLabel = new Label(datetime);
                dateLabel.setPrefWidth(135);
                dateLabel.setWrapText(true);

                // Create Hyperlink and set city
                Hyperlink locationLink = new Hyperlink(city);
                locationLink.setOnAction(event -> controller.handleSearchHistoryClick(city));

                // Add Label and Hyperlink to the HBox
                searchHistoryItem.getChildren().addAll(dateLabel, locationLink);

                // Set margin and padding for the HBox
                VBox.setMargin(searchHistoryItem, new Insets(0, 10, 0, 10)); // Set margin
                searchHistoryItem.setPadding(new Insets(10, 0, 10, 0)); // Set padding

                // Add HBox to the searchHistoryContainer
                controller.searchHistoryContainer.getChildren().add(searchHistoryItem);
            }

        } catch (Exception e) {
            ErrorLogger.logError("Error loading search history" + e.getMessage());
        }
    }
}
