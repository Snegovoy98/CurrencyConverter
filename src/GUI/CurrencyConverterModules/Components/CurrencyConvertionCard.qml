import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: root
    property alias currencyonChanged: currencyOnChangedTitle.text

    Row {
        id: selectedCurrency
        width: 100
        height: 40

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: currencyOnChangedTitle
            text: "Euro"
            color: "blue"
            font.pointSize: 16

            anchors.verticalCenter: parent.verticalCenter
        }

        Image {
            id: delimiter
            width: 30
            height: 30
            source:Qt.resolvedUrl("qrc:/private/currency_delimiter.svg")
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: currencyToChangedTitle
            text: "USD"
            color: "red"
            font.pointSize: 16

            anchors.verticalCenter: parent.verticalCenter
        }
    }

    TextField {
        id: currencyOnExchangeTextField
        width: root.width - selectedCurrency.width
        placeholderText: qsTr("I changing")
        selectByMouse: true

        anchors {
            top: selectedCurrency.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
    }

    Label {
        id: oneCurrencyOnChangedValue
        font: currencyOnExchangeTextField.font
        text: "- Test = 12121223.1 USD"
        x: currencyOnExchangeTextField.x
        anchors.top: currencyOnExchangeTextField.bottom
    }

    TextField {
        id: currencyToExchangeTextField
        width: root.width - selectedCurrency.width
        placeholderText: qsTr("I receive")
        selectByMouse: true

        anchors {
            top: oneCurrencyOnChangedValue.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
    }

    Label {
        id: oneCurrencyToChangedValue
        font: currencyOnExchangeTextField.font
        text: "- USD = 12121223.1 Euro"
        x: currencyToExchangeTextField.x
        anchors.top: currencyToExchangeTextField.bottom
    }
}
