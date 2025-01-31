#ifndef MODMASKFILE_H
#define MODMASKFILE_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>

#include "moding.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModMaskFile; }
QT_END_NAMESPACE

class ModMaskFile : public QMainWindow
{
    Q_OBJECT

public:
    ModMaskFile(QWidget *parent = nullptr);
    ~ModMaskFile();

private:
    Ui::ModMaskFile *ui;

    bool deleteInputFile{false};
    bool deleteOutFile{true};
    bool withTimer{false};
    QStringList filePath;
    QString DirPath;
    QString fileMask;
    QString dirToSave;

    QTimer *timer;

signals:
void toChangeFile(QTextStream&, QFileInfo, QString);
void dirName(QString);

public slots:

   void delete_input_file(bool tmp){ deleteInputFile=tmp;}
   void delete_out_file(bool tmp){ deleteOutFile=tmp;}
   void with_timer(bool tmp){ withTimer=tmp;}


   void select_in_files();
   void select_out_dir();
   void start();

   void push_start_button();

};
#endif // MODMASKFILE_H


