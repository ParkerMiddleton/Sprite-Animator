#ifndef FRAMEICON_H
#define FRAMEICON_H

/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief The FrameIcon class Displays all of the active Pixmaps of every modified frame that the user has
/// added to the application. These will display at the bottom of the UI. Upon clicking this object, the frame will
/// trigger an event that translates its pixmap data to the edit window to be worked on.
///
class FrameIcon : public QPushButton
{
	Q_OBJECT

public:
	///
	/// \brief Constructor.
	/// \param parent All parent classes with a has a relationship to this object.
	/// \param id ID of the frame in the sprite, identifying it position in the sprite.
	///
	explicit FrameIcon(int frameNum, QWidget *parent = nullptr);

private:
	QString highlightIconStylehseet;
	QString regularIconStylesheet;

};

#endif // FRAMEICON_H
