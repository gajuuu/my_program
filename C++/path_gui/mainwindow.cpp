#include "mainwindow.hh"
#include "gameboard.hh"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initBackground();
    initBoardLabel();
    initBoardButtons();
    initGameResetButton();

    initGameTimer();
    initPauseButton();

    initMovesCounter();
    initMessageBox();
    initDemoButton();
    initTargetMoves();

    initColorControl();
    initColorSetButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBackground(){
    QHBoxLayout *layout = new QHBoxLayout;
    ui->centralwidget->setLayout(layout);
    panel_ = new QWidget(this);
    palette_ = panel_->palette();
    palette_.setColor(QPalette::Window, Qt::transparent);
    panel_->setPalette(palette_);
    panel_->setAutoFillBackground(true);
    panel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(panel_);
    panel_->show();

    // In order to focus out of the spin box for the target number of moves
    // when clicking on an empty spot on the screen.
    panel_->setFocusPolicy(Qt::ClickFocus);
}

void MainWindow::initBoardLabel(){
    for(unsigned int i = 0; i < COLUMS; i++){
        colLabels_[i] = new QLabel(QString::number(i+1), this);
        colLabels_[i]->setGeometry(BOARD_SLOT_SIZE*(i+1), 0,
                                   BOARD_SLOT_SIZE, BOARD_SLOT_SIZE);
        colLabels_[i]->setAlignment(Qt::AlignCenter);
    }

    for(unsigned int j = 0; j < ROWS; j++){
        rowLabels_[j] = new QLabel(QString::number(j+1), this);
        rowLabels_[j]->setGeometry(0, BOARD_SLOT_SIZE*(j+1),
                                   BOARD_SLOT_SIZE, BOARD_SLOT_SIZE);
        rowLabels_[j]->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::initBoardButtons(){
    for(unsigned int i = 0; i < COLUMS; i++){
        for(unsigned int j = 0; j < ROWS; j++){

            boardButtons_[i][j] = new QPushButton(this);
            boardButtons_[i][j]->setGeometry(BOARD_SLOT_SIZE*(i+1),
                                             BOARD_SLOT_SIZE*(j+1),
                                             BOARD_SLOT_SIZE,
                                             BOARD_SLOT_SIZE);
            boardButtons_[i][j]->setFixedSize(BOARD_SLOT_SIZE,
                                              BOARD_SLOT_SIZE);

            Point p = {static_cast<int>(i), static_cast<int>(j)};
            setBoardButtonsColor(p, gameBoard.which_slot(p));

            if(gameBoard.which_slot(p) != UNUSED){
                connect(boardButtons_[i][j], &QPushButton::clicked,
                        this, &MainWindow::boardButtonClicked);
            }

            // EMPTY slots should not be clickable at the stage
            // where the piece to be moved is not selected.
            if(gameBoard.which_slot(p) == EMPTY){
                boardButtons_[i][j]->setDisabled(true);
            }
        }
    }
}


void MainWindow::setBoardButtonsColor(Point p, Slot_type state){
    QPushButton* button = boardButtons_[p.x][p.y];

    switch(state){
        case RED:
            button->setStyleSheet(selectedBottomColor_);
            break;
        case GREEN:
            button->setStyleSheet(selectedTopColor_);
            break;
        case EMPTY:
            button->setStyleSheet(getSelectedColor(COLOR_WHITE));
            break;
        case UNUSED:
            button->setStyleSheet(UNUSED_COLOR); // transparent (unclickable)
            break;
    }
}

void MainWindow::initGameTimer(){
    lcdNumberMin_ = new QLCDNumber(this);
    lcdNumberSec_ = new QLCDNumber(this);
    QLabel* minuteLabel_ = new QLabel("Min", this);
    QLabel* secondLabel_ = new QLabel("Sec", this);

    lcdNumberMin_->setGeometry(MARGIN,
                               MARGIN*2 + BOARD_SLOT_SIZE*(ROWS+1),
                               DEFAULT_WIDTH, BOARD_SLOT_SIZE);
    lcdNumberSec_->setGeometry(MARGIN + DEFAULT_WIDTH,
                               MARGIN*2 + BOARD_SLOT_SIZE*(ROWS+1),
                               DEFAULT_WIDTH, BOARD_SLOT_SIZE);
    minuteLabel_->move(lcdNumberMin_->geometry().left(),
                       lcdNumberMin_->geometry().top()
                       - minuteLabel_->height());
    secondLabel_->move(lcdNumberSec_->geometry().left(),
                       lcdNumberSec_->geometry().top()
                       - secondLabel_->height());

    gameTimer_ = new QTimer(this);
    connect(gameTimer_, &QTimer::timeout,
            this, &MainWindow::updateGameTimer);
}

void MainWindow::initPauseButton(){
    pauseButton_ = new QPushButton(this);
    pauseButton_->setText("Pause Timer");

    pauseButton_->setGeometry(MARGIN + BOARD_SLOT_SIZE*(COLUMS+1),
                              MARGIN + BOARD_SLOT_SIZE*(ROWS+1),
                              DEFAULT_WIDTH, DEFAULT_HEIGHT);

    connect(pauseButton_, &QPushButton::clicked,
            this, &MainWindow::stopGameTimer);
    pauseButton_->setDisabled(true);
}

void MainWindow::startGameTimer(){
    gameTimer_->start(GAME_TIMER_INTERVAL);
    pauseButton_->setEnabled(true);
}

void MainWindow::stopGameTimer(){
    gameTimer_->stop();
    pauseButton_->setDisabled(true);
}

void MainWindow::resetGameTimer(){
    timePassed_ = 0;
    displayGameTimer();
    stopGameTimer();
}

void MainWindow::updateGameTimer(){
    // Counts the elapsed time every second while the timer is running.
    ++timePassed_;
    displayGameTimer();
}

void MainWindow::displayGameTimer(){
    int minutes = timePassed_ / 60;
    int seconds = timePassed_ % 60;
    lcdNumberMin_->display(minutes);
    lcdNumberSec_->display(seconds);
}

void MainWindow::initGameResetButton(){
    resetButton_ = new QPushButton("Reset Game", this);    
    resetButton_->setGeometry(MARGIN + BOARD_SLOT_SIZE*5, MARGIN,
                              DEFAULT_WIDTH, DEFAULT_HEIGHT);
    connect(resetButton_, &QPushButton::clicked,
            this, &MainWindow::resetGame);
}

void MainWindow::initMessageBox(){
    messageBox_ = new QTextBrowser(this);
    messageBox_->setGeometry(MARGIN + BOARD_SLOT_SIZE*(COLUMS+1),
                             MARGIN + BOARD_SLOT_SIZE*3,
                             DEFAULT_WIDTH*2, DEFAULT_HEIGHT*2);
    messageBox_->setText(NOTHING);

    QLabel* messageLabel_ = new QLabel("Message:", this);
    messageLabel_->move(messageBox_->geometry().left(),
                        messageBox_->geometry().top()
                        - messageLabel_->height());
}

void MainWindow::initMovesCounter(){
    counterBox_ = new QTextBrowser(this);
    counterBox_->setGeometry(MARGIN + BOARD_SLOT_SIZE*(COLUMS+1),
                             BOARD_SLOT_SIZE*2,
                             DEFAULT_WIDTH, DEFAULT_HEIGHT);
    counterBox_->setText(QString::number(movesCounter_));

    QLabel* counterLabel_ = new QLabel("Count:", this);
    counterLabel_->move(counterBox_->geometry().left(),
                        counterBox_->geometry().top()
                        - counterLabel_->height());
}

void MainWindow::resetMovesCounter(){
    movesCounter_ = 0;
    counterBox_->setText(QString::number(movesCounter_));
}

void MainWindow::initTargetMoves(){
    spinBoxTarget_ = new QSpinBox(this);
    spinBoxTarget_->setMinimum(MIN_MOVES_TO_GOAL);
    spinBoxTarget_->setMaximum(MAX_MOVES_TO_GOAL);

    spinBoxTarget_->setGeometry(MARGIN*2 + BOARD_SLOT_SIZE*5 + DEFAULT_WIDTH,
                                BOARD_SLOT_SIZE*2,
                                DEFAULT_WIDTH, DEFAULT_HEIGHT);

    QLabel* labelTarget = new QLabel("Target:", this);
    labelTarget->move(spinBoxTarget_->geometry().left(),
                      spinBoxTarget_->geometry().top()
                      - spinBoxTarget_->height());

    connect(spinBoxTarget_, &QSpinBox::valueChanged,
            this, &MainWindow::onTargetChanged);
}

void MainWindow::onTargetChanged(){
    targetMoves_ = spinBoxTarget_->value();
}

void MainWindow::resetTargetMoves(){
    targetMoves_ = MIN_MOVES_TO_GOAL;
    spinBoxTarget_->setValue(targetMoves_);
    spinBoxTarget_->setEnabled(true);
}

void MainWindow::initColorControl(){

    sliderRed_ = new QSlider(Qt::Horizontal, this);
    sliderGreen_ = new QSlider(Qt::Horizontal, this);
    sliderBlue_ = new QSlider(Qt::Horizontal, this);

    spinBoxRed_ = new QSpinBox(this);
    spinBoxGreen_ = new QSpinBox(this);
    spinBoxBlue_ = new QSpinBox(this);

    QLabel* labelRed = new QLabel("R", this);
    QLabel* labelGreen = new QLabel("G", this);
    QLabel* labelBlue = new QLabel("B", this);

    colorLabel_ = new QLabel(this);
    colorLabel_->setGeometry(MARGIN + BOARD_SLOT_SIZE*10,
                             MARGIN*2 + BOARD_SLOT_SIZE*2,
                             COLOR_SAMPLE_SIZE, COLOR_SAMPLE_SIZE);

    std::vector<QSlider*> sliders
            = {sliderRed_, sliderGreen_, sliderBlue_};
    std::vector<QSpinBox*> spinBoxes
            = {spinBoxRed_, spinBoxGreen_, spinBoxBlue_};
    std::vector<QLabel*> labels
            = {labelRed, labelGreen, labelBlue};
    const std::vector<QString> colors
        = {"color: red", "color: green", "color: blue"};

    setColorControl(sliders, spinBoxes, labels, colors);

    // The color display is shown also in the initial state.
    onColorChanged();
}

void MainWindow::setColorControl(std::vector<QSlider*> sliders,
                                 std::vector<QSpinBox*> spinBoxes,
                                 std::vector<QLabel*> labels,
                                 std::vector<QString> colors){
    for(size_t i = 0; i < sliders.size(); i++){
        sliders[i]->setMinimum(RGB_MIN_VALUE);
        sliders[i]->setMaximum(RGB_MAX_VALUE);
        spinBoxes[i]->setMinimum(RGB_MIN_VALUE);
        spinBoxes[i]->setMaximum(RGB_MAX_VALUE);

        sliders[i]->setGeometry(MARGIN + BOARD_SLOT_SIZE*10,
                                MARGIN + DEFAULT_HEIGHT*i,
                                DEFAULT_WIDTH, DEFAULT_HEIGHT);
        spinBoxes[i]->move(sliders[i]->geometry().right() + MARGIN,
                           sliders[i]->geometry().top());
        labels[i]->setGeometry(sliders[i]->geometry().left() - MARGIN,
                               sliders[i]->geometry().top(),
                               MARGIN, DEFAULT_HEIGHT);
        labels[i]->setStyleSheet(colors[i]);

        connect(sliders[i], &QSlider::valueChanged, spinBoxes[i],
                &QSpinBox::setValue);
        connect(spinBoxes[i], &QSpinBox::valueChanged, sliders[i],
                &QSlider::setValue);
        connect(spinBoxes[i], &QSpinBox::valueChanged,
                this, &MainWindow::onColorChanged);
    }
}

void MainWindow::onColorChanged(){
    selectedColorValue_ = QColor(sliderRed_->value(),
                                 sliderGreen_->value(),
                                 sliderBlue_->value());

    QPixmap colorMap(COLOR_SAMPLE_SIZE, COLOR_SAMPLE_SIZE);
    colorMap.fill(selectedColorValue_);
    colorLabel_->setPixmap(colorMap);
}

void MainWindow::disableColorControl(){
    sliderRed_->setDisabled(true);
    sliderGreen_->setDisabled(true);
    sliderBlue_->setDisabled(true);
    spinBoxRed_->setDisabled(true);
    spinBoxGreen_->setDisabled(true);
    spinBoxBlue_->setDisabled(true);
    topColorChangeButton_->setDisabled(true);
    bottomColorChangeButton_->setDisabled(true);
}

void MainWindow::enableColorControl(){
    sliderRed_->setEnabled(true);
    sliderGreen_->setEnabled(true);
    sliderBlue_->setEnabled(true);
    spinBoxRed_->setEnabled(true);
    spinBoxGreen_->setEnabled(true);
    spinBoxBlue_->setEnabled(true);
    topColorChangeButton_->setEnabled(true);
    bottomColorChangeButton_->setEnabled(true);
}

void MainWindow::initColorSetButton(){
    topColorChangeButton_ = new QPushButton("Top Buttons", this);
    bottomColorChangeButton_ = new QPushButton("Bottom Buttons", this);

    topColorChangeButton_->setGeometry(MARGIN*2 + BOARD_SLOT_SIZE*10
                                       + COLOR_SAMPLE_SIZE,
                                       MARGIN*2 + BOARD_SLOT_SIZE*2,
                                       BOARD_SLOT_SIZE*3, DEFAULT_HEIGHT);
    bottomColorChangeButton_->setGeometry(MARGIN*2 + BOARD_SLOT_SIZE*10
                                          + COLOR_SAMPLE_SIZE,
                                          MARGIN*3 + BOARD_SLOT_SIZE*2
                                          + DEFAULT_HEIGHT,
                                          BOARD_SLOT_SIZE*3, DEFAULT_HEIGHT);

    connect(topColorChangeButton_, &QPushButton::clicked,
            this, &MainWindow::setTopColor);
    connect(bottomColorChangeButton_, &QPushButton::clicked,
            this, &MainWindow::setBottomColor);
}

QString MainWindow::getSelectedColor(const QColor& color){
    // Convert to string code that can be used in style sheets.
    QString selectedColorStr = "background-color: rgb("
                                + QString::number(color.red()) + ", "
                                + QString::number(color.green()) + ", "
                                + QString::number(color.blue()) + ")";
    return selectedColorStr;
}


void MainWindow::setTopColor(){
    selectedTopColor_  = getSelectedColor(selectedColorValue_);
    updateButtonsColor();
}

void MainWindow::setBottomColor(){
    selectedBottomColor_  = getSelectedColor(selectedColorValue_);
    updateButtonsColor();
}

void MainWindow::updateButtonsColor(){
    messageBox_->setText(NOTHING);

    if(!isAvailableColor()){
        return;
    }

    for(unsigned int i = 0; i < COLUMS; i++){
        for(unsigned int j = 0; j < ROWS; j++){
            Point p = {static_cast<int>(i), static_cast<int>(j)};

            if(gameBoard.which_slot(p) == GREEN){
                boardButtons_[i][j]->setStyleSheet(selectedTopColor_);
                prevTopColor_ = selectedTopColor_;

            }else if(gameBoard.which_slot(p) == RED){
                boardButtons_[i][j]->setStyleSheet(selectedBottomColor_);
                prevBottomColor_ = selectedBottomColor_;
            }
        }
    }
}

bool MainWindow::isAvailableColor(){

    // YELLOW and WHITE are used for the other roles.
    // To avoid confusion, these cannoe be selected.
    if(selectedColorValue_ == COLOR_YELLOW
            or selectedColorValue_ == COLOR_WHITE){
        messageBox_->setText(UNAVAILABLE_COLOR);

    // Top and Bottom colors cannot be same.
    }else if(selectedTopColor_ == selectedBottomColor_
            or selectedBottomColor_ == selectedTopColor_){
        messageBox_->setText(SAME_COLOR);

    }else{
        return true; // available
    }

    // Restore the state before selecting a color that is not available.
    selectedTopColor_ = prevTopColor_;
    selectedBottomColor_ = prevBottomColor_;
    return false;
}

void MainWindow::resetGameBoard(){
    for(unsigned int i = 0; i < COLUMS; i++) {
        for(unsigned int j = 0; j < ROWS; j++) {

            Point p = {static_cast<int>(i), static_cast<int>(j)};
            setBoardButtonsColor(p, gameBoard.which_slot(p));

            if(gameBoard.which_slot(p) != UNUSED) {
                // Reset the current connection
                boardButtons_[i][j]->disconnect();
                boardButtons_[i][j]->setEnabled(true);
                // Renew the connection
                connect(boardButtons_[i][j], &QPushButton::clicked,
                        this, &MainWindow::boardButtonClicked);
            }

            // EMPTY slots should not be clickable at the stage
            // where the piece to be moved is not selected.
            if(gameBoard.which_slot(p) == EMPTY) {
                boardButtons_[i][j]->setDisabled(true);
            }
        }
    }
}

void MainWindow::resetGame(){
    selectedTopColor_ = INIT_GREEN;
    selectedBottomColor_ = INIT_RED;
    gameBoard.reset_board();
    resetGameBoard();
    startPoint_ = POINT_NOT_SELECTED;
    destinationPoint_ = POINT_NOT_SELECTED;
    resetGameTimer();
    resetMovesCounter();
    resetColorSlider();
    resetBackground();
    resetTargetMoves();
    messageBox_->setText(NOTHING);
    enableColorControl();
}

void MainWindow::resetColorSlider(){
    sliderRed_->setValue(RGB_MIN_VALUE);
    sliderGreen_->setValue(RGB_MIN_VALUE);
    sliderBlue_->setValue(RGB_MIN_VALUE);
}

void MainWindow::resetBackground(){
    palette_.setColor(QPalette::Window, Qt::transparent);
    panel_->setPalette(palette_);
    panel_->setAutoFillBackground(true);
    panel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Point MainWindow::getBoardButtonCoord(QPushButton* button){
    // Keep the coordinates outside the game board as initial values.
    int row = -1;
    int col = -1;
    for(unsigned int i = 0; i < COLUMS; i++){
        for(unsigned int j = 0; j < ROWS; j++){
            if(button == boardButtons_[i][j]){
                row = i;
                col = j;
                break;
            }
        }
    }
    return {row, col};
}

void MainWindow::handleStartPoint(QPushButton* clickedButton,
                                  const Point &clickedPoint){

    // Set the coordinate of the starting point here.
    startPoint_ = clickedPoint;
    startButtonSlotType_ = gameBoard.which_slot(clickedPoint);
    originalColor_ = clickedButton->styleSheet();
    clickedButton->setStyleSheet(getSelectedColor(COLOR_YELLOW));
    messageBox_->setText(START_SELECTED);

    // Once the piece to be moved is selected,
    // the EMPTY slots become clickable.
    enableEmptyButtons();
//    }
}

void MainWindow::handleDestination(QPushButton* clickedButton,
                                   const Point &clickedPoint){

    // If the selected button is clicked again, the selection of
    // the piece to moved is released and the color of the piece
    // returns to the original color of it.
    if(clickedButton->styleSheet() == getSelectedColor(COLOR_YELLOW)){
        clickedButton->setStyleSheet(originalColor_);
        startPoint_ = POINT_NOT_SELECTED;
        messageBox_->setText(NOTHING);

    }else{
        destinationPoint_ = clickedPoint;
        destinationButtonSlotType_ = gameBoard.which_slot(clickedPoint);

        // It is determined if it can be moved
        // according to the logic of gameBoard.move.
        if (!gameBoard.move(startPoint_, destinationPoint_)){
            destinationPoint_ = POINT_NOT_SELECTED;
            messageBox_->setText(INVALID_DESTINATION);;

        }else{
            // Swap the colors of start and destination slots
            setBoardButtonsColor(startPoint_, destinationButtonSlotType_);
            setBoardButtonsColor(destinationPoint_, startButtonSlotType_);

            // Restore the state of the piece before selecting the piece
            // to be moved.
            disableEmptyButtons();
            startPoint_ = POINT_NOT_SELECTED;
            destinationPoint_ = POINT_NOT_SELECTED;

            countMoves();
            messageBox_->setText(MOVED);
        }
    }
}

void MainWindow::countMoves(){
    ++movesCounter_;
    counterBox_->setText(QString::number(movesCounter_));
}

void MainWindow::enableEmptyButtons(){
    for(unsigned int i = 0; i < COLUMS; i++) {
        for(unsigned int j = 0; j < ROWS; j++) {
            Point p = {static_cast<int>(i), static_cast<int>(j)};
            if (gameBoard.which_slot(p) == EMPTY) {
                boardButtons_[i][j]->setEnabled(true);
            }
        }
    }
}

void MainWindow::disableEmptyButtons(){
    for(unsigned int i = 0; i < COLUMS; i++) {
        for(unsigned int j = 0; j < ROWS; j++) {
            Point p = {static_cast<int>(i), static_cast<int>(j)};
            if(gameBoard.which_slot(p) == EMPTY) {
               boardButtons_[i][j]->setDisabled(true);
            }
        }
    }
}

void MainWindow::boardButtonClicked(){
    spinBoxTarget_->setDisabled(true);
    resetColorSlider();
    disableColorControl();

    // If start coordinate has not been selected yet,
    // the clicked button becomes the starting point.
    if (!gameBoard.is_valid_point(startPoint_)) {
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        Point clickedPoint = getBoardButtonCoord(clickedButton);
        handleStartPoint(clickedButton, clickedPoint);

    }else{
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        Point clickedPoint = getBoardButtonCoord(clickedButton);
        handleDestination(clickedButton, clickedPoint);
    }

    // The game timer starts when the first piece is clicked.
    if(!gameTimer_->isActive()){
        startGameTimer();
    }

    if(gameBoard.is_game_over()){
        gameOver();
    }
}

void MainWindow::disableAllGameButtons(){
    for(unsigned int i = 0; i < COLUMS; i++) {
        for(unsigned int j = 0; j < ROWS; j++) {
            boardButtons_[i][j]->setDisabled(true);
        }
    }
}

void MainWindow::gameOver(){
    stopGameTimer();
    disableAllGameButtons();

    // If the goal is reached in a minimum number of moves,
    // the background turns pink.
    if(movesCounter_ == MIN_MOVES_TO_GOAL){
        palette_.setColor(QPalette::Window, COLOR_PINK);
        panel_->setPalette(palette_);
        panel_->setAutoFillBackground(true);
        panel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // Different messages are displayed depending on whether or not
    // the target number of moves has been achieved.
    if(movesCounter_ > targetMoves_){
        messageBox_->setText(NOT_ACHIEVED);
    }else{
        messageBox_->setText(ACHIEVED);
    }
}

void MainWindow::initDemoButton(){
    demoButton_ = new QPushButton("Demo", this);
    demoButton_->setGeometry(MARGIN*2 + BOARD_SLOT_SIZE*5 + DEFAULT_WIDTH,
                             MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    connect(demoButton_, &QPushButton::clicked,
            this, &MainWindow::demoClicked);
}

void MainWindow::demoClicked(){
    // Initially, restores all the settings.
    resetGame();

    pairIndex_ = 0;

    disableAllGameButtons();
    resetButton_->setDisabled(true);
    demoButton_->setDisabled(true);
    spinBoxTarget_->setDisabled(true);
    disableColorControl();

    //
    demoTimer_ = new QTimer(this);
    connect(demoTimer_, &QTimer::timeout,
            this, &MainWindow::pieceMovedAsDemo);
    demoTimer_->start(DEMO_TIMER_INTERVAL);
}

void MainWindow::pieceMovedAsDemo() {
    // When the demonstration is over
    if(pairIndex_ >= PAIR_POINTS.size()) {
        resetButton_->setEnabled(true);
        demoButton_->setEnabled(true);
        messageBox_->setText(DEMO);
        demoTimer_->stop();
        return;
    }

    auto pair = PAIR_POINTS[pairIndex_];
    startPoint_ = pair.first;
    destinationPoint_ = pair.second;

    QPushButton* startButton = boardButtons_[startPoint_.x][startPoint_.y];
    QPushButton* destinationButton
            = boardButtons_[destinationPoint_.x][destinationPoint_.y];

    QString startColor = startButton->styleSheet();
    QString destinationColor = destinationButton->styleSheet();

    // Swap the colors of start and destination slots.
    startButton->setStyleSheet(destinationColor);
    destinationButton->setStyleSheet(startColor);

    countMoves();
    ++pairIndex_;
}
