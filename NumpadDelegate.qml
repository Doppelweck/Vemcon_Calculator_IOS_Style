import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Calculator 1.0


GridLayout{

    property double displayInput

    property bool operationChecked: false


    Layout.preferredWidth:numpadBox.width
    Layout.preferredHeight:calculatorDelegate.height
    columnSpacing: 0
    rowSpacing:0

    rows:4
    columns:5

    Repeater{
        id: numpadRepeater
        model: 19

        Rectangle {
            id: numbadElementBox
            readonly property var rowVector:    [0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4]
            readonly property var columnVector: [0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,2,3]
            readonly property var buttonName:   ["AC","+/-","%","÷","7","8","9","×","4","5","6","-","1","2","3","+"," 0",",","="]
            //readonly property var buttonName2:   ["C","+/-","%","÷","7","8","9","×","4","5","6","-","1","2","3","+"," 0",",","="]

            property int buttonWidth: numpadRepeater.itemAt(index).width < numpadRepeater.itemAt(index).height ? numpadRepeater.itemAt(index).width:numpadRepeater.itemAt(index).height
            property int buttonHeight: numpadRepeater.itemAt(index).width < numpadRepeater.itemAt(index).height ? numpadRepeater.itemAt(index).width:numpadRepeater.itemAt(index).height

            color: "black"
            //border.color: "black"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: index===16 ? 2:1
            Layout.rowSpan: index===16 ? 1:1
            Layout.preferredWidth: numpadBox.width/4
            Layout.preferredHeight: numpadBox.height/5
            Layout.row: rowVector[index]
            Layout.column: columnVector[index]
            Rectangle{
                id: numbadElementBoxBack
                width: index===16 ? (numpadRepeater.itemAt(index).width-(numpadRepeater.itemAt(index-1).width-numpadRepeater.itemAt(index-1).children[0].width))-2 : buttonWidth-12
                height: buttonHeight-12

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                radius:(buttonHeight-11)/2
                color:"#FFFFFF"

                RoundButton{
                    id: numPadButtons
                    width: index===16 ? numpadRepeater.itemAt(index).width-(numpadRepeater.itemAt(index-1).width-numpadRepeater.itemAt(index-1).children[0].width) : buttonWidth-10
                    height: buttonHeight-10
                    flat: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    checkable: false
                    checked: false

                    onClicked:{Calculator.numberInputFunction(index)
                        setChecked()
                        Calculator.getAcButton() !== 0 ? numpadRepeater.itemAt(0).children[0].children[0].children[0].text = "C" : numpadRepeater.itemAt(0).children[0].children[0].children[0].text = "AC"
                        console.log(Calculator.getAcButton())
                    }

                    function setChecked(){
                        switch(Calculator.getOperationHighlight()){
                        case 0:
                            numpadRepeater.itemAt(15).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(11).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(7).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(3).children[0].children[0].checked = false;
                            break;
                        case 1:
                            numpadRepeater.itemAt(11).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(7).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(3).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(15).children[0].children[0].checked = true;
                            break;
                        case 2:
                            numpadRepeater.itemAt(15).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(7).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(3).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(11).children[0].children[0].checked = true;
                            break;
                        case 3:
                            numpadRepeater.itemAt(15).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(11).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(3).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(7).children[0].children[0].checked = true;
                            break;
                        case 4:
                            numpadRepeater.itemAt(15).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(11).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(7).children[0].children[0].checked = false;
                            numpadRepeater.itemAt(3).children[0].children[0].checked = true;
                            break;
                        default:
                        }
                    }

                    //text: buttonName[index]
                    Text {
                        //id: controlText
                        anchors.fill: parent
                        horizontalAlignment: index===16? Text.AlignHLeft:Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: index===16? (numpadRepeater.itemAt(0).width-10)/4 : 0
                        font.pixelSize: buttonHeight/3
                        color: index<3 ?"#000000":"#FFFFFF"
                        text:buttonName[index]
                        font.bold: true
                    }

                    background: Rectangle {

                        color: setButtonColor(index)
                        opacity: parent.checked || parent.pressed ? 0.5:1
                        height: buttonHeight-10
                        width: index===16 ? numpadRepeater.itemAt(index).width-(numpadRepeater.itemAt(index-1).width-numpadRepeater.itemAt(index-1).children[0].width) : buttonWidth-10
                        radius:(buttonHeight-10)/2

                        function setButtonColor(index){
                            if(index<3)
                                return "#A0A0A0"
                            else if(index===3||index===7||index===11||index===15||index===18)
                                return "#F69906"
                            else
                                return "#313131"
                        }


                    }
                }



            }
        }

    }
}






//ColumnLayout{
//    Layout.preferredWidth:numpadBox.width/3
//    Layout.preferredHeight:calculatorDelegate.width/5
//    spacing:0

//    RowLayout{
//        Layout.preferredWidth:calculatorDelegate.width/3
//        Layout.preferredHeight:calculatorDelegate.width/5
//        spacing:0

//        Rectangle{
//            Layout.preferredWidth: calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//    }

//    RowLayout{
//        Layout.preferredWidth:calculatorDelegate.width/3
//        Layout.preferredHeight:calculatorDelegate.width/5
//        spacing:0

//        Rectangle{
//            Layout.preferredWidth: calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//    }

//    RowLayout{
//        Layout.preferredWidth:calculatorDelegate.width/3
//        Layout.preferredHeight:calculatorDelegate.width/5
//        spacing:0

//        Rectangle{
//            Layout.preferredWidth: calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//    }

//    RowLayout{
//        Layout.preferredWidth:calculatorDelegate.width/3
//        Layout.preferredHeight:calculatorDelegate.width/5
//        spacing:0

//        Rectangle{
//            Layout.preferredWidth: calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"blue"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//    }

//    RowLayout{
//        Layout.preferredWidth:calculatorDelegate.width/3
//        Layout.preferredHeight:calculatorDelegate.width/5
//        spacing:0

//        Rectangle{
//            Layout.preferredWidth: calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//        Rectangle{
//            Layout.preferredWidth:calculatorDelegate.width/4
//            Layout.preferredHeight:calculatorDelegate.width/5
//            Layout.alignment: Qt.AlignLeft
//            color:"black"


//        }
//    }

//}


