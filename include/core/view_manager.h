// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_VIEW_MANAGER_H
#define RTORRENT_CORE_VIEW_MANAGER_H

#include <string>
#include <torrent/utils/unordered_vector.h>

#include "core/view.h"

namespace core {

class ViewManager : public torrent::utils::unordered_vector<View*> {
public:
  using base_type   = torrent::utils::unordered_vector<View*>;
  using filter_args = std::list<std::string>;

  using base_type::const_iterator;
  using base_type::const_reverse_iterator;
  using base_type::iterator;
  using base_type::reverse_iterator;

  using base_type::size_type;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::empty;
  using base_type::size;

  ~ViewManager() {
    clear();
  }

  // Ffff... Just throwing together an interface, need to think some
  // more on this.

  void clear();

  iterator insert(const std::string& name);
  void     insert_throw(const std::string& name) {
    insert(name);
  }

  // When erasing, just 'disable' the view so that the users won't
  // suddenly find their pointer dangling?

  iterator find(const std::string& name);
  iterator find_throw(const std::string& name);
  View*    find_ptr_throw(const std::string& name) {
    return *find_throw(name);
  }

  // If View::last_changed() is less than 'timeout' seconds ago, don't
  // sort.
  //
  // Find a better name for 'timeout'.
  void sort(const std::string& name, uint32_t timeout = 0);

  // These could be moved to where the command is implemented.
  void set_sort_new(const std::string& name, const torrent::Object& cmd) {
    (*find_throw(name))->set_sort_new(cmd);
  }
  void set_sort_current(const std::string& name, const torrent::Object& cmd) {
    (*find_throw(name))->set_sort_current(cmd);
  }

  void set_filter(const std::string& name, const torrent::Object& cmd);
  void set_filter_temp(const std::string& name, const torrent::Object& cmd);
  void set_filter_on(const std::string& name, const filter_args& args);

  void set_event_added(const std::string& name, const torrent::Object& cmd) {
    (*find_throw(name))->set_event_added(cmd);
  }
  void set_event_removed(const std::string& name, const torrent::Object& cmd) {
    (*find_throw(name))->set_event_removed(cmd);
  }
};

}

#endif
