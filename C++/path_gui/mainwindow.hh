/* Class: MainWindow
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing the user interface function of the game.
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <gameboard.hh>

#include <QPushButton>
#include <QLabel>
#include <QLCDNumber>
#include <QTimer>
#include <QTextBrowser>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>
#include <QPalette>

#include <vector>
#include <algorithm>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Stops the game timer and disables the "Pause Timer" button.
     */
    void stopGameTimer();

    /**
     * @brief Updates the game timer every second.
     */
    void updateGameTimer();

    /**
     * @brief Resets the game and initializes the settings.
     */
    void resetGame();

    /**
     * @brief When the value of the spin box for the target number of
     * total moves is changed, this is called.
     * Obtains the value selected.
     */
    void onTargetChanged();

    /**
     * @brief When the value of the spin box of the color controller
     * is changed, this is called.
     * Obtains RGB values and displays the selected color.
     */
    void onColorChanged();

    /**
     * @brief Sets the top row of board buttons to a color
     * selected by the user.
     */
    void setTopColor();

    /**
     * @brief Sets the bottom row of board buttons to a color
     * selected by the user.
     */
    void setBottomColor();

    /**
     * @brief When a button on the game board is clicked, this is called.
     * If the piece to move is not selected yet, tries to select a piece.
     * Otherwise, tries to select the slot the piece moves to.
     */
    void boardButtonClicked();

    /**
     * @brief When the "Demo" button clicked, this is called.
     * Starts the automatic demonstration and disables all of the operations
     * during the demonstration.
     */
    void demoClicked();

    /**
     * @brief Makes pieces move on the game board autimatically to goal.
     * Also, if demonstration ends, enables some functions on the screen
     * and displays a given message.
     */
    void pieceMovedAsDemo();


