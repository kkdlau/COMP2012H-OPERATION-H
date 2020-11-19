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
     * @brief Hash map for storing key state, only keys used by combo are saved in this map.
     */
    QHash<char, KeyState> keyState;

    /**
     * @brief Vector for storing registered combo.
     */
    QVector<QString> comboList;

    /**
     * @brief Initialize a key's state.
     * @param key Key id in char
     */
    void keyInitialize(const char key);


    /**
     * @brief Check if all combo keys are pressed.
     * @param combo Constant reference of combo string
     * @return Is all combo keys pressed or not
     */
    bool isAllKeysPressed(const QString& combo);

public:
    KeyboardManager(QObject *parent);

    /**
     * @brief Add a combo to listening list. After adding to the listening list,
     * the Keyboard Manager listens and emit signal if all combo keys are pressed.
     *
     * @param combo: String representation of combo keys.
     * @return Ref. of KeyboardManager
     */
    KeyboardManager& addListeningCombo(QString combo);

    /**
     * @brief Remove a combo from listening list.
     * @param action String representation of combo keys.
     */
    void deleteCombo(QString action);

public slots:
    /**
     * @brief KeyPress event handler.
     * the Keyboard Manager determines keys' state based on this function.
     * This function should connect with KeyPressEvent.
     *
     * @param k Pointer of key event.
     */
    void pressKey(QKeyEvent* k);

    /**
     * @brief KeyRelease event handler.
     * the Keyboard Manager determines keys' state based on this function.
     * This function should connect with KeyReleaseEvent.
     *
     * @param k Pointer of key event.
     */
    void releaseKey(QKeyEvent* k);

signals:

    /**
     * @brief Signal of triggering combo.
     * If the Keyboard Manager detects any combo, it emits this signal with combo to be tirggered.
     *
     * @param combo Combo to be triggered in string representation
     */
    void comboPressed(const QString& combo);

};

#endif // KEYBOARDMANAGER_H
