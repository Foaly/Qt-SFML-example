////////////////////////////////////////////////////////////
//
// Qt SFML example - Setting up a SFML window inside a Qt window
// Copyright (C) 2016 Maximilian Wagenbach
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFMLWIDGET_HPP
#define SFMLWIDGET_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <QWidget>


class SFMLWidget : public QWidget
{
public:
    SFMLWidget(QWidget* parent = nullptr);

    void handleEvents();

    void update();

    void draw();

private:
    QPaintEngine *paintEngine() const;

    void enterEvent(QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;


    sf::RenderWindow                m_window;
    sf::View                        m_view;
    sf::CircleShape                 m_circle;
};


#endif //SFMLWIDGET_HPP
