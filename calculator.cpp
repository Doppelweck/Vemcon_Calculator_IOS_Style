#include "calculator.h"
#include <QDebug>
#include <iostream>
#include <string>
#include <math.h>
#include <bits/stdc++.h>

Calculator::Calculator(QObject *parent)
{

}

Calculator *Calculator::_instance = nullptr;

QObject *Calculator::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return Calculator::instance();
}

Calculator *Calculator::instance()
{
    if (_instance == nullptr) {
        _instance = new Calculator;
    }
    return _instance;

}


double Calculator::numberInputFunction(int index){

    qDebug()<< index;


    switch(index){
    case 0:  // AC
        acFunction();
        break;
    case 1:  // +-
        signFunction();
        break;
    case 2:  // %
        perCentFunction();
        break;
    case 3:  // /
        _op = DIV; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_op);
        _numberString = "";
        break;
    case 4:  // 7
        convertNumberFunction("7");
        break;
    case 5:  // 8
        convertNumberFunction("8");
        break;
    case 6:  // 9
        convertNumberFunction("9");
        break;
    case 7:  // *
        _op = MUL; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_op);
        _numberString = "";
        break;
    case 8:  // 4
        convertNumberFunction("4");
        break;
    case 9:  // 5
        convertNumberFunction("5");
        break;
    case 10: // 6
        convertNumberFunction("6");
        break;
    case 11: // -
        _op = SUB; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_op);
        _numberString = "";
        break;
    case 12: // 1
        convertNumberFunction("1");
        break;
    case 13: // 2
        convertNumberFunction("2");
        break;
    case 14: // 3
        convertNumberFunction("3");
        break;
    case 15: // +
        _op = ADD; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_op);
        _numberString = "";
        break;
    case 16: // 0
        convertNumberFunction("0");
        break;
    case 17: // ,
        if(_numberString.contains('.')){
            //Number already contains a komma
        }else{
            convertNumberFunction(".");
        }
        break;
    case 18: // =
        switch(_op){ //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        case 0:
            break;
        case 1:
            addFunction();
            setDisplayTXT(_akku_1);
            break;
        case 2:
            subFunction();
            setDisplayTXT(_akku_1);
            break;
        case 3:
            mulFunction();
            setDisplayTXT(_akku_1);
            break;
        case 4:
            divFunction();
            setDisplayTXT(_akku_1);
            break;
        default:
            break;
        }
        _numberString = "";
        break;
    }

    qDebug()<< "Akku1    : " << _akku_1;
    qDebug()<< "Akku2    : " << _akku_2;
    qDebug()<< "Operation: " << _op;
    qDebug()<< "OP HL    : " << _operationHighlight;

    if(_akku_1 != 0 || (_akku_2 != 0 && _op>0)){
        setAcButton(1);
    }else{
        setAcButton(0);
    }

    return 0;

}

double Calculator::roundNumber(double num, int numOfDecimalPlaces){

    //    num = num * std::pow(10,numOfDecimalPlaces);
    //    num = int(num);
    return num;//(num / std::pow(10,numOfDecimalPlaces));
}

void Calculator::displayClickedFunction(){

    int len = _numberString.length();
    if(_op == NOP){
        if(len == 1){
            _numberString =  "0";
            _akku_1 = 0;
            setDisplayTXT(_akku_1);

        }else if(len > 1){
            _numberString =  _numberString.left(len-1);//.substr(0,len-1);
            if(_numberString.right(0) == "."){
                _numberString =  _numberString.left(len-2);
            }
            _akku_1 =  _numberString.toDouble();
            setDisplayTXT(_akku_1);
        }
    }else{
        if(len == 1){

            _numberString =  "0";
            _akku_2 = 0;
            setDisplayTXT(_akku_2);

        }else if(len > 1){
            _numberString =  _numberString.left(len-1);
            if(_numberString.right(0) == "."){
                _numberString =  _numberString.left(len-2);
            }
            _akku_2 =  _numberString.toDouble();
            setDisplayTXT(_akku_2);
        }

    }

}

void Calculator::convertNumberFunction(QString symbol){

    _numberString = _numberString + symbol ;
    if(_op == NOP){
        _operationHighlight = _op;
        setOperationHighlight(_operationHighlight);
        _akku_1 = _numberString.toDouble();
        setDisplayTXT(_akku_1);

    }
    else{
        _operationHighlight = 0;
        setOperationHighlight(_operationHighlight);
        //_operation = 0;
        _akku_2 = _numberString.toDouble();
        setDisplayTXT(_akku_2);
    }

}

void  Calculator::addFunction(){
    _akku_1 = _akku_1 + _akku_2;
}

void  Calculator::subFunction(){
    _akku_1 = _akku_1 - _akku_2;
}

void  Calculator::mulFunction(){
    _akku_1 = roundNumber(_akku_1 * _akku_2,5);

}

void  Calculator::divFunction(){
    _akku_1 = roundNumber(_akku_1 /_akku_2,5);
}

void  Calculator::acFunction(){

    if(_op > NOP && _akku_2 != 0){
        //C Befehl AKKU 2
        _numberString = "";
        _akku_2 = 0;
        setDisplayTXT(_akku_2);
        setOperationHighlight(_op);

    }else if(_op > NOP && _akku_2 == 0){
        // AC Befehl
        _numberString = "";
        _akku_2 = 0;
        _akku_1 = 0;
        setDisplayTXT(_akku_1);
        _op = NOP;
        setOperationHighlight(_op);


    }else if(_op == NOP && _akku_2 == 0){
        // AC Befehl
        _numberString = "";
        _akku_2 = 0;
        _akku_1 = 0;
        setDisplayTXT(_akku_1);
        _op = NOP;
        setOperationHighlight(_op);

    }

}

void  Calculator::signFunction(){
    if(_op == NOP){
        _akku_1 = _akku_1*(-1);
        setDisplayTXT(_akku_1);
        _numberString =  QString::number(_akku_1);
    }
    else{
        _akku_2 = _akku_2*(-1);
        setDisplayTXT(_akku_2);
        _numberString =  QString::number(_akku_2);
    }
}

void  Calculator::perCentFunction(){
    qDebug()<< "percent: " << _akku_1;
    if(_op == NOP){
        _akku_1 = roundNumber(_akku_1*(0.01),5);
        setDisplayTXT(_akku_1);
        _numberString =  QString::number(_akku_1);

        int i = _numberString.length();
        for(i; i>0 && (_numberString.mid(i-1,i-1)=="0"||_numberString.mid(i-1,i-1)=="." ); i--){
            _numberString =  _numberString.mid(0,i-1);
        }
    }
    else{
        _akku_1 = roundNumber(_akku_2*(0.01),5);
        setDisplayTXT(_akku_2);
        _numberString =  QString::number(_akku_2);

        int i = _numberString.length();
        for(i; i>0 && (_numberString.mid(i-1,i-1)=="0"||_numberString.mid(i-1,i-1)=="." ); i--){
            _numberString =  _numberString.mid(0,i-1);
        }
    }
}
