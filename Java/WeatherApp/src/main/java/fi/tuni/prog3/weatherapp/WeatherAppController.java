package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

import java.net.URL;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.List;
import java.util.Optional;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 * Controls the main operations of the app.
 *
 * @author mikhail silaev, biswa.upreti, fumika matsuda
 */
public class WeatherAppController implements Initializable {

    private UserActivityModel activityData;
    private DisplayWeather displayWeather;
    private DisplayHistory displayHistory;
    private UnitHandler unitHandler;
    private ActivityLogger activityLogger;

    public String cityName;
    public double lat;
    public double lon;
    public String unit;

    public ZoneId timezone;
    public int clickedIndex;
    public List<LocalDateTime> fiveDates;

    public List<List<HourlyForecastData.Forecast>> hourlyForecastList;
    public JsonArray favoriteLocations;

    @FXML
    public BorderPane mainPane;

    @FXML
    public Label cityLabel;

    @FXML
    public Label tempUnitLabel;

    @FXML
    public Label feelsLikeUnitLabel;

    @FXML
    public Label windUnitLabel;

    @FXML
    public Label tempLabel;

    @FXML
    public ImageView weatherImage;

    @FXML
    public HBox dailyForecastRoot;

    @FXML
    public HBox hourlyForecastRoot;

    @FXML
    public Button favoriteAction;

    @FXML
    public Label feelsLikeLabel;

    @FXML
    public Label rainLabel;

    @FXML
    public Label humidityLabel;

    @FXML
    public Label humidityUnitLabel;

    @FXML
    public Label windSpeedLabel;

    @FXML
    public ImageView rainIcon;

    @FXML
    public ImageView humidityIcon;

    @FXML
    public ImageView windIcon;

    @FXML
    public StackPane rotateStackPane;

    @FXML
    public Button unitButton;

    @FXML
    public VBox searchHistoryContainer;

    /**
     * Handle search action. Loads input dialog.
     *
     * @param event
     */
    @FXML
    public void handleSearch(ActionEvent event) {
        String inputCity = "";

        SearchFavoriteController dialog
                = new SearchFavoriteController(inputCity, this);
        dialog.setTitle("Location Input");
        dialog.setHeaderText("Enter the location:");
        dialog.setContentText("Location:");

        Optional<String> result = dialog.showAndWait();

        result.ifPresent(inputLocation -> {
            displayAllDataForLocation(inputLocation.trim());
        });
    }

    /**
     * Display all information for the specific location.
     *
     * @param location
     */
    public void displayAllDataForLocation(String location) {
        LocationSearchHandler handler = new LocationSearchHandler();

        String[] cityLatLon = handler.searchLocation(location).split(",");
        if (cityLatLon.length != 3) {
            ErrorLogger.logError("Error with getting the city location");
            return;
        }

        cityName = cityLatLon[0];
        lat = Double.parseDouble(cityLatLon[1]);
        lon = Double.parseDouble(cityLatLon[2]);

        // Log searched location.
        activityLogger.logActivity("search");

        displayWeather.displayWeather();
        displayWeather.displayDailyForecast();
        hourlyForecastList = displayWeather.loadHourlyForecastList();

        // Day 1 is displayed as default.
        clickedIndex = 0;
        displayWeather.handleDailyForecastClick(
                (VBox) dailyForecastRoot.getChildren().get(0));

        displayHistory.displaySearchHistory();

        int isFavorite = activityData.isFavoriteLocation(
                cityName, favoriteLocations);
        favoriteAction.setText(getFavoriteIconText(isFavorite));
    }

    /**
     * Click event on search history item to display weather data.
     *
     * @param location
     */
    public void handleSearchHistoryClick(String location) {
        displayAllDataForLocation(location);
    }

    /**
     * Handle action when unitButton clicked.
     *
     * @param event
     */
    public void handleChangeUnitClick(ActionEvent event) {
        unitHandler.changeUnit();
        displayWeather.displayWeather();
        displayWeather.displayDailyForecast();
        hourlyForecastList = displayWeather.loadHourlyForecastList();
        displayWeather.displayHourlyForecast(hourlyForecastList);
    }

    /**
     * Saves location as favorite action.
     *
     * @param event
     */
    @FXML
    public void saveAsFavorite(ActionEvent event) {
        activityLogger.logActivity("favorite");
    }

    /**
     * Get Favorite icon text.
     *
     * @param isfavorite Index of favorite location.
     * @return Icon UNICODE character.
     */
    public String getFavoriteIconText(int isfavorite) {
        // get ☆ or ★.
        return (isfavorite >= 0) ? "\u2605" : "\u2606";
    }

    /**
     * On quit action.
     *
     * @param event
     */
    @FXML
    public void handleQuit(ActionEvent event) {
        // save last viewed information.
        activityLogger.logActivity("quit");
        Platform.exit();
    }

    /**
     * Set initial data from a JSON file.
     */
    private void initializeActivityData() {

        activityData = new UserActivityModel();

        // retrieve last viewed information and set them as default display.
        JsonObject jsonObject = activityData.getAllActivityData();
        cityName = jsonObject.get("last_viewed_location").getAsString();
        String latValue
                = jsonObject.get("last_viewed_latitude").getAsString();
        String lonValue
                = jsonObject.get("last_viewed_longitude").getAsString();
        unit = jsonObject.get("last_viewed_unit").getAsString();

        if (cityName == null || cityName.isEmpty()
                || latValue.isEmpty() || lonValue.isEmpty() || unit.isEmpty()) {
            ErrorLogger.logError("At least one empty value in the initial data");
            return;
        }

        lat = Double.parseDouble(latValue);
        lon = Double.parseDouble(lonValue);

        favoriteLocations = jsonObject.getAsJsonArray("favorite_location");
        int isFavorite = activityData.isFavoriteLocation(
                cityName, favoriteLocations);
        favoriteAction.setText(getFavoriteIconText(isFavorite));
    }

    /**
     * Show the initial display.
     */
    private void initializeWeatherDisplay() {
        displayWeather = new DisplayWeather(this);
        displayWeather.loadDailyForecastFXML();
        displayWeather.displayWeather();
        displayWeather.displayDailyForecast();
        hourlyForecastList = displayWeather.loadHourlyForecastList();
        // Day 1 is displayed as default.
        clickedIndex = 0;
        displayWeather.handleDailyForecastClick(
                (VBox) dailyForecastRoot.getChildren().get(0));
    }

    /**
     * Application close event.
     */
    private void closeEvent() {
        Platform.runLater(() -> {
            Stage stage = (Stage) mainPane.getScene().getWindow();
            stage.setOnCloseRequest((WindowEvent we) -> {
                activityLogger.logActivity("quit");
            });
        });
    }

    /**
     * Initialize the app.
     *
     * @param url
     * @param resourceBundle
     */
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        initializeActivityData();

        unitHandler = new UnitHandler(this);
        unitHandler.setUnit();

        initializeWeatherDisplay();

        displayHistory = new DisplayHistory(this);
        displayHistory.displaySearchHistory();

        activityLogger = new ActivityLogger(this);

        closeEvent();
    }
}
