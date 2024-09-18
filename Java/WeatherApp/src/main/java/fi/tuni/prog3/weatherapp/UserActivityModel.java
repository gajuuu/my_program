package fi.tuni.prog3.weatherapp;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import fi.tuni.prog3.config.ApiConfig;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * On quit, save user activity to JSON file.
 *
 * @author biswa.upreti
 */
public class UserActivityModel implements iReadAndWriteToFile {

    private String lastViewedCity;
    private String searchedCity;
    private String favoriteCity;
    private String lastViewedLat;
    private String lastViewedLon;
    private String lastViewedUnit;

    private String FILE_PATH = null;

    public JsonArray favoriteLocations;
    public String event;

    // Constructor to initialize the JSON file path
    public UserActivityModel() {
        // Reset properties.
        this.lastViewedCity = null;
        this.lastViewedLat = null;
        this.lastViewedLon = null;
        this.lastViewedUnit = null;
        this.searchedCity = null;
        this.favoriteCity = null;
        this.event = null;

        ApiConfig apiConfig = new ApiConfig();
        FILE_PATH = apiConfig.getDataJson();
    }

    public void setLastViewedCity(String lastViewedCity) {
        this.lastViewedCity = lastViewedCity;
    }

    public void setLastViewedLat(double lastViewedLat) {
        this.lastViewedLat = Double.toString(lastViewedLat);
    }

    public void setLastViewedLon(double lastViewedLon) {
        this.lastViewedLon = Double.toString(lastViewedLon);
    }

    public void setLastViewedUnit(String lastViewedUnit) {
        this.lastViewedUnit = lastViewedUnit;
    }

    public void setSearchedCity(String searchedCity) {
        this.searchedCity = searchedCity;
    }

    public void setFavoriteCity(String favoriteCity) {
        this.favoriteCity = favoriteCity;
    }

    public void setEvent(String event) {
        this.event = event;
    }

    public String getLastViewedCity() {
        return lastViewedCity;
    }

    public String getLastViewedLat() {
        return lastViewedLat;
    }

    public String getLastViewedLon() {
        return lastViewedLon;
    }

    public String getLastViewedUnit() {
        return lastViewedUnit;
    }

    public String getSearchedCity() {
        return searchedCity;
    }

    public String getFavoriteCity() {
        return favoriteCity;
    }

    public String getEvent() {
        return event;
    }

