module fi.tuni.prog3.weatherapp {
    requires javafx.controls;
    requires javafx.fxml;
    exports fi.tuni.prog3.weatherapp;
    requires com.google.gson;
    requires org.apache.httpcomponents.httpclient;
    requires org.apache.httpcomponents.httpcore;
    requires java.logging;
}
