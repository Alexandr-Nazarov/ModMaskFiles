#include "moding.h"

Moding::Moding()
{

}


void Moding::toChangeFile(/*QTextStream&in*/QByteArray& tochange, const QFileInfo fileinfo,const QString dirPath){

    static size_t num=0;
    QString filename=fileinfo.baseName()+"_"+QString::number(num) +"."+fileinfo.suffix();
    QFile file(dirPath+"/"+filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
//        QByteArray tochange;
//        while(!in.atEnd()){
//          //  qDebug()<<"ok2"<<in.read(1);
//          //   qDebug()<<in.read(1).toUtf8() ;
//            tochange.push_back(in.read(1).toUtf8() );
//            qDebug()<<"tochange";
//        }


        if (variadic.size()){
        for(int i=0; i<tochange.size();i++){
            if (operation==BINAR::AND){
            tochange[i]=tochange[i]&variadic[i%(variadic.size())];
            }
            else if (operation==BINAR::OR){
                tochange[i]=tochange[i]|variadic[i%(variadic.size())];
            }
            else if (operation==BINAR::XOR){
                tochange[i]=tochange[i]^variadic[i%(variadic.size())];
            }
          }
        }


         file.write(tochange);
    }

    file.close();
    num++;

    if(rewriteOutFile) num--;

}

