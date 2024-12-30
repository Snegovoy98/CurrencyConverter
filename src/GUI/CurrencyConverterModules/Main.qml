pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import com.preobrazhenskyi.Constants 1.0
import com.preobrazhenskyi.Theme 1.0
import "./Components"
import "./Common"
import "./Dialogs"
import com.preobrazhenskyi.currency_on_exchange_model 1.0
import com.preobrazhenskyi.currency_to_exchange_model 1.0
import com.preobrazhenskyi.history_exchanges_model 1.0

ApplicationWindow {
    id: mainPage
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: qsTr("Currency Converter")

    header: ToolBar {
        width: mainPage.width
        height: 50

        Label {
            text: qsTr("Currency Exchange")
            elide: Label.ElideRight
            anchors.centerIn: parent
        }

        ToolButton {
            id: lanugagesToolBar
            icon.source: "qrc:/private/language_button.svg"
            icon.width: 30
            icon.height: 30

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
            width: 140
            x: lanugagesToolBar.x - 15
            y: lanugagesToolBar.y + 35

            ListView {
                id: menuView
                anchors.fill: parent
                clip: true

                model: LanguagesModel {}

                delegate: ItemDelegate {
                    width: menuView.width
                    height: 35
                    spacing: 5

                    required property string source
                    required property color color
                    required property string title
                    required property string code

                    icon.source: source
                    icon.color: color
                    text: title
                    font.pointSize: Constants.languagesFontPointSize

                    onClicked: {
                        translator.setLanguage(code)
                        settingsWorker.saveSettings("language",  code)
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
                model: currencyOnExchangeModel
                textRole: "currency_title"
                valueRole: "currency_code"

                onCurrentTextChanged:  currencyCard.currencyOnChanged = selectionOnChanged.currentText

                onCurrentValueChanged:  currencyToExchangeModel.fetchCurrencyData(selectionOnChanged.currentValue)
            }

            RoundButton {
                id: refreshRoundButton
                Layout.preferredWidth: 30
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
                currentIndex: 0
                model: currencyToExchangeModel
                textRole: "currency_title"
                valueRole: "cross_rate"

                onCurrentTextChanged:  currencyCard.currencyToChanged = selectionToChanged.currentText

                onCurrentValueChanged:  {
                    if(currencyCard.crossRate !== undefined) {
                        currencyCard.crossRate = currentValue
                    }
                }
            }
        }

        CurrencyConvertionCard {
            id: currencyCard
            Layout.fillWidth: true
            Layout.preferredHeight: 250
            Layout.leftMargin:  Constants.margins
            Layout.rightMargin: Constants.margins
            radius: 12

            border {
                width: Constants.borderWidth
                color: Theme.borderStyleColor
            }
        }

        CurrencyOnExchangeModel {
            id: currencyOnExchangeModel
        }

        CurrencyToExchangeModel {
            id: currencyToExchangeModel
        }

        HistoryExchangesModel {
            id: historyExchangesModel

            Component.onCompleted:  historyExchangesModel.fetchExchangesHistory()
        }

        ConvertionHistory {
            id: convertionHistory
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin:  Constants.margins
            Layout.rightMargin: Constants.margins

            model: historyExchangesModel
        }

        Button {
            id: convertionButton
            text: qsTr("Save to history")
            Layout.preferredWidth: Constants.buttonsWidth
            Layout.preferredHeight: Constants.buttonsHeight
            highlighted: true
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 5

            onClicked: {
                if(!currencyCard.validate()) {
                    historyExchangesModel.saveHistory(selectionOnChanged.currentText,
                                                                    parseFloat(currencyCard.currencyOnExchangeTextField.text),
                                                                    selectionToChanged.currentText,
                                                                    parseFloat(currencyCard.currencyToExchangeTextField.text))
                } else {
                    if(!currencyCard.currencyOnExchangeTextField.focus) {
                         currencyCard.currencyOnExchangeTextField.focus = true
                    }
                }
            }
        }
    }

    MessageDialog {
        id: messgaeDialog
        width: 300
        height: 300
        visible:  checkMessageOnNull()
        message: checkMessageOnNull() ?  messageShower.message : ""
        anchors.centerIn: parent

        function checkMessageOnNull() {
            if(messageShower != null && messageShower.message != "") {
                return true
             } else {
                return false
            }
        }
    }
}
