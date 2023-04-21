import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Calculator 1.0


ApplicationWindow {
    id: applicationWindow
    width: 350
    height: 550
    visible: true
    title: qsTr("Calculator")


    CalculatorDelegate{
        width: applicationWindow.width
        height: applicationWindow.height
    }
}
