import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import Atomify 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent
        TextEdit {
            id: textEdit
            verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Button {
            text: "Run script"
        }
    }
}
