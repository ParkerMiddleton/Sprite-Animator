#ifndef FRAMETIMELINE_H
#define FRAMETIMELINE_H

#include <QWidget>
#include <QScrollArea>
#include <QVector>
#include "frameicon.h"

#include <QHBoxLayout>

// this class houses frame icons and controls adding, removing and moving frames in the view, not the model
class FrameTimeline : public QScrollArea
{
    Q_OBJECT
private:

    QWidget *par;
    QMap<int,FrameIcon*> *framesInUse;
    QLayout *layout;
    FrameIcon *activeFrame;


public:
    ///
    /// \brief FrameTimeline Constructs a FrameTimeline Object
    /// \param parent
    ///
    explicit FrameTimeline(QWidget *parent = nullptr);

    ///
    /// \brief Destructor
    ///
    ~FrameTimeline();



signals:
    void sendIconID(int id);


public slots:
    // void sendIconInformation();

    ///
    /// \brief addFrame  Triggers whenever
    /// the user wants to add a frame to a timeline.
    ///
    void addFrame();

    ///
    /// \brief removeFrame  Triggers whenever the
    /// user wants to remove a frame from the timeline.
    ///
    void removeFrame();

    ///
    /// \brief moveLeft  Triggers whenever the
    /// user wants to move an active frame left on the timeline
    ///
    void moveLeft();

    ///
    /// \brief moveRight Triggers whenever the user wants an active
    /// frame to move right on the timeline.
    ///
    void moveRight();
};

#endif // FRAMETIMELINE_H
