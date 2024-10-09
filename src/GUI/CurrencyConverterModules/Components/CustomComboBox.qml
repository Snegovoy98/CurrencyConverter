pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls

ComboBox {
    id: root

    model: ListModel {
        ListElement {
            currency: "Dollar"
            value: 41
        }

        ListElement {
            currency: "Euro"
            value: 42
        }
    }

    textRole: "currency"

    delegate: ItemDelegate {
        id: itemDelegate
        width: root.width
        required property int index
        required property string currency

        contentItem: Label {
            id: it
            text: itemDelegate.currency
            color: "blue"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        highlighted: root.highlightedIndex === index
    }
}
