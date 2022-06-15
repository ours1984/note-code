# note-code

![badge](https://img.shields.io/badge/-GTest-yellow?style=flat&logo=google)![badge](https://img.shields.io/badge/-glfw-orij?style=flat&logo=woo)
[![license](https://img.shields.io/github/license/xiaoqide/note-code.svg)](LICENSE)
[![note-code](https://img.shields.io/badge/opengl-code-brightgreen.svg?style=flat-square)](https://github.com/xiaoqide/note-code)

项目[opengl-note](https://github.com/xiaoqide/opengl-note)的配套代码

项目[gaames101-note](https://github.com/xiaoqide/gaames101-note)的配套代码

项目[grokking-note](https://github.com/xiaoqide/grokking-note)的配套代码

## 目录

- [note-code](#note-code)
  - [目录](#目录)
  - [背景](#背景)
  - [安装](#安装)
  - [使用](#使用)
    - [doc](#doc)
    - [opengl-note](#opengl-note)
    - [games101-note](#games101-note)
    - [grokking-note](#grokking-note)
    - [third](#third)
  - [贡献](#贡献)

## 背景

此仓库为本人学习笔记/教程的代码和资料

[![games101](https://github-readme-stats.vercel.app/api/pin/?username=xiaoqide&repo=opengl-note&show_owner)](https://github.com/xiaoqide/opengl-note)

[![games101](https://github-readme-stats.vercel.app/api/pin/?username=xiaoqide&repo=games101-note&show_owner)](https://github.com/xiaoqide/games101-note)

[![games101](https://github-readme-stats.vercel.app/api/pin/?username=xiaoqide&repo=grokking-note&show_owner)](https://github.com/xiaoqide/grokking-note)

为了教程的纯粹性,把项目配套代码单独列出一个仓库

## 安装

直接git克隆就可以了.注意到引用了googletest和glfw两个子仓库,所以按下面方式拉取代码

```bash
git clone --recursive https://github.com/xiaoqide/note-code.git 
```

window和linux和mac都可以.

## 使用

项目采用cmake生成,集成谷歌测试.依赖的三方库如下

- glew: OpenGL API查找模块,linux下直接`sudo apt install libglew-dev`
- glfw: 窗口运行环境,linux下直接`sudo apt install libglfw3-dev`
- googletest: 测试配套环境,linux下直接`sudo apt-get install libgtest-dev`
- eigen: 矩阵库.linux下直接`sudo apt install libeigen3-dev`
- glm: 数学库.linux下直接`sudo apt install libglm-dev`

### doc

- spec:  OpenGL规范相关文档
- games101-assignment: games所有作业要求

games101的ppt由于文件太大,单独开了一个仓库

[![games101](https://github-readme-stats.vercel.app/api/pin/?username=xiaoqide&repo=games101-ppt&show_owner)](https://github.com/xiaoqide/games101-ppt)

### opengl-note

从零开始学OpenGL系列教程配套代码,每一个文件对应[opengl-note](https://github.com/xiaoqide/opengl-note)的一篇文章

- [test_window(github)](opengl-note/test_window.cpp): [从零开始画窗口(blog)](https://blog.ours1984.top/posts/opengl-window)
- [test_triangle(github)](opengl-note/test_triangle.cpp): [从零开始画三角形(blog)](https://blog.ours1984.top/posts/opengl-triangle)
- [test_shader(github)](opengl-note/test_shader.cpp): [从零开始写着色器(blog)](https://blog.ours1984.top/posts/opengl-shader)
- [test_texture(github)](opengl-note/test_texture.cpp): [从零开始学纹理(blog)](https://blog.ours1984.top/posts/opengl-texture)
- [test_MVP(github)](opengl-note/test_camera.cpp): [从零开始学MVP(blog)](https://blog.ours1984.top/posts/opengl-camera)

### games101-note

games101课程的作业解答,每一个文件对应[games101-note](https://github.com/xiaoqide/games101-note)的一篇文章

- [Introduction(github)](games101-note/games101-01.md)：[看闫大神高屋建瓴(blog)](https://blog.ours1984.top/posts/games101-01)
- [Linear Algebra(github)](games101-note/games101-02.md)：[看闫大神讲线性代数(blog)](https://blog.ours1984.top/posts/games101-02)
- [Transformation(github)](games101-note/games101-03.md)：[看闫大神讲变形金刚(blog)](https://blog.ours1984.top/posts/games101-03)
- [Transformation Cout(github)](games101-note/games101-04.md)：[看闫大神讲观测和投影(blog)](https://blog.ours1984.top/posts/games101-04)

### grokking-note

图解算法的代码练习,每一个文件对应[grokking-note](https://github.com/xiaoqide/grokking-note)的一篇文章

- [search(github)](grokking-note/introduction.cpp)：[二分查找(blog)](https://blog.ours1984.top/posts/grokking-introduction)
- [sort(github)](grokking-note/sort.md)：[选择排序(blog)](https://blog.ours1984.top/posts/grokking-select)
- [Recursion(github)](grokking-note/grokking-recursion.md)：[递归(blog)](https://blog.ours1984.top/posts/grokking-recursion)
- [Quick(github)](grokking-note/grokking-quick.md)：[快速排序(blog)](https://blog.ours1984.top/posts/grokking-quick)
- [Map(github)](grokking-note/grokking-map.md)：[散列表(blog)](https://blog.ours1984.top/posts/grokking-map)
- [BFS(github)](grokking-note/grokking-bfs.md)：[广度优先搜索(blog)](https://blog.ours1984.top/posts/grokking-bfs)

### third

依赖的子项目

- softrender: 软光栅器,cpu实现OpenGL API和GLSL解析
- stb: 图像读取,音视频

## 贡献

PRs 是可以接受的.
