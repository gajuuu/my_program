package fi.tuni.prog3.weatherapp;

/**
 * Sets and Changes unit.
 *
 * @author fumika matsuda
 */
public class UnitHandler {

    private final String C = "\u00B0C";
    private final String F = "\u00B0F";
    private final String MS = "m/s";
    private final String MPH = "mph";

    public WeatherAppController controller;

    /**
     * Default constructor.
     *
     * @param controller
     */
    public UnitHandler(WeatherAppController controller) {
        super();
        this.controller = controller;
    }

    /**
     * Change unit.
     */
    public void changeUnit() {
        if ("metric".equals(controller.unit)) {
            controller.unit = "imperial";
            controller.tempUnitLabel.setText(F);
            controller.feelsLikeUnitLabel.setText(F);
            controller.windUnitLabel.setText(MPH);
            controller.unitButton.setText("Metric");
        } else {
            controller.unit = "metric";
            controller.tempUnitLabel.setText(C);
            controller.feelsLikeUnitLabel.setText(C);
            controller.windUnitLabel.setText(MS);
            controller.unitButton.setText("Imperial");
        }
    }

    /**
     * Set unit initially.
     */
    public void setUnit() {
        if ("metric".equals(controller.unit)) {
            controller.tempUnitLabel.setText(C);
            controller.feelsLikeUnitLabel.setText(C);
            controller.windUnitLabel.setText(MS);
            controller.unitButton.setText("Imperial");
        } else {
            controller.tempUnitLabel.setText(F);
            controller.feelsLikeUnitLabel.setText(F);
            controller.windUnitLabel.setText(MPH);
            controller.unitButton.setText("Metric");
        }
    }
}
