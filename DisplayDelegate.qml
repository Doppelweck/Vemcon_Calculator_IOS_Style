import QtQuick
import Calculator 1.0

Rectangle {

    //property alias a_DisplayText: displayText.text

    id: displayDelegate
    width:displayBox.width
    height:displayBox.height
    color: "black"
    Text {
        id: displayText
        text: Number(Calculator.displayTXT)
        width:displayDelegate.width
        height:displayDelegate.height
        //anchors.fill: calculatorDelegate
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignBottom
        font.pixelSize: displayDelegate.height/2
        rightPadding: 10
        color: "#FFFFFF"
        font.bold: false
        MouseArea {
            id: displayMouseArea
               anchors.fill: parent
               onClicked: {Calculator.displayClickedFunction()}
               onPressed: {}
           }
    }


}
