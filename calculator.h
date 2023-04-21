#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QQmlEngine>
#include <iostream>
#include <string>


class Calculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double displayTXT READ getDisplayTXT WRITE setDisplayTXT NOTIFY displayTXTChanged)
    Q_PROPERTY(double operationHighlight READ getOperationHighlight WRITE setOperationHighlight NOTIFY operationHighlightChanged)
    Q_PROPERTY(double acButton READ getAcButton WRITE setAcButton NOTIFY acButtonChanged)

private:
    static Calculator *_instance;
    double _akku_1 = 0;
    double _akku_2 = 0;
    std::string _numberString = "";
    int _operation = 0;  //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
    int _operationHighlight = 0;  //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/" Highlight for VIEW
    int _acButton = 0;
    double _displayTXT = 0;

public:
    //static QObject *_instance;
    explicit Calculator(QObject *parent = nullptr);
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    static Calculator *instance();

signals:
    void displayTXTChanged();
    void operationHighlightChanged();
    void acButtonChanged();
public slots:

    double numberInputFunction(int index);

    double roundNumber(double num, int numOfDecimalPlaces);

    void displayClickedFunction(void);

    void convertNumberFunction(std::string symbol);

    void addFunction();

    void subFunction();

    void mulFunction();

    void divFunction();

    void acFunction();

    void signFunction();

    void perCentFunction();


    double getDisplayTXT() {
        //qDebug()<< "Zahl   : " << _displayTXT;
        return _displayTXT;
    }

    void setDisplayTXT(double num) {
        _displayTXT = num;
        emit displayTXTChanged();

    }

    int getAcButton(){
        return _acButton;
    }

    void setAcButton(double num){
        _acButton = num;
        emit acButtonChanged();
    }

    int getOperationHighlight(){

        return _operationHighlight;
    }

    int setOperationHighlight(int op) {
        _operationHighlight = op;
        emit operationHighlightChanged();
        return op;
    }
};

#endif // CALCULATOR_H
