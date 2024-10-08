import QtQuick 2.15

ListModel {
    id: rootModel

    ListElement {
        source: "qrc:/private/countries_icons/en-language-icon.svg"
        title: qsTr("English")
        color: "blue"
        code: "en"
    }

    ListElement {
        source: "qrc:/private/countries_icons/fr-language-icon.svg"
        title: qsTr("French")
        color: "blue"
        code : "fr"
    }

    ListElement {
        source: "qrc:/private/countries_icons/it-language-icon.svg"
        title: qsTr("Italian")
        color: "blue"
        code : "it"
    }

    ListElement {
        source: "qrc:/private/countries_icons/es-language-icon.svg"
        title: qsTr("Spanish")
        color: "blue"
        code : "sp"
    }

    ListElement {
        source: "qrc:/private/countries_icons/ru-language-icon.svg"
        title: qsTr("Russian")
        color: "blue"
        code : "ru"
    }

    ListElement {
        source: "qrc:/private/countries_icons/uk-language-icon.svg"
        title: qsTr("Ukrainian")
        color: "blue"
        code : "ua"
    }
}
