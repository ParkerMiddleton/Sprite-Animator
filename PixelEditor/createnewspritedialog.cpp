#include "createnewspritedialog.h"

CreateNewSpriteDialog::CreateNewSpriteDialog(QWidget *parent, int defaultWidth, int defaultHeight)
	: QDialog(parent)
{
	this->setWindowTitle(tr("Create New Sprite"));
	//this->setWindowFlags(Qt::Popup);

	// Setup layout
	QFormLayout *layout = new QFormLayout(this);

	QLabel *title = new QLabel(tr("Pixel Size (from 1 to 512)"));
	layout->addRow(title);

	QLabel *widthLabel = new QLabel(tr("Width:"));
	QSpinBox *widthSpinBox = new QSpinBox;
	widthSpinBox->setRange(1, 512);
	widthSpinBox->setSingleStep(1);
	widthSpinBox->setValue(defaultWidth);

	QLabel *heightLabel = new QLabel(tr("Height:"));
	QSpinBox *heightSpinBox = new QSpinBox;
	heightSpinBox->setRange(1, 512);
	heightSpinBox->setSingleStep(1);
	heightSpinBox->setValue(defaultHeight);

	layout->addRow(widthLabel, widthSpinBox);
	layout->addRow(heightLabel, heightSpinBox);
	fields.push_back(widthSpinBox);
	fields.push_back(heightSpinBox);

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel
													   , Qt::Horizontal
													   , this);

	layout->addWidget(buttonBox);

	this->connect(buttonBox, &QDialogButtonBox::accepted
				  , this, &CreateNewSpriteDialog::accept);

	this->connect(buttonBox, &QDialogButtonBox::rejected
				  , this, &CreateNewSpriteDialog::reject);

	this->setLayout(layout);
}

QList<int> CreateNewSpriteDialog::getSize(QWidget *parent, int defaultWidth, int defaultHeight, bool &ok)
{
	CreateNewSpriteDialog *dialog = new CreateNewSpriteDialog(parent, defaultWidth, defaultHeight);
	QList<int> list;
	const int returnCode = dialog->exec();
	ok = !!returnCode;

	if (returnCode)
	{
		foreach (auto field, dialog->fields)
		{
			list.push_back(field->value());
		}
	}

	dialog->deleteLater();

	return list;
}
