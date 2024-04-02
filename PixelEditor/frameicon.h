#ifndef FRAMEICON_H
#define FRAMEICON_H

#include <QWidget>
#include <QPushButton>
/**
 * @authors Tommy Heimer, Egor Chesnokov, Kobe Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */



///
/// \brief The FrameIcon class Displays all of the active Pixmaps of every modified frame that the user has
/// added to the application. These will display at the bottom of the UI. Upon clicking this object, the frame will
/// trigger an event that translates its pixmap data to the edit window to be worked on.
///
///
class FrameIcon : public QPushButton
{
    Q_OBJECT

    QPixmap *pixmap;
    int frameID;
    QString highlightIconStylehseet;
    QString regularIconStylesheet;


public:
    ///
    /// \brief FrameIcon Constructs a frame Icon
    /// \param parent All parent classes with a has a relationship to this object
    /// \param id ID of the frame in the sprite, identifying it position in the sprite
    ///
    explicit FrameIcon(int frameNum, QWidget *parent = nullptr);

    /// Destructor for FrameIcon
    ~FrameIcon();

    ///Getter for Frame ID
    int getID();

    ///setter for FrameID
    void setID(int id);


signals:
    /// Sends frame data
    void sendActiveFrameID(int id);
};

#endif // FRAMEICON_H
