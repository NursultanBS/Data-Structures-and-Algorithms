#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  _traversal = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, PNG png, Point start, double tolerance) {
  _traversal = traversal;
  _png = png;
  _start = start;
  _cur = start;
  _tolerance = tolerance;
  _visited.resize(_png.width());
  for (unsigned i = 0; i < _png.width(); ++i) {
    _visited[i].resize(_png.height());
    for (unsigned j = 0; j < _png.height(); ++j) {
      _visited[i][j] = false;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  _visited[_cur.x][_cur.y] = true;
  while(!_traversal->empty() && (_visited[_traversal->peek().x][_traversal->peek().y] == true)) {
    _traversal->pop();
  }

  Point right = Point(_cur.x + 1, _cur.y);
  Point down = Point(_cur.x, _cur.y + 1);
  Point left = Point(_cur.x - 1, _cur.y);
  Point up = Point(_cur.x, _cur.y - 1);

  double Delta;
  if (right.x < _png.width() && right.y < _png.height()) {
    if (_visited[right.x][right.y] == false) {
      Delta = calculateDelta(_png.getPixel(_start.x, _start.y), _png.getPixel(right.x, right.y));
      if (Delta < _tolerance) {
        _traversal->add(right);
      }
    }
  }

  if (down.x < _png.width() && down.y < _png.height()){
    if (_visited[down.x][down.y] == false) {
      Delta = calculateDelta(_png.getPixel(_start.x, _start.y), _png.getPixel(down.x, down.y));
      if (Delta < _tolerance) {
        _traversal->add(down);
      }
    }
  }

  if (left.x < _png.width() && left.y < _png.height()) {
    if (_visited[left.x][left.y] == false) {
      Delta = calculateDelta(_png.getPixel(_start.x, _start.y), _png.getPixel(left.x, left.y));
      if (Delta < _tolerance) {
        _traversal->add(left);
      }
    }
  }

  if (up.x < _png.width() && up.y < _png.height()) {
    if(_visited[up.x][up.y] == false) {
      Delta = calculateDelta(_png.getPixel(_start.x, _start.y), _png.getPixel(up.x, up.y));
      if (Delta < _tolerance) {
        _traversal->add(up);
      }
    }
  }

  if (!_traversal->empty()) {
    _cur = _traversal->peek();
  } else {
    _traversal = NULL;
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return _cur;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->_traversal == NULL && other._traversal == NULL);
}

