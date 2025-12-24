#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTextEdit>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
    const int keyboard_width = 1160;
    resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
    
    QPixmap pixmap("img/grustnii-smail.png");
    QLabel* image = new QLabel(this);
    image->setFixedSize(200, 200);
    image->setPixmap(pixmap);
    image->setScaledContents(true);
    
    QHBoxLayout* smail_layout = new QHBoxLayout();
    smail_layout->addWidget(image);

    display = new QTextEdit();
    display->setMinimumHeight(80);
    display->setMaximumHeight(120); // делаем похожим по виду на QLineEdit
    display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
    display->setPlainText("Помоги мне заработать лучше...");

    keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
    
    connect(keyboard, &KeyBoard::buttonClicked, this, &KeyBoardWindow::onButtonClicked);
}

// --- Обработка физических нажатий кнопок клавиатуры (опционально, если нужно) ---
void biv::KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    const int key = event->nativeVirtualKey();
    if (keyboard->is_key_allowed(key)) {
        display->setPlainText(display->toPlainText() + keyboard->get_key_text(key));
        keyboard->animate_button(key);
    }
}

// --- Обработка кликов по виртуальной клавиатуре ---
void biv::KeyBoardWindow::onButtonClicked(const QString& text) {
    bool wasReadOnly = display->isReadOnly();
    display->setReadOnly(false);
    display->moveCursor(QTextCursor::End);

    if (text.isEmpty()) {
        display->insertPlainText(" ");
    } else if (text == "Удалить") {
        // Удалить последний символ
        QTextCursor cursor = display->textCursor();
        cursor.movePosition(QTextCursor::End);
        // выделить последний символ
        cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
    } else {
        display->insertPlainText(text);
    }

    display->setReadOnly(wasReadOnly);
}
