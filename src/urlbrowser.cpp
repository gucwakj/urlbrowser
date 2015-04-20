#include <QToolBar>
#include <QWebView>
#include <QWidget>
#include <QHBoxLayout>
#include <QUrl>

#include "urlbrowser.h"

urlBrowser::urlBrowser(const QUrl &url, QWidget *parent) : QWidget(parent) {
	// loading progress
	_progress = 0;

	// view web page
	_view = new QWebView(this);
	_view->load(url);
	QWidget::connect(_view, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
	QWidget::connect(_view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));

	// load into layout
	QHBoxLayout *hbox = new QHBoxLayout();
	hbox->addWidget(_view);
	hbox->setContentsMargins(0, 0, 0, 0);
	this->setLayout(hbox);

	// expand to all available space
	this->setContentsMargins(0, 0, 0, 0);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

urlBrowser::~urlBrowser(void) {
}

void urlBrowser::setToolBar(QToolBar *toolBar) {
	toolBar->addAction(_view->pageAction(QWebPage::Back));
	toolBar->addAction(_view->pageAction(QWebPage::Forward));
	toolBar->addAction(_view->pageAction(QWebPage::Reload));
	toolBar->addAction(_view->pageAction(QWebPage::Stop));
}

void urlBrowser::setProgress(int p) {
	_progress = p;
	this->setWindowTitle(QString("%1 (%2%)").arg(_view->title()).arg(_progress));
}

void urlBrowser::finishLoading(bool /*ok*/) {
	_progress = 100;
	this->setWindowTitle(_view->title());
	_view->page()->mainFrame();
	emit statusMessage("Blockly URL Browser page loaded", 2000);
}
