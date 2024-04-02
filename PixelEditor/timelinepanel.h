#ifndef TIMELINEPANEL_H
#define TIMELINEPANEL_H

#include "frameicon.h"
/**
 * @authors Tommy Heimer, Egor Chesnokov, Kobe Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

// this class houses frame icons and controls adding, removing and moving frames in the view, not the model
class TimelinePanel : public QScrollArea
{
	Q_OBJECT



public:
	/// \brief TimelinePanel Constructs a TimelinePanel Object
	/// \param parent
	explicit TimelinePanel(QWidget *parent = nullptr);

	/// \brief Destructor
	~TimelinePanel();

public slots:
	// void sendIconInformation();

	/// \brief addFrame  Triggers whenever
	/// the user wants to add a frame to a timeline.
	void addFrame();

	/// \brief removeFrame  Triggers whenever the
	/// user wants to remove a frame from the timeline.
	void removeFrame();

	/// \brief moveLeft  Triggers whenever the
	/// user wants to move an active frame left on the timeline
	void moveLeft();

	/// \brief moveRight Triggers whenever the user wants an active
	/// frame to move right on the timeline.
	void moveRight();


    ///frame startups
	void setupFrameButtons(int framesCount);

    ///
    /// \brief highlightFrameIcon Highlights a frame thats been clicked on
    /// so the user knows whcih frame is currently being worked on.
    /// \param id
    ///
    void highlightFrameIcon(int id);

signals:

    ///on selection
	void frameButtonSelected(int frameButtonIndex);

private:
	QWidget *par;
	QMap<int, FrameIcon*> *frameButtons;
	QLayout *layout;
	FrameIcon *activeFrame;
    int currentID;
    QString highlightIconStylehseet;
    QString regularIconStylesheet;

};

#endif // TIMELINEPANEL_H
