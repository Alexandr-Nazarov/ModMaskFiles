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

public:
    Moding();

public slots:

    void toChangeFile(QTextStream&, const QFileInfo, const QString);

    void changeVariadic(const QString& tmp) { variadic= tmp.toUtf8(); }

    void changeOperationAnd(){operation=BINAR::AND; }
    void changeOperationOr(){operation=BINAR::OR; }
    void changeOperationXor(){operation=BINAR::XOR;}

    void rewriteOut(bool tmp) {rewriteOutFile=tmp;}

};

#endif // MODING_H
