#pragma once

#include <godot_cpp/classes/node2d.hpp>

namespace godot {
  class Print : public Node2D {
    GDCLASS(Print, Node2D)

  public:
    static void _bind_methods();

    void _process(double_t delta) override;

    void set_output(const String& output) {
      _output = output;
    }

    [[nodiscard]] String get_output() const {
      return _output;
    }

  private:
    String _output = "Hello World!";
  };
}
