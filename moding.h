#ifndef MODING_H
#define MODING_H

#include <QDebug>

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QByteArray>

enum class BINAR{AND, OR, XOR};

class Moding: public QObject
{
    Q_OBJECT
private:

    QByteArray variadic;
    BINAR operation{BINAR::AND};
    bool rewriteOutFile{true};
    bool is_hex{false};

public:
    Moding();

public slots:

    void toChangeFile(QTextStream&, const QFileInfo, const QString);

    void changeVariadic(const QString& tmp) { if (is_hex) { variadic=QByteArray::fromHex(tmp.toUtf8().remove(0,2));} //0xa3f411b3432f31c2
                                                         else  {variadic= tmp.toUtf8();}  qDebug()<<variadic.toHex();}

    void changeOperationAnd(){operation=BINAR::AND; }
    void changeOperationOr(){operation=BINAR::OR; }
    void changeOperationXor(){operation=BINAR::XOR;}

    void rewriteOut(bool tmp) {rewriteOutFile=tmp;}

    void isHex(bool tmp){is_hex=tmp;}

};

#endif // MODING_H
