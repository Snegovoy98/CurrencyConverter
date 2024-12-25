import QtQuick 2.15
import QtQuick.Controls
import com.preobrazhenskyi.Constants 1.0
import com.preobrazhenskyi.Theme 1.0

Rectangle {
    id: root
    property alias currencyOnChanged: currencyOnChangedTitle.text
    property alias currencyToChanged: currencyToChangedTitle.text
    property alias currencyOnExchangeTextField: currencyOnExchangeTextField
    property alias currencyToExchangeTextField: currencyToExchangeTextField
    property double crossRate: 0.00

    function validate() {
        return currencyOnExchangeTextField.text == ""
    }

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
            color: Theme.currencyOnExchangedColor
            font.pointSize: Constants.currencyPointSize
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
            color: Theme.currencyToExchangedColor
            font.pointSize: Constants.currencyPointSize
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
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }

        validator: DoubleValidator{
            locale: "en"
            decimals: 2
        }

        onTextChanged: {
             if(text != "") {
                currencyToExchangeTextField.text = parseFloat(text) * root.crossRate
             } else {
                currencyToExchangeTextField.clear()
            }
        }
    }

    Label {
        id: oneCurrencyOnChangedValue
        font: currencyOnExchangeTextField.font
        text: "- Test = 12121223.1 USD"
        x: currencyOnExchangeTextField.x
        anchors {
            top: currencyOnExchangeTextField.bottom
            topMargin: 10
        }
    }

    TextField {
        id: currencyToExchangeTextField
        width: root.width - selectedCurrency.width
        placeholderText: qsTr("I receive")
        readOnly: true

        anchors {
            top: oneCurrencyOnChangedValue.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
    }

    Label {
        id: oneCurrencyToChangedValue
        font: currencyOnExchangeTextField.font
        text: "- USD = 12121223.1 Euro"
        x: currencyToExchangeTextField.x
        anchors{
            top: currencyToExchangeTextField.bottom
            topMargin: 10
        }
    }
}
