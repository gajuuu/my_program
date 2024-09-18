package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonObject;
import fi.tuni.prog3.config.ApiConfig;

/**
 * Log user activity to JSON.
 *
 * @author biswa.upreti
 */
public class ActivityLogger {

    /**
     * weatherAppController that handles display logic.
     */
    public WeatherAppController controller;
    
    /**
     * UserActivityModel to save data to data.json.
     */
    private final UserActivityModel activityData;

    /**
     * Default constructor.
     *
     * @param controller weatherAppController that handles display logic.
     */
    public ActivityLogger(WeatherAppController controller) {
        super();
        this.controller = controller;
        activityData = new UserActivityModel();
    }

    /**
     * Log user activity to JSON.
     *
     * @param event The defined user action that is to be handled.
     */
    public void logActivity(String event) {
        try {
            switch (event) {
                case "quit":
                    activityData.setLastViewedCity(controller.cityName);
                    activityData.setLastViewedLat(controller.lat);
                    activityData.setLastViewedLon(controller.lon);
                    activityData.setLastViewedUnit(controller.unit);
                    break;
                case "search":
                    activityData.setSearchedCity(controller.cityName);
                    break;
                case "favorite":
                    activityData.setFavoriteCity(controller.cityName);
                    break;
            }

            // Set the event to execute.
            activityData.setEvent(event);
            ApiConfig apiConfig = new ApiConfig();
            String filePath = apiConfig.getDataJson();
            boolean status = activityData.writeToFile(filePath);

            // Toggle favorite character, on set or unset.
            if (event.equals("favorite") && status) {
                JsonObject jsonObject = activityData.getAllActivityData();
                // Updated favorite locations.
                controller.favoriteLocations
                        = jsonObject.getAsJsonArray("favorite_location");

                int isFavorite = activityData.isFavoriteLocation(
                        controller.cityName, controller.favoriteLocations);
                controller.favoriteAction.setText(
                        controller.getFavoriteIconText(isFavorite));
            }

        } catch (Exception ex) {
            ErrorLogger.logError("Error registering user activity"
                    + ex.getMessage());
        }
    }
}
