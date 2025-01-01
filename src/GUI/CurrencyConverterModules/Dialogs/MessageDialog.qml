import QtQuick
import QtQuick.Controls
import com.preobrazhenskyi.Constants 1.0

Dialog {
    id: root
    modal: true
    standardButtons: Dialog.Ok

    property string message: ""

    header: Rectangle {
        width: parent.width

        Label {
             text: qsTr("Error")
             anchors.horizontalCenter: parent.horizontalCenter
             font.pixelSize: Constants.mainFontPointSize
             horizontalAlignment: Label.AlignHCenter
             verticalAlignment: Label.AlignVCenter
        }
    }

    contentItem: Rectangle {
        anchors.fill: parent

        Image {
            id: logo
            width: 120
            height: 120
            source:Qt.resolvedUrl("qrc:/private/alert_icon.svg")

            anchors {
                top: parent.top
                topMargin: 30
                horizontalCenter: parent.horizontalCenter
            }
        }

        Label {
             text: root.message
             width: 300
             height: 120
             font.pixelSize: Constants.currencyPointSize
             wrapMode: Label.WordWrap

             anchors {
                 top: logo.bottom
                 left: parent.left
                 leftMargin: 12
                 right: parent.right
                 bottom: parent.bottom
             }
        }
    }
}
