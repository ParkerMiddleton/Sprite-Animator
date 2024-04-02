#ifndef CREATENEWSPRITEDIALOG_H
#define CREATENEWSPRITEDIALOG_H

/**
 * @authors Tommy Heimer, Egor Chesnokov, Koby Dato, Parker Middleton, Aditya Mukerjee, Charles WolfGramm.
 *
 * @version 1.0
 * @date 4/1/2024
 */

///
/// \brief Dialog to ask the user for width and height of the new sprite to create.
///
class CreateNewSpriteDialog : public QDialog
{
	Q_OBJECT

public:
	///
	/// \brief Constructor.
	/// \param parent parent of this widget
	/// \param defaultWidth width for the spinbox
	/// \param defaultHeight height for the spinbox
	///
	explicit CreateNewSpriteDialog(QWidget *parent, int defaultWidth, int defaultHeight);

	///
	/// \brief Creates a new Message Dialog to ask the user for the size of the new sprite.
	/// \param parent parent widget of the dialog.
	/// \param defaultWidth width for the spinbox
	/// \param defaultHeight height for the spinbox
	/// \param ok if user clicked ok
	/// \return QList with width and height only
	///
	static QList<int> getSize(QWidget *parent, int defaultWidth, int defaultHeight, bool &ok);

private:
	QList<QSpinBox*> fields;

};

#endif // CREATENEWSPRITEDIALOG_H
