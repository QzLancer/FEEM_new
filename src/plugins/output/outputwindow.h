#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <coreplugin/context.h>

#include <QPlainTextEdit>
#include <QTimer>
#include <QTime>

namespace OutputPlugin {

class OutputWindowPrivate;

class OutputWindow : public QPlainTextEdit
{
    Q_OBJECT
public:
    OutputWindow(Core::Context context, QWidget *parent = nullptr);
    ~OutputWindow() override;

//    Utils::OutputFormatter *formatter() const;
//    void setFormatter(Utils::OutputFormatter *formatter);

    void appendMessage(const QString &out/*, Utils::OutputFormat format*/);
    /// appends a \p text using \p format without using formater
    void appendText(const QString &text, const QTextCharFormat &format = QTextCharFormat());

    void grayOutOldContent();
    void clear();

    void showEvent(QShowEvent *) override;

    void scrollToBottom();

    void setMaxCharCount(int count);
    int maxCharCount() const;

    void setBaseFont(const QFont &newFont);
    float fontZoom() const;
    void setFontZoom(float zoom);
    void setWheelZoomEnabled(bool enabled);

signals:
    void wheelZoom();

public slots:
    void setWordWrapEnabled(bool wrap);

protected:
    bool isScrollbarAtBottom() const;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    using QPlainTextEdit::setFont; // call setBaseFont instead, which respects the zoom factor
    QTimer m_scrollTimer;
    QTime m_lastMessage;
    void enableUndoRedo();
    QString doNewlineEnforcement(const QString &out);

    OutputWindowPrivate *d;
};
} // namespace OutputPlugin
#endif // OUTPUTWINDOW_H
