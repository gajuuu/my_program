package fi.tuni.prog3.weatherapp;

import java.util.List;

/**
 * A type-class for acquired daily forecast data. Getter classes have also been
 * implemented.
 *
 * @author fumika matsuda
 */
public class DailyForecastData {

    public City city;
    public int cod;
    public String message;
    public int cnt;
    public List<Forecast> list;
    public Forecast forecast;

    /**
     * Forecast information.
     */
    public class Forecast {

        public long dt;
        public int sunrise;
        public int sunset;
        public Temp temp;
        public FeelsLike feels_like;
        public int pressure;
        public int humidity;
        public List<Weather> weather;
        public double speed;
        public int deg;
        public double gust;
        public int clouds;
        public double pop;
        public double rain;
        public double snow;

        /**
         * Gets weather ID.
         *
         * @return int.
         */
        public int getWeatherID() {
            return this.weather.get(0).id;
        }

        /**
         * Gets icon ID.
         *
         * @return String.
         */
        public String getIcon() {
            return this.weather.get(0).icon;
        }

        /**
         * Gets the minimum temperature.
         *
         * @return int.
         */
        public int getTempMin() {
            double tempMin = this.temp.min;
            return (int) Math.round(tempMin);
        }

        /**
         * Gets the maximum temperature.
         *
         * @return int.
         */
        public int getTempMax() {
            double tempMax = this.temp.max;
            return (int) Math.round(tempMax);
        }

    }

    /**
     * City information.
     */
    public class City {

        public int id;
        public String name;
        public Coord coord;
        public String country;
        public int population;
        public int timezone;
    }

    /**
     * Temperature information.
     */
    public class Temp {

        public double day;
        public double min;
        public double max;
        public double night;
        public double eve;
        public double morn;
    }

    /**
     * Feels like information.
     */
    public class FeelsLike {

        public double day;
        public double night;
        public double eve;
        public double morn;
    }

    /**
     * Weather information.
     */
    public class Weather {

        public int id;
        public String main;
        public String description;
        public String icon;
    }

    /**
     * Co-ordinates.
     */
    public class Coord {

        public double lat;
        public double lon;
    }

    /**
     * Gets the list of daily forecast data.
     *
     * @return List.
     */
    public List<Forecast> getForecastList() {
        return this.list;
    }

}
