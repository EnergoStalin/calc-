# Умный(глупый) калькулятор

```
app
  --credit - Открывает кредитный калькулятор
  --deposit - Открывает дупозитный калькулятор
```
Без аргументов открывает обычный калькулятор

График появится после нажатия на равно в том случае если в выражении есть `x`
> Note: `=` не сработает если поле ввода в фокусе. используйте вместо жтого кнопку.

Для повторной отрисовки графа нажмите `Ctrl+R`.

Если нужно отрицательное число после бинарного оператора его нужно будет взять в скобки. `5-(-5)` это выражение будет равно 10 в тов ремя как `5--5` выдаст ошибку. Повторяющиеся подряд бинарные операторы не поддрживаются. Унарные операторы и функции могут быть использованны последовательно скобки опциональны но в таком случае на гарантирован порядок выполнения.

# Сборка
Для сборки используется xmake + make

## Зависимости
xmake сам поставить должен но он собирает всегда из сорсов а это долго в случае с qt так что лучше отдельно поставить.
- Qt5Base, QtGui, QtWidgets
- gtest
- qcustomplot(через xmake)

Под капотом [xmake](https://xmake.io)

## Основные цели
- build
- run
- test
- gcov_report
- clean
- fclean
- install

```sh
make run
```

# Установка
```sh
make install
```

Дата последнего коммита: Apr 29 2024
