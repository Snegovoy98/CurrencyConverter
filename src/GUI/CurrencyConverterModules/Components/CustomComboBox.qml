pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls

ComboBox {
    id: root

    delegate: ItemDelegate {
        id: itemDelegate
        width: root.width
        required property int index
        required property string currency_value

        contentItem: Label {
            id: it
            text: itemDelegate.currency_value
            color: "blue"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        highlighted: root.highlightedIndex === index
    }
}
