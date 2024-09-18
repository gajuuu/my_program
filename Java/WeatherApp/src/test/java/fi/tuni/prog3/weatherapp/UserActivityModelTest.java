package fi.tuni.prog3.weatherapp;

import com.google.gson.JsonArray;
import static org.junit.jupiter.api.Assertions.*;
import com.google.gson.JsonObject;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * User activity model test.
 *
 * @author biswa.upreti
 */
public class UserActivityModelTest {

    private UserActivityModel userActivityModel;

    @BeforeEach
    public void setUp() {
        userActivityModel = new UserActivityModel();
    }

    @Test
    public void testUpdateJsonObjectQuitEvent() {
        // Set up test data
        userActivityModel.setLastViewedCity("Helsinki");
        userActivityModel.setLastViewedLat(60.1695);
        userActivityModel.setLastViewedLon(24.9354);
        userActivityModel.setLastViewedUnit("Celsius");
        userActivityModel.setEvent("quit");

        // Call the method under test
        JsonObject jsonObject = userActivityModel.updateJsonObject();

        // Assert that the jsonObject is updated correctly
        assertNotNull(jsonObject);
        assertTrue(jsonObject.has("last_view_datetime"));
        assertEquals("Helsinki", jsonObject.get("last_viewed_location").getAsString());
        assertEquals("60.1695", jsonObject.get("last_viewed_latitude").getAsString());
        assertEquals("24.9354", jsonObject.get("last_viewed_longitude").getAsString());
        assertEquals("Celsius", jsonObject.get("last_viewed_unit").getAsString());
    }

    @Test
    public void testIsFavoriteLocation() {
        // Set up test data
        String city = "Helsinki";
        JsonArray locations = new JsonArray();
        locations.add("Helsinki");
        locations.add("Stockholm");
        locations.add("Oslo");

        // Call the method under test
        int index = userActivityModel.isFavoriteLocation(city, locations);

        // Assert that the index is correct
        assertEquals(0, index);
    }

}
