# opengl-note-code

![badge](https://img.shields.io/badge/-GTest-yellow?style=flat&logo=google)
![badge](https://img.shields.io/badge/-glfw-orij?style=flat&logo=woo)
[![license](https://img.shields.io/github/license/xiaoqide/opengl-note-code.svg)](LICENSE)
[![opengl-note-code](https://img.shields.io/badge/opengl-code-brightgreen.svg?style=flat-square)](https://github.com/xiaoqide/opengl-note-code)

项目[opengl-note](https://github.com/xiaoqide/opengl-note)的配套代码

## 目录

- [opengl-note-code](#opengl-note-code)
  - [目录](#目录)
  - [背景](#背景)
  - [安装](#安装)
  - [使用](#使用)
  - [贡献](#贡献)

## 背景

为了教程的纯粹性,把项目[opengl-note](https://github.com/xiaoqide/opengl-note)的配套代码单独列出一个仓库

## 安装

直接git克隆就可以了.注意到引用了googletest和glfw两个子仓库,所以按下面方式拉取代码

```bash
git clone --recursive https://github.com/xiaoqide/opengl-note-code.git 
```

window和linux和mac都可以.笔者使用vscode环境,在windows上搭配mingw编译

## 使用

项目采用cmake生成,集成谷歌测试.目录说明如下

- doc:  OpenGL规范相关文档
- glad: OpenGL API查找模块
- glfw: 窗口运行环境
- googletest: 测试配套环境
- src: 每一个文件应对[opengl-note](https://github.com/xiaoqide/opengl-note)的一篇教程
  - [test_window(github)](src/test_window.cpp): [从零开始画窗口(blog)](https://blog.ours1984.top/posts/opengl-window)
  - [test_triangle(github)](src/test_triangle.cpp): [从零开始画三角形(blog)](https://blog.ours1984.top/posts/opengl-triangle)
  - [test_shader(github)](src/test_shader.cpp): [从零开始学shader(blog)](https://blog.ours1984.top/posts/opengl-shader)

## 贡献

PRs 是可以接受的.
