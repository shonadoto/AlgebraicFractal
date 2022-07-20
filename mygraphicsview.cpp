#include "mygraphicsview.h"

int itr = 0;


void MyGraphicsView::draw(int mod, ComplexNumber C = ComplexNumber(0, 0)) {
  mod_ = mod, C_ = C;
  scene()->clear();
  setSceneRect(0, 0, width(), height());
  pix_img_ = new QPixmap();
  int w = width(), h = height();
  QImage * image = new QImage(w, h, QImage::Format_RGB32);
  for  (int i = 0; i < w; ++i)
    for (int j = 0; j < h; ++j)
      image->setPixelColor(i, j, QColor(Qt::white));
  if (mod_ == 2) {/*
      image->setPixelColor(0, 0, QColor(Qt::magenta));
      image->setPixelColor(w - 1, 0, QColor(Qt::magenta));
      image->setPixelColor(0, h - 1, QColor(Qt::magenta));
      image->setPixelColor(w - 1, h - 1, QColor(Qt::magenta));*/
      image->setPixelColor(0, 0, QColor(rng() % 256, rng() % 256, rng() % 256));
      image->setPixelColor(w - 1, 0, QColor(rng() % 256, rng() % 256, rng() % 256));
      image->setPixelColor(0, h - 1, QColor(rng() % 256, rng() % 256, rng() % 256));
      image->setPixelColor(w - 1, h - 1, QColor(rng() % 256, rng() % 256, rng() % 256));
      qDebug() << width() * height();
      itr = 0;
      drawStohastic(0, 0, w - 1, h - 1, image);
      pix_img_->convertFromImage(*image);
      QLabel* label = new QLabel();
      label->setPixmap(*pix_img_);
      scene_->addWidget(label);
      delete(pix_img_);
      return;
    }
  for (int i = 0; i < w - 1; ++i) {
      for (int j = 0; j < h - 1; ++j) {
          QPair<double, double> coords = getCoords(i, j);
          QColor clr;
          if (mod == Mondelbroth)
            clr = getMondColor(coords);
          else if (mod == Julia)
            clr = getJuliaColor(coords, C);
          image->setPixelColor(i, j, clr);
          //scene_->addLine(i,j, i + 1, j + 1, QPen(clr));
        }
    }
  pix_img_->convertFromImage(*image);
  QLabel* label = new QLabel();
  label->setPixmap(*pix_img_);
  scene_->addWidget(label);
  delete(pix_img_);
}


