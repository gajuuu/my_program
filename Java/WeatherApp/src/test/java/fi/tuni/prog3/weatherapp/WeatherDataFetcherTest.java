package fi.tuni.prog3.weatherapp;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 *
 * @author mikes
 */
public class WeatherDataFetcherTest {

    public WeatherDataFetcherTest() {
    }

    /**
     * Test of lookUpLocation method, of class WeatherDataFetcher.
     */
    @Test
    public void testLookUpLocation_ValidLocation() {
        // Test the lookUpLocation method with valid input
        System.out.println("testLookUpLocation_ValidLocation");
        String loc = "Helsinki";
        WeatherDataFetcher instance = new WeatherDataFetcher();
        String expResult = "Helsinki";
        String result = instance.lookUpLocation(loc);

        assertNotNull(result);
        assertTrue(result.contains(expResult));
    }

    /**
     * Test of lookUpLocation method of class WeatherDataFetcher with invalid
     * location
     */
    @Test
    public void testLookUpLocation_InvalidLocation() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();
        String location = null;

        // Call the method
        String result = weatherDataFetcher.lookUpLocation(location);

        // Assert that the result is null
        assertNull(result);
    }

    /**
     * Test of getCurrentWeather method, of class WeatherDataFetcher.
     */
    @Test
    public void testGetCurrentWeather() {
        System.out.println("testGetCurrentWeather");
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();
        String weatherData = weatherDataFetcher.getCurrentWeather(60.1695, 24.9354, "metric");
        assertNotNull(weatherData);
        System.out.println("Current weather data: " + weatherData);
    }

    /**
     * Test of getCurrentWeather method, of class WeatherDataFetcher with
     * invalid coordinates
     */
    @Test
    public void testGetCurrentWeather_InvalidCoordinates() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();

        // Define invalid latitude and longitude values
        double invalidLat = -100; // Invalid latitude value
        double invalidLon = 200; // Invalid longitude value
        String unit = "metric"; // Any unit can be used for testing
        String result = weatherDataFetcher.getCurrentWeather(invalidLat, invalidLon, unit);

        assertNull(result);
    }

    /**
     * Test of getDailyForecast method, of class WeatherDataFetcher.
     */
    @Test
    public void testGetDailyForecast() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();
        String forecastData = weatherDataFetcher.getDailyForecast(60.1695, 24.9354, "metric");
        assertNotNull(forecastData);
        System.out.println("Daily forecast data: " + forecastData);
    }

    /**
     * Test of getDailyForecast method, of class WeatherDataFetcher, with
     * invalid coordinates
     */
    @Test
    public void testGetDailyForecast_InvalidCoordinates() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();

        // Define invalid latitude and longitude values
        double invalidLat = -100; // Invalid latitude value
        double invalidLon = 200; // Invalid longitude value
        String unit = "metric"; // Any unit can be used for testing

        String result
                = weatherDataFetcher.getDailyForecast(invalidLat,
                        invalidLon, unit);

        assertNull(result);
    }

    /**
     * Test of getHourlyForecast method, of class WeatherDataFetcher.
     */
    @Test
    public void testGetHourlyForecast() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();
        String forecastData
                = weatherDataFetcher.getHourlyForecast(60.1695, 24.9354, "metric");
        assertNotNull(forecastData);
        System.out.println("Hourly forecast data: " + forecastData);
    }

    /**
     * Test of getHourlyForecast method, of class WeatherDataFetcher, with
     * invalid coordinates
     */
    @Test
    public void testGetHourlyForecast_InvalidCoordinates() {
        WeatherDataFetcher weatherDataFetcher = new WeatherDataFetcher();

        // Define invalid latitude and longitude values
        double invalidLat = -100; // Invalid latitude value
        double invalidLon = 200; // Invalid longitude value
        String unit = "metric"; // Any unit can be used for testing

        String result
                = weatherDataFetcher.getHourlyForecast(invalidLat,
                        invalidLon, unit);

        assertNull(result);

    }
}