private:
    Ui::MainWindow *ui;
    GameBoard gameBoard;

    // The messages displayed in the message box.
    const QString NOTHING = "";
    const QString INVALID_DESTINATION = "It cannot be moved there!";
    const QString MOVED = "Moved!";
    const QString START_SELECTED = "Start point is selected!";
    const QString DEMO = "You can do it like this.";
    const QString ACHIEVED = "Conglatulations! \nYour goal was achieved :)";
    const QString NOT_ACHIEVED = "Oops, your goal was not achieved :(";
    const QString UNAVAILABLE_COLOR = "This color cannot be selected! Sorry!";
    const QString SAME_COLOR = "The same color cannot be selected!";
    
    // The interval of the timer's signal (unit: millisecond)
    const int GAME_TIMER_INTERVAL = 1000; // 1 second
    const int DEMO_TIMER_INTERVAL = 500; // half second

    // The min and max numbers of moves the user can select for
    // setting the target number of moves
    const int MIN_MOVES_TO_GOAL = 30;
    const int MAX_MOVES_TO_GOAL = 100;

    // The min and max value of RGB in the user can select on 
    // the color controller.
    const int RGB_MIN_VALUE = 0;
    const int RGB_MAX_VALUE = 255;

    const QColor COLOR_PINK = QColor(255, 192, 203);
    const QColor COLOR_YELLOW = QColor(255, 255, 0);
    const QColor COLOR_WHITE = QColor(255, 255, 255);

    // The initial color of the pieces on the game board.
    const QString INIT_GREEN = "background-color: rgb(0, 128, 0)";
    const QString INIT_RED = "background-color: rgb(255, 0, 0)";

    // The setting for unused buttons (slots) on the game board.
    const QString UNUSED_COLOR = "background-color: transparent; border: none";

    // The coordinate for a point when it is not selected .
    const Point POINT_NOT_SELECTED = {-1, -1};

    // The minimum moves for the demonstration.
    // The first coodinate of eace pair is the starting point of the piece,
    // and the second one is the destination.
    const std::vector<std::pair<Point, Point>> PAIR_POINTS
    =   {{{1,4},{2,2}}, {{1,0},{1,4}}, {{0,0},{1,3}}, {{2,2},{0,0}},
         {{1,3},{1,0}}, {{1,4},{1,1}}, {{0,4},{2,2}}, {{1,1},{0,4}},
         {{1,0},{1,4}}, {{2,0},{1,3}}, {{3,0},{1,2}}, {{0,0},{3,0}},
         {{1,2},{2,0}}, {{2,2},{0,0}}, {{1,3},{1,0}}, {{1,4},{1,1}},
         {{2,4},{2,2}}, {{0,4},{1,2}}, {{3,4},{0,4}}, {{1,2},{3,4}},
         {{1,1},{2,4}}, {{1,0},{1,4}}, {{2,0},{1,3}}, {{2,2},{2,0}},
         {{1,3},{1,0}}, {{1,4},{1,1}}, {{0,4},{2,2}}, {{1,1},{0,4}},
         {{1,0},{1,4}}, {{2,2},{1,0}}};

    // The values used for the layout of each part on the screen.
    const int BOARD_SLOT_SIZE = 50;
    const int COLOR_SAMPLE_SIZE = 80;
    const int MARGIN = 20;
    const int DEFAULT_WIDTH = 100;
    const int DEFAULT_HEIGHT = 30;

    // Background
    QWidget* panel_;
    QPalette palette_;

    // holding ROWS QLabel pointers
    QLabel* rowLabels_[ROWS];
    // holding COLUMS QLabel pointers
    QLabel* colLabels_[COLUMS];
    // holding [COLUMS]*[ROWS] QPushButton pointers
    QPushButton* boardButtons_[COLUMS][ROWS];

    // Reset
    QPushButton* resetButton_;

    // Message box
    QTextBrowser* messageBox_;

    // The counter for moves
    QTextBrowser* counterBox_;

    // The target number of total moves
    QSpinBox* spinBoxTarget_;
    int targetMoves_ = MIN_MOVES_TO_GOAL;

    // Game timer
    QLCDNumber* lcdNumberMin_;
    QLCDNumber* lcdNumberSec_;
    QTimer* gameTimer_;
    QPushButton* pauseButton_;
    int timePassed_ = 0;

    // Demonstration
    QPushButton* demoButton_;
    QTimer* demoTimer_;

    // The color of the buttons on the game board
    QSlider* sliderRed_;
    QSlider* sliderGreen_;
    QSlider* sliderBlue_;
    QSpinBox* spinBoxRed_;
    QSpinBox* spinBoxGreen_;
    QSpinBox* spinBoxBlue_;
    QLabel* colorLabel_;
    QColor selectedColorValue_;
    QString selectedTopColor_ = INIT_GREEN;
    QString selectedBottomColor_ = INIT_RED;
    QPushButton* topColorChangeButton_;
    QPushButton* bottomColorChangeButton_;
    QString prevSelectedColor_;
    QString prevTopColor_ = INIT_GREEN;
    QString prevBottomColor_ = INIT_RED;

    Slot_type startButtonSlotType_;
    Slot_type destinationButtonSlotType_;
    QString originalColor_;

    // The move of the piece on the game board
    size_t pairIndex_ = 0;
    Point startPoint_ = POINT_NOT_SELECTED;
    Point destinationPoint_ = POINT_NOT_SELECTED;
    int movesCounter_ = 0;

    /**
     * @brief Sets the background color of the screen to transparent.
     */
    void initBackground();

    /**
     * @brief Creates the labels for rows and columns of the game board.
     */
    void initBoardLabel();

    /**
     * @brief Creates the button as a 4 x 5 grid.
     * Also, sets the color according to the initial state.
     */
    void initBoardButtons();

    /**
     * @brief Sets the color of the buttons on the game board
     * @param p, a cordinate of the button
     * @param state, a Slot_type which is defined at the GameBoard Class
     * Sets the color to the buttons on the game board by referring to
     * the slot type of the square.
     */
    void setBoardButtonsColor(Point p, Slot_type state);

    /**
     * @brief Creates the game timer.
     */
    void initGameTimer();

    /**
     * @brief Creates the "Pause Timer" button.
     */
    void initPauseButton();

    /**
     * @brief Starts the game timer and enables the "Pause Timer" button.
     */
    void startGameTimer();

    /**
     * @brief Resets and stops the game timer.
     */
    void resetGameTimer();

    /**
     * @brief Displays elapsed time in minutes and seconds on the game timer.
     */
    void displayGameTimer();

    /**
     * @brief Creates the "Reset Game" button.
     */
    void initGameResetButton();

    /**
     * @brief Creates the message box which displays various messages.
     */
    void initMessageBox();

    /**
     * @brief Creates the moves counter which counts the number of moves done.
     */
    void initMovesCounter();

    /**
     * @brief Resets the moves counter.
     */
    void resetMovesCounter();

    /**
     * @brief Creates a spin box for setting the target number of total moves.
     */
    void initTargetMoves();

    /**
     * @brief Resets the target number of the total moves.
     * Also, enables the spin box for setting the number.
     */
    void resetTargetMoves();

    /**
     * @brief Creates the color controller.
     * It has sliders, spin boxes, buttons for setting the color of
     * pieces at the top and bottom rows, respectively, and the sample
     * display for the selected color. Using this, the color of the pieces
     * on the game board can be changed.
     */
    void initColorControl();

    /**
     * @brief Sets the color controller on the screen.
     * @param the vector of the pointers fot sliders for RGB
     * @param the vector of the pointers for spin boxes for RGB
     * @param the vector of the pointers for labels for RGB sliders
     * @param the vector of strings which represent the color code
     */
    void setColorControl(std::vector<QSlider*> sliders,
                         std::vector<QSpinBox*> spinBoxes,
                         std::vector<QLabel*> labels,
                         std::vector<QString> colors);

    /**
     * @brief Creates the buttons for setting the color of pieces
     * at the top and bottom rows, respectively.
     */
    void initColorSetButton();

    /**
     * @brief Disables all of the functions on the color controller.
     */
    void disableColorControl();

    /**
     * @brief Enables all of the functions on the color controller.
     */
    void enableColorControl();

    /**
     * @brief Converts the value of QColor to the form of
     * QString code to specify background color.
     * @param color, the value of QColor of the given color.
     * @return QString, returns the code converted from
     * the color.
     */
    QString getSelectedColor(const QColor &color);


    /**
     * @brief Evaluates if the selected color is available or not.
     * @return boolean, if the color can be set, returns true.
     * Otherwise, returns false.
     */
    bool isAvailableColor();

    /**
     * @brief Updates the color of the pieces on the game board.
     */
    void updateButtonsColor();

    /**
     * @brief Resets the value of color sliders.
     */
    void resetColorSlider();

    /**
     * @brief Resets the game board to the initial state.
     */
    void resetGameBoard();

    /**
     * @brief Obtains the coordinate of the button.
     * @param button, the pointer of the button the coordinate of which
     * will be obtained.
     * @return Point, the coordinate of the button.
     */
    Point getBoardButtonCoord(QPushButton* button);

    /**
     * @brief Handles the starting point.
     * @param clickedButton, the pointer of the button clicked
     * @param clickedPoint, the coordinate of the button clicked
     * If the slot type of the clicked button is "RED" or "GREEN"
     * (which means the button is a piece), it will be selected and
     * the color of the button turns yellow. Displays a given message
     * and enables empty slots.
     */
    void handleStartPoint(QPushButton* clickedButton,
                          const Point &clickedPoint);

    /**
     * @brief Handles the destination.
     * @param clickedButton, the pointer of the button clicked
     * @param clickedPoint, the coordinate of the button clicked
     * If the selected piece is clicked again, releases the selection of
     * the start point. If the selected piece cannot be moved to the clicked
     * button, displays a given message. Otherwise, the selected piece
     * will be moved to the clicked button. Displays a given message and
     * the count of moves counter increases. Returns to the state before
     * the starting point is selected.
     */
    void handleDestination(QPushButton* clickedButton,
                           const Point &clickedPoint);

    /**
     * @brief Increases the number of the moves counter.
     */
    void countMoves();

    /**
     * @brief Enables the buttons at the square with the slot type "EMPTY"
     * on the game board.
     */
    void enableEmptyButtons();

    /**
     * @brief Disables the buttons at the square with the slot type "EMPTY"
     * on the game board.
     */
    void disableEmptyButtons();

    /**
     * @brief Disables all of the buttons on the game board.
     */
    void disableAllGameButtons();

    /**
     * @brief Change the screen to game over status.
     * Enables the "Reset Game" and "Demo" buttons.
     * If the game is cleared with equal to or fewer moves than
     * the target moves, displays a congratulatory message. Otherwise,
     * displays a failure message. Additionally, if the game is cleared
     * with possible minimum moves, the background turns pink.
     */
    void gameOver();

    /**
     * @brief Resets the background color as transparent.
     */
    void resetBackground();

    /**
     * @brief Creates the "Demo" button.
     */
    void initDemoButton();

};
#endif // MAINWINDOW_HH
