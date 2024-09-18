# Java Weather App

## Overview

This Java Weather App is developed as a group project by three members. It allows users to view current weather conditions and forecasts for various locations. The application features detailed daily and hourly forecasts, unit conversion, and the ability to save favorite locations. It fetches data from OpenWeatherMap and provides a user-friendly interface for interacting with weather data.

## Key Classes and Their Responsibilities

- **ApiConfig**: Provides the API configurations.
- **WeatherAppXML**: Application starter that loads `weather.fxml`.
- **WeatherAppController**: Controller tied to `weather.fxml`. Manages the overall operation of the application.
- **WeatherDataFetcher**: Implementation of the `iAPICustom` interface. Fetches data from OpenWeatherMap.
- **WeatherData**: Represents acquired weather data with getter methods.
- **DailyForecastData**: Represents daily forecast data with getter methods.
- **DailyForecastController**: Controller tied to `dailyForecast.fxml`. Manages the daily forecast display.
- **HourlyForecastData**: Represents hourly forecast data with getter methods.
- **HourlyForecastController**: Controller tied to `hourlyForecast.fxml`. Manages the hourly forecast display.
- **DisplayWeather**: Displays current weather and forecast.
- **LocationSearchHandler**: Retrieves the name, latitude, and longitude of the location based on user input.
- **SearchFavoriteController**: Controller tied to `searchFavoriteInputDialog.fxml`. Manages the favorite list in the search window.
- **DisplayHistory**: Displays the search history.
- **UserActivityModel**: Implementation of the `iReadAndWriteToFile` interface. Reads/writes JSON files on program start/end.
- **ActivityLogger**: Logs user activity to a JSON file.
- **ImageHandler**: Retrieves images based on weather type.
- **ErrorHandler**: Displays error messages to the user.
- **ErrorLogger**: Logs exceptions and errors.

## Project Functionality

- **Main Screen**: Displays the current weather, a 5-day simple forecast, and a detailed forecast for the selected day.
- **Current Weather**: Shows weather type image, temperature, sensation, precipitation, wind direction and speed, and humidity.
- **Simple Forecast**: Shows date, weather type image, and temperature range.
- **Detailed Forecast**: Displays hourly forecast including time, temperature, weather icon, wind direction, wind speed, precipitation probability, and humidity.
- **Search Function**: Allows users to search for weather by city name, with support for multiple formats and error handling for non-existent locations.
- **Favorites**: Save up to five locations as favorites, with the ability to add or remove them.
- **Search History**: View search history with the ability to access past locations.
- **Unit Conversion**: Switch between metric and imperial units.
- **Exit**: Save settings and locations upon exiting.

## Short User Manual

- **View Weather**: Open the program to see current weather and forecast. Click on any day to view a detailed forecast.
- **Search Locations**: Click the search button, enter a city name, and view results. Use favorite lists for quick access.
- **Save/Remove Favorites**: Click ☆ to save a location and ★ to remove it. Up to five favorites are allowed.
- **Change Units**: Click the Imperial (or Metric) button to switch units.
- **Exit Program**: Click Quit or the close button. Settings and locations are saved automatically.

## Missing Features

- **Hourly Forecast Display**: Improvements needed for displaying small amounts of data and clarity.
- **Favorite Functionality**: Unable to remove favorites directly from the list; performance improvements needed for data retrieval.
- **Overall Design**: Not optimized for various display sizes.

## Image Credits

- **Freepik**: `arrow.png`
- **Icon-pit**: `rain.png`, `humid.png`
- **Dorova**: All other images

## My Contributions

In this group project, I was primarily responsible for:
- **Fetching Data from OpenWeatherMap**: Implemented the logic to retrieve weather data from the OpenWeatherMap API.
- **Daily and Hourly Forecast Displays**: Developed the functionality to display both daily and hourly weather forecasts.
- **Obtaining and Handling Weather-Type Images**: Managed the retrieval and display of weather-type images based on the current weather conditions.
- **Unit Conversion Functionality**: Implemented the feature to switch between metric and imperial units for temperature and wind speed.
- **Documentation**: Created and maintained comprehensive documentation for the project.