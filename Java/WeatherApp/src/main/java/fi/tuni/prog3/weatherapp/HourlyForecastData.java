package fi.tuni.prog3.weatherapp;

import java.util.List;

/**
 * A type-class for acquired daily forecast data. 
 * Getter classes have also been implemented.
 * @author fumika matsuda
 */
public class HourlyForecastData {
    public int cod;
    public String message;
    public int cnt;
    public List<Forecast> list;
    public Forecast forecast;
    public City city;

    
    public class Forecast {
        public long dt;
        public Main main;
        public List<Weather> weather;
        public Clouds clouds;
        public Wind wind;
        public int visibility;
        public Rain rain;
        public Snow snow;
        public double pop;  // the chance of rain
        public Sys sys;
        public String dt_txt;

        /**
        * Gets timestamp.
        * @return long.
        */
        public long getTimeStamp() {
            return this.dt;
        }

        /**
        * Gets weather ID.
        * @return int.
        */        
        public int getWeatherID() {
            return this.weather.get(0).id;
        }
        
        /**
        * Gets weather icon ID.
        * @return String.
        */  
        public String getIcon() {
            return this.weather.get(0).icon;
        }

        /**
        * Gets temperature.
        * @return int.
        */          
        public int getTemp() {
            double temp = this.main.temp;
            return (int) Math.round(temp);
        }

        /**
        * Gets humidity.
        * @return int.
        */          
        public int getHumidity() {
            return this.main.humidity;
        }

        /**
        * Gets wind speed.
        * @return int.
        */  
        public int getWindSpeed() {
            double speed = this.wind.speed;
            return (int) Math.round(speed);
        }   

        /**
        * Gets wind degree.
        * @return int.
        */  
        public int getWindDegree() {
            return  this.wind.deg;
        }      

        /**
        * Gets chance of rain.
        * @return double.
        */  
        public double getPop() {
            return this.pop;
        }
        
    }

    public class Main {
        public double temp;
        public double feels_like;
        public double temp_min;
        public double temp_max;
        public int pressure;
        public int sea_level;
        public int grnd_lebel;
        public int humidity;
        public double temp_kf;
    }

    public class Weather {
        public int id;
        public String main;
        public String description;
        public String icon;
    }
        
    public class Clouds {
        public int all;
    }

    public class Wind {
        public double speed;
        public int deg;
        public double gust;
    }
    
    public class Rain {
        public double three_h_rain;
    }
    
    public class Snow {
        public double three_h_snow;
    }
    
    public class Sys {
        public char pod;
    }
    
    public class City {
        public int id;
        public String name;
        public Coord coord;
        public String country;
        public int population;
        public int timezone;
        public long sunrise;
        public long sunset;
    }
    
    public class Coord {
        public double lat;
        public double lon;
    }

    /**
    * Gets the list of hourly forecast data.
    *
    * @return A list of hourly forecast data.
    */      
    public List<Forecast> getForecastList() {
        return this.list;
    }

}
