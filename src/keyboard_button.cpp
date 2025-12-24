#include "keyboard_button.hpp"

#include <QSizePolicy>

using biv::KeyBoardButton;

KeyBoardButton::KeyBoardButton(const QString& text, QWidget* parent)
    : QPushButton(parent) {
    setFont(QFont("Roboto", 20));
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Подключаем стандартный сигнал clicked к нашему сигналу
    connect(this, &QPushButton::clicked, [this, text]() {
        emit clickedWithText(text);
    });
}
