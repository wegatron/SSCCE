import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property string inputtype : ""
    property string labelname : ""

    Component {
       id: checkboxComponent
       CheckBox {
            checked: true
            text: labelname
        }
    }

    Component {
        id: floatTextFieldComponent
        RowLayout {
            Label {
                text: labelname
            }
            TextField {
                id: textField1
                placeholderText: qsTr("Text Field")
            }
        }
    }

    Loader {
        sourceComponent: {
            switch(inputtype) {
            case "checkbox": return checkboxComponent
            case "floatTextField": return floatTextFieldComponent
            }
        }
    }
}
