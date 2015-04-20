#ifndef URLBROWSER_H_
#define URLBROWSER_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
class QToolBar;
class QWebView;
class QUrl;
QT_END_NAMESPACE

class urlBrowser : public QWidget {
		Q_OBJECT
	public:
		explicit urlBrowser(const QUrl&, QWidget* = 0);
		~urlBrowser(void);
		void setToolBar(QToolBar*);

	signals:
		void statusMessage(const QString&, int);

	protected slots:
		void setProgress(int);
		void finishLoading(bool);

	private:
		QWebView *_view;
		int _progress;
};

#endif // URLBROWSER_H_

