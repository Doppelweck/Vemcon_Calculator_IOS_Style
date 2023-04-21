import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts


ItemDelegate{
    id: calculatorDelegate
    width: applicationWindow.width
    height: applicationWindow.height
    Rectangle{
        id: calculatorDelegateBox
        width: applicationWindow.width
        height: applicationWindow.height
        color:"black"
    ColumnLayout{
        Layout.preferredWidth: calculatorDelegate.width
        Layout.preferredHeight:  calculatorDelegate.height
        spacing: 0

        Rectangle{//Top
            id: topBox
            Layout.preferredWidth: calculatorDelegate.width
            Layout.preferredHeight: 20
            Layout.alignment: Qt.AlignTop
            color:"black"
        }
        Rectangle{ //Display
            id: displayBox
            Layout.preferredWidth: calculatorDelegate.width
            Layout.preferredHeight: (calculatorDelegate.height*1/3) -topBox.height
            Layout.alignment: Qt.AlignTop
            color:"black"

            DisplayDelegate{id:displayDelegate}


        }
        Rectangle{//Numpad
            id: numpadBox
            Layout.preferredWidth: calculatorDelegate.width
            Layout.preferredHeight: (calculatorDelegate.height*2/3) -bottomBox.height
            Layout.alignment: Qt.AlignTop
            color:"black"

            NumpadDelegate{id:numpadDelagate}
        }
        Rectangle{//Bottom
            id: bottomBox
            Layout.preferredWidth: calculatorDelegate.width
            Layout.preferredHeight: 20
            Layout.alignment: Qt.AlignBottom
            color:"black"
        }
    }
}
}
