pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import com.preobrazhenskyi.Constants 1.0
import com.preobrazhenskyi.Theme 1.0

ListView {
    id: control

    clip: true

    Label {
        id: message
        text: qsTr("There is not data")
        visible: control.count == 0
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    delegate: Rectangle {
        id: convertionHistoryDelegate
        width: control.width
        height: 50

        required property string currency_on_exchange_title
        required property double value_per_unit
        required property string currency_to_exchange_title
        required property double exchanged_sum

        RowLayout {
            anchors.fill: parent

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: Constants.margins

                Label {
                    text: convertionHistoryDelegate.currency_to_exchange_title
                    font.pointSize: Constants.mainFontPointSize
                }

                Label {
                    text: convertionHistoryDelegate.value_per_unit.toFixed(Constants.currenciesNumbersAfterDot)
                    font.pointSize: Constants.mainFontPointSize
                    color: "grey"
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: Constants.margins

                Label {
                    Layout.alignment: Qt.AlignRight
                    text: convertionHistoryDelegate.currency_on_exchange_title
                    font.pointSize: Constants.mainFontPointSize
                }

                Label {
                    text: convertionHistoryDelegate.exchanged_sum.toFixed(Constants.currenciesNumbersAfterDot)
                    font.pointSize: Constants.mainFontPointSize
                    color: Theme.currencyOnExchangedColor
                }
            }
        }
    }

    ScrollBar.vertical: ScrollBar {
        hoverEnabled: true
        active: hovered || pressed
        size: control.contentHeight > 0 ? control.height / control.contentHeight : 1
        policy: ScrollBar.AsNeeded
    }
}
