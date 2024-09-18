package fi.tuni.prog3.weatherapp;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/**
 * Error logger. Logs generated error and exceptions to logs/app.log file (for
 * reference).
 *
 * @author biswa.upreti
 */
public class ErrorLogger {

    private static final Logger LOGGER = Logger.getLogger(ErrorLogger.class.getName());

    /**
     * Log error message to a log file.
     *
     * @param errorMessage The error message to log.
     */
    public static void logError(String errorMessage) {
        FileHandler fileHandler;

        try {
            // Configure the FileHandler to write logs to a file named "error.log"
            fileHandler = new FileHandler("logs/app.log");
            LOGGER.addHandler(fileHandler);

            // Create a SimpleFormatter to format log records as text
            SimpleFormatter formatter = new SimpleFormatter();
            fileHandler.setFormatter(formatter);

            // Set the logging level to capture error messages
            LOGGER.setLevel(Level.SEVERE);

            // Log the error message with Level.SEVERE
            LOGGER.severe(errorMessage);
        } catch (IOException e) {
            // If an exception occurs while setting up the FileHandler, log the exception
            e.printStackTrace();
        }
    }
}
