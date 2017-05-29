import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQml.Models 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("qml test")

    Rectangle {
        width: 200; height: 100

        DelegateModel {
            id: visualModel
            model: ListModel {
                ListElement {
                    itemName: qsTr("Apple")
                    itemInputType: "checkbox"
                }
                ListElement {
                    itemName: qsTr("Orange")
                    itemInputType: "floatTextField"
                }
            }
            delegate: BaseDelegate {
                height: 50
                width: 400
                labelname: itemName
                inputtype: itemInputType
            }
        }

        ListView {
            anchors.fill: parent
            model: visualModel
        }
    }
}
