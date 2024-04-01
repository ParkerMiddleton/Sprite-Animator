#ifndef CREATENEWSPRITEDIALOG_H
#define CREATENEWSPRITEDIALOG_H

class CreateNewSpriteDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreateNewSpriteDialog(QWidget *parent, int defaultWidth, int defaultHeight);

	static QList<int> getSize(QWidget *parent, int defaultWidth, int defaultHeight, bool &ok);

private:
	QList<QSpinBox*> fields;

};

#endif // CREATENEWSPRITEDIALOG_H
