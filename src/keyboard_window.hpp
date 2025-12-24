#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
    class KeyBoardWindow : public QWidget {
        Q_OBJECT
        
        private:
            QLineEdit* display;
            KeyBoard* keyboard;

        public:
            KeyBoardWindow(QWidget* parent = nullptr);
            
        private slots:
            void onButtonClicked(const QString& text);  // Новый слот
            
        protected:
            void keyPressEvent(QKeyEvent* event) override;
    };
}
