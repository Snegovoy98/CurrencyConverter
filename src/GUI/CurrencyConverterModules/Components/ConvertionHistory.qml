import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: control

    model: ListModel {
        ListElement {
          currency_title: "USD"
          value_per_unit: 41.121223123
          coverted_value: 3888
        }
    }

    delegate: Rectangle {
        id: convertionHistoryDelegate
        width: control.width
        height: 50

        RowLayout {
            anchors.fill: parent

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: 10

                Label {
                    text: model.currency_title
                    font.pointSize: 14
                }

                Label {
                    text: model.value_per_unit
                    font.pointSize: 14
                    color: "grey"
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 10

                Label {
                    text: model.coverted_value
                    font.pointSize: 14
                    color: "blue"
                }
            }
        }
    }
}
