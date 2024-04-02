#ifndef TIMELINEPANEL_H
#define TIMELINEPANEL_H

#include "frameicon.h"
/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief This class houses frame icons and controls adding, removing and moving frames in the view, not the model
///
class TimelinePanel : public QScrollArea
{
	Q_OBJECT

public:
	///
	/// \brief Contructor.
	/// \param parent parent of this widget.
	///
	explicit TimelinePanel(QWidget *parent = nullptr);

	///
	/// \brief TDestructor.
	///
	~TimelinePanel();

	///
	/// \brief Setups the layout of this widget. Must be called after the contructor.
	/// \param contents content of the QScrollArea
	///
	void setupLayout(QWidget *contents);

public slots:
	///
	/// \brief Adds the current frame button to the timeline.
	///
	void addFrame();

	///
	/// \brief Removes the current frame button from the timeline.
	///
	void removeFrame();

	///
	/// \brief Moves the current frame button to the left on the timeline.
	///
	void moveLeft();

	///
	/// \brief Moves the current frame button to the right on the timeline.
	///
	void moveRight();

	///
	/// \brief Adds a specified number of frame buttons to the timeline.
	/// \param framesCount How many buttons to add.
	///
	void setupFrameButtons(int framesCount);

    ///
	/// \brief Highlights a frame thats been clicked on so the user knows which frame is currently being worked on.
	/// \param id id of the frame button.
    ///
    void highlightFrameIcon(int id);

signals:
	/// \brief On frame button selected.
	void frameButtonSelected(int frameButtonIndex);

protected:
	void wheelEvent(QWheelEvent *event) override;

private:
	QHBoxLayout *contentsLayout;
	QMap<int, FrameIcon*> *frameButtons;

	FrameIcon *activeFrame;
    int currentID;
    QString highlightIconStylehseet;
    QString regularIconStylesheet;

};

#endif // TIMELINEPANEL_H
