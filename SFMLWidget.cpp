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

#include "SFMLWidget.hpp"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

#include <QResizeEvent>

#include <SFML/Window/Event.hpp>

#include <iostream>


SFMLWidget::SFMLWidget(QWidget *parent) :
    QWidget(parent),
    m_circle(100)
{
    //Setup some states to allow direct rendering into the widget.
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_PaintUnclipped);

    //Set strong focus to enable keyboard events to be received.
    setFocusPolicy(Qt::StrongFocus);

    //Under X11, we need to flush the commands sent to the server to ensure that
    //SFML will get an updated view of the windows
#ifdef Q_WS_X11
    XFlush(QX11Info::display());
#endif

    // Create the SFML window with the Qt widget handle
    m_window.create(reinterpret_cast<sf::WindowHandle>(winId()));

    //m_window.setFramerateLimit(60);

    m_circle.setFillColor(sf::Color::Red);
}


QPaintEngine* SFMLWidget::paintEngine() const
{
    //We make the paintEvent function return a null paint engine. This functions works together with
    //the WA_PaintOnScreen flag to tell Qt that we're not using any of its built-in paint engines.
    return nullptr;
}


void SFMLWidget::enterEvent(QEvent *)
{
    setFocus();
}


void SFMLWidget::paintEvent(QPaintEvent *)
{
    draw();
}


void SFMLWidget::resizeEvent(QResizeEvent *event)
{
    // update the view to the new size of the window
    sf::FloatRect visibleArea(0.f, 0.f, event->size().width(), event->size().height());
    m_window.setView(sf::View(visibleArea));
}


void SFMLWidget::handleEvents()
{
    // check all the windows events
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            m_window.close();

        else if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
        }

        else if (event.type == sf::Event::KeyReleased)
        {
            // close if escape key was pressed
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }

            else if (event.key.code == sf::Keyboard::Space)
            {
                m_circle.setFillColor(sf::Color::Green);
            }
        }

        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                std::cout << "They see me scrolling: " << event.mouseWheelScroll.delta << std::endl;
            }
        }

        else if (event.type == sf::Event::MouseButtonReleased)
        {
            std::cout << "Mouse was clicked!" << std::endl;
        }
    }
}


void SFMLWidget::update()
{
    // update all the things
}


void SFMLWidget::draw()
{
    // clear the window to dark grey
    m_window.clear(sf::Color(50, 50, 50));

    // draw the circle
    m_window.draw(m_circle);

    // display the windows content
    m_window.display();
}
