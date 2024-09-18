package fi.tuni.prog3.weatherapp;

import java.time.DayOfWeek;
import java.time.LocalDateTime;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;

/**
 * Controls the operation of the daily forecast display. A controller tied to
 * dailyForecast.fxml.
 *
 * @author fumika matsuda
 */
public class DailyForecastController {

    private Label weekdayLabel;
    private Label dateLabel;
    private ImageView weatherImage;
    private Label tempLabel;
    private Label tempUnitLabel;
    private Label hiddenIndexLabel;

    private final String CLICKED_COLOR = "-fx-background-color: #CCE6FF;";
    private final String DEFAULT_COLOR = "-fx-background-color: transparent;";
    private final String C = "\u00B0C";
    private final String F = "\u00B0F";

    /**
     * Set daily forecast information to the given VBox.
     *
     * @param vBox VBox to set information.
     * @param dateTime dateTime containing the date to be set.
     * @param image weather type image.
     * @param tempMin the minimum temperature of the day.
     * @param tempMax the maximum temperature of the day.
     * @param index Index of the number of days out of the 5 days displayed.
     * @param unit Unit to be displayed.
     */
    public void setDayForecast(VBox vBox, LocalDateTime dateTime, Image image,
            int tempMin, int tempMax, int index, String unit) {
        weekdayLabel = (Label) vBox.lookup("#weekdayLabel");
        dateLabel = (Label) vBox.lookup("#dateLabel");
        weatherImage = (ImageView) vBox.lookup("#weatherImage");
        tempLabel = (Label) vBox.lookup("#tempLabel");
        tempUnitLabel = (Label) vBox.lookup("#tempUnitLabel");
        hiddenIndexLabel = (Label) vBox.lookup("#hiddenIndexLabel");

        DayOfWeek dayOfWeek = dateTime.getDayOfWeek();
        int month = dateTime.getMonthValue();
        int day = dateTime.getDayOfMonth();
        String weekday
                = dayOfWeek.toString().substring(0, 1)
                + dayOfWeek.toString().substring(1, 3).toLowerCase();
        String temp = tempMin + "/" + tempMax;

        weekdayLabel.setText(weekday);
        dateLabel.setText(day + "." + month);
        weatherImage.setImage(image);
        tempLabel.setText(temp);
        hiddenIndexLabel.setText(Integer.toString(index));

        if ("metric".equals(unit)) {
            tempUnitLabel.setText(C);
        } else {
            tempUnitLabel.setText(F);
        }
    }

    /**
     * Sets the background color of the specified VBox as clicked color.
     *
     * @param vBox VBox to be changed the background color.
     */
    public void changeBackgroundColor(VBox vBox) {
        vBox.setStyle(CLICKED_COLOR);
    }

    /**
     * Sets the background color of the specified VBox as default color.
     *
     * @param vBox VBox to be reset to background color.
     */
    public void resetBackgroundColor(VBox vBox) {
        vBox.setStyle(DEFAULT_COLOR);
    }

    /**
     * Gets hidden index which indicates how many of the five days.
     *
     * @param vBox VBox from which to retrieve the hidden index.
     * @return int.
     */
    public int getHiddenIndex(VBox vBox) {
        hiddenIndexLabel = (Label) vBox.lookup("#hiddenIndexLabel");

        if (hiddenIndexLabel.getText() == null
                || hiddenIndexLabel.getText().trim().isEmpty()) {
            ErrorLogger.logError("The hidden index is not given.");
            return -1;
        }

        try {
            return Integer.parseInt(hiddenIndexLabel.getText().trim());
        } catch (NumberFormatException e) {
            ErrorLogger.logError("The hidden index cannot be converted to a number.");
            return -1;
        }
    }
}
