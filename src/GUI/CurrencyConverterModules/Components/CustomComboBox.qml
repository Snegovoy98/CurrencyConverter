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
        width: root.width
        contentItem: Label {
            text: model.currency
            color: "blue"
            font: root.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        highlighted: root.highlightedIndex === index
    }
}
