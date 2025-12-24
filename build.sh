#!/bin/bash

set -e  # Остановка при ошибке

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="."
IMG_FOLDER="img"

# Создаем директорию сборки если её нет
if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir -p "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

# Генерируем файлы сборки
cmake -G "$BUILD_TYPE" "../$SOURCE_FOLDER"

# Собираем проект
cmake --build . -- -j$(nproc)

# Копируем ресурсы (изображения)
if [ ! -d "$IMG_FOLDER" ]; then
    mkdir -p "$IMG_FOLDER"
fi

if [ -f "../$IMG_FOLDER/grustnii-smail.png" ]; then
    cp "../$IMG_FOLDER/grustnii-smail.png" "$IMG_FOLDER/"
fi

cd ..

echo "Сборка завершена!"
echo "Исполняемый файл: $BUILD_FOLDER/keyboard"
