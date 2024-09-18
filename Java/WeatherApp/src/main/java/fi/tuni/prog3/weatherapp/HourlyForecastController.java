package fi.tuni.prog3.weatherapp;

import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;

/**
 * Controls the operation of the hourly forecast display. A controller tied to
 * hourlyForecast.fxml.
 *
 * @author fumika matsuda
 */
public class HourlyForecastController {

    private Label timeLabel;
    private ImageView weatherImage;
    private Label tempLabel;
    private ImageView windImage;
    private Label windLabel;
    private Label rainLabel;
    private Label humidityLabel;
    private StackPane rotateStackPane;

    /**
     * Set hourly forecast information to the given VBox.
     *
     * @param vBox VBox to set information.
     * @param time Time to display.
     * @param weatherImg Weather type image.
     * @param temp Temperature at that hour.
     * @param windImg arrow image.
     * @param windDegree The wind degree at that hour.
     * @param windSpeed The wind speed at that hour.
     * @param rain The chance of rain at that hour.
     * @param humidity The humidity speed at that hour.
     */
    public void setHourForecast(VBox vBox, int time, Image weatherImg, int temp,
            Image windImg, int windDegree, int windSpeed,
            double rain, int humidity) {
        timeLabel = (Label) vBox.lookup("#timeLabel");
        weatherImage = (ImageView) vBox.lookup("#weatherImage");
        tempLabel = (Label) vBox.lookup("#tempLabel");
        windImage = (ImageView) vBox.lookup("#windImage");
        windLabel = (Label) vBox.lookup("#windLabel");
        rainLabel = (Label) vBox.lookup("#rainLabel");
        humidityLabel = (Label) vBox.lookup("#humidityLabel");
        rotateStackPane = (StackPane) vBox.lookup("#rotateStackPane");

        String rainStr = String.format("%.1f", rain);

        timeLabel.setText(Integer.toString(time));
        weatherImage.setImage(weatherImg);
        tempLabel.setText(Integer.toString(temp));
        windImage.setImage(windImg);
        windLabel.setText(Integer.toString(windSpeed));
        rainLabel.setText(rainStr);
        humidityLabel.setText(Integer.toString(humidity));
        rotateStackPane.setRotate(windDegree);
    }
}
