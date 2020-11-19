#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H
#include <QObject>
#include <QString>
#include <QHash>
#include <QVector>
#include <functional>
#include <QKeyEvent>
#include "KeyState.h"

class KeyboardManager: public QObject
{
    Q_OBJECT
private:

    /**
     * Hash map for storing key state, only keys used by combo are saved in this map.
     */
    QHash<char, KeyState> keyState;

    /**
     * Vector for storing registered combo.
     */
    QVector<QString> comboList;

    /**
     * initialize a key's state.
     *
     * @param key {const char}: key id in char
     */
    void keyInitialize(const char key);


    /**
     * check if all combo keys are pressed.
     *
     * @param combo {const QString&}: constant reference of combo string
     * @return {bool}: is all combo keys pressed or not
     */
    bool isAllKeysPressed(const QString& combo);

public:
    KeyboardManager(QObject *parent);

    KeyboardManager& addListeningCombo(QString combo);

    void deleteCombo(QString action);

public slots:
    void pressKey(QKeyEvent* k);

    void releaseKey(QKeyEvent* k);

signals:
    void comboPressed(const QString& combo);

};

#endif // KEYBOARDMANAGER_H
