#pragma once

#include <cstddef>

#include <QWidget>
#include <QGridLayout>
#include <QString>
#include <unordered_map>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"

namespace biv {
    class KeyBoard : public QWidget {
        Q_OBJECT

        private:
            const int button_width;
            std::unordered_map<int, KeyBoardButton*> buttons;

            KeyBoardData* keyboard_data;

            bool shift_ = false;
            bool caps_lock_ = false;

            void update_buttons_case(); 

            void create_buttons(
                const std::vector<KeyData>& data,
                QGridLayout* layout,
                const int line,
                const int start_position
            );

        public:
            KeyBoard(const int width, QWidget* parent = nullptr);

            void animate_button(const int code);
            QString get_key_text(const int code) const;
            bool is_key_allowed(const int code) const noexcept;
            void animateButtonByText(const QString& text);

              signals:
                  void buttonClicked(const QString& text);

              private slots:
                  void onButtonClicked(const QString& text);
          };
}
