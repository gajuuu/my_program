package fi.tuni.prog3.config;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Functional test for ApiConfig.
 * The goal is to make sure the methods in ApiConfig is able to return correct
 * values. Test directly reads the properties file for assertion.
 *
 * @author biswa.upreti
 */
public class ApiConfigTest {

    private static final String CONFIG_FILE_PATH = "src/main/resources/config/config.properties";
    private ApiConfig apiConfig;

    @BeforeEach
    public void setUp() {
        apiConfig = new ApiConfig();
    }

    @Test
    public void testGetApiKey() {
        Properties properties = new Properties();
        try {
            properties.load(new FileInputStream(CONFIG_FILE_PATH));
        } catch (IOException e) {
            e.printStackTrace();
        }
        assertEquals(properties.getProperty("api.key"), apiConfig.getApiKey());
    }

    @Test
    public void testGetApiUrl() {
        Properties properties = new Properties();
        try {
            properties.load(new FileInputStream(CONFIG_FILE_PATH));
        } catch (IOException e) {
            e.printStackTrace();
        }
        assertEquals(properties.getProperty("api.url"), apiConfig.getApiUrl());
    }

    @Test
    public void testGetDataJson() {
        Properties properties = new Properties();
        try {
            properties.load(new FileInputStream(CONFIG_FILE_PATH));
        } catch (IOException e) {
            e.printStackTrace();
        }
        assertEquals(properties.getProperty("data.path"), apiConfig.getDataJson());
    }
}
