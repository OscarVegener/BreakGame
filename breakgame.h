#ifndef BREAKGAME_H
#define BREAKGAME_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class BreakGame; }
QT_END_NAMESPACE

class BreakGame : public QMainWindow
{
    Q_OBJECT

public:
    BreakGame(QWidget *parent = nullptr);
    ~BreakGame();

private slots:
    void on_getFilesButton_clicked();

    void on_processFilesButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::BreakGame *ui;
    QStringList *fileList;
    void editFile(const QString &filePath, const QString &searchFor, const QString &changeTo);
    int fileContains(const QString &filePath, const QString &value);
    QStringList* getFileList(const QString &dirPath, const QString &searchFor);
};
#endif // BREAKGAME_H