void MyGraphicsView::keyPressEvent(QKeyEvent * event) {
  if (event->key() == Qt::Key_Minus) {
      if (resize_stack->size() > 1) {
          resize_stack->pop();
          x_range = resize_stack->top().first;
          y_range = resize_stack->top().second;
          scene_->clear();
          draw(mod_, C_);
        }
    }
  if (event->key() == Qt::Key_Plus) {
      double ax = (x_range.first + x_range.second) / 2;
      double dx = (x_range.second - x_range.first);
      x_range = {ax - dx / 4, ax + dx / 4};
      double ay = (y_range.first + y_range.second) / 2;
      double dy = (y_range.second - y_range.first);
      y_range = {ay - dy / 4, ay + dy / 4};
      resize_stack->push({x_range, y_range});
      scene_->clear();
      draw(mod_, C_);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event) {
  pressed_ = 1;
  zoom_rect_x_ = event->x(), zoom_rect_y_ = event->y();
  zoom_rect_ = scene_->addRect(zoom_rect_x_, zoom_rect_y_, 0, 0);
  zoom_rect_->setPen(QPen(QColor(Qt::gray), 2, Qt::DashLine));
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event) {
  if (!pressed_) return;
  zoom_rect_->setRect(zoom_rect_x_, zoom_rect_y_, event->x() - zoom_rect_x_, event->y() - zoom_rect_y_);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
  pressed_ = 0;
  x_range = {x_range.first + (x_range.second - x_range.first) * zoom_rect_x_/ width(), x_range.first + (x_range.second - x_range.first) * event->x() / width()};
  double y = y_range.first + (y_range.second - y_range.first) * zoom_rect_y_ / height();
  y_range = {y, y + (x_range.second - x_range.first) / width() * height()};
  resize_stack->push({x_range, y_range});
  scene_->clear();
  draw(mod_, C_);
}

void MyGraphicsView::resizeEvent(QResizeEvent* event) {
  QGraphicsView::resizeEvent(event);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scene_->clear();
  double range = 3;
  x_range = {-range, range};
  y_range = {-range / width() * height(), range / width() * height()};
  resize_stack = new std::stack<QPair<QPair<double, double>, QPair<double, double>>>;
  resize_stack->push({x_range, y_range});
  draw(mod_, C_);
}

QPair<double, double> MyGraphicsView::getCoords(int i, int j) {
  return {x_range.first + (x_range.second - x_range.first) / width() * i, y_range.first + (y_range.second - y_range.first) / height() * j};
}

QColor MyGraphicsView::getMondColor(QPair<double, double> coords) {
  ComplexNumber z, C(coords.first, coords.second);
  int cnt = 255;
  while (cnt > 0) {
      if (z.mod() > INF)
        return QColor((cnt) % 256, (4 * cnt) % 256, (6 * cnt) % 256);
      z = z * z + C;
      cnt--;
    }
  return QColor((cnt) % 256, (4 * cnt) % 256, (6 * cnt) % 256);
}

QColor MyGraphicsView::getJuliaColor(QPair<double, double> coords, ComplexNumber C) {
  ComplexNumber z(coords.first, coords.second);
  int cnt = 255;
  while (cnt > 0) {
      if (z.mod() > INF)
        return QColor((cnt) % 256, (4 * cnt) % 256, (6 * cnt) % 256);
      z = z * z + C;
      cnt--;
    }
  return QColor((cnt) % 256, (4 * cnt) % 256, (6 * cnt) % 256);
}

void MyGraphicsView::preset() {
  double range = 1;
  x_range = {-range, range};
  y_range = {-range / width() * height(), range / width() * height()};
  resize_stack = new std::stack<QPair<QPair<double, double>, QPair<double, double>>>;
  resize_stack->push({x_range, y_range});
}

void MyGraphicsView::drawStohastic(int x1, int y1, int x2, int y2, QImage *& image) {
  if (x1 == x2 && y1 == y2) {
      return;
    }
  if (x1 + 1 == x2 && y1 + 1 == y2) {
      return;
    }

  if (x1 + 1 == x2 && y1 == y2)
    return;

  if (x1 == x2 && y1 + 1 == y2)
    return;

  //int rr = sqrt((x2 - x1 + 1) * (y2 - y1 + 1) * 1.0 / (width() * height() + 1)) * 256;
  int rr = (x2 - x1 + 1) * (y2 - y1 + 1) * 1.0 / (width() * height() + 1) * 256;
  //int rr = ((x2 - x1) * 1.0 / width() + (y2 - y1) * 1.0 / height()) / 2 * 256;
  if (rr == 0) rr = 1;
  int add = rr;
  int xm = (x1 + x2) / 2;
  int ym = (y1 + y2) / 2;

  image->pixelColor(x1, y1);

  MyColor c1(image->pixelColor(x1, y1)),
      c2(image->pixelColor(x2, y1)),
      c3(image->pixelColor(x2, y2)),
      c4(image->pixelColor(x1, y2));

  if (x1 == x2) {
      MyColor c5 = (c1 + c3 + add) / 2;
      image->setPixelColor(x1, ym, c5.getColor());
      drawStohastic(x1, y1, x1, ym, image);
      drawStohastic(x1, ym, x2, y2, image);
      return;
    }

  if (y1 == y2) {
      MyColor c5 = (c1 + c3 + add) / 2;
      image->setPixelColor(xm, y1, c5.getColor());
      drawStohastic(x1, y1, xm, y1, image);
      drawStohastic(xm, y1, x2, y2, image);
      return;
    }

  if (x1 + 1 == x2) {

      MyColor c5 = (c1 + c4 + add) / 2;
      MyColor c6 = (c2 + c3 + add) / 2;

      image->setPixelColor(x1, ym, c5.getColor());
      image->setPixelColor(x2, ym, c6.getColor());

      drawStohastic(x1, y1, x1, ym, image);
      drawStohastic(x1, ym, x1, y2, image);
      drawStohastic(x2, y1, x2, ym, image);
      drawStohastic(x2, ym, x2, y2, image);

      return;
    } else if (y1 + 1 == y2) {

      MyColor c5 = (c1 + c2 + add) / 2;
      MyColor c6 = (c3 + c4 + add) / 2;
      c5.getColor();

      image->setPixelColor(xm, y1, c5.getColor());
      image->setPixelColor(xm, y2, c6.getColor());

      drawStohastic(x1, y1, xm, y1, image);
      drawStohastic(xm, y1, x2, y2, image);
      drawStohastic(x1, y2, xm, y2, image);
      drawStohastic(xm, y2, x2, y2, image);

      return;
    }
  MyColor c5 = (c1 + c2 + add) / 2,
      c6 = (c2 + c3 + add) / 2,
      c7 = (c3 + c4 + add) / 2,
      c8 = (c1 + c4 + add) / 2;

  if (image->pixelColor(xm, y1) == QColor(Qt::white))
    image->setPixelColor(xm, y1, c5.getColor());

  if (image->pixelColor(x2, ym) == QColor(Qt::white))
    image->setPixelColor(x2, ym, c6.getColor());

  if (image->pixelColor(xm, y2) == QColor(Qt::white))
    image->setPixelColor(xm, y2, c7.getColor());

  if (image->pixelColor(x1, ym) == QColor(Qt::white))
    image->setPixelColor(x1, ym, c8.getColor());

  MyColor c9 = (c1 + c2 + c3 + c4 + add) / 4;

  image->setPixelColor(xm, ym, c9.getColor());

  drawStohastic(x1, y1, xm, ym, image);
  drawStohastic(xm, y1, x2, ym, image);
  drawStohastic(x1, ym, xm, y2, image);
  drawStohastic(xm, ym, x2, y2, image);

  return;
}
