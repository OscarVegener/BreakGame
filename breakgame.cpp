#include "breakgame.h"
#include "ui_breakgame.h"

BreakGame::BreakGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BreakGame)
{
    ui->setupUi(this);
    ui->processFilesButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
}

BreakGame::~BreakGame()
{
    delete ui;
}

void BreakGame::editFile(const QString &filePath, const QString &searchFor, const QString &changeTo)
{
    QFile file(filePath);
    if (file.exists()){
        if (!file.open(QIODevice::ReadWrite)){
            return;
        }
        QTextStream fileStream(&file);
        QString text;
        text = fileStream.readAll();
        text.replace(searchFor, changeTo);
        file.resize(0);
        fileStream << text;
        file.close();
    }
}

int BreakGame::fileContains(const QString &filePath, const QString &value)
{
    QFile file(filePath);
    if (file.exists()){
        if(!file.open(QIODevice::ReadOnly)){
            return -1;
        }
        QTextStream fileStream(&file);
        QString text = fileStream.readAll();
        if (text.contains(value)){
            file.close();
            return 0;
        }
        else{
            file.close();
            return 1;
        }
    }
    return 2;
}

QStringList *BreakGame::getFileList(const QString &dirPath, const QString &searchFor)
{
    QStringList *list = new QStringList;
    QDir dir(dirPath);
    if (dir.exists()){
        QStringList allFilesList = dir.entryList();
        foreach (QString fileName, allFilesList) {
            QString path = dir.absoluteFilePath(fileName);
            if(!fileContains(path, searchFor)){
                list->push_back(path);
            }
        }
    }
    return list;
}


void BreakGame::on_getFilesButton_clicked()
{
    if (!ui->triggerLine->text().isEmpty()){
        QFileDialog dlg(this);
        dlg.setFileMode(QFileDialog::DirectoryOnly);
        if (dlg.exec()){
            QStringList fileNames = dlg.selectedFiles();
            if (fileNames.empty()){
                QMessageBox::warning(this, "BreakGame", "Error opening folder!");
                return;
            }
            QString dirPath = fileNames.takeAt(0);
            fileList = getFileList(dirPath, ui->triggerLine->text());
            qDebug() << *fileList;
            ui->pathsTextEdit->setPlainText(fileList->join("\n"));
            ui->processFilesButton->setEnabled(true);
            ui->clearButton->setEnabled(true);
            ui->statusbar->showMessage("Successfully got list of files!", 2000);
        }
    }
    else{
        QMessageBox::warning(this, "BreakGame", "You have not specified the trigger!");
    }
}

void BreakGame::on_processFilesButton_clicked()
{
    foreach (QString filePath, *fileList) {
        editFile(filePath, ui->searchLine->text(), ui->changeLine->text());
    }
    ui->statusbar->showMessage("Files have been edited!", 2000);
}

void BreakGame::on_clearButton_clicked()
{
    ui->processFilesButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->pathsTextEdit->clear();
    ui->triggerLine->clear();
    ui->searchLine->clear();
    ui->changeLine->clear();
    fileList->clear();
    ui->statusbar->showMessage("All fields have been cleared!", 2000);
}
