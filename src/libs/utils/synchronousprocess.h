#pragma once

#include "utils_global.h"

#include <QProcess>
#include <QSharedPointer>
#include <QTextCodec>

#include <functional>

QT_FORWARD_DECLARE_CLASS(QDebug)

namespace Utils {

class SynchronousProcessPrivate;

/* Result of SynchronousProcess execution */
class FEEM_UTILS_EXPORT SynchronousProcessResponse
{
public:
    enum Result {
        // Finished with return code 0
        Finished,
        // Finished with return code != 0
        FinishedError,
        // Process terminated abnormally (kill)
        TerminatedAbnormally,
        // Executable could not be started
        StartFailed,
        // Hang, no output after time out
        Hang };

    void clear();

    // Helper to format an exit message.
    QString exitMessage(const QString &binary, int timeoutS) const;

    QByteArray allRawOutput() const;
    QString allOutput() const;

    QString stdOut() const;
    QString stdErr() const;

    Result result = StartFailed;
    int exitCode = -1;

    QByteArray rawStdOut;
    QByteArray rawStdErr;
    QTextCodec *codec = QTextCodec::codecForLocale();
};

FEEM_UTILS_EXPORT QDebug operator<<(QDebug str, const SynchronousProcessResponse &);

using ExitCodeInterpreter = std::function<SynchronousProcessResponse::Result(int /*exitCode*/)>;
FEEM_UTILS_EXPORT SynchronousProcessResponse::Result defaultExitCodeInterpreter(int code);

class FEEM_UTILS_EXPORT SynchronousProcess : public QObject
{
    Q_OBJECT
public:
    enum Flags {
        // Unix: Do not give the child process a terminal for input prompting.
        UnixTerminalDisabled = 0x1
    };

    SynchronousProcess();
    ~SynchronousProcess() override;

    /* Timeout for hanging processes (triggers after no more output
     * occurs on stderr/stdout). */
    void setTimeoutS(int timeoutS);
    int timeoutS() const;

    void setCodec(QTextCodec *c);
    QTextCodec *codec() const;

    QProcess::ProcessChannelMode processChannelMode () const;
    void setProcessChannelMode(QProcess::ProcessChannelMode m);

    bool stdOutBufferedSignalsEnabled() const;
    void setStdOutBufferedSignalsEnabled(bool);

    bool stdErrBufferedSignalsEnabled() const;
    void setStdErrBufferedSignalsEnabled(bool);

    bool timeOutMessageBoxEnabled() const;
    void setTimeOutMessageBoxEnabled(bool);

    QStringList environment() const;
    void setEnvironment(const QStringList &);

    void setProcessEnvironment(const QProcessEnvironment &environment);
    QProcessEnvironment processEnvironment() const;

    void setWorkingDirectory(const QString &workingDirectory);
    QString workingDirectory() const;

    unsigned flags() const;
    void setFlags(unsigned);

    void setExitCodeInterpreter(const ExitCodeInterpreter &interpreter);
    ExitCodeInterpreter exitCodeInterpreter() const;

    // Starts an nested event loop and runs the binary with the arguments
    SynchronousProcessResponse run(const QString &binary, const QStringList &args, const QByteArray &writeData = {});
    // Starts the binary with the arguments blocking the UI fully
    SynchronousProcessResponse runBlocking(const QString &binary, const QStringList &args);

    // Create a (derived) processes with flags applied.
    static QSharedPointer<QProcess> createProcess(unsigned flags);

    // Static helper for running a process synchronously in the foreground with timeout
    // detection similar SynchronousProcess' handling (taking effect after no more output
    // occurs on stderr/stdout as opposed to waitForFinished()). Returns false if a timeout
    // occurs. Checking of the process' exit state/code still has to be done.
    static bool readDataFromProcess(QProcess &p,
                                    int timeoutS,
                                    QByteArray *rawStdOut = nullptr,
                                    QByteArray *rawStdErr = nullptr,
                                    bool timeOutMessageBox = false);
    // Stop a process by first calling terminate() (allowing for signal handling) and
    // then kill().
    static bool stopProcess(QProcess &p);

    // Helpers to find binaries. Do not use it for other path variables
    // and file types.
    static QString locateBinary(const QString &binary);
    static QString locateBinary(const QString &path, const QString &binary);

    static QString normalizeNewlines(const QString &text);

signals:
    void stdOutBuffered(const QString &lines, bool firstTime);
    void stdErrBuffered(const QString &lines, bool firstTime);

public slots:
    bool terminate();

private:
    void slotTimeout();
    void finished(int exitCode, QProcess::ExitStatus e);
    void error(QProcess::ProcessError);
    void processStdOut(bool emitSignals);
    void processStdErr(bool emitSignals);

    SynchronousProcessPrivate *d;
};

} // namespace Utils
