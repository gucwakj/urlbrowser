#include <QToolBar>
#include <QStatusBar>
#include <QUrl>

#include "mainwindow.h"
#include "urlbrowser.h"

MainWindow::MainWindow(void) {
	// main toolbar
	QToolBar *toolBar = addToolBar(tr("Navigation"));
	toolBar->setMovable(false);

	// create url browser widget
	urlBrowser *urlbrowser = new urlBrowser(QUrl("http://computing.ucdavis.edu/blockly"), this);

	// set toolbar elements
	urlbrowser->setToolBar(toolBar);

	// load widget
	this->setContentsMargins(0, 0, 0, 0);
	this->setCentralWidget(urlbrowser);

	// create status bar
	this->statusBar()->showMessage("Blockly URL Browser has started", 2000);
	QWidget::connect(urlbrowser, SIGNAL(statusMessage(const QString&, int)), this->statusBar(), SLOT(showMessage(const QString&, int)));
}