    /**
     * Reads save user activity contents from JSON file.
     *
     * @param filePath
     * @return JSON content as string.
     * @throws Exception
     */
    @Override
    public String readFromFile(String filePath) throws Exception {
        StringBuilder content;
        try (
                // Read JSON file content
                BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line);
            }
            reader.close();
            return content.toString();
        } catch (IOException e) {
            ErrorLogger.logError("Error when reading a file." + e.getMessage());
            return null;
        }
    }

    /**
     * Write user activity content to JSON file.
     *
     * @param fileName
     * @return
     * @throws Exception
     */
    @Override
    public boolean writeToFile(String fileName) throws Exception {
        // Parse JSON content
        Gson gson = new GsonBuilder().setPrettyPrinting().create();

        JsonObject upatedJsonObject = updateJsonObject();

        // Write updated JSON content back to file
        try (FileWriter file = new FileWriter(fileName)) {
            gson.toJson(upatedJsonObject, file);
            return true;
        } catch (IOException e) {
            ErrorLogger.logError("Error when saving data." + e.getMessage());
            return false;
        }
    }

    /**
     * Updates JSON with new data based on user action.
     *
     * @return jsonObject JSON to be saved to file.
     */
    public JsonObject updateJsonObject() {
        // Load json data.
        JsonObject jsonObject = getAllActivityData();

        // If event is not set, return loaded json as is.
        if (event == null) {
            return jsonObject;
        }

        // Update last_view_datetime with current date
        jsonObject.addProperty("last_view_datetime", getCurrentDate());

        switch (event) {
            case "quit":
                // Save last viewed location.
                if (!(this.getLastViewedCity() == null
                        || this.getLastViewedCity().isEmpty()
                        || this.getLastViewedLon() == null
                        || this.getLastViewedLon().isEmpty()
                        || this.getLastViewedLat() == null
                        || this.getLastViewedLat().isEmpty()
                        || this.getLastViewedUnit() == null
                        || this.getLastViewedUnit().isEmpty())) {
                    jsonObject.addProperty("last_viewed_location",
                            this.getLastViewedCity());
                    jsonObject.addProperty("last_viewed_latitude",
                            this.getLastViewedLat());
                    jsonObject.addProperty("last_viewed_longitude",
                            this.getLastViewedLon());
                    jsonObject.addProperty("last_viewed_unit",
                            this.getLastViewedUnit());
                }
                break;
            case "search":
                // Save last searched location.
                if (!(this.getSearchedCity() == null
                        || this.getSearchedCity().isEmpty())) {
                    // Get the search history array
                    JsonArray searchHistory
                            = jsonObject.getAsJsonArray("search_history");

                    // Create a new JsonObject for the new search entry
                    JsonObject newSearchEntry = new JsonObject();
                    newSearchEntry.addProperty("city", this.getSearchedCity());
                    newSearchEntry.addProperty("datetime", getCurrentDate());

                    // Add the new JsonObject to the search history array
                    searchHistory.add(newSearchEntry);

                    // Update the original jsonObject 
                    // with the modified searchHistory array
                    jsonObject.add("search_history", searchHistory);
                }
                break;
            case "favorite":
                // Save as favorite location.
                if (!(this.getFavoriteCity() == null
                        || this.getFavoriteCity().isEmpty())) {
                    JsonArray favoriteLocationArray
                            = jsonObject.getAsJsonArray("favorite_location");

                    // If the location doesn't exist, add it to the array
                    int locationExists = isFavoriteLocation(
                            this.getFavoriteCity(), favoriteLocationArray);
                    if (locationExists < 0) {
                        if (favoriteLocationArray.size() < 5) {
                            favoriteLocationArray.add(this.getFavoriteCity());
                        } else {
                            ErrorHandler.showError("Maximum 5 locations can be saved as favorite. Max limit reached!");
                        }
                    } else {
                        favoriteLocationArray.remove(locationExists);
                        // Additionally set temporary favorite city to null.
                        this.setFavoriteCity(null);
                    }
                }
                break;
        }

        return jsonObject;
    }

    /**
     * Get current system date.
     *
     * @return
     */
    public String getCurrentDate() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return sdf.format(new Date());
    }

    /**
     * Check if favorite location.
     *
     * @param city
     * @param locations
     * @return Returns index if exists, -1 if not.
     */
    public int isFavoriteLocation(String city, JsonArray locations) {
        if (city.isEmpty()) {
            return -1;
        }

        // Check if the new location already exists
        for (int i = 0; i < locations.size(); i++) {
            if (locations.get(i).getAsString().equals(city)) {
                return i;
            }
        }

        return -1;
    }

    /**
     * Get latest JSON.
     *
     * @return Parsed JsonObject.
     */
    public JsonObject getAllActivityData() {
        String jsonContent = null;

        try {
            jsonContent = readFromFile(FILE_PATH);
        } catch (Exception e) {
            ErrorLogger.logError("Error reading user data." + e.getMessage());
        }

        return JsonParser.parseString(jsonContent).getAsJsonObject();
    }

    /**
     * Get saved favorite locations.
     *
     * @return JsonArray.
     */
    public JsonArray getFavoriteLocations() {
        JsonObject jsonObject = getAllActivityData();

        // Favorite locations.
        return jsonObject.getAsJsonArray("favorite_location");
    }

    /**
     * Get search history.
     *
     * @return JsonArray for latest 10 search history.
     */
    public JsonArray getSearchHistory() {
        JsonObject jsonObject = getAllActivityData();

        // All favorite locations.
        JsonArray searchHistory = jsonObject.getAsJsonArray("search_history");

        // Limit to get only the last 10 items
        int totalItems = searchHistory.size();

        if (totalItems > 10) {
            // Start index to get the last 10 items
            int startIndex = Math.max(0, totalItems - 10);

            JsonArray last10Items = new JsonArray();
            for (int i = totalItems - 1; i >= startIndex; i--) {
                last10Items.add(searchHistory.get(i));
            }

            return last10Items;
        }

        return searchHistory;
    }
}
