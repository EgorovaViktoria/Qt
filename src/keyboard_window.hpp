#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QTextEdit>        // было #include <QLineEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
    class KeyBoardWindow : public QWidget {
        Q_OBJECT
        
        private:
            QTextEdit* display;         // было QLineEdit*
            KeyBoard* keyboard;

        public:
            KeyBoardWindow(QWidget* parent = nullptr);
            
        private slots:
            void onButtonClicked(const QString& text);
            
        protected:
            void keyPressEvent(QKeyEvent* event) override;
    };
}
