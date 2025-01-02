#include <cmath>
#include <iterator>
#include <iostream>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"
#include "ImageTraversal.h"
namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    work_list.push_back(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    Point cur;
    if (!work_list.empty()) {
      cur = work_list.front();
      work_list.pop_front();
    }
    return cur;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    Point cur;
    if (!work_list.empty()) {
      cur = work_list.back();
      work_list.pop_back();
    }
    return cur;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    work_list.push_back(start);
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    traversal_add_ = traversal_add;
    traversal_pop_ = traversal_pop;
    visited_ = std::vector<std::vector<bool>> (png.width(), std::vector<bool>(png.height(), false));
  }
  ImageTraversal::Iterator::Iterator(const PNG & png, ImageTraversal * traversal, const Point & start, const Point & current, std::vector<std::vector<bool>>& visited,std::deque<Point>& list) {
    png_ = png;
    traversal_ = traversal;
    start_ = start;
    current_ = current;
    visited_=visited;
    work_list=list;
  }
  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    return Iterator(png_, this, start_, start_, visited_, work_list);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    return Iterator(png_, this, Point(-1, -1), Point(-1, -1), visited_, work_list);
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {}


  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    Point cur;
    cur = traversal_->traversal_pop_(work_list);
    if (!visited_[cur.x][cur.y]) {
      visited_[cur.x][cur.y] = true;//access each which is not accessed
      HSLAPixel & start = png_.getPixel(start_.x, start_.y);
      HSLAPixel & curP = png_.getPixel(cur.x, cur.y);
      if (cur.x+1 < png_.width()) {//check tolerance for each neightbor and add each neightbor of point
        HSLAPixel right = png_.getPixel(cur.x+1, cur.y);
        if (calculateDelta(start, right) < traversal_->tolerance_) {
          traversal_->traversal_add_(work_list, Point(cur.x+1, cur.y));
        }
      }
      if (cur.y+1 < png_.height()) {
        HSLAPixel down = png_.getPixel(cur.x, cur.y+1);
        if (calculateDelta(start, down) < traversal_->tolerance_) {
          traversal_->traversal_add_(work_list, Point(cur.x, cur.y+1));
        }
      }
      if (cur.x > 0) {
          HSLAPixel left = png_.getPixel(cur.x-1, cur.y);
          if (calculateDelta(start, left) < traversal_->tolerance_) {
            traversal_->traversal_add_(work_list, Point(cur.x-1, cur.y));
          }
      }
      if (cur.y > 0) {
        HSLAPixel up = png_.getPixel(cur.x, cur.y-1);
        if (calculateDelta(start, up) < traversal_->tolerance_) {
          traversal_->traversal_add_(work_list, Point(cur.x, cur.y-1));
        }
      }

      if(traversal_->traversal_pop_==bfs_pop){
        if(!work_list.empty()){
          current_ = work_list.front();
          while(visited_[current_.x][current_.y]){
            traversal_->traversal_pop_(work_list);
            if(!work_list.empty()){
              current_ = work_list.front();
            }
            else {
              return *this;
            }
          }
        } else{
          return *this;
        }
      }else{
        if(!work_list.empty()){
          current_ = work_list.back();
          while(visited_[current_.x][current_.y]){
            traversal_->traversal_pop_(work_list);
            if(!work_list.empty()){
              current_ = work_list.back();
            }
            else {
              return *this;
            }
          }
        } else{
          return *this;
        }
      }
      return *this;
    }
    return *this;
  }

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    return current_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    return !work_list.empty();
  }
}