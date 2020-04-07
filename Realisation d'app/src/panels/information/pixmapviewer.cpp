/***************************************************************************
 *   Copyright (C) 2006 by Peter Penz <peter.penz19@gmail.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/

#include "pixmapviewer.h"

#include <KIconLoader>

#include <QImageReader>
#include <QMovie>
#include <QPainter>
#include <QStyle>

PixmapViewer::PixmapViewer(QWidget* parent, Transition transition) :
    QWidget(parent),
    m_animatedImage(nullptr),
    m_transition(transition),
    m_animationStep(0),
    m_sizeHint(),
    m_hasAnimatedImage(false)
{
    setMinimumWidth(KIconLoader::SizeEnormous);
    setMinimumHeight(KIconLoader::SizeEnormous);

    m_animation.setDuration(150);
    m_animation.setCurveShape(QTimeLine::LinearCurve);

    if (m_transition != NoTransition) {
        connect(&m_animation, &QTimeLine::valueChanged, this, QOverload<>::of(&PixmapViewer::update));
        connect(&m_animation, &QTimeLine::finished, this, &PixmapViewer::checkPendingPixmaps);
    }
}

PixmapViewer::~PixmapViewer()
{
}

void PixmapViewer::setPixmap(const QPixmap& pixmap)
{
    if (pixmap.isNull()) {
        return;
    }

    // Avoid flicker with static pixmap if an animated image is running
    if (m_animatedImage && m_animatedImage->state() == QMovie::Running) {
        return;
    }

    if ((m_transition != NoTransition) && (m_animation.state() == QTimeLine::Running)) {
        m_pendingPixmaps.enqueue(pixmap);
        if (m_pendingPixmaps.count() > 5) {
            // don't queue more than 5 pixmaps
            m_pendingPixmaps.takeFirst();
        }
        return;
    }

    m_oldPixmap = m_pixmap.isNull() ? pixmap : m_pixmap;
    m_pixmap = pixmap;
    update();

    const bool animateTransition = (m_transition != NoTransition) &&
                                   (m_pixmap.size() != m_oldPixmap.size());
    if (animateTransition) {
        m_animation.start();
    } else if (m_hasAnimatedImage) {
        // If there is no transition animation but an animatedImage
        // and it is not already running, start animating now
        if (m_animatedImage->state() != QMovie::Running) {
            m_animatedImage->setScaledSize(m_pixmap.size());
            m_animatedImage->start();
        }
    }
}

void PixmapViewer::setSizeHint(const QSize& size)
{
    if (m_animatedImage && size != m_sizeHint) {
        m_animatedImage->stop();
    }

    m_sizeHint = size;
    updateGeometry();
}

QSize PixmapViewer::sizeHint() const
{
    return m_sizeHint;
}

void PixmapViewer::setAnimatedImageFileName(const QString &fileName)
{
    if (!m_animatedImage) {
        m_animatedImage = new QMovie(this);
        connect(m_animatedImage, &QMovie::frameChanged, this, &PixmapViewer::updateAnimatedImageFrame);
    }

    if (m_animatedImage->fileName() != fileName) {
        m_animatedImage->stop();
        m_animatedImage->setFileName(fileName);
    }

    m_hasAnimatedImage = m_animatedImage->isValid() && (m_animatedImage->frameCount() > 1);
}


QString PixmapViewer::animatedImageFileName() const
{
    if (!m_hasAnimatedImage) {
        return QString();
    }
    return m_animatedImage->fileName();
}

void PixmapViewer::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    if (m_transition != NoTransition || (m_hasAnimatedImage && m_animatedImage->state() != QMovie::Running)) {
        const float value = m_animation.currentValue();
        const int scaledWidth  = static_cast<int>((m_oldPixmap.width()  * (1.0 - value)) + (m_pixmap.width()  * value));
        const int scaledHeight = static_cast<int>((m_oldPixmap.height() * (1.0 - value)) + (m_pixmap.height() * value));

        const bool useOldPixmap = (m_transition == SizeTransition) &&
                                  (m_oldPixmap.width() > m_pixmap.width());
        const QPixmap& largePixmap = useOldPixmap ? m_oldPixmap : m_pixmap;
        if (!largePixmap.isNull()) {
            const QPixmap scaledPixmap = largePixmap.scaled(scaledWidth,
                                                            scaledHeight,
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::FastTransformation);

            style()->drawItemPixmap(&painter, rect(), Qt::AlignCenter, scaledPixmap);
        }
    } else {
        style()->drawItemPixmap(&painter, rect(), Qt::AlignCenter, m_pixmap);
    }
}

void PixmapViewer::checkPendingPixmaps()
{
    if (!m_pendingPixmaps.isEmpty()) {
        QPixmap pixmap = m_pendingPixmaps.dequeue();
        m_oldPixmap = m_pixmap.isNull() ? pixmap : m_pixmap;
        m_pixmap = pixmap;
        update();
        m_animation.start();
    } else if (m_hasAnimatedImage) {
        m_animatedImage->setScaledSize(m_pixmap.size());
        m_animatedImage->start();
    } else {
        m_oldPixmap = m_pixmap;
    }
}

void PixmapViewer::updateAnimatedImageFrame()
{
    Q_ASSERT (m_animatedImage);

    m_pixmap = m_animatedImage->currentPixmap();
    update();
}

void PixmapViewer::stopAnimatedImage()
{
    if (m_hasAnimatedImage) {
        m_animatedImage->stop();
        m_hasAnimatedImage = false;
    }
}

bool PixmapViewer::isAnimatedImage(const QString &fileName)
{
    const QByteArray imageFormat = QImageReader::imageFormat(fileName);
    return !imageFormat.isEmpty() && QMovie::supportedFormats().contains(imageFormat);
}
