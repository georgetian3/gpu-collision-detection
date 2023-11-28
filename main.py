#!/usr/bin/env python
# -*- coding: utf-8 -*-

from imgui.integrations.glfw import GlfwRenderer
from test_window import show_test_window
import OpenGL.GL as gl
import glfw
import imgui

class CollisionDetector:
    ...


def main():
    width, height = 1280, 720
    window_name = 'minimal ImGui/GLFW3 example'

    if not glfw.init():
        print('Could not initialize OpenGL context')
        return

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 0)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_TRUE)

    window = glfw.create_window(int(width), int(height), window_name, None, None)
    if not window:
        print('Could not initialize Window')
        glfw.terminate()
        return
    glfw.make_context_current(window)


    imgui.create_context()
    impl = GlfwRenderer(window)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        impl.process_inputs()

        imgui.new_frame()

        show_test_window()

        gl.glClearColor(1.0, 1.0, 1.0, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)

        imgui.render()
        impl.render(imgui.get_draw_data())
        glfw.swap_buffers(window)

    impl.shutdown()
    glfw.terminate()



if __name__ == '__main__':
    main()