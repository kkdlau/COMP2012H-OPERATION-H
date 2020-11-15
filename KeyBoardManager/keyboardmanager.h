#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H
#include <QString>
#include <QHash>
#include <QVector>
#include <functional>

enum class KeyState {
    RELEASE,
    PRESSED,
    PRESSING
};

class KeyboardManager
{
private:
    QHash<const QString, std::function<void(void)>> actionList;
    QHash<char, KeyState> keyState;
    QVector<QString> comboList;

    void keyInitialize(const char key);

    void iterateAvailable();

    bool isAllKeysPressed(const QString& combo);

public:
    KeyboardManager();

    void addCombo(QString combo, std::function<void(void)> process);

    void deleteCombo(QString action);

    void pressKey(const char key);

    void releaseKey(const char key);
};

#endif // KEYBOARDMANAGER_H
