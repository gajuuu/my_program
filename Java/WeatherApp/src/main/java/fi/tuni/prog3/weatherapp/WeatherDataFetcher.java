package fi.tuni.prog3.weatherapp;

import fi.tuni.prog3.config.ApiConfig;

import java.io.IOException;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

/**
 * Gets data from OpenWeatherMap.
 *
 * @author fumika matsuda
 */
public class WeatherDataFetcher implements iAPICustom {

    private final ApiConfig apiConfig = new ApiConfig();
    private final String API_KEY = apiConfig.getApiKey();
    private final String BASE_URL = apiConfig.getApiUrl();

    /**
     * Returns coordinates for a location.
     *
     * @param loc Name of the location for which coordinates should be fetched.
     * @return String. cityName + "," + latitude + "," + longitude.
     */
    @Override
    public String lookUpLocation(String loc) {

        if (loc == null || loc.isEmpty()) {
            ErrorLogger.logError("Empty location provided");
            return null;
        }

        String encodedLoc = URLEncoder.encode(loc, StandardCharsets.UTF_8);

        // The limit value is used to limit the number of search results.
        // For now, set it to 1.
        String url = String.format(
                "%s/geo/1.0/direct?q=%s&limit=%d&appid=%s",
                BASE_URL, encodedLoc, 1, API_KEY);
        HttpClient httpClient = HttpClients.createDefault();
        HttpGet request = new HttpGet(url);

        try {
            HttpResponse response = httpClient.execute(request);
            HttpEntity entity = response.getEntity();

            if (entity != null) {
                String json = EntityUtils.toString(entity);
                JsonArray jsonArray
                        = JsonParser.parseString(json).getAsJsonArray();
                if (jsonArray.size() > 0) {
                    JsonObject jsonObject = jsonArray.get(0).getAsJsonObject();
                    String cityName = jsonObject.get("name").getAsString();
                    double latitude = jsonObject.get("lat").getAsDouble();
                    double longitude = jsonObject.get("lon").getAsDouble();
                    return cityName + "," + latitude + "," + longitude;
                }
            }
        } catch (IOException | IllegalArgumentException e) {
            ErrorLogger.logError("Error getting location weather data." + e.getMessage());
        }
        return null;
    }

    /**
     * Returns a hourly forecast for the given coordinates.
     *
     * @param url The URL of the data acquisition destination
     * @return String.
     */
    private String fetchData(String url) {
        HttpClient httpClient = HttpClients.createDefault();
        HttpGet request = new HttpGet(url);

        try {
            HttpResponse response = httpClient.execute(request);
            HttpEntity entity = response.getEntity();

            if (entity != null) {
                return EntityUtils.toString(entity);
            }
        } catch (IOException | IllegalArgumentException e) {
            ErrorLogger.logError("Error fetching data from API." + e.getMessage());
        }
        return null;
    }

    /**
     * Returns the current weather for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    @Override
    public String getCurrentWeather(double lat, double lon, String unit) {
        if (!(lat >= -90 && lat <= 90 && lon >= -180 && lon <= 180)) {

            ErrorLogger.logError("Invalid latitude or longitude provided");
            return null;
        }
        String url = String.format(
                "%s/data/2.5/weather?lat=%f&lon=%f&appid=%s&units=%s",
                BASE_URL, lat, lon, API_KEY, unit);

        String data = fetchData(url);
        
        return data;
    }

    /**
     * Returns a daily forecast for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    @Override
    public String getDailyForecast(double lat, double lon, String unit) {
        if (!(lat >= -90 && lat <= 90 && lon >= -180 && lon <= 180)) {

            ErrorLogger.logError("Invalid latitude or longitude provided");
            return null;
        }

        // The limit value is used to limit the number of days.
        // For now, set it to 5.
        String url = String.format(
                "%s/data/2.5/forecast/"
                + "daily?lat=%f&lon=%f&cnt=%d&appid=%s&units=%s",
                BASE_URL, lat, lon, 5, API_KEY, unit);

        String data = fetchData(url);
        return data;
    }

    /**
     * Returns a hourly forecast for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    @Override
    public String getHourlyForecast(double lat, double lon, String unit) {
        if (!(lat >= -90 && lat <= 90 && lon >= -180 && lon <= 180)) {

            ErrorLogger.logError("Invalid latitude or longitude provided");
            return null;
        }
        String url = String.format(
                "%s/data/2.5/forecast/hourly?lat=%f&lon=%f&appid=%s&units=%s",
                BASE_URL, lat, lon, API_KEY, unit);

        String data = fetchData(url);
        return data;
    }
}
