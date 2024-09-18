package fi.tuni.prog3.weatherapp;

import com.google.gson.annotations.SerializedName;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.ZoneOffset;
import java.util.ArrayList;
import java.util.List;

/**
 * A type-class for acquired current weather data. 
 * Getter classes have also been implemented.
 * @author fumika matsuda
 */
public class WeatherData {
    public Coord coord;
    public List<Weather> weather;
    public String base;
    public Main main;
    public int visibility;
    public Wind wind;
    public Rain rain;
    public Snow snow;
    public Clouds clouds;
    public long dt;  // timestamp
    public Sys sys;
    public int timezone;
    public int id;
    public String name;
    public int cod;


    public class Coord {
        public double lon;
        public double lat;
    }

    public class Weather {
        public int id;
        public String main;
        public String description;
        public String icon;
    }

    public class Main {
        public double temp;
        public double feels_like;
        public double temp_min;
        public double temp_max;
        public int pressure;
        public int humidity;
    }

    public class Wind {
        public double speed;
        public int deg;
    }

    public class Rain {
        @SerializedName("1h")
        public double one_h_rain;
    }

    public class Snow {
        public double one_h_snow;
    }
    
    public class Clouds {
        public int all;
    }

    public class Sys {
        public int type;
        public int id;
        public String country;
        public long sunrise;
        public long sunset;
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
    * Gets feels like temperature.
    * @return int.
    */    
    public int getFeelsLike() {
        double feelsLike = this.main.feels_like;
        return (int) Math.round(feelsLike);
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
    * Gets the amount of the rain for the last one hour.
    * @return double.
    */    
    public double getRainOneH() {        
        return  this.rain.one_h_rain;
    } 
    
    /**
    * Gets timezone ID.
    * @return zoneId.
    */        
    public ZoneId getTimeZone() {
        ZoneOffset zoneOffset = ZoneOffset.ofTotalSeconds(this.timezone);
        ZoneId zoneId = zoneOffset.normalized();
        return zoneId;
    } 

    /**
    * Gets the date for the recent five days including today.
    *
    * @return A list of recent five days including today. 
    */    
    public List<LocalDateTime> getRecentFiveDates() {
        List<LocalDateTime> fiveDays = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            Instant instant = Instant.ofEpochSecond(this.dt);
            LocalDateTime localDateTime = LocalDateTime.ofInstant(instant, getTimeZone());
            localDateTime = localDateTime.plusDays(i);
            fiveDays.add(localDateTime);
        }
        return fiveDays;
    }
    
}
