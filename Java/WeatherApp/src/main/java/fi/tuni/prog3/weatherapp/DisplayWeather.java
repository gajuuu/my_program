package fi.tuni.prog3.weatherapp;

import com.google.gson.Gson;
import java.io.IOException;
import java.time.Instant;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import javafx.fxml.FXMLLoader;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;

/**
 * Displays the current weather and forecast. 
 * 
 * @author fumika matsuda
 */
public final class DisplayWeather {
    
    public WeatherAppController controller;   
    private final WeatherDataFetcher fetcher;
    private final DailyForecastController dController;
    public int DAY_NUM = 5;
    private final int HOUR_NUM = 24;
    private final String IMG_PATH = "/images/";
    
    /**
     * Default constructor.
     *
     * @param controller The weatherAppController that handles view logic.
     */
    public DisplayWeather(WeatherAppController controller) {
        super();
        this.controller = controller;
        fetcher = new WeatherDataFetcher();
        dController = new DailyForecastController();
    }

    /**
     * Display fetched weather data.
     */ 
    public void displayWeather() {
        String data = fetcher.getCurrentWeather(
                controller.lat, controller.lon, controller.unit);

        WeatherData weatherData
                = new Gson().fromJson(data, WeatherData.class);

        controller.timezone = weatherData.getTimeZone();
        controller.fiveDates = weatherData.getRecentFiveDates();      
        controller.cityLabel.setText(controller.cityName);

        controller.tempLabel.setText("" + weatherData.getTemp());
        controller.weatherImage.setImage(new Image(getClass().getResource(
                ImageHandler.getImage(weatherData.getWeatherID(), 
                weatherData.getIcon())).toExternalForm()));    
        
        controller.rainIcon.setImage(new Image(getClass().getResource(
                IMG_PATH + "rain.png").toExternalForm()));
        controller.humidityIcon.setImage(new Image(getClass().getResource(
                IMG_PATH + "humid.png").toExternalForm()));
        controller.windIcon.setImage(new Image(getClass().getResource(
                IMG_PATH + "arrow.png").toExternalForm()));

        controller.feelsLikeLabel.setText(Integer.toString(weatherData.getFeelsLike()));
        controller.windSpeedLabel.setText(Integer.toString(weatherData.getWindSpeed()));
        controller.humidityLabel.setText(Integer.toString(weatherData.getHumidity()));
        controller.humidityUnitLabel.setText("%");
        controller.rotateStackPane.setRotate(weatherData.getWindDegree());

        double rain_mm = 0;

        try {
            rain_mm = weatherData.getRainOneH();
            String rain_mm_str = String.format("%.1f", rain_mm);
            controller.rainLabel.setText(rain_mm_str);
        } catch (NullPointerException e) {       
            String rain_mm_str = String.format("%.1f", rain_mm);
            controller.rainLabel.setText(rain_mm_str);
        }
    }

    
    /**
     * Display daily forecast.
     */
    public void displayDailyForecast() {
        String data = fetcher.getDailyForecast(
                controller.lat, controller.lon, controller.unit);
        DailyForecastData dailyData
                = new Gson().fromJson(data, DailyForecastData.class);
        
        if ( dailyData.list == null || dailyData.list.isEmpty()
                || dailyData.list.size() != DAY_NUM) {
            ErrorLogger.logError("the daily data is null.");
            return;
        }
        
        for (int i = 0; i < DAY_NUM; i++) {
            VBox vBox = (VBox) controller.dailyForecastRoot.getChildren().get(i);
    
            DailyForecastData.Forecast forecast = dailyData.list.get(i);
            Image image = new Image(getClass().getResource(
                    ImageHandler.getImage(forecast.getWeatherID(),
                            forecast.getIcon())).toExternalForm());
            int tempMin = forecast.getTempMin();
            int tempMax = forecast.getTempMax();

            dController.setDayForecast(vBox, controller.fiveDates.get(i), image, 
                                           tempMin, tempMax, i, controller.unit);
        } 
    }  
    
    /**
     * Load dailyForecast.fxml.
     */
    public void loadDailyForecastFXML() {
        for (int i = 0; i < DAY_NUM; i++) {
            FXMLLoader dailyForecastLoader = new FXMLLoader(
                    getClass().getResource("dailyForecast.fxml"));

            try {
                VBox dailyForecast = dailyForecastLoader.load();
                controller.dailyForecastRoot.getChildren().add(dailyForecast);
            } catch (IOException e) {
                ErrorLogger.logError("dailyForecast.fxml was not properly loaded" 
                                     + e.getMessage());
            }
            
            VBox vBox = (VBox) controller.dailyForecastRoot.getChildren().get(i);
            vBox.setOnMouseClicked(
                    event -> handleDailyForecastClick(vBox));
        }
    }
    
