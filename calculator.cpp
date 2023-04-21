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
        _operation = 4; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_operation);
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
        _operation = 3; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_operation);
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
        _operation = 2; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_operation);
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
        _operation = 1; //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
        setOperationHighlight(_operation);
        _numberString = "";
        break;
    case 16: // 0
        convertNumberFunction("0");
        break;
    case 17: // ,
        if(_numberString.find('.')!= std::string::npos){

        }else{
            convertNumberFunction(".");
        }
        break;
    case 18: // =
        switch(_operation){ //0="NOP"; 1="+" ; 2="-" ; 3="*"; 4="/"
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
    qDebug()<< "Operation: " << _operation;
    qDebug()<< "OP HL    : " << _operationHighlight;

    if(_akku_1 != 0 || (_akku_2 != 0 && _operation>0)){
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
    if(_operation==0){
        if(len == 1){
            _numberString =  "0";
            _akku_1 = 0;
            setDisplayTXT(_akku_1);

        }else if(len > 1){
            _numberString =  _numberString.substr(0,len-1);
            if(_numberString.substr(len-2,len-1) == "."){
                _numberString =  _numberString.substr(0,len-2);
            }
            _akku_1 =  std::stod(_numberString);
            setDisplayTXT(_akku_1);
        }
    }else{
        if(len == 1){

            _numberString =  "0";
            _akku_2 = 0;
            setDisplayTXT(_akku_2);

        }else if(len > 1){
            _numberString =  _numberString.substr(0,len-1);
            if(_numberString.substr(len-2,len-1) == "."){
                _numberString =  _numberString.substr(0,len-2);
            }
            _akku_2 =  std::stod(_numberString);
            setDisplayTXT(_akku_2);
        }

    }

}

void Calculator::convertNumberFunction(std::string symbol){

    _numberString = _numberString + symbol ;
    if(_operation==0){
        _operationHighlight = _operation;
        setOperationHighlight(_operationHighlight);
        _akku_1 = std::stod(_numberString);
        setDisplayTXT(_akku_1);

    }
    else{
        _operationHighlight = 0;
        setOperationHighlight(_operationHighlight);
        //_operation = 0;
        _akku_2 = std::stod(_numberString);
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

    if(_operation > 0 && _akku_2 != 0){
        //C Befehl AKKU 2
        _numberString = "";
        _akku_2 = 0;
        setDisplayTXT(_akku_2);
        setOperationHighlight(_operation);

    }else if(_operation > 0 && _akku_2 == 0){
        // AC Befehl
        _numberString = "";
        _akku_2 = 0;
        _akku_1 = 0;
        setDisplayTXT(_akku_1);
        _operation = 0;
        setOperationHighlight(_operation);


    }else if(_operation == 0 && _akku_2 == 0){
        // AC Befehl
        _numberString = "";
        _akku_2 = 0;
        _akku_1 = 0;
        setDisplayTXT(_akku_1);
        _operation = 0;
        setOperationHighlight(_operation);

    }

}

void  Calculator::signFunction(){
    if(_operation==0){
        _akku_1 = _akku_1*(-1);
        setDisplayTXT(_akku_1);
        _numberString =  std::to_string(_akku_1);
    }
    else{
        _akku_2 = _akku_2*(-1);
        setDisplayTXT(_akku_2);
        _numberString =  std::to_string(_akku_2);
    }
}

void  Calculator::perCentFunction(){
    qDebug()<< "percent: " << _akku_1;
    if(_operation==0){
        _akku_1 = roundNumber(_akku_1*(0.01),5);
        setDisplayTXT(_akku_1);
        _numberString =  std::to_string(_akku_1);

        int i = _numberString.length();
        for(i; i>0 && (_numberString.substr(i-1,i-1)=="0"||_numberString.substr(i-1,i-1)=="." ); i--){
            _numberString =  _numberString.substr(0,i-1);
        }
    }
    else{
        _akku_1 = roundNumber(_akku_2*(0.01),5);
        setDisplayTXT(_akku_2);
        _numberString =  std::to_string(_akku_2);

        int i = _numberString.length();
        for(i; i>0 && (_numberString.substr(i-1,i-1)=="0"||_numberString.substr(i-1,i-1)=="." ); i--){
            _numberString =  _numberString.substr(0,i-1);
        }
    }
}







