#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTextCursor>

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
    display->setMaximumHeight(120); // похожая высота как у QLineEdit
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

// --- Ввод с обычной клавиатуры ---
void biv::KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    int qtKey = event->key();

    // --- Ввод букв, цифр, знаков ---
    if (event->text().size() && event->text()[0].isPrint()) {
        bool wasReadOnly = display->isReadOnly();
        display->setReadOnly(false);
        display->moveCursor(QTextCursor::End);
        display->insertPlainText(event->text());
        display->setReadOnly(wasReadOnly);
        // Теперь красиво: вызываем метод у клавиатуры!
        keyboard->animateButtonByText(event->text());
        return;
    }


    switch (qtKey) {
        case Qt::Key_Space:
        {
            bool wasReadOnly = display->isReadOnly();
            display->setReadOnly(false);
            display->moveCursor(QTextCursor::End);
            display->insertPlainText(" ");
            display->setReadOnly(wasReadOnly);
            break;
        }
        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            bool wasReadOnly = display->isReadOnly();
            display->setReadOnly(false);
            display->moveCursor(QTextCursor::End);
            display->insertPlainText("\n");
            display->setReadOnly(wasReadOnly);
            break;
        }
        case Qt::Key_Backspace:
        {
            bool wasReadOnly = display->isReadOnly();
            display->setReadOnly(false);
            QTextCursor cursor = display->textCursor();
            cursor.movePosition(QTextCursor::End);
            cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
            display->setReadOnly(wasReadOnly);
            break;
        }
        case Qt::Key_Tab:
        {
            bool wasReadOnly = display->isReadOnly();
            display->setReadOnly(false);
            display->moveCursor(QTextCursor::End);
            display->insertPlainText("\t");
            display->setReadOnly(wasReadOnly);
            break;
        }
        default:
            QWidget::keyPressEvent(event); // стандартная обработка для прочих клавиш
    }
}

// --- Ввод через виртуальные кнопки ---
void biv::KeyBoardWindow::onButtonClicked(const QString& text) {
    bool wasReadOnly = display->isReadOnly();
    display->setReadOnly(false);
    display->moveCursor(QTextCursor::End);

    if (text.isEmpty()) {
        display->insertPlainText(" ");
    } else if (text == "Удалить") {
        QTextCursor cursor = display->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
    } else {
        display->insertPlainText(text);
    }

    display->setReadOnly(wasReadOnly);
}
