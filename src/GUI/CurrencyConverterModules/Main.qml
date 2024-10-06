import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Gui
import "./Components"
import "./Common"

ApplicationWindow {
    id: mainPage
    width: 640
    height: 480
    visible: true
    title: qsTr("Currency Converter")

    header: ToolBar {
        width: mainPage.width
        height: 50

        Label {
            text: qsTr("Currency Exchange")
            elide: Label.ElideRight
            anchors.centerIn: parent
            font.pointSize: Constants.mainFontPointSize
        }

        ToolButton {
            id: lanugagesToolBar
            icon.source: "qrc:/private/language_button.svg"
            icon.width: 25
            icon.height: 25

            anchors {
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            background: Rectangle {
                anchors.fill: parent
                color: "transparent"
            }

            onClicked: languagesMenu.open()
        }

        Menu {
            id: languagesMenu
            width: 100
            x: lanugagesToolBar.x - 15
            y: lanugagesToolBar.y + 35

            ListView {
                id: menuView
                anchors.fill: parent

                model: LanguagesModel {}

                delegate: MenuItem {
                    width: menuView.width
                    height: 25

                    icon.source: model.source
                    icon.color: model.color
                    text: model.title

                    onClicked: {
                        translator.setLanguage(model.code)
                        languagesMenu.close()
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    hoverEnabled: true
                    active: hovered || pressed
                    anchors {
                        top: parent.top
                        right: parent.right
                        bottom: parent.bottom
                    }
                }
            }
        }
    }

    background: Rectangle {
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: currencySelectionRow
            Layout.fillWidth: true
            Layout.fillHeight: true

            CustomComboBox {
                id: selectionOnChanged
                Layout.preferredWidth: Constants.comboboxWidth
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.leftMargin: Constants.margins
                currentIndex: 0
            }

            RoundButton {
                id: refreshRoundButton
                width: 30
                highlighted: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                icon.source: "qrc:/private/refresh_button.svg"

                onClicked: {
                    selectionOnChanged.currentIndex = 0
                    selectionToChanged.currentIndex = 1
                }
            }

            CustomComboBox {
                id: selectionToChanged
                Layout.preferredWidth: Constants.comboboxWidth
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.rightMargin: Constants.margins
                currentIndex: 1
            }
        }

        CurrencyConvertionCard {
            id: currencyCard
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin:  Constants.margins
            Layout.rightMargin: Constants.margins

            radius: 12

            border {
                width: Constants.borderWidth
                color: Theme.borderStyleColor
            }
        }

        ConvertionHistory {
            id: convertionHistory
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin:  Constants.margins
            Layout.rightMargin: Constants.margins
        }

        Button {
            id: convertionButton
            text: qsTr("Exchange")
            Layout.preferredWidth: Constants.buttonsWidth
            Layout.preferredHeight: Constants.buttonsHeight
            highlighted: true
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
