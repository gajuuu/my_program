package fi.tuni.prog3.config;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

/**
 * Provides the API configurations.
 *
 * @author biswa.upreti
 */
public class ApiConfig {
    private static final String CONFIG_FILE_PATH = "src/main/resources/config/config.properties";

    private Properties properties;

    public ApiConfig() {
        properties = new Properties();
        try {
            properties.load(new FileInputStream(CONFIG_FILE_PATH));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Gets the API key from properties.
     *
     * @return API key for open weather data API.
     */
    public String getApiKey() {
        return properties.getProperty("api.key");
    }

    /**
     * Gets API URL for open weather data.
     *
     * @return API URL.
     */
    public String getApiUrl() {
        return properties.getProperty("api.url");
    }

    /**
     * Gets path of data.json file, where user activity is stored.
     *
     * @return Gets data file path.
     */
    public String getDataJson() {
        return properties.getProperty("data.path");
    }
}
