#include "modmaskfile.h"
#include "ui_modmaskfile.h"

ModMaskFile::ModMaskFile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ModMaskFile)
{
    ui->setupUi(this);

    Moding *modingFile=new Moding();

    //отметка на удаление
    QObject::connect(ui->deleteBox, SIGNAL(clicked(bool)), this ,SLOT(delete_input_file(bool)));


    //выбор файлов по маске
     QObject::connect(ui->InButton, SIGNAL(clicked()), this ,SLOT(select_in_files()));

    //выбор сохранения
    QObject::connect(ui->rewriteBox, SIGNAL(clicked(bool)), this ,SLOT(delete_out_file(bool)));
    QObject::connect(ui->OutButton, SIGNAL(clicked()), this ,SLOT(select_out_dir()));
    QObject::connect(this, SIGNAL(dirName(QString)),ui->line_SaveDir, SLOT(setText(QString)));

    //старт
     QObject::connect(ui->StartButton, SIGNAL(clicked()), this, SLOT (/*start()*/push_start_button() ));
     QObject::connect(this, SIGNAL(toChangeFile(QTextStream&, QFileInfo, QString)), modingFile, SLOT(toChangeFile(QTextStream&, QFileInfo, QString)));

    //смена переменной и операции
     QObject::connect(ui->lineEdit, SIGNAL(textChanged(QString)), modingFile, SLOT(changeVariadic(QString)));
     QObject::connect(ui->radioButton_And, SIGNAL(clicked()), modingFile, SLOT(changeOperationAnd()));
     QObject::connect(ui->radioButton_Or, SIGNAL(clicked()), modingFile, SLOT(changeOperationOr()));
     QObject::connect(ui->radioButton_Xor, SIGNAL(clicked()), modingFile, SLOT(changeOperationXor()));

     //перезапись выходного
      QObject::connect(ui->rewriteBox, SIGNAL(clicked(bool)),modingFile, SLOT(rewriteOut(bool)));

      //таймер
      timer=new QTimer(this);
      QObject::connect(timer, SIGNAL(timeout()), this, SLOT(start()));
      QObject::connect(ui->timerBox, SIGNAL(clicked(bool)), this ,SLOT(with_timer(bool)));
}

ModMaskFile::~ModMaskFile()
{
    delete ui;
}


void ModMaskFile::select_in_files(){

    fileMask=ui->MaskEdit->text();

    filePath=QFileDialog::getOpenFileNames(nullptr, tr("Open file"),QDir::currentPath(),fileMask);

}

void ModMaskFile::select_out_dir(){

    DirPath=QFileDialog::getExistingDirectory(nullptr, tr("Save file"),QDir::currentPath());
    if (!DirPath.isEmpty()){

        dirToSave=DirPath;
            emit dirName(dirToSave);
        }
    }

void ModMaskFile::start(){

    for (const auto & x: filePath) {
    if (!/*filePath*/x.isEmpty()&&!DirPath.isEmpty() ){

        QFile file(/*filePath*/x);

        if (!file.isOpen())
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QFileInfo fileInfo(file);
            QTextStream out(&file);
            emit toChangeFile(out, fileInfo, DirPath);

            file.close();
            //удаление исходного
            if (deleteInputFile) {
                QFile::remove(/*filePath*/x);
            }
            qDebug()<<"start";
        }
 //   qDebug()<<"start";
    }
}
}

void ModMaskFile::push_start_button(){

    if (withTimer){
        timer->start(3000);
    }
    else {
        start();
    }
}


