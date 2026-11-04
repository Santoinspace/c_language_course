# C Programming Fundamentals · Course Materials

[简体中文](README.md) | **English**

Hands-on course materials for first-semester C programming students. Each week focuses on one real development tool — from getting your first program running in VS Code, to managing code with Git and building a graphical final project with raylib. Every guide follows the same structure: preparation → step-by-step walkthrough → FAQ → homework → self-check, with screenshots and a companion `checklist.md`.

> **Note:** the course documents themselves are written in Simplified Chinese. This English README is a repository overview.

> The repository grows with the course and currently contains materials for Weeks 1–5 plus the final project.

## Purpose

For beginners, the real obstacle is rarely the language — it is the environment: `gcc is not recognized`, spaces or non-ASCII characters in a path, CMake failing to find a compiler. This repository splits the course toolchain into six weeks, each solving one class of problems:

- Get the full **edit → compile → run → debug** loop working;
- Learn to use an **AI coding assistant** for study and troubleshooting;
- Manage multi-file projects with **CMake** and code history with **Git**;
- Get to know another beginner-friendly IDE and finish a runnable **raylib graphics project**.

Each week stands on its own and can be read independently; read in order, they build on one another — later weeks assume the previous week's environment is already set up.

## Weekly overview

| Week | Topic | What you will accomplish |
| --- | --- | --- |
| 1 | [Basic tool setup](week1/基本工具安装.md) | Install VS Code and MinGW-w64 GCC, configure PATH, extensions and debugging, run your first C program |
| 2 | [Claude Code setup](week2/ClaudeCode安装与配置.md) | Install the Claude Code extension and CC Switch, connect a ModelScope token, use an AI assistant inside VS Code |
| 3 | [CMake setup and usage](week3/CMake安装与使用.md) | Write `CMakeLists.txt`, build single- and multi-file projects out-of-source, create a static library |
| 4 | [Git setup and usage](week4/Git安装与使用.md) | Install and configure Git, commit, revert, ignore files, push to Gitee, with optional GitHub and branching |
| 5 | [RedPandaIDE setup and usage](week5/RedPandaIDE安装与使用.md) | Configure GCC in RedPanda C++, compile/run/debug with shortcuts, and work through a problem set |
| Final | [raylib graphics and project practice](weekFinal/raylib图形库与项目实操.md) | Configure, build, test and run the course project template, then start the final graphics assignment |

## Quick start

```powershell
git clone https://github.com/Santoinspace/c_language_course.git
```

1. Open `week1/基本工具安装.md` and start from the "课前准备" (preparation) section;
2. After each step, check yourself against the expected result in `week1/checklist.md`, and read the "避免" (pitfalls) column if it does not match;
3. Continue in order: Week 1 → Week 5 → Final.

> Commands in the guides are meant to run in **PowerShell, CMD, or the VS Code integrated terminal**. Installation and project paths should contain only ASCII characters and no spaces (e.g. `D:\Code`). The few steps that require Git Bash say so explicitly.

## Repository structure

```text
c_language_course/
├─ week1/                      # Week 1: basic tool setup
│  ├─ 基本工具安装.md           # Main guide
│  ├─ checklist.md             # Step-by-step checklist
│  └─ images/                  # Screenshots referenced by the guide
├─ week2/                      # Week 2: Claude Code setup
├─ week3/                      # Week 3: CMake setup and usage
├─ week4/                      # Week 4: Git setup and usage
├─ week5/                      # Week 5: RedPandaIDE setup and usage
├─ weekFinal/                  # Final: raylib graphics and project practice
├─ README.md                   # Chinese README
└─ README.en.md                # English README (this file)
```

Conventions:

- One directory per week (`weekN/`) with a single guide named after its Chinese topic, plus a `checklist.md`;
- All screenshots live in that week's `images/` and are referenced with relative paths, so the docs work offline after cloning;
- Every guide contains: objectives, preparation, walkthrough, FAQ, homework, self-check list, and image credits;
- The final-project template (raylib 6.0 + CMake) is distributed separately as course material and is not part of this repository.

## Environment and reading tips

| Item | Requirement |
| --- | --- |
| OS | Windows 11 (Windows 10 works too, though some screenshots and menus differ) |
| Paths | Use ASCII-only paths without spaces for installs, extraction and projects |
| Archive tool | 7-Zip or Bandizip (Windows 11 23H2+ can extract 7z natively) |
| Network | Needed for first-time steps such as downloading raylib |

Reading tips: start with the objectives to see what you should be able to do; use each guide's FAQ as a standalone troubleshooting reference; use the self-check list at the end for acceptance.

## Copyright and image credits

- The course-authored text, checklists and screenshots taken by the teaching assistant are copyright of this course and provided for teaching use.
- Some screenshots and procedures are adapted from public tutorials (CSDN, GitHub, GitHub Docs, Liao Xuefeng's Git tutorial, the official raylib site, etc.). Sources are credited in each guide's references and image-credits sections; copyright remains with the original authors.
- VS Code, MinGW-w64, Claude Code, CC Switch, ModelScope, CMake, Git, RedPandaIDE and raylib are products of their respective projects or companies. This repository is not affiliated with them.

## Feedback

If a step does not match your environment, an image is missing, or a command is wrong, feel free to open an [issue](https://github.com/Santoinspace/c_language_course/issues) or suggest a change on the relevant weekly guide.
