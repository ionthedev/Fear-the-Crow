#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "print.h"

using namespace godot;

void Print::_process(const double_t delta) {
  Node::_process(delta);

  const Input& input = *Input::get_singleton();

  if (input.is_action_just_pressed("ui_accept")) {
    UtilityFunctions::print(_output);
  }
}

void Print::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_output"), &Print::get_output);
  ClassDB::bind_method(D_METHOD("set_output", "output"), &Print::set_output);

  ADD_PROPERTY(PropertyInfo(Variant::STRING, "output"), "set_output", "get_output");
}
