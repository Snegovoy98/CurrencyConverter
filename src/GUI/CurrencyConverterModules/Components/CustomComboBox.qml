pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls
import com.preobrazhenskyi.Constants 1.0
import com.preobrazhenskyi.Theme 1.0

ComboBox {
    id: root

    delegate: ItemDelegate {
        id: itemDelegate
        width: root.width

        required property int index
        required property string currency_title

        contentItem: Label {
            id: it
            text: itemDelegate.currency_title
            color: "blue"
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        highlighted: root.highlightedIndex === index
    }
}
