package fi.tuni.prog3.weatherapp;

/**
 * Retrieve the name, latitude, and longitude of the location according to the
 * user input.
 *
 * @author fumika matsuda
 */
public class LocationSearchHandler {

    /**
     * Search location specific weather data.
     *
     * @param inputLocation
     * @return String Searched city and its co-ordinates.
     */
    public String searchLocation(String inputLocation) {
        if (inputLocation == null) {
            ErrorLogger.logError("Empty input is provided.");
            return "";
        }

        WeatherDataFetcher fetcher = new WeatherDataFetcher();
        String cityAndCoord = fetcher.lookUpLocation(inputLocation);
        if (cityAndCoord == null || cityAndCoord.isEmpty()) {
            ErrorHandler.showError("The input city was not found!");
            return "";
        }

        return cityAndCoord;
    }
}
