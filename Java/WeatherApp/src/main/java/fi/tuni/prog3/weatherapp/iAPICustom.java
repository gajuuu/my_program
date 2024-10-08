package fi.tuni.prog3.weatherapp;

/**
 * Interface for extracting data from the OpenWeatherMap API.
 */
public interface iAPICustom {

    /**
     * Returns coordinates for a location.
     *
     * @param loc Name of the location for which coordinates should be fetched.
     * @return String.
     */
    public String lookUpLocation(String loc);

    /**
     * Returns the current weather for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    public String getCurrentWeather(double lat, double lon, String unit);

    /**
     * Returns a daily forecast for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    public String getDailyForecast(double lat, double lon, String unit);

    /**
     * Returns a hourly forecast for the given coordinates.
     *
     * @param lat The latitude of the location.
     * @param lon The longitude of the location.
     * @param unit The unit for the temperature (metric/imperial).
     * @return String.
     */
    public String getHourlyForecast(double lat, double lon, String unit);
}
