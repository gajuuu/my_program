package fi.tuni.prog3.weatherapp;

/**
 * The ImageHandler class provides functionality to determine the appropriate
 * image file name based on weather conditions and icon ID.
 *
 * @author Mikhail Silaev
 *
 * <p>
 * The getImage method takes an ID representing weather conditions and an icon
 * string as input, and returns the corresponding image file name. The method
 * uses a switch statement to match the weather condition ID with predefined
 * cases and constructs the image file name accordingly.
 *
 * <p>
 * The generated file name is prefixed with "/images/" and returned for use in
 * displaying weather-related images.
 *
 * <p>
 * Weather condition ID values and their corresponding image file names: - 2xx:
 * Thunderstorm - 3xx: Drizzle - 5xx: Rain - 6xx: Snow - 7xx: Atmosphere - 800:
 * Clear - 80x: Clouds
 *
 * <p>
 * Icon strings are used to differentiate between day and night images. The last
 * character of the icon string is used to determine the image variant.
 *
 * <p>
 * The method returns the full file name of the weather-related image prefixed
 * with "/images/".
 */
public class ImageHandler {

    /**
     * Gets an image file name according to given weather ID and day/night
     * information.
     *
     * @param ID The ID representing weather conditions.
     * @param icon The icon string used to differentiate between day and night
     * images.
     * @return The full file name of the weather-related image.
     */
    public static String getImage(int ID, String icon) {
        int length = icon.length();
        char dn = icon.charAt(length - 1);

        String fname = "";

        switch (ID) {
            case 200:
            case 201:
            case 202:
            case 210:
            case 211:
            case 212:
            case 221:
            case 231:
            case 232:
                fname = "11" + dn + ".png";
                break;

            case 300:
            case 301:
            case 302:
            case 310:
            case 311:
            case 312:
            case 313:
            case 314:
            case 321:
            case 520:
            case 521:
            case 522:
            case 531:
                fname = "drizzle.png";
                break;

            case 500:
            case 501:
            case 502:
            case 503:
            case 504:
                fname = "10" + dn + ".png";
                break;

            case 511:
            case 611:
            case 612:
            case 613:
            case 615:
            case 616:
                fname = "rainsnow" + dn + ".png";
                break;

            case 600:
            case 601:
            case 602:
            case 620:
            case 621:
            case 622:
                fname = "13" + dn + ".png";
                break;

            case 701:
            case 711:
            case 721:
            case 731:
            case 751:
            case 761:
            case 762:
                fname = "50" + ".png";
                break;

            case 741:
                fname = "fog.png";
                break;

            case 771:
                fname = "squall.png";
                break;

            case 781:
                fname = "tornado.png";
                break;

            case 800:
                fname = "01" + dn + ".png";
                break;

            case 801:
                fname = "02" + dn + ".png";
                break;

            case 802:
                fname = "03" + ".png";
                break;

            case 803:
                fname = "04" + ".png";
                break;

            case 804:
                fname = "05" + ".png";
                break;
        }

        return "/images/" + fname;
    }
}
