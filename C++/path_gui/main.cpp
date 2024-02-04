/* Path
 *
 * Desc:
 *  This program implements a path that creates a game with GUI.
 * The Class "GameBoard" represents the action logic, and the Class
 * "MainWindow" represents the function of the user interface.
 *
 *  The game board is a 4x5 board. In addition, there is also the "Reset
 * Game" button, game timer, "Pause Timer" button, "Demo" button, message box,
 * the counter of total moves, and spin box for setting the target number
 * of moves, color controller fot the pieced of top and bottom rows on
 * the game screen. Any and all messages are displayed in the message box.
 *
 *  Initially, the buttons in the top row are set to green and those in the
 * bottom row to red. These are the pieces to move. White buttons indicate
 * empty slots. You can change the color of the pieces by using the sliders
 * or the spin box. By selecting a color and pressing the "Top Buttons" or
 * "Bottom Buttons", the colors can be set, respectively. However, these
 * two colors cannot be the same. Also, if there are colors that indicate
 * the other role, they cannot be selected as well.
 *
 *  The basic operations are as follows
 *  When the first piece is clicked, the game starts, and the game timer
 * starts counting. During the game, the color controller and the spin box
 * for setting target moves are disabled.
 *  When one of the pieces is clicked, the selected piece turns yellow.
 * In this state, when one of the other buttons is clicked, the piece will
 * be moved to the position if the piece can be moved there.
 * If the clicked button is the slot the piece cannot move to or the other
 * piece, a warning message will be displayed. Here, the selection status
 * is not released, so following this, a new destination will be selected.
 * To release the selection, the selected piece should be clicked again.
 * This means that the process begins again with the selection of the piece
 * to be moved.
 *
 *  When the "Reset Game" button is clicked, the game will be reset and the
 * settings return to the initial state. This operation can be done at
 * any time except during the demonstration.
 *  The game timer can be paused during the game by pressing the "Pause Timer"
 * button. This button is enabled when the timer is working. The timer can be
 * resumed simply by restarting the game by clicking on the piece or the slot
 *  (It depends on the status when the timer is paused).
 *
 *  The target number of moves can be set in the spin box. The minimum number
 * is 30 and the maximum is 100. If the game is cleared with equal to or fewer
 * moves than the target number, a congratulatory message will be displayed.
 * Conversely, if the game is cleared with larger moves than the target number,
 * a failure message will be displayed.
 *
 *  If the game is cleared with the minimum number of moves, the background
 * color temporarily changes. This will be restored when the "Reset Game" or
 * "Demo" button is clicked.
 *
 *  When the "Demo" button is clicked, the game state is reset, and the
 * automatic demonstration is started. It shows one of the patterns of how to
 * clear the game with a minimum number of moves. This can be done at any time
 * during the game except during the demonstration itself. Any operations are
 * disabled during the demonstration. The timer does not run, too.
 * When the demonstration ends, a given message is displayed, and the "Reset
 * Game" and "Demo" buttons are enabled.
 *
 *
 * Program author
 * Name: Fumika Matsuda
 * Student number: 151243936
 * UserID: qkfuma
 * E-Mail: fumika.matsuda@tuni.fi
 *
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