    /**
     * Handle action when vBox clicked.
     *
     * @param vBox VBox that triggers the click event.
     */
    public void handleDailyForecastClick(VBox vBox) {
        VBox clickedVBox = vBox;
        controller.clickedIndex = dController.getHiddenIndex(clickedVBox);      
        dController.changeBackgroundColor(clickedVBox);
        
        displayHourlyForecast(controller.hourlyForecastList);
        
        // The background color of VBoxes other than the selected one 
        // is returned to default color.
        for (int i = 0; i < DAY_NUM; i++) {
            if (i != controller.clickedIndex) {
                dController.resetBackgroundColor(
                        (VBox) controller.dailyForecastRoot.getChildren().get(i));
            }
        }
    }
    
    
    /**
     * Get hourly forecast data list.
     */
    private List<HourlyForecastData.Forecast> getAllHourlyForecastList() {
        
        String data = fetcher.getHourlyForecast(
                controller.lat, controller.lon, controller.unit);
  
        HourlyForecastData hourlyData
                = new Gson().fromJson(data, HourlyForecastData.class);

        if (hourlyData.list == null || hourlyData.list.isEmpty()) {
            ErrorLogger.logError("the hourly data is null.");  
            return null;
        }
        List<HourlyForecastData.Forecast> forecastList 
                = hourlyData.getForecastList();
        return forecastList;
    }
    
    /**
     * Get hourly forecast data list separated by date.
     * 
     * @return A list of hourly forecast data lists separated by date.
     */
    public List<List<HourlyForecastData.Forecast>> loadHourlyForecastList() {
        List<HourlyForecastData.Forecast> forecastList 
                = getAllHourlyForecastList();
        List<List<HourlyForecastData.Forecast>> 
                dividedHourlyForecastList = new ArrayList<>();
        List<HourlyForecastData.Forecast> 
                oneDayHourlyForecastList = new ArrayList<>();
        
        for (int i = 0; i < forecastList.size(); i++) {
            LocalDateTime localDateTime 
                    = LocalDateTime.ofInstant(Instant.ofEpochSecond(
                            forecastList.get(i).getTimeStamp()), controller.timezone);
            
            if (localDateTime.getHour() == 0) {
                dividedHourlyForecastList.add(oneDayHourlyForecastList);
                oneDayHourlyForecastList = new ArrayList<>();
            }
            oneDayHourlyForecastList.add(forecastList.get(i));
        }
        dividedHourlyForecastList.add(oneDayHourlyForecastList);
        return dividedHourlyForecastList;
    }  
  
    /**
     * Display hourly forecast.
     *
     * @param dividedForecastList Hourly forecast.
     */
    public void displayHourlyForecast(
            List<List<HourlyForecastData.Forecast>> dividedForecastList) {
   
        controller.hourlyForecastRoot.getChildren().clear();
        List<HourlyForecastData.Forecast> forecastList 
                = dividedForecastList.get(controller.clickedIndex);
        int dataSize = forecastList.size();     
        
        for (int i = 0; i < dataSize ; i++) {
            FXMLLoader hourlyForecastLoader = new FXMLLoader(
                    getClass().getResource("hourlyForecast.fxml"));
            try {
                VBox hourlyForecast = hourlyForecastLoader.load();
                controller.hourlyForecastRoot.getChildren().add(hourlyForecast);
            } catch (IOException e) {
                ErrorLogger.logError("hourlyForecast.fxml was not properly loaded" 
                                     + e.getMessage());
            }
            
            VBox vBox = (VBox) controller.hourlyForecastRoot.getChildren().get(i);
            HourlyForecastData.Forecast forecast = forecastList.get(i);
            
            int time = i;
            // the first hour for the Day 1 forecast. Otherwise, it starts 0.
            if (controller.clickedIndex == 0){
                time = HOUR_NUM - dataSize + i;
            }
            
            Image weatherImg = new Image(getClass().getResource(
                    ImageHandler.getImage(forecast.getWeatherID(),
                            forecast.getIcon())).toExternalForm());
            int temp = forecast.getTemp();
            Image windImg = new Image(getClass().getResource(
                    "/images/arrow.png").toExternalForm());
            int windDegree = forecast.getWindDegree();
            int windSpeed = forecast.getWindSpeed();
            double rain = forecast.getPop();
            int humidity = forecast.getHumidity();
            
            HourlyForecastController hController = new HourlyForecastController(); 
            hController.setHourForecast(vBox, time, weatherImg, temp, 
                                        windImg, windDegree, windSpeed, 
                                        rain, humidity);    
        }
    }
}
